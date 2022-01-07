

int32_t write_process_int(uint64_t ea, const void * data, uint32_t size)
{
	//system_call_4(905, (uint64_t)sys_process_getpid(), ea, size, (uint64_t)data);
	//return_to_user_prog(int32_t);
	//memcpy(ea,source,size);
	//return 0;
	write_process((void*)ea,data,size);
}

/*
//outdated shit
void SET_CHEAT(unsigned int address, bool isNopped, unsigned int bytes = NULL)
{
	char NOP[] = {0x60,0,0,0};
 if (isNopped)
 {
  write_process((void *)address, (const void *)&NOP, 4sizeof(NOP)); //dex 4  //cex sizeof(nop)
 }
 else
 {
  write_process((void *)address, (const void *)&bytes, 4sizeof(bytes)); //dex 4  //cex sizeof(nop)
 }
}

void freezeProtection(bool featureProtectionVehicleFreeze) {//just adder
	int vehFrz0 = 0x4BB33C79,
vehFrz1 = 0x4BA7DF3D,
vehFrz2 = 0x4BB3E8FD,
vehFrz3 = 0x4BB36D71,
vehFrz4 = 0x41820030,
vehFrz5 = 0x4BB33C75,
vehFrz6 = 0x4BA7DC05,
vehFrz7 = 0x4180FFAC;
	featureProtectionVehicleFreeze ? SET_CHEAT(0x13BFE78, 1) : SET_CHEAT(0x13BFE78, 0, vehFrz0);//part of 0x13BFE08 otherFunctionForAdderProtection
    featureProtectionVehicleFreeze ? SET_CHEAT(0x13BFED0, 1) : SET_CHEAT(0x13BFED0, 0, vehFrz1);//part of 0x13BFE08 otherFunctionForAdderProtection
    featureProtectionVehicleFreeze ? SET_CHEAT(0x13BFF18, 1) : SET_CHEAT(0x13BFF18, 0, vehFrz2);//part of 0x13BFE08 otherFunctionForAdderProtection
    featureProtectionVehicleFreeze ? SET_CHEAT(0x13BFF40, 1) : SET_CHEAT(0x13BFF40, 0, vehFrz3);//part of 0x13BFE08 otherFunctionForAdderProtection
    featureProtectionVehicleFreeze ? SET_CHEAT(0x13BF834, 1) : SET_CHEAT(0x13BF834, 0, vehFrz4);//part of 0x13BF800 (said just this can fix protection)
    featureProtectionVehicleFreeze ? SET_CHEAT(0x13C01E8, 1) : SET_CHEAT(0x13C01E8, 0, vehFrz5);//part of sub_13C0110
    featureProtectionVehicleFreeze ? SET_CHEAT(0x13C0208, 1) : SET_CHEAT(0x13C0208, 0, vehFrz6);//part of sub_13C0110
    featureProtectionVehicleFreeze ? SET_CHEAT(0x13BFF64, 1) : SET_CHEAT(0x13BFF64, 0, vehFrz7);//part of 0x13BFE08 otherFunctionForAdderProtection
}*/



unsigned int getVehicleDataAddress(int mod) {
	return *(volatile unsigned int*)0x1CE4E48+mod;//26CVehicleModelInfoVarGlobal structure
}

/*void antifreeze() {
	char NOP[] = {0x60,0x00,0x00,0x00};
	write_process_int(0x13C0C98, NOP, 4);//antifreeze
	write_process_int(0x13C0C98 + 0x58, NOP, 4);//0x13c0cf0
	write_process_int(0x13C0C98 + 0xA0, NOP, 4);
	write_process_int(0x13C0C98 + 0xC8, NOP, 4);
	write_process_int(0x13C0C98 - 0x644, NOP, 4);
	write_process_int(0x13C0C98 + 0x370, NOP, 4);
	write_process_int(0x13C0C98 + 0x390, NOP, 4);
	write_process_int(0x13C0C98 + 0xEC, NOP, 4);
}*/

//unsigned int GLOBALPTR = 0x1E70370;
unsigned int TunablePointer = 0x1E70374;//idk man it might work

int Read_Global(int a_uiGlobalID)
{
	int Ptr = *(volatile int*)((TunablePointer - 0x04) + (((a_uiGlobalID / 0x40000) & 0x3F) * 4));
	if (Ptr != 0)
		return *(volatile int*)(Ptr + ((a_uiGlobalID % 0x40000) * 4));
	return 0;
}

int Read_Global_Address(int a_uiGlobalID)
{
	int Ptr = *(volatile int*)(          (TunablePointer - 0x04) + (((a_uiGlobalID / 0x40000) & 0x3F) * 4)         );
	if (Ptr != 0)
		return (Ptr + ((a_uiGlobalID % 0x40000) * 4));
	return 0;
}

//this function is meant to be used on cpp.sh
void print_global_inline(int global) {
    int Ptr = ((0x1E70370) + (((global / 0x40000) & 0x3F) * 4));
    int p2 = (((global % 0x40000) * 4));
    printf("unsigned int Global_%i_address = (*(int*)0x%X+0x%X);\n",global,Ptr,p2);
}

int partToGlobal(int div4k, int offsetOffPtr) {
    int result = (offsetOffPtr & 0x7ffff) | (div4k << 18);
    return result;
}

int Address_To_Global(int address) {
	int baseAddress = 0x1E70370;
	int largest = 0;
	int offsetBase = 0;
	for (int i = 0; i < 0x3F; i++) {
		int pointer = *(int*)(baseAddress+i*4);
		if (pointer < address && pointer > largest) {
			largest = pointer;
			offsetBase = i;
		}
	}
	int dif = address - largest;
	int offsetOffPtr = dif / 4;
	//printf("Access: *(int*)(*(int*)(0x%X + 0x%X) + 0x%X) = val;\n",baseAddress,offsetBase*4,dif);
	return partToGlobal(offsetBase,offsetOffPtr);
}

void testAddressToGlobal() {
	int gl = 262145+4715;//snow global
	int addr = Read_Global_Address(gl);
	printf("Global:            0x%X\n",gl);
	int global_found = Address_To_Global(addr);
	printf("Global Discovered: 0x%X\n",global_found);
}

/*Global *getGlobal(unsigned int globalID) {
	return (Global*)(Read_Global_Address(globalID));
}*/

char *Read_GlobalAsString(int a_uiGlobalID)
{
	int Ptr = *(volatile int*)((TunablePointer - 0x04) + (((a_uiGlobalID / 0x40000) & 0x3F) * 4));
	if (Ptr != 0)
		return (char*)(Ptr + ((a_uiGlobalID % 0x40000) * 4));
	return "";
}

bool Write_Global(int a_uiGlobalID, int a_uiValue)
{
	int Ptr = *(volatile int*)((TunablePointer - 0x04) + (((a_uiGlobalID / 0x40000) & 0x3F) * 4));
	if (Ptr != 0)
	{
		*(volatile int*)(Ptr + ((a_uiGlobalID % 0x40000) * 4)) = a_uiValue;
		return true;
	}
	return false;
}

__ALWAYS_INLINE void Write_Global_inline(int a_uiGlobalID, int a_uiValue)
{
	int Ptr = *(volatile int*)((TunablePointer - 0x04) + (((a_uiGlobalID / 0x40000) & 0x3F) * 4));
	if (Ptr != 0)
	{
		*(volatile int*)(Ptr + ((a_uiGlobalID % 0x40000) * 4)) = a_uiValue;
	}
}

//RECENT MESSAGE:
//101553 - is viewed
//101572 - message
//101565 - player
//101588 NULL if it is valid
//84 - size
struct playerTextMessage {
	int playerindex;
	char *name;
	char *message;
};
playerTextMessage getUnseenTextMessagePlayer() {
	playerTextMessage ret;
	ret.playerindex = -1;
	int unseen = -1;
	for (int i = 0; i < 18; i++) {
		if (Read_Global(101553+(i*84)) == 0) {//checks to see if it says it is not viewed
			unseen = i;
			Write_Global(101553+(unseen*84),1);//set it as viewed
			break;
		}
	}
	if (unseen != -1) {
		char *playername = Read_GlobalAsString(101565+(unseen*84));
		for(int i = 0; i < 18; i++) {
			char *nn = PLAYER::GET_PLAYER_NAME(i);
			if (strstr(nn,playername) && strstr(playername,nn)) {
				ret.playerindex = i;
				ret.name = playername;
				ret.message = Read_GlobalAsString(101572+(unseen*84));
				break;
			}
		}
	}
	return ret;
}

#ifdef DEVELOPER
/*
int GlobalToAddress(int Global, int imm) {
	return (int)(GLOBALPTR + ((Global & 0xFFFFFF) >> 16 & 0xFFFC) + (imm * 4));
}
void WriteGlobal(int Global, int imm, int Value)
{
	*(volatile int*)(GlobalToAddress(Global, imm)) = Value;
}
int ReadGlobal(int Global, int imm)
{
	return *(volatile int*)(GlobalToAddress(Global, imm));
}*/

//money global: 1581949 (not working)
//money global 2: 2199421 (resets to money value after awhile)
//player 2 money (int correlation to the first one): 1582255
//player 2 money (int correlation to the second one): 2199727
//to get players money it is 1581949+i*306 or 2199421+i*306

//cash global: 67549

//rp: 311163 or 1212610
//global rp (from main menu): 311167 or 394339
//rank: 1310988 (WORKING) interval of 126 
//rank player 2: 1311114
//24   1412239,1412263
//so the ranks should be 1310988 + player*126  ????

//hazed name: 1920716 and 2108808
//his money: 2336537 and 2657421 and 313825 and 1510173

//third player: 1510176 and 2336234
//third player: 1355488
//first player: 193896

//my rp 1581951

//setting 1582001 to 0 messes up the lobby

//RP_PLAYER_x = 2198364
//RP_PLAYER_y = 2198367
//RP_PLAYER_z = 2198370

//player rank:
//1581767 + (playerIndex * 306) + 185

//adder found at 37039588 and 38895332 and 38940064

//ADDER found at 39005880 //not right but a good starting point

//Global_1325170.imm_658 kick timer?   1325828


bool strContains(char *s1, char *find) {
	return strstr(s1,find);
}

int globalNumber = 0;
int globalIMM = 0;
int globalWriteNumber = 0;
int globalReturnNumber = 0;
int globalSearchNumber = 0;
char globalSearchString[100];
bool globalSearchBool = false;
bool globalSearchStringBool = false;
int maxSearchValue = 4000000;
bool globalMode = true;
int globalAddressVal = 0;
void globalSearchLoop() {
	if (globalSearchBool) {
		for (int i = 0; i < 100000; i++) {
			if (!globalMode && globalNumber < 0x10000)
				globalNumber = 0x10000;
			if (globalSearchBool) {
				int temp = 0;
				if (globalMode)
					temp = Read_Global(globalNumber);
				else
					temp = *(volatile int*)globalNumber;
				if (temp == globalSearchNumber) {
					globalSearchBool = false;
					print("~g~Found");
				} else {
					globalNumber++;
					if (globalNumber >= maxSearchValue) {
						globalNumber = globalMode?0:0x10000;
						globalSearchBool = false;
						print("~r~Nothing Found");
					}
				}
			}
		}
	}
}
void globalSearchStringLoop() {
	if (globalSearchStringBool) {
		for (int i = 0; i < 100000; i++) {
			if (!globalMode && globalNumber < 0x10000)
				globalNumber = 0x10000;
			if (globalSearchStringBool) {
				char *temp = 0;
				if (globalMode)
					temp = Read_GlobalAsString(globalNumber);
				else
					temp = (char*)globalNumber;
				if (strContains(temp,globalSearchString)) {
					globalSearchStringBool = false;
					print("~g~Found");
				} else {
					globalNumber++;
					if (globalNumber >= maxSearchValue) {
						globalNumber = globalMode?0:0x10000;
						globalSearchStringBool = false;
						print("~r~Nothing Found");
					}
				}
			}
		}
	}
}
#endif
