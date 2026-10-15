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
//  buffer (GET): [0] data, [2] length, [3] flags (bit 2: not owned, never freed), [6] heap handle (-1 none).
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
	const int RESPONSE_BUFFER_NOT_OWNED = 2;
	const unsigned int MAX_SAVE_SIZE = 0x10000;//the POST refuses anything bigger

	//only one MP stats load runs at a time; the game parses (and decrypts in place) straight out of this buffer
	char loadBuffer[MAX_SAVE_SIZE];

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

	//replaces 0x129E478 (request, path, rockstar permissions, ...). Returns nonzero when the request was started
	int localCloudGet(int *request, const char *cloudPath, unsigned int r5, unsigned int r6, unsigned int r7) {
		char path[100];
		localPath(path, sizeof(path), cloudPath);
		int *response = (int*)((int)request + 0xC);
		request[1] = 0;
		request[2] = 1;
		int size = -1;
		int fd;
		if (cellFsOpen(path, CELL_FS_O_RDONLY, &fd, NULL, 0) == CELL_FS_SUCCEEDED) {
			uint64_t read = 0;
			if (cellFsRead(fd, loadBuffer, MAX_SAVE_SIZE, &read) == CELL_FS_SUCCEEDED)
				size = (int)read;
			cellFsClose(fd);
		}
		if (size > 0) {
			response[0] = (int)loadBuffer;
			response[1] = size;
			response[2] = size;
			response[3] |= RESPONSE_BUFFER_NOT_OWNED;
			response[6] = -1;
			request[1] = 200;
			request[0] = REQUEST_STATUS_SUCCEEDED;
		} else {
			//what the cloud answers for a player that never saved
			response[2] = 0;
			request[1] = 404;
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

	bool installed = false;

	//returns how many cloud checks were patched (CLOUD_CHECK_SITE_COUNT when everything matched)
	int install() {
		installed = true;
		PatchInJump2(CLOUD_GET, (int)localCloudGet, false);
		PatchInJump2(CLOUD_POST, (int)localCloudPost, false);
		int patched = 0;
		for (int i = 0; i < CLOUD_CHECK_SITE_COUNT; i++) {
			volatile unsigned int *site = (volatile unsigned int*)CLOUD_CHECK_SITES[i];
			if (isBlTo(CLOUD_CHECK_SITES[i], IS_CLOUD_AVAILABLE))
				*site = LI_R3_1;
			if (*site == LI_R3_1)
				patched++;
		}
		return patched;
	}

#if TEMPCHAR_DEBUG == 1
	//stats save manager (0x1DDDAC8) and savegame op state, logged on change
	void logManagerState() {
		static unsigned int last[6] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
		unsigned int now[6] = {
			*(volatile unsigned char*)(0x1DDDAC8 + 0x174),//bit 7: MP stats save manager active
			*(volatile unsigned char*)(0x1DDDAC8 + 0x15),//0xCE7A2411: block saves and loads
			*(volatile unsigned int*)0x1DDDB20,//slots waiting for a load (STAT_CLEAR_SLOT_FOR_RELOAD)
			*(volatile unsigned int*)0x22271A8,//savegame op in progress
			*(volatile unsigned int*)0x22271AC,//last op result
			*(volatile unsigned int*)0x22271B0,//last HTTP code
		};
		bool changed = false;
		for (int i = 0; i < 6; i++)
			if (now[i] != last[i])
				changed = true;
		if (!changed)
			return;
		for (int i = 0; i < 6; i++)
			last[i] = now[i];
		tempcharLog("[mpstats] mgr flags 0x%X block %u notloaded 0x%X op %u result %u http %u\n", now[0], now[1], now[2], now[3], now[4], now[5]);
	}
#endif

}
