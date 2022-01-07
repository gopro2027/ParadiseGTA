//unsigned int startOfEnc = 0xFFEEDDCC;
/*
int main();
__attribute__ ((naked)) int obfStart() {//size = 6*0x4
	//return (int)main;
	//return 0xFFEEDDCC+(int)main;
	__asm("lis %r3, 0xFFEE");//3C 60 FF EE 
	__asm("ori %r3, %r3, 0xDDCC");//60 63 DD CC 
	__asm("blr");//4E 80 00 20  
	//total: 3C 60 FF EE 60 63 DD CC 4E 80 00 20 
	//(byte)0x3C(byte)0x60(byte)0xFF(byte)0xEE(byte)0x60(byte)0x63(byte)0xDD(byte)0xCC(byte)0x4E(byte)0x80(byte)0x00(byte)0x20
	return (int)main;
}*/
#pragma optimize ("O2",on) 

//removes only stuff that prevents the hen version from working... aka encryption and auto update
#define HEN_MODE 0 

#define CRASH_DEBUGGER 1 
  
#define PAUSE_ON_LOAD 0  

#define DONT_UPDATE CRASH_DEBUGGER == 0 || HEN_MODE == 1
 
#define DISPLAY_KEY_READ_ERROR 0 
  
#define netlogfunc 1

//uncomment this for start and stop
//#define sJKFghjsadfjkgh_____________32423324sxvsdcc312 just to make sure I don't accidentally have it you know, double step

#define creationSpawner_  //if I enable this, I need to make modifications to the 'Structures' submenu  (currently enabled, add underscore to disable)

#define __ALWAYS_INLINE static inline __attribute__( ( always_inline ) )
#define __TDATA __attribute__((section(".tdata")))//crashes ugh
#define __NO_INLINE __attribute__((noinline))
#define __NAKED __attribute__ ((naked)) __attribute__((noinline))

#include <ppu_asm_intrinsics.h> 
#include <cellstatus.h>
#include <sys/prx.h>
#include <sys/ppu_thread.h>
#include <string.h> 
#include <sys/memory.h>
#include <sys/timer.h>
#include <sys/process.h>
#include <ppu_intrinsics.h>
#include <stdarg.h>
#include <cell/cell_fs.h>
#include <stdio.h>
#include <sysutil\sysutil_msgdialog.h>
#include <sysutil\sysutil_oskdialog.h>
#include <sysutil\sysutil_oskdialog_ext.h>

#include <cell/pad.h>
#include <cell/padfilter.h> 
#include "padutil.h"

//#include <stdlib.h>
#include <cstdlib>
#include <math.h>
//#include <dirent.h>
#include "types.h" //for the toc
#include "base64.h"
int Read_Global_Address(int a_uiGlobalID);
#include "GTAStructs.h"
#include "security.h"
namespace RTMTool {
	char *getMessage(int messageindex/*, char *store, int storeLength*/);
	bool chatEnabled = true;
	bool usePSN = false;
}; 
__ALWAYS_INLINE int findIndexOf(char *in, char *find,int sizeofin,unsigned int sizeoffind);
__ALWAYS_INLINE void decrypt(unsigned char *data, unsigned int startIndex, unsigned int endIndex, bool quick = false);
__ALWAYS_INLINE void reverseMemoryArea(unsigned char *data, unsigned int startIndex, unsigned int endIndex, bool quick = false);
__ALWAYS_INLINE void addTheBytesArea(unsigned char *data, unsigned int startIndex, unsigned int endIndex, bool quick = false);
#define COLOR_BACKGROUND 0, 0, 0
//#define COLOR_FOREGROUND 0, 168, 255  //46, 204, 113
Vector3 COLOR_FOREGROUND = {0, 168, 255};
int backgroundOpacity = 120;//120;//120;//65  40 for low
int optionsRed = 255;
int optionsGreen = 255;
int optionsBlue = 255;

float globalAddX = 0;
float globalAddY = 0;

bool assureHostOfFreemode(bool player);
void kickPlayerNonHost(int player);
//#define paradiseRpfDirectory "/dev_hdd0/tmp/gopro_2027/script.rpf"//"/dev_hdd0/game/BLES01807/USRDIR/Paradise.rpf"
__ALWAYS_INLINE int write_process_sc(void* destination, const void* source, size_t size);
unsigned int modelHashToAddress(unsigned int hash);
bool doesFileExist(char *file);

//#include "yxml.h"
void setPlayerStatInt(int player, int statIndex, int statValue, bool type);
/*__ALWAYS_INLINE */void PatchInJumpAddr(uint64_t Address, int Destination, bool Linked);

uint32_t jenkins(char *key, size_t key_len);





int snprintf(char *buffer, size_t len, const char *fmt, ...)
{
	va_list args;
	int i;

	va_start(args, fmt);
	i = vsnprintf(buffer, len, fmt, args);
	va_end(args);
	return i;
}

#define dropKickAnti() \
{\
	int Ptr = *(int*)(0x1E70384);\
	if (Ptr != 0) {\
		*(int*)(Ptr + 0x1DBC) = 0;\
	}\
}

#define dropKickAnti2() \
{\
	unsigned int Global_2387877_address = (*(int*)0x1E70394+0x1BE94);\
	if (*(int*)Global_2387877_address > 4) {\
		*(int*)Global_2387877_address = 4;\
	}\
}

#define antiFakeLeaveV2() \
{\
	unsigned int Global_1588610_address = (*(int*)0x1E70388+0xF608);\
	unsigned int Global_1572928_address = (*(int*)0x1E70388+0x100);\
	if (*(int*)Global_1588610_address == 0)\
		*(int*)Global_1588610_address = 0x12;\
	if (*(int*)Global_1572928_address == 0)\
		*(int*)Global_1572928_address = 2;\
}



//(opd_s*)snprintf;
opd_s snprintf$_stub = { /*0x14F9E1C*//*0x14FE110*/0x14FDCEC, TOC };
//int(*snprintf)(char * s, size_t n, const char * format, ...) = (int(*)(char*, size_t, const char*, ...))&(*snprintf$_stub);
int(*snprintf$)(char * s, size_t n, const char * format, ...) = (int(*)(char*, size_t, const char*, ...))&(snprintf$_stub);
namespace socketConnectionStuff {
unsigned int keyhash;
}
bool doDownloadRPF = false;
bool uninstallRPF = false;
bool dontShowRPFDownloadErrorMessage = false;
int downloadRPFErrorCode = 0;//0 is none, 1 is place not available
bool portalImageOverritten = false;
bool titleImageOverritten = false;
bool scrollerImageOverritten = false;
char key[36+1];//36 but need padding
bool menuStarted = false;
char *bufferReturn;// [10000] ; ;// = _malloc(10000)
#define SIZEOF_BUFFERRETURN 10000

//bool injectDDS(char *fileName, unsigned int pixelSize, char *textureData, unsigned int addAmount);
void dialogReturn(int button, void *userdata){}
#define dialog(text) cellMsgDialogOpen(1,text,dialogReturn,(void*) 0x0000aaab, NULL);
char *requestURL(char *url, char *buffer = bufferReturn, int sizeofbuffer = 10000, bool add8BytesForFileBug = false, bool startAndCloseConnection = true);
namespace socketConnectionStuff {
	bool requestURLAtHeader(char *requestData, char *saveTo, unsigned int size, unsigned int skipAtStart,bool makeNewConnection = true);
};
bool requestURLAtHeader(char *requestData, char *saveTo, unsigned int size, unsigned int skipAtStart,bool makeNewConnection = true) {
	return socketConnectionStuff::requestURLAtHeader(requestData,saveTo,size,skipAtStart,makeNewConnection);
}
 
char *getFormatForMemoryArea(void *address, unsigned int size);
void appendToFile(char *file, char buf[], int size);
void removeFileData(char *file);
void resetPrintfFile() {
	//sys_ppu_thread_exit(0);
	removeFileData("/dev_hdd0/debug_log.txt");
}
int printfFile(const char *fmt, ...)
{
	char strBuf[128];
	va_list args;
	int i, written = 0;

	va_start(args, fmt);
	i = vsnprintf(strBuf, 128, fmt, args);
	va_end(args);
	appendToFile("/dev_hdd0/debug_log.txt",strBuf,strlen(strBuf));

	return written;
}
bool readFile(char *file, char buf[], int size, unsigned int offset);
bool injectDDSFile(char *fileName, unsigned int pixelSize, char *textureData, unsigned int addAmount) {
	
	const unsigned int sizeof32 = 1152;//bit depth 32
	const unsigned int sizeof64 = 4224;//bit depth 32
	const unsigned int sizeof128 = 0;
	const unsigned int sizeof256 = 65664;
	const unsigned int sizeof512 = 262272;
	const unsigned int sizeof1024 = 0;
	unsigned int fileSize = 0;
	switch(pixelSize) {
	case 32: fileSize = sizeof32;break;
	case 64: fileSize = sizeof64;break;
	case 128: fileSize = sizeof128;break;
	case 256: fileSize = sizeof256;break;
	case 512: fileSize = sizeof512;break;
	case 1024: fileSize = sizeof1024;break;
	}
	if (fileSize == 0)//cannot download
		return false;
	readFile(fileName,textureData,fileSize-addAmount,addAmount);//addAmount would be starting at header or not
	return true;
}

//only called once so it doesn't make a difference in size being inline
/*__ALWAYS_INLINE */bool injectDDS(char *fileName, unsigned int pixelSize, char *textureData, unsigned int addAmount) {
	
	const unsigned int sizeof32 = 1152;//bit depth 32
	const unsigned int sizeof64 = 4224;//bit depth 32
	const unsigned int sizeof128 = 0;
	const unsigned int sizeof256 = 65664;
	const unsigned int sizeof512 = 262272;
	const unsigned int sizeof1024 = 0;
	unsigned int fileSize = 0;
	switch(pixelSize) {
	case 32: fileSize = sizeof32;break;
	case 64: fileSize = sizeof64;break;
	case 128: fileSize = sizeof128;break;
	case 256: fileSize = sizeof256;break;
	case 512: fileSize = sizeof512;break;
	case 1024: fileSize = sizeof1024;break;
	}
	//printf("Filesize: %i\n", fileSize);
	if (fileSize == 0)//cannot download
		return false;
	//char data[200];
	memset(global_temporary_buf,sizeof(global_temporary_buf),0);//has to be overritten for some reason
	snprintf$(global_temporary_buf,sizeof(global_temporary_buf),"res/downloadasset2.php?key=%s&filename=%s",key,fileName);//the data from this always starts with a 'F'
	//printf("Request: %s\n",data);
	//randomizeAddresses();
	//printf("Requesting url... %s\n",data);
	return requestURLAtHeader(global_temporary_buf,textureData,fileSize-addAmount,0);
#ifdef isjuhgajsidfhjgiaksjfghjklasr
	//stop after dis
	void *alloc;
	char *dat;
	if (fileSize <= 10000) {
		dat = requestURL(data,bufferReturn,10000,true);
	} else {
		alloc = textureData;//(void*)0x10070000;//malloc(fileSize+1000);//add 1000 for the network header crap    -    0x10070000 gives enough for 200kb
		dat = requestURL(data,(char*)alloc,fileSize+1000,true,true);
		return;
	}

	if (dat[0] != 'F') {
		//printf("Data is not F! %s\n",dat);
		/*if (fileSize <= 10000) {
			dat = requestURL(data,bufferReturn,10000,true);
		} else {
			alloc = (void*)0x10070000;//malloc(fileSize+1000);//add 1000 for the network header crap    -    0x10070000 gives enough for 200kb
			dat = requestURL(data,(char*)alloc,fileSize+1000,true);
		}*/
		return false;
	}
	dat++;//get past the 'F'

	/*dat+=8;
	//randomizeAddresses();
	while (dat[0] == 0)
		dat++;
	dat++;*/
	
	//cuz we are at the begin now



	//printf("Hash: 0x%X\n",socketConnectionStuff::keyhash);
	//for (int i = 0; i < fileSize; i++)
		//dat[i] = (char)dat[i]^(char)(socketConnectionStuff::keyhash&0xFF);/*^(char)(socketConnectionStuff::keyhash & 0xFF);*/
	//randomizeAddresses();
	//printfFile("\n%s contents:\n",fileName);
	//printf("\n%s contents:\n",fileName);
	for (int i = 0; i < fileSize-addAmount; i++) {
		textureData[i] = dat[i/*+addAmount*/]/*^socketConnectionStuff::keyhash*/;
		//printfFile("0x%X ",(unsigned int)dat[i]);
		//printf("0x%X ",(unsigned int)dat[i]);
		//dat[i] = 0;
	}
	for (int i = 0; i < fileSize; i++)
		dat[i] = 0;
	return true;
#endif
}
int entityToIndex(unsigned int entityAddress);
int entityToIndex(CObj *entityAddress);
void givePlayerRP(int player, int amount, int unk1 = -1, int unk2 = 1);
//static char *introtextfail2 = "Login failed!\nPlease go to the user panel at http://paradisesprx.net/user and check the status of your product key!";
void givePlayerMoney(int player, int amount);
//*(char*)0x1F1D6EC = 1;  pauses game. 0 to unpause
//int printf(const char *fmt, ...) {return 0;}
#define DEVELOPER1  ///set to DEVELOPER to enable my stuff        set DEVELOPER1 on public release           auto updates don't work unless it is set to DEVELOPER1
#define DOAUTH 1 //NEVER change
//#define CEX 1 //gonna keep this on true not since it doesn't actually make a difference anymore. you need cobra mode with cex or not
#define RIGHT 0
#define DEVELOPER_CHAT 0
//#define IDONTWANTTOSAVEMEMORY //use to show dev menu     set IDONTWANTTOSAVEMEMORY1 on public release

float addwidthspecialrender = 0;
float expandspecialrender = 0;
bool showOpenInstructions = true;
#define hasMenuBeenOpened() (!showOpenInstructions)
#include <netex/libnetctl.h>
/*
unsigned int getMacAddress() {
	CellNetCtlInfo netInfo1;
	opd_s f_t = {0x180540C,TOC};
	int(*f)(unsigned int a, unsigned int b) = (int(*)(unsigned int, unsigned int))&f_t;
	f(CELL_NET_CTL_INFO_ETHER_ADDR, (unsigned int)&netInfo1);//0x180540C is cellNetCtlGetInfo
	//should probably reverse the function above but eh

	const char *Mac = (const char *)netInfo1.ether_addr.data;
	static char MacAddress[30];
	printf("Mac address: %02X:%02X:%02X:%02X:%02X:%02X, 0x%X\n", Mac[0] & 0xFF, Mac[1] & 0xFF, Mac[2] & 0xFF, Mac[3] & 0xFF, Mac[4] & 0xFF, Mac[5] & 0xFF,*(volatile unsigned int*)(netInfo1.ether_addr.data));

	//return MacAddress;
	//unsigned int addressOfMac = (unsigned int)Mac;
	//unsigned int mac = *(volatile unsigned int*)mac;
	return *(volatile unsigned int*)(netInfo1.ether_addr.data);
}*/
unsigned int macAddress;
//my mac address: 0:1D:0D:45:E3:06, 0x1D0D45E3, 487409123
//#include "jump.h"


char introtext[] = {(char)103, (char)32, (char)103, (char)32, (char)103, (char)32, (char)103, (char)32, (char)103, (char)32, (char)103, (char)32, (char)103, (char)32, (char)-88, (char)-111, (char)-23, (char)87, (char)34, (char)108, (char)36, (char)111, (char)42, (char)101, (char)103, (char)116, (char)40, (char)-17, (char)-42, (char)-82, (char)77, (char)32, (char)103, (char)32, (char)103, (char)32, (char)103, (char)32, (char)103, (char)32, (char)103, (char)32, (char)103, (char)32, (char)103, (char)32, (char)-88, (char)-111, (char)-24, (char)80, (char)38, (char)114, (char)38, (char)100, (char)46, (char)115, (char)34, (char)33, (char)-88, (char)-111, (char)-24, (char)0};



char introtextfail[] = {(char)30, (char)111, (char)50, (char)114, (char)103, (char)107, (char)34, (char)121, (char)103, (char)105, (char)52, (char)32, (char)46, (char)110, (char)49, (char)97, (char)43, (char)105, (char)35, (char)46, (char)103, (char)82, (char)34, (char)116, (char)62, (char)112, (char)34, (char)32, (char)46, (char)116, (char)103, (char)105, (char)41, (char)32, (char)104, (char)100, (char)34, (char)118, (char)24, (char)104, (char)35, (char)100, (char)119, (char)47, (char)51, (char)109, (char)55, (char)47, (char)32, (char)111, (char)55, (char)114, (char)40, (char)95, (char)117, (char)48, (char)117, (char)55, (char)104, (char)75, (char)34, (char)121, (char)105, (char)116, (char)63, (char)116, (char)103, (char)40, (char)4, (char)65, (char)20, (char)69, (char)103, (char)83, (char)2, (char)78, (char)20, (char)73, (char)19, (char)73, (char)17, (char)69, (char)110, (char)0};//Your key is invalid. Retype it in /dev_hdd0/tmp/gopro_2027/Key.txt (CASE SENSITIVE)
void encryptDecrypt(char input[], char *output, int size = -1);
namespace socketConnectionStuff {

struct Addresses {
	unsigned int nativeTable;//1 - 0x1E6FF38
	unsigned int cashDropFix;//2 - 0x003FA510
	unsigned int scriptBypass;//3 - 0x01306254
	unsigned int teleportPlayerCallback;//4 - 0x1C6BF80
	unsigned int objectBypass;//5 - 0x3F8B84
	unsigned int modelToHash;//6 - 0x9D9830
	unsigned int entityToIndex;//7 - 0x474054
	unsigned int getCNetGamePlayer;//8 - 0x47E00C
	unsigned int getEntityAttachedTo;//9 - 0x3A9EFC
	unsigned int hookP1;//10 - 0x3D600000
	unsigned int hookP2;//11 - 0x396B0000
	unsigned int hookP3;//12 - 0x7D6903A6
	unsigned int hookP4;//13 - 0x4E800420
	unsigned int textData;//14 - 0x27A244D8
	unsigned int hookAddress;//15 - 0x3E3A20
	unsigned int NETWORK_CREATE_SYNCHRONISED_SCENE;//16 - 0xB06FE3FE
	unsigned int quadAddress;//17 - 0xDD2BFC77
	unsigned int entityFromIndex;//18 - 0xA552E0
	unsigned int devmode;//19 - 0x37896345 true 0x19974656 false
	unsigned int allClientStatsAddress;//20 - 0x12D141C real, 0x13AE3B0 for the special that is new
	unsigned int FCWfuncAddress;//21 - 0x12C2ECC
	unsigned int FCWarg0;//22 - 1
	unsigned int FCWarg1;//23 - 0xE
	unsigned int FCWarg2;//24 - 0x2148E84
	unsigned int FCWarg3;//25 - 0xD04
	unsigned int setPlayerTeamAddr;//26 - 0x08421B34 where &0xFFFFFF is the addr and 0xFF000000 >>(8*3) is the second arg
	unsigned int getPlayerIdAddr;//27 - 0x4241D4
	unsigned int setSCTVSlotsAddr;//28 - 0x043E4298 where &0xFFFFFF is the addr and 0xFF000000 >>(8*3) is the second arg
	unsigned int setPlayerTeamAddr2;//29 - 0x159A284
	unsigned int antiFreezeAddr1;//30 - 0x1C707E0
	unsigned int antiFreezeAddr2;//31 - 0x133C430
	unsigned int renderResulutionParams;//32 - 0x1DE12C0
	unsigned int stringDecryptHash;//33 - 0x68be968a
	unsigned int SCEventTicketFunc;//34 - 0xD38374
	unsigned int SCEventAnotherFunc;//35 - 0xDDF8506E
	unsigned int PedProtVal1;//36 - 0x1C72E70
	unsigned int PedProtVal2;//37 - 0x13CA768
	int temporaryTimeVal;//38, only used once but kept here for good measure
	unsigned int privk0;//39
	unsigned int privk1;//40
	unsigned int privk2;//41
	unsigned int privk3;//42
	unsigned int privk4;//43
	unsigned int privk5;//44
	unsigned int privk6;//45
	unsigned int privk7;//46
	unsigned int privk8;//47
	unsigned int privk9;//48
	unsigned int privk10;//49
	unsigned int privk11;//50
	unsigned int privk12;//51
	unsigned int privk13;//52
	unsigned int privk14;//53
	unsigned int privk15;//54
	unsigned int privk16;//55
	unsigned int privk17;//56
	unsigned int privk18;//57
	unsigned int privk19;//58
	unsigned int suggest;//59 - 0x9FC1F4, server: 0x5A5AF18E, local: suggest ^ 0x5ac5307a
	unsigned int privk_132AE30;//60
};
Addresses *addressespointer;
//fancy max: FC0FE6504327

unsigned int nSeed = 0;
unsigned int globaldecryptkey;
unsigned int addressesDataDecryptor = 0;
#define getMacAddress() (macAddress)
#define retreiveMacAddress() /*{macAddress = 0;}*/{CellNetCtlInfo netInfo1; ((int(*)(unsigned int, unsigned int))&(opd_s){0x180540C,TOC})/*cellNetCtlGetInfo*/(CELL_NET_CTL_INFO_ETHER_ADDR/*2*/, (unsigned int)&netInfo1);macAddress = *(volatile unsigned int*)(netInfo1.ether_addr.data+1);             /* const char *Mac = (const char *)netInfo1.ether_addr.data;printf("Mac address: %02X:%02X:%02X:%02X:%02X:%02X, 0x%X\n", Mac[0] & 0xFF, Mac[1] & 0xFF, Mac[2] & 0xFF, Mac[3] & 0xFF, Mac[4] & 0xFF, Mac[5] & 0xFF,*(volatile unsigned int*)(netInfo1.ether_addr.data+1));*/}//adds about 8kb too fyi
#define randomize() {socketConnectionStuff::nSeed = (8253729 * socketConnectionStuff::nSeed + 2396403) ^ getMacAddress();}
#define rand1() (socketConnectionStuff::nSeed)
#define dataDecryptor() (socketConnectionStuff::addressesDataDecryptor^socketConnectionStuff::keyhash   /*for the encryption key used on all addresses*/^dataEncryptionKey()^getMacAddress())
#define gdk()  (unsigned int)(socketConnectionStuff::globaldecryptkey ^ (unsigned int)socketConnectionStuff::addressespointer)
#define addr()  (unsigned int)((unsigned int)socketConnectionStuff::addressespointer ^ gdk())
#define addrstruct() (*(socketConnectionStuff::Addresses*)(addr()))
#define addrstructptr() ((socketConnectionStuff::Addresses*)(addr()))
__ALWAYS_INLINE void xorAddressesStructure(unsigned int xorKey) { for (int i = 0; i < sizeof(socketConnectionStuff::Addresses)/4; i++) {   *(volatile unsigned int*)( (unsigned int)addrstructptr()+(i*4) ) ^= xorKey;   }  }//take off the __ALWAYS_INLINE to add 64kb more memory
#define dataEncryptionKey() ((unsigned int)(rand1()/*getMacAddress()*/))//rand1() causes it to break
//every call to randomizeAddresses() is 2240 bytes
#define randomizeAddresses() {}//does nothing now
#define randomizeAddresses2() { /*printf("Key: 0x%X nativeTable: 0x%X should be 0x1E6FF38\n",dataEncryptionKey(),addrstruct().nativeTable^dataDecryptor());*/ /*start of decrypt data*/   socketConnectionStuff::xorAddressesStructure(dataEncryptionKey());     /*end of decrypt data*/ /*printf("This should be normal now: 0x%X^otherpartofkey = 0x1E6FF38\n",addrstruct().nativeTable);*/  randomize();unsigned int adre = addr(); unsigned int decryptkey = gdk()^rand1()^addr();*(volatile unsigned int*)&socketConnectionStuff::addressespointer = decryptkey^adre;socketConnectionStuff::globaldecryptkey = decryptkey;decryptkey=0;adre=0;socketConnectionStuff::globaldecryptkey ^= (unsigned int)socketConnectionStuff::addressespointer;      /*start of encrypt data*/   socketConnectionStuff::xorAddressesStructure(dataEncryptionKey());     /*end of encrypt data*/       /*printf("Pointer To Data Structure: 0x%X\n",*(volatile unsigned int*)&socketConnectionStuff::addressespointer);*/}
//#define isDevMode() ((bool)((addrstruct().devmode^dataDecryptor()) == 1))
#define isDevMode() ( (addrstruct().devmode^dataDecryptor()) > 0x27634725 )
//(addrstruct().^dataDecryptor())

};
/*
void retreiveMacAddress() {
	CellNetCtlInfo netInfo1;
	//((int(*)(unsigned int, unsigned int))&(opd_s){0x180540C,TOC})(CELL_NET_CTL_INFO_ETHER_ADDR, (unsigned int)&netInfo1);
	call<int>(0x180540C)(CELL_NET_CTL_INFO_ETHER_ADDR,(unsigned int)&netInfo1);
	macAddress = *(volatile unsigned int*)(netInfo1.ether_addr.data+1);
}*/
#define _C2			1	/* 0 if not 2's complement */
   #define INT_MAX		0x7fffffff
   #define INT_MIN		(-INT_MAX - _C2)
   #define UINT_MAX	(INT_MAX * 2U + 1)
//Menu base created by 2much4u and menu by gopro_2027
#pragma region includes
void *Memcpy(void *destination, const void *source, unsigned int size) {
	for (int i = 0; i < size; i++)
		*(char*)((unsigned int)destination+i) = (char)((unsigned int)source+i);
	return destination;
}
/*
void toggleTeleportProtection(bool enable) {
	
	write_process((char*)(0x12D86B4-0xe20),nop_bytes,4);// - network request synced scene
	write_process((char*)(0x12D86D0-0xe20),nop_bytes,4);// - network start synced scene
	write_process((char*)(0x12D86EC-0xe20),nop_bytes,4);// - network update synced scene
	write_process((char*)(0x12D8708-0xe20),nop_bytes,4);// - network stop synced scene
	
	int mflrr0 = 0x7C0802A6;
	int blr = 0x4E800020;
	if (enable == true) {
		*(volatile int*)0x12CB198 = blr;
		*(volatile int*)0x12CB55C = blr;
		*(volatile int*)0x12CB930 = blr;
		*(volatile int*)0x12CB70C = blr;
	} else {
		*(volatile int*)0x12CB198 = mflrr0;
		*(volatile int*)0x12CB55C = mflrr0;
		*(volatile int*)0x12CB930 = mflrr0;
		*(volatile int*)0x12CB70C = mflrr0;
	}
}*/

struct Rotation3 {float roll, pitch, yaw;Vector3 toVector3() {Vector3 ret = {roll,pitch,yaw};return ret;}};
typedef Vector3 Vec3;
typedef Rotation3 Rot3;

unsigned int StoUI(char *c );
unsigned long long StoULL(const char *c );
long long StoLL(const char *c );
//0x41143344 is name changer or sumthin
//0x41143324 + 0x6
//0x411432E4 spoof your location
void removeFileData(char *file);
void writeToFile(char *file, char buf[], int size);
void appendToFile(char *file, char buf[], int size);
bool deleteFile(const char *Path);
bool renameFile(const char *oldName, const char *newName);
void debugLogFile(char *text);
int getFileSize(char *file);
bool readFile(char *file, char buf[], int size);
bool readFile(char *file, char buf[], int size, unsigned int offset);
//char extrabuffer[100];
char *ItoS(int num);
float atof(char *str);
int StoI( const char *c );
char* FtoS(float input);
float StoF(const char* s);
int StoUI( const char *c );
bool StoBool(char *str);
unsigned int StoIUHEX(char *c);
void sleep(usecond_t time);
//#include "ArrayList.hpp"
//mymath
//#include "atof.h"
//#include <lotsOfMath.h>
#include "Buttons.h"
void* _malloc(uint32_t a_uiSize);
void _free(void* a_Addr);
//#include <bits/sce_stdlib.h>
int ConsoleWrite(const char * s){uint32_t len;system_call_4(403, 0, (uint64_t)s, std::strlen(s), (uint64_t)&len);return_to_user_prog(int);}
int write_process(void* destination, const void* source, size_t size);
#include "Enums.h"
/*struct drawTextAddresses {
	char padding1[4];
	unsigned int font;
	unsigned int scale;
	unsigned int color;
	char padding2[0xc];
	unsigned int wrap;
	unsigned int center;
	unsigned int entry;
	unsigned int atcs;
	unsigned int etc;
	unsigned int draw;
	char padding3[8];
};
drawTextAddresses textAddresses;
struct drawQuadAddresses {
	unsigned int quad;
	unsigned int texture;
};
drawQuadAddresses drawAddresses;*/
#define oldInvoke 1
#if oldInvoke == 1
#include "Natives.h"
#else
//#include "Natives_len.h"
#endif
#include "MyMath.h"
//#include "BitmapLoader.h"
//GTAImage testimg;
void print(char text[]);
unsigned int getEntityFromIndex(int entity) {
	//returns CPed
	opd_s getEntityFromIndex_t = {(addrstruct().entityFromIndex^dataDecryptor())/*0xA552E0*/,TOC};//same
	unsigned int (*getEntityFromIndexx)(int entity) = (unsigned int(*)(int))&getEntityFromIndex_t;
	return getEntityFromIndexx(entity);
}

//CPed, CVehicle...
CObj *getCObjFromIndex(int entity) {
	return (CObj*)getEntityFromIndex(entity);
}

/*
struct poolEntity {
	unsigned int unknown;//equals 0xffffffff when entity was deleted
	unsigned int addr;
	bool isValid() {
		return !(unknown == 0xFFFFFFFF) && unknown > 0xFA;
	}
	unsigned int getAddress() {
		return addr;
	}//0x7D0
};
struct entityPoolSingles {
	poolEntity individuals[1];//size doesn't matter, just need it to know it's an array//[0xFA];//  0xFA for the one pool
	//unsigned int nextPoolPointerUnk1;
	//unsigned int nextPoolPointerUnk2;
	//unsigned int nextPoolPointer;
};
struct entityPool {
	entityPoolSingles *entities;//0x0  size of 0x7D0
	char unknown1[0x4];//0x4
	int maxPoolSize;//0x8
	char unknown2[0x4];//0xC
	int poolSizeCurrent;//0x10

	//int totalsize;//0xB4
	poolEntity getEntity(int index) {
		return entities->individuals[index];
	}
};
entityPool *getEntityPool() {
	return (entityPool*)*(volatile int*)0x1CC5790;//same
}*/
//*(volatile int*)(*(volatile int*)0x1CC5790+0x10) = amount of objects in pool
	//*(volatile int*)(*(volatile int*)0x1CC5790) = start of pool

struct entityPool;

//event functions
opd_s updateEventDataWithServer_t = {0x9FCE50,TOC};//same
bool (*updateEventDataWithServer)(unsigned int eventDataPointer, int unknown2) = (bool(*)(unsigned int,int))&updateEventDataWithServer_t;

opd_s allocateEvent_t = {0x9FCDC8,TOC};//same
int (*allocateEvent)(int event_addr, int type,int unk1, int unk2, int unk3) = (int(*)(int,int,int,int,int))&allocateEvent_t;

opd_s getUnknownPoolData_t = {0xA546A8,TOC};//same
unsigned int (*getUnknownPoolData)(entityPool *poolPointer) = (unsigned int(*)(entityPool *))&getUnknownPoolData_t;

opd_s executeEventOnOnePlayer_t = {0x9FC88C,TOC};//do event on 1 player only?
int (*executeEventOnOnePlayer)(int eventDataPointer, int event_addr) = (int(*)(int,int))&executeEventOnOnePlayer_t;
//end event functions



unsigned int getEntityModelByAddress(unsigned int entityAddress) {
	unsigned int patch = *(volatile unsigned int*)0x003AC288;
	*(volatile unsigned int*)0x003AC288 = 0x60000000;
	unsigned int ret = ENTITY::GET_ENTITY_MODEL(entityAddress);
	*(volatile unsigned int*)0x003AC288 = patch;
	return ret;
}
opd_s isPlayerPedDataBeingUpdated_t = {0x1006338,TOC};
unsigned int(*isPlayerPedDataBeingUpdated)(unsigned int playerPed) = (unsigned int(*)(unsigned int))&isPlayerPedDataBeingUpdated_t;
#include "GlobalStuff.h"
/*__ALWAYS_INLINE */void PatchInJump2(uint64_t Address, int Destination, bool Linked)
{
		int FuncBytes[4];													// Use this data to copy over the address.
		Destination = *(volatile int*)Destination;									// Get the actual destination address (pointer to void).
		FuncBytes[0] = (0x3D600000) + ((Destination >> 16) & 0xFFFF);			// lis %r11, dest>>16
		if (Destination & 0x8000)											// if bit 16 is 1...
			FuncBytes[0] += 1;
		FuncBytes[1] = (0x396B0000) + (Destination & 0xFFFF);					// addi %r11, %r11, dest&OxFFFF
		FuncBytes[2] = (0x7D6903A6);											// mtctr %r11
		FuncBytes[3] = (0x4E800420);											// bctr
		if (Linked)
			FuncBytes[3] += 1;												// bctrl
		write_process((void*)Address, FuncBytes, 4 * 4);
}
void PatchInJumpNoWrite(int Destination, bool Linked, int FuncBytes[4])
{
														// Use this data to copy over the address.
		Destination = *(volatile int*)Destination;									// Get the actual destination address (pointer to void).
		FuncBytes[0] = (0x3D600000) + ((Destination >> 16) & 0xFFFF);			// lis %r11, dest>>16
		if (Destination & 0x8000)											// if bit 16 is 1...
			FuncBytes[0] += 1;
		FuncBytes[1] = (0x396B0000) + (Destination & 0xFFFF);					// addi %r11, %r11, dest&OxFFFF
		FuncBytes[2] = (0x7D6903A6);											// mtctr %r11
		FuncBytes[3] = (0x4E800420);											// bctr
		if (Linked)
			FuncBytes[3] += 1;												// bctrl
		
}
bool detachAllObjectsEnabled = true;
bool demiGodmode = false;
float textSize = 0.49f;//0.50 for ages
void dumpMem(void *_data, int size, int formatSize = 4, int lineSize = 16, bool showAsAscii = false);
#include "Mods.h"
#include "XML.h"
#include "OtherPlayerStats.h"
//#include "PSC.h"
int submenu = 0;
#include "Scaleforms.h"

#include "Networking.h"
#include "RTMTool.h"
#pragma endregion
#pragma region ps3 sms

//$(SCE_PS3_ROOT)\target\ppu\lib\libsysutil_np_stub.a
//$(SCE_PS3_ROOT)\target\ppu\lib\libsysmodule_stub.a
#include <cell/sysmodule.h>
#include "np.h"
#ifdef sceShit
/*static const SceNpCommunicationId s_communication_id = {
	{'N','P','X','S','0','0','0','2','4'},
	'\0',
	0,
	0
};*/

typedef uint16_t SceNpBasicMessageMainType;
typedef uint16_t SceNpBasicMessageSubType;
typedef uint32_t SceNpBasicMessageFeatures;
typedef struct SceNpBasicMessageDetails {
 SceNpBasicMessageId msgId;
 SceNpBasicMessageMainType mainType;
 SceNpBasicMessageSubType subType;
 SceNpBasicMessageFeatures msgFeatures;
 const SceNpId *npids;
 size_t count;
 const char *subject;
 const char *body;
 const void *data;
 size_t size;
} SceNpBasicMessageDetails;

SceNpId playerNpIds[18];
int registerPlayerNpId(int player) {
	char *user = PLAYER::GET_PLAYER_NAME(player);
	cellSysmoduleLoadModule(CELL_SYSMODULE_SYSUTIL_NP);
	int ret, transCtxId, titleCtxId;
	uint8_t np_pool[SCE_NP_MIN_POOL_SIZE];
	ret = sceNpInit(SCE_NP_MIN_POOL_SIZE, np_pool);
	printf("Initting NP...\n");
	if (ret < 0) {
		printf("Already initialized\n",ret);
	}
	printf("Looking up...\n");
	ret = sceNpLookupInit();
	if (ret < 0) {
		printf("Already initialized\n",ret);
	}
	printf("Look Up Success\n");
	SceNpCommunicationId communicationId = *(SceNpCommunicationId*)(*(volatile unsigned int*)(0x1CCB140)+0x168);//probably needs updating but I don't use it anmyways
	SceNpId selfNpId;
	// communicationId assumed to store an appropriate value
	ret = sceNpManagerGetNpId(&selfNpId);
	if (ret < 0) {
		printf("Failed to get np id %i\n",ret);
		return ret;
	}
	printf("CTX created\n");
	ret = sceNpLookupCreateTitleCtx(&communicationId, &selfNpId);
	if (ret < 0) {
		printf("Failed %i\n",ret);
		return ret;
	}
	titleCtxId = ret;
	printf("TITLE CTX Created\n");

	SceNpId npId;
	SceNpOnlineId onlineId;
	// titleCtxId assumed to store an appropriate value
	ret = sceNpLookupCreateTransactionCtx(titleCtxId);
	if (ret < 0) {
		printf("Failed %i\n",ret);
		return ret;
	}
	transCtxId = ret;
	printf("TRANSACTION CTX Created\n");
	// Transaction
	strncpy(onlineId.data, user, SCE_NET_NP_ONLINEID_MAX_LENGTH);
	ret = sceNpLookupNpIdAsync (
		transCtxId, // Transaction context ID
		&onlineId, // Online ID of the target user (case-insensitive)
		&npId, // NP ID of the target user will be stored
		0,
		NULL);
	if (ret < 0) {
		printf("Failed %i\n",ret);
		return ret;
	}
	memcpy((void*)&playerNpIds[player],(void*)&npId,sizeof(npId));




	// Destroy the transaction context
	sceNpLookupDestroyTransactionCtx(transCtxId);
	// Destroy the title context
	sceNpLookupDestroyTitleCtx(titleCtxId);
	return 0;
}

SceNpId *getPlayerNpId(int player) {
	return &playerNpIds[player];
}

int sendSceMessage(int player, char *message) {
	int ret;
	//do all the messae sending
	SceNpBasicMessageDetails msg;
	msg.msgId = 0;
	msg.mainType = SCE_NP_BASIC_MESSAGE_MAIN_TYPE_GENERAL;
	msg.subType = SCE_NP_BASIC_MESSAGE_GENERAL_SUBTYPE_NONE;
	msg.msgFeatures = SCE_NP_BASIC_MESSAGE_FEATURES_ASSUME_SEND ;
	msg.npids = getPlayerNpId(player);//0x10
	msg.count = 1;
	msg.subject = "Msg By Paradise";
	msg.body = message;
	msg.data = NULL;
	msg.size = 0;
	ret = sceNpBasicSendMessageGui(&msg,SYS_MEMORY_CONTAINER_ID_INVALID);//sceNpBasicSendMessage(&npId, buffer, size);
	if ( ret < 0 ) {
		printf("Failed to send message %i\n",ret);
		return ret;
	}
	printf("Message Send\n");
	return 0;
}
#endif
#ifdef psnnmessagesstuff
char *messageToSendPSN;
void sendMessagePatchedCallback(SceNpBasicMessageDetails *msg, unsigned int containerSomething) {
	//do patch in jump here 0xD2828C
	//r3 is the msg struct so r3 + 0x10 is the np id for sceNpBasicSendMessage(&npId, buffer, size);
	printf("Gonna send it!\n");
	unsigned int size = strlen(messageToSendPSN);
	if (size >= (SCE_NP_BASIC_MAX_MESSAGE_SIZE - 1)) {
		printf("data is too big.\n");
		return;
	}

	const SceNpId *to = msg->npids;
	sceNpBasicSendMessage(to,messageToSendPSN,size);
	printf("Sent it!\n");
}

void sendMessagePSN(int player, char *title,char *message, bool dialog) {
	if (*(volatile unsigned int*)(0x1CFB0AC)==0) {
		printf("Generating data necessary to run...");
		opd_s _0x175D138_t = {0x175D138,TOC};
		void(*_0x175D138)() = (void(*)())&_0x175D138_t;
		_0x175D138();//this properly generates it but does not properly put the name in
		printf("Done generating data\n");
		/*
		0 32F4C108 33995F50
0 32F95EB8 33995F50
0 33996060 33995F50
0 33BFC818 33995F50
0 3635CA9C 33995F50
0 3635CE9C 33995F50

		*/
		//must figure out how to get hostData or whatever properly. It's the same no matter the player num but it does change sometimes like when host changes.
		//this function populates the one above
		//sub_11082C(player,hostData?);//0x3361E8A0
		return;
	}
	opd_s sub_12ECFDC_t = {0x12ECFDC,TOC};
	unsigned int(*sub_12ECFDC)(unsigned int unk1, unsigned int unk2) = (unsigned int(*)(unsigned int, unsigned int))&sub_12ECFDC_t;
	printf("Sending message\n");
	unsigned int r30 = sub_12ECFDC(*(volatile unsigned int*)(0x1CFB0AC),*(volatile unsigned int*)(*(volatile unsigned int*)(0x1CFB0AC)+0x40));
	unsigned int playerData = *(volatile unsigned int*)(r30+4) + (0x30*player);
	messageToSendPSN = message;
	opd_s sendMessage_t = {0x13086AC,TOC};
	void (*sendMessage)(unsigned int playerData, unsigned int one, char *messageTitle, unsigned int unk) = (void(*)(unsigned int, unsigned int, char *, unsigned int))&sendMessage_t;
	
	if (dialog) {
		printf("Getting read to send. PlayerData: 0x%X\n",playerData);
		sendMessage(playerData,1,title,0x01809560);//just make regular dialog show up
	} else {
		//patch it
		printf("About to start\n");
		char save[4*4];
		memcpy(save,(void*)0xD282A0,4*4);
		PatchInJump2(0xD282A0,(int)sendMessagePatchedCallback,4*4);
		//run it
		printf("Gonna call\n");
		sendMessage(playerData,1,title,0x01809560);
		printf("Called\n");
		//unpatch it
		memcpy((void*)0xD282A0,save,4*4);
	}
}
#endif
#pragma endregion
#pragma region system module start
SYS_MODULE_INFO("GTAV_Native_Invoker", 0, 1, 1);
SYS_MODULE_START(main);

SYS_LIB_DECLARE_WITH_STUB( LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME );
SYS_LIB_EXPORT( _ParadiseMC_export_function, LIBNAME );

// An exported function is needed to generate the project's PRX stub export library
extern "C" int _ParadiseMC_export_function(void)
{
    return CELL_OK;
}


#pragma endregion
#pragma region Variables
Native_s** g_Natives;
int myEntityType = 0; 
int vehicleLightIntensityVar = 1;
int debugPlayer = 0;
bool triggerScrollDown = false;
bool triggerScrollUp = false;
bool minimalistic = true;
char loginstring[] = "Paradise/Login.php?Key=%s&ID=%s";
char loginstring2[] = "Login.php?Key=%s&ID=%s";
bool doDrawIPInfo = true;
bool fakeWater = false;
char returntrue[] = {0x38, 0x60, 0x00, 0x01, 0x4E, 0x80, 0x00, 0x20};//0x38 0x60 0x00 0x01 0x4E 0x80 0x00 0x20 aka 38 60 00 01 4E 80 00 20
char returnfalse[] = {0x38, 0x60, 0x00, 0x00, 0x4E, 0x80, 0x00, 0x20};//38 60 00 00 4E 80 00 20
char ATTACH_ENTITY_TO_ENTITY_reenable[] = {0x7C, 0x08, 0x02, 0xA6, 0x31, 0x81, 0xFF, 0xE8};
char ATTACH_ENTITY_TO_ENTITY_PHYSICALLY_reenable[] = {0x7C, 0x08, 0x02, 0xA6, 0x31, 0x81, 0xFF, 0xF0};
char DISABLE_CONTROL_ACTION_reenable[] = {0x7C, 0x08, 0x02, 0xA6, 0x49, 0x10, 0x9D, 0x7D};//{0x7C, 0x08, 0x02, 0xA6, 0x49, 0x10, 0xA1, 0xA5};//0x400D04
char SET_INPUT_EXCLUSIVE_reenable[] = {0x7C, 0x08, 0x02, 0xA6, 0x49, 0x10, 0x9D, 0xF5};//{0x7C, 0x08, 0x02, 0xA6, 0x49, 0x10, 0xA2, 0x1D};//0x400C98
char playerdimensions_orig[] = {0x7C, 0x40, 0xF9, 0xCE};//0x01555F70   0x1555B50   0x15645A4
//char ADD_EXPLOSION_reenable[8];//read it into the array
//char ADD_OWNED_EXPLOSION_reenable[8];//read it into the array
//char POSSIBLE_EXPLOSION_MAIN_reenable[8];//read it into the array
//char POSSIBLE_EXPLOSION_MAIN2_reenable[8];//read it into the array
//char POSSIBLE_EXPLOSION_MAIN3_reenable[8];//read it into the array
//char POSSIBLE_EXPLOSION_MAIN4_reenable[8];//read it into the array
char DUMMY_RPG_reenable[8];//0x00FF4C38
char nop_bytes[] = {0x60,0x00,0x00,0x00};
int patchthestatdata = 0x48000258;
//float glarex=1.14/2,glarey=0.516,glarew=0.83,glareh=0.99,glareinc=0.01;
float glarex=.43489,glarey=0.338999,glarew=0.728996,glareh=0.6429799,glareinc=0.01;
bool dimensionsEnabled = false;
bool snowBool = false;
int vision_integer = 0;
int vision_clearOnChoice = true;
float vehicleGravity = 9.8;
int currentVehicleWheel = 0;
bool isAuthed = false;
//char *screen_effects[] = {"SwitchHUDIn","SwitchHUDOut","FocusIn","FocusOut","MinigameEndNeutral","MinigameEndTrevor","MinigameEndFranklin","MinigameEndMichael","MinigameTransitionOut","MinigameTransitionIn","SwitchShortNeutralIn","SwitchShortFranklinIn","SwitchShortTrevorIn","SwitchShortMichaelIn","SwitchOpenMichaelIn","SwitchOpenFranklinIn","SwitchOpenTrevorIn","SwitchHUDMichaelOut","SwitchHUDFranklinOut","SwitchHUDTrevorOut","SwitchShortFranklinMid","SwitchShortMichaelMid","SwitchShortTrevorMid","DeathFailOut","CamPushInNeutral","CamPushInFranklin","CamPushInMichael","CamPushInTrevor","SwitchOpenMichaelIn","SwitchSceneFranklin","SwitchSceneTrevor","SwitchSceneMichael","SwitchSceneNeutral","MP_Celeb_Win","MP_Celeb_Win_Out","MP_Celeb_Lose","MP_Celeb_Lose_Out","DeathFailNeutralIn","DeathFailMPDark","DeathFailMPIn","MP_Celeb_Preload_Fade","PeyoteEndOut","PeyoteEndIn","PeyoteIn","PeyoteOut","MP_race_crash","SuccessFranklin","SuccessTrevor","SuccessMichael","DrugsMichaelAliensFightIn","DrugsMichaelAliensFight","DrugsMichaelAliensFightOut","DrugsTrevorClownsFightIn","DrugsTrevorClownsFight","DrugsTrevorClownsFightOut","HeistCelebPass","HeistCelebPassBW","HeistCelebEnd","HeistCelebToast","MenuMGHeistIn","MenuMGTournamentIn","MenuMGSelectionIn","ChopVision","DMT_flight_intro","DMT_flight","DrugsDrivingIn","DrugsDrivingOut","SwitchOpenNeutralFIB5","HeistLocate","MP_job_load","RaceTurbo","MP_intro_logo","HeistTripSkipFade","MenuMGHeistOut","MP_corona_switch","MenuMGSelectionTint","SuccessNeutral","ExplosionJosh3","SniperOverlay","RampageOut","Rampage","Dont_tazeme_bro","DeathFailOut"};
bool bouncyRpgRockets = false;
bool input_disabled_bool = false;
bool disable_explosions_bool = false;
//(addrstruct().^dataDecryptor())
/*
register player vehicle?
unk_0xDB718B21(uParam0, "Player_Vehicle", unk_0xF8D7AF3B(player_id()));
*/
CNetGamePlayer *getCNetGamePlayer(int player) {//CEA55F4C  just 0x47E00C is the address... 0x82918F38 on xbox
	opd_s getCNetGamePlayer_t = {(addrstruct().getCNetGamePlayer^dataDecryptor())/*0x47E00C*/,TOC};//didn't change
	unsigned int (*getCNetGamePlayer_1)(int entity,int one) = (unsigned int(*)(int,int))&getCNetGamePlayer_t;
	return (CNetGamePlayer*)getCNetGamePlayer_1(player,1);
}


unsigned int getCNetObjFromEntityIndex(unsigned int entityIndex) {
	//0x4C is CNetObjPlayer or just CNetObj anything
	return *(volatile unsigned int*)(getEntityFromIndex(entityIndex)+0x4C);
}

unsigned int getCNetObjPlayerFromPedIndex(unsigned int ped) {
	return getCNetObjFromEntityIndex(ped);
}

unsigned int getCNetObjAutomobileFromVehicleIndex(unsigned int index) {
	return getCNetObjFromEntityIndex(index);
}


//(addrstruct().^dataDecryptor())
int entityToIndex(unsigned int entityAddress) {
	//opd_s canPoolBeUsed_t = {0xA546A8,TOC};
	//unsigned int(*canPoolBeUsed)(unsigned int poolAddress) = (unsigned int(*)(unsigned int))&canPoolBeUsed_t;
	//if (canPoolBeUsed(*(volatile unsigned int*)ScriptEntityPool) == 0)
	//if (*(volatile int*)(*(volatile unsigned int*)ScriptEntityPool+0x10) == -1 && (*(volatile unsigned int*)(*(volatile unsigned int*)ScriptEntityPool+0x1c) == 0 || *(volatile unsigned int*)(*(volatile unsigned int*)ScriptEntityPool+0x24) == 0)) {
	//	printf("Returning 0 on the entity call %i\n",*(volatile int*)(*(volatile unsigned int*)ScriptEntityPool+0x10));
	//	return 0;
	//}
	if (entityAddress == 0)
		return 0;
	//printf("Calling entity to index\n");
	opd_s entityToIndex_t = {(addrstruct().entityToIndex^dataDecryptor())/*0x474054*/,TOC};//didn't change
	int(*entityToIndex1)(unsigned int entityAddress) = (int(*)(unsigned int))&entityToIndex_t;
	return entityToIndex1(entityAddress);
}

int entityToIndex(CObj *entityAddress) {
	return entityToIndex((unsigned int)entityAddress);
}

//(addrstruct().^dataDecryptor())
bool isEntityAttachedToEntity(int entityAddress, int baseEntityAddress) {
	opd_s getEntityAttachedTo_t = {(addrstruct().getEntityAttachedTo^dataDecryptor())/*0x3A9EFC*/,TOC};//didn't change
	unsigned int(*getEntityAttachedTo)(unsigned int entityIndex) = (unsigned int(*)(unsigned int))&getEntityAttachedTo_t;
	return getEntityAttachedTo(entityAddress) == baseEntityAddress;//not working
}
opd_s rfrpf_t = {0x4A6128,TOC};//didn't change
unsigned int(*readFromRPF)(char *dir,char *openType) = (unsigned int(*)(char*,char*))&rfrpf_t;
//Example: readFromRPF("common:/data/version.txt","r");
//036110
opd_s ggv_t = {0x036110,TOC};//didn't change
int(*getGameVersion)() = (int(*)())&ggv_t;

opd_s initWater_t = {0x1282B70-0xe20,TOC};//changed but fixed
int(*initWater)(int zero) = (int(*)(int))&initWater_t;

opd_s weaponHashToAddress_t = {0x1512F60-0xe20,TOC};//broken as shit
unsigned int (*weaponHashToAddress)(unsigned int weaponhash) = (unsigned int(*)(unsigned int))&weaponHashToAddress_t;

//for our freeze data we will use 0x9D0EBEE6

//key is a weapon hash multiplied by 2

opd_s weaponHashToAddress_t2 = {0x1512F60,TOC};//broken as shit. Not used much anyways
unsigned int (*weaponHashToAddress2)(unsigned int weaponhash) = (unsigned int(*)(unsigned int))&weaponHashToAddress_t2;

template <typename T>
void setSecretStuff(unsigned int key, T data) {
	unsigned int addr = weaponHashToAddress2(key/2);
	if (addr != 0)
		*(T*)(addr+0x54) = data;
}

	//key is a weapon hash multiplied by 3
	//return value is multiplied by 16
template <typename T>
unsigned int getSecretStuff(unsigned int key) {
	unsigned int addr = weaponHashToAddress2(key/3);
	if (addr != 0)
		return *(T*)(addr+0x54)*16;
	return (T)0;
}

//(addrstruct().^dataDecryptor())
unsigned int modelHashToAddress(unsigned int hash) {
	//returns CVehicleModelInfo
	opd_s modelHashToAddress_t = {(addrstruct().modelToHash^dataDecryptor())/*0x9D9830*/,TOC};//appears to be the same
	unsigned int (*modelHashToAddress_1)(unsigned int hash, unsigned int *unk1) = (unsigned int(*)(unsigned int, unsigned int*))&modelHashToAddress_t;
	unsigned int store = 0xFFFF;
	return modelHashToAddress_1(hash,/*0x10070200*/&store);
}

//same as above
unsigned int getCVehicleModelInfo(unsigned int hash) {
	opd_s modelHashToAddress_t = {0x9D9830,TOC};
	unsigned int (*modelHashToAddress_1)(unsigned int hash, unsigned int *store) = (unsigned int(*)(unsigned int, unsigned int *))&modelHashToAddress_t;
	unsigned int a;
	return modelHashToAddress_1(hash,&a);
}

CObjModelInfo *getCModelInfo(unsigned int hash) {
	return (CObjModelInfo*)modelHashToAddress(hash);
}

opd_s sub_138A124_t = {0x138A124-0xe20,TOC};//not the same. fixed
void (*sub_138A124)(unsigned int host, int arg1, int arg2) = (void(*)(unsigned int, int, int))&sub_138A124_t;
//0,0 end singleplayer session (according to thingy) 
//x,1 Reloads and makes it think you are in a singleplayer lobby. Makes your game very buffy though
//x,2 party leader has left
//x,3 nothing happens
//x,0 unknown network error
int sub_138A124_1 = 0;
int sub_138A124_2 = 1;

/*
KICK PLAYER CODE
unk_2259170 is the pointer for MsgKickPlayer

sub_13599A0 kicks them blah blah
r4 = sub_47E00C(player,1)
r3 = *(volatile int*)0x1CF72C4;
r5 = 0;

sub_1626C64 is the send server function: 
seg001:0000000001359B58                 li        r5, 0x3D6
seg001:0000000001359B5C                 bl        sub_A8B908
seg001:0000000001359B60                 lis       r3, unk_2259170@ha
seg001:0000000001359B64                 mr        r4, r24
seg001:0000000001359B68                 addic     r3, r3, unk_2259170@l
seg001:0000000001359B6C                 lwz       r3, 8(r3)
seg001:0000000001359B70                 bl        serverSend
*/

//0x18 is weapon type (int)
/*
0=unknown (or incorrect weaponHash)
1= no damage (flare,snowball, petrolcan)
2=melee
3=bullet
5=explosive (RPG, Railgun, grenade)
6=fire(molotov)
8=fall(WEAPON_HELI_CRASH)
10=electric
11=barbed wire
12=extinguisher
13=gas
14=water cannon(WEAPON_HIT_BY_WATER_CANNON)
*/
template <typename T>
void setWeaponData(unsigned int weaponhash, unsigned int data, T value) {
	unsigned int addr = weaponHashToAddress(weaponhash);
	if (addr)
		*(T*)(addr+data) = value;
}
template <typename T>
T getWeaponData(unsigned int weaponhash, unsigned int data) {
	unsigned int addr = weaponHashToAddress(weaponhash);
	if (addr)
		return *(T*)(addr+data);
	return (T)0;
}

unsigned int getCurrentWeaponAddress() {
	unsigned int weaponhash = 0;
	WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(),&weaponhash,1);
	return weaponHashToAddress(weaponhash);
}

void setCurrentWeaponType(int newType) {//BROKEN
	unsigned int weaponhash = 0;
	WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(),&weaponhash,1);
	setWeaponData<int>(weaponhash,0x18,newType);
	unsigned int addr = getWeaponData<unsigned int>(weaponhash,0x40);
	if (addr != 0) {
		*(volatile int*)(addr+8) = newType;
		print2("Set",1000);
	}
}



template <typename T>
void setModelData(unsigned int hash, unsigned int data, T value) {
	unsigned int addr = bodyguard::modelHashToAddress2(hash);
	if (addr)
		*(T*)(addr+data) = value;
}
template <typename T>
T getModelData(unsigned int hash, unsigned int data) {
	unsigned int addr = bodyguard::modelHashToAddress2(hash);
	if (addr)
		return *(T*)(addr+data);
	return (T)0;
}

template <typename T>
void setModelData2(unsigned int hash, unsigned int data, T value) {
	unsigned int addr = modelHashToAddress(hash);//0x1B8 is the type
	if (addr)
		*(T*)(addr+data) = value;
}
template <typename T>
T getModelData2(unsigned int hash, unsigned int data) {
	unsigned int addr = modelHashToAddress(hash);
	if (addr)
		return *(T*)(addr+data);
	return (T)0;
}


//0x1D4 is a float, wheel size (invisible)
//0x402deae4-0x402de910
//0x1B8 = (int)6   3 freezes
//nop 0x00F11C30 0x00F11C60 for safety
//tmp 0x402de910+0x1B8
//0x65 = (char)f;//probably freeze them (DOESN'T WORK)

//0x402bb870+0x1B8 dune nop 0x00F11C30 0x00F11C60

bool hhjjhhjj = true;//temporary
//47DF28 player id is first argument
namespace EntityStruct {
	unsigned int
		type = 0x14,
		godmode = 0xB4,
		health = 0x170,
		control = 0x4C,//0 means you have control   CNetObjPed NOT is it actually CNetObjPlayer
		vehicleSuspension = 0xCEC,
		vehicleGravity = 0x69c,
		modelData = 0x10,//pointer to it - 4 bytes
		littleTooMuchToDrink = 0xBF4,//0x41a00000 is 20
		currentSpeed = 0x428,
		wheel = 0xCA0,//also *(volatile unsigned int*)(vehicle+0x668) for this pointer, and the one after this is wheel count
		wheelRotMultiplier = 0x130,
		wheelFreeze = 0x2D8,//set to 5 and boom freeze. nop 0x00e813d0 to unfreeze
		pointer1 = 0x30,
		playerPointer = 0xBD0,//CPlayerInfo
		wheelContour = 0x8;
}//IP'S 0x20059CC
//sub_13E1A58 kick player non host?
//0x31197000+0xBD0
//0x411432C0

//x: (int)0x72C != 0 == PRESSED
//l2: (char)0x862 == 0x48 || (char)0x862 == 0xC8 == PRESSED OR     (char)0x1BF == 0 == PRESSED
//r2: (char)0x17A == 1 == PRESSED
/*int buttonPressed(int player, int button) {//0x186 is horn
	char buttonPressed = 0;
	unsigned int addr = getEntityFromIndex(PLAYER::GET_PLAYER_PED(player));
	if (addr) {
		addr = *(volatile unsigned int*)(addr+EntityStruct::playerPointer);
		if (addr) {
			buttonPressed = *(char*)(addr+button);//0x860 is free aiming
		}
		addr = *(volatile unsigned int*)(addr+0xE9C);
		return (int)addr;
		if (addr) {
			addr = *(volatile unsigned int*)(addr+0x4C);//CNetObjPed
			if (addr) {
				buttonPressed = *(char*)(addr+button);
			}
		}
	}
	return (int)buttonPressed;
}*/










bool doesEntityExist(unsigned int entity) {
	if (getEntityFromIndex(entity) == 0) return false;
	return true;
}
template <typename T>
T getEntityData(unsigned int entityIndex, unsigned int dataIndex) {
	if (doesEntityExist(entityIndex))
		return *(T*)(getEntityFromIndex(entityIndex)+dataIndex);
	return (T)0;
}
template <typename T>
void setEntityData(unsigned int entityIndex, unsigned int dataIndex, T data) {
	if (doesEntityExist(entityIndex))
		*(T*)(getEntityFromIndex(entityIndex)+dataIndex) = data;
#if HEN_MODE == 0
	endEncryptFunc();//End B
#endif
}
template <typename T>
T getVehicleWheelData(unsigned int vehicle, int wheelNum, unsigned int dataIndex) {
	if (doesEntityExist(vehicle)) {
		unsigned int addr = *(volatile int*)(getEntityFromIndex(vehicle)+(EntityStruct::wheel+4*wheelNum));
		if (addr > 0x10000)//motorcycles and 2 wheeled things are a nono
			return *(T*)(addr+dataIndex);
	}
	return (T)0;
}
template <typename T>
void setVehicleWheelData(unsigned int vehicle, int wheelNum, unsigned int dataIndex, T data) {//wheel countour is 8
	wheelNum = wheelNum%4;//hehe dank hax
	if (doesEntityExist(vehicle)) {
		unsigned int addr = *(volatile int*)(getEntityFromIndex(vehicle)+(EntityStruct::wheel/*0xCA0*/+4*wheelNum));
		if (addr > 0x10000)
			*(T*)(addr+dataIndex) = data;/*dataIndex is 8 for camber*/
	}
}

void freezeConsole() {
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(),true)) {
		write_process((char*)0x00e813d0,nop_bytes,4);//broken but ain't even used anyways so WTH
		setVehicleWheelData<float>(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),true),0,EntityStruct::wheelFreeze,5.0f);//freeze
	} else {
		print2("~r~You are not in a vehicle",1000);
	}
}
//(addrstruct().^dataDecryptor())
opd_s sub_47E00C_t = {0x47E00C,TOC};//same
int (*sub_47E00C)(int player, int one) = (int(*)(int,int))&sub_47E00C_t;
//sub_13599A0
opd_s sub_13599A0_t = {0x13599A0-0xe20,TOC};//fixed
int (*sub_13599A0)(int r3, int r4, int r5) = (int(*)(int,int,int))&sub_13599A0_t;
/*void kickPlayerNonHost(int player, int r5) {//0 is used in the basic one, 1 and 2 are used in other parts of code
	int r3 = *(volatile int*)0x1CF72C4;
	int r4 = sub_47E00C(player,1);
	sub_13599A0(r3,r4,r5);
}*/







int detachObjectsFromPlayerAddr = 0;
int detachObjectsFromPlayerCurrentIndex = 0;
bool detachObjectsFromPlayerCurrentlyRunning = false;
void detachObjectFromPlayerCallback(int previousEntity) {
	//for (int i = 0; i < Entities->poolSize && i < Entities->maxPoolSize; i++) {
	entityPool *Entities = getEntityPool();
	if (/*detachObjectsFromPlayerCurrentIndex >= Entities->poolSize || */detachObjectsFromPlayerCurrentIndex >= Entities->maxPoolSize) {
		detachObjectsFromPlayerCurrentlyRunning = false;
		return;//finished
	}

	poolEntity *ent = &Entities->getEntity(detachObjectsFromPlayerCurrentIndex);
	while (true) {
		//printf("entAddr: %i, max: %i, cur: %i\n",ent->addr,Entities->maxPoolSize,Entities->poolSize);
		//return;
		if (ent->isValid()) {
			int index = entityToIndex(ent->addr);
			//if (ENTITY::DOES_ENTITY_EXIST(index)) {
				if (ENTITY::GET_ENTITY_ATTACHED_TO(index) == detachObjectsFromPlayerAddr) {
				//if (getEntityAttachedTo(ent->addr) == detachObjectsFromPlayerAddr) {
					break;
				}
			//}
		}
		//!(ent->isValid() && /*isEntityAttachedToEntity(ent->addr,detachObjectsFromPlayerAddr)*/)
		//printf("Heyyo 2\n");
		detachObjectsFromPlayerCurrentIndex++;
		if (/*detachObjectsFromPlayerCurrentIndex >= Entities->poolSize || */detachObjectsFromPlayerCurrentIndex >= Entities->maxPoolSize) {
			detachObjectsFromPlayerCurrentlyRunning = false;
			return;//finished
		}
		//printf("Heyyo 3\n");
		ent = &Entities->getEntity(detachObjectsFromPlayerCurrentIndex);
	}
	//printf("Heyyo 4\n");
	//if (isEntityAttachedToEntity(ent.addr,detachObjectsFromPlayerAddr)) {
		int entityIndex = entityToIndex(ent->addr);
		//printf("Deleting entity of id %i\n",entityIndex);
		//netreq::reqent(entityIndex);
		removeObjectsSpecial::markEntityForDeletion(entityIndex,detachObjectFromPlayerCallback);
	//}
	//}
	//printf("Heyyo 5\n");
	detachObjectsFromPlayerCurrentIndex++;
}

void detachObjectsFromPlayer(int player) {
	if (detachObjectsFromPlayerCurrentlyRunning == false) {
		detachObjectsFromPlayerCurrentlyRunning = true;
		detachObjectsFromPlayerAddr = /*getEntityFromIndex(*/PLAYER::GET_PLAYER_PED(player)/*)*/;
		detachObjectsFromPlayerCurrentIndex = 0;
		detachObjectFromPlayerCallback(0);
	}
}

void detachAllObjects() {
	//0x009DBAEC gun  //0x09DBBE4  //0x0360B48
	//0x009DBD6C gun  //0x09DBE30  //CHECK THIS ONE 0x9DBE3C
	//0x009DBD98 gun  //0x09DBE30

	//0x00357EEC get in vehicle

	//*(volatile int*)(0x009DBAEC) = 0x60000000;//nop dat
	//*(volatile int*)(0x009DBD6C) = 0x60000000;
	//*(volatile int*)(0x009DBD98) = 0x60000000;
	//*(volatile int*)(0x00357EEC) = 0x60000000;

	//*(volatile int*)(0x09DBBE4) = 0x60000000;
	//*(volatile int*)(0x09DBE30) = 0x60000000;
	//*(volatile int*)(0x0360B48) = 0x60000000;//first one
	//*(volatile int*)(0x09DBF28) = 0x60000000;//second one
	//*(volatile int*)() = 0x60000000;
	/*unsigned int entity = PLAYER::PLAYER_PED_ID();
	if (!PED::IS_PED_IN_ANY_VEHICLE(entity,1)) {
		if (doesEntityExist(entity)) {
			WEAPON::SET_CURRENT_PED_WEAPON(entity,GAMEPLAY::GET_HASH_KEY("WEAPON_UNARMED"),true);
			unsigned int loc1 = getEntityData<unsigned int>(entity,0x2C);
			if (loc1 != 0)
				*(volatile int*)(loc1+0x34) = 0;//player pool pointer. I'm setting it to zero lol
			
		}
	} else {
		print2("~r~Disabled while in a vehicle due to freezes.",1000);
	}*/
	//int playerEntity = getEntityFromIndex(PLAYER::PLAYER_PED_ID());
	detachObjectsFromPlayer(PLAYER::PLAYER_ID());
}

//(int)ped id + 0xE48: 0 when punching, 2 when not punching
//(char)ped id + 0xE31: 0x40 when not aiming and 0x00 when aiming
//open and close menu: check when you get in car

//returns the script index of the entity
int getRandomPoolEntity() {
	entityPool *Entities = getEntityPool();
	int ret = 0;
	int timeout = 0;
	while (ret == 0 && timeout < 50) {
		int i = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0,Entities->maxPoolSize)%Entities->maxPoolSize;
		poolEntity *ent = &Entities->getEntity(i);
		if (ent->isValid()) {
			int index = entityToIndex(ent->addr);
			netreq::reqent(index);
			if (netreq::hasent(index)) {
				//bool alreadyattachedtoplayer = ENTITY::GET_ENTITY_ATTACHED_TO(index) == PLAYER::GET_PLAYER_PED(player);
				bool isme = index == PLAYER::PLAYER_PED_ID();
				if (/*!alreadyattachedtoplayer && */!isme) {
					ret = index;
				}
			}
		}
		timeout++;
	}
	return ret;
}

int attachAllObjectsToPlayerCount = 1;
void attachAllObjectsToPlayer(int player, int version = 0) {//actually just does a random one lol
	if (version == 1) {
		entityPool *Entities = getEntityPool();
		for (int i = 0; i < Entities->maxPoolSize; i++) {
			poolEntity *ent = &Entities->getEntity(i);
			if (ent->isValid()) {
				int index = entityToIndex(ent->addr);
				netreq::reqent(index);
				if (netreq::hasent(index)) {
					bool alreadyattachedtoplayer = ENTITY::GET_ENTITY_ATTACHED_TO(index) == PLAYER::GET_PLAYER_PED(player);
					bool isme = index == PLAYER::PLAYER_PED_ID();
					if (!alreadyattachedtoplayer && !isme) {
						float cord[3] = {0,0,0};
						float rot[3] = {GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0,360),GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0,360),GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0,360)};
						OBJ::attachPropAlreadySpawned(player,PlayerMods::bones::BONE_ROOT,index,cord,rot);
						//return;
					}
				}
			}
		}
	}
	if (version == 0) {
		for (int i = 0; i < attachAllObjectsToPlayerCount; i++) {
			int index = getRandomPoolEntity();
			if (index != 0)
				OBJ::attachPropAlreadySpawned(player,PlayerMods::bones::BONE_ROOT,index);
		}
	}
}






/*void detachAllObjectsRunLater(int nothing) {
	unsigned int entity = PLAYER::PLAYER_PED_ID();
	if (doesEntityExist(entity)) {
		unsigned int loc1 = getEntityData<unsigned int>(entity,0x2C);
		if (loc1 != 0)
			*(volatile int*)(loc1+0x34) = 0;
	}
}*/
/*void detachAllObjectAdvanced() {//DO NOT LOOP THIS
	unsigned int entity = PLAYER::PLAYER_PED_ID();
	if (!PED::IS_PED_IN_ANY_VEHICLE(entity,1)) {
		WEAPON::SET_CURRENT_PED_WEAPON(entity,GAMEPLAY::GET_HASH_KEY("WEAPON_UNARMED"),true);
		unsigned int entity = PLAYER::PLAYER_PED_ID();
		if (doesEntityExist(entity)) {
			unsigned int loc1 = getEntityData<unsigned int>(entity,0x2C);
			if (loc1 != 0)
				*(volatile int*)(loc1+0x34) = 0;
		}
	} else {
		print2("~r~Disabled while in a vehicle due to freezes.",1000);
	}
}*/
bool hasControlOfEntity(int entity) {
	if (!doesEntityExist(entity)) return false;
	int16_t c = getEntityData<int16_t>(entity,0x4C);//CNetObjPed
	if (c == 0) return true;
	if (getEntityData<char>(entity,0x27) != 0) return false;
	opd_s s_t = {0xA0D1B4,TOC};//same
	int(*s)(int j) = (int(*)(int))&s_t;
	if (s(c) != 0) return 0;
	return true;
}
void enableEntityControl(unsigned int entity) {
	//setEntityData<int16_t>(entity,EntityStruct::control,0x0000);
}
void setEntityGodmode(unsigned int entity, bool enabled) {
	enableEntityControl(entity);
	setEntityData<int16_t>(entity,EntityStruct::godmode,enabled?0x1080:0);
}
bool getEntityGodmode(unsigned int entity) {
	return (bool)getEntityData<int16_t>(entity,EntityStruct::godmode);
}
int getEntityType(unsigned int entity) {
	return (int)getEntityData<char>(entity,EntityStruct::type);
}
void setVehicleSuspension(unsigned int entity, float height) {
	enableEntityControl(entity);
	setEntityData<float>(entity,EntityStruct::vehicleSuspension,height);
}
float getVehicleSuspension(unsigned int entity) {
	return getEntityData<float>(entity,EntityStruct::vehicleSuspension);
}
void setVehicleGravity(unsigned int entity, float gravity) {
	enableEntityControl(entity);
	setEntityData<float>(entity,EntityStruct::vehicleGravity,gravity);
}
float getVehicleGravity(unsigned int entity) {
	return getEntityData<float>(entity,EntityStruct::vehicleGravity);
}
void changeVehicleModel(unsigned int vehicle, int offsetFromAdder) {//-52 is helicopter
	setEntityData<unsigned int>(vehicle,EntityStruct::modelData,0x402DE910+0x270*offsetFromAdder);
}
void printVehicleModel(int offsetFromAdder) {//-52 is helicopter
	//setEntityData<unsigned int>(vehicle,EntityStruct::modelData,0x402DE910+0x270*offsetFromAdder);
	print2((char*)(0x402DE910+0x270*offsetFromAdder+0x160),1000);//not used anyways
}
float getVehicleWheelRotMultiplier(int vehicle, int wheel) {
	return getVehicleWheelData<float>(vehicle,wheel,EntityStruct::wheelRotMultiplier);
}
void setVehicleWheelRotMultiplier(int vehicle, int wheel, float rotMultiplier) {
	setVehicleWheelData<float>(vehicle,wheel,EntityStruct::wheelRotMultiplier,rotMultiplier);
}

float getVehicleWheelContour(int vehicle, int wheel) {
	return getVehicleWheelData<float>(vehicle,wheel,EntityStruct::wheelContour);
}
void setVehicleWheelContour(int vehicle, int wheel, float contour) {
	if (wheel%2 == 0)
		contour = contour*-1;
	setVehicleWheelData<float>(vehicle,wheel,EntityStruct::wheelContour,contour);//wheelContour is 8
}

void enableVehicleModel(unsigned int hash,bool enable) {
	if (enable) {
		setModelData<char>(hash,0x1B8,0);
	} else {
		setModelData<char>(hash,0x1B8,1);
	}
}

/*
void setEntityVisible(int entity, bool visible) {
	*(volatile int*)(getEntityFromIndex(entity)+0x18) = visible;
}
void setEntityType(int entity, int type) {//4 is ped... other numbers are others
	*(volatile int*)(getEntityFromIndex(entity)+0x14) = type;
}
int getEntityType(int entity) {
	return (int)(*(char*)(getEntityFromIndex(entity)+0x14));
}*/









opd_s getPlayerFromPool_t = {0x47DFA0,TOC};//same
unsigned int (*getPlayerFromPool)(int player, bool arg1, bool arg2) = (unsigned int(*)(int,bool,bool))&getPlayerFromPool_t;
int getPlayerMod1(int player, int mod, bool arg1 = 1, bool arg2 = 1) {
	unsigned int addr = getPlayerFromPool(player,arg1,arg2)+0xBD0;
	return *(volatile int*)(addr+mod);
}//823750656+0xBD0 = 0x411432C0+0x160 = 0x31197000 + 0x4C











#ifdef iuzISDhjgijadsfjhgiujfasdgiu

void remove_all_weapons(int ped_mem_addr)
{
	updateEventDataWithServer(*(volatile int*)(0x1CF72B0), 1); //unknown               same
	
	int event_addr = getUnknownPoolData(getEntityPool(EventPool)/**(volatile int*)(0x1CC4A54)*/); //gets free event address      SAME
	 
	allocateEvent(event_addr, 0xE, 0, 0, 0); //prepare event with type (0xE = remove all weapons)
	
	*(volatile int*)(event_addr) = 0x1926B20; //Pointer sent to client, client calls *POINTER* + 0x1C on their system     change 0x1926B20+0x1C to GODMODE cuz it is currently an opd_s struct    0x193ABD8 is KICK PLAYER
	//same

	int ped_net_addr = *(volatile int*)(ped_mem_addr + 0x4C);
	short netID = *(short*)(ped_net_addr + 0x6);
	*(short*)(event_addr + 0x1C) = netID; //sets players netID into event_addr (so the game knows which client?)
	
	executeEventOnOnePlayer(*(volatile int*)(0x1CF72B0), event_addr); //unknown
}

void setWeather(int ped_mem_addr)
{
	updateEventDataWithServer(*(volatile int*)(0x1CF72B0), 1); //unknown               same
	
	int event_addr = getUnknownPoolData(getEntityPool(EventPool)); //gets free event address      SAME
	 
	allocateEvent(event_addr, 0xA, 0, 0, 0); //prepare event with type (0xE = remove all weapons)
	
	*(volatile int*)(event_addr) = 0x1926B20; //Pointer sent to client, client calls *POINTER* + 0x1C on their system     change 0x1926B20+0x1C to GODMODE cuz it is currently an opd_s struct    0x193ABD8 is KICK PLAYER
	//same

	int ped_net_addr = *(volatile int*)(ped_mem_addr + 0x4C);
	short netID = *(short*)(ped_net_addr + 0x6);
	*(short*)(event_addr + 0x1C) = netID; //sets players netID into event_addr (so the game knows which client?)
	
	executeEventOnOnePlayer(*(volatile int*)(0x1CF72B0), event_addr); //unknown
}

opd_s GIVE_PED_SCRIPTED_TASK_EVENT_local_t = {0x12CBFB0,TOC};
void (*GIVE_PED_SCRIPTED_TASK_EVENT_local)(unsigned int r3, unsigned int r4) = (void(*)(unsigned int, unsigned int))&GIVE_PED_SCRIPTED_TASK_EVENT_local_t;
void setPedTask(unsigned int ped_memory_address, unsigned int taskData) {
	int ped_net_addr = *(volatile int*)(ped_memory_address + 0x4C);
	if (ped_net_addr > 0x10000) {
		unsigned int r3ForFunction = *(volatile unsigned int*)(0x2C+ped_net_addr);
		unsigned int r4ForFunction = *(volatile unsigned int*)(0x218+ped_net_addr);
		GIVE_PED_SCRIPTED_TASK_EVENT_local(r3ForFunction,r4ForFunction);
	} else {
		printf("Ped net address not good!\n");
	}
}

void kick_player_non_host(int player)//doesn't work
{
	int entityIndex = PLAYER::GET_PLAYER_PED(player);

	unsigned int ped_mem_addr = getEntityFromIndex(entityIndex);

	//updateEventDataWithServer(*(volatile int*)(0x1CF72B0), 1); //unknown
	
	int event_addr = getUnknownPoolData(getEntityPool(EventPool)); //gets free event address
	
	allocateEvent(event_addr, 0x19, 1, 0, 0); //prepare event with type 0x19 is scripted event
	
	*(volatile int*)(event_addr) = 0x193ABD8; //Pointer sent to client, client calls *POINTER* + 0x1C on their system     change 0x1926B20+0x1C to GODMODE cuz it is currently an opd_s struct    0x193ABD8 is KICK PLAYER
	
	int ped_net_addr = *(volatile int*)(ped_mem_addr + 0x4C);//CNetObjPed
	short netID = *(short*)(ped_net_addr + 0x6);
	*(short*)(event_addr + 0x1C) = netID; //sets players netID into event_addr (so the game knows which client?)
	
	executeEventOnOnePlayer(*(volatile int*)(0x1CF72B0), event_addr); //unknown
}
#endif
float getFPS() {
	static int i = 0;
	static float fps = 0;
	i++;
	if (i%20 == 0) {
		i = 0;
		fps = 1.0f/GAMEPLAY::GET_FRAME_TIME();
	}
	return fps;
}
void kickPlayerNonHost(int player) {
	//0x00D003DFB4+10*0x4 = args
	unsigned int playerBit = (1<<player);
	//0x2 0x7 0x35     and 0xA was me so idk...
	ScriptArg args[3] = {0x2,player,0x35};//  53 calls the network bail thing :)   0x35 is the speccial one I guess
	//first arg is always 1
	//last arg is always the bit thing
	//second arg meh
	//third arg is the size of the data
	SCRIPT::TRIGGER_SCRIPT_EVENT(1,args,3,playerBit);
}

void removePlayerFromBadsport(int player) {
	//void func_6235(var uParam0) is for all events where the first param is 2, where it will read the second arg (like 53 for kick)
	//void func_5802(var uParam0) is for the swap for all trigger_script_event calls (166) so the first arg is the switch in here
	unsigned int playerBit = (1<<player);
	ScriptArg args[3] = {312,player,0x35};
	SCRIPT::TRIGGER_SCRIPT_EVENT(1,args,3,playerBit);
}

void backupHelicopter(int player) {
	//00000120 00000000 FFFFFFFF 0000000A 00000000 00000000
	//6 args
	//then 00000123 00000000 FFFFFFFF 0000000A 00000004 00000000

	//ammo drop:
	//00000120 00000000 FFFFFFFF 00000008 00000000 00000000
}

void ammoDrop(int player) {
	unsigned int playerBit = (1<<player);
	ScriptArg args[6] = {0x120,player,-1,8,0,0};
	SCRIPT::TRIGGER_SCRIPT_EVENT(1,args,6,playerBit);
	//void func_324(int iParam0, var uParam1, var uParam2, int iParam3)
	//from am_contact_requests
}



void diskErrorDetour(unsigned int r3) {
	ConsoleWrite((char*)r3);
	if (r3 == 0x018416BC)
		cellMsgDialogOpen(1,"Paradise SPRX:\nA GTA Disk Reading Error Occurred!\nIt is highly recommended that you restart GTA V to avoid freezing!\nThis error is caused when GTA has an error reading from the harddrive. This error is not caused by Paradise SPRX.",my_dialog2,(void*) 0x0000aaab, NULL);
}

void diskErrorDetourSetup() {
	PatchInJumpAddr(0x0014FDC5C,(int)diskErrorDetour,false);
}

//#define kjsdhg
#ifdef kjsdhg
opd_s _0x012C8D60_t = {0x0012C8D60,TOC};
unsigned int (*_0x0012C8D60)(unsigned int r3, unsigned int senderData, unsigned int recieverData, unsigned int r6, unsigned int r7, unsigned int r8, unsigned int r9) = (unsigned int(*)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))&_0x012C8D60_t;
//12D137C
opd_s _0x12D137C_t = {0x12D137C,TOC};
unsigned int (*_0x12D137C)(unsigned int r3, unsigned int senderData, unsigned int recieverData, unsigned int r6, unsigned int r7, unsigned int r8, unsigned int r9) = (unsigned int(*)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))&_0x12D137C_t;

//bool jobProtection = true;


unsigned int scriptEventDetour(unsigned int r3, unsigned int senderData, unsigned int recieverData, unsigned int r6, unsigned int r7, unsigned int r8, unsigned int r9) {
	unsigned int addressOfArgs = *(volatile unsigned int*)r3 + 0x4;  //r3+10*0x4;  there is an unknown value for the first arg in the list
	//printf("addressOfArgs: 0x%X, *(volatile int*)r3: 0x%X, dif: 0x%X\n",addressOfArgs,*(volatile int*)r3,addressOfArgs-*(volatile int*)r3);
	char *senderName = (char*)(*(volatile int*)(senderData+0x78)+0x10);
	int senderPlayerId = *(volatile int*)(*(volatile int*)(senderData+0x8)+0x8);
	//printf("%s did a script event, player ID 0x%X. senderData: 0x%X, event data: 0x%X 0x%X 0x%X 0x%X 0x%X\n",senderName,senderPlayerId,senderData,*(volatile int*)(addressOfArgs+0x0),*(volatile int*)(addressOfArgs+0x4),*(volatile int*)(addressOfArgs+0x8),*(volatile int*)(addressOfArgs+0xC),*(volatile int*)(addressOfArgs+0x10));
	//if (*(volatile int*)addressOfArgs == 166) {
		//this is the one I want to research cuz of func_6272("CnCTG_IN_BF", 2147483647, 1);
		//snprintf$(scriptEventDialogText,sizeof(scriptEventDialogText),"%s tried to kick you!",senderName);
		//printf("0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X (next is 1337) 0x%X\n",*(volatile int*)(addressOfArgs+0x4*0),*(volatile int*)(addressOfArgs+0x4*1),*(volatile int*)(addressOfArgs+0x4*2),*(volatile int*)(addressOfArgs+0x4*3),*(volatile int*)(addressOfArgs+0x4*4),*(volatile int*)(addressOfArgs+0x4*5),*(volatile int*)(addressOfArgs+0x4*6),*(volatile int*)(addressOfArgs+0x4*7),*(volatile int*)(addressOfArgs+0x4*8),*(volatile int*)(addressOfArgs+0x4*9),*(volatile int*)(addressOfArgs+0x4*10),*(volatile int*)(addressOfArgs+0x4*11),*(volatile int*)(addressOfArgs+0x4*12),*(volatile int*)(addressOfArgs+0x4*13),*(volatile int*)(addressOfArgs+0x4*14),*(volatile int*)(addressOfArgs+0x4*15),*(volatile int*)(addressOfArgs+0x4*16),*(volatile int*)(addressOfArgs+0x4*17),*(volatile int*)(addressOfArgs+0x4*18),*(volatile int*)(addressOfArgs+0x4*19),*(volatile int*)(addressOfArgs+0x4*20),*(volatile int*)(addressOfArgs+0x4*21),*(volatile int*)(addressOfArgs+0x4*22),1337);
		//return 0;
		//*(volatile int*)addressOfArgs = 0;
	//}
	if (*(volatile int*)addressOfArgs == 0x2/* && *(volatile int*)(addressOfArgs+0x4) == PLAYER::PLAYER_ID()*/ && *(volatile int*)(addressOfArgs+0x8) == 0x35) {
		//this is kick player
		snprintf$(scriptEventDialogText,sizeof(scriptEventDialogText),"%s tried to kick you!",senderName);
		print2(scriptEventDialogText,5000);
		//return 0;
		*(volatile int*)addressOfArgs = 0;
		disableAllScriptEvents = true;
	}
	if (*(volatile int*)addressOfArgs == 0x2/* && *(volatile int*)(addressOfArgs+0x4) == PLAYER::PLAYER_ID()*/ && *(volatile int*)(addressOfArgs+0x8) == 0x34) {
		//this is fake leave
		snprintf$(scriptEventDialogText,sizeof(scriptEventDialogText),"%s tried to make you fake leave!",senderName);
		print2(scriptEventDialogText,5000);
		//return 0;
		*(volatile int*)addressOfArgs = 0;
		disableAllScriptEvents = true;
	}
	if (*(volatile int*)addressOfArgs == 0x2/* && *(volatile int*)(addressOfArgs+0x4) == PLAYER::PLAYER_ID()*/ && *(volatile int*)(addressOfArgs+0x8) == 0x2e) {
		//this is fake leave
		snprintf$(scriptEventDialogText,sizeof(scriptEventDialogText),"%s tried to reset your view!",senderName);
		print2(scriptEventDialogText,5000);
		//return 0;
		*(volatile int*)addressOfArgs = 0;
		disableAllScriptEvents = true;
	}
	if (*(volatile int*)addressOfArgs == 0xD8) {
		//this is give rp
		snprintf$(scriptEventDialogText,sizeof(scriptEventDialogText),"%s tried to give you %i rp!",senderName,*(volatile int*)(addressOfArgs+0x8));
		print2(scriptEventDialogText,5000);
		//*(volatile int*)(addressOfArgs+0x8) = 0;//rp amount
		*(volatile int*)addressOfArgs = 0;
		//return 0;
		disableAllScriptEvents = true;
	}
	/*if (*(volatile int*)addressOfArgs == 0x9A) {
		//this is job circle
		if (jobProtection) {
			snprintf$(scriptEventDialogText,sizeof(scriptEventDialogText),"%s tried to make you go into a job with job protection enabled! This may be a false alarm.",senderName);
			print2(scriptEventDialogText,5000);
			//try doing *(volatile int*)addressOfArgs = 0 instead
			//return 0;
			*(volatile int*)addressOfArgs = 0;
		}
	}*/
	//not needed anymore because bypassed
	if (*(volatile int*)addressOfArgs == 0xDA || *(volatile int*)addressOfArgs == 0xDB /*219*/) {
		//this is money
		if (moneyProtection) {
			//Write_Global(262145+4812,0);//set the amount to zero instead of returning
			snprintf$(scriptEventDialogText,sizeof(scriptEventDialogText),"%s tried to give you money with money protection enabled!",senderName);
			print2(scriptEventDialogText,2000);
			//return 0;
			*(volatile int*)addressOfArgs = 0;
			disableAllScriptEvents = true;
		} else {
			//Write_Global(262145+4812,20000);
		}
	}
	if (*(volatile int*)addressOfArgs == 0x16C) {
		//this is apartment
		snprintf$(scriptEventDialogText,sizeof(scriptEventDialogText),"%s tried to force you into their apartment!",senderName);
		print2(scriptEventDialogText,5000);
		//return 0;
		*(volatile int*)addressOfArgs = 0;
		disableAllScriptEvents = true;
	}
	/*if (*(volatile int*)addressOfArgs == 200) {
		//this is mp intro
		snprintf$(scriptEventDialogText,sizeof(scriptEventDialogText),"%s tried to force you into the multiplayer intro!",senderName);
		print2(scriptEventDialogText,5000);
		//return 0;
		*(volatile int*)addressOfArgs = 0;
		disableAllScriptEvents = true;
	}*/
	if (*(volatile int*)addressOfArgs == 0x3) {
		if (*(volatile int*)(addressOfArgs+0x8) == 0x14) {
			//multiplayer intro
			snprintf$(scriptEventDialogText,sizeof(scriptEventDialogText),"%s tried to force you into multiplayer intro cutscene!",senderName);
			print2(scriptEventDialogText,5000);
			*(volatile int*)addressOfArgs = 0;
			disableAllScriptEvents = true;
		}
		if (*(volatile int*)(addressOfArgs+0x8) == 0x3A) {
			//flight school
			snprintf$(scriptEventDialogText,sizeof(scriptEventDialogText),"%s tried to force you into multiplayer intro flight school!",senderName);
			print2(scriptEventDialogText,5000);
			*(volatile int*)addressOfArgs = 0;
			disableAllScriptEvents = true;
		}
		if (*(volatile int*)(addressOfArgs+0x8) == 0x37 || *(volatile int*)(addressOfArgs+0x8) == 0x36 || *(volatile int*)(addressOfArgs+0x8) == 0x35 || *(volatile int*)(addressOfArgs+0x8) == 0x38/*freeze one*/ ) {
			//this is job
			snprintf$(scriptEventDialogText,sizeof(scriptEventDialogText),"%s tried to force you to join a job!",senderName);
			print2(scriptEventDialogText,5000);
			//return 0;
			*(volatile int*)addressOfArgs = 0;
			disableAllScriptEvents = true;
		}
	}
	if (disableAllScriptEvents)
		*(volatile int*)addressOfArgs = 0;//just disable them completely the game functions fine without them
	return _0x0012C8D60(r3,senderData,recieverData,r6,r7,r8,r9);
}
void setupScriptEventDetour() {
	*(volatile int*)(0x1C6BD80) = *(volatile int*)( /*this returns the opd struct address Function*/(int)&scriptEventDetour );//same
	*(volatile int*)((0x1C6BD80+0x4)) = *(volatile int*)( /*this returns the opd struct address TOC*/(int)&scriptEventDetour+0x4 );
}
//0x103A0

#define BREAK_CODE() {*(volatile unsigned int*)0x103A4 = 0x60000000;__asm__("lis %r11, 0x0001");__asm__("addi %r11, %r11, 0x03A4");__asm__("mtctr %r11");__asm__("bctrl");}





unsigned int statEventDetour(unsigned int r3, unsigned int senderData, unsigned int recieverData, unsigned int r6, unsigned int r7, unsigned int r8, unsigned int r9) {
	eventArgumentInfo *data = (eventArgumentInfo *)r3;
	
	static bool breakPoint = false;
	//int addressOfArgs = r3+10*0x4;
	char *senderName = (char*)(*(volatile int*)(senderData+0x78)+0x10);
	//int senderPlayerId = *(volatile int*)(*(volatile int*)(senderData+0x8)+0x8);
	//printf("breakpointBool: 0x%X, r3: 0x%X, senderData: 0x%X, receiverData: 0x%X\n",&breakPoint,r3,senderData,recieverData);
	if (breakPoint) {
		//__asm__("twu %1, %1");
		//BREAK_CODE();
	}

	unsigned int *statHash = data->data->getpUInt(0);
	int *statValue = data->data->getpInt(1);

	snprintf$(scriptEventDialogText,sizeof(scriptEventDialogText),"%s tried to set stat 0x%X with value %i",senderName,*statHash,*statValue);
	print2(scriptEventDialogText,5000);
	//printf(scriptEventDialogText);
	//printf("\n");
	
	//printf("SET_STAT(player, %i, %i);\n",*statHash,*statValue);
	//printf("//SET_STAT(player, 0x%X, 0x%X);\n",*statHash,*statValue);

	*statHash = 0;//stat name
	*statValue = 0;//stat value
	_0x12D137C(r3,senderData,recieverData,r6,r7,r8,r9);
}
void setupStatEventDetour() {
	*(volatile unsigned int*)(0x1C6C530+0x0) = *(volatile unsigned int*)((unsigned int)&statEventDetour+0x0);
	*(volatile unsigned int*)(0x1C6C530+0x4) = *(volatile unsigned int*)((unsigned int)&statEventDetour+0x4);
}
#endif
void resetPlayerView(int player) {
	ScriptArg args[3];
	args[0].i = 0x2;
	args[1].i = player;
	args[2].i = 0x2e;//46
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,3,bits);//https://i.imgur.com/8n57oB4.png
}
void freezePlayerBy16Event(int player) {
	ScriptArg args[22];
	args[0].i = 16;
	args[1].i = player;
	args[2].i = 0x5241494e;//46
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,22,bits);
}
void kickPlayerFromCarScriptEvent(int player) {
	ScriptArg args[2];
	args[0].i = 55;
	args[1].i = player;
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,2,bits);
}
void forcePlayerIntoMpIntro(int player) {
	//xFreak_Killz-_- did a script event, player ID 0x1. senderData: 0x222DE70, event data: 0x3 0x0 0x14 0x0 0x41030950
	ScriptArg args[4];
	args[0].i = 3;
	args[1].i = player;
	args[2].i = 0x14;
	args[3].i = 0x0;
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,4,bits);
}
void setPlayerBadsport(int player, bool badsport, unsigned int thevalue = 0x100) {
	unsigned int badsportValue = 0x7FFFFFFF;
	if (badsport == false) {
		badsportValue = 0xFFFFFFFF;
	}
	ScriptArg args[6];
	args[0].i = 0x124;
	args[1].ui = badsportValue;
	args[2].ui = badsportValue;
	args[3].ui = badsportValue;
	args[4].ui = badsportValue;
	args[5].ui = badsportValue;
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,6,bits);

	//0x138 1: 0x100 2: 0xA 3: 0x1
	//0x138 1: 0x100 2: 0x29 3: 0x1
	//0x138 1: 0x100 2: 0x48 3: 0x1
	ScriptArg args2[4];
	args[0].i = 0x138;
	args[1].i = thevalue;
	args[2].i = 0xA;//int_max?
	args[3].i = 0x1;
	PlayerMods::eventCreator::callScriptEvent(args2,4,bits);
	args[2].i = 0x29;
	PlayerMods::eventCreator::callScriptEvent(args2,4,bits);
	args[2].i = 0x48;
	PlayerMods::eventCreator::callScriptEvent(args2,4,bits);
}
bool resetViewBoolLoop[18];
void resetPlayerViewLoop() {
	for (int i = 0; i < 18; i++)
		if (resetViewBoolLoop[i])
			resetPlayerView(i);
}

void setPlayerStats(int player) {
	//event id is 150
	//get_event_data for it is in freemode at line 313711
	//the call to func_544 is set_stat_int usage
	//doesn't seem to have a trigger_script_event call
	ScriptArg args[12];
	args[0].i = 150;
	args[1].i = player;
	args[2].i = 0;//unknown value

	//the values are for NOT setting the correlated stat
	//these are the hash from the array. weird but it's wat it is
	args[3].i = 88;//int
	args[4].i = 34;//bool
	args[5].i = 1;//float
	args[6].i = 2949;//int
	args[7].i = 228;//bool
	args[8].i = 228;//float

	args[9].i = 0;//value to set for the int ones. This is added on to the previous value set for the stat
	args[10].i = 0;//value to set for the float ones. This is added on to the previous value set for the stat
	args[11].i = 0;//value to set for the bool ones
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,12,bits);
}

enum {
	EVENT_STAT_INT_0 = 3,
	EVENT_STAT_INT_1 = 6,
	EVENT_STAT_BOOL_0 = 4,
	EVENT_STAT_BOOL_1 = 7,
	EVENT_STAT_FLOAT_0 = 5,
	EVENT_STAT_FLOAT_1 = 8,
	EVENT_STAT_VALUE_INT = 9,
	EVENT_STAT_VALUE_FLOAT = 10,
	EVENT_STAT_VALUE_BOOL = 11
};
void setupDefaultStatEvent(int player, ScriptArg *args) {
	args[0].i = 150;
	args[1].i = player;
	args[2].i = player;//unknown value
	args[3].i = 88;//int
	args[4].i = 34;//bool
	args[5].i = 1;//float
	args[6].i = 2949;//int
	args[7].i = 228;//bool
	args[8].i = 228;//float
	args[9].i = 0;//value to set for the int ones. This is added on to the previous value set for the stat
	args[10].i = 0;//value to set for the float ones. This is added on to the previous value set for the stat
	args[11].i = 0;//value to set for the bool ones
}
//https://pastebin.com/N9HWunq3
bool globalStatVersionType = 1;//this decides whether I use the first 3 (0) or the last 3 (1)
void setPlayerStatInt(int player, int statIndex, int statValue, bool type = globalStatVersionType) {
	//statValue = 0xFFFFFFFF-statValue+1;
	ScriptArg args[12];
	setupDefaultStatEvent(player,args);
	//printf("%i\n",args[6].i);
	args[EVENT_STAT_VALUE_INT].ui = *(volatile unsigned int*)(&statValue);
	args[EVENT_STAT_VALUE_BOOL].i = statValue;
	args[EVENT_STAT_VALUE_FLOAT].f = statValue;
	if (type == 0)
		args[EVENT_STAT_INT_0].i = statIndex;
	else
		args[EVENT_STAT_INT_1].i = statIndex;
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,12,bits);
}
void setPlayerStatBool(int player, int statIndex, bool statValue, bool type = globalStatVersionType) {
	ScriptArg args[12];
	setupDefaultStatEvent(player,args);
	args[EVENT_STAT_VALUE_INT].i = *(volatile unsigned int*)(&statValue);
	args[EVENT_STAT_VALUE_BOOL].i = statValue;
	args[EVENT_STAT_VALUE_FLOAT].f = statValue;
	if (type == 0)
		args[EVENT_STAT_BOOL_0].i = statIndex;
	else
		args[EVENT_STAT_BOOL_1].i = statIndex;
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,12,bits);
}
void setPlayerStatFloat(int player, int statIndex, float statValue, bool type = globalStatVersionType) {
	ScriptArg args[12];
	setupDefaultStatEvent(player,args);
	args[EVENT_STAT_VALUE_INT].i = *(volatile unsigned int*)(&statValue);
	args[EVENT_STAT_VALUE_BOOL].i = statValue;
	args[EVENT_STAT_VALUE_FLOAT].f = statValue;
	if (type == 0)
		args[EVENT_STAT_FLOAT_0].i = statIndex;
	else
		args[EVENT_STAT_FLOAT_1].i = statIndex;
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,12,bits);
}

void setPlayerRpStat(int player, int rp) {
	//for (int i = 0; i < 25; i++)
	setPlayerStatInt(player,626,rp,true);
}
void setPlayerSnackStat(int player, int amt) {
	//for (int i = 0; i < 25; i++)
	setPlayerStatInt(player,1261,amt,true);
}
void setPlayerMentalStat(int player, float amt) {
	//for (int i = 0; i < 25; i++)
	setPlayerStatFloat(player,133,amt,true);
}
void setPlayerBadSportStat(int player, int value) {//MP0_BAD_SPORT_BITSET
	//for (int i = 0; i < 25; i++)
	setPlayerStatInt(player,1162,value,true);
}

/*
from FM_RACE_CREATOR
void func_1555(var uParam0)
{
	struct<5> Var0;
	
	if (get_event_data(1, uParam0, &Var0, 5))
	{
		if (!Var0.imm_4)
		{
			if (Var0.imm_3 == 0)
			{
				func_858(0, "XPT_PARTNER", 0, 0, Var0.imm_2, 1, -1, 0);
			}
			else
			{
				func_858(0, "XPT_GEN", 0, 0, Var0.imm_2, 1, -1, 0);
			}
		}
		else if (Var0.imm_3 == 0)
		{
			func_706(0, player_ped_id(), "XPT_PARTNER", 0, 0, Var0.imm_2, 1, -1, 0, 0);
		}
		else
		{
			func_706(0, player_ped_id(), "XPT_GEN", 0, 0, Var0.imm_2, 1, -1, 0, 0);
		}
	}
}
*/
void givePlayerRP(int player, int amount, int unk1, int unk2) {
	//rank 500 is 0x0103941C
	//rank 120 is 0x0021025A
	ScriptArg args[5];
	args[0].i = 0xD8;//216
	args[1].i = player;
	args[2].i = 0xffffffff-amount+1;//46
	args[3].i = 0;//-1   0 is partner, else is gen
	args[4].i = 0;//unk2;//1
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,5,bits);
}
/*void makePlayerGoToStripClub(int player, int stripper) {
	//join 000000F3 00000008 00000000
	//leave 00000109 00000008 00000000
	ScriptArg args[3];
	args[0].i = 0xF3;
	args[1].i = player;//player to be put in it
	args[2].i = stripper;
	unsigned int bits = 0xFFFFFFFF;//actually, a bit array of all the current players in the lobby, so like a 1 for players in the lobby, a 0 for players not in the lobbyy
	PlayerMods::eventCreator::callScriptEvent(args,3,bits);
}*/
//get_event_data(
void removePlayerWantedLevel(int player) {
	ScriptArg args[2];
	args[0].i = 356;
	args[1].i = player;
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,3,bits);
}
void setPlayerPassiveModeOn(int player) {
	ScriptArg args[3];
	args[0].i = 0x104;
	args[1].i = player;
	args[2].i = 0;
	unsigned int bits = 0xFFFFFFFF;//(1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,3,bits);
}
void setPlayerPassiveModeOff(int player) {
	ScriptArg args[3];
	args[0].i = 0x118;
	args[1].i = player;
	args[2].i = 0;
	unsigned int bits = 0xFFFFFFFF;//(1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,3,bits);
}
void activateBroadcastApp(int player) {
	ScriptArg args[3];
	args[0].i = 2;
	args[1].i = player;
	args[2].i = 0x23;//35
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,3,bits);
}
void sendPlayerMessage(int player, char *message) {
	//line 318419 freemode.c
	ScriptArg args[3];
	args[0].i = 152;
	args[1].i = player;
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,3,bits);
}
void fakeJoinJobMessage(int player) {
	ScriptArg args[3];
	args[0].i = 152;
	args[1].i = player;
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,3,bits);
}
void playSound(int player, int type) {//types: 0 or 1
	ScriptArg args[3];
	args[0].i = 30+type;
	args[1].i = player;
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,3,bits);

	//PLAY_SOUND_FROM_COORD(g_nsoundId, "3_2_1", s_coords.x, s_coords.y, s_coords.z, "HUD_MINI_GAME_SOUNDSET", 1, 1, 1);
}
void apartmentInvite(int sender, int reciever) {//I think it just sends it to the whole lobby
	ScriptArg args[2];
	args[0].i = 32;
	args[1].i = sender;
	unsigned int bits = (1<<reciever);
	PlayerMods::eventCreator::callScriptEvent(args,2,bits);
}
void onevonedeathmatchInvite(int sender, int reciever) {//I think it just sends it to the whole lobby
	ScriptArg args[3];
	args[0].i = 41;
	args[1].i = sender;
	unsigned int bits = (1<<reciever);
	PlayerMods::eventCreator::callScriptEvent(args,3,bits);
}
//00000150 00000000 00000004 00000001   change clothes for other team
void apartmentInvite(int playerToInvite, int apartmentOwner, int apartmentNum) {
	ScriptArg args[3];
	args[0].i = 0x16c;
	args[1].i = apartmentOwner;
	args[2].i = apartmentNum;
	unsigned int bits = (1<<playerToInvite);
	PlayerMods::eventCreator::callScriptEvent(args,3,bits);
}
void showOffTextAtBottom(int player) {
	ScriptArg args[3];
	args[0].i = 166;//this should actually be 15
	args[1].i = player;
	args[2].i = 15;//35
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,3,bits);
}
void deactivateBroadcastApp(int player) {
	ScriptArg args[3];
	args[0].i = 2;
	args[1].i = player;
	args[2].i = 0x24;//36
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,3,bits);
}
void crateDropTestEvent(int player) {
	ScriptArg args[6];
	args[0].i = 290;
	args[1].i = player;
	args[2].i = -1;
	args[3].i = 8;
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,6,bits);
}
void sendCash(int player, int amount) {
	ScriptArg args[5];
	args[0].i = 219;//0xDB
	args[1].i = 40;//player;
	args[2].i = amount;
	args[3].i = -1;
	args[4].i = 1;
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,5,bits);
}
/*
keys:
0FOQ5-KK57M-AESTM
 TJHLD-68F6Z-ABXOV
 00EYT-2LCJK-LFZHA
 WZ4F4-18VPV-EEK62
 JIGVF-1XMS1-3FETR
 ZVGJ9-GSZWY-DCE3S
 BNDV8-8C6FB-2E4WY
 LEK6P-OG63E-SHT2L
 507MQ-CLMAX-24646
 IGOQX-2H7I8-D4ZAO
 ZUJ3X-GBNLO-LWLDC
 CRQTM-G3NWY-GTHEK
 SCYU0-E8GJ7-LJUAB
 I351B-R79L2-W0R6H
 696SR-DQXNC-P28W5
 AOMFW-TWNY9-BWO0Y
 PSV5R-IKXUG-86Z15
 8QPIW-6DKAU-NN0OK
 D44D7-GZECS-R8MGF
 4O87A-50070-2D51C
 2YWYX-W9AKW-EACBS
 16TVD-77JX0-XHAQX
 WZ4F4-18VPV-EEK62
 JZO8D-HIA9M-4R7LU
 NK9EP-NQODV-EH4EN
 VOV6B-53RGG-1J93Y
 YQ32I-RSZFP-W9Y1I
 WPZ5G-URY2C-LWC7V
 MWU8S-BSA4T-ER26E
Serendipity

28KJ-EV78-6S9S-AV22
PD42-S7YY-U3F5-9APK
WVCX-CVQX-J4YY-U7TG
X4M5-DDVG-T4J7-2MJA
VKEV-KF2H-VD4S-3B5J
J3BU-XT8P-5EWU-4MGE
WJ34-HMVM-D4BP-Z6SN
NBH6-WQWB-EKM4-C6SJ
URSJ-CCQR-M4SA-2D2Q
5DVT-SGUB-TM38-6893
G3EK-6TM7-DG7W-TX7F
C5UZ-N2X3-NAZZ-E4WR
MQSE-DBAX-4RSZ-GS9Z
2CJ7-W6K2-JFWW-SB6H
lexicon
*/
/*void sendCash2(int player, int amount) {
	ScriptArg args[3];
	args[0].i = 219;//0xDB
	args[1].i = player;
	args[2].i = amount;
	unsigned int bits = 0xFFFFFFFF;
	PlayerMods::eventCreator::callScriptEvent(args,3,bits);
}*/
void makePlayerFakeLeave(int player) {
	{
	ScriptArg args[3];
	args[0].i = 0x2;
	args[1].i = player;
	args[2].i = 0x34;//46
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,3,bits);
	}

	{
	//this is supposed to be off radar but just causes me to fake leave so fuk it
	ScriptArg args[3];
	args[0].i = 203;
	args[1].i = player;
	args[2].i = 100000;//46
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,3,bits);
	}
}

void playerLeaveDialog(int player) {
	ScriptArg args[2];
	args[0].i = 193;
	args[1].i = PLAYER::GET_PLAYER_PED(player);
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,2,bits);
}

//000000DA 00000003 06648E28 00000001
//this is the one that I use
/*void Moneyeventloopp() {
 for(int i = 16; i < 500; i++)
{
 int Args[5];
 Args[0] = 219;
 Args[1] = i; 
 Args[2] = 20000;
 int Bitset = 0;
 GAMEPLAY::SET_BIT(&Bitset, playerid);
 SCRIPT::TRIGGER_SCRIPT_EVENT(1, Args, 3, Bitset);
 GAMEPLAY::CLEAR_BIT(&Bitset, i);
 }
}*/
void givePlayerMoney(int player, int amount) {//refunds to themself. max 20k
	for (int i = 16; i < amount/20000+16; i++) {
		ScriptArg args[4];
		args[0].i = 219;//0xDA = 218;
		args[1].i = i;//player;//cash giver (them cuz they refund themself)
		args[2].i = 20000;//46
		args[3].i = 1;
		unsigned int bits = (1<<player);//0xFFFFFFFF;
		PlayerMods::eventCreator::callScriptEvent(args,4,bits);
	}
}
/*void killPlayerByEvent(int player) {
	//my player id is 4
	//9 args
	//bits: 0xFFEF which is ~(1<<4)
	//data: 00000000 00000004 00000067 00000000 00000000 00000004 00000000 00000000 00000000
	ScriptArg args[9];
	args[0].i = 0x0;
	args[1].i = player;//cash giver (them cuz they refund themself)
	args[2].i = 0x67;//46
	args[3].i = 0;
	args[4].i = 0;
	args[5].i = player;
	args[6].i = 0;
	args[7].i = 0;
	args[8].i = 0;
	unsigned int bits = 0xFFFFFFFF;//~(1<<player);//(1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,4,bits);
}*/
void teleportPlayerIntoGolfEvent(int player) {
	ScriptArg args[3];
	args[0].i = 0x3;
	args[1].i = player;
	args[2].i = 0x37;
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,3,bits);
}
void teleportPlayerIntoDartsEvent(int player) {
	ScriptArg args[3];
	args[0].i = 0x3;
	args[1].i = player;
	args[2].i = 0x36;
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,3,bits);
}
void teleportPlayerIntoArmWrestlingEvent(int player) {
	ScriptArg args[3];
	args[0].i = 0x3;
	args[1].i = player;
	args[2].i = 0x35;
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,3,bits);
}
void ForceMugger(int player) {
	ScriptArg Args[3];
	Args[0].i = 3;
	Args[1].i = player;
	Args[2].i = 0x18;
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(Args, 3, bits);
}
void BadSport(int player) {
	ScriptArg Args[4];
	Args[0].i = 312;
	Args[1].i = player;
	Args[2].i = 10000000;
	Args[3].i = 100;
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(Args, 4, bits);
}
void freezePlayerEvent(int player) {//this is one way to do it
	ScriptArg args[3];
	args[0].i = 0x3;
	args[1].i = player;
	args[2].i = 0x38;
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,3,bits);
}
void changePlayerWeather(int player, char *weather = "RAIN") {
	ScriptArg args[22];
	args[0].i = 16;
	args[1].i = player;
	//strcpy((char*)&args[2].i,weather);
	//printf("\n%s\n",(char*)&args[2].i);
	args[2].ui = 0x187198C;
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,22,bits);
}
/*
void playerProperty(int player, int arg1, int arg2, int arg3) {//refunds to themself. max 20k
	ScriptArg args[5];
	args[0].i = 364;
	args[1].i = player;//apartment of this player
	args[2].i = 0;
	args[3].i = 0;
	args[4].i = 0;
	unsigned int bits = (1<<player);
	PlayerMods::eventCreator::callScriptEvent(args,5,bits);
}*/

int callEventInt = 0;
void callEvent(int entityIndex, unsigned int evt)
{
	unsigned int ped_mem_addr = getEntityFromIndex(entityIndex);

	if (ped_mem_addr != 0) {//event 0x49 froze me
			
		int event_addr = getUnknownPoolData(getEntityPool(EventPool)); //gets free event address
		
		allocateEvent(event_addr, evt, 0, 0, 0); //prepare event with type (0xE = remove all weapons)

		//*(volatile int*)(e_addr + 0x20) = 0;
		//*(volatile int*)(e_addr + 0x24) = 0;
		//*(volatile int*)(e_addr + 0x28) = 0;
		
		*(volatile int*)(event_addr) = 0x1926B20; //Pointer sent to client, client calls *POINTER* + 0x1C on their system     change 0x1926B20+0x1C to GODMODE cuz it is currently an opd_s struct 
		
		int net_addr = *(volatile int*)(ped_mem_addr + 0x4C);//CNetObjPed
		if (net_addr != 0) {
			short netID = *(short*)(net_addr + 0x6);
			*(short*)(event_addr + 0x1C) = netID; //sets players netID into event_addr (so the game knows which client?)
		}
	}
}

bool controlswitcheroonie = false;
opd_s sub_12BE230_t = {0x12BE230-0xe20,TOC};
void (*sub_12BE230)(unsigned int r3, char *type) = (void(*)(unsigned int, char *))&sub_12BE230_t;
void TaskNM(unsigned int entityIndex) {
	unsigned int addr = getEntityFromIndex(entityIndex);
	if (addr != 0) {
		unsigned int r3 = *(volatile unsigned int*)(addr+0x4C);
		if (r3 != 0)
			sub_12BE230(r3,"TaskNM");
	}
}
void request_control_of_entity(unsigned int entityIndex) {
	unsigned int addr = getEntityFromIndex(entityIndex);
	if (addr != 0) {
		unsigned int r3 = *(volatile unsigned int*)(addr+0x4C);//CNetObjPed
		if (r3 != 0)
			sub_12BE230(r3,"NETWORK_REQUEST_CONTROL_OF_ENTITY");
	}
}

void clear_ped_tasks(int event_addr, int ped_mem_addr, int unk)
{
	allocateEvent(event_addr, 0x27, 0, 0, 0); //prepare event with type (0x27 = clear_ped_tasks)
	
	*(char*)(event_addr + 0x1E) = unk; //immediatly (0 no, 1 yes)
	*(volatile int*)(event_addr) = 0x1927518; //Pointer sent to client, client calls *POINTER* + 0x1C, 0x20, 0x30 on their system
	*(short*)(event_addr + 0x1C) = 0; //clears netID?
	if (ped_mem_addr != 0)
	{
		int net_addr = *(volatile int*)(ped_mem_addr + 0x4C);
		if (net_addr != 0)
		{
			short netID = *(short*)(net_addr + 0x6);
			*(short*)(event_addr + 0x1C) = netID; //sets players netID into event_addr (so the game knows which client?)
		}
	}
}

void sub_12C45A4(int e_addr, int p_addr, int w_hash, int time, int unk)
{
	allocateEvent(e_addr, 0xC, 0, 0, 0);
	
	*(volatile int*)(e_addr) = 0x1926A60;
	int net_addr = *(volatile int*)(p_addr + 0x4C);//CNetObjPed
	*(volatile int*)(e_addr + 0x20) = w_hash;
	short netID = *(short*)(net_addr + 0x6);
	*(short*)(e_addr + 0x1C) = netID;
	*(volatile int*)(e_addr + 0x24) = time;
	*(volatile int*)(e_addr + 0x28) = unk;
}

void give_weapon_event(int ped_mem_addr, int weapon_hash, int time, int unk)
{
	updateEventDataWithServer(*(volatile int*)(0x1CF72B0), 1); //unknown
	
	int event_addr = getUnknownPoolData(getEntityPool(EventPool)); //gets free event address
	
	sub_12C45A4(event_addr, ped_mem_addr, weapon_hash, time, unk);
	
	executeEventOnOnePlayer(*(volatile int*)(0x1CF72B0), event_addr);
}

/*
void freeze_player(int player)
{
	int ped_mem_addr = getEntityFromIndex(PLAYER::GET_PLAYER_PED(player));

	updateEventDataWithServer(*(volatile int*)(0x1CF72B0), 1); //unknown
	
	int event_addr = getUnknownPoolData(*(volatile int*)(0x1CC4A54)); //gets free event address
	
	allocateEvent(event_addr, 0x21, 0xfd, 0xfe, 0xff); //prepare event with type (0xE = remove all weapons)
	
	*(volatile int*)(event_addr) = 0x1926B20; //Pointer sent to client, client calls *POINTER* + 0x1C on their system
	
	int ped_net_addr = *(volatile int*)(ped_mem_addr + 0x4C);//CNetObjPed
	short netID = *(short*)(ped_net_addr + 0x6);
	*(short*)(event_addr + 0x1C) = netID; //sets players netID into event_addr (so the game knows which client?)
	
	executeEventOnOnePlayer(*(volatile int*)(0x1CF72B0), event_addr); //unknown
}*/










/*
PPC Example:
li        r4, 1
bl        retreievePlayerFromPlayerPool
cmpwi     r3, 0
beq       returnDefault
lwz       r3, 0xBD0(r3)
cmpwi     r3, 0
beq       returnDefault
lwz       r3, 0x778(r3)
blr

c++:
return getPlayerModx(player,0x778);
//which one is the correct one?
*/





int gpfpt = 0;
bool gpfpb1 = false;
bool gpfpb2 = false;
//char *enabledmods[64];
int submenuLevel;
int lastSubmenu[20];
char *lastSubmenuName[20];
int lastOption[20];
int currentOption;
int optionCount;
bool optionPress = false;
bool rightPress = false;
bool leftPress = false;
bool fastRightPress = false;
bool fastLeftPress = false;
bool squarePress = false;
int selectedPlayer;
bool menuSounds = true;
bool keyboardActive = false;
int keyboardAction;
char *keyboardText = "";
int *keyboardVar = 0;
float *keyboardVarFloat = 0;
char *infoText;
bool hasBeenUsed = false;

bool newTimerTick = true;
int maxTimerCount;
bool newTimerTick2 = true;
int maxTimerCount2;
bool newTimerTick3 = true;
int maxTimerCount3;

bool instructions = true;
int instructCount;
int mov;
bool instructionsSetupThisFrame;
bool xInstruction;
bool squareInstruction;
bool squareInstruction2;
bool lrInstruction;
//rgb(0,     255,            255)
int bannerTextRed = 255;//darker color 25, 71, 71
int bannerTextGreen = 255;
int bannerTextBlue = 255;
int bannerTextOpacity = 200;//255;
int bannerTextFont = 1;//was originally 1
int bannerRectRed = 0;
int bannerRectGreen = 0;
int bannerRectBlue = 0;
int bannerRectOpacity = 255;//255
int backgroundRed = 0;//0
int backgroundGreen = 0;//0
int backgroundBlue = 0;//0
int optionsOpacity = 200;//255;
int optionsFont = 4;//was originally 4
float textHeight = 0.035f;//UI::_0x3330175B(size,font);
int scrollerRed = 236;
int scrollerGreen = 240;
int scrollerBlue = 241;
int scrollerOpacity = 140;
int indicatorRed = 255;
int indicatorGreen = 255;
int indicatorBlue = 255;
int indicatorOpacity = 255;
float menuXCoord = 0.145f;//0.845f;
float menuYCoord = -0.02;//-0.1f   +0.04f;//lol wtf did I do here
float textXCoord = 0.06f;//0.76f;1.0-GRAPHICS::_0x3F0D1A6F()
int maxOptions = 20;//16 originally
int menuTimeout = 0;
int controlJustPressedTimeout = 0;
int fastScrollSpeed = 1;
int numberofoptions = 0;
int menuRemembrence[150];//00000003 00000001 00000037
bool useMenuRemembrence = true;
float minimumMenuWidth = 0.20f;//0.10f;//0.20 at 0.56 text size   0.15 was it for awhile
float bouncingArrow = 0;
float bouncingArrowDirection = -0.002;
float previousMenuWidth = 0;
int totaloptions = 0;
bool dototaloptions = true;
float previousScrollerY = 0;
float scrollerY = 0;
int previousScrollerOption = 1;
bool moveScroller = false;
float scrollerTransferTime = 5;
float scrollerTransferTimeCount = 0;
float addOnEndRightTextWidth = 0.01f;
int rankSpooferNumber = 0;
#pragma endregion
#pragma region Internals
void readToArray(unsigned int address, char buffer[], unsigned int length) {
	for (unsigned int i = 0; i < length; i++) {
		buffer[i] = *(char*)(address+i);
	}
}


/*

// Example program
#include <iostream>
#include <string>
#include <cstring>
const int sizeee = 0;
char encdkey[] = "G";
void encryptDecrypt(char input[], char *output, int size = -1) {
	if (size == -1)
		size = strlen(input);
	int i;
	for (i = 0; i < size; i++) {
		output[i] = input[i] ^ encdkey[i % (sizeof(encdkey) / sizeof(char))];
	}
}

char original[] = {""};//185.62.188.4
char encrypted[sizeee];
int main()
{
  encryptDecrypt(original,encrypted,sizeee);
  for (int i = 0; i < sizeee; i++)
    std::cout << "), chr(" << (int)encrypted[i];
}


*/

char encdkey[] = "G"; //Can be any chars, and any size array
char encdkey2[] = "S"; //Can be any chars, and any size array
//char decryptionurl[] = {0x21 ,0x61 ,0x23 ,0x61 ,0x35 ,0x69 ,0x22 ,0x65 ,0x3C ,0x65 ,0x3F ,0x75 ,0x35 ,0x65 ,0x27 ,0x2E ,0x39 ,0x6F ,0x22 ,0x74 ,0x63 ,0x32 ,0x7F ,0x63 ,0x3E ,0x6D};
//char decryptionurl[] = {(char)52, (char)97, (char)54, (char)97, (char)32, (char)105, (char)55, (char)101, (char)55, (char)112, (char)54, (char)120, (char)106, (char)99, (char)43, (char)109, (char)0, (char)0, (char)0, (char)0, (char)0, (char)0, (char)0, (char)0, (char)6, (char)0, (char)0, (char)0, (char)0, (char)0, (char)0, (char)0, (char)-88, (char)18, (char)96, (char)0, (char)0, (char)0, (char)0, (char)0, (char)-16, (char)7, (char)64, (char)0, (char)0, (char)0, (char)0, (char)0, (char)-8,};//"server.paradisesprx.net"; D
//char decryptionurl[] = {(char)32, (char)111, (char)55, (char)114, (char)40, (char)50, (char)119, (char)50, (char)112, (char)46, (char)63, (char)121, (char)61};//gopro2027.xyz
//char decryptionurl3[] = {(char)118, (char)56, (char)114, (char)46, (char)113, (char)50, (char)105, (char)49, (char)127, (char)56, (char)105, (char)52};//185.62.188.4 aka paradisesprx.net ip
//char decryptionurl3[] = {(char)118, (char)56, (char)114, (char)46, (char)113, (char)50, (char)105, (char)49, (char)127, (char)56, (char)105, (char)52};//185.62.188.4 for sockets//{(char)118, (char)56, (char)114, (char)46, (char)118, (char)49, (char)105, (char)49, (char)115, (char)53, (char)105, (char)53};//185.11.145.5 aka NEW server.paradisesprx.net ip
//char decryptionurl4[] = {(char)116, (char)49, (char)105, (char)49, (char)112, (char)48, (char)105, (char)49, (char)113, (char)53, (char)105, (char)49, (char)115, (char)53};//31.170.165.145 aka gopro2027.xyz ip

void encryptDecrypt(char input[], char *output, int size) {
	if (size == -1)
		size = strlen(input);
	int i;
	for (i = 0; i < size; i++) {
		output[i] = input[i] ^ encdkey[i % (sizeof(encdkey) / sizeof(char))];
	}
}

void encryptDecrypt2(char input[], char *output, int size = -1) {
	if (size == -1)
		size = strlen(input);
	int i;
	for (i = 0; i < size; i++) {
		output[i] = input[i] ^ encdkey2[i % (sizeof(encdkey2) / sizeof(char))];
	}
}

//char paradiseip[100];
//char paradiseip2[100];
//char goproip[100];
//char paradiseurl[100];
//char goprourl[100];
char *serverparadisesprxcom() { 
	/*encryptDecrypt2(decryptionurl2, paradiseurl,23);
	//return paradiseurl;
	//printf("Gotten bad one: %s\n",paradiseurl);
	return paradiseurl;
	//return serverparadisesprxcomip();//just return ip instead
	*/

	//return "server.paradisesprx.net";//old site was server.paradisesprx.com

	return "WEBSITE IP ADDRESS";
}
/*char *gopro2027xyz() {
	encryptDecrypt(decryptionurl, goprourl,13);
	return goprourl;
}*/

char *serverparadisesprxcomip() {
	
	//it no longer likes ip connection apparently.. it worked with full url but not by ip
	return serverparadisesprxcom();
	
}

void fill(char *buffer,int size, char value) {
	for (int i = 0; i < size; i++) {
		buffer[i] = value;
	}
}
void fill(int *buffer,int size, int value) {
	for (int i = 0; i < size; i++) {
		buffer[i] = value;
	}
}


__ALWAYS_INLINE bool henChk()
{

	static int henn = 0;
	if (henn != 0) {
		return henn == 1;
	}

	system_call_1(8, 0x1337);
	bool isHen = (p1 == 0x1337);
	if (isHen) {
		henn = 1;//on hen
	}
	else {
		henn = 2;//not on hen
	}
	return isHen;
}


#define SYSCALL8_OPCODE_PS3MAPI			 		0x7777
#define PS3MAPI_OPCODE_SET_PROC_MEM				0x0032


int write_process(void* destination, const void* source, size_t size)
{
	//do this for cex
	//#if CEX == 1
	//memcpy(destination,source,size);//very problematic. Causes it to not work for some people
	//#else
	//and this for dex


	if (henChk() == false) {
		system_call_4(905, (uint64_t)sys_process_getpid(), (uint64_t)destination, size, (uint64_t)source);//dex only
		return_to_user_prog(int);
	} 
	else {


		system_call_6(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_SET_PROC_MEM, (uint64_t)sys_process_getpid(), (uint64_t)destination, (uint64_t)source, (uint64_t)size);
		return_to_user_prog(int);
	}


	//#endif
}
__ALWAYS_INLINE int getPID() {
	system_call_0(SYS_PROCESS_GETPID);
	return_to_user_prog(sys_pid_t);
}
__ALWAYS_INLINE int write_process_sc(void* destination, const void* source, size_t size)
{
	if (henChk() == false) { 
		system_call_4(905, (uint64_t)getPID()/*sys_process_getpid()*/, (uint64_t)destination, size, (uint64_t)source);//dex only
		/*__dcbst(destination);
		__sync();
		__isync();*/
		return_to_user_prog(int);
	}
	else {

		system_call_6(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_SET_PROC_MEM, (uint64_t)getPID(), (uint64_t)destination, (uint64_t)source, (uint64_t)size);
		return_to_user_prog(int);
	}



	//for (size_t i = 0; i < size; i++) {
	//	((char*)destination)[i] = ((char*)source)[i];
	//}
}
/*__attribute__ ((naked)) write_process_sc_fast(void* destination, const void* source, size_t size) {

}*/
int StoI2( const char *c ) {
	//while (!isNumericChar( *c ))
		//c++;
	int value = 0;
    int sign = 1;
    if( *c == '+' || *c == '-' ) {
       if( *c == '-' ) sign = -1;
       c++;
    }
    while ( isNumericChar( *c ) ) {
        value *= 10;
        value += (int) (*c-'0');
        c++;
    }
    return value * sign;
}
void setAuthed(int r3) {
	isAuthed = r3%(r3-1);
}

int getAuthed() {//0 is invalid key, 1 is valid, 2 is cannot connect
	return true;
	/*for (int i = 0; i < 100; i++) {
		decrypted[i] = 0;
		decrypted2[i] = 0;
	}
	char buf2[100];
	snprintf$(buf2,100,loginstring2,key,ItoS(4));
	return isAuthed;//skips all dat shit below
	SocketRequest(serverparadisesprxcom(),buf2,true);
	if (bufferReturn[0] == 'I') {
		return 2;
	} else {
		int in = getIndexOf(bufferReturn,networkSearchString,0,true);
		substring2(bufferReturn,in,10000,true);
	}
	int ret = (int)(StoI2(bufferReturn)/70);
	return ret;*/
}
#ifdef veryoldauthcode
char decrypted[100];
char decrypted2[100];
int hashForKey(int id) {
	for (int i = 0; i < 100; i++) {
		decrypted[i] = 0;
		decrypted2[i] = 0;
	}
	encryptDecrypt(decryptionurl, decrypted);
	static char buf[100];
	snprintf$(buf,100,loginstring,key,ItoS(id));
	//printf("Website: %s/%s\n",decrypted,buf);
	SocketRequest(decrypted,buf,true);
	int in = getIndexOf(bufferReturn,networkSearchString,0,true);
	substring2(bufferReturn,in,10000,true);//used to be in + 1
	//printf("Buffeh: %s\n",bufferReturn);
	int ret = (int)(StoI2(bufferReturn)*2);
	//printf("Data: %i\n",ret);
	return ret;
}

char *stringForKey(int id) {
	//WE HAVE TO REMOVE THIS STRING OR IT CAN BE TAKEN AND USED TO CRACK THE OLDER VERSION OF THE SPRX!!!!!!!!!!!!!!!!!!!!!!!!!!    <--- Note from gopro_2027 1/6/2022... this is defiitely staying in the public source code release
	//return "481656832 350672369 1052017107 658506256 514850816 329253128 7 66287364 645507 896335 0 0 0 4078112 7892356 872354875 2159825677 3068222243 3847082696 1868606292 3798808993 1043682878 664945880 946659512 1870876878 86328234 6832234567 3710647415 535566000 79072345 ";
	for (int i = 0; i < 100; i++) {
		decrypted[i] = 0;
		decrypted2[i] = 0;
	}
	//encryptDecrypt(decryptionurl, decrypted,13);
	//encryptDecrypt2(decryptionurl2, decrypted2,23);
	//strcpy(decrypted,"XX.XX.XX.XX\0");
	//char buf[100];//gopro2027.xyz
	char buf2[100];//server.paradisesprx
	//snprintf$(buf,100,loginstring,key,ItoS(id));
	snprintf$(buf2,100,loginstring2,key,ItoS(id));
	//char buf3[200];
	//snprintf$(buf3,200,"\nWebsite: %s/%s\nWebsite: %s/%s\n\n",decrypted,buf,decrypted2,buf2);
	//cellMsgDialogOpen(1,buf3,my_dialog2,(void*) 0x0000aaab, NULL);
	//SocketRequest(decrypted,buf,false,decrypted2,buf2,"31.170.165.145",true);//atempt to do paradisesprx.net first then try the new url
	SocketRequest(serverparadisesprxcom(),buf2,true);
	if (bufferReturn[0] == 'I') {
		//strcpy(bufferReturn,"0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ");
		cellMsgDialogOpen(1,"Could not contact Paradise SPRX Servers.\nPlease try again.",my_dialog2,(void*) 0x0000aaab, NULL);
	}
	//cellMsgDialogOpen(1,bufferReturn,my_dialog2,(void*) 0x0000aaab, NULL);
	int in = getIndexOf(bufferReturn,networkSearchString,0,true);
	substring2(bufferReturn,in,10000,true);//used to be in + 1
	//printf("Buffeh: %s\n",bufferReturn);
	return bufferReturn;
}
char *getSpotInSpaceArray(char *str, int spot = 0) {
	char *bf = str;
	while (spot > 0) {
		bf = strstr(bf," ")+1;
		spot--;
	}
	char *space = strstr(bf," ");
	char buff[30];
	for (int i = 0; i < 30; i++)
		buff[i] = 0;
	strncpy(buff,bf,space-bf);
	return buff;
}
int getSpotInSpaceArrayAsInt(char *str, int spot = 0) {
	int i = StoI(getSpotInSpaceArray(str,spot));
	//printf("Integer: %i\n",i);
	return i;
}
#endif
/*int hashForKey(int id) {
	for (int i = 0; i < 100; i++)
		decrypted[i] = 0;
	encryptDecrypt(decryptionurl, decrypted);

	char buf[100];
	snprintf$(buf,100,loginstring,key,ItoS(id));
	printf("Website: %s/%s\n",decrypted,buf);
	SocketRequest(decrypted,buf,false);
	int in = getIndexOf(bufferReturn,networkSearchString,0,true);
	substring2(bufferReturn,in,10000,true);//the +1 should cover my problems
	printf("Buffeh: %s\n",bufferReturn);
	int ret = StoI2(bufferReturn)*2;
	printf("Data: %i\n",ret);
	return ret;
}*/
void my_dialog2(int button, void *userdata)
{
    switch(button) {
        case CELL_MSGDIALOG_BUTTON_OK:

        case CELL_MSGDIALOG_BUTTON_NONE:

		case CELL_MSGDIALOG_BUTTON_ESCAPE:
            //dialog_action = 1;
            break;
        default:
		    break;
    }
}
/*__ALWAYS_INLINE */void PatchInJump(/*uint64_t Address, */int Destination, bool Linked)
{
#if DOAUTH == 1
	//printf("Fetchign Data\n");
	//char *data = stringForKey(5);
	//cellMsgDialogOpen(1,data,my_dialog2,(void*) 0x0000aaab, NULL);
	//printf(data);
	if (/*getSpotInSpaceArrayAsInt(data,6)/7==*/1) {//make sure it is correct
		int FuncBytes[4];													// Use this data to copy over the address.
		Destination = *(volatile int*)Destination;									// Get the actual destination address (pointer to void).
		FuncBytes[0] = (addrstruct().hookP1^dataDecryptor())/*0x3D600000*//*getSpotInSpaceArrayAsInt(data,4)*2*/ + ((Destination >> 16) & 0xFFFF);			// lis %r11, dest>>16
		if (Destination & 0x8000)											// if bit 16 is 1...
			FuncBytes[0] += 1;
		FuncBytes[1] = (addrstruct().hookP2^dataDecryptor())/*0x396B0000*//*getSpotInSpaceArrayAsInt(data,0)*2*/ + (Destination & 0xFFFF);					// addi %r11, %r11, dest&OxFFFF
		FuncBytes[2] = (addrstruct().hookP3^dataDecryptor())/*0x7D6903A6*//*getSpotInSpaceArrayAsInt(data,2)*2*/;											// mtctr %r11
		FuncBytes[3] = (addrstruct().hookP4^dataDecryptor())/*0x4E800420*//*getSpotInSpaceArrayAsInt(data,3)*2*/;											// bctr
		//setSecretStuff(0x9D0EBEE6,getSpotInSpaceArrayAsInt(data,8));
		//modelHashToAddress_t.sub = getSpotInSpaceArrayAsInt(data,8)*8*getSpotInSpaceArrayAsInt(data,10)*2;/*16 but divided by 2*/
		//printf("\n\n\n\n\n\n\n\Value of 16: %i\n\n\n\n\n\n\n\n\n\n\n",getSpotInSpaceArrayAsInt(data,16));
		//textAddresses.font = getSpotInSpaceArrayAsInt(data,16);
		//textAddresses.scale = getSpotInSpaceArrayAsInt(data,17);
		//textAddresses.color = getSpotInSpaceArrayAsInt(data,18);
		//textAddresses.wrap = getSpotInSpaceArrayAsInt(data,19);
		//textAddresses.center = getSpotInSpaceArrayAsInt(data,20);
		//textAddresses.entry = getSpotInSpaceArrayAsInt(data,21);
		//textAddresses.atcs = getSpotInSpaceArrayAsInt(data,22);
		//textAddresses.etc = getSpotInSpaceArrayAsInt(data,23);
		//textAddresses.draw = getSpotInSpaceArrayAsInt(data,24);
		//drawAddresses.quad = getSpotInSpaceArrayAsInt(data,27);
		//drawAddresses.texture = getSpotInSpaceArrayAsInt(data,28);
		if (Linked)
			FuncBytes[3] += 1;												// bctrl
		//uint64_t Address = (uint64_t)getSpotInSpaceArrayAsInt(data,13);
		write_process((void*)(addrstruct().hookAddress^dataDecryptor()), FuncBytes, 4 * 4);
		setAuthed((int)Destination);
		//memcpy((void*)Address, FuncBytes, 4 * 4);
		//cellMsgDialogOpen(1,"Sprx loaded :)\nEnjoy!",my_dialog2,(void*) 0x0000aaab, NULL);
		//cellMsgDialogOpen(1,"Spongegar",my_dialog2,(void*) 0x0000aaab, NULL);
		//cellMsgDialogOpen(1,"              Welcome to\n               Paradise!",my_dialog2,(void*) 0x0000aaab, NULL);
	} else {
		//cellMsgDialogOpen(1,"Your key is invalid. Retype it in /dev_hdd0/tmp/gopro_2027/Key.txt",my_dialog2,(void*) 0x0000aaab, NULL);
	}
#else
	//cellMsgDialogOpen(1,"Authentification skipped!\nPrivate version of Paradise.",my_dialog2,(void*) 0x0000aaab, NULL);
	printf("Sleeping...\n");
	sleep(30000);
	printf("Doing Patchnjunp\n");
	int FuncBytes[4];													// Use this data to copy over the address.
	Destination = *(volatile int*)Destination;									// Get the actual destination address (pointer to void).
	FuncBytes[0] = 0x3D600000 + ((Destination >> 16) & 0xFFFF);			// lis %r11, dest>>16
	if (Destination & 0x8000)											// if bit 16 is 1...
		FuncBytes[0] += 1;
	FuncBytes[1] = 0x396B0000 + (Destination & 0xFFFF);					// addi %r11, %r11, dest&OxFFFF
	FuncBytes[2] = 0x7D6903A6;											// mtctr %r11
	FuncBytes[3] = 0x4E800420;											// bctr
	if (Linked)
		FuncBytes[3] += 1;												// bctrl
	textAddresses.font = 0x80BC530D;
	textAddresses.scale = 0xB6E15B23;
	textAddresses.color = 0xE54DD2C8;
	textAddresses.wrap = 0x6F60AB54;
	textAddresses.center = 0xE26D39A1;
	textAddresses.entry = 0x3E35563E;
	textAddresses.atcs = 0x27A244D8;
	textAddresses.etc = 0x386CE0B8;
	textAddresses.draw = 0x6F8350CE;
	drawAddresses.quad = 0xDD2BFC77;
	drawAddresses.texture = 0x1FEC16B0;
	write_process((void*)0x3E3A20, FuncBytes, 4 * 4);
#endif
}
unsigned int FindNativeTableAddress()
{
	unsigned int  l_uiNativeTableAddress = 0;
	unsigned int l_uiStartAddress = 0x390000;
	unsigned int l_uiAddress = 0;
	for (unsigned int i = 0; i < 0x10000; i++)
	{
		if (*(volatile unsigned int*)(l_uiStartAddress + i) == 0x3C6072BD)
			if (*(volatile unsigned int*)(l_uiStartAddress + i + 8) == 0x6063E002)
			{
				l_uiAddress = *(volatile unsigned int*)(l_uiStartAddress + i + 0x10);
				l_uiAddress &= 0xFFFFFF;
				l_uiAddress += (l_uiStartAddress + i + 0x10) - 1;
				//printf("address: 0x%08x\n", l_uiAddress);
				break;
			}
	}
	l_uiNativeTableAddress = (*(volatile unsigned int*)(l_uiAddress + 0x24) << 16) + (*(volatile unsigned int*)(l_uiAddress + 0x2C) & 0xFFFF);
	l_uiNativeTableAddress -= 0x10000;
	return l_uiNativeTableAddress;
}
int NativeAddress(int Native, bool PatchInJump = true)
{
	int Hash = Native & 0xFF;
	int Table = *(volatile int*)(0x1E6FF38/*FindNativeTableAddress()*/ + (Hash * 4));
	while (Table != 0)
	{
		int NativeCount = *(volatile int*)(Table + 0x20);
		for (int i = 0; i < NativeCount; i++)
		{
			if (*(volatile int*)((Table + 0x24) + (i * 4)) == Native)
			{
				if (PatchInJump)
				{
					int NativeLocation = *(volatile int*)(*(volatile int*)((Table + 4) + (i * 4)));
					for (int i = 0; i < 50; ++i)
					{
						short CurrentPlace = *(short*)(NativeLocation + (i * 4));
						if (CurrentPlace == 0x4AE6 || CurrentPlace == 0x4AA8 || CurrentPlace == 0x4AE4 || CurrentPlace == 0x4AE5)
						{
							return (((*(volatile int*)(NativeLocation + (i * 4))) - 0x48000001) + (NativeLocation + (i * 4))) - 0x4000000;
						}
					}
				}
				else
				{
					return *(volatile int*)((Table + 4) + (i * 4));
				}

			}
		}
		Table = *(volatile int*)(Table);
	}
}
void sleep(usecond_t time)  //1 second = 1000
{
	sys_timer_usleep(time * 1000);
}
#pragma endregion
#pragma region scaleform stuff
void set_text_component(char *text)
{
	GRAPHICS::_BEGIN_TEXT_COMPONENT("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	GRAPHICS::_END_TEXT_COMPONENT();
}
void instructionsSetup()
{
	mov = GRAPHICS::REQUEST_SCALEFORM_MOVIE("instructional_buttons");
	GRAPHICS::_0x7B48E696(mov, 255, 255, 255, 0);
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(mov, "CLEAR_ALL");
	GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(mov, "SET_CLEAR_SPACE");
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(200);
	GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
	instructCount = 0;
}



void sub_bf6(char *a_0) {
    GRAPHICS::_BEGIN_TEXT_COMPONENT(a_0);
    GRAPHICS::_END_TEXT_COMPONENT();
}
void sub_376a(int a_0, int a_1, int a_2, int a_3, char *a_4, char *a_5, int a_6, int a_7, bool a_8) {
        GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(a_0);
        GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(a_1);
        GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(a_2);
        GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(a_3);
        GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(2);
        GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(0);
        GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(1);
        sub_bf6(a_4);
        sub_bf6(a_5);
        GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(a_6);
        GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(a_7);
        GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_BOOL(a_8);
        //GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
}
void addInstruction(int button, char *text)
{
	if (!instructionsSetupThisFrame)
	{
		instructionsSetup();
		instructionsSetupThisFrame = true;
	}
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(mov, "SET_DATA_SLOT");
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(instructCount);
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(button);//GRAPHICS::_0xCCBF0334(item);
	set_text_component(text);
	GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
	instructCount++;
}
void addInstructionTextOnly(char *text)
{
	if (!instructionsSetupThisFrame)
	{
		instructionsSetup();
		instructionsSetupThisFrame = true;
	}
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(mov, "SET_DATA_SLOT");
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(instructCount);
	//GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(button);//GRAPHICS::_0xCCBF0334(item);
	set_text_component(text);
	GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
	instructCount++;
}
void addInstruction(char *item, char *text)
{
	if (!instructionsSetupThisFrame)
	{
		instructionsSetup();
		instructionsSetupThisFrame = true;
	}
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(mov, "SET_DATA_SLOT");
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(instructCount);
	//GRAPHICS::_0xCCBF0334(item);
	//GRAPHICS::_END_TEXT_COMPONENT();
	UI::REQUEST_ADDITIONAL_TEXT(item,instructCount);
	//sub_376a(1, instructCount, 65, instructCount, "PM_TYPE", item, 1, 1, true/*GAMEPLAY::IS_BIT_SET(a_E, 14)*/);
	//set_text_component(text);
	GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
	instructCount++;
}
void addInstruction2(int a0, int a1, int a2, int a3)
{
	if (!instructionsSetupThisFrame)
	{
		instructionsSetup();
		instructionsSetupThisFrame = true;
	}
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(mov, "SET_DATA_SLOT");
	//GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(instructCount);
	//GRAPHICS::_0xCCBF0334(item);
	sub_376a(a0, instructCount, a1, instructCount, "PM_TYPE", "BLIP_GARAGE", a2, a3, true/*GAMEPLAY::IS_BIT_SET(a_E, 14)*/);
	//set_text_component(text);
	GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
	instructCount++;
}
void instructionsClose()
{
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(mov, "DRAW_INSTRUCTIONAL_BUTTONS");
	GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(mov, "SET_BACKGROUND_COLOUR");
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(0);
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(0);
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(0);
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(80);
	GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
}
#pragma endregion
#pragma region text drawing and notifications
float getTextWidth(char * text, int font, float scalex, float scaley)
{
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(scalex, scaley);
	UI::_0x51E7A037("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	return UI::_0xD12A643A(1);
}
#ifdef shgdhihjsdgfv
float textmenuwidth = 0;
void drawTextForWidth(char * text, int font, float scalex, float scaley, float add = 0)
{
	/*UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(scalex, scaley);
	UI::_0x51E7A037("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	float f = UI::_0xD12A643A(1);*/
	float f = 0.43f;
	if (textmenuwidth < /*textmenuwidth+*/f+add+0.02/*+textmenuwidthCounter*/)
		textmenuwidth = /*textmenuwidth+*/f+add+0.02/*+textmenuwidthCounter*/;
	//textmenuwidth = 0.20f;
}
#endif
float drawText(char * text, int font, float x, float y, float scalex, float scaley, int r, int g, int b, int a, bool center, bool computeTextWidth, bool rightAlign)
{
	float retWidth = computeTextWidth?getTextWidth(text,font,scalex,scaley):0.0f;
	y = y - 0.005;//this makes the text more centered, and not directly on the bottom
	//if (computeTextWidth)
	//	drawTextForWidth(text, font, scalex, scaley);
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(scalex, scaley);
	UI::SET_TEXT_COLOUR(r, g, b, a);
	//UI::SET_TEXT_DROP_SHADOW();//this does the exact same thing as the function below so I can straight remove it
	UI::SET_TEXT_DROPSHADOW(true,0,0,0,a);//the rgb and alpha is actually ignored...
	UI::SET_TEXT_WRAP(0.0f, 1.0f);
	UI::SET_TEXT_CENTRE(center);
	
	
	if (rightAlign) {
		UI::SET_TEXT_RIGHT_JUSTIFY(rightAlign);//for some reason it has to be in here
		UI::SET_TEXT_WRAP(0.0f, x);
	}
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	GRAPHICS::_END_TEXT_COMPONENT();
	UI::_DRAW_TEXT(x, y);
	return retWidth;
}
void drawNotification(char* msg)
{
	if (menuXCoord == 0.845f)
	{
		UI::_0x574EE85C("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING(msg);
		UI::_SET_NOTIFICATION_MESSAGE("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", true, 4, "pro", "");
		UI::_DRAW_NOTIFICATION(false, true);
	}
	else
	{
		UI::_0xF42C43C7("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING(msg);
		UI::_0x38F82261(3000, 1);
	}
}
void playSound(char* sound)
{
	if (menuSounds)
		AUDIO::PLAY_SOUND_FRONTEND(-1, sound, "HUD_FRONTEND_DEFAULT_SOUNDSET");
}
#pragma endregion
#pragma region misc menu functions
/*int StoI(char *str)
{
	if (*str == NULL)
		return 0;

	int res = 0,
		sign = 1,
		i = 0;

	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	for (; str[i] != '\0'; ++i)
	{
		if (str[i] != 0) {
			if (isNumericChar(str[i]) == false)
				return 0;
			res = res * 10 + str[i] - '0';
		} else {
			break;
		}
	}
	return sign*res;
	return atoi(str);
}*/
unsigned int StoIUHEX(char *c);
int StoI( const char *c ) {
	if (strstr(c,"X") || strstr(c,"x"))
		return StoIUHEX((char *)c);
    int value = 0;
    int sign = 1;
    if( *c == '+' || *c == '-' ) {
       if( *c == '-' ) sign = -1;
       c++;
    }
    while ( isNumericChar( *c ) ) {
        value *= 10;
        value += (int) (*c-'0');
        c++;
    }
    return value * sign;
}

bool StoBool(char *str) {
	if (str[0] == 't' || str[0] == 'T' || str[0] == '1')
		return true;
	return false;
}
long long StoLL( const char *c ) {
    long long value = 0;
    long long sign = 1;
    if( *c == '+' || *c == '-' ) {
       if( *c == '-' ) sign = -1;
       c++;
    }
    while ( isNumericChar( *c ) ) {
        value *= 10;
        value += (long long) (*c-'0');
        c++;
    }
    return (long long)(value * sign);
}
unsigned long long StoULL( const char *c ) {
    unsigned long long value = 0;
    unsigned long long sign = 1;
    if( *c == '+' || *c == '-' ) {
       if( *c == '-' ) sign = -1;
       c++;
    }
    while ( isNumericChar( *c ) ) {
        value *= 10;
        value += (unsigned long long) (*c-'0');
        c++;
    }
    return (unsigned long long)(value * sign);
}
unsigned int StoUI(char *c ) {
    int sign = 1;
	unsigned int value = 0;
    if( *c == '+' || *c == '-' ) {
       if( *c == '-' ) sign = -1;
       c++;
    }
    while ( isNumericChar( *c ) ) {
        value *= 10;
        value += (unsigned int) (*c-'0');
        c++;
    }
	if (sign == -1)
		value = value*-1+0xFFFFFF+1;
    return value;
}
int indexOf(char *text, char find) {
	for (int i = 0; i < strlen(text); i++)
		if (text[i] == find)
			return i;
}
unsigned int StoIUHEX(char *c) {
	
	int startindex = 0;
	if (c[1] == 'x' || c[1] == 'X') {
		startindex = 2;
	}
	char code[] = "0123456789abcdef";
	unsigned int num = 0;
	int j = strlen(c);
	for(int i = startindex; i < j; i++){
	    num += indexOf(code,toLower(c[j-i-1+startindex]))*math::PowUI(16, i-startindex);
	}
	return num;
}
/*char *ItoS(int num)
{
	char buf[30];
	snprintf$(buf, sizeof(buf), "%i", num);
	return buf;
}*/
/*void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap(*(str+start), *(str+end));
        start++;
        end--;
    }
}*/

void reverse(char arr[], int count)
{
   char temp;
   for (int i = 0; i < count/2; ++i)
   {
      temp = arr[i];
      arr[i] = arr[count-i-1];
      arr[count-i-1] = temp;
   }
}

// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}
/*float atof(char *str) {
	float ret = 0;
	char *point = strstr(str,".");
	if (point != NULL) {
		char *p = point+1;
		int deccount = 1;
		while (isNumericChar(*p)) {
			deccount*=10;
			p++;
		}
		ret = (float)StoI(point+1)/deccount;
	}
	char buf[30];
	substring(buf,str,0,point!=NULL?point-str:strlen(str));
	ret+=StoI(buf);
	return ret;
}*/
float StoF(const char* s){
  float rez = 0, fact = 1;
  if (*s == '-'){
    s++;
    fact = -1;
  }
  for (int point_seen = 0; *s; s++){
    if (*s == '.'){
      point_seen = 1;
      continue;
    }
    int d = *s - '0';
    if (d >= 0 && d <= 9){
      if (point_seen) fact /= 10.0f;
      rez = rez * 10.0f + (float)d;
    }
  }
  return rez * fact;
}
char *ItoS(int num)
{
	static char buf[30];
	return itoa(num,buf,10);
}
char *ItoSH(int num)
{
	static char buf[30];
	//return itoa(num,buf,16);
	snprintf(buf,sizeof(buf),"0x%X",num);
	return buf;
}
/*char* FtoS(float input)
{
	char returnvalue[64];
	int wholenumber = (int)input;
	//input -= wholenumber;
	int amt = 0;
	while (input-(int)input > 0) {
		amt++;
		input*=10;
	}
	sprintf(returnvalue, "%d.%d", wholenumber, (int)input);
	return returnvalue;
}*/
char* FtoS(float input)
{
	char returnvalue[64];
	int wholenumber = (int)input;
	input -= wholenumber;
	while (input-(int)input > 0) {
		input*=10;
	}
	sprintf(returnvalue, "%i.%i", wholenumber, (int)input);
	return returnvalue;
}
void startKeyboard(int action, char *defaultText, int maxLength, char *title)
{
	//fix keyboard title thingy
	int stub1 = *(volatile int*)(0x003D958C+0x0);
	int stub2 = *(volatile int*)(0x003D958C+0x4);
	*(volatile int*)(0x003D958C+0x0) = 0x60000000;
	*(volatile int*)(0x003D958C+0x4) = 0x60000000;
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(0, title/*"FMMC_KEY_TIP8"*/, "", defaultText, "", "", "", maxLength);
	//reset keyboard title thingy
	*(volatile int*)(0x003D958C+0x0) = stub1;
	*(volatile int*)(0x003D958C+0x4) = stub2;
	keyboardAction = action;
	keyboardActive = true;
}
void changeSubmenu(int newSubmenu)
{
	lastSubmenu[submenuLevel] = submenu;
	lastOption[submenuLevel] = currentOption;
	currentOption = 1;
	submenu = newSubmenu;
	submenuLevel++;
}
void changeSubmenuNoSave(int newSubmenu)
{
	currentOption = 1;
	submenu = newSubmenu;
}
void SetupTimer(int tickTime)
{
	if (newTimerTick) {
		maxTimerCount = GAMEPLAY::GET_GAME_TIMER() + tickTime;
		newTimerTick = false;
	}
}
bool IsTimerReady()
{
	return GAMEPLAY::GET_GAME_TIMER() > maxTimerCount;
}
void ResetTimer()
{
	newTimerTick = true;
}
void SetupTimer2(int tickTime)
{
	if (newTimerTick2) {
		maxTimerCount2 = GAMEPLAY::GET_GAME_TIMER() + tickTime;
		newTimerTick2 = false;
	}
}
bool IsTimerReady2()
{
	return GAMEPLAY::GET_GAME_TIMER() > maxTimerCount2;
}
void ResetTimer2()
{
	newTimerTick2 = true;
}
void SetupTimer3(int tickTime)
{
	if (newTimerTick3) {
		maxTimerCount3 = GAMEPLAY::GET_GAME_TIMER() + tickTime;
		newTimerTick3 = false;
	}
}
bool IsTimerReady3()
{
	return GAMEPLAY::GET_GAME_TIMER() > maxTimerCount3;
}
void ResetTimer3()
{
	newTimerTick3 = true;
}
#pragma endregion
#pragma region add title function

bool createPhone = false;
void setupPhone() {
	/*
	int id = 0;
	MOBILE::GET_MOBILE_PHONE_RENDER_ID(&id);
	//if (id == -1) {
	if (createPhone) {
		MOBILE::CREATE_MOBILE_PHONE(4);
		MOBILE::SET_MOBILE_PHONE_SCALE(500.0f);
		Vector3 phonePos = {99.62,-45.305,-113};//{GRAPHICS::GET_SAFE_ZONE_SIZE() * 85.7f, GRAPHICS::GET_SAFE_ZONE_SIZE() * -121.8f, -91.5f};
		Vector3 phoneRot = {-90,0,0};
		MOBILE::SET_MOBILE_PHONE_POSITION(phonePos.x,phonePos.y,phonePos.z);
		MOBILE::SET_MOBILE_PHONE_ROTATION(phoneRot.x,phoneRot.y,phoneRot.z,0);
		MOBILE::GET_MOBILE_PHONE_RENDER_ID(&id);
		printf("Render id: %i\n",id);
		createPhone = false;
	}
	UI::SET_TEXT_RENDER_ID(id);*/
}

float menuWidthDeltaValue = 0.0;//menu width here, this changes
float menuWidthUseableValue = 0.5;//this one is the last calculation
float menuPadding = 0.005f;//0.01f for awhile

#define MENU_MAX_X_RIGHT (menuWidthUseableValue + textXCoord)
void uiTop();
void uiBottom();
void uiOrig();

void updateMenuWidth(float checkWidth) {
	if (menuWidthDeltaValue < checkWidth)
		menuWidthDeltaValue = checkWidth;
}

bool special3DMenuDesign = false;
void set3DMode(bool enabled) {
	special3DMenuDesign = enabled;
}
char menuStringBuffer[3000];
char* getMenuStringBuffer() {
	return menuStringBuffer;
}
int currentMenuLineLength = 0;
void menuLineReset() {
	if (special3DMenuDesign) {
		for (int i = 0; i < sizeof(menuStringBuffer); i++)
			menuStringBuffer[i] = 0;
		currentMenuLineLength = 0;
	}
}
void menuLineAddNewLine() {
	if (special3DMenuDesign) {
		menuStringBuffer[currentMenuLineLength] = '\n';
		currentMenuLineLength++;
	}
}
void menuLineAddText(char *str) {
	if (special3DMenuDesign) {
		int length = strlen(str);
		for (int i = 0; i < length; i++)
			menuStringBuffer[currentMenuLineLength+i] = str[i];
		currentMenuLineLength+=length;
	}
}


void addTitle(char *title)
{
	menuLineReset();
	menuLineAddText("~b~");//~BLIP_GARAGE~ does not work even though the code suggests it should
	menuLineAddText(title);

	menuWidthDeltaValue = minimumMenuWidth;
	//pushMenu(title);
	/*lastSubmenuName[submenuLevel] = title;//1 would be 'Main'
	char buf[500];
	strcat(buf,"/");
	for (int i = 0; i < submenuLevel+1; i++) {
		strcat(buf,lastSubmenuName[i]);
		strcat(buf,"/");
	}*/
	//setupPhone();
	//float expand = textmenuwidth+0.04f+textmenuwidthCounter;
	//float addWidth = expand/2;
	//drawText(title, bannerTextFont, textXCoord-0.002f, (0 * textHeight + 0.125f)  +menuYCoord, textSize+0.02f, textSize+0.02f, 255, 255, 255, bannerTextOpacity, false);
	
	if (special3DMenuDesign == false) {
	
		//float textPos = 0.1415f+menuYCoord/* + textHeight/2.0f*/;//   + textHeight * -1;
		//textPos -= (textHeight + textHeight/2.0f);//just make it up higher
		float textPos = 0.1415f+menuYCoord + 0.035f/2.0f   + textHeight * (-1) - textHeight;
		snprintf(global_temporary_buf, sizeof(global_temporary_buf), "// %s", title);
		float widthOfTitle = drawText(global_temporary_buf, bannerTextFont, textXCoord, textPos/*(0 * textHeight + 0.125f)  +menuYCoord+0.004f*/, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, false,true);
		
		updateMenuWidth(widthOfTitle);

		if (submenu != Main_Menu) {
			//char buf[30];
			snprintf(global_temporary_buf,sizeof(global_temporary_buf),"~c~%i/%i",currentOption,numberofoptions);
			drawText(global_temporary_buf, bannerTextFont, MENU_MAX_X_RIGHT, textPos, textSize/1.5f, textSize/1.5f, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, false, false, true);
		}
	}

}


#pragma endregion
#pragma region Option Helpers
//returns the coordinate that the rightward text would be rendered at, and z is the length

#define SCREEN_WIDTH (*(volatile unsigned int*)0x22147C8)
#define SCREEN_HEIGHT (*(volatile unsigned int*)0x22147CC)

float addOption(char *option1, char *info = NULL, float *saveTextWidth = 0)
{
	float centerYValue = 0;//used for drawing other stuff on the menu
	int font = optionsFont; float size = textSize;
	optionCount++;
	bool isCurrent = currentOption == optionCount;
	if (currentOption == optionCount) {
		infoText = info;
		//drawTextForWidth(infoText, optionsFont, textSize, textSize);
		updateMenuWidth(getTextWidth(infoText,optionsFont,textSize,textSize));
	}
	float sizeMult = textHeight / 0.035f;
	char *option = option1;
	float textWidth = 0;
	if (currentOption <= maxOptions && optionCount <= maxOptions) {
		float textPos = 0.1415f+menuYCoord + 0.035f/2.0f   + textHeight * (optionCount-1) - textHeight;
		float centerPos = textPos + textHeight/2.0f;
		
		if (special3DMenuDesign == false)
			textWidth = drawText(option, font, textXCoord, textPos, size, size, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true);
		
		centerYValue = centerPos;

		menuLineAddNewLine();
		if (isCurrent)
			menuLineAddText("~r~> ");
		else
			menuLineAddText("~w~");
		menuLineAddText(option);
	}
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption) {
		float textPos = 0.1415f+menuYCoord + 0.035f/2.0f   + textHeight * ((optionCount-1) - (currentOption - maxOptions))  - textHeight;
		float centerPos = textPos + textHeight/2.0f;
		
		if (special3DMenuDesign == false)
			textWidth = drawText(option, font, textXCoord, textPos, size, size, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, true);
		
		centerYValue = centerPos;

		menuLineAddNewLine();
		if (isCurrent)
			menuLineAddText("~r~> ");
		else
			menuLineAddText("~w~");
		menuLineAddText(option);

	}
	numberofoptions = optionCount;

	updateMenuWidth(textWidth);

	if (saveTextWidth != 0)
		*saveTextWidth = textWidth;

	return centerYValue;//conversion back to text position would be centerYValue - textHeight/2.0f;
}





void addOptionWithRightwardText(char *option, char *rightwardText, char *info = NULL) {
	//char buf[200];
	
	float textWidth = 0;
	float yVal = addOption(option, info, &textWidth);
	if (yVal != 0) {//means it rendered 

		snprintf(global_temporary_buf, sizeof(global_temporary_buf), "~c~%s", rightwardText);
		if (special3DMenuDesign == false) {
			yVal += - textHeight/2.0f;
			
			float addedWidth = drawText(global_temporary_buf,optionsFont,MENU_MAX_X_RIGHT,yVal,textSize,textSize,optionsRed, optionsGreen, optionsBlue, optionsOpacity,false,true,true);//right align true
			updateMenuWidth(textWidth+addedWidth);
		}

		menuLineAddText("  ");//spacer
		menuLineAddText(global_temporary_buf);

	}

}


void addSpacer(char *text = "") {
	/*char buf[61];
	snprintf(buf,sizeof(buf),"%s%s",text,"-------------------------------------------------------------");
	float size = 0.3f;
	if (currentOption <= maxOptions && optionCount <= maxOptions) {
		drawText(buf, 1, textXCoord, (optionCount * textHeight + 0.125f)  +menuYCoord    + 0.125f, size, size, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
	}
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption) {
		drawText(buf, 1, textXCoord, ((optionCount - (currentOption - maxOptions)) * textHeight + 0.125f)  +menuYCoord    + 0.125f, size, size, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
	}*/
	addOption(text);
	if (currentOption == optionCount) {
		if (CONTROLS::IS_CONTROL_PRESSED(0, Dpad_Up)) {
			triggerScrollUp = true;
		}
		else if (CONTROLS::IS_CONTROL_PRESSED(0, Dpad_Down)) {
			triggerScrollDown = true;
		} else {
			triggerScrollDown = true;
		}
	}
}

void addOptionIcon(float yValue, char *dictionary, char *textureName, float rotation, int r, int g, int b, int a, float scale, float optionWidth) {

	if (yValue != 0) {
		uiTop();
		float sizeMult = textHeight / 0.035f;
		float height = 0.04f*sizeMult;
		float width = ((float)SCREEN_HEIGHT/(float)SCREEN_WIDTH) * height;//0.03f*sizeMult;
		float x = MENU_MAX_X_RIGHT - width/2.0f + 0.002f;//add on 0.002 bevcause there is a padding of transparency or something around the check mark box
		float y = yValue;
		drawing::DrawSprite(dictionary, textureName, x, y, 0.03f*sizeMult * scale, 0.04f*sizeMult * scale,rotation, r,g,b, a);//same opacity as screen text	
		
		updateMenuWidth(optionWidth+width);
		
		uiOrig();
	}
}

void addSubmenuOption(char *option, int newSubmenu, char *info = NULL)
{
	float yVal = addOption(option, info);

	//addOptionIcon(yVal,"commonmenu", "arrowright",0,255,255,255, optionsOpacity);


	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress) {
			changeSubmenu(newSubmenu);
			optionPress = false;//sometimes it will go to the next submmenu and still think the button is pressed. Set this to false instantly for fix. added 5/30/2018
		}
	}
}
void addTeleportOption(char *option, float x, float y, float z, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		squareInstruction2 = true;
		if (optionPress)
			PlayerMods::teleportToCoords(x,y,z);
		if (squarePress) {
			if (!camShit::enabled()) {
				camShit::attachToLocation(x,y,z+0.5f);
			} else {
				camShit::resetCam();
			}
		}
	}
}
void _addCustomOption(const char *arg, ... ){
    va_list arguments;

    for (va_start(arguments, arg); arg != NULL; arg = va_arg(arguments, const char *)) {
        //cout << arg << endl;
    }

    va_end(arguments);
}
#define addCustomOption(...) _addCustomOption(__VA_ARGS__, NULL)

//char booloptionbuf[50];
void addBoolOption(char *option, bool b00l, char *info = NULL,bool addtoenabledlist = true)
{
	/*for (int i = 0; i < 64; i++) {
		if (enabledmods[i] == option) {
			enabledmods[i] = NULL;
			//could remove this but it would make it slower
			break;
		}
	}*/
	//char buf[200];
	//snprintf(buf,sizeof(buf),"%s: %s",option,b00l?"~g~On":"~r~Off");
	float textWidth = 0;
	float yVal = addOption(option, info, &textWidth);
	//addOptionWithRightwardText(option,(char*)(b00l?"~g~On":"~r~Off"),info);


	/*uiTop();
	float sizeMult = textHeight / 0.035f;
	float height = 0.04f*sizeMult;
	float width = ((float)SCREEN_HEIGHT/(float)SCREEN_WIDTH) * height;//0.03f*sizeMult;
	float x = MENU_MAX_X_RIGHT - width/2.0f + 0.002f;//add on bevcause there is a padding of transparency or something around the check mark box
	float y = yVal;*/
	
	if (yVal != 0.0) {
		if (b00l) {
			//drawing::DrawSprite("commonmenu", "shop_box_tick", x, y, 0.03f*sizeMult, 0.04f*sizeMult,0, 255,255,255, optionsOpacity);//same opacity as screen text
			if (special3DMenuDesign == false)
				addOptionIcon(yVal,"commonmenu", "shop_box_tick",0, 255,255,255, optionsOpacity, 1.0f, textWidth);
			menuLineAddText("  ~g~On");
		} else {
			//drawing::DrawSprite("commonmenu", "shop_box_blank", x, y, 0.03f*sizeMult, 0.04f*sizeMult,0, 255, 255, 255, optionsOpacity);
			if (special3DMenuDesign == false)
				addOptionIcon(yVal,"commonmenu", "shop_box_blank",0, 255,255,255, optionsOpacity, 1.0f, textWidth);
			menuLineAddText("  ~c~Off");
		}
	}
	//uiOrig();
	

}

void addBoolOption(char *option, bool *b00l, char *info = NULL,bool addtoenabledlist = true)
{
	//char buf[200];
	//snprintf(buf,sizeof(buf),"%s: %s",option,(*b00l)?"~g~On":"~r~Off");
	//addOption(buf, info);
	//addOptionWithRightwardText(option,(char*)((*b00l)?"~g~On":"~r~Off"),info);
	addBoolOption(option,*b00l,info,addtoenabledlist);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress)
			*b00l = !*b00l;
	}
}


void addStrOption(char *s1, char *info = NULL) {
	char buf[50];
	snprintf(buf,sizeof(buf),"%s",s1);
	addOption(buf,info);
}
void addStrOption(char *s1, char *s2, char *info = NULL) {
	char buf[50];
	snprintf(buf,sizeof(buf),"%s%s",s1,s2);
	addOption(buf,info);
}
void addStrOption(char *s1, char *s2, char *s3, char *info = NULL) {
	char buf[50];
	snprintf(buf,sizeof(buf),"%s%s%s",s1,s2,s3);
	addOption(buf,info);
}
void addStrOption(char *s1, char *s2, char *s3, char *s4, char *info = NULL) {
	char buf[50];
	snprintf(buf,sizeof(buf),"%s%s%s%s",s1,s2,s3,s4);
	addOption(buf,info);
}
void addStrOption(char *s1, char *s2, char *s3, char *s4, char *s5, char *info = NULL) {
	char buf[50];
	snprintf(buf,sizeof(buf),"%s%s%s%s%s",s1,s2,s3,s4,s5);
	addOption(buf,info);
}
int arrayOptionNumber = 0;
void addIntOption(char *option, bool holdPress, int increment, int *var, int min, int max, bool keyboard, char *info = NULL, bool hex = false)
{
	//char buf[50];
	//snprintf(buf, sizeof(buf), "%s: ~g~%i", option, *var);
	//char *hi = buf;
	//addOption(option, info,0,0,0,0,false,ItoS(*var));
	char num[20];
	snprintf(num, sizeof(num), "%s", hex?ItoSH(*var):ItoS(*var));
	//char buf[200];
	
	//snprintf(buf,sizeof(buf),"%s: %s",option,num);
	
	//addOption(buf, info);

	addOptionWithRightwardText(option,num,info);

	if (currentOption == optionCount)
	{
		lrInstruction = true;
		if (holdPress)
		{
			if (fastRightPress || fastLeftPress) {
				arrayOptionNumber++;
				if (arrayOptionNumber == 1 || arrayOptionNumber  > 5) {
					if (arrayOptionNumber > 5)
						arrayOptionNumber=4;
			if (fastRightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + increment;
			}
			else if (fastLeftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - increment;
			}

				}
			} else {
				arrayOptionNumber = 0;
			}
		}
		else
		{
			if (rightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + increment;
			}
			else if (leftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - increment;
			}
		}
		if (keyboard)
		{
			squareInstruction = true;
			if (squarePress)
			{
				startKeyboard(0, "", 120/*(strlen(ItoS(max)) + 1)*/,"Enter Number");
				keyboardVar = var;
			}
		}
		/*lrInstruction = true;
		if (rightPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var >= max)
				*var = min;
			else
				*var = *var + 1;
		}
		else if (leftPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var <= min)
				*var = max;
			else
				*var = *var - 1;
		}
		if (keyboard)
		{
			squareInstruction = true;
			if (squarePress)
			{
				startKeyboard(0, "", (strlen(ItoS(max)) + 1));
				keyboardVar = var;
			}
		}*/
	}
}
void addHexOption(char *option, bool holdPress, int increment, int *var, int min, int max, bool keyboard, char *info = NULL){
	addIntOption(option, holdPress, increment, var, min, max, keyboard, info,true);
}
void addIntOption(char *option, int *var, int min, int max, bool keyboard, char *info = NULL, bool hex = false) {
	addIntOption(option,false,1,var,min,max,keyboard,info,hex);
}
void addHexOption(char *option, int *var, int min, int max, bool keyboard, char *info = NULL) {
	addHexOption(option,false,1,var,min,max,keyboard,info);
}




//this is to only be used inside the array option call
void addIntOptionWithRightText(char *option, bool holdPress, int *var, char *righttext,int min, int max, char *info = NULL)
{
	//char num[200];
	//snprintf(num, sizeof(num), "%s",*var, max, righttext);
	addOptionWithRightwardText(option,righttext,info);
	if (currentOption == optionCount)
	{
		lrInstruction = true;
		if (holdPress)
		{
			if (fastRightPress || fastLeftPress) {
				arrayOptionNumber++;
				if (arrayOptionNumber == 1 || arrayOptionNumber  > 5) {
					if (arrayOptionNumber > 5)
						arrayOptionNumber=4;
					if (fastRightPress)
					{
						playSound("NAV_UP_DOWN");
						*var = *var + 1;
						if (*var >= max)
							*var = min;
					}
					else if (fastLeftPress)
					{
						playSound("NAV_UP_DOWN");
						*var = *var - 1;
						if (*var < min)
							*var = max-1;
					}
				}
			} else {
				arrayOptionNumber = 0;
			}
		}
		else
		{
			if (rightPress)
			{
				playSound("NAV_UP_DOWN");
				*var = *var + 1;
				if (*var >= max)
					*var = min;
			}
			else if (leftPress)
			{
				playSound("NAV_UP_DOWN");
				*var = *var - 1;
				if (*var < min)
					*var = max-1;
			}
		}
	}
}
void addIntOptionWithRightText(char *option, int *var, char *righttext,int min, int max, char *info = NULL) {
	addIntOptionWithRightText(option,false,var,righttext,min,max,info);
}
void addArrayOption(char *option, bool holdPress, int *var, char *arr[], int arraySize, char *info = NULL) {
	char rightward[200];
	snprintf(rightward,sizeof(rightward),"[%i/%i] %s",*var+1,arraySize,arr[*var]);
	addIntOptionWithRightText(option,holdPress,var,rightward,0,arraySize,info);
}
void addArrayOption(char *option, int *var, char *arr[], int arraySize, char *info = NULL) {
	//char rightward[200];
	//snprintf(rightward,sizeof(rightward),"[%i/%i] %s",*var+1,arraySize,arr[*var]);
	//addIntOptionWithRightText(option,false,var,rightward,0,arraySize,info);
	addArrayOption(option,false,var,arr,arraySize,info);
}







int addFloatOption(char *option, float *var, float min, float max, bool holdPress,float increment, char *info = NULL, bool keyboard = false, bool loopAround = true)
{
	//printf("Option: %s\n",option);
	int ret = 0;
	//char buf[50];
	//snprintf(buf, sizeof(buf), "%s: ~g~%s", option, FtoS(*var));
	//char *hi = buf;
	//addOption(hi, info);
	char num[200];
	snprintf$(num, sizeof(num), "%.2f", *var);//this is the best method because of the .2f, otherwise use FtoS
	addOptionWithRightwardText(option,num,info);
	//addBarOption(option,((*var-min)/(max-min)),hi,info);
	if (currentOption == optionCount)
	{
		lrInstruction = true;
		if (holdPress)
		{
			if (fastRightPress)
			{
				ret = 1;
				playSound("NAV_UP_DOWN");
				if (*var >= max) {
					if (loopAround)
						*var = min;
				} else
					*var = *var + increment;
			}
			else if (fastLeftPress)
			{
				ret = -1;
				playSound("NAV_UP_DOWN");
				if (*var <= min) {
					if (loopAround)
						*var = max;
				} else
					*var = *var - increment;
			}
		}
		else
		{
			if (rightPress)
			{
				ret = 1;
				playSound("NAV_UP_DOWN");
				if (*var >= max) {
					if (loopAround)
						*var = min;
				} else
					*var = *var + increment;
				
			}
			else if (leftPress)
			{
				ret = -1;
				playSound("NAV_UP_DOWN");
				if (*var <= min) {
					if (loopAround)
						*var = max;
				} else
					*var = *var - increment;
			}
		}
		if (keyboard)
		{
			squareInstruction = true;
			if (squarePress)
			{
				startKeyboard(keyboard_float_option, "", 120/*(strlen(ItoS(max)) + 1)*/,"Enter Number");
				keyboardVarFloat = var;
			}
		}
	}
	return ret;
}
int addFloatOption(char *option, float *var, float min, float max, bool holdPress, char *info = NULL, bool keyboard = false, bool loopAround = true) {
	return addFloatOption(option,var,min,max,holdPress,0.01f,info,keyboard,loopAround);
}
void addKeyboardOption(char *option, int action, char *defaultText, int maxLength, char *title, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress)
			startKeyboard(action, defaultText, maxLength,title);
	}
}
#pragma endregion
#pragma region get option functions
int getOption()
{
	xInstruction = true;
	if (optionPress) {
		hasBeenUsed = true;
		return currentOption;
	}
	else return 0;
}
int getSquareOption()
{
	if (squarePress) {
		hasBeenUsed = true;
		return currentOption;
	}
	else return 0;
}
#pragma endregion
#pragma region monitor buttons
bool queClose = false;
void goBackASubmenu() {
	optionPress = false;
	if (submenu == Main_Menu)
	{
		queClose = true;
	}
	else {
		submenu = lastSubmenu[submenuLevel - 1];
		currentOption = lastOption[submenuLevel - 1];
		submenuLevel--;
	}
	playSound("Back");
}
void monitorButtons()
{
	//SetupTimer(20);

	//if (IsTimerReady())
	//{
		if (submenu == Closed)
		{
			//if (GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(drawing::gGlareHandle))
			//	GRAPHICS::SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(&drawing::gGlareHandle);//kek
			//GRAPHICS::_0x3FE33BD6();
			if ((CONTROLS::IS_CONTROL_PRESSED(0, Button_R1) && CONTROLS::IS_CONTROL_PRESSED(0, Dpad_Right))/* || (CONTROLS::IS_CONTROL_PRESSED(0, Button_L1) && CONTROLS::IS_CONTROL_PRESSED(0, Dpad_Up))*/)
			{
				globalAddX = -0.5f;
				submenu = Main_Menu;
				submenuLevel = 0;
				currentOption = 1;
				playSound("YES");
				//createPhone = true;
			}
		}
		else {
			if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_B)/* || CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_R3)*/)
			{
				if (submenu == Main_Menu)
				{
					
					//MOBILE::DESTROY_MOBILE_PHONE();
					//closeMiniMenu();
					queClose = true;
				}
				else {
					submenu = lastSubmenu[submenuLevel - 1];
					currentOption = lastOption[submenuLevel - 1];
					submenuLevel--;
				}
				//textmenuwidth = minimumMenuWidth;
				playSound("Back");
			}
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_A))
			{
				hasBeenUsed = true;
				optionPress = true;
				playSound("SELECT");
			}
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Dpad_Up) || triggerScrollUp)
			{
				previousScrollerOption = currentOption;
				scrollerTransferTimeCount = 0;
				scrollerY = 0;

				hasBeenUsed = true;
				controlJustPressedTimeout = 0;
				currentOption--;
				if (currentOption < 1)
				{
					currentOption = optionCount;
				}
				menuRemembrence[submenu] = currentOption;
				playSound("NAV_UP_DOWN");
				triggerScrollUp = false;
			}
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Dpad_Down) || triggerScrollDown)
			{
				previousScrollerOption = currentOption;
				scrollerTransferTimeCount = 0;
				scrollerY = 0;

				hasBeenUsed = true;
				controlJustPressedTimeout = 0;
				currentOption++;
				if (currentOption > optionCount)
				{
					currentOption = 1;
				}
				menuRemembrence[submenu] = currentOption;
				playSound("NAV_UP_DOWN");
				triggerScrollDown = false;
			}
			else if (CONTROLS::IS_CONTROL_PRESSED(0, Dpad_Up))
			{
				hasBeenUsed = true;
				controlJustPressedTimeout++;
				if (controlJustPressedTimeout > 10) {
					previousScrollerOption = currentOption;
					scrollerTransferTimeCount = 0;
					scrollerY = 0;
				currentOption = currentOption - fastScrollSpeed;
				if (currentOption < 1)
				{
					currentOption = optionCount;
				}
				menuRemembrence[submenu] = currentOption;
				playSound("NAV_UP_DOWN");
				}
			}
			else if (CONTROLS::IS_CONTROL_PRESSED(0, Dpad_Down))
			{
				hasBeenUsed = true;
				controlJustPressedTimeout++;
				if (controlJustPressedTimeout > 10) {
					previousScrollerOption = currentOption;
					scrollerTransferTimeCount = 0;
					scrollerY = 0;
				currentOption = currentOption + fastScrollSpeed;
				if (currentOption > optionCount)
				{
					currentOption = 1;
				}
				menuRemembrence[submenu] = currentOption;
				playSound("NAV_UP_DOWN");
				}
			}
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Dpad_Right))
			{
				hasBeenUsed = true;
				rightPress = true;
			}
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Dpad_Left))
			{
				hasBeenUsed = true;
				leftPress = true;
			}
			else if (CONTROLS::IS_CONTROL_PRESSED(0, Dpad_Right))
			{
				hasBeenUsed = true;
				fastRightPress = true;
			}
			else if (CONTROLS::IS_CONTROL_PRESSED(0, Dpad_Left))
			{
				hasBeenUsed = true;
				fastLeftPress = true;
				pressedButtons::dpadleftpressed = true;
			}
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_X))
			{
				hasBeenUsed = true;
				squarePress = true;
			}
		}


		//my buttons

		if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Dpad_Left)){
			pressedButtons::dpadleftpressed = true;
		} else {
			pressedButtons::dpadleftpressed = false;
		}

		if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Dpad_Right)){
			pressedButtons::dpadrightpressed = true;
		} else {
			pressedButtons::dpadrightpressed = false;
		}

		if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Dpad_Down)){
			pressedButtons::dpaddownpressed = true;
		} else {
			pressedButtons::dpaddownpressed = false;
		}

		if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Dpad_Up)){
			pressedButtons::dpaduppressed = true;
		} else {
			pressedButtons::dpaduppressed = false;
		}

		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_X)){
			pressedButtons::squarepressed = true;
		} else {
			pressedButtons::squarepressed = false;
		}

		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_R3)) {
			if (noclip::enabled) {
				CONTROLS::DISABLE_CONTROL_ACTION(0, Button_R3);
				CONTROLS::SET_INPUT_EXCLUSIVE(2, Button_R3);
			}
			noclip::r3pressed = true;
			pressedButtons::r3pressed = true;
		} else {
			noclip::r3pressed = false;
			pressedButtons::r3pressed = false;
		}

		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_L3)) {
			//CONTROLS::DISABLE_CONTROL_ACTION(0, Button_L3);
			//CONTROLS::SET_INPUT_EXCLUSIVE(2, Button_L3);
			VehicleMods::l3pressed = true;
			pressedButtons::l3pressed = true;
		} else {
			VehicleMods::l3pressed = false;
			pressedButtons::l3pressed = false;
		}

		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_L2)) {
			pressedButtons::l2pressed = true;
		} else {
			pressedButtons::l2pressed = false;
		}
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_L1)) {
			pressedButtons::l1pressed = true;
		} else {
			pressedButtons::l1pressed = false;
		}

		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_R2)) {
			pressedButtons::r2pressed = true;
		} else {
			pressedButtons::r2pressed = false;
		}
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_R1)) {
			pressedButtons::r1pressed = true;
		} else {
			pressedButtons::r1pressed = false;
		}






		if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_R3)) {
			if (noclip::enabled) {
				CONTROLS::DISABLE_CONTROL_ACTION(0, Button_R3);
				CONTROLS::SET_INPUT_EXCLUSIVE(2, Button_R3);
			}
			pressedButtons::r3jpressed = true;
		} else {
			pressedButtons::r3jpressed = false;
		}

		if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_L3)) {
			//CONTROLS::DISABLE_CONTROL_ACTION(0, Button_L3);
			//CONTROLS::SET_INPUT_EXCLUSIVE(2, Button_L3);
			pressedButtons::l3jpressed = true;
		} else {
			pressedButtons::l3jpressed = false;
		}

		if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_L2)) {
			pressedButtons::l2jpressed = true;
		} else {
			pressedButtons::l2jpressed = false;
		}
		if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_L1)) {
			pressedButtons::l1jpressed = true;
		} else {
			pressedButtons::l1jpressed = false;
		}

		if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_R2)) {
			pressedButtons::r2jpressed = true;
		} else {
			pressedButtons::r2jpressed = false;
		}
		if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_R1)) {
			pressedButtons::r1jpressed = true;
		} else {
			pressedButtons::r1jpressed = false;
		}

		// Left Analog X-Axis (188 = INPUT_SCRIPT_LEFT_AXIS_X)
		// 0 = Fully left
		// 127 = Centered
		// 254 = Fully right
		pressedButtons::leftAnalogX = CONTROLS::GET_CONTROL_VALUE(0, 188)-127;

		// Left Analog Y-Axis (189 = INPUT_SCRIPT_LEFT_AXIS_Y)
		// 0 = Fully up
		// 127 = Centered
		// 254 = Fully down
		pressedButtons::leftAnalogY = (CONTROLS::GET_CONTROL_VALUE(0, 189)-127)*-1;

		//ResetTimer();
	//}
}
#pragma endregion
#pragma region push menu item function
int scaleformmenuitem = 0;
void pushMenuItem(char *item, char *text) {
	/*GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(mov, "SET_DATA_SLOT");
    GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(scaleformmenuitem);
    GRAPHICS::_0xCCBF0334(item);
    GRAPHICS::_BEGIN_TEXT_COMPONENT(text);
    GRAPHICS::_END_TEXT_COMPONENT();
    GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();*/

	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(mov, "SET_DATA_SLOT");
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(scaleformmenuitem);
	GRAPHICS::_0xCCBF0334(item);//replacement for GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(button);
	set_text_component(text);
	GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();

	scaleformmenuitem++;
}
#pragma endregion
#pragma region normal menu actions
//ScaleformBlip myBlip;
//#define oldNormalMenuActions
#ifdef oldNormalMenuActions
__ALWAYS_INLINE void normalMenuActions()//memory eater #4
{
	//https://wiki.fivem.net/wiki/Controls has the ps3 controls
	//circle is 45, 57, 80, 140, 177
	//202 is INPUT_FRONTEND_CANCEL
	/*for (int i = 0; i < 32; i++) {
		CONTROLS::DISABLE_CONTROL_ACTION(i,45);
		CONTROLS::SET_INPUT_EXCLUSIVE(i   ,45);
		CONTROLS::DISABLE_CONTROL_ACTION(i,57);
		CONTROLS::SET_INPUT_EXCLUSIVE(i   ,57);
		CONTROLS::DISABLE_CONTROL_ACTION(i,80);
		CONTROLS::SET_INPUT_EXCLUSIVE(i   ,80);
		CONTROLS::DISABLE_CONTROL_ACTION(i,140);
		CONTROLS::SET_INPUT_EXCLUSIVE(i   ,140);
		CONTROLS::DISABLE_CONTROL_ACTION(i,177);
		CONTROLS::SET_INPUT_EXCLUSIVE(i   ,177);
		CONTROLS::DISABLE_CONTROL_ACTION(i,202);
		CONTROLS::SET_INPUT_EXCLUSIVE(i   ,202);
	}*/
	UI::HIDE_HELP_TEXT_THIS_FRAME();
	CAM::SET_CINEMATIC_BUTTON_ACTIVE(0);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(10);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(6);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(7);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(9);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(8);
	CONTROLS::DISABLE_CONTROL_ACTION(0,Button_B);//195
	CONTROLS::DISABLE_CONTROL_ACTION(0, 19);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 20);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 21);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 27);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 54);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 123);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 124);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 125);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 126);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 138);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 139);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 140);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 177);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 178);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 179);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 207);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 166);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 167);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 177);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 178);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 193);//x   if this is removed, x button doesn't work
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 194);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 195);//circle
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 202);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 203);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 204);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 205);
	int tempoptions = optionCount;
	//optionCount = 16;
	//menuYCoord+=0.005;
	//float expand = textmenuwidth+0.04f;
	//float addWidth = expand/2;
	float expand = textmenuwidth+0.02f;
	float addWidth = expand/2;
	float menuBGTopY = 0.1415f+menuYCoord + 0.035f/2.0f;//this is the y coordate at the bottom of the header or at the top of the background,  essentially replaces anywhere where + 0.159f + menuYcoord is used
	if (!GAMEPLAY::IS_STRING_NULL_OR_EMPTY(infoText))
	{
		if (optionCount > maxOptions)
		{
			drawText(infoText, optionsFont, textXCoord, menuBGTopY + (maxOptions * textHeight)/*((maxOptions + 1) * textHeight + 0.125f)  +menuYCoord-0.002f*/, textSize, textSize, optionsRed, optionsGreen, optionsBlue, bannerTextOpacity, false);
			expand = textmenuwidth+0.02f;
			addWidth = expand/2;
			//GRAPHICS::DRAW_RECT(menuXCoord+addWidth, (((maxOptions + 1) * textHeight) + 0.1415f)  +menuYCoord, 0.19f+expand, textHeight, bannerRectRed, bannerRectGreen, bannerRectBlue, backgroundOpacity); //Info Box OLD
			//GRAPHICS::DRAW_RECT(menuXCoord-(0.19f/2)+addWidth, (((maxOptions + 1) * textHeight) + 0.1415f)  +menuYCoord, expand, textHeight, bannerRectRed, bannerRectGreen, bannerRectBlue, backgroundOpacity); //Info Box
		}
		else
		{
			drawText(infoText, optionsFont, textXCoord, menuBGTopY + (optionCount * textHeight)/*((optionCount + 1) * textHeight + 0.125f)  +menuYCoord-0.002f*/, textSize, textSize, optionsRed, optionsGreen, optionsBlue, bannerTextOpacity, false);
			expand = textmenuwidth+0.02f;
			addWidth = expand/2;
			//GRAPHICS::DRAW_RECT(menuXCoord+addWidth, (((optionCount + 1) * textHeight) + 0.1415f)  +menuYCoord, 0.19f+expand, textHeight, bannerRectRed, bannerRectGreen, bannerRectBlue, backgroundOpacity); //Info Box OLD
			//GRAPHICS::DRAW_RECT(menuXCoord-(0.19f/2)+addWidth, (((optionCount + 1) * textHeight) + 0.1415f)  +menuYCoord, expand, textHeight, bannerRectRed, bannerRectGreen, bannerRectBlue, backgroundOpacity); //Info Box
		}
	}/* else {
		expand = textmenuwidth+0.04f;
		addWidth = expand/2;
	}*/
	previousMenuWidth = textmenuwidth;//+textmenuwidthCounter;
	addwidthspecialrender = addWidth;
	expandspecialrender = expand;
	//drawing::DRAW_RECT(menuXCoord-(0.19f/2)+addWidth, 0.1415f+menuYCoord-0.03f  -0.0175, expand, 0.06, 0,     255,            255 ,backgroundOpacity);//box above title
	//drawing::drawGlare(glarex,glarey,glarew,glareh,0,0,0);//this is for the glare thing globe


	//title stuff
	//GRAPHICS::DRAW_RECT(menuXCoord-(0.19f/2)+addWidth, 0.1415f+menuYCoord, expand/*-0.004f*/, textHeight, /*bannerRectRed, bannerRectGreen, bannerRectBlue */0,255,255,backgroundOpacity);//background of title
	//MENU HEADER (for text)
	//if (scrollerImageOverritten)
	//	drawing::DrawSprite("mpinventory","mp_specitem_meth",menuXCoord-(0.19f/2)+addWidth, menuBGTopY-(textHeight/2.0f)/*0.1415f+menuYCoord*/, expand/*-0.004f*/, textHeight/*0.035f*/, 0/*rotation*/, COLOR_FOREGROUND,backgroundOpacity);
	//MENU HEADER (image above text)
	if (titleImageOverritten)
		drawing::DrawSprite("mpmissmarkers256","corona_point",menuXCoord-(0.19f/2)+addWidth, menuBGTopY-(textHeight/2.0f)/*-textHeight*//*0.1415f+menuYCoord*/, expand/*-0.004f*/, textHeight/*0.035f*/, 0/*rotation*/, COLOR_FOREGROUND,backgroundOpacity);

	//drawing::DrawSprite("digitaloverlay","static1",/*"mpmissmarkers256","foot_race_icon",*/menuXCoord-(0.19f/2)+addWidth, 0.1415f+menuYCoord, expand, textHeight,90, bannerRectRed, bannerRectGreen, bannerRectBlue ,bannerRectOpacity);//background of title


	//char buf[30];
	snprintf(global_temporary_buf,sizeof(global_temporary_buf),"%i/%i",currentOption,numberofoptions);
	//textmenuwidthCounter = getTextWidth(buf,0,0.3,0.3);

	//drawText(buf, 0, menuXCoord-(0.19f/2)+expand-0.02, (0 * textHeight + 0.125f)  +menuYCoord/*+0.035*/, 0.3f, 0.3f, 255, 255, 255, bannerTextOpacity, false);

	float slength = getTextWidth(global_temporary_buf,0,0.3f,0.3f);
	//if (submenu != Main_Menu) {
		//drawText(buf,0,textXCoord+0.009+previousMenuWidth-slength     +addOnEndRightTextWidth, (0 * textHeight + 0.125f)  +menuYCoord/*+0.035*/,0.3f, 0.3f, 255, 255, 255, bannerTextOpacity, false);
		float textPos = menuBGTopY   + textHeight * -1 + 0.01f;
		drawing::DrawText(global_temporary_buf, bannerTextFont, menuXCoord-(0.19f/2)+expand - 0.005f, textPos, textSize/2.0f, textSize/2.0f, 255, 255, 255, bannerTextOpacity, false,false,true);

	//}
	//testimg.render((textXCoord+0.009+previousMenuWidth-slength     +addOnEndRightTextWidth)*WIDTH,((0 * textHeight + 0.125f)  +menuYCoord-0.035)*HEIGHT,5.0f,5.0f,255);
	
	//basically we are bypassing the background cuz I am too lazy to cut it out rn

	//rgb(0,     255,            255)
	//THIS IS FOR THE MENU BACKGROUND
	if (optionCount > maxOptions)
	{
		//GRAPHICS::DRAW_RECT(menuXCoord+addWidth, (((maxOptions * textHeight) / 2) + 0.159f)  +menuYCoord, 0.19f+expand, (maxOptions * textHeight), backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity); //Background
		GRAPHICS::DRAW_RECT(menuXCoord-(0.19f/2)+addWidth, (((maxOptions * textHeight) / 2)/* + 0.159f*/) +menuBGTopY  /*+menuYCoord*/, expand/*-0.004f*/, (maxOptions * textHeight), COLOR_BACKGROUND/*backgroundRed, backgroundGreen, backgroundBlue*/, backgroundOpacity); //Background NON TEXTURED
		//drawing::DrawSprite("digitaloverlay","static1",/*"mpmissmarkers256","foot_race_icon",*/menuXCoord-(0.19f/2)+addWidth, (((maxOptions * textHeight) / 2) + 0.159f)  +menuYCoord, expand, (maxOptions * textHeight),0, backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity);
			//drawing::DrawSprite("commonmenu","header_gradient_script",menuXCoord+addWidth, (((maxOptions * textHeight) / 2) + 0.159f)  +menuYCoord, 0.19f+expand, (maxOptions * textHeight),-90, backgroundRed, backgroundGreen, backgroundBlue, 0);//alpha is off
		//GRAPHICS::DRAW_RECT(menuXCoord-(0.19f/2)+addWidth,(((maxOptions * 0.035)) + 0.159f)  +menuYCoord,expand,0.005,0,255,255,backgroundOpacity);//bottom blue line
		//GRAPHICS::DRAW_RECT(menuXCoord-(0.19f/2)+addWidth,(0.159f)  +menuYCoord-0.005,expand,0.005,0,255,255,backgroundOpacity);//top blue line

		//GRAPHICS::DRAW_RECT(menuXCoord-(0.19f/2)+0.001, (((maxOptions * textHeight) / 2) + 0.159f)  +menuYCoord - (textHeight/2), 0.002, (maxOptions * textHeight)/*+0.005*/+textHeight, 0,     255,            255,backgroundOpacity); //left blue line
		//GRAPHICS::DRAW_RECT(menuXCoord-(0.19f/2)+(addWidth*2)-0.001, (((maxOptions * textHeight) / 2) + 0.159f)  +menuYCoord - (textHeight/2), 0.002, (maxOptions * textHeight)+textHeight, 0,     255,            255,backgroundOpacity); //right blue line

	}
	else
	{
		//GRAPHICS::DRAW_RECT(menuXCoord+addWidth, (((optionCount * textHeight) / 2) + 0.159f)  +menuYCoord, 0.19f+expand, (optionCount * textHeight), backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity); //Background
		GRAPHICS::DRAW_RECT(menuXCoord-(0.19f/2)+addWidth, (((optionCount * textHeight) / 2) /*+ 0.159f*/)  +menuBGTopY/*+menuYCoord*/, expand/*-0.004f*/, (optionCount * textHeight), COLOR_BACKGROUND/*backgroundRed, backgroundGreen, backgroundBlue*/, backgroundOpacity); //Background NON TEXTURED
		//drawing::DrawSprite("digitaloverlay","static1",/*"mpmissmarkers256","foot_race_icon",*/menuXCoord-(0.19f/2)+addWidth, (((optionCount * textHeight) / 2) + 0.159f)  +menuYCoord, expand, (optionCount * textHeight),0, backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity);
			//drawing::DrawSprite("commonmenu","header_gradient_script",menuXCoord+addWidth, (((optionCount * textHeight) / 2) + 0.159f)  +menuYCoord, 0.19f+expand, (optionCount * textHeight),-90, backgroundRed, backgroundGreen, backgroundBlue, 0);
		//GRAPHICS::DRAW_RECT(menuXCoord-(0.19f/2)+addWidth, (((optionCount * 0.035)) + 0.159f)  +menuYCoord, expand,0.005,0,255,255,backgroundOpacity);//bottom blue line
		//GRAPHICS::DRAW_RECT(menuXCoord-(0.19f/2)+addWidth, (0.159f)  +menuYCoord-0.005, expand,0.005,0,255,255,backgroundOpacity);//top blue line

		//GRAPHICS::DRAW_RECT(menuXCoord-(0.19f/2)+0.001, (((optionCount * textHeight) / 2) + 0.159f)  +menuYCoord - (textHeight/2), 0.002, (optionCount * textHeight)+textHeight,0,     255,            255,backgroundOpacity); //left blue line
		//GRAPHICS::DRAW_RECT(menuXCoord-(0.19f/2)+(addWidth*2)-0.001, (((optionCount * textHeight) / 2) + 0.159f)  +menuYCoord - (textHeight/2), 0.002, (optionCount * textHeight)+textHeight, 0,     255,            255,backgroundOpacity); //right blue line

	}


	float scny = 0;//currentOption > maxOptions          ? (maxOptions * textHeight)  +menuBGTopY  - 0.0175 : (currentOption * textHeight) +menuBGTopY   - 0.0175;
	float scoy = 0;//previousScrollerOption > maxOptions ? (((maxOptions * textHeight)))  +menuBGTopY - 0.0175 : (((previousScrollerOption * textHeight)) /*+ 0.159f*/)+menuBGTopY  /*+menuYCoord*/ - 0.0175;
	if (currentOption > maxOptions) {
		scny =  (maxOptions * textHeight)  +menuBGTopY  - textHeight/2.0f;
	} else {
		scny = (currentOption * textHeight) +menuBGTopY   - textHeight/2.0f;
	}
	if (previousScrollerOption > maxOptions) {
		scoy = (maxOptions * textHeight)  +menuBGTopY - textHeight/2.0f;
	} else {
		scoy = (previousScrollerOption * textHeight) + menuBGTopY  - textHeight/2.0f;
	}
	
	if (previousScrollerOption != currentOption) {
		float diff = (scny-scoy);
		scrollerY = scrollerY+(diff/scrollerTransferTime);
		scrollerTransferTimeCount++;
		//GRAPHICS::DRAW_RECT(menuXCoord-(0.19f/2)+addWidth, scoy+scrollerY, expand/*-0.004f*/, textHeight, 0,     255,            255,159.815668203/*backgroundOpacity*(1-(backgroundOpacity/255))*/);
		if (scrollerImageOverritten)
			drawing::DrawSprite(/*"mpmissmarkers256","basejump_icon"*/"mpinventory","mp_specitem_meth",menuXCoord-(0.19f/2)+addWidth, scoy+scrollerY, expand/*-0.004f*/, textHeight, 0/*rotation*/, COLOR_FOREGROUND/*0,     255,            255*/,159.815668203);
		if (scrollerTransferTimeCount == scrollerTransferTime) {
			scrollerTransferTimeCount = 0;
			previousScrollerOption = currentOption;
		}
	} else {
		scrollerY = 0;
		//GRAPHICS::DRAW_RECT(menuXCoord-(0.19f/2)+addWidth, scny/*0.1415f+menuYCoord*/, expand/*-0.004*/, textHeight, 0,     255,            255,159.815668203/*backgroundOpacity*(1-(backgroundOpacity/255))*/);
		if (scrollerImageOverritten)
			drawing::DrawSprite(/*"mpmissmarkers256","basejump_icon"*/"mpinventory","mp_specitem_meth",menuXCoord-(0.19f/2)+addWidth, scny/*0.1415f+menuYCoord*/, expand/*-0.004*/, textHeight,0/*rotation*/, COLOR_FOREGROUND/*0,     255,            255*/,159.815668203);
	}

	


	if (!GAMEPLAY::IS_STRING_NULL_OR_EMPTY(infoText)) {
		//GRAPHICS::DRAW_RECT(menuXCoord-(0.19f/2)+addWidth, optionCount > maxOptions?(maxOptions+1)*textHeight+ 0.159f  +menuYCoord - 0.0175:(optionCount+1)*textHeight+ 0.159f  +menuYCoord - 0.0175, expand, textHeight, 0,     255,            255,backgroundOpacity);//bottom
		if (scrollerImageOverritten) {
			float menuBottomY = 0;
			if (optionCount > maxOptions) {
				menuBottomY = (maxOptions)*textHeight + menuBGTopY;//(maxOptions+1)*textHeight/*+ 0.159f  +menuYCoord*/+menuBGTopY/* - 0.0175*/
			} else {
				menuBottomY = (optionCount)*textHeight + menuBGTopY;//(maxOptions+1)*textHeight/*+ 0.159f  +menuYCoord*/+menuBGTopY/* - 0.0175*/
			}
			drawing::DrawSprite("mpinventory","mp_specitem_meth",menuXCoord-(0.19f/2)+addWidth, menuBottomY + textHeight/2, expand, textHeight, 0/*rotation*/, COLOR_FOREGROUND/*0,     255,            255*/,backgroundOpacity);
			
		}
	}
	//menu title text
	//drawText("Paradise",7,textXCoord/*menuXCoord-(0.19f/2)+addWidth*/, 0.1415f+menuYCoord-0.055f  -0.018,0.8,0.8,255,255,255,255,false);
	//drawText("By gopro_2027",1,textXCoord/*menuXCoord-(0.19f/2)+addWidth*/, 0.1415f+menuYCoord-0.02f  -0.018,0.3,0.3,255,255,255,255,false);
	

	//menuYCoord-=0.005;

	//SetupTimer2(30);
	/*if (myBlip.created == false) {
			myBlip.create();
			myBlip.setIcon(BLIP_GARAGE);
			myBlip.setColor(BLIPCOLOR_RED);
		}*/
	//BriefMessage("~BLIP_GARAGE~Hey","");
	if (instructions) {
		//GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("CommonMenu", false);
			//char buf[20];
			snprintf$(global_temporary_buf,sizeof(global_temporary_buf),"%.0fFPS",getFPS());
			addInstructionTextOnly(global_temporary_buf);
			if (xInstruction)
				addInstruction(BUTTON_A, "Select");
			if (squareInstruction)
				addInstruction(BUTTON_X, "Keyboard");
			if (squareInstruction2)
				addInstruction(BUTTON_X, "Spectate");
			if (lrInstruction)
				addInstruction(BUTTON_DPAD_LEFT_RIGHT, "Scroll");
			addInstruction(BUTTON_DPAD_UP_DOWN, "Scroll");
			addInstruction(BUTTON_B, "Back");
		instructionsClose();
		ResetTimer2();
	}

	optionCount = tempoptions;

}
#else


class SmoothMovement {
private:
	float movex;
	float movey;
	float goalx;
	float goaly;
	int time;
	float move(float newX, float newY, int time) {
		goalx = newX;
		goaly = newY;
		this->time = time;
		movex = (newX-x) / (float)time;
		movey = (newY-y) / (float)time;
	}

public:
	float x,y;
	SmoothMovement(float x, float y) {
		this->x = x;
		this->y = y;
		movex = 0;
		movey = 0;
		time = 0;
		goalx = x;
		goaly = y;
	}

	float update(float tox, float toy, float timeRequest) {
		if (tox != goalx || toy != goaly) {
			//first, fast set to requested location so there is no lag
			this->x = goalx;
			this->y = goaly;
			//new position requested, move
			move(tox,toy,timeRequest);
		}
		if (time > 0) {
			time--;
			x += movex;
			y += movey;
		}
	}


};

SmoothMovement scrollerMovement(0,0);

void drawShadow(float centerX, float centerY, float width, float height, int elevation, float opacity, int orientation = 2) {
	//commonmenu header_gradient_script
	float offsetToEdge = height / 2.0f;
	height = (0.0025f*elevation);
	if (elevation > 0) {//don't bother to render if it is inside the obbject below it
		if (orientation == 2 || orientation == 1)//draw bottom
			drawing::DrawSprite("commonmenu","header_gradient_script",centerX, centerY+(height/2.0f)+offsetToEdge, width, height,0,  0,0,0,opacity);//bottom one
		if (orientation == 2 || orientation == 0)//draw top
			drawing::DrawSprite("commonmenu","header_gradient_script",centerX, centerY-(height/2.0f)-offsetToEdge, width, height,180/*flip it*/,  0,0,0,opacity);//top one
	}
}

bool doDrawCustomBG = false;
__ALWAYS_INLINE void normalMenuActions()//memory eater #4
{

	UI::HIDE_HELP_TEXT_THIS_FRAME();
	CAM::SET_CINEMATIC_BUTTON_ACTIVE(0);
	/*UI::HIDE_HUD_COMPONENT_THIS_FRAME(10);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(6);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(7);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(9);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(8);*/
	unsigned char cArray[] = {10,6,7,8,9};
	for (int i = 0; i < sizeof(cArray); i++)
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(cArray[i]);
	/*CONTROLS::DISABLE_CONTROL_ACTION(0,Button_B);//195
	CONTROLS::DISABLE_CONTROL_ACTION(0, 19);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 20);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 21);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 27);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 54);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 123);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 124);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 125);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 126);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 138);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 139);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 140);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 177);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 178);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 179);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 207);*/
	unsigned char bArray[] = {Button_B,19,20,21,27,54,123,124,125,126,138,139,140,177,178,179,207};
	for (int i = 0; i < sizeof(bArray); i++)
		CONTROLS::DISABLE_CONTROL_ACTION(0,bArray[i]);
	/*CONTROLS::SET_INPUT_EXCLUSIVE(2, 166);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 167);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 177);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 178);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 193);//x   if this is removed, x button doesn't work
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 194);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 195);//circle
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 202);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 203);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 204);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 205);*/
	unsigned char iArray[] = {166,167,177,178,193,194,195,202,203,204,205};
	for (int i = 0; i < sizeof(iArray); i++)
		CONTROLS::SET_INPUT_EXCLUSIVE(2,iArray[i]);
	int tempoptions = optionCount;

	//float expand = textmenuwidth+0.02f;
	//float addWidth = expand/2;

	//MENU CALCULATIONS
	float menuPaddingX = menuPadding;
	float menuLeftX = textXCoord - menuPaddingX;
	float menuWidth = menuWidthUseableValue + 2*menuPaddingX;
	float menuWidthNoPadding = menuWidthUseableValue;
	float menuRightX = menuLeftX + menuWidth;
	float menuCenterX = (menuLeftX+menuRightX)/2.0f;
	//END MENU CALCULATIONS

	float menuBGTopY = 0.1415f+menuYCoord + 0.035f/2.0f;


	int oc = optionCount;
	if (optionCount > maxOptions)
		oc = maxOptions;


	if (!GAMEPLAY::IS_STRING_NULL_OR_EMPTY(infoText))
	{
		oc++;//make it 1 larger so it can render the text at the bottom
		drawText(infoText, optionsFont, textXCoord, menuBGTopY + ((oc-1) * textHeight) - textHeight, textSize, textSize, optionsRed, optionsGreen, optionsBlue, bannerTextOpacity, false);
		
		//expand = textmenuwidth+0.02f;
		//addWidth = expand/2;
		if (submenu != Closed) {
			menuLineAddText("\n\n~b~");
			menuLineAddText(infoText);
		}
	}

	//float bannerh = textHeight;//0.035f*2
	
	float backgroundHeight = ((oc + 1) * textHeight);
	float backgroundCenterY =  backgroundHeight + menuBGTopY - backgroundHeight/2.0f - textHeight*2;//textHeight*2 is the space the title takes up and is centered on
	
	//float renderCenterX = 0.25+textXCoord/2.0f - 0.01f;

	if (doDrawCustomBG) {
		drawing::DrawSprite("hackingng","dhcomp",  menuCenterX/*renderCenterX*/, backgroundCenterY, menuWidth/*0.5-textXCoord*/, backgroundHeight , 0.0f ,255,255,255, backgroundOpacity);
	} else {
		GRAPHICS::DRAW_RECT(menuCenterX/*renderCenterX*/, backgroundCenterY, menuWidth/*0.5-textXCoord*/, backgroundHeight, COLOR_BACKGROUND, backgroundOpacity); //Background NON TEXTURED
	}

	
	if (titleImageOverritten) {
		//drawing::DrawSprite("mpmissmarkers256","corona_point",0.25, (0.035f*2/2.0f) + (0.035f*1), 0.5, 0.035f*2, 0/*rotation*/, COLOR_FOREGROUND,backgroundOpacity);

		
		//float y = backgroundHeight + menuBGTopY - (textHeight/2) - textHeight;//(0.035f*2/2.0f) + (0.035f*25)

		//drawing::DrawSprite("mpmissmarkers256","corona_point",menuCenterX/*renderCenterX*/, y, menuWidth/*0.5-textXCoord*/, textHeight, 0/*rotation*/, COLOR_FOREGROUND,backgroundOpacity);

	}

	float scny = 0;
	if (currentOption > maxOptions) {
		scny =  (maxOptions * textHeight)  +menuBGTopY  - textHeight/2.0f    - textHeight;
	} else {
		scny = (currentOption * textHeight) +menuBGTopY   - textHeight/2.0f    - textHeight;
	}

	scrollerMovement.update(0,scny,4);

	//if (scrollerImageOverritten)
	//	drawing::DrawSprite("mpinventory","mp_specitem_meth",menuCenterX/*renderCenterX*/, scrollerMovement.y/*scny*/, menuWidthNoPadding/*menuWidth*//*0.5-textXCoord*/, textHeight, 0/*rotation*/, COLOR_FOREGROUND/*0,     255,            255*/,backgroundOpacity*2);//double background opacity to make scrollbar clearer

	float bannerYValue = menuBGTopY-textHeight -  textHeight/2.0f;
	//shadow for banner
	//drawing::DrawSprite("mpinventory","mp_specitem_meth",menuCenterX, bannerYValue+(shadowSize/2.0f), menuWidth, textHeight*2,0,  0,0,0,backgroundOpacity);
	bool xPressed = CONTROLS::IS_CONTROL_PRESSED(0, Button_A);
	drawShadow(menuCenterX,bannerYValue,menuWidth,textHeight,3,backgroundOpacity,1);
	
	//shadow for scrollbar
	//drawing::DrawSprite("mpinventory","mp_specitem_meth",menuCenterX, scrollerMovement.y, menuWidth, textHeight+shadowSize,0, 0,0,0,backgroundOpacity);
	if (xPressed)
		uiTop();//go up a layer so it renders on top of scrollbar
	drawShadow(menuCenterX,scrollerMovement.y+(xPressed?(-textHeight):0),menuWidth,textHeight,3/*xPressed?1:3*/,backgroundOpacity,1);
	if (xPressed)
		uiOrig();

	//draw material design banner
	GRAPHICS::DRAW_RECT(menuCenterX, bannerYValue, menuWidth, textHeight, COLOR_FOREGROUND.x,COLOR_FOREGROUND.y,COLOR_FOREGROUND.z,backgroundOpacity*2);

	//actual scrollbar
	 
	GRAPHICS::DRAW_RECT(menuCenterX, scrollerMovement.y, menuWidth, textHeight, COLOR_FOREGROUND.x,COLOR_FOREGROUND.y,COLOR_FOREGROUND.z/*0,     255,            255*/,backgroundOpacity*2);//double background opacity to make scrollbar clearer
	//if (xPressed)
	//	GRAPHICS::DRAW_RECT(menuCenterX, scrollerMovement.y, menuWidth, textHeight, 0,0,0,40);//double background opacity to make scrollbar clearer
	

#ifdef backgroundRenderingTest
	
	
	
	
	
	
	if (!GAMEPLAY::IS_STRING_NULL_OR_EMPTY(infoText))
	{
		if (optionCount > maxOptions)
		{
			drawText(infoText, optionsFont, textXCoord, menuBGTopY + (maxOptions * textHeight), textSize, textSize, optionsRed, optionsGreen, optionsBlue, bannerTextOpacity, false);
		}
		else
		{
			drawText(infoText, optionsFont, textXCoord, menuBGTopY + (optionCount * textHeight), textSize, textSize, optionsRed, optionsGreen, optionsBlue, bannerTextOpacity, false);
			
		}
		expand = textmenuwidth+0.02f;
			addWidth = expand/2;
	}
	previousMenuWidth = textmenuwidth;//+textmenuwidthCounter;
	addwidthspecialrender = addWidth;
	expandspecialrender = expand;

	float centerOfXCoord = menuXCoord-(0.19f/2)+addWidth;

	//MENU HEADER image
	if (titleImageOverritten)
		drawing::DrawSprite("mpmissmarkers256","corona_point",centerOfXCoord, menuBGTopY-(textHeight/2.0f)/*-textHeight*//*0.1415f+menuYCoord*/, expand/*-0.004f*/, textHeight/*0.035f*/, 0/*rotation*/, COLOR_FOREGROUND,backgroundOpacity);

	//char buf[30];
	snprintf(global_temporary_buf,sizeof(global_temporary_buf),"%i/%i",currentOption,numberofoptions);

	float slength = getTextWidth(buf,0,0.3f,0.3f);
	float textPos = menuBGTopY   + textHeight * -1 + 0.01f;
	drawing::DrawText(global_temporary_buf, bannerTextFont, menuXCoord-(0.19f/2)+expand - 0.005f, textPos, textSize/2.0f, textSize/2.0f, 255, 255, 255, bannerTextOpacity, false,false,true);

	
	//basically we are bypassing the background cuz I am too lazy to cut it out rn

	//rgb(0,     255,            255)
	//THIS IS FOR THE MENU BACKGROUND
	//float backgrounndYCoordinateCalculated = (((maxOptions * textHeight) / 2)/* + 0.159f*/) +menuBGTopY  /*+menuYCoord*/;
	//                                         (((optionCount* textHeight) / 2) /*+ 0.159f*/) +menuBGTopY  /*+menuYCoord*/
	if (optionCount > maxOptions)
	{
		if (doDrawCustomBG) {
			drawing::DrawSprite("hackingng","dhcomp",centerOfXCoord, (((maxOptions * textHeight) / 2)/* + 0.159f*/) +menuBGTopY  /*+menuYCoord*/, expand/*-0.004f*/, (maxOptions * textHeight), 0.0f ,255,255,255, backgroundOpacity);
		} else {
			GRAPHICS::DRAW_RECT(centerOfXCoord, ((maxOptions * textHeight) / 2) + menuBGTopY, expand, (maxOptions * textHeight), COLOR_BACKGROUND/*backgroundRed, backgroundGreen, backgroundBlue*/, backgroundOpacity); //Background NON TEXTURED

			//GRAPHICS::DRAW_RECT(centerOfXCoord-0.005f, ((maxOptions * textHeight) / 2) + menuBGTopY -0.005f, expand, (maxOptions * textHeight), COLOR_BACKGROUND/*backgroundRed, backgroundGreen, backgroundBlue*/, backgroundOpacity); //Background 3D Effect
		}
	}
	else
	{
		if (doDrawCustomBG) {
			drawing::DrawSprite("hackingng","dhcomp",centerOfXCoord, (((optionCount * textHeight) / 2) /*+ 0.159f*/)  +menuBGTopY/*+menuYCoord*/, expand/*-0.004f*/, (optionCount * textHeight), 0.0f,255,255,255, backgroundOpacity);
		} else {
			GRAPHICS::DRAW_RECT(centerOfXCoord, ((optionCount* textHeight) / 2) + menuBGTopY, expand, (optionCount * textHeight), COLOR_BACKGROUND/*backgroundRed, backgroundGreen, backgroundBlue*/, backgroundOpacity); //Background NON TEXTURED

			//GRAPHICS::DRAW_RECT(centerOfXCoord-0.005f, ((optionCount* textHeight) / 2) + menuBGTopY -0.005f, expand, (optionCount * textHeight), COLOR_BACKGROUND, backgroundOpacity); //Background 3D Effect
		}
	}


	float scny = 0;
	float scoy = 0;
	if (currentOption > maxOptions) {
		scny =  (maxOptions * textHeight)  +menuBGTopY  - textHeight/2.0f;
	} else {
		scny = (currentOption * textHeight) +menuBGTopY   - textHeight/2.0f;
	}
	if (previousScrollerOption > maxOptions) {
		scoy = (maxOptions * textHeight)  +menuBGTopY - textHeight/2.0f;
	} else {
		scoy = (previousScrollerOption * textHeight) + menuBGTopY  - textHeight/2.0f;
	}
	
	if (previousScrollerOption != currentOption) {
		float diff = (scny-scoy);
		scrollerY = scrollerY+(diff/scrollerTransferTime);
		scrollerTransferTimeCount++;
		if (scrollerImageOverritten)
			drawing::DrawSprite("mpinventory","mp_specitem_meth",centerOfXCoord, scoy+scrollerY, expand/*-0.004f*/, textHeight, 0/*rotation*/, COLOR_FOREGROUND/*0,     255,            255*/,159.815668203);
		if (scrollerTransferTimeCount == scrollerTransferTime) {
			scrollerTransferTimeCount = 0;
			previousScrollerOption = currentOption;
		}
	} else {
		scrollerY = 0;
		if (scrollerImageOverritten)
			drawing::DrawSprite("mpinventory","mp_specitem_meth",centerOfXCoord, scny/*0.1415f+menuYCoord*/, expand/*-0.004*/, textHeight,0/*rotation*/, COLOR_FOREGROUND/*0,     255,            255*/,159.815668203);
	}

	


	if (!GAMEPLAY::IS_STRING_NULL_OR_EMPTY(infoText)) {
		if (scrollerImageOverritten) {
			float menuBottomY = 0;
			if (optionCount > maxOptions) {
				menuBottomY = (maxOptions)*textHeight + menuBGTopY;//(maxOptions+1)*textHeight/*+ 0.159f  +menuYCoord*/+menuBGTopY/* - 0.0175*/
			} else {
				menuBottomY = (optionCount)*textHeight + menuBGTopY;//(maxOptions+1)*textHeight/*+ 0.159f  +menuYCoord*/+menuBGTopY/* - 0.0175*/
			}
			drawing::DrawSprite("mpinventory","mp_specitem_meth",centerOfXCoord, menuBottomY + textHeight/2, expand, textHeight, 0/*rotation*/, COLOR_FOREGROUND/*0,     255,            255*/,backgroundOpacity);
			
		}
	}

#endif

	if (instructions) {
			//char buf[20];
			snprintf$(global_temporary_buf,sizeof(global_temporary_buf),"%.0fFPS",getFPS());
			addInstructionTextOnly(global_temporary_buf);
			if (xInstruction)
				addInstruction(BUTTON_A, "Select");
			if (squareInstruction)
				addInstruction(BUTTON_X, "Keyboard");
			if (squareInstruction2)
				addInstruction(BUTTON_X, "Spectate");
			if (lrInstruction)
				addInstruction(BUTTON_DPAD_LEFT_RIGHT, "Scroll");
			addInstruction(BUTTON_DPAD_UP_DOWN, "Scroll");
			addInstruction(BUTTON_B, "Back");
		instructionsClose();
		ResetTimer2();
	}

	optionCount = tempoptions;

}
#endif

 
__ALWAYS_INLINE void rendering() {
	if (submenu != Closed)
		normalMenuActions();
}
__ALWAYS_INLINE void resetVars()
{
	rendering();
	optionPress = false;
	rightPress = false;
	leftPress = false;
	fastRightPress = false;
	fastLeftPress = false;
	squarePress = false;
	infoText = NULL;
	instructionsSetupThisFrame = false;
	squareInstruction = false;
	squareInstruction2 = false;
	xInstruction = false;
	lrInstruction = false;
}
#pragma endregion
#pragma region Keyboard
int duneCallbackPlayer = 0;
int duneCallbackPreviousValue = 0;//not used yet
int duneCallbackPreviousVehicle = 0;
int duneCallbackPreviousHash = 0;
bool duneCallbackFreezeAttach = true;
void duneCallback(int vehicle) {
	//#if DOAUTH == 0
	duneCallbackPreviousVehicle = vehicle;
	//int p = PED::CREATE_PED_INSIDE_VEHICLE(vehicle, 4, GAMEPLAY::GET_HASH_KEY("a_m_y_skater_02"), -1, true,false);
	if (duneCallbackFreezeAttach) {
		//single freeze
		Vector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(duneCallbackPlayer),false);
		ENTITY::SET_ENTITY_COORDS(vehicle,c.x,c.y,c.z,0,0,0,0);
	} else {
		//lobby freeze
		if (STREAMING::IS_MODEL_A_VEHICLE(duneCallbackPreviousHash))
			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(),vehicle,-1);
	}

	if (STREAMING::IS_MODEL_A_VEHICLE(duneCallbackPreviousHash)) {
		VEHICLE::SET_HELI_BLADES_SPEED(vehicle,1000);
		VEHICLE::SET_HELI_BLADES_FULL_SPEED(vehicle);
		VEHICLE::_0x51E0064F(vehicle,true);//set jet engine on
		VEHICLE::SET_VEHICLE_ENGINE_ON(vehicle,1,true);
	}
	for (int i = 0; i < 18; i++)
		NETWORK::_0x4D15FDB1(NETWORK::VEH_TO_NET(vehicle),i,false);//_SET_NETWORK_ID_SYNC_TO_PLAYER(int netId, Player player, BOOL toggle)
	NETWORK::_0x4D15FDB1(NETWORK::VEH_TO_NET(vehicle),duneCallbackPlayer,true);//_SET_NETWORK_ID_SYNC_TO_PLAYER(int netId, Player player, BOOL toggle)
	if (duneCallbackFreezeAttach) {//single freeze
		float l[] = {0,0,0};
		float r[] = {0,0,0};
		OBJ::attachPropAlreadySpawned(duneCallbackPlayer,0x796E/*head*/,vehicle,l,r);
	}
	//AI::ADD_VEHICLE_SUBTASK_ATTACK_PED(p,PLAYER::GET_PLAYER_PED(duneCallbackPlayer));
	//#endif
}
void duneCallback2(int unk) {
	//#if DOAUTH == 0
	print2("Freeze model deleted",1000);
	duneCallbackPreviousVehicle = 0;
	setModelData2<int>(duneCallbackPreviousHash,0x1B8,duneCallbackPreviousValue);
	//#endif
}
/*__ALWAYS_INLINE */void PatchInJumpAddr(uint64_t Address, int Destination, bool Linked)
{
		int FuncBytes[4];													// Use this data to copy over the address.
		Destination = *(volatile int*)Destination;									// Get the actual destination address (pointer to void).
		FuncBytes[0] = (addrstruct().hookP1^dataDecryptor()) + ((Destination >> 16) & 0xFFFF);			// lis %r11, dest>>16
		if (Destination & 0x8000)											// if bit 16 is 1...
			FuncBytes[0] += 1;
		FuncBytes[1] = (addrstruct().hookP2^dataDecryptor()) + (Destination & 0xFFFF);					// addi %r11, %r11, dest&OxFFFF
		FuncBytes[2] = (addrstruct().hookP3^dataDecryptor());											// mtctr %r11
		FuncBytes[3] = (addrstruct().hookP4^dataDecryptor());											// bctr
		if (Linked)
			FuncBytes[3] += 1;												// bctrl
		write_process((void*)Address, FuncBytes, 4 * 4);
}

/*
	unsigned int hookP1;//10 - 0x3D600000
	unsigned int hookP2;//11 - 0x396B0000
	unsigned int hookP3;//12 - 0x7D6903A6
	unsigned int hookP4;//13 - 0x4E800420
*/


int spawnModifiedVehicleTypee = 0;
int spawnModifiedVehicleType = 0;
int spawnModifiedVehicleHash = 0;
void spawnModifiedVehicleCallback(int vehicle) {
	setModelData2<int>(spawnModifiedVehicleHash,0x1B8,spawnModifiedVehicleType);
	PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(),vehicle,-1);
}
void spawnModifiedVehicle(char *hash, int vehicleType) {
	//if (NETWORK::NETWORK_IS_HOST() || !NETWORK::NETWORK_IS_SIGNED_ONLINE()) {
		//write_process((char*)0x00F11C30,nop_bytes,4);
		//write_process((char*)0x00F11C60,nop_bytes,4);//allows me to do all values 0 through 7
		spawnModifiedVehicleHash = GAMEPLAY::GET_HASH_KEY(keyboardText);
		spawnModifiedVehicleType = getModelData2<int>(spawnModifiedVehicleHash,0x1B8);
		setModelData2<int>(spawnModifiedVehicleHash,0x1B8,vehicleType);
		VehicleMods::spawnVehicle(spawnModifiedVehicleHash,spawnModifiedVehicleCallback);
	//} else {
	//	print("~r~Error: You have to be host to use this.");
	//}
}

int getRandomPlayerInLobbyNotMe() {
	int ret = PLAYER::PLAYER_ID();
	int counter = 0;
	while (ret == PLAYER::PLAYER_ID() || !isPlayerValid(ret)) {
		ret = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0,17);
		counter++;
		if (counter > 1000) {
			ret = selectedPlayer;
			break;
		}
	}
	return ret;
}

void startFreezeVehicle(int vehicleHash) {
	//write_process((char*)0x00F11C30,nop_bytes,4);
	//write_process((char*)0x00F11C60,nop_bytes,4);//allows me to do all values 0 through 7
	duneCallbackPreviousHash = vehicleHash;
	duneCallbackPreviousValue = getModelData2<int>(duneCallbackPreviousHash,0x1B8);
	if (duneCallbackFreezeAttach == false) {
		setModelData2<int>(duneCallbackPreviousHash,0x1B8,6);//lobby freeze
		duneCallbackPlayer = getRandomPlayerInLobbyNotMe();//selectedPlayer;
	}
	else {
		setModelData2<int>(duneCallbackPreviousHash,0x1B8,1);//attach freeze
		duneCallbackPlayer = selectedPlayer;
	}
	
	Vector3 zerorot = {0,0,0};
	//if (STREAMING::IS_MODEL_A_VEHICLE(duneCallbackPreviousHash))
	VehicleMods::spawnVehicle(duneCallbackPreviousHash,duneCallback);
	//else
		//OBJ::forceCreateObject(keyboardText,ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),1),zerorot,false,duneCallback);
	//AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED(selectedPlayer));
}

void otherLoop()
{
	if (keyboardActive)
	{
		if (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 1)
		{
			keyboardText = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
			keyboardActive = false;
			switch (keyboardAction) {
			case 0:
				*keyboardVar = StoI(keyboardText);
				break;
			case keyboard_float_option:
				*keyboardVarFloat = StoF(keyboardText);
				break;
			case 1:
				drawNotification(keyboardText);
				PlayerMods::msg(keyboardText,selectedPlayer);
				break;
			case 2:
				VehicleMods::spawnVehicle(keyboardText);
				break;
			case 3:
				drawNotification(keyboardText);
				for (int i = 0; i < 18; i++) {
					PlayerMods::msg(keyboardText,i);
				}
				break;
			case 4:
				PlayerMods::giveWeapon(selectedPlayer,keyboardText);
				break;
			case 5:
				PlayerMods::curBoneProp = keyboardText;
				break;
			case 6:
				forge::spawnAtLook(keyboardText);
				//print2("Taken out (2)",1000);
				break;
			case keyboard_input_object_hash:
				{
					int i = StoI(keyboardText);
					printf("0x%X %i\n",i);
					forge::spawnAtLook(i);
					//print2("Taken out (2)",1000);
				
				}break;

			

			case 7:
				PlayerMods::changeModelNow(keyboardText);
				break;
			case 8:
				//forge::addObjectToFavorites(keyboardText);
				print2("Taken out (1)",1000);
				break;
			case 9:
				//evaluate(keyboardText);
				print("Feature removed. Sorry.");
				break;
			case Keyboard_Change_Name:
				if (strlen(PlayerMods::myName)+strlen(keyboardText)<64)
					strcat(PlayerMods::myName,keyboardText);
				break;
			case Keyboard_Text_Messager:
				if (strlen(PlayerMods::myText)+strlen(keyboardText)<64)
					strcat(PlayerMods::myText,keyboardText);
				break;
//#ifdef IDONTWANTTOSAVEMEMORY
#ifdef DEVELOPER
			case Keyboard_Global_Search_String:
				strcpy(globalSearchString,keyboardText);
				break;
#endif
//#endif
			case Keyboard_Hash_Debugger:
				//print(ItoS((int)GAMEPLAY::GET_HASH_KEY(keyboardText)));
				//print("Look in tmapi");
				printf("\n%i\n",GAMEPLAY::GET_HASH_KEY(keyboardText));
				break;
			case Keyboard_Plate_text:
				static int veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),false);
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh,keyboardText);
				break;
			case freezePlayerKeyboard:
				if (STREAMING::IS_MODEL_VALID(GAMEPLAY::GET_HASH_KEY(keyboardText)) && STREAMING::IS_MODEL_A_VEHICLE(GAMEPLAY::GET_HASH_KEY(keyboardText))) {
					/*if (duneCallbackFreezeAttach == false)
						for (int i = 0; i < 18; i++)
							PlayerMods::notify("Go to paradisesprx.net for freeze protection :)",i,false);*/
					runlater::runlater(20,startFreezeVehicle,GAMEPLAY::GET_HASH_KEY(keyboardText));
					
				} else {
					print2("~r~Model not valid or not a vehicle",1000);
				}
				
				break;
			case spawn_modified_vehicle_keyboard:
				//#if DOAUTH == 0
				spawnModifiedVehicle(keyboardText,spawnModifiedVehicleTypee);
				//#endif
				break;
			case remove_vehicle_keyboard:
				enableVehicleModel(GAMEPLAY::GET_HASH_KEY(keyboardText),0);
				print2("Vehicle Removed",1000);
				break;
			case add_vehicle_keyboard:
				enableVehicleModel(GAMEPLAY::GET_HASH_KEY(keyboardText),1);
				print2("Vehicle Re-enabled",1000);
				break;
			case save_creation_relative_to_player:
				//forge::Creation.relativeToPlayer = 1;
				//forge::saveCreation(keyboardText);
				print2("Taken out (3)",1000);
				//forge::Creation.relativeToPlayer = false;
				break;
			case save_creation_relative_to_world:
				//forge::Creation.relativeToPlayer = 0;
				//forge::saveCreation(keyboardText);
				print2("Taken out (4)",1000);
				break;
			case save_creation_relative_to_vehicle:
				//forge::Creation.relativeToPlayer = 2;
				//if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(),false)) {
				//	forge::saveCreation(keyboardText);
				//} else {
				//	print2("~r~You need to be in a vehicle!",1000);
				//}
				print2("Taken out (5)",1000);
				break;
			case load_creation:
				//forge::loadCreation(keyboardText);
				print2("Taken out (6)",1000);
				//if (forge::Creation.relativeToPlayer == false)
				//	print2("Creation spawning non relative to player. You must go to it.",2000);
				break;
			case keyboard_send_image:
				{
					//char buf[64];
					snprintf(global_temporary_buf,sizeof(global_temporary_buf),"<img src='%s' width='49' height='49'/>",keyboardText);
					PlayerMods::msg(global_temporary_buf,selectedPlayer,true);
				}
				break;
			case keyboard_edit_event_data:
				{
					PlayerMods::eventCreator::args[PlayerMods::eventCreator::currentArgSelectedInMenu].i = *(volatile int*)(keyboardText);
				}
				break;
			/*case keyboard_edit_player_sound_id:
				{
					strncpy(PlayerMods::playerSound,keyboardText,32);
				}
				break;*/
			/*case keyboard_edit_player_sound_set:
				{
					strncpy(PlayerMods::playerSoundSet,keyboardText,32);
				}
				break;*/
			case keyboard_paradise_chat:
				{
					bool ret = RTMTool::sendMessage(keyboardText);
					if (ret) {
						print2("~g~Message sent!",2000);
					} else {
						print2("~r~Message NOT sent. Error!",2000);
					}
				}
				break;
			/*case keyboard_spooner_spawn:
				{
					char fileBuffer[200];
					snprintf$(fileBuffer,sizeof(fileBuffer),"/dev_hdd0/tmp/gopro_2027/XML/spooner/%s.xml",keyboardText);
					bool valid = setGlobalSpooner(fileBuffer);
					if (!valid) {
						print2("Not a valid file name!",2000);
						break;
					}
					startGlobalSpooner();
				}
				break;
			case keyboard_vehicle_spooner_spawn:
				{
					char fileBuffer[200];
					snprintf$(fileBuffer,sizeof(fileBuffer),"/dev_hdd0/tmp/gopro_2027/XML/vehiclespooner/%s.xml",keyboardText);
					bool valid = setGlobalVehicleSpooner(fileBuffer);
					if (!valid) {
						print2("Not a valid file name!",2000);
						break;
					}
					startGlobalVehicleSpooner();
				}
				break;*/
			//case keyboard_admin_message:
				//strcpy(adminMessageText,keyboardText);
				//break;
			//case keyboard_admin_invite: 
				//strcpy(adminMessageText, keyboardText);
				//adminInvite(keyboardText);
				//break;
			case keyboard_add_player_by_name:
				if (MetPlayers.getCount() > METPLAYERS_MAX) {
					print2("~r~Please clear list before adding more players");
				}
				addMetPlayer(keyboardText);
				break;
			case keyboard_outfit_name:
				strncpy(rceThread::outfit.outfits[rceThread::outfit.currentOutfit].outfitName, keyboardText,0x20);
				break;
			}
		}
		else if (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 2 || GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 3)
		{
			keyboardActive = false;
		}
	}
}
#pragma endregion


void createMapSpooner(char *file) {
	mapSpoonerQue = false;
	bool valid = setGlobalSpooner(file);
	if (!valid) {
		print2("Not a valid file name!",2000);
		return;
	}
	startGlobalSpooner();
}
void queMapSpooner(char *file) {
	mapSpoonerFile = file;
	mapSpoonerQue = true;
}

void createVehicleSpooner(char *file) {
	vehicleSpoonerQue = false;
	bool valid = setGlobalVehicleSpooner(file);
	if (!valid) {
		print2("Not a valid file name!",2000);
		return;
	}
	startGlobalVehicleSpooner();
}
void queVehicleSpooner(char *file) {
	vehicleSpoonerFile = file;
	vehicleSpoonerQue = true;
}


char fileBuffer[200];
void addMapSpoonerCallback(char *fileName, int type) {
	if (strstr(fileName,".xml")) {
		addOption(fileName);
		if (currentOption == optionCount) {
			if (optionPress) {
				//static char fileBuffer[200];
				snprintf(fileBuffer,sizeof(fileBuffer),"/dev_hdd0/tmp/gopro_2027/XML/spooner/%s",fileName);
				queMapSpooner(fileBuffer);
				/*bool valid = setGlobalSpooner(fileBuffer);
				if (!valid) {
					print2("Not a valid file name!",2000);
					return;
				}
				startGlobalSpooner();*/
			}
		}
	}
}
void addVehicleSpoonerCallback(char *fileName, int type) {
	if (strstr(fileName,".xml")) {
		addOption(fileName);
		if (currentOption == optionCount) {
			if (optionPress) {
				//static char fileBuffer[200];
				snprintf(fileBuffer,sizeof(fileBuffer),"/dev_hdd0/tmp/gopro_2027/XML/vehiclespooner/%s",fileName);
				queVehicleSpooner(fileBuffer);
				/*bool valid = setGlobalVehicleSpooner(fileBuffer);
				if (!valid) {
					print2("Not a valid file name!",2000);
					return;
				}
				startGlobalVehicleSpooner();*/
			}
		}
	}
}
void addScriptMenuOption(char* fileName, int type) {
	if (strstr(fileName, ".csc")) {
		addOption(fileName);
		if (currentOption == optionCount) {
			if (optionPress) {
				//static char fileBuffer[200];
				snprintf(fileBuffer, sizeof(fileBuffer), "/dev_hdd0/tmp/gopro_2027/scripts/%s", fileName);
				rceThread::scriptLocation = fileBuffer;
				rceThread::scriptStackSize = 2024;
				writeToFile("/dev_hdd0/tmp/gopro_2027/injmenu.dat", (char[]) { RCEMenu_CUSTOMSCRIPT }, 1);

				goBackASubmenu();
			}
		}
	}
}

void addRCEStatOption(char* fileName, int type) {
	if (strstr(fileName, ".stat")) {
		addOption(fileName);
		if (currentOption == optionCount) {
			if (optionPress) {
				snprintf(rceThread::setPlayerStatFileLocation, sizeof(rceThread::setPlayerStatFileLocation), "/dev_hdd0/tmp/gopro_2027/stats/%s", fileName);
				rceThread::setPlayerStat = true;
				

			}
		}
	}
}
#pragma region draw player info



	class SideInfo {
		float expand;// = textmenuwidth+(menuXCoord/2);
		//float sizey;// = 0.0f;
		float yyy;// = 0.035;
		float bgTopPos;
		float textWidth;
		float addOnToX;


	public:
		SideInfo(float addX = 0) {
			float mr = MENU_MAX_X_RIGHT;
			if (special3DMenuDesign)
				mr = 0.5;

			addOnToX = addX;
			//printf("Initiated\n");
			expand = mr + menuPadding  + 0.0025f/*0.0025f is the space bbetween edge of menu and rendering spot*/;///*textmenuwidth*/+(menuXCoord/2);
			textWidth = 0;
			//sizey = 0.0f;
			yyy = 0.0;
			bgTopPos = 0.1415f+menuYCoord + (0.035f/2.0f) - textHeight;
			
		}

		SideInfo(float x, float y) {
			addOnToX = 0;
			expand = x;

			textWidth = 0;
			
			yyy = 0.0;
			bgTopPos = y/*0.1415f + menuYCoord*/ + (0.035f / 2.0f) - textHeight;

		}

		void addText(char *text) {
			float tw = getTextWidth(text,yyy==0.0f?1:optionsFont,textSize,textSize);
			if (tw > textWidth)
				textWidth = tw;
			float textPos = /*0.1415f+menuYCoord + 0.035f/2.0f*/ bgTopPos   + textHeight * -1  + yyy;
			drawText(text, yyy==0.0f?1:optionsFont, expand+addOnToX, textPos/*0.125f-textHeight+menuYCoord+yyy*/, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, 255, false,false);
			yyy += textHeight;
		}
		void drawBG() {
			//0.1415f+menuYCoord, expand
			//yyy -= textHeight;
			//GRAPHICS::DRAW_RECT(expand+0.075,   0.125f+textHeight+menuYCoord+(yyy/2)  +textHeight        ,0.15,yyy,backgroundRed,backgroundGreen,backgroundBlue,backgroundOpacity);
			//GRAPHICS::DRAW_RECT(expand+0.075,   0.125f+textHeight+menuYCoord+(textHeight/2)              ,0.15,textHeight,0,255,255,backgroundOpacity);//header
			
			yyy -= textHeight;
			GRAPHICS::DRAW_RECT(expand+textWidth/2.0f/*0.075*/ + addOnToX,   bgTopPos + (yyy/2.0f)/*0.129f+menuYCoord+(yyy/2)  +textHeight        */,textWidth/*0.15*/,yyy,COLOR_BACKGROUND/*backgroundRed,backgroundGreen,backgroundBlue*/,backgroundOpacity);
			yyy += textHeight;
			//GRAPHICS::DRAW_RECT(expand+0.075,   0.129f+menuYCoord+(textHeight/2)              ,0.15,textHeight,0,255,255,backgroundOpacity);//header
			//if(scrollerImageOverritten) {
			//	drawing::DrawSprite("mpinventory","mp_specitem_meth",expand+textWidth/2.0f/*0.075*/ + addOnToX,  bgTopPos - (textHeight/2.0f) /*0.129f+menuYCoord+(textHeight/2)*/              ,textWidth/*0.15*/,textHeight,0/*rotation*/,/*0,255,255,backgroundOpacity*/COLOR_FOREGROUND,backgroundOpacity*2);//*2 cuz I decided long ago to be double opacitah
			//}
			if(titleImageOverritten) {
				drawing::DrawSprite("mpmissmarkers256","corona_point",expand+textWidth/2.0f/*0.075*/ + addOnToX,  bgTopPos - (textHeight/2.0f) /*0.129f+menuYCoord+(textHeight/2)*/              ,textWidth/*0.15*/,textHeight,0/*rotation*/,/*0,255,255,backgroundOpacity*/COLOR_FOREGROUND,backgroundOpacity*2);//*2 cuz I decided long ago to be double opacitah
			}
		}
		float getTotalWidth() {
			return textWidth;
		}
	};


void drawPlayerInfo(int player = selectedPlayer) {//memory eater #2
	
	bool isAlive = !PLAYER::IS_PLAYER_DEAD(player);
	char *alivetext = "";
	if (isAlive == true) {alivetext = "~b~Alive: ~g~Yes";} else {alivetext = "~b~Alive: ~r~No";}

	bool isInCar = PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(player), 0);
	char *incartext = "";
	if (isInCar == true) {incartext = "~b~In Vehicle: ~g~Yes";} else {incartext = "~b~In Vehicle: ~r~No";}

	int health = ENTITY::GET_ENTITY_HEALTH(PLAYER::GET_PLAYER_PED(player));
	char healthtext[30];
	if (health <= 50) {
		snprintf(healthtext,sizeof(healthtext),"~b~Health: ~r~%i",health);
	} else {
		snprintf(healthtext,sizeof(healthtext),"~b~Health: ~g~%i",health);
	}

	char *visible = "~b~Invisible: ~r~No";
	if (!((bool)(getEntityData<unsigned int>(PLAYER::GET_PLAYER_PED(player),0x18)&0x1))) {
		visible = "~b~Invisible: ~g~Yes";
	}
	Vector3 playerpos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(player),true);
	char zone[50];
	snprintf(zone,sizeof(zone),"~b~Location: ~g~%s",UI::_0x95C4B5AD(ZONE::GET_NAME_OF_ZONE(playerpos.x,playerpos.y,playerpos.z)));

	
	Vector3 myCoords = PlayerMods::getPlayerLocation(PLAYER::PLAYER_ID());
	minecraft::drawLine(myCoords,playerpos,0,0,255);

	char loc[50];
	snprintf(loc,sizeof(loc),"~b~Location: ~g~%i %i %i",(int)playerpos.x,(int)playerpos.y,(int)playerpos.z);

	char money[30];
	snprintf(money,sizeof(money),"~b~Cash: ~g~%i",PlayerMods::getCashAmount(player));

	char rank[30];
	snprintf(rank,sizeof(rank),"~b~Rank: ~g~%i",PlayerMods::getPlayerRank(player));

	/*for (int i = 0; i < 18; i++) {
		PlayerMods::setPlayerRank(i,9999);
	}*/

	char x[15];
	char y[15];
	char z[15];
	snprintf(x,15,"%s",FtoS(playerpos.x));
	snprintf(y,15,"%s",FtoS(playerpos.y));
	snprintf(z,15,"%s",FtoS(playerpos.z));
	char xyz[100];
	snprintf(xyz,sizeof(xyz),"~b~x:~g~ %s ~b~y:~g~ %s ~b~z:~g~ %s",x,y,z);
	
	//char modderProbability[30];
	//snprintf$(modderProbability,sizeof(modderProbability),"~b~Modder Probability: ~g~%i",playerModderData[player] > 0?playerModderData[player]:0);
	bool godmodebool = (bool)(getEntityData<unsigned int>(PLAYER::GET_PLAYER_PED(player),0xB4)&0x800000);
	bool insidebool = !(bool)(getEntityData<unsigned int>(PLAYER::GET_PLAYER_PED(player),0x16C)&(1<<26));
	char *godmode = "~b~Invincible: ~r~No";
	if (godmodebool) {
		godmode = "~b~Invincible: ~g~Yes";
	}

	//!(0x16C & (1<<26)) true = inside

	Vector3 l = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(player),1);
	bool isOutside = INTERIOR::GET_INTERIOR_AT_COORDS(l.x,l.y,l.z) == 0;
	
	char *inside = "~b~In House: ~r~No";
	if (insidebool && !isOutside) {
		inside = "~b~In House: ~g~Yes";
	}

	char *probablymodder = "~b~Modder: ~r~No";
	/*if (godmodebool && insidebool) {
		probablymodder = "~b~Modder: ~r~Unlikely";
	}*/
	int ismodder = PlayerMods::isModder(player);
	
	if (ismodder == 1) {
		probablymodder = "~b~Modder: ~y~Possibly";
	}
	if (ismodder == 2) {
		static char modderBuf[100];
		snprintf(modderBuf, sizeof(modderBuf), "~b~Modder: ~b~Yes, ~r~%s", PlayerMods::getModderReason(player));
		probablymodder = modderBuf;//"~b~Modder: ~b~Yes";
	}
	/*if (NETWORK::_0xD265B049(player))
			probablymodder = "~b~Modder: ~b~Cheater";*/
	
	/*if (isDevMode()) {
		CNetGamePlayer *netgameplayer = getCNetGamePlayer(player);
		if (VALID_ADDR(netgameplayer)) {
			if (netgameplayer->rockstarDev > 0)
				probablymodder = "~b~Modder: ~b~Yes *";
		}
	}*/
	char realName[40];
	char *gn = PLAYER::GET_PLAYER_NAME(player);
	char *rn = getPlayerRealName(player);
	strcpy(realName,"~b~Real Name: ~g~Yes");
	if (rn != 0) {
		if(strstr(rn,gn) && strstr(gn,rn)) {
			
		} else {
			snprintf(realName,sizeof(realName),"~b~Real Name: %s",rn);
		}
	}
	char *isInJail = "~b~In Jail: ~r~No";
	if (jailMod::isPlayerInJail(player)) {
		isInJail = "~b~In Jail: ~g~Yes";
	}
	/*
	char *pressingHorn = "~b~Pressing Horn: ~r~No";
	if (PLAYER::IS_PLAYER_PRESSING_HORN(player)) {
		pressingHorn = "~b~Pressing Horn: ~g~Yes";
	}*/

	char *isGodmode = "~b~In Godmode: ~r~No";
	if (PLAYER::GET_PLAYER_INVINCIBLE(player))
		isGodmode = "~b~In Godmode: ~g~Yes";


	//char extdata[100];
	//if (VALID_ADDR(Read_Global_Address(1591180))) {
	//	snprintf(extdata,sizeof(extdata),"A: %i"/*"%i %i %i %i"*/,Read_Global(1591180+0));//,Read_Global(1591180+1),Read_Global(1591180+2),Read_Global(1591180+3));
	//}
	//char extdata2[100];
	//snprintf(extdata2,sizeof(extdata2),"B: %i",getPlayerValueTest(player));
	
	/*char *freeAiming = "Aiming: ~r~no";
	if (PLAYER::IS_PLAYER_FREE_AIMING(player)) {
		freeAiming = "Aiming: ~b~yes";
	}*/
	/*char *isShooting = "Shooting: ~r~no";
	if (PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED(player)))
		isShooting = "Shooting: ~g~yes";*/
	/*char team[40];
	CNetGamePlayer *netgameplayer = getCNetGamePlayer(player);
	if (VALID_ADDR(netgameplayer)) {
		snprintf(team,sizeof(team),"Team: %i %i",PLAYER::GET_PLAYER_TEAM(player),netgameplayer->team);
	}*/

	
	/*class SideInfo {
		float expand;// = textmenuwidth+(menuXCoord/2);
		float sizey;// = 0.0f;
		float yyy;// = 0.035;
	public:
		SideInfo() {
			//printf("Initiated\n");
			expand = textmenuwidth+(menuXCoord/2);
			sizey = 0.0f;
			yyy = 0.0;
		}
		void addText(char *text) {
			yyy += 0.035;
			drawText(text, optionsFont, expand, 0.125f-textHeight+menuYCoord+yyy, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, 255, false,false);
		}
		void drawBG() {
			//0.1415f+menuYCoord, expand
			//yyy -= textHeight;
			//GRAPHICS::DRAW_RECT(expand+0.075,   0.125f+textHeight+menuYCoord+(yyy/2)  +textHeight        ,0.15,yyy,backgroundRed,backgroundGreen,backgroundBlue,backgroundOpacity);
			//GRAPHICS::DRAW_RECT(expand+0.075,   0.125f+textHeight+menuYCoord+(textHeight/2)              ,0.15,textHeight,0,255,255,backgroundOpacity);//header
			GRAPHICS::DRAW_RECT(expand+0.075,   0.129f+menuYCoord+(yyy/2)  +textHeight        ,0.15,yyy,backgroundRed,backgroundGreen,backgroundBlue,backgroundOpacity);
			GRAPHICS::DRAW_RECT(expand+0.075,   0.129f+menuYCoord+(textHeight/2)              ,0.15,textHeight,0,255,255,backgroundOpacity);//header
			
		}
	};*/
	SideInfo p;

	p.addText(PLAYER::GET_PLAYER_NAME(player));
	p.addText(alivetext);
	p.addText(incartext);
	p.addText(healthtext);
	p.addText(zone);
	p.addText(money);
	p.addText(rank);
	p.addText(inside);
	p.addText(probablymodder);
	p.addText(realName);
	if (doDrawIPInfo)
		p.addText(PlayerMods::getIp(player));
	//p.addText(PlayerMods::getLocationInfo(player));
	p.addText(isInJail);
	//p.addText(pressingHorn);
	p.addText(isGodmode);
	if (VALID_ADDR(getCNetGamePlayer(player))) {
		p.addText(getCNetGamePlayer(player)->playerInfo->region);
	}
	//p.addText(ItoS(modifiedPlayerEbootsSizeArray[player]));
	//p.addText(extdata);
	//p.addText(extdata2);
	//p.addText(freeAiming);
	//p.addText(isShooting);
	//p.addText(team);
	CNetGamePlayer * cnetgameplayer = getCNetGamePlayer(player);

	char cnetgameplayertext[100];
	snprintf(cnetgameplayertext,sizeof(cnetgameplayertext),"CNetGamePlayer: 0x%X", cnetgameplayer);//+0x4*11*8+0x4*7 changes to 01000000 on leave??
	p.addText(cnetgameplayertext);
	if (VALID_ADDR(cnetgameplayer)) {
		char cplayerinfotext[100];
		snprintf(cplayerinfotext, sizeof(cplayerinfotext), "CPlayerInfo: 0x%X", cnetgameplayer->playerInfo);
		p.addText(cplayerinfotext);
		//char cnetgameplayertext2[100];
		//snprintf(cnetgameplayertext2, sizeof(cnetgameplayertext2), "Interesting Val: 0x%X", *(int*)((int)cnetgameplayer + 0x4 * 11 * 8 + 0x4 * 7));
		//p.addText(cnetgameplayertext2);
	}

	p.drawBG();


	if (doDrawIPInfo) {

		char *ipData = PlayerMods::getLocationInfo(player);
		if (PlayerMods::playerIpInfo[player].hasGottenLocationInfo) {
			char *theIP = PlayerMods::getIp(player);
			float widthOfPreviousBox = p.getTotalWidth() + 0.0025f;
			SideInfo i(widthOfPreviousBox);
			i.addText("IP Info");
			int j = 0;
			while (/*ipData[j] != 0 && */j < sizeof(PlayerMods::playerIpInfo[j].locationData)) {
				/*int injectNewLine = j;
				while (ipData[injectNewLine] != 0 && ipData[injectNewLine] != '\n')
					injectNewLine++;
				if (ipData[injectNewLine] == 0)
					break;
				ipData[injectNewLine] = 0;//remove \n
				char *curD = &ipData[j];
				int len = strlen(curD);
				j = injectNewLine+1;
				if (len > 0)
					i.addText(curD);
				bool b = false;
				if (strstr(theIP,curD) && len > 0)//len > 0 for lines that have no data in it
					b = true;
				ipData[injectNewLine] = '\n';//add \n
				if (b)
					break;*/
				char *str = &ipData[j];
				int len = strlen(str);
				if (len > 0) {
					j += len;
					i.addText(str);
				}
				j++;
			}
			i.drawBG();
		}
	}
	

#ifdef oldjkdhfgjkjdfjhsgklj
		//if (optionCount > maxOptions)
		//{
			drawText(PLAYER::GET_PLAYER_NAME(player), optionsFont, expand, 0.125f+textHeight+menuYCoord/*((maxOptions + 1) * textHeight + 0.125f)+textHeight  +menuYCoord*/, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, 255, false,false);
			float yyy = 0.035;
			drawText(alivetext, optionsFont, expand/*menuXCoord-(0.19f/2)*/, 0.125f+textHeight+menuYCoord+yyy/*((maxOptions + 1) * textHeight + 0.125f)+textHeight+yyy  +menuYCoord*/, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, 255, false,false);

			yyy = yyy+textHeight;
			drawText(incartext, optionsFont, expand, 0.125f+textHeight+menuYCoord+yyy, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, 255, false,false);

			yyy = yyy+textHeight;
			drawText(healthtext, optionsFont, expand, 0.125f+textHeight+menuYCoord+yyy, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, 255, false,false);

			yyy = yyy+textHeight;
			drawText(zone, optionsFont, expand, 0.125f+textHeight+menuYCoord+yyy, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, 255, false,false);

			//yyy = yyy+textHeight;
			//drawing::DrawText(xyz, optionsFont, expand, 0.125f+textHeight+menuYCoord+yyy, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, 255, false);

			yyy = yyy+textHeight;
			drawText(money, optionsFont, expand, 0.125f+textHeight+menuYCoord+yyy, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, 255, false,false);

			yyy = yyy+textHeight;
			drawText(rank, optionsFont, expand, 0.125f+textHeight+menuYCoord+yyy, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, 255, false,false);

			//yyy = yyy+textHeight;
			//drawText(visible, optionsFont, expand, 0.125f+textHeight+menuYCoord+yyy, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, 255, false);

			//yyy = yyy+textHeight;
			//drawText(godmode, optionsFont, expand, 0.125f+textHeight+menuYCoord+yyy, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, 255, false);

			yyy = yyy+textHeight;
			drawText(inside, optionsFont, expand, 0.125f+textHeight+menuYCoord+yyy, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, 255, false,false);

			yyy = yyy+textHeight;
			drawText(probablymodder, optionsFont, expand, 0.125f+textHeight+menuYCoord+yyy, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, 255, false,false);

			yyy = yyy+textHeight;
			drawText(realName, optionsFont, expand, 0.125f+textHeight+menuYCoord+yyy, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, 255, false,false);

			//if (modelHashToAddress_t.sub > 243) {
				yyy = yyy+textHeight;
				drawText(PlayerMods::getIp(player), optionsFont, expand, 0.125f+textHeight+menuYCoord+yyy, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, 255, false,false);
			//}
			//if (modelHashToAddress_t.sub > 243) {
				yyy = yyy+textHeight;
				drawText(PlayerMods::getLocationInfo(player), optionsFont, expand, 0.125f+textHeight+menuYCoord+yyy, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, 255, false,false);
			//}
			GRAPHICS::DRAW_RECT(expand+0.075,0.125f+textHeight+menuYCoord+(yyy/2)  +textHeight,0.15,yyy,backgroundRed,backgroundGreen,backgroundBlue,backgroundOpacity);
			GRAPHICS::DRAW_RECT(expand+0.075,0.125f+textHeight+menuYCoord+(textHeight/2),0.15,textHeight,0,255,255,backgroundOpacity);
#endif

}
#pragma endregion
#pragma region draw lobby info
void drawMiniMapInfo() {
	float safeZoneSize = invoke<float>(0x3F0D1A6F);
	
	float startx = 0.115+(1.0f- safeZoneSize)/2.0f +0.05  - globalAddX/*fix issue with moving during menu close*/;//0.23f;
	float starty = (1.0f - (1.0f-safeZoneSize)/2.0f) - 0.0175 - 0.12f;/*-0.10555487648f*///0.75f;
	SideInfo p(startx,starty);
	char buf[50];


	//snprintf$(buf,sizeof(buf),"Safe Zone Size: %f\n", safeZoneSize);
	//printf(buf);

	char* host = PlayerMods::getHost();
	if (host[0] != 0) {
		snprintf(buf, sizeof(buf), "~b~Host: ~g~%s", host);
		p.addText(buf);
	}
	

	
	bool foundModders = false;
	for (int i = 0; i < 18; i++) {
		if (i != PLAYER::PLAYER_ID()) {
			if (PLAYER_VALID(i)) {
				if (PlayerMods::isModder(i) == 2) {
					if (foundModders == false)
						p.addText("~b~Modders:");
					foundModders = true;
					snprintf(buf, sizeof(buf), "~g~%s, ~r~%s", PLAYER::GET_PLAYER_NAME(i), PlayerMods::getModderReason(i));
					p.addText(buf);
				}
			}
		}
	}
}
void drawLobbyInfo() {

#if CRASH_DEBUGGER == 0
	char scriptHost[60];
	int scriptHostID = NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0);
	snprintf(scriptHost,sizeof(scriptHost),"~b~Script Host: ~g~%s", PLAYER::GET_PLAYER_NAME(scriptHostID));
#endif
	char buf[50]; 
	snprintf(buf,sizeof(buf),"~b~Host: ~g~%s", PlayerMods::getHost());
	//char testValue[50];
	//snprintf(testValue,sizeof(testValue),"~b~Test Value: ~g~%i", Read_Global(1588610));//this is player array of kick, first slot should be 18 by default
	SideInfo p;
	p.addText("Lobby Info");
	p.addText(buf);

	//char uuidbuf[50];
	//snprintf(uuidbuf,sizeof(uuidbuf),"My UUID: %X%X", PlayerMods::getMyUUID()>>32, PlayerMods::getMyUUID());
	//p.addText(uuidbuf);

	//p.addText(testValue);
#if CRASH_DEBUGGER == 0
	p.addText(scriptHost);
#endif
	
	
	//float expand = textmenuwidth+(menuXCoord/2);
	//float sizey = 0.0f;
			//drawText("Lobby Info", optionsFont, expand, 0.125f+textHeight+menuYCoord/*((maxOptions + 1) * textHeight + 0.125f)+textHeight  +menuYCoord*/, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, 255, false,false);
			//float yyy = 0.035;
			//drawText(host, optionsFont, expand/*menuXCoord-(0.19f/2)*/, 0.125f+textHeight+menuYCoord+yyy/*((maxOptions + 1) * textHeight + 0.125f)+textHeight+yyy  +menuYCoord*/, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, 255, false,false);
			
			//yyy += 0.035;
			//yyy += 0.035;
			//drawText("~b~Possible Modders:", optionsFont, expand/*menuXCoord-(0.19f/2)*/, 0.125f+textHeight+menuYCoord+yyy/*((maxOptions + 1) * textHeight + 0.125f)+textHeight+yyy  +menuYCoord*/, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, 255, false,false);
			
			bool foundModders = false;
			for (int i = 0; i < 18; i++) {
				if (i != PLAYER::PLAYER_ID()) {
					if (PLAYER_VALID(i)) {
					//char *name = PLAYER::GET_PLAYER_NAME(i);
					//if (isPlayerValid(name)) {
						if (PlayerMods::isModder(i) == 2) {
							if (foundModders == false)
								p.addText("~b~Modders:");
							foundModders = true;
							snprintf(buf, sizeof(buf), "~g~%s, ~r~%s", PLAYER::GET_PLAYER_NAME(i), PlayerMods::getModderReason(i));
							p.addText(buf);
							//p.addText(PLAYER::GET_PLAYER_NAME(i));
							//yyy += 0.035;
							//drawText(PLAYER::GET_PLAYER_NAME(i), optionsFont, expand/*menuXCoord-(0.19f/2)*/, 0.125f+textHeight+menuYCoord+yyy/*((maxOptions + 1) * textHeight + 0.125f)+textHeight+yyy  +menuYCoord*/, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, 255, false,false);
						}
					}
				}
			}
			//if (!foundModders) {
			//	p.addText("~r~None found! ~s~(Besides you)");
				//yyy += 0.035;
			//	drawText("~r~None found! ~s~(Besides you)", optionsFont, expand/*menuXCoord-(0.19f/2)*/, 0.125f+textHeight+menuYCoord+yyy/*((maxOptions + 1) * textHeight + 0.125f)+textHeight+yyy  +menuYCoord*/, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, 255, false,false);
			//}

			//GRAPHICS::DRAW_RECT(expand+0.075,0.125f+textHeight+menuYCoord+(yyy/2)  +textHeight,0.15,yyy,backgroundRed,backgroundGreen,backgroundBlue,backgroundOpacity);
			//GRAPHICS::DRAW_RECT(expand+0.075,0.125f+textHeight+menuYCoord+(textHeight/2),0.15,textHeight,0,255,255,backgroundOpacity);
			p.drawBG();
			
}
#pragma endregion
#pragma region draw component info
#ifdef drawComponentInfoStuff
void drawComponentInfo() {
	char texture[30];
	char drawable[30];
	char palette[30];
	SideInfo p;
	p.addText("Component Info");
	snprintf$(texture,sizeof(texture),"Texture %i",PlayerMods::components::getTexture());
	snprintf$(drawable,sizeof(drawable),"Drawable %i",PlayerMods::components::getDrawable());
	snprintf$(palette,sizeof(palette),"Palette %i",PlayerMods::components::getPalette());
	float expand = textmenuwidth+(menuXCoord/2);
	float sizey = 0.0f;
		//if (optionCount > maxOptions) {
			/*drawing::DrawText(texture, optionsFont, menuXCoord-(0.19f/2), ((maxOptions + 1) * textHeight + 0.125f)+textHeight  +menuYCoord, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, false);
			float yyy = 0.025;
			drawing::DrawText(drawable, optionsFont, menuXCoord-(0.19f/2), ((maxOptions + 1) * textHeight + 0.125f)+textHeight+yyy  +menuYCoord, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, false);
			yyy = yyy+0.025f;
			drawing::DrawText(palette, optionsFont, menuXCoord-(0.19f/2), ((maxOptions + 1) * textHeight + 0.125f)+textHeight+yyy  +menuYCoord, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, false);*/

			//drawing::DrawText(texture, optionsFont, expand, 0.125f+textHeight+menuYCoord/*((maxOptions + 1) * textHeight + 0.125f)+textHeight  +menuYCoord*/, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, 255, false);
			p.addText(texture);
	
			float yyy = 0.035;
			//drawing::DrawText(drawable, optionsFont, expand/*menuXCoord-(0.19f/2)*/, 0.125f+textHeight+menuYCoord+yyy/*((maxOptions + 1) * textHeight + 0.125f)+textHeight+yyy  +menuYCoord*/, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, 255, false);
			p.addText(drawable);

			yyy = yyy+textHeight;
			//drawing::DrawText(palette, optionsFont, expand, 0.125f+textHeight+menuYCoord+yyy, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, 255, false);
			p.addText(palette);
			//yyy = yyy+0.025f;
			//drawing::DrawText(healthtext, optionsFont, menuXCoord-(0.19f/2), ((maxOptions + 1) * textHeight + 0.125f)+textHeight+yyy  +menuYCoord, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, false);
			//GRAPHICS::DRAW_RECT(menuXCoord, (((maxOptions + 1) * textHeight) + 0.1415f)+(textHeight*2)+(sizey/2)  +menuYCoord, 0.19f, 0.09f+sizey, bannerRectRed, bannerRectGreen, bannerRectBlue, backgroundOpacity); //Info Box
		//}
		/*else {
			drawing::DrawText(texture, optionsFont, menuXCoord-(0.19f/2), ((optionCount + 1) * textHeight + 0.125f)+textHeight  +menuYCoord, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, false);
			float yyy = 0.025;
			drawing::DrawText(drawable, optionsFont, menuXCoord-(0.19f/2), ((optionCount + 1) * textHeight + 0.125f)+textHeight+yyy  +menuYCoord, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, false);
			yyy = yyy+0.025f;
			drawing::DrawText(palette, optionsFont, menuXCoord-(0.19f/2), ((optionCount + 1) * textHeight + 0.125f)+textHeight+yyy  +menuYCoord, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, false);
			//yyy = yyy+0.025f;
			//drawing::DrawText(healthtext, optionsFont, menuXCoord-(0.19f/2), ((optionCount + 1) * textHeight + 0.125f)+textHeight+yyy  +menuYCoord, textSize, textSize, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, false);
			GRAPHICS::DRAW_RECT(menuXCoord, (((optionCount + 1) * textHeight) + 0.1415f)+(textHeight*2)+(sizey/2)  +menuYCoord, 0.19f, 0.09f+sizey, bannerRectRed, bannerRectGreen, bannerRectBlue, backgroundOpacity);
		}*/
			p.drawBG();
}
#endif
#pragma endregion
#pragma region draw enabled options
/*void drawEnabledOptions() {
	float y = 0.03-menuYCoord;
	float rightWard = 0.95f;
	for (int i = 0; i < 64; i++) {
		if (enabledmods[i] != NULL) {
			float width = getTextWidth(enabledmods[i],optionsFont,textSize,textSize);
			float x = rightWard-width;
			drawing::DrawText(enabledmods[i],optionsFont,x,y,textSize,textSize,255,255,255,255,false,false);
			//drawing::DrawShader(rightWard-(width/2),y+0.018f,width,textHeight,0,0,0,100);
			y += textHeight;
		}
	}
}*/
/*
void specialRenderCode() {
	printf("bout to render\n");
	drawing::DRAW_RECT_IMMEDIATELY(menuXCoord-(0.19f/2)+addwidthspecialrender, 0.1415f+menuYCoord-0.03f  -0.0175, expandspecialrender, 0.06, 0,     255,            255 ,backgroundOpacity);//box above title
	printf("rendered!\n");
}

opd_s renderfunction_t = {0x479878,TOC};
void(*renderfunction)(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int r6, unsigned int r7, unsigned int r8) = (void(*)(unsigned int , unsigned int , unsigned int , unsigned int , unsigned int , unsigned int ))&renderfunction_t;
char specialRenderHookReset[4*4];
void specialRenderHook(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int r6, unsigned int r7, unsigned int r8) {
	//hook to sub_479878 and render afterwards

	memcpy((void*)0x479878,specialRenderHookReset,4*4);//set it to normal so it works when called below

	printf("calling special function\n");
	renderfunction(r3,r4,r5,r6,r7,r8);//do all the original stuff
	printf("successfully called special function\n");
	specialRenderCode();//do custom stuff

	PatchInJump2(0x479878,(int)specialRenderHook,false);//reset so this function is called next time too

}*/
//void initSpecialRenderHook() {
	//memcpy(specialRenderHookReset,(void*)0x479878,4*4);
	//PatchInJump2(0x479878,(int)specialRenderHook,false);
//}
#pragma endregion
#pragma region Mods
char *cachedStrings;
char *cachedStringsEnglish;
int cachedStringsSize = -1;
int cachedStringsEnglishSize = -1;
char *getCachedStringFromString(char *strList, int sizeOfStrList, char *buf) {
	//reset mess ups in the array
	for (int i = 0; i < sizeOfStrList; i++)
	if (strList[i] == 0) {
		strList[i] = '\n';
		break;
	}

	//search for it
	//printf("Finding: %s\n",buf);
	char *str = strstr(strList,buf);
	//printf(cachedStrings);
	if (str) {
		str = str + strlen(buf);
		char *nextNewLine = strstr(str,"\n");
		if (nextNewLine)
			nextNewLine[0] = 0;//cut off end of string
		//printf("Found: %s\n",str);
		return str;
	}
	return 0;
}
char *getCachedString(char *find) {

	
	char buf[10];
	memset(buf,0,10);
	buf[0] = '\n';
	int len = strlen(find);
	for (int i = 0; i < len; i++) {
		buf[1+i] = find[i];
	}
	buf[1+len] = ':';

	/*
	for (int i = 0; i < cachedStringsSize; i++)
		if (cachedStrings[i] == 0) {
			cachedStrings[i] = '\n';
			break;
		}
	char buf[10];
	memset(buf,0,10);
	buf[0] = '\n';
	int len = strlen(find);
	for (int i = 0; i < len; i++) {
		buf[1+i] = find[i];
	}
	buf[1+len] = ':';
	//printf("Finding: %s\n",buf);
	char *str = strstr(cachedStrings,buf);
	//printf(cachedStrings);
	if (str) {
		str = str + strlen(buf);
		char *nextNewLine = strstr(str,"\n");
		if (nextNewLine)
			nextNewLine[0] = 0;//cut off end of string
		//printf("Found: %s\n",str);
		return str;
	}
	return "NOT FOUND DATA";
	*/
	char *str = getCachedStringFromString(cachedStrings,cachedStringsSize,buf);
	if (str == 0)
		str = getCachedStringFromString(cachedStringsEnglish,cachedStringsEnglishSize,buf);
	if (str == 0)
		return "NOT FOUND AT ALL. THIS SHOULD NOT HAPPEN";
	return str;
}
void allocateAndLoadFile(char *fileLoc, char **buffer, int *storeFileSize) {
	int fileSize = getFileSize(fileLoc);
	*storeFileSize = fileSize;
	*buffer = (char*)_malloc(fileSize);//call<char*>(0x10310)(fileSize);
	readFile(fileLoc,*buffer,fileSize);
}
void initCachedStrings() {
	//printf("initing cached strings\n");
	char *fileLoc = "/dev_hdd0/tmp/gopro_2027/strings.txt";
	char *fileLocNew = "/dev_hdd0/tmp/gopro_2027/strings_latest_version.txt";
	downloadFileFromDownloadFolder("strings.txt","gopro_2027/strings_latest_version.txt");//get the latest version for checks
	bool shouldDL = false;
	if (!doesFolderExist(fileLoc)) {
		shouldDL = true;
	} else {
		//check version
		/*
		int myversion = 0;
		int serverversion = 0;
		{
			char versionS1[10];
			readFile(fileLoc,versionS1,10);
			for (int i = 0; i < 10; i++)
				if (versionS1[i] == ' ')
					versionS1[i] = 0;
			myversion = StoI(versionS1);
			printf("strings.txt my version %i\n",myversion);
		}
		
		{
			char versionS[10];
			readFile(fileLocNew,versionS,10);
			for (int i = 0; i < 10; i++)
				if (versionS[i] == ' ')
					versionS[i] = 0;
			serverversion = StoI(versionS);
			printf("strings.txt server version %i\n",serverversion);
		}
		if (myversion != serverversion)
			shouldDL = true;
		*/
	}
	if (shouldDL) {
		//downloadFileFromDownloadFolder("strings.txt","gopro_2027/strings.txt");
		char *str = "STRINGS IN HERE WILL OVERRITE STRINGS IN strings_latest_version.txt\nYou can put custom strings or custom language stuff in this file\n";
		createFile(fileLoc);
		writeToFile(fileLoc,str,strlen(str));
	}
	
	//printf("Allocating data\n");
	allocateAndLoadFile(fileLocNew,&cachedStringsEnglish,&cachedStringsEnglishSize);
	allocateAndLoadFile(fileLoc,&cachedStrings,&cachedStringsSize);
	for (int i = 0; i < cachedStringsEnglishSize; i++)
	if (cachedStringsEnglish[i] == 0xD) {//0xD is carriage return, just set the fucker to \n so it fixes bugs
		cachedStringsEnglish[i] = '\n';
	}
	for (int i = 0; i < cachedStringsSize; i++)
	if (cachedStrings[i] == 0xD) {//0xD is carriage return, just set the fucker to \n so it fixes bugs
		cachedStrings[i] = '\n';
	}
	//printf("Done init\n");
}
int doInjectBGScript = false;
void checkRPFDownloadStatus() {
	//char buf[100];
	if (downloadRPFErrorCode == 0) {
		snprintf(global_temporary_buf,sizeof(global_temporary_buf),"Download %i%% Complete\nPlease refrain from using network mods while downloading.",downloadFilePercentCompleted);
		print2(global_temporary_buf);
		rpdownloadcompleted = true;
	}
	if (downloadRPFErrorCode == 2) {
		showDownloadOutput = false;//end output
		downloadRPFErrorCode = 0;
		print2("~g~Download finished!",20000);
		doInjectBGScript = 1;
	}
	if (downloadRPFErrorCode == 1) {
		showDownloadOutput = false;//end output
		downloadRPFErrorCode = 0;
		print2("~r~Cannot download!\nError A",10000);//this should never happen when set to tmp to don't bother modifying
	}
	if (downloadRPFErrorCode == 3) {
		showDownloadOutput = false;//end output
		//should never happen anymore
		downloadRPFErrorCode = 0;
		print2("~r~Cannot download!\nFile already exists!\nError C",10000);
	}
	if (downloadRPFErrorCode == 4) {
		showDownloadOutput = false;//end output
		downloadRPFErrorCode = 0;
		snprintf(global_temporary_buf,sizeof(global_temporary_buf),"~r~Error downloading! Please try again (%i%%).\nError B",downloadFilePercentCompleted);
		print2(global_temporary_buf,10000);//this works just fine
		doInjectBGScript = 2;//error but still need to be injected anyways to be able to get online
	}
}

/*void SET_STAT_BOOL(char *stat, int value)
 {
  if (strcmp(UI::_0x34A396EE(stat, 0, 5), "MPPLY") == 0)
   STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(stat), value, 1);
  else
  {
   char sbuf[50];
   int stat_r;
   STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_LAST_MP_CHAR"), &stat_r, 1);
   snprintf(sbuf, sizeof(sbuf), "MP%i%s", stat_r, stat);
   printf("Stat being set: %s\n",sbuf);
   STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(sbuf), value, 1);
  }
 }*/
//bool notickilerhickler = false;
int skipTutorialLoop = 0;
//bool badsportRemovalBool = false;
//bool freezePlayerOverflowBool = false;
static int modloaderScriptID = 0;
//bool hasStartedModloader = false;
void deleteScriptRPFFunc() {
	deleteFile(scriptLoadLocationString);//delete the file now boi
}

void giveObjectGravity() {

}

/*void notickilerhicklerfunc(int obj) {
	ENTITY::FREEZE_ENTITY_POSITION(obj, false);
	ENTITY::SET_ENTITY_HAS_GRAVITY(obj, true);
	ENTITY::APPLY_FORCE_TO_ENTITY(obj, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}*/

bool healthRegen = false;

void que() {


	//joinLoop();

	//PendingJoinRequestLoop();

	myvehiceladdr = (unsigned int)getCObjFromIndex(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false));
	if (tsunamiPrint != 0) {
		print2(tsunamiPrint,5000);
		tsunamiPrint = 0;
	}
	if (doPlayerSpoofLocation) {
		Vector3 l = PlayerMods::getPlayerLocation(customSpoofLocationPlayer);
		customSpoofPosition.x = l.x;
		customSpoofPosition.y = l.y;
		customSpoofPosition.z = l.z;
	}

	/*if (notickilerhickler) {
		if (_rand() % 1000 == 0) {
			print2("Your hickle was tickled!",1000);
			Vector3 rot = { 0,0,0 };
			OBJ::forceCreateObject("prop_cs_dildo_01",ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),1).add(0,0,1),rot,false, notickilerhicklerfunc);
		}
	}*/

	coolRocketsLoop();
	RTMTool::beat_command();
	startScriptLoop();
	//printf("A: %i, B: %i\n",showDownloadOutput,doDownloadRPF);
	if (showDownloadOutput == true || doDownloadRPF == true)
		checkRPFDownloadStatus();
	//printf("que!\n");
	//*(volatile unsigned int*)(0x3EE05C)
	/*if (skipTutorialLoop >= 200) {
		printf("Setting tut stat\n");
		SET_STAT_BOOL("_FM_CMODTUT_DONE", 1);
		SET_STAT_BOOL("_NO_TUT_SPAWN", 1);
		SET_STAT_BOOL("_FRONT_END_JIP_UNLOCKED", 1);
		SET_STAT_BOOL("_FM_TRIGTUT_DONE", 1);
		SET_STAT_BOOL("_FM_HOLDTUT_DONE", 1);
		SET_STAT_BOOL("_FM_RACETUT_DONE", 1);
		SET_STAT_BOOL("MPPLY_NO_MORE_TUTORIALS", 1);//2918038585
		skipTutorialLoop = 0;
	}
	skipTutorialLoop++;*/

	skateboard::loop();
	PlayerMods::teleportToCoordsManagerLoop();
	fixdisableAccount();
	/*char *modloaderScriptName = "ModLoader";
	if (SCRIPT::DOES_SCRIPT_EXIST(modloaderScriptName)) {
		if (!isScriptRunning(modloaderScriptName) && tryToStartScript == false) {
			lastStartedScriptIDPointer = &modloaderScriptID;
            SCRIPT::REQUEST_SCRIPT(modloaderScriptName);
			tryToStartScript = true;
			g_scriptNameToStart = modloaderScriptName;
			g_scriptStackSizeToStart = 1024;
		}
	}*/
	
	autoKickModdersLoop();

	FindRandomGamers::findRandomGamers();//this is for the

	STREAMING::REQUEST_MODEL(-1404353274);//request zombie model hash
	zombieOutbreak::loop();


	if (poolManipulations::drawLineBool) {
		poolManipulations::drawLineToAllObjects();
	}
	if (poolManipulations::drawNameBool) {
		poolManipulations::drawNameOnAllObjects();
	}

	assureHostOfFreemodeLoop();

	/*if (badsportRemovalBool) {
		allClientStats::commendFriend(selectedPlayer);
		//badsportRemovalBool = false;//temporary, just to do 1
	}*/
	/*if (freezePlayerOverflowBool) {
		allClientStats::overflowFreeze(selectedPlayer);
	}*/
	//RTMTool::spawnVehicleForUserLoop();//this is /nojb function
	jailMod::loop();
	portalGun::loop();//removed for memory
	PlayerMods::dropMoneyLoop();
	//PlayerMods::TeleportPlayerToMeLoop();//old version
	noclip::loop();
	PlayerMods::removeWantedLevelLoop();
	PlayerMods::showTalkingPlayersLoop();
	PlayerMods::changeModelLoop();
	if (VehicleMods::l3pressed && VehicleMods::wheelieEnabled)
		VehicleMods::liftcar();
	PlayerMods::weaponGivePlayerLoop();
	firstPerson::rendercrosshair();
	randomizeAddresses();
	firstPerson::loop();

	if (doInjectBGScript > 0) {
		if (*(int*)0x10B6C3C == 0x4E800020) {
			//print2("In here is bad if downloading file and this gets!\n");
			//all the code in here will only get called once max
			*(int*)0x10B6C3C = 0x7C0802A6;//reset old code

			if (doInjectBGScript == 1) {//1 is valid download
				/*unsigned int fileSizeDownloaded = 0;
				printf("About to read and malloc\n");
				char *memLoc = readFileFully(scriptLoadLocationString,&fileSizeDownloaded);
				strcpy(scriptLoadLocationString,getFormatForMemoryArea(memLoc,fileSizeDownloaded));
				printf("Memory formatted: %s\n",scriptLoadLocationString);*/
				setScriptLoadLocation(getScriptLoadLocation());//load the script
				PatchInJumpAddr(0x10B6D78,(int)deleteScriptRPFFunc,true);
			} else {
				//must be 2, which is failure, use default update.rpf instead, TODO
				//printf("Failure to install! Running default script\n");
			}

			call<int>(0x010B52E0)(*(int*)0x1CFB100);//bg script force download
		}
		doInjectBGScript = 0;
	}

	//checkTampering();
	camShit::loop();
	//VehicleMods::hydroulicsLoop(submenu);
	PlayerMods::revenge();
	VehicleMods::squareDriftModLoop();
	removeObjectsSpecial::markEntityForDeletionLoop();
	if (RTMTool::chatEnabled)
		printLoop();//this is now the paradise chat
	drawMiniMapInfo();
	/*if (bouncingArrow < -0.005 || bouncingArrow > 0.005)
		bouncingArrowDirection = -1*bouncingArrowDirection;
	bouncingArrow+=bouncingArrowDirection;*/
	VehicleMods::needForSpeed();
	if (pressedButtons::dpadleftpressed && pressedButtons::r1pressed) {
		noclip::toggle();
		/*for (int i = 0; i < 64; i++) {
			if (enabledmods[i] == "Noclip") {
				enabledmods[i] = NULL;
				break;
			}
		}
		if (noclip::enabled) {
			for (int i = 0; i < 64; i++) {
				if (enabledmods[i] == NULL) {
					enabledmods[i] = "Noclip";
					break;
				}
			}
		}*/
	}
	//PlayerMods::hulk();
	
	randomizeAddresses();
	VehicleMods::godmode(VehicleMods::enabledgodmodeloop);//may need fixed
	//noclip::grapplingHookLoop();
	PlayerMods::VehicleGunLoop();//secretly calling setNPTypeLoop()
	VehicleMods::playerCarRunLoop();
	rope::spiderman();
	forge::shootSpawningLoop();//print2("Taken out (7)",1000);
	VehicleMods::paradiseColorChangerLoop();
	PlayerMods::attachtoplayerloop();
	//generators::doAllMoneyGens();//cuz taken out
	//evaluatePSC(PSCscript,"hook");//taken out cuz lag
	//anticheater::removePropsLoop();
	//camShit::aimbot::loop();
	//randomizeAddresses();
	PlayerMods::forceFieldLoop();
	PlayerMods::clearScenesLoop();//might want to look at this
	//allObjects::loop();
	Write_Global(1325828,0);//disable timeout (for being idle)

	if (duneCallbackPreviousVehicle != 0 && !NETWORK::NETWORK_IS_PLAYER_CONNECTED(duneCallbackPlayer)) {
		forge::markEntityForDeletion(duneCallbackPreviousVehicle,duneCallback2);
	}


	//textMessageModMenu::loop();//This is for the whole mini menu thing in game, use RTM instead
	
	static int detachCounter = 0;
	detachCounter++;
	if (detachAllObjectsEnabled)
		//detachAllObjects();//this uses the old loopy thingy
		if (detachCounter%10 == 0)
			poolManipulations::detachAllEntities(PLAYER::PLAYER_PED_ID());
	if (poolManipulations::clearLagBool) {
		if ((detachCounter+9)%10 == 0) {
			Vector3 loc = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true);
			//float pos[3];
			//pos[0] = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true).x;
			//pos[1] = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true).y;
			//pos[2] = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true).z;
			//printf("Cleared lag: %i %i %i\n",(int)loc.x,(int)loc.y,(int)loc.z);
			GAMEPLAY::_CLEAR_AREA_OF_EVERYTHING(loc.x,loc.y,loc.z, 50000.0f, false, false, false, false);//_0x20E4FFD9  CLEAR_AREA
			//poolManipulations::deleteAllEntities();//still freezing idk why
		}
	}
	if (detachCounter > 99999)
		detachCounter = 0;


	//textMessageModMenu::CMDMenuLoop();//This is for the whole text message mod menu, use RTM instead



	//randomizeAddresses();
	VehicleMods::matrixPlate(VehicleMods::matrixPlateBool);
	PlayerMods::showAllPlayersLoop();
	/*static int chatCounterLol = 0;
	chatCounterLol++;
	if (chatCounterLol % 500 == 0) {
		PlayerMods::chatRestrict(true);
		printf("unrestricting chat\n");
	}*/
	PlayerMods::spamTextMessageLoop();
	
	RTMCommands::loop();//run the rtm stuff
	GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("mpinventory", false);
	GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("commonmenu", false);
	//GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("mphud", false);
	GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("mpmissmarkers256", false);
	GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("hackingng", false);//for custom background
	//missionpassedgradient from mphud is 512

	//retreiveMacAddress();
	static bool customBackgroundReplaced = false;

	if (customBackgroundReplaced == false) {
		if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED("hackingng")) {
			char *imageFileLoc = "/dev_hdd0/tmp/gopro_2027/background.dds";
			int fileSize = getFileSize(imageFileLoc);
			if (fileSize == 262272) {//size of 512
				doDrawCustomBG = drawing::overriteImageFromFile("hackingng","dhcomp",imageFileLoc,512);
			} else {
				if (fileSize > 0)
					print2("~r~Custom image not in correct format!",1000000);
			}
			customBackgroundReplaced = true;//skip it
			//printf("Done checking for custom background\n");//tested and confirmed to show up
		}
	}
}

void doDemiGod() {
	//char buf[500];
	if (demiGodmode) {
		CObj *ptr = getCObjFromIndex(PLAYER::PLAYER_PED_ID());
		if (VALID_ADDR(ptr)) {
			
			ptr->health = hexToFloat(0x7f7fffff);//200 by default
			ptr->maxHealth = hexToFloat(0x7f7fffff);
			//ptr->proofsBitset = 0xFFFFFFFF & ~BIT_FROM_LEFT(8);//8 is player godmode
			//ptr->proofsBitsetByte = 0xFF;
			
		}
	}

	if (healthRegen) {
		CObj* ptr = getCObjFromIndex(PLAYER::PLAYER_PED_ID());
		if (VALID_ADDR(ptr)) {
			ptr->health = ptr->maxHealth;
			//ptr->health = hexToFloat(200);//200 by default
			//ptr->maxHealth = hexToFloat(200);
			//ptr->proofsBitset = 0xFFFFFFFF & ~BIT_FROM_LEFT(8);//8 is player godmode
			//ptr->proofsBitsetByte = 0xFF;

		}
	}

}
//bool freezeLobbyV3 = false;
bool inFreemode = false;
void constantque() {
	/*if (inFreemode) {
		if (freezeLobbyV3) {
			printf("Doing freeze in script %s\n",SCRIPT::GET_THIS_SCRIPT_NAME());
			//NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES((void*)Read_Global_Address(262145+4715),1);
			setAllOutOfBadsport();
			setGlobalValueForAll(262145+4715,1);
			freezeLobbyV3 = false;
		}
	}*/


	animepunch_loop();
	
	forceKickAntiLoop();
	doDemiGod();
	resetPlayerViewLoop();
	//PlayerMods::v_3(PLAYER::PLAYER_ID());
	OBJ::forceCreateObjectLoop();
	PlayerMods::attachPropToPlayerLoop();
	GodMode::godmodeLoop();
	randomizeAddresses();
	
	if (globalXMLSettings.rainbowMode) {
		COLOR_FOREGROUND.x = colors::r;
		COLOR_FOREGROUND.y = colors::g;
		COLOR_FOREGROUND.z = colors::b;
	}
	/*static int kjsxdhgkjadsh = 0;
	if (kjsxdhgkjadsh%4 == 0) {
		//findGamers();
		kjsxdhgkjadsh = 0;
	}
	kjsxdhgkjadsh++;*/

#ifdef sJKFghjsadfjkgh
	findGamers();
#endif

	//lobbyModMenu::loop();//taken off vbecause of the new mod menu thing
	//VehicleMods::spawnVehicleLoop();
	PlayerMods::playerClearTaskLoop();
	PlayerMods::lobbyClearTaskLoop();
	randomizeAddresses();
	forge::loop();
	setShitToBeSpectator();
	minecraft::loop();
	PlayerMods::rapidsetinvisibleloop();
	bodyguard::loop();
	//entityMods::loop();
	randomizeAddresses();

	print3_loop();
	
	//weaponMods::runExplosiveBullets();
	PedAnim::loop();
	//PlayerPedControl::loop();
	PlayerMods::aimBotLoop();
	colors::change();
	PlayerMods::invisibleBallLoop();
//#ifdef IDONTWANTTOSAVEMEMORY
#ifdef DEVELOPER
	globalSearchLoop();
	globalSearchStringLoop();
#endif
//#endif
}
#pragma endregion
#pragma region evaluation of scripts
#ifdef oldweirdscriptevaluation
char freezechar[] = {'\0'};
char evalscript[1];
class String {
private:
    char *ptr;
    int size;
public:
    void alloc(int s) {
        release();
        size = s;
        //ptr = new char[s]; //need to fix these for it to work
		ptr = (char*)neww(s);
		//ptr = (char*) malloc (s);
    }

    void release() {
		if (size != 0) {
			//delete [] ptr;
			//free(ptr);
			deletee(ptr);
			size = 0;
		}
    }

    void setString(char string[]) {
        int q = strlen(string);
        alloc(q);
        for (int i = 0; i < q; i++)
            *(char*)(ptr+i) = string[i];
    }
    char *getString() {
        return ptr;
    }
    int getSize() {
        return size;
    }
};
/*class Stack {
public:
	int curspot;
	String strings[10];
	void clear(char str[]) {
		for (int i = 0; i < 50; i++) {
			str[i] = 0;
		}
	}
	//spot 0 will contain the function id in "cfg" code
	//spot 1 to 9 will contain the arguments
	void push(char str[]) {
		ConsoleWrite("Pushing data: ");
		//strncpy(getCurrentSpot(curspot),str,50);
		strings[curspot].setString(str);
		ConsoleWrite(strings[curspot].getString());
		ConsoleWrite("\nPushed data\n");
		curspot++;
	}
	void initstack(char str[]) {
		for (int i = 0; i < 10; i++)
			strings[i].release();
		curspot = 0;
		//strings[curspot].clear();
		//strcpy(strings[curspot],str);
		push(str);
	}
	void pop() {
		if (contains(strings[0].getString(),"SPAWNOBJECT")) {
			ConsoleWrite("\nPopping spawnobject function ");
			for (int i = 0; i < 10; i++)ConsoleWrite(strings[i].getString());
			ConsoleWrite(strings[0].getString());
			ConsoleWrite("hi\n");
			ConsoleWrite(strings[1].getString());
			ConsoleWrite("hi");
			//spot 1 is the object type
			Vector3 pos = {StoI(strings[2].getString())+OBJ::getPlayerPos().x,StoI(strings[3].getString())+OBJ::getPlayerPos().x,StoI(strings[4].getString())+OBJ::getPlayerPos().x};
			Vector3 rot = {0,0,0};
			OBJ::forceCreateObject(strings[1].getString(),pos,rot,false,false);
		}

		if (contains(strings[0].getString(),"SPAWNVEHICLE")) {
			printf("\nPopping function spawn vehicle: %s of size %i\n",strings[1].getString(),strlen(strings[1].getString()));
			//ConsoleWrite(getCurrentSpot(1));
			//ConsoleWrite(getCurrentSpot(0));
			//ConsoleWrite(getCurrentSpot(1));
			//char buf[20];
			//snprintf$(buf,20,"%s",getCurrentSpot(1));
			//ConsoleWrite(buf);
			//ConsoleWrite(buf);
			//ConsoleWrite(buf);
			//ConsoleWrite("\n");
			//char buf[15];
			//strcpy(buf,strings[1].getString());
			VehicleMods::spawnVehicle(strings[1].getString());
		}
		ConsoleWrite("\n");
		//for (int i = 0; i < 10; i++)
			//strings[i].release();
		//curspot = 0;
	}
};

String menuArguments[36];
char alphabet[] = "abcdefghijklmnopqrstuvwxyz1234567890";
int alphabetindex(char ch) {
	for (int i = 0; i < strlen(alphabet); i++) {
		if (alphabet[i] == ch) {
			return i;
		}
	}
	return -1;
}
char *varAt(int spot) {
	return menuArguments[spot].getString();
}

char chartoarray[1];
void evaluateScript(char data[]) {
	ConsoleWrite("\nEvaluating a custom script: ");
	ConsoleWrite(data);
	ConsoleWrite("\n");
	for (int i = 0; i < strlen(data); i++) {
		char ch = (char)(data[i]);
		ConsoleWrite("\nFound Identifier: ");
		chartoarray[0] = ch;
		ConsoleWrite(chartoarray);
		ConsoleWrite("\n");
		if (ch == '$') {
			char br = (char)(data[i+1]);
			char val = (char)(data[i+2]);
			ConsoleWrite("\nRunning A Builtin Function: ");
			ConsoleWrite(varAt(alphabetindex(br)));
			ConsoleWrite("\nWith argument: ");
			ConsoleWrite(varAt(alphabetindex(val)));
			ConsoleWrite("\n");
				eval(varAt(alphabetindex(br)),varAt(alphabetindex(val)));
			i+=2;
		}
		else if (ch == '#') {
			char br = (char)(data[i+1]);
			ConsoleWrite("\nRunning A Custom Function At: ");
			ConsoleWrite(varAt(alphabetindex(br)));
			ConsoleWrite("\n");
			evaluateScript(varAt(alphabetindex(br)));
			i+=1;
		}
	}
}
//dank menu: iEpHJfB3
char temporarybuf[50];
Stack evalStack;
void eval(char type[], char data[]) {
	if (isEqual(type,"TITLE"))
		strcpy(menuTitle,data);
	if (isEqual(type,"GODMODE"))
		GodMode::godmodeEnabled = StoI(data);
	if (isEqual(type,"NOCLIPSPEED"))
		noclip::speed = (float)StoI(data);
	if (isEqual(type,"NOCOPS"))
		PlayerMods::wantedLevelEnabled = StoI(data);
	if (isEqual(type,"BGTITLECOLORRED"))
		bannerRectRed = StoI(data);
	if (isEqual(type,"BGTITLECOLORGREEN"))
		bannerRectGreen = StoI(data);
	if (isEqual(type,"BGTITLECOLORBLUE"))
		bannerRectBlue = StoI(data);
	if (isEqual(type,"BGTITLEOPACITY"))
		bannerRectOpacity = StoI(data);
	if (isEqual(type,"REMEMBERALLOPTIONS"))
		useMenuRemembrence = StoI(data);
	if (isEqual(type,"BGBODYCOLORRED"))
		backgroundRed = StoI(data);
	if (isEqual(type,"BGBODYCOLORGREEN"))
		backgroundGreen = StoI(data);
	if (isEqual(type,"BGBODYCOLORBLUE"))
		backgroundBlue = StoI(data);
	if (isEqual(type,"BGBODYOPACITY"))
		backgroundOpacity = StoI(data);
	if (isEqual(type,"MINIMUMMENUWIDTH"))
		minimumMenuWidth = (float)StoI(data)/100.0f;
	if (isEqual(type,"TEXTCOLORRED"))
		optionsRed = StoI(data);
	if (isEqual(type,"TEXTCOLORGREEN"))
		optionsGreen = StoI(data);
	if (isEqual(type,"TEXTCOLORBLUE"))
		optionsBlue = StoI(data);
	if (isEqual(type,"TEXTOPACITY"))
		optionsOpacity = StoI(data);
	if (isEqual(type,"NAME"))
		PlayerMods::changeName(data);
	if (isEqual(type,"TITLECOLORRED"))
		bannerTextRed = StoI(data);
	if (isEqual(type,"TITLECOLORGREEN"))
		bannerTextGreen = StoI(data);
	if (isEqual(type,"TITLECOLORBLUE"))
		bannerTextBlue = StoI(data);
	if (isEqual(type,"TITLEOPACITY"))
		bannerTextOpacity = StoI(data);

	if (isEqual(type,"VAR")) {
		int i = alphabetindex(data[0]);
		if (i != -1) {
			substring(data,temporarybuf,1,strlen(data));
			menuArguments[i].setString(temporarybuf);
			ConsoleWrite("\nMenu Variable Set: ");
			ConsoleWrite(menuArguments[i].getString());
			ConsoleWrite("\n");
		}
	}
	if (isEqual(type,"SCRIPT"))
		evaluateScript(data);
	if (isEqual(type,"PRINT"))
		print(data);
	if (isEqual(type,"INITSTACK"))
		evalStack.initstack(data);
	if (isEqual(type,"PUSH"))
		evalStack.push(data);
	if (isEqual(type,"POP")) {
		evalStack.pop();
	}

}*/
#endif
#ifdef whekgfhsiughjsd
void runOnceStartup() {
	//loadCustomImage("/dev_hdd0/tmp/gopro_2027/customimage.ctd","customimage.ctd");
	//RegisterFile("/dev_hdd0/tmp/gopro_2027/ArabicGuy.csc","ArabicGuy.csc");
	//loadScript("ArabicGuy","/dev_hdd0/tmp/gopro_2027/");
	//triggerSafeLoadFunc();
	//registerFile("/dev_hdd0/tmp/gopro_2027/customimage.ctd","customimage.ctd");
	//registerFile("/dev_hdd0/tmp/gopro_2027/backgroundd.dds","backgroundd.dds");
	registerScriptFromFile("/dev_hdd0/tmp/gopro_2027/ArabicGuy.csc","ArabicGuy.csc");
}
#endif
#pragma endregion
#pragma region hooked function
bool triggerupdate = false;
opd_s __0x3EAC24 = {0x3EAC24,TOC};
int(*_0x3EAC24)() = (int(*)())&__0x3EAC24;
char ppcfuncbuf[25];
//Vector3 WHITE = {255,255,255};
#define renderingAtBottom 1
unsigned int originalUILayer = 0;
unsigned int currentUiLayer = -568;
void uiTop() {
	if (currentUiLayer == -568) 
		currentUiLayer = originalUILayer;

	GRAPHICS::_0xADF81D24(++currentUiLayer/*originalUILayer+1*/);
}
void uiBottom() {
	if (currentUiLayer == -568)
		currentUiLayer = originalUILayer;

	GRAPHICS::_0xADF81D24(--currentUiLayer/*originalUILayer-1*/);
}
void uiOrig() { 
	currentUiLayer = originalUILayer;
	GRAPHICS::_0xADF81D24(originalUILayer);
}

#include <sys/memory.h>
#include <sys/vm.h>

void ShowHelpText(char* text)
{
/*
UI::_SET_TEXT_COMPONENT_FORMAT("STRING");//BEGIN_TEXT_COMMAND_DISPLAY_HELP
UI::_ADD_TEXT_COMPONENT_STRING(text);//ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME
UI::_0xB59B530D(0, 0, 1, -1);//END_TEXT_COMMAND_DISPLAY_HELP
*/
	*(int*)0x3C9C48 = 0x60000000;
	*(int*)0x3C9C4C = 0x60000000;
	UI::DISPLAY_HELP_TEXT_THIS_FRAME(text,0);//second arg is ignored
	*(int*)0x3C9C48 = 0x306568B0;
	*(int*)0x3C9C4C = 0x489C7881;
}

#define IMG_HTML(dict,img,width,height) "<img src='img://" dict "/" img "' height='" height "' width='" width "'/>"

float motionBlurFloat = 0.3f;

//liighting setup: https://i.imgur.com/Rj7FWR2.png

#define BWGAMMA (*(int*)(0x2068780+0x12D8))    //0 is black and white
#define DOFBLUR (*(int*)(0x2068780+0x12DC))    //makes far away objects blurry when value is higher
#define PUDDLE_DATA (*(int*)(0x1CFB154))//FA9410 puddleData
#define PUDDLE_DATA2 (*(int*)(PUDDLE_DATA+0x74))
#define SOME_BRIGHTNESS (*(int*)(0x22223E0+0x20))   //when too high this causes many issues  3E000000
#define SOME_SATURATION (*(int*)(0x22223E0+0x28))   //0x3CC00000

void toggleRedux() {
	static bool redux = false;
	static int br = 0;
	static int s = 0;
	if (redux == false) {
		//currently off
		br = SOME_BRIGHTNESS;
		s = SOME_SATURATION;
	}
	redux = !redux;
	if (redux) {
		SOME_BRIGHTNESS = 0x3E000000;
		SOME_SATURATION = 0x3D500000;
	} else {
		SOME_BRIGHTNESS = br;
		SOME_SATURATION = s;
	}
}

bool inFreemodeScriptFirstPass = false;
ui64 runGtaThread_hook(GtaThread* thread, ui64 r4) {
	ui64 ret = call<ui64>(0x46D604)(thread, r4);
	//printf("Thread Hash: 0x%X %s\n",thread->nameHash, thread->threadName);
	if (thread->nameHash == 0xC875557D) {
		inFreemodeScriptFirstPass = true;
		//printf("Here!\n");
	}
	return ret;
}

int menuIsOpenSwitch();

void createLoadWordR3(unsigned int addressA, unsigned int addressB, int* value) {
	int firstHalf = ((((unsigned int)&value) & 0xFFFF0000) >> 16);
	unsigned short secondHalf = (((unsigned int)&value) & 0xFFFF);
	if (secondHalf > 0x7FFF) {
		firstHalf += 1;
		/*This middle calculation actually not required because being interpreted as a negative value it's already correct actually
		secondHalf = 0x10000 - secondHalf;
		secondHalf *= -1;*/
	}
	*(uint32_t*)addressA = 0x3C600000 + firstHalf;//lis %r3, val
	*(uint32_t*)addressB = 0x80630000 + (unsigned short)secondHalf;//lwz r3, val(r3)
}

bool doForceHostBool = false;

void doForceHostSetup() {

	char readTextBuffer[1];
	readFile("/dev_hdd0/tmp/gopro_2027/ForceHost.txt", readTextBuffer, 1);

	doForceHostBool = readTextBuffer[0] == '1';
	if (doForceHostBool) {
		//printf("**Doing force host\n");

		//*(uint32_t*)0x1CCB170 = 0;
		//*(uint32_t*)0x2005370 = 0;
		static int value = time(0) & 0xFFFF;
		//printf("Old val %X %X\n", *(uint32_t*)0x1CCB170, *(uint32_t*)0x1CCB174);
		//static int value = 0x00007090;//this is the unknown value
		*(uint32_t*)0x1CCB170 = 0;
		//*(uint32_t*)0x1CCB174 = value;
		int firstHalf = ((((unsigned int)&value) & 0xFFFF0000) >> 16);
		unsigned short secondHalf = (((unsigned int)&value) & 0xFFFF);
		if (secondHalf > 0x7FFF) {
			firstHalf += 1;
			/*
			This middle calculation actually not required because being interpreted as a negative value it's already correct actually
			secondHalf = 0x10000 - secondHalf;
			secondHalf *= -1;*/
		}
		*(uint32_t*)0xD25EBC = 0x3C600000 + firstHalf;
		*(uint32_t*)0xD25EC4 = 0x80630000 + (unsigned short)secondHalf;
		//printf("**Force Host Enabled! 0x%X\n",value);

		//printf("Old value of bool: 0x%X\n", *(bool*)0x1CCB158);
		*(bool*)0x1CCB158 = true;

		//printf("**Force Host Enabled!\n");
	}
	else {
		//printf("**NOT Doing force host\n");
	}
}

int Hook() {

	encryptFunctionStart_quick(Hook,6000);//5216

	/*GtaThread *prologue1 = getGtaThread(GAMEPLAY::GET_HASH_KEY("prologue1"));
	if (prologue1 != 0) {
		printf("Terminating 'prologue1' script!\n");
		//SCRIPT::TERMINATE_THIS_THREAD();
		//printf("GtaThread terminate a: %p\n", prologue1);
		//prologue1->terminate();
	}*/


	static bool runOnceInPrologue = true;
	/*static bool sjdfsjfdk = true;
	if (*(bool*)0x1CCB158 == 0 && sjdfsjfdk) {
		printf("Old value of bool (a): 0x%X\n", *(bool*)0x1CCB158);
		*(bool*)0x1CCB158 = 1;
		sjdfsjfdk = false;
	}*/
	if (runOnceInPrologue) {
		//printf("**Ran once in prologue!\n");
		/*if (doForceHostBool) {

			//doForceHostSetup();
			doForceHostBool = false;
		}*/

		runOnceInPrologue = false;
	}

	

	if (I_AM_ONLINE)
		echoStartValueOfIt_loop();



	//findRCEV5StartValue_loop();


	if (rceThread::renderPercents) {
		char buf[500];
		snprintf$(buf, sizeof(buf), "Part 1: %.1f%%\nPart 2: %.1f%%\n", rceThread::percentOnFirstPart * 100, rceThread::percentOnSecondPart * 100);
		print2(buf);
		//phase2PercentOutputBool
	}

	phase2PercentOutput();

	
	/*ConfigNetScriptBroadcastData *d = get_PlayerBroadcastData_ConfigNetScriptBroadcastData(0);
	if (d != 0) {
		printf("%i 0x%X\n",d->SizeOfData,d->SizeOfData);
	}*/

	


	//CAM::SET_CAM_MOTION_BLUR_STRENGTH(CAM::GET_RENDERING_CAM(),5000.0f);
	if (VALID_ADDR(*(int*)0x1DDD224))
		*(float*)(*(int*)0x1DDD224+0x80) = motionBlurFloat;
	//have this in here to try to reduce the amount of script memory that is being used

	/*
	if (Read_Global(1312623) != 0) {
		//being vote kicked
		print2("~r~You are being vote kicked!");
	}
	Write_Global(1312623,0);//this is anti-kick for it :/
	*/
	/*if (freemodeScriptGtaThread != 0) {
		if (freemodeScriptGtaThread->localDataPointer != 0) {
			printf("Address 0x%X\n",freemodeScriptGtaThread->localDataPointer);
			freemodeScriptGtaThread->setLocal(2981,Read_Global(1315372)+3);//idk just 3 cuz why not
			//freemodeScriptGtaThread->setLocal(2204,);
		}
	}*/


	menuWidthUseableValue = menuWidthDeltaValue;//delta is reset on addTitle call

	originalUILayer = *(int*)0x1C97564;
	//printf("Ui layer: %i\n",originalUILayer);
	SetupTimer3(20);
	/*if (IsTimerReady3())
	{
#if renderingAtBottom == 0
		resetVars();
#endif

	}*/

	

#ifdef uwsehjgfkjshdfkjsd
	static bool ranOnce = false;
	if (ranOnce == false) {
		runOnceStartup();
		ranOnce = true;
	}
	

	static bool drawTestImage = false;
	if (drawTestImage)
		drawing::DrawSprite("customimage","linux_penguin_tux_",0.5f,0.5f,0.4f,0.4f,0,255,255,255,100);
#endif
	//dialog("yolo");
	//printf("In hook\n");
	
	//{
		//printf("In hook\n");
		//sys_ppu_thread_stack_t info;
		//sys_ppu_thread_get_stack_information(&info);
		//printf("Current stack size: 0x%X\n",info.pst_size);
		//sys_ppu_thread_yield();
	//}


#if CRASH_DEBUGGER == 0

	
	snprintf(global_temporary_buf, sizeof(global_temporary_buf), "\n\nBuild %s %s", __DATE__, __TIME__);
	drawText(global_temporary_buf, 1, 0.7, 0.0 + 0.005, 0.35, 0.35, 0, 255, 255, 255, true, false);
	
#endif

	
	inFreemode = false;
	if (I_AM_ONLINE)//also NETWORK_IS_GAME_IN_PROGRESS
		if (!strncmp(SCRIPT::GET_THIS_SCRIPT_NAME(), "freemode", strlen("freemode"))) {
			inFreemode = true;
			freemodeScriptGtaThread = getCurrentGtaThread();
			freemodeScriptCGameScriptHandlerNetwork = getCurrentCGameScriptHandlerNetwork();
			if (inFreemodeScriptFirstPass) {
				//printf("F\n");
				rceThread::hooked::loopInHook();//moved a bit below so it is in the timer to only be ran once per frame
				inFreemodeScriptFirstPass = false;
			}
		}
		else if (!strncmp(SCRIPT::GET_THIS_SCRIPT_NAME(), "ingamehud", strlen("ingamehud")))
			int i = 0;
		else {
			//dropKickAnti();//this is for anti drop kick, spot #1
			//dropKickAnti2();
			//return *(char*)0x2242720;
			goto endOfHook;
		}

	/*if (I_AM_ONLINE) {
		if (VALID_ADDR(freemodeScriptCGameScriptHandlerNetwork)) {
			if (freemodeScriptCGameScriptHandlerNetwork->cGameScriptHandlerNetComponentSyncOne == 0) {
				print2("~r~NETWORK ERROR");
			}
		}
	}*/
	
	textHeight = UI::_0x3330175B(textSize,optionsFont);//textHeight
	menuStarted = true;
	/*if (*(volatile int*)(Read_Global_Address(81586)-0x8C) == 0xA) {
		*(volatile int*)(Read_Global_Address(81586)-0x8C) = 0xB;
	}*/
	//if (dototaloptions && submenu == Closed)
		//submenu = 1;
	menuXCoord = 0.095+(1.0-GRAPHICS::_0x3F0D1A6F());/*(1.0-GRAPHICS::_0x3F0D1A6F())*//*+0.025f*///0.145f;//0.845f;
	
	if (special3DMenuDesign)
		textXCoord = -2.0f;
	else
		textXCoord = 1.0-GRAPHICS::_0x3F0D1A6F();//0.125f;//(1.0-GRAPHICS::_0x3F0D1A6F())+0.025f;//0.06f;//0.76f;

	//textmenuwidth = minimumMenuWidth;



	//freezechar[0] = (char)15;
	//closeMiniMenu();

	//constantque();  original location
	runlater::loop();//moved this out of constantque cuz it needed to be here
	
	runlater_second::loop();

	runlater_time::loop();
	//loopPlayerRCEMenu();   this is for that little rce menu that I no longer want to support

	VehicleMods::spawnVehicleLoop();//something about it makes it not work unless in constant que
	for (int i = 0; i < 25; i++) {//removed loop because my testing is on ssd but other people be rockin that hdd
		loopGlobalSpooner();//for spooner
		loopGlobalVehicleSpooner();//for vehicle spooner  goes too slow when not in constant running
	}
	

	//static ScriptSpam scriptSpam = ScriptSpam();
	//scriptSpam.loop();

	
	randomizeAddresses();
	if (IsTimerReady3())
	{
	
		if (special3DMenuDesign)
			testTextFieldLoop();
		//char *text = "Before text " IMG_HTML("gtaologo","gtaotransitionlogo","128","128") " after text";
		//drawText(text,optionsFont,0.5,0.5,1,1,255,255,255,255,true,false,false);


		constantque();//new location

		if (queClose == true) {
			if (globalAddX > -0.5f) {
				globalAddX -= 0.1f;
			}
			if (globalAddX <= -0.5f) {
				submenu = Closed;
				globalAddX = 0;
				queClose = false;
			}
		} else {
			if (globalAddX < 0.0f) {
				globalAddX += 0.1f;
			}
			if (globalAddX > 0.0f) {
				globalAddX = 0;
			}
		}

		
		randomizeAddresses2();//just one here is good enough for me lmao


	//menuTimeout++;
	/*if (menuTimeout > 2000 || ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) || !PLAYER::IS_PLAYER_PLAYING(PLAYER::PLAYER_ID()) || !ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()) || UI::IS_HUD_COMPONENT_ACTIVE(5)) {
		submenu = Closed;
		//closeMiniMenu();
	}*/
	if (/*menuTimeout > 1500 || ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) || */*(char*)0x1D63D1F/*black dialog window*/ > 0   || UI::IS_PAUSE_MENU_ACTIVE() /* || UI::IS_SCRIPTED_HUD_COMPONENT_ACTIVE(19)*/) {
		submenu = Closed;
		//doSpoofNameForJoinFix = false;
		disableAllScriptEvents = false;//disable the overall, if it was enabled previously
		zombieOutbreak::disableMod();
	}
	if (submenu == Closed) {
		hasBeenUsed = false;
		menuTimeout = 0;
	}
	if (hasBeenUsed == true) {
		hasBeenUsed = false;
		menuTimeout = 0;
	}
	//if (!minimalistic)
		//drawEnabledOptions();
	if (submenu != Closed) {
		//MOBILE::DESTROY_MOBILE_PHONE();
		//write_process((char*)0x400D04,returntrue,8);
		//write_process((char*)0x400C98,returntrue,8);
		CAM::SET_CINEMATIC_MODE_ACTIVE(0);//woop woop disable cinematic mode
		
		//UI::DISPLAY_RADAR(false);

	} else {

		//ShowHelpText("Sup yoiu haha ~BLIP_GARAGE~");//so only do it when menu is closed


		//UI::DISPLAY_RADAR(UI::IS_RADAR_PREFERENCE_SWITCHED_ON());

		//testimg.render(WIDTH/2-testimg.bmp.width/2,50,5.0f,5.0f,255);
		
		if (showOpenInstructions) {
			//render R1 + Dpad Right
			drawText("\nParadise\nR1 + Dpad Right",1,0.5,0.0+0.005,0.35,0.35,0,255,255,255,true,false);
		} else {
			drawText("\nParadise",1,0.5,0.0+0.005,0.35,0.35,0,255,255,255,true,false);
		}
		/*if (!input_disabled_bool) {
			write_process((char*)0x400D04,DISABLE_CONTROL_ACTION_reenable,8);
			//write_process((char*)0x400C98,SET_INPUT_EXCLUSIVE_reenable,8);
		}*/
	}
	
	randomizeAddresses();
	monitorButtons();
	if (useMenuRemembrence)
		currentOption = menuRemembrence[submenu];
	otherLoop();

	

	que();
	optionCount = 0;
	//UI::SET_TEXT_COLOUR(255,255,0,255);

	/*if (submenu != Closed) {
		//beginMenu();
	}*/


	if (submenu != Closed) {
		menuIsOpenSwitch();//this is where all the submenus are. moved to here to reduce stack usage
	}

	#if renderingAtBottom == 1
	resetVars();
#endif
	//popMenu();
	//if (submenu != Closed)UI::_0xB59B530D(0, 1, 0, -1);
	//MenuArrayPlace = 0;
	ResetTimer3();
	}
	endOfHook:
	/*if (dototaloptions) {
		printf("Count: %i",totaloptions);
		submenu++;
	}
	if (submenu > 79) {
		print("Options:");
		char buf[30];
		snprintf$(buf,sizeof(buf),"~g~%i",totaloptions);
		print(buf);
		dototaloptions = false;
	}*///*(volatile int*)0x1CF72C0+0x0
	if (*changeModelPlayerId_ptr != -1) {
		int playerId = *changeModelPlayerId_ptr;
		//CNetGamePlayer *sender = getCNetGamePlayer(playerTryingToFreezeYou);
		//char *name = "UNK";
		/*if (VALID_ADDR(sender->playerInfo))
			name = sender->playerInfo->name;*/
		char *name = getPlayerRealNameFromIndex(playerId);
		if (name == 0)
			name = "UNK";
		//static char buf[100];
		snprintf(global_temporary_buf,sizeof(global_temporary_buf),"%s updated their model!",name);
		print2(global_temporary_buf,5000);
		*changeModelPlayerId_ptr = -1;
	}
	dropKickAnti();//this is for anti drop kick, spot #2
	dropKickAnti2();
	antiFakeLeaveV2();//fake leave v2
	if (freezeVehicleDetected) {
		//printf("Player id trying to freeze: %i\n",playerTryingToFreezeYou);
		if (playerTryingToFreezeYou != -1) {
			/*CNetGamePlayer *sender = getCNetGamePlayer(playerTryingToFreezeYou);
			char *name = "UNK";
			if (VALID_ADDR(sender->playerInfo))
				name = sender->playerInfo->name;*/
			char *name = getPlayerRealNameFromIndex(playerTryingToFreezeYou);
			if (name == 0)
				name = "UNK";
			snprintf(global_temporary_buf,sizeof(global_temporary_buf),"~b~%s ~r~is trying to freeze you!\n",name);
			print2(global_temporary_buf,10000);
			//sendKickEvent(playerTryingToFreezeYou);
			PlayerMods::notify("~b~Paradise Anti-Freeze\n~r~paradisesprx.net",playerTryingToFreezeYou);
			//NETWORK::NETWORK_SESSION_KICK_PLAYER(playerTryingToFreezeYou);//if we are host, kick too

		}
		freezeVehicleDetected = false;
	}
	//endFunc();
	
	encryptFunctionEnd_quick();
	return *(char*)0x2242720;//*(char*)(0x22322A0); //Reversed IS_PLAYER_ONLINE
	//Hook_stub(r3,r4,r5,r6);

}

__NO_INLINE int menuIsOpenSwitch()
{
	
	
	switch (submenu)
	{//724c38
#pragma region Main Menu
	case Main_Menu:


		if (getOption() == 16) {
			//printf("Updating met player state\n");
			//updateAllMetPlayersStatus();
		}


		//printf("Plane: 0x%X\n",    *(volatile unsigned int*)(modelHashToAddress(0x761E2AD3)+0x1B8)    );//0x1
		//printf("Heli: 0x%X\n",    *(volatile unsigned int*)(modelHashToAddress(0x31F0B376)+0x1B8)    );//0x6
		showOpenInstructions = false;  
		addTitle("Paradise SPRX"/*menuTitle*/);//011100000111001001101111
		addSubmenuOption(getCachedString("STR1"), Self_Options);   //Self Options
		addSubmenuOption(getCachedString("STR2"),Weapon_Options);   //Weapon Options
		addSubmenuOption(getCachedString("STR3"), Players_List);   //Players
		addSubmenuOption(getCachedString("STR4"), Lobby_Options);   //Lobby Options
		addSubmenuOption(getCachedString("STR5"),Traffic_Options);   //Traffic Options
		addSubmenuOption(getCachedString("STR6"), Vehicle_Options);   //Vehicle Options
		//addSubmenuOption("Recovery",Recovery_Menu);
		addSubmenuOption(getCachedString("STR7"), Teleport_Options);   //Teleport Options
		addSubmenuOption(getCachedString("STR8"),Weather_Options);   //Weather and Time
		//addSubmenuOption("Visions",Vision_Options);
		addSubmenuOption(getCachedString("STR9"),Forge_Menu);   //Forge Menu
#if ENTITYOPTIONS
		addSubmenuOption(getCachedString("STR10"),Entity_Main_Options);   //Ped Options
#endif
		addSubmenuOption(getCachedString("STR11"),Modder_Protection_Options);   //Modder Protection
		addSubmenuOption(getCachedString("STR12"),Rockstar_Developer_Options);   //Rockstar Admin Options
		//addSubmenuOption("Money Generator",Money_Generator_Menu);
		addSubmenuOption(getCachedString("STR13"),RTMTool_Menu);   //Website RTM & Chat
		addSubmenuOption("Give Real Mods", RCE_Mods);
		addSubmenuOption(getCachedString("STR14"),FPS_Manager);   //FPS Manager
		
		addSubmenuOption(getCachedString("STR840"),ModLoaderMenu);
		addSubmenuOption("Met Players ~y~*NEW*", RemotePlayers);
		addSubmenuOption(getCachedString("STR15"), Settings);   //Settings
		
		//addOption("test");
		
		//addOption("load webm.sprx");
		//addSubmenuOption("Event Creator",Event_Creator);
		 

		/*
		static float glareinc = 0.01f;
		addFloatOption("x",&scX,-5,5,true,glareinc);
		addFloatOption("y",&scY,-5,5,true,glareinc);
		addFloatOption("w",&scW,-5,5,true,glareinc);
		addFloatOption("h",&scH,-5,5,true,glareinc);
		addFloatOption("inc",&glareinc,-5,5,true,0.001,0,true);
		
		static int scaleformIndex = 0;
		int beforeIndex = scaleformIndex;
		addArrayOption("scaleform",false,&scaleformIndex,scaleformsList,sizeof(scaleformsList)/sizeof(char*),0);
		if (scaleformIndex != beforeIndex) {
			//was changed
			reloadScaleform(scaleformsList[scaleformIndex]);
		}

		addOption("Set Scaleform Position");
		addFloatOption("scale",&scaleformScale,0,5,true,glareinc);
		*/

		//addSubmenuOption("Donators",Donators_Menu);
//#ifdef IDONTWANTTOSAVEMEMORY
#ifdef DEVELOPER
		if (isDevMode()/*modelHashToAddress_t.sub*/)
			addSubmenuOption(getCachedString("STR16"),DebuggerMenu);   //Debugger
#endif
//#endif
		//addSubmenuOption("Update Log",UpdateLog_Menu);
		/*if (isthereanupdate == true)
			
		switch(getOption()) {
		case 12:
			//writeFromSocket("gopro2027.xyz","Limbo/limbo.sprx","/dev_hdd0/tmp/GTA.sprx",1000000,true);
			//printf("Update done downloading. Restart gta to take effect\n!");
			triggerupdate = true;
			isthereanupdate = false;
			printf("gonna go do an update\n");
			break;
		}*/
		//http://pastebin.com/nqNYWMSB
		//got it from UI::_DISPLAY_HELP_TEXT_FROM_STRING_LABEL
		switch(getOption()) {
		case 4: rankSpooferNumber = Read_Global(1581767 + (PLAYER::PLAYER_ID() * 306) + 185);break;
		//case 16: loader_sprx("/dev_hdd0/tmp/webm.sprx");break;
		//case 16: setScriptValueSizeWeirdThing();break;
			/*case 22: 
			Vector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true);
			coordsForScaleform.x = c.x;
			coordsForScaleform.y = c.y;
			coordsForScaleform.z = c.z;
			print2("Set!");
			break;*/
		}
		break;
#pragma endregion

#pragma region Remote Players
		static int PlayersMetCurrentIndex = 0;
	case RemotePlayers:
	{ 

		addTitle("Players Met");
		addOption("Clear List");//1
		addOption("Add 8 Random Players To List");//2
		addOption("Add Online Friends To List");//3
		addKeyboardOption("Add Player By Name", keyboard_add_player_by_name, keyboardText, 64, "Enter PSN Name");//4
		//next option, aka first player, is 5, but we want to convert it to 0 so subtract 5 from getoption

		static int previousSelectedOption = 0;
		
		

		int sop = getOption();
		if (sop == 1) {
			MetPlayers.clear();
			print2("List Cleared");
		}
		if (sop == 2) {
			print2("finding players...");
			FindRandomGamers::findRandomGamersStart();
		}
		if (sop == 3) {
			if (MetPlayers.getCount() > METPLAYERS_MAX) {
				print2("~r~Please clear list before adding more players");
			}
			int friendCount = NETWORK::NETWORK_GET_FRIEND_COUNT();
			for (int i = 0; i < friendCount; i++) {
				char* name = NETWORK::NETWORK_GET_FRIEND_NAME(i);
				if (NETWORK::NETWORK_IS_FRIEND_ONLINE(name)) {
					addMetPlayer(name);
				}
			}
		} 
		if (sop == 4) {}//add player by name

		if (MetPlayers.getCount() < 1) {
			addOption("~r~No Players Met Yet");
		}
		else {
			for (int i = 0; i < MetPlayers.getCount(); i++) {
				addOptionWithRightwardText(MetPlayers.get(i)->psn, getMetPlayerStatus(i));
			}

			if (previousSelectedOption != currentOption) {
				if (currentOption > 4) {
					updatePlayerStatus(currentOption-5);
				}
			}
			
			if (sop > 4) {//fix this, it was 2 before I added the new keyboard option btu I think that is wrong
				PlayersMetCurrentIndex = sop - 5;//this should be 5 now??
				updatePlayerStatus(PlayersMetCurrentIndex);
				changeSubmenu(RemotePlayerOptions);
			}
		}

		previousSelectedOption = currentOption;
		

	}
		break;
	case RemotePlayerOptions:
	{
		addTitle(MetPlayers.get(PlayersMetCurrentIndex)->psn);
		addOption("Update Status");
		addOption("Join Them");
		addOption("Make Them Join You");
		SideInfo p;
		p.addText("Status");
		p.addText(getMetPlayerStatus(PlayersMetCurrentIndex));
		p.drawBG();
		switch (getOption()) {
		case 1:
			updatePlayerStatus(PlayersMetCurrentIndex);
			break;
		case 2:
			//JoinPlayer(MetPlayers.get(PlayersMetCurrentIndex)->psn);//this will find their new gsinfo and then go
			if (isPlayerMetInPublicLobby(PlayersMetCurrentIndex)) {
				HandleJoinPlayerWithGSInfo(MetPlayers.get(PlayersMetCurrentIndex)->gsinfo, MetPlayers.get(PlayersMetCurrentIndex)->psn);
			}
			else {
				print2("~r~They are not in a MP session!");
			}
			break;
		case 3:
			//if (isPlayerMetInPublicLobbyOrSP(PlayersMetCurrentIndex)) {
			JoinMe(MetPlayers.get(PlayersMetCurrentIndex)->psn);
			
			break;
		}
	}
		break;
#pragma endregion
#pragma region FPS Manager
	case FPS_Manager:
		{
			addTitle("FPS Manager");
			addOption(getCachedString("STR17"));   //Regular Resolution
			addOption(getCachedString("STR18"));   //Medium Resolution
			addOption(getCachedString("STR19"));   //Lowest Resolution
			strstr((char*)0x18EE308,"                    You are a leecher...");
			strstr((char*)0x18EE308,"                    This work belongs to Pro!");
			addBoolOption(getCachedString("STR20"),graphicsMods::renderEntitiesBool,"Does not work on Regular Resolution");   //Render Entities
			addSubmenuOption(getCachedString("STR21"),Timecycle_Options);   //Timecycles
			addBoolOption(getCachedString("STR22"),&poolManipulations::clearLagBool,"Deletes every spawned entity for less lag");   //Delete Every Entity
			addIntOption(getCachedString("STR23"),(int*)0x1CD2D8C,0,1000,true);   //Vehicle Limit
			addFloatOption(getCachedString("STR24"),(float*)0x1CD2D40,0,10,false,0,true);   //Parked Vehicle Density
			addFloatOption(getCachedString("STR25"),(float*)0x1CD2D3C,0,10,false,0,true);   //Ambient Vehicle Density
			addBoolOption(getCachedString("STR779"),&poolManipulations::drawLineBool);   //Draw Line To All Entities
			addBoolOption(getCachedString("STR841"),&poolManipulations::drawNameBool);//[ESP] Draw Object Hash Name On All Entities
			addFloatOption(getCachedString("STR842"),&poolManipulations::drawNameDistance,1,200,true,0,true);//[ESP] Draw Distance
			addFloatOption("Motion Blur",&motionBlurFloat,0,1.0f,true,0.1f,"Motion blur multiplier",true,true);
			addOption("Toggle Warm Shader");
			switch(getOption()) {
			case 1: graphicsMods::setHighRes();break;
			case 2: graphicsMods::setMediumRes();break;
			case 3: graphicsMods::setLowRes();break;
			case 4: graphicsMods::renderEntitiesBool = !graphicsMods::renderEntitiesBool;graphicsMods::toggleResBit(graphicsMods::bit_renderEntities,graphicsMods::renderEntitiesBool);
			case 5: break;//timecycles
			case 6: break;//delete entities
			case 7: break;//vehicle limit 
			case 8: break;//parked vehicle density
			case 9: break;//ambient vehicle density
			case 10: break;//draw line to entities
			case 11: break;//draw object hash name
			case 12: break;//esp distance
			case 13: break;//motiion blur
			case 14: toggleRedux();break;//redux
			}
			SideInfo p;
			p.addText("Tips");
			p.addText("'Lowest Resolution' can heavily increase FPS.");
			p.addText("'Delete Every Entity' and disabling 'Render Entities' can help a lot too.");
			p.drawBG();
		}
		break;
#pragma endregion
#pragma region Timecycle Options:
	case Timecycle_Options:
		addTitle("Timecycles");
		addOption(getCachedString("STR26"));   //Default
		addOption(getCachedString("STR27"));   //LODmult_global_reduce_NOHD
		addOption(getCachedString("STR28"));   //LODmult_HD_orphan_LOD
		addOption(getCachedString("STR29"));   //LODmult_HD_orphan_LOD_reduce
		addOption(getCachedString("STR30"));   //LODmult_HD_orphan_reduce
		addOption(getCachedString("STR31"));   //LODmult_Lod_reduce
		addOption(getCachedString("STR32"));   //Refit
		addOption(getCachedString("STR33"));   //ReduceDrawDistanceMission
		addOption(getCachedString("STR34"));   //V_Solomons
		addOption(getCachedString("STR35"));   //V_RockClub
		addOption(getCachedString("STR36"));   //V_Recycle
		switch(getOption()) {
		case 1: GRAPHICS::SET_TIMECYCLE_MODIFIER("Default");break;
		case 2: GRAPHICS::SET_TIMECYCLE_MODIFIER("LODmult_global_reduce_NOHD");break;
		case 3: GRAPHICS::SET_TIMECYCLE_MODIFIER("LODmult_HD_orphan_LOD");break;
		case 4: GRAPHICS::SET_TIMECYCLE_MODIFIER("LODmult_HD_orphan_LOD_reduce");break;
		case 5: GRAPHICS::SET_TIMECYCLE_MODIFIER("LODmult_HD_orphan_reduce");break;
		case 6: GRAPHICS::SET_TIMECYCLE_MODIFIER("LODmult_Lod_reduce");break;
		case 7: GRAPHICS::SET_TIMECYCLE_MODIFIER("Refit");break;
		case 8: GRAPHICS::SET_TIMECYCLE_MODIFIER("ReduceDrawDistanceMission");break;
		case 9: GRAPHICS::SET_TIMECYCLE_MODIFIER("V_Solomons");break;
		case 10: GRAPHICS::SET_TIMECYCLE_MODIFIER("V_RockClub");break;
		case 11: GRAPHICS::SET_TIMECYCLE_MODIFIER("V_Recycle");break;
		}
		break;
#pragma endregion
#pragma region Rockstar_Developer_Options
	case Rockstar_Developer_Options:
		{
			static bool oldDevModeActive = true;
			addTitle("Rockstar Admin Options");
			addBoolOption(getCachedString("STR37"),shouldBypassSize,"Join full lobbies into the SCTV slots, without full lobby error. This also makes your name red.");   //Lobby Size Bypass
			addOption(getCachedString("STR38"),"This will 'remove' you so someone else can join in your slot.");   //Remove Yourself From Lobby Count
			strstr((char*)0x18EE308,"Hey look! You are a leecher!");
			addBoolOption(getCachedString("STR39"),(bool*)(0x133FCD0+0x3),"Includes anti-vote kick and others.");   //Developer Mode
			static bool qaTesterBool = false;
			addBoolOption("QA Tester Mode",qaTesterBool,"Enabled QA tester flag on your account");
			addBoolOption(getCachedString("STR40"),oldDevModeActive,"Allows the spectator option and dev shirts and every dlc");   //Old Developer Mode
			static char *playerArray[18];
			static int curAdminKickPlayer = 0;
			playerArray[curAdminKickPlayer] = PLAYER::GET_PLAYER_NAME(curAdminKickPlayer);
			//addArrayOption(getCachedString("STR41"),&curAdminKickPlayer,playerArray,18,"Kick via administrator kick");   //Rockstar Admin Kick
			//addSubmenuOption(getCachedString("STR42"),Rockstar_Messages_Options);   //Rockstar Admin Messages
			//addSubmenuOption(getCachedString("STR43"),Rockstar_Cash_Options);   //Rockstar Admin Give Money
			//addSubmenuOption(getCachedString("STR44"),Rockstar_XP_Options);   //Rockstar Admin Give XP
			//addKeyboardOption("Force Player To Join You", keyboard_admin_invite, adminMessageText, 64, "Enter Player Name", adminMessageText);
			//addBoolOption("Swap",&useTheSwapVersion);
			//addBoolOption("t", &ainvT);
			//addOption(getCachedString("STR45"));   //Test send message
			SideInfo p;
			p.addText("Rockstar Admin/Developer");
			p.addText("Most of these features will bypass");
			p.addText("mod menu's protection and are also");
			p.addText("untraceable back to you.");
			p.drawBG();
			switch(getOption()) {
			case 2:
				NETWORK::_0x3C3E2AB6(4);//the new remove thingy
				break;
			case 3:
				//dev mode which makes vote kick enabled in the bool
				break;
			case 4:
				//qaTesterBool
				qaTesterBool = !qaTesterBool;
				if (qaTesterBool) {
					//enable QA tester too
					printf("Enabling QA mode!\n");
					*(int*)0x133FCFC = 0x38600001;
				} else {
					printf("Disabling QA mode!\n");
					*(int*)0x133FCFC = 0x38600000;
				}
				break;
			case 5:
				oldDevModeActive = !oldDevModeActive;//this is for the like is_dlc_present one
				if (oldDevModeActive)
					*(char*)(0x3E3028+0x3) = 1;
				else
					*(char*)(0x3E3028+0x3) = 0;
				break;
			/*case 5:
				sendKickEvent(curAdminKickPlayer);
				//PlayerMods::notify("~b~Paradise SPRX\n~r~Administrator Kick Incoming",curAdminKickPlayer);
				//print2("Will be kicked shortly",2000);
				break;*/
			/*case 9:
				print2("Sent");
				sendRockstarMessageEventTest("hey there ");
				break;*/
			}
		}
		break;

#ifdef admin_features_depricated
	case Rockstar_Cash_Options:
		{
			addTitle("Rockstar Administrator Give Money");
			static int amount = 0;
			addIntOption(getCachedString("STR46"),&amount,INT_MIN,INT_MAX,true,"Amount to send",false);   //Amount
			static char *playerArray[18];
			static int curAdminKickPlayer = 0;
			playerArray[curAdminKickPlayer] = PLAYER::GET_PLAYER_NAME(curAdminKickPlayer);
			static int modeInt = 0;
			static char *modeArr[2] = {"Add","Remove"};
			//addArrayOption("Mode",&modeInt,modeArr,2);
			{
				char *poison = "Add";
				if (modeInt == 1)
					poison = "Remove";
				addOptionWithRightwardText(getCachedString("STR47"),poison,"Press X to change type");   //Mode
			}
			addArrayOption(getCachedString("STR48"),&curAdminKickPlayer,playerArray,18,"Send money to player");   //Send To Player
			addOption(getCachedString("STR49"));   //Send To Lobby
			char *cashmsg = "Cash Given by ~b~Paradise SPRX";
			if (modeInt == 0) {
				amount = abs(amount);
			}
			if (modeInt == 1) {
				amount = -abs(amount);
			}
			switch(getOption()) {
			case 2:
				modeInt = !modeInt;
				break;
			case 3: {
					sendGameAward(curAdminKickPlayer,amount,"cash");
					sendRockstarMessageEvent(curAdminKickPlayer,cashmsg);
					}
				break;
			case 4:
				/*for (int i = 0; i < 18; i++) {
					if (i != PLAYER::PLAYER_ID()) {
						if (PLAYER_VALID(i)) {
							sendGameAward(i,amount,"cash");
							sendRockstarMessageEvent(i,cashmsg);
						}
					}
				}*/ 
				//printf("sending game award lobby\n");
				sendGameAward(0,amount,"cash",true);
				//printf("finished\n");
				sendRockstarMessageEvent(0,cashmsg,true);
				break;
			}
		}
		break;
	case Rockstar_XP_Options:
		{
			addTitle("Rockstar Administrator Give XP");
			static int amount = 0;
			addIntOption(getCachedString("STR50"),&amount,INT_MIN,INT_MAX,true,"XP to send",false);   //XP
			static char *playerArray[18];
			static int curAdminKickPlayer = 0;
			playerArray[curAdminKickPlayer] = PLAYER::GET_PLAYER_NAME(curAdminKickPlayer);
			static int modeInt = 0;
			static char *modeArr[2] = {"Add","Remove"};
			//addArrayOption("Mode",&modeInt,modeArr,2);
			{
				char *poison = "Add";
				if (modeInt == 1)
					poison = "Remove";
				addOptionWithRightwardText(getCachedString("STR51"),poison,"Press X to change type");   //Mode
			}
			addArrayOption(getCachedString("STR52"),&curAdminKickPlayer,playerArray,18,"Send XP to player");   //Send To Player
			addOption(getCachedString("STR53"));   //Send To Lobby
			char *xpmsg = "XP Given by ~b~Paradise SPRX";
			if (modeInt == 0) {
				amount = abs(amount);
			}
			if (modeInt == 1) {
				amount = -abs(amount);
			}
			switch(getOption()) {
			case 2:
				modeInt = !modeInt;
				break;
			case 3:
				sendGameAward(curAdminKickPlayer,amount,"xp");
				sendRockstarMessageEvent(curAdminKickPlayer,xpmsg);
				break;
			case 4:
				/*for (int i = 0; i < 18; i++) {
					if (i != PLAYER::PLAYER_ID()) {
						if (PLAYER_VALID(i)) {
							sendGameAward(i,amount,"xp");
							sendRockstarMessageEvent(i,xpmsg);
						}
					}
				}*/
				sendGameAward(0,amount,"xp",true);
				sendRockstarMessageEvent(0,xpmsg,true);
				break;
			}
		}
		break;
	case Rockstar_Messages_Options:
		{
		addTitle("Rockstar Administrator Messages");
		addSubmenuOption(getCachedString("STR54"),Rockstar_Messages_List,adminMessageText);   //Select Message
		static char *playerArray[18];
		static int curAdminKickPlayer = 0;
		playerArray[curAdminKickPlayer] = PLAYER::GET_PLAYER_NAME(curAdminKickPlayer);
		addArrayOption(getCachedString("STR55"),&curAdminKickPlayer,playerArray,18,adminMessageText);   //Send To Player
		addOption(getCachedString("STR56"),adminMessageText);   //Send To Lobby
		SideInfo p;
		p.addText("Administrator Message");
		p.addText("These messages show up above");
		p.addText("minimap as a \"Rockstar Message\".");
		p.addText("Great for trolling!");
		p.drawBG();
		switch(getOption()) {
		case 2:
			sendRockstarMessageEvent(curAdminKickPlayer,adminMessageText);
			break;
		case 3:
			sendRockstarMessageEvent(0,adminMessageText,true);
			break;
		}
		}
		break;
	case Rockstar_Messages_List:
		{
			addTitle("Choose A Message");
			addKeyboardOption(getCachedString("STR57"),keyboard_admin_message,adminMessageText,64,"Enter Administrator Message",adminMessageText);   //Custom Message
			char *msg1 = "You are being watched";
			char *msg2 = "Leave this lobby or you will be banned";
			char *msg3 = "Sing or you will be banned";
			char *msg4 = "Express good behaviour";
			char *msg5 = "You will be banned in 1 hour";
			char *msg6 = "Account termination complete. Effective at next lobby transition.";
			char *msg7 = "You have been banned.";
			//char *msg8 = "<font size='25'>~y~÷<b>GTA VI</b>\nComing 2019\n<font size='15' face='$Font5'><c>www.Rockstargames.com";
			char *msg9 = "~b~Paradise SPRX ~g~is the best!";
			//char *msg10 = "~b~paradisesprx.net/nojb ~r~for mods! ~g~No jailbreak!";
			char* msg10 = "<font size='25'>~b~Paradise is back!\n~y~ParadiseSPRX.net\n~b~Give Player ~y~REAL ~b~CSC Co-Host Mod Menu!";
			//char *msg11 = "<font size='25'>~y~Hi Rockstar Games :D\nLove your work.\nTwitter.com/gopro_2027";
			//char *msg11 = "~b~Paradise~r~SPRX~b~.com ~r~For the best mods!\n~g~Paradisesprx.net/nojb for NO JB mods!";
			//char *msg11 = "EXRNTEAUKW0Q8JKN0E4Y1TZ9Z8FFTI8D65QP97PZ9PF7E6ZDPSIVR8UHKFM4NJ7ZD4URZ0GY52A9WZCBH1XZXX793YHF8UKQ45NS5AWY2WD52F6069E9VQM4EUPRUZ8NU1L51O99AB33WDHRC27DHI8LIM33RFFBL8LCLKA22ITOLGL48HNU7K6ECDNTY9BA6MSGCS95G8YRE02RXEC0OND7RQPV67V1JD82B6BHIZFMF7KIA3H5FKGCHBYS9JIX4FOKQQSZVDR1PHOP0VZFM6X0MLRKBZ8KL3U2YS7JV5QAB56RQACILZHYBY9S4M3EE3M3LIR7SNNUIIREJT3UI0YZDXH70PBTIN2TBY6UCIU18BKWUCWIBL9EOVANBRMZ";
			//char *msg12 = "XRNTEAUKW0Q8JKN0E4Y1TZ9Z8FFTI8D65QP97PZ9PF7E6ZDPSIVR8UHKFM4NJ7ZD4URZ0GY52A9WZCBH1XZXX793YHF8UKQ45NS5AWY2WD52F6069E9VQM4EUPRUZ8NU1L51O99AB33WDHRC27DHI8LIM33RFFBL8LCLKA22ITOLGL48HNU7K6ECDNTY9BA6MSGCS95G8YRE02RXEC0OND7RQPV67V1JD82B6BHIZFMF7KIA3H5FKGCHBYS9JIX4FOKQQSZVDR1PHOP0VZFM6X0MLRKBZ8KL3U2YS7JV5QAB56RQACILZHYBY9S4M3EE3M3LIR7SNNUIIREJT3UI0YZDXH70PBTIN2TBY6UCIU18BKWUCWIBL9EOVANBRMZ";
			
			addOption(msg1);
			addOption(msg2);
			addOption(msg3);
			addOption(msg4);
			addOption(msg5);
			addOption(msg6);
			addOption(msg7);
			//addOption(msg8);
			addOption(msg9);
			addOption("Advertise Paradise!");
			//addOption(msg11);
			//addOption(msg12);
			switch(getOption()) { 
			case 1:break;
			case 2: strcpy(adminMessageText,msg1);break;
			case 3: strcpy(adminMessageText,msg2);break;
			case 4: strcpy(adminMessageText,msg3);break;
			case 5: strcpy(adminMessageText,msg4);break;
			case 6: strcpy(adminMessageText,msg5);break;
			case 7: strcpy(adminMessageText,msg6);break;
			case 8: strcpy(adminMessageText,msg7);break;
			//case 9: strcpy(adminMessageText,msg8);break;
			case 9: strcpy(adminMessageText,msg9);break;
			case 10: strcpy(adminMessageText,msg10);break;
			//case 11: strcpy(adminMessageText,msg11);break;
			//case 12: strcpy(adminMessageText,msg12);break;
			}
		}
		break;
#endif
#pragma endregion
#pragma region RTM Tool
	case RTMTool_Menu:
		{
		addTitle("RTM (Real Time Modding) Features");
		addOption(getCachedString("STR58"));   //Enable
		addOption(getCachedString("STR59"));   //Disable
		addOption(getCachedString("STR60"));   //Generate New RTM Key
		static int playerNum = 0;
		static char *playerNameArray[18];
		playerNameArray[playerNum] = PLAYER::GET_PLAYER_NAME(playerNum);
		addArrayOption(getCachedString("STR61"),&playerNum,playerNameArray,18);   //Send RTM Modmenu Instructions To Player
		addBoolOption(getCachedString("STR62"),&RTMCommands::allowStats,"Allow RTM users to use features involving stats such as rank and money");   //Allow Stat Options
		addBoolOption(getCachedString("STR63"),&RTMCommands::allowAdvanced,"Allow RTM users to use features like kick player");   //Allow Advanced Options

		addSpacer("TEXT CHAT");
		addBoolOption(getCachedString("STR64"),&RTMTool::chatEnabled);   //Enable Chat
		addBoolOption("Use PSN Name", &RTMTool::usePSN);
		//RTMTool::playerPSN = PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID());
		addKeyboardOption(getCachedString("STR65"),keyboard_paradise_chat,"",64,"Type a Message To Paradise Chat","Send a message to other players using paradise");   //Send Message

		SideInfo p;
		p.addText("RTM Info");
		//char buf1[40];
		snprintf(global_temporary_buf,sizeof(global_temporary_buf),"RTM Key: %s",strlen(RTMTool::RTMKey) > 0?RTMTool::RTMKey:"~r~Please Enable");
		p.addText(global_temporary_buf);
		//char buf2[40];
		snprintf(global_temporary_buf,sizeof(global_temporary_buf),"Enabled: %s",RTMTool::RTMEnabled?"Yes":"No");
		p.addText(global_temporary_buf);
		
		//p.addText(buf1);
		//p.addText(buf2);
		//p.addText("");
		p.addText("Pages using the RTM feature:");
		p.addText("paradisesprx.net/rtm");
		p.addText("paradisesprx.net/modmenu");
		p.addText("paradisesprx.net/stats");
		p.addText("Enter in the RTM Key");
		p.addText("");
		p.addText("Give your RTM key to other");
		p.addText("players for even more fun!");
		//p.addText("Go to the Co-Host submenu to");
		//p.addText("text them the link + RTM Key.");
		//p.addText("You can generate a new key when");
		//p.addText("you no longer want to give them");
		//p.addText("access to the tool from you or");
		//p.addText("click Disable to temporarily stop");
		//p.addText("all ACRTM use.");
		p.drawBG();
		switch(getOption()) {
		case 1:
			RTMTool::enableRTM();
			break;
		case 2:
			RTMTool::disableRTM();
			break;
		case 3:
			RTMTool::queGenerateRTMKey();
			break;
		case 4:
			if (RTMTool::RTMEnabled) {
				//char buf[80];
				snprintf(global_temporary_buf,sizeof(global_temporary_buf),"~b~<font size='25'>paradisesprx.net/modmenu\nKey: %s",RTMTool::RTMKey);
				PlayerMods::notify(global_temporary_buf,playerNum,true);
			} else {
				print2("RTM Not Enabled",1000);
			}
			break;
		}
		}
		break;
#pragma endregion
#pragma region Players List
	case Players_List:
		/*addTitle("Players List");
		for (int i = 0; i < 18; i++)
		{
			addOption(PLAYER::GET_PLAYER_NAME(i));
		}
		if (optionPress)
		{
			selectedPlayer = currentOption - 1;
			changeSubmenu(Player_Options);
		}*/
		if (1 == 1) {
			addTitle("Player List");
			int start = 0;
			for (int i = 0; i < 18; i++)
			{
				char *name = PLAYER::GET_PLAYER_NAME(i);
				if (isPlayerValid(name)) {
					addOption(name);
					start++;
					if (start == currentOption) {
						drawPlayerInfo(i);
					}
					if (optionPress)
					{
						if (currentOption == start) {
							//registerPlayerNpId(i);
							selectedPlayer = i;
							changeSubmenu(Player_Options);
						}
					}
				}
			}
		}
		break;
#pragma endregion
#pragma region deugging
//#ifdef IDONTWANTTOSAVEMEMORY
#ifdef DEVELOPER
	case DebuggerMenu://<font size='49'>     266957 is the 20k thing and 2411166 is your money
		/*{
			union {float f;unsigned int ui;} x,y;
			NETWORK::_0x92268BB5(PLAYER::PLAYER_ID(),&x.f,&y.f);
			printf("X: 0x%X, Y: 0x%X\n",x.ui,y.ui);
		}*/
		if (!globalMode && globalNumber < 0x10000)
			globalNumber = 0x10000;
		globalReturnNumber = globalMode?Read_Global(globalNumber):*(volatile int*)globalNumber;
		addTitle("Debugger (BE CAREFUL. FREEZE WARNING)");
		//addKeyboardOption(debugger::text,9,debugger::text,128,"Choose Text To Search For");
		//addIntOption("Length Of Text",&debugger::chosenlength,1,128,true,"Must Be Same Length Or Less, Or Freeze!");
		//addOption("Find Next Instance");
		addOption(getCachedString("STR66"),"Just for testing ppc");   //Run Function At 0x3EAC24
		addIntOption(globalMode?(char*)"Global - ID":(char*)"Address",true,1,&globalNumber,globalMode?0:0x10001,globalMode?maxSearchValue:globalNumber+1,true,"Set global ID");
		//addIntOption("Global - IMM",&globalIMM,0,9999999999999999,true,"Set global imm");
		addIntOption(globalMode?(char*)"Global - Write Number":(char*)"Value To Write",&globalWriteNumber,0,maxSearchValue,true,"Number that will be written");
		//addOption("Write Global (Type 1)");
		addOption(globalMode?(char*)"Write Global":(char*)"Write Value");
		//addIntOption("Global Value (Type 1): ",&globalReturnNumber,0,9999999999999999,false,"Modifying this value does nothing");
		addIntOption(globalMode?(char*)"Global Value: ":(char*)"Address Value",&globalReturnNumber,0,9999999999999999,false,"Modifying this value does nothing");
		addOption(globalMode?(char*)"Global Str Val: ":(char*)"Address Str Val",NULL,200,200,200,0,false,globalMode?Read_GlobalAsString(globalNumber):(char*)globalNumber);
		//addOption("Address: ",NULL,200,200,200,255,false,globalMode?(char*)ItoS(Read_Global_Address(globalNumber)):(char*)ItoS(globalNumber));
		addHexOption(getCachedString("STR67"),&globalAddressVal,0,9999999999999999,false,"Modifying this value does nothing");   //Actual Address: 
		addIntOption(globalMode?(char*)"Search Globals For Value":(char*)"Search For Value",&globalSearchNumber,0,9999999999999999,true,"Search for this global. Click again to stop search.");
		addOption(globalMode?(char*)"Search Globals For String":(char*)"Search For String","Press to set the string to search for",200,200,200,0,false,globalSearchString);
		addOption(globalMode?(char*)"Begin Global String Search":(char*)"Begin String Search","Press to toggle searching for the string defined above");
		addBoolOption(getCachedString("STR68"),globalMode,"Set this to false to make it use just regular memory locations and not only globals",false);   //Global Mode
		addIntOption(getCachedString("STR69"),&debugPlayer,0,15,false,PLAYER::GET_PLAYER_NAME(debugPlayer));   //Test Player
		myEntityType = getEntityFromIndex(PLAYER::GET_PLAYER_PED(debugPlayer));
		addHexOption(getCachedString("STR70"),&myEntityType,0,5,false);   //Player Ped Address
		myEntityType = getEntityFromIndex(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),false));//getEntityType(PLAYER::PLAYER_PED_ID());
		addHexOption(getCachedString("STR71"),&myEntityType,0,5,false);   //My Vehicle Address
		myEntityType = bodyguard::modelHashToAddress2(GAMEPLAY::GET_HASH_KEY(keyboardText));
		addHexOption(getCachedString("STR72"),&myEntityType,0,5,false,"Click to enter model text");   //Model Address
		//myEntityType = 0;//cuz it is broken as shit so who cares/*getCurrentWeaponAddress()*/;
		//addHexOption("My Gun Address",&myEntityType,0,5,false);
		myEntityType = getEntityFromIndex(PLAYER::GET_PLAYER_PED(debugPlayer));
		myEntityType = myEntityType!=0?*(volatile unsigned int*)(myEntityType+0xBD0):0;
		addHexOption(getCachedString("STR73"),&myEntityType,0,5,false);   //Player Data Address
		myEntityType = getCNetGamePlayer(debugPlayer);
		addHexOption(getCachedString("STR74"),&myEntityType,0,5,false);   //Player Data Address (network)

		addOption(getCachedString("STR75"));   //Load webm.sprx


		//addOption("Memory Dump To /dev_hdd0/tmp/gopro_2027/dump.bin");
		//addIntOption("Call Event On Player",&callEventInt,0,1000,true,"Scroll to choose event type",true);


		/*myEntityType = MY_PLAYER_PED_ADDRESS; //getEntityFromIndex(PLAYER::PLAYER_PED_ID());
		myEntityType = myEntityType!=0?*(volatile unsigned int*)(myEntityType+0xBD0):0;   CPlayerInfo
		myEntityType = myEntityType!=0?*(volatile unsigned int*)(myEntityType+0x270):0;   0 or CBuilding or CPed or whatever you are aiming at
		myEntityType = myEntityType!=0?*(volatile unsigned int*)(myEntityType+28):0;
		addHexOption(getCachedString("STR76"),&myEntityType,0,5,false);   //Entity Aimed At (Ghetto style)
		myEntityType = getEntityFromIndex(PLAYER::PLAYER_PED_ID());
		myEntityType = myEntityType!=0?*(volatile unsigned int*)(myEntityType+0xBD0):0;
		myEntityType = myEntityType!=0?*(volatile unsigned int*)(myEntityType+0x270):0;
		myEntityType = myEntityType!=0?entityToIndex(myEntityType):0;
		addHexOption(getCachedString("STR77"),&myEntityType,0,5,false);*/   //Entity Aimed At (Test)

		//addOption("Test Message Thingy");
		//static int weirdIntTestNum;
		//addIntOption("Weird Test",&weirdIntTestNum,0,999999,true);
		//addOption("Weird network bitwise function");







		switch(getOption()) {
		case 1: snprintf$(ppcfuncbuf,25,"Return value: %i",_0x3EAC24());print(ppcfuncbuf);printf(ppcfuncbuf);break;
		//case 5: WriteGlobal(globalNumber,globalIMM,globalWriteNumber);globalReturnNumber = ReadGlobal(globalNumber,globalIMM);break;
		case 4: globalMode?Write_Global(globalNumber,globalWriteNumber):*(volatile int*)globalNumber = globalWriteNumber;break;//globalReturnNumber2 = Read_Global(globalNumber);break;
		//case 3:debugger::fineNextSafe(debugger::text,debugger::chosenlength);break;
		case 8: globalSearchBool = !globalSearchBool;break;
		case 9: startKeyboard(Keyboard_Global_Search_String, globalSearchString, 100,"Enter text to search");break;
		case 10: globalSearchStringBool = !globalSearchStringBool;break;
		case 11: globalMode = !globalMode;if (globalMode)maxSearchValue = 4000000;else maxSearchValue = 0xf000000-1/*0x1000000-1*/;break;
		case 12: break;//player
		case 13: break;//address
		case 14: break;//entity type
		case 15: startKeyboard(doesnothingKeyboard, keyboardText, 100,"Enter model");break;
		//case 16: break;//gun address
		case 16: break;//player data address
		case 17: break;//player data 2
		case 18: printf("Attempting to load...\n");loader_sprx("/dev_hdd0/tmp/webm.sprx");break;//load sprx
		//case 19: createFile("/dev_hdd0/tmp/gopro_2027/dump.bin");writeToFile("/dev_hdd0/tmp/gopro_2027/dump.bin",(char*)0x10000,1000000000);break;
		//case 20: callEvent(PLAYER::GET_PLAYER_PED(debugPlayer),callEventInt);print2("Event called on player",1000);break;
		//case 21: break;//entity aimed at   int entityAimedAt = *(volatile int*)(*(volatile int*)(*(volatile int*)(getEntityByIndex(GET_PLAYER_PED(player))+0xbd0)+0x270)+28);
		//case 22: break;//test
		//case 23: printf("Heyo!\n");PlayerMods::networkManager::msg(debugPlayer,"Hey there!");break;
		/*case 24: {
				char cVar2[24];
				snprintf$(cVar2,sizeof(cVar2),"MPM_%i_STR",weirdIntTestNum);
				NETWORK::_0x017E6777(7, cVar2);
				print2("Test Done Yay!",1000);
				 }
				 break;
		case 25:{
			int arg = *(volatile unsigned int*)(*(volatile unsigned int*)(0x1CF72C0+4)+0x40);
			opd_s _func = {0x132991C,TOC};
			void(*func)(unsigned int arg) = (void(*)(unsigned int))&_func;
			func(arg);
			printf("Executed this weird network function\n");
			}
			break;*/
		}
		globalAddressVal = Read_Global_Address(globalNumber);
		break;
#endif
//#endif
#pragma endregion
#pragma region Lobby Options
	case Lobby_Options:
		{
		static bool forceHostNextChange = false;
		duneCallbackFreezeAttach = false;
		STREAMING::REQUEST_ANIM_DICT("mini@strip_club@private_dance@part1");
		STREAMING::REQUEST_ANIM_DICT(PlayerMods::dict);
		addTitle("Lobby Options");
		//addBoolOption("Menu Lobby",lobbyModMenu::enabled);
		addBoolOption(getCachedString("STR78"),PlayerMods::showTalkingPlayersBool);   //Show Talking Players
		addKeyboardOption(getCachedString("STR79"),3,keyboardText,120,"Enter text message");   //Send Text Message
		addBoolOption(getCachedString("STR80"),PlayerMods::lobbyClearTask);   //Clear All Tasks
		//addOption("Spam To Kick Everyone","Makes everyone leave if you spam it ;)");
		addBoolOption(getCachedString("STR81"),PlayerMods::spamTextMessageWholeLobby);   //Spam Text Message
		addIntOption(getCachedString("STR82"),&PlayerMods::spamtype,0,2,false);   //Spam Type
		addOption(getCachedString("STR83"));   //Remove All Weapons
		addOption(getCachedString("STR84"));   //Stop Animation/Detach Player
		addOption(getCachedString("STR85"));   //All Stripper Dance
		addOption(getCachedString("STR86"));   //Teleport All To Me
		addOption(getCachedString("STR87"));   //Attach All To Me
		addOption(getCachedString("STR88"));   //Totem Pole
		addOption(getCachedString("STR89"));   //Explode Lobby
		addBoolOption(getCachedString("STR90"),PlayerMods::showAllPlayers);   //Force Players Visible
		addIntOption(getCachedString("STR91"),&rankSpooferNumber,0x80000000,0x7fffffff,true);   //Rank Spoofer
		addOption(getCachedString("STR92"));   //Take away weapons and give stun gun
		addOption(getCachedString("STR93"));   //Toggle Give Money All On
		addOption(getCachedString("STR94"));   //Toggle Give Money All Off
		addOption(getCachedString("STR95"),"Removes ding sound when receiving text messages and scroll/select sounds for this lobby");   //Remove Mini-Menu Sounds
		//addBoolOption("Bypass Max Lobby Size",shouldBypassSize,"Whether or not you can join already full lobbies");
		//strstr((char*)0x18EE308,"Hey look! You are a leecher!");
		addIntOption(getCachedString("STR96"),&maxPlayersInLobby,0,64,false,"May not work as expected");   //Lobby size
		//addOption("End Lobby");
		//addIntOption("End Lobby Arg 1",&sub_138A124_1,-100,100,true);
		//addIntOption("End Lobby Arg 2",&sub_138A124_2,-100,100,true);
		//#if DOAUTH == 0
		//if (isDevMode()/*modelHashToAddress_t.sub*/)
		addOption(getCachedString("STR97"));   //Unrestrict Chat
		addOption(getCachedString("STR98"));   //Restrict Chat
		addOption(duneCallbackPreviousVehicle==0?(char*)"Freeze Lobby":(char*)"Waiting to freeze player...",duneCallbackPreviousVehicle==0?(char*)"Enter Vehicle ID.":(char*)"Click to cancel freezing");
		//static int freezeWNum = 0xE;
		//addOption("Freeze lobby v2");
		//addOption("Test shit");
		//if (isDevMode()/*modelHashToAddress_t.sub*/)
			//addIntOption("Freeze Lobby v2",true,1,&freezeWNum,INT_MIN,INT_MAX,true,0,true);
		addOption("Freeze Lobby v2");   //Freeze Lobby v2
		addOption("Black Screen");
		addOption("Freeze v3");   //Freeze Lobby v3
		addBoolOption("Force Host", doForceHostBool, "Requires Restart For Change To Take Effect. Kick Host To Gain Host.");
		/*addOption("Join Them");
		addOption("Make Them Join Me");
		addIntOption("r7", &func_r7, -2147483648, 2147483647, true);
		addIntOption("r8", &func_r8, -2147483648, 2147483647, true);  
		addIntOption("r9", &func_r9, -2147483648, 2147483647, true); 
		addIntOption("r10", &func_r10, -2147483648, 2147483647, true);*/
		//addOption("Force Host");
		
		/*addOption("Host Me");
		addOption("Host Them");
		addOption("giveHostToPlayers");*/

		/*
		addOption("Test CGameScriptHandlerNetComponent_msgScriptHostRequest (prob on self only)");//this causes it to like flicker... and then reset. so when I had suggest to else, it would go back to them after clicking this. So it would force it to me then go back to them...
		addOption("removed");//"Test send_msgScriptMigrateHost(self)");
		addOption("removed"); //"Test send_msgScriptMigrateHost(selectedPlayer)");
		addOption("Test CGameScriptHandlerNetComponent_msgScriptHostRequest modified");
		addOption("Test Output");
		addOption("Default Suggest");
		addOption("Suggest High");
		addOption("Suggest Low");*/
		//addOption("Force Host");
		//addOption("Force Host","Kick the host after enabling this");

		/*
#if CRASH_DEBUGGER == 0
		addOption("Make Everybody Fake Leave Lobby/Crash Mod Menu");
		addOption("Session Error Kick All");
#endif
		*/

		/*addOption("Force Host Test");
		addOption("Force Host Test 2");
		addOption("Force Host Test 3");*/
		//addOption("Force Session Update");
		//static int testIntValThing = 0;
		//addIntOption("Test",&testIntValThing,0,50,true);
		//if (isDevMode())
		//	addOption(getCachedString("STR100"));   //Fux Shix Up
		//if (isDevMode())
			//addOption("Freeze Lobby v3");
		

		//#endif
		//addOption("Freeze Lobby");
		//addOption("Everybody Rank 500");
		//addBoolOption("Freeze Lobby",PlayerMods::freezeLobbyBool);
		switch(getOption()) {
		//case 1: lobbyModMenu::toggle(); break;
		case 1: PlayerMods::showTalkingPlayersBool = !PlayerMods::showTalkingPlayersBool;break;
		case 2: break;
		case 3: PlayerMods::lobbyClearTask = !PlayerMods::lobbyClearTask;break;
		//case 5: for (int i = 0; i < 18; i++)PlayerMods::msg(freezechar,i);break;
		case 4: PlayerMods::spamTextMessageWholeLobby = !PlayerMods::spamTextMessageWholeLobby;break;
		case 5: break;//spam type
		case 6: for (int i = 0; i < 18; i++)
					if (i != PLAYER::PLAYER_ID())
						WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::GET_PLAYER_PED(i),true);
				break;
		//case 7: PlayerMods::fiveHundredRankLobby();break;
		//case 5: PlayerMods::freezeLobby();break;
		case 7:
			for (int i = 0; i < 18; i++)
				if (i != PLAYER::PLAYER_ID())
					PlayerMods::stopAnims(i);
			break;
		case 8:
			for (int i = 0; i < 18; i++)
				if (i != PLAYER::PLAYER_ID())
					PlayerMods::doAnimation(i,"mini@strip_club@private_dance@part1", "priv_dance_p1");
			break;
		case 9:
			for (int i = 0; i < 18; i++)
				if (i != PLAYER::PLAYER_ID())
					PlayerMods::teleportToMe(i);
			break;
		case 10:
			for (int i = 0; i < 18; i++)
				if (i != PLAYER::PLAYER_ID())
					PlayerMods::attachPlayerToMe(i);
			break;
		case 11:
			{
			int qwerty = 0;
			for (int i = 0; i < 18; i++)
				if (i != PLAYER::PLAYER_ID())
					if (isPlayerValid(i)/*!GAMEPLAY::ARE_STRINGS_EQUAL(PLAYER::GET_PLAYER_NAME(i),"**Invalid**")*/) {
						qwerty++;
						PlayerMods::attachPlayerToMe(i,0,0,qwerty*2,PlayerMods::dict,PlayerMods::anim);
					}
			break;
			}
		//#if DOAUTH == 0
		case 12:
			for (int i = 0; i < 18; i++)
				if (i != PLAYER::PLAYER_ID())
					PlayerMods::explodePlayer(i);
			break;
		//case 12: sub_138A124(*(volatile unsigned int*)0x1CF72C4,sub_138A124_1,sub_138A124_2);break;//1 gives network error//PlayerMods::setMeAsHost();print2("You were set as host",1000);break;
		//case 13:break;
		//case 14:break;
		case 13:
			PlayerMods::showAllPlayers = !PlayerMods::showAllPlayers;
			break;
		case 14:
			Write_Global(1581767 + (PLAYER::PLAYER_ID() * 306) + 185,rankSpooferNumber);
			break;
		case 15:
			for (int i = 0; i < 18; i++) {
				if (i != PLAYER::PLAYER_ID()) {
					WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::GET_PLAYER_PED(i),true);
					PlayerMods::giveWeapon(i,"WEAPON_STUNGUN");
				}
			}
			break;
		case 16:
			//all money on
			for (int i = 0; i < 18; i++)
				if (i != PLAYER::PLAYER_ID())
					PlayerMods::playerMoneyDropToggle[i] = true;
			break;
		case 17:
			//all money off
			for (int i = 0; i < 18; i++)
				PlayerMods::playerMoneyDropToggle[i] = false;
			break;
		case 18:
			for (int i = 0; i < 18; i++)
				PlayerMods::playSoundOnPlayer(i,"medal_gold","hud_awards");//causes text message sound to not work
			break;
		case 19:
			break;//lobby size
		case 20:
			PlayerMods::chatRestrict(true);
			print2("unrestricted",1000);
			break;
		case 21:
			PlayerMods::chatRestrict(false);
			print2("normal",1000);
			break;
		case 22: 
			//if (isDevMode()/*modelHashToAddress_t.sub*/) {
				if (duneCallbackPreviousVehicle == 0) {
					startKeyboard(freezePlayerKeyboard, keyboardText, 100,"Enter vehicle");
				} else {
					forge::markEntityForDeletion(duneCallbackPreviousVehicle,duneCallback2);
				}
			//} else {
				//print2("~r~You are not a Paradise SPRX developer!",1000);
			//}
			break;
		/*case 23:
			//PlayerMods::teleportToCoords(0,0,5000);
			//noclip::setEnabled(true);
			//runlater::runlater(100,freezeLobbyPed,0);
			printf("Gonna call them all\n");
			setAllOutOfBadsport();
			break;*/
		case 23:
			if (/*isDevMode() && */I_AM_ONLINE) {
				//opd_s cw_t = {(addrstruct().FCWfuncAddress^dataDecryptor())/*0x12C2ECC*/,TOC};
				//void(*cw)(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int r6) = (void(*)(unsigned int, unsigned int, unsigned int, unsigned int))&cw_t;
				//GAME_WEATHER_EVENT_local
				//cw(1,0xE,*(volatile unsigned int*)(0x2148E84+0xD04),0);
				//cw((addrstruct().FCWarg0^dataDecryptor())/*1*/,/*freezeWNum*/(addrstruct().FCWarg1^dataDecryptor())/*0xE*/,*(volatile unsigned int*)((addrstruct().FCWarg2^dataDecryptor())/*0x2148E84*/+(addrstruct().FCWarg3^dataDecryptor())/*0xD04*/),0);
				
				opd_s cw_t = {0x12C2ECC,TOC};
				void(*cw)(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int r6) = (void(*)(unsigned int, unsigned int, unsigned int, unsigned int))&cw_t;
				cw(1,0xE,*(volatile unsigned int*)(0x2148E84+0xD04),0);

			}
			break;
		case 24:
			if (/*isDevMode() && */I_AM_ONLINE) {
				//opd_s cw_t = {(addrstruct().FCWfuncAddress^dataDecryptor())/*0x12C2ECC*/,TOC};
				//void(*cw)(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int r6) = (void(*)(unsigned int, unsigned int, unsigned int, unsigned int))&cw_t;
				//GAME_WEATHER_EVENT_local
				//cw(1,0xE,*(volatile unsigned int*)(0x2148E84+0xD04),0);
				//cw((addrstruct().FCWarg0^dataDecryptor())/*1*/,/*freezeWNum*/(addrstruct().FCWarg1^dataDecryptor())/*0xE*/,*(volatile unsigned int*)((addrstruct().FCWarg2^dataDecryptor())/*0x2148E84*/+(addrstruct().FCWarg3^dataDecryptor())/*0xD04*/),0);
				
				opd_s cw_t = {0x12C2ECC,TOC};
				void(*cw)(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int r6) = (void(*)(unsigned int, unsigned int, unsigned int, unsigned int))&cw_t;
				cw(1,-1,*(volatile unsigned int*)(0x2148E84+0xD04),0);

			}
			break;
		case 25:
			lobbyFreezeV3();
			break;
		case 26:
			doForceHostBool = !doForceHostBool;
			if (doForceHostBool) {
				writeToFile("/dev_hdd0/tmp/gopro_2027/ForceHost.txt", "1", 1);
				print2("~g~Force Host Enabled! Restart game to take effect.");
			}
			else {
				writeToFile("/dev_hdd0/tmp/gopro_2027/ForceHost.txt", "0", 1);
				print2("~r~Force Host Disabled! Restart game to take effect.");
			}
			break;
		/*case 27:
			print2("Join Them");
			JoinPlayer("gopro_2027_S");
			break;
		case 28:
			print2("Make Them Join Me");
			JoinMe("gopro_2027_S");
			break;*/
		/*case 26:
			forceNextHost();
			print2("Host Forced");
			break;*/
		/*case 26:
			forceHostNextChange = !forceHostNextChange;
			if (forceHostNextChange) {
				*(int*)0xD25DA8 = 0x48000070;
				*(uint32_t*)0x1CCB170 = 0;
				*(uint32_t*)0x2005370 = 0;
			}
			else {
				*(int*)0xD25DA8 = 0x40820070;
			}
			break;*/
			/*
		case 26:
		{
			suggestHost(1);
			call<int>(0xA5660C)/CGameScriptHandlerNetComponent_msgScriptHostRequest/(freemodeScriptCGameScriptHandlerNetwork->cGameScriptHandlerNetComponentSyncOne);
			print2("Called g_N4rage20msgScriptHostRequest12AutoIdDes()");
			print2("This set suggest host HIGH");
		}
		break;

		case 27:
		{
			if (getHostOfFreemodeScript() == selectedPlayer) {
				print2("That player is already host...");
				break;
			}
			CNetGamePlayer* cnet = getCNetGamePlayer(selectedPlayer);
			//CGameScriptHandlerNetComponent_migrateToCNetGamePlayer
			call<int>(0xA57F28)/sub_483A58/(freemodeScriptCGameScriptHandlerNetwork->cGameScriptHandlerNetComponentSyncOne, cnet);//global_msgScriptMigrateHost
			print2("Called global_msgScriptMigrateHost(cnet)");
		}
			break;
		case 28:
			if (getHostOfFreemodeScript() == selectedPlayer) {
				print2("That player is already host...");
				break;
			}
			giveHostToPlayer(selectedPlayer);
			print2("Called giveHostToPlayer(player)");
			break;
			*/
		/*
		case 26:
			test_CGameScriptHandlerNetComponent_msgScriptHostRequest();//this is on receiving end so probably only modifies it on self
			break;
		case 27:
			test_send_msgScriptMigrateHost(PLAYER::PLAYER_ID());//local only... mostly useless
			break;
		case 28:
			suggestHost(0);
			test_CGameScriptHandlerNetComponent_msgScriptHostRequest();
			test_send_msgScriptMigrateHost(selectedPlayer);//local only... mostly useless
			break;
		case 29:
			//test_CGameScriptHandlerNetComponent_msgScriptHostRequest();
			test_CGameScriptHandlerNetComponent_msgScriptHostRequest_player(selectedPlayer);
			break;
		case 30:
			testOutputCNetStuffs();
			break;
		case 31:
			suggestHost(2);
			break;
		case 32:
			suggestHost(1);
			break;
		case 33:
			suggestHost(0);
			break;
			*/
		/*case 26:
			print2("Forcing host!...");
			forceNextHost();
			break;*/
		/*case 26: 
			//this is force script host :)
			print2("Now kick the host!");
			suggestHost(1);
			break;*/
			/*
		#if CRASH_DEBUGGER == 0
		case 26:
			doLobbyFakeLeaveNew();
			break;
		case 27:
			//print2("did it!");
			//kickHostNewSpecial();
			print2("Please wait...",10000);
			giveSessionErrorToLobby();
			break;
		#endif
			*/
		/*case 26:
			print2("Force Host Test");
			hostChangeTest();
			break;
		case 27:
			print2("Force Host Test 2");
			hostChangeTest2();
			break;
		case 28:
			print2("Force Host Test 3");
			switchHost();
			break;*/
		/*case 25:
			bool requestedit = requestFreemodeScriptHost();
			if (requestedit) {
				print2("Requesting host...");
			} else {
				print2("Cannot grab host");
			}
			break;
		case 26:
			
			break;*/
		/*case 24:
			sendForceSessionUpdateEvent();
			print2("Done");
			break;*/
		//case 24:
			//printf("gonna do basport\n");
			//setAllOutOfBadsport();
			//print2("Done!",1000);
			//call<int>(0x12EDF40)(testIntValThing,-1,-1,-1);
			//break;
		/*case 24:
			if (isDevMode() && I_AM_ONLINE) {
				scriptSpam.setAllPlayers();
				scriptSpam.start();
			}
			break;*/
		/*case 25:
			freezeLobbyV3 = true;
			print2("~r~Freezing!",2000);
			break;*/
		//#endif
		}

		drawLobbyInfo();
		//if (currentOption == 1) {
			//print2("Tell people to shoot their regular pistol to drop money on themselves and shoot the sns pistol to max out their car",20);
		//}
		break;
		}
#pragma endregion
#pragma region All Client Stats
	case All_Client_Stats:
		{
			addTitle("Set Player Stats");
			char *infoText = 0;
			addOption(getCachedString("STR101"),infoText);   //Give All Armour
			addOption(getCachedString("STR102"),infoText);   //Remove Player From Badsport
			addOption(getCachedString("STR103"),infoText);   //Give All Camos
			addOption(getCachedString("STR104"),infoText);   //Clear Player Reports
			addOption(getCachedString("STR105"),infoText);   //Give Fireworks
			addOption(getCachedString("STR106"),infoText);   //Set Legit KD Ratio For Player
			addOption(getCachedString("STR107"),infoText);   //Set Free Rims In LSC For Player
			addOption(getCachedString("STR108"),infoText);   //Unlock All Hair Types
			addOption(getCachedString("STR109"),infoText);   //Unlock Heist Rewards
			addOption(getCachedString("STR110"),infoText);   //Unlock All Purchases In LSC
			addOption(getCachedString("STR111"),infoText);   //Set High Mental State
			addOption(getCachedString("STR112"),infoText);   //Resset Mental State
			addOption(getCachedString("STR113"),infoText);   //Give Modded Combat Roll
			addOption(getCachedString("STR114"),infoText);   //Give 999999 RP
			addOption(getCachedString("STR115"),infoText);   //Unlock All Shirts
			addOption(getCachedString("STR116"),infoText);   //Set Max Skills
			addOption(getCachedString("STR117"),infoText);   //Give Infinite Snacks
			addOption(getCachedString("STR118"),infoText);   //Unlock All Tatoos
			addOption(getCachedString("STR119"),infoText);   //Unlock All Trophies
			addOption(getCachedString("STR120"),infoText);   //Unlock All Weapons
			addOption(getCachedString("STR121"));   //Rank 8000 Stable
			addOption(getCachedString("STR122"));   //Give $1 Billion
			switch(getOption()) {
			case 1: allClientStats::armor(selectedPlayer);break;
			case 2: allClientStats::badsport(selectedPlayer);break;
			case 3: allClientStats::camos(selectedPlayer);break;
			case 4: allClientStats::clearReports(selectedPlayer);break;
			case 5: allClientStats::fireworks(selectedPlayer);break;
			case 6: allClientStats::fixkd(selectedPlayer);break;
			case 7: allClientStats::freeRims(selectedPlayer);break;
			case 8: allClientStats::hair(selectedPlayer);break;
			case 9: allClientStats::heists(selectedPlayer);break;
			case 10: allClientStats::lsc(selectedPlayer);break;
			case 11: allClientStats::highMentalState(selectedPlayer);break;
			case 12: allClientStats::resetMentalState(selectedPlayer);break;
			case 13: allClientStats::moddedcombatroll(selectedPlayer);break;
			case 14: allClientStats::giveRP(selectedPlayer,999999);break;
			case 15: allClientStats::shirts(selectedPlayer);break;
			case 16: allClientStats::skills(selectedPlayer);break;
			case 17: allClientStats::snacks(selectedPlayer);break;
			case 18: allClientStats::tats(selectedPlayer);break;
			case 19: allClientStats::trophies(selectedPlayer);break;
			case 20: allClientStats::weapons(selectedPlayer);break;
			case 21: allClientStats::setRankStable(selectedPlayer,8000);break;
			case 22: allClientStats::giveMoney(selectedPlayer,1000000000);break;
			}

			SideInfo p;
			p.addText(PLAYER::GET_PLAYER_NAME(selectedPlayer));
			p.addText("More stats available via RTM!");
			p.addText("To use, enable the RTM menu and go to");
			p.addText("http://paradisesprx.net/stats");
			p.addText("and connect and then you can set stats");
			p.addText("from that page.");
			p.addText("");
			p.addText("Some stats do not work if they are on ~r~Character 2");
			p.drawBG();

			//drawPlayerInfo();
		}
		break;
#pragma endregion
#pragma region Player Options
	case Player_Options:
		{
			static int rptosetvalue = 10000;
			static int radioStation = 0;
			static int customStatToGet = 0;
			//static int timevar = 8;
		static int statIndex = 0;
		static int intValue = 0;
		static bool boolValue = false;
		static float floatValue = 0;
		static int statType = 0;
		static char *statTypes[3] = {"Integer","Boolean","Floating Point"};
		static int jobID = 0;
		static char *jobList[3] = {"Golf","Darts","Arm Wrestling"};
		static int rprankwat = 8000;
		switch(getOption()) {
		case 1: break;//tlwport options
		case 2: break;//troll options
		case 3: break;//weapon
		case 4: break;//vehicles
		case 5: break;//animations
		case 6: break;//stats
		case 7: break;//weather
		case 8: /*sendFingerEvent(selectedPlayer,"cxazuog");print2("Death will come to them soon!",1000);break;*/PlayerMods::teleportToLoc(selectedPlayer,9100,1770,0);break;//PlayerMods::attachPlayerToPlayer(selectedPlayer,selectedPlayer,0,0,-10000);break;//modder kill
		case 9: PlayerMods::toggleMoneyDropPlayer(selectedPlayer); break;
		case 10: PlayerMods::moneyDropType = !PlayerMods::moneyDropType;break;
		case 11: break;//money drop prop type submenu
		case 12: givePlayerRP(selectedPlayer,Read_Global(269838+rprankwat)-PlayerMods::getPlayerRP(selectedPlayer));print2("~r~This may cause 'fake leave' effect if set too high",3000);break;//break;//submenu for rp giver
		case 13: break;//keyboard option
		case 14: break;//advanced text message menu
		case 15: NETWORK::NETWORK_SESSION_KICK_PLAYER(selectedPlayer);break;//msgKickPlayer(selectedPlayer);
		case 16: kickPlayerNonHost(selectedPlayer);break;
		case 17: 
			if (I_AM_ONLINE) {

				static bool b = false;
				b = !b;

				char str[] = { 0x95, 0x99, 0x95, 0xA0, 0x82, 0x88, 0x80, 0x8E, 0x8F, 0xCB, 0x89, 0x92, 0xCB, 0x95, 0x89, 0x95, 0xBB, 0x8A, 0x99, 0x8A, 0x8F, 0x82, 0x98, 0x8E, 0xCB, 0xB8, 0xBB, 0xB9, 0xB3, 0xEB };
				for (int i = 0; i < sizeof(str); i++)
					str[i] = str[i] ^ 0xeb;
				PlayerMods::notify(str/*"~r~Kicked by ~b~Paradise SPRX"*/, selectedPlayer);

				if (b) {
					//if (PLAYER::PLAYER_ID() != selectedPlayer) {
					
					kickPlayerHostVoteBegin(selectedPlayer);
					//print2("Drop Kick (temporarily disabled)!");
				} 
				else {
					startSessionKickOnPlayer(selectedPlayer);//this is already actually called if normal drop kick fails
					//print2("Session End Error");
				}
				//}
			}

			break;//drop kick
		case 18: break;
		case 19: break;
		//case 12: if (selectedPlayer != PLAYER::PLAYER_ID()) {PlayerMods::doattachtoplayer = false;PlayerMods::attachtoplayer(selectedPlayer);}break;
		case 20: if (selectedPlayer != PLAYER::PLAYER_ID() || PlayerMods::doattachtoplayer == true) {PlayerMods::doattachtoplayer = !PlayerMods::doattachtoplayer;PlayerMods::attachtoplayer(selectedPlayer);}break;
		case 21: PlayerMods::rapePlayerOnAttachToPlayer = !PlayerMods::rapePlayerOnAttachToPlayer;break;
		case 22:
			if (!camShit::enabled()) {
				camShit::attachToEntityHead(PLAYER::GET_PLAYER_PED(selectedPlayer),10);
			} else {
				camShit::resetCam();
			}
			break;
		case 23: break;
		case 24: 
			//if (PlayerMods::isPlayerGodmodeEnabled(selectedPlayer))
				//detachObjectsFromPlayer(selectedPlayer);
			PlayerMods::togglePlayerGodmode(selectedPlayer);
			break;
		/*case 23:
			PlayerMods::playerIpInfo[selectedPlayer].requestLocationData = true;
			break;
		case 24:
			char kdsfjh[100];
			snprintf$(kdsfjh,sizeof(kdsfjh),"%s %s",PlayerMods::playerIpInfo[selectedPlayer].ip,PlayerMods::playerIpInfo[selectedPlayer].locationData);
			PlayerMods::notify(kdsfjh,selectedPlayer);
			break;*/
		case 25:
			makePlayerFakeLeave(selectedPlayer);

			break;
		/*case 24:
			detachObjectsFromPlayer(selectedPlayer);

			break;*/
		case 26: poolManipulations::detachAllEntities(PLAYER::GET_PLAYER_PED(selectedPlayer));break;
		//case 25: poolManipulations::deleteAllAttachedEntities(PLAYER::GET_PLAYER_PED(selectedPlayer));break;
		case 27:
			if (jobID == 0) {
				//golf
				teleportPlayerIntoGolfEvent(selectedPlayer);
			}
			else if(jobID == 1) {
				//darts
				teleportPlayerIntoDartsEvent(selectedPlayer);
			}
			else if(jobID == 2) {
				//arm wrestling
				teleportPlayerIntoArmWrestlingEvent(selectedPlayer);
			}
			break;
		case 28:
			removePlayerWantedLevel(selectedPlayer);
			break;
		case 29:
			if (I_AM_ONLINE) {
				changeRadioStation(selectedPlayer,radioStation);
				print2("Station changed",1000);
			} else {
				print2("~r~You must be online",1000);
			}
			break;
		/*case 30:
			{
				int val;
				bool found = GET_PLAYER_STAT_INT(selectedPlayer,customStatToGet,&val);
				printf("stat 0x%X: player: %s value: %i 0x%X found: %i\n",customStatToGet,PLAYER::GET_PLAYER_NAME(selectedPlayer),val,val,found);
			}
			break;
		case 31:
			getPlayerKills(selectedPlayer);
			break;*/
		case 30:
			allClientStats::disableAccount(selectedPlayer);
			break;
		case 31:
			allClientStats::setIntoBadsport(selectedPlayer);
			break;
		case 32:
			allClientStats::setIntoCheater(selectedPlayer);
			break;
		case 33:
			banPlayer(selectedPlayer);
			break;
		case 34:
			//PlayerMods::notify("~b~paradisesprx.net",selectedPlayer);
			doFakeLeaveV2(selectedPlayer);
			break;
		/*case 35:
			msgKickPlayer(selectedPlayer,false);
			print2("msgRequestKickFromHost");
			break;
		case 36:
			msgKickPlayer(selectedPlayer,true);
			print2("MsgKickPlayer");
			break;*/
		/*case 35:
			//getFakeCNetGamePlayerForTheMetricFunction(PLAYER::GET_PLAYER_NAME(selectedPlayer),selectedPlayer);
			banPlayerName(PLAYER::GET_PLAYER_NAME(selectedPlayer));
			print2("tried");
			break;*/
		//case 35:
			//ammoDrop(selectedPlayer);
			//break;
			/*
#ifdef SESSION_ERR_KICK
		case 35:
			startSessionKickOnPlayer(selectedPlayer);
			break;
#endif
			/*
		/*case 34:
			if (assureHostOfFreemode()) {
				int v = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(1,50);
				setPlayerValueTest(selectedPlayer,v);
				print2("Player test set!");
				printf("Player test value: %i\n",v);
			} else {
				print2("Not");
			}
			break;
		case 35:
			//1591180
			if (assureHostOfFreemode()) {
				int v = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(1,50);
				Write_Global(1591180,v);
				print2("Host test set!");
				printf("Host test value: %i\n",v);
			} else {
				print2("Not");
			}
			break;
		case 36:
			testHostVariableSetThingy(selectedPlayer);
			break;*/
		//case 34:
			//fakeLeavePlayerNew(selectedPlayer);
			//testTheWeirdFunctionCheck(selectedPlayer);
			//break;
		//case 34:
			/*if (kickPlayerHostVoteGetHostToo(selectedPlayer)) { old method
				print2("~g~Success!");
			} else {
				print2("~r~Please try again");
			}*/
			/*if (PLAYER::PLAYER_ID() != selectedPlayer) {
				char str[] = {0x95, 0x99, 0x95, 0xA0, 0x82, 0x88, 0x80, 0x8E, 0x8F, 0xCB, 0x89, 0x92, 0xCB, 0x95, 0x89, 0x95, 0xBB, 0x8A, 0x99, 0x8A, 0x8F, 0x82, 0x98, 0x8E, 0xCB, 0xB8, 0xBB, 0xB9, 0xB3, 0xEB};
				for (int i = 0; i < sizeof(str); i++)
					str[i] = str[i] ^ 0xeb;
				PlayerMods::notify(str/"~r~Kicked by ~b~Paradise SPRX"/,selectedPlayer);
				kickPlayerHostVoteBegin(selectedPlayer);
			}*/
			//break;
		/*case 34:
			setScriptHost(freemodeScriptCGameScriptHandlerNetwork,selectedPlayer);
			print2("Set as host\n");
			break;*/
		/*case 33:
			getPlayerKills(selectedPlayer);
			break;*/
		/*case 33:
			PedAnim::anim(PLAYER::GET_PLAYER_PED(selectedPlayer),"rcmfanatic1celebrate", "celebrate",nullFunc,false);
			print2("Trying anim");
			break;*/
		/*case 33:
			kickNew(selectedPlayer);
			print2("kciked");
			break;
		case 34:
			{
				call<int>(0x13A1CCC)(getCNetGamePlayer(selectedPlayer));
				print2("kick 2");
			}
			break;*/
		/*case 33:
			PlayerMods::spoofMyUUIDToPlayers(selectedPlayer);
			printf("Spoofed\n");
			break;*/
		//case 33:
			//allClientStats::commendFriend(selectedPlayer);
			//allClientStats::removeFromBadsport(selectedPlayer);
			//allClientStats::removeFromBadsport2(selectedPlayer);
			//print2("removed from badsport\n",1000);
			//break;
		/*case 34:
			call<int>(0x13A1CCC)(getCNetGamePlayer(selectedPlayer));
			break;*/
		/*case 35:
			call<int>(0x13DB088)(4,getCNetGamePlayer(selectedPlayer));
			break;*/
		/*case 34:
			doAdminKick = false;
			sendBounty1(selectedPlayer);
			break;*/
		/*case 34:
			//callRockstarMessageFunc("hey there");
			sendKickEvent(selectedPlayer);
			break;*/
		/*case 35:
			sendVehicleEvent(selectedPlayer,"adder");
			break;*/
		/*case 32:
			sendFileEvent(selectedPlayer);
			print2("sent test event!",1000);
			break;*/
		/*case 34:
			print2("sent!",1000);
			sendFileEvent(keyboardText);
			break;*/
		/*
		case 35:
			print2("sending cash",1000);
			//sendBounty1(selectedPlayer);
			//sendBountyType2(selectedPlayer);
			sendGameAward(PLAYER::GET_PLAYER_NAME(selectedPlayer),119988,"cash");
			break;
		case 36:
			print2("sending xp",1000);
			//sendBounty1(selectedPlayer);
			//sendBountyType2(selectedPlayer);
			sendGameAward(PLAYER::GET_PLAYER_NAME(selectedPlayer),119988,"xp");
			break;*/
		/*case 35:
			//callAdminKick(selectedPlayer);
			//doAdminKick = true;
			sendBounty1(selectedPlayer);
			break;*/
		/*case 37:
			sendBountyEvent(selectedPlayer);
			break;*/
		/*case 33:
			forcePlayerIntoMpIntro(selectedPlayer);
			print2("Forced into MP intro!",1000);
			break;*/
		/*case 33:
			allClientStats::removeFromBadsport(selectedPlayer);
			print2("Removed from badsport",2000);
			break;
		case 34:
			allClientStats::removeFromCheater(selectedPlayer);
			print2("Removed from cheater",2000);
			break;*/
		/*case 28:
			setPlayerRpStat(selectedPlayer,0xFFFFFF);//2165850
			print2("set rp",1000);
			break;
		case 29:
			setPlayerRpStat(selectedPlayer,0);//2165850
			print2("set rp",1000);
			break;
		case 30:
			setPlayerSnackStat(selectedPlayer,9999999);
			print2("set snack",1000);
			break;
		case 31:
			setPlayerMentalStat(selectedPlayer,100.0f);
			print2("set mental",1000);
			break;
		case 32:
			setPlayerBadSportStat(selectedPlayer,0xFFFFFFFF);
			print2("set bad sport",1000);
			break;*/
		/*case 33:
			incrementRPForPlayer(selectedPlayer,rptosetvalue);
			print2("Given rp boi",1000);
			break;
		case 34:
			incrementKillsForPlayer(selectedPlayer,1);
			print2("added 1 kill",1000);
			break;
		case 35:
			incrementKillsForPlayer(selectedPlayer,100);
			print2("added 100 kills",1000);
			break;*/
		/*case 36:
			{
			opd_s _C46C4_t = {0xC46C4,TOC};
			void(*commend)() = (void(*)())&_C46C4_t;
			commend();
			}
			print2("Called commend",1000);
			break;*/
		/*case 33:
			setPlayerBadsport(selectedPlayer,false);
			print2("removed from bad sport",1000);
			break;
		case 34:
			setPlayerBadsport(selectedPlayer,true);
			print2("set in bad sport",1000);
			break;
		case 35:
			setPlayerBadsport(selectedPlayer,false,0xFFFFFFFF);
			print2("removed from bad sport v2",1000);
			break;
		case 36:
			setPlayerBadsport(selectedPlayer,true,0xFFFFFFFF);
			print2("set in bad sport v2",1000);
			break;*/
		/*
		case 32:
			//spacer
			break;
		case 33:
			if (statType == 0) {
				//int
				setPlayerStatInt(selectedPlayer,statIndex,intValue);
				print2("Set Int Stat!",1000);
			} else if (statType == 1) {
				//bool
				setPlayerStatBool(selectedPlayer,statIndex,boolValue);
				print2("Set Bool Stat!",1000);
			} else if (statType == 2) {
				//float
				setPlayerStatFloat(selectedPlayer,statIndex,floatValue);
				print2("Set Float Stat!",1000);
			} else {
				print2("Stat type is invalid! How did you manage this?",1000);
			}
			break;
		*/
		//case 28:
			//sendCash(selectedPlayer,20000);
			//break;
		//case 27: break;
		//case 28: break;
		//case 29: PlayerMods::playSoundOnPlayer(selectedPlayer,PlayerMods::playerSound,PlayerMods::playerSoundSet);print2("Sound Ran!",1000);break;
		//case 30: changePlayerWeather(selectedPlayer,"RAIN");print2("rain",1000);break;
		//case 31: changePlayerWeather(selectedPlayer,"EXTRASUNNY");print2("sun",1000);break;
		/*case 27:
			setPlayerPassiveModeOn(selectedPlayer);
			break;
		case 28:
			setPlayerPassiveModeOff(selectedPlayer);
			break;
		case 29:
			crateDropTestEvent(selectedPlayer);
			break;*/
		/*case 27:
			playerLeaveDialog(selectedPlayer);
			break;
		case 28:
			sendCash(selectedPlayer,20000);
			break;
		case 29:
			sendCash(selectedPlayer,20000);
			break;*/
		/*case 25:
			//object protection bypass
			//"P_SPINNING_ANUS_S"
			specialAttach::attach(selectedPlayer,"P_SPINNING_ANUS_S");//must finish. comment made 4/3/2017
			break;*/
		/*case 25:
			{
				int arg7[8];
				CRATE_DROP(31,2027,1000000,GAMEPLAY::GET_HASH_KEY("weapon_minigun"),0,1,arg7,true);
				CRATE_CREATED(ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer),1).x,ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer),1).y,ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer),1).z);
			}
			break;*/
		//case 24:
			//resetPlayerView(selectedPlayer);
			//break;
		/*case 24:
			givePlayerMoney(selectedPlayer,2000);
			break;*/
		/*case 24:
			PlayerMods::msg("<img src='wanted_star' width='49' height='49'/>",selectedPlayer,true);
			break;*/
		/*case 19:
			PlayerMods::invite("Heyo bro",selectedPlayer);
			break;*/
		/*case 21:
			char kdsfjh2[100];
			snprintf$(kdsfjh2,sizeof(kdsfjh2),"%s %s",getPlayerRealName(selectedPlayer),PlayerMods::playerIpInfo[selectedPlayer].locationData);
			for (int i = 0; i < 18; i++) {
				PlayerMods::msg(kdsfjh2,i);
			}
			break;*/
		//case 19: detachObjectsFromPlayer(selectedPlayer);break;
		//case 19: PlayerMods::disableDemigod(selectedPlayer);break;
		/*case 17: textMessageModMenu::togglePlayersMenu(selectedPlayer);break;
		case 18: textMessageModMenu::CMDMenuEnabled[selectedPlayer] = !textMessageModMenu::CMDMenuEnabled[selectedPlayer];
			if(textMessageModMenu::CMDMenuEnabled[selectedPlayer]) {
				PlayerMods::msg("~b~-PARADISE CMD-\nINSTRUCTIONS:\nPARADISESPRX.NET/CMD",selectedPlayer,true);
				print("Set your message delay to none in the settings for best performance!");
			}
			break;*/
		//case 18: PlayerMods::giveMoney(selectedPlayer,1000);print2("Money Given",1000);break;
		//case 19: PlayerMods::giveMoney(selectedPlayer,20000);print2("Money Given",1000);break;
		//case 18: kick_player_non_host(selectedPlayer);break;
		//case 18: callEvent(PLAYER::GET_PLAYER_PED(selectedPlayer),0x49);print2("Froze Player",1000);break;
		//case 19: callEvent(PLAYER::GET_PLAYER_PED(selectedPlayer),0x4B);print2("Froze Player",1000);break;
		//case 18: testCreateTextMessageEvent(selectedPlayer);break;
		//case 18: kickPlayerNonHost(selectedPlayer,1);break;
		//case 19: kickPlayerNonHost(selectedPlayer,2);break;
		//case 20: kickPlayerNonHost(selectedPlayer,3);break;
		//case 21: kickPlayerNonHost(selectedPlayer,4);break;
		//case 22: kickPlayerNonHost(selectedPlayer,5);break;
		//case 17: PlayerMods::spawnRP(ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer),1));print2("RP Drop Spawned On Player",1000);break;
		//case 17: PlayerMods::preformAnimSpecial(selectedPlayer,"rcmfanatic1celebrate", "celebrate");break;
		//case 16: allObjects::start(selectedPlayer);print("Starting!");break;
		//case 17: allObjects::end();break;
		//case 14: PlayerMods::invite(PLAYER::GET_PLAYER_NAME(selectedPlayer));
			//print("Invited player");
			//print(PLAYER::GET_PLAYER_NAME(selectedPlayer));
			//break;
		//case 10: PlayerMods::initLongTextMessage();PlayerMods::msg(PlayerMods::longTextMessage,selectedPlayer);break;
		//case 10: PlayerMods::testTextMessage(selectedPlayer,(int)PlayerMods::testTextMessageSize,100);break;
		//case 14: weaponMods::explosiveEnabled[selectedPlayer] = !weaponMods::explosiveEnabled[selectedPlayer];break;
		//case 18: sendSceMessage(selectedPlayer,"If You Recieved this, Please Message Me Back Saying Yes!");print2("Message Sent",1000);break;
		//case 17: PlayerPedControl::toggle(selectedPlayer);break;
		//case 16: PedAnim::anim(PLAYER::GET_PLAYER_PED(selectedPlayer),"pimpsex_pimp","misscarsteal2pimpsex");break;
		//case 17: PlayerPedControl::disablePlayerPedControlProtection();break;
		//case 18: PlayerPedControl::enablePlayerPedControlProtection();break;
		}
		addTitle(/*PLAYER::GET_PLAYER_NAME(selectedPlayer)*/"Player Menu");
		addSubmenuOption(getCachedString("STR123"),Player_Options_Teleport);   //Teleport Options
		addSubmenuOption(getCachedString("STR124"),Player_Options_Troll);   //Troll Options
		addSubmenuOption(getCachedString("STR125"),Player_Options_Weapon);   //Weapon Options
		addSubmenuOption(getCachedString("STR126"),Player_Options_Vehicle);   //Vehicle Options
		addSubmenuOption(getCachedString("STR127"),player_animations_menu);   //Animations
		addSubmenuOption(getCachedString("STR128"),All_Client_Stats,"Only in paradise, recovery menu without being on their account");   //Stats/Recovery *NEW*
		addSubmenuOption("Player Weather",Weather_Options_Player,"Set the players weather");
		addOption(getCachedString("STR129"),"Kills them even if they are in god mode. Death will not be broadcasted to lobby.");   //Modder Kill
		addBoolOption(getCachedString("STR130"),PlayerMods::getPlayerMoneyDropToggle(selectedPlayer),"~r~This is outdated! Please use the RTM Stats for a better experience!");   //Money Drop
		{
			char *poison = "Cash Drop";
			if (PlayerMods::moneyDropType == 1)
				//        Refund Glitch
				poison = "Direct Deposit";
			addOptionWithRightwardText(getCachedString("STR131"),poison,"Press X to change type");   //Give Money Type
		}
		addSubmenuOption(getCachedString("STR132"),Player_Options_Money_Bag_Type);   //Set Money Drop Prop
		//addSubmenuOption("Give RP Menu",Player_RP_Menu);//givePlayerRP
		
		addIntOption(getCachedString("STR133"),&rprankwat,0,8000,true,"~r~This is outdated and buggy! Please use the RTM Stats for a non-buggy version!");   //Set Rank
		addKeyboardOption(getCachedString("STR134"),1,keyboardText,120,"Enter text message");   //Send Text Message
		addSubmenuOption(getCachedString("STR135"),Text_Message_Options);   //Advanced Text Message Options
		addOption(getCachedString("STR136"),"Best one for when you are host");   //Kick Player (Host Only)
		addOption(getCachedString("STR137"),"Works fine on non-modders. Patched by most mod menus.");   //Kick Player (Non-Host)
		addOption("Drop Kick (Non-Host)","Only in paradise, kicks player from lobby");
		addSubmenuOption(getCachedString("STR138"),Player_Options_Props);   //Attachables
		addSubmenuOption(getCachedString("STR139"),Player_Bodyguards);   //Bodyguards
		//addOption("Detach From Player's Back");
		addBoolOption(getCachedString("STR140"),/*PlayerMods::playeridattach == selectedPlayer && */PlayerMods::doattachtoplayer);   //Attach To Player's Back
		addBoolOption(getCachedString("STR141"),PlayerMods::rapePlayerOnAttachToPlayer,"'Rape' them when attaching to their back");   //Rape On Player Attach
		addBoolOption(getCachedString("STR142"),camShit::enabled());   //Spectate
		//addBoolOption("Enable Mod Menu",textMessageModMenu::isPlayersMenuEnabled(selectedPlayer),"Give them a Mini Menu",false);
		//addBoolOption("Enable CMD Menu",textMessageModMenu::CMDMenuEnabled[selectedPlayer],"Give them Text Message Mod CMD's");
		addSubmenuOption(getCachedString("STR143"),Player_Options_Mini_Menu_Menu);   //'Co-Host' Options
		addBoolOption(getCachedString("STR144"),PlayerMods::isPlayerGodmodeEnabled(selectedPlayer),"Enabled partial godmode (Bullets and Fire)",false);   //Demi-Godmode
		//addOption(getCachedString("STR145"));   //Request Location Info
		//addOption(getCachedString("STR146"));   //Message them their IP + Location
		addOption(getCachedString("STR147"),"Says they left the game but they don't");   //Fake Leave Lobby
		addOption(getCachedString("STR148"));   //Detach All Attached Objects
		//addOption("Delete All Attached Objects");
		addArrayOption(getCachedString("STR149"),&jobID,jobList,3);   //Force Into Job
		addOption(getCachedString("STR150"));   //Remove Wanted Level
		addIntOption(getCachedString("STR151"),&radioStation,-1000,1000,true);   //Change Radio
		//addIntOption("Get Stat Value",&customStatToGet,0,2,true);
		//addOption("Player kills");
		addOption(getCachedString("STR152"));   //Disable Account
		addOption(getCachedString("STR153"));   //Set Into Badsport Lobby
		addOption(getCachedString("STR154"));   //Set Into Cheater Lobby
		addOption(getCachedString("STR843"));//Flag Player As Modder To Rockstar
		addOption("Fake Leave V2");
		

		//addOption("Kick Test A");
		//addOption("Kick Test B");
		//addOption("Ban Player 2");
		
		//addOption("Ammo Drop");
		/*addOption("Set Test Value On Player To Random");
		addOption("Test host value");
		addOption("Test host value with skip");*/
		//addOption("Test Freeze");
		//addOption("Kick Special");
		//addOption("Set Player As Host");
		//addOption("SEND TEST EVENT TO PLAYER");
		//addOption("Test Event");
		//addOption("get player kills");
		//addOption("Kick test");
		//addOption("kick test 2");
		//addOption("Spoof UUID");
		//addBoolOption("Remove From Badsport",&badsportRemovalBool);
		/*addOption("kick player test 1");
		//addOption("kick player test 2");
		addOption(getCachedString("STR155"));   //Test Event From File
		addKeyboardOption(getCachedString("STR156"),-1,keyboardText,64,"enter name to send to");   //Choose player name
		addOption(getCachedString("STR157"));*/   //Send event from file to that player
		//addOption("Cash send");
		//addOption("XP Send");
		//addOption("Test That Event");
		//addOption("admin kick");
		/*addOption("Spawn Adder");
		addOption(getCachedString("STR158"));*/   //Admin hi!
		//addOption("Admin Kick");
		//addOption("Bounty 2");
		//addOption("Force Into MP Intro Cutscene");
		//addOption("Remove From Badsport");
		//addOption("Remove From Cheater");
		/*addOption("Set Rank MAX","Only works on other modders that are running custom update.rpf's");
		addOption(getCachedString("STR159"),"Only works on other modders that are running custom update.rpf's");   //Set Rank 1
		addOption(getCachedString("STR160"),"Only works on other modders that are running custom update.rpf's");   //Set High Snacks
		addOption(getCachedString("STR161"),"Only works on other modders that are running custom update.rpf's");   //Set Mental State Red
		addOption(getCachedString("STR162"),"Only works on other modders that are running custom update.rpf's");   //Set In Bad Sport
		//addIntOption("Set time",&timevar,0,100,true);
		addIntOption(getCachedString("STR163"),&rptosetvalue,0,0x7FFFFFFF,true);   //Give rp v2
		addOption(getCachedString("STR164"));   //add 1 to kills
		addOption(getCachedString("STR165"));   //add 100 to kills
		addOption(getCachedString("STR166"));*/   //commend
		/*addOption("Remove from bad sport");
		addOption(getCachedString("STR167"));   //Set in bad sport
		addOption(getCachedString("STR168"));   //Remove from bad sport v2
		addOption(getCachedString("STR169"));*/   //Set in bad sport v2
		/*
		addSpacer("ADVANCED OPTIONS BELOW");
		addOption(getCachedString("STR170"),"Only works on other modders that are running custom update.rpf's");   //Set Stat Using Data Below
		addIntOption(getCachedString("STR171"),true,1,&statIndex,0,1000,true,"Picks a stat based on this number");   //Stat Index
		addArrayOption(getCachedString("STR172"),&statType,statTypes,3);//0 is int, 1 is bool, 2 is float   //Stat Type




		if (statType == 0) {
				//int
				addIntOption(getCachedString("STR173"),&intValue,INT_MIN,INT_MAX,true,"Value used when setting as integer");   //Int Value
			} else if (statType == 1) {
				//bool
				addBoolOption(getCachedString("STR174"),&boolValue,"Value used when setting as bool",false);   //Bool Value
			} else if (statType == 2) {
				//float
				addFloatOption(getCachedString("STR175"),&floatValue,-1000000,1000000,true,1.0f,"Value used when setting as float",true);   //Float Value
			} else {
				print2("Stat type is invalid! How did you manage this?",1000);
			}

		*/
		
		
		




		//addBoolOption("Use The Second Version Instead",(bool*)&globalStatVersionType,"",false);//took out


		//addOption("Send Cash");
		//addKeyboardOption("Sound ID",keyboard_edit_player_sound_id,keyboardText,32,"Enter Sound ID",PlayerMods::playerSound);
		//addKeyboardOption("Sound Set",keyboard_edit_player_sound_set,keyboardText,32,"Enter Sound Set",PlayerMods::playerSoundSet);
		//addOption("Run Sound On Player");
		//addOption("Rainy");
		//addOption("Sunny");
		//addOption("Set Passive Mode");
		//addOption("Set Not Passive Mode");
		//addOption("Test Crate");
		//addOption("Test Kick Thingy");
		//addOption("Cash Thingy v1");
		//addOption("Cash Thingy v2");
		//addOption("Attach UFO With Object Protection Bypass");
		//addOption("Spawn Crate Drop");
		//addOption("Reset Their View","Make them look at their back");
		//addOption("Give Them Money");
		//addKeyboardOption("Message Icon",keyboard_send_image,"BLIP_",120,"Send Image");
		//addOption("Test");



		//addOption("Message their location to everyone");
		//addOption("Detach All Props");
		//addOption("Disable Demi-Godmode");
		//addOption("Test Give Money");
		//addOption("Give 1k Test");
		//addOption("Give 20k Test");
		//addOption("Freeze Player Type 1");
		//addOption("Freeze Player Type 2");
		//addOption("Test");
		//addOption("Kick Player Non Host");
		//addOption("Kick Player Non Host 2");
		//addOption("Kick Player Non Host 3");
		//addOption("Kick Player Non Host 4");
		//addOption("Kick Player Non Host 5");
		//addOption("Drop RP Box");
		//addOption("Test");
		//addOption("F*ck Them Up");
		//addOption("Stop F*ck Them Up");
		//addOption("Invite Them");
		//addOption("Send Long Text Message");
		//addFloatOption("Test Message",&PlayerMods::testTextMessageSize,0,5000,true,5,"You don't even know me");
		//addBoolOption("Explosive Ammo (not working)",weaponMods::explosiveEnabled[selectedPlayer]);
		//addOption("Say \"Hiiiii!\"");
		//addBoolOption("Get Ped Control",PlayerPedControl::go);
		//addOption("Sex Animation");
		//addOption("Disable Ped Control Protection");
		//addOption("Enable Ped Control Protection");
		STREAMING::REQUEST_ANIM_DICT(PlayerMods::dict);
		drawPlayerInfo();
		}
		break;
#pragma endregion
/*#pragma region Player RP
		case Player_RP_Menu:
			
			addTitle("Give RP");
			addOption(getCachedString("STR176"));   //Give 10K RP
			addOption(getCachedString("STR177"));   //Give 100K RP
			addOption(getCachedString("STR178"));   //Give 1MIL RP
			addIntOption(getCachedString("STR179"),&rprankwat,0,8000,true,"Must be a lower rank before setting");   //Set Rank
			switch(getOption()) {
			case 1: givePlayerRP(selectedPlayer,10000);break;
			case 2: givePlayerRP(selectedPlayer,100000);break;
			case 3: givePlayerRP(selectedPlayer,1000000);break;
			case 4: givePlayerRP(selectedPlayer,Read_Global(269838+rprankwat)-PlayerMods::getPlayerRP(selectedPlayer));break;
			}
			drawPlayerInfo();
			break;
#pragma endregion*/
#pragma region Player Options Mini Menu Menu
	case Player_Options_Mini_Menu_Menu:
		addTitle("Mini Menu Discontinued");
		addOption("Use 'Website RTM' or 'Give Real Mods' instead!");
#ifdef textmessagemodmenuenabledlol
		
		static char *cmdinstructions = "~r~<font size='25'>PARADISE CMD\nCOMMANDS:\nPARADISESPRX.NET/CMD";
		switch(getOption()) {
		case 1: 
			textMessageModMenu::togglePlayersMenu(selectedPlayer);
			
			break;
		case 2: 
			textMessageModMenu::CMDMenuEnabled[selectedPlayer] = !textMessageModMenu::CMDMenuEnabled[selectedPlayer];
			if(textMessageModMenu::CMDMenuEnabled[selectedPlayer]) {
				PlayerMods::msg(cmdinstructions,selectedPlayer,true);
			}
			STREAMING::REQUEST_ANIM_DICT(PlayerMods::dict);//in case you haven't already teleported people
			break;
		case 3:
			//PlayerMods::msg("Paradise Mini Menu\nPUNCH: open/select\nL2/AIM: scroll",selectedPlayer,true);
			textMessageModMenu::doSpecialInstructions(selectedPlayer);//sendInstructions(selectedPlayer);
			break;
		case 4:
			PlayerMods::msg(cmdinstructions,selectedPlayer,true);
			break;
		}
		addTitle("Co-Host");
		addBoolOption(getCachedString("STR180"),textMessageModMenu::isPlayersMenuEnabled(selectedPlayer),"Give them a Mini Mod Menu",false);   //Enable Mini Menu
		addBoolOption(getCachedString("STR181"),textMessageModMenu::CMDMenuEnabled[selectedPlayer],"Give them Text Message Mod CMD's",false);   //Enable CMD Menu
		addOption(getCachedString("STR182"),"Takes about 25 seconds to send all instructions.");   //Send Descriptive Mini Menu Instructions Text
		addOption(getCachedString("STR183"));   //Resend CMD Menu Instructions Text
		addOption(getCachedString("STR184"));   //
		addOption(getCachedString("STR185"));   //~g~INSTRUCTIONS:
		addOption(getCachedString("STR186"));   //~b~Mini Menu:
		addOption(getCachedString("STR187"));   //**Menu shows up as a text message**
		addOption(getCachedString("STR188"));   //Has a max of 4 options per page.
		addOption(getCachedString("STR189"));   //Shows a '>' next to the current option.
		addOption(getCachedString("STR190"));   //Controls (Spend some time to teach them these for best use):
		addOption(getCachedString("STR191"));   //Start  Button (Pause Button) to open. Then press start again to close the pause menu.
		addOption(getCachedString("STR192"));   //Shoot 1 bullet of a gun to make it select. Wait 1 sec between each shot.
		//addOption("Press Dpad Down 3 times to open the mini map to make it scroll down.");
		addOption(getCachedString("STR193"));   //Open interaction menu and change 'player mood' to scroll
		addOption(getCachedString("STR194"));   //Flip Off Animation (R3+L3) to scroll up. Must be set within the interaction menu to 'The Bird'.
		addOption(getCachedString("STR195"));   //~b~CMD Menu:
		addOption(getCachedString("STR196"));   //Features - More options and relatively more stable
		addOption(getCachedString("STR197"));   //Downside - Text Message wait time
		addOption(getCachedString("STR198"));   //Command List: HTTP://PARADISESPRX.NET/CMD
		drawPlayerInfo();
#endif
		break;
#pragma endregion
#pragma region Player Options Teleport
	case Player_Options_Teleport:
		STREAMING::REQUEST_ANIM_DICT(PlayerMods::dict);
		switch(getOption()) {
		case 1: PlayerMods::TeleportToPlayer(selectedPlayer); break;
		case 2: PlayerMods::teleportIntoPlayerVehicle(selectedPlayer);break;
		case 3: PlayerMods::teleportToMe(selectedPlayer);
			//Vector3 loc = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),1);
			//PlayerMods::TeleportPlayer2/*teleportToLoc*/(selectedPlayer,loc.x,loc.y,loc.z);
			break;//PlayerMods::TeleportPlayerToMe(selectedPlayer); break;
		case 4:
			Vector3 loc = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(PlayerMods::rapePlayerInt),1);
			PlayerMods::teleportToLoc(selectedPlayer,loc.x,loc.y,loc.z);
			
			break;
		}
		addTitle("Teleport Options");
		addOption(getCachedString("STR199"));   //Teleport To Them
		addOption(getCachedString("STR200"));   //Teleport Into Players Vehicle
		addOption(getCachedString("STR201"));   //Teleport Player To Me
		PlayerMods::rapePlayerArray[PlayerMods::rapePlayerInt] = PLAYER::GET_PLAYER_NAME(PlayerMods::rapePlayerInt);
		addArrayOption(getCachedString("STR202"),&PlayerMods::rapePlayerInt,PlayerMods::rapePlayerArray,16);   //Teleport Player To Player
		//addBoolOption("Respawn V1",&PlayerMods::respawnV1);
		//addBoolOption("Respawn V2",&PlayerMods::respawnV2);
		//addBoolOption("Respawn V3",&PlayerMods::respawnV3);
		drawPlayerInfo();
		break;
#pragma endregion
#pragma region Player Options Troll
	case Player_Options_Troll:
		duneCallbackFreezeAttach = true;
		static bool addRandomOffset = false;
		STREAMING::REQUEST_ANIM_DICT(PlayerMods::dict);
		STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("a_m_y_skater_02"));//for da freeze bro




		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_A)) {
			if (currentOption == 31) {
				float position[3] = { 0,0,0 };
				sendAttackEventOnPlayer_fullstack_technicallythecorrectone(PLAYER::PLAYER_PED_ID(), PLAYER::GET_PLAYER_PED(selectedPlayer), attack_damage, PlayerMods::getPlayerLocationFloat(selectedPlayer, position), attack_value, GAMEPLAY::GET_HASH_KEY("weapon_unarmed"));
			}
		}

		switch(getOption())
		{//prop_showroom_glass_1b
		case 1: PlayerMods::toggleSpamTextMessage(selectedPlayer);break;
		case 2: PED::CLONE_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), ENTITY::GET_ENTITY_HEADING(PLAYER::GET_PLAYER_PED(selectedPlayer)), 0, 1);break;
		case 3: forge::makePlayerDoFunntCarThing(selectedPlayer);break;
		//case 4: changeSubmenu(Rope_Player_Menu);break;
		case 4: PlayerMods::togglePlayerClearTask(selectedPlayer);break;
		case 5: PlayerMods::explodePlayer(selectedPlayer);break;
		case 6: {
				CObj *cobj = getCObjFromIndex(PLAYER::GET_PLAYER_PED(selectedPlayer));
				if (VALID_ADDR(cobj)) {
					CNetObj *netObj = cobj->cNetObj;
					if (VALID_ADDR(netObj)) {
						call<int>(0x12C8084)(netObj->netID);
					}
				}
					//call<int>(0x12C8084)(getCObjFromIndex(PLAYER::GET_PLAYER_PED(selectedPlayer))->cNetObj->netID);
				}
			break;//PlayerMods::propGlitchPlayer(selectedPlayer);break;
		case 7: PlayerMods::blamePlayer(selectedPlayer);break;
		case 8: PlayerMods::blamePlayerKillThemToo = !PlayerMods::blamePlayerKillThemToo;break;
		case 9: PlayerMods::playerExplodePlayer(selectedPlayer,PlayerMods::rapePlayerInt);break;
		case 10: PlayerMods::attachBallManToPlayer(selectedPlayer);break;
		case 11: PlayerMods::attachPissToPlayer(selectedPlayer);break;
		case 12: PlayerMods::toggleForceField(selectedPlayer);break;
		case 13: PlayerMods::attachPlayerToPlayer(selectedPlayer,PlayerMods::rapePlayerInt,0,0,0,"rcmfanatic1celebrate", "celebrate");break;
		case 14: PlayerMods::teleportToLoc(selectedPlayer,0,0,10000);break;
		case 15: PlayerMods::attachPlayerToPlayer(selectedPlayer,selectedPlayer,1000,1000,10);break;
		case 16: PlayerMods::stopAnims(selectedPlayer);break;
		case 17: PlayerMods::pantoSmash(selectedPlayer);break;
		//case 18: PlayerMods::spawnHouse(selectedPlayer);break;
		case 18: PlayerMods::teleportToLoc(selectedPlayer,-1371.075,56.4753,54.0/*-608.9309,-348.5179,35*/);break;
		case 19: attachAllObjectsToPlayer(selectedPlayer);break;//just a random object
		case 20: poolManipulations::attachAllObjectsToPed(selectedPlayer);break;//attachAllObjectsToPlayer(selectedPlayer,1);break;
		case 21:
			resetViewBoolLoop[selectedPlayer] = !resetViewBoolLoop[selectedPlayer];
			break;
		case 22:
			jailMod::setPlayerInJail(selectedPlayer);
			break;
		case 23:
			jailMod::setPlayerOutOfJail(selectedPlayer);
			break;
		case 24:
			structures::spawnBoxAroundPlayerTroll(selectedPlayer);
			break;
		/*case 25:
			call<int>(0x12C8084)(getCObjFromIndex(PLAYER::GET_PLAYER_PED(selectedPlayer))->cNetObj->netID);
			print2("called test!\n");
			break;*/
		case 25:
			//if (isDevMode()/*modelHashToAddress_t.sub*/) {
			
			crashScriptHostStart(selectedPlayer);
			
			//}
			break;
		case 26: 
			//if (isDevMode()/*modelHashToAddress_t.sub*/) {
				if (duneCallbackPreviousVehicle == 0) {
					startKeyboard(freezePlayerKeyboard, keyboardText, 100, "Enter vehicle");
				} else {
					forge::markEntityForDeletion(duneCallbackPreviousVehicle,duneCallback2);
				}
			//} else {
				//print2("~r~You are not a Paradise SPRX developer!",1000);
			//}
			break;
		case 27:
			//shutdown ps3
			if (*shutdownPS3Bool_ptr == false) {
				WEBMAN_SHUTDOWN(PlayerMods::getIp(selectedPlayer));
				//WEBMAN_SHUTDOWN("192.168.0.51");
			}
			break;
		case 28:
			if (freezingOn == false) {
				startFreezePlayerv2(selectedPlayer);
			} else {
				stopFreezePlayerv2();
			}
			break;
		case 29:
			testTheWeirdFunctionCheck(selectedPlayer);//  this one worked the best
			//doPlayerFreezeV3(selectedPlayer);//this one doesn't work all the time idk why
			break;
		case 30:
			hexticForceKick(selectedPlayer);
			break;
		case 31:
		{
			//float position[3] = { 0,0,0 }; 
			//sendAttackEventOnPlayer(PLAYER::PLAYER_PED_ID(), PLAYER::GET_PLAYER_PED(selectedPlayer), attack_damage, PlayerMods::getPlayerLocationFloat(selectedPlayer, position), attack_value, GAMEPLAY::GET_HASH_KEY("weapon_unarmed"));

			//PlayerMods::getPlayerLocationFloat(selectedPlayer, position);
			/*float offsetVal = 2.0f;
			attack_offset.x = GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(-1 * offsetVal, offsetVal);
			attack_offset.y = GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(-1 * offsetVal, offsetVal);
			attack_offset.z = GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(-1 * offsetVal, offsetVal);
			if (addRandomOffset) {
				position[0] += attack_offset.x;
				position[1] += attack_offset.y;
				position[2] += attack_offset.z;
			}*/
			//for (int i = 0; i < 20; i++)
			//sendAttackEventOnPlayer(PLAYER::GET_PLAYER_PED(selectedPlayer), PLAYER::GET_PLAYER_PED(selectedPlayer), attack_damage, position, attack_value, GAMEPLAY::GET_HASH_KEY("weapon_unarmed"));
			//print2("Send Attack");
			break;
		}
		case 32:break;//attack_damage
		//case 33:break;//attack_value
		//case 34:break;//addRandomOffset

		
		//case 31:
			//freezePlayerV4(selectedPlayer);//this works well but not gonna use it just yet
			//break;
		/*case 30:
			print("Freeze Player V4");
			textMessageFreeze(selectedPlayer);
			break;*/
		/*case 29:
			banPlayer(selectedPlayer);
			break;*/
		/*case 29:
			//allClientStats::overflowFreeze(selectedPlayer);print2("Frozen");
			print2("fuckUpSyncs\n");
			fuckUpSyncs();
			//causeCrashLol();
			break;
		case 30:
			//allClientStats::overflowFreeze(selectedPlayer);print2("Frozen");
			print2("causeCrashLol\n");
			//fuckUpSyncs();
			causeCrashLol();
			break;
		case 31:
			//NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES((void*)Read_Global_Address(262145+4715),1);
			setGlobalPlayerBroadcast(262145+4715,1);
			printf("Set global %i to 1\n",262145+4715);
			break;
		case 32:
			{
				//CGamePlayerBroadcastDataHandler_Remote data;
				//data.classData = (ClassData*)0x192A038;
				//this array is size of 0xF8
				unsigned int CGamePlayerBroadcastDataHandler_Remote_data[] = {0x0192A038, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000012, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000012, 0x00010000, 0x00120000, 0x00000000, 0x00000000, 0xFF000000, 0x33805224, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x40D13A80, 0x00010203, 0x04FF0607, 0xFF090A0B, 0x0C0D0E0F, 0xFFFF0000, 0x00000000, 0x00000000, 0x019262D8, 0x0222DE70, 0x00000003, 0x01000000, 0x00000001, 0x018B8758, 0xC875557D, 0x66726565, 0x6D6F6465, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000922F3, 0x00000000, 0xFFFFFFFF, 0xC875557D, 0x00000000};
				printf("Before\n");
				call<int>(0x130CD80)(getG_CGameArrayMgr(),CGamePlayerBroadcastDataHandler_Remote_data);//this function is ggggreat. this is like add.
				printf("Done\n");
			}
			break;*/
		/*case 27:
			if (isDevMode() && I_AM_ONLINE) {
				//scriptSpam.setPlayer(selectedPlayer);
				//scriptSpam.start();
			}
			break;*/
		//case 22:
			//if (modelHashToAddress_t.sub)
				//freeze_player(selectedPlayer);
			//break;
			
			//setModelData<char>(GAMEPLAY::GET_HASH_KEY("dune"),0x65,0xf);duneCallbackPlayer = selectedPlayer;VehicleMods::spawnVehicle("dune",duneCallback);break;
		//case 18: PlayerMods::preformSequenceAnim(selectedPlayer,"rcmfanatic1celebrate", "celebrate");print2("Test",1000);break;
		//case 19: PlayerMods::preformAnimSpecial(selectedPlayer,"rcmfanatic1celebrate", "celebrate");print2("Test 2",1000);break;
		//case 18: AUDIO::PLAY_PAIN(6,PLAYER::GET_PLAYER_PED(selectedPlayer),PLAYER::GET_PLAYER_PED(selectedPlayer));break;
		//case 19: AI::TASK_SCRIPTED_ANIMATION(PLAYER::GET_PLAYER_PED(selectedPlayer),"rcmfanatic1celebrate", "celebrate","celebrate",1,1);break;
		//case 20: AI::TASK_SCRIPTED_ANIMATION(PLAYER::GET_PLAYER_PED(selectedPlayer),"rcmfanatic1celebrate", "rcmfanatic1celebrate","celebrate",1,1);break;
		//case 21: AI::PLAY_ENTITY_SCRIPTED_ANIM(PLAYER::GET_PLAYER_PED(selectedPlayer),"rcmfanatic1celebrate", "celebrate","celebrate",1,1);break;
		//case 22: AI::PLAY_ENTITY_SCRIPTED_ANIM(PLAYER::GET_PLAYER_PED(selectedPlayer),"rcmfanatic1celebrate", "rcmfanatic1celebrate","celebrate",1,1);break;
		//case 17: PlayerMods::killInGodMode(selectedPlayer);break;

		//case 12: PlayerMods::doAnimation(selectedPlayer,"mini@strip_club@private_dance@part1", "priv_dance_p1");print2("May take a few clicks!",1000);break;
		//case 11: PlayerMods::attachHotdogToPlayer(selectedPlayer);break;
		//case 7: NETWORK::TEXTURE_DOWNLOAD_REQUEST(PlayerMods::v_3(selectedPlayer),"/dev_hdd0/photo/test/","hahaha_biiiiitch",true);break;
		//case 7: PlayerMods::doRealFreezePlayer(selectedPlayer);break;
		//case 12: PlayerMods::freezePlayer(selectedPlayer);break;
		}
		PlayerMods::rapePlayerArray[PlayerMods::rapePlayerInt] = PLAYER::GET_PLAYER_NAME(PlayerMods::rapePlayerInt);
		addTitle("Troll Options");
		addBoolOption(getCachedString("STR203"),PlayerMods::spamTextMessageBool[selectedPlayer],"Don't Spam For Too Long");   //Spam Text Message
		addOption(getCachedString("STR204"));   //Clone Player
		addOption(getCachedString("STR205"));//now makes doors locked too   //Screw With Their Car
		//addOption("Attach By Rope");
		addBoolOption(getCachedString("STR206"),PlayerMods::playerClearTask[selectedPlayer]);   //Clear Task Loop
		addOption(getCachedString("STR207"));   //Kill Player
		//addOption("Give Them 'First Person Mode'","Lol idek");
		addOption(getCachedString("STR208"));   //Radgoll Player *NEW*
		addOption(getCachedString("STR209"),"Make them kill the lobby");   //Blame Player
		addBoolOption(getCachedString("STR210"),PlayerMods::blamePlayerKillThemToo);   //Kill Them Too When Blaming Them
		//addSubmenuOption("Make Player Kill Player",Player_Options_Troll_Blame);
		addArrayOption(getCachedString("STR211"),&PlayerMods::rapePlayerInt,PlayerMods::rapePlayerArray,16);   //Make Kill
		addOption(getCachedString("STR212"));   //Michelin Man Outfit
		addOption(getCachedString("STR213"));   //Peeing
		//addOption("Hotdog Dick");
		//addOption("Freeze Player");
		addBoolOption(getCachedString("STR214"),PlayerMods::getForceField(selectedPlayer));   //Forcefield
		STREAMING::REQUEST_ANIM_DICT("rcmfanatic1celebrate");
		addArrayOption(getCachedString("STR215"),&PlayerMods::rapePlayerInt,PlayerMods::rapePlayerArray,16);   //Dance On
		addOption(getCachedString("STR216"),"Requested by Zundappchef");   //Teleport To Space
		addOption(getCachedString("STR217"));   //Spazz Mode
		addOption(getCachedString("STR218"));   //Clear Animations/Detach Player
		addOption(getCachedString("STR219"));   //PANTO SMASH
		//addOption(getCachedString("STR220"));   //Spawn House
		addOption(getCachedString("STR221"));   //Teleport Into Golf
		addOption(getCachedString("STR222")/*,&attachAllObjectsToPlayerCount,1,30,false,"Number is the amount of objects"*/);   //Attach Random Object To Player
		addOption(getCachedString("STR223"),"~r~Freeze warning. Using this too often/quickly may cause a freeze");   //Attach All Objects To Player
		addBoolOption(getCachedString("STR224"),resetViewBoolLoop[selectedPlayer],false);   //Reset View Loop
		addOption(getCachedString("STR225"));   //Send To Jail
		addOption(getCachedString("STR226"));   //Release From Jail
		//addOption("test mod");
		addOption(getCachedString("STR227"));   //Box Troll
		//if (isDevMode()/*modelHashToAddress_t.sub*/)
			addOption(getCachedString("STR228"));   //Other Freeze Console
		//#if DOAUTH == 0
		//if (isDevMode()/*modelHashToAddress_t.sub*/)
			addOption(duneCallbackPreviousVehicle==0?(char*)"Freeze Player (Vehicle)":(char*)"Waiting to freeze player...",duneCallbackPreviousVehicle==0?(char*)"Enter Vehicle ID.":(char*)"Click to cancel freezing");
		//addBoolOption("Freeze Console v2",&freezePlayerOverflowBool);
		//addOption("Freeze Console v2");
		
			//if (modelHashToAddress_t.sub)
			//addOption("Freeze Player Good");
		//if (isDevMode())
		//	addOption(getCachedString("STR229"));   //Fux Shix Up
		//#endif
		addOption((*shutdownPS3Bool_ptr) == true?(char*)"Please Wait...":getCachedString("STR839"),"Attempts to shut off their PS3. Will not always work.");//Attempt PS3 Shutdown
		addBoolOption("Freeze Player V2",freezingOn,"If your camera gets stuck, enable then disable first person mode");
		addOption("Freeze Player V3","A new freeze method");
		addOption("Disconnect Kick","Does not work on the host.");
		addOption("Punch Them","Hold X for multiple punches");
		addFloatOption("Attack Damage",&attack_damage,-9999.0f,9999.0f, true, 1.0f, 0, true, true);
		//addIntOption("Attack Number", &attack_value,0,50,true);
		//addBoolOption("Add Random Offset", &addRandomOffset);
		//addOption("Test Function");
		//addOption("Freeze Player V4");
		//addOption("Ban Player");
		/*addOption("Test");
		addOption("Test 2");
		addOption("Test 3");
		addOption("Test 4");*/
		//addOption("Kill In God Mode");
		//addOption("Do some fucked up shit");
		//addOption("Freeze Player");
		drawPlayerInfo();
		break;
#pragma endregion
#pragma region player_animations_menu
	/*case player_animations_2_menu:
		addTitle("Other Anims");
		addOption(getCachedString("STR230"));   //Fuck you
		switch (getOption()) {
		case 1: doAnimV2(selectedPlayer,"GENERIC_FUCK_YOU", "SPEECH_PARAMS_FORCE");print2("did");break;
		}
		break;*/
	case player_animations_menu:
		addTitle("Animations");
		//addOption("Animations V2 List");
		addOption(getCachedString("STR231"));   //Clear Animations
		addOption(getCachedString("STR232"));   //Celebrate
		addOption(getCachedString("STR233"));   //Pole Dance
		addOption(getCachedString("STR234"));   //Push-Ups
		addOption(getCachedString("STR235"));   //Suicide
		addOption(getCachedString("STR236"));   //Stripper Dance
		addOption(getCachedString("STR237"));   //Sit-Ups
		addOption(getCachedString("STR238"));   //Electrocution
		addOption(getCachedString("STR239"));   //Monkey Dance
		addOption(getCachedString("STR240"));   //Air Guitar
		addOption(getCachedString("STR241"));   //Fishing
		addOption(getCachedString("STR242"));   //Dance
		addOption(getCachedString("STR243"));   //Sex Recieve
		addOption(getCachedString("STR244"));   //Sex Give
		addOption(getCachedString("STR245"));   //Freak Out
		addOption(getCachedString("STR246"));   //Poo
		addOption(getCachedString("STR247"));   //Shower
		//addOption("Test Anim");
		//addBoolOption("False for NM",controlswitcheroonie);
		//addBoolOption("PSA1",PlayerMods::psa1,"",false);
		//addBoolOption("PSA2",PlayerMods::psa2,"",false);
		//addIntOption("PSA3",&PlayerMods::psa3,0,10,false,"");
		//addBoolOption("PSA4",PlayerMods::psa4,"",false);
		switch (getOption())
		{
		//case 1: changeSubmenu(player_animations_2_menu);break;
		case 1: PlayerMods::stopAnims(selectedPlayer); break;
		case 2: PlayerMods::doAnimation(selectedPlayer,"rcmfanatic1celebrate", "celebrate"); break;
		case 3: PlayerMods::doAnimation(selectedPlayer,"mini@strip_club@pole_dance@pole_dance1", "pd_dance_01"); break;
		case 4: PlayerMods::doAnimation(selectedPlayer,"amb@world_human_push_ups@male@base", "base"); break;
		case 5: PlayerMods::doAnimation(selectedPlayer,"mp_suicide", "pistol"); break;
		case 6: PlayerMods::doAnimation(selectedPlayer,"mini@strip_club@private_dance@part1", "priv_dance_p1"); break;
		case 7: PlayerMods::doAnimation(selectedPlayer,"amb@world_human_sit_ups@male@base", "base"); break;
		case 8: PlayerMods::doAnimation(selectedPlayer,"ragdoll@human", "electrocute"); break;
		case 9: PlayerMods::doAnimation(selectedPlayer,"missfbi5ig_30monkeys", "monkey_a_freakout_loop"); break;
		case 10: PlayerMods::doAnimation(selectedPlayer,"switch@trevor@guitar_beatdown", "001370_02_trvs_8_guitar_beatdown_idle_busker"); break;
		case 11: PlayerMods::doAnimation(selectedPlayer,"amb@world_human_stand_fishing@base", "base"); break;
		case 12: PlayerMods::doAnimation(selectedPlayer,"misschinese2_crystalmazemcs1_cs", "dance_loop_tao"); break;
		case 13: PlayerMods::doAnimation(selectedPlayer,"rcmpaparazzo_2", "shag_loop_poppy"); break;
		case 14: PlayerMods::doAnimation(selectedPlayer,"rcmpaparazzo_2", "shag_loop_a"); break;
		case 15: PlayerMods::doAnimation(selectedPlayer,"missfbi5ig_30monkeys", "monkey_b_freakout_loop"); break;
		case 16: PlayerMods::doAnimation(selectedPlayer,"missfbi3ig_0", "shit_loop_trev"); break;
		case 17: PlayerMods::doAnimation(selectedPlayer,"mp_safehouseshower@male@", "male_shower_idle_b"); break;
		//case 18: PedAnim::anim(PLAYER::GET_PLAYER_PED(selectedPlayer),"ragdoll@human", "electrocute");break;
		//case 19: controlswitcheroonie = !controlswitcheroonie;break;
		//case 18: PlayerMods::psa1 = !PlayerMods::psa1;break;
		//case 19: PlayerMods::psa2 = !PlayerMods::psa2;break;
		//case 20: break;
		//case 21: PlayerMods::psa4 = !PlayerMods::psa4;break;
		}
		//if (!controlswitcheroonie)
		//	TaskNM(PLAYER::GET_PLAYER_PED(selectedPlayer));
		//else
		//	request_control_of_entity(PLAYER::GET_PLAYER_PED(selectedPlayer));
		drawPlayerInfo();
		break;
#pragma endregion
#pragma region Player Options Troll Blame
	case Player_Options_Troll_Blame:
		if (1 == 1) {
			addTitle("Kill Player");
			int start = 0;
			for (int i = 0; i < 18; i++)
			{
				char *name = PLAYER::GET_PLAYER_NAME(i);
				if (isPlayerValid(name)) {
					addOption(name);
					start++;
					if (optionPress)
					{
						if (currentOption == start) {
							PlayerMods::playerExplodePlayer(selectedPlayer,i);
						}
					}
				}
			}
		}
		drawPlayerInfo();
		break;
#pragma endregion
#pragma region Player Options Weapon
	case Player_Options_Weapon:
		switch(getOption())
		{
		case 1: weaponMods::infiniteAmmo(selectedPlayer);break;
		case 2: PlayerMods::togglePlayerAimbot(selectedPlayer);break;
		case 3: break;//keyboard option
		case 4: PlayerMods::giveAllWeaponsToPlayer(selectedPlayer);break;
		case 5: WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::GET_PLAYER_PED(selectedPlayer),true);break;
		}
		addTitle("Player's Weapons");
		addBoolOption(getCachedString("STR248"),weaponMods::infiniteAmmoBool[selectedPlayer]);   //Infinite Ammo
		addBoolOption(getCachedString("STR249"),PlayerMods::isAimbotEnabled(selectedPlayer),"Toggle the players aimbot");   //Aimbot
		addKeyboardOption(getCachedString("STR250"),4,keyboardText,120,"Enter weapon");   //Give Weapon
		addOption(getCachedString("STR251"));   //Give All Weapons
		addOption(getCachedString("STR252"));   //Remove All Weapons
		drawPlayerInfo();
		break;
#pragma endregion
#pragma region Player Options Vehicle
	case Player_Options_Vehicle:
		switch(getOption()) {
		case 1:VehicleMods::modPlayerCar(selectedPlayer,TrafficMods::fix);break;
		case 2:VehicleMods::modPlayerCar(selectedPlayer,TrafficMods::colorize);break;
		case 3:VehicleMods::modPlayerCar(selectedPlayer,TrafficMods::boost);break;
		case 4:VehicleMods::modPlayerCar(selectedPlayer,TrafficMods::hop);break;
		case 5:VehicleMods::modPlayerCar(selectedPlayer,TrafficMods::gayify);break;
		case 6:VehicleMods::modPlayerCar(selectedPlayer,TrafficMods::explode);break;
		case 7:
			switch(TrafficMods::gravityType) {
			case 0: VehicleMods::modPlayerCar(selectedPlayer,TrafficMods::gravityHIGH);break;
			case 1: VehicleMods::modPlayerCar(selectedPlayer,TrafficMods::gravityNORMAL);break;
			case 2: VehicleMods::modPlayerCar(selectedPlayer,TrafficMods::gravityLOW);break;
			case 3: VehicleMods::modPlayerCar(selectedPlayer,TrafficMods::gravityNEGATIVE);break;
			}
			break;
		case 8: VehicleMods::modPlayerCar(selectedPlayer,TrafficMods::raiseSuspension);break;
		case 9: VehicleMods::modPlayerCar(selectedPlayer,TrafficMods::lowerSuspension);break;
		case 10: VehicleMods::modPlayerCar(selectedPlayer,TrafficMods::deleteVehicle);break;
		case 11: kickPlayerFromCarScriptEvent(selectedPlayer);break;
		case 12: TrafficMods::stealVehicleOwner = selectedPlayer; VehicleMods::modPlayerCar(selectedPlayer,TrafficMods::stealOwnership);break;
		}
		addTitle("Player's Vehicle");
		addOption(getCachedString("STR253"));   //Fix And Wash
		addOption(getCachedString("STR254"));   //Paint Random
		addOption(getCachedString("STR255"));   //Boost Forwards
		addOption(getCachedString("STR256"));   //Jump Into Air
		addOption(getCachedString("STR257"));   //Gayify
		addOption(getCachedString("STR258"),"Warning: Explosions");   //Explode
		addArrayOption(getCachedString("STR259"),&TrafficMods::gravityType,TrafficMods::gravityTypes,4);   //Gravity
		addOption(getCachedString("STR260"));   //Raise Suspension
		addOption(getCachedString("STR261"));   //Lower Suspension
		addOption(getCachedString("STR262"));   //Delete Vehicle
		addOption(getCachedString("STR263"));   //Kick Out Of Vehicle
		addOption("Steal Vehicle Ownership");
		drawPlayerInfo();
		break;
#pragma endregion
#pragma region Player Bodyguards
	case Player_Bodyguards:
		addTitle("Bodyguards");
		addOption(getCachedString("STR264"));   //Monkey
		addOption(getCachedString("STR265"));   //Deer
		addOption(getCachedString("STR266"));   //Cow
		addOption(getCachedString("STR267"));   //Marine
		addOption(getCachedString("STR268"));   //Hipster
		drawPlayerInfo();
		switch(getOption()) {
		case 1: bodyguard::spawnNow(selectedPlayer,bodyguard::pmonkey,bodyguard::types::Player);break;
		case 2: bodyguard::spawnNow(selectedPlayer,bodyguard::pdeer,bodyguard::types::Player);break;
		case 3: bodyguard::spawnNow(selectedPlayer,bodyguard::pcow,bodyguard::types::Player);break;
		case 4: bodyguard::spawnNow(selectedPlayer,bodyguard::parmy,bodyguard::types::Player);break;
		case 5: bodyguard::spawnNow(selectedPlayer,bodyguard::phipster,bodyguard::types::Player);break;
		}
		break;
#pragma endregion
#pragma region Weather Options
	case Weather_Options:
		static char *weatherChangedString = 0;//"~b~PARADISE SPRX\n~r~Weather changed!";
		static int staticWeatherNum = 0;
		switch(getOption()) {
		case 4:
			if (I_AM_ONLINE)
				setlobbytime(timeandweather::hours,timeandweather::minutes,timeandweather::seconds);
				//for (int i = 0; i < 18; i++)
				//	setTime(i,timeandweather::hours,timeandweather::minutes,timeandweather::seconds);
			//print2("If you are host, time will show for other people too.",1000);
			break;
		case 5: timeandweather::timeFrozen = !timeandweather::timeFrozen;TIME::PAUSE_CLOCK(timeandweather::timeFrozen);break;
		case 6: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("CLEAR");for (int i = 0; i < 18; i++)PlayerMods::notify(weatherChangedString,i);break;
		case 7: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("EXTRASUNNY");for (int i = 0; i < 18; i++)PlayerMods::notify(weatherChangedString,i);break;
		case 8: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("CLOUDS");for (int i = 0; i < 18; i++)PlayerMods::notify(weatherChangedString,i);break;
		case 9: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("OVERCAST");for (int i = 0; i < 18; i++)PlayerMods::notify(weatherChangedString,i);break;
		case 10: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("RAIN");for (int i = 0; i < 18; i++)PlayerMods::notify(weatherChangedString,i);break;
		case 11: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("CLEARING");for (int i = 0; i < 18; i++)PlayerMods::notify(weatherChangedString,i);break;
		case 12: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("THUNDER");for (int i = 0; i < 18; i++)PlayerMods::notify(weatherChangedString,i);break;
		case 13: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("SMOG");for (int i = 0; i < 18; i++)PlayerMods::notify(weatherChangedString,i);break;
		case 14: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("FOGGY");for (int i = 0; i < 18; i++)PlayerMods::notify(weatherChangedString,i);break;
		case 15: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("XMAS");for (int i = 0; i < 18; i++)PlayerMods::notify(weatherChangedString,i);break;
		case 16: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("SNOWLIGHT");for (int i = 0; i < 18; i++)PlayerMods::notify(weatherChangedString,i);break;
		case 17: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("BLIZZARD");for (int i = 0; i < 18; i++)PlayerMods::notify(weatherChangedString,i);break;
		case 18: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("NEUTRAL");for (int i = 0; i < 18; i++)PlayerMods::notify(weatherChangedString,i);break;
		//case 19: changeWetherTest(staticWeatherNum);print2("test test test set");break;
			case 19: snowBool = !snowBool;
				Write_Global(262145+4715,snowBool);
				break;
			//case 20: testSnowSync();break;
				//setGlobalValueForAll<int>(262145+4715,snowBool);break;//139908 in arabic 266860 266860
		//case 20: setAllOutOfBadsport();break;
			//case 20: testAddressToGlobal();break;
		}
		addTitle("Weather and Time");
		addIntOption(getCachedString("STR269"),true,1,&timeandweather::hours,0,23,false);   //Set Hours
		addIntOption(getCachedString("STR270"),true,1,&timeandweather::minutes,0,59,false);   //Set Minutes
		addIntOption(getCachedString("STR271"),true,1,&timeandweather::seconds,0,59,false);   //Set Seconds
		addOption(getCachedString("STR272"));   //Set Time
		addBoolOption(getCachedString("STR273"),timeandweather::timeFrozen);   //Freeze Time
		static char *showsForAllPlayers = "Shows for all players";
		addOption(getCachedString("STR274"),showsForAllPlayers);   //Clear
		addOption(getCachedString("STR275"),showsForAllPlayers);   //Sunny
		addOption(getCachedString("STR276"),showsForAllPlayers);   //Clouds
		addOption(getCachedString("STR277"),showsForAllPlayers);   //Overcast
		addOption(getCachedString("STR278"),showsForAllPlayers);   //Rain
		addOption(getCachedString("STR279"),showsForAllPlayers);   //Clearing
		addOption(getCachedString("STR280"),showsForAllPlayers);   //Thunder
		addOption(getCachedString("STR281"),showsForAllPlayers);   //Smog
		addOption(getCachedString("STR282"),showsForAllPlayers);   //Foggy
		addOption(getCachedString("STR283"),showsForAllPlayers);   //Christmas
		addOption(getCachedString("STR284"),showsForAllPlayers);   //Light Snow
		addOption(getCachedString("STR285"),showsForAllPlayers);   //Blizzard
		addOption(getCachedString("STR286"),showsForAllPlayers);   //Alien Weather
		addBoolOption(getCachedString("STR287"),snowBool);   //Snow
		//addOption("Test");
		//addOption("Test");
		//addOption("set all out of badsport");
		//addHexOption("Test",true,1,&staticWeatherNum,-0xFF,0xFF,true,0);
		break;
#pragma endregion






#pragma region Weather Options Player
	case Weather_Options_Player:
		switch(getOption()) {
		case 1: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("CLEAR",selectedPlayer);break;
		case 2: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("EXTRASUNNY",selectedPlayer);break;
		case 3: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("CLOUDS",selectedPlayer);break;
		case 4: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("OVERCAST",selectedPlayer);break;
		case 5: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("RAIN",selectedPlayer);break;
		case 6: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("CLEARING",selectedPlayer);break;
		case 7: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("THUNDER",selectedPlayer);break;
		case 8: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("SMOG",selectedPlayer);break;
		case 9: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("FOGGY",selectedPlayer);break;
		case 10: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("XMAS",selectedPlayer);break;
		case 11: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("SNOWLIGHT",selectedPlayer);break;
		case 12: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("BLIZZARD",selectedPlayer);break;
		case 13: GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("NEUTRAL",selectedPlayer);break;
		
		}
		addTitle("Weather For Player");
		addOption(getCachedString("STR274"));   //Clear
		addOption(getCachedString("STR275"));   //Sunny
		addOption(getCachedString("STR276"));   //Clouds
		addOption(getCachedString("STR277"));   //Overcast
		addOption(getCachedString("STR278"));   //Rain
		addOption(getCachedString("STR279"));   //Clearing
		addOption(getCachedString("STR280"));   //Thunder
		addOption(getCachedString("STR281"));   //Smog
		addOption(getCachedString("STR282"));   //Foggy
		addOption(getCachedString("STR283"));   //Christmas
		addOption(getCachedString("STR284"));   //Light Snow
		addOption(getCachedString("STR285"));   //Blizzard
		addOption(getCachedString("STR286"));   //Alien Weather
		drawPlayerInfo();
		break;
#pragma endregion




#pragma region Vision Options
	/*case Vision_Options:
		switch(getOption()) {
		case 1: if (vision_clearOnChoice)
					for (int i = 0; i < 83; i++)
						GRAPHICS::_0x06BB5CDA(screen_effects[i]);
				GRAPHICS::_0x1D980479(screen_effects[vision_integer],0,false);
				break;
		case 2: for (int i = 0; i < 83; i++)
					GRAPHICS::_0x06BB5CDA(screen_effects[i]);
				break;
		case 3: vision_clearOnChoice = !vision_clearOnChoice;break;
		}
		addTitle("Visions");
		addArrayOption(getCachedString("STR288"),true,&vision_integer,screen_effects,83);   //Visions
		addOption(getCachedString("STR289"));   //Stop Vision
		addBoolOption(getCachedString("STR290"),vision_clearOnChoice,"Automatically clear the previous vision",false);   //Clear Vision On Select
		break;*/
#pragma endregion
#pragma region Rope Player Menu
	case Rope_Player_Menu:
		rope::init();
		addTitle("Attach Rope To...");
		/*for (int i = 0; i < 18; i++)
		{
			addOption(PLAYER::GET_PLAYER_NAME(i));
		}
		if (optionPress)
		{
			rope::playerRopes[selectedPlayer].toggle(currentOption - 1);
			//changeSubmenuNoSave(Player_Options);
			submenu = lastSubmenu[submenuLevel - 1];
			currentOption = lastOption[submenuLevel - 1];
			submenuLevel--;
			playSound("Back");
		}*/
		if (1 == 1) {
			int start = 0;
			for (int i = 0; i < 18; i++)
			{
				char *name = PLAYER::GET_PLAYER_NAME(i);
				if (isPlayerValid(name)) {
					addOption(name);
					start++;
					if (optionPress)
					{
						if (currentOption == start) {
							rope::playerRopes[selectedPlayer].toggle(i);
							submenu = lastSubmenu[submenuLevel - 1];
							currentOption = lastOption[submenuLevel - 1];
							submenuLevel--;
							playSound("Back");
						}
					}
				}
			}
		}
		break;
#pragma endregion
#pragma region Player Options Props
	case Player_Options_Props:
		addTitle("Attach Props Main");
		addSubmenuOption(getCachedString("STR291"),Player_Options_Props_Select);   //Select Prop
		addSubmenuOption(getCachedString("STR292"),Player_Options_Props_Attach);   //Attach Prop
		break;
#pragma endregion
#pragma region Player Options Props Select
	case Player_Options_Props_Select:
		addTitle("Attach Props To Player");
		addKeyboardOption(getCachedString("STR293"),5,PlayerMods::curBoneProp,60,"Set prop ID to attach");   //Set Prop ID
		addOption(getCachedString("STR294"));   //UFO
		addOption(getCachedString("STR295"));   //Giant Orange
		addOption(getCachedString("STR296"));   //Big Blue Ball
		addOption(getCachedString("STR297"));   //Big Jet
		addOption(getCachedString("STR298"));   //White Box
		addOption(getCachedString("STR299"));   //Katana
		addOption(getCachedString("STR300"));   //Strobe Light
		addOption(getCachedString("STR301"));   //Tree Log
		addOption(getCachedString("STR302"));   //Future Gun
		addOption(getCachedString("STR303"));   //Bong
		addOption(getCachedString("STR304"));   //Dildo
		addOption(getCachedString("STR305"));   //Poop
		addOption(getCachedString("STR306"));   //Large TV
		addOption(getCachedString("STR307"));   //Lightsaber
		addOption(getCachedString("STR308"));   //Ferris Wheel
		addOption(getCachedString("STR309"));   //Alien Egg
		addOption(getCachedString("STR310"));   //Elevator
		addOption(getCachedString("STR311"));   //Boulder
		addOption(getCachedString("STR312"));   //Sculpture
		//addOption("Minecraft Block");
		drawPlayerInfo();
		switch(getOption()) {
		case 1: break;
		case 2: PlayerMods::curBoneProp = "P_SPINNING_ANUS_S";break;//PlayerMods::forceAttachPropToPlayer(selectedPlayer,PlayerMods::bones::Head,"P_SPINNING_ANUS_S");break;
		case 3: PlayerMods::curBoneProp = "prop_juicestand";break;//PlayerMods::forceAttachPropToPlayer(selectedPlayer,PlayerMods::bones::Head,"prop_juicestand");break;
		case 4: PlayerMods::curBoneProp = "prop_swiss_ball_01";break;//PlayerMods::forceAttachPropToPlayer(selectedPlayer,PlayerMods::bones::Head,"prop_swiss_ball_01");break;
		case 5: PlayerMods::curBoneProp = "p_cs_mp_jet_01_s";break;//PlayerMods::forceAttachPropToPlayer(selectedPlayer,PlayerMods::bones::Head,"p_cs_mp_jet_01_s");break;
		case 6: PlayerMods::curBoneProp = "prop_dummy_car";break;//PlayerMods::forceAttachPropToPlayer(selectedPlayer,PlayerMods::bones::Head,"prop_dummy_car");break;
		case 7: PlayerMods::curBoneProp = "prop_cs_katana_01";break;//PlayerMods::forceAttachPropToPlayer(selectedPlayer,PlayerMods::bones::Head,"prop_cs_katana_01");break;
		//case 8: PlayerMods::curBoneProp = "root_scrool_anim_skel";break;
		case 8: PlayerMods::curBoneProp = "prop_dummy_light"; break;
		case 9: PlayerMods::curBoneProp = "prop_log_03"; break;
		case 10: PlayerMods::curBoneProp = "prop_space_rifle"; break;
		case 11: PlayerMods::curBoneProp = "prop_sh_bong_01"; break;
		case 12: PlayerMods::curBoneProp = "prop_cs_dildo_01"; break;
		case 13: PlayerMods::curBoneProp = "prop_big_shit_02"; break;
		case 14: PlayerMods::curBoneProp = "prop_huge_display_01"; break;
		case 15: PlayerMods::curBoneProp = "prop_parking_wand_01"; break;
		case 16: PlayerMods::curBoneProp = "prop_Ld_ferris_wheel"; break;
		case 17: PlayerMods::curBoneProp = "prop_alien_egg_01"; break;
		case 18: PlayerMods::curBoneProp = "prop_test_elevator"; break;
		case 19: PlayerMods::curBoneProp = "prop_test_boulder_01"; break;
		case 20: PlayerMods::curBoneProp = "prop_sculpt_fix"; break;
		//case 21: PlayerMods::curBoneProp = ""; break;
		}
		break;
#pragma endregion
#pragma region Player Options Props Attach
	case Player_Options_Props_Attach:
		addTitle("Attach To Body Part");
		addOption(getCachedString("STR313"));   //Stomach
		addOption(getCachedString("STR314"));   //Chest
		addOption(getCachedString("STR315"));   //Gentils
		addOption(getCachedString("STR316"));   //Head
		addOption(getCachedString("STR317"));   //Left Arm
		addOption(getCachedString("STR318"));   //Left Hand
		addOption(getCachedString("STR319"));   //Left Knee
		addOption(getCachedString("STR320"));   //Left Shoe
		addOption(getCachedString("STR321"));   //Left Shoulder
		addOption(getCachedString("STR322"));   //Left Wrist
		addOption(getCachedString("STR323"));   //Mouth
		addOption(getCachedString("STR324"));   //Right Arm
		addOption(getCachedString("STR325"));   //Right Hand
		addOption(getCachedString("STR326"));   //Right Knee
		addOption(getCachedString("STR327"));   //Right Shoe
		addOption(getCachedString("STR328"));   //Right Shoulder
		addOption(getCachedString("STR329"));   //Right Wrist
		addOption(getCachedString("STR330"));   //Umbilical
		drawPlayerInfo();
		switch(getOption()) {
		case 1: PlayerMods::forceAttachPropToPlayer(selectedPlayer,PlayerMods::bones::BONE_ROOT,PlayerMods::curBoneProp);break;
		case 2: PlayerMods::forceAttachPropToPlayer(selectedPlayer,PlayerMods::bones::Chest,PlayerMods::curBoneProp);break;
		case 3: PlayerMods::forceAttachPropToPlayer(selectedPlayer,PlayerMods::bones::Gentils,PlayerMods::curBoneProp);break;
		case 4: PlayerMods::forceAttachPropToPlayer(selectedPlayer,PlayerMods::bones::Head,PlayerMods::curBoneProp);break;
		case 5: PlayerMods::forceAttachPropToPlayer(selectedPlayer,PlayerMods::bones::Left_Arm,PlayerMods::curBoneProp);break;
		case 6: PlayerMods::forceAttachPropToPlayer(selectedPlayer,PlayerMods::bones::Left_Hand,PlayerMods::curBoneProp);break;
		case 7: PlayerMods::forceAttachPropToPlayer(selectedPlayer,PlayerMods::bones::Left_Knee,PlayerMods::curBoneProp);break;
		case 8: PlayerMods::forceAttachPropToPlayer(selectedPlayer,PlayerMods::bones::Left_Shoe,PlayerMods::curBoneProp);break;
		case 9: PlayerMods::forceAttachPropToPlayer(selectedPlayer,PlayerMods::bones::Left_Shoulder,PlayerMods::curBoneProp);break;
		case 10: PlayerMods::forceAttachPropToPlayer(selectedPlayer,PlayerMods::bones::Left_Wrist,PlayerMods::curBoneProp);break;
		case 11: PlayerMods::forceAttachPropToPlayer(selectedPlayer,PlayerMods::bones::Month,PlayerMods::curBoneProp);break;
		case 12: PlayerMods::forceAttachPropToPlayer(selectedPlayer,PlayerMods::bones::Right_Arm,PlayerMods::curBoneProp);break;
		case 13: PlayerMods::forceAttachPropToPlayer(selectedPlayer,PlayerMods::bones::Right_Hand,PlayerMods::curBoneProp);break;
		case 14: PlayerMods::forceAttachPropToPlayer(selectedPlayer,PlayerMods::bones::Right_Knee,PlayerMods::curBoneProp);break;
		case 15: PlayerMods::forceAttachPropToPlayer(selectedPlayer,PlayerMods::bones::Right_Shoe,PlayerMods::curBoneProp);break;
		case 16: PlayerMods::forceAttachPropToPlayer(selectedPlayer,PlayerMods::bones::Right_Shoulder,PlayerMods::curBoneProp);break;
		case 17: PlayerMods::forceAttachPropToPlayer(selectedPlayer,PlayerMods::bones::Right_Wrist,PlayerMods::curBoneProp);break;
		case 18: PlayerMods::forceAttachPropToPlayer(selectedPlayer,PlayerMods::bones::Umbilical,PlayerMods::curBoneProp);break;
		}
		break;
#pragma endregion
#pragma region Player Options Money Bag Type
	case Player_Options_Money_Bag_Type:
	addTitle("Set Money Bag Type");
    addOption("Airport Ramp");
    addOption("UFO");
    addOption("Windmill");
    addOption("Huge Barge");
    addOption("Dummy");
    addOption("Huge Ball");
    addOption("Glowing EMP");
    addOption("Crashed Tram");
    addOption("AA Gun");
    addOption("Spinning");
    addOption("Radar");
    addOption("Tug Boat");
    addOption("Cable Car");
    addOption("Soccer Ball");
    addOption("Roller Car");
    addOption("Ferris Wheel");
    addOption("Bank Safe");
    addOption("Oil Slick");
    addOption("ATM Machine");
    addOption("Big Jet");
    addOption("Mini Gun");
    addOption("Car Seat");
    addOption("Ramp 01");
    addOption("Ramp 02");
    addOption("Ramp 03");
    addOption("Beach Fire");
    addOption("Weed Pallet");
    addOption("Crashed Heli");
    addOption("Space Pistol");
    addOption("Toilet");
    addOption("Wheelchair");
    addOption("Trolley");
    addOption("Flat TV");
    addOption("Ice Locker");
    addOption("Road Cone");
    addOption("Air Stair");
    addOption("Wheel");
    addOption("Dustbin");
    addOption("Beggers Sign");
    addOption("Food Van");
    addOption("Golf Bag");
    addOption("Carwash Roller");
    addOption("Skip");
    addOption("Cash Crate");
    addOption("Dummy Plane");
    addOption("Air Lights");
    addOption("Portacabin");
    addOption("Beer Neon");
    addOption("Haybail");
    addOption("40K Money Bag");
    switch (getOption())
    {
    case 1: PlayerMods::setMoneyDropType("PROP_AIR_BLASTFENCE_01"); break;
    case 2: PlayerMods::setMoneyDropType("p_spinning_anus_s"); break;
    case 3: PlayerMods::setMoneyDropType("prop_windmill_01"); break;
    case 4: PlayerMods::setMoneyDropType("prop_lev_des_barge_02"); break;
    case 5: PlayerMods::setMoneyDropType("prop_dummy_01"); break;
    case 6: PlayerMods::setMoneyDropType("prop_juicestand"); break;
    case 7: PlayerMods::setMoneyDropType("hei_prop_heist_emp"); break;
    case 8: PlayerMods::setMoneyDropType("p_tram_crash_s"); break;
    case 9: PlayerMods::setMoneyDropType("hei_prop_carrier_defense_01"); break;
    case 10: PlayerMods::setMoneyDropType("prop_air_bigradar"); break;
    case 11: PlayerMods::setMoneyDropType("hei_prop_carrier_radar_1"); break;
    case 12: PlayerMods::setMoneyDropType("hei_prop_heist_tug"); break;
    case 13: PlayerMods::setMoneyDropType("p_cablecar_s"); break;
    case 14: PlayerMods::setMoneyDropType("p_ld_soc_ball_01"); break;
    case 15: PlayerMods::setMoneyDropType("prop_roller_car_01"); break;
    case 16: PlayerMods::setMoneyDropType("prop_Ld_ferris_wheel"); break;
    case 17: PlayerMods::setMoneyDropType("p_v_43_safe_s"); break;
    case 18: PlayerMods::setMoneyDropType("p_oil_slick_01"); break;
    case 19: PlayerMods::setMoneyDropType("prop_atm_01"); break;
    case 20: PlayerMods::setMoneyDropType("PROP_MED_JET_01"); break;
    case 21: PlayerMods::setMoneyDropType("prop_minigun_01"); break;
    case 22: PlayerMods::setMoneyDropType("prop_car_seat"); break;
    case 23: PlayerMods::setMoneyDropType("prop_mp_ramp_01"); break;
    case 24: PlayerMods::setMoneyDropType("prop_mp_ramp_02"); break;
    case 25: PlayerMods::setMoneyDropType("prop_mp_ramp_03"); break;
    case 26: PlayerMods::setMoneyDropType("prop_beach_fire"); break;
    case 27: PlayerMods::setMoneyDropType("prop_weed_pallet"); break;
    case 28: PlayerMods::setMoneyDropType("prop_crashed_heli"); break;
    case 29: PlayerMods::setMoneyDropType("prop_space_pistol"); break;
    case 30: PlayerMods::setMoneyDropType("prop_ld_toilet_01"); break;
    case 31: PlayerMods::setMoneyDropType("prop_wheelchair_01"); break;
    case 32: PlayerMods::setMoneyDropType("prop_cs_trolley_01"); break;
    case 33: PlayerMods::setMoneyDropType("prop_tv_06"); break;
    case 34: PlayerMods::setMoneyDropType("prop_cs_ice_locker"); break;
    case 35: PlayerMods::setMoneyDropType("prop_roadcone01a"); break;
    case 36: PlayerMods::setMoneyDropType("prop_air_stair_03"); break;
    case 37: PlayerMods::setMoneyDropType("prop_wheel_01"); break;
    case 38: PlayerMods::setMoneyDropType("prop_bin_04a"); break;
    case 39: PlayerMods::setMoneyDropType("prop_beggers_sign_01"); break;
    case 40: PlayerMods::setMoneyDropType("prop_food_van_01"); break;
    case 41: PlayerMods::setMoneyDropType("prop_golf_bag_01b"); break;
    case 42: PlayerMods::setMoneyDropType("prop_carwash_roller_vert"); break;
    case 43: PlayerMods::setMoneyDropType("prop_skip_01a"); break;
    case 44: PlayerMods::setMoneyDropType("prop_cash_crate_01"); break;
    case 45: PlayerMods::setMoneyDropType("prop_dummy_plane"); break;
    case 46: PlayerMods::setMoneyDropType("prop_air_lights_02a"); break;
    case 47: PlayerMods::setMoneyDropType("prop_portacabin01"); break;
    case 48: PlayerMods::setMoneyDropType("prop_beer_neon_01"); break;
    case 49: PlayerMods::setMoneyDropType("prop_ld_haybail"); break;
	case 50: PlayerMods::setMoneyDropTypeOriginal();break;
    }
	break;
#pragma endregion
#if ENTITYOPTIONS
#pragma region Entity Main Options
	case Entity_Main_Options:
		addTitle("Peds");
		addOption(getCachedString("STR331"));   //Ped 1
		addOption(getCachedString("STR332"));   //Ped 2
		addOption(getCachedString("STR333"));   //Ped 3
		addOption(getCachedString("STR334"));   //Ped 4
		addOption(getCachedString("STR335"));   //Ped 5
		switch(getOption()) {
		case 1: entityMods::curEntity = 1;entityMods::curEntityComponentValue = PlayerMods::components::getTexture(entityMods::getPed(entityMods::curEntity),0);changeSubmenu(Entity_Sub_Options);break;
		case 2: entityMods::curEntity = 2;entityMods::curEntityComponentValue = PlayerMods::components::getTexture(entityMods::getPed(entityMods::curEntity),0);changeSubmenu(Entity_Sub_Options);break;
		case 3: entityMods::curEntity = 3;entityMods::curEntityComponentValue = PlayerMods::components::getTexture(entityMods::getPed(entityMods::curEntity),0);changeSubmenu(Entity_Sub_Options);break;
		case 4: entityMods::curEntity = 4;entityMods::curEntityComponentValue = PlayerMods::components::getTexture(entityMods::getPed(entityMods::curEntity),0);changeSubmenu(Entity_Sub_Options);break;
		case 5: entityMods::curEntity = 5;entityMods::curEntityComponentValue = PlayerMods::components::getTexture(entityMods::getPed(entityMods::curEntity),0);changeSubmenu(Entity_Sub_Options);break;
		}
		break;
#pragma endregion
#pragma region Entity Sub Options
	case Entity_Sub_Options:
		//char ebuf[10];
		snprintf$(global_temporary_buf,sizeof(global_temporary_buf),"Ped %i",entityMods::curEntity);
		addTitle(global_temporary_buf);
		addBoolOption(getCachedString("STR336"),entityMods::isAlive(entityMods::curEntity));   //Spawn
		addOption(getCachedString("STR337"));   //Remove
		addOption(getCachedString("STR338"));   //Set As Bodyguard
		addOption(getCachedString("STR339"));   //Remove Bodyguard
		addOption(getCachedString("STR340"));   //Set Invincible
		addOption(getCachedString("STR341"));   //Set Not Invincible
		addOption(getCachedString("STR342"));   //Give Minigun
		addOption(getCachedString("STR343"));   //Remove Minigun
		addOption(getCachedString("STR344"));   //Attach To Player
		addOption(getCachedString("STR345"));   //Detach
		addOption(getCachedString("STR346"));   //Attack Player
		addOption(getCachedString("STR347"));   //Teleport To Ped
		addOption(getCachedString("STR348"));   //Teleport To Me
		addIntOption(getCachedString("STR349"),&entityMods::curEntityComponentValue,0,255,true);   //Texture ID
		addOption(getCachedString("STR350"));   //Animations
		switch(getOption()) {
		case 1: changeSubmenu(Entity_Sub_Options_List_Peds);break;
		case 2: entityMods::remove(entityMods::curEntity);print("Entity Removed");break;
		case 3: changeSubmenu(Entity_Set_As_Bodyguard_Options);break;
		case 4: entityMods::removeAsBodyguard(entityMods::curEntity);break;
		case 5: entityMods::setInvincible(entityMods::getPed(entityMods::curEntity),true);break;
		case 6: entityMods::setInvincible(entityMods::getPed(entityMods::curEntity),false);break;
		case 7: entityMods::giveMinigun(entityMods::getPed(entityMods::curEntity));break;
		case 8: entityMods::removeAllGuns(entityMods::getPed(entityMods::curEntity));break;
		case 9: changeSubmenu(Entity_Attach_To_Player_List);
		case 10: ENTITY::DETACH_ENTITY(entityMods::getPed(entityMods::curEntity),true,true);break;
		case 11: changeSubmenu(Entity_Attack_Player_List);break;
		case 12: ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),ENTITY::GET_ENTITY_COORDS(entityMods::getPed(entityMods::curEntity),true).x,ENTITY::GET_ENTITY_COORDS(entityMods::getPed(entityMods::curEntity),true).y,ENTITY::GET_ENTITY_COORDS(entityMods::getPed(entityMods::curEntity),true).z,0,0,0,true);break;//teleport to it
		case 13: ENTITY::SET_ENTITY_COORDS(entityMods::getPed(entityMods::curEntity),ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true).x,ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true).y,ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true).z,0,0,0,true);break;//teleport it to you
		case 14: break;
		case 15: changeSubmenu(Entity_Anim_List);break;
		}
		break;
#pragma endregion
#pragma region Entity Anim List
	case Entity_Anim_List:
		addTitle("Animations");
		addOption(getCachedString("STR351"));   //Stop Animations
		addOption(getCachedString("STR352"));   //Play Music
		addOption(getCachedString("STR353"));   //Take Photo
		addOption(getCachedString("STR354"));   //Binoculars
		addOption(getCachedString("STR355"));   //Drink
		addOption(getCachedString("STR356"));   //Play Golf
		addOption(getCachedString("STR357"));   //Lift Weights
		addOption(getCachedString("STR358"));   //Smoke
		addOption(getCachedString("STR359"));   //Handyman
		addOption(getCachedString("STR360"));   //Yoga
		addOption(getCachedString("STR361"));   //Flex Muscles
		addOption(getCachedString("STR362"));   //Celebrate
		addOption(getCachedString("STR363"));   //Pole Dance
		addOption(getCachedString("STR364"));   //Push-Ups
		addOption(getCachedString("STR365"));   //Suicide
		addOption(getCachedString("STR366"));   //Stripper Dance
		addOption(getCachedString("STR367"));   //Sit-Ups
		addOption(getCachedString("STR368"));   //Electrocution
		switch (getOption())
		{
		case 1: AI::CLEAR_PED_TASKS_IMMEDIATELY(entityMods::getPed(entityMods::curEntity)); break;
		case 2: AI::TASK_START_SCENARIO_IN_PLACE(entityMods::getPed(entityMods::curEntity), "WORLD_HUMAN_MUSICIAN", 0, 1); break;
		case 3: AI::TASK_START_SCENARIO_IN_PLACE(entityMods::getPed(entityMods::curEntity), "WORLD_HUMAN_PAPARAZZI", 0, 1); break;
		case 4: AI::TASK_START_SCENARIO_IN_PLACE(entityMods::getPed(entityMods::curEntity), "WORLD_HUMAN_BINOCULARS", 0, 1); break;
		case 5: AI::TASK_START_SCENARIO_IN_PLACE(entityMods::getPed(entityMods::curEntity), "WORLD_HUMAN_DRINKING", 0, 1); break;
		case 6: AI::TASK_START_SCENARIO_IN_PLACE(entityMods::getPed(entityMods::curEntity), "WORLD_HUMAN_GOLF_PLAYER", 0, 1); break;
		case 7: AI::TASK_START_SCENARIO_IN_PLACE(entityMods::getPed(entityMods::curEntity), "WORLD_HUMAN_MUSCLE_FREE_WEIGHTS", 0, 1); break;
		case 8: AI::TASK_START_SCENARIO_IN_PLACE(entityMods::getPed(entityMods::curEntity), "WORLD_HUMAN_SMOKING_POT", 0, 1); break;
		case 9: AI::TASK_START_SCENARIO_IN_PLACE(entityMods::getPed(entityMods::curEntity), "WORLD_HUMAN_HAMMERING", 0, 1); break;
		case 10: AI::TASK_START_SCENARIO_IN_PLACE(entityMods::getPed(entityMods::curEntity), "WORLD_HUMAN_YOGA", 0, 1); break;
		case 11: AI::TASK_START_SCENARIO_IN_PLACE(entityMods::getPed(entityMods::curEntity), "WORLD_HUMAN_MUSCLE_FLEX", 0, 1); break;
		case 12: PedAnim::anim(entityMods::getPed(entityMods::curEntity),"rcmfanatic1celebrate", "celebrate"); break;
		case 13: PedAnim::anim(entityMods::getPed(entityMods::curEntity),"mini@strip_club@pole_dance@pole_dance1", "pd_dance_01"); break;
		case 14: PedAnim::anim(entityMods::getPed(entityMods::curEntity),"amb@world_human_push_ups@male@base", "base"); break;
		case 15: PedAnim::anim(entityMods::getPed(entityMods::curEntity),"mp_suicide", "pistol"); break;
		case 16: PedAnim::anim(entityMods::getPed(entityMods::curEntity),"mini@strip_club@private_dance@part1", "priv_dance_p1"); break;
		case 17: PedAnim::anim(entityMods::getPed(entityMods::curEntity),"amb@world_human_sit_ups@male@base", "base"); break;
		case 18: PedAnim::anim(entityMods::getPed(entityMods::curEntity),"ragdoll@human", "electrocute"); break;
		}
		break;
#pragma endregion
#pragma region Entity Sub Options List Peds
	case Entity_Sub_Options_List_Peds:
		//char eebuf[30];
		//snprintf$(eebuf,sizeof(eebuf),"Spawn List",entityMods::curEntity);
		addTitle("Spawn List");
		for (int i = 0; i < 30; i++) {//597
			addOption(entityMods::pedHashes[i]);
			if (getOption() == i+1) {
				entityMods::initEntity(entityMods::pedHashes[i],entityMods::curEntity);
			}
		}
		break;
#pragma endregion
#pragma region Entity Attach To Player List
	case Entity_Attach_To_Player_List:

		if (1 == 1) {
			addTitle("Attach To Player");
			int start = 0;
			for (int i = 0; i < 18; i++)
			{
				char *name = PLAYER::GET_PLAYER_NAME(i);
				if (isPlayerValid(name)) {
					addOption(name);
					start++;
					if (optionPress)
					{
						if (currentOption == start) {
							entityMods::attachToPlayer(i,entityMods::curEntity);
						}
					}
				}
			}
		}
		break;
#pragma endregion
#pragma region Entity Attack Player List
	case Entity_Attack_Player_List:
		addTitle("Attack Player");

		if (1 == 1) {
			int start = 0;
			for (int i = 0; i < 18; i++)
			{
				char *name = PLAYER::GET_PLAYER_NAME(i);
				if (isPlayerValid(name)) {
					addOption(name);
					start++;
					if (optionPress)
					{
						if (currentOption == start) {
							entityMods::attackPlayer(i,entityMods::curEntity);
						}
					}
				}
			}
		}
		break;
#pragma endregion
#pragma region Entity_Set_As_Bodyguard_Options
	case Entity_Set_As_Bodyguard_Options:
		addTitle("Set As Bodyguard");

		if (1 == 1) {
			int start = 0;
			for (int i = 0; i < 18; i++)
			{
				char *name = PLAYER::GET_PLAYER_NAME(i);
				if (isPlayerValid(name)) {
					addOption(name);
					start++;
					if (optionPress)
					{
						if (currentOption == start) {
							entityMods::setAsBodyguard(i,entityMods::curEntity);
						}
					}
				}
			}
		}
		break;
#pragma endregion
		#endif
#pragma region Teleport Options
	case Teleport_Options:
		switch(getOption()) {
		case 1: PlayerMods::teleportToWaypoint();break;
		case 2: break;
		}
		addTitle("Teleport Options");
		addOption(getCachedString("STR369"));   //Teleport To Waypoint
		addSubmenuOption(getCachedString("STR370"),Teleport_Multiplayer_Locations);   //Multiplayer Locations
		addSubmenuOption(getCachedString("STR371"),Teleport_Singleplayer_Locations);   //Singleplayer Locations
		addSubmenuOption(getCachedString("STR372"),Teleport_Landmarks_Locations);   //Landmarks
		addSubmenuOption(getCachedString("STR373"),Teleport_Favorites);   //My Favorites
		break;
#pragma endregion
		//possible addresses for liscense plate: 31541704 37039588
#pragma region Vehicle Options
	case Vehicle_Options:
		addTitle("Vehicle Options");
		addSubmenuOption(getCachedString("STR374"),Vehicle_Spawner_Main);   //Vehicle Spawner
		addSubmenuOption(getCachedString("STR375"),Vehicle_ModShop);   //Vehicle Part Shop
		addSubmenuOption(getCachedString("STR376"),Vehicle_Regular_Mods);   //Regular Vehicle Mods
		break;
#pragma endregion
#pragma region Vehicle Modshop Sub
	case Vehicle_Modshop_Sub:
		VehicleMods::getControlOfCurrentVehicle();
		addTitle(VehicleMods::curShopPartText/*VEHICLE::GET_MOD_SLOT_NAME(VehicleMods::getMyVehicle(),VehicleMods::curShopPart)*/);
		VehicleMods::maxVehOptions = VehicleMods::getMaxMods(VehicleMods::curShopPart);
		addOption(getCachedString("STR377"));   //Default
		for (int i = 0; i < VehicleMods::maxVehOptions;i++) {
			char *text = UI::_0x95C4B5AD(VEHICLE::GET_MOD_TEXT_LABEL(VehicleMods::getMyVehicle(),VehicleMods::curShopPart,i));
			if (strstr("NULL",text)) {
				//static char buf[30];
				snprintf(global_temporary_buf,sizeof(global_temporary_buf),"%s %i",VehicleMods::curShopPartText,i+1);
				text = global_temporary_buf;
			}
			addOption(text);
		}
		if(getOption() != 0) {
			if (getOption() == 1) {
				VehicleMods::setVehicleMod(VehicleMods::curShopPart,-1);
			} else {
				VehicleMods::setVehicleMod(VehicleMods::curShopPart,getOption()-2);//-1 is normal but -2 since the default
			}
			print2("Part Set!",1000);
		}
		break;
#pragma endregion
#pragma region Vehicle Mod Shop
	case Vehicle_ModShop:
		addTitle("Los Santos Customs");
		switch(getOption()) {
		case 1: break;
		case 2: VehicleMods::saveinsideofvehiclemenu();break;
		case 3: break;
		}
		addSubmenuOption(getCachedString("STR378"),Vehicle_Modshop_Parts);   //Parts
		addSubmenuOption(getCachedString("STR379"),Vehicle_Modshop_Colors);   //Colors
		addSubmenuOption(getCachedString("STR380"),Vehicle_Modshop_Colors_RGB);   //More Colors
		addOption(getCachedString("STR381"));   //Extras
		addKeyboardOption(getCachedString("STR382"),Keyboard_Plate_text,keyboardText,120,"Enter liscence plate");   //Set License Plate Text
		if (getOption() == 4) {
			//for (int i = 0; i < 25; i++)VehicleMods::extras[i] = 0;/*VehicleMods::extras[i] = VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(VehicleMods::getMyVehicle(),i);*/
			changeSubmenu(Vehicle_Extras);break;
		}
		break;
#pragma endregion
#pragma region Vehicle Extras
	case Vehicle_Extras:
		addTitle("Extras");
		extracurrentoption = 0;
		for (int i = 0; i < 25; i++) {
			int veh = VehicleMods::getMyVehicle();
			if (VEHICLE::DOES_EXTRA_EXIST(veh,i)) {
				//static char buf[10];
				snprintf(global_temporary_buf,sizeof(global_temporary_buf),"Extra %i",i);
				//int b = VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(veh,i);
				//addBoolOption(buf,b);
				extracurrentoption++;
				//VehicleMods::extras[i] = VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(veh,i);
				addBoolOption(global_temporary_buf,VehicleMods::extras[i],"This extra is available",false);
				if (getOption() == extracurrentoption) {
					//print("Debug Extras");
					//snprintf$(buf,sizeof(buf),"Option: %i eco: %i",getOption(),extracurrentoption);
					//print(buf);
					//snprintf$(buf,sizeof(buf),"Current: %i",b);
					//print(buf);
					//snprintf$(buf,sizeof(buf),"To be: %i",!b);
					//print(buf);
					//VEHICLE::SET_VEHICLE_EXTRA(veh,i,!b);
					VehicleMods::extras[i] = !VehicleMods::extras[i];
				}
				VEHICLE::SET_VEHICLE_EXTRA(veh,i,VehicleMods::extras[i]);
			}
		}
		if (extracurrentoption == 0) {
			addOption(getCachedString("STR383"));   //There Are No Extras For This Car
		}
		break;
#pragma endregion
#pragma region Vehicle Mod Shop Parts
	case Vehicle_Modshop_Parts:
		addTitle("Vehicle Mod Shop");

		switch(getOption()) {
		case 1: VehicleMods::curShopPart = VehicleMods::Spoilers_id;strncpy(VehicleMods::curShopPartText,"Spoilers",50);break;
		case 2: VehicleMods::curShopPart = VehicleMods::Front_Bumper_id;strncpy(VehicleMods::curShopPartText,"Front Bumper",50);break;
		case 3: VehicleMods::curShopPart = VehicleMods::Rear_Bumper_id;strncpy(VehicleMods::curShopPartText,"Rear Bumper",50);break;
		case 4: VehicleMods::curShopPart = VehicleMods::Side_Skirt_id;strncpy(VehicleMods::curShopPartText,"Side Skirt",50);break;
		case 5: VehicleMods::curShopPart = VehicleMods::Exhaust_id;strncpy(VehicleMods::curShopPartText,"Exhaust",50);break;
		case 6: VehicleMods::curShopPart = VehicleMods::Frame_id;strncpy(VehicleMods::curShopPartText,"Frame",50);break;
		case 7: VehicleMods::curShopPart = VehicleMods::Grille_id;strncpy(VehicleMods::curShopPartText,"Grille",50);break;
		case 8: VehicleMods::curShopPart = VehicleMods::Hood_id;strncpy(VehicleMods::curShopPartText,"Hood",50);break;
		case 9: VehicleMods::curShopPart = VehicleMods::Fender_id;strncpy(VehicleMods::curShopPartText,"Fender",50);break;
		case 10: VehicleMods::curShopPart = VehicleMods::Right_Fender_id;strncpy(VehicleMods::curShopPartText,"Right Fender",50);break;
		case 11: VehicleMods::curShopPart = VehicleMods::Roof_id;strncpy(VehicleMods::curShopPartText,"Roof",50);break;
		case 12: VehicleMods::curShopPart = VehicleMods::Engine_id;strncpy(VehicleMods::curShopPartText,"Engine",50);break;
		case 13: VehicleMods::curShopPart = VehicleMods::Brakes_id;strncpy(VehicleMods::curShopPartText,"Brakes",50);break;
		case 14: VehicleMods::curShopPart = VehicleMods::Transmission_id;strncpy(VehicleMods::curShopPartText,"Transmission",50);break;
		case 15: VehicleMods::curShopPart = VehicleMods::Horns_id;strncpy(VehicleMods::curShopPartText,"Horns",50);break;
		case 16: VehicleMods::curShopPart = VehicleMods::Suspension_id;strncpy(VehicleMods::curShopPartText,"Suspension",50);break;
		case 17: VehicleMods::curShopPart = VehicleMods::Armor_id;strncpy(VehicleMods::curShopPartText,"Armor",50);break;
		case 18: VehicleMods::curShopPart = VehicleMods::Front_Wheels_id;strncpy(VehicleMods::curShopPartText,"Front Wheels",50);break;
		case 19: VehicleMods::curShopPart = VehicleMods::Back_Wheels_id;strncpy(VehicleMods::curShopPartText,"Back Wheels",50);break;
		}

		addSubmenuOption(getCachedString("STR384"), Vehicle_Modshop_Sub);   //Spoilers
		addSubmenuOption(getCachedString("STR385"), Vehicle_Modshop_Sub);   //Front Bumper
		addSubmenuOption(getCachedString("STR386"), Vehicle_Modshop_Sub);   //Rear Bumper
		addSubmenuOption(getCachedString("STR387"), Vehicle_Modshop_Sub);   //Side Skirt
		addSubmenuOption(getCachedString("STR388"), Vehicle_Modshop_Sub);   //Exhaust
		addSubmenuOption(getCachedString("STR389"), Vehicle_Modshop_Sub);   //Frame
		addSubmenuOption(getCachedString("STR390"), Vehicle_Modshop_Sub);   //Grille
		addSubmenuOption(getCachedString("STR391"), Vehicle_Modshop_Sub);   //Hood

		addSubmenuOption(getCachedString("STR392"), Vehicle_Modshop_Sub);   //Fender
		addSubmenuOption(getCachedString("STR393"), Vehicle_Modshop_Sub);   //Right Fender
		addSubmenuOption(getCachedString("STR394"), Vehicle_Modshop_Sub);   //Roof
		addSubmenuOption(getCachedString("STR395"), Vehicle_Modshop_Sub);   //Engine
		addSubmenuOption(getCachedString("STR396"), Vehicle_Modshop_Sub);   //Brakes
		addSubmenuOption(getCachedString("STR397"), Vehicle_Modshop_Sub);   //Transmission
		addSubmenuOption(getCachedString("STR398"), Vehicle_Modshop_Sub);   //Horns

		addSubmenuOption(getCachedString("STR399"), Vehicle_Modshop_Sub);   //Suspension
		addSubmenuOption(getCachedString("STR400"), Vehicle_Modshop_Sub);   //Armor
		addSubmenuOption(getCachedString("STR401"), Vehicle_Modshop_Sub);   //Front Wheels
		addSubmenuOption(getCachedString("STR402"), Vehicle_Modshop_Sub,"Only For Bikes");   //Back Wheels
		break;
#pragma endregion
#pragma region Vehicle Regular Mods
	case Vehicle_Regular_Mods:
		static float tmp1we = 1.0f;
		switch(getOption()) {
			//case 1: break;
			case 1: VehicleMods::max();break;
			//case 3: VehicleMods::godmode(true);break;
			//case 4: VehicleMods::godmode(false);break;
			case 2: VehicleMods::enabledgodmodeloop = !VehicleMods::enabledgodmodeloop;break;
			case 3: VehicleMods::fixandwash();break;
			case 4: VehicleMods::stickToGround = !VehicleMods::stickToGround;break;
			case 5: VehicleMods::nfs = !VehicleMods::nfs;break;
			case 6: break;//nfs speed
			case 7: break;
			case 8: VehicleMods::paradiseColorChanger = !VehicleMods::paradiseColorChanger;break;
			case 9:
				setVehicleSuspension(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),true),getVehicleSuspension(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),true))-0.1f);
				break;
			case 10:
				setVehicleSuspension(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),true),getVehicleSuspension(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),true))+0.1f);
				break;
			case 11: break;
			case 12: break;
			case 13: setVehicleWheelRotMultiplier(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),false),currentVehicleWheel,tmp1we);print2("Set");break;
			case 14:
				for (int i = 0; i < 4; i++)
					setVehicleWheelContour(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),true),i,1);
				break;
			case 15:
				for (int i = 0; i < 4; i++)
					setVehicleWheelContour(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),true),i,-1);
				break;
			case 16:
				for (int i = 0; i < 4; i++)
					setVehicleWheelContour(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),true),i,0);
				break;
			case 17: VehicleMods::squareDriftModBool = !VehicleMods::squareDriftModBool;break;
			case 18:
				for (int i = 0; i < 8; i++)
					VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),true),i,false,true);
				break;
			case 19:
				for (int i = 0; i < 8; i++)
					VEHICLE::SET_VEHICLE_DOOR_SHUT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),true),i,true);
				break;
			case 20:
				VehicleMods::matrixPlateBool = !VehicleMods::matrixPlateBool;
				break;
			/*case 21:
				setEntityData<float>(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),true),0x520 float offset for light intensity,(float)vehicleLightIntensityVar);
				break;*/
			
			case 21:
				VEHICLE::SET_VEHICLE_LIGHT_MULTIPLIER(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),true),(float)vehicleLightIntensityVar);
				break;
			case 22:
				//PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),false)
				ENTITY::SET_ENTITY_COLLISION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),false),ENTITY::_0xCCF1E97BEFDAE480(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),false)),true);
				break;
			case 23:
				ENTITY::SET_ENTITY_VISIBLE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),false),!ENTITY::IS_ENTITY_VISIBLE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),false)));
				break;
			case 24:
				{
					int veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
					VEHICLE::_0xFDA7B6CA(veh, 0.0f, -9.0f, 10.0f);
				}
				break;
			case 25:
				STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("cargobob3"));
				STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("submersible"));
				VEHICLE::REQUEST_VEHICLE_ASSET(GAMEPLAY::GET_HASH_KEY("cargobob3"), 3);
				VEHICLE::REQUEST_VEHICLE_ASSET(GAMEPLAY::GET_HASH_KEY("submersible"), 3);
				VEHICLE::SET_VEHICLE_HAS_BEEN_OWNED_BY_PLAYER(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),false),true);
				VEHICLE::SET_VEHICLE_IS_STOLEN(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),false),false);
				print2("Set");
				break;
			case 26:break;//wheelie
			//case 27: VehicleMods::setVehicleOwnedByPlayer(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),false),PLAYER::PLAYER_ID());break;//steal control
			//case 28: STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"),0x7FFFFFFF,true);print2("yeet");break;
		}
		VehicleMods::getControlOfCurrentVehicle();
		addTitle("Vehicle Mods");
		//addSubmenuOption("Hydraulics",Hydroulics_Options);
		addOption(getCachedString("STR403"));   //Max Out Car
		addBoolOption(getCachedString("STR404"),VehicleMods::enabledgodmodeloop,"Constantly sets your car to godmode");   //Godmode
		//addOption("Set Vehicle Not Invincible");
		addOption(getCachedString("STR405"));   //Fix And Wash Vehicle
		addBoolOption(getCachedString("STR406"),VehicleMods::stickToGround);   //Stick To Ground
		addBoolOption(getCachedString("STR407"),VehicleMods::nfs);   //Need For Speed
		addFloatOption(getCachedString("STR837"),&VehicleMods::nfsSpeed,0,5,true,0.1f,0,true,true); //Need For Speed Speed
		addIntOption(getCachedString("STR408"),&VehicleMods::nfsmode,0,1,false);   //Need For Speed Mode
		addBoolOption(getCachedString("STR409"),VehicleMods::paradiseColorChanger);   //Paradise Style Rainbow Car
		addOption(getCachedString("STR410"));   //Raise Suspension
		addOption(getCachedString("STR411"));   //Lower Suspension
		vehicleGravity = getVehicleGravity(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),false));
		addFloatOption(getCachedString("STR412"),&vehicleGravity,-10000,10000,true,1,0,true);   //Gravity
		setVehicleGravity(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),false),vehicleGravity);
		addIntOption(getCachedString("STR413"),&currentVehicleWheel,0,3,false);   //Wheel To Modify
		
		addFloatOption(getCachedString("STR414"),&tmp1we,-50,50,true,0.1f,"Click to set value. 1.00 is default");   //Wheel Rotation Multiplier
		//tmp1we = getVehicleWheelRotMultiplier(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),false),currentVehicleWheel);
		//setVehicleWheelRotMultiplier(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),false),currentVehicleWheel,tmp1we);
		addOption(getCachedString("STR415"),"Idea from youtuber nHxModz");   //Negative Camber
		addOption(getCachedString("STR416"),"Idea from youtuber nHxModz");   //Positive Camber
		addOption(getCachedString("STR417"),"Idea from youtuber nHxModz");   //No Camber
		addBoolOption(getCachedString("STR418"),VehicleMods::squareDriftModBool);   //Square To Drift
		addOption(getCachedString("STR419"));   //Open All Doors
		addOption(getCachedString("STR420"));   //Close All Doors
		addBoolOption(getCachedString("STR421"),VehicleMods::matrixPlateBool);   //Matrix Plate
		addIntOption(getCachedString("STR422"),&vehicleLightIntensityVar,0,0x7fffffff,true,"Try super high values lol");//vehicle+0x520 float is light intensity   //Vehicle Light Intensity
		addBoolOption(getCachedString("STR423"),!ENTITY::_0xCCF1E97BEFDAE480(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),false)));   //Vehicle Collision
		addBoolOption(getCachedString("STR424"),ENTITY::IS_ENTITY_VISIBLE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),false)));   //Vehicle Visibility
		addOption(getCachedString("STR425"));   //Eject Seat
		addOption(getCachedString("STR426"));   //Special cargobob 3 and submarine
		addBoolOption(getCachedString("STR427"),&VehicleMods::wheelieEnabled,"Press L3 to wheelie");   //Wheelie
		//addOption("Take Ownership Of Vehicle","Currently buggy");
		//addOption("Set Stat Test");

		//addIntOption("Vehicle Light Intensity (test)",&vehicleLightIntensityVar,0,0xffff,true,"Try super high values lol");//vehicle+0x520 float is light intensity
		break;
#pragma endregion
#pragma region Hydroulics Options
		/*
	case Hydroulics_Options:
		VehicleMods::getControlOfCurrentVehicle();
		addTitle("Hydraulics");
		addBoolOption(getCachedString("STR427"),VehicleMods::wheelieEnabled,"Press L3 to wheelie");   //Wheelie
		addBoolOption(getCachedString("STR428"),VehicleMods::hydroulicsEnabled,"Use L1 + DPad to bounce");   //Low Rider Mode
		addIntOption(getCachedString("STR429"),&VehicleMods::hydroulicsPower,1,30,true);   //Hydraulics Power
		addFloatOption(getCachedString("STR430"),&VehicleMods::hydroulicsLowness,0,3,true);   //Hydraulics Lowness
		//addBoolOption("Constant Hydraulics",VehicleMods::hydroulicsConstant);
		//addOption("Toggle Hydaulics Type");
		addOption(getCachedString("STR431"));   //Disable Horn
		addOption(getCachedString("STR432"));   //Enable Horn

		switch(getOption()) {
			case 1: VehicleMods::wheelieEnabled = !VehicleMods::wheelieEnabled;break;
			case 2: VehicleMods::hydroulicsEnabled = !VehicleMods::hydroulicsEnabled;break;
			case 3: break;
			case 4: break;
			//case 5: VehicleMods::hydroulicsConstant = !VehicleMods::hydroulicsConstant;break;
			//case 6: VehicleMods::hydroulicsToggleSide();
			case 5: AUDIO::SET_HORN_ENABLED(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()),false);break;
			case 6: AUDIO::SET_HORN_ENABLED(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()),true);break;
		}
		break;*/
#pragma endregion
#pragma region Vehicle Mod Shop Colors
	case Vehicle_Modshop_Colors:
		VehicleMods::getControlOfCurrentVehicle();
		addTitle("Vehicle Colors");
		//VehicleMods::saveinsideofvehiclemenu();
		addIntOption(getCachedString("STR433"), &VehicleMods::Color1, 0, 160, true);   //Primary Color
		addIntOption(getCachedString("STR434"), &VehicleMods::Color2, 0, 160, true);   //Secondary Color
		addIntOption(getCachedString("STR435"), &VehicleMods::Color3, 0, 160, true);   //Pearlescent Color
		addIntOption(getCachedString("STR436"), &VehicleMods::Color4, 0, 160, true);   //Wheel Color
		VehicleMods::insideofvehiclemenu();
		break;
#pragma endregion
#pragma region Vehicle Modshop Colors RGB
	case Vehicle_Modshop_Colors_RGB:
		addTitle("RGB color");
		addIntOption(getCachedString("STR437"),&VehicleMods::rgbred,0,255,true);   //Red
		addIntOption(getCachedString("STR438"),&VehicleMods::rgbgreen,0,255,true);   //Green
		addIntOption(getCachedString("STR439"),&VehicleMods::rgbblue,0,255,true);   //Blue
		addOption(getCachedString("STR440"));   //Set Colors
		addOption(getCachedString("STR441"));   //Set Tire Smoke
		addOption(getCachedString("STR442"));   //Set Patriot Smoke
		switch(getOption()) {
		case 1: break;
		case 2: break;
		case 3: break;
		case 4: VehicleMods::setColorRGBCar(VehicleMods::rgbred,VehicleMods::rgbgreen,VehicleMods::rgbblue);
		case 5: VehicleMods::setTireSmokeColor(VehicleMods::rgbred,VehicleMods::rgbgreen,VehicleMods::rgbblue,false);
		case 6: VehicleMods::setTireSmokeColor(0,0,0,true);
		}
		break;
#pragma endregion
#pragma region Self Options
	case Self_Options:
		static float floatPlayerSpeed = 1;
		switch (getOption())
		{
		case 1: break;//animations menu
		case 2: break;//superhero options
		case 3: break;//name changer
		case 4: break;//model changer
		case 5: detachAllObjects();break;
		case 6: GodMode::toggleGodmode();break;//PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), !PLAYER::GET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID())); break;
		case 7:
			demiGodmode = !demiGodmode;
			//printf("0x%X 0x%X\n",getCObjFromIndex(PLAYER::PLAYER_PED_ID())->proofsBitset,getCObjFromIndex(PLAYER::PLAYER_PED_ID())->proofsBitsetByte);
			if (demiGodmode == false) {
				CObj *ptr = getCObjFromIndex(PLAYER::PLAYER_PED_ID());
				if (VALID_ADDR(ptr)) {
					ptr->health = 200.0f;//reset it
					ptr->maxHealth = 200.0f;
					//ptr->proofsBitset = 0x30000800;//0xFFFFFFFF & ~BIT_FROM_LEFT(8);//8 is player godmode
					//ptr->proofsBitsetByte = 0x6E;//0xFF;
				}
			}
			break;
		case 8:
			{
				CObj *ptr = getCObjFromIndex(PLAYER::PLAYER_PED_ID());
				if (VALID_ADDR(ptr)) {
					ptr->proofsBitset = 0xFFFFFFFF & ~BIT_FROM_LEFT(8);//8 is player godmode
					ptr->proofsBitsetByte = 0xFF;
				}
				print2("Change model to disable\n",20000);
			}
			break;
		case 9:  PlayerMods::togglerapidsetinvisible(); break;
		case 10: noclip::toggle();break;
		case 11: break;
		case 12: PlayerMods::wantedLevelEnabled = !PlayerMods::wantedLevelEnabled;break;
		case 13: PlayerMods::increaseFPS();break;
		case 14: PlayerMods::funnyScreenEnabled = !PlayerMods::funnyScreenEnabled; PlayerMods::funnyScreen(PlayerMods::funnyScreenEnabled);break;
		//case 11: break;
		case 15: firstPerson::toggle();break;
		case 16: break;//portal gun
		case 17: minecraft::enabled = !minecraft::enabled;break;
		case 18: break;
		case 19: ENTITY::SET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID(),bodyguard::playerAlpha,true);print("set alpha");break;
		case 20: PlayerMods::revengeEnabled = !PlayerMods::revengeEnabled;break;
		//case 17: PlayerMods::hulkBool = !PlayerMods::hulkBool;break;
		//case 18: rope::dospiderman = !rope::dospiderman;break;
		//case 19: input_disabled_bool = !input_disabled_bool;if (input_disabled_bool){write_process((char*)0x400D04,returntrue,8);write_process((char*)0x400C98,returntrue,8);}else {write_process((char*)0x400D04,DISABLE_CONTROL_ACTION_reenable,8);write_process((char*)0x400C98,SET_INPUT_EXCLUSIVE_reenable,8);}break;//removed because dumb people
		//case 20: PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(),223,!PED::GET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(),223,1));
			//Another way to do this would be to set 0x0123A3DC to be li %r4, 0 for off, li %r4, 1 for on (regularly r4 will become 0x80000000 when on), then modify flt_181AFE0 to be any scale value
		//	break;
		case 21: PlayerMods::toggleForceField(PLAYER::PLAYER_ID());break;
		case 22:
			//print("Currently not working because of 1.27 update. Please give me time to update");
			//break;
			dimensionsEnabled = !dimensionsEnabled;
			if (dimensionsEnabled) {
				write_process((char*)0x1555B50/*0x01555F70*/,nop_bytes,4);//not working. needs updated
			} else {
				write_process((char*)0x1555B50/*0x01555F70*/,playerdimensions_orig,4);
			}
			break;
		case 23: 
			*(volatile int*)0x424CF8 = (int)0x408f4000;//still works
			*(volatile int*)0x424CFC = (int)0x00000000;
			PLAYER::_0x825423C2(PLAYER::PLAYER_ID(),floatPlayerSpeed);
			break;
		case 24:
			PLAYER::_0x825423C2(PLAYER::PLAYER_ID(),1);
			break;
		case 25:
			//no water
			static unsigned int waterPoolAddress = *(volatile unsigned int*)0x21C8C48/*0x021C8848 old*/;
			for (unsigned int i = 0; i < 0x5994; i++)
				*(char*)(waterPoolAddress+i) = 0;
			break;
		case 26:
			//0x01284B30 = 38 60 00 00 4E 80 00 20 makes water not show up when underwater   7C 08 02 A6 31 81 FF E8 enable again
			fakeWater = !fakeWater;
			if (fakeWater) {
				char data[8] = {0x38, 0x60, 0x00, 0x00, 0x4E, 0x80, 0x00, 0x20};
				write_process((void*)(0x01284B30-0xe20),data,8);
			} else {
				char data[8] = {0x7C, 0x08, 0x02, 0xA6, 0x31, 0x81, 0xFF, 0xE8};
				write_process((void*)(0x01284B30-0xe20),data,8);
			}
			break;
		case 27:
			PlayerMods::allowRagdoll(false);
			print2("You can no longer ragdoll");
			break;
		case 28:
			PlayerMods::allowRagdoll(true);
			print2("You can now ragdoll");
			break;
		case 29:
			if (*(volatile int*)0x03D5F84 == 0xEC200029) {
				*(volatile int*)0x03D5F84 = 0xEC20082C;//set to normal
			} else {
				*(volatile int*)0x03D5F84 = 0xEC200029;//enably bypass
				//GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("prologue1");
			}
			break;
		case 30:
			jailMod::teleportToWardenLocation();
			break;
		case 31:
			//spoof into badsport lobbies
			*(volatile unsigned int*)(0x327728+0x0) = 0x38600001;
			*(volatile unsigned int*)(0x327728+0x4) = 0x4E800020;
			break;
		case 32:
			//spoof out of badsport lobbies
			*(volatile unsigned int*)(0x327728+0x0) = 0x38600000;
			*(volatile unsigned int*)(0x327728+0x4) = 0x4E800020;
			break;
		case 33:
			//spoof into cheater lobbies
			*(volatile unsigned int*)(0x12EE2FC+0x0) = 0x38600001;
			*(volatile unsigned int*)(0x12EE2FC+0x4) = 0x4E800020;
			break;
		case 34:
			//spoof out of cheater lobbies
			*(volatile unsigned int*)(0x12EE2FC+0x0) = 0x38600000;
			*(volatile unsigned int*)(0x12EE2FC+0x4) = 0x4E800020;
			break;
		//case 35:break;//this is for tutorial bypass
		case 35:
			if (I_AM_ONLINE) {
				call<int>(0x13596DC)();
				print2("Forced session update!",1000);
			}
			break;
		case 36:
			if (I_AM_ONLINE) {
				removeMyselfFromBadsport();
				print2("Removed from badsport!",2000);
			} else {
				print2("~r~Please go online to use this",2000);
			}
			break;
		case 37:
			/*
			//setNPType(true);
			*spoofNPTypeVal_ptr = 2;
			//patchTheRestOfJapaneese();
			print2("JP NP Servers Now On. Currently breaks matchmaking!\nYou must join a BLJM friend to get in a lobby!",10000);*/
			setBLJM(true);
			if (getFileSize("/dev_hdd0/tmp/gopro_2027/BLJM.rpf") != 90209280) {
				//file not proper, redownload
				downloadBLJMRPF = true;
			}
			else {
				//*spoofNPTypeVal_ptr = 2;
				print2("Restart game to be on BLJM (Japan) servers!",10000);
			}
			break;
		case 38:
			/*
			//setNPType(false);
			*spoofNPTypeVal_ptr = 1;
			//patchTheRestOfEuro();
			print2("EN NP Servers Now On");*/
			setBLJM(false);
			//*spoofNPTypeVal_ptr = 1;
			print2("Restart game to be on normal (EN NP) servers!", 10000);
			break;
		case 39: break;//skateboarding
		case 40:
			zombieOutbreak::toggle();
			break;
		case 41:break;//fix disable account
		case 42: PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(),223,!PED::GET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(),223,1));break;//toggle custom size
		case 43: break;//custom size float toggle
		case 44: GAMEPLAY::_0xDA02F415(1.0f); print2("Waves removed!"); break;//water intensity
		/*case 45:
			Write_Global(1592429+65012,0xFFFFFFFF);//1592429+65012
			print2("Set!\n");
			break;*/
		/*case 45:
			antiBan();
			print2("set anti ban");
			break;*/
			/*case 40:
			findGamersInit();
			print2("Started");
			break;
		case 41:
			findGamersStop();
			print2("Stopped");
			break;*/
		/*case 38:
			if (I_AM_ONLINE) {
				removeMyselfFromBadsport2();
				print2("Removed from badsport!",2000);
			} else {
				print2("~r~Please go online to use this",2000);
			}
			break;*/
		/*case 34:
			{
				unsigned int entid = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),false);
				unsigned int CNetObjAddress = getCNetObjFromEntityIndex(entid);
				char *className = getClassName(CNetObjAddress);
				unsigned int classAddress = *(volatile unsigned int*)CNetObjAddress;
				unsigned int model = ENTITY::GET_ENTITY_MODEL(entid);
				unsigned int vehicleType = *(volatile unsigned int*)(modelHashToAddress(model)+0x1B8);
				unsigned int CEntityAddress = getEntityFromIndex(entid);*/
				//printf("CNetObj: 0x%X CEntity: 0x%X\n",/*"Hash: 0x%X, Class: %s, Type: 0x%X, Class Address: 0x%X 0x%X\n",model,className,vehicleType,*/CNetObjAddress,CEntityAddress);
				/*unsigned int entid = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),false);
				unsigned int CEntityAddress = getEntityFromIndex(entid);
				unsigned int CNetObjAddress = getCNetObjFromEntityIndex(entid);
				printf("Vehicle CEntityAddress: 0x%X, CNetObjAddreess: 0x%X\n",CEntityAddress,CNetObjAddress);*/
			//}
			//break;
			//000000DA 00000003 06648E28 00000001 give player jobshare cash
		/*case 26:
			Write_Global(266957,2147483647);
			Write_Global(2411166,2147483647);
			break;*/

		/*case 25:
			//initWater(0);//resets water
			unsigned int waterPoolAddress1 = *(volatile unsigned int*)0x021C8848;
			if (doesFolderExist("/dev_hdd0/tmp/gopro_2027/tsunamiWater.bin"))
				readFile("/dev_hdd0/tmp/gopro_2027/tsunamiWater.bin",(char*)waterPoolAddress1,0x5994);
			else
				print2("~r~File Not Downloaded (Please go to paradisesprx.net for assistance)",2000);
			break;*/
		/*case 25:
			//initWater(0);//resets water
			unsigned int waterPoolAddress2 = *(volatile unsigned int*)0x021C8848;
			if (doesFolderExist("/dev_hdd0/tmp/gopro_2027/normalWater.bin"))
				readFile("/dev_hdd0/tmp/gopro_2027/normalWater.bin",(char*)waterPoolAddress2,0x5994);
			else
				print2("~r~File Not Downloaded (Please go to paradisesprx.net for assistance)",2000);
			break;*/
		//case 21:
			//for (int i = 0; i < 306; i++)
			//	Write_Global(1581767 + (PLAYER::PLAYER_ID() * 306)+i,1);
			//break;


		/*case 22:
			Write_Global(2394218+55,(int)999999999999999);//off radar time?
			Write_Global(2410912+4146,1);
			Write_Global(2390201+PLAYER::PLAYER_ID()*223+169,1);//170 is freeze?
			break;
		case 23:
			Write_Global(2394218+56,(int)999999999999999);
			Write_Global(2390201+PLAYER::PLAYER_ID()*223+172,1);
			break;*/
		/*case 17:
			write_process((char*)0x3B0088,returntrue,8);//ATTACH_ENTITY_TO_ENTITY disable             //original 7C 08 02 A6 31 81 FF E8
			write_process((char*)0x3B0390,returntrue,8);//ATTACH_ENTITY_TO_ENTITY_PHYSICALLY disable  //original 7C 08 02 A6 31 81 FF F0
			break;
		case 18:
			write_process((char*)0x3B0088,ATTACH_ENTITY_TO_ENTITY_reenable,8);//ATTACH_ENTITY_TO_ENTITY disable             //original 7C 08 02 A6 31 81 FF E8
			write_process((char*)0x3B0390,ATTACH_ENTITY_TO_ENTITY_PHYSICALLY_reenable,8);//ATTACH_ENTITY_TO_ENTITY_PHYSICALLY disable  //original 7C 08 02 A6 31 81 FF F0
			break;*/
		//case 17: noclip::grapplingHookEnabled = !noclip::grapplingHookEnabled;break;
		//case 17: char buf[10];snprintf$(buf,sizeof(buf),"%i",NETWORK::NETWORK_IS_HOST());print(buf);break;
		}
		addTitle("Self Options");
		addSubmenuOption(getCachedString("STR443"),Animation_Options);   //Animations
		addSubmenuOption(getCachedString("STR444"),Superhero_Options);   //Superheros
		addSubmenuOption(getCachedString("STR445"),Name_Change_Options);   //Name Changer
		addSubmenuOption(getCachedString("STR446"),Model_Menu);   //Model Changer
		addOption(getCachedString("STR447"));   //Detach All Objects From You
		addBoolOption(getCachedString("STR448"), PLAYER::GET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID()));   //Godmode
		addBoolOption(getCachedString("STR449"),demiGodmode,"Detected by some mod menus, use health regen");   //Undetectable Godmode
		//addOption("Undetectable Godmode V2","The only way to turn off is to change your model");
		addBoolOption("Health Regen",&healthRegen,"Regens health automatically");
		addBoolOption(getCachedString("STR450"), PlayerMods::rapidsetinvisible);   //Invisibility
		addBoolOption(getCachedString("STR451"),noclip::enabled,"Press R3 To Fly. Also Enable With R1+DpadLeft");   //Noclip
		addFloatOption(getCachedString("STR452"),&noclip::speed,0.01f,5,true,0.05f,0,true,false);   //Noclip Speed
		addBoolOption(getCachedString("STR453"),PlayerMods::wantedLevelEnabled);   //No Cops
		addBoolOption(getCachedString("STR454"),PlayerMods::increaseFPSBool);   //Remove Lights
		addBoolOption(getCachedString("STR455"),PlayerMods::funnyScreenEnabled,"Big Guns Also"/*"Big Guns Also (~r~POSSIBLE FREEZE WARNING~s~)"*/);   //Funny Screen
		//MODEL CHANGER USED TO BE HERE
		addBoolOption(getCachedString("STR456"),firstPerson::enabled);   //First Person
		addBoolOption(getCachedString("STR457"),&portalGun::enabled,"Shoot to spawn/delete portal, r1 to swap portal");   //Portal Gun
		addBoolOption(getCachedString("STR458"),minecraft::enabled,"Aim and press L1 to place, R1 to break");   //Minecraft
		addIntOption(getCachedString("STR459"),&minecraft::clipDistance,0,20,false);   //Minecraft Reach Distance
		addIntOption(getCachedString("STR460"),&bodyguard::playerAlpha,0,255,true);   //Player Opacity
		addBoolOption(getCachedString("STR461"),PlayerMods::revengeEnabled,"Nobody can shoot you or death");   //Revenge
		
		//addBoolOption("Allow Shooting In Garage",input_disabled_bool,"WARNING: Makes phone show up in menu");
		//addBoolOption(getCachedString("STR462")/*,&PlayerMods::shrinkSize,-100,100,false*/,PED::GET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(),223,1));   //Shrink
		addBoolOption(getCachedString("STR463"),PlayerMods::getForceField(PLAYER::PLAYER_ID()));   //Forcefield
		addBoolOption(getCachedString("STR464"),dimensionsEnabled);   //2D Mode
		addFloatOption(getCachedString("STR465"),&floatPlayerSpeed,0,500,true,0.1,"Click to set speed",true);   //Super Speed Test
		addOption(getCachedString("STR466"));   //Reset Super Speed
		addOption(getCachedString("STR467"),"Best for exploring. ~r~IRREVERSABLE");   //No Water
		addBoolOption(getCachedString("STR468"),fakeWater,"Shows water but it's not actually there");   //'Fake' Water
		addOption(getCachedString("STR469"));   //No Ragdoll ON
		addOption(getCachedString("STR470"));   //No Ragdoll OFF
		
		addBoolOption(getCachedString("STR471"),*(volatile int*)0x03D5F84 == 0xEC200029,"Lets you teleport to the main map without the mission restarting in prologue.");   //Bypass Prologue Distance Check
		addOption(getCachedString("STR472"));   //Teleport To Jail Cells
		addOption(getCachedString("STR473"),"This will NOT save to your account");   //Spoof Into Badsport Lobbies
		addOption(getCachedString("STR474"),"This will NOT save to your account");   //Spoof Out Of Badsport Lobbies
		addOption(getCachedString("STR475"),"This will NOT save to your account");   //Spoof Into Cheater Lobbies
		addOption(getCachedString("STR476"),"This will NOT save to your account");   //Spoof Out Of Cheater Lobbies
		//addBoolOption(getCachedString("STR477"),TUTORIALBYPASSSAFE,"Enable when in prologue then disable when you get to MP");   //GTA Online Tutorial Bypass
		addOption(getCachedString("STR478"));   //Force Session Update
		addOption(getCachedString("STR479"),"Permanent, unlike spoof");   //Remove Account From Badsport
		//addOption("blah blah test");
		addOption(getCachedString("STR480"),"On first click, will download an RPF BLJM.rpf to gopro_2027 folder!");   //Spoof To JP Servers
		addOption(getCachedString("STR481"));   //Spoof To English Servers
		addBoolOption(getCachedString("STR838"),&skateboard::skateboardingEnabled,"X Go, R1 Jump, Square/Circle/L3 Tricks"); //Skateboarding Skateboard Mode 
		addBoolOption(getCachedString("STR844"),zombieOutbreak::enabled);//Zombie Outbreak
		addBoolOption(getCachedString("STR845"),&runFixDisableAccount,"Enable when in singleplayer, go to character selection then press L3 to do it");//Fix Disable Account
		addBoolOption("Toggle Custom Player Size"/*getCachedString("STR462")*//*,&PlayerMods::shrinkSize,-100,100,false*/,PED::GET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(),223,1));   //Shrink
		addFloatOption("Player Size",playerSizeFloat,-20.0f,100.0f,true,0.1f,"Must have toggle custom player size enabled",true,true);
		addOption("Flat Ocean");
		//addOption("Add IPL's to job","For in job creator");
		//addOption("Anti ban");
		//addOption(getCachedString("STR482"));   //Start Finding
		//addOption(getCachedString("STR483"));   //Stop Finding
		//addOption("Get Vehile Info");
		//addOption("Bypass $20,000 jobshare cash limit","If it says you have to do a job first, drop ");//2410912+254 is percentage
		//addOption("Tsunami Water");
		//addOption("Normal Water");
		//addOption("Test");
		//addOption("Off Radar");
		//addOption("Show Players");
		//ALL THOSE ABOVE WERE TAKEN OFF TEMPORARILY


		//addIntOption("Aimbot Mode",&camShit::aimbot::aimbotMode,0,5,false);
		//addSubmenuOption("Name Changer Menu",Name_Change_Options);
		//addBoolOption("Grappling Hook",noclip::grapplingHookEnabled,"Press R3");
		//addOption("Disable People Attaching Objects");
		//addOption("Enable People Attaching Objects");
		//addOption("Am I Host?");
		//PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(),223,PlayerMods::shrinkSize);
		break;
#pragma endregion
#pragma region Name_Change_Options
	case Name_Change_Options:
		switch(getOption()) {
		case 2: break;//keyboard//http://pastebin.com/nqNYWMSB pastebin link
		case 3: if (strlen(PlayerMods::myName)>62)break;strcat(PlayerMods::myName,"~");break;
		case 4: if (strlen(PlayerMods::myName)>60)break;strcat(PlayerMods::myName,"~h~");break;

		case 5: if (strlen(PlayerMods::myName)>50)break;strcat(PlayerMods::myName,"~BLIP_RP~");break;
		case 6: if (strlen(PlayerMods::myName)>60)break;strcat(PlayerMods::myName,"~r~");break;
		case 7: if (strlen(PlayerMods::myName)>60)break;strcat(PlayerMods::myName,"~g~");break;
		case 8: if (strlen(PlayerMods::myName)>60)break;strcat(PlayerMods::myName,"~b~");break;
		case 9: if (strlen(PlayerMods::myName)>60)break;strcat(PlayerMods::myName,"~y~");break;
		case 10: if (strlen(PlayerMods::myName)>60)break;strcat(PlayerMods::myName,"~p~");break;
		case 11: if (strlen(PlayerMods::myName)>60)break;strcat(PlayerMods::myName,"~o~");break;
		case 12: if (strlen(PlayerMods::myName)>60)break;strcat(PlayerMods::myName,"~c~");break;
		case 13: if (strlen(PlayerMods::myName)>60)break;strcat(PlayerMods::myName,"~m~");break;
		case 14: if (strlen(PlayerMods::myName)>60)break;strcat(PlayerMods::myName,"~u~");break;
		case 15: if (strlen(PlayerMods::myName)>60)break;strcat(PlayerMods::myName,"~s~");break;


		case 16: for (int i = 0; i < 64; i++)
					if (PlayerMods::myName[i] == '-')
						PlayerMods::myName[i] = '~';
				break;

				{
					static char star[4] = {0xEF, 0x91, 0xB6, 0x20};
					static char fire[4] = {0xEF, 0x91, 0xB7, 0x20};
					static char expl[4] = {0xEF, 0x91, 0xAE, 0x20};
		case 17: write_process(PlayerMods::myName+strlen(PlayerMods::myName),star,4);break;
		case 18: write_process(PlayerMods::myName+strlen(PlayerMods::myName),fire,4);break;
		case 19: write_process(PlayerMods::myName+strlen(PlayerMods::myName),expl,4);break;
				}
		case 20: for (int i = 0; i < 64; i++)
					PlayerMods::myName[i] = 0;
				break;
		case 21: PlayerMods::changeName(PlayerMods::myName);break;
		case 22: PlayerMods::changeNamePSN(PlayerMods::myName);break;
		}
		//char buf2023[64];
		//snprintf$(buf2023,64,"Currently Editing: %s",PlayerMods::myName);
		addTitle("Name Changer");
		addOption(PlayerMods::myName/*buf2023*/);
		addKeyboardOption(getCachedString("STR484"),Keyboard_Change_Name,keyboardText,120,"Enter text");   //Add Text
		addOption(getCachedString("STR485"));   //Add ~~
		addOption(getCachedString("STR486"));   //Bold
		addOption(getCachedString("STR487"));//~BLIP_RP~   //Tiny Name
		addOption(getCachedString("STR488"),"For more colors visit http://pastebin.com/nqNYWMSB");   //Add Red
		addOption(getCachedString("STR489"),"For more colors visit http://pastebin.com/nqNYWMSB");   //Add Green
		addOption(getCachedString("STR490"),"For more colors visit http://pastebin.com/nqNYWMSB");   //Add Blue
		addOption(getCachedString("STR491"),"For more colors visit http://pastebin.com/nqNYWMSB");   //Add Yellow
		addOption(getCachedString("STR492"),"For more colors visit http://pastebin.com/nqNYWMSB");   //Add Purple
		addOption(getCachedString("STR493"),"For more colors visit http://pastebin.com/nqNYWMSB");   //Add Orange
		addOption(getCachedString("STR494"),"For more colors visit http://pastebin.com/nqNYWMSB");   //Add Grey
		addOption(getCachedString("STR495"),"For more colors visit http://pastebin.com/nqNYWMSB");   //Add Dark Grey
		addOption(getCachedString("STR496"),"For more colors visit http://pastebin.com/nqNYWMSB");   //Add Black
		addOption(getCachedString("STR497"),"For more colors visit http://pastebin.com/nqNYWMSB");   //Add White
		addOption(getCachedString("STR498"));   //Replace All '-' with '~~'
		addOption(getCachedString("STR499"));   //Add Stars (PSN Only)
		addOption(getCachedString("STR500"));   //Add Fire (PSN Only)
		addOption(getCachedString("STR501"));   //Add Explosion (PSN Only)
		addOption(getCachedString("STR502"));   //Clear Name
		addOption(getCachedString("STR503"));   //Save Changes (GTA)
		addOption(getCachedString("STR504"),"Special steps required to work correctly");   //Save Changes (PSN)
		break;
#pragma endregion
#pragma region Text Message Extra Options
	case Text_Message_Options:
		static int playerSpoofAs = 0;
		switch(getOption()) {
		case 2: break;//keyboard//http://pastebin.com/nqNYWMSB pastebin link
		case 3: if (strlen(PlayerMods::myText)>62)break;strcat(PlayerMods::myText,"~");break;
		case 4: if (strlen(PlayerMods::myText)>60)break;strcat(PlayerMods::myText,"~h~");break;
		case 5: if (strlen(PlayerMods::myText)>40)break;strcat(PlayerMods::myText,"<font size='49'>");break;//<font size='49'>
		case 6: if (strlen(PlayerMods::myText)>62)break;strcat(PlayerMods::myText,"\n");break;
		case 7: if (strlen(PlayerMods::myText)>60)break;strcat(PlayerMods::myText,"~r~");break;
		case 8: if (strlen(PlayerMods::myText)>60)break;strcat(PlayerMods::myText,"~g~");break;
		case 9: if (strlen(PlayerMods::myText)>60)break;strcat(PlayerMods::myText,"~b~");break;
		case 10: if (strlen(PlayerMods::myText)>60)break;strcat(PlayerMods::myText,"~y~");break;
		case 11: if (strlen(PlayerMods::myText)>60)break;strcat(PlayerMods::myText,"~p~");break;
		case 12: if (strlen(PlayerMods::myText)>60)break;strcat(PlayerMods::myText,"~o~");break;
		case 13: if (strlen(PlayerMods::myText)>60)break;strcat(PlayerMods::myText,"~c~");break;
		case 14: if (strlen(PlayerMods::myText)>60)break;strcat(PlayerMods::myText,"~m~");break;
		case 15: if (strlen(PlayerMods::myText)>60)break;strcat(PlayerMods::myText,"~u~");break;
		case 16: if (strlen(PlayerMods::myText)>60)break;strcat(PlayerMods::myText,"~s~");break;

		case 17: if (strlen(PlayerMods::myText)>60)break;strcat(PlayerMods::myText,"<");break;
		case 18: if (strlen(PlayerMods::myText)>60)break;strcat(PlayerMods::myText,">");break;
		case 19: if (strlen(PlayerMods::myText)>60)break;strcat(PlayerMods::myText,"/");break;
		case 20: if (strlen(PlayerMods::myText)>60)break;strcat(PlayerMods::myText,"'");break;
		case 21: if (strlen(PlayerMods::myText)>60)break;strcat(PlayerMods::myText,"\"");break;
		case 22: if (strlen(PlayerMods::myText)>60)break;strcat(PlayerMods::myText,"=");break;
		case 23: if (strlen(PlayerMods::myText)>60)break;strcat(PlayerMods::myText,"$");break;
		case 24: if (strlen(PlayerMods::myText)>60)break;strcat(PlayerMods::myText,"_");break;
		case 25: if (strlen(PlayerMods::myText)>60)break;strcat(PlayerMods::myText,"¦");break;
		case 26: if (strlen(PlayerMods::myText)>60)break;strcat(PlayerMods::myText,"÷");break;
		case 27: if (strlen(PlayerMods::myText)>60)break;strcat(PlayerMods::myText,"∑");break;

		case 28: for (int i = 0; i < 64; i++)
					if (PlayerMods::myText[i] == '-')
						PlayerMods::myText[i] = '~';
				break;
		case 29:
			if (strlen(PlayerMods::myText)>52)break;
			{
				//static char buf[55];
				snprintf(global_temporary_buf,sizeof(global_temporary_buf),"<img src='wanted_star' width='%i' height='%i'/>",PlayerMods::myTextStarInt,PlayerMods::myTextStarInt);
				strcat(PlayerMods::myText, global_temporary_buf);break;
			}
			break;
		case 30: for (int i = 0; i < 64; i++)
					PlayerMods::myText[i] = 0;
				break;
		case 31: PlayerMods::msg(PlayerMods::myText,selectedPlayer,true);break;
		case 32: PlayerMods::notify(PlayerMods::myText,selectedPlayer,true);break;
		case 33: PlayerMods::sendSpoofedText(PlayerMods::myText,selectedPlayer,playerSpoofAs,true);break;
		case 34: for(int i = 0; i < 18; i++)PlayerMods::sendSpoofedText(PlayerMods::myText,i,playerSpoofAs,true);break;
		//case 31: PlayerMods::msg((char*)0x10070400,selectedPlayer,true);break;//<img src='wanted_star' width='0750' height='0999'>
		//case 32: PlayerMods::msg("<img src='wanted_star'width='750'height='999'>",selectedPlayer,true);break;
		}
		//char buf2023[64];
		//snprintf$(buf2023,64,"Currently Editing: %s",PlayerMods::myText);
		addTitle("Text Messager");
		addOption(PlayerMods::myText);
		addKeyboardOption(getCachedString("STR505"),Keyboard_Text_Messager,keyboardText,120,"Enter text");   //Add Text
		addOption(getCachedString("STR506"));   //Add ~~
		addOption(getCachedString("STR507"));   //Bold
		addOption(getCachedString("STR508"),"Add this to the beginning of the text");   //Big Text
		addOption(getCachedString("STR509"));   //Add New Line
		addOption(getCachedString("STR510"),"For more colors visit http://pastebin.com/nqNYWMSB");   //Add Red
		addOption(getCachedString("STR511"),"For more colors visit http://pastebin.com/nqNYWMSB");   //Add Green
		addOption(getCachedString("STR512"),"For more colors visit http://pastebin.com/nqNYWMSB");   //Add Blue
		addOption(getCachedString("STR513"),"For more colors visit http://pastebin.com/nqNYWMSB");   //Add Yellow
		addOption(getCachedString("STR514"),"For more colors visit http://pastebin.com/nqNYWMSB");   //Add Purple
		addOption(getCachedString("STR515"),"For more colors visit http://pastebin.com/nqNYWMSB");   //Add Orange
		addOption(getCachedString("STR516"),"For more colors visit http://pastebin.com/nqNYWMSB");   //Add Grey
		addOption(getCachedString("STR517"),"For more colors visit http://pastebin.com/nqNYWMSB");   //Add Dark Grey
		addOption(getCachedString("STR518"),"For more colors visit http://pastebin.com/nqNYWMSB");   //Add Black
		addOption(getCachedString("STR519"),"For more colors visit http://pastebin.com/nqNYWMSB");   //Add White
		addOption(getCachedString("STR520"));   //Add <
		addOption(getCachedString("STR521"));   //Add >
		addOption(getCachedString("STR522"));   //Add /
		addOption(getCachedString("STR523"));   //Add '
		addOption(getCachedString("STR524"));   //Add \"
		addOption(getCachedString("STR525"));   //Add =
		addOption(getCachedString("STR526"));   //Add $
		addOption(getCachedString("STR527"));   //Add _
		addOption(getCachedString("STR528"));   //Add ¦
		addOption(getCachedString("STR529"));   //Add ÷
		addOption(getCachedString("STR530"));   //Add ∑
		addOption(getCachedString("STR531"));   //Replace All '-' with '~~'
		addIntOption(getCachedString("STR532"),true,5,&PlayerMods::myTextStarInt,1,9999,true,"A graphical star");   //Add Star Of Size
		addOption(getCachedString("STR533"));   //Clear Text
		addOption(getCachedString("STR534"));   //Send Text
		addOption(getCachedString("STR535"));   //Send Text Spoofed As Them
		static char *playerArr[18];
		playerArr[playerSpoofAs] = PLAYER::GET_PLAYER_NAME(playerSpoofAs);
		addArrayOption(getCachedString("STR536"),&playerSpoofAs,playerArr,18);   //Send Text Spoofed As Player
		addArrayOption(getCachedString("STR537"),&playerSpoofAs,playerArr,18,"This option completely ignores the currently selected player you are on");   //Send To Lobby Spoofed As Player
		//addOption("Send Text At 0x10070400","Write the text in mem through rtm");//<img src='wanted_star'width='750'height='999'>
		//addOption("Test");
		drawPlayerInfo();
		break;
#pragma endregion
#pragma region Superhero Options
	case Superhero_Options:
		switch(getOption()) {
			//case 1: PlayerMods::hulkBool = !PlayerMods::hulkBool;break;
			case 1: rope::dospiderman = !rope::dospiderman;
				if(!rope::dospiderman) {
					if (ENTITY::DOES_ENTITY_EXIST(rope::lastspiderobject))
						forge::markEntityForDeletion(rope::lastspiderobject);
					if (ROPE::DOES_ROPE_EXIST(&rope::spiderweb))
						ROPE::DELETE_ROPE(&rope::spiderweb);
				}
				break;
		}
		addTitle("Superheros");
		//addBoolOption(getCachedString("STR538"),PlayerMods::hulkBool,"Super speed and super jump!");   //Hulk
		addBoolOption(getCachedString("STR539"),rope::dospiderman,"Press R2 to shoot webs~n~Press L2 to break your current web~n~Jump once and shoot a web to start!");   //Spiderman
		break;
#pragma endregion
#pragma region Weapon Options
	case Weapon_Options:
		switch(getOption())
		{
		case 1: weaponMods::toggleOneShotOneKill();break;
		case 2: PlayerMods::enabledVehicleGun = !PlayerMods::enabledVehicleGun;break;
		//case 3: forge::forceGun = !forge::forceGun;break;
		case 3: weaponMods::infiniteAmmo(PLAYER::PLAYER_ID());break;
		case 4: PlayerMods::togglePlayerAimbot(PLAYER::PLAYER_ID());break;
		/*case 5: bouncyRpgRockets = !bouncyRpgRockets;
				if (bouncyRpgRockets) {
					write_process((char*)(0xFF4C38-0xe20),returnfalse,8);
				} else {
					write_process((char*)(0xFF4C38-0xe20),DUMMY_RPG_reenable,8);
				}
				break;*/
		case 5: WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::PLAYER_PED_ID(),true);break;
		case 6: PlayerMods::giveAllWeaponsToPlayer(PLAYER::PLAYER_ID());break;
		case 7: camShit::resetCam();break;//cool rockets
		case 8: break;//hd rockets
		case 9: break;//animepunch_bool
		/*case 7: camShit::aimbot::enabled = !camShit::aimbot::enabled;break;
		case 8: camShit::aimbot::needVisibility = !camShit::aimbot::needVisibility;break;
		//case 22: break;//aimbot configurations
		case 9: camShit::aimbot::pedmode = !camShit::aimbot::pedmode;break;
		case 10: camShit::aimbot::aimOnly = !camShit::aimbot::aimOnly;break;*/
			/*
		case 12: setCurrentWeaponType(1);break;
		case 13: setCurrentWeaponType(2);break;
		case 14: setCurrentWeaponType(3);break;
		case 15: setCurrentWeaponType(5);break;
		case 16: setCurrentWeaponType(6);break;
		case 17: setCurrentWeaponType(8);break;
		case 18: setCurrentWeaponType(10);break;
		case 19: setCurrentWeaponType(11);break;
		case 20: setCurrentWeaponType(12);break;
		case 21: setCurrentWeaponType(13);break;
		case 22: setCurrentWeaponType(14);break;*/
		}
		addTitle("Weapon Options");
		addBoolOption(getCachedString("STR540"),weaponMods::osok);   //One Shot One Kill
		addBoolOption(getCachedString("STR541"),PlayerMods::enabledVehicleGun);   //Vehicle Gun
		//addBoolOption("Force Gun",forge::forceGun);
		addBoolOption(getCachedString("STR542"),weaponMods::infiniteAmmoBool[PLAYER::PLAYER_ID()]);   //Infinite Ammo
		addBoolOption(getCachedString("STR543"),PlayerMods::isAimbotEnabled(PLAYER::PLAYER_ID()),"Works like Curved Bullets type aimbot");   //Aimbot
		//addBoolOption("Bouncy RPG Rockets",bouncyRpgRockets);
		addOption(getCachedString("STR544"));   //Remove All Weapons
		addOption(getCachedString("STR545"));   //Give All Weapons
		addBoolOption("Cool Rockets",&coolRockets,"Shoot a rocket launcher type weapon");
		addBoolOption("HD Cool Rockets",&coolRocketsHD,"HD will cause a bit of lag, but work better");
		addBoolOption("Anime Punch",&animepunch_bool);

		/*addBoolOption("Aimbot",camShit::aimbot::enabled,"~r~Must enable first person too!");
		addBoolOption(getCachedString("STR546"),camShit::aimbot::needVisibility,"Target has to be in sight when enabled",false);   //Stealth Aimbot
		//not used my dude addIntOption("Aimbot Mode",&camShit::aimbot::aimbotMode,0,5,false);
		addBoolOption(getCachedString("STR547"),camShit::aimbot::pedmode,"When unchecked, aim to players",false);   //Ped Mode
		addBoolOption(getCachedString("STR548"),camShit::aimbot::aimOnly,"Must aim for aimbot to take effect",false);*/   //Require Aiming
		/*
		addOption(getCachedString("STR549"));   //Shooting Type: No Damage
		addOption(getCachedString("STR550"));   //Shooting Type: Melee
		addOption(getCachedString("STR551"));   //Shooting Type: Bullet
		addOption(getCachedString("STR552"));   //Shooting Type: Explosive
		addOption(getCachedString("STR553"));   //Shooting Type: Fire
		addOption(getCachedString("STR554"));   //Shooting Type: Fall
		addOption(getCachedString("STR555"));   //Shooting Type: Electric
		addOption(getCachedString("STR556"));   //Shooting Type: Barbed Wire
		addOption(getCachedString("STR557"));   //Shooting Type: Extinguisher
		addOption(getCachedString("STR558"));   //Shooting Type: Gas
		addOption(getCachedString("STR559"));*/   //Shooting Type: Water Cannon
		break;
#pragma endregion
#pragma region Model Menu
	case Model_Menu:
		addTitle("Change Model");
		addOption(getCachedString("STR560"));   //Alien
		addOption(getCachedString("STR561"));   //Police
		addOption(getCachedString("STR562"));   //Marine
		addOption(getCachedString("STR563"));   //Jesus
		addOption(getCachedString("STR564"));   //Hacker
		addOption(getCachedString("STR565"));   //Gross Dude
		addOption(getCachedString("STR566"));   //Body Builder
		addOption(getCachedString("STR567"));   //Fat Lady
		addOption(getCachedString("STR568"));   //Skinny Lady
		addOption(getCachedString("STR569"));   //Male Character
		addOption(getCachedString("STR570"));   //Female Character
		//addOption("Components");
		addKeyboardOption(getCachedString("STR571"),7,keyboardText,120,"Enter model");   //Custom Input
		switch(getOption()) {
		case 1: PlayerMods::changeModelNow("s_m_m_movalien_01");break;//Alien
		case 2: PlayerMods::changeModelNow("s_m_y_cop_01");break;//Police
		case 3: PlayerMods::changeModelNow("s_m_y_marine_01");break;//Marine
		case 4: PlayerMods::changeModelNow("u_m_m_jesus_01");break;//Jesus
		case 5: PlayerMods::changeModelNow("hc_hacker");break;//Hacker
		case 6: PlayerMods::changeModelNow("a_m_y_acult_01");break;//Gross Dude
		case 7: PlayerMods::changeModelNow("a_f_m_bodybuild_01");break;//Body Builder
		case 8: PlayerMods::changeModelNow("a_f_m_fatwhite_01");break;//Fat Lady
		case 9: PlayerMods::changeModelNow("a_f_y_topless_01");break;//Skinny Lady
		case 10: PlayerMods::changeModelNow("mp_m_freemode_01"/*,PlayerMods::components::myComponents::load*/);break;
		case 11: PlayerMods::changeModelNow("mp_f_freemode_01"/*,PlayerMods::components::myComponents::load*/);break;
		//case 12: changeSubmenu(Self_Options_Components_List);break;
		case 12: break;
		}
		break;
#pragma endregion
/*#pragma region Self Options Components
	case Self_Options_Components:
		char compbufff[30];
		snprintf$(compbufff,sizeof(compbufff),"Component %s",PlayerMods::components::getComponentName());
		addTitle(compbufff);
		addOption(getCachedString("STR572"));   //Texture + 1
		addOption(getCachedString("STR573"));   //Texture - 1
		//addOption("Drawable + 1");
		//addOption("Drawable - 1");
		addOption(getCachedString("STR574"));   //Drawable + 1
		addOption(getCachedString("STR575"));   //Drawable - 1
		drawComponentInfo();
		switch(getOption()) {
		case 1: PlayerMods::components::textureAdd();break;
		case 2: PlayerMods::components::textureMinus();break;
		//case 3: PlayerMods::components::drawableAdd();break;
		//case 4: PlayerMods::components::drawableMinus();break;
		case 3: PlayerMods::components::drawableAdd();break;
		case 4: PlayerMods::components::drawableMinus();break;
		}
		break;
#pragma endregion*/
/*#pragma region Self Options Components List
	case Self_Options_Components_List:
		addTitle("Components");
		addOption(getCachedString("STR576"));   //Save Component Set
		addOption(getCachedString("STR577"));   //Load Component Set
		for (int i = 0; i < 12; i++) {
			addOption(PlayerMods::components::getComponentName(i));
			if (getOption() == i+3) {
				PlayerMods::components::currentComponent = i;
				changeSubmenu(Self_Options_Components);
			}
		}
		switch(getOption()) {
		case 1: PlayerMods::components::myComponents::save();break;
		case 2: PlayerMods::components::myComponents::load(0);break;
		}
		break;
#pragma endregion*/
#pragma region Vehicle_Spawner_Main
	case Vehicle_Spawner_Main:
		addTitle("Spawn Options");
		addSubmenuOption(getCachedString("STR578"),Vehicle_Spawner_Main_All);   //Vehicle List
		addKeyboardOption(getCachedString("STR579"),2,keyboardText,120,"Enter vehicle");   //Spawn Custom Vehicle
		addBoolOption(getCachedString("STR580"),VehicleMods::spawnInsideOfCar);   //Spawn Inside Of Car
		addBoolOption(getCachedString("STR581"),VehicleMods::spawnAsMaxed);   //Spawn Maxed
		addFloatOption(getCachedString("STR582"),&VehicleMods::spawnGravity,-10,10,true,0.1,"Shows to other players. Default: 9.8",true);   //Spawn Gravity
		addFloatOption(getCachedString("STR583"),&VehicleMods::spawnSuspension,-10,10,true,0.1,"Shows to other players. Default: 0",true);   //Spawn Suspension
		#if DOAUTH == 0
		addIntOption(getCachedString("STR584"),&spawnModifiedVehicleTypee,0,7,false,"Model Type Changes.");   //Spawn Modified Vehicle
		#endif
		//addOption("Spawn Random Vehicle");
		switch(getOption()) {
		case 1: break;
		case 2: break;
		//case 3: VehicleMods::randomCarSpawn();break;
		case 3: VehicleMods::spawnInsideOfCar = !VehicleMods::spawnInsideOfCar;break;
		case 4: VehicleMods::spawnAsMaxed = !VehicleMods::spawnAsMaxed;break;
		#if DOAUTH == 0
		case 7: startKeyboard(spawn_modified_vehicle_keyboard, keyboardText, 100,"lksdfg");break;
		#endif
		}
		break;
#pragma endregion
#pragma region Vehicle Spawner Main All
	case Vehicle_Spawner_Main_All:
		switch(getOption()) {
		case 1:VehicleMods::spawnVehicle(VehicleMods::g_uiSuperCars[VehicleMods::g_pcSuperCarsInt],VehicleMods::returnFuncToSpawnInsideVehicle);break;
		case 2:VehicleMods::spawnVehicle(VehicleMods::g_uiSportsCars[VehicleMods::g_pcSportsCarsInt],VehicleMods::returnFuncToSpawnInsideVehicle);break;
		case 3:VehicleMods::spawnVehicle(VehicleMods::g_uiSportsClassicCars[VehicleMods::g_pcSportsClassicCarsInt],VehicleMods::returnFuncToSpawnInsideVehicle);break;
		case 4:VehicleMods::spawnVehicle(VehicleMods::g_uiMuscleCars[VehicleMods::g_pcMuscleCarsInt],VehicleMods::returnFuncToSpawnInsideVehicle);break;
		case 5:VehicleMods::spawnVehicle(VehicleMods::g_uiSedans[VehicleMods::g_pcSedansInt],VehicleMods::returnFuncToSpawnInsideVehicle);break;
		case 6:VehicleMods::spawnVehicle(VehicleMods::g_uiCoupes[VehicleMods::g_pcCoupesInt],VehicleMods::returnFuncToSpawnInsideVehicle);break;
		case 7:VehicleMods::spawnVehicle(VehicleMods::g_uiCompacts[VehicleMods::g_pcCompactsInt],VehicleMods::returnFuncToSpawnInsideVehicle);break;
		case 8:VehicleMods::spawnVehicle(VehicleMods::g_uiSUVnTrucks[VehicleMods::g_pcSUVnTrucksInt],VehicleMods::returnFuncToSpawnInsideVehicle);break;
		case 9:VehicleMods::spawnVehicle(VehicleMods::g_uiOffRoads[VehicleMods::g_pcOffRoadsInt],VehicleMods::returnFuncToSpawnInsideVehicle);break;
		case 10:VehicleMods::spawnVehicle(VehicleMods::g_uiVans[VehicleMods::g_pcVansInt],VehicleMods::returnFuncToSpawnInsideVehicle);break;
		case 11:VehicleMods::spawnVehicle(VehicleMods::g_uiEmergencyCars[VehicleMods::g_pcEmergencyCarsInt],VehicleMods::returnFuncToSpawnInsideVehicle);break;
		case 12:VehicleMods::spawnVehicle(VehicleMods::g_uiServicVehicles[VehicleMods::g_pcServiceVehiclesInt],VehicleMods::returnFuncToSpawnInsideVehicle);break;
		case 13:VehicleMods::spawnVehicle(VehicleMods::g_uiMilitary[VehicleMods::g_pcMilitaryInt],VehicleMods::returnFuncToSpawnInsideVehicle);break;
		case 14:VehicleMods::spawnVehicle(VehicleMods::g_uiMotorcycles[VehicleMods::g_pcMotorcyclesInt],VehicleMods::returnFuncToSpawnInsideVehicle);break;
		case 15:VehicleMods::spawnVehicle(VehicleMods::g_uiBicycles[VehicleMods::g_pcBicyclesInt],VehicleMods::returnFuncToSpawnInsideVehicle);break;
		case 16:VehicleMods::spawnVehicle(VehicleMods::g_uiCommercialVehicles[VehicleMods::g_pcCommercialVehiclesInt],VehicleMods::returnFuncToSpawnInsideVehicle);break;
		case 17:VehicleMods::spawnVehicle(VehicleMods::g_uiHelicopters[VehicleMods::g_pcHelicoptersInt],VehicleMods::returnFuncToSpawnInsideVehicle);break;
		case 18:VehicleMods::spawnVehicle(VehicleMods::g_uiPlanes[VehicleMods::g_pcPlanesInt],VehicleMods::returnFuncToSpawnInsideVehicle);break;
		case 19:VehicleMods::spawnVehicle(VehicleMods::g_uiBoats[VehicleMods::g_pcBoatsInt],VehicleMods::returnFuncToSpawnInsideVehicle);break;
		case 20:VehicleMods::spawnVehicle(VehicleMods::g_uiTrailers[VehicleMods::g_pcTrailersInt],VehicleMods::returnFuncToSpawnInsideVehicle);break;
		}
		addTitle("Spawn Car");
		addArrayOption(getCachedString("STR585"),&VehicleMods::g_pcSuperCarsInt,VehicleMods::g_pcSuperCars,11);   //Super
		addArrayOption(getCachedString("STR586"),&VehicleMods::g_pcSportsCarsInt,VehicleMods::g_pcSportsCars,29);   //Sports Cars
		addArrayOption(getCachedString("STR587"),&VehicleMods::g_pcSportsClassicCarsInt,VehicleMods::g_pcSportsClassicCars,20);   //Sports Classic Cars
		addArrayOption(getCachedString("STR588"),&VehicleMods::g_pcMuscleCarsInt,VehicleMods::g_pcMuscleCars,12);   //Muscle Cars
		addArrayOption(getCachedString("STR589"),&VehicleMods::g_pcSedansInt,VehicleMods::g_pcSedans,23);   //Sedans
		addArrayOption(getCachedString("STR590"),&VehicleMods::g_pcCoupesInt,VehicleMods::g_pcCoupes,10);   //Coupes
		addArrayOption(getCachedString("STR591"),&VehicleMods::g_pcCompactsInt,VehicleMods::g_pcCompacts,8);   //Compacts
		addArrayOption(getCachedString("STR592"),&VehicleMods::g_pcSUVnTrucksInt,VehicleMods::g_pcSUVnTrucks,28);   //SUVs and Trucks
		addArrayOption(getCachedString("STR593"),&VehicleMods::g_pcOffRoadsInt,VehicleMods::g_pcOffRoads,19);   //Offroad Vehicles
		addArrayOption(getCachedString("STR594"),&VehicleMods::g_pcVansInt,VehicleMods::g_pcVans,31);   //Vans
		addArrayOption(getCachedString("STR595"),&VehicleMods::g_pcEmergencyCarsInt,VehicleMods::g_pcEmergencyCars,18);   //Emergency Vehicles
		addArrayOption(getCachedString("STR596"),&VehicleMods::g_pcServiceVehiclesInt,VehicleMods::g_pcServicVehicles,6);   //Service Vehicles
		addArrayOption(getCachedString("STR597"),&VehicleMods::g_pcMilitaryInt,VehicleMods::g_pcMilitary,7);   //Military Vehicles
		addArrayOption(getCachedString("STR598"),&VehicleMods::g_pcMotorcyclesInt,VehicleMods::g_pcMotorcycles,21);   //Motorcycles
		addArrayOption(getCachedString("STR599"),&VehicleMods::g_pcBicyclesInt,VehicleMods::g_pcBicycles,7);   //Bicycles
		addArrayOption(getCachedString("STR600"),&VehicleMods::g_pcCommercialVehiclesInt,VehicleMods::g_pcCommercialVehicles,39);   //Commercial Vehicles
		addArrayOption(getCachedString("STR601"),&VehicleMods::g_pcHelicoptersInt,VehicleMods::g_pcHelicopters,14);   //Helicopters
		addArrayOption(getCachedString("STR602"),&VehicleMods::g_pcPlanesInt,VehicleMods::g_pcPlanes,19);   //Planes
		addArrayOption(getCachedString("STR603"),&VehicleMods::g_pcBoatsInt,VehicleMods::g_pcBoats,14);   //Boats
		addArrayOption(getCachedString("STR604"),&VehicleMods::g_pcTrailersInt,VehicleMods::g_pcTrailers,27);   //Trailers
		//addSubmenuOption("Super Cars",Super_Cars);
		//addSubmenuOption("Sports Cars",Sports_Cars);
		//addSubmenuOption("Sports Classic Cars",Sports_Classic_Cars);
		//addSubmenuOption("Muscle Cars",Muscle_Cars);
		//addSubmenuOption("Sedans",Sedans);
		//addSubmenuOption("Coupes",Coupes);
		//addSubmenuOption("Compacts",Compacts);
		//addSubmenuOption("SUVs and Trucks",SUVs_and_Trucks);
		//addSubmenuOption("Offroad Vehicles",Offroad_Vehicles);
		//addSubmenuOption("Vans",Vans);
		//addSubmenuOption("Emergency Vehicles",Emergency_Vehicles);
		//addSubmenuOption("Service Vehicles",Service_Vehicles);
		//addSubmenuOption("Military Vehicles",Military_Vehicles);
		//addSubmenuOption("Motorcycles",Motorcycles);
		//addSubmenuOption("Bicycles",Bicycles);
		//addSubmenuOption("Commercial Vehicles",Commercial_Vehicles);
		//addSubmenuOption("Helicopters",Helicopters);
		//addSubmenuOption("Planes",Planes);
		//addSubmenuOption("Boats",Boats);
		//addSubmenuOption("Trailers",Trailers);
		break;
#pragma endregion
#pragma region vehicle spawning menus
		/* just removed 4/12/2017. Removed almost 11kb (10944b)
	case Super_Cars:
		addTitle("Super Cars");
		for (int i = 0; i < 11; i++) {
			addOption(VehicleMods::g_pcSuperCars[i]);
		}
		if(getOption() != 0) {
			VehicleMods::spawnVehicle(VehicleMods::g_uiSuperCars[getOption()-1]);
		}
		break;
	case Sports_Cars:
		addTitle("Sports Cars");
		for (int i = 0; i < 29; i++) {
			addOption(VehicleMods::g_pcSportsCars[i]);
		}
		if(getOption() != 0) {
			VehicleMods::spawnVehicle(VehicleMods::g_uiSportsCars[getOption()-1]);
		}
		break;
	case Sports_Classic_Cars:
		addTitle("Sports Classic Cars");
		for (int i = 0; i < 20; i++) {
			addOption(VehicleMods::g_pcSportsClassicCars[i]);
		}
		if(getOption() != 0) {
			VehicleMods::spawnVehicle(VehicleMods::g_uiSportsClassicCars[getOption()-1]);
		}
		break;
	case Muscle_Cars:
		addTitle("Muscle Cars");
		for (int i = 0; i < 12; i++) {
			addOption(VehicleMods::g_pcMuscleCars[i]);
		}
		if(getOption() != 0) {
			VehicleMods::spawnVehicle(VehicleMods::g_uiMuscleCars[getOption()-1]);
		}
		break;
	case Sedans:
		addTitle("Sedans");
		for (int i = 0; i < 23; i++) {
			addOption(VehicleMods::g_pcSedans[i]);
		}
		if(getOption() != 0) {
			VehicleMods::spawnVehicle(VehicleMods::g_uiSedans[getOption()-1]);
		}
		break;
	case Coupes:
		addTitle("Coupes");
		for (int i = 0; i < 10; i++) {
			addOption(VehicleMods::g_pcCoupes[i]);
		}
		if(getOption() != 0) {
			VehicleMods::spawnVehicle(VehicleMods::g_uiCoupes[getOption()-1]);
		}
		break;
	case Compacts:
		addTitle("Compacts");
		for (int i = 0; i < 8; i++) {
			addOption(VehicleMods::g_pcCompacts[i]);
		}
		if(getOption() != 0) {
			VehicleMods::spawnVehicle(VehicleMods::g_uiCompacts[getOption()-1]);
		}
		break;
	case SUVs_and_Trucks:
		addTitle("SUVs and Trucks");
		for (int i = 0; i < 28; i++) {
			addOption(VehicleMods::g_pcSUVnTrucks[i]);
		}
		if(getOption() != 0) {
			VehicleMods::spawnVehicle(VehicleMods::g_uiSUVnTrucks[getOption()-1]);
		}
		break;
	case Offroad_Vehicles:
		addTitle("Offroad Vehicles");
		for (int i = 0; i < 19; i++) {
			addOption(VehicleMods::g_pcOffRoads[i]);
		}
		if(getOption() != 0) {
			VehicleMods::spawnVehicle(VehicleMods::g_uiOffRoads[getOption()-1]);
		}
		break;
	case Vans:
		addTitle("Vans");
		for (int i = 0; i < 31; i++) {
			addOption(VehicleMods::g_pcVans[i]);
		}
		if(getOption() != 0) {
			VehicleMods::spawnVehicle(VehicleMods::g_uiVans[getOption()-1]);
		}
		break;
	case Emergency_Vehicles:
		addTitle("Emergency Vehicles");
		for (int i = 0; i < 18; i++) {
			addOption(VehicleMods::g_pcEmergencyCars[i]);
		}
		if(getOption() != 0) {
			VehicleMods::spawnVehicle(VehicleMods::g_uiEmergencyCars[getOption()-1]);
		}
		break;
	case Service_Vehicles:
		addTitle("Service Vehicles");
		for (int i = 0; i < 6; i++) {
			addOption(VehicleMods::g_pcServicVehicles[i]);
		}
		if(getOption() != 0) {
			VehicleMods::spawnVehicle(VehicleMods::g_uiServicVehicles[getOption()-1]);
		}
		break;
	case Military_Vehicles:
		addTitle("Military");
		for (int i = 0; i < 7; i++) {
			addOption(VehicleMods::g_pcMilitary[i]);
		}
		if(getOption() != 0) {
			VehicleMods::spawnVehicle(VehicleMods::g_uiMilitary[getOption()-1]);
		}
		break;
	case Motorcycles:
		addTitle("Motorcycles");
		for (int i = 0; i < 21; i++) {
			addOption(VehicleMods::g_pcMotorcycles[i]);
		}
		if(getOption() != 0) {
			VehicleMods::spawnVehicle(VehicleMods::g_uiMotorcycles[getOption()-1]);
		}
		break;
	case Bicycles:
		addTitle("Bicycles");
		for (int i = 0; i < 7; i++) {
			addOption(VehicleMods::g_pcBicycles[i]);
		}
		if(getOption() != 0) {
			VehicleMods::spawnVehicle(VehicleMods::g_uiBicycles[getOption()-1]);
		}
		break;
	case Commercial_Vehicles:
		addTitle("Commercial Vehicles");
		for (int i = 0; i < 39; i++) {
			addOption(VehicleMods::g_pcCommercialVehicles[i]);
		}
		if(getOption() != 0) {
			VehicleMods::spawnVehicle(VehicleMods::g_uiCommercialVehicles[getOption()-1]);
		}
		break;
	case Helicopters:
		addTitle("Helicopters");
		for (int i = 0; i < 14; i++) {
			addOption(VehicleMods::g_pcHelicopters[i]);
		}
		if(getOption() != 0) {
			VehicleMods::spawnVehicle(VehicleMods::g_uiHelicopters[getOption()-1]);
		}
		break;
	case Planes:
		addTitle("Planes");
		for (int i = 0; i < 19; i++) {
			addOption(VehicleMods::g_pcPlanes[i]);
		}
		if(getOption() != 0) {
			VehicleMods::spawnVehicle(VehicleMods::g_uiPlanes[getOption()-1]);
		}
		break;
	case Boats:
		addTitle("Boats");
		for (int i = 0; i < 14; i++) {
			addOption(VehicleMods::g_pcBoats[i]);
		}
		if(getOption() != 0) {
			VehicleMods::spawnVehicle(VehicleMods::g_uiBoats[getOption()-1]);
		}
		break;
	case Trailers:
		addTitle("Trailers");
		for (int i = 0; i < 27; i++) {
			addOption(VehicleMods::g_pcTrailers[i]);
		}
		if(getOption() != 0) {
			VehicleMods::spawnVehicle(VehicleMods::g_uiTrailers[getOption()-1]);
		}
		break;
		*/
#pragma endregion
#pragma region Recovery Menu
#ifdef recoveryinthemenunotlolhaha
	case Recovery_Menu:
		//char buf[50];
		//snprintf$(buf,sizeof(buf),"Player %i",stats::curplayer+1);
		//addTitle(buf);
		addTitle("Recovery");
		//addOption("Switch Character");
		addOption(getCachedString("STR605"));   //Clear Reports
		/*addOption("Unlock Heist Vehicles");
		addOption(getCachedString("STR606"));   //Clear Badsport
		addOption(getCachedString("STR607"));   //100% Skills
		addOption(getCachedString("STR608"));   //All Tattos
		addOption(getCachedString("STR609"));   //Unlimited Snacks
		addOption(getCachedString("STR610"));   //Max Armor
		addOption(getCachedString("STR611"));   //Free Fireworks
		addOption(getCachedString("STR612"));   //Unlock All Camos
		addOption(getCachedString("STR613"));   //Free Rims
		addOption(getCachedString("STR614"));   //Buy All Shirts
		addOption(getCachedString("STR615"));   //Finish All LSC Challenges
		addOption(getCachedString("STR616"));   //Unlock All Trophies
		addOption(getCachedString("STR617"));   //All Hair Unlocked
		addOption(getCachedString("STR618"));*/   //All Weapons Unlocked
		addOption(getCachedString("STR619"));   //Reset Mental State
		//addOption("Rank 120");
		addOption(getCachedString("STR620"));   //Legit KD
		addIntOption(getCachedString("STR621"),&stats::moneyAmount,1,10000000,true);   //Give Money
		addIntOption(getCachedString("STR622"),&fixedstats::deductAmount,1,1000000000,true,"Positive Number");   //Deduct Money
		addOption(getCachedString("STR623"));   //Rank 120
		//addOption("High Mental State");
		addOption(getCachedString("STR624"));   //Set Into Badsport
		addOption(getCachedString("STR625"));   //Remove From Badsport
		addOption(getCachedString("STR626"));   //Remove From Cheater
		switch(getOption()) {
		//case 1: stats::changeplayer();break;
		case 1: fixedstats::clearReports();break;
		/*case 3: fixedstats::heists();break;
		case 4: fixedstats::badsport();break;
		case 5: fixedstats::skills();break;
		case 6: fixedstats::tats();break;
		case 7: fixedstats::snacks();break;
		case 8: fixedstats::armor();break;
		case 9: fixedstats::fireworks();break;
		case 10: fixedstats::camos();break;
		case 11: fixedstats::freeRims();break;
		case 12: fixedstats::shirts();break;
		case 13: fixedstats::lsc();break;
		case 14: fixedstats::trophies();break;
		case 15: fixedstats::hair();break;
		case 16: fixedstats::weapons();break;*/
		case 2: fixedstats::resetMentalState();break;
		//case 3: fixedstats::rank120();break;
		case 3: stats::fixkd();break;
		case 4: stats::giveMoney(stats::moneyAmount);break;
		case 5: fixedstats::deductMoney();break;
		case 6: fixedstats::rank120();break;
		case 7: stats::setintobadsport();print2("set into badsport!",1000);break;
		case 8: stats::noBadsport();print2("Removed from badsport!",1000);break;
		case 9: stats::noCheater();print2("Removed from cheater!",1000);break;
		//case 7: stats::highMentalState();break;
		//case 8: stats::setintobadsport();print2("set into badsport!",1000);break;
		}
		break;
#endif
#pragma endregion

#pragma region Forge Menu
	case Forge_Menu:
		//char forgemenutitle[30];
		snprintf(global_temporary_buf,sizeof(global_temporary_buf),"Forge Menu: %i",forge::curObject);
		addTitle(global_temporary_buf);
		addOption(getCachedString("STR627"));   //Spawn List
		addOption(getCachedString("STR628"),"Skyscrapers & Bases");   //Pre-Built Structures
		addOption(getCachedString("STR629"));   //Object And Vehicle Spooner *NEW*
		addBoolOption(getCachedString("STR630"),forge::enabled,"Enabled forge mode");   //Forge Mode
		addBoolOption(getCachedString("STR631"),forge::gunLook,"Forge mode must be enabled!");   //Dynamic Movement
		addIntOption(getCachedString("STR632"),&forge::clipDistance,1,100,true);   //Dynamic Distance
		//addIntOption("X",(int*)&forge::loc.x,-10000000,10000000,false,"Increments of 1");
		//addIntOption("Y",(int*)&forge::loc.y,-10000000,10000000,false,"Increments of 1");
		//addIntOption("Z",(int*)&forge::loc.z,-10000000,10000000,false,"Increments of 1");
		addOption(getCachedString("STR633"));   //Placement
		//addFloatOption("Increment",&forge::increment,0,25,true);
		//addFloatOption("X",&forge::loc.x,-10000000,10000000,true,forge::increment);
		//addFloatOption("Y",&forge::loc.y,-10000000,10000000,true,forge::increment);
		//addFloatOption("Z",&forge::loc.z,-10000000,10000000,true,forge::increment);
		addOption(getCachedString("STR634"));   //Variables
		addOption(getCachedString("STR635"));   //Attach To Player
		addBoolOption(getCachedString("STR636"),forge::vaccume,"Aim to delete objects. Must have forge mode enabled");   //Delete Gun
		addBoolOption(getCachedString("STR637"),forge::attachToPlayerOnSpawn,"Forge mode must be enabled!");   //Attach To Player On Selection
		addBoolOption(getCachedString("STR638"),forge::attachToPlayerOnSpawnCollision,"Forge mode must be enabled!");   //Enable Collision On Player Attach
		addBoolOption(getCachedString("STR639"),forge::attachToPlayerOnSpawnInvisibility,"Forge mode must be enabled!");   //Set Invisible On Player Attach
		//addBoolOption("Customizer Mode",forge::setEntityToAttachToMode,"If true, all new spawned/chosen entities will be attached to the last spawned/chosen entity");
		addBoolOption(getCachedString("STR640"),forge::moneyDrop);   //Spawn As Money
		addBoolOption(getCachedString("STR641"),forge::gunmode,"Shoot to spawn the objects instead");   //Spawn Gun
		addOption(getCachedString("STR642"));   //Release Object
		addOption(forgeMenuSave,"Update object name (Causes brief lag)");
		//addOption("Creation Menu");
		addOption(getCachedString("STR643"));   //Clone Object
		switch(getOption()) {
		case 1: changeSubmenu(Forge_Menu_Object_List);break;
		case 2: changeSubmenu(Pre_Built_Structures_Menu);break;
		case 3: changeSubmenu(spooner_menu);break;//spooner menu
		case 4: forge::toggle();break;
		case 5: forge::gunLook = !forge::gunLook;break;
		case 6: break;
		case 7: changeSubmenu(Forge_Menu_Movement);break;//1
		//case 6: break;//2
		//case 7: break;//3
		//case 8: break;//4
		case 8: changeSubmenu(Forge_Menu_Variables);break;
		case 9: changeSubmenu(Forge_Attach_List);break;
		case 10: forge::vaccume = !forge::vaccume;
			if (forge::vaccume) {
				forge::enabled = true;
				print2("~r~NOTICE: Forge mode turned on too!");
			}
			break;
		case 11: if (forge::attachToPlayerOnSpawn == false){changeSubmenu(Forge_Attach_Player_Auto_List);}else{forge::attachToPlayerOnSpawn = false;}break;
		case 12: forge::attachToPlayerOnSpawnCollision = !forge::attachToPlayerOnSpawnCollision;break;
		case 13: forge::attachToPlayerOnSpawnInvisibility = !forge::attachToPlayerOnSpawnInvisibility;break;
		//case 12: forge::setEntityToAttachToMode = !forge::setEntityToAttachToMode;break;
		case 14: forge::moneyDrop = !forge::moneyDrop;break;
		case 15: forge::gunmode = !forge::gunmode;break;
		case 16: forge::remove();break;
		case 17: strcpy(forgeMenuSave,getHashName(ENTITY::GET_ENTITY_MODEL(forge::curObject)));break;
		//case 18: changeSubmenu(Creation_Management);break;
		case 18: forge::clone();break;
		}
		break;
#pragma endregion
#pragma region spooner_menu
	case spooner_menu:
		{
			addTitle("Object Spooner");
			//addKeyboardOption("Spawn Custom Spooner By File Name",keyboard_spooner_spawn,keyboardText,64,"Type FILE NAME Like spooner/FILE NAME.xml","Spawn Spooner *BETA*");
			//addKeyboardOption("Spawn Custom Vehicle Spooner By File Name",keyboard_vehicle_spooner_spawn,keyboardText,64,"Type FILE NAME Like vehiclespooner/FILE NAME.xml","Spawn Vehicle Spooner *BETA*");
			addOption(getCachedString("STR644"));   //Map Spooner List
			addOption(getCachedString("STR645"));   //Vehicle Spooner List
			addOption(getCachedString("STR646"));   //Stop Spawning
			SideInfo p = SideInfo();
			p.addText("Spooner *BETA*");
			p.addText("This feature is in development and may have bugs.");
			p.addText("Report any freezes or major bugs during use to customer support chat.");
			p.addText("");
			p.addText("How to use:");
			p.addText("1. Download the zip from the link below.");
			p.addText("2. Put the 2 folders from the download in /dev_hdd0/tmp/gopro_2027/XML/");
			//p.addText("3. Click the option and type in the name of the file, example: Skatepark");
			p.addText("Download zip: http://bit.ly/paradisespooner Thanks to semjases for giving me these premade XML files!");
			/*p.addText("REMOVED");
			p.addText("Removed, in favor of other options.");
			p.addText("Will probably be in Tiny Menu in the future");
			p.addText("or some free menu.");*/
			p.drawBG();
			switch(getOption()) {
			case 1: changeSubmenu(spooner_map_list_menu);break;
			case 2: changeSubmenu(spooner_veh_list_menu);break;
			case 3:
				globalSpooner.stop();
				globalVehicleSpooner.stop();
				print2("Spawning Stopped");
				break;
			}
		}
		break;
#pragma endregion
#pragma region spooner_map_list_menu
	case spooner_map_list_menu:
		addTitle("Spooner Maps");
		readDir("/dev_hdd0/tmp/gopro_2027/XML/spooner",addMapSpoonerCallback);
		break;
#pragma endregion
#pragma region spooner_veh_list_menu
	case spooner_veh_list_menu:
		addTitle("Spooner Vehicles");
		readDir("/dev_hdd0/tmp/gopro_2027/XML/vehiclespooner",addVehicleSpoonerCallback);
		break;
#pragma endregion
/*#pragma region Creation Management
	case Creation_Management:
		addTitle("Creation Management");
		switch(getOption()){
		case 1: forge::addObjectToCreation(forge::curObject);break;
		case 2: forge::clearCreation();break;
		case 7: forge::spawnCreation();break;
		}
		addOption(getCachedString("STR647"),"Max of 100 objects");   //Add Current Object To Creation
		addOption(getCachedString("STR648"));   //~r~Clear Current Creation
		addKeyboardOption(getCachedString("STR649"),save_creation_relative_to_player,keyboardText,20,"Enter creation name");   //Save Creation As Relative To Player
		addKeyboardOption(getCachedString("STR650"),save_creation_relative_to_world,keyboardText,20,"Enter creation name");   //Save Creation As Relative To World
		addKeyboardOption(getCachedString("STR651"),save_creation_relative_to_vehicle,keyboardText,20,"Enter creation name","Stand where the vehicle will be when attached. *STILL IN DEVELOPMENT*");   //Save Creation As Relative To Vehicle
		addKeyboardOption(getCachedString("STR652"),load_creation,keyboardText,20,"Enter creation name");   //Load Creation
		addOption(getCachedString("STR653"));   //Spawn Creation
		break;
#pragma endregion*/
#pragma region Pre_Built_Structures_Menu
	case Pre_Built_Structures_Menu:
		//103 0 0 (3) is get into circle
		struct intoJob {
			int identifier;//0000009A
			int player;//0
			int data[5];//FFFFFFFF 00000005 00000037 00000000 00000028
			char jobName[4*6];//46414B45 5F474F4C 465F5F5F 30000000 00000000 00000000 which is FAKE_GOLF___0
			int moredata[7];//FFFFFFFF 00000000 00000001 FFFFFFFF FFFFFFFF 00000000 004D464C
		};
		//0000009A 00000000 FFFFFFFF 00000005 00000040 0000000B 0000003E 2D424F46 7A764672 7355694B 53735576 56627A79 4D410000 FFFFFFFF 00000000 00000001 FFFFFFFF FFFFFFFF 00000000 003C1EB6 (0x14) a race job circle
		//0000009A 00000000 FFFFFFFF 00000005 00000040 0000002D 0000003E 73795759 61354933 4E456D38 62725545 77755672 73510000 FFFFFFFF 00000000 00000001 FFFFFFFF FFFFFFFF 00000000 00404EF5 (0x14) same as one right below
		//0000009A 00000000 FFFFFFFF 00000005 00000040 0000002D 0000003E 73795759 61354933 4E456D38 62725545 77755672 73510000 FFFFFFFF 00000000 00000001 FFFFFFFF FFFFFFFF 00000000 00449799 (0x14) teleport into that job circle on corner
		//0000009A 00000000 FFFFFFFF 00000005 00000037 00000000 00000028 46414B45 5F474F4C 465F5F5F 30000000 00000000 00000000 FFFFFFFF 00000000 00000001 FFFFFFFF FFFFFFFF 00000000 004D464C (0x14) teleport into golf

		//0000009A 00000000 FFFFFFFF 00000005 00000040 0000002D 0000003E 73795759 61354933 4E456D38 62725545 77755672 73510000 FFFFFFFF (0x14) is part 2
		//00001692 00000000 00000000 FFFFFFFF 33B0CF30 33B0CF2C (6) is part 3
		//0000009E 00000000 00247502 (3) is part 4
		//000000A8 00000000 00247502 (3) is part 5
		//000000E4 00000000 (2) is part 6
		//000000CC 00000000 (2) is part 7
		//00000002 00000000 0000002D (3) is part 8
		//000000CC 00000000 (2) is part 9

		//000000E4 00000000 (2) idle kick?
		switch(getOption()) {
			//char *uytgsduyfg = "~r~Please download the required files from http://paradisesprx.net/user/Creations ";
#ifdef creationSpawner
		case 1: forge::loadAndSpawnCreation("base");break;
		case 2: forge::loadAndSpawnCreation("base2");break;
		case 3: forge::loadAndSpawnCreation("base3");break;
		case 4: forge::loadAndSpawnCreation("carkour");break;
		case 5: forge::loadAndSpawnCreation("mazeramp");break;
		case 6: structures::nextBarge(0);print2("Only spawn 1",1000);break;
#endif
		case 7: /*if (!STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("dt1_05_build1_h")))STREAMING::LOAD_SCENE(-26.0f,-747.0f,45.0f);*/forge::spawnAtLook("dt1_05_build1_h");break;
		case 8: /*if (!STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("dt1_05_build2_h")))STREAMING::LOAD_SCENE(-26.0f,-747.0f,45.0f);*/forge::spawnAtLook("dt1_05_build2_h");break;
		case 9: /*if (!STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("dt1_10_build1")))STREAMING::LOAD_SCENE(-26.0f,-747.0f,45.0f);*/forge::spawnAtLook("dt1_10_build1");break;

		case 10: /*if (!STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("dt1_12_build1")))STREAMING::LOAD_SCENE(-26.0f,-747.0f,45.0f);*/forge::spawnAtLook("dt1_12_build1");break;
		case 11: /*if (!STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("dt1_12_build2")))STREAMING::LOAD_SCENE(-26.0f,-747.0f,45.0f);*/forge::spawnAtLook("dt1_12_build2");break;
		case 12: /*if (!STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("dt1_12_build3")))STREAMING::LOAD_SCENE(-26.0f,-747.0f,45.0f);*/forge::spawnAtLook("dt1_12_build3");break;
		case 13: /*if (!STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("dt1_tc_dufo_core")))STREAMING::LOAD_SCENE(-2012.8470f, 2956.5270f, 32.8101f);*/forge::spawnAtLook("dt1_tc_dufo_core");break;

		case 14: forge::spawnAtLook("dt1_lod_slod3");break;
		case 15: forge::spawnAtLook("id1_lod_slod4");break;
		case 16: forge::spawnAtLook("id2_lod_slod4");break;
		case 17: forge::spawnAtLook("hw1_lod_slod4");break;
		case 18: forge::spawnAtLook("po1_lod_slod4");break;
		case 19: forge::spawnAtLook("sc1_lod_slod4");break;
		case 20: forge::spawnAtLook("ss1_lod_slod3");break;
		case 21: forge::spawnAtLook("ap1_lod_slod4");break;
		case 22: forge::spawnAtLook("kt1_lod_slod4");break;
		case 23: forge::spawnAtLook("bh1_lod_slod3");break;
		case 24: forge::spawnAtLook("sp1_lod_slod4");break;
		case 25: forge::spawnAtLook("sm_lod_slod4");break;
		case 26: forge::spawnAtLook("vb_lod_slod4");break;
		}

		{
		//*(char*)0x1C97578 = 0;//game pauses for steaming false
		addTitle("Structures");
#ifdef creationSpawner
		char *jsjdfn0 = "By gopro_2027 via Creations Menu";
		addOption(getCachedString("STR654"),jsjdfn0);   //Sky Base 1
		addOption(getCachedString("STR655"),jsjdfn0);   //Sky Base 2
		addOption(getCachedString("STR656"),jsjdfn0);   //Big Land Base
		addOption(getCachedString("STR657"),jsjdfn0);   //Car Parkour
		addOption(getCachedString("STR658"),jsjdfn0);   //Maze Bank Megaramp
		addOption(getCachedString("STR659"));   //Hidden Base Under Map
		//char *nf0 = "Temporary freeze";
#endif
		char *nf1 = "Must visit place prior to spawn";
		char *nf0 = nf1;
		addOption(getCachedString("STR660"),nf0);   //Skyscraper 1
		addOption(getCachedString("STR661"),nf0);   //Skyscraper 2
		addOption(getCachedString("STR662"),nf0);   //Skyscraper 3
		addOption(getCachedString("STR663"),nf0);   //Skyscraper 4
		addOption(getCachedString("STR664"),nf0);   //Skyscraper 5
		addOption(getCachedString("STR665"),nf0);   //Skyscraper 6
		addOption(getCachedString("STR666"),nf0);   //Black UFO From Military Base
		addOption(getCachedString("STR667"),nf1);   //Downtown
		addOption(getCachedString("STR668"),nf1);   //Industrial 1
		addOption(getCachedString("STR669"),nf1);   //Industrial 2
		addOption(getCachedString("STR670"),nf1);   //Hollywood
		addOption(getCachedString("STR671"),nf1);   //Port
		addOption(getCachedString("STR672"),nf1);   //Central
		addOption(getCachedString("STR673"),nf1);   //Sunset
		addOption(getCachedString("STR674"),nf1);   //Airport
		addOption(getCachedString("STR675"),nf1);   //Koreatown
		addOption(getCachedString("STR676"),nf1);   //Beverly Hills
		addOption(getCachedString("STR677"),nf1);   //San Pedro
		addOption(getCachedString("STR678"),nf1);   //Santa Monica
		addOption(getCachedString("STR679"),nf1);   //Venice Beach
		}
		//addOption("",nf1);
		break;
#pragma endregion
/*#pragma region Creator Mode
	case Creator_Mode:
		addTitle("Creator Mode");
		//addBoolOption("Enabled",&forge::creatorMode);
		break;
#pragma endregion*/
#pragma region Forge Menu Variables
	case Forge_Menu_Variables:
		addTitle("Variables");
		addOption(getCachedString("STR680"));   //Delete Object
		addOption(getCachedString("STR681"));   //Detach Object
		addOption(getCachedString("STR682"));   //Enable Collision
		addOption(getCachedString("STR683"));   //Disable Collision
		addOption(getCachedString("STR684"));   //Set Visible
		addOption(getCachedString("STR685"));   //Set Invisible
		addOption(getCachedString("STR686"));   //Enable Gravity
		addOption(getCachedString("STR687"));   //Disable Gravity
		addOption(getCachedString("STR688"));   //Freeze
		addOption(getCachedString("STR689"));   //Unfreeze
		switch(getOption()) {
			case 1: forge::remove();break;
			case 2: forge::detach();break;
			case 3: forge::setCollision(true);break;//forge::toggleCollision();break;
			case 4: forge::setCollision(false);break;
			case 5: forge::setVisible(true);break;
			case 6: forge::setVisible(false);break;
			case 7: forge::setGravity(true);break;
			case 8: forge::setGravity(false);break;
			case 9: forge::freeze(true);break;
			case 10: forge::freeze(false);break;
		}
		break;
#pragma endregion
#pragma region Forge Attach Player Auto List
	case Forge_Attach_Player_Auto_List:
		addTitle("Choose A Player To Auto Attach To...");
		if (1 == 1) {
			int start = 0;
			for (int i = 0; i < 18; i++)
			{
				char *name = PLAYER::GET_PLAYER_NAME(i);
				if (isPlayerValid(name)) {
					addOption(name);
					start++;
					if (optionPress)
					{
						if (currentOption == start) {
							forge::attachToPlayerOnSpawn = true;
							forge::attachToPlayerOnSpawnPlayer = i;
							//submenu = lastSubmenu[submenuLevel-1];
							//currentOption = lastOption[submenuLevel-1];
							//submenuLevel--;
							//playSound("Back");
						}
					}
				}
			}
		}
		break;
#pragma endregion
#pragma region Forge Menu Movement
	case Forge_Menu_Movement:
		addTitle("Placement");
		//addSpacer("Position");
		addFloatOption(getCachedString("STR690"),&forge::increment,0,25,true,"Value in which to move/rotate by",true);   //Increment
		addFloatOption(getCachedString("STR691"),&forge::loc.x,-10000000,10000000,true,forge::increment);   //X Pos
		addFloatOption(getCachedString("STR692"),&forge::loc.y,-10000000,10000000,true,forge::increment);   //Y Pos
		addFloatOption(getCachedString("STR693"),&forge::loc.z,-10000000,10000000,true,forge::increment);   //Z Pos
		//addSpacer("Rotation");
		addFloatOption(getCachedString("STR694"),&forge::rot.x,0,360,true,forge::increment,0,true);   //Object X Rot
		addFloatOption(getCachedString("STR695"),&forge::rot.y,0,360,true,forge::increment,0,true);   //Object Y Rot
		addFloatOption(getCachedString("STR696"),&forge::rot.z,0,360,true,forge::increment,0,true);   //Object Z Rot
#ifdef fancyPlacementForge
		addFloatOption(getCachedString("STR697"),&forge::plane.pitch,0,360,true,forge::increment,0,true);   //Axis Pitch
		addFloatOption(getCachedString("STR698"),&forge::plane.roll,0,360,true,forge::increment,0,true);   //Axis Roll
		addFloatOption(getCachedString("STR699"),&forge::plane.yaw,0,360,true,forge::increment,0,true);   //Axis Yaw
		//addOption("Set Movement Rot Equal To Object Rot");
		{
			float dif = forge::loc.x;
			int val = addFloatOption("Move In X Axis",&dif,-10000000,10000000,true,forge::increment,"Scroll To Move");
			if (val != 0)
				forge::plane.translate(forge::increment*val,0,0);
			dif = forge::loc.y;
			val = addFloatOption("Move In Y Axis",&dif,-10000000,10000000,true,forge::increment,"Scroll To Move");
			if (val != 0)
				forge::plane.translate(0,forge::increment*val,0);
			dif = forge::loc.z;
			val = addFloatOption("Move In Z Axis",&dif,-10000000,10000000,true,forge::increment,"Scroll To Move");
			if (val != 0)
				forge::plane.translate(0,0,forge::increment*val);
		}
#endif
		addOption(getCachedString("STR700"),"Clones the object");//14   //Place Object
		//addBoolOption("Add Object To Creation On Place",forge::creationClonePlace,"If enabled, when you click 'place object' it adds it to the creation from the creations submenu. Max of 100 objects");
		
		static Vector3 objectDif = {0,0,0};
		static Rot3 translateRot = {0,0,0};
		static Rot3 objRot = {0,0,0};
		static bool flippitch = false;
		static bool fliproll = false;
		static bool flipyaw = false;
		static bool ninetycalc = false;
		/*
		addOption(getCachedString("STR701"));   //Get Object Dif
		addOption(getCachedString("STR702"));   //Attach To Car
		addBoolOption(getCachedString("STR703"),&flippitch);   //Flip Pitch
		addBoolOption(getCachedString("STR704"),&fliproll);   //Flip Roll
		addBoolOption(getCachedString("STR705"),&flipyaw);   //Flip Yaw
		addBoolOption(getCachedString("STR706"),&ninetycalc);*/   //Use 90 degrees instead
		switch (getOption()) {
		/*case 10:
			forge::creatorModeRot.x = forge::rot.z;
			forge::creatorModeRot.y = forge::rot.x;
			forge::creatorModeRot.z = 0;
			break;*/
#if fancyPlacementForge
		case 14:
			forge::freeze(true);
			//if (forge::creationClonePlace)
				//forge::addObjectToCreation(forge::curObject);
			forge::clone();
			break;
		case 15:
			forge::creationClonePlace = !forge::creationClonePlace;
			break;
#else
		case 8:
			forge::freeze(true);
			forge::clone();
			break;
#endif
		/*case 16:
			{
			
				int veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),false);
			Vec3 rr = ENTITY::GET_ENTITY_ROTATION(veh,2);
			Rot3 r = {ENTITY::GET_ENTITY_ROLL(veh),ENTITY::GET_ENTITY_PITCH(veh),rr.z};
			Vector3 vpos = {0,0,0};//ENTITY::GET_ENTITY_COORDS(veh,1);
			int part = ENTITY::_0xE4ECAC22(veh,"engine");
			forge::_0x7C6339DF(&vpos,veh,part);//GET_WORLD_POSITION_OF_ENTITY_BONE
			Vector3 vpos2 = ENTITY::GET_ENTITY_COORDS(veh,1);
			Vector3 vposd = rotationMath::getDif(vpos,vpos2);

				Vec3 car = vpos;//{28,595,15};
					Vec3 obj = {forge::loc.x,forge::loc.y,forge::loc.z};
					Rot3 carRot = r;//{r.rol,r.x,r.z};
					Vec3 dif = rotationMath::getDif(car,obj);
					//dif.x*=-1;//x axis is flipped
					Rot3 rot = rotationMath::getRot(dif);
					//rot.yaw*=-1;
					rot.roll-=carRot.roll;
					rot.pitch-=carRot.pitch;
					rot.yaw-=carRot.yaw;
					objectDif.x = dif.x;
					objectDif.y = dif.y;
					objectDif.z = dif.z;
					translateRot.pitch = carRot.pitch;
					translateRot.roll = carRot.roll;
					translateRot.yaw = carRot.yaw;
					objRot.pitch = rot.pitch;
					objRot.roll = rot.roll;
					objRot.yaw = rot.yaw;
					//Vec3 n = rotationMath::translatePoint(dif,rot);
					//Creation.objects[i].x = n.x;
					//Creation.objects[i].y = n.y;
					//Creation.objects[i].z = n.z;
					print2("Difference gotten!",1000);
			}
			break;
		case 17:
			{
				Vec3 n = rotationMath::translatePoint(objectDif,translateRot,fliproll,flippitch,flipyaw,ninetycalc);
				Vector3 vpos = {0,0,0};//ENTITY::GET_ENTITY_COORDS(veh,1);
				int veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),0);
				int part = ENTITY::_0xE4ECAC22(veh,"engine");
				forge::_0x7C6339DF(&vpos,veh,part);//GET_WORLD_POSITION_OF_ENTITY_BONE
				OBJ::attachPropAlreadySpawnedObject(veh,part,forge::curObject,n,objRot.toVector3());
				print2("Attached!",1000);
			}
			break;*/
		}
		break;
#pragma endregion
/*#pragma region Forge Menu Object List All
	case Forge_Menu_Object_List_All:
		addTitle("Spawn List");
		forge::objectListOption = currentOption;
		for (int i = 0; i < 1077; i++) {
			addOption(forge::propHashes[i],"Press square to save to favorites");
			if (getOption() == i+1) {
				//entityMods::initEntity(entityMods::pedHashes[i],entityMods::curEntity);
				forge::spawnAtLook(forge::propHashes[i]);
			}
			if (getSquareOption() == i+1) {
				forge::addObjectToFavorites(forge::propHashes[i]);
			}
		}
		break;
#pragma endregion*/
#pragma region Forge Menu Object List Short
	case Forge_Menu_Object_List_Short:
	addTitle("Quick Spawn List");
    addOption("Airport Ramp");
    addOption("UFO");
    addOption("Windmill");
    addOption("Huge Barge");
    addOption("Dummy");
    addOption("Huge Ball");
    addOption("Glowing EMP");
    addOption("Crashed Tram");
    addOption("AA Gun");
    addOption("Spinning");
    addOption("Radar");
    addOption("Tug Boat");
    addOption("Cable Car");
    addOption("Soccer Ball");
    addOption("Roller Car");
    addOption("Ferris Wheel");
    addOption("Bank Safe");
    addOption("Oil Slick");
    addOption("ATM Machine");
    addOption("Big Jet");
    addOption("Mini Gun");
    addOption("Car Seat");
    addOption("Ramp 01");
    addOption("Ramp 02");
    addOption("Ramp 03");
    addOption("Beach Fire");
    addOption("Weed Pallet");
    addOption("Crashed Heli");
    addOption("Space Pistol");
    addOption("Toilet");
    addOption("Wheelchair");
    addOption("Trolley");
    addOption("Flat TV");
    addOption("Ice Locker");
    addOption("Road Cone");
    addOption("Air Stair");
    addOption("Wheel");
    addOption("Dustbin");
    addOption("Beggers Sign");
    addOption("Food Van");
    addOption("Golf Bag");
    addOption("Carwash Roller");
    addOption("Skip");
    addOption("Cash Crate");
    addOption("Dummy Plane");
    addOption("Air Lights");
    addOption("Portacabin");
    addOption("Beer Neon");
    addOption("Haybail");
    addOption("Flat Ramp");
	addOption(getCachedString("STR707"));   //Fun Box
	addOption(getCachedString("STR708"));   //Half Pipe
	addOption(getCachedString("STR709"));   //Kicker
	addOption(getCachedString("STR710"));   //Quarter Pipe
	addOption(getCachedString("STR711"));   //Rail
	addOption(getCachedString("STR712"));   //Spiner
	addOption(getCachedString("STR713"));   //TV With Video Transmission
	addOption(getCachedString("STR714"));   //TV With Video Transmission v2
	addOption(getCachedString("STR715"));   //TV With Video Transmission v3
    switch (getOption())
    {
    case 1: forge::spawnAtLook("PROP_AIR_BLASTFENCE_01"); break;
    case 2: forge::spawnAtLook("p_spinning_anus_s"); break;
    case 3: forge::spawnAtLook("prop_windmill_01"); break;
    case 4: forge::spawnAtLook("prop_lev_des_barge_02"); break;
    case 5: forge::spawnAtLook("prop_dummy_01"); break;
    case 6: forge::spawnAtLook("prop_juicestand"); break;
    case 7: forge::spawnAtLook("hei_prop_heist_emp"); break;
    case 8: forge::spawnAtLook("p_tram_crash_s"); break;
    case 9: forge::spawnAtLook("hei_prop_carrier_defense_01"); break;
    case 10: forge::spawnAtLook("prop_air_bigradar"); break;
    case 11: forge::spawnAtLook("hei_prop_carrier_radar_1"); break;
    case 12: forge::spawnAtLook("hei_prop_heist_tug"); break;
    case 13: forge::spawnAtLook("p_cablecar_s"); break;
    case 14: forge::spawnAtLook("p_ld_soc_ball_01"); break;
    case 15: forge::spawnAtLook("prop_roller_car_01"); break;
    case 16: forge::spawnAtLook("prop_Ld_ferris_wheel"); break;
    case 17: forge::spawnAtLook("p_v_43_safe_s"); break;
    case 18: forge::spawnAtLook("p_oil_slick_01"); break;
    case 19: forge::spawnAtLook("prop_atm_01"); break;
    case 20: forge::spawnAtLook("PROP_MED_JET_01"); break;
    case 21: forge::spawnAtLook("prop_minigun_01"); break;
    case 22: forge::spawnAtLook("prop_car_seat"); break;
    case 23: forge::spawnAtLook("prop_mp_ramp_01"); break;
    case 24: forge::spawnAtLook("prop_mp_ramp_02"); break;
    case 25: forge::spawnAtLook("prop_mp_ramp_03"); break;
    case 26: forge::spawnAtLook("prop_beach_fire"); break;
    case 27: forge::spawnAtLook("prop_weed_pallet"); break;
    case 28: forge::spawnAtLook("prop_crashed_heli"); break;
    case 29: forge::spawnAtLook("prop_space_pistol"); break;
    case 30: forge::spawnAtLook("prop_ld_toilet_01"); break;
    case 31: forge::spawnAtLook("prop_wheelchair_01"); break;
    case 32: forge::spawnAtLook("prop_cs_trolley_01"); break;
    case 33: forge::spawnAtLook("prop_tv_06"); break;
    case 34: forge::spawnAtLook("prop_cs_ice_locker"); break;
    case 35: forge::spawnAtLook("prop_roadcone01a"); break;
    case 36: forge::spawnAtLook("prop_air_stair_03"); break;
    case 37: forge::spawnAtLook("prop_wheel_01"); break;
    case 38: forge::spawnAtLook("prop_bin_04a"); break;
    case 39: forge::spawnAtLook("prop_beggers_sign_01"); break;
    case 40: forge::spawnAtLook("prop_food_van_01"); break;
    case 41: forge::spawnAtLook("prop_golf_bag_01b"); break;
    case 42: forge::spawnAtLook("prop_carwash_roller_vert"); break;
    case 43: forge::spawnAtLook("prop_skip_01a"); break;
    case 44: forge::spawnAtLook("prop_cash_crate_01"); break;
    case 45: forge::spawnAtLook("prop_dummy_plane"); break;
    case 46: forge::spawnAtLook("prop_air_lights_02a"); break;
    case 47: forge::spawnAtLook("prop_portacabin01"); break;
    case 48: forge::spawnAtLook("prop_beer_neon_01"); break;
    case 49: forge::spawnAtLook("prop_ld_haybail"); break;
	case 50: forge::spawnAtLook("prop_skate_flatramp"); break;
	case 51: forge::spawnAtLook("prop_skate_funbox"); break;
	case 52: forge::spawnAtLook("prop_skate_halfpipe"); break;
	case 53: forge::spawnAtLook("prop_skate_kickers"); break;
	case 54: forge::spawnAtLook("prop_skate_quartpipe"); break;
	case 55: forge::spawnAtLook("prop_skate_rail"); break;
	case 56: forge::spawnAtLook("prop_skate_spiner"); break;
	case 57: forge::spawnAtLook(-1211836083); break;//the cool tv from prologue, 480355301 for the same object but a different transmission
	case 58: forge::spawnAtLook(480355301); break;
	case 59: forge::spawnAtLook(-1787521651); break;
		//another tv (no pole): -1787521651
    }
	break;
#pragma endregion
/*#pragma region Forge Menu Object List Favorites
	case Forge_Menu_Object_List_Favorites:
		addTitle("Favorites");
		if (true) {
			int cur02834 = 0;
		for (int i = 0; i < 64; i++) {
			if (forge::propFavorites[i] != NULL) {
				addOption(forge::propFavorites[i]);
				cur02834++;
				if (getOption() == cur02834) {
					forge::spawnAtLook(forge::propFavorites[i]);
				}
				if (getSquareOption() == cur02834) {
					forge::propFavorites[i] = NULL;
				}
			}
		}
		}
		addKeyboardOption(getCachedString("STR716"),8,keyboardText,120,"Enter prop");   //Add A Favorite
		break;
#pragma endregion*/
#pragma region Forge_Menu_Object_List
	case Forge_Menu_Object_List:
		addTitle("Spawnables");
		//addSubmenuOption("Choose From Full List",Forge_Menu_Object_List_All);
		addSubmenuOption(getCachedString("STR717"),Forge_Menu_Object_List_Short);   //Choose From Short List
		//addSubmenuOption(getCachedString("STR718"),Forge_Menu_Object_List_Favorites);   //Choose From Favorites
		addKeyboardOption(getCachedString("STR719"),6,keyboardText,120,"Enter object");   //Custom Input
		addKeyboardOption("Custom Input (Hash)",keyboard_input_object_hash,keyboardText,120,"Enter object (hash)");   //Custom Input
		//switch(getOption()) {
		//case 1: currentOption = forge::objectListOption;break;
		//}
		break;
#pragma endregion
#pragma region Forge Attach List
	case Forge_Attach_List:
		if (1 == 1) {
			addTitle("Attach To Player");
			int start = 0;
			for (int i = 0; i < 18; i++)
			{
				char *name = PLAYER::GET_PLAYER_NAME(i);
				if (isPlayerValid(name)) {
					addOption(name);
					start++;
					if (optionPress)
					{
						if (currentOption == start) {
							forge::playerToAttachTo = i;//currentOption-1;
							changeSubmenu(Forge_Attach_List_Parts);
						}
					}
				}
			}
		}
		break;
#pragma endregion
#pragma region Forge Attach List Parts
	case Forge_Attach_List_Parts:
		addTitle("Attach To Body Part");
		addOption(getCachedString("STR720"));   //Stomach
		addOption(getCachedString("STR721"));   //Chest
		addOption(getCachedString("STR722"));   //Gentils
		addOption(getCachedString("STR723"));   //Head
		addOption(getCachedString("STR724"));   //Left Arm
		addOption(getCachedString("STR725"));   //Left Hand
		addOption(getCachedString("STR726"));   //Left Knee
		addOption(getCachedString("STR727"));   //Left Shoe
		addOption(getCachedString("STR728"));   //Left Shoulder
		addOption(getCachedString("STR729"));   //Left Wrist
		addOption(getCachedString("STR730"));   //Month
		addOption(getCachedString("STR731"));   //Right Arm
		addOption(getCachedString("STR732"));   //Right Hand
		addOption(getCachedString("STR733"));   //Right Knee
		addOption(getCachedString("STR734"));   //Right Shoe
		addOption(getCachedString("STR735"));   //Right Shoulder
		addOption(getCachedString("STR736"));   //Right Wrist
		addOption(getCachedString("STR737"));   //Umbilical
		switch(getOption()) {
		case 1: forge::attachToPlayer(forge::playerToAttachTo,PlayerMods::bones::BONE_ROOT);break;
		case 2: forge::attachToPlayer(forge::playerToAttachTo,PlayerMods::bones::Chest);break;
		case 3: forge::attachToPlayer(forge::playerToAttachTo,PlayerMods::bones::Gentils);break;
		case 4: forge::attachToPlayer(forge::playerToAttachTo,PlayerMods::bones::Head);break;
		case 5: forge::attachToPlayer(forge::playerToAttachTo,PlayerMods::bones::Left_Arm);break;
		case 6: forge::attachToPlayer(forge::playerToAttachTo,PlayerMods::bones::Left_Hand);break;
		case 7: forge::attachToPlayer(forge::playerToAttachTo,PlayerMods::bones::Left_Knee);break;
		case 8: forge::attachToPlayer(forge::playerToAttachTo,PlayerMods::bones::Left_Shoe);break;
		case 9: forge::attachToPlayer(forge::playerToAttachTo,PlayerMods::bones::Left_Shoulder);break;
		case 10: forge::attachToPlayer(forge::playerToAttachTo,PlayerMods::bones::Left_Wrist);break;
		case 11: forge::attachToPlayer(forge::playerToAttachTo,PlayerMods::bones::Month);break;
		case 12: forge::attachToPlayer(forge::playerToAttachTo,PlayerMods::bones::Right_Arm);break;
		case 13: forge::attachToPlayer(forge::playerToAttachTo,PlayerMods::bones::Right_Hand);break;
		case 14: forge::attachToPlayer(forge::playerToAttachTo,PlayerMods::bones::Right_Knee);break;
		case 15: forge::attachToPlayer(forge::playerToAttachTo,PlayerMods::bones::Right_Shoe);break;
		case 16: forge::attachToPlayer(forge::playerToAttachTo,PlayerMods::bones::Right_Shoulder);break;
		case 17: forge::attachToPlayer(forge::playerToAttachTo,PlayerMods::bones::Right_Wrist);break;
		case 18: forge::attachToPlayer(forge::playerToAttachTo,PlayerMods::bones::Umbilical);break;
		}
		break;
#pragma endregion

#pragma region Animations
	case Animation_Options:
		addTitle("Animations");
		addOption(getCachedString("STR738"));   //Stop Animations
		addOption(getCachedString("STR739"));   //Play Music
		addOption(getCachedString("STR740"));   //Take Photo
		addOption(getCachedString("STR741"));   //Binoculars
		addOption(getCachedString("STR742"));   //Drink
		addOption(getCachedString("STR743"));   //Play Golf
		addOption(getCachedString("STR744"));   //Lift Weights
		addOption(getCachedString("STR745"));   //Smoke
		addOption(getCachedString("STR746"));   //Handyman
		addOption(getCachedString("STR747"));   //Yoga
		addOption(getCachedString("STR748"));   //Flex Muscles
		addOption(getCachedString("STR749"));   //Celebrate
		addOption(getCachedString("STR750"));   //Pole Dance
		addOption(getCachedString("STR751"));   //Push-Ups
		addOption(getCachedString("STR752"));   //Suicide
		addOption(getCachedString("STR753"));   //Stripper Dance
		addOption(getCachedString("STR754"));   //Sit-Ups
		addOption(getCachedString("STR755"));   //Electrocution
		switch (getOption())
		{
		case 1: AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID()); break;
		case 2: AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MUSICIAN", 0, 1); break;
		case 3: AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_PAPARAZZI", 0, 1); break;
		case 4: AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_BINOCULARS", 0, 1); break;
		case 5: AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_DRINKING", 0, 1); break;
		case 6: AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_GOLF_PLAYER", 0, 1); break;
		case 7: AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MUSCLE_FREE_WEIGHTS", 0, 1); break;
		case 8: AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SMOKING_POT", 0, 1); break;
		case 9: AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_HAMMERING", 0, 1); break;
		case 10: AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_YOGA", 0, 1); break;
		case 11: AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MUSCLE_FLEX", 0, 1); break;
		case 12: PedAnim::anim(PLAYER::PLAYER_PED_ID(),"rcmfanatic1celebrate", "celebrate"); break;
		case 13: PedAnim::anim(PLAYER::PLAYER_PED_ID(),"mini@strip_club@pole_dance@pole_dance1", "pd_dance_01"); break;
		case 14: PedAnim::anim(PLAYER::PLAYER_PED_ID(),"amb@world_human_push_ups@male@base", "base"); break;
		case 15: PedAnim::anim(PLAYER::PLAYER_PED_ID(),"mp_suicide", "pistol"); break;
		case 16: PedAnim::anim(PLAYER::PLAYER_PED_ID(),"mini@strip_club@private_dance@part1", "priv_dance_p1"); break;
		case 17: PedAnim::anim(PLAYER::PLAYER_PED_ID(),"amb@world_human_sit_ups@male@base", "base"); break;
		case 18: PedAnim::anim(PLAYER::PLAYER_PED_ID(),"ragdoll@human", "electrocute"); break;
		}
		break;
#pragma endregion
#pragma region teleports locations
	case Teleport_Multiplayer_Locations:
	addTitle("MP Locations");
    addTeleportOption("Los Santos Airport", -1102.2910f, -2894.5160f, 13.9467f);
    addTeleportOption("Emergency Helipad", 308.9238f, -1458.9330f, 46.5095f);
    addTeleportOption("Inside IAA Building", 113.9319f, -618.5334f, 206.0465f);
    addTeleportOption("IAA Building Roof", 130.6824f, -634.9446f, 262.8510f);
    addTeleportOption("Waterfall", -597.9525f, 4475.2910f, 25.6890f);
    addTeleportOption("Bank Vault", 255.5819f, 217.6896f, 101.6834f);
    addTeleportOption("Inside FIB Building", 135.5220f, -749.0003f, 260.0000f);
    addTeleportOption("FIB Building Roof", 135.5220f, -749.0009f, 266.6102f);
    addTeleportOption("Dirtbike Trail", -1202.0910f, 2802.44f, 14.8256f);
    addTeleportOption("400k Apartment Inside", -878.5444f, -445.3285f, 125.6352f);
    addTeleportOption("400k Garage (Outside)", -795.46f, 308.89f, 85.71f);
    addTeleportOption("400k Apartment (Outside)", -775.0500f, 312.32f, 85.7f);
    addTeleportOption("400k Apartment (Roof)", -769.8004f, 331.2076f, 234.2694f);
    addTeleportOption("Airport Overwatch", -985.1005f, -2642.046f, 63.5170f);
	break;

	case Teleport_Singleplayer_Locations:
    addTitle("SP Locations");
    addTeleportOption("Franklin's New House", 7.4150, 535.5486, 176.0279);
    addTeleportOption("Franklin's Old House", -14.9693, -1436.4430, 31.1185);
    addTeleportOption("Trevor's House ", 1974.7580, 3819.4570, 33.4363);
    addTeleportOption("Michael's House", -813.6030, 179.4738, 72.1589);
    addTeleportOption("Lester's House", 1273.69, -1718.72, 54.68);
    addTeleportOption("Trevor's Meth Lab", 1397.5240f, 3607.4230f, 38.9419f);
    addTeleportOption("Wayne's Cousin's House", -1159.034, -1521.180, 10.6327);
    addTeleportOption("Trevor's Office", 97.2707, -1290.9940, 29.2688);
	break;

	case Teleport_Landmarks_Locations:
    addTitle("Landmarks");
    addTeleportOption("Maze Bank Helipad", -73.92588, -818.455078, 326.174377);
    addTeleportOption("Mount Chiliad", 496.75f, 5591.17f, 795.03f);
    addTeleportOption("Mount Chiliad (Jump)", 430.2037f, 5614.7340f, 766.1684f);
    addTeleportOption("Fort Zancudo", -2012.8470f, 2956.5270f, 32.8101f);
    addTeleportOption("Calafia Bridge", -175.2189f, 4244.1940f, 44.0730f);
    addTeleportOption("Pier", -1709.98f, -1085.03f, 13.10f);
    addTeleportOption("Lighthouse", 3433.6570f, 5175.4090f, 35.8053f);
    addTeleportOption("Cannibal Camp", -1138.67f, 4921.97f, 220.07f);
    addTeleportOption("Mount Josiah", -1186.1070f, 3849.7530f, 489.0641f);
    addTeleportOption("Los Santos Airport", -1102.2910f, -2894.5160, 13.9467f);
    addTeleportOption("Elysian Island Base", 574.3914f, -3121.3220f, 18.7687f);
    addTeleportOption("Ontop of Vinewood Logo", 776.8780f, 1175.6080f, 345.9564f);
    addTeleportOption("Trevor's Air Field", 1741.4960f, 3269.2570f, 41.6014f);
    addTeleportOption("Mount Gordo", 2948.4480f, 5323.8120f, 101.1872f);
    addTeleportOption("Prison", 1679.0490f, 2513.7110f, 45.5649f);
    addTeleportOption("Prison Gym", 1640.7910f, 2530.0440f, 45.5649f);
    addTeleportOption("Prison Tower", 1541.6290f, 2470.1400f, 62.8751f);
	break;

	case Teleport_Favorites:
		switch(getOption()) {
		case 1:
			STREAMING::REQUEST_IPL("prologue01");
			STREAMING::REQUEST_IPL("prologue01c");
			STREAMING::REQUEST_IPL("prologue01d");
			STREAMING::REQUEST_IPL("prologue01e");
			STREAMING::REQUEST_IPL("prologue01f");
			STREAMING::REQUEST_IPL("prologue01g");
			STREAMING::REQUEST_IPL("prologue01h");
			STREAMING::REQUEST_IPL("prologue01i");
			STREAMING::REQUEST_IPL("prologue01j");
			STREAMING::REQUEST_IPL("prologue01k");
			STREAMING::REQUEST_IPL("prologue01z");
			STREAMING::REQUEST_IPL("prologue02");
			STREAMING::REQUEST_IPL("prologue03");
			STREAMING::REQUEST_IPL("prologue03b");
			STREAMING::REQUEST_IPL("prologue03_grv_fun");
			STREAMING::REQUEST_IPL("prologue04");
			STREAMING::REQUEST_IPL("prologue04b");
			STREAMING::REQUEST_IPL("prologue05");
			STREAMING::REQUEST_IPL("prologue05b");
			STREAMING::REQUEST_IPL("prologue06");
			STREAMING::REQUEST_IPL("prologue06b");
			STREAMING::REQUEST_IPL("prologue06_int");
			STREAMING::REQUEST_IPL("prologuerd");
			STREAMING::REQUEST_IPL("prologuerdb");
			STREAMING::REQUEST_IPL("prologue_DistantLights");
			STREAMING::REQUEST_IPL("prologue_LODLights");
			STREAMING::REQUEST_IPL("prologue_m2_door");
			break;
		case 2:
			STREAMING::REQUEST_IPL("hei_carrier");
			STREAMING::REQUEST_IPL("hei_carrier_DistantLights");
			STREAMING::REQUEST_IPL("hei_Carrier_int1");
			STREAMING::REQUEST_IPL("hei_Carrier_int2");
			STREAMING::REQUEST_IPL("hei_Carrier_int3");
			STREAMING::REQUEST_IPL("hei_Carrier_int4");
			STREAMING::REQUEST_IPL("hei_Carrier_int5");
			STREAMING::REQUEST_IPL("hei_Carrier_int6");
			STREAMING::REQUEST_IPL("hei_carrier_LODLights");
			break;
		case 3:
			STREAMING::REQUEST_IPL("hei_yacht_heist");
			STREAMING::REQUEST_IPL("hei_yacht_heist_Bar");
			STREAMING::REQUEST_IPL("hei_yacht_heist_Bedrm");
			STREAMING::REQUEST_IPL("hei_yacht_heist_Bridge");
			STREAMING::REQUEST_IPL("hei_yacht_heist_DistantLights");
			STREAMING::REQUEST_IPL("hei_yacht_heist_enginrm");
			STREAMING::REQUEST_IPL("hei_yacht_heist_LODLights");
			STREAMING::REQUEST_IPL("hei_yacht_heist_Lounge");
			break;
		}
		addTitle("gopro_2027's Favorites");
		addTeleportOption(getCachedString("STR756"),3547.1920,-4675.1490,114.1681);   //Yankton
		addTeleportOption(getCachedString("STR757"),3069.98f,-4632.49f, 16.26f);   //Aircraft Carrier
		addTeleportOption(getCachedString("STR758"),-2043.974,-1031.582, 11.981);   //Yacht
		addTeleportOption(getCachedString("STR759"),-1909.6820,1389.1480,218.4604);   //Mini Cave
		addTeleportOption(getCachedString("STR760"),3852.0770,3625.5670,9.2139);   //Private Beach
		addTeleportOption(getCachedString("STR761"),-20.4297,-685.1064,32.3381);   //Hidden Garage
		addTeleportOption(getCachedString("STR762"),135.9541,-749.8984,258.1520);   //FBI Building
		addTeleportOption(getCachedString("STR763"),-2177.4400,5182.5960,16.4753);   //Private Island
		addTeleportOption(getCachedString("STR764"),-1159.0340,-1521.1800,10.6327);   //House
		addTeleportOption(getCachedString("STR765"),495.0000,5586.0000,794.0000);   //Chiliad
		break;

#pragma endregion
#pragma region Traffic Options
	case Traffic_Options:
		switch(getOption()) {
		case 1:TrafficMods::runTrafficMod(TrafficMods::fix);break;
		case 2:TrafficMods::runTrafficMod(TrafficMods::colorize);break;
		case 3:TrafficMods::runTrafficMod(TrafficMods::boost);break;
		case 4:TrafficMods::runTrafficMod(TrafficMods::hop);break;
		case 5:TrafficMods::runTrafficMod(TrafficMods::gayify);break;
		case 6:TrafficMods::runTrafficMod(TrafficMods::explode);break;
		case 7: VehicleMods::carmageddon();break;
		case 8:
			switch(TrafficMods::gravityType) {
			case 0: TrafficMods::runTrafficMod(TrafficMods::gravityHIGH);break;
			case 1: TrafficMods::runTrafficMod(TrafficMods::gravityNORMAL);break;
			case 2: TrafficMods::runTrafficMod(TrafficMods::gravityLOW);break;
			case 3: TrafficMods::runTrafficMod(TrafficMods::gravityNEGATIVE);break;
			}
			break;
		case 9: TrafficMods::runTrafficMod(TrafficMods::raiseSuspension);break;
		case 10: TrafficMods::runTrafficMod(TrafficMods::lowerSuspension);break;
		}
		addTitle("Traffic Options");
		addOption(getCachedString("STR766"));   //Fix And Wash
		addOption(getCachedString("STR767"));   //Paint Random
		addOption(getCachedString("STR768"));   //Boost Forwards
		addOption(getCachedString("STR769"));   //Jump Into Air
		addOption(getCachedString("STR770"));   //Gayify
		addOption(getCachedString("STR771"),"Warning: Explosions");   //Explode
		addBoolOption(getCachedString("STR772"),VehicleMods::carmageddonBool,"Just what it says (~r~POSSIBLE FREEZE WARNING~s~)");   //Carmageddon
		addArrayOption(getCachedString("STR773"),&TrafficMods::gravityType,TrafficMods::gravityTypes,4);   //Gravity
		addOption(getCachedString("STR774"));   //Raise Suspension
		addOption(getCachedString("STR775"));   //Lower Suspension
		break;
#pragma endregion
#pragma region Modder Protection Options
	case Modder_Protection_Options:
		addTitle("Modder Protection");
		//print2("Neither of these work properly.~n~I just wanted to show yall what will be in the future (hopefully)",20);
		switch(getOption()) {
		//case 1: PlayerMods::disableExplosionKilling(!PED::GET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(),342,1));break;
		case 1: 
			detachAllObjectsEnabled = !detachAllObjectsEnabled;
			//if(detachAllObjectsEnabled)
				//print("~r~You may not use guns while object protection is enabled due to possible freezes.");
			break;
		//case 2: break;//clear lag aka delete all objects constantly
		//case 3: freezeProtection(true);break;//enableVehicleModel(GAMEPLAY::GET_HASH_KEY("adder"),false);enableVehicleModel(GAMEPLAY::GET_HASH_KEY("hotknife"),false);enableVehicleModel(GAMEPLAY::GET_HASH_KEY("taxi"),false);break;
		//case 4: freezeProtection(false);break;//enableVehicleModel(GAMEPLAY::GET_HASH_KEY("adder"),true);enableVehicleModel(GAMEPLAY::GET_HASH_KEY("hotknife"),true);enableVehicleModel(GAMEPLAY::GET_HASH_KEY("taxi"),true);break;
		case 2: NETWORK::NETWORK_SET_FRIENDLY_FIRE_OPTION(0);break;//called by am_pi_menu
		case 3: NETWORK::NETWORK_SET_FRIENDLY_FIRE_OPTION(1);break;
		//case 5: teleportProtectionEnabled = !teleportProtectionEnabled;toggleTeleportProtection(teleportProtectionEnabled);break;//moneyProtection = !moneyProtection;break;
		//case 6: poolManipulations::deleteAllEntities();break;
		//case 7: poolManipulations::detachAllEntities(PLAYER::PLAYER_PED_ID());break;
		//case 4: break;//lines
		//case 5: break;//hash name
		case 4: break;//block all script events
		case 5: break;//event protection list
		case 6: break;//game_event block
		case 7: break;//block all entities
		case 8: break;//Block clones and spawned peds
		case 9: break;//block modders script events
		case 10: break;//network location spoof
		case 11: toggleNinjaMode();break;//ninja mode
		case 12: break;//auto kick
		case 13: loadNamesBypassesKick();break;
		//case 8: poolManipulations::deleteAllAttachedEntities(PLAYER::PLAYER_PED_ID());break;
		//case 7: jobProtection = !jobProtection;break;
		//case 3: write_process((char*)0x3C1768,returnfalse,8);write_process((char*)0x12FB8F4,returnfalse,8);break;//idk if it works
		//case 3: anticheater::removePropsBool=!anticheater::removePropsBool;break;
		}
		//addBoolOption("Disable Explosions",disable_explosions_bool);
		//addOption("Knock Off Props");
		//addBoolOption("Disable Modders From Using Explosions To Make You Kill People",PED::GET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(),342,1),"Kinda like how you can go into passive mode to make modders not be able to make you blow up people",false);
		addBoolOption(getCachedString("STR776"),detachAllObjectsEnabled,"Redirects to player, if attached by them");   //Object Attachment Protection
		//addOption("Enable Freeze Protection","Adder, hotknife, taxi... enabled by default");
		//addOption("Disable Freeze Protection","Adder, hotknife, taxi...");
		//addKeyboardOption("Remove Custom Vehicle",remove_vehicle_keyboard,keyboardText,100,"Enter vehicle id");
		//addKeyboardOption("Re-add Custom Vehicle",add_vehicle_keyboard,keyboardText,100,"Enter vehicle id");
		addOption(getCachedString("STR777"));   //Disable Blame Player On You
		addOption(getCachedString("STR778"));   //Enable Blame Player On You
		//addBoolOption("Teleport Protection",teleportProtectionEnabled);
		//addOption("Delete all entities","~r~Not working currently. Will in a future update.");
		//addOption("Remove all entities attached to you");
		//addBoolOption(getCachedString("STR779"),&poolManipulations::drawLineBool);   //Draw Line To All Entities
		//addBoolOption("Draw Object Hash Name On All Entities",&poolManipulations::drawNameBool);
		addBoolOption(getCachedString("STR780"),&disableAllScriptEvents,"It is recommended to leave this OFF");   //Block All Script Events
		addSubmenuOption(getCachedString("STR781"),Modder_Protection_Event_List_Options,"Chose events to block. Best to leave as-is");   //Event List
		addBoolOption(getCachedString("STR782"),GAME_AWARD_CHECK_BOOL);   //Block Admin Give XP/Money
		addBoolOption(getCachedString("STR783"),ENTITY_BLOCKER_BOOL,"Enable this if you are in a modder war. ~r~THIS OPTION CAUSES MANY BUGS, RECOMMENDED NOT TO USE.");   //Block All Networked Entities
		addBoolOption(getCachedString("STR784"),shouldSpawnPeds,"Blocks players from cloning you and freezing you with spanwed peds. Recommended to keep enabled.");   //Block clones and spawned peds
		//addOption(getCachedString("STR785"),"Test by having your friends try to freeze you with vehicle freeze!");   //Vehicle Anti-Freeze protections enabled automatically too!
		addBoolOption("Block script events from modders",&disableModderScriptEvents,"If they are a modder, automatically block all script events from them");
		//addOption("Delete all entities attached to you");
		//addBoolOption("Join Job Protection",jobProtection);
		//addOption("");
		//addOption("ALL OTHER PROTECTION IS ENABLED AUTOMATICALLY");

		//addOption("Disable Particles");//0x3C1768 /*non looped*/ and 0x12FB8F4 /*looped*/
		//addBoolOption("Remove Attached Objects",anticheater::removePropsBool);

		addSubmenuOption("Networked Location Spoofer",Modder_Protection_Location_Spoofer);

		addBoolOption("Ninja Mode",ninjaModeNetwork,"~r~EXPERIMENTAL ~s~Causes your player to not show up on map and many other quirks");
		addBoolOption("Auto Kick Modders ~y~*NEW*",&autoKickModders,"Automatically kicks modders from your lobby");
		addOption("Reload List Of Friends To Not Kick","modder_friends.txt put 1 PSN name per line, max of 20 names");
		addBoolOption("Block Player Model Changes", changeModelBoolValue_ptr, "Prevents players from changing their model into freeze models");
		//addBoolOption("No Tickiler Hickler", &notickilerhickler, "Protects you from other people freezing youuuuu");
		
		/*addBoolOption("Disable 0x138F9DC",&disable_0x138F9DC);
		addBoolOption("Disable 0xD1511C", &disable_0xD1511C);
		addBoolOption("Disable 0xA15C24", &disable_0xA15C24);
		addBoolOption("Disable 0xD1EE1C", &disable_0xD1EE1C);*/

		addBoolOption("Bunker Mode", &disable_all_events, "Powerful Anti-freeze, but will mess with game functionality");


		{
		SideInfo p;
		p.addText("Tip");
		p.addText("Enabling 'Block All Networked Entites' and 'Block clones and spawned peds' should");
		p.addText("guarentee protection from all entity based freezes, but is not necessary to have");
		p.addText("enabled all the time.");
		p.addText("Bunker mode offers more protection in modder battles.");
		p.drawBG();
		}

		break;
#pragma endregion
#pragma region Modder_Protection_Location_Spoofer
	case Modder_Protection_Location_Spoofer:
		addTitle("Networked Location Spoofer");
		addBoolOption("Spoof Your Networked Location",doCustomSpoofLocation,"Will make them think you are at the custom location");
		addFloatOption("Net Loc X",&customSpoofPosition.x,-100000000,100000000,true,0,true);
		addFloatOption("Net Loc Y",&customSpoofPosition.y,-100000000,100000000,true,0,true);
		addFloatOption("Net Loc Z",&customSpoofPosition.z,-100000000,100000000,true,0,true);
		addOption("Set Location To Golf Job Cirlce");
		addBoolOption("Spoof Location To Specific Player",&doPlayerSpoofLocation);

		{
			static char *playerArray[18];
			playerArray[customSpoofLocationPlayer] = PLAYER::GET_PLAYER_NAME(customSpoofLocationPlayer);
			addArrayOption("Player To Spoof Onto",&customSpoofLocationPlayer,playerArray,18,"Must have 'Spoof Location To Specific Player' enabled");
		}

		switch (getOption()) {
		case 1:
			toggleTeleportDataHook(); 
			if (doCustomSpoofLocation)
				print2("May cause some extra lag");
			break;
		case 5:
			customSpoofPosition.x = -1371.6047;
			customSpoofPosition.y = 58.0968;
			customSpoofPosition.z = 53.7;
			break;
		}
		break;
#pragma endregion
#pragma region Modder_Protection_Event_List_Options
	case Modder_Protection_Event_List_Options:
		addTitle("Blocking Event List");
		for (int i = 0; i < EVENT_LIST_SIZE; i++)
			addBoolOption(EVENT_NAMES[i],&eventProtectionsBool[i],0,false);
		break;
#pragma endregion
#pragma region Donations
/*	case Donators_Menu:
		addTitle("Donators");
		//addOption(donations);
		for(int i = 0; i < 15; i++)
			addOption(getCachedString("STR786"));   //
		break;*/
#pragma endregion
#pragma region UpdateLog Menu
#ifdef updatelogmenu
	case UpdateLog_Menu:
		addTitle("Update Log");
		addOption(updateLog);
		break;
#endif
#pragma endregion
#pragma region Money Generators
#ifdef moneygeneratormenu
	case Money_Generator_Menu:
		switch(getOption()) {
		case 2: Vector3 n = {0,0,0};generators::moneyGens[generators::currentGenerator].init("prop_money_bag_01",n,PLAYER::PLAYER_ID());break;
		case 3: generators::moneyGens[generators::currentGenerator].enabled = !generators::moneyGens[generators::currentGenerator].enabled;break;
		}
		//generators::doAllMoneyGens();
		//print2("Money Only Generates While In This Menu",5);
		addTitle("Money Generator");
		addIntOption(getCachedString("STR787"),&generators::currentGenerator,0,9,false);   //Current Generator
		addOption(getCachedString("STR788"));   //Reset
		addBoolOption(getCachedString("STR789"),generators::moneyGens[generators::currentGenerator].enabled);   //Enabled
		addIntOption(getCachedString("STR790"),&generators::moneyGens[generators::currentGenerator].speed,0,100,true);   //Speed
		addIntOption(getCachedString("STR791"),&generators::moneyGens[generators::currentGenerator].numberspawn,1,15,false);   //Bags To Drop
		addFloatOption(getCachedString("STR792"),&generators::moneyGens[generators::currentGenerator].radius,0,100,true,0.1);   //Radius
		//addIntOption("Player",&generators::moneyGens[generators::currentGenerator].player,-1,15,true,"-1 for detach from player");
		addSubmenuOption(getCachedString("STR793"),Money_Generator_Menu_Players);   //Attach To Player
		break;
#endif
#pragma endregion
#pragma region Forge Attach Player Auto List
#ifdef moneygeneratormenu
	case Money_Generator_Menu_Players:
		switch(getOption()) {
		case 1: generators::moneyGens[generators::currentGenerator].player = -1;
		}
		addTitle("Attach Generator To Player");
		addOption(getCachedString("STR794"));   //Take Off Player
		if (1 == 1) {
			int start = 1;//start  at 1
			for (int i = 0; i < 18; i++)
			{
				char *name = PLAYER::GET_PLAYER_NAME(i);
				if (isPlayerValid(name)) {
					addOption(name);
					start++;
					if (optionPress)
					{
						if (currentOption == start) {
							forge::attachToPlayerOnSpawn = true;
							generators::moneyGens[generators::currentGenerator].player = i;
						}
					}
				}
			}
		}
		break;
#endif
#pragma endregion
		/*
#ifdef IDONTWANTTOSAVEMEMORY
#pragma region eventCreator
	case Event_Creator:
		{
		switch(getOption()) {
		case 1: break;//arg count changer
		case 2: PlayerMods::eventCreator::players[PlayerMods::eventCreator::currentPlayerSelectedInMenu] = !PlayerMods::eventCreator::players[PlayerMods::eventCreator::currentPlayerSelectedInMenu];break;
		case 3: changeSubmenu(Event_Arg_Editor);break;
		case 4: PlayerMods::eventCreator::triggerScriptEvent();break;
		}

		addTitle("Event Creator");
		addIntOption(getCachedString("STR795"),&PlayerMods::eventCreator::argsCount,1,100,false);   //Arg Count
		//addIntOptionWhRightText(char *option,     int *var,                                              char *righttext,                                                                                    int min, int max,  char *info = NULL)
		char *righttext = "No";
		if (PlayerMods::eventCreator::players[PlayerMods::eventCreator::currentPlayerSelectedInMenu])
			righttext = "Yes";
		//char *righttext = PlayerMods::eventCreator::players[PlayerMods::eventCreator::currentPlayerSelectedInMenu]?"Yes":"No";
		addIntOptionWithRightText("Player Affected",&PlayerMods::eventCreator::currentPlayerSelectedInMenu,righttext,0,       17,       PLAYER::GET_PLAYER_NAME(PlayerMods::eventCreator::currentPlayerSelectedInMenu));
		addIntOption(getCachedString("STR796"),&PlayerMods::eventCreator::currentArgSelectedInMenu,0,PlayerMods::eventCreator::argsCount,false);   //Edit Arg
		addOption(getCachedString("STR797"));   //Run Event
		}
		break;
#pragma endregion
#pragma region Event Arg Editor
	case Event_Arg_Editor:
		{
		char title[10];
		snprintf$(title,sizeof(title),"Arg %i",PlayerMods::eventCreator::currentArgSelectedInMenu);
		int arg = PlayerMods::eventCreator::currentArgSelectedInMenu;
		addTitle(title);
		//StoF();
		addIntOption(getCachedString("STR798"),true,1,&PlayerMods::eventCreator::args[arg].i,INT_MIN,INT_MAX,true,"",false);   //Edit As Int
		addIntOption(getCachedString("STR799"),true,1,&PlayerMods::eventCreator::args[arg].i,INT_MIN,INT_MAX,true,"",true);   //Edit As Int
		addFloatOption(getCachedString("STR800"),&PlayerMods::eventCreator::args[arg].f,(float)INT_MIN,(float)INT_MAX,true,0.1,"",true);   //Edit As Float
		addKeyboardOption(getCachedString("STR801"),keyboard_edit_event_data,"",5,"Edit Event Data As Text",(char*)(&PlayerMods::eventCreator::args[arg].i));   //Edit As String
		}
		break;
#pragma endregion
#endif*/
#pragma region modloader
	case ModLoaderMenu:
		addTitle("Script Menu Loader");
		addBoolOption("Ap ii Intense (R1+[])",isScriptRunning("rock_menu2"),"A classic mod menu, recently remastered into version v2.");
		addBoolOption("Arabic Guy (R1+X)",isScriptRunning("ArabicGuy"),"A new and powerful script with many features. Dev: RFood Modz");
		addBoolOption("Console Trainer V (R1+Left)",isScriptRunning("console_trainer_v"),"Contains many useful features for exploring GTA. Dev: Evil Blunt");
		addBoolOption("K&K Dark Horse (L1+R1)",isScriptRunning("krank1"),"A small but classic mod menu. Dev: Krank");
		//addBoolOption("Map Loader (L1+O)",isScriptRunning("MapLoader"),"Contains some map mods.");
		addBoolOption("NotYourDope's (R1+Down)",isScriptRunning("NotYourDopeV4"),"A very neat menu. Dev: Not Your Dope");
		addBoolOption("ParticleMenu (Right+[])",isScriptRunning("ParticleMenu"),"Contains particle effects. Dev: Jay");
		addBoolOption("ProjectCL (Right+[])",isScriptRunning("ProjectCL"),"A new menu with some nice features. Dev: AnTrAX X MoDz");
		addBoolOption("Recovery Menu (Right+X)",isScriptRunning("Recoveryv3"),"Contains features to modify an account. Dev: 2much4u");
		addBoolOption("Spawn Car Design (L1+Triangle)",isScriptRunning("Spawncar"),"A car spawner with car images. Not all images may load.");
		addBoolOption("Ultimate Teleport Menu (R1+O)",isScriptRunning("franklinz"),"A mod menu with a neat design and some basic features.");
		addBoolOption("Ultimate Teleport Menu 2.5 (R1+O)", isScriptRunning("Tgsaudoiz"), "A mod menu with a neat design and some basic features.");
		//addBoolOption("James Reborn Recovery Menu",isScriptRunning("JRrecovery"),"Has many very useful recovery features");
		
		addBoolOption("Toggle Modloader Script",isScriptRunning("ModLoader"),"Toggles ModLoader.csc");
		//addBoolOption("ScriptInstancesDebug", isScriptRunning("ScriptInstancesDebug"), "");
		//addBoolOption("ur Script",isScriptRunning("Unrestrained"),"Toggles Murc");
		{
		SideInfo p;
		p.addText("Info");
		p.addText("You can install/uninstall the scripts");
		p.addText("from the 'Settings' submenu.");
		p.addText("Disclaimer:");
		p.addText("Credits to each menu goes to their");
		p.addText("individual creators. Paradise does not");
		p.addText("take credit for any of these script menus.");
		p.addText("Some menus may also have buggy features or options.");
		p.drawBG();
		}
		switch (getOption()) {
		case 1:
			{
				static int menu = 0;
				ToggleScript("rock_menu2",0x07E8,&menu);
			}
			break;
		case 2:
			{
				static int menu = 0;
				ToggleScript("ArabicGuy",6304/*0x07E8*/,&menu);
			}
			break;
		case 3:
			{
				static int menu = 0;
				ToggleScript("console_trainer_v",0x400,&menu);
			}
			break;
		case 4:
			{
				static int menu = 0;
				ToggleScript("krank1",0x400,&menu);
			}
			break;
		/*case 5:
			{
				static int menu = 0;
				ToggleScript("MapLoader",0x400,&menu);
			}
			break;*/
		case 5:
			{
				static int menu = 0;
				ToggleScript("NotYourDopeV4",0x07E8,&menu);
			}
			break;
		case 6:
			{
				static int menu = 0;
				ToggleScript("ParticleMenu",0x400,&menu);
			}
			break;
		case 7:
			{
				static int menu = 0;
				ToggleScript("ProjectCL",0x400,&menu);
			}
			break;
		case 8:
			{
				static int menu = 0;
				ToggleScript("Recoveryv3",0x400,&menu);
			}
			break;
		case 9:
			{
				static int menu = 0;
				ToggleScript("Spawncar",0x400,&menu);
			}
			break;
		case 10:
			{
				static int menu = 0;
				ToggleScript("franklinz",0x400,&menu);
			}
			break;
		case 11:
		{
			static int menu = 0;
			ToggleScript("Tgsaudoiz", 1820, &menu);
		}
		break;
		/*case 11:
			{
				static int menu = 0;
				ToggleScript("JRrecovery",/0x400/1820,&menu);
			}
			break;*/
		case 12:
			{
				static int menu = 0;
				ToggleScript("ModLoader",0x400,&menu);
			}
			break;
		/*case 13:
		{
			static int menu = 0;
			ToggleScript("ScriptInstancesDebug", 2552, &menu);
		}
		break;*/
		/*case 12:
			{
				static int menu = 0;
				ToggleScript("Unrestrained",2024,&menu);
			}
			break;*/
		}
		break;
#pragma endregion
#pragma region Settings
	case Settings:
		static char busdfgsadfgsadasdf[] = "0";
		busdfgsadfgsadasdf[0] = '0';
		addTitle("Settings");
		//addSubmenuOption("Banners", Settings_Banners);
		//addSubmenuOption("Body", Settings_Body);
		//addSubmenuOption("Scroller", Settings_Scroller);
		addBoolOption("3D Menu Design *NEW*",&special3DMenuDesign,"Special 3D Menu Design",false);
		if (special3DMenuDesign) {
			addFloatOption(getCachedString("STR802"),&scaleformScale,0.0f,5.0f,true);   //Menu Scale
		} else {
			addFloatOption(getCachedString("STR802"),&textSize,0.1f,5.0f,true);   //Menu Scale
		}
		addIntOption(getCachedString("STR803"), &optionsFont, 0, 7, false);   //Text Font
		//addSubmenuOption("Indicators", Settings_Indicators);
		addBoolOption(getCachedString("STR804"), menuSounds,NULL,false);   //Sounds
		addBoolOption(getCachedString("STR805"), instructions,NULL,false);   //Instructions
		//addCustomBoolOption("Left Sided", menuXCoord, 0.145f);
		addIntOption(getCachedString("STR806"), &maxOptions, 1, 25, false,0);   //Max Options
		addIntOption(getCachedString("STR807"),&fastScrollSpeed,1,5,false);   //Fast Scroll Speed
		addBoolOption(getCachedString("STR808"),useMenuRemembrence,"Remember the last option used on every menu (not just previous menu's)",false);   //All Menu Option Rememberence
		addFloatOption(getCachedString("STR809"),&minimumMenuWidth,0,0.5,false,0.01f,"Set The Minimum Menu Width");   //Minimum Menu Width
		//addOption("Clear Debug Text");
		//addKeyboardOption("Run A Script",9,keyboardText,128,"Put In Pastebin ID or 8 zeros (00000000) to load ParadiseScript.txt","No longer working");
		//addBoolOption(getCachedString("STR810"),minimalistic,"Disabled extra ui features");   //Minimalist Mode
		
		addOption(doDownloadRPF==false?(char*)"Install Paradise Script Menus":(char*)"Download in progress! Please wait patiently.","Will load alongside your current update.rpf");
		addOption(doDownloadRPF==false?(char*)"Un-Install Paradise Script Menus":(char*)"Download in progress! Please wait patiently.","Uninstalls the extra scripts");
		addOption("Install Tsunami Mod","Restart Required");
		addOption("Uninstall Tsunami Mod","Restart Required");
		addOption("Download Fresh settings.xml File","This will overrite your current settings.xml file");
		addOption("Install Paradise Update.RPF","Will use this update.rpf instead of your current one in USRDIR (Does NOT overrite your update.rpf)");
		addOption("Delete Paradise Update.RPF");
		addBoolOption("Draw IP Info On Players", &doDrawIPInfo, "For streamers if they want to disable ip info");
		//addBoolOption("Network Debug Log", isNetworkDebugEnabled());
#ifdef sJKFghjsadfjkgh
		addOption("Start");
		addOption("Stop");
#endif



#ifdef oldrce_in_settings



		//static int testValueForIt = 0;
		//static int testValueForItImm = 0;
		addOption("Start freemode script");

		static int indexChosen = 0;
		static int indexValue = 0;
		addIntOption("Address", false, 4, &indexChosen, -2147483648, 2147483647, true, "", true);
		addIntOption("Value", false, 1, &indexValue, -2147483648, 2147483647, true, "", true);
		//char sdfkjgjhdfskjg[100];
		//int g_val = indexChosen;
		//int g_addr = Read_Global_Address(g_val);
		//int r_addr = Read_Global_Address(1666041+1) + (indexChosen-(1666041+1))*4;

		snprintf(global_temporary_buf, sizeof(global_temporary_buf), "(Write) Address: 0x%X", indexChosen);//"(Execute) Global: %i, Address: 0x%X, r_a: 0x%X",g_val,g_addr,r_addr);
		addOption(global_temporary_buf);
		snprintf(global_temporary_buf, sizeof(global_temporary_buf), "(Read) Address: 0x%X", indexChosen);//"(Execute) Global: %i, Address: 0x%X, r_a: 0x%X",g_val,g_addr,r_addr);
		addOption(global_temporary_buf);

		static int playerToExploitOn = 0;
		int hostPlayer = NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0);
		if (hostPlayer != PLAYER::PLAYER_ID())
			playerToExploitOn = hostPlayer;
		addIntOption("(Phase 0) Player To Exploit On", &playerToExploitOn, 0, 17, false, PLAYER::GET_PLAYER_NAME(playerToExploitOn));
		addOption("(Phase 1) Init rcev5", "PLEASE READ INSTRUCTIONS");
		//addIntOption("(Phase 2) Base Search Range",true,1,&recv5searchRange,0,99/* -99 is the largest it will display in the 4 bytes*/,true,"Larger values are more likely to freeze, but may not find it");
		//addOption("(Phase 2) Find Base Search (Method A)");
		//addOption("(Phase 2) Find Base Search (Method B)");
		//addKeyboardOption("(Phase 3) Enter in result from base search",keyboard_input_rcev5_mult,"",4,"Enter in the number that the players name was set to","Ask the player to open player list and say their new number name");
		addOption("(Phase 2) Search for start");
		//addOption("[Test] Set their name to \"1337\"");
		addOption("[Test] Check to make sure address is correct and BLUS check");
		addKeyboardOption("Set the message to send", keyboard_input_rcev5_str, rcev5TestMessageBuffer, 120, "Enter a message");
		addOption("Turn Message On");
		addOption("Turn Message Off");
		addOption("Invisibility");
		addOption("(Phase 3) Find Player Pointers");
		addOption("Set Health High");
		addOption("Set Health Low");
		addOption("Godmode On");
		addOption("Godmode Off");
		//addOption("Super Run");
		addBoolOption("Tethered Mod Menu", doPlayerRCEMenu);
		addOption("Notify Their Addresses");
		addOption("RPF Injection");
		addOption("Check Invisibility Value");
		addOption("debug echo Freemode Script Data");
		//addBoolOption("Do the negative check (don't use this!)",&doRCEV5NegativeFix);
		addOption("(Phase 4) Find values for script RCE");
		addOption("(Phase 5) Initiate the script RCE patch");
		//playerToDoRCEOn
		addIntOption("Change Player To RCE On", &playerToDoRCEOn, 0, 17, false, PLAYER::GET_PLAYER_NAME(playerToDoRCEOn), "This is for if you go to a new lobby and already did all the setup through 5");
		addOption("Set model alien");
		addOption("test name set new");
		addOption("Set model test via threaded invoker");
		addOption("(a) Copy Script To Remote System");
		addOption("(b) Req Script Load");
		addOption("(c) Overrite Loaded Script With Copied Script");
		addOption("(d) Start Script");
		addIntOption("Script Stack Size On Start", &rceThread::scriptStackSize, 0, 99999999, true);
		addBoolOption("Output test vals",&outputTheEchoTestValues);
#endif





		//static int testValueForIt = 0;
		//static int testValueForItImm = 0;
		//addOption("Start freemode script");
		
		
		//addIntOption("Timeout test value",&timeoutvaluetest,0,100,true);
		//addOption("Test set them host");
		//static int valueOfSearch = 0;
		//addIntOption("Manual base search (click to check)",&valueOfSearch,-20,20,false);

		//addKeyboardOption("Custom Input (Hash)",keyboard_input_object_hash,keyboardText,120,"Enter object (hash)");
		//addIntOption("Move Base Value (Click for info)",true,4096,&addOnToBaseExploitAddress,-2147483644,2147483644,false);
		/*addIntOption("Choose index",&testValueForIt,0,14,false);
		addOptionWithRightwardText("Global ID",ItoS(hostGlobalsArr[testValueForIt]));
		addIntOption("Choose Imm (Click to set)",&testValueForItImm,0,hostGlobalsArrSize[testValueForIt]-1,true);
		addOptionWithRightwardText("Value Of Global",ItoS(Read_Global(hostGlobalsArr[testValueForIt]+testValueForItImm)));
		static int testValueOfG = 0x7FFFFFFF;
		addIntOption("Choose Value (Click To Set)",&testValueOfG,-2147483648,2147483647,true);

		static int globalChosen = 2;
		static int globalValueAdd = 1;
		addIntOption("Choose Global",true,8,&globalChosen,0,2147483647,true);
		addIntOption("Value",&globalValueAdd,0,2147483647,true);
		addOptionWithRightwardText("Value Of Global (Click to test exploit)",ItoS(Read_Global(globalChosen)));
		addOption("Test rce v3 p1");
		addOption("Test rce v3 p2");
		static int testIndexV4 = 0;
		addIntOption("Test v5",&testIndexV4,-999999,999999,true);

		addOptionWithRightwardText(ItoS(2390071+1+testIndexV4),ItoS(Read_Global(2390071+1+testIndexV4)));*/
		/*
		static int hudColorIndex = 140;
		//addIntOption("Hud Color Index",true,1,&hudColorIndex,0,0xB5,true,"140 aka 0x8C is 3D menu color",true);
		int r,g,b,a;
		get_hud_color_rgb(hudColorIndex,&r,&g,&b,&a);
		addIntOption("3D menu Background Color Red",true,1,&r,0,255,false,0,true);
		addIntOption("3D menu Background Color Green",true,1,&g,0,255,false,0,true);
		addIntOption("3D menu Background Color Blue",true,1,&b,0,255,false,0,true);
		addIntOption("3D menu Background Color Alpha",true,1,&a,0,255,false,0,true);
		set_hud_color_rgb(hudColorIndex,r,g,b,a);
		
		addOption("Set 3D Menu Background Color");*/
		
		/*addFloatOption("3D Menu Sharpness",&ScaleformLib::RAGE::sharpness,0.0f,100.0f,true,0.1f,"Higher sharpness causes more lag",true,true);
		addFloatOption("3D Menu Unk1",&ScaleformLib::RAGE::unk1,0.0f,100.0f,true,0.1f,0,true,true);
		addFloatOption("3D Menu Unk2",&ScaleformLib::RAGE::unk2,0.0f,100.0f,true,0.1f,0,true,true);
		*/



		/*
		static char *playerArray[18];
		playerArray[playerToSpoofDataTo] = PLAYER::GET_PLAYER_NAME(playerToSpoofDataTo);
			
		addArrayOption("Spoof Location Player",&playerToSpoofDataTo,playerArray,18,"Choose spoof to player");   //Send To Player
		*/



		//addIntOption("Event Number",&globalEvtChooser,0,5,true);
		//addOption("DL fresh bgxml");

		//addBoolOption("test render",&drawTestImage);
		//addOption("Original Register");
		//addOption("Reinstall bg scripts debug");


		//addOption("Trigger load");
		//addBoolOption("Tes This",&didit);
		//addOption("testf reeze");
		//addOption("print script info");
		//addBoolOption("Toggle audiotest script",isScriptRunning("audiotest"));
		//addBoolOption("Toggle arabicguy script",isScriptRunning("ArabicGuy1"));
		//addOption("Set No Script");
		//addOption("Set Arabic Guy Script");
		//addIntOption("Script Stack Size",&global_scriptStackSize,0,1000000,true);
		//addBoolOption("Toggle Script",isScriptRunning(getvalentinerpreward2()));
		//addOption("Reload Script From File");
		//addBoolOption("Toggle Paradise Modloader Script",isScriptRunning("ModLoader"),"Open: L3 + R3");
		//addBoolOption("Load Arabic Guy",isScriptRunning("ArabicGuy"));
		
		switch (getOption())
		{
		case 4: menuSounds = !menuSounds; break;//6
		case 5: instructions = !instructions; break;//7
		/*case 8:
			if (menuXCoord == 0.145f)
			{
				menuXCoord = 0.845f;
				textXCoord = 0.76f;
			}
			else
			{
				menuXCoord = 0.145f;
				textXCoord = 0.06f;
			}
			break;*/
		//case 9: break;
		//case 10: break;
		case 8: useMenuRemembrence = !useMenuRemembrence;break;//11
		//case 12: break;
		//case 8: strncpy(printMessages1,"",sizeof(printMessages1));strncpy(printMessages2,"",sizeof(printMessages2));strncpy(printMessages3,"",sizeof(printMessages3));strncpy(printMessages4,"",sizeof(printMessages4));strncpy(printMessages5,"",sizeof(printMessages5));break;//for (int i = 0; i < 5; i++)printMessages[i] = "";break;   13
		//case 9: minimalistic = !minimalistic;break;//15

		
		case 10: //char bugsdfsdfsdfsdfehrdytjhrf[] = "1";
				busdfgsadfgsadasdf[0] = '1';
				 //writeToFile("/dev_hdd0/tmp/gopro_2027/customscripts.txt",bugsdfsdfsdfsdfehrdytjhrf,1);
				 //break;
				 //uninstallRPF=false;doDownloadRPF = true;break;
		case 11: 
				 writeToFile("/dev_hdd0/tmp/gopro_2027/customscripts.txt",busdfgsadfgsadasdf,1);
				 print2("~g~Reload GTA to take effect!");
				 break;
				 //uninstallRPF=true;doDownloadRPF = true;break;
		case 12: 
			installTsunamiMod = true;
			print2("Please wait...");
			break;
		case 13: 
			if (doesFolderExist("/dev_hdd0/tmp/gopro_2027/tsunami_water.xml")) {
				deleteFile("/dev_hdd0/tmp/gopro_2027/tsunami_water.xml");
				print2("~g~Deleted!");
			} else {
				print2("~r~File does not exist!");
			}
			break;
		case 14: downloadNewSettingsFile = true;print2("Downloading...");break;
		case 15: downloadNewRPFFile = true;print2("Downloading...");break;
		case 16:
			if (doesFolderExist("/dev_hdd0/tmp/gopro_2027/Paradise.rpf")) {
				deleteFile("/dev_hdd0/tmp/gopro_2027/Paradise.rpf");
				print2("~g~Deleted!");
			} else {
				print2("~r~File does not exist!");
			}
			break;

		/*case 17:
			toggleNetworkDebug();
			break;*/


#ifdef sJKFghjsadfjkgh
		case 18:
			printf("Started\n");
			findGamersInit();
			break;
		case 19:
			printf("Stopped\n");
			findGamersStop();
			break;
#endif








#ifdef oldrce_in_settings




		case 17:
		{
			static int menu = 0;
			ToggleScript("freemode", 21000, &menu);
		}
		break;
		/*case 20:
		case 22: print2("~g~Set!");Write_Global(hostGlobalsArr[testValueForIt]+testValueForItImm,testValueOfG);break;
		case 25: print2("yay");executeRCEV2(selectedPlayer,globalChosen,globalValueAdd);break;
		case 26: testExecuteRCEV3();break;
		case 27: testExecuteRCEV3p2();break;
		case 28: executeRCEV4(0,2390071+1+testIndexV4);print2("ayy");break;*/


		case 20:
			print2("Written");
			//echoStartValueOfItAddress(playerToExploitOn,indexChosen);
			executeRCEV5Address(playerToExploitOn, indexChosen, indexValue);
			break;
		case 21: print2("Read (console)"); echoStartValueOfItAddress(playerToExploitOn, indexChosen); break;
		case 22: break;//player name
		case 23:
			hasRCEScriptbennSetup = false;//so you can't accidentally do rce stuff. Only set after you click the patch freemode script to find the address
			doRCEV5NegativeFix = true;//set to true after reset
			readyForFinalRCE = false;
			initRCEV5();
			break;
		case 24: print2("Searching...", 5000); startNewFindData(playerToExploitOn); break;//findRCEV5StartValue_init(playerToExploitOn);break;
		/*case 24:
			//setPlayerNameRCEV5(selectedPlayer);
			findRCEV5BaseByNameA(playerToExploitOn);
			break;
		case 25:
			findRCEV5BaseByNameB(playerToExploitOn);
			break;
		case 26:break;//text input the base that was found
			*/
		case 25: checkGameVersion(); break;//setPlayerNameRCEV5(playerToExploitOn,0x31333337);break;
		case 26: break;//message set
		case 27: renderTextForPlayerRCEV5(playerToExploitOn, rcev5TestMessageBuffer, true); break;//message on
		case 28: renderTextForPlayerRCEV5(playerToExploitOn, rcev5TestMessageBuffer, false); break;//message off
		case 29: print2("set invisibility"); executeRCEV5Address(playerToExploitOn, 0x15734C4, 0x38800000); break;//invisibility
		case 30: print2("Finding values..."); findAddressesOfPlayerRCE(playerToExploitOn); break;
		case 31: print2("set high"); setRCEPlayersHealth(9999999.0f); renderTextForPlayerRCEV5(playerToExploitOn, "Health Maxed", true); break;
		case 32: print2("set low"); setRCEPlayersHealth(0); renderTextForPlayerRCEV5(playerToExploitOn, "Health 0", true); break;
		case 33: print2("set on"); setRCEPlayerGodmode(true); renderTextForPlayerRCEV5(playerToExploitOn, "Godmode On", true); break;
		case 34: print2("set off"); setRCEPlayerGodmode(false); renderTextForPlayerRCEV5(playerToExploitOn, "Godmode Off", true); break;
		case 35: doPlayerRCEMenu = !doPlayerRCEMenu; renderTextForPlayerRCEV5(playerToExploitOn, "", false); break;
		case 36: notifyPlayerAddressesTest(); break;
		case 37: print2("Done!"); injectRPFOnPlayer(playerToExploitOn); break;
		case 38: print2("Read 0x15734C4 (console)"); echoStartValueOfItAddress(playerToExploitOn, 0x15734C4); break;
		case 39: {
			printf("Hash of freemode: 0x%X\n", GAMEPLAY::GET_HASH_KEY("freemode"));
			N4rage10scrProgramE* s = findScript(GAMEPLAY::GET_HASH_KEY("freemode"));
			printf("freemode N4rage10scrProgramE address: 0x%X\n", s);
			debug_output_address(0x9C6EC);
		}
			   break;
		case 40: patchNegativeRCEBug(playerToExploitOn); break;//(Phase 4) Find values for script RCE
		case 41: setupPlayerRCEOnTriggerScript(); break;//(Phase 5) Initiate the script RCE patch (should work same on bles and blus)
		case 42: break;//rce player chooser
		case 43: print2("Set!"); setPlayerPedTest(); break;
		case 44: {
			print2("Set!");
			int arr[] = { 0x4f692048, 0x61780000 };
			callRCEWriteFunction(0x41143344, 2, arr);
			break;
		}
		case 45: rceThread::doTestRank = true; break;//should be set to alien
		case 46: rceThread::doInjectScriptIntoMemory = true; break;
		case 47: /*SCRIPT::REQUEST_SCRIPT("fm_deathmatch_creator");*/rceThread::requestScriptLoad = true; break;
		case 48: /*if (SCRIPT::HAS_SCRIPT_LOADED("fm_deathmatch_creator")){rceThread::injectScript = true;} else {print2("Not loaded yet\n");}*/rceThread::injectScript = true; break;
		case 49: /*GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("fm_deathmatch_creator");SYSTEM::START_NEW_SCRIPT("fm_deathmatch_creator", 0x07E8);*/rceThread::startScript = true; break;
			//setPlayerPedTest();break;
		case 50: break;//stack size

#endif








		/*case 17:
			testTheGlobals(testValueForIt);
			print2("Ran");
			break;*/
		/*case 17:
			{
				static int menu = 0;
				ToggleScript("freemode",21000,&menu);
			}
			break;
		*/
		//case 35: print2("set super run");//0x411433DC float walk speed, 1.0 default
		//case 36: print2("Time scale set");//0x1CC57A8 float time scale, 1.0 default
		//case 31: print2("Tested");assureHostOfFreemode(playerToExploitOn);break;

		//case 26: testFindPlayersName(selectedPlayer,valueOfSearch);print2("Click until their name is the same as the number");break;

		/*case 23:
			someTestStuffRCEV5Local();
			break;*/
		/*case 19:
			reloadScaleform(scaleformName);
			break;*/
#ifdef registercode2
		case 13: break;
		case 14:
			{
			int i = registerFile(/*"bgscripts_cloud:/ArabicGuy.csc",*/"ArabicGuy.csc");//registerFile("/dev_hdd0/tmp/gopro_2027/customimage.ctd","customimage.ctd");
			printf("Registered original %i\n",i);
			}
			break;
#endif
		/*case 13:
			invoke<int>(0x98EFB921);
			print2("re-ran\n");
			break;*/

		/*case 15:
			{
			int i = registerFile2("/dev_hdd0/tmp/gopro_2027/customimage.ctd","customimage.ctd");
			printf("Registered New %i\n",i);
			}
			break;*/
		/*case 13:
			triggerSafeLoadFunc();
			print2("triggered\n");
			break;*/
		/*case 12:break;
		case 13:
			print2("did it\n");
			callFreezeMethod();
			break;*/
		/*case 11:
			N4rage10scrProgramE *script = findScript(joaat("audiotest"));
			if (VALID_ADDR(script)) {
				printf("audiotest script found! Status: %i, Code segment: 0x%X\n",script->status,*(int*)script->goodPointer1);
			} else {
				printf("Could not find audiotest script\n");
			}
			break;*/
		//case 11:
			//ToggleScript("audiotest");
			/*if (!VALID_ADDR(defaultBGScript.memoryAddress)) {
				printf("Loading default script\n");
				loadBgScriptInfo("/dev_hdd0/tmp/gopro_2027/scripts/script_default.rpf",&defaultBGScript);
			}
			injectBgScriptInfo(&defaultBGScript);
			global_scriptStackSize = 1024;
			reloadScript();*/
			//startScript("none",1024);
			//break;
		//case 12:
			//ToggleScript("ArabicGuy1",2024);
			//startScript("ArabicGuy",2024);
			//break;
		/*case 11:
			//script stack size
			break;
		case 12:
			ToggleScript(getvalentinerpreward2(),global_scriptStackSize );
			break;*/

		/*case 13:
			//terminate_thread_by_name(getvalentinerpreward2());
			GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(getvalentinerpreward2());
			break;*/
		/*case 13:
			//invoke<int>(0x98EFB921);//download bg scripts
			reloadScript();
			print2("Reloaded script!\n");
			break;*/
		/*case 12:
			//print2("trying to load");
			
			ToggleScript("ModLoader",1024, &modloaderScriptID);
			break;*/
		/*case 15:
			//print2("trying to load");
			static int arabigGuyScriptSave = 0;
			ToggleScript("ArabicGUy",2024, &arabigGuyScriptSave);
			break;*/
		/*case 14:
			ToggleScript("ArabicGuy",2024,lastStartedScriptID);
			print2("Loaded arabic guy!\n");
			break;*/
		/*case 15:
			GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("ArabicGuy");
			printf("Terminated arabicguyy\n");
			break;*/
		}
		
		SideInfo p;
		p.addText("Debug Info");
		p.addText("Veh Addr:");
		p.addText(ItoSH((unsigned int)getCObjFromIndex(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),false))));
		p.addText("Ped Addr:");
		p.addText(ItoSH((unsigned int)getCObjFromIndex(PLAYER::PLAYER_PED_ID())));
		p.addText("Player Info:");
		p.addText(ItoSH((unsigned int)getCNetGamePlayer(PLAYER::PLAYER_ID())));
		//p.addText("Instances of script running:");
		//p.addText(ItoS((unsigned int)(SCRIPT::_0x029D3841(GAMEPLAY::GET_HASH_KEY(getvalentinerpreward2())))));
		//p.addText(ItoS(get_gta_thread_count(getvalentinerpreward2())));
		//p.addText(ItoS(get_gta_thread_count("ArabicGuy")));
		//printf("Count valentines %i\n",get_gta_thread_count(getvalentinerpreward2()));
		//printf("Count arabbic %i\n",get_gta_thread_count("ArabicGuy"));
		p.drawBG();
		break;

		/*
	case Settings_Banners:
		addTitle("Banners");
		addIntOption(getCachedString("STR811"), &bannerTextRed, 0, 255, true);   //Text Red
		addIntOption(getCachedString("STR812"), &bannerTextGreen, 0, 255, true);   //Text Green
		addIntOption(getCachedString("STR813"), &bannerTextBlue, 0, 255, true);   //Text Blue
		addIntOption(getCachedString("STR814"), &bannerTextOpacity, 0, 255, true);   //Text Opacity
		addIntOption(getCachedString("STR815"), &bannerTextFont, 0, 7, false);   //Text Font
		addIntOption(getCachedString("STR816"), &bannerRectRed, 0, 255, true);   //Rect Red
		addIntOption(getCachedString("STR817"), &bannerRectGreen, 0, 255, true);   //Rect Green
		addIntOption(getCachedString("STR818"), &bannerRectBlue, 0, 255, true);   //Rect Blue
		addIntOption(getCachedString("STR819"), &bannerRectOpacity, 0, 255, true);   //Rect Opacity
		break;
	case Settings_Body:
		addTitle("Body");
		addIntOption(getCachedString("STR820"), &optionsRed, 0, 255, true);   //Text Red
		addIntOption(getCachedString("STR821"), &optionsGreen, 0, 255, true);   //Text Green
		addIntOption(getCachedString("STR822"), &optionsBlue, 0, 255, true);   //Text Blue
		addIntOption(getCachedString("STR823"), &optionsOpacity, 0, 255, true);   //Text Opacity
		addIntOption(getCachedString("STR824"), &optionsFont, 0, 7, false);   //Text Font
		addIntOption(getCachedString("STR825"), &backgroundRed, 0, 255, true);   //Rect Red
		addIntOption(getCachedString("STR826"), &backgroundGreen, 0, 255, true);   //Rect Green
		addIntOption(getCachedString("STR827"), &backgroundBlue, 0, 255, true);   //Rect Blue
		addIntOption(getCachedString("STR828"), &backgroundOpacity, 0, 255, true);   //Rect Opacity
		break;
	case Settings_Scroller:
		addTitle("Scroller");
		addIntOption(getCachedString("STR829"), &scrollerRed, 0, 255, true);   //Red
		addIntOption(getCachedString("STR830"), &scrollerGreen, 0, 255, true);   //Green
		addIntOption(getCachedString("STR831"), &scrollerBlue, 0, 255, true);   //Blue
		addIntOption(getCachedString("STR832"), &scrollerOpacity, 0, 255, true);   //Opacity
		break;
	case Settings_Indicators:
		addTitle("Indicators");
		addIntOption(getCachedString("STR833"), &indicatorRed, 0, 255, true);   //Red
		addIntOption(getCachedString("STR834"), &indicatorGreen, 0, 255, true);   //Green
		addIntOption(getCachedString("STR835"), &indicatorBlue, 0, 255, true);   //Blue
		addIntOption(getCachedString("STR836"), &indicatorOpacity, 0, 255, true);   //Opacity
		break;
		*/
#pragma endregion
	

#pragma region RCE

	static int playerToExploitOn = 0;
	case RCE_Mods:
	{

		addTitle("Give Real Mods");
		//addIntOption("Chosen Player", &playerToExploitOn, 0, 17, false);
		addSubmenuOption("Choose Player", RCE_Mods_PlayerChooser);
		addSubmenuOption("Initialization Process", RCE_Mods_Init);
		addSubmenuOption("Mods", RCE_Mods_Mods);

		//int hostPlayer = NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0);

		SideInfo p;

		p.addText("Info:");
		p.addText("These are next level mods which allow you to do stuff to the player");
		p.addText("which would normally require them to own a CFW and Mod Menu!");
		p.addText("");
		p.addText("Host of lobby (initialize on them for 'Host Spoof Kick' to work):");
		p.addText(PlayerMods::getHost());
		p.addText("");

		p.addText("~b~Player You Are Currently Modding:");
		p.addText(PLAYER::GET_PLAYER_NAME(playerToExploitOn));
		/*if (hostPlayer != PLAYER::PLAYER_ID()) {
			//p.addText(ItoS(hostPlayer));
			p.addText(PLAYER::GET_PLAYER_NAME(hostPlayer));
		} 
		else
			p.addText("Not ready yet...");*/
		
		
		p.drawBG();

	}
		break;

	case RCE_Mods_PlayerChooser:
		addTitle("Choose A Player");
		for (int i = 0; i < 18; i++) {
			addOption(PLAYER::GET_PLAYER_NAME(i));
		}

		{
			int o = getOption();
			if (o != 0) {
				playerToExploitOn = o - 1;
				goBackASubmenu();
			}
		}

		{
			SideInfo p;
			p.addText("Info:");
			p.addText("Choose a player to do the special mods on.");
			p.addText("");
			p.addText("The host of the lobby is (choose them for 'Host Spoof Kick' to work):");
			p.addText(PlayerMods::getHost());
			p.drawBG();
		}
		break;

	case RCE_Mods_Init:
	{
		addTitle("Initialization");
		
		/*int hostPlayer = NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0);
		if (hostPlayer != PLAYER::PLAYER_ID())
			playerToExploitOn = hostPlayer;*/

		addOption("(Phase 1) Initialize Start");
		addOption("(Phase 2) Search for data","~r~If this fails or takes longer than 30 seconds, try again");
		addOption("(Phase 3) Check for BLES or BLUS");
		addOption("(Phase 4) Work Part A");//Get Some Player Info
		addOption("(Phase 5) Work Part B");//Find values for script RCE
		addOption("(Phase 6) Work Part C");//Initiate the script RCE patch
		//addBoolOption("valueForTesting", &valueForTesting);

		
		SideInfo p;
		p.addText("Important Info");
		p.addText("It is common for 'Phase 2' to take multiple tries.");
		p.addText("Please expect bugs. This is a very complex mod.");
		p.addText("");
		p.addText("~b~Player You Are Currently Modding:");
		p.addText(PLAYER::GET_PLAYER_NAME(playerToExploitOn));
		
		p.drawBG();

		switch (getOption()) {
		case 1:
			print2("Working...",10000);
			phase2PercentOutputBool = false;
			hasRCEScriptbennSetup = false;//so you can't accidentally do rce stuff. Only set after you click the patch freemode script to find the address
			doRCEV5NegativeFix = true;//set to true after reset
			readyForFinalRCE = false;
			rceThread::abortAllCalls = true;//abort any current calls because we are resetting
			initRCEV5(playerToExploitOn);
			break;

		case 2:
			print2("Working...", 10000);
			phase2PercentOutputBool = false;
			startNewFindData(playerToExploitOn); 
			break;

		case 3:
			print2("Working...", 10000);
			readyForRCEReadValue = true;
			checkGameVersion(); 
			break;

		case 4:
			print2("Working...", 10000);
			readyForRCEReadValue = true;
			findAddressesOfPlayerRCE(playerToExploitOn);
			break;

		case 5: 
			print2("Working...", 10000);
			readyForRCEReadValue = true;
			patchNegativeRCEBug(playerToExploitOn); 
			break;

		case 6: 
			print2("Working...", 10000);
			readyForRCEReadValue = true;
			setupPlayerRCEOnTriggerScript(); 
			break;



		}
		
	}
		break;


	case RCE_Mods_Mods:
	{
		addTitle("Mods List");
		addSubmenuOption("~y~Mod Menu Injector", RCE_Mods_MenuInjector);
		addSubmenuOption("~y~Host Spoof Kick (Unpatchable Player Kick)", RCE_Mods_KickList);//playerToDoRCEOn
		addSubmenuOption("Model Changer", RCE_Mods_ModelChanger);
		addSubmenuOption("Stats Manager", RCE_Mods_StatFileSelector);
		//addOption("Set Health High");
		//addOption("Set Health Low");
		addOption("Godmode On");
		addOption("Godmode Off");
		addOption("Disable Cops");
		addOption("Enable Cops");
		addOption("~r~Temp Ban Player");
		//addOption("~r~Kick This Player");
		addOption("~r~Freeze Player Console");
		addOption("~y~Outfit Changer");
		addOption("Teleport To North Yankton");
		addOption("Teleport To Yacht");
		addOption("Remove Ocean Water","Removes the ocean water on their game");
		addOption("~r~Disable SPRX","Will FREEZE them if they are not a modder");
		
		  //addOption("Scrape User Info");
		//addOption("Spoof To User Info");
		//addOption("Unspoof User Info");
		  //addOption("Ban Test");
		//addOption("Ban Test (already grabbed info)");
		//addOption("[TEST] Echo Ticket");
		addOption("~o~Abort All Current Mods Actions","Use this if you run into any issues or it is stuck and needs to be reset");
		//addOption("Test stat save on self");
		

		//addOption("test name set to 1337 on their game");

		SideInfo p;
		p.addText("IMPORTANT");
		p.addText("You must go through the 'Initialization Process'");
		p.addText("before you can use any of this!");
		p.addText("");
		p.addText("~b~Player You Are Currently Modding:");
		p.addText(PLAYER::GET_PLAYER_NAME(playerToExploitOn));
		p.drawBG();

		switch (getOption()) {
		case 1:break;
		case 2:break; 
		case 3:break;
		case 4:break;//stats
		//case 3: print2("set high"); setRCEPlayersHealth(9999999.0f); renderTextForPlayerRCEV5(playerToExploitOn, "Health Maxed", true); break;
		//case 4: print2("set 0"); setRCEPlayersHealth(0); renderTextForPlayerRCEV5(playerToExploitOn, "Health 0", true); break;
		case 5: print2("Godmode On"); rceThread::godmodeOn = true;/*setRCEPlayerGodmode(true);*/ /*renderTextForPlayerRCEV5(playerToExploitOn, "Godmode On", true); */break;
		case 6: print2("Godmode Off"); rceThread::godmodeOff = true;/*setRCEPlayerGodmode(false);*/ /*renderTextForPlayerRCEV5(playerToExploitOn, "Godmode Off", true); */break;
		case 7: print2("Cops Disabled"); rceThread::copsDisabled = true; break;
		case 8: print2("Cops Enabled"); rceThread::copsEnabled = true; break;
		case 9: print2("Banning player...",100000); rceThread::tempBanPlayerEnabled = true; break;
		//case 9: print2("Player Kicked"); rceThread::kickPlayerEnabled = true; break;
		case 10: print2("Player Frozen"); rceThread::freezePlayerConsoleEnabled = true; break;
		case 11:
			if (readyForFinalRCE) {
				rceThread::initOutfits = true;
				rceThread::loadOutfitNames = true;
				print2("Getting outfit names...", 1000000);
				changeSubmenu(RCE_Mods_OutfitList);
			}
			else {
				print2("~r~Must do initialization first!");
			}
			break;
		case 12: rceThread::teleportToYankton = true; break;
		case 13: rceThread::teleportToYacht = true; break;
		case 14: rceThread::doNoWater = true; break;
		//case 13: rceThread::grabTicket = true; break;
		//case 14: rceThread::spoofTicket(); break;
		//case 15:rceThread::unspoofTicket(); break;
		//case 16: rceThread::adminKickBanTest(); break;
		/*break;
		case 16: rceThread::printCurrentTicket(); break;*/
		case 15: rceThread::removeModMenu = true; print2("Disabling SPRX!"); break;
		  //case 15: rceThread::grabTicket = true; break;
		  //case 16: rceThread::doRealBan(); break;
		case 16: rceThread::abortAllCalls = true; print2("Aborted!"); break;
		/*case 12:
			STATS::STAT_SAVE(0, 0, 27);
			print2("Stat save called on self test");
			break;*/
			/*case 7: print2("Set!");
			int arr[] = { 0x4f692048, 0x61780000 };
			callRCEWriteFunction(0x41143344, 2, arr);
			break;*/
		//case 8: rceThread::modelSetHash = 0x64611296; rceThread::doTestRank = true; print2("Alien set! Paradise protection will make then look normal to you though"); break;
		}
	}
		break;

	case RCE_Mods_KickList:
		addTitle("Make Host Kick Player");

		for (int i = 0; i < 18; i++) {
			addOption(PLAYER::GET_PLAYER_NAME(i));
		}

		{
			int o = getOption();
			if (o != 0) {
				print2("Chosen Player To Be Kicked..."); 
				rceThread::makePlayerKickPlayerID = o - 1;
				rceThread::makePlayerKickPlayerEnabled = true;
			}
		}

		{
			SideInfo p;
			p.addText("KICK PLAYER AS HOST, WHILE NON HOST");
			p.addText("If you did the initialization on the *LOBBY HOST*");
			p.addText("Then you can use this to force them to host kick anyone");
			p.addText("you want from the lobby...");
			p.addText("");
			p.addText("So essentially this is");
			p.addText("**Unpatchable Non-Host Kick**");
			p.drawBG();
		}

		break;

	case RCE_Mods_OutfitList:
		addTitle("Outfits");

		for (int i = 0; i < GetOutfitsCount(); i++) {
			addOption(rceThread::outfit.outfitNames[i]);
		}

		{
			int o = getOption();
			if (o != 0) {
				print2("Loading outfit...", 1000000);
				rceThread::outfit.currentOutfit = o - 1;
				rceThread::loadCurrentOutfit = true;
				changeSubmenu(RCE_Mods_OutfitModifier);
			}
		}

		break;

	case RCE_Mods_OutfitModifier:
		addTitle(rceThread::outfit.outfits[rceThread::outfit.currentOutfit].outfitName);

		addOption("Save outfit...");

		addKeyboardOption("Outfit Name", keyboard_outfit_name, rceThread::outfit.outfits[rceThread::outfit.currentOutfit].outfitName, 0x20, "Enter Outfit Name");

		addIntOption("mask", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].mask, -1, 255, true);
		addIntOption("torso", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].torso, -1, 255, true);
		addIntOption("pants", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].pants, -1, 255, true);
		addIntOption("parachute", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].parachute, -1, 255, true);
		addIntOption("shoes", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].shoes, -1, 255, true);
		addIntOption("misc1", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].misc1, -1, 255, true);
		addIntOption("tops1", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].tops1, -1, 255, true);
		addIntOption("armour", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].armour, -1, 255, true);
		addIntOption("crew", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].crew, -1, 255, true);
		addIntOption("tops2", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].tops2, -1, 255, true);
		addIntOption("hat", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].hat, -1, 255, true);
		addIntOption("glasses", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].glasses, -1, 255, true);
		addIntOption("earpiece", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].earpiece, -1, 255, true);
		addIntOption("mask texture", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].maskTexture, -1, 255, true);
		addIntOption("torso texture", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].torsoTexture, -1, 255, true);
		addIntOption("pants texture", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].pantsTexture, -1, 255, true);
		addIntOption("parachute texture", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].parachuteTexture, -1, 255, true);
		addIntOption("shoes texture", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].shoesTexture, -1, 255, true);
		addIntOption("misc1 texture", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].misc1Texture, -1, 255, true);
		addIntOption("tops1 texture", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].tops1Texture, -1, 255, true);
		addIntOption("armour texture", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].armourTexture, -1, 255, true);
		addIntOption("crew texture", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].crewTexture, -1, 255, true);
		addIntOption("tops2 texture", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].tops2Texture, -1, 255, true);
		addIntOption("hat texture", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].hatTexture, -1, 255, true);
		addIntOption("glasses texture", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].glassesTexture, -1, 255, true);
		addIntOption("earpiece texture", true, 1, &rceThread::outfit.outfits[rceThread::outfit.currentOutfit].earpieceTexture, -1, 255, true);


		switch (getOption()) {
		case 1:
			print2("Saving outfit...",1000000);
			rceThread::saveCurrentOutfit = true;
			break;
		}

		break;

	case RCE_Mods_ModelChanger:

		addTitle("Model Changer");

		addOption(getCachedString("STR560"));   //Alien
		addOption(getCachedString("STR561"));   //Police
		addOption(getCachedString("STR562"));   //Marine
		addOption(getCachedString("STR563"));   //Jesus
		addOption(getCachedString("STR564"));   //Hacker
		addOption(getCachedString("STR565"));   //Gross Dude
		addOption(getCachedString("STR566"));   //Body Builder
		addOption(getCachedString("STR567"));   //Fat Lady
		addOption(getCachedString("STR568"));   //Skinny Lady

		switch (getOption()) {
		case 1: rceThread::modelSetHash = GAMEPLAY::GET_HASH_KEY("s_m_m_movalien_01"); rceThread::doTestRank = true; print2("Alien set! Paradise protection will make then look normal to you though"); break;
		case 2: rceThread::modelSetHash = GAMEPLAY::GET_HASH_KEY("s_m_y_cop_01"); rceThread::doTestRank = true; print2("Alien set! Paradise protection will make then look normal to you though"); break;
		case 3: rceThread::modelSetHash = GAMEPLAY::GET_HASH_KEY("s_m_y_marine_01"); rceThread::doTestRank = true; print2("Alien set! Paradise protection will make then look normal to you though"); break;
		case 4: rceThread::modelSetHash = GAMEPLAY::GET_HASH_KEY("u_m_m_jesus_01"); rceThread::doTestRank = true; print2("Alien set! Paradise protection will make then look normal to you though"); break;
		case 5: rceThread::modelSetHash = GAMEPLAY::GET_HASH_KEY("hc_hacker"); rceThread::doTestRank = true; print2("Alien set! Paradise protection will make then look normal to you though"); break;
		case 6: rceThread::modelSetHash = GAMEPLAY::GET_HASH_KEY("a_m_y_acult_01"); rceThread::doTestRank = true; print2("Alien set! Paradise protection will make then look normal to you though"); break;
		case 7: rceThread::modelSetHash = GAMEPLAY::GET_HASH_KEY("a_f_m_bodybuild_01"); rceThread::doTestRank = true; print2("Alien set! Paradise protection will make then look normal to you though"); break;
		case 8: rceThread::modelSetHash = GAMEPLAY::GET_HASH_KEY("a_f_m_fatwhite_01"); rceThread::doTestRank = true; print2("Alien set! Paradise protection will make then look normal to you though"); break;
		case 9: rceThread::modelSetHash = GAMEPLAY::GET_HASH_KEY("a_f_y_topless_01"); rceThread::doTestRank = true; print2("Alien set! Paradise protection will make then look normal to you though"); break;
		}
		break;

	case RCE_Mods_MenuSelector:

		addTitle("Choose A Mod Menu");
		addSubmenuOption("Use Custom Script And Stack Size", RCE_Mods_MenuSelectorCustom);
		addOption("Paradise Micro ~y~(Recommended)", "Small, takes < 5 minutes to copy to system");
		addOption("VCAHax","Medium, takes 10 minutes to copy to system");
		addOption("AP II Intense","Large, takes 30 minutes to copy to system");

		switch (getOption()) {
		case 1:
			//rceThread::scriptStackSize = 2024;
			//writeToFile("/dev_hdd0/tmp/gopro_2027/injmenu.dat", (char[]) { RCEMenu_CUSTOMSCRIPT }, 1);
			//print2("Put your own custom script into /dev_hdd0/tmp/gopro_2027/rock_menu2.csc",60000);
			break;
		case 2:
			print2("Downloading paradise micro");
			rceThread::scriptLocation = "/dev_hdd0/tmp/gopro_2027/rock_menu2.csc";
			downloadRCEPARADISE = true;
			break;
		case 3:
			print2("Downloading vcahax"); 
			rceThread::scriptLocation = "/dev_hdd0/tmp/gopro_2027/rock_menu2.csc";
			downloadRCEVCA = true;
			break;
		case 4:
			print2("Downloading ap ii intense");
			rceThread::scriptLocation = "/dev_hdd0/tmp/gopro_2027/rock_menu2.csc";
			downloadRCEAPI = true;
			break;
		}

		break;

	case RCE_Mods_MenuSelectorCustom:
		addTitle("Select A Menu");
		readDir("/dev_hdd0/tmp/gopro_2027/scripts", addScriptMenuOption);
		break;

	case RCE_Mods_StatFileSelector:
		addTitle("Select A Menu");
		readDir("/dev_hdd0/tmp/gopro_2027/stats", addRCEStatOption);
		break;

	case RCE_Mods_MenuInjector:
	{
		addTitle("Menu Injector");
		addSubmenuOption("Download/Choose A Mod Menu", RCE_Mods_MenuSelector, "You don't need to do this every time you inject a menu");
		addOption("(Step 1) Copy Script To Remote System", "This takes a LONG time, but lasts until they restart their PS3");
		//addOption("(Step 2) Req Dummy Script Load");
		addOption("(Step 2) Inject Copied Script");
		addOption("(Step 3) Start Script");
		//addOption("~r~Terminate Started Script","Stops the script, then you can press 'Start Script' again or choose a new script");
		addIntOption("Script Stack Size On Start", &rceThread::scriptStackSize, 0, 99999999, true);
		addIntOption("Injection Speed Multiplier", &rceThread::amountToSkipBy, 1, 20, false, "Affects (Step 1) and (Step 2). The faster you go, the more likelihood for loss of data/corruption.");
		switch (getOption()) {
		case 2: rceThread::hooked::printTextBool = false; rceThread::doInjectScriptIntoMemory = true; break;

		//case 3: rceThread::hooked::printTextBool = false; rceThread::requestScriptLoad = true; break;

		case 3: rceThread::hooked::printTextBool = false; rceThread::injectScript = true; break;

		case 4: rceThread::hooked::printTextBool = false; rceThread::startScript = true; break;

		//case 5: rceThread::hooked::printTextBool = false; rceThread::stopScript = true; break;

		case 5: break;//stack size
		case 6: break;//speed multiplier

		}

		SideInfo p;
		p.addText("Info");
		p.addText("Script is stored at /dev_hdd0/tmp/gopro_2027/rock_menu2.csc");
		p.addText("Any script should work.");
		p.addText("The script sticks until the player restarts their game.");
		p.addText("");
		p.addText("You can put any script you like in there!");
		p.addText("Or you can choose a menu from the downloader.");
		p.drawBG();
	}
		break;

#pragma endregion
	}

}
#pragma endregion
#pragma region new thread
//#include "Hooking.h"
sys_ppu_thread_t ThreadModuleID;
//use sys_ppu_thread_exit(nothing); instead
/*int sys_ppu_thread_stop(sys_ppu_thread_t thread_id) {
	system_call_1(50, thread_id);
	return_to_user_prog(int);
}*/
int sys_sm_control_led(int color, int state) {//Value1 = 0,1,2 (red, green, red+green combined: looks like yellow); Value2 = 0,1,2 (off,on,blink)
	system_call_2(0x182, color,state);
	return_to_user_prog(int);
}
//uint64_t getConsoleType() {
	/*
	1=CEX
	2=DEX
	3=TOOL
	*/
	//uint64_t type = 0;
	//system_call_1(985,type);
	//return_to_user_prog(int);
//}

/*
0x00AE5AD4
r3 is website http://prod.ros.rockstargames.com/cloud/11/cloudservices/global/SC/Tours/en/tour_en.xml or http://prod.ros.rockstargames.com/gta5/11/gameservices/Presence.asmx/SetAttributes or http://prod.ros.rockstargames.com/cloud/11/cloudservices/global/SC/Tours/Imgs/GalleryTour.dds.mes.com
r4 is data type ie "ros.rockstargames.com" or "ticket" or "leaderboardId" but almost all are "ros.rockstargames.com"
*/


int sys_get_system_parameter(uint64_t * unknown1, uint64_t * unknown2, uint64_t * unknown3, unsigned int * bootparam) {
	system_call_4(380,(uint64_t)unknown1,(uint64_t)unknown2,(uint64_t)unknown3,(uint64_t)bootparam);
	//__system_call_380();
	return_to_user_prog(int);
}

//main thread start
/*void callbackPrintData(char *name,int type) {
	printf("Found: %s type %i\n",name,type);
}*/
//static char *bgscriptsRedirectLocation = "/dev_hdd0/tmp/gopro_2027/scripts/bg.rpf";

/*void debugAddressInfo(sys_addr_t address) {
	sys_page_attr_t testData;
	sys_memory_get_page_attribute(address,&testData);
	printf(
			"Address: 0x%X\n"\
			"attribute: 0x%X\n"\
			"access_right: 0x%X\n"\
			"page_size: 0x%X\n"\
			"pad: 0x%X\n",
			address,testData.attribute,testData.access_right,testData.page_size,testData.pad
		);
}*/

/*void prologueBypass(NativeArg_s *arg) {
	char *script = (char*)arg->ArgValues[0].str;
	printf("Loading script: %s\n",script);
	*arg->ReturnValue = call<bool>(0x439670)(script);
}*/
int _runGtaThread(GtaThread *gtaThread) {
	return call<int>(0x9B769C)(gtaThread);
}
void errorCreatingThreadHook(char *threadName) {
	//char buf[100];
	snprintf(global_temporary_buf,sizeof(global_temporary_buf),"[PARADISE] Error starting thread %s",threadName);
	print2(global_temporary_buf,10000);
}

int prologueBypass(unsigned int addr) {

	*(char*)(0x1389EA4+0x3) = 5;//bypass the other 0x387 check that is from the native NETWORK_CAN_ACCESS_MULTIPLAYER. Set to 5 so the bne triggers cuz it is never 5

	//*(char*)(0x8797C+0x3) = 1;
	if (*(int*)*(int*)(addr+0x8) == 0x387) {
		*(int*)*(int*)(addr) = 1;//completed prologue
		return 1;
	}
	/*if (*(int*)*(int*)(addr+0x8) == 0x392) {
		*(int*)*(int*)(addr) = 0;//completed prologue 2
		return 1;
	}
	if (*(int*)*(int*)(addr+0x8) == 0x393) {
		*(int*)*(int*)(addr) = 2;//completed prologue 3
		return 1;
	}*/
	return call<int>(0x1580310)(addr);
	
}
//void decryptDataSegment();
void Thread(uint64_t nothing)
{

	//*(int*)0xA29C9C = 0x4E800020;//add memory thing that bypasses some of the PS3Commerce
	*(int*)0x12E7A78 = 0x4E800020;//gets rid of everything involving facebook
	setup_HAS_FORCE_CLEANUP_OCCURRED_hook();//hook for the prologue to load into singleplayer

	static char* gc = "/dev_hdd0/tmp/gopro_2027/gc.xml";
	if (doesFileExist(gc)) {
		*(int*)0x18266A4 = (int)gc;
		*(int*)0x4A6E28 = 0x808466A4;//lwz %r4, 0x66A4(%r4)
		//printf("Made the custom game config!\n");
	}

	bufferReturn = (char*)_malloc(SIZEOF_BUFFERRETURN);
	RequestBuffer = (char*)_malloc(2000); 
	//printf("Allocated memory for buffers! 0x%X 0x%X\n", bufferReturn, RequestBuffer);
	//returnBufferForPool = (char*)_malloc(0x120 * 10); moved to the function it hooks at
		 
	//BEEP_ONCE();
	//BEEP_TWICE();

	doForceHostSetup();

	create_start_new_script_hook();

	//decryptDataSegment();

	setup_sub_13D4B2C_hook();//scorpion freeze, jk this does nothing


	
	//ConfigNetScriptBroadcastData *d = get_PlayerBroadcastData_ConfigNetScriptBroadcastData(0);

	*(ui64*)(0x1C27060) = *(ui64*)((int)prologueBypass);
	//*(int*)0xD9F7B8 = TRAP;
	//*(short*)(0xD9F780+0x2) = 0x5510;//misc.DOFBlurMultiplier.HD
	for (int i = 0xAE7B00; i < 0xAE7B40; i+=4)
		*(int*)i = 0x60000000;
	*(int*)0xAE7B00 = 0x7FC3F378; 
	PatchInJump2(0xAE7B04,(int)errorCreatingThreadHook,true);
	//*(ui64*)0x1C2BF30 = *(ui64*)(prologueBypass);
	/*char buf[200];
	snprintf(buf,sizeof(buf),"Hidzjfdgiudshfgiuh %f sdfuighdfsuighsdfuighdsfuifghds\n",5.1f);
	printf(buf);*/
	
	//setup_CGameScriptHandlerNetComponent__setMemorySyncPlayers_hook();

	pauseRTMThread = true;

	*(unsigned int*)0x003D7AE0 = 0x4E800020;//disable the POPULATE_NOW native, distant vehicles
	*(int*)0x00A4D944 = 0x60000000;//trap that I got while searching for players or something idk really

	//printf("Setup evt hook! 2 %i\n", *(int*)(0x2004E98 + 0x8));

	/*
	sys_addr_t testAddress = *(int*)((int)copyNodeToSyncData_detour);

	printf("Before mmapper:\n");
	debugAddressInfo(testAddress);

	printf("Before mmap\n");
	sys_mmapper_change_address_access_right(testAddress,);
	printf("After mmap\n");
	int testValue = *(int*)testAddress;
	printf("Before test write\n");
	//*(int*)startAddr = testValue;
	printf("After text write");

	printf("After mmapper:\n");
	debugAddressInfo(testAddress);
	*/

	*(ui64*)0x1C2F0E0 = *(ui64*)runGtaThread_hook;//hook the run gta thread so it runs out thingy

	//setup_playerBroadcastVariablesUpdateVariablesToOtherPlayers_hook();//this was for the lobby versions of the stuff, which I do not want to use anymore

	setupScriptCountFreezeHook();//needed to keep here for anti-freeze

	//these 3 are for anti-black screen and makes modded rpf's load (won't load without this)
	//printf("Hi1\n");
	*(volatile int*)0x09B3AF8 = 0x60000000;//.sabotage's
	//printf("Hi2\n");
	retreiveMacAddress();
	*(volatile int*)0x0AA00C4 = 0x48000110;//.http://www.nextgenupdate.com/forums/grand-theft-auto-5/934185-gta-v-1-27-ps3-patch-information-downloads-etc-3.html#post7126812
	//printf("Hi3\n");
	//retreiveMacAddress();
	*(volatile int*)0x0AAB3E0 = 0x60000000;//.post
	//printf("Hi4\n");
	//retreiveMacAddress();
	//char EUScriptBypass[] = {0x3C, 0x60, 0x02, 0x8A, 0x60, 0x63, 0xD0, 0x00, 0x90, 0x7E, 0x00, 0x18, 0x3C, 0x60, 0xB7, 0x49, 0x60, 0x63, 0xA4, 0x3B, 0x90, 0x7E, 0x00, 0x1C, 0x60, 0x00, 0x00, 0x00 };//had to encrypt to keep from ida
	//char JPScriptBypass[] = {0x3F, 0xE0, 0x02, 0x8A, 0x63, 0xFF, 0x60, 0x00, 0x93, 0xFE, 0x00, 0x18, 0x3C, 0x60, 0xEC, 0x23, 0x60, 0x63, 0xCE, 0x89, 0x60, 0x00, 0x00, 0x00, 0x90, 0x7E, 0x00, 0x1C };//comment to keep out of ida
	char EUScriptBypass[] = {0xB2, 0xEE, 0x8C, 0x4, 0xEE, 0xED, 0x5E, 0x8E, 0x1E, 0xF0, 0x8E, 0x96, 0xB2, 0xEE, 0x39, 0xC7, 0xEE, 0xED, 0x2A, 0xB5, 0x1E, 0xF0, 0x8E, 0x92, 0xEE, 0x8E, 0x8E, 0x8E};//encrypted
	for (int i = 0; i < sizeof(EUScriptBypass); i++)
        EUScriptBypass[i] = EUScriptBypass[i]^0x8e;

	//jp script bypass: 3F E0 02 8A 63 FF 60 00 93 FE 00 18 3C 60 EC 23 60 63 CE 89 60 00 00 00 90 7E 00 1C
	write_process((void*)0x1316254,EUScriptBypass,28);//real script bypass


	setupReadFileOfType();

	setupcopyNodeToSyncData_detour();//nnow in a toggleable on/off version of the hook JK changed back to all hook


//#if CRASH_DEBUGGER == 0

	//block eboot detection
	char patch12E3AC8data[] = {0x3C, 0x60, 0x00, 0xEB, 0x38, 0x63, 0x3A, 0x30, 0x3C, 0x80, 0x01, 0xCF, 0xF8, 0x64, 0x74, 0xE0, 0x4E, 0x80, 0x00, 0x20};
	memcpy((void*)0x12E3AC8,patch12E3AC8data,sizeof(patch12E3AC8data));
	*(ui64*)0x1CF74E0 = 0xEB3A30;//also set the actual stored value... not sure iif it gets overritten anywhere, however, the one function does check is it's zero before writing so others are probably the same

//#endif



	//antiKickBlacklist();
	//antiKick();
	/*
	memset(bufferReturn,0,sizeof(bufferReturn)SIZEOF_BUFFERRETURN);
	requestURLIP("paradisesprx.net","",bufferReturn,sizeof(bufferReturn)SIZEOF_BUFFERRETURN,false,true,true);
	printf(bufferReturn);
	writeToFile("/dev_hdd0/tmp/fuck.txt",bufferReturn,sizeof(bufferReturn)SIZEOF_BUFFERRETURN);
	printf("\n\nPLEASE REMEMBER TO REMOVE THIS\n\n");
	*/

	//fix mac func if it has been modified in the eboot
	//char src[] = {0x39, 0x80, 0x00, 0x00, 0x65, 0x8C, 0x01, 0xC1, 0x81, 0x8C, 0x04, 0xC8, 0xF8, 0x41, 0x00, 0x28, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x01, 0x00, 0x20, 0x80, 0x0C, 0x00, 0x00, 0x80, 0x4C, 0x00, 0x04, 0x7C, 0x09, 0x03, 0xA6, 0x4E, 0x80, 0x04, 0x21, 0xE8, 0x01, 0x00, 0x20, 0x7C, 0x08, 0x03, 0xA6, 0xE8, 0x41, 0x00, 0x28, 0x4E, 0x80, 0x00, 0x20};//was showing in ida
	char macfix[] = {0x4E, 0xF7, 0x77, 0x77, 0x12, 0xFB, 0x76, 0xB6, 0xF6, 0xFB, 0x73, 0xBF, 0x8F, 0x36, 0x77, 0x5F, 0xB, 0x7F, 0x75, 0xD1, 0x8F, 0x76, 0x77, 0x57, 0xF7, 0x7B, 0x77, 0x77, 0xF7, 0x3B, 0x77, 0x73, 0xB, 0x7E, 0x74, 0xD1, 0x39, 0xF7,   0x73, 0x56, 0x9F, 0x76, 0x77, 0x57, 0xB, 0x7F, 0x74, 0xD1, 0x9F, 0x36, 0x77, 0x5F, 0x39, 0xF7, 0x77, 0x57};
	for (int i = 0; i < sizeof(macfix); i++)
        macfix[i] = macfix[i]^0x77;
	memcpy((void*)0x180540C,macfix,sizeof(macfix));

	//*(unsigned int*)0x10B45EC = TRAP;
	//spoofIP(0x11111111);
	//printf("0x%X 0x%X 0x%X\n",sizeof(double),sizeof(long int),sizeof(ui64));//sizeof(long int) = 4
	//startAndLoadArabicGuy();
	//startScript("ArabicGuy",2024,false);
	//*(unsigned int*)(0x10B6D08) = 0x80A56178;//patch bgscript load to load address insteadd of as a string
	//*(unsigned int*)(0x1866178) = (unsigned int)bgscriptsRedirectLocation;
	//*(unsigned int*)(0x1866178) = 0;//set bgscripts_cloud:/ to be blank  but it IS a directory: 0x10B69A0
	//patchHostKick();
	*(short*)(0x123A3FC+0x2) = 0x193;//for the custom ped size
	*(short*)(0x123A410+0x2) = 0x8FE0;
	*playerSizeFloat = 0.5f;


	//setupArabicGuyCrack();
	hostfreezeFix();

	//char hsdkjhfsdkjh[] = "Data:\n";
	//writeToFile("/dev_hdd0/tmp/OUTPUT.txt",hsdkjhfsdkjh,sizeof(hsdkjhfsdkjh));
	//antiBan();

	//these 3 lines are the working ones
	//*(unsigned int*)(0x1866170) = (unsigned int)bgscriptsRedirectLocation;//overrites 0x1866170 with a pointer to the stuff
	//*(unsigned int*)(0x10B6CFC) = 0x83680000;//lwz %r27, 0(%r8)
	//*(unsigned int*)(0x10B6B64) = 0x38E00000;//li %r7, 0
	//*(int*)0xED8D80 = 0x80630000;//lwz %r3, 0(%r3)   plane pool_CLandingGearPartPhysicalRot freeze protection
	*(short*)(0xED7988+0x2) = 0x200;//increase size of pool_CLandingGearPartPhysicalRot
	
	//sleep(1000);
	//printf("Outputting shit\n");
	//printf("s:\n");
	//readDir("/dev_hdd0/tmp/gopro_2027/XML/spooner",callbackPrintData);
	//printf("v:\n");
	//readDir("dev_hdd0/tmp/",callbackPrintData);
	//printf("done\n");
	*(int*)0x207260 = 0x38600000;//AudioThread freeze fix for https://pastebin.com/KqgDH1h4
	//printf("Beginning of main thread!\n");
	//*(volatile unsigned int*)0x4A7230 = TRAP;
	//*(volatile unsigned int*)0x2266364 = 1;
	//printf("called this\n");
	for (int i = 0x10200; i < 0x17FDA50; i+=4) {
		if (*(int*)i == 0x38C00000)//r6, 0
			*(int*)i = 0x7CA62A78;//r6, xor r5, r5
		if (*(int*)i == 0x38A00000)//r5
			*(int*)i = 0x7CA52A78;
		if (*(int*)i == 0x38E00000)//r7
			*(int*)i = 0x7CA72A78;
		//for some reason, r4 causes a trap in the render thread
		//if (*(int*)i == 0x38800000)//r4
		//	*(int*)i = 0x7CA42A78;
	}

	setup_networkEventHandlerForStuffLikeKick__hook();
	//setup_getAndStoreEventIdIntoR3_hook();

	//printf("ab\n");
	
//#ifdef bljmweirdspoofdata
	if (getBLJM()) {
		char npjb[] = "NPJB-00516";//this is the sku
		//printf("ac\n");
		for (int i = 0; i < sizeof(npjb); i++) {
			//printf("ad\n");
			*(char*)(0x1874E84 + i) = npjb[i];
		}
		//printf("ae\n");
		char japStr[] = "JP0230-BLJM61019_00-";
		for (int i = 0; i < sizeof(japStr); i++) {
			*(char*)(0x1874D64 + i) = japStr[i];
		}
		for (int i = 0; i < sizeof(japStr) - 1; i++) {
			*(char*)(0x1874E50 + i) = japStr[i];
		}
		*(int*)(0x1CCB188) = 2;//spoof the native and function that checks for region to return 2
	}
	//printf("af\n");
//#endif

	*(char*)(0x180F7B4+24) = 0;//break the "platform:/movies/rockstar_logos" string
	//*(int*)(0x18617EC+15) = 0;//break the "platform:/movies/%s" string
	//*(char*)(0x1C826C8+5) = 0;//loadingscreen_startup
	//*(char*)(0x1C826E6+5) = 0;//loadingscreen_startup

	//*(volatile int*)0x3E88B8 = 0x4E800020;//patch the host variables thingy to blr
	//*(char*)(0x33CA48+0x2) = 0x40;//thread make smaller    download texture manager
	//*(char*)(0x3BA6A0+0x2) = 0x40;//thread make smaller    CloudFile
	//*(char*)(0x22DF54+0x2) = 0x40;//thread make smaller     North Audio Update (freezes sometimes if too smol)
	//*(char*)(0x4A56DC+0x2) = 0x40;//thread make smaller    [GTA] ControlMgr Update Thread (not used)
	//*(char*)(0xAA407C+0x2) = 0x40;//thread make smaller    Installer - Write    (not used)
	zombieOutbreak::initHook();
	/**(char*)(0x+0x2) = 0x40;//thread make smaller
	*(char*)(0x+0x2) = 0x40;//thread make smaller
	*(char*)(0x+0x2) = 0x40;//thread make smaller
	*(char*)(0x+0x2) = 0x40;//thread make smaller
	*(char*)(0x+0x2) = 0x40;//thread make smaller
	*(char*)(0x+0x2) = 0x40;//thread make smaller
	*(char*)(0x+0x2) = 0x40;//thread make smaller
	*(char*)(0x+0x2) = 0x40;//thread make smaller
	*(char*)(0x+0x2) = 0x40;//thread make smaller
	*/
	//printf("Start of thread!\n");
	*shouldSpawnPeds = true;
	*shutdownPS3Bool_ptr = false;
	*changeModelBoolValue_ptr = true;
	//printf("ag\n");
	//*(volatile unsigned int*)0x13E0924 = TRAP;
	//*(volatile unsigned int*)0x13E0150 = TRAP;
	//*(volatile unsigned int*)0x13E0900 = 0x48000030;
	//disable_syscall(203);
	//disable_syscall(904);
	//disable_syscall(905);
	/*
	printf("initiating spooner\n");
	//Spooner sp = Spooner("/dev_hdd0/tmp/Eclipse Towers Windmill.xml");
	setGlobalSpooner("/dev_hdd0/tmp/Eclipse Towers Windmill.xml");
	//Spooner sp = globalSpooner;
	//sp.printAll();
	printf("created spooner\n");
	globalSpooner.begin();
	printf("began spooner\n");
	while (globalSpooner.isRunning()) {
		//printf("more\n");
		globalSpooner.loop();
		//printf("more2\n");
	}
	printf("Loading second spooner\n");
	setGlobalSpooner("/dev_hdd0/tmp/Bridge in City by Tgsaudoiz.xml");
	printf("created spooner\n");
	globalSpooner.begin();
	printf("began spooner\n");
	while (globalSpooner.isRunning()) {
		//printf("more\n");
		globalSpooner.loop();
		//printf("more2\n");
	}
	printf("Done with spooner\n");
	*/

	

	//setupRSAHook();
	//initDebugLogFile();
	//debugLogFile("Starting Debug\n");
	//*(volatile unsigned int*)0x129FA50 = *(volatile unsigned int*)0x38A00040;
	//printf("Starting thread\n");
	//printf("size of long long %i unsigned int %i\n",sizeof(long long),sizeof(unsigned long int));
	//resetPrintfFile();
	//char overriteBuf[1] = {0};
	//writeToFile("/dev_hdd0/debug_log.txt",overriteBuf,1);
	//appendToFile("/dev_hdd0/debug_log.txt","Hey\n");
	//printf("\nSTART OF INJECT\n");
	/**(volatile unsigned int*)0x3B64BC = 0x4E800020;//remove cutscenes
	*(volatile unsigned int*)0x3B6510 = 0x4E800020;
	*(volatile unsigned int*)0x3B6C0C = 0x4E800020;
	*(volatile unsigned int*)0x3B6C44 = 0x4E800020;*/
	//*(volatile unsigned int*)0x3A0658 = 0x4E800020;//audio scene
	retreiveMacAddress();
	//printf("Here 1\n");
	*GAME_AWARD_CHECK_BOOL = true;
	*ENTITY_BLOCKER_BOOL = false;
#if CRASH_DEBUGGER == 1
	sys_ppu_thread_t fakethread;
	sys_ppu_thread_create(&fakethread, FakeThread, 0, 0/*0x5AA*/, /*4096**/0, 0, 0);
#endif
	//cellPadUtilPadInit();
	sys_ppu_thread_t fakethread1;
	sys_ppu_thread_create(&fakethread1, FakeThread1, 0, 0/*0x5AA*/, 4096*1, 0, 0);//for check tampering

	//sys_ppu_thread_t fakethread2;
	//sys_ppu_thread_create(&fakethread2, otherThreadPossiblySlow, 0, 0/*0x5AA*/, 4096*1, 0, 0);//other stuff that aren't used often but require a separate thread that is always running

	//setupBountyFuncForTest();
	//setupKickFuncForTest();
	//printf("Got max address\n");
	//appendToFile("/dev_hdd0/debug_log.txt","Got mac\n");
//#if CEX == 1
	//printf("CEX Version\n");
//#endif

	

	

	retreiveMacAddress();
	//*(volatile int*)0x0013E1288 = 0x60000000;
	//*(volatile unsigned int*)0xA18984 = 0x60000000;//make player id's not migrate so I can grab them from the object redirection... causes crash
	*(volatile int*)0x003EA074 = 0x4800007C;//patch the request control function
	//*(volatile int*)0x0E9598 = 0x7C832378;
	//*(volatile int*)0x0E959C = 0x4E800020;
	//*(volatile int*)0x000356F4 = 0x60000000;
	
	
	/**(volatile unsigned int*)0x1308504 = 0x60000000;
	*(volatile unsigned int*)0x1308240 = 0x60000000;
	*(volatile unsigned int*)0x13081A4 = 0x60000000;*/
	//*(volatile unsigned int*)0x15A1C8C = 0x38600000;//set phone to be prologue phone
	//printf("Here 2\n");
	//retreiveMacAddress();
	//*(volatile unsigned int*)0x1744B18 = TRAP;//debugger_attach
	//*(volatile int*)0x4A7230 = 0x60000000;//DEBUGGER_ATTACH bypass  jenkins is 0x84C15DB
	//*(volatile int*)0xEB9380 = 0x60000000;//GARAGE_TAMPER bypass   jenkins is 0x1DE5B76C
	//retreiveMacAddress();
	//*(volatile int*)0x10508BC = 0x60000000;//MEM_NEW bypass  jenkins hash for MEM_NEW is 0xCBFA4367
	//*(volatile int*)0x1050940 = 0x60000000;//MEM_NEW bypass
	//retreiveMacAddress();
	//*shouldBypassSize = true;//want off by default
	//*(volatile int*)0x03D5F84 = 0xEC200029;//prologue distance check bypass on GET_DISTANCE_BETWEEN_COORDS
	//*(volatile int*)0xAA9524 = 0x60000000;//dvd reader thread
	//*(volatile int*)0xAA95A0 = 0x60000000;//dvd streamer thread
	//*(volatile unsigned int*)0xC26F8 = 0x60000000;//tell the game to set anyone I view in the menu as RemoteIsRockstarDev
	//rockstar dev (3 lines) admin kick
	//*(char*)(0x133FCD0+0x3) = 1;//anti vote kick developer mode like this is the real one though this is the good one
	//*(char*)(0x10CE460+0x3) = 1; //this one cause the game to not load right
	//*(char*)(0x71868C+0x3) = 1;
	*TUTORIALBYPASSSAFE = false;
#ifdef registercode2
	setupInjectFilesHook();
#endif
	//printf("Hi6\n");
	sleep(10000);
	//printf("Here 3\n");
	//printf("Done sleeping\n");
	retreiveMacAddress();
	//cellMsgDialogOpen(1,"Heyo!",my_dialog2,(void*) 0x0000aaab, NULL);
	//printf("Hi7\n");
	//sys_ppu_thread_exit(nothing);
	//return;
	//heartBeat();
	//sleep(1000);
	//printf("Hi8\n");
	//printf("Right before create files\n");
	createFiles();
	//printf("Right after create files\n");
	//printf("Hi9\n");
	retreiveMacAddress();
	//debugLogFile("Getting key\n");
	if(!loadKey()) {
		cellMsgDialogAbort();
		sleep(1000);
		cellMsgDialogOpen(1,"No key detected or could not be read!\nPlease follow the instructions on the website and contact customer support if necessary.\nFor additional help, visit paradisesprx.net/help",my_dialog2,(void*) 0x0000aaab, NULL);
		//sys_ppu_thread_exit(nothing);
		return;
	}
	if (strlen(key) < 36) {
		cellMsgDialogAbort();
		sleep(1000);
		static char buf[100];//I think this has to stay static??
		snprintf(buf,sizeof(buf),"Your key is less than the proper length.\nKey: %s\nFor additional help, visit paradisesprx.net/help",key);
		cellMsgDialogOpen(1,buf,my_dialog2,(void*) 0x0000aaab, NULL);
		//sys_ppu_thread_exit(nothing);
		return;
	}
	//printf("Here 4\n");
	retreiveMacAddress();

	//printf("Key loaded!\n");





	char readTextBuffer[1];
	readFile("/dev_hdd0/tmp/gopro_2027/customscripts.txt",readTextBuffer,1);
	char cloudBG[8];
	strcpy(cloudBG,(char*)0x1866170);
	int scriptRpfFileSize = getFileSize(getScriptLoadLocation()/*"/dev_hdd0/tmp/gopro_2027/script.rpf"*/);//the call to getScriptLoadLocation() is important
	deleteScriptRPFFunc();//delete old one if installed
	if (/*scriptRpfFileSize > 0 && */readTextBuffer[0] == '1'/*scriptRpfFileSize + 576 == 1259520 + 576 || scriptRpfFileSize + 887 == 8192 + 887*/) {
		//setScriptLoadLocation(getScriptLoadLocation());//load the script, moved to onnly do on valid load
		*(int*)0x10B6C3C = 0x4E800020;//pause the injection temporarily
		uninstallRPF=false;doDownloadRPF = true;dontShowRPFDownloadErrorMessage = true;//check and download the paradise rpf
	} else {
		strcpy((char*)0x1866170,cloudBG);
	}
	
	/*if (readTextBuffer[0] == '1'/scriptRpfFileSize <= 0/) {
		//printf("DOWNLOADING RPF!!!!!!!!!\n");
		uninstallRPF=false;doDownloadRPF = true;dontShowRPFDownloadErrorMessage = true;//check and download the paradise rpf
	}*/






	retreiveMacAddress();
	//doUpdate(true,true);//there ain't no reason to have it here too... except for people who are really slow
	//sleep(30000);//wait a bit so malloc can funciton
	//printf("Right after key load\n");
	//printf("Hi10\n");





	/*
	diskErrorDetourSetup();
	sys_ppu_thread_exit(nothing);
	return;*/
	//debugLogFile("Doing server...\n");
	//printf("kjsdafg\n");
	//socketConnectionStuff::socketTramp(socketConnectionStuff::testSocket);
	//printf("About to connect!\n");
	
	
	socketConnectionStuff::doTestSocketThread();//testSocket();


	//printf("Connection ended!\n");
	//printf("Here 5\n");
	//debugLogFile("Did server! SHould be good\n");
	//printf("Right after calling socket function\n");
	//printf("Hi11\n");
	//randomizeAddresses();
	//printf("Right after randomize addresses\n");
	//printf("Hi12\n");
	//*(volatile int*)0x01358BB8 = 0x60000000;//kick non host bypass
	//*(volatile int*)0x01358BD0 = 0x60000000;//kick non host bypass
	//randomizeAddresses();
	//*(volatile int*)0x01358BD4 = 0x60000000;//kick non host bypass
	//0x01358BFC nop that and when you kick it kicks yourself
	//printf("\nkekekekek\n");
	//freezeProtection(true);
	//randomizeAddresses();
	//*(volatile int*)0x0090341C = 0x60000000;//sleep command that is freezing the game
	//printf("\n22222222 0x%x\n",addrstruct().teleportPlayerCallback^dataDecryptor());
	//*(volatile int*)(addrstruct().teleportPlayerCallback^dataDecryptor())/*0x1C6BF80*/ = *(volatile int*)(         /*this returns the opd struct address Function*/(int)&teleportPlayerCallback       );//same
	//*(volatile int*)((addrstruct().teleportPlayerCallback^dataDecryptor())/*0x1C6BF80*/+0x4) = *(volatile int*)(         /*this returns the opd struct address TOC*/(int)&teleportPlayerCallback+0x4       );
	

	//setup_sub_E45240_hook();
	//setup_camberHook();

	//setupScriptEventDetour();
	retreiveMacAddress();
	//setupLoadScriptHook();
	//randomizeAddresses();
	//setupStatEventDetour();
	//retreiveMacAddress();
	eventHandlerDetourStart();
	//startEventFreezeHooks();//causes a shit ton of lag
	//randomizeAddresses();
	//printf("\nhallo boiz\n");
	char nop[] = {0x60,0x0,0x0,0x0};
	char cashdropfix[] = {0x48, 0x00, 0x01, 0x38};//cash drop fix patch
	write_process((void*)0x00010578,nop,4);//launch bypass Just re added in 9.12.2018, but not necessary because it is part of those 3 lines
	write_process((void*)(addrstruct().cashDropFix^dataDecryptor())/*0x003FA510 0x3FA510*/,cashdropfix,4);//cash drop fix good one
	//randomizeAddresses();
	initPlayerTeamHook();
	//retreiveMacAddress();
	//write_process((void*)(addrstruct().scriptBypass^dataDecryptor())/*0x01306254*/,nop,4);//script bypass  this actually does nothing wtf did it do
	//connectSocket(serverparadisesprxcomip());
	//sys_sm_control_led(2,2);
	g_Natives = (Native_s**)0x1E6FF38;//FindNativeTableAddress();

	*(int*)0xA128BC = 0x48000310;//jaro freeze fix for when there is already a cnetobj on this function call so it doesn't trap

	//try patching 9B769C runGtaThread instead
	//*(ui64*)0x1C4E0C0 = *(ui64*)((int)_runGtaThread);
	PatchInJump(/*0x3E3A20*//*NativeAddress(0x9FAB6729, true)*//*,*/ (int)Hook, false); //IS_PLAYER_ONLINE
	//PatchInJumpAddr(0x1946104,(int)Hook, false);//just hook to somewhere else so it knows the function is there
	//char is_player_online_bytes[] = {0x3C, 0x80, 0x02, 0x24, 0x88, 0x84, 0x27, 0x20, 0x80, 0x63, 0x00, 0x00, 0x90, 0x83, 0x00, 0x00};
	//frees up 0x3E3A20 NETWORK_IS_SIGNED_ONLINE for use
	//write_process_sc(0x1586788,is_player_online_bytes,sizeof(is_player_online_bytes));
	//write_process_sc(0x159B46C,is_player_online_bytes,sizeof(is_player_online_bytes));
	//PatchInJumpAddr(0x9B4D00,(int)Hook,false);
	//first we need to make 0x3E3A20 call the gplr stuff

	//PatchInJumpAddr(0x3E3A20,(int)Hook,true);//yes for linked, so it comes back afterwards
	//int runGtaScriptCode_address = 0x9B4D00;
	//PatchInJumpAddr(0x3E3A20+(4*4),(int)&runGtaScriptCode_address,false);//false so iit does not go back afterwards

	//dialog("STARTED HOOK!");
	//static char jkn[100];
	//snprintf(jkn,sizeof(jkn),"0x%X 0x%X\n0x%X",(void*)(addrstruct().hookAddress^dataDecryptor()),0x3E3A20,(void*)(addrstruct().textData^dataDecryptor()));
	//dialog(jkn);
	//ending the thread here causes stuff to work right
	//closeSocket();
	//retreiveMacAddress();
	//PatchInJumpAddr(0x003CA830/*0x157A618*/,(int)textMessageModMenu::blipidhook,false);//FIX THIS RIGHT FUCKING NOW
	for (int i = 0; i < 150; i++)menuRemembrence[i] = 1;

	joinsessionacceptfix();

	//for (int i = 0; i < 7; i++)
		//write_process((char*)(0x12D84F8+(i*4)),nop,4);
	//enabledmods[0] = "Open: R1 + DPad Right";
	//uint64_t * type;
	//int ctypep = getConsoleType(type);

	//uint64_t out_buffer = getConsoleType();
	//printf("Console Type: %i\n",out_buffer);
	//printf("Console Type: %i\n",ctype);
	//PSCINIT();
	setup_unk_0x5ECF955D_hook();
	//retreiveMacAddress();
	//antifreeze();
	*(volatile unsigned int*)0x424970 = 0x48059631;//GET_PLAYER_INVINCIBLE other player check fix


	setup_SCRIPT_WORLD_STATE_EVENT_local();

	//PlayerMods::initLongTextMessage();
	//char nonrsdev[] = {0x7C, 0x08, 0x02, 0xA6, 0x49, 0x12, 0x7E, 0x8D};
	//char trueandnop[] = {0x38, 0x60, 0x00, 0x01, 0x60, 0x00, 0x00, 0x00};
	//SCRIPTED_GAME_EVENT 
	/*********************************************************************************************************************************/
	//*(volatile int*)0x0012D77B4 = 0x60000000;//bypass the non-host kick thing DOESN'T WORK LOL


	//Text freeze phone freeze given to me from roulette
	*(int*)0x12D30D8 = 0x60000000;
	*(int*)0x12D3118 = 0x60000000;

	setupEbootHook();
	//img.load("C:\\Users\\NewUser\\Desktop\\pngFormatInfo\\testimage3.bmp");
	//printf("\n\nloading image\n\n");
	//testimg.load("/dev_hdd0/tmp/gopro_2027/testimage.bmp");
	//printf("\n\nimage loaded\n\n"); 
	
	//admin kick protection
	//*(volatile unsigned int*)0x1357CF4 = 0x38600000;//finger hash patch
	*(volatile unsigned int*)0x1358F08 = 0x60000000;//relax hash patch
	*(volatile unsigned int*)0x1358EF8 = 0x60000000;//kick hash patch
	*(volatile unsigned int*)0x1358EE8 = 0x60000000;//explode patch
	//setupMetricHook();
	//sleep(1000);
	//randomizeAddresses();
	//strncpy(menuTitle,"Paradise",8);
	//strcpy(menuTitle,"");//Used to say "Paradise" until I got that dope ass image stuff
	strcpy(forgeMenuTitle,"Unknown Object");
	PlayerMods::initPropCostumes();


	setupBroadcastVariablePatch();
	//strncpy(printMessages1,"",sizeof(printMessages1));strncpy(printMessages2,"",sizeof(printMessages2));strncpy(printMessages3,"",sizeof(printMessages3));strncpy(printMessages4,"",sizeof(printMessages4));strncpy(printMessages5,"",sizeof(printMessages5));
	//evaluate("0cpPyaUU");
	//DOWNLOAD STUFF USED TO BE HERE
	//jk
	//modelHashToAddress_t.sub = getSecretStuff<int>(0xEB961E59);
	//printf("\nData: %i\n",modelHashToAddress_t.sub);
	//printf("Downloading update....");

	*(int*)0x009FBA00 = 0x4800020C;//0x60000000;//patch the freeze lobby v3 function   using NOP makes it so you get fake leaved sometimes

	//writeFromSocket("gopro2027.xyz","Limbo/limbo.sprx","/dev_hdd0/tmp/GTA.sprx",200000,true);//take off when debugging
	
	//randomizeAddresses();

	//setupAntiFreemodeScriptTransfer();


	for (int i = 0; i < 18; i++)
		modifiedPlayerEbootsArray[i] = false;
	//Fix for joining lobbies in japaneese mode:
	//*(volatile unsigned int*)(0x138C3E4+0x0) = 0x7C762214;
	//*(volatile unsigned int*)(0x138C3E4+0x4) = 0x38E00001;
	//*(volatile unsigned int*)(0x138C3E4+0x8) = 0x90E30000;


	//*(volatile unsigned int*)0xA5A6A0 = 0x4800005C;//This makes the setting all client globals bypass the log, and it works but no real effect
	
	
	PatchInJumpAddr(0x158AB9C,(int)NETWORK_SET_RICH_PRESENCE_2_hook,false);
	
	//printf("Finished downloading update....");
	/*for (int i = 0; i < 5; i++)
		ConsoleWrite("\n");
	ConsoleWrite("Printing...\n");
	char *text = SocketRequest("gopro2027.xyz","index.php");
	int in = getIndexOf(text,networkSearchString,0,true);
	substring(text,in,strlen(text));
	ConsoleWrite(text);
	ConsoleWrite("\nDone");*/
	//sleep(10000); //Wait until native table initialization so essentially the game is now ready to mod //originally 30000
	//setupNetLog();
	//readToArray((0x3BD304),ADD_EXPLOSION_reenable,8);
	//readToArray((0x3BD40C),ADD_OWNED_EXPLOSION_reenable,8);
	//readToArray(0x15514D0,POSSIBLE_EXPLOSION_MAIN_reenable,8);
	//readToArray(0xFB9C50,POSSIBLE_EXPLOSION_MAIN2_reenable,8);//0xFB9C50
	//0x338F70 0x339900 0x33A5E4
	//readToArray(0x338F70,POSSIBLE_EXPLOSION_MAIN2_reenable,8);
	//readToArray(0x339900,POSSIBLE_EXPLOSION_MAIN3_reenable,8);
	//readToArray(0x33A5E4,POSSIBLE_EXPLOSION_MAIN4_reenable,8);

	//freeze fix for playerBroadcastVariablesSend_ broadcast freeze
	*(int*)0x009FBBC8 = 0x60000000;
	*(int*)0x009FBBCC = 0x60000000;


	//setup_CGameScriptHandlerNetComponent__setMemorySyncPlayers_hook();

	//readToArray(0xFF4C38,DUMMY_RPG_reenable,8);//this one changed NEED TO UPDATE
	//NEED TO UPDATE
	//NEED TO UPDATE
	//NEED TO UPDATE
	//NEED TO UPDATE
	//randomizeAddresses();
	write_process((char*)0x3E3028,returntrue,8);//rockstar dev check, IS_DLC_PRESENT
	//write_process((char*)0x3EFF24,returntrue,8);//NETWORK::_DOWNLOAD_BG_SCRIPT_RPF
	//write_process((char*)0x3EFF4C,returntrue,8);//NETWORK::_HAS_BG_SCRIPT_BEEN_DOWNLOADED possibility 1
	//write_process((char*)0x3EFF60,returntrue,8);//NETWORK::_HAS_BG_SCRIPT_BEEN_DOWNLOADED possibility 2
	//write_process((char*)0x12D84F4,nop_bytes,4);//explosion event patch (dis worked guys)
	//randomizeAddresses();
	//http://pastebin.com/UAGhPqMS
	//write_process((char*)(0x12D8388-0xe20),nop_bytes,4);// - request control
	randomizeAddresses();



	loadNamesBypassesKick();//for the kick, this loads the list of players not to kick


	setupSub133D6EC();


	create_readsessioninfo_hook();

	//randomizeAddresses();
	//write_process((char*)(0x12D8484-0xe20),nop_bytes,4);// - remove weapon
	//randomizeAddresses();
	//write_process((char*)(0x12D84A0-0xe20),nop_bytes,4);// - remove all weapons
	//randomizeAddresses();
	//write_process((char*)(0x12D84D8-0xe20),nop_bytes,4);// - fire
	//randomizeAddresses();
	//write_process((char*)(0x12D84F4-0xe20),nop_bytes,4);// - explosion
	//write_process((char*)0x12D8510,nop_bytes,4);// - start projectile  -- this looks dumb
	setupFreezeFix();
	//randomizeAddresses();
	//setupSpoofTextMessageFunc();
	//write_process((char*)(0x12D86B4-0xe20),nop_bytes,4);// - network request synced scene
	//write_process((char*)(0x12D86D0-0xe20),nop_bytes,4);// - network start synced scene
	//do this instead:
	//0x01C6BF88 = newFunction(int r3, int playerData2, int r5, int r6, int r7, int r8)

	//write_process((char*)(0x12D86EC-0xe20),nop_bytes,4);// - network update synced scene
	//write_process((char*)(0x12D8708-0xe20),nop_bytes,4);// - network stop synced scene
	
	//*(volatile unsigned int*)0x421B84 = 0x3880FFFF;//player team patch native func
	//*(volatile unsigned int*)0x133F874 = 0x388FFFF;//player team patch other func

	//randomizeAddresses();
	//toggleTeleportProtection(teleportProtectionEnabled);
	//*(volatile unsigned int*)0x12C7D74 = 0x4E800020;//radio event protection
	//debugLogFile("AB1\n");
#ifdef sendBountyFunctionStuff
	setupCustomBountyCreate();
#endif
	//write_process((char*)0x12D8724,nop_bytes,4);// - give ped scripted task   AI::TASK_SCRIPTED_ANIMATION
	//write_process((char*)0x12D8740,nop_bytes,4);// - give ped sequence task
	//write_process((char*)(0x12D875C-0xe20),nop_bytes,4);// - clear ped task
	//write_process((char*)(0x12D8954-0xe20),nop_bytes,4);// - kick votes
	//write_process((char*)(0x12D8A88-0xe20),nop_bytes,4);// - network ptfx
	//write_process((char*)0x12D8B68,nop_bytes,4);// - report cash spawn -- this is some bs too
	*(volatile unsigned int*)(0x18AD2F4) = (int)eventHandlerDetour;// I don't remmeber why this is here
#ifdef blippositionhookcrap
	setupBlipPosHook();
#endif
	*(volatile unsigned int*)0x3B07B4 = 0x60000000;//DELETE_ENTITY fix delete entity fix for script
	diskErrorDetourSetup();
	//*(volatile unsigned int*)0x138E670 = 0x60000000;//this is for host kick, make it not show up

	*(int*)0x138E660 = *(int*)0x138E664;//make it so r4 gets the value loaded for the kicik call in the hook
	//PatchInJumpAddr(0x138E664,(int)hostKickFunctionCallback,true);//kick kick with message
	//sys_ppu_thread_exit(nothing);
	//return;
	setupHookSessions();//hook for going to online session to patch max players
	//randomizeAddresses();
	//processHelicopterShit_patch();
	//randomizeAddresses();
	//write_process((char*)0x13E26EC,nop_bytes,4);//disable text messages - not working
	//write_process((char*)(0x13E20A8-0xe20),nop_bytes,4);//kick from host, this is from inside the func that is only called once to init some things
	randomizeAddresses();
	//*(volatile unsigned int*)0x3FA624 = 0x60000000;//patch the call to REPORT_CASH_SPAWN_EVENT_local
	randomizeAddresses();
	//write_process((char*)(0x13E25CC-0xe20),nop_bytes,4);//blacklist -- again this deos nothign
	//randomizeAddresses();
	//randomizeAddresses();
	//write_process((char*)(0x13E17B8/*0x13E25D8-0xe20*/),nop_bytes,4);//regular kick? this actually does nothing
	//write_process((char*)0x,nop_bytes,4);
	//write_process((char*)0x,nop_bytes,4);
	//randomizeAddresses();
	*(volatile unsigned int*)0x404B24 = 0x60000000;//CREATE_PED script fix online
	
	//to make 0x13AE3B0 branch to NETWORK_INCREMENT_STAT, 0x13AE618 to branch to, 0x13AE3C0 write the branch
	//*(volatile unsigned int*)0x13AE3C0 = 0x48000258;//b 0x258;
	write_process((char*)(0x13AE3C0),&patchthestatdata,4);

	//randomizeAddresses();
	write_process((char*)(addrstruct().objectBypass^dataDecryptor())/*0x3F8B84*/,nop_bytes,4);//all object spawn fix (CREATE_OBJECT)  SHOULD BE THE SAME
	//randomizeAddresses();
	//randomizeAddresses();
	//write_process((char*)0x435870,nop_bytes,4);//all object spawn fix (REQUEST_MODEL)   no this doesn't work, I am a dummy
	//randomizeAddresses();
	//write_process((char*)0x435884,nop_bytes,4);//all object spawn fix (REQUEST_MODEL)   no again not working I am dummy
	setuptriggerScriptEventHook();//this is actually stat get bool fix
	//write_process((char*)0x00F11C30,nop_bytes,4);//allows me to do all values 0 through 7 on car data   CANNOT UPDATE WITHOUT DEBUGGING
	//write_process((char*)0x00F11C60,nop_bytes,4);//allows me to do all values 0 through 7 on car data   CANNOT UPDATE WITHOUT DEBUGGING
	
	
	//setupPlayerBroadcastVariablesSendDetour();//this is for the broadcast send

	*spoofNPTypeVal_ptr = 1;//patch to english servers on start in case of modified stuffs (tsunami, other files, ect)

	if (getBLJM()) {
		*spoofNPTypeVal_ptr = 2;//jap servers boiiii
	}


	eventFunction_special_Hook_setup();

	setup_WEAPON_DAMAGE_EVENT_local_hook();

	//setupRegisterPlayerBroadcastVariablesHook();
	
	
	
	/*
	write_process((char*)0x13E1BC4,nop_bytes,4);//anti kick
	write_process((char*)0x13A53BC,nop_bytes,4);//anti kick   None of these worked anyways so just gonna take them out
	write_process((char*)0x139AD98,nop_bytes,4);//anti kick
	write_process((char*)0x139ACF8,nop_bytes,4);//anti kick
	write_process((char*)0x139AC70,nop_bytes,4);//anti kick
	write_process((char*)0x138F1E0,nop_bytes,4);//anti kick
	write_process((char*)0x1359D98,nop_bytes,4);//anti kick
	*/

	//write_process((char*)0x012F7EAC,nop_bytes,4);//end lobby fix
	//write_process((char*)0x012F7EB0,nop_bytes,4);//end lobby fix
	//write_process((char*)0x03E4188,nop_bytes,4);//end lobby fix
	//write_process((char*)0x03E418C,nop_bytes,4);//end lobby fix
	//write_process((char*)0x03E4190,nop_bytes,4);//end lobby fix
	//NETWORK::NETWORK_SESSION_END();
	//write_process((char*)0x,nop_bytes,4);//end lobby fix
	//sub_138A124(*(volatile int*)0x1CF72C4,1,0);
	setupPedSpawnDetour();
	//write_process((char*)(0x1836F70+11),"MULE",4);
	//randomizeAddresses();
	randomizeAddresses();
	
	//randomizeAddresses();
	//eventHandlerDetourStart();
	//initSpecialRenderHook();
	//randomizeAddresses();
	//these both do not work!
	//13E25D8
	//write_process((char*)0x13E25D8,nop_bytes,4);// anti-kick
	//13E20A8 request kick from host
	//write_process((char*)0x13E20A8,nop_bytes,4);// anti-kick from host

	//char is_player_playing_call[] = {0x48, 0x42, 0x2B, 0x97};
	//write_process((char*)0x1574290,is_player_playing_call,4);//add_explosion
	//write_process((char*)0x3B0088,returntrue,8);//ATTACH_ENTITY_TO_ENTITY disable             //original 7C 08 02 A6 31 81 FF E8
	//write_process((char*)0x3B0390,returntrue,8);//ATTACH_ENTITY_TO_ENTITY_PHYSICALLY disable  //original 7C 08 02 A6 31 81 FF F0
	//write_process((char*)0x12E4EDC,returntrue,8);//the real is host function. prolly doesn't work tho. yep, doesn't work
	//write_process((char*)0x3F39CC,returnfalse,8);//_IS_PLAYER_BANNED 0 means you are banned so we return true
	//write_process((char*)0x3F3910,returnfalse,8);//_IS_ROCKSTAR_BANNED 0 means you are banned so we return true
	//write_process((char*)0x3F3964,returnfalse,8);//_IS_ROCKSTAR_BANNED 0 means you are banned so we return true
	//loadStartingConfig();

	*changeModelPlayerId_ptr = -1;

	//write_process((char*)0x3E41C4,trueandnop,8);//bypass host on kick player
	//char nop[] = {0x60,0x00,0x00,0x00};
	//write_process((char*)0x3E41C4,nop,4);//kick host check disable 1
	//write_process((char*)0x3E41C8,nop,4);//kick host check disable 2
	//always host
	//write_process((char*)0x3E3B00,returntrue,8);

	//native patch n jump used to be here

	/*while (true) {
		popMenu();
		sleep(1);
	}*/
	/*for (;;) {
		debugger::loop();
	}*/

	//MOVED DOWNLOAD STUFF TO HERE
	//jk
	//printf("Downloading creation files\n");
	//fixRequestControlWithPools();
	//*(volatile unsigned int*)0x12C2F24 = 0x38C00000;

	setup_hooks();

	//start weather patch SET_WEATHER_TYPE_NOW_PERSIST
	randomizeAddresses();
	*(volatile unsigned int*)0x10953F8 = 0x60000000;
	//randomizeAddresses();
	//randomizeAddresses();
	*(volatile unsigned int*)0x10953A4 = 0x60000000;
	//randomizeAddresses();
	*(volatile unsigned int*)0x3D3EB0 = 0x60000000;
	randomizeAddresses();
	//end weather patch
	
	//*(volatile unsigned int*)0xEDF9EC = 0x60000000;//freeze bypass
	//*(volatile unsigned int*)0xEDF944 = 0x60000000;//freeze bypass
	/**(volatile unsigned int*)0x1C9624C = 0;
	*(volatile unsigned int*)0xEDF648 = 0x38600000;//li r3, 0
	*(volatile unsigned int*)0xEDF64C = 0x4E800020;//blr
	*(volatile unsigned int*)0xEDF834 = 0x4E800020;
	*(volatile unsigned int*)0x354444 = 0x38800004;//li r4, entityType... 
	*(volatile unsigned int*)0x354450 = 0x38600000;//li r3, 0
	*(volatile unsigned int*)0x354650 = 0x38600000;//li r3, 0
	*(volatile unsigned int*)0x354704 = 0x38800000;//li r4, entityType... 
	*(volatile unsigned int*)0x35476C = 0x38600000;//li r3, 0
	*(volatile unsigned int*)0x353164 = 0x38600000;//li r3, 0
	*(volatile unsigned int*)0x354A48 = 0x38800000;//li r4, entityType... 
	*(volatile unsigned int*)0x336DB0 = 0x4E800020;//blr
	*(volatile unsigned int*)0x447A0000*/
	//0x0EDFA3C  = nop
	//0x0EDFA48  = nop
	//0x00EDFA50 = nop
	//0x000EDFA54  = nop
	//setupSendHook();//for network send
	//sleep(10000);
	/*printf("Adding stat native\n");
	addStatNative();//adding native
	printf("done Adding stat native\n");*/
	//debugLogFile("AB2\n");
	//randomizeAddresses();

	
#ifdef creationSpawner
	downloadFile("dl/base.creation","gopro_2027/base.creation",forge::sizeOfCreation);
	//randomizeAddresses();
	downloadFile("dl/base2.creation","gopro_2027/base2.creation",forge::sizeOfCreation);
	//randomizeAddresses();
	downloadFile("dl/base3.creation","gopro_2027/base3.creation",forge::sizeOfCreation);
	//randomizeAddresses();
	downloadFile("dl/carkour.creation","gopro_2027/carkour.creation",forge::sizeOfCreation);
	downloadFile("dl/mazeramp.creation","gopro_2027/mazeramp.creation",forge::sizeOfCreation);
#endif
	//downloadFile("dl/default_settings.a","gopro_2027/settings2.xml",0,true);
	if (!doesFolderExist("/dev_hdd0/tmp/gopro_2027/settings.xml")) {
		downloadFileFromDownloadFolder("default_settings.xml","gopro_2027/settings.xml");
		//downloadFile("dl/default_settings.xml","gopro_2027/settings.xml",0,true);
	}

	if (!doesFolderExist("/dev_hdd0/tmp/gopro_2027/gta_v_blus_addresses_narray.dat")) {
		downloadFileFromDownloadFolder("gta_v_blus_addresses_narray.dat", "gopro_2027/gta_v_blus_addresses_narray.dat");
	}
	if (!doesFolderExist("/dev_hdd0/tmp/gopro_2027/gta_v_blus_addresses_oarray.dat")) {
		downloadFileFromDownloadFolder("gta_v_blus_addresses_oarray.dat", "gopro_2027/gta_v_blus_addresses_oarray.dat");
	}

	//The script sticks until the player restarts their game
	
	/*if (!doesFolderExist("/dev_hdd0/tmp/gopro_2027/rock_menu2.csc_apiiintense")) {
		downloadFileFromDownloadFolder("rock_menu2.csc_apiiintense", "gopro_2027/rock_menu2.csc_apiiintense");
	}*/
	/*if (!doesFolderExist("/dev_hdd0/tmp/gopro_2027/rock_menu2.csc")) {
		downloadFileFromDownloadFolder("rock_menu2.csc_vcahax", "gopro_2027/rock_menu2.csc");

		writeToFile("/dev_hdd0/tmp/gopro_2027/injmenu.dat", (char*) { (char)RCEMenu_VCAHax }, 1);
	}*/
	if (!doesFolderExist("/dev_hdd0/tmp/gopro_2027/rock_menu2.csc")) {
		downloadFileFromDownloadFolder("rock_menu2.csc_paradisemicro", "gopro_2027/rock_menu2.csc");
		writeToFile("/dev_hdd0/tmp/gopro_2027/injmenu.dat", (char[]) { RCEMenu_Paradise }, 1);
	}

	if (!doesFolderExist("/dev_hdd0/tmp/gopro_2027/background.dds")) {
		downloadFileFromDownloadFolder("background.dds", "gopro_2027/background.dds");
	}

	initCachedStrings();

	toggleRedux();//do the redux thingy :)
	
	pauseRTMThread = false;

	//doDownloadRPF = true;
	

	//printf("End of this part\n");
#ifdef DEVELOPER1
	//doUpdate();
#endif


#if DOAUTH == 1
	if(getAuthed()) {
		//cellMsgDialogOpen(1,"              Welcome to\n               Paradise!",my_dialog2,(void*) 0x0000aaab, NULL);
		//encryptDecrypt(introtext,extrabuffer,62);
		//cellMsgDialogOpen(1,extrabuffer,my_dialog2,(void*) 0x0000aaab, NULL);
		//randomizeAddresses();
	} else {
		
		//cellMsgDialogOpen(1,introtextfail2,my_dialog2,(void*) 0x0000aaab, NULL);
		//encryptDecrypt(introtextfail,extrabuffer,84);
		//cellMsgDialogOpen(1,extrabuffer,my_dialog2,(void*) 0x0000aaab, NULL);
	}
#endif
	//sleep(10000);
	//#if CEX == 0
	//updateSprx();
	//#endif
	//updateLogAndDonators();
	//randomizeAddresses();
	//debugLogFile("AB3\n");
	//printf("yieldinng it\n");
	//sys_ppu_thread_yield();
	//sleep(10000);
	//dialog("hey!");
	readSettingsFileData();//keep this at end because an invalid config could cause the thread to crash
//#if CRASH_DEBUGGER == 0

#if HEN_MODE == 0

	__asm("lis %r3, 0xFEEE");//3C 60 FE EE 
	__asm("ori %r3, %r3, 0xDECC");//60 63 DE CC 
	unsigned char *beginEncryptThread = (unsigned char*)*(int*)Thread;
	//printf("Thread start location: 0x%X\n",beginEncryptThread);
	char findBytesStart[] = {(char)0x3C,(char)0x60,(char)0xFE,(char)0xEE,(char)0x60,(char)0x63,(char)0xDE,(char)0xCC};//3C 60 FE EE 60 63 DE CC
	int foundIndexEndDecrypt = findIndexOf((char*)beginEncryptThread,findBytesStart,1000000,8);
	decrypt(beginEncryptThread,0,foundIndexEndDecrypt);
	//printf("Finished encrypting %i\n",foundIndexEndDecrypt);
#endif

	//printf("Exiting!\n");
	sys_ppu_thread_exit(nothing);
//#endif
	/*for (;;) {
		sleep(2);
		for (int i = 0; i < 18; i++) {
			if (PlayerMods::playerIpInfo[i].requestLocationData) {
				strncpy(PlayerMods::playerIpInfo[i].locationData,getIpInfo(PlayerMods::playerIpInfo[i].ip),sizeof(PlayerMods::playerIpInfo[i].locationData));
				PlayerMods::playerIpInfo[i].requestLocationData = false;
				//sleep(1000);
			}
		}
	}*/
	//sys_ppu_thread_stop(ThreadModuleID);

#if HEN_MODE == 0

	endEncryptFunc();//End A

#endif
}
/*void updateThread(uint64_t gettem) {
	for(;;) {
		sleep(50);
		if (triggerupdate) {
			triggerupdate = false;
			writeFromSocket("gopro2027.xyz","Limbo/limbo.sprx","/dev_hdd0/tmp/GTA.sprx",200000,true);
		}
	}
}*/
/*void exitGameStub() {

}
void exitGame() {
	//0x004A0EE8
	*(volatile unsigned int*)0x004A0F20 = 0x4E800020;
	__asm ("ba 0x004A0EE8");
	//__asm__(  "ba %0, %1, %2" : "=r"( __ppu_asm_tmp ) : "r"( a ), "r"( b ) );
	__asm(  "ba 0x004A0EE8" );
}*/
#pragma endregion
sys_ppu_thread_t rtmthread;
sys_ppu_thread_t rcethread;
//sys_ppu_thread_t decryptthread;
#pragma region prx entry
//unsigned long long endOfEnc = 0xFFEEDDCCBBAA9977;

__ALWAYS_INLINE int findIndexOf(char *in, char *find,int sizeofin,unsigned int sizeoffind) {
	unsigned int lengthOfFind = sizeoffind;
	unsigned int inLength = sizeofin;
	unsigned int currentStartPos = 0;
	unsigned int currentSpotInFind = 0;
	for (unsigned int i = 0; i < inLength; i++) {
		if (in[i] == find[currentSpotInFind]) {
			currentSpotInFind++;
			if (currentSpotInFind == lengthOfFind)
				return currentStartPos+1;
		} else {
			currentStartPos++;
			i = currentStartPos;
			currentSpotInFind = 0;
		}
	}
	return -1;
}

__ALWAYS_INLINE int console_print2(char* a_szText)
{

	uint32_t l_uiTextLen;
	uint32_t l_uiWriteLen;

	l_uiWriteLen	= 0;
	//strlen
	l_uiTextLen = 0;
	while(a_szText[l_uiTextLen] != 0) l_uiTextLen++;
	system_call_4(403, 0, (uint64_t)a_szText, l_uiTextLen, (uint64_t)&l_uiWriteLen);
	return (l_uiTextLen == l_uiWriteLen);

}

__ALWAYS_INLINE void decrypt(unsigned char *data, unsigned int startIndex, unsigned int endIndex, bool quick) {
	// 32 11 07 8a e9 5b 90 c3 06 02 8e 78 09 8e b2 24 d4 d1 14 06 81 34 76 e7 7e 30 28 c1 6d fb 59 3c 9f 3d 9d a8 8f 3a 85 2d 4d 53 e6 9b ed fb f2 01 24 0c cf 53 7e 74 42 fa 86 
	//printf("in decryption\n");
	static char key[57];// = {(char)0x32,(char)0x11,(char)0x07,(char)0x8a,(char)0xe9,(char)0x5b,(char)0x90,(char)0xc3,(char)0x06,(char)0x02,(char)0x8e,(char)0x78,(char)0x09,(char)0x8e,(char)0xb2,(char)0x24,(char)0xd4,(char)0xd1,(char)0x14,(char)0x06,(char)0x81,(char)0x34,(char)0x76,(char)0xe7,(char)0x7e,(char)0x30,(char)0x28,(char)0xc1,(char)0x6d,(char)0xfb,(char)0x59,(char)0x3c,(char)0x9f,(char)0x3d,(char)0x9d,(char)0xa8,(char)0x8f,(char)0x3a,(char)0x85,(char)0x2d,(char)0x4d,(char)0x53,(char)0xe6,(char)0x9b,(char)0xed,(char)0xfb,(char)0xf2,(char)0x01,(char)0x24,(char)0x0c,(char)0xcf,(char)0x53,(char)0x7e,(char)0x74,(char)0x42,(char)0xfa,(char)0x86};
	key[0] = 0x32;key[1] = 0x11;key[2] = 0x7;key[3] = 0x8A;key[4] = 0xE9;key[5] = 0x5B;key[6] = 0x90;key[7] = 0xC3;key[8] = 0x6;key[9] = 0x2;key[10] = 0x8E;key[11] = 0x78;key[12] = 0x9;key[13] = 0x8E;key[14] = 0xB2;key[15] = 0x24;key[16] = 0xD4;key[17] = 0xD1;key[18] = 0x14;key[19] = 0x6;key[20] = 0x81;key[21] = 0x34;key[22] = 0x76;key[23] = 0xE7;key[24] = 0x7E;key[25] = 0x30;key[26] = 0x28;key[27] = 0xC1;key[28] = 0x6D;key[29] = 0xFB;key[30] = 0x59;key[31] = 0x3C;key[32] = 0x9F;key[33] = 0x3D;key[34] = 0x9D;key[35] = 0xA8;key[36] = 0x8F;key[37] = 0x3A;key[38] = 0x85;key[39] = 0x2D;key[40] = 0x4D;key[41] = 0x53;key[42] = 0xE6;key[43] = 0x9B;key[44] = 0xED;key[45] = 0xFB;key[46] = 0xF2;key[47] = 0x1;key[48] = 0x24;key[49] = 0xC;key[50] = 0xCF;key[51] = 0x53;key[52] = 0x7E;key[53] = 0x74;key[54] = 0x42;key[55] = 0xFA;key[56] = 0x86;
	//printf("key is above\n");
	for (unsigned int i = startIndex; i < endIndex; i++) {
		if (i%4 == 0 || i%4 == 1) {
			/*static char dataString[20];
			console_print2("Data: ");
			itoa((unsigned int)data,dataString,16);
			console_print2(dataString);
			console_print2(" ");
			itoa(i,dataString,16);
			console_print2(dataString);
			console_print2("\n");*/
			//data[i] = data[i]^0xFA;
			//printf("about to geddit 0x%X+0x%X\n",data,i);
			unsigned char n[1] = {data[i]^key[(i-startIndex)%sizeof(key)]/*0xFA*/};
			//printf("boutta write\n");
			if (quick == false) {
				write_process_sc(data+i,n,1);
			} else {
			//*(unsigned char*)(data+i) = n[0];
				unsigned int address = ((unsigned int)data + i);
				*(char*)address = n[0];
			}
		}
	}
	//printf("Out of decryption\n");
}

__ALWAYS_INLINE void reverseMemoryArea(unsigned char *data, unsigned int startIndex, unsigned int endIndex, bool quick) {
	unsigned int length = endIndex - startIndex;
	for (unsigned int i = 0; i < length/2-4; i++) {
		if ((startIndex+i)%4 == 0 || (startIndex+i)%4 == 1) {
			unsigned char tmpBegin = data[startIndex+i];

			if (quick == false) {
				write_process_sc(data+startIndex+i,data+endIndex-3-i,1);
				write_process_sc(data+endIndex-3-i,&tmpBegin,1);
			} else {
				*(unsigned char*)(data+startIndex+i) = *(unsigned char*)(data+endIndex-3-i);
				*(unsigned char*)(data+endIndex-3-i) = tmpBegin;
			}
		}
	}
}

__ALWAYS_INLINE void addTheBytesArea(unsigned char *data, unsigned int startIndex, unsigned int endIndex, bool quick) {
	//0xd7, 0xad, 0x6a, 0x5d, 0x65, 0x00, 0xde, 0xdd, 0xb3, 0x7e, 0x67, 0x00, 0xb3, 0x26, 0x53, 0xfa, 0x1d, 0x80, 0x74, 0x08, 0x9b, 0xaa, 0x6b, 0xaa, 0xc8, 0x6f, 0x57, 0xbf, 0x01, 0x5b, 0x95, 0x75, 0x04, 0x08, 0x3a, 0x28, 0x7f, 0x90, 0x32, 0xee, 0x34, 0x9e, 0x33, 0xb0, 0xc1, 0x07, 0xa7, 0x5f, 0xf6, 0x4a, 0x0c, 0x55, 0xe0, 0xd8, 0xf9, 0xf3, 0x2f, 0x54, 0x0d, 0xea, 0x6d, 0x15, 0x1a, 0xa3, 0x01, 0xe3, 0xcc, 0x63, 0xd7, 0xc2, 0x60, 0x3a, 0x24, 0xb7, 0xbc, 0x01
	char key[76];// = {0xd7, 0xad, 0x6a, 0x5d, 0x65, 0x00, 0xde, 0xdd, 0xb3, 0x7e, 0x67, 0x00, 0xb3, 0x26, 0x53, 0xfa, 0x1d, 0x80, 0x74, 0x08, 0x9b, 0xaa, 0x6b, 0xaa, 0xc8, 0x6f, 0x57, 0xbf, 0x01, 0x5b, 0x95, 0x75, 0x04, 0x08, 0x3a, 0x28, 0x7f, 0x90, 0x32, 0xee, 0x34, 0x9e, 0x33, 0xb0, 0xc1, 0x07, 0xa7, 0x5f, 0xf6, 0x4a, 0x0c, 0x55, 0xe0, 0xd8, 0xf9, 0xf3, 0x2f, 0x54, 0x0d, 0xea, 0x6d, 0x15, 0x1a, 0xa3, 0x01, 0xe3, 0xcc, 0x63, 0xd7, 0xc2, 0x60, 0x3a, 0x24, 0xb7, 0xbc, 0x01};
	key[0] = 0xD7;key[1] = 0xAD;key[2] = 0x6A;key[3] = 0x5D;key[4] = 0x65;key[5] = 0x0;key[6] = 0xDE;key[7] = 0xDD;key[8] = 0xB3;key[9] = 0x7E;key[10] = 0x67;key[11] = 0x0;key[12] = 0xB3;key[13] = 0x26;key[14] = 0x53;key[15] = 0xFA;key[16] = 0x1D;key[17] = 0x80;key[18] = 0x74;key[19] = 0x8;key[20] = 0x9B;key[21] = 0xAA;key[22] = 0x6B;key[23] = 0xAA;key[24] = 0xC8;key[25] = 0x6F;key[26] = 0x57;key[27] = 0xBF;key[28] = 0x1;key[29] = 0x5B;key[30] = 0x95;key[31] = 0x75;key[32] = 0x4;key[33] = 0x8;key[34] = 0x3A;key[35] = 0x28;key[36] = 0x7F;key[37] = 0x90;key[38] = 0x32;key[39] = 0xEE;key[40] = 0x34;key[41] = 0x9E;key[42] = 0x33;key[43] = 0xB0;key[44] = 0xC1;key[45] = 0x7;key[46] = 0xA7;key[47] = 0x5F;key[48] = 0xF6;key[49] = 0x4A;key[50] = 0xC;key[51] = 0x55;key[52] = 0xE0;key[53] = 0xD8;key[54] = 0xF9;key[55] = 0xF3;key[56] = 0x2F;key[57] = 0x54;key[58] = 0xD;key[59] = 0xEA;key[60] = 0x6D;key[61] = 0x15;key[62] = 0x1A;key[63] = 0xA3;key[64] = 0x1;key[65] = 0xE3;key[66] = 0xCC;key[67] = 0x63;key[68] = 0xD7;key[69] = 0xC2;key[70] = 0x60;key[71] = 0x3A;key[72] = 0x24;key[73] = 0xB7;key[74] = 0xBC;key[75] = 0x1;
	unsigned int length = endIndex - startIndex;
	for (unsigned int i = 0; i < length; i++) {
		if ((startIndex+i)%4 == 0 || (startIndex+i)%4 == 1) {
			unsigned char val = data[startIndex+i] + key[i%sizeof(key)];
			if (quick == false) {
				write_process_sc(data+startIndex+i,&val,1);
			} else {
				unsigned int address = (unsigned int)data+startIndex+i;
				*(unsigned char*)address = val;
			}
		}
	}
}

//unsigned int addressCheckFrom = 0;
__ALWAYS_INLINE void findAndDecrypt() {
	//DECRYPT STUFF HERE
	unsigned char *startOfPRX = (unsigned char*)(*(volatile unsigned int*)vsnprintf);
	char findBytesStart[] = {(char)0x3C,(char)0x60,(char)0xFF,(char)0xEE,(char)0x60,(char)0x63,(char)0xDD,(char)0xCC};//3C 60 FF EE 60 63 DD CC
	char findBytesEnd[] = {(char)0x3C,(char)0x60,(char)0xFF,(char)0xEE,(char)0x60,(char)0x63,(char)0xDD,(char)0xCD};//3C 60 FF EE 60 63 DD CD
	int start = findIndexOf((char*)startOfPRX,findBytesStart,1000000,8);
	int end = findIndexOf((char*)startOfPRX,findBytesEnd,1000000,8);
	//printf("found indexes! %i %i\n",start,end);
	char nop[] = {0x60,0,0,0,0x60,0,0,0};
	write_process_sc((void*)(startOfPRX+start),nop,8);
	write_process_sc((void*)(startOfPRX+end),nop,8);
	//addressCheckFrom = (unsigned int)startOfPRX+start;
	//printf("test: %X %X %X %X\n",*(volatile unsigned int*)(startOfPRX+start+0x8),*(volatile unsigned int*)(startOfPRX+start+0xC),*(volatile unsigned int*)(startOfPRX+start+0x10),*(volatile unsigned int*)(startOfPRX+start+0x14));
	//__asm("trap");
	//printf("start: %i\n",end);
	//printf("startend: 0x%X 0x%X\n",start,end);//THESE ADDRESSES ARE THE SAME WHEN OPENED IN IDA
	addTheBytesArea(startOfPRX,start+0x8,end);
	reverseMemoryArea(startOfPRX,start+0x8,end);
	decrypt(startOfPRX,start+0x8,end);
}

__ALWAYS_INLINE void decryptDataSegment() { 

	
	sys_prx_module_info_t MainModuleInfo;
	char filename[SYS_PRX_MODULE_FILENAME_SIZE];
	sys_prx_segment_info_t segments[2];
	MainModuleInfo.size = sizeof(MainModuleInfo);
	MainModuleInfo.segments = segments;
	MainModuleInfo.segments_num = sizeof(segments) / sizeof(sys_prx_segment_info_t);
	MainModuleInfo.filename = filename;
	MainModuleInfo.filename_size = sizeof(filename);
	sys_prx_get_module_info(sys_prx_get_my_module_id(), SYS_PRX_MODULE_FILENAME_SIZE, &MainModuleInfo);
	unsigned int addr = MainModuleInfo.segments[1].base;
	int sz = MainModuleInfo.segments[1].memsz;//filesz is not correct... memsz is the size that aligns with the ida and prx file
	

	char key[35];
	key[0] = 0x27; key[1] = 0xC5; key[2] = 0x8B; key[3] = 0x13; key[4] = 0xA8; key[5] = 0x97; key[6] = 0x4B; key[7] = 0xCB; key[8] = 0x0C; key[9] = 0x1F; key[10] = 0x47; key[11] = 0xEB; key[12] = 0x37; key[13] = 0x4F; key[14] = 0xEE; key[15] = 0xE0; key[16] = 0x7D; key[17] = 0xFB; key[18] = 0x0D; key[19] = 0x91; key[20] = 0xE4; key[21] = 0xB1; key[22] = 0x07; key[23] = 0x4A; key[24] = 0x58; key[25] = 0xE0; key[26] = 0x19; key[27] = 0x36; key[28] = 0x31; key[29] = 0x01; key[30] = 0x86; key[31] = 0x59; key[32] = 0xC6; key[33] = 0x11; key[34] = 0x6C;
	//*(int*)0x10024008 = 5;
	//*(int*)0x10024000 = addr - MainModuleInfo.segments[0].base;
	//*(int*)0x10024004 = sz;

	//unsigned int addrorig = addr;

	for (int i = 0; i < sz; i++) {
		unsigned char val = *(unsigned char*)(addr) ^ key[i % sizeof(key)];
		write_process_sc((void*)addr, &val, 1); 
		addr++;
	}
	
	
	//Seg 2: addr: 0x70000, size: 0x2300
	//printf("Seg 2: seg0addr: 0x%X, addr: 0x%X, size: 0x%X 0x%X   %i %i\n", MainModuleInfo.segments[0].base, addrorig, sz, MainModuleInfo.segments[1].memsz, MainModuleInfo.segments_num, MainModuleInfo.all_segments_num);
	
}

/*__ALWAYS_INLINE */__attribute__((noinline)) void startThreads() {


	//setup_createEventAndIncrement_hook();

	encryptFunctionStart((void*)startThreads);
	

	//*(int*)0x10500 = 0x7FE10808;//add temporary trap
	 
	//*(int*)0x107E0 = 0x48000024; 
	
	//remove the savegame threads
	 
	//strcpy((char*)0x1822668,"none");
	//*(int*)0x47B478 = 0x60000000;

	//*(int*)0x12A7FA4 = 0x38600000;//GetSavegameFileSizeThread
	//*(uint64_t*)0xA9D81C = 0x386000004E800020;//FreeSpaceCheckThread ExtraSpaceCheckThread SaveThread
	//*(int*)0x12A1BA8 = 0x38600000;//SizesOfAllSavesThread
	
	//*(uint64_t*)0xA9DF08 = 0x386000004E800020;//LoadThread this is the one for the prompt of screen brightness, but leaving it in causes memory issues
	//*(int*)0x12A395C = 0x38600000;//its this one but I can't remove it :/
	//*(int*)0x12A3BC0 = 0x38600000;//not this one
	//*(int*)0x12A7E4C = 0x38600000;//not this one
	


	//*(uint64_t*)0xCFFEF8 = 0x386000004E800020;//GetSaveNamesThread

	//createThreadHookStart();

	//*(int*)0x208CC = 0x60000000;//load profile remove it CRASH
	//*(char*)(0x129FA50 + 0x2) = 0;//GetSaveNamesThread stack size

	//*(int*)0x12A9F94 = 0x38600000;//GetSavegameFileModifedTimeThread
	//*(int*)0x12B3838 = 0x38600000;//GetSaveNamesThread  INFINITE LOADING
	//*(uint64_t*)0xA9E5A8 = 0x386000004E800020;//GetCreatorThread
	*(int*)0x13DE310 = 0x38600000;//VoiceChat Worker

	//*(char*)(0xF56288 + 2) = 0x40;//RMPTFX Update stack size

	sys_ppu_thread_create(&ThreadModuleID, Thread, 0, 0x5AA, 4096*3/*5 9 worked also*/, 0, "gopro_2027's Mod Menu");//0xFFF is too small of a stack size. causes it to crash when calling auth
																													 //*(volatile unsigned int*)0x188E460 = *(volatile unsigned int*)Thread;
	sys_ppu_thread_create(&rtmthread, RTMTool::RTMThread, 0, 0x5AA, 4096/*0x1000*/*2, 0, "rtm thread");
	sys_ppu_thread_create(&rcethread, rceThread::Thread, 0, 0x5AA, 4096/*0x1000*/ * 7, 0, "ltt thread");//lol

	//while (socketConnectionStuff::networkingThreadDone == false)
	//	sleep(1000);//wait until test socket thread is over

	//printf("Threads started!\n");
	encryptFunctionEnd();
}


/*__attribute__ ((naked)) */extern "C" int main(void)
{

#if PAUSE_ON_LOAD == 1
	__asm("trap");
#endif
	
	//decryptDataSegment(); 

#if HEN_MODE == 0

	inline_encryptFunctionStart((void*)main);


	
	//*(int*)0x4BB1EC = TRAP;
	//printf("Running main!\n");
	//printf("verification:\n0x%X 0x%X\n",*(volatile unsigned int*)0x0250FED4,);
	//obfStart();
	/*
	force threads to keep trying
	*(volatile unsigned int*)0xAE7AF0 = 0x38600001;//li %r3, 1 //1 second
	*(volatile unsigned int*)0xAE7AF4 = 0x4BFFFE71;//bl 0xAE7964-0xAE7AF4 (-0x190 aka -400) (sleep)  4BFFFE70   4B FF FE 71  = 0x4B000000 + (0x1000000-value cuz backwards) + 1 for bl
	*(volatile unsigned int*)0xAE7AF8 = 0x60000000;//nop
	*(volatile unsigned int*)0xAE7AFC = 0x4BFFFFC0;//b loc_AE7ABC
	*/
	/*int _prx_obf_start = *(volatile int*)obfStart;//equivalent of find("3C 60 FF EE 60 63 DD CC 4E 80 00 20 ")
	int _prx_obf_end = *(volatile int*)main;//equivalent of _prx_obf_start+
	//printf("\n\nStart: 0x%X, End: 0x%X, beginFunc: 0x%X, 0x%X\n\n\n\n",_prx_obf_start,_prx_obf_end,(int)main,obfStart());
	for(int i = _prx_obf_start; i < _prx_obf_end; i++){
		*(char*)(i) = *(char*)(i)^0xFA;
	}*/
	//*(volatile unsigned int*)0x244A50 = 0x60000000;
	//static char *jp = "BLJM61019";
	//*(char**)(0x1C7E084) = jp;
	//strncpy((char*)0x1809384,"BLJM61019",9);
	//*(volatile unsigned int*)0x12D9D60 = 0x48000055;//bl 0x54  this should set to only do that maybe
	//*(volatile unsigned int*)0x12E2FE0 = 0x4E800020;//test nop this and see what happens
	//sys_ppu_thread_create(&decryptthread, decryptThread, 0, 0x5AA, 4096*1, 0, "decrypt thread");

	//set it to always say JP version, this kinda works :/
	
	/*
	*(volatile unsigned int*)(0x0D2BEFC) = 0x38600002;
	*(volatile unsigned int*)(0x0D2BEFC+0x4) = 0x4E800020;
	*/
	
	/*char *MSAA_2xMS = "2xMS";
	for (int i = 0; i < 4; i++) {
		*(char*)(0x18266C4+0x5+i) = MSAA_2xMS[i];
	}*/
	//*(volatile unsigned int*)(0xBCE7CC) = 0x60000000;//msaa
	//*(volatile unsigned int*)0x1FCF10C = *(volatile unsigned int*)0x1F87098;//msaa thing again
	//printf("did shit!\n");
	//*(volatile unsigned int*)0x1CF7250 = (unsigned int)japStr;
	
	//*(char*)(0x01247450+0x2) = 0x6;//screen res
	//printf("\n\n\nSYTYGYUEDGFH\n\n\n");



	/*
	uint64_t unkVal1,unkVal2,unkVal3;
	unsigned int bootparam;
	sys_get_system_parameter(&unkVal1,&unkVal2,&unkVal3,&bootparam);
	printf("Boot parameter: 0x%X 0x%X 0x%X 0x%X\n",unkVal1,unkVal2,unkVal3,bootparam);*/

	//dialog("SPRX is being ran! Installed correctly!\n");

#ifndef kjfdsghnsfd
	
	//findAndDecrypt();//for the intro thread
	
	
	findAndDecrypt();//from end of this function to the last one found (write all globals)
	findAndDecrypt();//from vsnprintf to end of main thread (which was put right before the intro func luckily)

#endif

	//findAndDecrypt();//for misc stuff in mods.h, trying to cover stuff before this func
	//findAndDecrypt();//for function that starts rtm thread aka startThreads()
	//dialog("Decryption finished without error!");
	//__asm("trap");
	//*(volatile unsigned int*)(startOfPRX+start+0x0) = 0x60000000;
	//*(volatile unsigned int*)(startOfPRX+start+0x4) = 0x60000000;
	//printf("about to start threads!\n");

	//printf("Hello!\n");

#define loadUsbRPF false
#if loadUsbRPF == false
	
	//static char *paradiseRpfLocalDir = "update:/Paradise.rpf";
	static char *paradiseRPFDirectoryInTmp = "/dev_hdd0/tmp/gopro_2027/Paradise.rpf";
	if (getFileSize(paradiseRPFDirectoryInTmp/*paradiseRpfDirectory*/) == 66447360) {
		//printf("Paradise RPF Exists and with proper size!\n");
		/*char *para = "Paradise.rpf";
		char *orig = (char*)(0x181F00C+0x8);
		for (int i = 0; i < 12; i++) {
			orig[i] = para[i];
		}*/
		*(int*)0x375DB4 = 0x839CF00C;//lwz %r4, 0(%r28)
		*(int*)0x181F00C = (int)paradiseRPFDirectoryInTmp;//paradiseRpfDirectory
		//printf("Set the load info!\n");
	}

	static char* bljmRPFDirectoryInTmp = "/dev_hdd0/tmp/gopro_2027/BLJM.rpf";

	if (getBLJM()) {
		printf("Trying to load bljm rpf\n");
		if (getFileSize(bljmRPFDirectoryInTmp) == 90209280) {
			*(int*)0x375DB4 = 0x839CF00C;//lwz %r4, 0(%r28)
			*(int*)0x181F00C = (int)bljmRPFDirectoryInTmp;//paradiseRpfDirectory
			//printf("Actually Not loading custom rpf!!!!!!!!!!!!!!!!!\n");
		}
		else {
			printf("BLJM file is invalid, not loading");
		}
	}

	

#else
	/*
	//max of 0x18 24 characters
	static char *hddString = "/dev_usb000/update.rpf";
	strncpy((char*)0x181F00C,hddString,24);//24 is size for that string to be at
*/
#endif
	
	
	startThreads();

	

	//printf("Started threads!\m");
	//printf("Decrypted!\n");
	//printf("test: %X %X %X %X\n",*(volatile unsigned int*)(addressCheckFrom+0x8),*(volatile unsigned int*)(addressCheckFrom+0xC),*(volatile unsigned int*)(addressCheckFrom+0x10),*(volatile unsigned int*)(addressCheckFrom+0x14));
	
#if HEN_MODE == 0

	inline_encryptFunctionEnd();


	//__asm("lis %r3, 0xFFEE");//3C 60 FF EE 
	//__asm("ori %r3, %r3, 0xDDCC");//60 63 DD CC 
	//startFunc();
	startEncryptFunc();//Start B

#endif
	
#endif
	return SYS_PRX_RESIDENT;
	//return startOfEnc + endOfEnc;
	//*(volatile int*)(*(volatile int*)0x1CC5790+0x10) = amount of objects in pool
	//*(volatile int*)(*(volatile int*)0x1CC5790) = start of pool
	/*struct entity {
	unsigned int unknown;
	unsigned int addr;
	}
	*/
	//this is start of prx. search bytes:
	//3C 60 FF EE 60 63 DD CC
}
#pragma endregion
/*







first one we look at is the ip in COD
its hidden in 4 bytes
same as gta

in bytes that is


so the xuid is the 8 bytes before the name on COD
so its located at 0x00F9E690 if you are in custom game on your own




                    this.gameIngame = 0U;
                    this.gameInParty = 0U;
                    this.gameInterval = 136U;
                    this.gameName = 1073896576U;
                    this.gameIp = 1073896648U;
                    this.gamePartyName = 1073896576U;
                    this.gamePartyIp = 1073896648U;
                    this.numOfPlayers = 99U;
                    this.canUse = 0U;

  private uint gameIngame = 0;
        private uint gameInParty = 0;
        private uint gameInterval = 0;
        private uint gameName = 0;
        private uint gameIp = 0;
        private uint gamePartyName = 0;
        private uint gamePartyIp = 0;
        private uint numOfPlayers = 0;
        private uint canUse = 0;
        private uint nameOfs = 0;
        private uint ipOfs = 0;
dank hax


*/


/*
AI::TASK_START_SCENARIO_IN_PLACE
task patches:
0x4883E4 = nop
0x1373B20 = nop

*/

/*
PC code:
NETWORK_INCREMENT_STAT(int32_t player, uint32_t hash, int32_t value) {
	//sub_7FF694188674 gets the player data
	//sub_7FF69488741C sets the stat
	sub_7FF69488741C(hash,value,sub_7FF694188674(player,1));

	//sub_7FF694188674(ebx,dl)
	//sub_7FF69488741C(ecx,edx,r8)
	//sub_7FF69442FAD4 NETWORK_PLAYER_GET_NAME
}
*/

//XBOX Code:
/*
namespace XBOX {
	void setWeather(char *weatherType) {
		*(volatile unsigned int*)0x82C6CDC8 = 0x60000000;
		*(volatile unsigned int*)0x82533CBC = 0x60000000;
		*(volatile unsigned int*)0x82533CFC = 0x60000000;
		GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST(weatherType);
	}
	void incrementPlayerStatInt(int player, unsigned int hash, unsigned int amount) {
		unsigned int playerDataPointer = ((unsigned int(*)(int, int)) 0x82918F38)(player,1);
		((void(*)(unsigned int, unsigned int, unsigned int)) 0x830DD390)(hash,amount,playerDataPointer);
	}
}*/

/*
places my ip shows up at:
0 01FFE6A4 475BD1A1
0 01FFFD00 475BD1A1
0 0205CEC4 475BD1A1  this one  set 0x0016B6A08 to nop to make it not overrite
0 020635D4 475BD1A1

0 01FFFD00 475BD1A1 showed up after I went to an online lobby

tw trap code 7FE00008 which is tw   31,r0,r0


make tasks work:
0x4883E4 = nop
0x1373B20 = nop but it makes it stop working


button spots:

0 01FD7D90 00000002
0 01FD87F4 00000002
0 01FD87F8 00000002


*/

/*
 Hash playerModel = ENTITY::GET_ENTITY_MODEL(PLAYER::GET_PLAYER_PED(isSelected));
 for (int i = 0; i < 18; i++)
 {
  char RegionBuffer[2][10];
  int Handle[13];
  NETWORK::NETWORK_HANDLE_FROM_PLAYER(isSelected, &Handle[0], 13);
  char *RealName = NETWORK::NETWORK_GET_GAMERTAG_FROM_HANDLE(&Handle[0]);
  char *ipName = readbytesIP(0x40025C80 + (i * 136), 100);
  if (!strcmp(RealName, ipName))
  {

   int ip = *(int *)(0x40025CC8 + (isSelected * 0x88));
   int internal_ip = *(int *)(0x40025CA8 + (isSelected * 0x88));
   char *Region = readbytesIP(0x40025C96 + (isSelected * 0x88), 100);
   int port = *(volatile int*)(0x40025CCC + (isSelected * 0x88));

   int p1 = (ip & 0xff000000) >> 24;
   int p2 = (ip & 0x00ff0000) >> 16;
   int p3 = (ip & 0x0000ff00) >> 8;
   int p4 = (ip & 0x000000ff) >> 0;

   int p5 = (internal_ip & 0xff000000) >> 24;
   int p6 = (internal_ip & 0x00ff0000) >> 16;
   int p7 = (internal_ip & 0x0000ff00) >> 8;
   int p8 = (internal_ip & 0x000000ff) >> 0;
   int p9 = (port & 0xff000000) >> 24;
   int p10 = (port & 0x00ff0000) >> 16;
   int portToShow = (p9 << 8) | p10;

   sprintf(IPADDR1[0], "%i.%i.%i.%i", p1, p2, p3, p4);
   sprintf(IPADDR1[1], "%i.%i.%i.%i", p5, p6, p7, p8);
   sprintf(IPADDR1[2], "%i", portToShow);
   sprintf(IPADDR1[3], "%s", Region);
   if (strstr(IPADDR1[0], "255.255.255.255") == NULL && strstr(IPADDR1[0], "0.0.0.0") == NULL)
   {
    strcpy(RegionBuffer[0], IPADDR1[3]);
    memcpy(RegionBuffer[1], RegionBuffer[0], strlen(RegionBuffer[0]) - 3);
    PrintTextRightJustify_Stat(IPADDR1[0], ((XValue)+0.230f) + 0.108f, (12 * textHeight) + YValue, 0.35f, 0.35f, optionsRed, optionsGreen, optionsBlue, selectedTextOpacity, false);
    PrintTextRightJustify_Stat(IPADDR1[1], ((XValue)+0.230f) + 0.108f, (13 * textHeight) + YValue, 0.35f, 0.35f, optionsRed, optionsGreen, optionsBlue, selectedTextOpacity, false);
    PrintTextRightJustify_Stat(IPADDR1[2], ((XValue)+0.230f) + 0.108f, (14 * textHeight) + YValue, 0.35f, 0.35f, optionsRed, optionsGreen, optionsBlue, selectedTextOpacity, false);
    PrintTextRightJustify_Stat(IPADDR1[3], ((XValue)+0.230f) + 0.108f, (15 * textHeight) + YValue, 0.35f, 0.35f, optionsRed, optionsGreen, optionsBlue, selectedTextOpacity, false);
   }
   else
   {
    PrintTextRightJustify_Stat("N/A", ((XValue)+0.230f) + 0.108f, (12 * textHeight) + YValue, 0.35f, 0.35f, optionsRed, optionsGreen, optionsBlue, selectedTextOpacity, false);
    PrintTextRightJustify_Stat("N/A", ((XValue)+0.230f) + 0.108f, (13 * textHeight) + YValue, 0.35f, 0.35f, optionsRed, optionsGreen, optionsBlue, selectedTextOpacity, false);
    PrintTextRightJustify_Stat("N/A", ((XValue)+0.230f) + 0.108f, (14 * textHeight) + YValue, 0.35f, 0.35f, optionsRed, optionsGreen, optionsBlue, selectedTextOpacity, false);
    PrintTextRightJustify_Stat("N/A", ((XValue)+0.230f) + 0.108f, (15 * textHeight) + YValue, 0.35f, 0.35f, optionsRed, optionsGreen, optionsBlue, selectedTextOpacity, false);

   }
  }
 }

*/


/*
unsigned int getFilesizeOfImage(unsigned int pixelSize) {
	const unsigned int sizeof32 = 1152;//bit depth 32
	const unsigned int sizeof64 = 4224;
	const unsigned int sizeof128 = 0;
	const unsigned int sizeof256 = 65664;
	const unsigned int sizeof512 = 262272;
	const unsigned int sizeof1024 = 0;
	unsigned int fileSize = 0;
	switch(pixelSize) {
	case 32: fileSize = sizeof32;break;
	case 64: fileSize = sizeof64;break;
	case 128: fileSize = sizeof128;break;
	case 256: fileSize = sizeof256;break;
	case 512: fileSize = sizeof512;break;
	case 1024: fileSize = sizeof1024;break;
	}
	return fileSize;
}

bool overriteImage(char *dictionary, char *name, char *fileName, unsigned int pixelSize = 32) {
	opd_s getTextureAddress_t = {0x3C083C,TOC};
	unsigned int (*getTextureAddress)(char *dict, char *name) = (unsigned int(*)(char*,char*))&getTextureAddress_t;
	unsigned int address = getTextureAddress(dictionary,name);

	if (address < 0x10000) {
		return false;
	}

	char *textureData = (char*)(*(volatile unsigned int*)(address + 0x1c)+0xC0000000);
	char *textureName = (char*)(*(volatile unsigned int*)(address + 0x20));

	if (strcmp(textureName,"none") == 0) {
		return false;
	}

	if (textureData[0] == 'D' && textureData[1] == 'D' && textureData[2] == 'S') {
		textureData+=0x80;
	}
	
	char buf[10000];//image buffer size
	unsigned int fileSize = getFileSize(fileName);
	if (fileSize > 10000) {
		return false;
	}
	
	readFile(fileName,buf,fileSize,0x80);
	for (int i = 0; i < fileSize-0x80; i++)
		textureData[i] = buf[i];
	return true;
}*/

//*(volatile unsigned int*)(pedAddr+0x4C)+0x688


/*
Idea for check:


*/

//tv prop with moving screen: -1211836083

/*
13E1208 sendDataFunction CHECK THAT BECAUSE THAT LOOKS LIKE IT MAY BE RECEIVING HELI DATA

https://alexguirre.github.io/jooat/
jenkins jooat online

*/

/*
anti host kick:
0x1358AAC = blr
lr = 0x138E670 so set that to nop

*/



/*
BLJS conversion:
Anything before 0xAB96C can stay the same
Anything between 0xAB96C and 0xEA7474, subtract 0x70 from the BLES version to get the BLJS version
Anything between 0xEA919C and 0x1315B28, subtract 0xA0
    not use this:  anything between 0x1318CB4 and END subtract 0xBC
    not use this: after 0x137B4EC, subtract 0x28
    not use this: after 0x137F504, subtract 0x1CC (doesn't last for long)
After 0x1412858, add 0x50

Dead zones (areas not calculated right, and need to be looked at or converted manually)
0xEA7474 to 0xEA919C
0x1315B28 to 0x1412858

//EA7694
sub_0xEA7474 checks 3 hashes in BLES but only 1 in BLJM

*/


/*
compile .o file
C:\usr\local\cell\host-win32\ppu\bin>ppu-lv2-c++.exe *.o c:\usr\local\cell\target\ppu\lib\*.a

*/

#ifdef fiber
#include <cell\fiber\ppu_fiber.h>
#include <cell/fiber/ppuUtilDefine.h>
#include <cassert>
#include <cell/fiber/ppuUtilRuntime.h>

static int fiber_entry_Hello(uint64_t arg)
{
    printf("Hello, fiber!\n");
 
    return 0;
}
 
void fiberRun()
{
 
 
    cellFiberPpuInitialize();
    CellFiberPpuScheduler* scheduler = (CellFiberPpuScheduler*)memalign(CELL_FIBER_PPU_SCHEDULER_ALIGN, CELL_FIBER_PPU_SCHEDULER_SIZE);
    CellFiberPpuSchedulerAttribute schedAttr;
    cellFiberPpuSchedulerAttributeInitialize(&schedAttr);
    schedAttr.debuggerSupport = true;
    cellFiberPpuInitializeScheduler(scheduler, &schedAttr);
    CellFiberPpu* fiberHello = (CellFiberPpu*)memalign(CELL_FIBER_PPU_ALIGN, CELL_FIBER_PPU_SIZE);
    void* fiberHelloStack = memalign(CELL_FIBER_PPU_STACK_ALIGN, 2048);
    CellFiberPpuAttribute attr;
    cellFiberPpuAttributeInitialize(&attr);
    strncpy(attr.name, "Sample Hello Fiber", CELL_FIBER_PPU_NAME_MAX_LENGTH);
    cellFiberPpuCreateFiber(scheduler, fiberHello, fiber_entry_Hello, 0ULL, 1, fiberHelloStack, 2048, &attr);
    cellFiberPpuRunFibers(scheduler);
    int status;
    cellFiberPpuJoinFiber(fiberHello, &status);
 
    //free(fiberHello);
    //free(fiberHelloStack);
}

#endif
