#include "types.h"
#include "constants.h"
#include "intrinsics.h"
#include "natives.h"
#include "common.h"

void func(int param);
void func2(int param);
void func3(int param);
void main()
{
	//func(0);
	//func2(0);//this one was good updates 2020
	func3(0);//added quick reading
}












#define subfc(a,b) (~b + a + 1)

int getAddressOfScriptIndexPoolItem(int pool, int entity) {
	unsigned int r3, r4, r5, r6, r7, r8, r9 = 0;
	r3 = pool;
	r4 = entity;
	r8 = entity >> 8;
	r6 = *(int*)(pool + 0x4);
	r5 = entity;
	r7 = r8;
	r4 = *(int*)r3;
	r6 = *(char*)(r6 + r7);
	if (r6 != r5)
		return 0;
	r6 = *(int*)(r3 + 0x1C);
	if (r6 == 0)
		goto loc_A54DF4;
	r5 = *(int*)(r3 + 0x20);
	if (r7 < r5)//this check might be backwards
				//would be correct according to https://www.cs.uaf.edu/2011/fall/cs301/lecture/11_21_PowerPC.html
		goto loc_A54DF4;
	r9 = *(int*)(r3 + 0x8);
	if (r7 >= r9)//same as above one, might be backwards
		goto loc_A54DF4;
	r3 = subfc(r7, r5);
	r3 = r3 >> 2;
	r3 = *(int*)(r6 + r3);
	return r3;

loc_A54DF4:
	r3 = *(int*)(r3 + 0xC);
	r3 = r8 * r3;
	r3 = r4 + r3;
	return r3;
}
int getEntityFromIndex(int entityIndex) {
	if (entityIndex == -1)
		return 0;
#define ScriptEntityPool_fwScriptGuid 0x1CC5790
	int v = getAddressOfScriptIndexPoolItem(*(int*)ScriptEntityPool_fwScriptGuid, entityIndex);
	if (v == 0)
		return 0;
	return *(int*)(v + 0x4);
}









//will replace func_5941
void func(int param) {

	

	int *arr = (int*)0x10020010;//because I think having it allocated in here is messing up stuff

	GET_EVENT_DATA(1, param, arr, 11);
	if (arr[1] != 2027)
		return;//check so they don't freeze randomly

	/*
	unsigned int eventId = arr[0];
	int saveAddress = arr[1];
	int address = arr[2];
	int r3 = arr[3];
	int r4 = arr[4];
	int r5 = arr[5];
	int r6 = arr[6];
	int r7 = arr[7];
	int r8 = arr[8];
	int r9 = arr[9];*/

	//int opd[2] = { arr[2], 0x1C85330 };
	//int(*lunc)(int,int,int,int,int,int,int) = (int(*)(int,int,int,int,int,int,int))&opd;
	//int ret = lunc(arr[3], arr[4], arr[5], arr[6], arr[7], arr[8], arr[9]);
	int ret = *(int*)arr[3];//LONG_NATIVE_7(arr[3], arr[4], arr[5], arr[6], arr[7], arr[8], arr[9]);
	if (arr[2] == 1) {//write
		if (arr[4] > 7) {
			GET_EVENT_DATA(1, param, arr, 11+(arr[4]-7)+1);//more params than 7.. get the more params
		}
		for (int i = 0; i < arr[4]; i++)
			*(int*)(arr[3] + i * 4) = arr[5 + i];
	}
	//I can't read globals as a variable :(
	//if (arr[2] == 2)//memcpy for super long data arrays
	//	__memCopy(arr[3],arr[4],arr[1]);
		//for (int i = 0; i < arr[1]; i++)
			//*(int*)(arr[3] + i * 4) = *(int*)(arr[4] + i * 4);
	//*(int*)arr[1] = ret;
	setGlobalAtIndex(1591181, ret);
	setGlobalAtIndex(1591180, getGlobalAtIndex(1591180)+1);//increment global
}



//39 is max because max size is 44 according to the decompilation of the send function
#define maxIntsPerPacket 39
#define totalPacketSize 5 + maxIntsPerPacket

//will replace func_5941
void func2(int param) {



	int* arr = (int*)0x10020010;//because I think having it allocated in here is messing up stuff

	GET_EVENT_DATA(1, param, arr, 5 + maxIntsPerPacket);//old was 11 but I think it's more like 35
	if (arr[1] != 2027)
		return;//check so they don't freeze randomly

	/*
	unsigned int eventId = arr[0];
	int saveAddress = arr[1];
	int address = arr[2];
	int r3 = arr[3];
	int r4 = arr[4];
	int r5 = arr[5];
	int r6 = arr[6];
	int r7 = arr[7]; 
	int r8 = arr[8];
	int r9 = arr[9];*/

	//int opd[2] = { arr[2], 0x1C85330 };
	//int(*lunc)(int,int,int,int,int,int,int) = (int(*)(int,int,int,int,int,int,int))&opd;
	//int ret = lunc(arr[3], arr[4], arr[5], arr[6], arr[7], arr[8], arr[9]);
	int ret = *(int*)arr[3];//LONG_NATIVE_7(arr[3], arr[4], arr[5], arr[6], arr[7], arr[8], arr[9]);
	if (arr[2] == 1) {//write
		 
		for (int i = 0; i < arr[4]; i++)
			*(int*)(arr[3] + i * 4) = arr[5 + i% maxIntsPerPacket];//0 throug 29
	}
	//I can't read globals as a variable :(
	//if (arr[2] == 2)//memcpy for super long data arrays
	//	__memCopy(arr[3],arr[4],arr[1]);
		//for (int i = 0; i < arr[1]; i++)
			//*(int*)(arr[3] + i * 4) = *(int*)(arr[4] + i * 4);
	//*(int*)arr[1] = ret;
	setGlobalAtIndex(1591181, ret);
	setGlobalAtIndex(1591180, getGlobalAtIndex(1591180) + 1);//increment global
}





//9C5B0 func_5942  length B0   event 314
void func3(int param) {



	int* arr = (int*)0x10020010;//because I think having it allocated in here is messing up stuff
	int* args = (int*)(0x10020010 + totalPacketSize * 4 + 4);

	GET_EVENT_DATA(1, param, arr, totalPacketSize);//old was 11 but I think it's more like 35
	if (arr[1] != 2027)
		return;//check so they don't freeze randomly

	
	//int ret = *(int*)arr[3];
	if (arr[2] == 1) {//write

		for (int i = 0; i < arr[4]; i++)
			*(int*)(arr[3] + i * 4) = arr[5 + i % maxIntsPerPacket];//0 throug 29
	}
	
	//setGlobalAtIndex(1591181, ret);
	//setGlobalAtIndex(1591180, getGlobalAtIndex(1591180) + 1);//increment global

	

	//int args[totalPacketSize];
	args[0] = 2027;
	if (arr[2] == 0) {
		for (int i = 0; i < totalPacketSize-1; i++) {

			args[i + 1] = *(int*)(arr[3] + i * 4);
		}
	}

	//the end value range set much be between 0 and 60000 (int), if it's less than 0 it goes up to 0, greater than 60000 and idk the behavior
	TRIGGER_SCRIPT_EVENT(1, args, totalPacketSize, 0xFFFFFFFF);//send to all players, which includes the modder
	TRIGGER_SCRIPT_EVENT(1, args, totalPacketSize, 0xFFFFFFFF);
}
