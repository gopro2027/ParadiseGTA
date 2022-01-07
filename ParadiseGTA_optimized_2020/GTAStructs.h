//some useful defines
#define VALID_ADDR(x) ((unsigned int)(x) > 0x10000)
typedef unsigned long long ui64;
typedef long long s64;
typedef unsigned long long u64;
typedef unsigned int ui32;
typedef int s32;
typedef unsigned char u8;
typedef uint64_t(*one_hook_function_call)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
#define TRAP() __asm("trap")
#define SC() __asm("sc")
#define TRAP_BYTES (0x7FE00008) 
#define SC_BYTES (0x44000002)
#define BIT_FROM_LEFT(x) (0x80000000>>x)
#define BIT_FROM_RIGHT(x) (1<<x)
#define B(address_jump_at, address_jump_to) (0x48000000 & ((address_jump_to-address_jump_at) & 0xFFFFFF))
#define BL(address_jump_at, address_jump_to) (B(address_jump_at, address_jump_to) + 1)
#define BA(address_jump_to) (B(0,address_jump_to) + 2)
#define BLA(address_jump_to) (B(0,address_jump_to) + 3)
#define MAX_B 0xffffff
//typedef ui64 (*fnptr)(...);
//template <typename RET>
//typedef RET (*fnptr)(...);
#define PLAYER_VALID(i) (VALID_ADDR(getCNetGamePlayer(i)))
#define IS_LOADED_INTO_LOBBY ((bool)(*(int*)(*(int*)0x1CF72C4+0xA098) == 8))    //from NETWORK_IS_SESSION_ACTIVE function   and more like... IS_STARTING_TRANSITION_TO_LOBBY
#define MY_PLAYER_PED_ADDRESS (*(volatile unsigned int*)( *(volatile unsigned int*)0x1CEFCF8 + 0x4) + 0)   //from the PLAYER_PED_ID function
#define I_AM_ONLINE (*(char*)0x223F0C0)
#define BLACK_SCREEN_DIALOG_OPEN (*(char*)0x1D63D1F > 0)
char global_temporary_buf[200];

__NAKED unsigned int getR22() { __asm__("mr %r3, %r22"); __asm__("blr"); }
__NAKED unsigned int getR23() { __asm__("mr %r3, %r23"); __asm__("blr"); }
__NAKED unsigned int getR24() { __asm__("mr %r3, %r24"); __asm__("blr"); }
__NAKED unsigned int getR25() { __asm__("mr %r3, %r25"); __asm__("blr"); }
__NAKED unsigned int getR26() { __asm__("mr %r3, %r26"); __asm__("blr"); }
__NAKED unsigned int getR27() { __asm__("mr %r3, %r27"); __asm__("blr"); }
__NAKED unsigned int getR28() { __asm__("mr %r3, %r28"); __asm__("blr"); }
__NAKED unsigned int getR29() { __asm__("mr %r3, %r29"); __asm__("blr"); }
__NAKED unsigned int getR30() { __asm__("mr %r3, %r30"); __asm__("blr"); }
__NAKED unsigned int getR31() { __asm__("mr %r3, %r31"); __asm__("blr"); }

#define PAD(x,s) char unk##x[s]

void sync_mem(unsigned int Address) {
	__dcbst((void*)Address); // Data Cache Block Store | Allows a program to copy the contents of a modified block to main memory.
	__sync(); // Synchronize | Ensure the dcbst instruction has completed.
	__isync(); // Instruction Synchronize | Refetches any instructions that might have been fetched prior to this instruction.
}

template <typename T>
__ALWAYS_INLINE T(*call(unsigned int address, unsigned int toc = TOC))(...) {
	volatile opd_s opd = { address,toc };
	T(*func)(...) = (T(*)(...)) & opd;
	return func;
}

void PatchInJump2(uint64_t Address, int Destination, bool Linked);//needed to be defined for use below

class Hooker { 
public:
	char orig[4 * 4];
	char patch[4 * 4];
	int address;
	Hooker() {}
	void init(int addressOfOriginalFunction, int opdOfDetour) {
		address = addressOfOriginalFunction;
		memcpy((void*)orig, (void*)address, 4 * 4);
		PatchInJump2(address, opdOfDetour, false);
		memcpy((void*)patch, (void*)address, 4 * 4);
	}
	void unhook() {
		memcpy((void*)address, (void*)orig, 4 * 4);
		//sync_mem(address);//optional
	}
	void rehook() {
		memcpy((void*)address, (void*)patch, 4 * 4);
		//sync_mem(address);//optional
	}
	template <typename T>
	T(*call())(...) {
		volatile opd_s opd = { address,TOC };
		T(*func)(...) = (T(*)(...)) & opd;
		return func;
	}
};

//https://gta.nick7.com/stuff/gta5/ps3-classes.txt
/*
Entity layout:
017237C8:class CPhysical: public CDynamicEntity  I CALL THIS CObj
01788D48:  class CVehicle: public CPhysical
01788D58:    class CAutomobile: public CVehicle
01788D68:      class CQuadBike: public CAutomobile
01788DC0:      class CRotaryWingAircraft: public CAutomobile
01788DD0:        class CHeli: public CRotaryWingAircraft
01788DF0:          class CBlimp: public CHeli
01788DE0:        class CAutogyro: public CRotaryWingAircraft
01788E80:      class CTrailer: public CAutomobile
01788E60:      class CPlane: public CAutomobile
01788D90:    class CBike: public CVehicle
01788EB0:      class CBmx: public CBike
01788EC0:    class CBoat: public CVehicle
01788F08:    class CSubmarine: public CVehicle
01788E28:    class CTrain: public CVehicle
0178FB60:  class CObject: public CPhysical
0178ADB0:    class CProjectile: public CObject
0178AE00:      class CProjectileRocket: public CProjectile
0178AEA8:      class CProjectileThrown: public CProjectile
0178FB90:    class CDoor: public CObject
01791928:    class CPickup: public CObject
0178B678:  class CPed: public CPhysical
*/
char* getClassName(unsigned int classAddress);
struct ClassData;
struct CNonPhysicalPlayerData;
struct CPlayerInfo;
struct CNetGamePlayer;
struct GtaThread;
struct CGameScriptHandlerNetwork;
struct CGameScriptHandlerNetComponent;
struct CGameScriptId;
struct CObj;
struct CNetObj;
struct CFingerOfGodPresenceEvent;
class Global;
class Struct;
typedef CObj CPed;
typedef struct Vector3
{
	float x;
	float y;
	float z;
	Vector3 add(float x, float y, float z) {
		Vector3 n = { x + this->x,y + this->y,z + this->z };
		return n;
	}
};
typedef struct
{
	float x;
	float y;
} Vector2;

struct ClassData {//this would be the 0x19...
	unsigned int base;

	unsigned int getClassDataAddress() {
		return (unsigned int)&base;
	}
	char* className() {
		return getClassName(getClassDataAddress());
	}
	//alternate us using the typedef fnptr and doing fnptr call(unsigned int offset)...
	template <typename T>
	T(*call(unsigned int offset))(...) {//currently untested
		unsigned int __opd_s = *(volatile unsigned int*)(getClassDataAddress() + offset);
		T(*func)(...) = (T(*)(...)) & __opd_s;
		return func;
	}
	/*template <typename RET>
	fnptr<RET> call(unsigned int offset) {
		unsigned int opd_s = *(volatile unsigned int*)(getClassDataAddress()+offset);
		fnptr<RET> func = fnptr&opd_s;
		return func;
	}*/
};
struct CNonPhysicalPlayerData {
	ClassData* classData;//0x0
	unsigned int unk1;//0x4
	unsigned int playerIndex;//0x8
};
struct CPlayerInfo {//this is at offset 0xBD0 from entity class, such as CPed
	ClassData* classData;//0x0
	unsigned char unk1[0x4 * 3];//0x4
	char name[0x4 * 5];//0x10
	char region[0x4 * 2];//0x24
	PAD(2, 0x40 - 0x2C);//0x2C
	ui64 uuid;//0x40
	PAD(3, 0x160 - 0x48);//0x48
	CObj* cPed;//0x160  this is the CPed of the player
	//spoofed name is at 0x84 (0x10 + 0x74)
};
struct Metric {
	virtual void unkfunc1();
	virtual void unkfunc2();
	virtual void return4();
	virtual void return0();
	virtual char* getMetricName();
	virtual bool storeJsonData(unsigned int unk);
	virtual int getMetricID();
};
#pragma pack(1)
struct CNetGamePlayer {
	ClassData* classData;//0x0
	unsigned int unk1;//0x4
	CNonPhysicalPlayerData* nonPhysicalPlayerData;//0x8
	unsigned char unk2[0xC];//0xC
	unsigned int unk3;//0x18
	unsigned char unk4[0xD];//0x1C
	unsigned char playerIndex;//0x29   0 through 17 ya know
	unsigned char unk41[0x38 - 0x2A];//0x2A
	unsigned int team;//0x38
	unsigned int unk5;//0x3C
	CNetGamePlayer* myCNetgamePlayer;//0x40
	unsigned char unk6[0x4 * 3];//0x44
	CNetGamePlayer* myCNetgamePlayer1;//0x50
	unsigned char unk7[0x4 * 3];//0x54
	CNetGamePlayer* myCNetgamePlayer2;//0x60
	unsigned char unk8[0x4 * 5];//0x64
	CPlayerInfo* playerInfo;//0x78
	unsigned char unk9[0xF4];//0x7C
	unsigned char unk10[0x1];//0x170
	unsigned char rockstarDev;//0x171
	unsigned char rockstarQA;//0x172
	unsigned char isCheater;//0x173
	unsigned char unk12[0xFFFFFF];//0x174 just here to note that it's not at 0x174

	//offset 0xBE is crew name
	//offset 0xD7 is crew tag
	void* getWeirdNetInfo() {
		return classData->call<void*>(0x1C)(this);//this returns CPlayerInfo + 0x10
	}
};
#pragma pack(4)
struct GtaThread {
	ClassData* classData;//0x0
	unsigned int threadID;//0x4
	unsigned int nameHash;//0x8
	//unsigned char unk1[0x5C];//0xC
	PAD(0, 0x54 - 0xC);//0xC
	void* localDataPointer;//0x54
	PAD(1, 0x68 - 0x58);//0x58
	char threadName[0x4 * 6];//0x68
	//30CGameScriptHandlerNetComponent is 0xAC
	/*
	virtual void unkfunc1();//0x0
	virtual void unkfunc2();//0x4
	virtual void unkfunc3();//0x8
	virtual void unkfunc4();//0xC
	virtual void unkfunc5();//0x10
	virtual void terminate_thread();//0x14
	*/

	void setLocal(int local, int value) {
		if (VALID_ADDR(localDataPointer))
			*(int*)((int)localDataPointer + (local * 4)) = value;
	}
	void terminate() {
		//call<void>(0x46D6F8)(&classData);
		classData->call<int>(0x14)(this);
		//terminate_thread();//I wonder if this will work at all hmm
	}

};
struct CGameScriptId {
	ClassData* classData;//0x0
	unsigned int unk1;
	char scriptName[0x4 * 0x8];//max size, but might be less
};
struct CGameScriptHandlerNetwork {
	ClassData* classData;//0x0
	unsigned char unk1[0x8];//0x4
	GtaThread* gtaThread;//0xC
	unsigned char unk2[0x14];//0x10
	CGameScriptHandlerNetComponent* cGameScriptHandlerNetComponentSyncOne;//0x24   this one is used in CGameScriptHandlerNetComponent__setMemorySyncPlayers and CGameScriptHandlerNetComponent__setMemorySyncHost as r3
	unsigned char unk3[0x30];//0x28
	CGameScriptHandlerNetComponent* cGameScriptHandlerNetComponent;//0x58
	unsigned char unk4[0x10];//0x5C
	CGameScriptId cGameScriptId;//0x6C         //0x38 - //this may be bigger in size, unsure 
};
#pragma pack(1)
struct CGameScriptHandlerNetComponent {//this is used for setting memory in script to be shared
	ClassData* classData;//0x0
	CGameScriptHandlerNetwork* cGameScriptHandlerNetwork;//0x4
	unsigned int unk1;//0x8  -- used in some places
	//0x34 is a cnetgameplayer
	int getHost() {
		unsigned int unkStruct = *(unsigned int*)((unsigned int)this + 0x1C);
		if (unkStruct == 0)
			return -1;
		CNetGamePlayer* p = (CNetGamePlayer*) *(int*)(unkStruct + 0x8);
		return p->playerIndex;
	}
};

struct CGamePlayerBroadcastDataHandler_Remote {//size of 0xF8
	//There is a pool of these at 0x1CF7318, max size of 000001F4, entry size of 000000F8
	ClassData* classData;//0x0
	CGamePlayerBroadcastDataHandler_Remote* next;//0x4
	CGamePlayerBroadcastDataHandler_Remote* previous;//0x8
	PAD(1, 0x5E - 0xC);//0xC
	short maxSize;//0x5E  this is the max size it can be that iis shared
	PAD(15, 0x70 - 0x60);
	int* pointerToDataSyncLocation;//0x70
	PAD(2, 0xA0 - 0x74);//0x74
	unsigned int sizeOfSyncData;//0xA0   modifyy this on host broadcast to be smaller than it should be and it can cause a crash
	PAD(3, 0xB0 - 0xA4);//0xA4
	unsigned int affectedPlayerId;//0xB0
	unsigned int unkValue131234;//0xB4   this looks like a boolean
	unsigned int currentNumberWeird;//0xB8    this value is shared. Like if you use the player sync this value will be used 18 times
	CGameScriptId cGameScriptId;//0xBC
	PAD(4, 0x130 - (0xBC + sizeof(CGameScriptId/*should be 0x28*/)));//sizeof(CGameScriptId/*should be 0x28*/)
	char scriptName[7 * 4];//0x130 idk the size of it, I just know it's at 0x130
	//unsure after this because idk the size of CGameScriptId
	unsigned int getAddressOfCopiedOverData() {
		return *(unsigned int*)((unsigned int)this + 0xD0);
	}
};
struct CGamePlayerBroadcastDataHandler_Local : CGamePlayerBroadcastDataHandler_Remote {};//size of 0x164 according to address 0x130C858
struct CGameHostBroadcastDataHandler : CGamePlayerBroadcastDataHandler_Remote {};//basically the same as this, but the important ones are pointerToDataSyncLocation and 
#pragma pack(4)
struct eventArgumentData {
	unsigned char data[0xF];//this is an array, not of size 0xFFFFFFFF but doesn't matter
	unsigned int* getArr(unsigned int offset = 0) {
		return (unsigned int*)(&(data[offset]));
	}
	int getInt(int index) {
		return *(volatile int*)&(getArr()[index]);
	}
	unsigned int getUInt(int index) {
		return getArr()[index];
	}
	int* getpInt(int index) {
		return (int*)&(getArr()[index]);
	}
	unsigned int* getpUInt(int index) {
		return &(getArr()[index]);
	}
};
struct eventArgumentInfo {//this is r3
	eventArgumentData* data;
	//more data within the r3
};
struct phInstGta {
	ClassData* classData;//0x0
};
struct CObjModelInfo {
	ClassData* classData;//0x0
	PAD(1, 0xC - 0x4);//0x4
	unsigned int modelHash;//0xC
	PAD(2, 0x20 - 0x10);//0x10
	Vector3 modelDimensionMin;//0x20
	PAD(3, 0x30 - 0x2C);//0x2C
	Vector3 modelDimensionMax;//0x30
	PAD(4, 0x160 - 0x3C);//0x3C
	//0x6B is like 5 if model is a vehicle... idk lmao
	char modelName[0x4];//0x160 is where it starts but idk where it ends
	PAD(5, 0x1B8 - 0x164);//0x164
	unsigned int modelType;//0x1B8
};
struct CPedDrawHandler {
	ClassData* classData;//0x0
};
struct CNetBlenderPed {
	ClassData* classData;//0x0
};
struct CPedInventory {
	ClassData* classData;//0x0
};
struct CWeaponInfo {
	ClassData* classData;//0x0
};
struct CPedWeaponManager {
	ClassData* classData;//0x0
	PAD(0, 0x4);//0x4
	CPed* unkCPed;//0x8
	unsigned int unkValue;//0xC
	CWeaponInfo* cWeaponInfo;//0x10
};
struct CNetObj_CSyncData {//N10CNetObjPed12CPedSyncDataE
	ClassData* classData;//0x0

};
#pragma pack(1)
struct CNetObj {
	ClassData* classData;//0x0
	unsigned short unk;//0x4
	unsigned short netID;//0x6
	//0x8 is CNetworkSyncData, but not a pointer to it. like *(int*)(this+0x8) = the classData for CNetworkSyncData aka 0x018F84B8
	//you can use A076C0 getCNetGamePlayerFromCNetObjPlayer to get the cnetgamme player for a cnetobj
	//unsigned char unk1[0x4*7];//0x8
	ClassData* N4rage18CNetworkSyncDataULILj18EEE;//0x8
	CNetObj_CSyncData* syncData;//0xC
	PAD(0, 0x24 - 0x10);//0x10
	unsigned int ownerData;//0x24
	unsigned int unk2;//0x28
	CObj* cObj;//0x2C - CPed...
	CNetBlenderPed* cNetBlenderPed;//0x30
	PAD(3, 0x374 - 0x34);//0x34
	short netID2;//0x374 used in other places, different than netID
	int getCurrentOwner() {//0x25
		int data = ownerData & 0x00FF0000;
		data = data >> 16;
		return data;
	}
	bool isCurrentOwner() {//0x27
		int data = ownerData & 0x000000FF;
		return data == 0;//data should be 0 or 1, 0 if I am owner.... unless I am mistaken and this is the same as 0x25
	}
	//this is important too, just not got stuff in it yet
};
#pragma pack(4)
#pragma pack(1)
struct CObj {//getEntityFromIndex, entityToIndex, CPed...

	//byte at 0x6DC contains the bit for visibility at insrwi    r3, r31, 1,29

	ClassData* classData;//0x0
	unsigned char unk[0xC];//0x4
	CObjModelInfo* modelInfo;//0x10
	unsigned int unk_bitset;//0x14    the first byte of this has values, and 3 is checks in delete entity
	unsigned char unk1[0x4];//0x18
	phInstGta* unk_phInstGta;//0x1C
	unsigned char unk2[0x8];//0x20
	CPedDrawHandler* cPedDrawHandler;//0x28
	unsigned char unk3[0x20];//0x2C  //used to be 0x10 of size but realized I fucked up
	CNetObj* cNetObj;//0x4C  Player associated with it
	unsigned char unk4[0x10];//0x50
	ClassData* classDataForStartOfOtherClass;//0x60
	unsigned char unk5[0x50];//0x64
	unsigned int proofsBitset;//0xB4  //0xA4 is what it shows though
	unsigned char proofsBitsetByte;//0xB8
	unsigned char unk6[3];//filling up the rest of that
	unsigned char unk7[0xB4];//0xBC
	float health;//0x170
	float maxHealth;//0x174
	unsigned char unk8[0xA58];//0x178
	CPlayerInfo* cPlayerInfo;//0xBD0  This CObj can be refernced back through this struct
	CPedInventory* cPedInventory;//0xBD4
	CPedWeaponManager* cPedWeaponManager;//0xBD8

	//0xE9C is the vehicle they are in when a ped

};
#pragma pack(4)

struct CSectorPositionDataNode {//This one ended up not bbeing used 
	ClassData* classData;//0x0
	PAD(0, 0x6C - 0x4);//0x4
	float x;//0x6C
	float y;//0x70
	float z;//0x74
	ClassData* CProjectBaseSyncParentNode;
};

struct CPlayerSectorPosNode {
	ClassData* classData;//0x0
	PAD(0, 0x6C - 0x4);//0x4
	float x;//0x6C
	float y;//0x70
	float z;//0x74
};

#pragma pack(1)
struct CSectorDataNode {
	ClassData* classData;//0x0
	CPlayerSectorPosNode* posNode;//0x4
	PAD(0, 0x6C - 0x8);//0x8
	//During testing with breakpoints, this data seemed to be stable for player ped cnet. I could even see it increment slowly as I moved
	short x;//0x6C
	short y;//0x6E
	short z;//0x70
	short unk;//0x72
	ClassData* CSectorPositionDataNode;//0x74
};
#pragma pack(4)


//size if 0x50 -- confirmed because there is a static one
struct CFingerOfGodPresenceEvent {
	ClassData* classData;//0x0
	unsigned int hashValue;//0x4
	int unk1;//0x8
	char vehicleName[0x20];//0xC -- 0x20 is a guess
	char unk2[0x24];//0x2C
	void receiveFunc2(int value) {
		//classData->call<int>(0x14)(this,value);
		//0x14
	}
	void receiveFunc() {
		//0x18
	}
	void sendFunc() {
		//0x10 - it returns 0
	}
};


struct CBountyPresenceEvent {
	ClassData* classData;//0x0
	char playerName[0x20];//0x4
	char unk[0x50];//0x24  I don't actually know the size
	void startFunc(int value) {
		classData->call<int>(0x14)(this, value);
	}
	void receiveFunc() {
		//0x18
	}
	void sendFunc() {
		//bountyEventFunction_send
		//0x10 - not in this!!!! it returns 0
	}
};

union IntFloat {
	int i;
	unsigned int ui;
	float f;
};
struct CStatUpdatePresenceEvent {//max size of 0x98, probably 0x94
	ClassData* classData;//0x0
	unsigned int statHash;//0x4
	int statType;//0x8 - 1 for float, else for int (and others?)
	IntFloat value;//0xC
	unsigned int v2;//0x10 - unknown value necessary
	char from[0x40];//0x14
	char sv[0x40];//0x54
	unsigned int unk;//0x94 - I don't think this is actually ever used. probably size 0x94
};

struct N4rage10scrProgramE {
	ClassData* classData;//0x0
	unsigned int unk1;//0x4
	unsigned int goodPointer1;//0x8
	PAD(0, 0x38 - 0xC);//0xC
	unsigned int nameHash;//0x38
	unsigned int status;//0x3C  - 1 is not running, 2 is running, 0 maybe not loaded
};

struct JsonArg {
	char* jsonString;//0x0
	int jsonStringBufferSize;//0x4  max length  0x100
	int unk1;//0x8 -1
	int unk2;//0xC -1
	int unk3;//0x10 0
	int jsonStringLength;//0x14 strlen
};

struct EventDataStruct {//size = 0x1C
	int unk1;
	int unk2;
	int unk3;
	int unk4;
	int unk5;
	int unk6;
	int unk7;
	char unk8[200];
};
class Global {
private:
	unsigned int index;
	unsigned int getAddress() {
		return Read_Global_Address(index);
	}
public:
	Global(unsigned int globalID)
		: index(globalID/*Read_Global_Address(globalID)*/)
	{}
	Global imm(int i) {
		return Global(index + i);
	}
	Global arr(int index, int size) {
		return imm(index * size);
	}
	template <typename T>
	void set(T value) {
		*(T*)getAddress() = value;
	}
	template <typename T>
	T get() {
		return *(T*)getAddress();
	}
	unsigned int* at() {
		return (unsigned int*)getAddress();
	}
};

class Struct {
public:
	unsigned int address;
	Struct(unsigned int* data)
		: address((unsigned int)data)
	{}
	Struct imm(int i) {
		return Struct((unsigned int*)(((unsigned int)address) + (i * 4)));
	}
	Struct arr(int index, int size) {
		return imm(index * size);
	}
	template <typename T>
	void set(T value) {
		*(T*)address = value;
	}
	template <typename T>
	T get() {
		return *(T*)address;
	}
	unsigned int* at() {
		return (unsigned int*)address;
	}
};

class StackFrame {
private:
	void* stack;
	unsigned int size;
public:
	StackFrame(void* _stack, unsigned int _size) :
		stack(_stack), size(_size)
	{

	}
	void* get(unsigned int offset) {
		return (void*)((unsigned int)stack + (size - offset));
	}
	template <typename T>
	void setArg(unsigned int offset, T value) {
		*(T*)get(offset) = value;
	}
	template <typename T>
	T getArg(unsigned int offset) {
		return *(T*)get(offset);
	}
};

//signature checks and scrProgram struct by roulette
bool DataCompare(const uint8_t* pbData, const uint8_t* pbMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pbData, ++pbMask)
	{
		if (*szMask == 'x' && *pbData != *pbMask)
		{
			return false;
		}
	}
	return (*szMask == NULL);
}

uintptr_t FindPattern(uintptr_t startAddress, uintptr_t endAddress, uint8_t* pbPattern, const char* szMask)
{
	for (uintptr_t i = 0; i < endAddress; i++)
		if (DataCompare((uint8_t*)(startAddress + i), pbPattern, szMask))
			return (uintptr_t)(startAddress + i);

	return NULL;
}

uintptr_t FindPattern(uintptr_t startAddress, uintptr_t endAddress, uint8_t* pbPattern, const char* szMask, uintptr_t* occurrences, uint32_t maxOccurances)
{
	uint32_t numFound = 0;
	for (uintptr_t i = 0; i < endAddress; i++)
		if (DataCompare((uint8_t*)(startAddress + i), pbPattern, szMask) && numFound < maxOccurances)
			return occurrences[numFound++] = (uintptr_t)(startAddress + i);

	return NULL;
}

struct scrProgram
{
	void* m_vmt;
	uintptr_t** m_unknown;           // 0x0004
	uint8_t** m_code_blocks;         // 0x0008
	uint32_t m_hash;                 // 0x0000
	uint32_t m_code_size;            // 0x0000
	uint32_t m_arg_count;            // 0x0000
	uint32_t m_local_count;          // 0x0000
	uint32_t m_global_count;         // 0x0000
	uint32_t m_native_count;         // 0x0000
	int32_t* m_local_data;           // 0x0024
	int64_t** m_global_data;         // 0x0000
	void** m_native_entrypoints;     // 0x0000
	char m_padding6[0x08];           // 0x0000
	uint32_t m_name_hash;            // 0x0000
	char m_padding7[0x04];           // 0x0000
	const char* m_name;              // 0x0000
	const char** m_strings_data;     // 0x0000
	uint32_t m_strings_count;        // 0x0000
	char m_padding8[0x0C];           // 0x0000


	bool IsValid() const
	{
		return m_code_size > 0;
	}

	uint32_t GetNumCodePages() const
	{
		return (m_code_size + 0x3FFF) >> 14;
	}

	uint32_t GetCodePageSize(uint32_t page) const
	{
		return (page < 0 || page >= GetNumCodePages() ? 0 : (page == GetNumCodePages() - 1) ? m_code_size & 0x3FFF : 0x4000);
	}

	uint8_t* GetCodePage(uint32_t page) const
	{
		return m_code_blocks[page];
	}

	uint8_t* GetCodeAddress(uint32_t codePosition) const
	{
		return codePosition < 0 || codePosition >= m_code_size ? NULL : &m_code_blocks[codePosition >> 14][codePosition & 0x3FFF];
	}

	const char* GetString(uint32_t stringPosition) const
	{
		return stringPosition < 0 || stringPosition >= m_strings_count ? NULL : &m_strings_data[stringPosition >> 14][stringPosition & 0x3FFF];
	}

	int32_t GetLocal(uint32_t localPosition) const
	{
		return m_local_data[localPosition];
	}

	void SetLocal(uint32_t localPosition, int32_t value)
	{
		m_local_data[localPosition] = value;
	}
};

struct scrProgramTableEntry
{
	scrProgram* m_program;
	char padding[4];
	uint32_t hash;

	bool IsLoaded() const
	{
		return m_program != NULL;
	}
};

struct scrProgramTable
{
	scrProgramTableEntry* m_data;
	uintptr_t* m_bitmap;
	uint32_t m_size;
	scrProgramTableEntry* FindScript(uint32_t hash)
	{
		if (m_data == NULL)
			return NULL; // table initialization hasn't happened yet

		for (uint32_t i = 0; i < m_size; i++)
		{
			if (m_data[i].hash == hash)
			{
				return &m_data[i];
			}
		}
		return NULL;
	}
};

scrProgramTable* scriptTable = (scrProgramTable*)0x1DE8EC0;


//some global function definitions based on these...
CNetGamePlayer* getCNetGamePlayer(int player);//0x47E00C
CObj* getCObjFromIndex(int entity);//getEntityFromIndex 0xA552E0
int entityToIndex(CObj* entityAddress);//0x474054 aka 0xA551A4
CObjModelInfo* getCModelInfo(unsigned int hash);//0x9D9830 actual function r4 is unused int pointer (stores return index or some shit)
GtaThread* getCurrentGtaThread() { return call<GtaThread*>(0x9B82DC)();/*return ((GtaThread*(*)())0x9B82DC)();*/ }
GtaThread* getGtaThreadById(int id) { return call<GtaThread*>(0x9B80DC)(id);/*return ((GtaThread*(*)(int))0x9B80DC)(id);*/ };
CFingerOfGodPresenceEvent* globalCFingerOfGodPresenceEvent = (CFingerOfGodPresenceEvent*)0x225A3E8;
unsigned int getG_CGameArrayMgr() { return call<unsigned int>(0x9F8E20)();/*return ((unsigned int(*)())0x9F8E20)();*/ }
CGameScriptHandlerNetwork* getCurrentCGameScriptHandlerNetwork() { return call<CGameScriptHandlerNetwork*>(0x47DEC4)();/*return ((CGameScriptHandlerNetwork *(*)())0x47DEC4)();*/ };
unsigned int joaat(char* text, int r4 = 0) { return call<unsigned int>(0xAE580C)(text, r4); };
unsigned int getMyPlayerNetworkData() { return call<unsigned int>(0x12EF35C)(); };
CObj* getMyCPed() { return call<CObj*>(0x1117978)(); };
CObj* getPlayerCPedByIndex(int index) { return call<CObj*>(0x47DFA0)(index); };
void calculatePlayerPosition(float realCoords[3], float* sectorX, float* sectorY, float* sectorZ, float segmentPos[3]) { call<int>(0x1344108)(realCoords, sectorX, sectorY, sectorZ, segmentPos); };
N4rage10scrProgramE* getN4rage10scrProgramE(unsigned int scriptHash) { return call<N4rage10scrProgramE*>(0x9B45E4)(scriptHash); }
scrProgram* getScrProgram(unsigned int scriptHash) { return call<scrProgram*>(0x9B45E4)(scriptHash); }
CPlayerInfo* getMyCPlayerInfo() { return call<CPlayerInfo*>(0x36CBE4)(); };
char* getMyPSNName() { return call<char*>(0x12ED734)(); };

//example would be 0x1CF7374 for pool_NetworkEntityAreas_32CNetworkEntityAreaWorldStateData
bool doesPoolHaveOpenSlot(unsigned int poolPointer) {
	unsigned int poolAddr = *(unsigned int*)poolPointer;
	int neg1check = *(int*)(poolAddr + 0x10);
	if (neg1check == -1) {
		if (*(int*)(poolAddr + 0x1C) == 0)
			return false;
		if (*(int*)(poolAddr + 0x24) == 0)
			return false;
		//probably an issue.... but we'll stick to this
	}
	return true;
}

//some enums
enum EVENTS {
	OBJECT_ID_FREED_EVENT,
	OBJECT_ID_REQUEST_EVENT,
	ARRAY_DATA_VERIFY_EVENT,
	SCRIPT_ARRAY_DATA_VERIFY_EVENT,
	REQUEST_CONTROL_EVENT,
	GIVE_CONTROL_EVENT,
	WEAPON_DAMAGE_EVENT,
	REQUEST_PICKUP_EVENT,
	REQUEST_MAP_PICKUP_EVENT,
	GAME_CLOCK_EVENT,
	GAME_WEATHER_EVENT,
	RESPAWN_PLAYER_PED_EVENT,
	GIVE_WEAPON_EVENT,
	REMOVE_WEAPON_EVENT,
	REMOVE_ALL_WEAPONS_EVENT,
	VEHICLE_COMPONENT_CONTROL_EVENT,
	FIRE_EVENT,
	EXPLOSION_EVENT,
	START_PROJECTILE_EVENT,
	ALTER_WANTED_LEVEL_EVENT,
	CHANGE_RADIO_STATION_EVENT,
	RAGDOLL_REQUEST_EVENT,
	PLAYER_TAUNT_EVENT,
	PLAYER_CARD_STAT_EVENT,
	DOOR_BREAK_EVENT,
	SCRIPTED_GAME_EVENT,
	REMOTE_SCRIPT_INFO_EVENT,
	REMOTE_SCRIPT_LEAVE_EVENT,
	MARK_AS_NO_LONGER_NEEDED_EVENT,
	CONVERT_TO_SCRIPT_ENTITY_EVENT,
	SCRIPT_WORLD_STATE_EVENT,
	INCIDENT_ENTITY_EVENT,
	CLEAR_AREA_EVENT,
	NETWORK_REQUEST_SYNCED_SCENE_EVENT,
	NETWORK_START_SYNCED_SCENE_EVENT,
	NETWORK_UPDATE_SYNCED_SCENE_EVENT,
	NETWORK_STOP_SYNCED_SCENE_EVENT,
	GIVE_PED_SCRIPTED_TASK_EVENT,
	GIVE_PED_SEQUENCE_TASK_EVENT,
	NETWORK_CLEAR_PED_TASKS_EVENT,
	NETWORK_START_PED_ARREST_EVENT,
	NETWORK_START_PED_UNCUFF_EVENT,
	NETWORK_SOUND_CAR_HORN_EVENT,
	NETWORK_ENTITY_AREA_STATUS_EVENT,
	NETWORK_GARAGE_OCCUPIED_STATUS_EVENT,
	PED_CONVERSATION_LINE_EVENT,
	SCRIPT_ENTITY_STATE_CHANGE_EVENT,
	NETWORK_PLAY_SOUND_EVENT,
	NETWORK_STOP_SOUND_EVENT,
	NETWORK_BANK_REQUEST_EVENT,
	REQUEST_DOOR_EVENT,
	NETWORK_TRAIN_REQUEST_EVENT,
	NETWORK_TRAIN_REPORT_EVENT,
	NETWORK_INCREMENT_STAT_EVENT,
	MODIFY_VEHICLE_LOCK_WORD_STATE_DATA,
	REQUEST_PHONE_EXPLOSION_EVENT,
	REQUEST_DETACHMENT_EVENT,
	KICK_VOTES_EVENT,
	GIVE_PICKUP_REWARDS_EVENT,
	NETWORK_CRC_HASH_CHECK_EVENT,
	BLOW_UP_VEHICLE_EVENT,
	NETWORK_SPECIAL_FIRE_EQUIPPED_WEAPON,
	NETWORK_RESPONDED_TO_THREAT_EVENT,
	NETWORK_SHOUT_TARGET_POSITION,
	VOICE_DRIVEN_MOUTH_MOVEMENT_FINISHED_EVENT,
	PICKUP_DESTROYED_EVENT,
	UPDATE_PLAYER_SCARS_EVENT,
	NETWORK_CHECK_EXE_SIZE_EVENT,
	NETWORK_PTFX_EVENT,
	NETWORK_PED_SEEN_DEAD_PED_EVENT,
	REMOVE_STICKY_BOMB_EVENT,
	NETWORK_CHECK_CODE_CRCS_EVENT,
	INFORM_SILENCED_GUNSHOT_EVENT,
	PED_PLAY_PAIN_EVENT,
	CACHE_PLAYER_HEAD_BLEND_DATA_EVENT,
	REMOVE_PED_FROM_PEDGROUP_EVENT,
	NO_EVENT,
	REPORT_CASH_SPAWN_EVENT,
	EVENT_LIST_SIZE//always keep this one last
};
char* EVENT_NAMES[] = { "OBJECT_ID_FREED_EVENT","OBJECT_ID_REQUEST_EVENT","ARRAY_DATA_VERIFY_EVENT","SCRIPT_ARRAY_DATA_VERIFY_EVENT","REQUEST_CONTROL_EVENT","GIVE_CONTROL_EVENT","WEAPON_DAMAGE_EVENT","REQUEST_PICKUP_EVENT","REQUEST_MAP_PICKUP_EVENT","GAME_CLOCK_EVENT","GAME_WEATHER_EVENT","RESPAWN_PLAYER_PED_EVENT","GIVE_WEAPON_EVENT","REMOVE_WEAPON_EVENT","REMOVE_ALL_WEAPONS_EVENT","VEHICLE_COMPONENT_CONTROL_EVENT","FIRE_EVENT","EXPLOSION_EVENT","START_PROJECTILE_EVENT","ALTER_WANTED_LEVEL_EVENT","CHANGE_RADIO_STATION_EVENT","RAGDOLL_REQUEST_EVENT","PLAYER_TAUNT_EVENT","PLAYER_CARD_STAT_EVENT","DOOR_BREAK_EVENT","SCRIPTED_GAME_EVENT","REMOTE_SCRIPT_INFO_EVENT","REMOTE_SCRIPT_LEAVE_EVENT","MARK_AS_NO_LONGER_NEEDED_EVENT","CONVERT_TO_SCRIPT_ENTITY_EVENT","SCRIPT_WORLD_STATE_EVENT","INCIDENT_ENTITY_EVENT","CLEAR_AREA_EVENT","NETWORK_REQUEST_SYNCED_SCENE_EVENT","NETWORK_START_SYNCED_SCENE_EVENT","NETWORK_UPDATE_SYNCED_SCENE_EVENT","NETWORK_STOP_SYNCED_SCENE_EVENT","GIVE_PED_SCRIPTED_TASK_EVENT","GIVE_PED_SEQUENCE_TASK_EVENT","NETWORK_CLEAR_PED_TASKS_EVENT","NETWORK_START_PED_ARREST_EVENT","NETWORK_START_PED_UNCUFF_EVENT","NETWORK_SOUND_CAR_HORN_EVENT","NETWORK_ENTITY_AREA_STATUS_EVENT","NETWORK_GARAGE_OCCUPIED_STATUS_EVENT","PED_CONVERSATION_LINE_EVENT","SCRIPT_ENTITY_STATE_CHANGE_EVENT","NETWORK_PLAY_SOUND_EVENT","NETWORK_STOP_SOUND_EVENT","NETWORK_BANK_REQUEST_EVENT","REQUEST_DOOR_EVENT","NETWORK_TRAIN_REQUEST_EVENT","NETWORK_TRAIN_REPORT_EVENT","NETWORK_INCREMENT_STAT_EVENT","MODIFY_VEHICLE_LOCK_WORD_STATE_DATA","REQUEST_PHONE_EXPLOSION_EVENT","REQUEST_DETACHMENT_EVENT","KICK_VOTES_EVENT","GIVE_PICKUP_REWARDS_EVENT","NETWORK_CRC_HASH_CHECK_EVENT","BLOW_UP_VEHICLE_EVENT","NETWORK_SPECIAL_FIRE_EQUIPPED_WEAPON","NETWORK_RESPONDED_TO_THREAT_EVENT","NETWORK_SHOUT_TARGET_POSITION","VOICE_DRIVEN_MOUTH_MOVEMENT_FINISHED_EVENT","PICKUP_DESTROYED_EVENT","UPDATE_PLAYER_SCARS_EVENT","NETWORK_CHECK_EXE_SIZE_EVENT","NETWORK_PTFX_EVENT","NETWORK_PED_SEEN_DEAD_PED_EVENT","REMOVE_STICKY_BOMB_EVENT","NETWORK_CHECK_CODE_CRCS_EVENT","INFORM_SILENCED_GUNSHOT_EVENT","PED_PLAY_PAIN_EVENT","CACHE_PLAYER_HEAD_BLEND_DATA_EVENT","REMOVE_PED_FROM_PEDGROUP_EVENT","NO_EVENT","REPORT_CASH_SPAWN_EVENT" };
namespace TYPES {
	enum vehicleType {
		AUTOMOBILE,
		BIKE,
		BOAT,
		DOOR,
		HELI,
		OBJECT,
		PED,
		PICKUP,
		PICKUP_PLACEMENT,
		PLANE,
		SUBMARINE,
		PLAYER,
		TRAILER,
		TRAIN,
		GLASS_PANE
	};
};

//So these RPFTYPES are like weird because I don't quite understand why they are different than TYPES but they are, so not all are correct
namespace RPFTYPES {
	enum vehicleType {
		AUTOMOBILE,
		PLANE,//correct
		BOAT,
		DOOR,
		PED,
		OBJECT,
		HELI,//correct
		PICKUP,
		PICKUP_PLACEMENT,
		BIKE,
		SUBMARINE,
		PLAYER,
		TRAILER,
		TRAIN,
		GLASS_PANE
	};
};


/*
I wrote this so keeping it here anyways... would have to reformat other code though and ain't bothering
struct PlayerDataSend;
class SCEvent {
private:
	char *jsonData;                       //ptr to json data
	const int amtPlayers = 0x20;          //amount in player array
	PlayerDataSend players[amtPlayers];   //player array
	int spot;                             //current player count
public:
	SCEvent(char *_jsonData);             //create it
	void setJsonData(char *_jsonData);    //set the data
	void resetPlayers();                  //reset player list
	void addPlayer(char *name);           //add player by name
	unsigned int getPlayersAddress();     //private, used in send func
	void send();                          //send type 1 (to all the players said via addPlayer)
	void sendType2();                     //send type 2 (to all the players said via addPlayer)
	void pushEventOnPlayerInLobby(int player);      //set to send to player by player id
	void pushEventOnPlayerName(char *playerName);   //set to send to player by player name
	void pushEventOnLobby();              //set to send to everyone in lobby
};
*/





enum rceScriptInvoker {
	REQUEST_SCRIPT,
	NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT,
	_GET_NUMBER_OF_INSTANCES_OF_SCRIPT_WITH_NAME_HASH,
	HAS_SCRIPT_LOADED,
	START_NEW_SCRIPT,
	SET_SCRIPT_AS_NO_LONGER_NEEDED,
	NETWORK_IS_HOST_OF_THIS_SCRIPT,
	SET_THIS_SCRIPT_CAN_REMOVE_BLIPS_CREATED_BY_ANY_SCRIPT,
	SET_AUDIO_FLAG,
	SET_GPS_FLASHES,
	HIDE_HUD_AND_RADAR_THIS_FRAME,
	_0x6D6840CEE8845831,
	NETWORK_IS_ACTIVITY_SESSION,
	SET_AMBIENT_ZONE_STATE_PERSISTENT,
	NETWORK_IS_SCRIPT_ACTIVE,
	PLAYER_ID,
	WAIT,
	PLAYER_PED_ID,
	DOES_ENTITY_EXIST,
	IS_ENTITY_VISIBLE,
	SET_ENTITY_VISIBLE,
	_TRANSITION_FROM_BLURRED,
	_REMOVE_LOADING_PROMPT,
	NETWORK_SET_LOCAL_PLAYER_INVINCIBLE_TIME,
	_0xADED7F5748ACAFE6,
	_0xA8FDB297A8D25FBA,
	IS_PED_INJURED,
	_SET_ENTITY_SOMETHING,
	IS_NEW_LOAD_SCENE_ACTIVE,
	SET_PLAYER_TEAM,
	unk_0xE8C0C629,
	FREEZE_ENTITY_POSITION,
	NETWORK_IS_IN_SESSION,
	NETWORK_CAN_SESSION_END,
	NETWORK_SESSION_END,
	_NETWORK_GET_NUM_PARTICIPANTS_HOST,
	DOES_SCRIPT_VEHICLE_GENERATOR_EXIST,
	DELETE_SCRIPT_VEHICLE_GENERATOR,
	CREATE_SCRIPT_VEHICLE_GENERATOR,
	SET_SCRIPT_VEHICLE_GENERATOR,
	IS_BIT_SET,
	SET_BIT,
	CLEAR_BIT,
	INT_TO_PARTICIPANTINDEX,
	NETWORK_IS_PARTICIPANT_ACTIVE,
	NETWORK_GET_PLAYER_INDEX,
	_GET_POSIX_TIME,
	TRIGGER_SCRIPT_EVENT,
	INT_TO_PLAYERINDEX,
	NETWORK_HASH_FROM_PLAYER_HANDLE,
	VDIST,
	GET_NUMBER_OF_FIRES_IN_RANGE,
	IS_ANY_VEHICLE_NEAR_POINT,
	VMAG,
	GET_MODEL_DIMENSIONS,
	ABSF,
	IS_POINT_IN_ANGLED_AREA,
	COS,
	SIN,
	GET_PLAYER_PED,
	GET_ENTITY_COORDS,
	NETWORK_PLAYER_ID_TO_INT,
	ARE_STRINGS_EQUAL,
	IS_STRING_NULL_OR_EMPTY,
	GET_FRAME_COUNT,
	NETWORK_ARE_HANDLES_THE_SAME,
	NETWORK_IS_HANDLE_VALID,
	NETWORK_IS_GAME_IN_PROGRESS,
	GET_NETWORK_TIME,
	GET_TIME_DIFFERENCE,
	ABSI,
	GET_GAME_TIMER,
	_0x89023FBBF9200E9F,
	NETWORK_GET_THIS_SCRIPT_IS_NETWORK_SCRIPT,
	GET_NUM_RESERVED_MISSION_PEDS,
	GET_NUM_RESERVED_MISSION_VEHICLES,
	GET_NUM_RESERVED_MISSION_OBJECTS,
	GET_PLAYER_WANTED_LEVEL,
	IS_ENTITY_DEAD,
	IS_PED_A_PLAYER,
	NETWORK_GET_PLAYER_INDEX_FROM_PED,
	_NETWORK_IS_PLAYER_EQUAL_TO_INDEX,
	NETWORK_IS_IN_TUTORIAL_SESSION,
	DECOR_IS_REGISTERED_AS_TYPE,
	GET_PLAYER_PED_SCRIPT_INDEX,
	DECOR_EXIST_ON,
	DECOR_GET_INT,
	TO_FLOAT,
	ROUND,
	GET_RANDOM_INT_IN_RANGE,
	IS_PLAYER_TELEPORT_ACTIVE,
	GET_TIME_OFFSET,
	IS_TIME_MORE_THAN,
	IS_TIME_LESS_THAN,
	GET_PLAYER_TEAM,
	GET_DISTANCE_BETWEEN_COORDS,
	GET_RANDOM_FLOAT_IN_RANGE,
	_GET_OBJECT_OFFSET_FROM_COORDS,
	IS_PLAYER_PLAYING,
	NETWORK_IS_PLAYER_ACTIVE,
	_0xE64A3CA08DFA37A9,
	NETWORK_ADD_ENTITY_AREA,
	_0x4DF7CFFF471A7FB1,
	_0x4A2D4E8BF4265B0F,
	NETWORK_REMOVE_ENTITY_AREA,
	DOES_SCRIPT_EXIST,
	SET_PLAYER_CONTROL,
	SET_FRONTEND_ACTIVE,
	IS_SCREEN_FADED_OUT,
	IS_SCREEN_FADING_OUT,
	DO_SCREEN_FADE_OUT,
	SET_ENTITY_INVINCIBLE,
	START_NEW_SCRIPT_WITH_ARGS,
	CLEAR_PLAYER_WANTED_LEVEL,
	_0xC32EA7A2F6CA7557,
	_NETWORK_CLAN_ANIMATION,
	IS_PLAYER_ONLINE,
	_NETWORK_PLAYER_IS_IN_CLAN,
	NETWORK_CLAN_PLAYER_IS_ACTIVE,
	NETWORK_GET_LOCAL_HANDLE,
	NETWORK_IS_SIGNED_ONLINE,
	NETWORK_IS_SIGNED_IN,
	_0x67A5589628E0CFF6,
	IS_PLAYER_SWITCH_IN_PROGRESS,
	GET_POSIX_TIME,
	_0xAD5FDF34B81BFE79,
	STOP_PLAYER_TELEPORT,
	IS_PAUSE_MENU_ACTIVE,
	_0xEF7D17BC6C85264C,
	STOP_PLAYER_SWITCH,
	IS_ENTITY_FOCUS,
	CLEAR_FOCUS,
	NEW_LOAD_SCENE_START_SPHERE,
	NEW_LOAD_SCENE_STOP,
	IS_NEW_LOAD_SCENE_LOADED,
	_0x71E7B2E657449AAD,
	IS_PED_DEAD_OR_DYING,
	IS_SOCIAL_CLUB_ACTIVE,
	IS_WARNING_MESSAGE_ACTIVE,
	_STOP_ALL_SCREEN_EFFECTS,
	DOES_CAM_EXIST,
	GET_CAM_COORD,
	SET_ENTITY_COORDS,
	START_PLAYER_SWITCH,
	GET_CAM_ROT,
	GET_CAM_FOV,
	GET_CAM_FAR_CLIP,
	SET_PLAYER_SWITCH_OUTRO,
	_0x933BBEEB8C61B5F4,
	_0xD8295AF639FD9CB8,
	unk_0x4062FF73,
	_GET_SCREEN_EFFECT_IS_ACTIVE,
	_START_SCREEN_EFFECT,
	GET_INTERIOR_FROM_ENTITY,
	unk_0x59CC312D,
	SET_PLAYER_VISIBLE_LOCALLY,
	GET_PLAYER_SWITCH_TYPE,
	GET_PLAYER_SWITCH_STATE,
	DOES_ENTITY_BELONG_TO_THIS_SCRIPT,
	IS_ENTITY_A_MISSION_ENTITY,
	SET_ENTITY_AS_MISSION_ENTITY,
	DELETE_PED,
	SET_PLAYER_INVINCIBLE,
	_0x22A249A53034450A,
	_0xDE81239437E8C5A8,
	IS_PARTICLE_FX_DELAYED_BLINK,
	_0x7B226C785A52A0A9,
	GET_IDEAL_PLAYER_SWITCH_TYPE,
	REQUEST_MODEL,
	HAS_MODEL_LOADED,
	CREATE_PED,
	CLEAR_PED_TASKS_IMMEDIATELY,
	GET_ENTITY_HEADING,
	SET_PED_DESIRED_HEADING,
	SET_ENTITY_COLLISION,
	SET_FOCUS_ENTITY,
	SET_MODEL_AS_NO_LONGER_NEEDED,
	CLEAR_PED_TASKS,
	SET_BLOCKING_OF_NON_TEMPORARY_EVENTS,
	NETWORK_RESURRECT_LOCAL_PLAYER,
	RESURRECT_PED,
	REVIVE_INJURED_PED,
	RESET_PLAYER_ARREST_STATE,
	_RESET_LOCALPLAYER_STATE,
	_SET_FROZEN_RENDERING_DISABLED,
	_0xE1C8709406F2C41C,
	HIDE_HUD_COMPONENT_THIS_FRAME,
	HIDE_HELP_TEXT_THIS_FRAME,
	STOP_PAD_SHAKE,
	DISABLE_CONTROL_ACTION,
	IS_MOBILE_PHONE_CALL_ONGOING,
	STOP_SCRIPTED_CONVERSATION,
	GET_MOBILE_PHONE_POSITION,
	SET_MOBILE_PHONE_POSITION,
	BEGIN_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED,
	END_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED,
	STAT_GET_BOOL,
	CLEAR_AREA,
	SET_MULTIPLAYER_HUD_CASH,
	IS_MINIGAME_IN_PROGRESS,
	SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED,
	HAS_SCALEFORM_MOVIE_LOADED,
	SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED,
	NETWORK_HAS_CONTROL_OF_ENTITY,
	DECOR_REMOVE,
	_0x35F0B98A8387274D,
	NET_TO_VEH,
	NETWORK_DOES_NETWORK_ID_EXIST,
	SET_VEHICLE_AS_NO_LONGER_NEEDED,
	OVERRIDE_VEH_HORN,
	SET_VEHICLE_ENVEFF_SCALE,
	DECOR_SET_INT,
	GET_PLAYER_NAME,
	GET_HASH_KEY,
	NETWORK_IS_GAMER_IN_MY_SESSION,
	NETWORK_MEMBER_ID_FROM_GAMER_HANDLE,
	_0xFE26117A5841B2FF,
	_DOES_VEHICLE_HAVE_DECAL,
	NETWORK_GET_PLAYER_FROM_GAMER_HANDLE,
	_GET_VEHICLE_SUSPENSION_HEIGHT,
	_ADD_CLAN_DECAL_TO_VEHICLE,
	IS_VEHICLE_DRIVEABLE,
	GET_ENTITY_BONE_INDEX_BY_NAME,
	GET_ENTITY_MODEL,
	_0x595F028698072DD9,
	SET_VEHICLE_NUMBER_PLATE_TEXT,
	GET_NUMBER_OF_VEHICLE_NUMBER_PLATES,
	SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX,
	SET_VEHICLE_CUSTOM_PRIMARY_COLOUR,
	CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR,
	SET_VEHICLE_CUSTOM_SECONDARY_COLOUR,
	CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR,
	SET_VEHICLE_COLOURS,
	SET_VEHICLE_EXTRA_COLOURS,
	SET_VEHICLE_TYRE_SMOKE_COLOR,
	SET_VEHICLE_WINDOW_TINT,
	SET_VEHICLE_TYRES_CAN_BURST,
	SET_VEHICLE_DOORS_LOCKED,
	SET_VEHICLE_IS_STOLEN,
	GET_VEHICLE_LIVERY_COUNT,
	SET_VEHICLE_LIVERY,
	IS_THIS_MODEL_A_BICYCLE,
	IS_THIS_MODEL_A_BIKE,
	SET_VEHICLE_WHEEL_TYPE,
	IS_VEHICLE_A_CONVERTIBLE,
	RAISE_CONVERTIBLE_ROOF,
	LOWER_CONVERTIBLE_ROOF,
	IS_THIS_MODEL_A_HELI,
	IS_THIS_MODEL_A_BOAT,
	IS_VEHICLE_EXTRA_TURNED_ON,
	SET_VEHICLE_EXTRA,
	GET_NUM_MOD_KITS,
	SET_VEHICLE_MOD_KIT,
	TOGGLE_VEHICLE_MOD,
	GET_VEHICLE_MOD,
	REMOVE_VEHICLE_MOD,
	SET_VEHICLE_MOD,
	SET_VEHICLE_STRONG,
	SET_VEHICLE_HAS_STRONG_AXLES,
	GET_MOD_TEXT_LABEL,
	IS_DLC_PRESENT,
	CAN_REGISTER_MISSION_VEHICLES,
	CLEAR_AREA_OF_VEHICLES,
	CREATE_VEHICLE,
	VEH_TO_NET,
	NETWORK_GET_ENTITY_IS_NETWORKED,
	SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES,
	GET_ID_OF_THIS_THREAD,
	_0x07FB139B592FA687,
	_0xF7B79A50B905A30D,
	NETWORK_IS_FRIEND,
	NETWORK_HANDLE_FROM_PLAYER,
	NETWORK_CLAN_PLAYER_GET_DESC,
	IS_ENTITY_VISIBLE_TO_SCRIPT,
	_0x25B99872D588A101,
	GET_NTH_CLOSEST_VEHICLE_NODE_ID_WITH_HEADING,
	IS_VEHICLE_NODE_ID_VALID,
	GET_VEHICLE_NODE_POSITION,
	_GET_IS_SLOW_ROAD_FLAG,
	_GET_SUPPORTS_GPS_ROUTE_FLAG,
	GET_VEHICLE_NODE_PROPERTIES,
	VDIST2,
	GET_NTH_CLOSEST_VEHICLE_NODE_WITH_HEADING,
	GET_CLOSEST_ROAD,
	GET_NTH_CLOSEST_VEHICLE_NODE,
	GET_ANGLE_BETWEEN_2D_VECTORS,
	_SET_NETWORK_ID_SYNC_TO_PLAYER,
	IS_ANY_PED_NEAR_POINT,
	IS_ANY_OBJECT_NEAR_POINT,
	IS_SPHERE_VISIBLE,
	IS_SPHERE_VISIBLE_TO_PLAYER,
	GET_CLOSEST_VEHICLE,
	GET_PLAYERS_LAST_VEHICLE,
	GET_LAST_PED_IN_VEHICLE_SEAT,
	DECOR_GET_BOOL,
	DECOR_SET_BOOL,
	NETWORK_REQUEST_CONTROL_OF_ENTITY,
	GET_VEHICLE_DEFAULT_HORN,
	GET_VEHICLE_ENVEFF_SCALE,
	IS_VEHICLE_SEAT_FREE,
	GET_PED_IN_VEHICLE_SEAT,
	GET_VEHICLE_NUMBER_PLATE_TEXT,
	GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX,
	GET_VEHICLE_COLOURS,
	GET_VEHICLE_EXTRA_COLOURS,
	GET_VEHICLE_TYRE_SMOKE_COLOR,
	GET_VEHICLE_WINDOW_TINT,
	GET_VEHICLE_LIVERY,
	GET_VEHICLE_WHEEL_TYPE,
	GET_VEHICLE_DOOR_LOCK_STATUS,
	GET_VEHICLE_CUSTOM_SECONDARY_COLOUR,
	GET_CONVERTIBLE_ROOF_STATE,
	GET_VEHICLE_TYRES_CAN_BURST,
	IS_VEHICLE_STOLEN,
	GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM,
	GET_VEHICLE_CUSTOM_PRIMARY_COLOUR,
	GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM,
	IS_TOGGLE_MOD_ON,
	GET_VEHICLE_MOD_VARIATION,
	IS_PED_IN_ANY_VEHICLE,
	IS_VALID_INTERIOR,
	_0x121FB4DDDC2D5291,
	NETWORK_CAN_BET,
	NETWORK_CAN_SPEND_MONEY,
	NETWORK_SPENT_BETTING,
	unk_0x25915CB9,
	unk_0x18867C61,
	unk_0xB2E83B75,
	_0x0BCA1D2C47B0D269,
	NETWORK_PLAYER_IS_CHEATER,
	NETWORK_HAVE_ONLINE_PRIVILEGES,
	_0x422D396F80A96547,
	_0xC980E62E33DF1D5C,
	LEADERBOARDS2_WRITE_DATA,
	FLOOR,
	STAT_SET_INT,
	STAT_GET_INT,
	NETWORK_GET_VC_BANK_BALANCE,
	NETWORK_GET_VC_WALLET_BALANCE,
	unk_0xBEE23713,
	POW,
	STAT_SET_BOOL,
	GET_PED_ARMOUR,
	_0x616093EC6B139DD9,
	GET_PLAYER_MAX_ARMOUR,
	ADD_SHOCKING_EVENT_AT_POSITION,
	HAS_ANIM_EVENT_FIRED,
	ADD_AMMO_TO_PED,
	GIVE_WEAPON_TO_PED,
	GET_AMMO_IN_PED_WEAPON,
	SET_PED_AMMO,
	IS_CONTROL_PRESSED,
	IS_PED_RAGDOLL,
	IS_PED_RUNNING_RAGDOLL_TASK,
	IS_PED_IN_MELEE_COMBAT,
	IS_ENTITY_PLAYING_ANIM,
	SET_PED_STEALTH_MOVEMENT,
	TASK_PLAY_ANIM,
	SET_CURRENT_PED_WEAPON,
	REQUEST_ANIM_DICT,
	HAS_ANIM_DICT_LOADED,
	GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS,
	GET_GROUND_Z_FOR_3D_COORD,
	START_SHAPE_TEST_BOX,
	GET_SHAPE_TEST_RESULT,
	IS_DISABLED_CONTROL_JUST_PRESSED,
	GET_CURRENT_PED_WEAPON,
	IS_PLAYER_FREE_FOR_AMBIENT_TASK,
	IS_PLAYER_CONTROL_ON,
	IS_SCREEN_FADED_IN,
	IS_ENTITY_IN_AIR,
	IS_ENTITY_IN_WATER,
	IS_PED_ON_VEHICLE,
	IS_PED_IN_COVER,
	IS_HUD_COMPONENT_ACTIVE,
	unk_0xD315978E,
	_IS_PROJECTILE_TYPE_IN_RADIUS,
	_SET_WARNING_MESSAGE_3,
	unk_0x065C597B,
	NETWORK_IS_PLAYER_IN_MP_CUTSCENE,
	SET_LOCAL_PLAYER_VISIBLE_LOCALLY,
	SET_ENTITY_ALPHA,
	RESET_ENTITY_ALPHA,
	SET_FACIAL_IDLE_ANIM_OVERRIDE,
	_GET_VEHICLE_CLASS_MAX_SPEED,
	GET_VEHICLE_CLASS_MAX_ACCELERATION,
	GET_VEHICLE_CLASS_MAX_AGILITY,
	GET_VEHICLE_CLASS_MAX_TRACTION,
	GET_VEHICLE_CLASS_MAX_BRAKING,
	NETWORK_IS_IN_MP_CUTSCENE,
	IS_GAMEPLAY_CAM_RENDERING,
	_0xA13C11E1B5C06BFC,
	_GET_LABEL_TEXT,
	_0x583049884A2EEE3C,
	_SET_NOTIFICATION_TEXT_ENTRY,
	ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME,
	_SET_NOTIFICATION_COLOR_NEXT,
	ADD_TEXT_COMPONENT_INTEGER,
	_SET_NOTIFICATION_MESSAGE_2,
	_DRAW_NOTIFICATION,
	IS_PS3_VERSION,
	unk_0xAB07CBBE,
	IS_XBOX360_VERSION,
	IS_PC_VERSION,
	_GET_LENGTH_OF_STRING,
	GET_THIS_SCRIPT_NAME,
	IS_PED_SWIMMING_UNDER_WATER,
	PLAY_SOUND_FRONTEND,
	BEGIN_SCALEFORM_MOVIE_METHOD,
	_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT,
	END_SCALEFORM_MOVIE_METHOD,
	BEGIN_TEXT_COMMAND_SCALEFORM_STRING,
	END_TEXT_COMMAND_SCALEFORM_STRING,
	GET_CLOCK_SECONDS,
	GET_CLOCK_MINUTES,
	GET_CLOCK_HOURS,
	GET_CLOCK_DAY_OF_MONTH,
	GET_CLOCK_MONTH,
	GET_CLOCK_YEAR,
	IS_PEDHEADSHOT_VALID,
	IS_PEDHEADSHOT_READY,
	UNREGISTER_PEDHEADSHOT,
	IS_PED_SPRINTING,
	IS_SCRIPTED_CONVERSATION_ONGOING,
	IS_PED_IN_PARACHUTE_FREE_FALL,
	GET_IS_PED_GADGET_EQUIPPED,
	IS_PLAYER_CLIMBING,
	IS_PED_PLANTING_BOMB,
	IS_SPECIAL_ABILITY_ACTIVE,
	IS_AIM_CAM_ACTIVE,
	GET_PED_CONFIG_FLAG,
	RESTART_SCRIPTED_CONVERSATION,
	_0x14922ED3E38761F0,
	NETWORK_GET_FRIEND_COUNT,
	NETWORK_GET_FRIEND_NAME,
	NETWORK_IS_FRIEND_IN_MULTIPLAYER,
	IS_ORBIS_VERSION,
	_0x72D918C99BCACC54,
	_0xAEEF48CDF5B6CE7C,
	IS_DURANGO_VERSION,
	NETWORK_IS_CLOUD_AVAILABLE,
	HIDE_SCRIPTED_HUD_COMPONENT_THIS_FRAME,
	_0x25F87B30C382FCA7,
	DISPLAY_RADAR,
	IS_INTERIOR_READY,
	UNPIN_INTERIOR,
	_0xFF300C7649724A0B,
	_0x5A34CD9C3C5BEC44,
	RENDER_SCRIPT_CAMS,
	IS_CAM_ACTIVE,
	SET_CAM_ACTIVE,
	DESTROY_CAM,
	UNLOCK_MINIMAP_ANGLE,
	TEXTURE_DOWNLOAD_RELEASE,
	CLEAR_HELP,
	SET_WIDESCREEN_BORDERS,
	_0xC65AB383CD91DF98,
	NETWORK_DOES_ENTITY_EXIST_WITH_NETWORK_ID,
	NET_TO_ENT,
	SET_ENTITY_AS_NO_LONGER_NEEDED,
	IS_CAM_RENDERING,
	_0xFC18DB55AE19E046,
	SET_PED_COMPONENT_VARIATION,
	_0x1280804F7CFD2D6C,
	_0x687C0B594907D2E8,
	SET_PED_PROP_INDEX,
	CLEAR_PED_PROP,
	IS_PED_WEARING_HELMET,
	REMOVE_PED_HELMET,
	CLEAR_ALL_PED_PROPS,
	GET_PED_DRAWABLE_VARIATION,
	GET_PED_TEXTURE_VARIATION,
	GET_HASH_NAME_FOR_COMPONENT,
	_0x341DE7ED1D2A1BFD,
	SET_PED_HEAD_BLEND_DATA,
	unk_0xF48F3051,
	_CLEAR_PED_FACIAL_DECORATIONS,
	_SET_PED_DECORATION,
	_GET_TATTOO_ZONE,
	_GET_NUM_DECORATIONS,
	_0xFF56381874F82086,
	_IS_DLC_DATA_EMPTY,
	GET_SHOP_PED_COMPONENT,
	_GET_NUM_FORCED_COMPONENTS,
	GET_FORCED_COMPONENT,
	INIT_SHOP_PED_PROP,
	_GET_NUM_PROPS_FROM_OUTFIT,
	GET_SHOP_PED_QUERY_PROP,
	INIT_SHOP_PED_COMPONENT,
	GET_SHOP_PED_QUERY_COMPONENT,
	GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS,
	GET_NUMBER_OF_PED_TEXTURE_VARIATIONS,
	GET_PED_PROP_INDEX,
	GET_PED_PROP_TEXTURE_INDEX,
	GET_HASH_NAME_FOR_PROP,
	GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS,
	GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS,
	_0xC17AD0E5752BECDA,
	GET_VARIANT_COMPONENT,
	GET_SHOP_PED_OUTFIT,
	_0xA9F9C2E0FDE11CBB,
	_0xF3FBE2D50A6A8C28,
	GET_SHOP_PED_QUERY_OUTFIT,
	_GET_PROP_FROM_OUTFIT,
	unk_0x021F5B36,
	unk_0x8FDDB5DB,
	SET_PED_HEAD_OVERLAY,
	_GET_PSTAT_INT_HASH,
	_0x94F12ABF9C79E339,
	_GET_TUPSTAT_INT_HASH,
	STAT_GET_MASKED_INT,
	STAT_GET_FLOAT,
	GET_PED_PALETTE_VARIATION,
	SET_PLAYER_PARACHUTE_VARIATION_OVERRIDE,
	SET_PLAYER_PARACHUTE_PACK_TINT_INDEX,
	SET_PLAYER_PARACHUTE_PACK_MODEL_OVERRIDE,
	CLEAR_PLAYER_PARACHUTE_PACK_MODEL_OVERRIDE,
	unk_0xC560D7C0,
	unk_0x22DAE257,
	IS_ENTITY_ATTACHED,
	NETWORK_SET_OVERRIDE_SPECTATOR_MODE,
	SET_GAMEPLAY_CAM_RELATIVE_HEADING,
	SET_GAMEPLAY_CAM_RELATIVE_PITCH,
	NETWORK_END_TUTORIAL_SESSION,
	_STOP_SCREEN_EFFECT,
	SET_MAX_WANTED_LEVEL,
	NETWORK_SET_IN_MP_CUTSCENE,
	NETWORK_GET_TIMEOUT_TIME,
	IS_PED_SITTING_IN_ANY_VEHICLE,
	_0x48ADC8A773564670,
	GET_INTERIOR_AT_COORDS_WITH_TYPE,
	IS_INTERIOR_DISABLED,
	DISABLE_INTERIOR,
	_LOAD_INTERIOR,
	_0x82EBB79E258FA2B7,
	SET_ENTITY_HEADING,
	CLEAR_PED_WETNESS,
	GET_ENTITY_ROTATION,
	CLEAR_PED_BLOOD_DAMAGE,
	STOP_AUDIO_SCENE,
	IS_SCREEN_FADING_IN,
	DO_SCREEN_FADE_IN,
	IS_PED_SITTING_IN_VEHICLE,
	_0xE1CD1E48E025E661,
	IS_PED_FALLING,
	_GET_PSTAT_BOOL_HASH,
	_0xF4D8E7AC2A27758C,
	STAT_SET_BOOL_MASKED,
	_GET_TUPSTAT_BOOL_HASH,
	STAT_GET_BOOL_MASKED,
	HAS_COLLISION_LOADED_AROUND_ENTITY,
	SET_VEHICLE_ON_GROUND_PROPERLY,
	ACTIVATE_PHYSICS,
	SET_ENTITY_DYNAMIC,
	REMOVE_IPL,
	SET_AMBIENT_ZONE_LIST_STATE_PERSISTENT,
	SET_PED_CAN_BE_TARGETTED,
	GET_SCRIPT_TASK_STATUS,
	SET_PED_USING_ACTION_MODE,
	SET_PED_CAN_BE_DRAGGED_OUT,
	SET_PED_CONFIG_FLAG,
	SET_PLAYER_VEHICLE_DEFENSE_MODIFIER,
	unk_0x76A9FEB6,
	NETWORK_SET_FRIENDLY_FIRE_OPTION,
	GET_HEADING_FROM_VECTOR_2D,
	unk_0xE23416C1,
	IS_THREAD_ACTIVE,
	IS_PLAYER_DEAD,
	GET_INTERIOR_AT_COORDS,
	_0xFB1F9381E80FA13F,
	_0xFB8F2A6F3DF08CBE,
	_0xFEE4A5459472A9F8,
	_0x3C67506996001F5E,
	IS_NAVMESH_LOADED_IN_AREA,
	unk_0x76AFFBB5,
	_0x5A6FFA2433E2F14C,
	_0x4BA92A18502BCA61,
	_0x2DF9038C90AD5264,
	_0xB2AFF10216DEFA2F,
	GET_SAFE_COORD_FOR_PED,
	_0x3C891A251567DFCE,
	_0xF445DE8DA80A1792,
	_0xA586FBEB32A53DBB,
	_0xA635C11B8C44AFC2,
	NETWORK_GET_RESPAWN_RESULT,
	_0x280C7E3AC7F56E90,
	_0x6C34F1208B8923FD,
	_0xB782F8238512BAD5,
	_0x68772DB2B2526F9F,
	SQRT,
	GET_PED_NEARBY_PEDS,
	GET_PED_RELATIONSHIP_GROUP_HASH,
	GET_RELATIONSHIP_BETWEEN_GROUPS,
	IS_THIS_MODEL_A_PLANE,
	_ARE_COORDS_COLLIDING_WITH_EXTERIOR,
	GET_INTERIOR_GROUP_ID,
	ADD_NAVMESH_REQUIRED_REGION,
	REMOVE_NAVMESH_REQUIRED_REGIONS,
	_0x29C24BFBED8AB8FB,
	GET_INDEX_OF_CURRENT_LEVEL,
	SET_PED_RESET_FLAG,
	GET_VEHICLE_PED_IS_IN,
	IS_THIS_MODEL_A_CAR,
	STOP_FIRE_IN_RANGE,
	_START_SHAPE_TEST_RAY,
	CLEAR_AREA_OF_OBJECTS,
	NETWORK_GET_NETWORK_ID_FROM_ENTITY,
	IS_VEHICLE_MODEL,
	SET_NETWORK_VEHICLE_RESPOT_TIMER,
	IS_PED_IN_VEHICLE,
	NETWORK_DISABLE_INVINCIBLE_FLASHING,
	_SET_NETWORK_OBJECT_NON_CONTACT,
	NETWORK_GET_ENTITY_IS_LOCAL,
	GET_CLOSEST_VEHICLE_NODE,
	GET_ENTITY_FORWARD_VECTOR,
	START_SHAPE_TEST_CAPSULE,
	GET_CURRENT_PED_VEHICLE_WEAPON,
	GET_VEHICLE_PED_IS_USING,
	START_PLAYER_TELEPORT,
	GET_PLAYER_RADIO_STATION_INDEX,
	SET_PED_CAN_RAGDOLL,
	TASK_ENTER_VEHICLE,
	_0x2208438012482A1A,
	NETWORK_FADE_IN_ENTITY,
	_0xE851E480B814D4BA,
	SET_VEHICLE_CAN_BE_USED_BY_FLEEING_PEDS,
	_0xAB04325045427AAE,
	SET_NETWORK_ID_VISIBLE_IN_CUTSCENE,
	STAT_SET_LICENSE_PLATE,
	STAT_SET_MASKED_INT,
	SET_VEH_RADIO_STATION,
	ADD_TEXT_COMPONENT_SUBSTRING_TEXT_LABEL,
	_0x99AD4CCCB128CBC9,
	IS_MODEL_A_VEHICLE,
	GET_NUM_DLC_VEHICLES,
	GET_DLC_VEHICLE_DATA,
	IS_THIS_MODEL_A_QUADBIKE,
	IS_CUTSCENE_PLAYING,
	GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS,
	GET_RANDOM_VEHICLE_MODEL_IN_MEMORY,
	SET_VEHICLE_FIXED,
	SET_VEHICLE_ENGINE_ON,
	SET_VEHICLE_LIGHTS,
	SET_HELI_BLADES_FULL_SPEED,
	SET_VEHICLE_DOORS_LOCKED_FOR_TEAM,
	_0x5E569EC46EC21CAE,
	SET_VEHICLE_ENGINE_CAN_DEGRADE,
	DOES_EXTRA_EXIST,
	SET_CONVERTIBLE_ROOF,
	GET_LANDING_GEAR_STATE,
	CONTROL_LANDING_GEAR,
	_0x336511A34F2E5185,
	_SET_VEHICLE_ST,
	DELETE_VEHICLE,
	IS_MODEL_VALID,
	PARTICIPANT_ID,
	NETWORK_OVERRIDE_TRANSITION_CHAT,
	_0x77FADDCBE3499DF7,
	NETWORK_DO_TRANSITION_TO_FREEMODE,
	NETWORK_IS_HOST,
	NETWORK_DO_TRANSITION_TO_NEW_FREEMODE,
	_0xC5BE134EC7BA96A0,
	_0xF45352426FF3A4F0,
	_0xFD75DABC0957BF33,
	_0x1153FA02A659051C,
	_NETWORK_SCTV_SLOTS,
	SET_PLAYER_TARGETING_MODE,
	_0xCAE55F48D3D7875C,
	_0x3F52E880AAF6C8CA,
	_0xF1EEA2DDA9FFA69D,
	_NETWORK_SESSION_SET_MAX_PLAYERS,
	_0xF49ABC20D8552257,
	_GET_GAMEPLAY_CAM_COORDS,
	_GET_GAMEPLAY_CAM_ROT,
	_0x80EC114669DAEFF4,
	CREATE_CAM_WITH_PARAMS,
	SET_CAM_FOV,
	SET_CAM_PARAMS,
	STOP_GAMEPLAY_HINT,
	_0x6F72CD94F7B5B68C,
	GET_PAUSE_MENU_STATE,
	_0xD2B32BE3FC1626C6,
	IS_SRL_LOADED,
	END_SRL,
	CLEAR_PRINTS,
	_SWITCH_OUT_PLAYER,
	_SET_RADAR_BIGMAP_ENABLED,
	_0x2A2173E46DAECD12,
	_0x419594E137637120,
	NETWORK_SET_IN_SPECTATOR_MODE,
	KEY_HUD_COLOUR,
	NETWORK_IS_IN_SPECTATOR_MODE,
	_0xEE778F8C7E1142E2,
	_0x56C8B608CFD49854,
	RESERVE_NETWORK_MISSION_VEHICLES,
	IS_BIG_VEHICLE,
	IS_THIS_MODEL_A_TRAIN,
	COMPARE_STRINGS,
	NETWORK_GET_NUM_CONNECTED_PLAYERS,
	NETWORK_IS_SESSION_STARTED,
	NETWORK_SESSION_KICK_PLAYER,
	IS_GAMEPLAY_HINT_ACTIVE,
	SET_CINEMATIC_BUTTON_ACTIVE,
	IS_STRING_NULL,
	IS_ENTITY_A_PED,
	GET_PED_INDEX_FROM_ENTITY_INDEX,
	_0x7D7A2E43E74E2EB8,
	GET_PED_FLOOD_INVINCIBILITY,
	IS_TRACKED_PED_VISIBLE,
	IS_ENTITY_A_VEHICLE,
	GET_VEHICLE_INDEX_FROM_ENTITY_INDEX,
	TRACK_VEHICLE_VISIBILITY,
	IS_VEHICLE_VISIBLE,
	IS_ENTITY_AN_OBJECT,
	GET_OBJECT_INDEX_FROM_ENTITY_INDEX,
	TRACK_OBJECT_VISIBILITY,
	IS_OBJECT_VISIBLE,
	IS_HELP_MESSAGE_BEING_DISPLAYED,
	IS_ENTITY_ON_SCREEN,
	TASK_CLEAR_LOOK_AT,
	BEGIN_TEXT_COMMAND_DISPLAY_HELP,
	END_TEXT_COMMAND_DISPLAY_HELP,
	IS_FOLLOW_VEHICLE_CAM_ACTIVE,
	GET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL,
	IS_GAMEPLAY_CAM_LOOKING_BEHIND,
	IS_PED_MALE,
	SET_GAMEPLAY_ENTITY_HINT,
	TASK_LOOK_AT_ENTITY,
	START_AUDIO_SCENE,
	GET_IS_TASK_ACTIVE,
	IS_PLAYER_TARGETTING_ANYTHING,
	IS_DISABLED_CONTROL_JUST_RELEASED,
	IS_DISABLED_CONTROL_PRESSED,
	_0xC64DED7EF0D2FE37,
	_0x4C61B39930D045DA,
	IS_ENTITY_IN_ANGLED_AREA,
	_CLAMP_GAMEPLAY_CAM_PITCH,
	GET_PED_NEARBY_VEHICLES,
	SET_VEHICLE_DOORS_LOCKED_FOR_ALL_PLAYERS,
	_0xCFD778E7904C255E,
	NETWORK_HAS_CONTROL_OF_NETWORK_ID,
	GET_PLAYER_RADIO_STATION_NAME,
	SET_VEHICLE_DOORS_LOCKED_FOR_PLAYER,
	DOES_BLIP_EXIST,
	REMOVE_BLIP,
	ADD_BLIP_FOR_ENTITY,
	SET_BLIP_SPRITE,
	SET_BLIP_PRIORITY,
	SET_BLIP_NAME_FROM_TEXT_FILE,
	SET_BLIP_FLASHES,
	SET_BLIP_FLASH_TIMER,
	SET_ENTITY_LOCALLY_INVISIBLE,
	SET_PLAYER_WANTED_LEVEL,
	SET_PLAYER_WANTED_LEVEL_NOW,
	NETWORK_REQUEST_CONTROL_OF_NETWORK_ID,
	DELETE_ENTITY,
	NETWORK_FADE_OUT_ENTITY,
	SET_VEHICLE_BRAKE_LIGHTS,
	SET_VEHICLE_INDICATOR_LIGHTS,
	DOES_SCENARIO_GROUP_EXIST,
	IS_SCENARIO_GROUP_ENABLED,
	SET_SCENARIO_GROUP_ENABLED,
	GET_VEHICLE_ENGINE_HEALTH,
	SET_VEHICLE_ENGINE_HEALTH,
	GET_VEHICLE_PETROL_TANK_HEALTH,
	SET_VEHICLE_PETROL_TANK_HEALTH,
	GET_VEHICLE_BODY_HEALTH,
	SET_VEHICLE_BODY_HEALTH,
	STAT_GET_NUMBER_OF_DAYS,
	STAT_GET_NUMBER_OF_HOURS,
	STAT_GET_NUMBER_OF_MINUTES,
	NETWORK_BUY_ITEM,
	GET_PLAYER_INDEX,
	STAT_GET_POS,
	ROLL_DOWN_WINDOWS,
	IS_ENTITY_AT_ENTITY,
	SET_VEHICLE_EXCLUSIVE_DRIVER,
	_0xDBC631F109350B8C,
	GET_ENTITY_SCRIPT,
	NETWORK_IS_PLAYER_MUTED_BY_ME,
	NETWORK_IS_PLAYER_BLOCKED_BY_ME,
	NETWORK_AM_I_BLOCKED_BY_PLAYER,
	NETWORK_AM_I_MUTED_BY_PLAYER,
	GET_ONSCREEN_KEYBOARD_RESULT,
	NETWORK_SEND_TEXT_MESSAGE,
	_0x7543BB439F63792B,
	_DRAW_NOTIFICATION_CLAN_INVITE,
	_DRAW_NOTIFICATION_APARTMENT_INVITE,
	unk_0x761BE00B,
	DISPLAY_ONSCREEN_KEYBOARD,
	_0x3ED1438C1F5C6612,
	_DISPLAY_ONSCREEN_KEYBOARD_2,
	UPDATE_ONSCREEN_KEYBOARD,
	GET_LENGTH_OF_LITERAL_STRING,
	_GET_TEXT_SUBSTRING,
	_SC_HAS_CHECK_STRING_TASK_COMPLETED,
	_SC_GET_CHECK_STRING_STATUS,
	_0x930DE22F07B1CCE3,
	_SC_START_CHECK_STRING_TASK,
	_REMOVE_NOTIFICATION,
	_0x66B59CFFD78467AF,
	unk_0xA79E5B05,
	GET_PED_PARACHUTE_STATE,
	unk_0xF1F5DCF0,
	_0xA0F93D5465B3094D,
	_0x34770B9CE0E03B91,
	_0x88578F6EC36B4A3A,
	_0x71B008056E5692D6,
	LEADERBOARDS_READ_CLEAR,
	LEADERBOARDS2_READ_BY_HANDLE,
	LEADERBOARDS_READ_PENDING,
	LEADERBOARDS_READ_SUCCESSFUL,
	_0xA31FD15197B192BD,
	PLAYSTATS_AWARD_XP,
	GET_LOCAL_PLAYER_AIM_STATE,
	_GET_NUM_MEMBERSHIP_DESC,
	NETWORK_CLAN_GET_MEMBERSHIP_DESC,
	_0x855BC38818F6F684,
	NETWORK_SESSION_VOICE_LEAVE,
	NETWORK_IS_FRIEND_ONLINE,
	NETWORK_IS_GAMER_MUTED_BY_ME,
	NETWORK_IS_GAMER_BLOCKED_BY_ME,
	NETWORK_AM_I_MUTED_BY_GAMER,
	NETWORK_AM_I_BLOCKED_BY_GAMER,
	NETWORK_SET_KEEP_FOCUSPOINT,
	GET_ENTITY_SUBMERGED_LEVEL,
	IS_CUTSCENE_ACTIVE,
	NETWORK_IS_SESSION_ACTIVE,
	NETWORK_PLAYER_HAS_HEADSET,
	IS_CONTROL_JUST_PRESSED,
	_0xEF0912DDF7C4CB4B,
	NETWORK_SET_PROPERTY_ID,
	NETWORK_CLEAR_PROPERTY_ID,
	_0x919B3C98ED8292F9,
	_0xBBDF066252829606,
	NETWORK_IS_IN_TRANSITION,
	SET_BLIP_COLOUR,
	GET_BLIP_COLOUR,
	SET_BLIP_AS_SHORT_RANGE,
	ADD_BLIP_FOR_COORD,
	SET_BLIP_SCALE,
	SET_BLIP_ROUTE,
	NETWORK_PAY_UTILITY_BILL,
	NETWORK_PAY_EMPLOYEE_WAGE,
	_0xA9CBFD40B3FA3010,
	_0xFDB423997FA30340,
	DELETE_OBJECT,
	_0xE3B05614DCE1D014,
	DRAW_SCALEFORM_MOVIE_FULLSCREEN_MASKED,
	DRAW_SCALEFORM_MOVIE_FULLSCREEN,
	REQUEST_SCALEFORM_MOVIE,
	_0x1AD5B71586B94820,
	SET_RELATIONSHIP_BETWEEN_GROUPS,
	REMOVE_CUTSCENE,
	HAS_CUTSCENE_LOADED,
	NETWORK_SET_VOICE_ACTIVE,
	START_CUTSCENE,
	SET_FRONTEND_RADIO_ACTIVE,
	HAS_CUTSCENE_FINISHED,
	REMOVE_ANIM_DICT,
	SET_PLAYER_INVISIBLE_LOCALLY,
	NETWORK_BLOCK_INVITES,
	_NETWORK_BLOCK_INVITES_2,
	_0x5AA3BEFA29F03AD4,
	_0x0D01D20616FC73FB,
	GET_PROFILE_SETTING,
	SET_PARTICLE_FX_CAM_INSIDE_VEHICLE,
	DISPLAY_HUD,
	SET_USER_RADIO_CONTROL_ENABLED,
	SPECIAL_ABILITY_DEACTIVATE_FAST,
	SET_ALL_RANDOM_PEDS_FLEE,
	SET_POLICE_IGNORE_PLAYER,
	_0x03FC694AE06C5A20,
	CLEAR_FLOATING_HELP,
	_NETWORK_RESPAWN_PLAYER,
	IS_PED_DUCKING,
	SET_PED_DUCKING,
	CLEAR_TIMECYCLE_MODIFIER,
	IS_CAM_INTERPOLATING,
	DISABLE_FRONTEND_THIS_FRAME,
	GET_FRAME_TIME,
	SET_TIMECYCLE_MODIFIER_STRENGTH,
	SET_TRANSITION_TIMECYCLE_MODIFIER,
	REQUEST_CUTSCENE,
	_0xFB680D403909DC70,
	SET_LOCAL_PLAYER_VISIBLE_IN_CUTSCENE,
	SET_CUTSCENE_TRIGGER_AREA,
	ADD_NAVMESH_BLOCKING_OBJECT,
	SET_PED_NON_CREATION_AREA,
	START_CUTSCENE_AT_COORDS,
	NETWORK_OVERRIDE_CLOCK_TIME,
	SET_OVERRIDE_WEATHER,
	REMOVE_NAVMESH_BLOCKING_OBJECT,
	CLEAR_PED_NON_CREATION_AREA,
	_0xDC459CFA0CCE245B,
	CLEAR_OVERRIDE_WEATHER,
	CREATE_CAM,
	DRAW_RECT,
	NETWORK_IS_CLOCK_TIME_OVERRIDDEN,
	NETWORK_CLEAR_CLOCK_TIME_OVERRIDE,
	_SET_CAM_EFFECT,
	unk_0xF3A6309E,
	unk_0xAB688DAB,
	NETWORK_RESET_BODY_TRACKER,
	STAT_GET_STRING,
	IS_ENTITY_AT_COORD,
	GET_ROOM_KEY_FROM_ENTITY,
	SET_BLIP_DISPLAY,
	REQUEST_SCRIPT_AUDIO_BANK,
	RELEASE_NAMED_SCRIPT_AUDIO_BANK,
	_0x4669B3ED80F24B4E,
	NETWORK_GET_HOST_OF_SCRIPT,
	REMOVE_SCENARIO_BLOCKING_AREA,
	ADD_SCENARIO_BLOCKING_AREA,
	SHOW_TICK_ON_BLIP,
	_DOES_DOOR_EXIST,
	NETWORK_HAS_CONTROL_OF_DOOR,
	_SET_DOOR_ACCELERATION_LIMIT,
	_0x4BC2854478F3A749,
	_0x160AA1B32F6139B8,
	REMOVE_DOOR_FROM_SYSTEM,
	NETWORK_REQUEST_CONTROL_OF_DOOR,
	ADD_DOOR_TO_SYSTEM,
	DOES_PICKUP_EXIST,
	REMOVE_PICKUP,
	CREATE_PICKUP_ROTATE,
	SET_PICKUP_REGENERATION_TIME,
	GET_PED_MAX_HEALTH,
	_GET_WEAPON_HASH_FROM_PICKUP,
	GET_MAX_AMMO_IN_CLIP,
	_0x6ADAABD3068C5235,
	_REQUEST_VEHICLE_PHONE_EXPLOSION,
	SET_VEHICLE_TIMED_EXPLOSION,
	NETWORK_PLAYER_IS_BADSPORT,
	STAT_GET_DATE,
	_0x60EDD13EB3AC1FF3,
	STAT_SET_DATE,
	STAT_SET_FLOAT,
	GET_HUD_COLOUR,
	DRAW_MARKER,
	BEGIN_TEXT_COMMAND_CLEAR_PRINT,
	END_TEXT_COMMAND_CLEAR_PRINT,
	_ADD_TEXT_COMPONENT_SCALEFORM,
	BEGIN_TEXT_COMMAND_IS_MESSAGE_DISPLAYED,
	END_TEXT_COMMAND_IS_MESSAGE_DISPLAYED,
	GET_BLIP_INFO_ID_DISPLAY,
	SET_ALL_RANDOM_PEDS_FLEE_THIS_FRAME,
	SHAKE_CAM,
	TRIGGER_MUSIC_EVENT,
	SET_BLIP_ROUTE_COLOUR,
	SET_PED_CAN_PLAY_AMBIENT_ANIMS,
	SET_PED_CAN_USE_AUTO_CONVERSATION_LOOKAT,
	PAUSE_SCRIPTED_CONVERSATION,
	GET_DLC_VEHICLE_FLAGS,
	SET_ENTITY_CAN_BE_DAMAGED,
	CREATE_MODEL_HIDE,
	CREATE_MODEL_SWAP,
	REQUEST_IPL,
	REMOVE_MODEL_HIDE,
	REMOVE_MODEL_SWAP,
	GET_VEHICLE_NUMBER_OF_PASSENGERS,
	IS_PED_IN_ANY_HELI,
	IS_PED_IN_ANY_PLANE,
	GET_NUM_VEHICLE_MODS,
	DISABLE_ALL_CONTROL_ACTIONS,
	ENABLE_CONTROL_ACTION,
	IS_ENTITY_OCCLUDED,
	NETWORK_GET_NUM_SCRIPT_PARTICIPANTS,
	_0x3B39236746714134,
	SET_WANTED_LEVEL_DIFFICULTY,
	RESET_WANTED_LEVEL_DIFFICULTY,
	GET_MAX_WANTED_LEVEL,
	GET_WEAPONTYPE_GROUP,
	GET_PLAYER_SPRINT_TIME_REMAINING,
	_0xE6B0E8CFC3633BF0,
	HAS_PED_GOT_WEAPON,
	unk_0xDB0A7A58,
	IS_POSITION_OCCUPIED,
	_0x82377B65E943F72D,
	_GET_CURRENT_NOTIFICATION,
	unk_0x7C43D32A,
	unk_0x616D5040,
	unk_0x815CAE99,
	GET_VEHICLE_MODEL_NUMBER_OF_SEATS,
	IS_VEHICLE_TYRE_BURST,
	IS_WAYPOINT_ACTIVE,
	_0xE67C6DFD386EA5E7,
	SET_STORE_ENABLED,
	TASK_GO_STRAIGHT_TO_COORD,
	NETWORK_SET_TEAM_ONLY_CHAT,
	NETWORK_SET_TALKER_PROXIMITY,
	_0x3C5C1E2C2FF814B1,
	SET_ALL_VEHICLE_GENERATORS_ACTIVE_IN_AREA,
	SET_ROADS_BACK_TO_ORIGINAL_IN_ANGLED_AREA,
	DESTROY_ALL_CAMS,
	PARTICIPANT_ID_TO_INT,
	OPEN_SEQUENCE_TASK,
	CLOSE_SEQUENCE_TASK,
	TASK_PERFORM_SEQUENCE,
	CLEAR_SEQUENCE_TASK,
	_0xB56BBBCC2955D9CB,
	_0x2A56C06EBEF2B0D9,
	REGISTER_ENTITY_FOR_CUTSCENE,
	CLONE_PED_TO_TARGET,
	ADD_BLIP_FOR_RADIUS,
	SET_BLIP_ALPHA,
	_0x75A16C3DA34F1245,
	SET_BLIP_AS_MISSION_CREATOR_BLIP,
	BEGIN_TEXT_COMMAND_SET_BLIP_NAME,
	END_TEXT_COMMAND_SET_BLIP_NAME,
	TASK_FOLLOW_NAV_MESH_TO_COORD,
	TASK_TURN_PED_TO_FACE_COORD,
	HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY,
	CREATE_PED_INSIDE_VEHICLE,
	SET_ENTITY_PROOFS,
	SET_PED_RELATIONSHIP_GROUP_HASH,
	SET_PED_RANDOM_COMPONENT_VARIATION,
	REQUEST_VEHICLE_RECORDING,
	HAS_VEHICLE_RECORDING_BEEN_LOADED,
	SET_ENTITY_CAN_BE_DAMAGED_BY_RELATIONSHIP_GROUP,
	START_PLAYBACK_RECORDED_VEHICLE,
	SKIP_TIME_IN_PLAYBACK_RECORDED_VEHICLE,
	PAUSE_PLAYBACK_RECORDED_VEHICLE,
	_0x788E7FD431BD67F1,
	_0x784BA7E0ECEB4178,
	_0xB094BC1DB4018240,
	_0x7679CC1BCEBE3D4C,
	IS_PLAYBACK_GOING_ON_FOR_VEHICLE,
	UNPAUSE_PLAYBACK_RECORDED_VEHICLE,
	CREATE_SYNCHRONIZED_SCENE,
	ATTACH_SYNCHRONIZED_SCENE_TO_ENTITY,
	TASK_SYNCHRONIZED_SCENE,
	PLAY_SYNCHRONIZED_ENTITY_ANIM,
	IS_SYNCHRONIZED_SCENE_RUNNING,
	GET_SYNCHRONIZED_SCENE_PHASE,
	FORCE_PED_MOTION_STATE,
	_0x3044240D2E0FA842,
	HAS_ACHIEVEMENT_BEEN_PASSED,
	GIVE_ACHIEVEMENT_TO_PLAYER,
	_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_FLOAT,
	_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_BOOL,
	CREATE_OBJECT,
	GET_PED_BONE_INDEX,
	ATTACH_ENTITY_TO_ENTITY,
	_0x7350823473013C02,
	SET_PED_DEFAULT_COMPONENT_VARIATION,
	_IS_VEHICLE_MOD_LOAD_DONE,
	STOP_GAMEPLAY_CAM_SHAKING,
	CUSTOM_MENU_COORDINATES,
	_0x0225778816FDC28C,
	CLEAR_ENTITY_LAST_DAMAGE_ENTITY,
	SET_ENTITY_HEALTH,
	_LEADERBOARDS_DEATHS,
	HAS_PED_GOT_WEAPON_COMPONENT,
	SET_PED_SHOOTS_AT_COORD,
	GET_ENTITY_ANIM_CURRENT_TIME,
	SET_PED_TO_RAGDOLL,
	SET_WANTED_LEVEL_MULTIPLIER,
	NETWORK_BUY_HEALTHCARE,
	SET_VEHICLE_DIRT_LEVEL,
	REMOVE_DECALS_FROM_VEHICLE,
	FORCE_ENTITY_AI_AND_ANIMATION_UPDATE,
	NET_TO_PED,
	TASK_LEAVE_ANY_VEHICLE,
	RESET_PED_LAST_VEHICLE,
	SET_PED_COMBAT_ATTRIBUTES,
	SET_PED_FLEE_ATTRIBUTES,
	SET_PED_KEEP_TASK,
	GET_VEHICLE_MOD_KIT,
	_0xEEBFC7A7EFDC35B4,
	_GET_VEHICLE_HORN_HASH,
	GET_VEHICLE_MOD_MODIFIER_VALUE,
	GET_VEHICLE_MOD_KIT_TYPE,
	IS_POINT_OBSCURED_BY_A_MISSION_ENTITY,
	GET_NAME_OF_ZONE,
	_0xDA024BDBD600F44A,
	_0x6AFD2CD753FEEF83,
	ARE_PLAYER_FLASHING_STARS_ABOUT_TO_DROP,
	ARE_PLAYER_STARS_GREYED_OUT,
	GET_GAMEPLAY_CAM_COORD,
	_0xA071E0ED98F91286,
	GET_PED_BONE_COORDS,
	_0x4008EDF7D6E48175,
	REGISTER_SCRIPT_WITH_AUDIO,
	RELEASE_SCRIPT_AUDIO_BANK,
	SET_PLAYER_WEAPON_DAMAGE_MODIFIER,
	SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER,
	SET_PLAYER_WEAPON_DEFENSE_MODIFIER,
	SET_PLAYER_MELEE_WEAPON_DEFENSE_MODIFIER,
	STOP_STREAM,
	LOAD_STREAM,
	PLAY_STREAM_FRONTEND,
	REQUEST_STREAMED_TEXTURE_DICT,
	HAS_STREAMED_TEXTURE_DICT_LOADED,
	_SCREEN_DRAW_POSITION_BEGIN,
	_SCREEN_DRAW_POSITION_RATIO,
	_SCREEN_DRAW_POSITION_END,
	HAS_SOUND_FINISHED,
	_0xC8F3AAF93D0600BF,
	unk_0xAB6BD72F,
	_DRAW_NOTIFICATION_AWARD,
	IS_HUD_HIDDEN,
	IS_RADAR_HIDDEN,
	IS_STUNT_JUMP_MESSAGE_SHOWING,
	IS_STUNT_JUMP_IN_PROGRESS,
	IS_FIRST_PERSON_AIM_CAM_ACTIVE,
	IS_HELP_MESSAGE_ON_SCREEN,
	IS_PED_GETTING_INTO_A_VEHICLE,
	_0xA48931185F0536FE,
	SET_PLAYER_MAY_NOT_ENTER_ANY_VEHICLE,
	CLEAR_THIS_PRINT,
	IS_PED_WALKING,
	IS_PED_RUNNING,
	STOP_PED_WEAPON_FIRING_WHEN_DROPPED,
	SET_PED_DROPS_INVENTORY_WEAPON,
	GET_BEST_PED_WEAPON,
	TASK_SCRIPTED_ANIMATION,
	GET_SAFE_PICKUP_COORDS,
	CREATE_AMBIENT_PICKUP,
	STOP_ANIM_TASK,
	SET_PED_LEG_IK_MODE,
	GET_NUMBER_OF_EVENTS,
	GET_EVENT_AT_INDEX,
	GET_EVENT_DATA,
	DOES_TEXT_LABEL_EXIST,
	_0x451294E859ECC018,
	_0x9D728C1E12BF5518,
	REMOVE_WEAPON_FROM_PED,
	IS_WEAPON_VALID,
	SET_PLAYER_PARACHUTE_TINT_INDEX,
	SET_PLAYER_PARACHUTE_MODEL_OVERRIDE,
	SET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR,
	SET_PLAYER_CAN_LEAVE_PARACHUTE_SMOKE_TRAIL,
	GET_PED_AMMO_TYPE_FROM_WEAPON,
	SET_PED_AMMO_BY_TYPE,
	_PED_SKIP_NEXT_RELOADING,
	SET_PED_WEAPON_TINT_INDEX,
	GIVE_WEAPON_COMPONENT_TO_PED,
	GET_NUM_DLC_WEAPONS,
	GET_DLC_WEAPON_DATA,
	_GET_PED_HEAD_BLEND_DATA,
	unk_0x7B2A0337,
	unk_0x99F58A07,
	SET_NIGHTVISION,
	GET_PLAYER_HAS_RESERVE_PARACHUTE,
	HAS_THIS_ADDITIONAL_TEXT_LOADED,
	REQUEST_ADDITIONAL_TEXT,
	GET_ENTITY_HEALTH,
	_0x33EE12743CCD6343,
	IS_VEHICLE_STOPPED,
	IS_PED_IN_FLYING_VEHICLE,
	IS_VEHICLE_ON_ALL_WHEELS,
	IS_PED_IN_ANY_BOAT,
	IS_PED_IN_ANY_TRAIN,
	IS_PED_IN_ANY_SUB,
	IS_PED_ON_ANY_BIKE,
	GET_ENTITY_SPEED,
	HAS_ENTITY_COLLIDED_WITH_ANYTHING,
	_0xD3D15555431AB793,
	_0x996DD1E1E02F1008,
	GET_PED_RESET_FLAG,
	_SET_VEHICLE_HALT,
	IS_PED_STOPPED,
	_0x95CF81BD06EE1887,
	REMOVE_MULTIPLAYER_BANK_CASH,
	_0xC2D15BEF167E27BC,
	SET_MULTIPLAYER_BANK_CASH,
	_0x82CEDC33687E1F50,
	IS_AUDIO_SCENE_ACTIVE,
	_BEGIN_SCALEFORM_MOVIE_METHOD_HUD_COMPONENT,
	_HAS_HUD_SCALEFORM_LOADED,
	GET_LOCAL_TIME,
	PLAYSTATS_RANK_UP,
	CEIL,
	SET_PED_MAX_HEALTH,
	_0x975D66A0BC17064C,
	SET_PLAYER_MAX_ARMOUR,
	SET_PED_ARMOUR,
	_0x06A320535F5F0248,
	GET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR,
	SET_SWIM_MULTIPLIER_FOR_PLAYER,
	SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER,
	SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER,
	GET_PEDHEADSHOT_TXD_STRING,
	_SET_NOTIFICATION_MESSAGE,
	SET_AUTO_GIVE_PARACHUTE_WHEN_ENTER_PLANE,
	GET_NUM_DLC_WEAPON_COMPONENTS,
	GET_DLC_WEAPON_COMPONENT_DATA,
	_REQUEST_HUD_SCALEFORM,
	_0x09C0403ED9A751C2,
	_SET_UI_LAYER,
	DRAW_SCALEFORM_MOVIE,
	_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_STRING,
	ADD_TEXT_COMPONENT_SUBSTRING_TIME,
	_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_BUTTON_NAME,
	_CLEAR_NOTIFICATIONS_POS,
	NETWORK_SESSION_IS_CLOSED_FRIENDS,
	NETWORK_SESSION_IS_CLOSED_CREW,
	NETWORK_SESSION_IS_SOLO,
	NETWORK_SESSION_IS_PRIVATE,
	IS_FRONTEND_FADING,
	SET_PED_CURRENT_WEAPON_VISIBLE,
	SET_CAM_COORD,
	SET_CAM_ROT,
	_0x5A43C76F7FC7BA5F,
	unk_0x4C4C10CF,
	SET_BLIP_HIGH_DETAIL,
	NETWORK_EARN_FROM_NOT_BADSPORT,
	_SET_NOTIFICATION_FLASH_COLOR,
	_0x17AD8C9706BDD88A,
	_DRAW_NOTIFICATION_2,
	_0xFDD85225B2DEA55E,
	_GET_DATE_AND_TIME_FROM_UNIX_EPOCH,
	_0xBC1CC91205EC8D6E,
	_0xBFA0A56A817C6C7D,
	_0xDF649C4E9AFDD788,
	SHIFT_RIGHT,
	SHIFT_LEFT,
	STAT_SET_POS,
	GET_PLAYER_WANTED_CENTRE_POSITION,
	GET_WANTED_LEVEL_RADIUS,
	SET_PLAYER_WANTED_CENTRE_POSITION,
	_NETWORK_GET_PLAYER_CREW_EMBLEM_TXD_NAME,
	unk_0x76FB0F21,
	LEADERBOARDS_GET_CACHE_EXISTS,
	LEADERBOARDS_GET_CACHE_TIME,
	_0x8EC74CEB042E7CFF,
	NETWORK_PLAYER_IS_ROCKSTAR_DEV,
	_0x26F07DD83A5F7F98,
	_0xB309EBEA797E001F,
	_0xADB57E5B663CCA8B,
	DOES_VEHICLE_HAVE_ROOF,
	NETWORK_GET_NUM_PARTICIPANTS,
	_NETWORK_IS_PLAYER_IN_SCRIPT,
	SET_VEHICLE_IS_WANTED,
	_NETWORK_SESSION_IS_PLAYER_VOTED_TO_KICK,
	_0x5DA3A8DE8CB6226F,
	_0xD7D22F5592AED8BA,
	_NETWORK_CHAT_MUTE,
	HAS_PLAYER_BEEN_SPOTTED_IN_STOLEN_VEHICLE,
	NETWORK_IS_PLAYER_A_PARTICIPANT,
	NETWORK_GET_PARTICIPANT_INDEX,
	_0x5C707A667DF8B9FA,
	REQUEST_PTFX_ASSET,
	HAS_PTFX_ASSET_LOADED,
	GET_ENTITY_ATTACHED_TO,
	START_PARTICLE_FX_LOOPED_ON_ENTITY,
	STOP_PARTICLE_FX_LOOPED,
	START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE,
	_HAS_MP_GAMER_TAG,
	IS_MP_GAMER_TAG_ACTIVE,
	_SET_MP_GAMER_TAG_,
	ADD_TREVOR_RANDOM_MODIFIER,
	REMOVE_MP_GAMER_TAG,
	_HAS_MP_GAMER_TAG_2,
	unk_0x0098D244,
	SET_MP_GAMER_TAG_WANTED_LEVEL,
	SET_MP_GAMER_TAG_NAME,
	_SET_MP_GAMER_TAG_CHATTING,
	SET_MP_GAMER_TAG_VISIBILITY,
	_SET_MP_GAMER_TAG_COLOR,
	SET_MP_GAMER_TAG_HEALTH_BAR_COLOUR,
	SET_MP_GAMER_TAG_COLOUR,
	SET_MP_GAMER_TAG_ALPHA,
	_0x0C15B0E443B2349D,
	NETWORK_IS_PLAYER_TALKING,
	_SET_MP_GAMER_TAG_ICONS,
	GET_ENTITY_ALPHA,
	GET_BLIP_ALPHA,
	IS_PLAYER_TARGETTING_ENTITY,
	IS_PLAYER_FREE_AIMING_AT_ENTITY,
	GET_ENTITY_PLAYER_IS_FREE_AIMING_AT,
	IS_SCRIPTED_HUD_COMPONENT_ACTIVE,
	NETWORK_OVERRIDE_CHAT_RESTRICTIONS,
	_DRAW_NOTIFICATION_3,
	unk_0x495BE324,
	_0x5009DFD741329729,
	unk_0xC589CD7D,
	SET_PED_MAX_MOVE_BLEND_RATIO,
	IS_CINEMATIC_CAM_RENDERING,
	IS_PLAYER_WANTED_LEVEL_GREATER,
	IS_PED_STILL,
	GET_PED_STEALTH_MOVEMENT,
	GET_PED_COMBAT_MOVEMENT,
	SET_PED_COMBAT_MOVEMENT,
	IS_PED_USING_ACTION_MODE,
	SET_NO_LOADING_SCREEN,
	SET_PED_PATHS_IN_AREA,
	_BEGIN_TEXT_COMMAND_BUSY_STRING,
	_END_TEXT_COMMAND_BUSY_STRING,
	CLEAR_AREA_OF_PEDS,
	CLEAR_ROOM_FOR_ENTITY,
	SET_ENTITY_NO_COLLISION_ENTITY,
	GET_PED_DECORATIONS_STATE,
	_0xD1B0F412F109EA5D,
	_0x0FB82563989CF4FB,
	_0xF4C8CF9E353AFECA,
	IS_SCRIPT_GLOBAL_SHAKING,
	STOP_SCRIPT_GLOBAL_SHAKING,
	_0x83B8201ED82A9A2D,
	_RENDER_FIRST_PERSON_CAM,
	NETWORK_CREATE_SYNCHRONISED_SCENE,
	NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE,
	NET_TO_OBJ,
	NETWORK_ADD_ENTITY_TO_SYNCHRONISED_SCENE,
	_NETWORK_FORCE_LOCAL_USE_OF_SYNCED_SCENE_CAMERA,
	NETWORK_START_SYNCHRONISED_SCENE,
	SET_ENTITY_VISIBLE_IN_CUTSCENE,
	_NETWORK_CONVERT_SYNCHRONISED_SCENE_TO_SYNCHRONIZED_SCENE,
	CLEAR_PED_SECONDARY_TASK,
	DOES_PARTICLE_FX_LOOPED_EXIST,
	DETACH_ENTITY,
	APPLY_FORCE_TO_ENTITY,
	SET_OBJECT_AS_NO_LONGER_NEEDED,
	SET_PLAYER_VEHICLE_DAMAGE_MODIFIER,
	CAN_REGISTER_MISSION_OBJECTS,
	OBJ_TO_NET,
	unk_0x55461BE6,
	SET_ENTITY_LOCALLY_VISIBLE,
	SET_ENTITY_ANIM_CURRENT_TIME,
	CLONE_PED,
	SET_PED_HELMET,
	_0x4668D80430D6C299,
	GET_ANIM_INITIAL_OFFSET_POSITION,
	GET_ANIM_INITIAL_OFFSET_ROTATION,
	SET_GAME_PAUSES_FOR_STREAMING,
	_TASK_MOVE_NETWORK,
	_0x921CE12C489C4C41,
	_0xB4F47213DF45A64C,
	_0x30ED88D5E0C56A37,
	_0xD01015C7316AE176,
	_0xD5BB4025AE449A4E,
	_0xB0A6CFD2C69C1088,
	GET_GAMEPLAY_CAM_RELATIVE_HEADING,
	DRAW_DEBUG_SPHERE,
	DRAW_DEBUG_LINE,
	GET_GAMEPLAY_CAM_RELATIVE_PITCH,
	IS_PED_SWIMMING,
	IS_PED_DIVING,
	IS_PED_SHOOTING,
	IS_PED_PRONE,
	IS_PED_GOING_INTO_COVER,
	IS_PED_CLIMBING,
	IS_PED_STRAFING,
	IS_PED_JUMPING,
	IS_PED_HANGING_ON_TO_VEHICLE,
	IS_PED_ACTIVE_IN_SCENARIO,
	IS_PED_VAULTING,
	unk_0xA1008E0E,
	unk_0x0170C6E1,
	_0xF2385935BFFD4D92,
	DOES_ANIM_DICT_EXIST,
	IS_PLAYING_PHONE_GESTURE_ANIM,
	IS_PED_RUNNING_MOBILE_PHONE_TASK,
	GET_PHONE_GESTURE_ANIM_CURRENT_TIME,
	GET_PHONE_GESTURE_ANIM_TOTAL_TIME,
	GET_ENTITY_ANIM_TOTAL_TIME,
	HAS_ENTITY_ANIM_FINISHED,
	IS_PED_DOING_DRIVEBY,
	_0x49482F9FCD825AAA,
	IS_GAMEPLAY_CAM_SHAKING,
	SHAKE_GAMEPLAY_CAM,
	IS_CINEMATIC_CAM_SHAKING,
	SHAKE_CINEMATIC_CAM,
	PLAY_SOUND_FROM_ENTITY,
	unk_0xD4F5D07D,
	SET_ENTITY_ANIM_SPEED,
	GET_VEHICLE_LAYOUT_HASH,
	FIND_ANIM_EVENT_PHASE,
	PLAY_FACIAL_ANIM,
	TASK_PLAY_PHONE_GESTURE_ANIMATION,
	_0x7F2C4CDF2E82DF4C,
	SET_PAUSE_MENU_ACTIVE,
	NETWORK_IS_MULTIPLAYER_DISABLED,
	_0x444C4525ECE0A4B9,
	_SET_HUD_COLOUR,
	CLEAR_PED_DECORATIONS,
	_0xDFA80CB25D0A19B3,
	_GET_VEHICLE_MAX_SPEED,
	SET_VEHICLE_BOOST_ACTIVE,
	IS_PED_BEING_STEALTH_KILLED,
	GET_MELEE_TARGET_FOR_PED,
	IS_PED_PERFORMING_STEALTH_KILL,
	_END_SCALEFORM_MOVIE_METHOD_RETURN,
	_0xC6372ECD45D73BCD,
	IS_PED_BEING_ARRESTED,
	TIMESTEP,
	HIDE_LOADING_ON_FADE_THIS_FRAME,
	SET_TEXT_COLOUR,
	SET_TEXT_WRAP,
	SET_TEXT_JUSTIFICATION,
	SET_TEXT_SCALE,
	SET_TEXT_CENTRE,
	SET_TEXT_FONT,
	BEGIN_TEXT_COMMAND_DISPLAY_TEXT,
	END_TEXT_COMMAND_DISPLAY_TEXT,
	DRAW_SPRITE,
	_BEGIN_TEXT_COMMAND_WIDTH,
	_END_TEXT_COMMAND_GET_WIDTH,
	GET_SCREEN_RESOLUTION,
	GET_TEXTURE_RESOLUTION,
	GET_IS_WIDESCREEN,
	ADD_TEXT_COMPONENT_FORMATTED_INTEGER,
	SET_TEXT_OUTLINE,
	SET_TEXT_DROP_SHADOW,
	ADD_TEXT_COMPONENT_FLOAT,
	CLEAR_DRAW_ORIGIN,
	GET_SCREEN_COORD_FROM_WORLD_COORD,
	SET_DRAW_ORIGIN,
	_GET_TEXT_SCALE_HEIGHT,
	SET_TEXT_RIGHT_JUSTIFY,
	GET_PLAYER_CURRENT_STEALTH_NOISE,
	_0x1121BFA1A1A522A8,
	IS_PED_CURRENT_WEAPON_SILENCED,
	_0x9049FE339D5F6F6F,
	_0x4A9923385BDB9DAD,
	IS_VEHICLE_IN_BURNOUT,
	IS_PLAYER_PRESSING_HORN,
	GET_BLIP_SPRITE,
	GET_BLIP_COORDS,
	GET_MAIN_PLAYER_BLIP_ID,
	SET_BLIP_ROTATION,
	SET_BLIP_NAME_TO_PLAYER_NAME,
	GET_BLIP_HUD_COLOUR,
	_SET_PLAYER_BLIP_POSITION_THIS_FRAME,
	LOCK_MINIMAP_POSITION,
	_0x20FE7FDFEEAD38C0,
	UNLOCK_MINIMAP_POSITION,
	_DISABLE_RADAR_THIS_FRAME,
	_0xC4278F70131BAA6D,
	SHOW_HEADING_INDICATOR_ON_BLIP,
	_SET_BLIP_FRIEND,
	_0xDCFB5D4DB8BF367E,
	_SET_BLIP_FRIENDLY,
	SET_BLIP_SECONDARY_COLOUR,
	SET_BLIP_FADE,
	_DISABLE_AUTOMATIC_RESPAWN,
	_0x2EAC52B4019E2782,
	_0xCC3FDDED67BCFC63,
	CLEAR_FACIAL_IDLE_ANIM_OVERRIDE,
	IS_PED_BEING_JACKED,
	NEW_LOAD_SCENE_START,
	NETWORK_IS_LOCAL_PLAYER_INVINCIBLE,
	SET_RADIO_TO_STATION_INDEX,
	SET_RADIO_TO_STATION_NAME,
	SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE,
	POINT_CAM_AT_COORD,
	NETWORK_GET_ENTITY_KILLER_OF_PLAYER,
	_0xD38C4A6D047C019D,
	_0x7DB53B37A2F211A0,
	_0x2E0BF682CC778D49,
	NETWORK_SPENT_CASH_DROP,
	NETWORK_SPENT_ARREST_BAIL,
	SET_CURRENT_PED_VEHICLE_WEAPON,
	SET_SCENARIO_PEDS_SPAWN_IN_SPHERE_AREA,
	HAS_PED_HEAD_BLEND_FINISHED,
	_SET_FOCUS_AREA,
	_NETWORK_RESPAWN_COORDS,
	STOP_ENTITY_FIRE,
	_0x459FD2C8D0AB78BC,
	GET_TIMECYCLE_MODIFIER_INDEX,
	REMOVE_PARTICLE_FX_FROM_ENTITY,
	IS_ENTITY_ON_FIRE,
	SET_PLAYER_CAN_USE_COVER,
	SET_GAMEPLAY_CAM_SHAKE_AMPLITUDE,
	SET_CINEMATIC_CAM_SHAKE_AMPLITUDE,
	STOP_CINEMATIC_CAM_SHAKING,
	_0x12561FCBB62D5B9C,
	IS_CAM_SHAKING,
	SET_CAM_SHAKE_AMPLITUDE,
	STOP_CAM_SHAKING,
	RESET_PED_MOVEMENT_CLIPSET,
	CLEAR_PED_ALTERNATE_MOVEMENT_ANIM,
	SET_PED_IS_DRUNK,
	_0x88EAEC617CD26926,
	SET_PED_HELMET_PROP_INDEX,
	SET_PED_HELMET_TEXTURE_INDEX,
	_0xE861D0B05C7662B8,
	_0xE66C690248F11150,
	SET_AMBIENT_VOICE_NAME,
	APPLY_PED_DAMAGE_PACK,
	unk_0x83BAE814,
	_0x5AAB586FFEC0FD96,
	_0xF79F9DEF0AADE61A,
	unk_0x8CD3E487,
	_0x39D55A620FCB6A3A,
	_IS_PED_PROP_VALID,
	_0x66680A92700F43DF,
	_0x784002A632822099,
	unk_0x52559BB6,
	CLEAR_PLAYER_PARACHUTE_MODEL_OVERRIDE,
	CLEAR_PLAYER_PARACHUTE_VARIATION_OVERRIDE,
	SET_PLAYER_MODEL,
	IS_MODEL_IN_CDIMAGE,
	SET_VEHICLE_FORWARD_SPEED,
	_0x7669F9E39DC17063,
	_0xB6871B0555B02996,
	NETWORK_SPENT_BUY_PASSIVE_MODE,
	CALL_SCALEFORM_MOVIE_METHOD,
	REGISTER_PEDHEADSHOT,
	_0xEBB376779A760AA8,
	_0xF0DAEF2F545BEE25,
	_0x876928DDDFCCC9CD,
	_0xE8A169E666CBC541,
	_0x5D517B27CF6ECD04,
	_0x953563CE563143AF,
	PLAYSTATS_NPC_INVITE,
	_IS_NIGHTVISION_ACTIVE,
	FORCE_ROOM_FOR_ENTITY,
	_SET_SYNCHRONIZED_SCENE_OCCLUSION_PORTAL,
	SET_SYNCHRONIZED_SCENE_LOOPED,
	PLAY_SYNCHRONIZED_CAM_ANIM,
	GET_SYNCHRONIZED_SCENE_RATE,
	_IS_LOADING_PROMPT_BEING_DISPLAYED,
	SET_SYNCHRONIZED_SCENE_PHASE,
	_0xB4BBFD9CD8B3922B,
	_0x044DBAD7A7FA2BE5,
	SET_SYNCHRONIZED_SCENE_RATE,
	_0x7F2F4F13AC5257EF,
	GET_SOUND_ID,
	PLAY_SOUND_FROM_COORD,
	CREATE_OBJECT_NO_OFFSET,
	SET_ENTITY_ROTATION,
	_0xBA751764F0821256,
	SET_WARNING_MESSAGE_WITH_HEADER,
	IS_CONTROL_JUST_RELEASED,
	_0x6DEE77AFF8C21BD1,
	IS_BLIP_SHORT_RANGE,
	_REMOVE_SPEED_ZONE,
	_ADD_SPEED_ZONE_FOR_COORD,
	_GET_CURRENT_FRONTEND_MENU,
	SET_PLAYER_WANTED_LEVEL_NO_DROP,
	NETWORK_REFUND_CASH,
	IS_PED_ON_FOOT,
	CREATE_CHECKPOINT,
	_ADD_DECAL_TO_MARKER,
	DELETE_CHECKPOINT,
	_GET_TUNABLES_CONTENT_MODIFIER_ID,
	NETWORK_ACCESS_TUNABLE_FLOAT,
	NETWORK_DOES_TUNABLE_EXIST,
	_DRAW_SCALEFORM_MOVIE_3D_NON_ADDITIVE,
	_0xB7ED70C49521A61D,
	IS_MESSAGE_BEING_DISPLAYED,
	ADD_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS,
	BEGIN_TEXT_COMMAND_PRINT,
	END_TEXT_COMMAND_PRINT,
	_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2,
	unk_0x07CE2EA4,
	_0x4A0C7C9BB10ABB36,
	_GET_TEXT_SUBSTRING_SLICE,
	_0x40F7E66472DF3E5C,
	NETWORK_GET_NUM_PRESENCE_INVITES,
	NETWORK_GET_PRESENCE_INVITE_SESSION_ID,
	_0x742B58F723233ED9,
	NETWORK_REMOVE_PRESENCE_INVITE,
	_0x2D5DC831176D0114,
	_0x5E0165278F6339EE,
	_0xEBFA8D50ADDC54C4,
	_0x162C23CA83ED0A62,
	_SET_NOTIFICATION_MESSAGE_CLAN_TAG,
	NETWORK_BAIL_TRANSITION,
	CREATE_CAMERA,
	SET_CAM_FAR_CLIP,
	GET_IS_LOADING_SCREEN_ACTIVE,
	unk_0xECE8365D,
	SET_ENTITY_COORDS_NO_OFFSET,
	SET_INPUT_EXCLUSIVE,
	_0xD8E694757BCEA8E9,
	SET_MISSION_NAME,
	_SET_MISSION_NAME_2,
	_0x817B86108EB94E51,
	_0x8D74E26F54B4E5C3,
	STAT_SET_GXT_LABEL,
	NETWORK_SET_RICH_PRESENCE,
	_NETWORK_SET_RICH_PRESENCE_2,
	GET_BLIP_INFO_ID_TYPE,
	GET_BLIP_INFO_ID_ENTITY_INDEX,
	PULSE_BLIP,
	IS_BLIP_FLASHING,
	SET_BLIP_FLASH_INTERVAL,
	IS_PLAYER_IN_CUTSCENE,
	SHOW_NUMBER_ON_BLIP,
	HIDE_NUMBER_ON_BLIP,
	unk_0x9320E642,
	SET_BLIP_CATEGORY,
	GET_BLIP_FROM_ENTITY,
	_0x6B1DE27EE78E6A19,
	_GET_VEHICLE_OWNER,
	GET_MAX_RANGE_OF_CURRENT_PED_WEAPON,
	unk_0x27512BA0,
	FADE_OUT_LOCAL_PLAYER,
	IS_ENTITY_ATTACHED_TO_ANY_VEHICLE,
	IS_PED_FATALLY_INJURED,
	SHUTDOWN_LOADING_SCREEN,
	GET_CONTROL_VALUE,
	_0x75BA1CB3B7D40CAF,
	IS_PED_TRACKED,
	_0x511F1A683387C7E2,
	_0x0C1F7D49C39D2289,
	_0x0AFCE529F69B21FF,
	_0xC7BE335216B5EC7C,
	_0xA72835064DD63E4C,
	SET_PED_DENSITY_MULTIPLIER_THIS_FRAME,
	SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME,
	GET_VEHICLE_DOORS_LOCKED_FOR_PLAYER,
	_0x3DBF2DF0AEB7D289,
	_0x8806CEBFABD3CE05,
	NETWORK_ACCEPT_PRESENCE_INVITE,
	STRING_TO_INT,
	NETWORK_CAN_ACCESS_MULTIPLAYER,
	_0xFF8F3A92B75ED67A,
	_0x4A7D6E727F941747,
	_0x699E4A5C8C893A18,
	_0x19853B5B17D77BCA,
	_0x8CC469AB4D349B7C,
	GET_LAST_DRIVEN_VEHICLE,
	unk_0x575504DE,
	NETWORK_PLAYER_GET_USERID,
	_NETWORK_GET_DESROYER_OF_ENTITY,
	NETWORK_EARN_FROM_PICKUP,
	GET_WEAPON_DAMAGE_TYPE,
	GET_ENTITY_HEIGHT_ABOVE_GROUND,
	NETWORK_SPENT_PAY_VEHICLE_INSURANCE_PREMIUM,
	GET_ENTITY_VELOCITY,
	WAS_PED_KILLED_BY_STEALTH,
	WAS_PED_KILLED_BY_TAKEDOWN,
	STAT_SET_USER_ID,
	NETWORK_IS_ACTIVITY_SPECTATOR_FROM_HANDLE,
	NETWORK_APPLY_TRANSITION_PARAMETER,
	NETWORK_MARK_TRANSITION_GAMER_AS_FULLY_JOINED,
	_0x4811BBAC21C5FCD5,
	_0x5539C3EBF104A53A,
	_0x702BC4D605522539,
	DOES_VEHICLE_EXIST_WITH_DECORATOR,
	_0x0D77A82DC2D0DA59,
	NETWORK_SET_GAMER_INVITED_TO_TRANSITION,
	NETWORK_REMOVE_TRANSITION_INVITE,
	unk_0x8AFE3D90,
	NETWORK_SEND_TRANSITION_GAMER_INSTRUCTION,
	NETWORK_GET_GAMERTAG_FROM_HANDLE,
	_NETWORK_PLAYER_SOMETHING,
	NETWORK_RECEIVE_PLAYER_JOBSHARE_CASH,
	NETWORK_EARN_FROM_BOUNTY,
	SET_ENTITY_IS_TARGET_PRIORITY,
	CREATE_MODEL_HIDE_EXCLUDING_SCRIPT_OBJECTS,
	NETWORK_SPENT_PLAYER_HEALTHCARE,
	_0x10BD227A753B0D84,
	NETWORK_REQUEST_CLOUD_TUNABLES,
	NETWORK_BAIL,
	_0x16A304E6CB2BFAB9,
	_0x7AE0589093A2E088,
	LEADERBOARDS_READ_CLEAR_ALL,
	CLEAR_BRIEF,
	UNCUFF_PED,
	_0x5B8ED3DB018927B1,
	_NETWORK_EARN_FROM_GANG_PICKUP,
	_NETWORK_EARN_FROM_ARMOUR_TRUCK,
	NETWORK_EARN_FROM_HOLDUPS,
	GET_PED_AMMO_BY_TYPE,
	GET_ENTITY_MAX_HEALTH,
	GET_ENTITY_SPEED_VECTOR,
	SET_VEHICLE_TYRE_BURST,
	_GET_PICKUP_HASH,
	NETWORK_GET_ACTIVITY_PLAYER_NUM,
	unk_0x5AC9F04D,
	BAD_SPORT_PLAYER_LEFT_DETECTED,
	NETWORK_IS_TRANSITION_HOST,
	STAT_GET_NUMBER_OF_SECONDS,
	NETWORK_IS_IN_PARTY,
	NETWORK_IS_PARTY_MEMBER,
	_0xEBEFC2E77084F599,
	GET_EVENT_EXISTS,
	IS_VEHICLE_WINDOW_INTACT,
	REMOVE_VEHICLE_WINDOW,
	SET_VEHICLE_MODEL_IS_SUPPRESSED,
	REMOVE_MULTIPLAYER_HUD_CASH,
	unk_0xE67446E9,
	REMOVE_SCENARIO_BLOCKING_AREAS,
	TERMINATE_THIS_THREAD,
	_0x64F62AFB081E260D,
	_0x675721C9F644D161,
	_0xB695E2CD0A2DA9EE,
	SET_PED_DIES_IN_WATER,
	SET_PED_MAX_TIME_UNDERWATER,
	SET_PED_DIES_IN_SINKING_VEHICLE,
	unk_0xB731DF54,
	STAT_SET_STRING,
	SET_STATIC_EMITTER_ENABLED,
	NETWORK_SESSION_WAS_INVITED,
	NETWORK_SESSION_GET_INVITER,
	NETWORK_HAS_PLAYER_STARTED_TRANSITION,
	NETWORK_ARE_TRANSITION_DETAILS_VALID,
	NETWORK_JOIN_TRANSITION,
	ENABLE_STUNT_JUMP_SET,
	DISABLE_STUNT_JUMP_SET,
	RESERVE_NETWORK_MISSION_OBJECTS,
	SET_VEHICLE_POPULATION_BUDGET,
	NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES_,//added the _ because I'm lazy and it collides with the function in mods.h
	NETWORK_REGISTER_HOST_BROADCAST_VARIABLES,
	SET_THIS_SCRIPT_CAN_BE_PAUSED,
	SET_CREATE_RANDOM_COPS,
	SET_DITCH_POLICE_MODELS,
	ENABLE_DISPATCH_SERVICE,
	_0x6B0E6172C9A4D902,
	SET_AI_WEAPON_DAMAGE_MODIFIER,
	SET_AI_MELEE_WEAPON_DAMAGE_MODIFIER,
	USE_PLAYER_COLOUR_INSTEAD_OF_TEAM_COLOUR,
	NETWORK_CAN_BAIL,
	HINT_SCRIPT_AUDIO_BANK,
	NETWORK_HANDLE_FROM_USER_ID,
	STAT_GET_USER_ID,
	_0x5D10B3795F3FC886,
	_0x487912FD248EFDDF,
	ADD_RELATIONSHIP_GROUP,
	NETWORK_GET_SCRIPT_STATUS,
	unk_0xE642F2FD,
	unk_0x95FFACF8,
	unk_0xB97A966B,
	unk_0x104DDE8D,
	unk_0x063DC4A5,
	LEADERBOARDS_CLEAR_CACHE_DATA,
	unk_0x19EAE282,
	SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED,
};




#ifdef sdjvhskjfvhxfjkn






#include <iostream>
#include <string>
#include<stdlib.h>

unsigned int values[] = { 1588610,1315372,1587565,0x1CC4A34,0xA8B814,0xA8B908,0x1EC6980,0x1626844,0xA8B5FC,0xA8BBBC,0xA8B978,0x9F8FF0,0x1888BD0,0x1894210,0x51BA0,0x1888BE0,0x150BAA4,0x1EC672C,0x1CC57B8 };

int main()
{
	srand(time(NULL));
	for (int i = 0; i < 10000; i++)
		rand();
	for (int i = 0; i < sizeof(values) / sizeof(unsigned int); i++) {
		unsigned int value = values[i];
		unsigned int key = rand();
		unsigned int secret = value ^ key;
		char name[10];
		snprintf(name, sizeof(name), "privk%i", i);
		printf("name: %s , real: 0x%X , server: getNextData(addrstruct().%s); , conversion: (addrstruct().%s^dataDecryptor()^0x%X)/*value: 0x%X*/ , val on server: 0x%X\n", name, secret ^ key, name, name, secret, value, key);
	}
}




#endif