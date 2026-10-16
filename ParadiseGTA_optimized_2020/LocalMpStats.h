//Local MP stats saves
//
//GTA Online stats normally live in the Rockstar cloud: the MP stats savegame operations upload a slot's serialized
//(and platform encrypted) stats with an HTTP POST and download them with a GET, as
//"GTA5/saves/mpstats/save_default0000.save" (slot 0, shared) and "save_char0001.save" / "save_char0002.save"
//(characters 1 and 2). With the cloud gone, both requests are replaced with file I/O on the console, so the game's
//own serialization, encryption and load/save logic stay untouched: a save writes exactly what it would upload and a
//load hands back exactly what it would download.
//
//1.27 EBOOT (names from IDA/PS3/1.27/EBOOT.map where available):
//  0x12A60B0 MP stats load op: isCloudAvailable -> 0x129E478 (GET into the request at op+0x18) -> wait for the request
//            status -> 0x12A5FEC applies the data
//  0x12A7574 MP stats save op: serialize, encrypt -> isCloudAvailable -> 0x129E5B4 (POST, request at op+0x20) -> wait
//  0x129E478 / 0x129E5B4 have no other callers, so they are replaced outright (PatchInJump2).
//  Request: [0] status (1 pending, 2 failed, 3 succeeded), [1] HTTP code, [2] type (1 GET, 2 POST), +0xC response
//  buffer (GET), a rage grow buffer: [0] data, [1] capacity, [2] length, [3] flags, [4] allocator, [6] device handle.
//  The real GET sets it up with 0xA8AEB8(buffer, network allocator *0x1CF72D8, 4, 0x100) and the download is written
//  into it through fiDeviceGrowBuffer, whose Write (vtable +0x28) is 0xA8B0E4(buffer, src, len): append, growing with
//  the buffer's allocator. The local GET does exactly that, so a load uses the game's own memory, the same amount a
//  real cloud load would, and the game frees it after parsing. The SPRX itself allocates nothing (PS3 memory is too
//  tight: a 64 KB static buffer here made the game crash at boot).
//  isCloudAvailable (0x12DB918) gates the stats save manager (0x1DDDAC8) and both ops. It also backs the
//  NETWORK_IS_CLOUD_AVAILABLE native the scripts use, so only the call sites on the MP stats path are patched to
//  "li r3,1".
//Research notes: research/temp-character-mode.md

#if TEMPCHAR_DEBUG == 1
//debug log for testing on hardware, shared with TempCharacter.h. Written next to the other Paradise files, since a game
//can't create files in the root of dev_hdd0. Fsynced so the last lines before a crash are on disk
#define TEMPCHAR_LOG_FILE "/dev_hdd0/tmp/gopro_2027/tempchar_log.txt"

void tempcharLog(const char *fmt, ...) {
	char buf[200];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, sizeof(buf), fmt, args);
	va_end(args);
	int fd;
	uint64_t written;
	if (cellFsOpen(TEMPCHAR_LOG_FILE, CELL_FS_O_RDWR | CELL_FS_O_APPEND | CELL_FS_O_CREAT, &fd, NULL, 0) != CELL_FS_SUCCEEDED)
		return;
	cellFsWrite(fd, (const void*)buf, (uint64_t)strlen(buf), &written);
	cellFsFsync(fd);
	cellFsClose(fd);
}
#endif

namespace LocalMpStats {

	#define LOCAL_MP_STATS_DIR "/dev_hdd0/tmp/gopro_2027/"

	const unsigned int CLOUD_GET = 0x129E478;//only caller: MP stats load op
	const unsigned int CLOUD_POST = 0x129E5B4;//only caller: MP stats save op
	const unsigned int IS_CLOUD_AVAILABLE = 0x12DB918;
	const unsigned int LI_R3_1 = 0x38600001;

	//isCloudAvailable calls on the MP stats path (stats save manager, STAT_LOAD, the two ops). Not patched: 0x3298A4
	//(tunables) and the other savegame-module callers (CCloudManager files, UGC).
	const unsigned int CLOUD_CHECK_SITES[] = {
		0x32B01C,//0x32AFF4
		0x32B0D4,//0x32B03C, save trigger
		0x32B2A0, 0x32B340,//0x32B238
		0x32B728, 0x32B7E4,//0x32B6B0, load start
		0x32BD54,//0x32BD3C, stats save manager update
		0x32CA24, 0x32CABC,//0x32C9B8, load
		0x433AA0,//STAT_LOAD native
		0x12A614C,//load op
		0x12A7880,//save op
	};
	const int CLOUD_CHECK_SITE_COUNT = sizeof(CLOUD_CHECK_SITES) / sizeof(CLOUD_CHECK_SITES[0]);

	const int REQUEST_STATUS_FAILED = 2;
	const int REQUEST_STATUS_SUCCEEDED = 3;
	const unsigned int MAX_SAVE_SIZE = 0x10000;//the POST refuses anything bigger

	const unsigned int GROW_BUFFER_INIT = 0xA8AEB8;//(buffer, allocator, flags, grow step)
	const unsigned int GROW_BUFFER_APPEND = 0xA8B0E4;//(buffer, src, len), returns bytes appended
	const unsigned int CLOUD_ALLOCATOR = 0x1CF72D8;//allocator the real GET hands its response buffer (0x12D87D8)
	const int GROW_BUFFER_FLAGS = 4;//keep a terminating 0 byte, as the real GET
	const int GROW_BUFFER_STEP = 0x100;
	const int LOAD_CHUNK_SIZE = 256;//stack chunk the file is streamed through

	//"GTA5/saves/mpstats/save_char0001.save" -> "/dev_hdd0/tmp/gopro_2027/mpstats_save_char0001.save"
	void localPath(char *out, int outSize, const char *cloudPath) {
		const char *name = cloudPath;
		for (const char *p = cloudPath; *p; p++)
			if (*p == '/')
				name = p + 1;
		snprintf(out, outSize, LOCAL_MP_STATS_DIR "mpstats_%s", name);
	}

	void slotPath(char *out, int outSize, int slot) {
		char cloudName[40];
		snprintf(cloudName, sizeof(cloudName), "%s%04d.save", slot == 0 ? "save_default" : "save_char", slot);
		localPath(out, outSize, cloudName);
	}

	bool hasSlotSave(int slot) {
		char path[100];
		slotPath(path, sizeof(path), slot);
		CellFsStat st;
		return cellFsStat(path, &st) == CELL_FS_SUCCEEDED && st.st_size > 0;
	}

	//loads actually served from a file. STAT_LOAD can report success without loading anything (see TempCharacter.h),
	//so the character load checks this went up
	int servedLoads = 0;

	//replaces 0x129E478 (request, path, rockstar permissions, ...). Returns nonzero when the request was started
	int localCloudGet(int *request, const char *cloudPath, unsigned int r5, unsigned int r6, unsigned int r7) {
		char path[100];
		localPath(path, sizeof(path), cloudPath);
		int *response = (int*)((int)request + 0xC);
		request[1] = 0;
		request[2] = 1;
		//same setup as the real GET; this also releases whatever the buffer held from the last load
		call<int>(GROW_BUFFER_INIT)(response, *(volatile int*)CLOUD_ALLOCATOR, GROW_BUFFER_FLAGS, GROW_BUFFER_STEP);
		int size = 0;
		int failCode = 404;//no file (or an empty one): what the cloud answers for a player that never saved
		int fd;
		if (cellFsOpen(path, CELL_FS_O_RDONLY, &fd, NULL, 0) == CELL_FS_SUCCEEDED) {
			char chunk[LOAD_CHUNK_SIZE];
			while (true) {
				uint64_t read = 0;
				if (cellFsRead(fd, chunk, LOAD_CHUNK_SIZE, &read) != CELL_FS_SUCCEEDED) {
					failCode = 500;
					size = -1;
					break;
				}
				if (read == 0)
					break;
				if (size + (int)read > (int)MAX_SAVE_SIZE ||
					call<int>(GROW_BUFFER_APPEND)(response, chunk, (unsigned int)read) != (int)read) {
					failCode = 500;//too big, or the game's allocator couldn't grow the buffer
					size = -1;
					break;
				}
				size += (int)read;
			}
			cellFsClose(fd);
		}
		//the load op frees the buffer in its cleanup either way
		if (size > 0) {
			servedLoads++;
			request[1] = 200;
			request[0] = REQUEST_STATUS_SUCCEEDED;
		} else {
			request[1] = failCode;
			request[0] = REQUEST_STATUS_FAILED;
		}
#if TEMPCHAR_DEBUG == 1
		tempcharLog("[mpstats] load %s: %i bytes\n", path, size);
#endif
		return 1;
	}

	//replaces 0x129E5B4 (request, data, size, path, rockstar permissions, ...)
	int localCloudPost(int *request, const char *data, unsigned int size, const char *cloudPath, unsigned int r7, unsigned int r8) {
		char path[100];
		localPath(path, sizeof(path), cloudPath);
		request[1] = 0;
		request[2] = 2;
		bool ok = false;
		if (data != 0 && size != 0 && size <= MAX_SAVE_SIZE) {
			//write to a temp file first so a crash mid-write never leaves a broken save behind
			char tmpPath[110];
			snprintf(tmpPath, sizeof(tmpPath), "%s.tmp", path);
			int fd;
			if (cellFsOpen(tmpPath, CELL_FS_O_WRONLY | CELL_FS_O_CREAT | CELL_FS_O_TRUNC, &fd, NULL, 0) == CELL_FS_SUCCEEDED) {
				uint64_t written = 0;
				ok = cellFsWrite(fd, data, size, &written) == CELL_FS_SUCCEEDED && written == size;
				cellFsFsync(fd);
				cellFsClose(fd);
				if (ok) {
					cellFsUnlink(path);
					ok = cellFsRename(tmpPath, path) == CELL_FS_SUCCEEDED;
				}
			}
		}
		request[1] = ok ? 200 : 500;
		request[0] = ok ? REQUEST_STATUS_SUCCEEDED : REQUEST_STATUS_FAILED;
#if TEMPCHAR_DEBUG == 1
		tempcharLog("[mpstats] save %s: %u bytes, %s\n", path, size, ok ? "ok" : "FAILED");
#endif
		return 1;
	}

	bool isBlTo(unsigned int site, unsigned int target) {
		unsigned int ins = *(volatile unsigned int*)site;
		if ((ins >> 26) != 18 || (ins & 3) != 1)
			return false;
		int offset = ins & 0x03FFFFFC;
		if (offset & 0x02000000)
			offset -= 0x04000000;
		return site + offset == target;
	}

	//Online profile stats (rlProfileStats, object at 0x224A968, read for MP = type 2): the stats save manager wants the
	//server-side MP profile stats read before it saves. 0x12E8A70(obj, 2) checks obj+0x34 ("read done"). Without the
	//Rockstar servers the read never happens, so (first hardware test of the local saves) every STAT_SAVE returned 0:
	//the save function refuses, and the manager update keeps trying to start the read and, when it can't, marks the
	//slot being loaded as failed (+0x64), which the save function refuses as well. These calls are patched to "read".
	const unsigned int PROFILE_STATS_READ = 0x12E8A70;
	const unsigned int PROFILE_STATS_SITES[] = {
		0x32C138,//0x32BD3C stats save manager update: request the read / mark the slot failed
		0x32C68C,//0x32C5B0 save
		0x32EFF0,//0x32EF48 ready to save
	};
	const int PROFILE_STATS_SITE_COUNT = sizeof(PROFILE_STATS_SITES) / sizeof(PROFILE_STATS_SITES[0]);
	const int PATCH_SITE_COUNT = CLOUD_CHECK_SITE_COUNT + PROFILE_STATS_SITE_COUNT;

	int patchCallsToLiR3One(const unsigned int *sites, int count, unsigned int target) {
		int patched = 0;
		for (int i = 0; i < count; i++) {
			volatile unsigned int *site = (volatile unsigned int*)sites[i];
			if (isBlTo(sites[i], target))
				*site = LI_R3_1;
			if (*site == LI_R3_1)
				patched++;
		}
		return patched;
	}

	bool installed = false;

	//returns how many checks were patched (PATCH_SITE_COUNT when everything matched)
	int install() {
		installed = true;
		PatchInJump2(CLOUD_GET, (int)localCloudGet, false);
		PatchInJump2(CLOUD_POST, (int)localCloudPost, false);
		return patchCallsToLiR3One(CLOUD_CHECK_SITES, CLOUD_CHECK_SITE_COUNT, IS_CLOUD_AVAILABLE) +
			patchCallsToLiR3One(PROFILE_STATS_SITES, PROFILE_STATS_SITE_COUNT, PROFILE_STATS_READ);
	}

#if TEMPCHAR_DEBUG == 1
	//stats save manager (0x1DDDAC8) and savegame op state, logged on change
	const int MANAGER_VALUE_COUNT = 10;

	void logManagerState() {
		static unsigned int last[MANAGER_VALUE_COUNT];
		static bool first = true;
		unsigned int now[MANAGER_VALUE_COUNT] = {
			*(volatile unsigned char*)(0x1DDDAC8 + 0x174),//bit 7: MP stats save manager active, bit 6: waiting for profile stats
			*(volatile unsigned char*)(0x1DDDAC8 + 0x15),//0xCE7A2411: block saves and loads
			*(volatile unsigned int*)(0x1DDDAC8 + 0x58),//slots waiting for a load (STAT_CLEAR_SLOT_FOR_RELOAD)
			*(volatile unsigned int*)(0x1DDDAC8 + 0x64),//slots whose load failed (save refuses them)
			*(volatile unsigned int*)(0x1DDDAC8 + 0x0C),//slots with a save queued
			*(volatile unsigned char*)(0x1DDDAC8 + 0x180),//bits 6/7 set: save refused
			*(volatile unsigned int*)(0x224A968 + 0x34),//MP profile stats read
			*(volatile unsigned int*)0x22271A8,//savegame op in progress
			*(volatile unsigned int*)0x22271AC,//last op result
			*(volatile unsigned int*)0x22271B0,//last HTTP code
		};
		bool changed = first;
		for (int i = 0; i < MANAGER_VALUE_COUNT; i++)
			if (now[i] != last[i])
				changed = true;
		if (!changed)
			return;
		first = false;
		for (int i = 0; i < MANAGER_VALUE_COUNT; i++)
			last[i] = now[i];
		tempcharLog("[mpstats] mgr flags 0x%X block %u notloaded 0x%X failed 0x%X queued 0x%X savebits 0x%X profile %u op %u result %u http %u\n",
			now[0], now[1], now[2], now[3], now[4], now[5], now[6], now[7], now[8], now[9]);
	}

	//the STAT_SAVE native (0x433E40) gates, logged before Paradise's periodic save
	void logSaveGates() {
		int gamer = *(volatile int*)0x1CF7308;//onlineRockstarPermissions: local gamer index
		int signedOnline = gamer >= 0 && gamer < 1 ? *(volatile unsigned char*)(0x2242728 + gamer) : -1;//0x12EE394(-1, 1)
		tempcharLog("[mpstats] save gates: gamer %i signedonline %i notloaded 0x%X failed 0x%X savebits 0x%X\n", gamer, signedOnline,
			*(volatile unsigned int*)(0x1DDDAC8 + 0x58), *(volatile unsigned int*)(0x1DDDAC8 + 0x64), *(volatile unsigned char*)(0x1DDDAC8 + 0x180));
	}
#endif

}
