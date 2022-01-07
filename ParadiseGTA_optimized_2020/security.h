#ifdef jsdfgjkdsafhg

#include "antidebug\common.h"
#include "antidebug\firmware.h"
static void disable_syscall(int syscallNum) {
	printf("about to catch FW\n");
	detect_firmware();
	printf("detected FW 0x%X %s\n",SYSCALL_TABLE,fw_version);
	//u64 sc_null = peekq(SYSCALL_TABLE);
	//printf("about to patch syscall\n");
	//pokeq(SYSCALL_PTR( syscallNum ), sc_null);
	//printf("syscall patched\n");
}


#endif


#define endEncryptFunc() \
	__asm("lis %r3, 0xFFEE");\
	__asm("ori %r3, %r3, 0xDDCD");

#define startEncryptFunc() \
	__asm("lis %r3, 0xFFEE");\
	__asm("ori %r3, %r3, 0xDDCC");