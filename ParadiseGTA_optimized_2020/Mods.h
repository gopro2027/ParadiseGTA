//these funcs are redefines in security.h so I can share with printf.cpp
#include "security.h"
/*__ALWAYS_INLINE __attribute__ ((naked)) void endEncrptFunc() {
	__asm("lis %r3, 0xFFEE");//3C 60 FF EE 
	__asm("ori %r3, %r3, 0xDDCD");//60 63 DD CC 
	//__asm("blr");//4E 80 00 20 
	//total: 3C 60 FF EE 60 63 DD CD
	//(byte)0x3C(byte)0x60(byte)0xFF(byte)0xEE(byte)0x60(byte)0x63(byte)0xDD(byte)0xCD(byte)0x4E(byte)0x80(byte)0x00(byte)0x20
}

__ALWAYS_INLINE __attribute__ ((naked)) void startEncrptFunc() {
	__asm("lis %r3, 0xFFEE");//3C 60 FF EE 
	__asm("ori %r3, %r3, 0xDDCC");//60 63 DD CC 
	//__asm("blr");//4E 80 00 20 
	//total: 3C 60 FF EE 60 63 DD CC
	//(byte)0x3C(byte)0x60(byte)0xFF(byte)0xEE(byte)0x60(byte)0x63(byte)0xDD(byte)0xCD(byte)0x4E(byte)0x80(byte)0x00(byte)0x20
}
*/
void startSessionKickOnPlayer(int player);
float drawText(char * text, int font, float x, float y, float scalex, float scaley, int r, int g, int b, int a, bool center, bool computeTextWidth = false, bool rightAlign = false);
unsigned int getCVehicleModelInfo(unsigned int hash);
bool modifiedPlayerEbootsArray[18];
//int modifiedPlayerEbootsSizeArray[18];
char *getPlayerRealNameFromIndex(int player) {
	CNetGamePlayer *p = getCNetGamePlayer(player);
	if (VALID_ADDR(p)) {
		CPlayerInfo *info = p->playerInfo;
		if (VALID_ADDR(info)) {
			return info->name;
		}
	}
	return 0;
}

//this caused it to be like copied to an unencrypted area
//namespace moreMods{
//	__ALWAYS_INLINE void setNPTypeLoop();
//}

#define encryptFunctionStart(functionAddress) {}
#define encryptFunctionEnd() {}
#define encryptFunctionEnd_deletedata() {}

#define encryptFunctionStart_quick(functionAddress,bufferSize) {}
#define encryptFunctionEnd_quick() {}

#define inline_encryptFunctionStart(functionAddress) {}
#define inline_encryptFunctionEnd() {}



#pragma region top misc stuff

int getHostOfFreemodeScript() {
	//encryptFunctionStart(getHostOfFreemodeScript);
	char freemode[] = {0x3D, 0x29, 0x3E, 0x3E, 0x36, 0x34, 0x3F, 0x3E, 0x5B};//"freemode"
	for (int i = 0; i < sizeof(freemode); i++)
		freemode[i] ^= 0x5b;
	int ret = NETWORK::NETWORK_GET_HOST_OF_SCRIPT(freemode, -1, 0);
	//encryptFunctionEnd();
	return ret;
}

GtaThread *freemodeScriptGtaThread = 0;
CGameScriptHandlerNetwork *freemodeScriptCGameScriptHandlerNetwork = 0;
//char adminMessageText[400];
//__attribute__((noinline)) void sendRockstarMessageEvent(char *player, char *text, bool wholeLobby);
//void sendRockstarMessageEvent(int player, char *text);//does an extra check on name
opd_s gppbi = {0x0047DFA0,TOC};
unsigned int(*getPlayerPedByIndex)(int player) = (unsigned int(*)(int))&gppbi;
int playerModderData[18];
float getVehicleSuspension(unsigned int entity);
void detachEntityViaPoolFunctions(unsigned int entity);
void setVehicleSuspension(unsigned int entity, float height);
void setVehicleGravity(unsigned int entity, float gravity);
char *ItoSH(int num);
void nullFunc(int i) {};
char *getPlayerRealName(int player) {
	/*__asm("lis %r3, 0xFFEE");//3C 60 FF EE 
	__asm("ori %r3, %r3, 0xDDCC");//60 63 DD CC 
	__asm("blr");//4E 80 00 20 
	//total: 3C 60 FF EE 60 63 DD CC 4E 80 00 20 
	//(byte)0x3C(byte)0x60(byte)0xFF(byte)0xEE(byte)0x60(byte)0x63(byte)0xDD(byte)0xCC(byte)0x4E(byte)0x80(byte)0x00(byte)0x20

	*/
	
	CNetGamePlayer *netgameplayer = getCNetGamePlayer(player);
	if (VALID_ADDR(netgameplayer)) {
		return netgameplayer->playerInfo->name;
	}
	return 0;
}
namespace poolManipulations {
	void invisibleAllEntities(int entityToInvisibleFromIndex);
	void detachAllEntities(int entityToDetachFromIndex);
};
char toLower(char c) {
		if (c<='Z'&&c>='A')
			c = c-('A'-'a');
		return c;
	}

	void toLower(char *str) {
		int len = strlen(str);
		for (int i = 0; i < len; i++) {
			str[i] = toLower(str[i]);
		}
	}
/*
extortion render text: 0x2066FCC
*/
//create another one for vehicles
int getPedsNearPed(int ped, int *saveArray, int saveArraySize) {
	if (saveArraySize > 100)
		saveArraySize = 100;
	int data[100+1];
	data[0] = saveArraySize;
	int size = PED::GET_PED_NEARBY_PEDS(ped,data,73284658);
	int maxSize = size;
	if (maxSize > saveArraySize)
		maxSize = saveArraySize;
	for (int i = 0; i < maxSize; i++) {
		saveArray[i] = data[i+1];
	}
	return maxSize;
}
int getVehiclesNearPed(int ped, int *saveArray, int saveArraySize) {
	if (saveArraySize > 100)
		saveArraySize = 100;
	int data[100+1];
	data[0] = saveArraySize;
	int size = PED::GET_PED_NEARBY_VEHICLES(ped,data);
	int maxSize = size;
	if (maxSize > saveArraySize)
		maxSize = saveArraySize;
	for (int i = 0; i < maxSize; i++) {
		saveArray[i] = data[i+1];
	}
	return maxSize;
}
int getEntitiesNearPed(int ped, int *saveArray, int saveArraySize) {
	if (saveArraySize > 100)
		saveArraySize = 100;
	int saveArraySizePed = saveArraySize/2;
	int saveArraySizeVehicle = saveArraySize/2;
	int pedArray[50];
	int vehArray[50];
	int pedCount = getPedsNearPed(ped,pedArray,saveArraySizePed);
	int vehCount = getVehiclesNearPed(ped,vehArray,saveArraySizeVehicle);
	int total = 0;
	for (int i = 0; i < pedCount; i++) {
		saveArray[total] = pedArray[i];
		total++;
	}
	for (int i = 0; i < vehCount; i++) {
		saveArray[total] = vehArray[i];
		total++;
	}
	return total;
}

opd_s GET_PED_LAST_WEAPON_IMPACT_COORD_t = { 0x468F40, TOC };
int(*GET_PED_LAST_WEAPON_IMPACT_COORD)(int PedID, float* Coords) = (int(*)(int, float*))&GET_PED_LAST_WEAPON_IMPACT_COORD_t;
bool getBulletEndPosition(Vector3 *save) {
	float Loc[3];
	if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID())) {
		if (GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), Loc)) {
			save->x = Loc[0];
			save->y = Loc[1];
			save->z = Loc[2];
			return true;
		}
	}
	return false;
}
void setEntityMigrateable(int entity, bool migrateable) {
	NETWORK::SET_NETWORK_ID_CAN_MIGRATE(NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity),migrateable);
}
int getPlayerIndexFromNetworkData(unsigned int networkDataAddress) {
	unsigned int p1 = *(volatile int*)(networkDataAddress+0x8);
	if (p1 > 0x10000) {
		return *(volatile int*)(p1+0x8);
	}
	return -1;
}
void WriteMemory(int Address, int range, ...) {
	va_list ap;
	va_start(ap, range);
	for(int i=0; i<range; i++)
		*(unsigned char*) (Address + i) = va_arg(ap, char);
	va_end(ap);
}
void WriteMemory_char(int Address, int range, unsigned char Offset){
	*(unsigned char*)(Address + range) = Offset;
}
void print(char *text);
#include "Stats.h"

namespace PlayerMods {


	namespace networkManager {




/*
0x54E79E9C
0xF633805A


int func_372(var uParam0, var uParam1, bool bParam2, var uParam3, bool bParam4, var uParam5, bool bParam6, bool bParam7)
{
	int iVar0;
	char[64] cVar1;
	int iVar2;
	int iVar3;
	
	iVar0 = -1;
	if (unk_0xE66A0B40(player_id(), uParam1) || uParam3)
	{
		if (!bParam2)
		{
			StringCopy(&cVar1, get_player_name(uParam1), 64);
		}
		else
		{
			StringCopy(&cVar1, get_player_name(uParam1), 64);
		}
		unk_0x574EE85C(uParam0);
		unk_0x6F1A1901(func_380(uParam1, -2, 1, 0));
		unk_0x27A244D8(func_378(&cVar1));
		if (!bParam4)
		{
			iVar0 = unk_0x08F7AF78(0, 1);
		}
		else
		{
			Global_2410499 = {func_88(uParam1)};
			if (network_clan_player_get_desc(&Global_2410429, 35, &Global_2410499))
			{
				iVar2 = 0;
				if (are_strings_equal(&Global_2410429.imm_22, "Leader") && Global_2410429.imm_30 == 0)
				{
					iVar2 = 1;
				}
				if (Global_2410429.imm_21 > 0)
				{
					iVar3 = 0;
				}
				else
				{
					iVar3 = 1;
				}
				if (bParam6)
				{
					if (bParam7)
					{
						cVar1 = {func_377(&cVar1)};
					}
					iVar0 = unk_0x88B9B909(iVar3, unk_0x54E79E9C(&Global_2410429, 35), &Global_2410429.imm_17, Global_2410429.imm_30, iVar2, 0, Global_2410429, &cVar1, Global_1316031, Global_1316032, Global_1316033);
				}
				else
				{
					iVar0 = unk_0xA9CCEF66(iVar3, unk_0x54E79E9C(&Global_2410429, 35), &Global_2410429.imm_17, Global_2410429.imm_30, iVar2, 0, Global_2410429, Global_1316031, Global_1316032, Global_1316033);
				}
			}
			else
			{
				iVar0 = unk_0x08F7AF78(0, 1);
			}
		}
		func_373(14, uParam0, 1, &cVar1, 0, 0, 0, 0, 1, 0, 0, 0);
	}
	return iVar0;
}


*/
		networkHandleMgr netHandle; 
		networkClanMgr clan;
		int msg(Player player, char *text) {
			
			char *playerName = PLAYER::GET_PLAYER_NAME(player);
			UI::_0x574EE85C("STRING");//_SET_NOTIFICATION_TEXT_ENTRY("STRING");
			UI::_0x6F1A1901(0);//_SET_NOTIFACTION_COLOR_NEXT(1);
			UI::_ADD_TEXT_COMPONENT_STRING(text);//ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(playerName);
			printf("o1\n");
			NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, &netHandle, 13);
			printf("o2\n");
			if (NETWORK::NETWORK_CLAN_PLAYER_IS_ACTIVE(&netHandle)) {
				printf("o3\n");
				NETWORK::NETWORK_CLAN_PLAYER_GET_DESC(&clan, 35, &netHandle);
				printf("o4\n");
				printf("Clan: 0x%X NetHandle: 0x%X\n",(unsigned int)&clan,(unsigned int)&netHandle);
				int iVar2 = 0;
				int iVar3 = 0;
				//if ((unsigned int)clan.crewRole > 0x10000)
				if (GAMEPLAY::ARE_STRINGS_EQUAL(clan.crewRole, "Leader") && clan.isLeader == 0)
					iVar2 = 1;
				if (clan.isCrewActive > 0)
					iVar3 = 0;
				else
					iVar3 = 1;
				printf("o5\n");
				UI::_0x88B9B909(0, NETWORK::_0x54E79E9C(&clan, 35), &clan.unk17, clan.isLeader,iVar2, 0, clan,"Paradise SPRX", 0, 255, 255);
				printf("o6\n");
			}
			printf("o7\n");
			return 0;
		}
	};//end of namespace

void msg(char *text, int player, bool dontCheckMyName = false);
}

float *vector3ToFloatArray(Vector3 vec) {
	float ret[3];
	ret[0] = vec.x;
	ret[1] = vec.y;
	ret[2] = vec.z;
}

void WriteTunable(int Index, int Value)
{
	*(volatile int*)(*(volatile unsigned int*)0x1E80774 + (Index * 0x04)) = Value;//maybe it still works? hopefully?
}
void APPLY_FORCE(int Entity, Vector3 Force, Vector3 Position, int type = 1, bool relative = true) {
		//float Forc[] = {Force.x,Force.y,Force.z};
		//float Positio[] = {Position.x,Position.y,Position.z};
		ENTITY::APPLY_FORCE_TO_ENTITY(Entity, type, Force.x,Force.y,Force.z, Position.x,Position.y,Position.z, 0, relative, 1, 1, 0, 1);
	}
	void forceEntity(int entity, float x, float y, float z, float rotx, float roty, float rotz, int type = 1) {
		Vector3 force = {x,y,z};
		Vector3 rot = {rotz,roty,rotz};
		APPLY_FORCE(entity,force,rot,type);
	}

void APPLY_FORCE_NONREL(int Entity, Vector3 Force, Vector3 Position, int type = 1) {
		//float Forc[] = {Force.x,Force.y,Force.z};
		//float Positio[] = {Position.x,Position.y,Position.z};
		ENTITY::APPLY_FORCE_TO_ENTITY(Entity, type, Force.x,Force.y,Force.z, Position.x,Position.y,Position.z, 0, 0, 1, 1, 0, 1);
	}
	void forceEntityNonRel(int entity, float x, float y, float z, float rotx, float roty, float rotz, int type = 1) {
		Vector3 force = {x,y,z};
		Vector3 rot = {rotz,roty,rotz};
		APPLY_FORCE_NONREL(entity,force,rot,type);
	}
struct MyObject {
	char *prop;
	int bone;
	Vector3 pos;
	Vector3 rot;
	MyObject() {
		bone = 0;
		pos.x = 0;
		pos.y = 0;
		pos.z = 0;
		rot.x = 0;
		rot.y = 0;
		rot.z = 0;
	}
};
#pragma endregion



#define spoofNPTypeVal_ptr ((char*)0x192EBF3)
unsigned int spoofNPTypeVal_key = 0x4D212A94;
#define spoofNPTypeVal_safe *(char*)(0x4CB3C167^spoofNPTypeVal_key)
__ALWAYS_INLINE void setNPTypeLoop() {
	//finding 63 FF 60 00 93 FE 00 18  3C 60 EC 23 60 63 CE 89 in IDA
	if (spoofNPTypeVal_safe == 1) {
		//EU
		*(volatile unsigned int*)(0x0223EF00+0x18) = 0x028AD000;
		*(volatile unsigned int*)0x138B3F8 = 0x3B003860;//li %r24, 0x3860
		*(volatile unsigned int*)(0x0223EF00+0x1C) = 0xB749A43B;
		*(volatile unsigned int*)(0x0223EF00+0x28) = 0x8706EF58;
		*(unsigned char*)(0x0223EF00+0x14) = 0x0;

		int EUValues[] = {0x4A6E1F29, 0x000001A9, 0x50624EC2, 0x000001D0, 0x00000000, 0x00000000, 0x028AD000, 0xB749A43B, 0x59B962CD, 0x00000000, 0x8706EF58};

		memcpy((void*)0x0223EF00,(void*)EUValues,sizeof(EUValues));

		spoofNPTypeVal_safe = 0;
	}
	else if (spoofNPTypeVal_safe == 2) {
		//JP
		*(volatile unsigned int*)(0x0223EF00+0x18) = 0x028A6000;
		*(volatile unsigned int*)(0x0223EF00+0x1C) = 0xEC23CE89;
		*(volatile unsigned int*)0x138B3F8 = 0x3B003879;//li %r24, 0x3879
		*(volatile unsigned int*)(0x0223EF00+0x28) = 0x3618AB6C;
		*(unsigned char*)(0x0223EF00+0x14) = 0x1;//from func storer4intostructofsize0x2C you can see this change

		int JPValues[] = {0x4A6E1F29, 0x000001A9, 0x50624EC2, 0x000001D0, 0x00000000, 0x01000000, 0x028A6000, 0xEC23CE89, 0x59B962CD, 0x00000000, 0x3618AB6C};

		memcpy((void*)0x0223EF00,(void*)JPValues,sizeof(JPValues));

		spoofNPTypeVal_safe = 0;
	}
}



#pragma region drawing
float getTextWidth(char * text, int font, float scalex, float scaley);
bool isEqual(char *s1, char *s2);
namespace drawing {

	bool overriteImage(char *dictionary, char *name, char *fileName, unsigned int pixelSize = 32) {
		opd_s getTextureAddress_t = {0x3C083C,TOC};
		unsigned int (*getTextureAddress)(char *dict, char *name) = (unsigned int(*)(char*,char*))&getTextureAddress_t;
		unsigned int address = getTextureAddress(dictionary,name);
		if (address < 0x10000) {
			//printf("Count not find texture address!\n");
			return false;
		}
		char *textureData = (char*)(*(volatile unsigned int*)(address + 0x1c)+0xC0000000);
		char *textureName = (char*)(*(volatile unsigned int*)(address + 0x20));
		if (strcmp(textureName,"none") == 0) {
			//printf("Texture name is 'none'\n");
			return false;
		}
		unsigned int addAmount = 0x80;
		if (textureData[0] == 'D' && textureData[1] == 'D' && textureData[2] == 'S') {
			//printf("Texture data starts with 'DDS'\n");
			//addAmount = 0;
			textureData+=0x80;
		}

		/*char buf[10000];//image buffer size
		unsigned int fileSize = getFileSize(fileName);
		if (fileSize > 10000) {
			printf("Image too large! %i bytes over the max size!\n",(fileSize-10000));
			return false;
		}*/
		//printf("Texture address: 0x%X\nTexture data: 0x%X\nTexture Name: %s\n",address,(unsigned int)textureData,textureName);
		//return true;//say it overritten but it aint
		return injectDDS(fileName,pixelSize,textureData,addAmount);
		/*readFile(fileName,buf,fileSize);//0x80 cuz that's the offset
		for (int i = 0; i < fileSize-addAmount; i++)
			textureData[i] = buf[i+addAmount];*/
		//printf("Texture overritten!\n");
		//return true;
	}

	bool overriteImageFromFile(char *dictionary, char *name, char *fileName, unsigned int pixelSize = 32) {
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
		unsigned int addAmount = 0x80;
		if (textureData[0] == 'D' && textureData[1] == 'D' && textureData[2] == 'S') {
			textureData+=0x80;//the data in memory includes header
		}
		return injectDDSFile(fileName,pixelSize,textureData,addAmount);
	}

	void DrawShader(float x1, float y1, float Width, float Height, int r, int g, int b, int a)
	{
		GRAPHICS::DRAW_RECT(x1, y1, Width, Height, r, g, b, a);
	}

	void DrawText(char *text, int font, float x, float y, float scaleX, float scaleY, int r, int g, int b, int a, bool centered,bool background = false, bool right = false)
	{
		y = y - 0.005f;
		if (strlen(text) >= 1 && background) {
			float width = getTextWidth(text,font,scaleX,scaleY);
			drawing::DrawShader(x+(width/2),y+0.0175f/*just gotta assume it is this size*/,width,0.035f,0,0,0,100);
		}

		UI::SET_TEXT_FONT(font);
		UI::SET_TEXT_SCALE(scaleX, scaleY);
		UI::SET_TEXT_COLOUR(r, g, b, a);
		UI::SET_TEXT_WRAP(0.0f, 1.0f);
		UI::SET_TEXT_CENTRE(centered);
		UI::SET_TEXT_RIGHT_JUSTIFY(right);
		if (right)
			UI::SET_TEXT_WRAP(0.0f, x);
		//if (background == true) {
			//UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
			//UI::SET_TEXT_OUTLINE();
		//}
		UI::_SET_TEXT_ENTRY("STRING");
		//UI::_SET_TEXT_GXT_ENTRY("STRING");
		//UI::_SET_TEXT_COMPONENT_FORMAT("STRING");//UI::_SET_TEXT_COMPONENT_FORMAT
		//UI::_ADD_TEXT_COMPONENT_ITEM_STRING(text);//add text component item string
		UI::_ADD_TEXT_COMPONENT_STRING(text);
		UI::_DRAW_TEXT(x, y);
	}

	void DrawFloat(float number, int font, float x, float y, float scaleX, float scaleY, int r, int g, int b, int a, bool centered, int decimalPlaces,bool background = false)
	{
		UI::SET_TEXT_FONT(font);
		UI::SET_TEXT_SCALE(scaleX, scaleY);
		UI::SET_TEXT_COLOUR(r, g, b, a);
		UI::SET_TEXT_WRAP(0.0f, 1.0f);
		UI::SET_TEXT_CENTRE(centered);
		if (background == true) {
			UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
			UI::SET_TEXT_OUTLINE();
		}
		UI::_SET_TEXT_ENTRY("NUMBER");
		UI::ADD_TEXT_COMPONENT_FLOAT(number,decimalPlaces);
		UI::_DRAW_TEXT(x, y);

	}

	void DrawSprite(char * textureDict, char * textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
	{
        GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(textureDict, false);
        if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(textureDict)) {
			GRAPHICS::DRAW_SPRITE(textureDict, textureName, x, y, width, height, rotation, r, g, b, a);
		}
	}

	void DrawSprite(char * textureDict, char * textureName, float x, float y, float width, float height, float rotation, Vector3 color, int a)
	{
		DrawSprite(textureDict, textureName, x, y, width, height, rotation, color.x,color.y,color.z, a);
	}


	opd_s getTextureAddress_t = {0x3C083C,TOC};
	unsigned int(*getTextureAddress)(char *texturedict, char *texturename) = (unsigned int(*)(char*,char*))&getTextureAddress_t;

	void spoofTextureAddress(unsigned int textureaddressoriginal, unsigned int textureaddressnew) {
		unsigned int id = *(volatile unsigned int*)(textureaddressoriginal+0x30);
		id = id<<2;//shift it
		*(volatile unsigned int*)(0x1F28980+id) = textureaddressnew;
	}


	struct hasTextureAddressInHere {
		unsigned int textureaddress;
	};


#ifdef oldshit
	struct SPRITE {
		hasTextureAddressInHere *textureaddress;
		char data[0x44];
	};
	
	void renderSprite(SPRITE *sprite) {
		opd_s render_t = {0x477428,TOC};
		void (*render)(unsigned int spriteaddress, unsigned int r4, unsigned int r5) = (void(*)(unsigned int,unsigned int,unsigned int))&render_t;
		render((unsigned int)&sprite,1,4/*or 8*/);
	}

	void DRAW_RECT_IMMEDIATELY(float posX, float posY, float scaleX, float scaleY, int R, int G, int B, int A) {
		//patch draw_rect to use my own address
		//function to patch: 0x477FD8
		//code to make it say:
		//li r3, 0
		//lis r3, 0x1002
		//blr
		//data: 3C 60 10 02 4E 80 00 20
		unsigned int patch0 = 0x38600000;
		unsigned int patch1 = 0x3c601002;
		unsigned int patch2 = 0x4e800020;
		unsigned int unpatch0 = *(volatile unsigned int*)(0x477FD8+0x0);
		unsigned int unpatch1 = *(volatile unsigned int*)(0x477FD8+0x4);
		unsigned int unpatch2 = *(volatile unsigned int*)(0x477FD8+0x8);
		*(volatile unsigned int*)(0x477FD8+0x0) = patch0;
		*(volatile unsigned int*)(0x477FD8+0x4) = patch1;
		*(volatile unsigned int*)(0x477FD8+0x8) = patch2;
		SPRITE *sprite = (SPRITE*)0x10020000;//also used in the other shit
		GRAPHICS::DRAW_RECT(posX, posY, scaleX, scaleY, R, G, B, A);
		*(volatile unsigned int*)(0x477FD8+0x0) = unpatch0;
		*(volatile unsigned int*)(0x477FD8+0x4) = unpatch1;
		*(volatile unsigned int*)(0x477FD8+0x8) = unpatch2;
		//render now
		//printf("Sprite address: 0x%X\n",(unsigned int)sprite);
		if ((unsigned int)sprite > 0x10000)
			renderSprite(sprite);
	}
#endif



	/*
	
	53454141 0D0FFFFF

0x387ABA80

//getTextureDictID... goes something like this
sub_151081C (unsigned int listofthem = 0x1EC1DA4, unsigned int hashOfTextureDict) {
	struct value {unsigned int hash,unsigned int index};
	value *array = (value*)(*(volatile unsigned int*)(listofthem+0x60));
	value *found = array[0];
	int i = 0;
	while (found->hash != hashOfTextureDict) {
		found = &(array[++i]);
	}
	return ((found->index&0xFFFF0000)>>16);
}

opd_s getTextureAddress_t = {0x3C083C,TOC};
unsigned int(*getTextureAddress)(char *texturedict, char *texturename) = (unsigned int(*)(char*,char*))&getTextureAddress_t;

void changeTextureAddress(unsigned int textureaddressoriginal, unsigned int textureaddressnew) {
	unsigned int id = *(volatile unsigned int*)(textureeaddressoriginal+0x30);
	id = id<<2;//shift it
	*(volatile unsigned int*)(0x1F28980+id) = textureaddressnew;
}

textureaddress+0x10 short is the width
textureaddress+0x12 short is the height
textureaddress+0x20 is a pointer to the names of the items in the texture dictionary
textureaddress+0x4*13 might be interesting... unsure
textureaddress is of size 0x40

struct hasTextureAddressInHere {
	unsigned int textureaddress;
};
struct SPRITE {
	hasTextureAddressInHere *textureaddress;
	char data[0x44];
};

//this is the thing that is a size of 0x48
//typedef unsigned int RENDERABLESPRITE

SPRITE getNextOpenAddressToRenderAt() {
	unsigned int r3fortheactualfunction = (0x1DE8F28+ ( ( *(volatile int*)( 0x1EC0298 +0x30) ) *0x7084));
	opd_s nextopenaddr_t = {0x477FD8,TOC};
	SPRITE(*nextopenaddr)(unsigned int r3) = (SPRITE(*)(unsigned int))&nextopenaddr_t;
	return nextopenaddr(r3fortheactualfunction);
}

//found at 0x479980
void renderSprite(SPRITE sprite) {
	opd_s render_t = {0x477428,TOC};
	void (*render)(SPRITE t, unsigned int r4, unsigned int r5) = (void(*)(SPRITE,unsigned int,unsigned int))&render_t;
	render(sprite,1,4 or 8);
}

0x01DF0114-0x1DF00CC = 0x48
0x01DE8F70-0x01DE8F28 = 0x48
0x001DE8FB8-0x01DE8F70 = 0x48
0x1DE9000-0x001DE8FB8 = 0x48
	
	*/


/*
	// Global variable(s)
int gGlareHandle; // int
float gGlareDir;
 
// Function(s)
float conv360(float base, float min, float max) {
    // This is the function the script used. I just adapted it for C++.
    float fVar0;
    if (min == max) return min;
    fVar0 = max - min;
    base -= math::round(base - min / fVar0) * fVar0;
    if (base < min) base += fVar0;
    return base;
}
void drawGlare(float pX, float pY, float sX = 1, float sY = 1, int r = 255, int g = 255, int b = 255) {
    // Request the scaleform
    gGlareHandle = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_MENU_GLARE");
    // Get Player Camera Rotation
    Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
    // Calculate Glare Rotation
    float dir = conv360(rot.z, 0, 360);
    // Check if custom rotation is necessary for the rotation component.
    if ((gGlareDir == 0 || gGlareDir - dir > 0.5) || gGlareDir - dir < -0.5) {
        // Set global variable to current direction
        gGlareDir = dir;
        // Open Data Slot Function
        GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(gGlareHandle, "SET_DATA_SLOT");
        // Set Data Slot Value/Parameter
        GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_FLOAT(gGlareDir);
        // Close Data Slot Function
        GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
    }
    // Draw Scaleform
	//GRAPHICS::_0x76C641E4(0.845f, .1135f, 0.22f, .0895f);
    GRAPHICS::DRAW_SCALEFORM_MOVIE(gGlareHandle, pX, pY, sX, sY, r, g, b, 255); // Custom positioning & size
    // DRAW_SCALEFORM_MOVIE_FULLSCREEN(gGlareHandle, r, g, b, 255, 0); // Default positioning & size
}*/

}
#pragma endregion
#pragma region colors
namespace colors {

	int timeout = 0;

	
	bool pr = false;
	bool pg = false;
	bool pb = false;

	bool dr = true;
	bool dg = false;
	bool db = false;

	int r = 255;
	int g = 255;
	int b = 255;

	void change() {
		//timeout = timeout + 1;
		//if (timeout > 5) {

			//timeout = 0;
		if (dr) {
			if (!pr) {
				r = r - 1;
				if (r == 0) {
					pr = true;
				}
			} else {
				r = r + 1;
				if (r == 255) {
					pr = false;
					dr = false;
					dg = true;
				}
			}
		}

		Write_Global_inline(262250,0x7FFFFFFF);//timeout when joining lobby fix lobby timeout
		Write_Global_inline(262222,0x7FFFFFFF);//timeout when joining lobby fix lobby timeout

		if (dg) {
			if (!pg) {
				g = g - 1;
				if (g == 0) {
					pg = true;
				}
			} else {
				g = g + 1;
				if (g == 255) {
					pg = false;
					dg = false;
					db = true;
				}
			}
		}

		if (db) {
			if (!pb) {
				b = b - 1;
				if (b == 0) {
					pb = true;
				}
			} else {
				b = b + 1;
				if (b == 255) {
					pb = false;
					db = false;
					dr = true;
				}
			}
		}
		//}
	}
};
#pragma endregion
#pragma region printing
//char printMessages[5][100];// = {"","","","",""};
/*char printMessages1[100];
char printMessages2[100];
char printMessages3[100];
char printMessages4[100];
char printMessages5[100];*/
char *printMessages1 = "";
char *printMessages2 = "";
char *printMessages3 = "";
char *printMessages4 = "";
char *printMessages5 = "";
void updateParadiseChat() {
	printMessages1 = RTMTool::getMessage(0);
	printMessages2 = RTMTool::getMessage(1);
	printMessages3 = RTMTool::getMessage(2);
	printMessages4 = RTMTool::getMessage(3);
	printMessages5 = RTMTool::getMessage(4);
	/*RTMTool::getMessage(1,printMessages2,100);
	RTMTool::getMessage(2,printMessages3,100);
	RTMTool::getMessage(3,printMessages4,100);
	RTMTool::getMessage(4,printMessages5,100);*/
}
/*
char tprintMessages1[100];
char tprintMessages2[100];
char tprintMessages3[100];
char tprintMessages4[100];*/
__attribute__((noinline)) void printLoop() {
	
	float startx = 0.95;//0.115+(1.0-GRAPHICS::_0x3F0D1A6F()) +0.05;//0.23f;
	float starty = GRAPHICS::_0x3F0D1A6F()-0.0175 - 0.1;/*-0.10555487648f*///0.75f;
	/*for (int i = 0; i < 5; i++) {
		drawing::DrawText(printMessages[i],0,startx,starty+(0.02f*i),0.4f,0.4f,255,255,255,255,false,true);
	}*/
	drawing::DrawText(printMessages5,0,startx,starty-(0.035f/*.02*/*0),0.4f,0.4f,255,255,255,255,false,false,true);
	drawing::DrawText(printMessages4,0,startx,starty-(0.035f*1),0.4f,0.4f,255,255,255,255,false,false,true);
	drawing::DrawText(printMessages3,0,startx,starty-(0.035f*2),0.4f,0.4f,255,255,255,255,false,false,true);
	drawing::DrawText(printMessages2,0,startx,starty-(0.035f*3),0.4f,0.4f,255,255,255,255,false,false,true);
	drawing::DrawText(printMessages1,0,startx,starty-(0.035f*4),0.4f,0.4f,255,255,255,255,false,false,true);
	drawing::DrawText("~b~Paradise & Semjases Chat",0,startx,starty-(0.035f*5),0.4f,0.4f,255,255,255,255,false,false,true);
}
void print(char text[]) {
	return;//this function is disabled
	/*
	printf("%s\n\n",text);
	if (!GAMEPLAY::ARE_STRINGS_EQUAL(printMessages5,text)) {
		strncpy(tprintMessages1,printMessages2,sizeof(tprintMessages1));
		strncpy(tprintMessages2,printMessages3,sizeof(tprintMessages2));
		strncpy(tprintMessages3,printMessages4,sizeof(tprintMessages3));
		strncpy(tprintMessages4,printMessages5,sizeof(tprintMessages4));

		strncpy(printMessages5,text,sizeof(printMessages5));
		strncpy(printMessages4,tprintMessages4,sizeof(printMessages4));
		strncpy(printMessages3,tprintMessages3,sizeof(printMessages3));
		strncpy(printMessages2,tprintMessages2,sizeof(printMessages2));
		strncpy(printMessages1,tprintMessages1,sizeof(printMessages1));
	}*/
	//UI::_0xF42C43C7("STRING");
	//UI::_ADD_TEXT_COMPONENT_STRING(text);
	//UI::_0x38F82261(3000, 1);
}
void printNoCheck(char *text) {
	return;//this function is disabled
		/*char *tmp1 = printMessages[1];
		char *tmp2 = printMessages[2];
		char *tmp3 = printMessages[3];
		char *tmp4 = printMessages[4];
		printMessages[4] = text;
		printMessages[3] = tmp4;
		printMessages[2] = tmp3;
		printMessages[1] = tmp2;
		printMessages[0] = tmp1;*/
		/*strncpy(tprintMessages1,printMessages1,sizeof(tprintMessages1));
		strncpy(tprintMessages2,printMessages2,sizeof(tprintMessages2));
		strncpy(tprintMessages3,printMessages3,sizeof(tprintMessages3));
		strncpy(tprintMessages4,printMessages4,sizeof(tprintMessages4));

		strncpy(printMessages5,text,sizeof(printMessages5));
		strncpy(printMessages4,tprintMessages4,sizeof(printMessages4));
		strncpy(printMessages3,tprintMessages3,sizeof(printMessages3));
		strncpy(printMessages2,tprintMessages2,sizeof(printMessages2));
		strncpy(printMessages1,tprintMessages1,sizeof(printMessages1));*/
}

void print2(char *text, int time = 2000) {
	UI::_0xF42C43C7("STRING"/*"CnCTG_IN_BF"*/);
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	UI::_0x38F82261(time/*3000*/, 1);
	printf("%s\n",text);
}
bool print3bool = false;
char* print3char = "";
int print3time = 0;
void print3(char* text, int time = 2000) {
	//print2 but thread safe
	print3char = text;
	print3time = time;
	print3bool = true;
}
void print3_loop() {
	if (print3bool) {
		print3bool = false;
		UI::_0xF42C43C7("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING(print3char);
		UI::_0x38F82261(print3time, 1);
		printf("%s\n", print3char);
	}
}
#pragma endregion
#pragma region network requesting
namespace netreq {

	bool hasent(uint entity) {
		return NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity);
	}

	bool hasnetid(int networkid) {
		return NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(networkid);
	}

	int getnetidfroment(uint entity) {
		return NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity);
	}

	void reqent(uint entity) {
		if (!hasent(entity)) {
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
			int netid = getnetidfroment(entity);
			NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(netid);
		}
	}

	void reqid(int networkid) {
		if (!hasnetid(networkid)) {
			NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(networkid);
		}
	}

};
#pragma endregion
#pragma region run later
namespace runlater {
	void (*saveFunc)(int);
	bool runlaterBool = false;
	int runlaterInterval = 0;
	int callVar = 0;
	int current = 0;
	void loop() {
		if (runlaterBool ==  true) {
			current++;
			if (current > runlaterInterval) {
				current = 0;
				runlaterBool = false;
				saveFunc(callVar);
			}
		}
	}
	void runlater(int interval, void(*f)(int) = nullFunc, int callVarr = 0) {
		current = 0;
		runlaterBool = true;
		saveFunc = f;
		callVar = callVarr;
		runlaterInterval = interval;
	}
}
namespace runlater_second {
	void (*saveFunc)(int);
	bool runlaterBool = false;
	int runlaterInterval = 0;
	int callVar = 0;
	int current = 0;
	void loop() {
		if (runlaterBool == true) {
			current++;
			if (current > runlaterInterval) {
				current = 0;
				runlaterBool = false;
				saveFunc(callVar);
			}
		}
	}
	void runlater(int interval, void(*f)(int) = nullFunc, int callVarr = 0) {
		current = 0;
		runlaterBool = true;
		saveFunc = f;
		callVar = callVarr;
		runlaterInterval = interval;
	}
}
namespace runlater_time {
	void (*saveFunc)(int);
	bool runlaterBool = false;
	int runlaterInterval = 0;
	int callVar = 0;
	void loop() {
		if (runlaterBool == true) {
			if (time(0) > runlaterInterval) {
				runlaterBool = false;
				saveFunc(callVar);
			}
		}
	}
	void runlater(int seconds, void(*f)(int) = nullFunc, int callVarr = 0) {
		runlaterBool = true;
		saveFunc = f;
		callVar = callVarr;
		runlaterInterval = time(0) + seconds;
	}
}
#pragma endregion

#pragma region Vehicle Mods-pre
namespace VehicleMods {
	void spawnVehicle(char model[], void(*f)(int) = nullFunc);
	void setVehicleOwnedByPlayer(int vehicle, int player);
}
#pragma endregion

#pragma region Traffic Mod
namespace TrafficMods {
	const int trafficsize = 20;
	int traffic[trafficsize];
	int count = 0;
	int arrSize = 0;

	enum modTypes {
		colorize,
		//flip,
		hop,
		boost,
		explode,
		gayify,
		fix,
		raiseSuspension,
		lowerSuspension,
		gravityHIGH,
		gravityNORMAL,
		gravityLOW,
		gravityNEGATIVE,
		deleteVehicle,
		stealOwnership
	};

	int stealVehicleOwner = 0;

	char *gayPlateText[] = {"MMMCOCK","FAGGOT","RAINBOWS"};
	int gayPlateInt = 0;
	char *gravityTypes[] = {"HIGH","NORMAL","LOW","NEGATIVE"};
	int gravityType = 0;
	void runMod(int modType, int car) {
		VEHICLE::SET_VEHICLE_MOD_KIT(car,0);
		switch (modType) {
		case colorize:
			VEHICLE::SET_VEHICLE_COLOURS(car,GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0,160),GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0,160));
			break;
		case hop:
			forceEntity(car,0,0,50,0,0,0);
			break;
		case boost:
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(car,500);
			break;
		case explode:
			static Vector3 c = ENTITY::GET_ENTITY_COORDS(car,true);
			FIRE::ADD_EXPLOSION(c.x,c.y,c.z,26,1,true,true,1);
			break;
		case gayify:
			if (gayPlateInt > 2)//size of the array -1
				gayPlateInt= 0;
			VEHICLE::SET_VEHICLE_COLOURS(car,137,136);
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(car,gayPlateText[gayPlateInt]);
			gayPlateInt++;
			break;
		case fix:
			VEHICLE::SET_VEHICLE_FIXED(car);
			VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(car);
			VEHICLE::SET_VEHICLE_DIRT_LEVEL(car,0);
			break;
		case gravityHIGH:
			setVehicleGravity(car,1000);
			break;
		case gravityNORMAL:
			setVehicleGravity(car,9.8);
			break;
		case gravityLOW:
			setVehicleGravity(car,2);
			break;
		case gravityNEGATIVE:
			setVehicleGravity(car,-9.8);
			break;
		case raiseSuspension:
			setVehicleSuspension(car,getVehicleSuspension(car)-0.1f);
			break;
		case lowerSuspension:
			setVehicleSuspension(car,getVehicleSuspension(car)+0.1f);
			break;
		case deleteVehicle:
			VEHICLE::DELETE_VEHICLE(&car);
			break;
		case stealOwnership:
			VehicleMods::setVehicleOwnedByPlayer(car,stealVehicleOwner);//selectedPlayer cuz from when in sub menus... too lazy to fix lmao
			break;
		}
	}

	
	void trafficModRunLater(int typeOfMod) {
		for (int i = 0; i < count; i++){
			if (traffic[i] != NULL && ENTITY::DOES_ENTITY_EXIST(traffic[i])){
				//do stuff to the cars
				runMod(typeOfMod, traffic[i]);
			}
		}
	}
	void runTrafficMod(int typeOfMod) {
		//arrSize = trafficsize * 2 + 2;
		//traffic[0] = trafficsize;
		count = getVehiclesNearPed(PLAYER::PLAYER_PED_ID(),traffic,trafficsize);//PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), traffic);
		for (int i = 0; i < count; i++){
			if (traffic[i] != NULL && ENTITY::DOES_ENTITY_EXIST(traffic[i])){
				netreq::reqent(traffic[i]);
				netreq::reqent(traffic[i]);
				netreq::reqent(traffic[i]);
				netreq::reqent(traffic[i]);
				netreq::reqent(traffic[i]);
				netreq::reqent(traffic[i]);
			}
		}
		runlater::runlater(20,trafficModRunLater,typeOfMod);
	}
}
#pragma endregion
#pragma region OTHER-pre
namespace OTHER {

	//opd_s GET_ENTITY_COORDS_2_t = { 0x3AB2B0, TOC };
	//Vector3(*GET_ENTITY_COORDS_2)(uint ped, bool b) = (Vector3(*)(uint,bool))&GET_ENTITY_COORDS_2_t;

	//opd_s getcoords_t = { 0x3AB2B0, TOC };
	//void(*getcoords)(int address, uint pedID) = (void(*)(int, uint))&getcoords_t;
	opd_s ADD_OWNED_EXPLOSION_t = { 0x3BD40C, TOC };
	void(*ADD_OWNED_EXPLOSION)(uint pedid, float* xyz, int explosionType, float damageScale, bool isAudible, bool isInvisible, float cameraShake) = (void(*)(uint, float*, int, float, bool, bool, float))&ADD_OWNED_EXPLOSION_t;
	opd_s ADD_EXPLOSION_t = { 0x3BD304, TOC };
	void(*ADD_EXPLOSION)(float* xyz, int explosionType, float damageScale, bool isAudible, bool isInvisible, float cameraShake) = (void(*)(float*, int, float, bool, bool, float))&ADD_EXPLOSION_t;
	//float floatArray[100];float* ReadFloat(int address, int length){for (int i = 0; i < length; i++){floatArray[i] = *(float*)(address + (i * 0x04));}return floatArray;}
	//float* GET_ENTITY_COORDS(uint pedID){getcoords(0x10030000, pedID);return ReadFloat(0x10030000, 3);}
}
#pragma endregion
#pragma region forge-pr
namespace forge {
	//void markEntityForDeletion(int ent, void(*f)(int) = nullFunc);
	void (*saveFunc)(int);
	int markEntityForDeletionTimeout = 0;
	bool markEntityForDeletionBool = false;
	int markEntityForDeletionEntity = 0;
	void markEntityForDeletionLoop() {
		if (markEntityForDeletionBool == true) {
			printf("Trying to delete the entity\n");
			markEntityForDeletionTimeout++;
			if (markEntityForDeletionTimeout < 1000) {
				if (ENTITY::DOES_ENTITY_EXIST(markEntityForDeletionEntity)) {
					netreq::reqent(markEntityForDeletionEntity);
					if (netreq::hasent(markEntityForDeletionEntity)) {
						printf("I have entity\n");
						ENTITY::DETACH_ENTITY(markEntityForDeletionEntity,true,true);
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(markEntityForDeletionEntity,0,1);
						ENTITY::DELETE_ENTITY(&markEntityForDeletionEntity);
						if (!ENTITY::DOES_ENTITY_EXIST(markEntityForDeletionEntity)) {
							printf("Entity Deleted!\n");
							markEntityForDeletionBool = false;
							markEntityForDeletionTimeout = 0;
							saveFunc(markEntityForDeletionEntity);//only executes upon successful completion
						}
					}
				} else {
					printf("Entity Deleted!\n");
					markEntityForDeletionBool = false;
					markEntityForDeletionTimeout = 0;
					saveFunc(markEntityForDeletionEntity);//only executes upon successful completion
				}
			} else {
				markEntityForDeletionTimeout = 0;
				printf("~r~Entity Failed To Delete!\n");
				markEntityForDeletionBool = false;
				//saveFunc(0);
			}
		}
	}
	void markEntityForDeletion(int ent, void(*f)(int) = nullFunc) {
		markEntityForDeletionTimeout = 0;
		markEntityForDeletionEntity = ent;
		markEntityForDeletionBool = true;
		saveFunc = f;
	}
}
namespace removeObjectsSpecial {
	//void markEntityForDeletion(int ent, void(*f)(int) = nullFunc);
	void (*saveFunc)(int);
	int markEntityForDeletionTimeout = 0;
	bool markEntityForDeletionBool = false;
	int markEntityForDeletionEntity = 0;
	void markEntityForDeletionLoop() {
		if (markEntityForDeletionBool == true) {
			//printf("Trying to delete the entity\n");
			markEntityForDeletionTimeout++;
			if (markEntityForDeletionTimeout < 1000) {
				if (ENTITY::DOES_ENTITY_EXIST(markEntityForDeletionEntity)) {
					netreq::reqent(markEntityForDeletionEntity);
					if (netreq::hasent(markEntityForDeletionEntity)) {
						ENTITY::DETACH_ENTITY(markEntityForDeletionEntity,true,true);
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(markEntityForDeletionEntity,0,1);
						ENTITY::DELETE_ENTITY(&markEntityForDeletionEntity);
						if (!ENTITY::DOES_ENTITY_EXIST(markEntityForDeletionEntity)) {
							//printf("Entity Deleted!\n");
							markEntityForDeletionBool = false;
							markEntityForDeletionTimeout = 0;
							saveFunc(markEntityForDeletionEntity);//only executes upon successful completion
						}
					}
				} else {
					//printf("Entity Deleted!\n");
					markEntityForDeletionBool = false;
					markEntityForDeletionTimeout = 0;
					saveFunc(markEntityForDeletionEntity);//only executes upon successful completion
				}
			} else {
				markEntityForDeletionTimeout = 0;
				//printf("~r~Entity Failed To Delete!\n");
				markEntityForDeletionBool = false;
				//saveFunc(0);
			}
		}
	}
	void markEntityForDeletion(int ent, void(*f)(int) = nullFunc) {
		markEntityForDeletionTimeout = 0;
		markEntityForDeletionEntity = ent;
		markEntityForDeletionBool = true;
		saveFunc = f;
	}
}
#pragma endregion
#pragma region OBJ
namespace OBJ {
	//opd_s GET_ENTITY_COORDS_t = { 0x3AB2B0, TOC };
	//Vector3(*GET_ENTITY_COORDS)(uint Hash, bool b) = (Vector3(*)(uint,bool))&GET_ENTITY_COORDS_t;
	Vector3 getPlayerPos() {return ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true);}
	Vector3 getOtherPlayerPos(int id) {return ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(id),true);}
	//int create_object_a[2] = {0x3F8F0C,TOC};
	//int(*create)(unsigned int hash, float*) = (int(*)(unsigned int,float*))&create_object_a;
	//prop_tv_flat_01_screen is inpenetrable and invisible from one side
	int make_object(int ObjectName, Vector3 Coordinates, bool freeze, void(*f)(int) = nullFunc) {
		//STREAMING::LOAD_ALL_OBJECTS_NOW();
		int ObjectHash = ObjectName;
				STREAMING::REQUEST_MODEL(ObjectHash);//on first call to this, getCVehicleModelInfo for ufo is non-zer, but for purple dino (ch3_01_dino) is 0
				//STREAMING::IS_MODEL_IN_CDIMAGE(ObjectHash);//not sure if this is necesssary
				if (STREAMING::HAS_MODEL_LOADED(ObjectHash))
				{
					//print2("model loaded",1000);
					float coords[] = {Coordinates.x,Coordinates.y,Coordinates.z};
					int obj = OBJECT::CREATE_OBJECT(ObjectHash,coords[0],coords[1],coords[2],1,1,1);
					if (ENTITY::DOES_ENTITY_EXIST(obj)) {
						if (freeze) {
							ENTITY::FREEZE_ENTITY_POSITION(obj, true);
						}
						return obj;
					}
				}
		return 0;
	}
	int make_object(char* ObjectName, Vector3 Coordinates, bool freeze, void(*f)(int) = nullFunc) {
		int ObjectHash = GAMEPLAY::GET_HASH_KEY(ObjectName);
		return make_object(ObjectHash, Coordinates, freeze, f);
	}
	/*void spawnMoneyModel(const char* Model, Vector3 Position, const char* Pickup = "PICKUP_MONEY_CASE")
{
	int ModelHash = GET_HASH_KEY(Model);
	int PickupHash = GET_HASH_KEY(Pickup);
	REQUEST_MODEL(ModelHash);
	if (HAS_MODEL_LOADED(ModelHash))
	{
		CREATE_AMBIENT_PICKUP(PickupHash, &Position, 0, 2000, ModelHash, 0, 1);
		SET_MODEL_AS_NO_LONGER_NEEDED(ModelHash);
	}
}*/
	int make_ambient_object(int ObjectName, Vector3 Coordinates, bool freeze, void(*f)(int) = nullFunc, char* Pickup = "PICKUP_MONEY_CASE") {
		int PickupHash = GAMEPLAY::GET_HASH_KEY(Pickup);
		int ObjectHash = ObjectName;
				STREAMING::REQUEST_MODEL(ObjectHash);
				//STREAMING::REQUEST_MODEL(PickupHash);
				if (STREAMING::HAS_MODEL_LOADED(ObjectHash)/* && STREAMING::HAS_MODEL_LOADED(PickupHash)*/)
				{

					int obj = OBJECT::CREATE_AMBIENT_PICKUP(PickupHash, Coordinates.x,Coordinates.y,Coordinates.z, 0, 40000, ObjectHash/*0x113FD533*/, false, true);
					NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(obj),true);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(ObjectHash/*0x113FD533*/);
					if (ENTITY::DOES_ENTITY_EXIST(obj)) {
						if (freeze) {
							ENTITY::FREEZE_ENTITY_POSITION(obj, true);
						}
						return obj;
					}
				}
		return 0;
	}
	int make_ambient_object(char *ObjectName, Vector3 Coordinates, bool freeze, void(*f)(int) = nullFunc, char* Pickup = "PICKUP_MONEY_CASE") {
		int ObjectHash = GAMEPLAY::GET_HASH_KEY(ObjectName);
		return make_ambient_object(ObjectHash,Coordinates, freeze, f, Pickup);
	}
	/*char*/unsigned int forceCreateObjectId;//[100];
	int forceCreateObjectBool = false;
	Vector3 forceCreateObjectCoords = {0,0,0};
	Vector3 forceCreateObjectRotation = {0,0,0};
	bool forceCreateObjectFreeze = false;
	int forceCreateObjectTimeout = 0;
	bool forceCreateObjectMoneyDrop = false;
	void (*saveFunc)(int);
	void forceCreateObjectLoop() {
		if (forceCreateObjectBool == true) {
			//printf("Timeout: %i\n",forceCreateObjectTimeout);
			forceCreateObjectTimeout = forceCreateObjectTimeout + 1;
			int obj;
			if (!forceCreateObjectMoneyDrop)
				obj = make_object(forceCreateObjectId,forceCreateObjectCoords,forceCreateObjectFreeze);
			else
				obj = make_ambient_object(forceCreateObjectId,forceCreateObjectCoords,forceCreateObjectFreeze);
			if (obj != 0) {
				//NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(obj),true);
				//saveFunc(obj);
				printf("Object Spawned\n");
				forceCreateObjectBool = false;
				forceCreateObjectTimeout = 0;
				ENTITY::SET_ENTITY_ROTATION(obj,forceCreateObjectRotation.x,forceCreateObjectRotation.y,forceCreateObjectRotation.z,true,true);
				forceCreateObjectRotation.x = 0;
				forceCreateObjectRotation.y = 0;
				forceCreateObjectRotation.z = 0;
				setEntityMigrateable(obj,false);//set it to not be migrateable
				saveFunc(obj);
			}
			if (forceCreateObjectTimeout > 500) {//2000 previously but after further testing, 2000 is way too much. I just wrote bool on accident
				printf("Object NOT Spawned\n");
				saveFunc(-1);
				forceCreateObjectBool = false;
				forceCreateObjectTimeout = 0;
			}
		}
	}
	void forceCreateObject(unsigned int object,Vector3 pos,Vector3 rot, bool freeze, void(*f)(int) = nullFunc, bool moneyDrop = false) {
		bool valid = STREAMING::IS_MODEL_IN_CDIMAGE(object) || STREAMING::IS_MODEL_VALID(object);
		if (!valid) {
			f(-1);
			return;
		}


		//for (int i = 0; i < 100; i++)
			//forceCreateObjectId[i] = 0;
		//strncpy(forceCreateObjectId,object,100);
		forceCreateObjectId = object;
		forceCreateObjectFreeze = freeze;
		forceCreateObjectCoords.x = pos.x;
		forceCreateObjectCoords.y = pos.y;
		forceCreateObjectCoords.z = pos.z;
		forceCreateObjectRotation.x = rot.x;
		forceCreateObjectRotation.y = rot.y;
		forceCreateObjectRotation.z = rot.z;
		forceCreateObjectMoneyDrop = moneyDrop;
		forceCreateObjectBool = true;
		saveFunc = f;
	}
	void forceCreateObject(char *object,Vector3 pos,Vector3 rot, bool freeze, void(*f)(int) = nullFunc, bool moneyDrop = false) {
		forceCreateObject(GAMEPLAY::GET_HASH_KEY(object),pos,rot,freeze,f,moneyDrop);
	}
	opd_s ATTACH_ENTITY_TO_ENTITY_t = {0x3B0088,TOC};
	void(*ATTACH_ENTITY_TO_ENTITY_F)(uint entity1, uint entity2, int boneIndex, float *co, float *rot, bool p9, bool isRel, bool ignoreUpVec, bool p12, int unk, bool p14) = (void(*)(uint, uint, int, float *, float *, bool, bool, bool, bool, int, bool))&ATTACH_ENTITY_TO_ENTITY_t;
	opd_s GET_PED_BONE_INDEX_t = {0x41A0FC,TOC};
	int(*GET_PED_BONE_INDEX)(uint ped, int bone) = (int(*)(uint,int))&GET_PED_BONE_INDEX_t;
	int attachProp(int player, int bodyPart, char* prop) {
		Vector3 oloc = getOtherPlayerPos(player);
		Vector3 nloc = {oloc.x,oloc.y,oloc.z+2};
		int obj = make_object(prop,nloc,false);
		if (obj != 0) {
			float cord[] = {0,0,0};
			float rot[] = {0,90,0};
			ATTACH_ENTITY_TO_ENTITY_F(obj, PLAYER::GET_PLAYER_PED(player), GET_PED_BONE_INDEX(PLAYER::GET_PLAYER_PED(player),bodyPart), cord, rot, 1, 1, 0, 0, 2, 1);
		}
		return obj;
	}









	float oooooooo[] = {0,0,0};
	float ooooooo[] = {0,90,0};
	void attachPropAlreadySpawned(int player, int bodyPart, int prop, float cord[] = oooooooo, float rot[] = ooooooo) {
		if (prop != 0) {
			ATTACH_ENTITY_TO_ENTITY_F(prop, PLAYER::GET_PLAYER_PED(player), GET_PED_BONE_INDEX(PLAYER::GET_PLAYER_PED(player),bodyPart), cord, rot, 1, 1, 0, 0, 2, 1);
		}
	}

	void attachPropAlreadySpawnedAddress(int player, int bodyPart, int addressOfEntity, float cord[] = oooooooo, float rot[] = ooooooo) {
		unsigned int patch = *(volatile unsigned int*)0x3B0104;
		*(volatile unsigned int*)0x3B0104 = 0x60000000;
		if (addressOfEntity != 0) {
			ATTACH_ENTITY_TO_ENTITY_F(addressOfEntity, PLAYER::GET_PLAYER_PED(player), GET_PED_BONE_INDEX(PLAYER::GET_PLAYER_PED(player),bodyPart), cord, rot, 1, 1, 0, 0, 2, 1);
		}
		*(volatile unsigned int*)0x3B0104 = patch;
	}

	void attachPropAlreadySpawned(int player, int bodyPart, int prop, Vector3 c, Vector3 r) {
		if (prop != 0) {
			float cord[] = {c.x,c.y,c.z};
			float rot[] = {r.x,r.y,r.z};
			ATTACH_ENTITY_TO_ENTITY_F(prop, PLAYER::GET_PLAYER_PED(player), GET_PED_BONE_INDEX(PLAYER::GET_PLAYER_PED(player),bodyPart), cord, rot, 1, 1, 0, 0, 2, 1);
		}
	}

		void attachPropAlreadySpawnedObject(int objectToAttachTo, int bodyPart, int prop, Vector3 c, Vector3 r, bool parseBone = true) {
		if (prop != 0) {
			float cord[] = {c.x,c.y,c.z};
			float rot[] = {r.x,r.y,r.z};
			if (parseBone)
					bodyPart = GET_PED_BONE_INDEX(objectToAttachTo,bodyPart);
			ATTACH_ENTITY_TO_ENTITY_F(prop, objectToAttachTo, bodyPart, cord, rot, 1, 1, 0, 0, 2, 1);
		}
	}

}
#pragma endregion
#pragma region Ped Anim
namespace PedAnim {
	bool enabled = false;
	int ped = 0;
	char *animID = "";
	char *animDict = "";
	void (*saveFunc)(int);
	int timeout = 0;
	bool doNetRequest = true;
	void loop() {
		if (enabled == true) {
			timeout++;
			if (timeout < 5000) {
				netreq::reqent(ped);
				if (netreq::hasent(ped) || doNetRequest == false) {
					STREAMING::REQUEST_ANIM_DICT(animDict);
					if(STREAMING::HAS_ANIM_DICT_LOADED(animDict)) {
						AI::TASK_PLAY_ANIM(ped, animDict, animID, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
						enabled = false;
						timeout = 0;
						saveFunc(ped);
					}
				}
			} else {
				enabled = false;
				timeout = 0;
				print("Could not set entity animation");
			}
		}
	}

	void anim(int pedd, char *dict, char *anim, void(*f)(int) = nullFunc, bool netCheck = true) {
		saveFunc = f;
		animDict = dict;
		animID = anim;
		ped = pedd;
		enabled = true;
		doNetRequest = netCheck;
	}
}
#pragma endregion
#pragma region pressed Buttons
namespace pressedButtons {
	bool l1pressed = false;
	bool l2pressed = false;
	bool l3pressed = false;
	bool r1pressed = false;
	bool r2pressed = false;
	bool r3pressed = false;
	bool l1jpressed = false;
	bool l2jpressed = false;
	bool l3jpressed = false;
	bool r1jpressed = false;
	bool r2jpressed = false;
	bool r3jpressed = false;
	bool dpaduppressed = false;
	bool dpaddownpressed = false;
	bool dpadleftpressed = false;
	bool dpadrightpressed = false;
	int leftAnalogX = 0;
	int leftAnalogY = 0;
	bool squarepressed = false;
}
#pragma endregion
#pragma region noclip
namespace noclip {
	bool enabled = false;
	bool r3pressed = false;
	float speed = 2;

	float x = 0, y = 0, z = 0;

	Vector3 GET_COORDS_INFRONT(float d, float offset = 0) {
		Vector3 ro = CAM::GET_GAMEPLAY_CAM_ROT(2);
		Vector3 rot;
		float x = /*math::ceil(*/ro.z+90+offset;//);
		while (x < 0) x = x + 360;
		while (x > 360) {
			x = x - 360;
		}
		bool fix = false;
		if (x > 180) {
			fix = true;
		}
		//if (offset > 180)
			//offset = (offset-180)*-1;
		//char buf[50];
		//snprintf$$(buf,sizeof(buf),"x: %f",x);
		//print(buf);
		rot.x = x;
		rot.z = /*math::ceil(*/ro.x;//);
		float cosrotz = math::Cos(rot.z);
		float x1 = 0;
		float y1 = 0;
		float z1 = d*math::Sin(rot.z/**(offset/180)*/);
		if (fix == true) {
			rot.x = (rot.x-180);
			x1 = -d*math::Cos(rot.x)*cosrotz;
			y1 = -d*math::Sin(rot.x)*cosrotz;
		} else {
			x1 = d*math::Cos(rot.x)*cosrotz;
			y1 = d*math::Sin(rot.x)*cosrotz;
		}
		Vector3 Coords = {x1,y1,z1};
        return Coords;
	}

	Vector3 DIF_TO_ROT(float d, float offset = 0) {
		Vector3 ro = CAM::GET_GAMEPLAY_CAM_ROT(2);
		Vector3 rot;
		float x = ro.z+90+offset;
		while (x < 0) x = x + 360;
		while (x > 360) {
			x = x - 360;
		}
		bool fix = false;
		if (x > 180) {
			fix = true;
		}
		rot.x = x;
		rot.z = ro.x;
		float cosrotz = math::Cos(rot.z);
		float x1 = 0;
		float y1 = 0;
		float z1 = d*math::Sin(rot.z);
		if (fix == true) {
			rot.x = (rot.x-180);
			x1 = -d*math::Cos(rot.x)*cosrotz;
			y1 = -d*math::Sin(rot.x)*cosrotz;
		} else {
			x1 = d*math::Cos(rot.x)*cosrotz;
			y1 = d*math::Sin(rot.x)*cosrotz;
		}
		Vector3 Coords = {x1,y1,z1};
        return Coords;
	}

	float zeroTo360(float degree) {
		while (degree > 360)
			degree-=360;
		while (degree < 0)
			degree+=360;
		return degree;
	}

	float leftanalogpreviousx = 0;
	float leftanalogpreviousy = 0;
	volatile float extrot = 0;
	float zmult = 1;
	void loop() {

		if (enabled == true) {
			int handle = PLAYER::PLAYER_PED_ID();
			if (PED::IS_PED_IN_ANY_VEHICLE(handle,0)) {
				handle = PED::GET_VEHICLE_PED_IS_USING(handle);
				netreq::reqent(handle);
				ENTITY::SET_ENTITY_ROTATION(handle,0,0,0,0,0);
			}
			float newSpeed = speed;
			if (pressedButtons::r1pressed)
				newSpeed *= 4.0f;
			if (pressedButtons::l1pressed)
				newSpeed /= 4.0f;
			/*if (pressedButtons::r2pressed)
				z += newSpeed/5.0f;//so default with no speed modifer is 0.4
			if (pressedButtons::l2pressed)
				z -= newSpeed/5.0f;*/

			if (/*r3pressed == true*/pressedButtons::leftAnalogX != 0 || pressedButtons::leftAnalogY != 0) {
				//r3pressed = false;
				if (leftanalogpreviousx != pressedButtons::leftAnalogX || leftanalogpreviousy != pressedButtons::leftAnalogY) {
					leftanalogpreviousx = pressedButtons::leftAnalogX;
					leftanalogpreviousy = pressedButtons::leftAnalogY;
					float tmpx = pressedButtons::leftAnalogX;
					if (tmpx == 0)
						tmpx = 0.000001f;
					extrot = zeroTo360(GAMEPLAY::ATAN2(pressedButtons::leftAnalogY,tmpx));//0 to 360
					if (extrot <= 90) {//1nd quadrant
						zmult = extrot/90;
					} else if (extrot <= 180) {
						zmult = (extrot*-1+180)/90;
					} else if (extrot <= 270) {
						zmult = (extrot-180)/-90;
					} else if (extrot <= 360) {
						zmult = ((extrot-180)*-1+180)/-90;
					}
					extrot = zeroTo360(extrot-90);
					//extrot is not being calculated correctly for some reason
					//printf("extrot: %i, x: %i, y: %i\n",(int)(extrot),pressedButtons::leftAnalogX,pressedButtons::leftAnalogY);
					//char buf[50];
					//snprintf(buf,sizeof(buf),"X: %i, Y: %i, extrot: %.2f, zmult: %.2f",pressedButtons::leftAnalogX,pressedButtons::leftAnalogY,extrot,zmult);
					//printf("%s\n",buf);
				}
				//drawing::DrawFloat(extrot,0,0.5,0.5,1,1,255,255,255,255,true,5,true);
				
				Vector3 c = GET_COORDS_INFRONT(newSpeed,extrot/**(((math::abs(pressedButtons::leftAnalogX)+math::abs(pressedButtons::leftAnalogY))/2)/127)*//*,extrot*/);
				x = x+c.x;
				y = y+c.y;
				z = z+c.z*zmult;
			}
			Vector3 ro = CAM::GET_GAMEPLAY_CAM_ROT(2);
			ENTITY::SET_ENTITY_COORDS(handle,x,y,z,ro.x,ro.y,ro.z,0);
		}
	}

	bool toggle() {
		Vector3 m = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true);
		x = m.x;
		y = m.y;
		z = m.z;
		enabled = !enabled;
		/*if (enabled) {
			ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(),true);
		} else {
			ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(),false);
		}*/
		return enabled;
	}

	bool setEnabled(bool val) {
		enabled = val;
		Vector3 m = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true);
		x = m.x;
		y = m.y;
		z = m.z;
	}

	/*bool grapplingHookEnabled = false;
	void grapplingHookLoop() {
		if (grapplingHookEnabled) {
			if (pressedButtons::r3jpressed) {
				Vector3 infront = noclip::GET_COORDS_INFRONT(5);
				//OBJECT::SLIDE_OBJECT(PLAYER::PLAYER_PED_ID(),infront.x,infront.y,infront.z,5,5,5,true);
				forceEntity(PLAYER::PLAYER_PED_ID(),infront.x,infront.y,infront.z,0,0,0,true);
			}
		}
	}*/
}
#pragma endregion
#pragma region create_vehicle
namespace create_vehicle {
	/*opd_s CREATE_VEHICLE_t = { 0x44DE68, TOC };
	int(*CREATE_VEHICLE)(int carHash, float* getCords, float r0, bool fallsee, bool fallse) = (int(*)(int, float*, float, bool, bool))&CREATE_VEHICLE_t;

	int create_vehicle(int hash) {
		if (STREAMING::IS_MODEL_IN_CDIMAGE(hash) && STREAMING::IS_MODEL_A_VEHICLE(hash)) {
			STREAMING::REQUEST_MODEL(hash);
			if(STREAMING::HAS_MODEL_LOADED(hash)) {
				int veh = CREATE_VEHICLE(hash, OTHER::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID()), 0, 1, 0);
				return veh;
			}
		}
		return 0;
	}

	int create_vehicle(int hash, float *loc) {
		if (STREAMING::IS_MODEL_IN_CDIMAGE(hash) && STREAMING::IS_MODEL_A_VEHICLE(hash)) {
			STREAMING::REQUEST_MODEL(hash);
			if(STREAMING::HAS_MODEL_LOADED(hash)) {
				int veh = CREATE_VEHICLE(hash, loc, 0, 1, 0);
				return veh;
			}
		}
		return 0;
	}*/

	bool setVehOnGround = true;//this can be set anywhere if the next vehicle you spawn you do not want to set on ground properly
	int CREATE_VEHICLE(int hash, float x, float y, float z) {
		//if (strstr(SCRIPT::GET_THIS_SCRIPT_NAME(),"freemode") != NULL){
			//print("script is freemode");
			int model = hash;
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model)) {
				STREAMING::REQUEST_MODEL(model);
				//while (!STREAMING::HAS_MODEL_LOADED(model)) SYSTEM::WAIT(1);
				if (STREAMING::HAS_MODEL_LOADED(model) == true) {
					//print("Model Loaded");
					Vehicle veh = VEHICLE::CREATE_VEHICLE(model, x, y, z, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 0);
					if(ENTITY::DOES_ENTITY_EXIST(veh)){
						if (setVehOnGround)
							VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
						setVehOnGround = true;//reset
  						//PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
  						//ENTITY::SET_ENTITY_CAN_BE_DAMAGED(veh, false);
  						//STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
						//print("did all that shiat");
						return veh;
					}
				}
			}
		//} else {
			//print("script is not freemode");
		//}
		return 0;
	}

}
#pragma endregion
#pragma region lobby Mod Menu
namespace lobbyModMenu {

	
	/*void maxOutCar(int player) {
		//VEHICLE::GET_NUM_VEHICLE_MODS(VehicleHandle,id);

		int VehicleHandle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(player));
		VEHICLE::SET_VEHICLE_MOD_KIT(VehicleHandle, 0);
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(VehicleHandle, "PRO");
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(VehicleHandle, 5);
		VEHICLE::TOGGLE_VEHICLE_MOD(VehicleHandle, 18, 1);
		VEHICLE::TOGGLE_VEHICLE_MOD(VehicleHandle, 22, 1);
		VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 16, 5, 0);//5
		VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 12, 2, 0);//2
		VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 11, 3, 0);//3
		VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 14, 14, 0);//14
		VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 15, 3, 0);//3
		VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 13, 2, 0);//2
		VEHICLE::SET_VEHICLE_WHEEL_TYPE(VehicleHandle, 6);
		VEHICLE::SET_VEHICLE_WINDOW_TINT(VehicleHandle, 5);
		VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 23, 19, 1);//19
		VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 0, 1, 0);//1
		VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 1, 1, 0);
		VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 2, 1, 0);
		VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 3, 1, 0);
		VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 4, 1, 0);
		VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 5, 1, 0);
		VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 6, 1, 0);
		VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 7, 1, 0);
		VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 8, 1, 0);
		VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 9, 1, 0);
		VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 10, 1, 0);//1
		VEHICLE::TOGGLE_VEHICLE_MOD(VehicleHandle, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(VehicleHandle, 0, 0, 0);
	}*/

	void maxOutCar(int player) {
		int VehicleHandle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(player));
		VEHICLE::SET_VEHICLE_MOD_KIT(VehicleHandle, 0);
		for (int i = 0; i < 25; i++) {
			//printf("Part %i is %i ",i,VEHICLE::GET_NUM_VEHICLE_MODS(VehicleHandle,i));
			VEHICLE::SET_VEHICLE_MOD(VehicleHandle, i, VEHICLE::GET_NUM_VEHICLE_MODS(VehicleHandle,i)-1, 0);
		}
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(VehicleHandle, "paradise");
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(VehicleHandle, 5);
		VEHICLE::TOGGLE_VEHICLE_MOD(VehicleHandle, 18, 1);
		VEHICLE::TOGGLE_VEHICLE_MOD(VehicleHandle, 22, 1);
		VEHICLE::SET_VEHICLE_WHEEL_TYPE(VehicleHandle, 6);
		VEHICLE::SET_VEHICLE_WINDOW_TINT(VehicleHandle, 5);
		VEHICLE::TOGGLE_VEHICLE_MOD(VehicleHandle, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(VehicleHandle, 0, 0, 0);
	}

	void setColorOtherCar(int r, int g, int b, int base,int player) {
		int VehicleHandle =PED:: GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(player));
		VEHICLE::SET_VEHICLE_MOD_KIT(VehicleHandle, 0);
		VEHICLE::SET_VEHICLE_COLOURS(VehicleHandle, base, base);//120 is chrome
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(VehicleHandle,r,g,b);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(VehicleHandle,r,g,b);
	}


	/*int CREATE_VEHICLE_ONLINE_COORD(uint hash, float* coords) {
		STREAMING::REQUEST_MODEL(hash);
		if (STREAMING::IS_MODEL_IN_CDIMAGE(hash) && STREAMING::IS_MODEL_A_VEHICLE(hash)) {
			if(STREAMING::HAS_MODEL_LOADED(hash)) {
				return VEHICLE::CREATE_VEHICLE(hash, coords[0],coords[1],coords[2], 0, 1, 0);
			}
		}
		return 0;
	}*/


	int spawnVehicleLoc(char* model, float* coords) {
		//float coords[] = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID());//OTHER::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID());
		return create_vehicle::CREATE_VEHICLE(GAMEPLAY::GET_HASH_KEY(model),coords[0],coords[1],coords[2]);
		//return CREATE_VEHICLE_ONLINE_COORD(GAMEPLAY::GET_HASH_KEY(model), coords);
	}

	int moneyBagDrop = 0x113FD533;
	void dropMoneyBag(int index) {
		STREAMING::REQUEST_MODEL(moneyBagDrop);

		if (STREAMING::HAS_MODEL_LOADED(moneyBagDrop)) {
			uint PICKUP_MONEY_CASE = GAMEPLAY::GET_HASH_KEY("PICKUP_MONEY_CASE");
			Vector3 playerpos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(index),true);
			int obj = OBJECT::CREATE_AMBIENT_PICKUP(PICKUP_MONEY_CASE, playerpos.x,playerpos.y,playerpos.z, 0, 40000, moneyBagDrop, false, true);
			NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(obj),true);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(moneyBagDrop);
		}
	}

	bool spawncarbool[] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};//20 for safe measures
	int spawncarint[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int spawncarinttimeout[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	void checkspawncar(int player) {

		if (spawncarbool[player] == true) {
			spawncarinttimeout[player] = spawncarinttimeout[player]+1;
			if (spawncarinttimeout[player] < 1000) {
				int playerped = PLAYER::GET_PLAYER_PED(player);
				Vector3 playerpos = ENTITY::GET_ENTITY_COORDS(playerped,true);
				float pos[] = {playerpos.x,playerpos.y,playerpos.z};
				spawncarint[player] = spawnVehicleLoc("adder",pos);
				if (ENTITY::DOES_ENTITY_EXIST(spawncarint[player]) == true) {
					spawncarinttimeout[player] = 0;
					spawncarbool[player] = false;
				}
			} else {
				spawncarinttimeout[player] = 0;
				spawncarbool[player] = false;
			}
		}
	}

	bool maxcarbool[] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};//20 for safe measures
	int maxcarinttimeout[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	void domaxcar(int player) {
		if (maxcarbool[player] == true) {
			int playerped = PLAYER::GET_PLAYER_PED(player);
			if (PED::IS_PED_IN_ANY_VEHICLE(playerped,0)) {
				int car = PED::GET_VEHICLE_PED_IS_USING(playerped);
				netreq::reqent(car);
				if (netreq::hasent(car)) {
					maxOutCar(player);
					setColorOtherCar(52, 152, 219,120,player);
					maxcarinttimeout[player] = 0;
					maxcarbool[player] = false;
				} else {
					maxcarinttimeout[player] = maxcarinttimeout[player]+1;
					if (maxcarinttimeout[player] > 2000) {
						maxcarinttimeout[player] = 0;
						maxcarbool[player] = false;
					}
				}
			} else {
				maxcarinttimeout[player] = 0;
				maxcarbool[player] = false;
			}
		}
	}

	void domods(int player) {
		int playerped = PLAYER::GET_PLAYER_PED(player);
		int weaponhash = WEAPON::GET_SELECTED_PED_WEAPON(playerped);
		int spawnadder = GAMEPLAY::GET_HASH_KEY("WEAPON_COMBATPISTOL");
		int spawnmoney = GAMEPLAY::GET_HASH_KEY("WEAPON_PISTOL");
		int maxcar = GAMEPLAY::GET_HASH_KEY("WEAPON_SNSPISTOL");

		if (weaponhash == spawnadder) {
			//spawncarbool[player] = true; //I do not like people spawning adders
		}
		if (weaponhash == spawnmoney) {
			dropMoneyBag(player);
			dropMoneyBag(player);
			dropMoneyBag(player);
			dropMoneyBag(player);
			dropMoneyBag(player);
		}
		if (weaponhash == maxcar) {
			maxcarbool[player] = true;
		}
	}

	bool enabled = false;
	bool hasshot[] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};//20 for safe measures
	void loop() {
		if (enabled == true) {
			for (int i = 0; i < 18; i++) {
				checkspawncar(i);
				domaxcar(i);
				if (PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED(i))) {
					if (hasshot[i] == false) {
						hasshot[i] = true;
						domods(i);
					}
				} else {
					hasshot[i] = false;
				}
			}
		}
	}

	bool toggle() {
		enabled = !enabled;
		return enabled;
	}

};
#pragma endregion
#pragma region God Mode
namespace GodMode {
	bool godmodeEnabled = false;
	void toggleGodmode() {
		godmodeEnabled = !godmodeEnabled;
		PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(),false);
	}

	void godmodeLoop() {
		if (godmodeEnabled == true) {
			PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(),godmodeEnabled);
		}
	}
}
#pragma endregion
#pragma region Player Mods
template <typename T>
T getEntityData(unsigned int entityIndex, unsigned int dataIndex);
void sleep(usecond_t time);
//void * neww (std::size_t sz);
//void deletee (void *ptr);
/*
namespace webmanccapi {
	void AreYouCCAPIorWebMan();
	void ShutDownPS3();
};*/

void createMapSpooner(char *file);
void createVehicleSpooner(char *file);
char *mapSpoonerFile = "";
bool mapSpoonerQue = false;
char *vehicleSpoonerFile = "";
bool vehicleSpoonerQue = false;

bool vehicleSpoonerQueFunction();
bool spoonerQueFunction();


bool otherThreadLoopedFunctions();

#include <time.h>


__ALWAYS_INLINE void antiBreakpoint() {

	static bool antiDebuggingSetupDone = false;
	sys_prx_module_info_t MainModuleInfo;
	if (antiDebuggingSetupDone == false) {
		antiDebuggingSetupDone = true;
		char filename[SYS_PRX_MODULE_FILENAME_SIZE];
		sys_prx_segment_info_t segments[2];
		MainModuleInfo.size = sizeof(MainModuleInfo);
		MainModuleInfo.segments = segments;
		MainModuleInfo.segments_num = sizeof(segments) / sizeof(sys_prx_segment_info_t);
		MainModuleInfo.filename = filename;
		MainModuleInfo.filename_size = sizeof(filename);
		sys_prx_get_module_info(sys_prx_get_my_module_id(), SYS_PRX_MODULE_FILENAME_SIZE, &MainModuleInfo);
	}

	for (int i = 0; i < MainModuleInfo.segments[0].filesz / 4; i++) {
		if (*(uint32_t*)(MainModuleInfo.segments[0].base + (4 * i)) == 0x7FE00008) {
			//printf("\nbreakpoint has been set at %p! please remove it :)\n", MainModuleInfo.segments[0].base + (4 * i));
			sys_prx_stop_module(sys_prx_get_my_module_id(), SYS_PRX_MODULE_FILENAME_SIZE, 0, 0, 0, 0);
			sys_prx_unload_module(sys_prx_get_my_module_id(), 0, 0);

			//crash
			for (unsigned int i = 0x10200; i < 0x1D03377; i++) {
				*(char*)i = 0;
			}
		}
	}
}

// 0x0006 single beep
// 0x0036 double beep
// 0x01B6 triple beep
// 0x0FFF continuous beep, gruesome!!!
void beep(uint8_t mode)
{
	uint16_t param = 0;

	switch (mode)
	{
	case 1: param = 0x0006; break;		// single beep
	case 2: param = 0x0036; break;		// double beep
	case 3: param = 0x01B6; break;		// triple beep
	case 4: param = 0x0FFF; break;		// continuous beep, gruesome!!!
	}

	system_call_3(392, 0x1004, 0xA, param);
}

#define BEEP_ONCE() {}//beep(1)
#define BEEP_TWICE() {}//beep(2)

#define CELL_UTIL_PAD_MAX	7
static CellPadInfo2  sPadInfo2;

bool updatePadInfo()
{
	CellPadInfo2 pad_info2;
	int32_t cr = cellPadGetInfo2(&pad_info2);
	if (cr != CELL_PAD_OK) return false;

	sPadInfo2 = pad_info2;

	return true;
}

bool isConnected(uint8_t pad)
{
	if (pad >= CELL_UTIL_PAD_MAX) return false;
	if (pad >= sPadInfo2.max_connect) return false;

	return (sPadInfo2.port_status[pad] & CELL_PAD_STATUS_CONNECTED);
}

bool cellPadUtilIsConnected(uint8_t pad)
{
	if (!updatePadInfo()) {
		return false;
	}
	return isConnected(pad);
}


void quitDetection() {
	//cellPadUtilUpdate();

	static int pad = -1;
	if (pad == -1) {
		for (int i = 0; i < CELL_UTIL_PAD_MAX; i++) {
			if (cellPadUtilIsConnected(i))
				pad = i;
		}
	}
	//CellPadUtilPress padInfo = cellPadUtilGetPressValue(pad);
	CellPadData tmppaddata;
	static CellPadData paddata;
	int32_t ret = cellPadGetData(pad == -1 ? 0 : pad, &tmppaddata);
	if (ret == CELL_PAD_OK && tmppaddata.len != 0) {
		paddata = tmppaddata;
	}
	
	

	bool bOnlineGameCrashed = false;
	if (*(bool*)(0x1D65D80)) // MULTIPLAYER_IS_ACTIVE
	{
		if (*(int32_t*)(0x223F198/*0x223F19B*/) == 2) // online session
		{ 
			static uint32_t cache_dynamic_hash = 0;
			uint32_t dynamic_hash = *(uint32_t*)(0x1EC66FC);
			// just checks if they are different. If both dynamic_hash and cache_dynamic_hash are the same value then that means we crashed


			if (dynamic_hash == cache_dynamic_hash) {
				bOnlineGameCrashed = true;

				// beep twice so they know they froze
				BEEP_TWICE();
			}

			cache_dynamic_hash = dynamic_hash;

		}
	}

	/*if (paddata.button[CELL_PAD_BTN_OFFSET_PRESS_CIRCLE]) {
		printf("You are pressing circle!\n");
	}*/


	if (bOnlineGameCrashed)
	{
		
		printf("You have crashed! Press L3 + R3 to exit game\n");

		//if (cell_pad & circle_button)
		//if (paddata.button[CELL_PAD_BTN_OFFSET_PRESS_CIRCLE])
		int data = paddata.button[CELL_PAD_BTN_OFFSET_DIGITAL1];
		if ((data & CELL_PAD_CTRL_R3) && (data & CELL_PAD_CTRL_L3))
		{
			// beep once so they know we are restarting the game
			BEEP_ONCE();
			sys_process_exit(0);
		}
	}
}


__ALWAYS_INLINE void checkTampering() {
	//webmanccapi::AreYouCCAPIorWebMan();
	static time_t time1 = time(0);
	bool bypassTime1 = false;

	quitDetection();


	/*This is other code I throw inn this thread*/
	if (mapSpoonerQue) {
		createMapSpooner(mapSpoonerFile);
		bypassTime1 = true;
	}
	if (vehicleSpoonerQue) {
		createVehicleSpooner(vehicleSpoonerFile);
		bypassTime1 = true;
	}

	/*if (vehicleSpoonerQueFunction()) {//this is for file loading
		bypassTime1 = true;
	}

	if (spoonerQueFunction()) {//this is for file loading
		bypassTime1 = true;
	}*/

	if (otherThreadLoopedFunctions()) {
		bypassTime1 = true;//bypass timer if done something that would pause it
	}

	/*end of other code I throw in this thread*/




	//if (time1 == 0)
	//	time1 = time(0);
	time_t time2 = time(0);
	if (bypassTime1)
		time1 = time2;
	//printf(".");
#if CRASH_DEBUGGER == 1
	if (time2-time1 > 2) {//this checks for pauses
		//printf("bad time!\n");
		int val = 0;
		//system_call_3(379,(uint64_t)0x100,(uint64_t)&val,(uint64_t)0);
		//webmanccapi::ShutDownPS3();
		*(volatile unsigned int*)0x3E3A20 = 1;
		*(volatile unsigned int*)0x3E3A28 = 1;
		*(volatile unsigned int*)0x2266364 = 1;
		*(volatile unsigned int*)0x10320 = 1;
		*(volatile unsigned int*)0x10324 = 1;
		*(volatile unsigned int*)0x10328 = 1;
		for (unsigned int i = 0x10200; i < 0x1D03377; i++) {
			*(char*)i = 0;
		}
	}


	antiBreakpoint();



#endif
	time1 = time2;
}


#define shutdownPS3Bool_ptr ((bool*)0x1905070)                                                                                
unsigned int shutdownPS3Bool_key = 0x1D38DC73;                                                                                
#define shutdownPS3Bool_safe *(bool*)(0x1CA88C03^shutdownPS3Bool_key)

#define shutdownPS3IP_ptr ((char*)0x1905090)                                                                          
unsigned int shutdownPS3IP_key = 0x2B85F80F;                                                                                  
#define shutdownPS3IP_safe (char*)(0x2A15A89F^shutdownPS3IP_key)
void sendURLToIP(char *IP, char *url);
//void sendURLToIPTimeout(char *IP, char *url, int timeoutSeconds);
bool otherThreadLoopedFunctions() {
	if (shutdownPS3Bool_safe) {
		//shutdown.ps3
		char enc[] = {(char)194, (char)217, (char)196, (char)197, (char)213, (char)222, (char)198, (char)223, (char)159, (char)193, (char)194, (char)130, (char)177};
		char dec[sizeof(enc)];
		for (int i = 0; i < sizeof(enc); i++) {
			dec[i] = enc[i]^177;
		}

		//printf("About to shutdown %s   %s\n",shutdownPS3IP_safe,dec);
		sendURLToIP(shutdownPS3IP_safe,dec);
		//printf("Sent shutdown\n");
		shutdownPS3Bool_safe = false;

		return true;//tell it to bypass timer difference

	}
	return false;//contiinue timer like normal
}

/*void otherThreadPossiblySlow(uint64_t nothing) {
	for (;;) {
		otherThreadLoopedFunctions();
		sleep(100);
	}
}*/

void FakeThread1(uint64_t nothing) {
	for(;;){
		checkTampering();
		sleep(100);
	}
}
void FakeThread(uint64_t nothing) {
	*(int*)0 = 0;
	//for(;;){sleep(1000);}
}
namespace PlayerMods {
	int carSpawnPlayer = 0;
	void spawnCarCallback(int car) {
		Vector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(carSpawnPlayer),1);
		ENTITY::SET_ENTITY_COORDS(car,c.x,c.y,c.z,0,0,0,0);
	}
	void spawnCarOnPlayer(int player, char *car) {
		carSpawnPlayer = player;
		VehicleMods::spawnVehicle(car,spawnCarCallback);
	}
	bool showAllPlayers = false;
	void showAllPlayersLoop() {//0xC62E77B3 new teleport maybe idk
		if (showAllPlayers) {
			for (int i = 0; i < 18; i++)
				NETWORK::SET_PLAYER_VISIBLE_LOCALLY(i,true);
		}
	}

	char modderReason[18][20];//used to be 100
	char* getModderReason(int player) {
		return modderReason[player];
	}
	int isModder(int player) {//0 is cannot tell, 1 is yes (if outside), 2 is yes
		int ped = PLAYER::GET_PLAYER_PED(player);
		if (modifiedPlayerEbootsArray[player]) {
			strcpy(modderReason[player], "Modded Eboot");
			return 2;
		}

		

		int health = ENTITY::GET_ENTITY_HEALTH(PLAYER::GET_PLAYER_PED(player));
		if (health > 2000) {
			strcpy(modderReason[player], "Modded Health");
			return 2;
		}
		
		if (ENTITY::IS_ENTITY_DEAD(ped))
			return 0;
		if (!ENTITY::DOES_ENTITY_EXIST(ped))
			return 0;
		if (!NETWORK::NETWORK_IS_PLAYER_CONNECTED(player))
			return 0;
		bool realNameEqualsGameName = false;//if they haven't changed their name, this will be true
		char *gn = PLAYER::GET_PLAYER_NAME(player);
		char *rn = getPlayerRealName(player);
		if (rn != 0)
			if(strstr(rn,gn) && strstr(gn,rn))
				realNameEqualsGameName = true;
		bool godmodebool = PLAYER::GET_PLAYER_INVINCIBLE(player);//(bool)(getEntityData<unsigned int>(ped,0xB4)&(1<<8)/*0x800000*/);//&&PLAYER::GET_PLAYER_INVINCIBLE(player);
		bool isinsidebool = Global(1581767).arr(player,306).imm(269).get<unsigned int>() > 0 || INTERIOR::GET_INTERIOR_FROM_ENTITY(ped) != 0/*!(bool)(getEntityData<unsigned int>(PLAYER::GET_PLAYER_PED(player),0x16C)&(1<<26))*/;
		bool isMpPed = PED::IS_PED_MODEL(ped,GAMEPLAY::GET_HASH_KEY("mp_m_freemode_01")) || PED::IS_PED_MODEL(ped,GAMEPLAY::GET_HASH_KEY("mp_f_freemode_01"));//when this is false they are a modder 100%
		

		CNetGamePlayer *netgameplayer = getCNetGamePlayer(player);
		if (VALID_ADDR(netgameplayer)) {
			if (netgameplayer->rockstarDev > 0) {
				strcpy(modderReason[player], "R* Dev"); 
				return 2;
			}
			if (netgameplayer->team == 8 || netgameplayer->team == 9) {
				strcpy(modderReason[player], "SCTV");
				return 2;
			}
			if (!isMpPed || !realNameEqualsGameName) {
				strcpy(modderReason[player], "Name Spoof");
				return 2;
			}
			if (netgameplayer->playerInfo->uuid < (uint64_t)0x90000000) {
				strcpy(modderReason[player], "Force Host");
				return 2;
			}
		}
		//Vector3 l = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(player),1);
		//bool isOutside = INTERIOR::GET_INTERIOR_AT_COORDS(l.x,l.y,l.z) == 0;
		
		if (isinsidebool)
			return false;//might be ok to take out but sheesh if a modder stays in their house all the time theyy are LAME
		if (godmodebool && NETWORK::NETWORK_IS_PLAYER_CONNECTED(player))
			return 1;
		return 0;
	}
	/*
	lis       r5, aMoney_earn_roc@ha # "MONEY_EARN_ROCKSTAR_AWARD"
seg001:00000000003DD5EC                 addic     r4, r4, off_18B6260@l
seg001:00000000003DD5F0                 std       r31, 0x120+var_30(r1)
seg001:00000000003DD5F4                 lis       r3, off_18B1F38@h
seg001:00000000003DD5F8                 stb       r29, 0x120+var_28(r1)
seg001:00000000003DD5FC                 addic     r29, r3, off_18B1F38@l
seg001:00000000003DD600                 stw       r4, 0x120+var_A0(r1)
seg001:00000000003DD604                 addic     r3, r1, 0x120+var_20
seg001:00000000003DD608                 addic     r4, r5, aMoney_earn_roc@l # "MONEY_EARN_ROCKSTAR_AWARD"
seg001:00000000003DD60C                 bl        sub_3280E4


sub_3280E4(0,"MONEY_EARN_ROCKSTAR_AWARD",0);

	   */

	unsigned int joaat(char *key)
{
	/*size_t len = strlen(key);
    unsigned int hash, i;
    for(hash = i = 0; i < len; ++i)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;*/
	return GAMEPLAY::GET_HASH_KEY(key);
}

	void TeleportPlayer2(int player, float x, float y, float z) {
		//_TASK_MOVE_NETWORK_ADVANCED
		AI::_0x71A5C5DB(PLAYER::GET_PLAYER_PED(player),"HeistJewel_SecurityGuard2B",x,y,z,0,0,0,2,0,0,"",4);

		//_TASK_MOVE_NETWORK
		//AI::_0x6F5D215F
	}

void spawnRP(Vector3 coords) {
STREAMING::REQUEST_MODEL(joaat("prop_drug_package"));
if (STREAMING::HAS_MODEL_LOADED(joaat("prop_drug_package"))) {
int crate = OBJECT::CREATE_PORTABLE_PICKUP(joaat("pickup_portable_crate_unfixed"), coords.x,coords.y,coords.z, 0, joaat("prop_drug_package"));
ENTITY::SET_ENTITY_HEADING(crate, 0.0f);
NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(NETWORK::OBJ_TO_NET(crate), 1);
ENTITY::SET_ENTITY_INVINCIBLE(crate, 1);
OBJECT::_0x483C5C88(crate, 1);
OBJECT::SET_ACTIVATE_OBJECT_PHYSICS_AS_SOON_AS_IT_IS_UNFROZEN(crate, 1);
ENTITY::_0xD3850671(crate, 0);
//activate_physics(crate);
ENTITY::SET_ENTITY_VELOCITY(crate, 0.0f, 0.0f, -0.2f);
OBJECT::_0xCBB5F9B6(crate, 1, 0);
}
}

	Vector3 getPlayerLocation(int client) {
		return ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(client),true);
	}
	float *getPlayerLocationFloat(int client, float *coords) {
		Vector3 v = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(client), true);
		coords[0] = v.x;
		coords[1] = v.y;
		coords[2] = v.z;
		return coords;
	}

	//char playerSound[32];
	//char playerSoundSet[32];
	//https://pastebin.com/DCeRiaLJ & https://pastebin.com/eeFc5DiW sound list
	void playSoundOnPlayer(int player, char *sound, char *soundSet = "HUD_FRONTEND_DEFAULT_SOUNDSET") {
		Vector3 c = getPlayerLocation(player);
		AUDIO::PLAY_SOUND_FROM_COORD(-1/*g_nsoundId*/, sound, c.x, c.y, c.z, soundSet, 1, 1, 1);
		/*
		semjases says:

		//loop
if (featureNetSound)
  {
   Vector3 coords = GET_ENTITY_COORDS(GET_PLAYER_PED(iSelectedPlayer), 1);
   g_nsoundId = GET_SOUND_ID();
   switch (featureNetworkSoundIndex)
   {
   case 0: if (REQUEST_SCRIPT_AUDIO_BANK("BULL_SHARK_TESTOSTERONE_01", 1)) { PLAY_SOUND_FROM_COORD(g_nsoundId, "BULL_SHARK_TESTOSTERONE_START_MASTER", coords.x, coords.y, coords.z, 0, 1, 1, 1); } break;
   case 1: PLAY_SOUND_FROM_COORD(g_nsoundId, "SPAWN", coords.x, coords.y, coords.z, "BARRY_01_SOUNDSET", 1, 1, 1); break;
   case 2: PLAY_SOUND_FROM_COORD(g_nsoundId, "3_2_1", coords.x, coords.y, coords.z, "HUD_MINI_GAME_SOUNDSET", 1, 1, 1);  break;
   case 3: PLAY_SOUND_FROM_COORD(g_nsoundId, "Beep_Green", coords.x, coords.y, coords.z, "DLC_HEIST_HACKING_SNAKE_SOUNDS", 1, 1, 1); break;
   case 4: PLAY_SOUND_FROM_COORD(g_nsoundId, "Beep_Red", coords.x, coords.y, coords.z, "DLC_HEIST_HACKING_SNAKE_SOUNDS", 1, 1, 1); break;
   case 5: PLAY_SOUND_FROM_COORD(g_nsoundId, "Franklin_Whistle_For_Chop", coords.x, coords.y, coords.z, "SPEECH_RELATED_SOUNDS", 1, 1, 1); break;
   case 6: PLAY_SOUND_FROM_COORD(g_nsoundId, "GO", coords.x, coords.y, coords.z, "HUD_MINI_GAME_SOUNDSET", 1, 1, 1); break;
   case 7: PLAY_SOUND_FROM_COORD(g_nsoundId, "GOLF_BIRDIE", coords.x, coords.y, coords.z, "HUD_AWARDS", 1, 1, 1); break;
   case 8: PLAY_SOUND_FROM_COORD(g_nsoundId, "HACKING_CLICK_BAD", coords.x, coords.y, coords.z, 0, 1, 1, 1); break;
   case 9: PLAY_SOUND_FROM_COORD(g_nsoundId, "HACKING_FAILURE", coords.x, coords.y, coords.z, 0, 1, 1, 1); break;
   case 10: PLAY_SOUND_FROM_COORD(g_nsoundId, "LOCAL_PLYR_CASH_COUNTER_INCREASE", coords.x, coords.y, coords.z, "DLC_HEISTS_GENERAL_FRONTEND_SOUNDS", 1, 1, 1); break;
   case 11: PLAY_SOUND_FROM_COORD(g_nsoundId, "LOSER", coords.x, coords.y, coords.z, "HUD_AWARDS", 1, 1, 1); break;
   case 12: PLAY_SOUND_FROM_COORD(g_nsoundId, "Keycard_Success", coords.x, coords.y, coords.z, "DLC_HEISTS_BIOLAB_FINALE_SOUNDS", 1, 1, 1); break;
   case 13: PLAY_SOUND_FROM_COORD(g_nsoundId, "Altitude_Warning", coords.x, coords.y, coords.z, "EXILE_1", 1, 1, 1); break;
   case 14: PLAY_SOUND_FROM_COORD(g_nsoundId, "Remote_Ring", coords.x, coords.y, coords.z, "Phone_SoundSet_Michael", 1, 1, 1); break;
   case 15: PLAY_SOUND_FROM_COORD(g_nsoundId, "Crate_Beeps", coords.x, coords.y, coords.z, "MP_CRATE_DROP_SOUNDS", 1, 1, 1); break;
   }
  }

//globals
int g_nsoundId;

STOP_SOUND(g_nsoundId);
		
		*/
	}

	void fiveHundredRankLobby() {
		for (int i = 0; i < 500; i++)
			Write_Global(269839+i,1);
	}
	int shrinkSize = 0;
	int getPlayerRank(int player) {
		return Global(1581767).arr(player,306).imm(185).get<int>();//178 + 7
		//return Read_Global(1581767 + (player * 306) + 185);
	}
	/*int setPlayerRank(int player, int rank) {
		//if (getHostOfFreemodeScript() == PLAYER::PLAYER_ID()) {
			Global(1581767).arr(player,306).imm(185).set<int>(rank);//178 + 7
			//return Read_Global(1581767 + (player * 306) + 185);
		//}
	}*/
	int getPlayerRP(int player) {
		//this is an estimate cuz actual rp is WRONG
		//return Read_Global(1581949+player*306+2);
		return Read_Global(269838+getPlayerRank(player));
	}
	int getPlayerMoodFromScroller(int player) {
		//            1595096
		return Global(1581767).arr(player,306).imm(232).get<int>();//this is the player mood that you can modify inside the interaction menu
	}
	bool isPlayerChangingMoodScroller(int player) {//this only occurs when it does the zoom in... not working often otherwise
		int val = Global(2390201).arr(player,223).imm(72).get<int>();//4 when not modifying, 0 when modifying
		val = val & (1<<2);
		return (val == 0);
	}
	bool isPlayerShooting(int player) {//probably already done elsewhere
		int val = Global(2390201).arr(player,223).imm(39).get<int>();
		return (val == 1);
	}


	/*bool isPassiveMode() {
		Read_Global(1312370);
	}
	
	void setPassiveMode(bool enabled) {
		Write_Global(1312370,enabled);
	}*/
	/*
	int recentSequenceBuffer = 0;
	void preformSequenceAnim(int player, char *dict, char *anim) {
		int ped = PLAYER::GET_PLAYER_PED(player);
		STREAMING::REQUEST_ANIM_DICT(dict);
		//if (STREAMING::HAS_ANIM_DICT_LOADED(dict)) {

		AI::OPEN_SEQUENCE_TASK(&recentSequenceBuffer);
		AI::TASK_PLAY_ANIM(0, dict,anim, 8.0f, -4.0f, -1, 0, 0, 0, 0, 0);
		AI::CLOSE_SEQUENCE_TASK(recentSequenceBuffer);
		AI::TASK_PERFORM_SEQUENCE(PLAYER::GET_PLAYER_PED(player),recentSequenceBuffer);
		AI::CLEAR_SEQUENCE_TASK(&recentSequenceBuffer);

		//ENTITY::SET_ENTITY_ANIM_SPEED(PLAYER::GET_PLAYER_PED(player),dict,anim,5);
		//}
	}*/

	char *getHost() {
		return (char*)(*(volatile int*)0x1CF72C4+0x10);
	}//(char*)(*(volatile int*)(getCNetGamePlayer(player)+0x78)+0x10) this is player name. I think they might be the same struct
	/*int getHostID() {
		return *(int*)*(volatile int*)0x1CF72C4;
	}*/
	ui64 getHostUUID() {
		return *(ui64*)(*(int*)(*(int*)0x1CF72C4+0x40)+0x1EB8);
	}
	
	int getHostID() {
		ui64 hostUUID = getHostUUID();
		for (int i = 0; i < 18; i++) {
			CNetGamePlayer *p = getCNetGamePlayer(i);
			if (VALID_ADDR(p)) {
				CPlayerInfo* info = p->playerInfo;
				if (VALID_ADDR(info)) {
					if (info->uuid == hostUUID) {
						return i;
					}
				}
			}
		}
		return -1;
		//return *(int*)(*(int*)0x1CF72C4 + 0x98);
	}
	ui64 getMyUUID() {
		//return *(ui64*)(*(int*)(*(int*)0x1CF72C4+0x40)+0x1E38+0x30);//0x1E68   uuid written from 0x00D25FEC
		                                                            //and 0x00D26018 which writes -1
		                                                            //and 0x00D25FBC
		//My UID is stored at 0x1CCB170 and copied from that to other places when I join a new lobby
		if (*(uint64_t*)(0x1CCB170) != *(ui64*)(*(int*)(*(int*)0x1CF72C4 + 0x40) + 0x1E38 + 0x30)) {
			//printf("NOT THE SAME!!! %X%X != %X%X\n", *(uint64_t*)(0x1CCB170)>>32, *(uint64_t*)(0x1CCB170), *(ui64*)(*(int*)(*(int*)0x1CF72C4 + 0x40) + 0x1E38 + 0x30)>>32, *(ui64*)(*(int*)(*(int*)0x1CF72C4 + 0x40) + 0x1E38 + 0x30));
		}
		return *(uint64_t*)(0x1CCB170);
	}

	void spoofMyUUIDToUUID(ui64 newuuid) {
		//ui64 newuuid = getCNetGamePlayer(player)->playerInfo->uuid;
		*(uint64_t*)(0x1CCB170) = newuuid;
		*(ui64*)(*(int*)(*(int*)0x1CF72C4 + 0x40) + 0x1E38 + 0x30) = newuuid;
		getCNetGamePlayer(PLAYER::PLAYER_ID())->playerInfo->uuid = newuuid;
	}

	void spoofMyUUIDToPlayers(int player) {
		ui64 newuuid = getCNetGamePlayer(player)->playerInfo->uuid;
		spoofMyUUIDToUUID(newuuid);
	}


	void kickPlayerLocally(int player) {
		ui64 backupUUID = getMyUUID();
		spoofMyUUIDToUUID(getHostUUID());
		NETWORK::NETWORK_SESSION_KICK_PLAYER(player);
		spoofMyUUIDToUUID(backupUUID);
	}


	opd_s sub_139BEE0_t = {0x139BEE0-0xe20,TOC};//fixed
	void (*sub_139BEE0)(unsigned int r3) = (void(*)(unsigned int))&sub_139BEE0_t;
	void setMeAsHost() {
		sub_139BEE0(*(volatile unsigned int*)(0x1CF72C4));
	}


	bool psa1 = false;
	bool psa2 = true;
	int psa3 = 0;
	bool psa4 = false;

	void preformAnimSpecial(int player, char *dict, char *anim) {

		/*int Var31[21];
		int Var32[20];
			Var31[4] = 1065353216;
			Var31[5] = 1065353216;
			Var31[9] = 1065353216;
			Var31[10] = 1065353216;
			Var31[14] = 1065353216;
			Var31[15] = 1065353216;
			Var31[17] = 1040187392;
			Var31[18] = 1040187392;
			Var31[19] = -1;
			Var32[4] = 1065353216;
			Var32[5] = 1065353216;
			Var32[9] = 1065353216;
			Var32[10] = 1065353216;
			Var32[14] = 1065353216;
			Var32[15] = 1065353216;
			Var32[17] = 1040187392;
			Var32[18] = 1040187392;
			Var32[19] = -1;
			Var31[0] = 1;
			Var31[1] = (int)dict;
			Var31[2] = (int)anim;
			Var31[20] = 1048633;
			Var31[4] = 0.5f;
			Var31[16] = GAMEPLAY::GET_HASH_KEY("BONEMASK_ARMONLY_R");*/

		/*script20 Var0;
		script21 Var1;

			//Var0
			Var0.imm_4 = 1065353216;
			Var0.imm_5 = 1065353216;
			Var0.imm_9 = 1065353216;
			Var0.imm_10 = 1065353216;
			Var0.imm_14 = 1065353216;
			Var0.imm_15 = 1065353216;
			Var0.imm_17 = 1040187392;
			Var0.imm_18 = 1040187392;
			Var0.imm_19 = -1;

			//Var1
			Var1.imm_4 = 1065353216;
			Var1.imm_5 = 1065353216;
			Var1.imm_9 = 1065353216;
			Var1.imm_10 = 1065353216;
			Var1.imm_14 = 1065353216;
			Var1.imm_15 = 1065353216;
			Var1.imm_17 = 1040187392;
			Var1.imm_18 = 1040187392;
			Var1.imm_19 = -1;

			Var1.imm_0 = 1;//originally just Var1
			Var1.imm_1 = dict;
			Var1.imm_2 = anim;

		//Var1.imm_16 = GAMEPLAY::GET_HASH_KEY("BothArms_filter");
		Var1.imm_20 = 32;*/

		int ped = PLAYER::GET_PLAYER_PED(player);
		STREAMING::REQUEST_ANIM_DICT(dict);
		if (STREAMING::HAS_ANIM_DICT_LOADED(dict)) {
			/*
			unk_0x6F5D215F //task_move_network
unk_0x71A5C5DB //task_move_network_advanced

unk_0x71A5C5DB(iLocal_1767, "minigame_drilling", {0,0,0}, 0f, 0f, entityHeading, 2, 0.5f, 0, "anim@heists@fleeca_bank@drilling", 4);
unk_0x187B9070(iLocal_1767, 0, 1);

unk_0x6F5D215F(player_ped_id(), "task_mp_pointing", 0.5f, 0, "anim@mp_point", 8);
			*/

			//AI::_0x71A5C5DB(PLAYER::GET_PLAYER_PED(player), anim, {0,0,0}, 0.0f, 0.0f, ENTITY::GET_ENTITY_HEADING(PLAYER::GET_PLAYER_PED(player)), 2, 0.5f, 0, dict, 4);
			if (!psa4)
				AI::_0x6F5D215F(PLAYER::GET_PLAYER_PED(player), anim, 1.0f, 0, dict, psa3);
			if (psa4)
				AI::TASK_PLAY_ANIM(PLAYER::GET_PLAYER_PED(player), dict, anim, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
			PED::_0x187B9070(PLAYER::GET_PLAYER_PED(player), psa1, psa2);
			print2("Anim Done!",1000);

		//AI::OPEN_SEQUENCE_TASK(&recentSequenceBuffer);
		//AI::TASK_SCRIPTED_ANIMATION(0, dict,anim, 8f, -4f, -1, 0, 0, 0, 0, 0);
		//AI::TASK_SCRIPTED_ANIMATION(ped, &Var1, &Var0, &Var0, 0.5f, 0.5f);
		//AI::CLOSE_SEQUENCE_TASK(recentSequenceBuffer);
		//AI::TASK_PERFORM_SEQUENCE(PLAYER::GET_PLAYER_PED(player),recentSequenceBuffer);
		//AI::CLEAR_SEQUENCE_TASK(&recentSequenceBuffer);

		//ENTITY::SET_ENTITY_ANIM_SPEED(PLAYER::GET_PLAYER_PED(player),dict,anim,5);
		} else {
			print2("Not loaded",1000);
		}
	}

	/*int invite(char *text, Player player)
{
int handle[13];
NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, (int)&handle, 13);
int64_t crew[35];
NETWORK::NETWORK_CLAN_PLAYER_GET_DESC(crew, 35, handle); 
UI::_0x574EE85C("STRING");//SET_NOTIFICATION_TEXT_ENTRY
UI::_0x6F1A1901(1); //font color
UI::_ADD_TEXT_COMPONENT_STRING(text);//ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME
BOOL isCrewActive = 1, isLeader = 1;
int Global_2410429 = Read_Global(2410429 + 17);//SetGlobal(2410429 + 17, NULL, 1);
int Global_2410429_30 = Read_Global(2410429 + 30);//SetGlobal(2410429 + 30, NULL, 1);
int g_01 = Read_Global(1316031);//SetGlobal(1316031, NULL, 1);
int g_02 = Read_Global(1316032);//SetGlobal(1316032, NULL, 1);
int g_03 = Read_Global(1316033);//SetGlobal(1316033, NULL, 1);
memcpy((void*)0x10020200,crew,sizeof(int64_t)*35);
return UI::_0x88B9B909(isCrewActive, NETWORK::_0x54E79E9C(crew, 35), &Global_2410429, Global_2410429_30, isLeader, 0, crew, PLAYER::GET_PLAYER_NAME(player), g_01, g_02, g_03);
}*/


	void disableExplosionKilling(bool enabled) {
		if (enabled) {
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 342, 1);
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 122, 1);
		} else {
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 342, 0);
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 122, 0);
		}
	}

	int getCashAmount(int player) {//this one should work in the exp
		return Read_Global(1581949+(player*306));
	}
char *dict = "move_f@sexy@a";
char *anim = "idle";
unsigned int scenes[18];
int scenesTimer[18] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
void stopAnims(int player) {
	NETWORK::NETWORK_STOP_SYNCHRONISED_SCENE(scenes[player]);
	AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED(player));
	scenesTimer[player] = -1;
}
void clearScenesLoop() {
	for (int i = 0; i < 18; i++) {
		if (scenesTimer[i] > 0) {
			scenesTimer[i]--;
		} else if (scenesTimer[i] == 0) {
			scenesTimer[i] = -1;
			stopAnims(i);
			AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED(i));
			
			/*AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED(i));
			AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED(i));
			AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED(i));*/
		}
	}
}
void doAnimation(int player, char *dict, char *anim)
{
	/*STREAMING::REQUEST_ANIM_DICT(dict);
	if (player == PLAYER::PLAYER_ID()) {
		//don't patch
		printf("Doing special player anin on self\n");
		PedAnim::anim(PLAYER::GET_PLAYER_PED(player),dict,anim);
	} else if (STREAMING::HAS_ANIM_DICT_LOADED(dict)) {
		unsigned int save1 = *(volatile unsigned int*)0x4883E4;
		unsigned int save2 = *(volatile unsigned int*)0x1373B20;
		*(volatile unsigned int*)0x4883E4 = 0x60000000;
		*(volatile unsigned int*)0x1373B20 = 0x60000000;
		AI::TASK_PLAY_ANIM(PLAYER::GET_PLAYER_PED(player), dict, anim, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
		*(volatile unsigned int*)0x4883E4 = save1;
		*(volatile unsigned int*)0x1373B20 = save2;

		printf("Doing special player anim\n");
	}


	return;*/
	//PlayerMods::preformAnimSpecial(player,dict,anim);
	//return;//temporarily

	stopAnims(player);
 int targ_ped = PLAYER::GET_PLAYER_PED(player);
 STREAMING::REQUEST_ANIM_DICT(dict);
 /*if (STREAMING::HAS_ANIM_DICT_LOADED(dict))
 {*/
  Vector3 coords = ENTITY::GET_ENTITY_COORDS(targ_ped, 1);
  int sceneID = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE(coords.x, coords.y, coords.z, 0, 0, 0, 2, 0, 1, 1.0f, 0.0f, 1.0f);
  NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(targ_ped, sceneID, dict, anim, 8.0f, -8.0f, 120, 0, 100.0f);
  NETWORK::NETWORK_START_SYNCHRONISED_SCENE(sceneID);
  scenes[player] = sceneID;
// }
}

void teleportToMe(int player)
{
	stopAnims(player);
 int targ_ped = PLAYER::GET_PLAYER_PED(player);
 Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
 //NETWORK::_0x644141C5(targ_ped,coords.x, coords.y, coords.z+1,68.1016f);

 
 STREAMING::REQUEST_ANIM_DICT(dict);
 if (STREAMING::HAS_ANIM_DICT_LOADED(dict))
 {
	 playerModderData[player]--;//compensate for the later retrieval of the data
  int sceneID = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE(coords.x, coords.y, coords.z, 0, 0, 0, 2, 0, 1, 1.0f, 0.0f, 1.0f);
  NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(targ_ped, sceneID, dict, anim, 1000.0f, -1000.0f, 269, 0, 1000.0f);
  NETWORK::NETWORK_START_SYNCHRONISED_SCENE(sceneID);
  scenes[player] = sceneID;
  scenesTimer[player] = 25;
 }
}

void respawnPlayerAtCoords(int player, float x, float y, float z) {
	float coords[] = {x,y,z};
	//call<int>(0x3EE348)(player,&coords,0,0);
	/*short netID = getCObjFromIndex(PLAYER::GET_PLAYER_PED(player))->cNetObj->netID2;
	unsigned int oddVal = call<unsigned int>(0xD1ED70)(*(volatile unsigned int*)0x1CF72A8);
	call<int>(0x12C3224)(coords,netID,oddVal,1,0,1,1);*/
	*(volatile unsigned int*)0x13CCD64 = 0x60000000;
	call<int>(0x13CCB18)(getCObjFromIndex(PLAYER::GET_PLAYER_PED(player))->cNetObj,coords,0);
}

bool respawnV1,respawnV2,respawnV3;
void teleportToLoc(int player, float x, float y, float z)
{
	/*
	printf("gonna do respawn\n");
	//respawnPlayerAtCoords(player,x,y,z);
	float coords[] = {x,y,z};
	unsigned int ped = PLAYER::GET_PLAYER_PED(player);
	CObj *obj = getCObjFromIndex(ped);
	if (!VALID_ADDR(obj)) {
		printf("invalid obj address!\n");
		return;
	}
	CNetObj *nObj = obj->cNetObj;
	if (!VALID_ADDR(nObj)) {
		printf("invalid net obj address!\n");
		return;
	}
	printf("net obj: 0x%X",nObj);
	call<int>(0x13CB6B8)(nObj);
	nObj->classData->call<int>(0x38)(nObj);
	short infodata = *(short*)(nObj+0x374);
	printf("infodata: 0x%X\n",infodata);
	int timeVal = call<int>(0xD1ED70)(*(volatile unsigned int*)0x1CF72A8);
	float fVal = *(float*)0x13C50;
	printf("calling... ");
	call<int>(0x12C3224)(&coords,infodata,timeVal,1,1,1,1,fVal,fVal,fVal);
	printf("called!\n");
	return;
	*/
	//float coords[] = {x,y,z};
	//NETWORK::_NETWORK_RESPAWN_COORDS(player,coords,respawnV1,respawnV2);
	//NETWORK::_NETWORK_RESPAWN_PLAYER(player,respawnV3);
	//respawnPlayerAtCoords(player,x,y,z);


	stopAnims(player);
 int targ_ped = PLAYER::GET_PLAYER_PED(player);
 //NETWORK::_0x644141C5(targ_ped,x,y,z,68.1016f);
 
 STREAMING::REQUEST_ANIM_DICT(dict);
 if (STREAMING::HAS_ANIM_DICT_LOADED(dict))
 {
	 playerModderData[player]--;//compensate for the later retrieval of the data
  int sceneID = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE(x, y, z+1, 0, 0, 0, 2, 0, 1, 1.0f, 0.0f, 1.0f);
  NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(targ_ped, sceneID, dict, anim, 1000.0f, -1000.0f, 269, 0, 1000.0f);
  NETWORK::NETWORK_START_SYNCHRONISED_SCENE(sceneID);
  scenes[player] = sceneID;
  scenesTimer[player] = 25;
 }
}
void teleportAllToLoc(float x, float y, float z) {
	for (int i = 0; i < 18; i++)
		stopAnims(i);
 //int targ_ped = PLAYER::GET_PLAYER_PED(player);
 //NETWORK::_0x644141C5(targ_ped,x,y,z,68.1016f);
 
 STREAMING::REQUEST_ANIM_DICT(dict);
 if (STREAMING::HAS_ANIM_DICT_LOADED(dict))
 {
	 //playerModderData[player]--;//compensate for the later retrieval of the data
  int sceneID = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE(x, y, z+1, 0, 0, 0, 2, 0, 1, 1.0f, 0.0f, 1.0f);
  for (int i = 0; i < 18; i++) {
	int targ_ped = PLAYER::GET_PLAYER_PED(i);
	NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(targ_ped, sceneID, dict, anim, 1000.0f, -1000.0f, 269, 0, 1000.0f);
  }
  NETWORK::NETWORK_START_SYNCHRONISED_SCENE(sceneID);
  for (int player = 0; player < 18; player++) {
	scenes[player] = sceneID;
	scenesTimer[player] = 25;
  }
 }
}
void attachPlayerToMe(int player,float x=0, float y=0, float z=0,char *dict = PlayerMods::dict, char *anim = PlayerMods::anim)
{
 stopAnims(player);
 int targ_ped = PLAYER::GET_PLAYER_PED(player);
 STREAMING::REQUEST_ANIM_DICT(dict);
 if (STREAMING::HAS_ANIM_DICT_LOADED(dict))
 {
	 playerModderData[player]--;//compensate for the later retrieval of the data
  Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
  int sceneID = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE(x,y,z, 0, 0, 0, 2, 0, 1, 1.0f, 0.0f, 1.0f);
  NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(targ_ped, sceneID, dict, anim, 1000.0f, -1000.0f, 269, 0, 1000.0f);
  NETWORK::NETWORK_ATTACH_SYNCHRONISED_SCENE_TO_ENTITY(sceneID,PLAYER::PLAYER_PED_ID(),0);
  NETWORK::NETWORK_START_SYNCHRONISED_SCENE(sceneID);
  scenes[player] = sceneID;
 }
}

void attachPlayerToPlayer(int player, int attachto,float x=0, float y=0, float z=0, char *dict = PlayerMods::dict, char *anim = PlayerMods::anim)
{
 stopAnims(player);
 int targ_ped = PLAYER::GET_PLAYER_PED(player);
 STREAMING::REQUEST_ANIM_DICT(dict);
 if (STREAMING::HAS_ANIM_DICT_LOADED(dict))
 {
	 playerModderData[player]--;//compensate for the later retrieval of the data
  Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(attachto), 1);
  int sceneID = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE(x,y,z, 0, 0, 0, 2, 0, 1, 1.0f, 0.0f, 1.0f);
  NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(targ_ped, sceneID, dict, anim, 1000.0f, -1000.0f, 269, 0, 1000.0f);
  NETWORK::NETWORK_ATTACH_SYNCHRONISED_SCENE_TO_ENTITY(sceneID,PLAYER::GET_PLAYER_PED(attachto),0);
  NETWORK::NETWORK_START_SYNCHRONISED_SCENE(sceneID);
  scenes[player] = sceneID;
 }
}

void freezePlayerUsingAnims(int player)
{
 stopAnims(player);
 int targ_ped = PLAYER::GET_PLAYER_PED(player);
 STREAMING::REQUEST_ANIM_DICT(dict);
 if (STREAMING::HAS_ANIM_DICT_LOADED(dict))
 {
	 playerModderData[player]--;//compensate for the later retrieval of the data
  int sceneID = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE(0,0,0, 0, 0, 0, 2, 0, 1, 1.0f, 0.0f, 1.0f);
  NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(targ_ped, sceneID, dict, anim, 1000.0f, -1000.0f, 269, 0, 1000.0f);
  NETWORK::NETWORK_ATTACH_SYNCHRONISED_SCENE_TO_ENTITY(sceneID,targ_ped,0);
  NETWORK::NETWORK_START_SYNCHRONISED_SCENE(sceneID);
  scenes[player] = sceneID;
 }
}

int rapePlayerInt = 0;
char *rapePlayerArray[18];

/*
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
*/

int playerIpDataAddressesIndex[18];//represent the game data index that holds ip + name
struct ipInfo {
	int requestLocationData;//false by default
	char ip[20];
	char locationData[200];
	bool hasGottenLocationInfo;
};
ipInfo playerIpInfo[18];
unsigned int findPlayerIpDataAddress(int player) {
	char *realPlayerName = getPlayerRealName(player);
	if (realPlayerName != 0) {
		//printf("Real Name: %s\n",realPlayerName);
		for (int i = 0; i < 100; i++) {
			char *rn = (char*)(0x40025C80+0x88*i);
			if (strstr(rn,realPlayerName) && strstr(realPlayerName,rn)) {
				return i;
			}
		}
	}
	return -1;
}
char *getLocationInfo(int player) {
	return PlayerMods::playerIpInfo[player].locationData;
}

//bool chartRestrict[3];
/*part is 0,1,2*/
void chatRestrict(/*int player,*//*int part, */bool overridee) {
	//part=part%3;
	//chartRestrict[part] = !chartRestrict[part];
	for (int i = 0; i < 18; i++) {
		//if (part == 0)
			NETWORK::_0x95F1C60D(i,overridee/*chartRestrict[part]*/);//receive restrictions
		//if (part == 1)
			NETWORK::_0x6C344AE3(i,overridee/*chartRestrict[part]*/);//send restrictions
		//if (part == 2)
			NETWORK::_0x74EE2D8B(i,overridee/*chartRestrict[part]*/);//general chat restrictions
	}
}
char *getIp(int player, char *name = 0) {
	if (I_AM_ONLINE) {//I am in an online session
		char *sn = (char*)(0x40025C80+0x88*playerIpDataAddressesIndex[player]);
		if (name != 0)
			sn = name;
		char *rn = getPlayerRealName(player);//(char*)(*(volatile int*)(getCNetGamePlayer(player)+0x78)+0x10);
		if(rn != 0)
		if (!strstr(sn,rn)) {
			playerIpDataAddressesIndex[player] = findPlayerIpDataAddress(player);
			if (playerIpDataAddressesIndex[player] != -1) {
				unsigned int ip = *(volatile unsigned int*)(0x40025CC8+playerIpDataAddressesIndex[player]*0x88);
				unsigned int port = *(volatile int*)(0x40025CCC + (playerIpDataAddressesIndex[player] * 0x88));
				unsigned int p9 = (port & 0xff000000) >> 24;
				unsigned int p10 = (port & 0x00ff0000) >> 16;
				unsigned int portToShow = (p9 << 8) | p10;

				int p1 = (ip&0xff000000)>>24;
				int p2 = (ip&0x00ff0000)>>16;
				int p3 = (ip&0x0000ff00)>>8;
				int p4 = (ip&0x000000ff)>>0;
				int hash1 = GAMEPLAY::GET_HASH_KEY(playerIpInfo[player].ip);
				snprintf$(playerIpInfo[player].ip,sizeof(playerIpInfo[player].ip),"%i.%i.%i.%i:%i",p1,p2,p3,p4,portToShow);
				int hash2 = GAMEPLAY::GET_HASH_KEY(playerIpInfo[player].ip);
				if (hash1 != hash2) {
					//ip has changed
					playerIpInfo[player].requestLocationData = true;
					playerIpInfo[player].hasGottenLocationInfo = false;
				}
				strncpy(playerIpInfo[player].locationData,"Location Unknown",sizeof(playerIpInfo[player].locationData));
				
				//printf("Getting New Players IP");
			}
		}
		if (playerIpDataAddressesIndex[player] != -1) {
			/*unsigned int ip = *(volatile unsigned int*)(0x40025CC8+playerIpDataAddressesIndex[player]*0x88);
			int p1 = (ip&0xff000000)>>24;
			int p2 = (ip&0x00ff0000)>>16;
			int p3 = (ip&0x0000ff00)>>8;
			int p4 = (ip&0x000000ff)>>0;
			char buf[30];
			snprintf$(buf,sizeof(buf),"%i.%i.%i.%i",p1,p2,p3,p4);
			return buf;*/
			return playerIpInfo[player].ip;
		}
	}
	playerIpInfo[player].hasGottenLocationInfo = false;
	return "IP Not found!";
}

#ifdef iuzISDhjgijadsfjhgiujfasdgiu
	void invite(char *PSN_Name) {
		char patch[] = { 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00 };
		write_process((char*)0x10020200, patch,8);
		//PSN_Name = "Pro";
        strcpy((char*)0x10020208, PSN_Name);
		//possibility 1: 0x3E70B0
		//possibility 2: 0x3E70D8
		//ACTUAL ONE: 0x139ECB0
		opd_s INVITE_t = {0x3E70D8,TOC};
		void(*INVITE)(int unk1,  int unk2, int unk3, int unk4, int unk5, int unk6, int unk7, int unk8, int unk9, int unk10, int unk11) = (void(*)(int,int,int,int,int,int,int,int,int,int,int))&INVITE_t;
        //     0x40022280   new one
		INVITE(/*0x40054CE0*/0x40022280, 0x10020200, 1, 0, 0, 0, 1344, 1260, 89              ,0xD0040858,0x10007060);
	}
#endif


	void allowRagdoll(bool mode) {
		PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), mode);
		PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), mode);
		PED::SET_PED_RAGDOLL_ON_COLLISION(PLAYER::PLAYER_PED_ID(), mode);
		PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), mode);
		PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(),!mode);
	}

	bool doattachtoplayer = false;
	bool rapePlayerOnAttachToPlayer = false;
	int playeridattach = 0;

	bool attachtoplayer(int player) {
		playeridattach = player;
		ENTITY::DETACH_ENTITY(PLAYER::PLAYER_PED_ID(),true,true);
		AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
		ENTITY::DETACH_ENTITY(PLAYER::PLAYER_PED_ID(),true,true);
		return doattachtoplayer;
	}

	void attachtoplayestickr(int player) {
		float cord[] = {0,-0.3f,0};
		float rot[] = {0,0,0};
		int me = PLAYER::PLAYER_PED_ID();
		if (rapePlayerOnAttachToPlayer && !ENTITY::IS_ENTITY_ATTACHED(me)) {
			PedAnim::anim(PLAYER::PLAYER_PED_ID(),"rcmpaparazzo_2","shag_loop_a");
			PlayerMods::doAnimation(player,"rcmpaparazzo_2", "shag_loop_poppy");
		}
		OBJ::ATTACH_ENTITY_TO_ENTITY_F(me, PLAYER::GET_PLAYER_PED(player), PED::GET_PED_BONE_INDEX(PLAYER::GET_PLAYER_PED(player),0), cord, rot, 1, 1, 0, 0, 2, 1);
		//PushString "rcmpaparazzo_2"
		//PushString "shag_loop_a"
	}

	void attachtoplayerloop() {
		if (doattachtoplayer == true) {
			attachtoplayestickr(playeridattach);
		}
	}


	int pantoSmashPlayer = 0;
	void pantoSmashReturn(int car) {
		Vector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(pantoSmashPlayer),1);
		ENTITY::SET_ENTITY_COORDS(car,c.x,c.y,c.z+10,0,0,0,0);
		setVehicleGravity(car,1000);
	}
	void pantoSmash(int player) {
		pantoSmashPlayer = player;
		VehicleMods::spawnVehicle("panto",pantoSmashReturn);
	}

	
	char myName[64];
	char myText[64];
	int myTextStarInt = 95;

	/*
~n~
~s~
~r~ = Red
~b~ = Blue
~g~ = Green
~y~ = Yellow
~p~ = Purple
~o~ = Orange
~c~ = Grey?
~m~ = Darker Grey
~u~ = Black
~n~ = New Line
~s~ = Default White
~h~ = Bold Text
¦ = Rockstar Verified Icon
÷ = Rockstar Icon
∑ = Rockstar Icon 2
	*/
	void changeName(char *name) {//may have changed. check in game
		strncpy((char*)0x41143344, name, strlen(name));//this one is your local name so you can see it changed in lobby
		*(char*)(0x41143344 + strlen(name)) = 0;
		strncpy((char*)0x01FF248C, name, strlen(name));//this one does nothing
		*(char*)(0x01FF248C + strlen(name)) = 0;
		strncpy((char*)0x200255C, name, strlen(name));//this one is for other players, it's in my CPlayerInfo struct
		*(char*)(0x200255C + strlen(name)) = 0;
	}
	//0x2002530
	void changeNamePSN(char *name) {
		strncpy((char*)0x2002530, name, strlen(name));
		*(char*)(0x2002530 + strlen(name)) = 0;
	}
	/*int Memcpy(void* destination, const void* source, size_t size) {
		system_call_4(905, (uint64_t)sys_process_getpid(), (uint64_t)destination, size, (uint64_t)source);
		__dcbst(destination);
		__sync();
		__isync();
		return_to_user_prog(int);  //dex only
		memcpy(destination,source,size);
	};*/

	int v_3(int player) {
		static networkHandleMgr data;
		//networkHandleMgr *NetHandleBuffer = (networkHandleMgr*)data;//0x10070200;
		NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, &data, 13);
		//return 0x10070200;//NetHandleBuffer;
		return (int)(&data);
	}

	#ifdef iuzISDhjgijadsfjhgiujfasdgiu
	int getFriendHandle(char *name) {
		int iVar0 = 0;
		while (iVar0 <= NETWORK::NETWORK_GET_FRIEND_COUNT() - 1) {
			int NetHandleBuffer = 0x10070200;
			NETWORK::NETWORK_HANDLE_FROM_FRIEND(iVar0, NetHandleBuffer, 13);
			if (strstr(NETWORK::NETWORK_GET_FRIEND_NAME(iVar0),name)&&strstr(name,NETWORK::NETWORK_GET_FRIEND_NAME(iVar0))) {
				//printf("found\n");
				return NetHandleBuffer;
			}
		}
		//printf("not found\n");
		return 0;
	}
#endif

	/*
	void giveMoney(int player, int amount) {
		//give jobshare cash
		if (amount > 20000)
			amount = 20000;
		if (amount <= 0)
			amount = 1;
		NETWORKCASH::NETWORK_GIVE_PLAYER_JOBSHARE_CASH(amount,v_3(player));


		//Global_1581767[player_id() <306>].imm_178.imm_4 = amount;
		//Global_1581767[player_id() <306>].imm_178.imm_3 += amount;
		int g = 1581767+PLAYER::PLAYER_ID()*306+178;
		int neg = -1*amount;
		Write_Global(g+4,neg);//actual my money
		Write_Global(g+3,Read_Global(g+3)+neg);


		int uVar1 = STATS::_0xB5BF87B2(31 - 0, 0, 1, Read_Global(1312622));
		int iVar2 = 31 - 0 - STATS::_0xDFC25D66(31 - 0) * 64;
		bool iVar0 = STATS::STAT_SET_BOOL_MASKED(uVar1, 1, iVar2, 1);


		//something idk
		Write_Global(2410912+255,Read_Global(2410912+255)+amount);
	}
	*/

	/*
	opd_s sub_17746A4_t = {0x17746A4,TOC};//doesn't work but I ain't even gonna bother with it
	unsigned int (*sub_17746A4)(unsigned int r3) = (unsigned int(*)(unsigned int))&sub_17746A4_t;
	void forceExecuteTextMessages() {
		sub_17746A4(0x2259F54);
	}*/
	
	void msg(char *text, int player, bool sendToSelfAlso) {
		if (text == 0)
			return;//don't send
		//if (player != PLAYER::PLAYER_ID()) {
			NETWORK::NETWORK_SEND_TEXT_MESSAGE(text, v_3(player));
			//forceExecuteTextMessages();
		//} else {
		if (player == PLAYER::PLAYER_ID()) {
			if (sendToSelfAlso) {
				UI::_0x574EE85C("STRING");
				UI::_ADD_TEXT_COMPONENT_STRING3(text);//0x0829A799
				UI::_DRAW_NOTIFICATION(2000, false/*show in brief*/);//0x08F7AF78 aka 

				print2(text,2000);
			}
		}
		//}
		
	}

	opd_s sub_12EF35C_t = {0x12EF35C,TOC};
	unsigned int(*sub_12EF35C)() = (unsigned int(*)())&sub_12EF35C_t;

	void sendSpoofedText(char *message, int to, int from, bool sendToSelfAlso = false) {
		unsigned int addr = sub_12EF35C();
		char *name = (char*)(addr+0x8);
		CNetGamePlayer *p = getCNetGamePlayer(from);
		if (VALID_ADDR(p)) {
			if (VALID_ADDR(p->playerInfo)) {
				strcpy(name,p->playerInfo->name);
				PlayerMods::msg(message,to,sendToSelfAlso);
				strcpy(name,getCNetGamePlayer(PLAYER::PLAYER_ID())->playerInfo->name);
			}
		}
	}

	void notify(char *message, int player, bool sendToSelfAlso = false) {
		/*unsigned int addr = sub_12EF35C();
		char *name = (char*)(addr+0x8);
		CNetGamePlayer *p = getCNetGamePlayer(player);
		if (VALID_ADDR(p)) {
			strcpy(name,p->playerInfo->name);
			PlayerMods::msg(message,player,sendToSelfAlso);
			strcpy(name,getCNetGamePlayer(PLAYER::PLAYER_ID())->playerInfo->name);
			//sendRockstarMessageEvent(p->playerInfo->name,message);
		}*/
		sendSpoofedText(message,player,player,sendToSelfAlso);
	}
	void spoofMsg(char *message, int playerToSpoofTo, int playerToSendTo = -1, bool sendToSelfAlso = false) {
		unsigned int addr = sub_12EF35C();
		char *name = (char*)(addr+0x8);
		CNetGamePlayer *p = getCNetGamePlayer(playerToSpoofTo);
		if (VALID_ADDR(p)) {
			strcpy(name,p->playerInfo->name);
			if (playerToSendTo != -1)
				PlayerMods::msg(message,playerToSendTo,sendToSelfAlso);
			else
				for (int i = 0; i < 18; i++)
					PlayerMods::msg(message,i,sendToSelfAlso);
			strcpy(name,getCNetGamePlayer(PLAYER::PLAYER_ID())->playerInfo->name);
		}
	}

#ifdef iuzISDhjgijadsfjhgiujfasdgiu
	void requestControlOfPlayer(int player) {
		
		unsigned int entity = getPlayerPedByIndex(PLAYER::GET_PLAYER_PED(player));
		unsigned int address = *(volatile unsigned int*)(entity+0x4C);
		opd_s callreq = {0x12BD410,TOC};
		unsigned int(*callrequest)(unsigned int networkdata, char *text) = (unsigned int(*)(unsigned int,char*))&callreq;
		callrequest(address,"NETWORK_REQUEST_CONTROL_OF_ENTITY");
	}

	bool hornPressFunction(unsigned int r3) {
		/*
		r3 = getPlayerPedByIndex(player);
		r3 = *(volatile unsigned int*)(r3+0xBD0);
		r31 = *(volatile unsigned int*)(r3+0x160);
		r4 = *(volatile unsigned int*)(r31+0x4c);
		*/
		opd_s _C08D00_t = {0xC08D00,TOC};
		unsigned int (*_C08D00)(unsigned int r3, unsigned int r4, unsigned int r5, float f1) = (unsigned int(*)(unsigned int, unsigned int, unsigned int, float))&_C08D00_t;
		opd_s ButtonStuff_t = {0x04A4548,TOC};
		unsigned int(*ButtonStuff)(unsigned int r3) = (unsigned int(*)(unsigned int))&ButtonStuff_t;
		opd_s isPlayerPedDataBeingUpdated_t = {0x1006338,TOC};
		unsigned int(*isPlayerPedDataBeingUpdated)(unsigned int playerPed) = (unsigned int(*)(unsigned int))&isPlayerPedDataBeingUpdated_t;
		unsigned int r4,r5,r6,r7,r8,r9,r10,r31;
		printf("r3: %i.\n",r3);
		r31 = *(volatile unsigned int*)(r3+0x160);
		printf("r31: %i..\n",r31);
		if (r31 == 0)return false;
		r4 = *(volatile unsigned int*)(r31+0x4c);
		printf("r4: %i...\n",r4);
		if (r4 == 0)
			goto loc_1164C98;
		r3 = *(char*)(r4+0x27);
		printf("r3: %i....\n",r3);
		if (r3 == 0)
			goto loc_1164C98;
		//r3 = r31; simplified in below
		r3 = isPlayerPedDataBeingUpdated(r31);
		printf("r3: %i.....\n",r3);//this is false when they are not in car
		if (r3 == 0) return false;//this one is 0 when they are too far away
		r31 = *(volatile unsigned int*)(r31+0xe9c);
		printf("r3: %i......\n",r3);
		r31 = *(volatile unsigned int*)(r31+0x4c);
		if (r31 == 0) return false;
		r4 = *(char*)(r31+0x186);
		printf("r3: %i.......\n",r3);
		r3 = 0;
		return r3;//not exactly but close enough

loc_1164C98:
		printf("r3: %i........\n",r3);
		r3 = r31;
		r3 = isPlayerPedDataBeingUpdated(r3);//this is checking if the player is in a car
		printf("r3: %i.........\n",r3);
		r4 = r3;
		r3 = 0;
		if (r4 == 0) return r3;//if I take this out it should work out of car?
		printf("Player is in a car!\n",r3);//this only shows up when in a car
		r3 = 1;
		r3 = ButtonStuff(r3);
		printf("r3: %i............\n",r3);
		r3 = r3 + 0x1814;//unsure exactly what this is
		printf("r3: %i.............\n",r3);
		r5 = 0x1FD8CFC;
		float f1 = 0.5f;
		r3 = _C08D00(r3/*31493396 me horn button*/,r4/*1*/,r5/*0x1FD8CFC*/,f1);//this tests if they are pressing the horn or not. returns 1 or 0
		printf("r3: %i..............\n",r3);
		r4 = r3;
		r3 = 0;
		printf("r4 (return): %i\n",r4);
		if (r4 == 0) return false;
		return true;
	}

	bool isPressingHorn(int player) {
		opd_s gppbi = {0x0047DFA0,TOC};
		int(*getPlayerPedByIndex)(int player) = (int(*)(int))&gppbi;
		int r3,r4,r5,r6,r7,r8,r9,r31;
		printf("\n\n\n\n");
		r3 = getPlayerPedByIndex(player);
		printf("r3: %i\n",r3);
		if (r3 != 0) {
			r3 = *(volatile unsigned int*)(r3+0xBD0);
			printf("r3: %i\n",r3);
			return hornPressFunction(r3);
		}
		return false;
	}

#endif



	/*int currentBitToModify = 0;

	int scriptEventId = 151;
	int scriptBitset = 1;
	void triggerScriptEvent(int player) {
		int args[100];
		args[0] = scriptEventId;
		args[1] = player;
		
		for (int i = 1; i < 100; i++) {
			args[i] = player;
		}
		SCRIPT::TRIGGER_SCRIPT_EVENT(1,args,100,scriptBitset);
	}*/

	namespace eventCreator {
		/*
		Documented ones:
		{2,player,0x1F} - Triggered when clicked quick gps none
		{0x103,player,0} - triggered halfway opening pause menu
		{0x117,player,0} - triggered when closing pause menu
		{0x104,player,0} - triggered when enable passive mode
		{0x118,player,0} - triggered when passive mode ended
		{00000120 00000000 FFFFFFFF 00000007 00000000 00000000} - triggered when pressing sultan from mechanic (6)
		{00000123 00000000 FFFFFFFF 00000007 00000004 00000000} - part 2 sultan get (6)
		{00000121 00000000 FFFFFFFF 00000007 00000000 00000000} - part 3 (6)
		{0000012D 00000000 C43A7644 C4F40630 40EE0000 4390C95C 39DA2754} - part 4 monents later = spawn car (7) THIS IS THE GOOD ONE?
		{0000012E 00000000 00000001} - part 5 (3)

		{0000012D 00000000 C41D0759 C42C0000 41F0C000 43B40000 39DA2754} - request personal vehicle (7)
		{0000012E 00000000 00000001} - p2 (3) (called after the first one aka don't ened to call manually)
		{00000161 00000000 00000000} - p3 (3)

		{00000000 FFFFFFFF 00000001 00000000 00000000 33B052B0 33B052BC 00000000 00000000 00000001 00000000} - after death (11) (this is wrong)
		{00000008 00000000 00000001 00000000 000045ED} -after death (5)
		{00000007 00000000 00000003 C44599CD C4CE6CEA 416FAD72 C4653570 C4E0E00B 4199625D C4460018 C4CE7023} -after death (11)
		{00000008 00000000 00000001 00000000 0000AEFE} - after death (5)
		*/
		int currentPlayerSelectedInMenu;
		int currentArgSelectedInMenu;
		int argsCount = 1;
		ScriptArg args[102];
		bool players[18];
		void triggerScriptEvent() {
			unsigned int playerBits;
			for (int i = 0; i < 18; i++)
				if (players[i])
					playerBits |= (1<<i);
			SCRIPT::TRIGGER_SCRIPT_EVENT(1,args,argsCount,playerBits);
		}
		void callScriptEvent(ScriptArg *args,int argsCount,unsigned int playerBits) {
			SCRIPT::TRIGGER_SCRIPT_EVENT(1,args,argsCount,playerBits);
		}
	};

	void msgFriend(char *text, char *name) {
		//NETWORK::NETWORK_SEND_TEXT_MESSAGE(text, getFriendHandle(text));
		print2("Currently not working",1000);
	}

	void setMoneyDropType(char *dropType) {
		lobbyModMenu::moneyBagDrop = GAMEPLAY::GET_HASH_KEY(dropType);
	}

	void setMoneyDropTypeOriginal() {
		lobbyModMenu::moneyBagDrop = 0x113FD533;
	}

	/*char longTextMessage[100];
	void initLongTextMessage() {
		for (int i = 0; i < 100; i++)
			longTextMessage[i] = 'A';
	}*/

	bool spamTextMessageBool[16];
	void toggleSpamTextMessage(int player) {
		spamTextMessageBool[player] = !spamTextMessageBool[player];
	}
	
	bool spamTextMessageWholeLobby = false;
	int spamTextMessageWholeLobbyCounter = 0;
	int spamTextMessageWholeLobbyCounterMax = 2;
	int spamtype = 0;//0 is paradise advertise, 1 is big crap, 2 is numbers
	void spamTextMessageLoop() {
		spamTextMessageWholeLobbyCounter++;
		if(spamTextMessageWholeLobbyCounter >= spamTextMessageWholeLobbyCounterMax)
			spamTextMessageWholeLobbyCounterMax = 0;
		for (int i = 0; i < 18; i++) {
			if (spamTextMessageWholeLobby || spamTextMessageBool[i]) {
				//if (spamtype == 0) {
					switch(spamTextMessageWholeLobbyCounter) {
					case 0:
						notify("<font size='49'>~r~Paradise sprx ~y~by ~b~gopro_2027",i);
						break;
					case 1:
						notify("<font size='49'>~h~~r~paradisesprx.net",i);
						break;
					}
				/*}
				if (spamtype == 1) {
					switch(spamTextMessageWholeLobbyCounter) {
					case 0:
						msg("<font size='99'>¦¦¦",i);
						break;
					case 1:
						msg("<font size='99'>~b~¦¦¦",i);
						break;
					}
				}
				if (spamtype == 2) {
					char buf[64];
					snprintf$(buf,sizeof(buf),"<font size='1'>%s",ItoSH(NETWORK::GET_NETWORK_TIME()));
					msg(buf,i);
				}*/
			}
		}
	}

	/*void freezePlayer(int player) {
		int NetHandleBuffer = 0x10070200;
		NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, NetHandleBuffer, 13);
		*(char*)(&NetHandleBuffer) = 0x3F, 0x70, 0x20, 0x35;//idk what it will do but hopefully something good
		NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(NetHandleBuffer,true);
	}*/

	void freezePlayer(int player) {
		//WriteMemory(0x6179796 + (player*0x6a6b), 0xc6d616f);
		//*(char*)(0x6179796 + (player*0x6a6b)) = 0xc6d616f;
		//print("~r~LOL YOU GOT TROLLED HAHAHAHAHAHAHAH *cough* Geeze you really think I would give that ability to the public?");
	}

	/*float testTextMessageSize = 0;
	void testTextMessage(int player, int size, int iterations) {
		char *buf = (char*)neww(size);
		for (int i = 0; i < size; i++) {
			*(char*)(buf+i) = i;
		}
		for (int i = 0; i < iterations; i++) {
			sleep(1);
			msg(buf,player);
		}
		deletee(buf);
	}*/

	int wantedLevelTimer = 0;
	bool wantedLevelEnabled = false;
	void removeWantedLevelLoop() {
		randomizeAddresses();
		if (wantedLevelEnabled == true) {
			wantedLevelTimer++;
			if (wantedLevelTimer > 10) {
				wantedLevelTimer = 0;
				PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
			}
		}
	}

	bool disableRespawnBool = false;void disableRespawn() { disableRespawnBool = !disableRespawnBool; GAMEPLAY::_0x296574AE(disableRespawnBool); }

	bool increaseFPSBool = false;
	void increaseFPS() {
		increaseFPSBool = !increaseFPSBool;
		GRAPHICS::_0xAA2A0EAF(increaseFPSBool);//set blackout
		GRAPHICS::_0xFE903D0F(increaseFPSBool);//setFarShadowsSupressed
	}

	void TeleportToPlayer(int client) {
		if(PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0) == true) {
			Vector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(client),true);
			int handle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			ENTITY::SET_ENTITY_COORDS(handle, c.x,c.y,c.z, false, false, false, true);
			noclip::x = c.x;
			noclip::y = c.y;
			noclip::z = c.z;
			print("Teleported!");
		} else {
			Vector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(client),true);
			ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), c.x,c.y,c.z, false, false, false, true);
			noclip::x = c.x;
			noclip::y = c.y;
			noclip::z = c.z;
			print("Teleported!");
		}
	}
	/*
	int TeleportPlayerToMeID = 0;
	bool TeleportPlayerToMeENABLE = false;
	int TeleportPlayerToMeTIMEOUT = 0;
	int TeleportPlayerToMeTIMEOUT2 = 0;

	void TeleportPlayerToMe(int client) {
		if(PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(client), 0) == true) {
			TeleportPlayerToMeTIMEOUT2 = 0;
			Vector3 me = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true);
			int veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(client));
			ENTITY::SET_ENTITY_COORDS(veh, me.x,me.y,me.z, false, false, false, true);
			TeleportPlayerToMeENABLE = true;
			TeleportPlayerToMeID = client;
			TeleportPlayerToMeTIMEOUT = 0;
		} else {
			TeleportPlayerToMeENABLE = false;
			TeleportPlayerToMeID = 0;
			TeleportPlayerToMeTIMEOUT = 0;
			TeleportPlayerToMeTIMEOUT2 = 0;
			print("~r~Player not in vehicle");
		}
	}*/

	/*void TeleportPlayerToMeLoop() {
		if (TeleportPlayerToMeENABLE == true) {
			if (TeleportPlayerToMeTIMEOUT < 1000) {
				TeleportPlayerToMeTIMEOUT++;
				Vector3 me = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true);
				int veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(TeleportPlayerToMeID));
				netreq::reqent(veh);
				if (netreq::hasent(veh)) {
					TeleportPlayerToMeTIMEOUT2++;
					ENTITY::SET_ENTITY_COORDS(veh, me.x,me.y,me.z, false, false, false, true);
					if (TeleportPlayerToMeTIMEOUT2 > 100) {
						TeleportPlayerToMeENABLE = false;
						TeleportPlayerToMeID = 0;
						TeleportPlayerToMeTIMEOUT = 0;
						TeleportPlayerToMeTIMEOUT2 = 0;
						print("Player teleported to you");
					}
				}
			} else {
				TeleportPlayerToMeENABLE = false;
				TeleportPlayerToMeID = 0;
				TeleportPlayerToMeTIMEOUT = 0;
				TeleportPlayerToMeTIMEOUT2 = 0;
				print("Could not gain control of player's vehicle");
			}
		}
	}*/

	bool funnyScreenEnabled = false;
	void funnyScreen(bool enabled) {
		if(enabled == true) {
			//medium
			*(char*)(0x1D260) = 0x40, 0x00, 0x00, 0x00;//proper
		} else {
			//normal
			*(char*)(0x1D260) = 0x3F, 0x80, 0x00, 0x00;
		}
	}

	bool playerMoneyDropToggle[] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};//20 for safe measures
	
	void toggleMoneyDropPlayer(int player) {
		playerMoneyDropToggle[player] = !playerMoneyDropToggle[player];
	}

	bool getPlayerMoneyDropToggle(int player) {
		return playerMoneyDropToggle[player];
	}

	int moneyDropType = 0;//0 = cash drop, 1 = refund glitch

	void dropMoneyLoop() {
		for (int i = 0; i < 18; i++) {
			if (playerMoneyDropToggle[i] == true) {
				if (moneyDropType == 0)
					lobbyModMenu::dropMoneyBag(i);
				else
					givePlayerMoney(i, 500000/*50000000*//*0x7FFFFFFF*/);
			}
		}
	}

	bool doBlackFade = false;
	Vector3 teleportToCoordsVec = {0,0,0};
	bool teleportToCoordsBool = false;
	void teleportToCoords(float x, float y, float z, bool doBlackScreen = false) {
		doBlackFade = doBlackScreen;
			/*int Handle = PLAYER::PLAYER_PED_ID();
			if (PED::IS_PED_IN_ANY_VEHICLE(Handle,true))
				Handle = PED::GET_VEHICLE_PED_IS_IN(Handle,false);
			ENTITY::SET_ENTITY_COORDS(Handle,x,y,z,0,0,0,0);*/
			
if (doBlackFade)
			CAM::DO_SCREEN_FADE_OUT(500);//500 milliseconds

			//PLAYER::START_PLAYER_TELEPORT(PLAYER::PLAYER_ID(), x, y, z,1/*heading*/, true, true, true);
			teleportToCoordsVec.x = x;
			teleportToCoordsVec.y = y;
			teleportToCoordsVec.z = z;
			teleportToCoordsBool = true;
	}

	void teleportToCoordsManagerLoop() {
		static int mode = 0;
		if (teleportToCoordsBool) {
			bool isFadedOut = true;
			if (doBlackFade)
				isFadedOut = CAM::IS_SCREEN_FADED_OUT();
			if (isFadedOut && mode == 0) {
				//start TP
				STREAMING::CLEAR_FOCUS();
				PLAYER::START_PLAYER_TELEPORT(PLAYER::PLAYER_ID(),teleportToCoordsVec.x,teleportToCoordsVec.y,teleportToCoordsVec.z,ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()),true,true,false);
				noclip::x = teleportToCoordsVec.x;
				noclip::y = teleportToCoordsVec.y;
				noclip::z = teleportToCoordsVec.z;
				mode = 1;
				//printf("Started the teleport\n");
			}
			if (!PLAYER::IS_PLAYER_TELEPORT_ACTIVE() && mode == 1) {
				//end TP
				PLAYER::STOP_PLAYER_TELEPORT();
				if (doBlackFade) {
					float zval = 0;
					GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(teleportToCoordsVec.x,teleportToCoordsVec.y,teleportToCoordsVec.z,&zval);
					int Handle = PLAYER::PLAYER_PED_ID();
					if (PED::IS_PED_IN_ANY_VEHICLE(Handle,true))
						Handle = PED::GET_VEHICLE_PED_IS_IN(Handle,false);
					if (zval == 0) {//not found
						teleportToCoordsVec.z-=1.0f;
						if (teleportToCoordsVec.z > 0)
							return;//continue
						print2("~r~Error finding spawn point!");
					}
					ENTITY::SET_ENTITY_COORDS(Handle,teleportToCoordsVec.x,teleportToCoordsVec.y,zval,0,0,0,0);
					CAM::DO_SCREEN_FADE_IN(500);
				}
				mode = 0;
				teleportToCoordsBool = false;
				//printf("Ended the teleport\n");
			}
		}
	}

	void teleportToWaypoint() {
		int WaypointHandle = UI::GET_FIRST_BLIP_INFO_ID(8);								
		if(UI::DOES_BLIP_EXIST(WaypointHandle)) {
			Vector3 pos = UI::GET_BLIP_COORDS(WaypointHandle);
			/*int Handle = PLAYER::PLAYER_PED_ID();
			if (PED::IS_PED_IN_ANY_VEHICLE(Handle,true))
				Handle = PED::GET_VEHICLE_PED_IS_IN(Handle,false);
			ENTITY::SET_ENTITY_COORDS(Handle,pos.x,pos.y,-1000,0,0,0,0);
			noclip::x = pos.x;
			noclip::y = pos.y;
			noclip::z = pos.z;*/
			teleportToCoords(pos.x,pos.y,pos.z+1000,true);
			print("Teleported!");
		}else {
			print("~r~No Present Waypoint");
		}
	}

	bool showTalkingPlayersBool = false;
	void showTalkingPlayersLoop() {
		randomizeAddresses();
		if (showTalkingPlayersBool == true) {
			int index = 0;
			for (int i = 0; i < 18; i++) {
				if (NETWORK::NETWORK_PLAYER_HAS_HEADSET(i)) {
					char *name = (char *)PLAYER::GET_PLAYER_NAME(i);
					char buf[50];
					if (NETWORK::NETWORK_IS_PLAYER_TALKING(i)) {
						snprintf$(buf,sizeof(buf),"~b~%s",name);
					} else {
						//not talking
						snprintf$(buf,sizeof(buf),"~c~%s",name);
					}
					drawing::DrawText(buf,0,0.95,GRAPHICS::_0x3F0D1A6F()-0.4175-(0.035*index),0.35,0.35,255,255,255,255,false,false,true);
					index++;
				}
			}
			if (index != 0)
				drawing::DrawText("~g~Game Chat",0,0.95,GRAPHICS::_0x3F0D1A6F()-0.4175-(0.035*index),0.35,0.35,255,255,255,255,false,false,true);
			else
				drawing::DrawText("~r~Game Chat (none)",0,0.95,GRAPHICS::_0x3F0D1A6F()-0.4175-(0.035*index),0.35,0.35,255,255,255,255,false,false,true);
			index++;
		}
	}

	char attachpropchar[100];
	int attachpropplayer = 0;
	bool doattachproploop = false;
	int attachproptimeout = 0;
	int attachpropbodypart = 0;
	bool bypassProtection = false;

	int forceAttachPropToPlayer(int player,int bodyPart, char *object) {
		for (int i = 0; i < 100; i++)
			attachpropchar[i] = 0;
		strncpy(attachpropchar,object,100);

		attachpropbodypart = bodyPart;
		attachpropplayer = player;
		attachproptimeout = 0;
		doattachproploop = true;
		bypassProtection = false;
	}



	void attachPropToPlayerLoop() {
		if (doattachproploop == true) {
			attachproptimeout++;
			if (attachproptimeout < 1000) {
				int obj;
				obj = OBJ::attachProp(attachpropplayer,attachpropbodypart,attachpropchar);
				if (obj != 0) {
					attachproptimeout = 0;
					doattachproploop = false;
					attachpropplayer = 0;
					//attachpropchar = "";
					for (int i = 0; i < 100; i++)
						attachpropchar[i] = 0;
					print("~g~Prop attached!");
				}
			} else {
				print("~r~Could not attach prop to player!");
				attachproptimeout = 0;
				doattachproploop = false;
				attachpropplayer = 0;
				//attachpropchar = "";
				for (int i = 0; i < 100; i++)
					attachpropchar[i] = 0;
			}
		}
	}

	namespace bones {
		int BONE_ROOT = 0x0000,Head = 0x796E,Left_Hand = 0x49d9, Right_Wrist = 0x6F06,Left_Wrist = 0xEB95,Right_Hand = 0xDEAD,Chest = 0x60F2,Month = 0x9995,Left_Wrist2 = 0x49D9,Left_Knee = 0xF9BB,Right_Knee = 0x9000,Left_Shoe = 0x3779,Right_Shoe = 0xCC4D,Gentils = 0xCA72,Umbilical = 0x2E28,Right_Shoulder = 0x9D4D,Right_Arm = 0x6E5C,Left_Shoulder = 0xB1C5,Left_Arm = 0xEEEB;
	}
	char *curBoneProp = "";

	bool changeModelBool = false;
	char *changeModelChar = "";
	int changeModelTimeout = 0;
	void (*saveFunc)(int) = nullFunc;
	void changeModelNow(char *model, void(*f)(int) = nullFunc) {
		changeModelTimeout = 0;
		changeModelBool = true;
		changeModelChar = model;
		saveFunc = f;
	}
	void changeModel(char* Model) {
		int ModelHash = GAMEPLAY::GET_HASH_KEY(Model);
		if (STREAMING::IS_MODEL_IN_CDIMAGE(ModelHash)) {
			if (STREAMING::IS_MODEL_VALID(ModelHash)) {
				STREAMING::REQUEST_MODEL(ModelHash);
				if (STREAMING::HAS_MODEL_LOADED(ModelHash))
				{
					PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), ModelHash);
					//STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(ModelHash);
					saveFunc(ModelHash);
				}
			}
		}
	}

	void changeModelLoop() {
		if (changeModelBool == true) {
			changeModelTimeout++;
			if (changeModelTimeout < 20) {
				changeModel(changeModelChar);
			} else {
				changeModelTimeout = 0;
				changeModelBool = false;
			}
		}
	}

	bool playerClearTask[] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};
	bool togglePlayerClearTask(int player) {
		playerClearTask[player] = !playerClearTask[player];
		return playerClearTask[player];
	}

	void playerClearTaskLoop() {
		for (int i = 0; i < 18; i++) {
			if (playerClearTask[i] == true) {
				AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED(i));
			}
		}
	}

	bool lobbyClearTask = false;

	void lobbyClearTaskLoop() {
		if (lobbyClearTask == true) {
			int playerid = PLAYER::PLAYER_ID();
			for (int i = 0; i < 18; i++) {
				if (i != playerid) {
					AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED(i));
				}
			}
		}
	}

	enum ExplosionTypes {
	EXPLOSION_GRENADE,
	EXPLOSION_GRENADELAUNCHER,
	EXPLOSION_STICKYBOMB,
	EXPLOSION_MOLOTOV,
	EXPLOSION_ROCKET,
	EXPLOSION_TANKSHELL,
	EXPLOSION_HI_OCTANE,
	EXPLOSION_CAR,
	EXPLOSION_PLANE,
	EXPLOSION_PETROL_PUMP,
	EXPLOSION_BIKE,
	EXPLOSION_DIR_STEAM,
	EXPLOSION_DIR_FLAME,
	EXPLOSION_DIR_WATER_HYDRANT,
	EXPLOSION_DIR_GAS_CANISTER,
	EXPLOSION_BOAT,
	EXPLOSION_SHIP_DESTROY,
	EXPLOSION_TRUCK,
	EXPLOSION_BULLET,
	EXPLOSION_SMOKEGRENADELAUNCHER,
	EXPLOSION_SMOKEGRENADE,
	EXPLOSION_BZGAS,
	EXPLOSION_FLARE,
	EXPLOSION_GAS_CANISTER,
	EXPLOSION_EXTINGUISHER,
	EXPLOSION_PROGRAMMABLEAR,
	EXPLOSION_TRAIN,
	EXPLOSION_BARREL,
	EXPLOSION_PROPANE,
	EXPLOSION_BLIMP,
	EXPLOSION_DIR_FLAME_EXPLODE,
	EXPLOSION_TANKER,
	EXPLOSION_PLANE_ROCKET,
	EXPLOSION_VEHICLE_BULLET,
	EXPLOSION_GAS_TANK,
	EXPLOSION_BIRD_CRAP};

	void drawLine(Vector3 p1, Vector3 p2) {
		GRAPHICS::DRAW_LINE(p1.x,p1.y,p1.z,p2.x,p2.y,p2.z,255,0,0,255);
	}

	bool canPlayerSeePlayer(int player, int see) {
		int bone1 = PED::GET_PED_BONE_INDEX(PLAYER::GET_PLAYER_PED(see), 0x796E);
        Vector3 head1 = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED(see), bone1,0,0,0);
		return NETWORK::IS_SPHERE_VISIBLE_TO_PLAYER(player,head1.x,head1.y,head1.z,1);
		//return CAM::IS_SPHERE_VISIBLE(head1.x,head1.y,head1.z,1);
		/*head1.z+=1;
		int bone2 = PED::GET_PED_BONE_INDEX(PLAYER::GET_PLAYER_PED(player2), 0x796E);
        Vector3 head2 = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED(player2), bone2,0,0,0);
		head2.z+=1;
		
		//debug
		drawLine(head1,head2);

		int type = 1;//1 is intersect with map
		opd_s _crp_t = {0x428EF0,TOC};
		int(*_CAST_RAY_POINT_TO_POINT)(float x1, float y1, float z1, float x2, float y2, float z2, int type, int u1, int u2) = (int(*)(float,float,float,float,float,float,int,int,int))&_crp_t;
		int handle = _CAST_RAY_POINT_TO_POINT(head1.x, head1.y, head1.z, head2.x, head2.y, head2.z, type, 0, 7); //unk_0x8251485D
		if (handle == 0)
			return true;
		return false;*/
		/*int Type = 1;
		bool hitsomething = 0;
		int entityhandle = 0;
		Vector3 hitCoords, surfaceNormal;
		opd_s _grr = {0x429AA8,TOC};
		void(*_GET_RAYCAST_RESULT)(int rayHandle, bool *hit, Vector3 *endCoords,  Vector3 *surfaceNormal, int *objHit) = (void(*)(int,bool *,Vector3 *, Vector3 *,int *))&_grr;  //unk_0xF3C2875A
		_GET_RAYCAST_RESULT(handle, &hitsomething, &hitCoords, &surfaceNormal, &entityhandle);
		//drawing::DrawFloat((float)hitsomething,0,0.5,0.5,0.5,0.5,255,255,255,255,true,1,true);
		return !hitsomething;*/
	}

	bool isPlayerVisible(int player) {
		int bone1 = PED::GET_PED_BONE_INDEX(PLAYER::GET_PLAYER_PED(player), 0x796E);
        Vector3 head1 = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED(player), bone1,0,0,0);
		return CAM::IS_SPHERE_VISIBLE(head1.x,head1.y,head1.z,1);
	}
	
	void explodePlayer(int player) {
		int ped = PLAYER::GET_PLAYER_PED(player);
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(ped,1);
		float co[] = {coords.x,coords.y,coords.z};
		OTHER::ADD_OWNED_EXPLOSION(ped, co/*OTHER::GET_ENTITY_COORDS(ped)*/, EXPLOSION_BLIMP, 0.5f, true, false, 0.0f);
	}

	void explodePlayerSilent(int player) {
		int ped = PLAYER::GET_PLAYER_PED(player);
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(ped,1);
		float co[] = {coords.x,coords.y,coords.z};
		OTHER::ADD_OWNED_EXPLOSION(ped, co/*OTHER::GET_ENTITY_COORDS(ped)*/, EXPLOSION_BLIMP, 0.5f, false, true, 0.0f);
	}

	void playerExplodePlayer(int killer, int victim) {
		int ped = PLAYER::GET_PLAYER_PED(victim);
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(ped,1);
		float co[] = {coords.x,coords.y,coords.z};
		int ped2 = PLAYER::GET_PLAYER_PED(killer);
		OTHER::ADD_OWNED_EXPLOSION(ped2, co, EXPLOSION_BLIMP, 0.1f, true, false, 0.0f);
	}

	void playerExplodePlayerSilent(int killer, int victim) {
		int ped = PLAYER::GET_PLAYER_PED(victim);
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(ped,1);
		float co[] = {coords.x,coords.y,coords.z};
		int ped2 = PLAYER::GET_PLAYER_PED(killer);
		OTHER::ADD_OWNED_EXPLOSION(ped2, co, EXPLOSION_BLIMP, 0.1f, false, true, 0.0f);
	}

	bool blamePlayerKillThemToo = false;
	void blamePlayer(int player) {
		for (int i = 0; i < 18; i++)
			if (i != PLAYER::PLAYER_ID())
				if (i != player || blamePlayerKillThemToo)
					playerExplodePlayer(player,i);
	}

	void explodeLobby() {
		for (int i = 0; i < 18; i++)
			if (i != PLAYER::PLAYER_ID())
				explodePlayer(i);
	}

	void killwithstyle(int player) {
		int bone = PED::GET_PED_BONE_INDEX(PLAYER::GET_PLAYER_PED(player), 0x796E);
        Vector3 handcoords = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED(player), bone,0,0,0);
		Vector3 c1 = {handcoords.x+0.01f,handcoords.y,handcoords.z};
		Vector3 c2 = {handcoords.x-0.01f,handcoords.y,handcoords.z};
		int launchDistance = 250;
		int weaponHash = GAMEPLAY::GET_HASH_KEY("");
		float launchSpeed = 1500.0f;
		GAMEPLAY::_0x52ACCB7B(c1.x,c1.y,c1.z,c2.x,c2.y,c2.z,launchDistance,0,weaponHash,PLAYER::GET_PLAYER_PED(player),1,1,launchSpeed,PLAYER::GET_PLAYER_PED(player));
	}

	bool dropItem(int index, int hash, int model) {
		STREAMING::REQUEST_MODEL(model);//0x113FD533
		if (STREAMING::HAS_MODEL_LOADED(model)) {
			//uint PICKUP_MONEY_CASE = GAMEPLAY::GET_HASH_KEY("PICKUP_MONEY_CASE");
			Vector3 playerpos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(index),true);
			OBJECT::CREATE_AMBIENT_PICKUP(hash, playerpos.x,playerpos.y,playerpos.z, 0, 40000, model, false, true);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
		}
	}

	/*int weaponSpawnableHashes[] = {0x6E4E65C2,0x741C684A,0x68605A36,0x6C5B941A,0xD3A39366,0x550447A9,0xF99E15D0,0xA421A532,0xF33C83B0,0xDF711959,0xB2B5325E,0x85CAA9B1,0xB2930A14,0xFE2A352C,0x693583AD,0x1D9588D3,0x3A4C2AD2,0x4D36C349,0x2F36B434,0xA9355DCD,0x96B412A3,0x9299C95B,0x5E0683A1,0x2DD30479,0x1CD604C7,0x7C119D58,0xF9AFB48F,0x8967B4F3,0x3B662889,0x2E764125,0xFD16169E,0xCB13D282,0xC69DE3FF,0x278D8734,0x5EA16D74,0x295691A9,0x81EE601E,0x88EAACA7,0x872DC888,0xD0AACEF7,0xCC8B3905,0xA54AE7B7,0xA717F898,0x84D676D4,0x65A7D8E9,0x2C804FE3,0xB86AEE5B,0xCC7CCD1B,0x2E071B5A,0x20796A82,0x116FC4E6,0xE4BD2FC6,0xDE58E0B3,0x77F3F2DD,0xC02CF125,0x881AB0A8,0x84837FD7,0xF25A01B9,0x815D66E8,0xFA51ABF5,0xC5B72713,0x5307A4EC,0x9CF13918,0x0968339D,0xBFEE6C3B,0xEBF89D5F,0x22B15640,0x763F7121,0xF92F486C,0x602941D0,0xBED46EC5,0x079284A9,0x624F7213,0xC01EB678,0x5C517D97,0xBD4DE242,0xE013E01C};
	void spawnWeapons(int player) {
		for (int i = 0; i < sizeof(weaponSpawnableHashes)/sizeof(int);i++) {
			int hash = weaponSpawnableHashes[i];
			//dropItem(player,hash,hash);
			print2("~r~NNNNNNNNNNNNOOOOOOOOOOOPPPPPPPPPPPPEEEEEEEEEE",500);
		}
	}*/

	void removeGuns(int id) {
		WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::GET_PLAYER_PED(id),true);
	}

	//char *weps[] = {"WEAPON_UNARMED","WEAPON_ANIMAL","WEAPON_COUGAR","WEAPON_KNIFE","WEAPON_NIGHTSTICK","WEAPON_HAMMER","WEAPON_BAT","WEAPON_GOLFCLUB","WEAPON_CROWBAR","WEAPON_PISTOL","WEAPON_COMBATPISTOL","WEAPON_APPISTOL","WEAPON_PISTOL50","WEAPON_MICROSMG","WEAPON_SMG","WEAPON_ASSAULTSMG","WEAPON_ASSAULTRIFLE","WEAPON_ADVANCEDRIFLE","WEAPON_MG","WEAPON_COMBATMG","WEAPON_PUMPSHOTGUN","WEAPON_SAWNOFFSHOTGUN","WEAPON_ASSAULTSHOTGUN","WEAPON_BULLPUPSHOTGUN","WEAPON_STUNGUN","WEAPON_SNIPERRIFLE","WEAPON_HEAVYSNIPER","WEAPON_REMOTESNIPER","WEAPON_GRENADELAUNCHER","WEAPON_GRENADELAUNCHER_SMOKE","WEAPON_RPG","WEAPON_PASSENGER_ROCKET","WEAPON_AIRSTRIKE_ROCKET","WEAPON_STINGER","WEAPON_MINIGUN","WEAPON_GRENADE","WEAPON_STICKYBOMB","WEAPON_SMOKEGRENADE","WEAPON_BZGAS","WEAPON_MOLOTOV","WEAPON_FIREEXTINGUISHER","WEAPON_PETROLCAN","WEAPON_DIGISCANNER","WEAPON_BRIEFCASE","WEAPON_BRIEFCASE_02","WEAPON_BALL","WEAPON_FLARE","WEAPON_VEHICLE_ROCKET","WEAPON_BARBED_WIRE","WEAPON_DROWNING","WEAPON_DROWNING_IN_VEHICLE","WEAPON_BLEEDING","WEAPON_ELECTRIC_FENCE","WEAPON_EXPLOSION","WEAPON_FALL","WEAPON_EXHAUSTION","WEAPON_HIT_BY_WATER_CANNON","WEAPON_RAMMED_BY_CAR","WEAPON_RUN_OVER_BY_CAR","WEAPON_HELI_CRASH","WEAPON_FIRE","WEAPON_BOTTLE","WEAPON_GUSENBERG","WEAPON_SPECIALCARBINE","WEAPON_HEAVYPISTOL","WEAPON_SNSPISTOL","WEAPON_BULLPUPRIFLE","WEAPON_DAGGER","WEAPON_VINTAGEPISTOL","WEAPON_FIREWORK","WEAPON_MUSKET","WEAPON_HEAVYSHOTGUN","WEAPON_MARKSMANRIFLE","WEAPON_HOMINGLAUNCHER","WEAPON_PROXMINE","WEAPON_SNOWBALL","WEAPON_FLAREGUN","WEAPON_GARBAGEBAG","WEAPON_HANDCUFFS","WEAPON_COMBATPDW","WEAPON_MARKSMANPISTOL","WEAPON_KNUCKLE","WEAPON_CARBINERIFLE"};
	char *weps[] = {"WEAPON_UNARMED","WEAPON_KNIFE","WEAPON_NIGHTSTICK","WEAPON_HAMMER","WEAPON_BAT","WEAPON_GOLFCLUB","WEAPON_CROWBAR","WEAPON_PISTOL","WEAPON_COMBATPISTOL","WEAPON_APPISTOL","WEAPON_PISTOL50","WEAPON_MICROSMG","WEAPON_SMG","WEAPON_ASSAULTSMG","WEAPON_ASSAULTRIFLE","WEAPON_ADVANCEDRIFLE","WEAPON_MG","WEAPON_COMBATMG","WEAPON_PUMPSHOTGUN","WEAPON_SAWNOFFSHOTGUN","WEAPON_ASSAULTSHOTGUN","WEAPON_BULLPUPSHOTGUN","WEAPON_STUNGUN","WEAPON_SNIPERRIFLE","WEAPON_HEAVYSNIPER","WEAPON_REMOTESNIPER","WEAPON_GRENADELAUNCHER","WEAPON_GRENADELAUNCHER_SMOKE","WEAPON_RPG","WEAPON_STINGER","WEAPON_MINIGUN","WEAPON_GRENADE","WEAPON_STICKYBOMB","WEAPON_SMOKEGRENADE","WEAPON_BZGAS","WEAPON_MOLOTOV","WEAPON_FIREEXTINGUISHER","WEAPON_PETROLCAN","WEAPON_BALL","WEAPON_FLARE","WEAPON_BOTTLE","WEAPON_GUSENBERG","WEAPON_SPECIALCARBINE","WEAPON_HEAVYPISTOL","WEAPON_SNSPISTOL","WEAPON_BULLPUPRIFLE","WEAPON_DAGGER","WEAPON_VINTAGEPISTOL","WEAPON_FIREWORK","WEAPON_MUSKET","WEAPON_HEAVYSHOTGUN","WEAPON_MARKSMANRIFLE","WEAPON_HOMINGLAUNCHER","WEAPON_PROXMINE","WEAPON_SNOWBALL","WEAPON_FLAREGUN","WEAPON_GARBAGEBAG","WEAPON_COMBATPDW","WEAPON_MARKSMANPISTOL","WEAPON_KNUCKLE","WEAPON_CARBINERIFLE"};

	int weapongivetimeout = 0;
	bool weapongivebool = false;
	int weapongiveplayer = 0;
	int curweapongive = 0;

	/*void giveAll(int id) {
		for (int i = 0; i < 83; i++) {
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(id), GAMEPLAY::GET_HASH_KEY(weps[i]), -1, 1);//-1 may be 9999
		}
	}*/

	void giveAllWeaponsToPlayer(int player) {
		weapongivetimeout = 0;
		weapongivebool = true;
		weapongiveplayer = player;
	}

	void giveWeapon(int player, char *weapon, int ammo = -1) {WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(player), GAMEPLAY::GET_HASH_KEY(weapon), ammo, 1);}
	void giveWeapon(int player, int weapon, int ammo = -1) {WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(player), weapon, ammo, 1);}


	void weaponGivePlayerLoop() {
		if (weapongivebool == true) {
			weapongivetimeout++;
			if (curweapongive > 61/*82*/ ){
				char buf[150];
				snprintf$(buf,sizeof(buf),"~g~Done giving all weapons to %s",PLAYER::GET_PLAYER_NAME(weapongiveplayer));
				print(buf);
				curweapongive = 0;
				weapongivebool = false;
				weapongivetimeout = 0;
			}

			if (weapongivetimeout > 1) {//originally 5
				weapongivetimeout = 0;
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(weapongiveplayer), GAMEPLAY::GET_HASH_KEY(weps[curweapongive]), -1, 1);
				curweapongive++;
			}
		}
	}

	/*void freezePlayerPosition1(int i) {
		WEAPON::SET_CURRENT_PED_WEAPON(PLAYER::GET_PLAYER_PED(i),GAMEPLAY::GET_HASH_KEY("WEAPON_COUGAR"),true);
	}*/
	void freezePlayerPosition(int player) {
		WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::GET_PLAYER_PED(player),true);
		WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(player), GAMEPLAY::GET_HASH_KEY("WEAPON_COUGAR"), -1, 1);
		WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(player), GAMEPLAY::GET_HASH_KEY("WEAPON_PISTOL"), -1, 1);
		//runlater::runlater(100,freezePlayerPosition1,player);
	}

	bool rapidsetinvisible = false;
	void rapidsetinvisibleloop() {
		if (rapidsetinvisible == true) {
			ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true);
			ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), false);
			//SET_PLAYER_MODEL(PLAYER_ID(), spawnCar::GET_HASH_KEY("mp_m_freemode_01"));
		}
	}

	bool togglerapidsetinvisible() {
		rapidsetinvisible = !rapidsetinvisible;
		ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true);
		if (rapidsetinvisible == true) {
			print("Enable passive mode to not allow people to explode you");
		}
	}

	int propGlichPlayerReturnPlayer = 0;
	int propGlichPlayerLastProp = 0;
	int propGlichPlayerNumber = 0;
	//char *propGlitchPlayerString = "p_ing_skiprope_01";
	//char *propGlitchPlayerString[] = {"p_ing_skiprope_01","prop_Ld_ferris_wheel"};
	//int propGlitchPlayerStringSize = 2;
	char *propGlitchPlayerString[] = {"prop_cs_ashtray","prop_cs_amanda_shoe","prop_beware_dog_sign","prop_beta_tape","prop_biotech_store","prop_biolab_g_door","prop_cont_chiller_01","prop_el_guitar_01","prop_employee_month_01","prop_scn_police_torch","prop_mb_sandblock_01","prop_air_bagloader","prop_attache_case_01","","","","","","","","","",""};
	int propGlitchPlayerStringSize = 11;
	Vector3 nullVector = {0,0,0};
	void propGlitchPlayer(int player);
	void propGlitchPlayerReturn(int objectID) {
		//ENTITY::ATTACH_ENTITY_TO_ENTITY(objectID, PLAYER::GET_PLAYER_PED(propGlichPlayerReturnPlayer),PlayerMods::bones::Head,vector3ToFloatArray(nullVector),vector3ToFloatArray(nullVector),true,true,true,true,2,true);
		float l[] = {0,0,0};
		float l2[] = {0,0,0};
		OBJ::attachPropAlreadySpawned(propGlichPlayerReturnPlayer,PlayerMods::bones::Head,objectID,l,l2);
			
			
			
			//ENTITY::ATTACH_ENTITY_TO_ENTITY_PHYSICALLY(objectID, PLAYER::GET_PLAYER_PED(propGlichPlayerReturnPlayer), false,false,0,0,0,0,0,0,0,0,0,99999,1,1,true,1,2);
		//else
			//ENTITY::ATTACH_ENTITY_TO_ENTITY(objectID, propGlichPlayerLastProp,0,vector3ToFloatArray(nullVector),vector3ToFloatArray(nullVector),true,true,true,true,2,true);
			//ENTITY::ATTACH_ENTITY_TO_ENTITY_PHYSICALLY(objectID, propGlichPlayerLastProp, false,false,0,0,0,0,0,0,0,0,0,99999,1,1,true,1,2);
		//OBJ::attachPropAlreadySpawned(doRealFreezePlayerPlayer,PlayerMods::bones::Head,objectID,vector3ToFloatArray(nullvec3),vector3ToFloatArray(doRealFreezePlayernul));
		propGlichPlayerLastProp = objectID;
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(objectID,true,true);
        //ENTITY::SET_ENTITY_VISIBLE(objectID, true);//false//ENTITY::FREEZE_ENTITY_POSITION(objectID, true);//ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(objectID, PLAYER::GET_PLAYER_PED(propGlichPlayerReturnPlayer),false);//ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(objectID, propGlichPlayerLastProp,false);
        ENTITY::SET_ENTITY_COLLISION(objectID,true,true);
		ENTITY::SET_ENTITY_VISIBLE(objectID,false);
		propGlichPlayerNumber++;
		if (propGlichPlayerNumber == propGlitchPlayerStringSize) {
			propGlichPlayerReturnPlayer = 0;
			propGlichPlayerLastProp = 0;
			propGlichPlayerNumber = 0;
			//print("Spawned Object On Player");
		} else {
			runlater::runlater(10,propGlitchPlayer,propGlichPlayerReturnPlayer);
		}
	}
	void propGlitchPlayer(int player) {
		propGlichPlayerReturnPlayer = player;
		Vector3 tmp = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(player),true);
		Vector3 nul = {0,0,0};
		//print(propGlitchPlayerString[propGlichPlayerNumber]);
		OBJ::forceCreateObject(propGlitchPlayerString[propGlichPlayerNumber],tmp,nul,false,propGlitchPlayerReturn);
	}

	/*int doRealFreezePlayerPlayer = 0;
	int doRealFreezePlayerCount = 0;
	Vector3 doRealFreezePlayernul = {0,0,0};
	Vector3 nullvec3 = {0,0,0};
	void doRealFreezePlayerReturn(int objectID) {
		ENTITY::ATTACH_ENTITY_TO_ENTITY(objectID, PLAYER::GET_PLAYER_PED(doRealFreezePlayerPlayer),0,vector3ToFloatArray(nullVector),vector3ToFloatArray(doRealFreezePlayernul),true,true,true,true,2,true);
		//OBJ::attachPropAlreadySpawned(doRealFreezePlayerPlayer,PlayerMods::bones::Head,objectID,vector3ToFloatArray(nullvec3),vector3ToFloatArray(doRealFreezePlayernul));
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(objectID,true,true);
        ENTITY::FREEZE_ENTITY_POSITION(objectID, true);
        ENTITY::SET_ENTITY_COLLISION(objectID,true,true);
		doRealFreezePlayernul.x++;
		doRealFreezePlayernul.y+=2;
		doRealFreezePlayernul.z+=3;
		if (doRealFreezePlayernul.x > 360)
			doRealFreezePlayernul.x = 0;
		if (doRealFreezePlayernul.y > 360)
			doRealFreezePlayernul.y = 0;
		if (doRealFreezePlayernul.z > 360)
			doRealFreezePlayernul.z = 0;
		doRealFreezePlayerCount++;
		if (doRealFreezePlayerCount < 2)
			OBJ::forceCreateObject("p_ing_skiprope_01",nullvec3,doRealFreezePlayernul,false,doRealFreezePlayerReturn);
	}
	void doRealFreezePlayer(int player) {
		doRealFreezePlayerCount = 0;
		doRealFreezePlayerPlayer = player;
		OBJ::forceCreateObject("p_ing_skiprope_01",doRealFreezePlayernul,doRealFreezePlayernul,false,doRealFreezePlayerReturn);
	}*/






	MyObject objectListForArrayAttach[100];
	int lengthForArrayAttach = 0;
	int currentLengthForArrayAttach = 0;
	int playerForArrayAttach = 0;
	bool dontAttach = false;
	bool setInvisibleBall = false;
	int playerGodmodeBalls[18];
	void invisibleBallLoop() {
		for (int i = 0; i < 18; i++) {
			if (playerGodmodeBalls[i] > 0x10000) {
				char *name = PLAYER::GET_PLAYER_NAME(i);
				if (isPlayerValid(name)) {
					poolManipulations::invisibleAllEntities(PLAYER::GET_PLAYER_PED(i));
					/*if (playerGodmodeBalls[i] > 0x10000) {
						int gb = entityToIndex(playerGodmodeBalls[i]);//NETWORK::NETWORK_GET_ENTITY_FROM_NETWORK_ID(playerGodmodeBalls[i]);
						if (ENTITY::DOES_ENTITY_EXIST(gb)) {
							netreq::reqent(gb);
							if (netreq::hasent(gb)) {
								ENTITY::SET_ENTITY_VISIBLE(gb,false);
								*(volatile unsigned int*)(getEntityFromIndex(gb) no need to reconvert cuz its the addressplayerGodmodeBalls[i]+0xB4) = 0xFFFFFFFF;
								ENTITY::SET_ENTITY_LOD_DIST(gb,99999999);
								Vector3 p = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(i),1);
								FIRE::STOP_FIRE_IN_RANGE(p.x,p.y,p.z,3);
								//GAMEPLAY::CLEAR_AREA_OF_PROJECTILES would mess up their shooting
							}
						}
					}*/
					
				} else {
					//if (playerGodmodeBalls[i] > 0x10000) {//ball exists
						//poolManipulations::detachAllEntities(PLAYER::GET_PLAYER_PED(i));//player is gone who cares if it is still there
						playerGodmodeBalls[i] = 0;
					//}
					/*if (playerGodmodeBalls[i] > 0x10000) {//ball exists
						int ent = entityToIndex(playerGodmodeBalls[i]);
						forge::markEntityForDeletion(ent);
					}
					if (ENTITY::DOES_ENTITY_EXIST(NETWORK::NET_TO_ENT(playerGodmodeBalls[i]))) {
						forge::markEntityForDeletion(NETWORK::NET_TO_ENT(playerGodmodeBalls[i]));
						playerGodmodeBalls[i] = 0;
					}*/
				}
			}
		}
	}
	void disableDemigod(int player) {
		/*if (playerGodmodeBalls[player] > 0x10000) {
			int gb = entityToIndex(playerGodmodeBalls[player]);//NETWORK::NET_TO_ENT(playerGodmodeBalls[player]);
			//printf("After Delete: Ent: %i, Net: %i\n",gb,playerGodmodeBalls[player]);
			if (ENTITY::DOES_ENTITY_EXIST(gb)) {
				forge::markEntityForDeletion(gb);
				playerGodmodeBalls[player] = 0;
			}
		}*/
		if (playerGodmodeBalls[player] > 0x10000) {//ball exists
			//poolManipulations::detachAllEntities(PLAYER::GET_PLAYER_PED(i));//player is gone who cares if it is still there
			playerGodmodeBalls[player] = 0;
		}
	}
	bool isPlayerGodmodeEnabled(int player) {
		return playerGodmodeBalls[player] != 0;
	}
	void attachHotdogToPlayer(int player);
	//returns what it is changed to after the function is ran
	bool togglePlayerGodmode(int player) {
		 if(isPlayerGodmodeEnabled(player)) {
			 //turn it off
			 disableDemigod(player);
			 return false;
		 } else {
			 playerGodmodeBalls[player] = 1;
			 attachHotdogToPlayer(player);
			 return true;
		 }
	}
	void arrayAttachCallback(int previousProp) {
		//assume that previousProp was spawned successfully
		if (setInvisibleBall) {
			disableDemigod(playerForArrayAttach);
			//ENTITY::SET_ENTITY_PROOFS(previousProp,true,true,true,true,true,false,false,false);
			*(volatile unsigned int*)(getEntityFromIndex(previousProp)+0xB4) = 0xFFFFFFFF;
			//ENTITY::SET_ENTITY_ALPHA(previousProp,0,0);
			ENTITY::SET_ENTITY_LOD_DIST(previousProp,99999999);
			ENTITY::SET_ENTITY_VISIBLE(previousProp,false);
			playerGodmodeBalls[playerForArrayAttach] = getEntityFromIndex(previousProp);//NETWORK::VEH_TO_NET(previousProp);
			//printf("After Make: Ent: %i, Net: %i\n",previousProp,playerGodmodeBalls[playerForArrayAttach]);
		}

		if (!dontAttach)
			OBJ::attachPropAlreadySpawned(playerForArrayAttach,objectListForArrayAttach[currentLengthForArrayAttach].bone,previousProp,objectListForArrayAttach[currentLengthForArrayAttach].pos,objectListForArrayAttach[currentLengthForArrayAttach].rot);
		if (dontAttach) {
			Vector3 p = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(playerForArrayAttach),1);
			ENTITY::SET_ENTITY_COORDS(previousProp,objectListForArrayAttach[currentLengthForArrayAttach].pos.x+p.x,objectListForArrayAttach[currentLengthForArrayAttach].pos.y+p.y,objectListForArrayAttach[currentLengthForArrayAttach].pos.z+p.z,objectListForArrayAttach[currentLengthForArrayAttach].rot.x,objectListForArrayAttach[currentLengthForArrayAttach].rot.y,objectListForArrayAttach[currentLengthForArrayAttach].rot.z,true);
			ENTITY::SET_ENTITY_ROTATION(previousProp,objectListForArrayAttach[currentLengthForArrayAttach].rot.x,objectListForArrayAttach[currentLengthForArrayAttach].rot.y,objectListForArrayAttach[currentLengthForArrayAttach].rot.z,1,1);
		}
		//printf("Prop %i attached",currentLengthForArrayAttach);
		currentLengthForArrayAttach++;
		if (currentLengthForArrayAttach < lengthForArrayAttach) {
			OBJ::forceCreateObject(objectListForArrayAttach[currentLengthForArrayAttach].prop,objectListForArrayAttach[currentLengthForArrayAttach].pos,objectListForArrayAttach[currentLengthForArrayAttach].rot,dontAttach,arrayAttachCallback);
		} else {
			lengthForArrayAttach = 0;
			currentLengthForArrayAttach = 0;
			playerForArrayAttach = 0;
			setInvisibleBall = false;
		}
	}

	void arrayAttach(int player, MyObject objectList[], int length, int attachToPlayer = true) {
		dontAttach = !attachToPlayer;
		lengthForArrayAttach = length;
		currentLengthForArrayAttach = 0;
		for (int i = 0; i < length; i++) {
			objectListForArrayAttach[i].bone = objectList[i].bone;
			objectListForArrayAttach[i].prop = objectList[i].prop;
			objectListForArrayAttach[i].rot.x = objectList[i].rot.x;
			objectListForArrayAttach[i].rot.y = objectList[i].rot.y;
			objectListForArrayAttach[i].rot.z = objectList[i].rot.z;
			objectListForArrayAttach[i].pos.x = objectList[i].pos.x;
			objectListForArrayAttach[i].pos.y = objectList[i].pos.y;
			objectListForArrayAttach[i].pos.z = objectList[i].pos.z;
		}
		playerForArrayAttach = player;
		if (lengthForArrayAttach > 0) {
			OBJ::forceCreateObject(objectListForArrayAttach[0].prop,objectListForArrayAttach[0].pos,objectListForArrayAttach[0].rot,dontAttach,arrayAttachCallback);
		}
	}


































	int arrayAttachVehicleID = 0;
	void arrayAttachVehicleCallback(int previousProp) {
		//assume that previousProp was spawned successfully
		OBJ::attachPropAlreadySpawnedObject(arrayAttachVehicleID,objectListForArrayAttach[currentLengthForArrayAttach].bone,previousProp,objectListForArrayAttach[currentLengthForArrayAttach].pos,objectListForArrayAttach[currentLengthForArrayAttach].rot);
		currentLengthForArrayAttach++;
		if (currentLengthForArrayAttach < lengthForArrayAttach) {
			VehicleMods::spawnVehicle(objectListForArrayAttach[currentLengthForArrayAttach].prop,arrayAttachVehicleCallback);
		} else {
			lengthForArrayAttach = 0;
			currentLengthForArrayAttach = 0;
			arrayAttachVehicleID = 0;
		}
	}

	void arrayAttachVehicle(int objectToAttachTo, MyObject objectList[], int length) {
		lengthForArrayAttach = length;
		currentLengthForArrayAttach = 0;
		for (int i = 0; i < length; i++) {
			objectListForArrayAttach[i].bone = objectList[i].bone;
			objectListForArrayAttach[i].prop = objectList[i].prop;
			objectListForArrayAttach[i].rot.x = objectList[i].rot.x;
			objectListForArrayAttach[i].rot.y = objectList[i].rot.y;
			objectListForArrayAttach[i].rot.z = objectList[i].rot.z;
			objectListForArrayAttach[i].pos.x = objectList[i].pos.x;
			objectListForArrayAttach[i].pos.y = objectList[i].pos.y;
			objectListForArrayAttach[i].pos.z = objectList[i].pos.z;
		}
		arrayAttachVehicleID = objectToAttachTo;
		if (lengthForArrayAttach > 0) {
			VehicleMods::spawnVehicle(objectListForArrayAttach[0].prop,arrayAttachVehicleCallback);
		}
	}









	MyObject ballMan[19];
	MyObject piss[1];
	MyObject hotdogDick[1];
	//const int houseSize = 16+16+6+6+8;
	//MyObject house[houseSize];//16 for floor, 16 for roof
	//MyObject tankRobot[100];
	char *sandblock = "prop_mb_sandblock_01";
	//y goes from front to back of player
	//x goes from size to side
	//z goes up and down
	void initPropCostumes() {
		//ball
		for (int i = 0; i < 19; i++) {
			ballMan[i].prop = "prop_swiss_ball_01";
			/*ballMan[i].pos.x = 0;
			ballMan[i].pos.y = 0;
			ballMan[i].pos.z = 0;
			ballMan[i].rot.x = 0;
			ballMan[i].rot.y = 0;
			ballMan[i].rot.z = 0;*/
		}
		ballMan[0].bone = bones::BONE_ROOT;
		ballMan[1].bone = bones::Chest;
		ballMan[2].bone = bones::Gentils;
		ballMan[3].bone = bones::Head;
		ballMan[4].bone = bones::Left_Arm;
		ballMan[5].bone = bones::Left_Hand;
		ballMan[6].bone = bones::Left_Knee;
		ballMan[7].bone = bones::Left_Shoe;
		ballMan[8].bone = bones::Left_Shoulder;
		ballMan[9].bone = bones::Left_Wrist;
		ballMan[10].bone = bones::Left_Wrist2;
		ballMan[11].bone = bones::Month;
		ballMan[12].bone = bones::Right_Arm;
		ballMan[13].bone = bones::Right_Hand;
		ballMan[14].bone = bones::Right_Knee;
		ballMan[15].bone = bones::Right_Shoe;
		ballMan[16].bone = bones::Right_Shoulder;
		ballMan[17].bone = bones::Right_Wrist;
		ballMan[18].bone = bones::Umbilical;

		piss[0].bone = bones::BONE_ROOT;
		piss[0].rot.x = -90;
		piss[0].prop = "prop_sprink_golf_01";

		//hotdog dick
		hotdogDick[0].bone = bones::BONE_ROOT;
		hotdogDick[0].prop = "prop_juicestand"/*"prop_cs_hotdog_02"*/;
		//hotdogDick[0].pos.x+=0.05f;

		/*
		int currentHouseIndex = 0;
		for (int x = 0; x < 4; x++) {//bottom
			for (int y = 0; y < 4; y++) {
				house[currentHouseIndex].pos.x = x*1.5f;
				house[currentHouseIndex].pos.y = y*1.5f;
				house[currentHouseIndex].pos.z = 0;
				house[currentHouseIndex].pos.x+=1;
				house[currentHouseIndex].prop = sandblock;
				currentHouseIndex++;
			}
		}
		for (int x = 0; x < 4; x++) {//top
			for (int y = 0; y < 4; y++) {
				house[currentHouseIndex].pos.x = x*1.5f;
				house[currentHouseIndex].pos.y = y*1.5f;
				house[currentHouseIndex].pos.z = 1.5*3;
				house[currentHouseIndex].pos.x+=1;
				house[currentHouseIndex].prop = sandblock;
				currentHouseIndex++;
			}
		}
		for (int x = 0; x < 3; x++) {//left wall
			for (int y = 1; y < 3; y++) {
				house[currentHouseIndex].pos.x = x*1.5f;
				house[currentHouseIndex].pos.y = 0;
				house[currentHouseIndex].pos.z = y*1.5f;
				house[currentHouseIndex].pos.x+=1;
				house[currentHouseIndex].prop = sandblock;
				currentHouseIndex++;
			}
		}
		for (int x = 0; x < 3; x++) {//right wall
			for (int y = 1; y < 3; y++) {
				house[currentHouseIndex].pos.x = x*1.5f;
				house[currentHouseIndex].pos.y = 3*1.5;
				house[currentHouseIndex].pos.z = y*1.5f;
				house[currentHouseIndex].pos.x+=1;
				house[currentHouseIndex].prop = sandblock;
				currentHouseIndex++;
			}
		}
		for (int x = 0; x < 4; x++) {
			for (int y = 1; y < 3; y++) {//back wall
				house[currentHouseIndex].pos.x = 3*1.5;
				house[currentHouseIndex].pos.y = x*1.5f;
				house[currentHouseIndex].pos.z = y*1.5f;
				house[currentHouseIndex].pos.x+=1;
				house[currentHouseIndex].prop = sandblock;
				currentHouseIndex++;
			}
		}
		*/

	}

	void attachBallManToPlayer(int player) {
		arrayAttach(player,ballMan,19);
	}

	/*void attachGodmodeBallManToPlayer(int player) {
		setInvisibleBall = true;
	}*/

	void attachHotdogToPlayer(int player) {
		setInvisibleBall = true;
		arrayAttach(player,hotdogDick,1);
	}

	void attachPissToPlayer(int player) {
		arrayAttach(player,piss,1);
	}

	/*void spawnHouse(int player) {
		arrayAttach(player,house,houseSize,false);
	}*/


	/*void removeProps(int player) {
		Entity attachedEnt = ENTITY::GET_ENTITY_ATTACHED_TO(PLAYER::GET_PLAYER_PED(player));
		if (ENTITY::DOES_ENTITY_EXIST(attachedEnt)) {
			if (ENTITY::IS_ENTITY_A_VEHICLE(attachedEnt) == false) {
				//forge::markEntityForDeletion(attachedEnt);
			}
		}
	}*/

	/*void removeAPlayerProp(int player) {
		int Type = -1;
		bool hit = true;
		float radius = 0.2f;
		int entityhandle = 0;
		Vector3 hitCoords, surfaceNormal;
		Vector3 tmp = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(player),true);
		int ray = WORLDPROBE::_0x591EA833(tmp.x,tmp.y,tmp.z+4,tmp.x,tmp.y,tmp.z,radius,Type,PLAYER::GET_PLAYER_PED(player),7);
		WORLDPROBE::_0xF3C2875A(ray, &hit, &hitCoords, &surfaceNormal, &entityhandle);
		if (ENTITY::DOES_ENTITY_EXIST(entityhandle) && PED::IS_PED_A_PLAYER(entityhandle) == false) {
			forge::markEntityForDeletion(entityhandle);
			print("Deleting one of the players attached props!");
		} else {
			print("Could not find a prop attached to the player!");
		}
		//char buf[50];
		//snprintf$$(buf,sizeof(buf),"x: %f y: %f z: %f       %f",hitCoords.x,hitCoords.y,hitCoords.z,cx);
		//print(buf);
	}*/


	/*int flcam = 0;
	void freezeLobbyRetFunc(int i) {
		flcam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA",1);
		Vector3 coords = {0.0,0.15,0.02};
		//CAM::ATTACH_CAM_TO_PED_BONE(flcam,PLAYER::PLAYER_PED_ID(),31086,coords.x,coords.y,coords.z,1);
		//CAM::SET_CAM_INHERIT_ROLL_VEHICLE(cam,true);
		CAM::SET_CAM_COORD(flcam,0,0,0);
		CAM::SET_CAM_ACTIVE(flcam,1);
		CAM::RENDER_SCRIPT_CAMS(1,0,3000,1,0);

		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(),0,4,4,2);
	}
	void freezeLobbyRetFunc2(int i) {
			if (CAM::DOES_CAM_EXIST(flcam)) {
				CAM::SET_CAM_ACTIVE(flcam,0);
				CAM::RENDER_SCRIPT_CAMS(0,0,3000,1,0);
				CAM::DESTROY_CAM(flcam,0);
			}
	}*/
#pragma region components
#ifdef componentslol
	namespace components {
		namespace myComponents {
			int texture[] = {0,0,0,0,0,0,0,0,0,0,0};
			int drawable[] = {0,0,0,0,0,0,0,0,0,0,0};
			int palette[] = {0,0,0,0,0,0,0,0,0,0,0};

			void save() {
				for (int i = 0; i < 12; i++) {
					texture[i] = PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(),i);
					drawable[i] = PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(),i);
					palette[i] = PED::GET_PED_PALETTE_VARIATION(PLAYER::PLAYER_PED_ID(),i);
				}
			}

			void load(int i) {
				for (int i = 0; i < 12; i++) {
					PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), i,drawable[i],texture[i],palette[i]);
				}
			}
		}
		int currentComponent = 0;
		char *getComponentName(int i = currentComponent) {
			if (i == 0) {
				return "Face";
			}
			if (i == 1) {
				return "Beard";
			}
			if (i == 2) {
				return "Hair";
			}
			if (i == 3) {
				return "Shirt";
			}
			if (i == 4) {
				return "Pants";
			}
			if (i == 5) {
				return "Hands";
			}
			if (i == 6) {
				return "Shoes";
			}
			if (i == 7) {
				return "Eyes";
			}
			if (i == 8) {
				return "Accessories";
			}
			if (i == 9) {
				return "Mission Items";
			}
			if (i == 10) {
				return "Decals";
			}
			if (i == 11) {
				return "Collars";
			}
			return "Invalid Component";
		}
		void setFace(int ped, int value) {
			PED::SET_PED_COMPONENT_VARIATION(ped, 0, PED::GET_PED_DRAWABLE_VARIATION(ped,0), value, PED::GET_PED_PALETTE_VARIATION(ped, 0));
		}
		int getTexture(int ped,int id){
			return PED::GET_PED_TEXTURE_VARIATION(ped,id);
		}
		int getTexture(){
			return PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(),currentComponent);
		}
		int getDrawable() {
			return PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(),currentComponent);
		}
		int getPalette() {
			return PED::GET_PED_PALETTE_VARIATION(PLAYER::PLAYER_PED_ID(),currentComponent);
		}
		void textureAdd() {
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), currentComponent, PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(),currentComponent), PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(),currentComponent)+1, PED::GET_PED_PALETTE_VARIATION(PLAYER::PLAYER_PED_ID(), currentComponent));
		}
		void textureMinus() {
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), currentComponent, PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(),currentComponent), PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(),currentComponent)-1, PED::GET_PED_PALETTE_VARIATION(PLAYER::PLAYER_PED_ID(), currentComponent));
		}
		void drawableAdd() {
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), currentComponent, PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(),currentComponent)+1, PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(),currentComponent), PED::GET_PED_PALETTE_VARIATION(PLAYER::PLAYER_PED_ID(), currentComponent));
		}
		void drawableMinus() {
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), currentComponent, PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(),currentComponent)-1, PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(),currentComponent), PED::GET_PED_PALETTE_VARIATION(PLAYER::PLAYER_PED_ID(), currentComponent));
		}
		void paletteAdd() {
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), currentComponent, PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(),currentComponent), PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(),currentComponent), PED::GET_PED_PALETTE_VARIATION(PLAYER::PLAYER_PED_ID(), currentComponent)+1);
		}
		void paletteMinus() {
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), currentComponent, PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(),currentComponent), PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(),currentComponent), PED::GET_PED_PALETTE_VARIATION(PLAYER::PLAYER_PED_ID(), currentComponent)-1);
		}
	}
#endif
#pragma endregion
	bool enabledAimbot[] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};
	void aimBotLoop() {
		for (int player = 0; player < 18; player++)
			if (enabledAimbot[player] == true)
				if (PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED(player)))
					for (int victim = 0; victim < 18; victim++)
						if (victim != player) {
							Vector3 vloc = OBJ::getOtherPlayerPos(victim);
							if (NETWORK::IS_SPHERE_VISIBLE_TO_PLAYER(player,vloc.x,vloc.y,vloc.z,1))
								PlayerMods::playerExplodePlayerSilent(player,victim);
						}
	}
	void togglePlayerAimbot(int player) {
		enabledAimbot[player] = !enabledAimbot[player];
	}
	bool isAimbotEnabled(int player) {
		return enabledAimbot[player];
	}
	void teleportIntoPlayerVehicle(int player) 
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(player),true)) {
		int vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(player),false);
			for (int SeatIndex = -1; SeatIndex < 10; SeatIndex++) 
			{
				if (VEHICLE::IS_VEHICLE_SEAT_FREE(vehicle, SeatIndex))
				{
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, SeatIndex);
					break;
				}
			}
		} else {
			print("~r~Player not in a vehicle");
		}
	}

	Vector3 tmplochehe = {0,0,0};
	void VehicleGunReturnFunction(int vehicle) {
		Vector3 tmp = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true);
		Vector3 c = noclip::GET_COORDS_INFRONT(5);
		tmplochehe.x = tmp.x+c.x;
		tmplochehe.y = tmp.y+c.y;
		tmplochehe.z = tmp.z+c.z;
		Vector3 ro = CAM::GET_GAMEPLAY_CAM_ROT(2);
		ENTITY::SET_ENTITY_COORDS(vehicle,tmplochehe.x,tmplochehe.y,tmplochehe.z,ro.x,ro.y,ro.z,0);
		VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, 100.0);
	}
	bool enabledVehicleGun = false;
	bool chickenbob = 0;
	void VehicleGunLoop() {
		setNPTypeLoop();
		//if (chickenbob > 10) {
			if (enabledVehicleGun == true) {
				if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID())) {
					if (!chickenbob) {
						chickenbob = true;
						VehicleMods::spawnVehicle("adder",VehicleGunReturnFunction);
					}
				} else {
					chickenbob = false;
				}
			}
		//}
		//chickenbob++;
	}

	bool revengeEnabled = false;

	void revenge() {
		if (revengeEnabled)
		for (int i = 0; i < 18; i++) {
			if ( PLAYER::IS_PLAYER_TARGETTING_ENTITY(i,PLAYER::PLAYER_PED_ID()) ) {
				explodePlayer(i);
			}
		}
	}

	bool flashBool = false;
	void flash() {
		if (flashBool) {
			if (AI::IS_PED_RUNNING(PLAYER::PLAYER_PED_ID()) || AI::IS_PED_SPRINTING(PLAYER::PLAYER_PED_ID())) {
				//forceEntity(PLAYER::PLAYER_PED_ID(),0,0,0.5,0,0,0,1);//walk upwards
				//PLAYER::_0x825423C2(PLAYER::PLAYER_ID(), 1.49f);
				forceEntity(PLAYER::PLAYER_PED_ID(),0,6,0,0,0,0);
			}
		}
	}

#ifdef hulkmod
	bool hulkBool = false;
	void hulk() {
		if (hulkBool) {
			PlayerMods::allowRagdoll(false);
			for (int i = 0; i < 10; i++)
				PED::_0x9C8F830D(PLAYER::PLAYER_PED_ID(),i);
			/*if (AI::IS_PED_RUNNING(PLAYER::PLAYER_PED_ID())) {
				forceEntity(PLAYER::PLAYER_PED_ID(),0,1.5,0,0,0,0);
			}*/
			if (AI::IS_PED_SPRINTING(PLAYER::PLAYER_PED_ID())) {
				forceEntity(PLAYER::PLAYER_PED_ID(),0,4,0,0,0,0);
			}
			if (!ENTITY::IS_ENTITY_IN_AIR(PLAYER::PLAYER_PED_ID()) && !PED::IS_PED_FALLING(PLAYER::PLAYER_PED_ID()) && PED::IS_PED_JUMPING(PLAYER::PLAYER_PED_ID())) {
				forceEntity(PLAYER::PLAYER_PED_ID(),0,0,25,0,0,0);
			}
			if (PED::IS_PED_RUNNING_RAGDOLL_TASK(PLAYER::PLAYER_PED_ID())) {
				AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
			}
		}
	}
#endif
	bool forcefield[18] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};
	void forceFieldLoop() {
		for (int i = 0; i < 18; i++) 
			if (forcefield[i])
				PlayerMods::explodePlayerSilent(i);
	}
	void toggleForceField(int player) {
		forcefield[player] = !forcefield[player];
	}
	bool getForceField(int player) {
		return forcefield[player];
	}

	int killInGodModePlayer = 0;
	int killInGodModeTimeout = 0;
	bool killInGodModeEnabled = false;
	void killInGodModeLoop() {
		if (killInGodModeEnabled) {
			killInGodModeTimeout++;
			if (killInGodModeTimeout > 40) {
				killInGodModeTimeout = 0;
				killInGodModeEnabled = false;
				PlayerMods::attachPlayerToPlayer(killInGodModePlayer ,killInGodModePlayer ,0,0,-10000);
			}
		}
	}
	void killInGodMode(int player) {
		killInGodModeTimeout = 0;
		killInGodModeEnabled = true;
		killInGodModePlayer = player;
		PlayerMods::teleportToLoc(player,574,-4182,537);
	}
};
/*

{

     func_4268(&Param2, &Param3, "XP_REWARD", Global_2394218.imm_676[uParam0 <29>].imm_3, iVar7);

    }

    else if (Global_2394218.imm_676[uParam0 <29>].imm_8 == 7 || Global_2394218.imm_676[uParam0 <29>].imm_8 == 6)

    {

     func_4268(&Param2, &Param3, "CASH_REWARD", Global_2394218.imm_676[uParam0 <29>].imm_3, iVar7);

    }

*/
#pragma endregion




#pragma region Vehicle Mods
namespace VehicleMods {
	void maxOutCar(int VehicleHandle) {
		VEHICLE::SET_VEHICLE_MOD_KIT(VehicleHandle, 0);
		for (int i = 0; i < 25; i++) {
			VEHICLE::SET_VEHICLE_MOD(VehicleHandle, i, VEHICLE::GET_NUM_VEHICLE_MODS(VehicleHandle,i)-1, 0);
		}
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(VehicleHandle, "paradise");
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(VehicleHandle, 5);
		VEHICLE::TOGGLE_VEHICLE_MOD(VehicleHandle, 18, 1);
		VEHICLE::TOGGLE_VEHICLE_MOD(VehicleHandle, 22, 1);
		VEHICLE::SET_VEHICLE_WHEEL_TYPE(VehicleHandle, 6);
		VEHICLE::SET_VEHICLE_WINDOW_TINT(VehicleHandle, 5);
		VEHICLE::TOGGLE_VEHICLE_MOD(VehicleHandle, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(VehicleHandle, 0, 0, 0);
	}
	void max() {
		lobbyModMenu::maxOutCar(PLAYER::PLAYER_ID());
	}
	void getControlOfCurrentVehicle() {
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(),false)) {netreq::reqent(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()));}
	}
	int waitVehicleSpawn = 0;
	bool doSpawnVehicleLoop = false;
	int doSpawnVehicleLoopTimeout = 0;
	bool MaxOnSpawn = false;
	void (*saveFunc)(int) = nullFunc;
	void (*callbackFailFunc)(int) = nullFunc;

	/*int CREATE_VEHICLE_ONLINE_COORD(uint hash, float* coords) {
		STREAMING::REQUEST_MODEL(hash);
		if (STREAMING::IS_MODEL_IN_CDIMAGE(hash) && STREAMING::IS_MODEL_A_VEHICLE(hash)) {
			if(STREAMING::HAS_MODEL_LOADED(hash)) {
				return VEHICLE::CREATE_VEHICLE(hash, coords[0],coords[1],coords[2], 0, 1, 0);
			}
		}
		return 0;
	}

	int spawnVehicleLoc(int modelhash, float* coords) {
		return CREATE_VEHICLE_ONLINE_COORD(modelhash, coords);
	}*/

	void setIntoVehicle(int vehicle) {
		for (int SeatIndex = -1; SeatIndex < 10; SeatIndex++) 
			{
				if (VEHICLE::IS_VEHICLE_SEAT_FREE(vehicle, SeatIndex))
				{
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, SeatIndex);
					break;
				}
			}
	}

	int spawnVehicleInstant(int id) {
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),0);
		//float co[3] = {coords.x+2,coords.y,coords.z};
		int vehicle = create_vehicle::CREATE_VEHICLE(id,coords.x+2,coords.y,coords.z);
		return vehicle;
	}

	void spawnVehicle(char model[], void(*f)(int)) {// = nullFunc
		doSpawnVehicleLoop = true;
		doSpawnVehicleLoopTimeout = 0;
		waitVehicleSpawn = GAMEPLAY::GET_HASH_KEY(model);
		saveFunc = f;
	}
	bool spawnInsideOfCar;
	bool spawnAsMaxed = true;
	float spawnGravity = 9.8f;
	float spawnSuspension = 0;
	void setVehicleColor(int color, bool secondary);
	void setColorRGBCar(int r, int g, int b);
	void returnFuncToSpawnInsideVehicle(int vehicle) {
		if (spawnInsideOfCar) {
			/*for (int SeatIndex = -1; SeatIndex < 10; SeatIndex++) 
			{
				if (VEHICLE::IS_VEHICLE_SEAT_FREE(vehicle, SeatIndex))
				{
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, SeatIndex);
					break;
				}
			}*/
			setIntoVehicle(vehicle);
		}
		if (spawnAsMaxed) {
			maxOutCar(vehicle);
			VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
			VEHICLE::SET_VEHICLE_COLOURS(vehicle, 120, 120);
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle,GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0,255),GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0,255),GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0,255));
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle,GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0,255),GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0,255),GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0,255));
			//setColorRGBCar(GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0,255),GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0,255),GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0,255),vehicle);
		}
		setVehicleSuspension(vehicle,getVehicleSuspension(vehicle)-spawnSuspension);
		setVehicleGravity(vehicle,spawnGravity);
	}
	void spawnVehicle(int modelhash, void(*f)(int) = nullFunc, void(*callbackFail)(int) = nullFunc) {
		doSpawnVehicleLoop = true;
		doSpawnVehicleLoopTimeout = 0;
		waitVehicleSpawn = modelhash;
		saveFunc = f;
		callbackFailFunc = callbackFail;
	}

	void spawnVehicleLoop() {
		if (doSpawnVehicleLoop == true) {
			doSpawnVehicleLoopTimeout++;
			if (doSpawnVehicleLoopTimeout < 1000) {
				int vehicle = spawnVehicleInstant(waitVehicleSpawn);
				if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
					doSpawnVehicleLoopTimeout = 0;
					doSpawnVehicleLoop = false;
					saveFunc(vehicle);
				}
			} else {
				doSpawnVehicleLoopTimeout = 0;
				doSpawnVehicleLoop = false;
				print("~r~Could not spawn vehicle");
				callbackFailFunc(-1);
			}
		}
		
	}

	int Color1 = 0,Color2 = 0,Color3 = 0,Color4 = 0;
	int rgbred=0,rgbgreen=0,rgbblue=0;
	bool extras[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	void setVehicleColor(int color, bool secondary) {
		int VehicleHandle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		VEHICLE::SET_VEHICLE_MOD_KIT(VehicleHandle, 0);
		int col1 = 0,col2 = 0;
		VEHICLE::GET_VEHICLE_COLOURS(VehicleHandle,&col1,&col2);
		if (secondary == false) {
			VEHICLE::SET_VEHICLE_COLOURS(VehicleHandle, color, col2);
		} else {
			VEHICLE::SET_VEHICLE_COLOURS(VehicleHandle, col1, color);
		}
	}

	void setVehiclePearl(int color) {
		int VehicleHandle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		VEHICLE::SET_VEHICLE_MOD_KIT(VehicleHandle, 0);
		int col1 = 0,col2 = 0;
		VEHICLE::GET_VEHICLE_EXTRA_COLOURS(VehicleHandle,&col1,&col2);
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(VehicleHandle, color, col2);
	}

	void setVehicleWheelColor(int color) {
		int VehicleHandle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		VEHICLE::SET_VEHICLE_MOD_KIT(VehicleHandle, 0);
		int col1 = 0,col2 = 0;
		VEHICLE::GET_VEHICLE_EXTRA_COLOURS(VehicleHandle,&col1,&col2);
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(VehicleHandle, col1, color);
	}

	void setTireSmokeColor(int r, int g, int b, bool patriot) {
		int VehicleHandle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		VEHICLE::SET_VEHICLE_MOD_KIT(VehicleHandle, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(VehicleHandle, 20, patriot);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(VehicleHandle, r, g, b);
	}

	void setColorRGBCar(int r, int g, int b) {
		int VehicleHandle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		VEHICLE::SET_VEHICLE_MOD_KIT(VehicleHandle, 0);
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(VehicleHandle,r,g,b);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(VehicleHandle,r,g,b);
	}

	void setVehicleMod(int mod, int value) {//mod is 15 for suspension
		int VehicleHandle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		VEHICLE::SET_VEHICLE_MOD_KIT(VehicleHandle, 0);
		VEHICLE::SET_VEHICLE_MOD(VehicleHandle, mod, value, 0);
	}

	int getMyVehicle() {
		int VehicleHandle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		return VehicleHandle;
	}

	int getPlayerVehicle(int player) {
		int VehicleHandle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(player));
		return VehicleHandle;
	}

	void setVehicleOwnedByPlayer(int vehicle, int player) {
		if (!netreq::hasent(vehicle)) {
			print2("Please gain control of vehicle");
			return;
		}
		int nameHash = GAMEPLAY::GET_HASH_KEY(PLAYER::GET_PLAYER_NAME(player));
		int nameHash2 = _0xF8D7AF3B(player);
		printf("Name hashes: 0x%X 0x%X\n",nameHash,nameHash2);
		DECORATOR::DECOR_SET_INT(vehicle,"Not_Allow_As_Saved_Veh",0);//0 should allow it to be stored, 1 or playerhash means cant store according to garage
		DECORATOR::DECOR_SET_INT(vehicle,"Player_Vehicle",nameHash/*_0xF8D7AF3B(player)*//*-1 to be not owned*/);//unk_0xF8D7AF3B which is network hash from player, can be that or -1 to say owner
		DECORATOR::DECOR_SET_INT(vehicle,"Veh_Modded_By_Player",nameHash);
		DECORATOR::DECOR_SET_INT(vehicle,"Previous_Owner",-1/*-1 to be not owned*/);//same value type as Player_Vehicle
		//DECORATOR::DECOR_SET_INT(vehicle,"PV_Slot",0);//not sure real value, sometimes used 0 or -1
		print2("Set!");
	}
	
	int curShopPart = 0;
	int maxVehOptions = 0;
	char curShopPartText[50];
	
	int Spoilers_id = 0,
	Front_Bumper_id = 1,
	Rear_Bumper_id = 2,
	Side_Skirt_id = 3,
	Exhaust_id = 4,
	Frame_id = 5,
	Grille_id = 6,
	Hood_id = 7,
	Fender_id = 8,
	Right_Fender_id = 9,
	Roof_id = 10,
	Engine_id = 11,
	Brakes_id = 12,
	Transmission_id = 13,
	Horns_id = 14,
	Suspension_id = 15,
	Armor_id = 16,
	Front_Wheels_id = 23,
	Back_Wheels_id = 24;

	int getMaxMods(int id) {
		int VehicleHandle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		VEHICLE::SET_VEHICLE_MOD_KIT(VehicleHandle, 0);
		return VEHICLE::GET_NUM_VEHICLE_MODS(VehicleHandle,id);
	}
	
	void saveinsideofvehiclemenu() {
			int VehicleHandle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			VEHICLE::SET_VEHICLE_MOD_KIT(VehicleHandle, 0);
			VEHICLE::GET_VEHICLE_COLOURS(VehicleHandle,&Color1,&Color2);
	}

	void insideofvehiclemenu() {
			setVehicleColor(Color1,false);
			setVehicleColor(Color2,true);
			setVehiclePearl(Color3);
			setVehicleWheelColor(Color4);
	}

	void fixandwash() {
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(),false)) {
		int VehicleHandle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		int speed = ENTITY::GET_ENTITY_SPEED(VehicleHandle);
		VEHICLE::SET_VEHICLE_FIXED(VehicleHandle);
		VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(VehicleHandle);
		VEHICLE::SET_VEHICLE_DIRT_LEVEL(VehicleHandle,0);
		int modifier = 1;
		if (pressedButtons::l2pressed)
			modifier = -1;
		VEHICLE::SET_VEHICLE_FORWARD_SPEED(VehicleHandle,speed*modifier);
		}
	}

	void godmode(bool b){
		if (b) {
			int VehicleHandle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			ENTITY::SET_ENTITY_PROOFS(VehicleHandle,b,b,b,b,b,b,b,b);
			if (VEHICLE::_0xDAC523BC(VehicleHandle)) {
				fixandwash();
			}
		}
	}

	bool enabledgodmodeloop = false;

	void randomCarSpawn() {
		int hash;
		int useless;
		VEHICLE::GET_RANDOM_VEHICLE_MODEL_IN_MEMORY(true,&hash,&useless);
		spawnVehicle(hash);
	}

	int g_pcSuperCarsInt = 0;
	int g_pcSportsCarsInt = 0;
	int g_pcSportsClassicCarsInt = 0;
	int g_pcMuscleCarsInt = 0;
	int g_pcSedansInt = 0;
	int g_pcCoupesInt = 0;
	int g_pcCompactsInt = 0;
	int g_pcSUVnTrucksInt = 0;
	int g_pcOffRoadsInt = 0;
	int g_pcVansInt = 0;
	int g_pcEmergencyCarsInt = 0;
	int g_pcServiceVehiclesInt = 0;
	int g_pcMilitaryInt = 0;
	int g_pcMotorcyclesInt = 0;
	int g_pcBicyclesInt = 0;
	int g_pcCommercialVehiclesInt = 0;
	int g_pcHelicoptersInt = 0;
	int g_pcPlanesInt = 0;
	int g_pcBoatsInt = 0;
	int g_pcTrailersInt = 0;

	char* g_pcMainMenu[20] = {"Super Cars", "Sports Cars", "Sports Classic Cars", "Muscle Cars", "Sedans", "Coupes", "Compacts", "SUVs and Trucks", "Offroad Vehicles", "Vans", "Emergency Vehicles", "Service Vehicles", "Military Vehicles", "Motorcycles", "Bicycles", "Commercial Vehicles", "Helicopters", "Planes", "Boats", "Trailers"};
	char* g_pcSuperCars[11] = { "Truffade Adder", "Overflod Entity XF", "Grotti Cheetah", "Pegassi Infernus", "Pegassi Vacca", "Vapid Bullet", "Coil Voltic", "Pegassi Zentorno", "Grotti Turismo R", "Pegassi Osiris", "Progen T20" };
	char* g_pcSportsCars[29] = { "Annis Elegy RH8", "Hijak Khamelion", "Grotti Carbonizzare", "Benefactor Feltzer 1", "Benefactor Feltzer 2", "Dewbauchee Rapid GT 1", "Inverto Coquette 1", "Dewbauchee Rapid GT 2", "Obey 9F Cabrio", "Obey 9F", "Benefactor Surano", "Bravado Banshee", "Pfister Comet", "Benefactor Schwartzer", "Schyster Fusilade", "Bravado Buffalo", "Bravado Buffalo 2", "Maibatsu Penumbra", "Karin Sultan", "Karin Futo", "Lampadati Furore GT", "Dewbauchee Massacro 1", "Dewbauchee Massacro 2", "Dinka Jester 1", "Dinka Jester 2", "Enus Windsor", "Albany Alpha", "Karin Kuruma 1", "Karin Kuruma 2" };
	char* g_pcSportsClassicCars[20] = { "Inverto Coquette 2", "Inverto Coquette 3", "Truffade Z-Type", "Grotti Stinger GT", "Grotti Stinger", "Pegassi Monroe", "Dewbauchee JB 700", "Declasse Tornado 1", "Declasse Tornado 2", "Declasse Tornado 3", "Declasse Tornado 4", "Vapid Peyote", "Albany Manana", "Albany Virgo", "Albany Roosevelt", "Vapid Blade", "Benefactor Glendale", "Lampadati Pigalle", "Lampadati Casco", "Vapid Chino" };
	char* g_pcMuscleCars[12] = { "Vapid Hotknife", "Bravado Gauntlet", "Declasse Vigero", "Vapid Dominator", "Albany Buccaneer", "Imponte Phoenix", "Declasse Sabre Turbo", "Imponte Ruiner", "Declasse Voodoo", "Cheval Picador", "Rat Loader 1", "Rat Loader 2" };
	char* g_pcSedans[23] = {"Enus Super Diamond", "Ubermacht Oracle 1", "Ubermacht Oracle 2", "Dundreary Stretch", "Cheval Fugitive", "Cheval Surge", "Benefactor Schafter", "Karin Asterope", "Karin Intruder", "Albany Washington", "Vapid Stanier", "Vulcan Ingot", "Albany Emperor 1", "Albany Emperor 2", "Albany Emperor 3", "Albany Primo", "Dundreary Regina", "Chariot Romero Hearse", "Obey Tailgater", "Declasse Premier", "Zirconium Stratum", "Declasse Asea 1", "Declasse Asea 2"};
	char* g_pcCoupes[10] = { "Dewbauchee Exemplar", "Enus Cognoscenti Cabrio", "Lampadati Felon GT", "Lampadati Felon", "Ubermacht Zion Cabrio", "Ubermacht Zion", "Ubermacht Sentinel XS", "Ubermacht Sentinel", "Ocelot F620", "Ocelot Jackal"};
	char* g_pcCompacts[8] = { "Karin Dilettante 1", "Karin Dilettante 2", "Weeny Issi", "Bollokan Prairie", "Dinka Blista", "Declasse Rhapsody", "Vulcar Warrener", "Benefactor Panto" };
	char* g_pcSUVnTrucks[28] = {"Gallivanter Baller 1", "Gallivanter Baller 2", "Obey Rocoto", "Albany Cavalcade 1", "Albany Cavalcade 2", "Benefactor Dubsta 1", "Benefactor Dubsta 2", "Benefactor Dubsta 3", "Benefactor Serrano", "Dundreary Landstalker", "Fathom FQ 2", "Mammoth Patriot", "Emperor Habanero", "Vapid Radius", "Declasse Granger", "Canis Mesa 1", "Canis Mesa 2", "Canis Seminole", "Canis Kalahari", "Bravado Gresley", "Karin BeeJay XL", "Enus Huntley", "Sadler 1", "Sadler 2", "Vapid Guardian", "HVY Insurgent 1", "HVY Insurgent 2", "Karin Technical"};
	char* g_pcOffRoads[19] = {"Monster Truck", "Vapid Sandking XL", "BF Dune Buggy", "BF Dune 2 (Space Docker)", "BF Injection", "BF Bifta", "Nagasaki Blazer 1", "Nagasaki Blazer 2 (Trevors)", "Canis Mesa (Merryweather)", "Vapid Sandking SWB", "Bravado Duneloader", "Canis Bodhi", "Declasse Rancher XL 1", "Declasse Rancher XL 2", "Karin Rebel 1", "Karin Rebel 2", "Nagasaki Blazer Lifeguard", "Coil Brawler", "Dinka Enduro"};
	char* g_pcVans[31] = {"Bravado Bison 1", "Bravado Bison 2", "Bravado Bison 3", "Bravado Paradise", "Zirconium Journey", "Vapid Minivan", "Vapid Bobcat XL", "Bravado Rumpo 1", "Bravado Rumpo 2", "Brute Pony 1", "Brute Pony 2", "Declasse Burrito 1", "Declasse Burrito 2", "Declasse Burrito 3", "Declasse Burrito 4", "Declasse Burrito 5", "Declasse Burrito 6", "Declasse Burrito 7", "Vapid Speedo 1", "Vapid Speedo 2", "Bravado Youga", "Boxville 1", "Boxville 2", "Boxville 3", "Boxville 4", "Brute Camper", "Taco Van", "BF Surfer", "BF Surfer (Rusted)", "Vapid Slamvan 1", "Vapid Slamvan 2"};
	char* g_pcEmergencyCars[18] = { "FIB", "FIB SUV", "Firetruck", "Ambulance", "Police 1", "Police 2", "Police 3", "Police 4", "Police Bike", "Police Old 1", "Police Old 2", "Police Van", "Swat Truck", "Sheriff 1", "Sheriff 2", "Prison Bus", "Park Ranger", "Life Guard SUV" };
	char* g_pcServicVehicles[6] = {"Airport Bus", "Dashhound", "Bus", "Rental Shuttle Bus", "Tour Bus", "Taxi"};
	char* g_pcMilitary[7] = { "Rhino Tank", "Barracks 1", "Barracks 2", "Barracks 3", "Canis Crusader", "Tanker 1", "Tanker 2" };
	char* g_pcMotorcycles[21] = { "Nagasaki Carbon RS", "Pegassi Bati 801RR", "Pegassi Bati 801", "LCC Hexer", "LCC Innovation", "Dinka Double-T", "Dinka Thrust", "Dinka Vindicator", "Pegassi Ruffian", "Shitzu Vader", "Shitzu PCJ 600", "Shitzu Hakuchou", "Dinka Akuma", "Maibatsu Sanchez (Decal)", "Maibatsu Sanchez", "Pegassi Faggio", "Western Daemon", "Western Bagger", "Principe Nemesis", "Sovereign", "Principe Lectro" };
	char* g_pcBicycles[7] = {"Whippet Race Bike", "Tri-Cycles Race Bike", "Scorcher", "Endurex Race Bike", "Cruiser", "BMX", "Fixter"};
	char* g_pcCommercialVehicles[39] = {"Maibatsu Mule 1", "Maibatsu Mule 2", "Maibatsu Mule 3", "JoBuilt Phantom", "Vapid Benson", "MTL Packer", "MTL Pounder", "JoBuilt Hauler", "Brute Stockade 1", "Brute Stockade 2", "HVY Biff", "HVY Dump", "HVY Dozer", "HVY Forklift", "HVY Handler", "HVY Cutter", "Utility Truck 1", "Utility Truck 2", "Utility Truck 3", "Trashmaster 1", "Trashmaster 2", "Towtruck 1", "Towtruck 2", "TipTruck 1", "TipTruck 2", "Mixer 1", "Mixer 2", "Flatbed Truck", "Airport Ripley", "Rubble", "Vapid Scrap Truck", "Lawnmower", "Dock Tug", "Airport Tug", "Tractor 1", "Tractor 2", "Tractor 3", "Caddy 1", "Caddy 2"};
	char* g_pcHelicopters[14] = {"Annihilator", "Buzzard Attack Chopper 1", "Buzzard Attack Chopper 2", "Frogger 1", "Frogger 2", "Maverick", "Cargobob 1", "Cargobob 2", "Cargobob 3", "Police Maverick", "Swift 1", "Swift 2", "Buckingham Valkyrie", "Savage"};
	char* g_pcPlanes[19] = {"Titan", "Buckingham Luxor 1", "Buckingham Luxor 2", "Buckingham Shamal", "Buckingham Vestra", "Buckingham Miljet", "Velum 1", "Velum 2", "Mammatus", "Duster", "Mallard", "Cuban 800", "Cargo Plane", "Blimp", "P-996 Lazer", "Skylift", "Jet", "Bersa", "Mammoth Hydra"};
	char* g_pcBoats[14] = {"Dinka Marquis", "Shitzu Jetmax", "Shitzu Squalo", "Shitzu Suntrap", "Shitzu Tropic", "Speedophile Seashark 1", "Speedophile Seashark 2", "Police Predator", "Submarine", "Pegassi Speeder", "Nagasaki Dinghy 1", "Nagasaki Dinghy 2", "Nagasaki Dinghy 3", "Lampadati Toro"};
	char* g_pcTrailers[27] = {"Army Tanker", "Army Trailer 1", "Army Trailer 2", "Bale Trailer", "Boat Trailer", "Cablecar", "Dock Trailer", "Freight Car 1", "Freight Car 2", "Freight Container 1", "Freight Container 2", "Freight Train Boxcar", "Grain Trailer", "Metro Train", "Mobile Home Trailer", "Rake Trailer", "Train Fuel Tank Car", "Car Carrier Trailer", "Marquis Trailer", "Super Car Carrier Trailer", "Trailer Logs", "Trailers 1", "Trailers 2", "Trailers 3", "Trailer Small", "Trailer Flat", "Tv Trailer"};
	
	unsigned int g_uiSuperCars[11] = { 0xB779A091, 0xB2FE5CF9, 0xB1D95DA0, 0x18F25AC7, 0x142E0DC3, 0x9AE6DDA1, 0x9F4B77BE, 0xAC5DF515, 0x185484E1, 0x767164D6, 0x6322B39A };
	unsigned int g_uiSportsCars[29] = { 0xDE3D9D22, 0x206D1B68, 0x7B8AB45F, 0x8911B9F5, 0xA29D6D10, 0x8CB29A14, 0x067BC037, 0x679450AF, 0x3D8FA25C, 0xA8E38B01, 0x16E478C1, 0xC1E908D2, 0xC1AE4D16, 0xD37B7976, 0x1DC0BA53, 0xEDD516C6, 0x2BEC3CBE, 0xE9805550, 0x39DA2754, 0x7836CE2F, 0xBF1691E0, 0xF77ADE32, 0xDA5819A3, 0xB2A716A3, 0xBE0E6126, 0x5E4327C8, 0x2DB8D1AA, 0xAE2BFE94, 0x187D938D };
	unsigned int g_uiSportsClassicCars[20] = { 0x3C4E2113, 0x2EC385FE, 0x2D3BD401, 0x82E499FA, 0x5C23AF9B, 0xE62B361B, 0x3EAB5555, 0x1BB290BC, 0x5B42A5C4, 0x690A4153, 0x86CF7CDD, 0x6D19CCBC, 0x81634188, 0xE2504942, 0x06FF6914, 0xB820ED5E, 0x047A6BC1, 0x404B6381, 0x3822BDFE, 0x14D69010 };
	unsigned int g_uiMuscleCars[12] = { 0x0239E390, 0x94B395C5, 0xCEC6B9B7, 0x04CE68AC, 0xD756460C, 0x831A21D5, 0x9B909C94, 0xF26CEFF9, 0x1F3766E3, 0x59E0FBF3, 0xD83C13CE, 0xDCE1D9F7 };
	unsigned int g_uiSedans[23] = { 0x42F2ED16, 0x506434F6, 0xE18195B2, 0x8B13F083, 0x71CB2FFB, 0x8F0E3594, 0xB52B5113, 0x8E9254FB, 0x34DD8AA1, 0x69F06B57, 0xA7EDE74D, 0xB3206692, 0xD7278283, 0x8FC3AADC, 0xB5FCF74E, 0xBB6B404F, 0xFF22D208, 0x2560B2FC, 0xC3DDFDCE, 0x8FB66F9B, 0x66B4FC45, 0x94204D89, 0x9441D8D5 };
	unsigned int g_uiCoupes[10] = { 0xFFB15B5E, 0x13B57D8A, 0xFAAD85EE, 0xE8A8BDA8, 0xBD1B39C3, 0xB8E2AE18, 0x50732C82, 0x3412AE2D, 0xDCBCBE48, 0xDAC67112 };
	unsigned int g_uiCompacts[8] = { 0xBC993509, 0x64430650, 0xB9CB3B69, 0xA988D3A2, 0xEB70965F, 0x322CF98F, 0x51D83328, 0xE644E480 };
	unsigned int g_uiSUVnTrucks[28] = { 0xCFCA3668, 0x08852855, 0x7F5C91F1, 0x779F23AA, 0xD0EB2BE5, 0x462FE277, 0xE882E5F6, 0xB6410173, 0x4FB1A214, 0x4BA4E8DC, 0xBC32A33B, 0xCFCFEB3B, 0x34B7390F, 0x9D96B45B, 0x9628879C, 0x36848602, 0xD36A4B44, 0x48CECED3, 0x05852838, 0xA3FC0F4D, 0x32B29A4B, 0x1D06D681, 0xDC434E51, 0x2BC345D1, 0x825A9F4C, 0x7B7E56F0, 0x9114EADA, 0x83051506 };
	unsigned int g_uiOffRoads[19] = { 0xCD93A7DB, 0xB9210FD0, 0x9CF21E0F, 0x1FD824AF, 0x432AA566, 0xEB298297, 0x8125BCF9, 0xB44F0582, 0x84F42E51, 0x3AF8C345, 0x698521E3, 0xAA699BB6, 0x6210CBB0, 0x7341576B, 0xB802DD46, 0x8612B64B, 0xFD231729, 0xA7CE1BC5, 0x6882FA73 };
	unsigned int g_uiVans[31] = { 0xFEFD644F, 0x7B8297C5, 0x67B3F020, 0x58B3979C, 0xF8D48E7A, 0xED7EADA4, 0x3FC5D440, 0x4543B74D, 0x961AFEF7, 0xF8DE29A8, 0x38408341, 0xAFBB2CA4, 0xC9E8FF76, 0x98171BD3, 0x353B561D, 0x437CF2A0, 0x11AA0E14, 0x97FA4F36, 0xCFB3870C, 0x2B6DC64A, 0x03E5F6B8, 0x898ECCEA, 0xF21B33BE, 0x07405E08, 0x1A79847A, 0x6FD95F68, 0x744CA80D, 0x29B0DA97, 0xB1D80E06, 0x2B7F9DE3, 0x31ADBBFC };
	unsigned int g_uiEmergencyCars[18] = { 0x432EA949, 0x9DC66994, 0x73920F8E, 0x45D56ADA, 0x79FBB0C5, 0x9F05F101, 0x71FA16EA, 0x8A63C7B9, 0xFDEFAEC3, 0xA46462F7, 0x95F4C618, 0x1B38E955, 0xB822A1AA, 0x9BAA707C, 0x72935408, 0x885F3671, 0x2C33B46E, 0x1BF8D381 };
	unsigned int g_uiServicVehicles[6] = { 0x4C80EB0E, 0x84718D34, 0xD577C962, 0xBE819C63, 0x73B1C3CB, 0xC703DB5F };
	unsigned int g_uiMilitary[7] = { 0x2EA68690, 0xCEEA3F4B, 0x4008EABB, 0x2592B5CF, 0x132D5A1A, 0xD46F4737, 0x74998082 };
	unsigned int g_uiMotorcycles[21] = { 0x00ABB0C0, 0xCADD5D2D, 0xF9300CC5, 0x11F76C14, 0xF683EACA, 0x9C669788, 0x6D6F8F43, 0xAF599F01, 0xCABD11E8, 0xF79A00F7, 0xC9CEAF06, 0x4B6C568A, 0x63ABADE7, 0x2EF89E46, 0xA960B13E, 0x0350D1AB, 0x77934CEE, 0x806B9CC3, 0xDA288376, 0x2C509634, 0x26321E67 };
	unsigned int g_uiBicycles[7] = { 0x4339CD69, 0xE823FB48, 0xF4E1AA15, 0xB67597EC, 0x1ABA13B5, 0x43779C54, 0xCE23D3BF };
	unsigned int g_uiCommercialVehicles[39] = { 0x35ED670B, 0xC1632BEB, 0x85A5B471, 0x809AA4CB, 0x7A61B330, 0x21EEE87D, 0x7DE35E7D, 0x5A82F9AE, 0x6827CF72, 0xF337AB36, 0x32B91AE8, 0x810369E2, 0x7074F39D, 0x58E49664, 0x1A7FCEFA, 0xC3FBA120, 0x1ED0A534, 0x34E6BF6B, 0x7F2153DF, 0x72435A19, 0xB527915C, 0xB12314E0, 0xE5A2D6C6, 0x02E19879, 0xC7824E5E, 0xD138A6BB, 0x1C534995, 0x50B0215A, 0xCD935EF9, 0x9A5B1DCC, 0x9A9FD3DF, 0x6A4BD8F6, 0xCB44B1CA, 0x5D0AAC8F, 0x61D6BA8C, 0x843B73DE, 0x562A97BD, 0x44623884, 0xDFF0594C };
	unsigned int g_uiHelicopters[14] = { 0x31F0B376, 0x2F03547B, 0x2C75F0DD, 0x2C634FBD, 0x742E9AC0, 0x9D0450CA, 0xFCFCB68B, 0x60A7EA10, 0x53174EEF, 0x1517D4D9, 0xEBC24DF2, 0x4019CB4C, 0xA09E15FD, 0xFB133A17 };
	unsigned int g_uiPlanes[19] = { 0x761E2AD3, 0x250B0C5E, 0xB79F589E, 0xB79C1BF5, 0x4FF77E37, 0x09D80F93, 0x9C429B6A, 0x403820E8, 0x97E55D11, 0x39D6779E, 0x81794C70, 0xD9927FE3, 0x15F27762, 0xF7004C86, 0xB39B0AE6, 0x3E48BF23, 0x3F119114, 0x6CBD1D6D, 0x39D6E83F };
	unsigned int g_uiBoats[14] = { 0xC1CE1183, 0x33581161, 0x17DF5EC2, 0xEF2295C9, 0x1149422F, 0xC2974024, 0xDB4388E4, 0xE2E7D4AB, 0x2DFF622F, 0x0DC60D2B, 0x3D961290, 0x107F392C, 0x107F392C/*copy of other diunghy*//*0x1****4EA*/, 0x3FD5AA2F };
	unsigned int g_uiTrailers[27] = { 0xB8081009, 0xA7FF33F5, 0x9E6B14D6, 0xE82AE656, 0x1F3D44B5, 0xC6C3242D, 0x806EFBEE, 0x3D6AAA9B, 0x0AFD22A6, 0x36DCFF98, 0x0E512E79, 0x264D9262, 0x3CC7F596, 0x33C9E158, 0x153E1B0A, 0x174CB172, 0x22EDDC30, 0x7BE032C6, 0x6A59902D, 0x7CAB34D0, 0x782A236D, 0xCBB2BE0E, 0xA1DA3C91, 0x8548036D, 0x2A72BEAB, 0xAF62F6B2, 0x967620BE };
	//3f7a4

	char* super1[11] = { "lgm_default", "lgm_default", "lgm_default", "lgm_default", "lgm_default", "lgm_default", "lgm_default", "lgm_dlc_business2", "lgm_dlc_business", "lgm_dlc_luxe", "lgm_dlc_luxe" };
char* super2[11] = { "adder", "entityxf", "cheetah", "infernus", "vacca", "bullet", "voltic_tless", "zentorno", "turismor", "osiris", "t20" };
char* sport11[29] = { "lgm_default", "lgm_default", "lgm_default", "www_eyefind_info", "www_eyefind_info", "lgm_default", "lgm_default", "lgm_default", "lgm_default", "lgm_default", "lgm_default", "lgm_default", "lgm_default", "sssa_default", "sssa_dlc_business2", "sssa_dlc_hipster", "sssa_dlc_business2", "www_eyefind_info", "www_eyefind_info", "lgm_dlc_lts_creator", "www_eyefind_info", "sssa_dlc_christmas_2", "www_eyefind_info", "sssa_dlc_christmas_2", "lgm_dlc_luxe", "lgm_dlc_business", "sssa_dlc_heist", "sssa_dlc_heist" };
char* sport22[29] = { "elegy2", "khamel", "carboniz", "ad_legendarymotorsport_net", "ad_legendarymotorsport_net", "rapidgt", "coquette", "rapidgt2", "ninef", "ninef2", "surano_convertable", "banshee", "comet2", "schwarze", "fusilade", "buffalo", "penumbra", "ad_legendarymotorsport_net", "ad_legendarymotorsport_net", "furore", "ad_legendarymotorsport_net", "massacro2", "ad_legendarymotorsport_net", "jester2", "windsor", "alpha", "kuruma", "kuruma2" };
char* classic11[20] = { "lgm_dlc_pilot", "lgm_dlc_luxe", "lgm_default", "lgm_default", "lgm_default", "lgm_default", "lgm_default", "www_eyefind_info", "www_eyefind_info", "www_eyefind_info", "www_eyefind_info", "www_eyefind_info", "www_eyefind_info", "lgm_dlc_luxe", "lgm_dlc_valentines", "sssa_dlc_heist", "sssa_dlc_hipster", "sssa_dlc_hipster", "lgm_dlc_heist", "lgm_dlc_luxe" };
char* classic22[20] = { "coquette2", "coquette3", "ztype", "stingerg", "stinger", "monroe", "jb700", "ad_legendarymotorsport_net", "ad_legendarymotorsport_net", "ad_legendarymotorsport_net", "ad_legendarymotorsport_net", "ad_legendarymotorsport_net", "ad_legendarymotorsport_net", "virgo", "roosevelt", "blade", "glendale", "pigalle", "casco", "chino" };
char* muscle11[12] = { "lgm_default", "sssa_default", "sssa_default", "sssa_dlc_mp_to_sp", "www_eyefind_info", "www_eyefind_info", "www_eyefind_info", "www_eyefind_info", "www_eyefind_info", "sssa_dlc_hipster", "www_eyefind_info", "sssa_dlc_christmas_2" };
char* muscle22[12] = { "hotknife", "gauntlet", "vigero", "dominator2", "ad_legendarymotorsport_net", "ad_legendarymotorsport_net", "ad_legendarymotorsport_net", "ad_legendarymotorsport_net", "ad_legendarymotorsport_net", "picador", "ad_legendarymotorsport_net", "rloader2" };
char* suv11[23] = { "www_eyefind_info", "sssa_default", "sssa_dlc_heist", "sssa_default", "sssa_default", "sssa_dlc_heist", "sssa_dlc_heist", "www_eyefind_info", "sssa_dlc_business", "sssa_dlc_business", "sssa_dlc_business", "sssa_dlc_business", "www_eyefind_info", "www_eyefind_info", "www_eyefind_info", "sssa_dlc_hipster", "sssa_dlc_hipster", "www_eyefind_info", "sssa_dlc_hipster", "sssa_dlc_business", "sssa_dlc_business", "sssa_dlc_business", "www_eyefind_info" };
char* suv22[23] = { "ad_legendarymotorsport_net", "oracle", "oracle1", "stretch", "fugitive", "surge", "schafter2", "ad_legendarymotorsport_net", "intruder", "washingt", "stanier", "ingot", "ad_legendarymotorsport_net", "ad_legendarymotorsport_net", "ad_legendarymotorsport_net", "primo", "regina", "ad_legendarymotorsport_net", "tailgater", "premier", "stratum", "asea", "ad_legendarymotorsport_net" };
char* terrain11[19] = { "candc_default", "sssa_default", "sssa_default", "www_eyefind_info", "sssa_default", "sssa_default", "sssa_default", "sssa_dlc_hipster", "candc_default", "sssa_default", "www_eyefind_info", "sssa_default", "sssa_dlc_business", "www_eyefind_info", "sssa_dlc_hipster", "sssa_dlc_hipster", "sssa_dlc_hipster", "lgm_dlc_luxe", "sssa_dlc_heist" };
char* terrain22[19] = { "monster", "sandkin2", "dune", "ad_legendarymotorsport_net", "bfinject", "bifta", "blazer", "blazer3", "mesa", "sandking", "ad_legendarymotorsport_net", "bodhi2", "rancherx", "ad_legendarymotorsport_net", "rebel2", "rebel2", "blazer3", "brawler", "enduro" };
char* urgence11[18] = { "www_suemurry_com", "www_suemurry_com", "www_suemurry_com", "www_suemurry_com", "www_suemurry_com", "www_suemurry_com", "www_suemurry_com", "www_suemurry_com", "www_suemurry_com", "www_suemurry_com", "www_suemurry_com", "www_suemurry_com", "www_suemurry_com", "www_suemurry_com", "www_suemurry_com", "candc_default", "www_suemurry_com", "www_suemurry_com" };
char* urgence22[18] = { "suemurry_background_left", "suemurry_background_left", "suemurry_background_left", "suemurry_background_left", "suemurry_background_left", "suemurry_background_left", "suemurry_background_left", "suemurry_background_left", "suemurry_background_left", "suemurry_background_left", "suemurry_background_left", "suemurry_background_left", "suemurry_background_left", "suemurry_background_left", "suemurry_background_left", "pbus", "suemurry_background_left", "suemurry_background_left" };
char* service11[6] = { "candc_default", "www_suemurry_com", "candc_default", "candc_default", "candc_default", "www_suemurry_com" };
char* service22[6] = { "airbus", "suemurry_background_left", "bus", "rentbus", "rentbus", "suemurry_background_left" };
char* militaire11[9] = { "candc_default", "candc_default", "www_suemurry_com", "www_suemurry_com", "candc_default", "www_suemurry_com", "www_suemurry_com", "candc_default", "candc_default" };
char* militaire22[9] = { "rhino", "barracks", "suemurry_background_left", "suemurry_background_left", "crusader", "suemurry_background_left", "suemurry_background_left", "insurgent", "technical" };
char* moto11[21] = { "lgm_default", "sssa_default", "sssa_default", "sssa_default", "sssa_dlc_heist", "sssa_default", "lgm_dlc_business2", "lgm_dlc_luxe", "sssa_default", "sssa_default", "sssa_default", "sssa_dlc_lts_creator", "sssa_default", "sssa_default", "sssa_default", "www_eyefind_info", "www_eyefind_info", "www_eyefind_info", "sssa_dlc_heist", "lgm_dlc_heist" };
char* moto22[21] = { "carbon", "bati2", "bati", "hexer", "innovation", "double", "thrust", "vindicator", "ruffian", "vader", "pcj", "hakuchou", "akuma", "sanchez2", "sanchez", "ad_southernsanandreassuperautos_com", "ad_southernsanandreassuperautos_com", "ad_southernsanandreassuperautos_com", "nemesis", "lectro" };
char* velo11[7] = { "www_eyefind_info", "pandm_default", "pandm_default", "www_eyefind_info", "pandm_default", "pandm_default", "www_eyefind_info" };
char* velo22[7] = { "ad_pandmcycles_com", "tribike", "scorcher", "ad_pandmcycles_com", "cruiser", "bmx", "ad_pandmcycles_com" };
char* helico11[12] = { "elt_default", "candc_default", "candc_default", "elt_default", "www_eyefind_info", "candc_default", "www_eyefind_info" };
char* helico22[8] = { "annihl", "buzzard", "buzzard", "frogger", "ad_elitastravel_com", "cargobob", "ad_elitastravel_com", "ad_elitastravel_com" };
char* avion11[19] = { "elt_default", "elt_default", "elt_dlc_luxe", "elt_default", "elt_dlc_business", "elt_dlc_pilot", "elt_default", "elt_default", "elt_default", "elt_default", "www_eyefind_info", "elt_default", "www_eyefind_info", "www_eyefind_info", "www_eyefind_info", "www_eyefind_info", "www_eyefind_info", "www_eyefind_info", "candc_default" };
char* avion22[19] = { "titan", "luxor", "luxor2", "shamal", "vestra", "miljet", "velum", "velum2", "mammatus", "duster", "ad_elitastravel_com", "cuban800", "ad_elitastravel_com", "ad_elitastravel_com", "ad_elitastravel_com", "ad_elitastravel_com", "ad_elitastravel_com", "ad_elitastravel_com", "hydra" };
char* bateau11[13] = { "dock_default", "dock_default", "dock_default", "dock_default", "dock_default", "dock_default", "www_eyefind_info", "www_eyefind_info", "www_eyefind_info", "dock_default", "www_eyefind_info", "www_eyefind_info", "dock_default" };
char* bateau22[13] = { "marquis", "jetmax", "squalo", "suntrap", "tropic", "seashark", "ad_docktease_com", "ad_docktease_com", "ad_docktease_com", "speeder", "ad_docktease_com", "ad_docktease_com", "toro" };


	bool l3pressed = false;
	bool wheelieEnabled = false;
	/*void APPLY_FORCE(int Entity, Vector3 Force, Vector3 Position, int type = 1) {
		//float Forc[] = {Force.x,Force.y,Force.z};
		//float Positio[] = {Position.x,Position.y,Position.z};
		ENTITY::APPLY_FORCE_TO_ENTITY(Entity, type, Force.x,Force.y,Force.z, Position.x,Position.y,Position.z, 0, 1, 1, 1, 0, 1);
	}
	void forceEntity(int entity, float x, float y, float z, float rotx, float roty, float rotz, int type = 1) {
		Vector3 force = {x,y,z};
		Vector3 rot = {rotz,roty,rotz};
		APPLY_FORCE(entity,force,rot,type);
	}*/
	void liftcar() {
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(),false)) {
			int veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			forceEntity(veh,0,0,0.2f,0,3,0);
		}
	}
	bool hydroulicsEnabled = false;
	float hydroulicsNumX = 0;
	float hydroulicsNumY = 0;
	float hydroulicsNumXChange = 0.5;
	float hydroulicsNumYChange = -0.5;
	float side = 0;
	int hydroulicsPower = 10;
	float hydroulicsLowness = 0.25f;
	bool hydroulicsConstant = false;
	void hydroulicsChange(float i, float change) {
		i+=change;
		if (i > 3) change = -0.5;
		if (i < -3) change = 0.5;
	}

	int curHydroulicsMode = 0;
#ifdef hydraulics
	void hydroulicsToggleSide() {
		curHydroulicsMode++;
		/*if (curHydroulicsMode == 0) {
			print("Front");
		}*/
		if (curHydroulicsMode == 1) {
			print("Back");
		}
		if (curHydroulicsMode == 2) {
			print("Bounce");
		}
		if (curHydroulicsMode > 2) {
			curHydroulicsMode = 0;
			print("front");
		}
	}
	bool hru = true;
	bool hrd = true;
	bool hrl = true;
	bool hrr = true;
	void hydroulicsLoop(int currentmenu) {
		//if (currentmenu==Hydroulics_Options ||  currentmenu == Closed)
			if (hydroulicsEnabled == true) {
				if (pressedButtons::l1pressed) {
					CONTROLS::DISABLE_CONTROL_ACTION(0, Dpad_Up);
					CONTROLS::DISABLE_CONTROL_ACTION(0, Dpad_Down);
					CONTROLS::DISABLE_CONTROL_ACTION(0, Dpad_Left);
					CONTROLS::DISABLE_CONTROL_ACTION(0, Dpad_Right);
					CONTROLS::DISABLE_CONTROL_ACTION(0, Button_L1);
					CONTROLS::SET_INPUT_EXCLUSIVE(2, Dpad_Up);
					CONTROLS::SET_INPUT_EXCLUSIVE(2, Dpad_Down);
					CONTROLS::SET_INPUT_EXCLUSIVE(2, Dpad_Left);
					CONTROLS::SET_INPUT_EXCLUSIVE(2, Dpad_Right);
					CONTROLS::SET_INPUT_EXCLUSIVE(2, Button_L1);
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(),false)) {
					int veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
					/*if (VehicleMods::l3pressed || VehicleMods::hydroulicsConstant) {
						if (curHydroulicsMode == 0) {//front
							if (side == 1) {//front
								forceEntity(veh,0,0,0.075f*hydroulicsPower,0,3,0);
							}
							if (side == 2.25f) {//middle
								forceEntity(veh,0,0,0.075f*hydroulicsPower,0,-1,0);
							}
						}
						else if (curHydroulicsMode == 1) {//back
							if (side == 1) {//middle
								forceEntity(veh,0,0,0.075f*hydroulicsPower,0,-3,0);
							}
							if (side == 2.25) {//front
								forceEntity(veh,0,0,0.075f*hydroulicsPower,0,1,0);
							}
						}
						else if (curHydroulicsMode == 2) {//center
							if (side == 1) {
								forceEntity(veh,0,0,0.1f*hydroulicsPower+GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(0,0.2f),0,-3,0);
								forceEntity(veh,0,0,0.1f*hydroulicsPower+GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(0,0.2f),0,3,0);
							}
						}
						side+=0.25f;
						if (side > 3 && VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(veh)) {
							side = 0;
						}*/
						bool isonwheels = VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(veh);
						int m = hydroulicsPower;//regular is 1
						if (pressedButtons::dpaduppressed /*&& (isonwheels || hru == true)*/) {//front
							forceEntity(veh,0,0,0.09*m,0,3,0);
							hru = false;
						}
						if (pressedButtons::dpaddownpressed /*&& (isonwheels || hrd == true)*/) {//back
							forceEntity(veh,0,0,0.09*m,0,-3,0);
							hrd = false;
						}
						if (pressedButtons::dpadleftpressed /*&& (isonwheels || hrl == true)*/) {//left
							forceEntity(veh,0.06f*m,0,0,0,0,3);
							hrl = false;
						}
						if (pressedButtons::dpadrightpressed/* && (isonwheels || hrr == true)*/) {//right
							forceEntity(veh,0.06f*m,0,0,0,0,-3);
							hrr = false;
						}
						/*if (side == 4) {//jump
							forceEntity(veh,0,0,1*m,0,0,0);
						}*/
					//} else {
						//side = 0;
						if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(veh) == true) {
							//forceEntity(veh,0,0,hydroulicsLowness*-1,0,0,0);
							hru = true;
							hrd = true;
							hrl = true;
							hrr = true;
						}
					//}
				}
				}
			//}
	}
	}

#endif

	bool squareDriftModBool = false;
	void squareDriftModLoop() {
		if (squareDriftModBool) {
			if (pressedButtons::squarepressed) {
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(),false)) {
					int veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
					VEHICLE::SET_VEHICLE_REDUCE_GRIP(veh,true);//https://i.imgur.com/Ae1v9jf.png
				}
			} else {
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(),false)) {
					int veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
					VEHICLE::SET_VEHICLE_REDUCE_GRIP(veh,false);//https://i.imgur.com/Ae1v9jf.png
				}
			}
		}
	}


	void killPlayerInVehicle(int player) {
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(player),false)) {
			VEHICLE::SET_VEHICLE_OUT_OF_CONTROL(getPlayerVehicle(player),true,true);
		}
	}

	bool nfs = false;
	int nfsmode = 0;
	bool stickToGround = false;
	float nfsSpeed = 1;
	void needForSpeed() {
		if (stickToGround) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(),false)) {
				int vehicle = getMyVehicle();
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(vehicle);
			}
		}
		if (nfs) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(),false)) {
				int vehicle = getMyVehicle();
				CONTROLS::DISABLE_CONTROL_ACTION(0, Button_L1);
				CONTROLS::SET_INPUT_EXCLUSIVE(2, Button_L1);
				if (nfsmode == 1 || VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(vehicle)) {
					//bool moving = false;
					if (pressedButtons::r2pressed) {
						//VEHICLE::_0x642DA5AA(vehicle,10);
						VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle,ENTITY::GET_ENTITY_SPEED(vehicle)+nfsSpeed);
						//moving = true;
					}
					if (pressedButtons::l2pressed) {
						//VEHICLE::_0x642DA5AA(vehicle,10);
						VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle,-1*(ENTITY::GET_ENTITY_SPEED(vehicle)+nfsSpeed));
						//moving = true;
					}
					if (pressedButtons::l2jpressed || (pressedButtons::l2pressed&&pressedButtons::r2pressed))
						VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle,0);
					//use 3 for force type
					if (pressedButtons::r1pressed/* && moving*/) {
						Vector3 rotation = ENTITY::GET_ENTITY_ROTATION(vehicle,2);
						ENTITY::SET_ENTITY_ROTATION(vehicle,rotation.x,rotation.y,rotation.z-2,2,1);
						//ENTITY::APPLY_FORCE_TO_ENTITY(vehicle,0,/*-825735706*/0,/*9.8742232646474E-30*/0,-1,0,0,0,0,1,1,1,1,0);
						//forceEntity(vehicle,1,0,0,0,0,0,3);
					}
					if (pressedButtons::l1pressed/* && moving*/) {
						Vector3 rotation = ENTITY::GET_ENTITY_ROTATION(vehicle,2);
						ENTITY::SET_ENTITY_ROTATION(vehicle,rotation.x,rotation.y,rotation.z+2,2,1);
						//ENTITY::APPLY_FORCE_TO_ENTITY(vehicle,0,/*-825735706*/0,/*9.8742232646474E-30*/0,+1,0,0,0,0,1,1,1,1,0);
						//forceEntity(vehicle,-1,0,0,0,0,0,3);
					}
					//if (nfsmode == 0 && moving) {
						//VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(vehicle);
					//}
				}
			}
		}
	}

	int playercarbool = false;
	int playercarplayer = 0;
	int playercartype = 0;
	void playerCarRunLoop() {
		if (playercarbool == true) {
			int car = getPlayerVehicle(playercarplayer);
			netreq::reqent(car);
			if (netreq::hasent(car)) {
				TrafficMods::runMod(playercartype,car);
				playercarbool = false;
			}
		}
	}
	void modPlayerCar(int player, int type) {
		playercarplayer = player;
		playercartype = type;
		playercarbool = true;
	}

	bool carmageddonBool = false;
	void carmageddon() {
		char patchOn[] = {0x50, 0x00, 0x00, 0x00};
		char patchOff[] = {0x3F, 0x00, 0x00, 0x00};
		carmageddonBool = !carmageddonBool;
		if (carmageddonBool)
			write_process((char*)0x1A8C190,patchOn,4);//might be wrong idk
		else
			write_process((char*)0x1A8C190,patchOff,4);
	}
	bool paradiseColorChanger = false;
	void paradiseColorChangerLoop() {
		if (paradiseColorChanger)
			VehicleMods::setColorRGBCar(colors::r,colors::g,colors::b);
	}
	bool matrixPlateBool = false;
	char matrixPlateText[10];
	void matrixPlate(bool doit = true) {
		if (doit) {
			int car = getPlayerVehicle(PLAYER::PLAYER_ID());
			for (int i = 0; i < 10; i++)
				matrixPlateText[i] = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(48,90);
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(car, matrixPlateText);
		}
	}
}
#pragma endregion
#pragma region first Person
int extracurrentoption = 0;

namespace firstPerson {
	opd_s SET_CAM_ROT_t = {0x3A39D8,TOC};
	void(*SET_CAM_ROT)(uint cam, float *, int p4) = (void(*)(uint,float *,int))&SET_CAM_ROT_t;
	opd_s SET_CAM_NEAR_CLIP_t = {0x3A3D0C,TOC};
	void(*SET_CAM_NEAR_CLIP)(int camera,float offset) = (void(*)(int,float))&SET_CAM_NEAR_CLIP_t;
	bool firstperson = false;//call to enable fp
	bool firstperson1 = false;//call to remove fp
	bool enabled = false;
	//bool firstperson2 = true;
	uint cam;
	void loop() {
		if(firstperson == true) {
			cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA",1);
			Vector3 coords = {0.0,0.15,0.07};//0.02
			CAM::ATTACH_CAM_TO_PED_BONE(cam,PLAYER::PLAYER_PED_ID(),31086,coords.x,coords.y,coords.z,1);
			SET_CAM_NEAR_CLIP(cam,0.225f);
			//CAM::SET_CAM_INHERIT_ROLL_VEHICLE(cam,true);
			CAM::SET_CAM_ACTIVE(cam,1);
			CAM::RENDER_SCRIPT_CAMS(1,0,3000,1,0);
			firstperson = false;
		}
		Vector3 v = CAM::GET_GAMEPLAY_CAM_ROT(2);
		float v1[] = {v.x,v.y,v.z};
		SET_CAM_ROT(cam,v1,2);
		if (firstperson1 == true) {
			if (CAM::DOES_CAM_EXIST(cam)) {
				CAM::SET_CAM_ACTIVE(cam,0);
				CAM::RENDER_SCRIPT_CAMS(0,0,3000,1,0);
				CAM::DESTROY_CAM(cam,0);
			}
			firstperson1 = false;
		}
	}

	bool toggle() {
		enabled = !enabled;
		if (enabled == true) {
			firstperson = true;
		} else {
			firstperson1 = true;
		}
	}

	void rendercrosshair() {
		if (enabled == true) {
			drawing::DrawSprite("visualflow","crosshair",0.5f,0.5f,0.01f,0.01f,0,255,255,255,255);
		}
	}
}
#pragma endregion
#pragma region camera shit
namespace camShit {
	opd_s SET_CAM_ROT_t = {0x3A39D8,TOC};
	void(*SET_CAM_ROT)(uint cam, float *, int p4) = (void(*)(uint,float *,int))&SET_CAM_ROT_t;
	opd_s SET_CAM_NEAR_CLIP_t = {0x3A3D0C,TOC};
	void(*SET_CAM_NEAR_CLIP)(int camera,float offset) = (void(*)(int,float))&SET_CAM_NEAR_CLIP_t;
	uint cam;
	Vector3 location = {0,0,0};
	int entity = 0;
	bool doCamRot = true;
	void loop() {
		if (CAM::DOES_CAM_EXIST(cam)) {
			//if (ENTITY::DOES_ENTITY_EXIST(entity)) {
				//Vector3 v = ENTITY::GET_ENTITY_FORWARD_VECTOR(entity);
				//float v1[] = {v.x,v.y,v.z};
				//SET_CAM_ROT(cam,v1,2);
			//} else {
				Vector3 v = CAM::GET_GAMEPLAY_CAM_ROT(2);
				float v1[] = {v.x,v.y,v.z};
				if (doCamRot)
					SET_CAM_ROT(cam,v1,2);
			//}
		}
	}

	void attachToLocation(float x, float y, float z, bool setFocusOnEntity = true) {
		if (setFocusOnEntity) {
			STREAMING::CLEAR_FOCUS();
			STREAMING::_0x14680A60(x,y,z,0,0,0);
		}
		entity = 0;
		if (!CAM::DOES_CAM_EXIST(cam))
			cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA",1);
		//Vector3 coords = {0.0,0.15,0.07};
		//CAM::ATTACH_CAM_TO_PED_BONE(cam,PLAYER::PLAYER_PED_ID(),31086,x,y,z,1);
		CAM::SET_CAM_COORD(cam,x,y,z);
		//SET_CAM_NEAR_CLIP(cam,0.225f);
		CAM::SET_CAM_ACTIVE(cam,1);
		CAM::RENDER_SCRIPT_CAMS(1,0,3000,1,0);
		Vector3 v = CAM::GET_GAMEPLAY_CAM_ROT(2);
		float v1[] = {v.x,v.y,v.z};
		SET_CAM_ROT(cam,v1,2);
	}

	void attachToEntityHead(int ent, float offsetz = 0, bool setFocusOnEntity = true, bool justEntityAttach = false, bool doCamRot_ = true) {
		doCamRot = doCamRot_;
		if (setFocusOnEntity) {
			STREAMING::CLEAR_FOCUS();
			STREAMING::SET_FOCUS_ENTITY(ent);
		}
		entity = ent;
		if (!CAM::DOES_CAM_EXIST(cam))
			cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA",1);
		Vector3 coords = {0.0,0.15,0.07+offsetz};
		if (justEntityAttach == false)
			CAM::ATTACH_CAM_TO_PED_BONE(cam,ent,31086,coords.x,coords.y,coords.z,1);
		else
			CAM::ATTACH_CAM_TO_ENTITY(cam,ent,0,0,0,true);
		//CAM::SET_CAM_COORD(cam,x,y,z);
		SET_CAM_NEAR_CLIP(cam,0.225f);
		CAM::SET_CAM_ACTIVE(cam,1);
		CAM::RENDER_SCRIPT_CAMS(1,0,3000,1,0);
		Vector3 v = CAM::GET_GAMEPLAY_CAM_ROT(2);
		float v1[] = {v.x,v.y,v.z};
		SET_CAM_ROT(cam,v1,2);
	}

	

	void resetCam(bool clearFocus = true) {
		doCamRot = true;
		if (CAM::DOES_CAM_EXIST(cam)) {
			if (clearFocus)
				STREAMING::CLEAR_FOCUS();
			CAM::SET_CAM_ACTIVE(cam,0);
			CAM::RENDER_SCRIPT_CAMS(0,0,3000,1,0);
			CAM::DESTROY_CAM(cam,0);
			cam = 0;
		}
	}
	bool enabled() {
		
		return CAM::DOES_CAM_EXIST(cam);
	}

#include <math.h>	
#ifdef calc_aimbot
	namespace aimbot {
		
		




struct vec3
{
	float x;
	float y;
	float z;
};
float angleseeeee[3];
vec3 vectoangles(vec3 Angles)
{
	/*float forward;
	float yaw, pitch;
	//float PI = 3.1415926535897931;
	if (Angles.x == 0 && Angles.y == 0)
	{
		yaw = 0;
		if (Angles.z > 0) pitch = 90.00;
		else pitch = 270.00;
	}
	else
	{
		if (Angles.x != -1) yaw = (float)(atan2((double)Angles.y, (double)Angles.x) * 180.00 / PI);
		else if (Angles.y > 0) yaw = 90.00;
		else yaw = 270;
		if (yaw < 0) yaw += 360.00;

		forward = (float)sqrt((double)(Angles.x * Angles.x + Angles.y * Angles.y));
		pitch = (float)(atan2((double)Angles.z, (double)forward) * 180.00 / PI);
		if (pitch < 0) pitch += 360.00;
	}
	angleseeeee[0] = -pitch;
	angleseeeee[1] = yaw;
	angleseeeee[2] = 0;

	vec3 Angless = { angleseeeee[0], angleseeeee[1], angleseeeee[2] };
	return Angless;*/
	
}

float dx, dy, dz;
float GetDistance(Vector3 c1, Vector3 c2)
{
	float dx = c2.x - c1.x;
	float dy = c2.y - c1.y;
	float dz = c2.z - c1.z;

	return sqrt((float)((dx * dx) + (dy * dy) + (dz * dz)));
}


	bool enabled = false;
	int aimbotClient = 0;
	int getNearestPed() {
		int peds[50];
		int sizeOfArr = getPedsNearPed(PLAYER::PLAYER_PED_ID(),peds,50);
		Vector3 myLoc = PlayerMods::getPlayerLocation(PLAYER::PLAYER_ID());
		int client = -1;
		float maxDist = (float)9999999999;
		for (int i = 0; i < sizeOfArr; i++) {
			float dist = GetDistance(myLoc,ENTITY::GET_ENTITY_COORDS(peds[i],1));
			if (dist < maxDist) {
				client = peds[i];
				maxDist = dist;
			}
		}
		return client;
		/*int client = -1;
		int myId = PLAYER::PLAYER_ID();
		float distance = (float)9999999999;


		const int numElements = 10;
		const int arrSize = numElements * 2 + 2;
		int nearbyPed[arrSize];
		 
        nearbyPed[0] = numElements;
        int count = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), nearbyPed, -1);
		printf("Created Ped Array\n");
        if (nearbyPed != NULL)
        {
			printf("Not Null\n");
            for (int i = 0; i < count-1; i++)
            {
				printf("Count %i\n",i);
                int offsettedID = i * 2 + 2;
				printf("OffID %i\n",offsettedID);
				printf("PedID %i\n",nearbyPed[offsettedID]);
                if (nearbyPed[offsettedID] > 0)
                {
					printf("Ped > 0\n");
					if (ENTITY::DOES_ENTITY_EXIST(nearbyPed[offsettedID])) {
						int pedID = nearbyPed[offsettedID];
						printf("Valid ped\n");
						if (pedID != PLAYER::PLAYER_PED_ID()) {
						float dist = GetDistance(PlayerMods::getPlayerLocation(myId),ENTITY::GET_ENTITY_COORDS(pedID,1));
						printf("got distance\n");
							if (dist < distance) {
								distance = dist;
								client = pedID;
							}
						}
					}
                } else {
					//break if ped is null
					printf("Null ped!\n");
					break;
				}
            }
        }
		//printf("PedID: %i\n",(int)client);
		printf("Returning\n");
		return client;*/
	}
	bool needVisibility = false;
	bool pedmode = false;
	bool aimOnly = true;
	int getNearestPlayer() {
		int nearest = -1;
		float distance = (float)9999999;
		int myId = PLAYER::PLAYER_ID();
		for (int i = 0; i < 18; i++) {
			if (i != myId) {
				if (!ENTITY::IS_ENTITY_DEAD(PLAYER::GET_PLAYER_PED(i))) {
					if (needVisibility) {
						if (PlayerMods::isPlayerVisible(i)) {
							float dist = GetDistance(PlayerMods::getPlayerLocation(myId),PlayerMods::getPlayerLocation(i));
							if (dist < distance) {
								distance = dist;
								nearest = i;
							}
						}
					} else {
						float dist = GetDistance(PlayerMods::getPlayerLocation(myId),PlayerMods::getPlayerLocation(i));
						if (dist < distance) {
							distance = dist;
							nearest = i;
						}
					}
				}
			}
		}
		return nearest;
	}
	int aimbotMode = 0;
	void loop() {
		if (CAM::DOES_CAM_EXIST(cam))
			CAM::STOP_CAM_POINTING(cam);
		if (CAM::DOES_CAM_EXIST(firstPerson::cam))
			CAM::STOP_CAM_POINTING(firstPerson::cam);
		if (enabled) {
			if (pedmode)
				aimbotClient = getNearestPed();
			else
				aimbotClient = getNearestPlayer();
			bool doeeit = true;
			if (aimOnly)
				doeeit = PLAYER::IS_PLAYER_FREE_AIMING(PLAYER::PLAYER_ID());
			if (aimbotClient != -1 && doeeit) {
					Vector3 Aim;
					if (pedmode) {
						int bone = PED::GET_PED_BONE_INDEX(aimbotClient, 0x796E);//head
						Aim = PED::GET_PED_BONE_COORDS(aimbotClient, bone,0,0,0);
						//Aim = ENTITY::GET_ENTITY_COORDS(aimbotClient,true);
					}
					else {
						int bone = PED::GET_PED_BONE_INDEX(PLAYER::GET_PLAYER_PED(aimbotClient), 0x796E);//head
						Aim = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED(aimbotClient), bone,0,0,0);
						//Aim = PlayerMods::getPlayerLocation(aimbotClient);
					}
					int bone = PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), 0x796E);//head
					Vector3 me = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), bone,0,0,0);
					/*if (CAM::DOES_CAM_EXIST(firstPerson::cam))
						me = CAM::GET_CAM_COORD(firstPerson::cam);//PlayerMods::getPlayerLocation(PLAYER::PLAYER_ID());
					else
						me = PlayerMods::getPlayerLocation(PLAYER::PLAYER_ID());*/
					vec3 coords = {Aim.x - me.x,Aim.y - me.y,Aim.z - me.z};
					float dist = GetDistance(Aim,me);
					//float x = *(float*)read_process(ClActive() + BaseAngle,4);
					//float y = *(float*)read_process(ClActive() + BaseAngle + 0x4,4);
					//float z = *(float*)read_process(ClActive() + BaseAngle + 0x8,4);
					//vec3 base = {x,y,z};
					//vec3 cangle = vectoangles(angles);
					Vector3 cangle = {0,0,0};
					//float x = GAMEPLAY::ATAN(coords.x/coords.y);//this is 100% the x rotation no matter what the view angle is. this does not
					float x = GAMEPLAY::ACOS(coords.x/(dist!=0?dist:0.000001f));//probably the right one
					float z = GAMEPLAY::ASIN(coords.z/dist);//this is 100% the y rotation no matter what the view angle is. this works.
					Vector3 v = CAM::GET_GAMEPLAY_CAM_ROT(2);
					/*cangle.x = z;
					cangle.y = z;
					cangle.z = z;
					if (aimbotMode > 2) {
						cangle.x = x;
						cangle.y = x;
						cangle.z = x;
					}
					switch(aimbotMode) {
						case 0: cangle.x = x;break;
						case 1: cangle.y = x;break;
						case 2: cangle.z = x;break;
						case 3: cangle.x = z;break;
						case 4: cangle.y = z;break;
						case 5: cangle.z = z;break;
					}*/
					x = math::constrainAngle(x-90);
					cangle.x = z;//working! this works 100% for sure y axis         
					cangle.y = 0;//cangle.y is your turning rotation. turns your screen sideways
					cangle.z = x;//working! cangle.z is x direction
					/*switch(aimbotMode) {
						case 0: break;
						case 1: cangle.z = x-180;break;//increments are clockwise rather than counter clockwise
						case 2: cangle.z = x-270;break;
						case 3: cangle.z = x-180;cangle.x = 0;cangle.y = z;break;
						case 4: cangle.z = x-270;cangle.x = 0;cangle.y = z;break;
						case 5: cangle.x = 0;cangle.y = z;break;
					}*/
					//printf("Set angles %i %i %i\n",(int)cangle.x,(int)cangle.y,(int)cangle.z);
					//vec3 fin = {cangle.x - base.x,cangle.y - base.y,0};
					//float v1[] =  {cangle.x - v.x,cangle.y - v.y,cangle.z - v.z};
					float v1[] =  {cangle.x,cangle.y,cangle.z};
					SET_CAM_ROT(CAM::GET_RENDERING_CAM(),v1,2);
					if (CAM::DOES_CAM_EXIST(cam)) {
						//SET_CAM_ROT(cam,v1,2);
						CAM::POINT_CAM_AT_COORD(cam, Aim.x, Aim.y, Aim.z);
					}
					if (CAM::DOES_CAM_EXIST(firstPerson::cam)) {
						//SET_CAM_ROT(firstPerson::cam,v1,2);
						CAM::POINT_CAM_AT_COORD(firstPerson::cam, Aim.x, Aim.y, Aim.z);
					}
					//*(float*)(ClActive() + Angleoffset) = fin.x;
					//*(float*)(ClActive() + Angleoffset + 0x4) = fin.y;
					//*(float*)(ClActive() + Angleoffset + 0x8) = fin.z;
			}
		}
	}

	}
#endif
}

#pragma endregion
#pragma region forge
struct Plane3D {
float roll;//yrot axis turn like if a plane does a corkscrew or a barrel rolling
float pitch;//xrot axis turn like how a plane turns if you go up or down
float yaw;//zrot axis turn like how the earth spins
Vector3 *origin;//center of the plane
#ifdef fancyPlacementForge
void translate(float x, float y, float z) {
//moves the origin in that direction based on the roll pitch and yaw
	//yaw messes up move in y axis
	//roll messes up move in x axis 
	//pitch messes up move in z axis (fixed)
if (x != 0) {
 Vector3 t = translateX(x);
 origin->x+=t.x;
 origin->y+=t.y;
 origin->z+=t.z;
}
if (y != 0) {
 Vector3 t = translateY(y);
 origin->x+=t.x;
 origin->y+=t.y;
 origin->z+=t.z;
}
if (z != 0) {
 Vector3 t = translateZ(z);
 origin->x+=t.x;
 origin->y+=t.y;
 origin->z+=t.z;
}
//end of translate function
}
Vector3 translateX(float r) {
float z = r*math::Sin(-roll);
float x2 = r*math::Cos(roll);
float x = x2*math::Cos(yaw);
float y = x2*math::Sin(yaw);
Vector3 ret = {x,y,z};
return ret;
}
Vector3 translateY(float r) {
float z = r*math::Sin(pitch);
float y2 = r*math::Cos(pitch);
float y = y2*math::Cos(yaw);
float x = y2*math::Sin(-yaw);
Vector3 ret = {x,y,z};
return ret;
}
Vector3 translateZ(float r) {
/*float x = r*math::Sin(roll);
float y = r*math::Sin(pitch);
float r2 = x*x+y*y;
float z = math::root(r*r-r2,2);*/
float x = r*math::Sin(roll);
float z2 = r*math::Cos(roll);
float z = z2*math::Cos(pitch);
float y = z2*math::Sin(-pitch);
Vector3 ret = {x,y,z};
return ret;
}
void rotateAroundOrigin(Vector3 rotatethis, Vector3 *save) {
	float r = math::length(*origin,rotatethis);
	float rotx = pitch;
	float roty = roll;
	float rotz = yaw;
	float y2 = r*math::Cos(rotx);
	float z2 = r*math::Sin(rotx);
	float y = y2*math::Cos(rotz);
	float x1 = y2*math::Sin(rotz);
	float z = z2*math::Sin(roty);
	float x2 = z2*math::Cos(roty);
	float x = math::dist(x1,x2,0)*(abs(x1)/x1);
	char buf[200];
	//snprintf$(buf,sizeof(buf),"rao:\norig - x: %f, y: %f, z: %f\nnew - x: %f, y: %f, z: %f\n\n",rotatethis.x,rotatethis.y,rotatethis.z,x,y,z);
	//printf(buf);
	save->x = x+origin->x;
	save->y = y+origin->y;
	save->z = z+origin->z;
}
#endif
};
#ifdef fancyPlacementForge
namespace rotationMath {
Vector3 getDif(Vector3 pos1, Vector3 pos2) {
Vector3 dif = {pos2.x-pos1.x,pos2.y-pos1.y,pos2.z-pos1.z};
return dif;
}
Rot3 getRot(Vector3 dif) {
//Vec3 dif = {pos2.x-pos1.x,pos2.y-pos1.y,pos2.z-pos1.z};
Rot3 rot;
rot.roll = math::atan2(dif.z,dif.x);
rot.pitch = math::atan2(dif.z,dif.y);
rot.yaw = math::atan2(dif.y,dif.x);
return rot;
};
Vector3 translatePoint(Vector3 dif, Rot3 rot, bool fliproll = false, bool flippitch = false, bool flipyaw = false, bool useninety = false) {
float roll = rot.roll;
float pitch = rot.pitch;
float yaw = rot.yaw;
float xx = dif.x;
float yy = dif.y;
float zz = dif.z;
float m = math::sqrt(xx*xx+yy*yy+zz*zz);
//printf("%f\n",m);
//float x = sqrt(pow(m*cos(roll),2)+pow(m*cos(yaw),2));
//float y = sqrt(pow(m*sin(yaw),2)+pow(m*cos(pitch),2));
//float z = sqrt(pow(m*sin(pitch),2)+pow(m*sin(roll),2));
float x,y,z,x1,y1,z1,z2;
if (flipyaw == false) {
	x1 = m*math::cos(yaw);
	y1 = m*math::sin(yaw);
} else {
	if (useninety == false) {
		x1 = m*math::sin(yaw);
		y1 = m*math::cos(yaw);
	} else {
		x1 = m*math::cos(yaw+90);
		y1 = m*math::sin(yaw+90);
	}
}
if (fliproll == false) {
	x = x1*math::cos(roll);
	z2 = x1*math::sin(roll);
} else {
	if (useninety == false) {
		x = x1*math::sin(roll);
		z2 = x1*math::cos(roll);
	} else {
		x = x1*math::cos(roll+90);
		z2 = x1*math::sin(roll+90);
	}
}
if (flippitch == false) {
	y = y1*math::cos(pitch);
	z1 = y1*math::sin(pitch);
} else {
	if (useninety == false) {
		y = y1*math::sin(pitch);
		z1 = y1*math::cos(pitch);
	} else {
		y = y1*math::cos(pitch+90);
		z1 = y1*math::sin(pitch+90);
	}
}

	
float normalz = abs(z1)/z1;
z = math::sqrt(z1*z1+z2*z2)*normalz;
//m = sqrt(x*x+y*y+z*z);
//printf("%f\n\n",m);
Vector3 ret = {x,y,z};
return ret;
}
};
#endif

//0x18ACBAD
#define ENTITY_BLOCKER_BOOL ((bool*)0x18ACBAD)
int ENTITY_BLOCKER_CONST = 0x94030503;
#define ENTITY_BLOCKER (*(char*)(0x9589CEAE^ENTITY_BLOCKER_CONST))


//0x18ACC05 is the check
#define GAME_AWARD_CHECK_BOOL ((bool*)0x18ACC05)
int GAME_AWARD_CHECK_CONST = 0xCE6039E6;
#define GAME_AWARD_CHECK (*(char*)(0xcfeaf5e3^GAME_AWARD_CHECK_CONST))
bool okayOnThisSCHash(unsigned int hash) {
	if (hash == 0xD36120CE && GAME_AWARD_CHECK == 1) {//game_award
		return false;
	}
	return true;
}
	
void unk_0x5ECF955D_hook(unsigned int r3) {

	unsigned int arg = *(volatile unsigned int*)*(volatile int*)(r3+0x8);
	unsigned int retVal = call<unsigned int>(0x429E70)(arg);//call the native func
	if (!okayOnThisSCHash(retVal)) {
		retVal = 0;
	}
	unsigned int addr = *(volatile unsigned int*)(r3+0x0);
	*(volatile unsigned int*)addr = retVal;
}

void setup_unk_0x5ECF955D_hook() {
	PatchInJumpAddr(0x159D608,(int)unk_0x5ECF955D_hook,false);
}




namespace forge {
	int objectListOption = 0;
	bool enabled = false;
	int curObject = 0;
	float increment = 0.01;
	int blackListedObject = 0;
	Vector3 loc = {0,0,0};
	Vector3 rot = {0,0,0};
	//bool creatorMode = true;
	//Vector3 creatorModeRot = {0,0,0};
	Plane3D plane = {0,0,0,&loc};
	int clipDistance = 10;
	int playerToAttachTo = 0;
	bool gunLook = false;
	bool vaccume = false;
	int vaccumeTimeout = 0;
	char *propHashes[] = {"prop_a4_pile_01"};//,"prop_a4_sheet_01","prop_abat_roller_static","prop_abat_slide","prop_acc_guitar_01","prop_aerial_01a","prop_afsign_amun","prop_agave_01","prop_aiprort_sign_01","prop_aircon_l_01","prop_aircon_m_09","prop_aircon_s_01a","prop_airhockey_01","prop_air_bagloader","prop_alarm_01","prop_alien_egg_01","prop_aloevera_01","prop_amanda_note_01","prop_amb_40oz_02","prop_amb_beer_bottle","prop_amb_ciggy_01","prop_amb_donut","prop_amp_01","prop_am_box_wood_01","prop_anim_cash_note","prop_apple_box_01","prop_arcade_01","prop_arc_blueprints_01","prop_armchair_01","prop_armenian_gate","prop_armour_pickup","prop_arm_gate_l","prop_arm_wrestle_01","prop_artgallery_02_dl","prop_artgallery_dl","prop_artifact_01","prop_ashtray_01","prop_asteroid_01","prop_atm_02","prop_attache_case_01","prop_aviators_01","prop_a_base_bars_01","prop_a_trailer_door_01","prop_bahammenu","prop_ballistic_shield","prop_bandsaw_01","prop_bank_shutter","prop_barbell_01","prop_barier_conc_01b","prop_barn_door_l","prop_barrachneon","prop_barrel_01a","prop_barriercrash_03","prop_barrier_wat_01a","prop_barrier_work01c","prop_barry_table_detail","prop_bar_coastbarr","prop_basejump_target_01","prop_basketball_net","prop_bath_dirt_01","prop_battery_01","prop_bball_arcade_01","prop_bbq_2","prop_beachbag_01","prop_beachball_02","prop_beachflag_le","prop_beach_bars_01","prop_beach_bbq","prop_beerneon","prop_beer_bison","prop_beggers_sign_01","prop_bench_01b","prop_beta_tape","prop_beware_dog_sign","prop_bh1_03_gate_l","prop_bh1_08_mp_gar","prop_bh1_09_mp_gar","prop_bh1_16_display","prop_bh1_44_door_01l","prop_bh1_48_backdoor_l","prop_bh1_48_gate_1","prop_bhhotel_door_l","prop_big_bag_01","prop_big_clock_01","prop_big_shit_01","prop_bikerack_2","prop_bikini_disp_01","prop_billboard_01","prop_billb_frame01a","prop_binoc_01","prop_bin_04a","prop_biolab_g_door","prop_biotech_store","prop_bison_winch","prop_blackjack_01","prop_bleachers_01","prop_blox_spray","prop_bmu_01","prop_bodyarmour_02","prop_bollard_01a","prop_bomb_01","prop_bonesaw","prop_bongos_01","prop_bong_01","prop_boogbd_stack_01","prop_boogieboard_01","prop_boombox_01","prop_bottle_cap_01","prop_bowling_ball","prop_bowl_crisps","prop_boxcar5_handle","prop_boxing_glove_01","prop_boxpile_10a","prop_box_ammo01a","prop_breadbin_01","prop_bread_rack_01","prop_broken_cboard_p1","prop_broken_cell_gate_01","prop_broom_unit_01","prop_bskball_01","prop_bs_map_door_01","prop_buckets_02","prop_bucket_01a","prop_buck_spade_01","prop_bumper_01","prop_burto_gate_01","prop_bush_dead_02","prop_bush_grape_01","prop_bush_ivy_01_1m","prop_bush_ivy_02_1m","prop_bush_lrg_01","prop_bush_med_01","prop_bush_neat_01","prop_bush_ornament_01","prop_busker_hat_01","prop_byard_bench01","prop_b_board_blank","prop_c4_final","prop_cabinet_01","prop_cablespool_01a","prop_cable_hook_01","prop_camera_strap","prop_candy_pqs","prop_can_canoe","prop_cap_01","prop_carcreeper","prop_cargo_int","prop_carjack","prop_carjack_l2","prop_carrier_bag_01","prop_cartwheel_01","prop_carwash_roller_horz","prop_car_battery_01","prop_car_bonnet_01","prop_car_door_01","prop_car_engine_01","prop_car_exhaust_01","prop_car_ignition","prop_casey_sec_id","prop_cash_case_01","prop_cash_crate_01","prop_cash_dep_bag_01","prop_cash_envelope_01","prop_cash_note_01","prop_cash_pile_01","prop_cash_trolly","prop_casino_door_01l","prop_cattlecrush","prop_cat_tail_01","prop_cctv_02_sm","prop_cctv_cont_01","prop_cctv_unit_01","prop_cementmixer_01a","prop_ceramic_jug_01","prop_ch1_07_door_01l","prop_ch2_05d_g_door","prop_ch2_07b_20_g_door","prop_ch2_09b_door","prop_ch2_09c_garage_door","prop_ch3_01_trlrdoor_l","prop_ch3_04_door_01l","prop_chair_01a","prop_chall_lamp_01","prop_chateau_chair_01","prop_cheetah_covered","prop_chem_grill","prop_cherenneon","prop_chickencoop_a","prop_chip_fryer","prop_choc_ego","prop_ch_025c_g_door_01","prop_cigar_01","prop_clapper_brd_01","prop_cleaver","prop_cliff_paper","prop_clippers_01","prop_clothes_rail_02","prop_clothes_tub_01","prop_clown_chair","prop_cntrdoor_ld_l","prop_coathook_01","prop_cockneon","prop_coffee_cup_trailer","prop_coffee_mac_02","prop_coffin_02","prop_coke_block_01","prop_compressor_01","prop_com_gar_door_01","prop_com_ls_door_01","prop_conc_sacks_02a","prop_cone_float_1","prop_conschute","prop_consign_01c","prop_conslift_base","prop_console_01","prop_construcionlamp_01","prop_const_fence01a","prop_cons_crate","prop_container_01a","prop_contnr_pile_01a","prop_controller_01","prop_control_rm_door_01","prop_cont_chiller_01","prop_cooker_03","prop_copier_01","prop_copper_pan","prop_coral_bush_01","prop_coral_flat_01","prop_coral_grass_01","prop_coral_kelp_01","prop_coral_pillar_01","prop_coral_spikey_01","prop_coral_stone_03","prop_coral_sweed_01","prop_cora_clam_01","prop_cork_board","prop_couch_01","prop_crane_01_truck1","prop_cranial_saw","prop_crashed_heli","prop_cratepile_07a_l1","prop_crate_01a","prop_creosote_b_01","prop_crisp","prop_crisp_small","prop_crosssaw_01","prop_cs1_14b_traind","prop_cs4_05_tdoor","prop_cs4_10_tr_gd_01","prop_cs4_11_door","prop_cs6_03_door_l","prop_cs_20m_rope","prop_cs_30m_rope","prop_cs_abattoir_switch","prop_cs_aircon_01","prop_cs_amanda_shoe","prop_cs_ashtray","prop_cub_door_lifeblurb","prop_cub_lifeblurb","prop_cuff_keys_01","prop_cup_saucer_01","prop_curl_bar_01","prop_damdoor_01","prop_dart_1","prop_defilied_ragdoll_01","prop_desert_iron_01","prop_detergent_01a","prop_devin_box_01","prop_devin_rope_01","prop_diggerbkt_01","prop_direct_chair_01","prop_display_unit_01","prop_disp_cabinet_002","prop_disp_razor_01","prop_distantcar_day","prop_dj_deck_01","prop_dock_bouy_1","prop_dock_crane_01","prop_dock_float_1","prop_dock_moor_01","prop_dock_ropefloat","prop_dog_cage_01","prop_dolly_01","prop_donut_01","prop_door_01","prop_double_grid_line","prop_dress_disp_01","prop_drop_armscrate_01","prop_drop_crate_01","prop_drug_burner","prop_drywallpile_01","prop_dt1_13_groundlight","prop_dt1_20_mp_door_l","prop_dt1_20_mp_gar","prop_ducktape_01","prop_dummy_01","prop_dumpster_3a","prop_d_balcony_l_light","prop_d_balcony_r_light","prop_ear_defenders_01","prop_ecg_01","prop_ecola_can","prop_egg_clock_01","prop_ejector_seat_01","prop_elecbox_03a","prop_el_guitar_01","prop_employee_month_01","prop_energy_drink","prop_entityxf_covered","prop_epsilon_door_l","prop_etricmotor_01","prop_exer_bike_01","prop_faceoffice_door_l","prop_face_rag_01","prop_facgate_01","prop_fac_machine_02","prop_fag_packet_01","prop_fan_01","prop_fax_01","prop_fbi3_coffee_table","prop_fbibombbin","prop_fbibombcupbrd","prop_fbibombfile","prop_fbibombplant","prop_feeder1","prop_feed_sack_01","prop_fence_log_01","prop_ferris_car_01","prop_ff_counter_01","prop_ff_noodle_01","prop_ff_shelves_01","prop_ff_sink_01","prop_fib_badge","prop_film_cam_01","prop_fireescape_01a","prop_fire_driser_1a","prop_fire_hosereel","prop_fishing_rod_01","prop_fish_slice_01","prop_flagpole_1a","prop_flare_01","prop_flash_unit","prop_flatbed_strap","prop_flatscreen_overlay","prop_flattrailer_01a","prop_flattruck_01a","prop_fleeca_atm","prop_flight_box_01","prop_flipchair_01","prop_floor_duster_01","prop_fncconstruc_02a","prop_fnccorgm_05a","prop_fnclink_01gate1","prop_fnclog_01a","prop_fncpeir_03a","prop_fncres_02a","prop_fncsec_01a","prop_fncwood_07gate1","prop_folded_polo_shirt","prop_folder_01","prop_food_bin_01","prop_food_bs_bshelf","prop_food_burg1","prop_forsalejr2","prop_forsalejr3","prop_forsalejr4","prop_foundation_sponge","prop_fountain1","prop_fountain2","prop_franklin_dl","prop_freeweight_01","prop_fridge_01","prop_front_seat_01","prop_fruitstand_b_nite","prop_fruit_basket","prop_ftowel_01","prop_f_b_insert_broken","prop_f_duster_01_s","prop_f_duster_02","prop_gaffer_arm_bind","prop_gaffer_leg_bind","prop_gaffer_tape","prop_game_clock_01","prop_garden_dreamcatch_01","prop_garden_edging_01","prop_garden_zapper_01","prop_gardnght_01","prop_gar_door_01","prop_gascage01","prop_gascyl_ramp_01","prop_gas_01","prop_gatecom_02","prop_gate_airport_01","prop_gate_bridge_ld","prop_gate_cult_01_l","prop_gate_docks_ld","prop_gate_farm_01a","prop_gate_frame_01","prop_gate_military_01","prop_gate_prison_01","prop_gate_tep_01_l","prop_gazebo_03","prop_gd_ch2_08","prop_generator_02a","prop_ghettoblast_02","prop_girder_01a","prop_glasscutter_01","prop_glass_suck_holder","prop_glf_roller","prop_gold_bar","prop_golf_bag_01","prop_golf_ball","prop_grain_hopper","prop_grapes_01","prop_grass_dry_02","prop_gravestones_01a","prop_gravetomb_01a","prop_griddle_01","prop_grumandoor_l","prop_gshotsensor_01","prop_gun_case_01","prop_gun_frame","prop_hacky_sack_01","prop_handdry_01","prop_handrake","prop_handtowels","prop_hand_toilet","prop_hanger_door_1","prop_hard_hat_01","prop_hat_box_01","prop_haybailer_01","prop_haybale_01","prop_hd_seats_01","prop_headphones_01","prop_headset_01","prop_hedge_trimmer_01","prop_helipad_01","prop_henna_disp_01","prop_hifi_01","prop_hobo_stove_01","prop_hockey_bag_01","prop_hole_plug_01","prop_holster_01","prop_homeless_matress_01","prop_hose_1","prop_hospitaldoors_start","prop_hospital_door_l","prop_hotel_clock_01","prop_hotel_trolley","prop_hottub2","prop_huf_rag_01","prop_huge_display_01","prop_hunterhide","prop_hw1_03_gardoor_01","prop_hw1_04_door_l1","prop_hw1_23_door","prop_hwbowl_pseat_6x1","prop_hwbowl_seat_01","prop_hydro_platform_01","prop_ice_box_01","prop_ice_cube_01","prop_id2_11_gdoor","prop_id2_20_clock","prop_idol_01","prop_id_21_gardoor_01","prop_indus_meet_door_l","prop_ind_barge_01","prop_ind_coalcar_01","prop_ind_conveyor_01","prop_ind_crusher","prop_inflatearch_01","prop_inflategate_01","prop_ing_camera_01","prop_ing_crowbar","prop_inhaler_01","prop_int_gate01","prop_in_tray_01","prop_irish_sign_01","prop_iron_01","prop_jb700_covered","prop_jeans_01","prop_jetski_ramp_01","prop_jet_bloodsplat_01","prop_jewel_02a","prop_juice_dispenser","prop_jukebox_01","prop_jyard_block_01a","prop_j_disptray_01","prop_j_heist_pic_01","prop_j_neck_disp_01","prop_kayak_01","prop_kebab_grill","prop_keg_01","prop_kettle","prop_kettle_01","prop_keyboard_01a","prop_kino_light_01","prop_kitch_juicer","prop_knife","prop_knife_stand","prop_kt1_06_door_l","prop_kt1_10_mpdoor_l","prop_ladel","prop_laptop_02_closed","prop_laptop_jimmy","prop_large_gold","prop_lawnmower_01","prop_ld_alarm_01","prop_ld_ammo_pack_01","prop_ld_armour","prop_leaf_blower_01","prop_lectern_01","prop_letterbox_04","prop_lev_crate_01","prop_lev_des_barge_01","prop_lifeblurb_01","prop_life_ring_02","prop_lift_overlay_01","prop_litter_picker","prop_loggneon","prop_logpile_05","prop_log_01","prop_loose_rag_01","prop_lrggate_01c_l","prop_lrggate_01_l","prop_lrggate_02_ld","prop_lrggate_03a","prop_luggage_01a","prop_magenta_door","prop_makeup_trail_01","prop_map_door_01","prop_mast_01","prop_mat_box","prop_mb_cargo_01a","prop_mb_crate_01a","prop_mb_hesco_06","prop_mb_ordnance_01","prop_mb_sandblock_01","prop_medal_01","prop_medstation_02","prop_med_bag_01","prop_med_jet_01","prop_megaphone_01","prop_mem_candle_04","prop_mem_reef_01","prop_mem_teddy_01","prop_metalfoodjar_01","prop_metal_plates01","prop_meth_bag_01","prop_michaels_credit_tv","prop_michael_backpack","prop_microphone_02","prop_microwave_1","prop_micro_01","prop_military_pickup_01","prop_mil_crate_01","prop_minigun_01","prop_mobile_mast_1","prop_money_bag_01","prop_monitor_01c","prop_motel_door_09","prop_mouse_01","prop_movie_rack","prop_mp3_dock","prop_mp_arrow_barrier_01","prop_mp_barrier_01","prop_mp_base_marker","prop_mp_boost_01","prop_mp_cant_place_lrg","prop_mp_cone_01","prop_mp_drug_package","prop_mp_icon_shad_lrg","prop_mp_max_out_lrg","prop_mp_num_0","prop_mp_placement","prop_mr_rasberryclean","prop_muscle_bench_01","prop_muster_wboard_01","prop_m_pack_int_01","prop_necklace_board","prop_news_disp_02a_s","prop_new_drug_pack_01","prop_nigel_bag_pickup","prop_night_safe_01","prop_notepad_01","prop_novel_01","prop_npc_phone","prop_office_alarm_01","prop_office_desk_01","prop_offroad_bale01","prop_off_chair_01","prop_off_phone_01","prop_oiltub_01","prop_oil_derrick_01","prop_oil_guage_01","prop_oil_spool_02","prop_oil_valve_01","prop_oil_wellhead_01","prop_oldplough1","prop_old_boot","prop_orang_can_01","prop_outdoor_fan_01","prop_out_door_speaker","prop_overalls_01","prop_owl_totem_01","prop_paints_can01","prop_paint_brush01","prop_pallettruck_01","prop_palm_fan_02_a","prop_palm_fan_03_a","prop_palm_fan_04_a","prop_palm_huge_01a","prop_palm_med_01a","prop_palm_sm_01a","prop_paper_bag_01","prop_paper_ball","prop_pap_camera_01","prop_parachute","prop_parapack_01","prop_parasol_01","prop_parking_sign_06","prop_parking_wand_01","prop_park_ticket_01","prop_partsbox_01","prop_passport_01","prop_patio_heater_01","prop_patio_lounger1","prop_patriotneon","prop_paynspray_door_l","prop_pc_01a","prop_peanut_bowl_01","prop_ped_pic_01","prop_pencil_01","prop_pharm_sign_01","prop_phonebox_05a","prop_phone_ing","prop_picnictable_02","prop_piercing_gun","prop_pier_kiosk_01","prop_pile_dirt_01","prop_ping_pong","prop_pipes_01a","prop_pipe_single_01","prop_pistol_holster","prop_pitcher_01_cs","prop_pizza_box_01","prop_pizza_oven_01","prop_planer_01","prop_plant_01a","prop_plastic_cup_02","prop_plas_barier_01a","prop_plate_04","prop_player_gasmask","prop_pliers_01","prop_plywoodpile_01a","prop_podium_mic","prop_police_door_l","prop_police_phone","prop_poly_bag_01","prop_poolball_1","prop_poolskimmer","prop_pooltable_02","prop_pool_ball_01","prop_pool_cue","prop_porn_mag_01","prop_portable_hifi_01","prop_portacabin01","prop_portasteps_01","prop_postcard_rack","prop_poster_tube_01","prop_postit_drive","prop_potatodigger","prop_pot_01","prop_power_cell","prop_premier_fence_01","prop_printer_01","prop_pris_bars_01","prop_pris_bench_01","prop_pris_door_01_l","prop_pris_door_02","prop_prlg_gravestone_05a_l1","prop_prlg_gravestone_06a","prop_projector_overlay","prop_prologue_phone","prop_prop_tree_01","prop_protest_sign_01","prop_protest_table_01","prop_prototype_minibomb","prop_proxy_chateau_table","prop_punch_bag_l","prop_pylon_01","prop_p_jack_03_col","prop_p_spider_01a","prop_ql_revolving_door","prop_quad_grid_line","prop_radiomast01","prop_radiomast02","prop_rad_waste_barrel_01","prop_ragganeon","prop_rag_01","prop_railsleepers01","prop_railsleepers02","prop_railstack01","prop_railstack02","prop_railstack03","prop_railstack04","prop_railstack05","prop_rail_boxcar","prop_range_target_01","prop_rebar_pile01","prop_recyclebin_02a","prop_ret_door","prop_rf_conc_pillar","prop_riding_crop_01","prop_riot_shield","prop_rio_del_01","prop_roadcone01a","prop_roadcone01b","prop_roadcone01c","prop_roadcone02a","prop_roadcone02b","prop_roadcone02c","prop_roadheader_01","prop_rock_1_a","prop_rock_2_a","prop_rock_3_a","prop_rock_4_c","prop_rock_chair_01","prop_rolled_sock_01","prop_rolled_yoga_mat","prop_roller_car_01","prop_ron_door_01","prop_roofpipe_01","prop_roofvent_011a","prop_rope_family_3","prop_rope_hook_01","prop_roundbailer01","prop_roundbailer02","prop_rub_bike_01","prop_rub_binbag_sd_01","prop_rub_busdoor_01","prop_rub_buswreck_01","prop_rub_cabinet","prop_rural_windmill_l1","prop_rus_olive","prop_sacktruck_01","prop_safety_glasses","prop_sam_01","prop_sandwich_01","prop_satdish_2_a","prop_satdish_3_b","prop_satdish_l_01","prop_satdish_s_03","prop_sc1_06_gate_l","prop_sc1_12_door","prop_sc1_21_g_door_01","prop_scaffold_pole","prop_scafold_01a","prop_scalpel","prop_scn_police_torch","prop_scourer_01","prop_scrap_2_crate","prop_scrap_win_01","prop_scrim_01","prop_scythemower","prop_section_garage_01","prop_securityvan_lightrig","prop_security_case_01","prop_sec_gate_01b","prop_set_generator_01","prop_sewing_fabric","prop_sglasses_stand_01","prop_sglasss_1b_lod","prop_sglasss_1_lod","prop_shamal_crash","prop_shelves_01","prop_shopping_bags01","prop_shop_front_door_l","prop_shots_glass_cs","prop_shower_01","prop_showroom_door_l","prop_showroom_glass_1b","prop_shredder_01","prop_shrub_rake","prop_shuttering01","prop_shuttering02","prop_shuttering03","prop_shuttering04","prop_sh_beer_pissh_01","prop_sh_bong_01","prop_sh_cigar_01","prop_sh_joint_01","prop_sh_mr_rasp_01","prop_sh_shot_glass","prop_sh_tall_glass","prop_sh_tt_fridgedoor","prop_sh_wine_glass","prop_side_lights","prop_sign_airp_01a","prop_sign_big_01","prop_sign_mallet","prop_single_grid_line","prop_single_rose","prop_sink_01","prop_skate_flatramp","prop_skid_chair_01","prop_skid_sleepbag_1","prop_skid_tent_01","prop_skip_01a","prop_skunk_bush_01","prop_skylight_01","prop_sky_cover_01","prop_slacks_01","prop_sluicegate","prop_sluicegatel","prop_sluicegater","prop_slush_dispenser","prop_sm1_11_doorl","prop_smg_holster_01","prop_sm_10_mp_door","prop_sm_14_mp_gar","prop_sm_19_clock","prop_sm_27_door","prop_sm_locker_door","prop_snow_bailer_01","prop_snow_barrel_pile_03","prop_snow_bench_01","prop_snow_bin_01","prop_snow_bush_01_a","prop_snow_bush_02_a","prop_snow_bush_03","prop_snow_cam_03","prop_snow_diggerbkt_01","prop_snow_dumpster_01","prop_snow_elecbox_16","prop_snow_facgate_01","prop_snow_field_01","prop_snow_flower_01","prop_snow_fnclink_03crnr2","prop_snow_fncwood_14a","prop_snow_fnc_01","prop_snow_gate_farm_03","prop_snow_grain_01","prop_snow_grass_01","prop_snow_light_01","prop_snow_oldlight_01b","prop_snow_rail_signals02","prop_snow_rub_trukwreck_2","prop_snow_side_spreader_01","prop_snow_streetlight01","prop_soap_disp_01","prop_solarpanel_01","prop_sol_chair","prop_space_pistol","prop_speaker_01","prop_speedball_01","prop_sponge_01","prop_sports_clock_01","prop_spot_01","prop_sprayer","prop_spraygun_01","prop_spray_backpack_01","prop_spray_jackframe","prop_sprink_crop_01","prop_sprink_golf_01","prop_sprink_park_01","prop_spycam","prop_squeegee","prop_ss1_05_mp_door","prop_ss1_08_mp_door_l","prop_ss1_10_door_l","prop_ss1_14_garage_door","prop_ss1_mpint_door_l","prop_ss1_mpint_garage","prop_stag_do_rope","prop_start_finish_line_01","prop_start_grid_01","prop_staticmixer_01","prop_stat_pack_01","prop_steam_basket_01","prop_steps_big_01","prop_stickbfly","prop_stickhbird","prop_still","prop_stockade_wheel","prop_stool_01","prop_storagetank_01","prop_stripmenu","prop_strip_door_01","prop_strip_pole_01","prop_studio_light_02","prop_sub_chunk_01","prop_sub_cover_01","prop_sub_crane_hook","prop_sub_frame_01a","prop_sub_gantry","prop_suitcase_01","prop_surf_board_ldn_01","prop_syringe_01","prop_s_pine_dead_01","prop_tablesaw_01","prop_tablesmall_01","prop_table_02","prop_taco_01","prop_tail_gate_col","prop_tapeplayer_01","prop_target_arm","prop_tarp_strap","prop_taxi_meter_1","prop_tea_trolly","prop_telegraph_01a","prop_telegwall_01a","prop_telescope","prop_telescope_01","prop_temp_block_blocker","prop_tennis_bag_01","prop_tennis_ball","prop_test_boulder_01","prop_test_elevator","prop_tick","prop_tick_02","prop_till_01_dam","prop_till_02","prop_time_capsule_01","prop_tint_towel","prop_toaster_01","prop_toiletfoot_static","prop_toilet_01","prop_toolchest_01","prop_tool_adjspanner","prop_toothbrush_01","prop_toothb_cup_01","prop_toothpaste_01","prop_tornado_wheel","prop_torture_01","prop_tourist_map_01","prop_towel2_01","prop_towel_01","prop_towercrane_01a","prop_traffic_rail_1c","prop_trailer01","prop_trailer01_up","prop_trailer_01_new","prop_trailer_door_closed","prop_trailer_monitor_01","prop_trailr_base","prop_train_ticket_02","prop_tram_pole_double01","prop_tree_birch_01","prop_tree_cedar_02","prop_tree_cypress_01","prop_tree_eng_oak_01","prop_tree_eucalip_01","prop_tree_fallen_01","prop_tree_jacada_01","prop_tree_lficus_02","prop_tree_log_01","prop_tree_maple_02","prop_tree_mquite_01","prop_tree_oak_01","prop_tree_olive_01","prop_tree_pine_01","prop_tree_stump_01","prop_trevor_rope_01","prop_trev_sec_id","prop_trev_tv_01","prop_triple_grid_line","prop_tri_finish_banner","prop_tri_pod","prop_trough1","prop_truktrailer_01a","prop_tshirt_box_02","prop_tshirt_shelf_1","prop_tshirt_stand_01","prop_tt_screenstatic","prop_tumbler_01","prop_tunnel_liner01","prop_turkey_leg_01","prop_turnstyle_01","prop_tv_02","prop_tyre_rack_01","prop_tyre_spike_01","prop_t_coffe_table","prop_t_shirt_ironing","prop_t_sofa","prop_umpire_01","prop_utensil","prop_valet_03","prop_vault_shutter","prop_vb_34_tencrt_lighting","prop_vcr_01","prop_veg_corn_01","prop_veg_crop_01","prop_veg_grass_01_a","prop_veg_grass_02_a","prop_vehicle_hook","prop_vend_coffe_01","prop_vend_condom_01","prop_vend_fags_01","prop_vend_fridge01","prop_venice_board_01","prop_venice_counter_01","prop_venice_shop_front_01","prop_venice_sign_09","prop_ventsystem_01","prop_ven_market_stool","prop_ven_shop_1_counter","prop_vertdrill_01","prop_voltmeter_01","prop_v_15_cars_clock","prop_v_5_bclock","prop_v_bmike_01","prop_v_cam_01","prop_v_door_44","prop_v_hook_s","prop_v_m_phone_01","prop_v_parachute","prop_waiting_seat_01","prop_wait_bench_01","prop_walllight_ld_01b","prop_wall_light_08a","prop_wall_vent_01","prop_wardrobe_door_01","prop_warehseshelf01","prop_warehseshelf02","prop_warehseshelf03","prop_warninglight_01","prop_washer_01","prop_washing_basket_01","prop_watercrate_01","prop_wateringcan","prop_watertower01","prop_watertower02","prop_watertower03","prop_watertower04","prop_waterwheela","prop_waterwheelb","prop_water_bottle","prop_weed_01","prop_weight_10k","prop_welding_mask_01","prop_weld_torch","prop_wheat_grass_empty","prop_wheelbarrow01a","prop_wheelbarrow02a","prop_wheelchair_01","prop_wheel_01","prop_whisk","prop_white_keyboard","prop_winch_hook_long","prop_windmill2","prop_windmill_01_l1","prop_windowbox_a","prop_win_plug_01","prop_win_trailer_ld","prop_wok","prop_woodpile_02a","prop_worklight_01a_l1","prop_worklight_03a_l1","prop_worklight_03b_l1","prop_worklight_04a","prop_workwall_01","prop_wreckedcart","prop_wrecked_buzzard","prop_w_board_blank","prop_w_fountain_01","prop_w_r_cedar_01","prop_yacht_lounger","prop_yaught_chair_01","prop_yaught_sofa_01","prop_yell_plastic_target","prop_yoga_mat_01","prop_ztype_covered","p_ing_skiprope_01","p_skiprope_r_s","test_prop_gravestones_04a","test_prop_gravetomb_01a"};
	//char *propFavorites[] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};//64
	bool attachToPlayerOnSpawn = false;
	int attachToPlayerOnSpawnPlayer = 0;
	bool attachToPlayerOnSpawnCollision = false;
	bool attachToPlayerOnSpawnInvisibility = false;
	bool attachToSecondObjectWaiting = false;//not used yet
	bool moneyDrop = false;


	/*void moveInDir(float r) {
		float rotx = creatorModeRot.x+-rot.z;
		float roty = creatorModeRot.y+rot.x;
		float z = r*math::Sin(roty);
		float r2 = r*math::Cos(roty);
		float x = r2*math::Sin(rotx);
		float y = r2*math::Cos(rotx);
		loc.x+=x;
		loc.y+=y;
		loc.z+=z;
	}*/

#ifdef creationSpawner
	struct object {
		unsigned int model;
		float x;
		float y;
		float z;
		float rotx;
		float roty;
		float rotz;
	};
	//const unsigned int sizeOfObject = 28;
	struct creation {
		char signature[4];
		short size;
		short relativeToPlayer;//0 = no, 1 = yes, 2 = vehicle
		//int relativeToPlayer;
		object objects[100];
		//ArrayList<object> objects;
	};
	const unsigned int sizeOfCreation = sizeof(creation);//sizeOfObject*100+4;
	creation Creation;
	opd_s _0x7C6339DF_t = {0x3ACFF0,TOC};
	int (*_0x7C6339DF)(Vector3 *savePos,int entity, int bone) = (int(*)(Vector3*,int,int))&_0x7C6339DF_t;
	int currentCreationObjectIndex = 0;
	Vector3 playerCoords = {0,0,0};
	void spawnCreationCallback(int previousObject) {
		if (ENTITY::DOES_ENTITY_EXIST(previousObject)) {
			Vector3 loc = {Creation.objects[currentCreationObjectIndex-1].x,Creation.objects[currentCreationObjectIndex-1].y,Creation.objects[currentCreationObjectIndex-1].z};
			Vector3 rot = {Creation.objects[currentCreationObjectIndex-1].rotx,Creation.objects[currentCreationObjectIndex-1].roty,Creation.objects[currentCreationObjectIndex-1].rotz};
			//char buf[100];
			//snprintf$(buf,sizeof(buf),"x: %f, y: %f, z: %f\n",loc.x,loc.y,loc.z);
			//printf(buf);
			if (Creation.relativeToPlayer == 1) {
				loc.x+=playerCoords.x;
				loc.y+=playerCoords.y;
				loc.z+=playerCoords.z;
			}
			ENTITY::SET_ENTITY_COORDS(previousObject,loc.x,loc.y,loc.z,rot.x,rot.y,rot.z,true);
			if (Creation.relativeToPlayer == 2) {//vehicle
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(),false)) {
					int veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),false);
					Vector3 r = ENTITY::GET_ENTITY_ROTATION(veh,2);
					/*rot.x+=r.x;
					rot.y+=r.y;
					rot.z+=r.z;*/
					OBJ::attachPropAlreadySpawnedObject(veh,ENTITY::_0xE4ECAC22(veh,"engine"),previousObject,loc,rot);
					//ENTITY::ATTACH_ENTITY_TO_ENTITY(previousObject,veh,-1,loc.x,loc.y,loc.z,r.x,r.y,r.z,true,false,false,false,0,true);
				} else {
					print2("~r~You are not in a vehicle!",1000);
				}
			}
		}
		if (currentCreationObjectIndex < 100) {
			while(Creation.objects[currentCreationObjectIndex].model == 0) {
				currentCreationObjectIndex++;
				if (currentCreationObjectIndex > 99) {
					currentCreationObjectIndex = 0;
					return;
				}
			}

			/*spawn object (doesn't really matter position)*/
			Vector3 pos = {Creation.objects[currentCreationObjectIndex].x,Creation.objects[currentCreationObjectIndex].y,Creation.objects[currentCreationObjectIndex].z};
			Vector3 rot = {Creation.objects[currentCreationObjectIndex].rotx,Creation.objects[currentCreationObjectIndex].roty,Creation.objects[currentCreationObjectIndex].rotz};
			if (Creation.relativeToPlayer == 1 || Creation.relativeToPlayer == 2) {
				pos.x+=playerCoords.x;
				pos.y+=playerCoords.y;
				pos.z+=playerCoords.z;
			}
			OBJ::forceCreateObject(Creation.objects[currentCreationObjectIndex].model,pos,rot,true,spawnCreationCallback,false);


			currentCreationObjectIndex++;
		} else {
			currentCreationObjectIndex = 0;
		}
	}
	void clearCreation();
	//bool creationClonePlace = false;//for the positioning submenu
#ifdef savecreation
	void saveCreation(char *name) {
		Creation.signature[0] = 'C';
		Creation.signature[1] = 'R';
		Creation.signature[2] = 'E';
		Creation.signature[3] = 'A';
		Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true);
		Vector3 savePos[100];
		//set coords and rot for offset
		if (Creation.relativeToPlayer == 1) {
			for (int i = 0; i < 100; i++) {
				if (Creation.objects[i].model != 0) {
					Creation.objects[i].x-=playerCoords.x;
					Creation.objects[i].y-=playerCoords.y;
					Creation.objects[i].z-=playerCoords.z;
				}
			}
		}
		if (Creation.relativeToPlayer == 2 && PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(),false)) {
			int veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),false);
			Vec3 rr = ENTITY::GET_ENTITY_ROTATION(veh,2);
			Rot3 r = {ENTITY::GET_ENTITY_ROLL(veh),ENTITY::GET_ENTITY_PITCH(veh),rr.z};
			Vector3 vpos = {0,0,0};/*ENTITY::GET_ENTITY_COORDS(veh,1);*/
			int part = ENTITY::_0xE4ECAC22(veh,"engine");
			printf("Part: %i\n",part);
			_0x7C6339DF(&vpos,veh,part);//GET_WORLD_POSITION_OF_ENTITY_BONE
			Vector3 vpos2 = ENTITY::GET_ENTITY_COORDS(veh,1);
			Vector3 vposd = rotationMath::getDif(vpos,vpos2);
			//char buf[50];
			snprintf$(global_temporary_buf,sizeof(global_temporary_buf),"q1: %f %f %f\n",vpos.x,vpos.y,vpos.z);
			printf(global_temporary_buf);
			snprintf$(global_temporary_buf,sizeof(global_temporary_buf),"dif: %f %f %f\n",vposd.x,vposd.y,vposd.z);
			printf(global_temporary_buf);
			for (int i = 0; i < 100; i++) {
				if (Creation.objects[i].model != 0) {


					/*Creation.objects[i].rotx-=r.x;
					Creation.objects[i].roty-=r.y;
					Creation.objects[i].rotz-=r.z;*/
					/*Creation.objects[i].rotx*=-1;
					Creation.objects[i].roty*=-1;
					Creation.objects[i].rotz*=-1;*/

					/*Vector3 objpos = {Creation.objects[i].x,Creation.objects[i].y,Creation.objects[i].z};
					//float r = math::length(vpos,objpos);
					float difx = objpos.x-vpos.x;//left right
					float dify = objpos.y-vpos.y;//forward back
					float difz = objpos.z-vpos.z;//up down
					float rotx = GAMEPLAY::ATAN2(difz,dify);
					float roty = GAMEPLAY::ATAN2(difz,difx);
					float rotz = GAMEPLAY::ATAN2(dify,difx);

					Vector3 o = {vpos.x,vpos.y,vpos.z};
					Plane3D p = {roty,rotx,rotz,&o};
					p.yaw*=-1;
					p.rotateAroundOrigin(objpos,&objpos);
					
					savePos[i].x = Creation.objects[i].x;
					savePos[i].y = Creation.objects[i].y;
					savePos[i].z = Creation.objects[i].z;

					Creation.objects[i].x=objpos.x-vpos.x;
					Creation.objects[i].y=objpos.y-vpos.y;
					Creation.objects[i].z=objpos.z-vpos.z;*/


					Vec3 car = vpos;//{28,595,15};
					Vec3 obj = {Creation.objects[i].x,Creation.objects[i].y,Creation.objects[i].z};
					Rot3 carRot = r;//{r.rol,r.x,r.z};
					Vec3 dif = rotationMath::getDif(car,obj);
					//dif.x*=-1;//x axis is flipped
					Rot3 rot = rotationMath::getRot(dif);
					//rot.yaw*=-1;
					rot.roll-=carRot.roll;
					rot.pitch-=carRot.pitch;
					rot.yaw-=carRot.yaw;
					Vec3 n = rotationMath::translatePoint(dif,rot);
					Creation.objects[i].x = n.x;
					Creation.objects[i].y = n.y;
					Creation.objects[i].z = n.z;
				}
			}
		}
		


		//save to the file
		//char buf[100];
		snprintf$(global_temporary_buf,sizeof(global_temporary_buf),"/dev_hdd0/tmp/gopro_2027/%s.creation",name);
		writeToFile(global_temporary_buf,(char*)&Creation,sizeOfCreation);
		print2("Creation saved!",2000);




		//reset coords and rot
		if (Creation.relativeToPlayer == 1) {
			for (int i = 0; i < 100; i++) {
				if (Creation.objects[i].model != 0) {
					Creation.objects[i].x+=playerCoords.x;
					Creation.objects[i].y+=playerCoords.y;
					Creation.objects[i].z+=playerCoords.z;
				}
			}
		}
		if (Creation.relativeToPlayer == 2 && PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(),false)) {
			int veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(),false);
			Vector3 r = ENTITY::GET_ENTITY_ROTATION(veh,2);
			//Vector3 c = ENTITY::_0x7C6339DF(veh,-1);//GET_WORLD_POSITION_OF_ENTITY_BONE
			for (int i = 0; i < 100; i++) {
				if (Creation.objects[i].model != 0) {
					/*Creation.objects[i].rotx+=r.x;
					Creation.objects[i].roty+=r.y;
					Creation.objects[i].rotz+=r.z;
					Creation.objects[i].x=savePos[i].x;
					Creation.objects[i].y=savePos[i].y;
					Creation.objects[i].z=savePos[i].z;*/
				}
			}
			clearCreation();
			print2("Creation saved and cleared!",2000);
		}
	}
#endif
	bool loadCreation(char *name) {
		//Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true);
		//char buf[100];
		snprintf$(global_temporary_buf,sizeof(global_temporary_buf),"/dev_hdd0/tmp/gopro_2027/%s.creation",name);
		if (readFile(global_temporary_buf,(char*)&Creation,sizeOfCreation)) {
			/*if (Creation.relativeToPlayer == 1) {
				for (int i = 0; i < 100; i++) {
					if (Creation.objects[i].model != 0) {
						Creation.objects[i].x += playerCoords.x;
						Creation.objects[i].y += playerCoords.y;
						Creation.objects[i].z += playerCoords.z;
					}
				}
			}*/
			return true;
		}
		return false;
	}

	void spawnCreation(int nothing = 0) {
		playerCoords.x = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true).x;
		playerCoords.y = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true).y;
		playerCoords.z = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true).z;
		currentCreationObjectIndex = 0;
		spawnCreationCallback(0);
	}

	bool loadAndSpawnCreation(char *name) {//used for the presets forge menu
		if (forge::loadCreation(name)) {
			print2("Spawning creation relative to player.",2000);
			if (forge::Creation.relativeToPlayer == false)
				print2("Creation spawning non relative to player. You must go to it.",2000);
			//runlater::runlater(100,forge::spawnCreation,0);
			forge::spawnCreation();
			return true;
		} else {
			print2("~r~Creation not valid!",2000);
			return false;
		}
	}
	
	/*void clearCreation() {
		for (int i = 0; i < 100; i++) {
			Creation.objects[i].model = 0;
			Creation.objects[i].x = 0;
			Creation.objects[i].y = 0;
			Creation.objects[i].z = 0;
			Creation.objects[i].rotx = 0;
			Creation.objects[i].roty = 0;
			Creation.objects[i].rotz = 0;
		}
	}*/
	/*void addObjectToCreation(unsigned int entity) {
		if (ENTITY::DOES_ENTITY_EXIST(entity)) {
			for (int i = 0; i < 100; i++) {
				if (Creation.objects[i].model == 0) {
					Creation.objects[i].model = ENTITY::GET_ENTITY_MODEL(entity);
					Creation.objects[i].x = ENTITY::GET_ENTITY_COORDS(entity,1).x;
					Creation.objects[i].y = ENTITY::GET_ENTITY_COORDS(entity,1).y;
					Creation.objects[i].z = ENTITY::GET_ENTITY_COORDS(entity,1).z;
					Creation.objects[i].rotx = ENTITY::GET_ENTITY_ROTATION(entity,1).x;
					Creation.objects[i].roty = ENTITY::GET_ENTITY_ROTATION(entity,1).y;
					Creation.objects[i].rotz = ENTITY::GET_ENTITY_ROTATION(entity,1).z;
					return;
				}
			}
		}
	}*/

#endif
	//bool setEntityToAttachToMode = false;
	//int entityToAttachTo = 0;
	unsigned int gunObject = 0;
	bool gunmode = false;
	/*void addObjectToFavorites(char *object) {
		for (int i = 0; i < 64; i++) {
			if (propFavorites[i] == NULL) {
				propFavorites[i] = object;
				return;
			}
		}
		print("Object List Full!");
	}*/

	void cloneCallback(int previousObject) {
#ifdef creationSpawner
		if (ENTITY::DOES_ENTITY_EXIST(previousObject)) {
			ENTITY::FREEZE_ENTITY_POSITION(previousObject,1);
			Vector3 loc = {Creation.objects[currentCreationObjectIndex-1].x,Creation.objects[currentCreationObjectIndex-1].y,Creation.objects[currentCreationObjectIndex-1].z};
			Vector3 rot = {Creation.objects[currentCreationObjectIndex-1].rotx,Creation.objects[currentCreationObjectIndex-1].roty,Creation.objects[currentCreationObjectIndex-1].rotz};
			ENTITY::SET_ENTITY_COORDS(previousObject,loc.x,loc.y,loc.z,rot.x,rot.y,rot.z,true);
			curObject = previousObject;
		}
#endif
	}
	Vector3 normalizeVector(Vector3 dif, float distance) {
		float zrot = GAMEPLAY::ATAN2(dif.z,dif.x);
		float xrot = GAMEPLAY::ATAN2(dif.y,dif.x);
		float z = distance*math::Sin(zrot);
		float r2 = distance*math::Cos(zrot);
		float y = r2*math::Sin(xrot);
		float x = r2*math::Cos(xrot);
		Vector3 ret = {x,y,z};
		return ret;
	}
	/*bool forceGun = false;
	bool forceGunLoop() {
		if (forceGun) {
			int obj = -1;
			PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(),&obj);
			if (obj != -1 && ENTITY::DOES_ENTITY_EXIST(obj)) {
				if (ENTITY::IS_ENTITY_A_PED(obj))
					if (PED::IS_PED_IN_ANY_VEHICLE(obj,false))
						obj = PED::GET_VEHICLE_PED_IS_IN(obj,false);
				Vector3 zero = {0,0,0};
				Vector3 mycoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),1);
				Vector3 objcoords = ENTITY::GET_ENTITY_COORDS(obj,1);
				Vector3 dif = {objcoords.x-mycoords.x,objcoords.y-mycoords.y,objcoords.z-mycoords.z};
				APPLY_FORCE(obj,normalizeVector(dif,5),zero,1,false);
			}
		}
	}*/

	void clone() {
		if (ENTITY::DOES_ENTITY_EXIST(curObject)) {
			ENTITY::FREEZE_ENTITY_POSITION(curObject,1);
			OBJ::forceCreateObject(ENTITY::GET_ENTITY_MODEL(curObject),ENTITY::GET_ENTITY_COORDS(curObject,1),ENTITY::GET_ENTITY_ROTATION(curObject,1),true,cloneCallback,false);
			curObject = 0;
		}
	}

	void lookingPosition() {
		if (gunLook == true) {
			if (ENTITY::DOES_ENTITY_EXIST(curObject)) {
				if (PLAYER::IS_PLAYER_FREE_AIMING(PLAYER::PLAYER_ID()) == true) {
					Vector3 tmp = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true);
					Vector3 c = noclip::GET_COORDS_INFRONT(clipDistance);
					loc.x = tmp.x+c.x;
					loc.y = tmp.y+c.y;
					loc.z = tmp.z+c.z;
				}
			}
		}
	}

	void setPosition() {
		randomizeAddresses();
		//printf("1a\n");
		if (ENTITY::DOES_ENTITY_EXIST(curObject)) {
			//printf("2a\n");
			if (netreq::hasent(curObject)) {
				/*if (setEntityToAttachToMode) {
					if (ENTITY::DOES_ENTITY_EXIST(entityToAttachTo)) {
						float pos[] = {loc.x,loc.y,loc.z};
						float rot1[] = {rot.x,rot.y,rot.z};
						printf("curObject: %i entityToAttachTo: %i\n",curObject,entityToAttachTo);
						if (curObject != entityToAttachTo)
							OBJ::ATTACH_ENTITY_TO_ENTITY_F(entityToAttachTo,PLAYER::PLAYER_PED_ID(), 0, pos, rot1, 1, 1, 0, 0, 2, 1);
					}
				} else {*/
					//OBJECT::SLIDE_OBJECT(curObject, loc.x,loc.y,loc.z, 0.2f, 0.2f, 0.2f, 1);
					//if (!ENTITY::IS_ENTITY_AN_OBJECT) {
						ENTITY::SET_ENTITY_COORDS(curObject,loc.x,loc.y,loc.z,rot.x,rot.y,rot.z,true);
						ENTITY::SET_ENTITY_ROTATION(curObject,rot.x+plane.pitch,rot.y+plane.roll,rot.z+plane.yaw,2,1);
					//}

				//}
			}
		} else {
			//printf("2b\n");
		}
	}

	void reset(int ret = 0) {
		curObject = 0;
		blackListedObject = 0;
		vaccumeTimeout = 0;
	}

	void remove() {
		if (ENTITY::DOES_ENTITY_EXIST(curObject)) {
			netreq::reqent(curObject);
			if (netreq::hasent(curObject)) {
				markEntityForDeletion(curObject,reset);// :)
			}
		}
	}

	void detach() {
		if (ENTITY::DOES_ENTITY_EXIST(curObject)) {
			ENTITY::DETACH_ENTITY(curObject,true,true);
			//detachEntityViaPoolFunctions(curObject);
			//curObject = 0;
			//blackListedObject = 0;
		}
	}

	//bool collision = false;
	void setCollision(bool collision) {
		if (ENTITY::DOES_ENTITY_EXIST(curObject)) {
			//collision = !collision;
			ENTITY::SET_ENTITY_COLLISION(curObject,collision,0);
			if (collision == true) {
				print("Collision: true");
			} else {
				print("Collision: false");
			}
		}
	}

	void setVisible(bool visible) {
		if (ENTITY::DOES_ENTITY_EXIST(curObject)) {
			//collision = !collision;
			ENTITY::SET_ENTITY_VISIBLE(curObject,visible);
			if (visible == true) {
				print("Visibility: true");
			} else {
				print("Visibility: false");
			}
		}
	}

	void setGravity(bool enabl) {
		if (ENTITY::DOES_ENTITY_EXIST(curObject)) {
			ENTITY::SET_ENTITY_HAS_GRAVITY(curObject,enabl);
			if (enabl == true) {
				print("Gravity: true");
			} else {
				print("Gravity: false");
			}
		}
	}

	void freeze(bool enabl) {
		if (ENTITY::DOES_ENTITY_EXIST(curObject)) {
			ENTITY::FREEZE_ENTITY_POSITION(curObject,enabl);
			if (enabl == true) {
				print("Frozen: true");
			} else {
				print("Frozen: false");
			}
		}
	}

	void attachToPlayer(int player, int bodyPart = PlayerMods::bones::Head) {
		if (ENTITY::DOES_ENTITY_EXIST(curObject)) {
			float l[] = {0,0,0};
			float r[] = {rot.x,rot.y,rot.z};
			OBJ::attachPropAlreadySpawned(player,bodyPart,curObject,l,r);
			if (attachToPlayerOnSpawnCollision == true) {
				setCollision(true);
			}
			if (attachToPlayerOnSpawnInvisibility == true) {
				setVisible(false);
			}
		}
	}

	/*void shootObject() {
		if (ENTITY::DOES_ENTITY_EXIST(curObject)) {
			if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID())) {
				curObject = 0;
				blackListedObject = curObject;
				Vector3 zero = {0,0,0};
				APPLY_FORCE(curObject,noclip::GET_COORDS_INFRONT(10),zero);
			}
		}
	}*/

	void setIdAfterSpawn(int id) {
		Vector3 tmp = ENTITY::GET_ENTITY_COORDS(id,true);
		loc.x = tmp.x;
		loc.y = tmp.y;
		loc.z = tmp.z;
		rot.x = 0;
		rot.y = 0;
		rot.z = 0;
		blackListedObject = 0;
		print("Entity spawned and set!");
		vaccumeTimeout = 0;

		/*if (ENTITY::DOES_ENTITY_EXIST(curObject)) {
			if (attachToPlayerOnSpawn == true) {
				attachToPlayer(attachToPlayerOnSpawnPlayer);
			}
		}*/
		if (ENTITY::DOES_ENTITY_EXIST(id)) {
			//if (!setEntityToAttachToMode)
				//entityToAttachTo = id;
			//else
				curObject = id;
			if (attachToPlayerOnSpawn == true) {
				attachToPlayer(attachToPlayerOnSpawnPlayer);
			}
		}
	}

	opd_s GET_GROUND_Z_FOR_3D_COORD_t = {0x3D4690,TOC};
	bool(*GET_GROUND_Z_FOR_3D_COORD_F)(float *, float *newz) = (bool(*)(float *,float *))&GET_GROUND_Z_FOR_3D_COORD_t;
	void spawnAtLook(unsigned int hash) {
		if (gunmode) {
			print2("Gun Mode Set!~n~Shoot To Spawn This Object",2000);
			gunObject = hash;
			return;
		}
		//Vector3 c = noclip::GET_COORDS_INFRONT(clipDistance);
		//Vector3 p = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true);
		//float x = p.x+c.x;
		//float y = p.y+c.y;
		//float z = p.z+c.z;
		//float newz = 0;
		//float coord[] = {c.x,c.y,50};
		//GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(x,y,z,&newz);
		//GET_GROUND_Z_FOR_3D_COORD_F(coord,&newz);
		Vector3 tmp = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true);
		Vector3 c = noclip::GET_COORDS_INFRONT(clipDistance);
		float cx = tmp.x+c.x;
		float cy = tmp.y+c.y;
		float cz = tmp.z+c.z;
		Vector3 ooo = {0,0,0};
		float newz = 0;
		float coord[] = {cx,cy,1000};
		GET_GROUND_Z_FOR_3D_COORD_F(coord,&newz);
		Vector3 coords = { cx, cy, newz};
		OBJ::forceCreateObject(hash,coords,ooo,false,setIdAfterSpawn,moneyDrop);
		STREAMING::REQUEST_COLLISION_FOR_MODEL(hash);
		//collision = false;
	}

	void spawnAtLook(char *hash) {
		spawnAtLook(GAMEPLAY::GET_HASH_KEY(hash));
	}

	opd_s GET_PED_LAST_WEAPON_IMPACT_COORD_t = { 0x468F40, TOC };
	int(*GET_PED_LAST_WEAPON_IMPACT_COORD)(int PedID, float* Coords) = (int(*)(int, float*))&GET_PED_LAST_WEAPON_IMPACT_COORD_t;
	void shootSpawningLoop() {
		if (gunmode) {
			float Loc[3];
			if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
			{
				if (GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), Loc))
				{
					Vector3 coords = {Loc[0],Loc[1],Loc[2]};
					Vector3 ooo = {0,0,0};
					OBJ::forceCreateObject(gunObject,coords,ooo,false,setIdAfterSpawn,moneyDrop);
				}
			}
		}
	}

	void getaimedentity() {
		int obj = 0;//this used to not be set to 0 and I guess that is what cuased the freeze. I think it was getting assigned to a random stack var and not overritten since the optimization changes
		bool ex = PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(),&obj);
		//bool ex = ENTITY::DOES_ENTITY_EXIST(obj);//this is freezing
		if (ex) {
			if (obj != curObject && obj != blackListedObject) {
				if (ENTITY::IS_ENTITY_A_PED(obj))
					if (PED::IS_PED_IN_ANY_VEHICLE(obj,false))
						obj = PED::GET_VEHICLE_PED_IS_IN(obj,false);
				Vector3 tmp = ENTITY::GET_ENTITY_COORDS(obj,true);
				loc.x = tmp.x;
				loc.y = tmp.y;
				loc.z = tmp.z;
				rot.x = 0;
				rot.y = 0;
				rot.z = 0;
				/*if (setEntityToAttachToMode) {
					if (ENTITY::DOES_ENTITY_EXIST(obj)) {
						forge::entityToAttachTo = obj;
						print("Chosen entity that you will be attaching spawned objects to");
					}
				} else {*/
					curObject = obj;
					blackListedObject = 0;
					print("Entity selected!");
					vaccumeTimeout = 0;
					if (ENTITY::DOES_ENTITY_EXIST(curObject)) {
						//if (!setEntityToAttachToMode)
							//entityToAttachTo = obj;
						if (attachToPlayerOnSpawn == true) {
							attachToPlayer(attachToPlayerOnSpawnPlayer);
						}
					}
				//}
			}
		}
	}

	void loop() {
		markEntityForDeletionLoop();//for the delete entity thing. Might as well put it in here
		
		if (enabled == true) {
			netreq::reqent(curObject);
			getaimedentity();
			lookingPosition();
			setPosition();
			if (vaccume == true) {
				if (vaccumeTimeout < 10000) {
					vaccumeTimeout++;
					remove();
				}
			}
			//shootObject();
		}
		//forceGunLoop();
	}


	void toggle() {
		enabled = !enabled;
		if (enabled == true) {
			rot.x = 0;
			rot.y = 0;
			rot.z = 0;
		} else {
			curObject = 0;
		}
	}

	int makePlayerDoFunntCarThingPlayer = 0;
	void makePlayerDoFunntCarThing1(int id) {
		float l[] = {0,0,0};
		float r[] = {0,0,0};
		OBJ::attachPropAlreadySpawned(makePlayerDoFunntCarThingPlayer,PlayerMods::bones::Head,id,l,r);
		ENTITY::SET_ENTITY_COLLISION(id,true,0);
		ENTITY::SET_ENTITY_VISIBLE(id,false);
	}
	int lockCarDoorCounter = 0;
	void lockCarDoor(int player) {
		if (lockCarDoorCounter > 500) {
			lockCarDoorCounter = 0;
			return;
		}
		int ped = PLAYER::GET_PLAYER_PED(player);
		if (PED::IS_PED_IN_ANY_VEHICLE(ped,true)) {
			int veh = PED::GET_VEHICLE_PED_IS_IN(ped,false);
			netreq::reqent(veh);
			if (netreq::hasent(veh)) {
				lockCarDoorCounter = 0;
				VEHICLE::SET_VEHICLE_DOORS_LOCKED(veh,4);//4 is locked, 1 is unlocked
			} else {
				runlater::runlater(5,lockCarDoor,player);
			}
		}
	}
	void makePlayerDoFunntCarThing(int player) {
		char *skirope = "p_ing_skiprope_01";
		makePlayerDoFunntCarThingPlayer = player;
		Vector3 tmp = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(player),true);
		Vector3 ooo = {0,0,0};
		OBJ::forceCreateObject(skirope,tmp,ooo,false,makePlayerDoFunntCarThing1);
		lockCarDoorCounter = 0;
		runlater::runlater(5,lockCarDoor,player);
	}

}
#pragma endregion
#pragma region rope
namespace rope {
	/*
	opd_s GET_PED_LAST_WEAPON_IMPACT_COORD_t = { 0x468F40, TOC };
	int(*GET_PED_LAST_WEAPON_IMPACT_COORD)(int PedID, float* Coords) = (int(*)(int, float*))&GET_PED_LAST_WEAPON_IMPACT_COORD_t;

	float Loc[3];
			if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
			{
				if (GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), Loc))
				{*/

	int spiderweb = 0;
	int lastspiderobject = 0;
	float spidermanweblength = 0;
	//void forcefunkforspidey(int i) {
	//	forceEntity(PLAYER::PLAYER_PED_ID(),0,25,0,0,0,0);
	//}
	void spidermanReturnFunc(int ent2) {
						if (ENTITY::DOES_ENTITY_EXIST(lastspiderobject))
							forge::markEntityForDeletion(lastspiderobject);
						lastspiderobject = ent2;
						if (ROPE::DOES_ROPE_EXIST(&spiderweb))
							ROPE::DELETE_ROPE(&spiderweb);
						ENTITY::SET_ENTITY_VISIBLE(ent2,false);
						ENTITY::FREEZE_ENTITY_POSITION(ent2,true);

						Vector3 c = PlayerMods::getPlayerLocation(PLAYER::PLAYER_ID());
						Vector3 v = ENTITY::GET_ENTITY_COORDS(ent2,1);//ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ent2, 0.0, 2.1, 0.6);
						spidermanweblength = math::length(c,v);
						//ROPE::ROPE_RESET_LENGTH(spiderweb,spidermanweblength);
						//always does 35 for some reason
						spiderweb = ROPE::ADD_ROPE(c.x,c.y,c.z,0.0,0.0,0.0,spidermanweblength,4,spidermanweblength,1.0,0.0,false,false,false,5.0,false,NULL);//(c.x, c.y, c.z, 0.0, 0.0, 0.0, 28.0, 1, -1.0, 0.5, 0.5, 0, 1, 1, 0x3f800000, 0, 0);
						//ROPE::LOAD_ROPE_DATA(rope, "ropeFamily3");
						//ROPE::ROPE_FORCE_LENGTH(spiderweb,spidermanweblength);
						int ent1 = PLAYER::PLAYER_PED_ID();

						printf("Rope Length: %i\n",(int)ROPE::_0xFD309DC8(spiderweb));
						
						ROPE::ATTACH_ENTITIES_TO_ROPE(spiderweb, ent1, ent2, c.x,c.y,c.z, v.x,v.y,v.z, 35.0, 0, 0, 0, 0);


						//runlater::runlater(5,forcefunkforspidey);//make player go faster
						
						
						//ROPE::_0x5187BED3(rope);//START_ROPE_WINDING
						//print("Spawned Rope");
						
						
						
						
						//Vector3 c = PlayerMods::getPlayerLocation(PLAYER::PLAYER_ID());
						//spiderweb = ROPE::ADD_ROPE(c.x,c.y,c.z,0.0,0.0,0.0,20.0,4,20.0,1.0,0.0,false,false,false,5.0,false,NULL);//(c.x, c.y, c.z, 0.0, 0.0, 0.0, 28.0, 1, -1.0, 0.5, 0.5, 0, 1, 1, 0x3f800000, 0, 0);
						//ROPE::LOAD_ROPE_DATA(rope, "ropeFamily3");
						//int ent1 = PLAYER::PLAYER_PED_ID();
						//Vector3 v = ENTITY::GET_ENTITY_COORDS(ent2,1);//ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ent2, 0.0, 2.1, 0.6);
						//ROPE::ATTACH_ENTITIES_TO_ROPE(spiderweb, ent1, ent2, c.x,c.y,c.z, v.x,v.y,v.z, 35.0, 0, 0, 0, 0);
						
						
						/*Vector3 attachLoc = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ent1,0,0,0);
						ROPE::ATTACH_ROPE_TO_ENTITY(rope, ent1, attachLoc.x, attachLoc.y, attachLoc.z, 1);
						printf("Loc: x:%i y:%i z:%i\n",(int)Loc[0],(int)Loc[1],(int)Loc[2]);
						ROPE::PIN_ROPE_VERTEX(rope,1,Loc[0],Loc[1],Loc[2]);
						ROPE::ATTACH_ROPE_TO_ENTITY(rope, ent1, attachLoc.x, attachLoc.y, attachLoc.z, 1);
						//ROPE::_0x5187BED3(rope);//START_ROPE_WINDING
						Vector3 loc2 = {Loc[0],Loc[1],Loc[2]};*/
						//ROPE::ROPE_FORCE_LENGTH(rope,math::length(c,loc2));
						//ROPE::SET_DISABLE_BREAKING(rope,true);
						//ROPE::ACTIVATE_PHYSICS(rope);
	}

	bool dospiderman = false;
	void spiderman() {
		if (dospiderman) {
			if (ENTITY::IS_ENTITY_IN_AIR(PLAYER::PLAYER_PED_ID())) {
				//Vector3 ro = CAM::GET_GAMEPLAY_CAM_ROT(2);
				Vector3 force = noclip::GET_COORDS_INFRONT(1);
				//forceEntityNonRel(PLAYER::PLAYER_PED_ID(),0,1,0,0,0,0);
				forceEntityNonRel(PLAYER::PLAYER_PED_ID(),force.x/2,force.y/2,0,0,0,0);
				//printf("ro: x:%i y:%i z:%i\n",ro.x,ro.y,ro.z);
			}
			if (!ENTITY::IS_ENTITY_IN_AIR(PLAYER::PLAYER_PED_ID()) && !PED::IS_PED_FALLING(PLAYER::PLAYER_PED_ID()) && PED::IS_PED_JUMPING(PLAYER::PLAYER_PED_ID())) {
				forceEntity(PLAYER::PLAYER_PED_ID(),0,0,10,0,0,0);
			}
			PlayerMods::allowRagdoll(false);
			ROPE::ROPE_LOAD_TEXTURES();
			/*if (spidermanweblength > 1) {
				if (ROPE::DOES_ROPE_EXIST(&spiderweb)) {
					spidermanweblength = spidermanweblength-0.1f;
					ROPE::ROPE_RESET_LENGTH(spiderweb,spidermanweblength);
					//int ent1 = PLAYER::PLAYER_PED_ID();
					//Vector3 attachLoc = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ent1,0,0,0);
					//ROPE::ATTACH_ROPE_TO_ENTITY(spiderweb, ent1, attachLoc.x, attachLoc.y, attachLoc.z, 1);
				}
			}*/
			float Loc[3];
			//Vector3 coords;
			
			//if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
			//{
				//if (GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), Loc))
				//{
			if (pressedButtons::r2jpressed) {
					if (ROPE::_0x5FDC1047()) {
						Vector3 c2 = PlayerMods::getPlayerLocation(PLAYER::PLAYER_ID());
						Vector3 rot = {0,0,0};
						//Vector3 c = {Loc[0],Loc[1],Loc[2]};
						Vector3 c = noclip::GET_COORDS_INFRONT(36.5f);
						c.x = c.x + c2.x;
						c.y = c.y + c2.y;
						c.z = c.z + c2.z;
						OBJ::forceCreateObject("p_ing_skiprope_01",c,rot,true,spidermanReturnFunc);
					} else {
						print("~r~Rope textures not loaded");
					}
			}
			if (pressedButtons::l2jpressed) {
				if (ENTITY::DOES_ENTITY_EXIST(lastspiderobject))
					forge::markEntityForDeletion(lastspiderobject);
				if (ROPE::DOES_ROPE_EXIST(&spiderweb))
					ROPE::DELETE_ROPE(&spiderweb);
			}
				//}
			//}
		}
	}


	//ALL OF THE SHIT BELOW HERE IS KINDA USELESS
	struct RopePlayer {
		int basePlayer;
		bool attachedTo[18];
		int ropes[18];
		RopePlayer() {
			for (int i = 0; i < 18; i++) {
				attachedTo[i] = false;
				ropes[i] = 0;
			}
		}

		int create(int id) {
			ROPE::ROPE_LOAD_TEXTURES();
			Vector3 Scoords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(id),true);
			Vector3 Ecoords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(basePlayer),true);
			float distance = GAMEPLAY::ABSF(Scoords.x - Ecoords.x) + GAMEPLAY::ABSF(Scoords.y - Ecoords.y) + GAMEPLAY::ABSF(Scoords.z - Ecoords.z);
			int rope = ROPE::ADD_ROPE(Scoords.x, Scoords.y, Scoords.z, Ecoords.x, Ecoords.y, Ecoords.z, distance ,3, 7.0f, 4.0f, 1.4f, 1, 1, 1, 1065353216, 0, 0);
			return rope;
		}
		void attach(int id) {
			int rope = create(id);
			int e1 = PLAYER::GET_PLAYER_PED(id);
			int e2 = PLAYER::GET_PLAYER_PED(basePlayer);
			Vector3 Scoords = ENTITY::GET_ENTITY_COORDS(e1,true);
			Vector3 Ecoords = ENTITY::GET_ENTITY_COORDS(e2,true);
			float distance = GAMEPLAY::ABSF(Scoords.x - Ecoords.x) + GAMEPLAY::ABSF(Scoords.y - Ecoords.y) + GAMEPLAY::ABSF(Scoords.z - Ecoords.z);
			ROPE::ATTACH_ENTITIES_TO_ROPE(rope,e1,e2,0,0,0,0,0,0,/*ROPE::_0xFD309DC8(rope)*/distance,0,0,0,0);
			attachedTo[id] = true;
			ropes[id] = rope;
		}
		void detach(int id) {
			if (attachedTo[id] == true) {
				//ROPE::DELETE_ROPE(ropes[id]);
				ropes[id] = 0;
				attachedTo[id] = false;
			}
		}
		void toggle(int id) {
			if (attachedTo[id] == true) {
				detach(id);
			} else {
				attach(id);
			}
		}
	};

	RopePlayer playerRopes[18];
	void init() {
		for (int i = 0; i < 18; i++)
			playerRopes[i].basePlayer = i;
	}
}
#pragma endregion
#pragma region minecraft
namespace minecraft {
	char *lava = "prop_mb_sandblock_01";//"prop_dumpster_3a";//"root_scrool_anim_skel";//prop_yell_plastic_target
	bool enabled = false;
	int clipDistance = 10;
	int timeout = 0;
	void drawLine(Vector3 p1, Vector3 p2) {
		GRAPHICS::DRAW_LINE(p1.x,p1.y,p1.z,p2.x,p2.y,p2.z,255,0,0,255);
	}
	void drawLine(Vector3 p1, Vector3 p2, unsigned char r, unsigned char g, unsigned char b) {
		GRAPHICS::DRAW_LINE(p1.x,p1.y,p1.z,p2.x,p2.y,p2.z,r,g,b,255);
	}
	void makePropNotUnspawn(int prop){ENTITY::SET_ENTITY_AS_MISSION_ENTITY(prop,1,1);}
	void loop() {
		if (enabled == true) {
			timeout--;
			if (timeout < 0) {
				timeout = -1;
				if (PLAYER::IS_PLAYER_FREE_AIMING(PLAYER::PLAYER_ID()) == true) {
					CONTROLS::DISABLE_CONTROL_ACTION(0, Button_L1);
					CONTROLS::SET_INPUT_EXCLUSIVE(2, Button_L1);
					CONTROLS::DISABLE_CONTROL_ACTION(0, Button_R1);
					CONTROLS::SET_INPUT_EXCLUSIVE(2, Button_R1);
					Vector3 tmp = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true);
					int bone = PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), 0x796E);
                    Vector3 handcoords = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), bone,0,0,0);
					Vector3 c = noclip::GET_COORDS_INFRONT(clipDistance);
					float cx = tmp.x+c.x;
					float cy = tmp.y+c.y;
					float cz = tmp.z+c.z;
					//int Type = -1;
					bool hit = true;
					//int entityhandle = 0;
					//Vector3 hitCoords, surfaceNormal;
					//int ray = WORLDPROBE::_0x8251485D(tmp.x,tmp.y,tmp.z,cx,cy,cz,Type,PLAYER::PLAYER_PED_ID(),7);
					//WORLDPROBE::_0xF3C2875A(ray, &hit, &hitCoords, &surfaceNormal, &entityhandle);
					//char buf[50];
					//snprintf$$(buf,sizeof(buf),"x: %f y: %f z: %f       %f",hitCoords.x,hitCoords.y,hitCoords.z,cx);
					//print(buf);
					float coeff = (1.0f/1.5f);
					float x = math::round(/*hitCoords.x*/cx*coeff)/coeff;
					float y = math::round(/*hitCoords.y*/cy*coeff)/coeff;
					float z = math::round(/*hitCoords.z*/cz*coeff)/coeff;
					GRAPHICS::DRAW_LINE(handcoords.x,handcoords.y,handcoords.z,x,y,z/*hitCoords.x,hitCoords.y,hitCoords.z*/,255,0,0,255);
					//GRAPHICS::DRAW_LINE(x,y,z,x,y,z+0.1f,0,0,255,255);
					//GRAPHICS::DRAW_LINE(x,y,z,x,y+0.1f,z,0,255,0,255);
					//GRAPHICS::DRAW_LINE(x,y,z,x+0.1f,y,z,255,255,255,255);
					Vector3 c1 = {x+0.75f,y+0.75f,z+0.1f};Vector3 c11 = {x+0.75f,y+0.75f,z-1.5f+0.1f};
					Vector3 c2 = {x+0.75f,y-0.75f,z+0.1f};Vector3 c22 = {x+0.75f,y-0.75f,z-1.5f+0.1f};
					Vector3 c3 = {x-0.75f,y-0.75f,z+0.1f};Vector3 c33 = {x-0.75f,y-0.75f,z-1.5f+0.1f};
					Vector3 c4 = {x-0.75f,y+0.75f,z+0.1f};Vector3 c44 = {x-0.75f,y+0.75f,z-1.5f+0.1f};
					drawLine(c1,c2);
					drawLine(c2,c3);
					drawLine(c3,c4);
					drawLine(c1,c4);

					drawLine(c11,c22);
					drawLine(c22,c33);
					drawLine(c33,c44);
					drawLine(c11,c44);

					drawLine(c1,c11);
					drawLine(c2,c22);
					drawLine(c3,c33);
					drawLine(c4,c44);

					if (hit != 0) {
						
						if (pressedButtons::l1pressed == true) {
							Vector3 coord = {x,y,z};
							Vector3 rot = {0,180,0};
							OBJ::forceCreateObject(lava,coord,rot,true,makePropNotUnspawn);
							timeout = 10;//originally 100
						}

						if (pressedButtons::r1pressed == true) {
							int obj;
							PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(),&obj);
							forge::markEntityForDeletion(obj);
							timeout = 20;//oriiginally 200
						}
					}
				}
			}
		}
	}

}
#pragma endregion
#pragma region bodyguard
namespace bodyguard {

	char *pmonkey = "a_c_chimp";
	char *pdeer = "a_c_deer";
	char *pcow = "a_c_cow";
	char *parmy = "s_m_m_marine_01";
	char *phipster = "a_m_y_hipster_01";

	namespace types {
		int Player=1,Male=4,Female=5,Cop=6,Human=26,SWAT=27,Animal = 28,Army = 29;
	}

	Vector3 lCoords = {0,0,0};
	int lPlayer = 0;
	char *lID = "";
	int lType = 0;
	bool lisbodyguard = true;
	bool go = false;
	bool timeout = 0;

	int recentlySpawnedPed = 0;
	void (*saveFunc)(int);

	void spawnNow(int player,char *id,int type, bool isbodyguard = true, void(*f)(int) = nullFunc) {
		bodyguard::recentlySpawnedPed = 0;
		lCoords.x = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(player),true).x;
		lCoords.y = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(player),true).y;
		lCoords.z = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(player),true).z;
		lPlayer = player;
		lID = id;
		lType = type;
		lisbodyguard = isbodyguard;
		go = true;
		saveFunc = f;
	}

	void spawnNow(Vector3 coords,char *id,int type,void(*f)(int) = nullFunc) {
		bodyguard::recentlySpawnedPed = 0;
		lCoords.x = coords.x;
		lCoords.y = coords.y;
		lCoords.z = coords.z;
		lID = id;
		lType = type;
		lPlayer = 0;
		lisbodyguard = false;
		go = true;
		saveFunc = f;
	}

	void setAsBodyguard(int ped, int player) {
		int player_group = PLAYER::GET_PLAYER_GROUP(player);//GTA.Native.Function.Call<int>(GTA.Native.Hash.GET_PLAYER_GROUP, Game.Player.Handle);
		PED::SET_PED_AS_GROUP_MEMBER(ped,player_group);//GTA.Native.Function.Call(GTA.Native.Hash.SET_PED_AS_GROUP_MEMBER, ped.Handle, player_group);
		//ped.RelationshipGroup = Game.Player.Character.RelationshipGroup;
		//SET_RELATIONSHIP_BETWEEN_GROUPS(int relationship, Hash group1, Hash group2)
		
		//ped.CanBeTargetted = true;
		PED::SET_PED_CAN_BE_TARGETTED(ped,true);
		//GTA.Native.Function.Call(GTA.Native.Hash.SET_PED_AS_GROUP_LEADER, Game.Player.Character, player_group);
		PED::SET_PED_AS_GROUP_LEADER(PLAYER::GET_PLAYER_PED(player),player_group);
		//ped.Weapons.Give(WeaponHash.MicroSMG, 1000, true, true);
		WEAPON::GIVE_WEAPON_TO_PED(ped, GAMEPLAY::GET_HASH_KEY("WEAPON_MINIGUN"), -1, true,true);
		PED::SET_PED_CAN_SWITCH_WEAPON(ped, true);
		//ped.Accuracy = 100;
		PED::SET_PED_ACCURACY(ped,100);
		//ped.IsInvincible = true;
		ENTITY::SET_ENTITY_PROOFS(ped,true,true,true,true,true,true,true,true);
		//ped.Task.FightAgainstHatedTargets(50000);
		//AI::TASK_COMBAT_HATED_TARGETS_AROUND_PED(ped,50000,0);
		//PED::SET_PED_COMBAT_ATTRIBUTES(ped,46,true);
		//PED::SET_PED_KEEP_TASK(ped,true);
		//ped.AlwaysKeepTask = true;
		PED::SET_PED_NEVER_LEAVES_GROUP(ped,player_group);

		PED::_0xD0D8BDBC(ped,player_group,true);
	}

	unsigned int modelHashToAddress2(unsigned int hash) {
		//(addrstruct().^dataDecryptor())
		opd_s modelHashToAddress_t2 = {(addrstruct().modelToHash^dataDecryptor())/*0x9D9830*/,TOC};//proper
		unsigned int (*modelHashToAddress_2)(unsigned int hash, unsigned int unk1,unsigned int unk2,unsigned int unk3) = (unsigned int(*)(unsigned int, unsigned int, unsigned int, unsigned int))&modelHashToAddress_t2;
		return modelHashToAddress_2(hash,0x10080400,0x0000FFFF,0xFFFFFFF0);
	}

	int spawn(Vector3 coords,char *id,int type, bool isbodyguard = true) {
		Vector3 tmp = coords;//ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true);
		Vector3 c = noclip::GET_COORDS_INFRONT(2);
		float cx = tmp.x+c.x;
		float cy = tmp.y;
		float cz = tmp.z+c.z;
		int ped = PED::CREATE_PED(type,GAMEPLAY::GET_HASH_KEY(id),cx,cy,cz,0.0f,true,false);

		if (isbodyguard == true) {

		setAsBodyguard(ped,lPlayer);
		}
		return ped;
	}

	void loop() {
		if (go == true) {
			timeout++;
			if (timeout > 5000) {
				timeout = 0;
				go = false;
				print("Timed Out");
				return;
			}
			int PigHash = GAMEPLAY::GET_HASH_KEY(lID);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(PigHash)) {
				if (STREAMING::IS_MODEL_VALID(PigHash)) {
					STREAMING::REQUEST_MODEL(PigHash);
					if (STREAMING::HAS_MODEL_LOADED(PigHash)) {
						int ped = spawn(lCoords,lID,lType,lisbodyguard);
						if (ENTITY::DOES_ENTITY_EXIST(ped)) {
							print("Spawned");
							timeout = 0;
							go = false;
							recentlySpawnedPed = ped;
							saveFunc(ped);
						}
					}
				}
			}
		}
	}
	int playerAlpha = 255;
}
#pragma endregion
#pragma region entity Mods
#ifdef entityModsLol
namespace entityMods {
	int entity1 = 0;
	int entity2 = 0;
	int entity3 = 0;
	int entity4 = 0;
	int entity5 = 0;

	int curEntity = 1;
	int curEntityComponentValue = 0;
	char *pedHashes[] = {"a_c_boar","a_c_chickenhawk","a_c_chimp","a_c_cormorant","a_c_cow","a_c_coyote","a_c_crow","a_c_deer","a_c_fish","a_c_hen","a_c_pig","a_c_pigeon","a_c_rat","a_c_rhesus","a_c_seagull","a_f_m_beach_01","a_f_m_bevhills_01","a_f_m_bevhills_02","a_f_m_bodybuild_01","a_f_m_business_02","a_f_m_downtown_01","a_f_m_eastsa_01","a_f_m_eastsa_02","a_f_m_fatbla_01","a_f_m_fatcult_01","a_f_m_fatwhite_01","a_f_m_ktown_01","a_f_m_ktown_02","a_f_m_prolhost_01","a_f_m_salton_01"};//,"a_f_m_skidrow_01","a_f_m_soucentmc_01","a_f_m_soucent_01","a_f_m_soucent_02","a_f_m_tourist_01","a_f_m_trampbeac_01","a_f_m_tramp_01","a_f_o_genstreet_01","a_f_o_indian_01","a_f_o_ktown_01","a_f_o_salton_01","a_f_o_soucent_01","a_f_o_soucent_02","a_f_y_beach_01","a_f_y_bevhills_01","a_f_y_bevhills_02","a_f_y_bevhills_03","a_f_y_bevhills_04","a_f_y_business_01","a_f_y_business_02","a_f_y_business_03","a_f_y_business_04","a_f_y_eastsa_01","a_f_y_eastsa_02","a_f_y_eastsa_03","a_f_y_epsilon_01","a_f_y_fitness_01","a_f_y_fitness_02","a_f_y_genhot_01","a_f_y_golfer_01","a_f_y_hiker_01","a_f_y_hippie_01","a_f_y_hipster_01","a_f_y_hipster_02","a_f_y_hipster_03","a_f_y_hipster_04","a_f_y_indian_01","a_f_y_juggalo_01","a_f_y_runner_01","a_f_y_rurmeth_01","a_f_y_scdressy_01","a_f_y_skater_01","a_f_y_soucent_01","a_f_y_soucent_02","a_f_y_soucent_03","a_f_y_tennis_01","a_f_y_topless_01","a_f_y_tourist_01","a_f_y_tourist_02","a_f_y_vinewood_01","a_f_y_vinewood_02","a_f_y_vinewood_03","a_f_y_vinewood_04","a_f_y_yoga_01","a_m_m_acult_01","a_m_m_afriamer_01","a_m_m_beach_01","a_m_m_beach_02","a_m_m_bevhills_01","a_m_m_bevhills_02","a_m_m_business_01","a_m_m_eastsa_01","a_m_m_eastsa_02","a_m_m_farmer_01","a_m_m_fatlatin_01","a_m_m_genfat_01","a_m_m_genfat_02","a_m_m_golfer_01","a_m_m_hasjew_01","a_m_m_hillbilly_01","a_m_m_hillbilly_02","a_m_m_indian_01","a_m_m_ktown_01","a_m_m_malibu_01","a_m_m_mexcntry_01","a_m_m_mexlabor_01","a_m_m_og_boss_01","a_m_m_paparazzi_01","a_m_m_polynesian_01","a_m_m_prolhost_01","a_m_m_rurmeth_01","a_m_m_salton_01","a_m_m_salton_02","a_m_m_salton_03","a_m_m_salton_04","a_m_m_skater_01","a_m_m_skidrow_01","a_m_m_socenlat_01","a_m_m_soucent_01","a_m_m_soucent_02","a_m_m_soucent_03","a_m_m_soucent_04","a_m_m_stlat_02","a_m_m_tennis_01","a_m_m_tourist_01","a_m_m_trampbeac_01","a_m_m_tramp_01","a_m_m_tranvest_01","a_m_m_tranvest_02","a_m_o_acult_01","a_m_o_acult_02","a_m_o_beach_01","a_m_o_genstreet_01","a_m_o_ktown_01","a_m_o_salton_01","a_m_o_soucent_01","a_m_o_soucent_02","a_m_o_soucent_03","a_m_o_tramp_01","a_m_y_acult_01","a_m_y_acult_02","a_m_y_beachvesp_01","a_m_y_beachvesp_02","a_m_y_beach_01","a_m_y_beach_02","a_m_y_beach_03","a_m_y_bevhills_01","a_m_y_bevhills_02","a_m_y_breakdance_01","a_m_y_busicas_01","a_m_y_business_01","a_m_y_business_02","a_m_y_business_03","a_m_y_cyclist_01","a_m_y_dhill_01","a_m_y_downtown_01","a_m_y_eastsa_01","a_m_y_eastsa_02","a_m_y_epsilon_01","a_m_y_epsilon_02","a_m_y_gay_01","a_m_y_gay_02","a_m_y_genstreet_01","a_m_y_genstreet_02","a_m_y_golfer_01","a_m_y_hasjew_01","a_m_y_hiker_01","a_m_y_hippy_01","a_m_y_hipster_01","a_m_y_hipster_02","a_m_y_hipster_03","a_m_y_indian_01","a_m_y_jetski_01","a_m_y_juggalo_01","a_m_y_ktown_01","a_m_y_ktown_02","a_m_y_latino_01","a_m_y_methhead_01","a_m_y_mexthug_01","a_m_y_motox_01","a_m_y_motox_02","a_m_y_musclbeac_01","a_m_y_musclbeac_02","a_m_y_polynesian_01","a_m_y_roadcyc_01","a_m_y_runner_01","a_m_y_runner_02","a_m_y_salton_01","a_m_y_skater_01","a_m_y_skater_02","a_m_y_soucent_01","a_m_y_soucent_02","a_m_y_soucent_03","a_m_y_soucent_04","a_m_y_stbla_01","a_m_y_stbla_02","a_m_y_stlat_01","a_m_y_stwhi_01","a_m_y_stwhi_02","a_m_y_sunbathe_01","a_m_y_surfer_01","a_m_y_vindouche_01","a_m_y_vinewood_01","a_m_y_vinewood_02","a_m_y_vinewood_03","a_m_y_vinewood_04","a_m_y_yoga_01","comp_peds_generic","comp_peds_helmets_moped","comp_peds_helmets_motox","comp_peds_helmets_shorty","comp_peds_helmets_sports","comp_peds_marine","csb_abigail","csb_anita","csb_anton","csb_ballasog","csb_bride","csb_burgerdrug","csb_car3guy1","csb_car3guy2","csb_chef","csb_chin_goon","csb_cletus","csb_cop","csb_customer","csb_denise_friend","csb_fos_rep","csb_g","csb_groom","csb_grove_str_dlr","csb_hao","csb_hugh","csb_imran","csb_janitor","csb_maude","csb_mweather","csb_ortega","csb_oscar","csb_porndudes","csb_prologuedriver","csb_prolsec","csb_ramp_gang","csb_ramp_hic","csb_ramp_hipster","csb_ramp_marine","csb_ramp_mex","csb_reporter","csb_roccopelosi","csb_screen_writer","csb_stripper_01","csb_stripper_02","csb_tonya","csb_trafficwarden","g_f_y_ballas_01","g_f_y_families_01","g_f_y_lost_01","g_f_y_vagos_01","g_m_m_armboss_01","g_m_m_armgoon_01","g_m_m_armlieut_01","g_m_m_chemwork_01","g_m_m_chiboss_01","g_m_m_chicold_01","g_m_m_chigoon_01","g_m_m_chigoon_02","g_m_m_korboss_01","g_m_m_mexboss_01","g_m_m_mexboss_02","g_m_y_armgoon_02","g_m_y_azteca_01","g_m_y_ballaeast_01","g_m_y_ballaorig_01","g_m_y_ballasout_01","g_m_y_famca_01","g_m_y_famdnf_01","g_m_y_famfor_01","g_m_y_korean_01","g_m_y_korean_02","g_m_y_korlieut_01","g_m_y_lost_01","g_m_y_lost_02","g_m_y_lost_03","g_m_y_mexgang_01","g_m_y_mexgoon_01","g_m_y_mexgoon_02","g_m_y_mexgoon_03","g_m_y_pologoon_01","g_m_y_pologoon_02","g_m_y_salvaboss_01","g_m_y_salvagoon_01","g_m_y_salvagoon_02","g_m_y_salvagoon_03","g_m_y_strpunk_01","g_m_y_strpunk_02","ig_abigail","ig_ashley","ig_bankman","ig_barry","ig_bestmen","ig_beverly","ig_bride","ig_car3guy1","ig_car3guy2","ig_casey","ig_chef","ig_chengsr","ig_chrisformage","ig_clay","ig_claypain","ig_cletus","ig_dale","ig_dreyfuss","ig_fbisuit_01","ig_groom","ig_hao","ig_hunter","ig_janet","ig_jewelass","ig_jimmyboston","ig_joeminuteman","ig_johnnyklebitz","ig_josef","ig_josh","ig_kerrymcintosh","ig_lifeinvad_01","ig_lifeinvad_02","ig_magenta","ig_manuel","ig_marnie","ig_maryann","ig_maude","ig_michelle","ig_mrsphillips","ig_mrs_thornhill","ig_natalia","ig_nigel","ig_old_man1a","ig_old_man2","ig_oneil","ig_ortega","ig_paper","ig_priest","ig_prolsec_02","ig_ramp_gang","ig_ramp_hic","ig_ramp_hipster","ig_ramp_mex","ig_roccopelosi","ig_russiandrunk","ig_screen_writer","ig_talina","ig_tanisha","ig_terry","ig_tomepsilon","ig_tonya","ig_trafficwarden","ig_tylerdix","ig_zimbor","mp_g_m_pros_01","mp_m_exarmy_01","slod_human","slod_large_quadped","slod_small_quadped","s_f_m_fembarber","s_f_m_maid_01","s_f_m_shop_high","s_f_m_sweatshop_01","s_f_y_airhostess_01","s_f_y_bartender_01","s_f_y_baywatch_01","s_f_y_cop_01","s_f_y_factory_01","s_f_y_hooker_01","s_f_y_hooker_02","s_f_y_hooker_03","s_f_y_migrant_01","s_f_y_movprem_01","s_f_y_ranger_01","s_f_y_scrubs_01","s_f_y_sheriff_01","s_f_y_shop_low","s_f_y_shop_mid","s_f_y_stripperlite","s_f_y_stripper_01","s_f_y_stripper_02","s_f_y_sweatshop_01","s_m_m_ammucountry","s_m_m_armoured_01","s_m_m_armoured_02","s_m_m_autoshop_01","s_m_m_autoshop_02","s_m_m_bouncer_01","s_m_m_chemsec_01","s_m_m_ciasec_01","s_m_m_cntrybar_01","s_m_m_dockwork_01","s_m_m_doctor_01","s_m_m_fiboffice_01","s_m_m_fiboffice_02","s_m_m_gaffer_01","s_m_m_gardener_01","s_m_m_gentransport","s_m_m_hairdress_01","s_m_m_highsec_01","s_m_m_highsec_02","s_m_m_janitor","s_m_m_lathandy_01","s_m_m_lifeinvad_01","s_m_m_linecook","s_m_m_lsmetro_01","s_m_m_mariachi_01","s_m_m_marine_01","s_m_m_marine_02","s_m_m_migrant_01","s_m_m_movalien_01","s_m_m_movprem_01","s_m_m_movspace_01","s_m_m_paramedic_01","s_m_m_pilot_01","s_m_m_pilot_02","s_m_m_postal_01","s_m_m_postal_02","s_m_m_prisguard_01","s_m_m_scientist_01","s_m_m_security_01","s_m_m_snowcop_01","s_m_m_strperf_01","s_m_m_strpreach_01","s_m_m_strvend_01","s_m_m_trucker_01","s_m_m_ups_01","s_m_m_ups_02","s_m_o_busker_01","s_m_y_airworker","s_m_y_ammucity_01","s_m_y_armymech_01","s_m_y_autopsy_01","s_m_y_barman_01","s_m_y_baywatch_01","s_m_y_blackops_01","s_m_y_blackops_02","s_m_y_busboy_01","s_m_y_chef_01","s_m_y_clown_01","s_m_y_construct_01","s_m_y_construct_02","s_m_y_cop_01","s_m_y_dealer_01","s_m_y_devinsec_01","s_m_y_dockwork_01","s_m_y_doorman_01","s_m_y_dwservice_01","s_m_y_dwservice_02","s_m_y_factory_01","s_m_y_fireman_01","s_m_y_garbage","s_m_y_grip_01","s_m_y_hwaycop_01","s_m_y_marine_01","s_m_y_marine_02","s_m_y_marine_03","s_m_y_mime","s_m_y_pestcont_01","s_m_y_pilot_01","s_m_y_prismuscl_01","s_m_y_prisoner_01","s_m_y_ranger_01","s_m_y_robber_01","s_m_y_sheriff_01","s_m_y_shop_mask","s_m_y_strvend_01","s_m_y_swat_01","s_m_y_uscg_01","s_m_y_valet_01","s_m_y_waiter_01","s_m_y_winclean_01","s_m_y_xmech_01","s_m_y_xmech_02","u_f_m_corpse_01","u_f_m_miranda","u_f_m_promourn_01","u_f_o_moviestar","u_f_o_prolhost_01","u_f_y_bikerchic","u_f_y_comjane","u_f_y_corpse_01","u_f_y_corpse_02","u_f_y_hotposh_01","u_f_y_jewelass_01","u_f_y_mistress","u_f_y_poppymich","u_f_y_princess","u_f_y_spyactress","u_m_m_aldinapoli","u_m_m_bankman","u_m_m_bikehire_01","u_m_m_fibarchitect","u_m_m_filmdirector","u_m_m_glenstank_01","u_m_m_griff_01","u_m_m_jesus_01","u_m_m_jewelsec_01","u_m_m_jewelthief","u_m_m_markfost","u_m_m_partytarget","u_m_m_prolsec_01","u_m_m_promourn_01","u_m_m_rivalpap","u_m_m_spyactor","u_m_m_willyfist","u_m_o_finguru_01","u_m_o_taphillbilly","u_m_o_tramp_01","u_m_y_abner","u_m_y_antonb","u_m_y_babyd","u_m_y_baygor","u_m_y_burgerdrug_01","u_m_y_chip","u_m_y_cyclist_01","u_m_y_fibmugger_01","u_m_y_guido_01","u_m_y_gunvend_01","u_m_y_hippie_01","u_m_y_imporage","u_m_y_justin","u_m_y_mani","u_m_y_militarybum","u_m_y_paparazzi","u_m_y_party_01","u_m_y_pogo_01","u_m_y_prisoner_01","u_m_y_proldriver_01","u_m_y_rsranger_01","u_m_y_sbike","u_m_y_staggrm_01","u_m_y_tattoo_01","u_m_y_zombie_01","a_c_chop","a_c_husky","a_c_mtlion","a_c_retriever","a_c_rottweiler","a_c_sharktiger","a_c_shepherd","hc_driver","hc_gunman","hc_hacker","ig_amandatownley","ig_andreas","ig_ballasog","ig_brad","ig_davenorton","ig_denise","ig_devin","ig_dom","ig_drfriedlander","ig_fabien","ig_floyd","ig_jay_norris","ig_jimmydisanto","ig_lamardavis","ig_lazlow","ig_lestercrest","ig_milton","ig_molly","ig_mrk","ig_nervousron","ig_omega","ig_orleans","ig_patricia","ig_siemonyetarian","ig_solomon","ig_stevehains","ig_stretch","ig_taocheng","ig_taostranslator","ig_tenniscoach","ig_tracydisanto","ig_wade","mp_f_deadhooker","mp_f_freemode_01","mp_f_misty_01","mp_f_stripperlite","mp_headtargets","mp_m_claude_01","mp_m_famdd_01","mp_m_fibsec_01","mp_m_freemode_01","mp_m_marston_01","mp_m_niko_01","mp_m_shopkeep_01","mp_s_m_armoured_01","player_one","player_two","player_zero"};
	//char *pedHashes[] = {"a_c_boar","a_c_chickenhawk","a_c_chimp","a_c_cormorant","a_c_cow","a_c_coyote","a_c_crow","a_c_deer","a_c_fish","a_c_hen","a_c_pig","a_c_pigeon","a_c_rat","a_c_rhesus","a_c_seagull","a_f_m_beach_01","a_f_m_bevhills_01","a_f_m_bevhills_02","a_f_m_bodybuild_01","a_f_m_business_02","a_f_m_downtown_01","a_f_m_eastsa_01","a_f_m_eastsa_02","a_f_m_fatbla_01","a_f_m_fatcult_01","a_f_m_fatwhite_01","a_f_m_ktown_01","a_f_m_ktown_02","a_f_m_prolhost_01","a_f_m_salton_01","a_f_m_skidrow_01","a_f_m_soucentmc_01"};
	
	char *animationsID[] = {""};
	char *animationsDict[] = {""};
	void setPed(int num, int ped) {
		if (num == 1) {
			entity1 = ped;
		}
		else if (num == 2) {
			entity2 = ped;
		}
		else if (num == 3) {
			entity3 = ped;
		}
		else if (num == 4) {
			entity4 = ped;
		}
		else if (num == 5) {
			entity5 = ped;
		}
	}

	int getPed(int num) {
		if (num == 1) {
			return entity1;
		}
		else if (num == 2) {
			return entity2;
		}
		else if (num == 3) {
			return entity3;
		}
		else if (num == 4) {
			return entity4;
		}
		else if (num == 5) {
			return entity5;
		}
		return -1;
	}
	
	bool updateRecentPed = false;

	void giveMinigun(int ped) {
		WEAPON::GIVE_WEAPON_TO_PED(ped, GAMEPLAY::GET_HASH_KEY("WEAPON_MINIGUN"), -1, true,true);
	}

	void removeAllGuns(int ped) {
		WEAPON::REMOVE_ALL_PED_WEAPONS(ped,true);
	}

	void setInvincible(int ped, bool enable) {
		ENTITY::SET_ENTITY_PROOFS(ped,enable,enable,enable,enable,enable,enable,enable,enable);
	}


	void setAsBodyguardd(int ped, int player) {
		int player_group = PLAYER::GET_PLAYER_GROUP(player);
		PED::SET_PED_AS_GROUP_LEADER(PLAYER::GET_PLAYER_PED(player),player_group);
		PED::SET_PED_AS_GROUP_MEMBER(ped,player_group);
		PED::SET_PED_CAN_BE_TARGETTED(ped,true);
		//WEAPON::GIVE_WEAPON_TO_PED(ped, GAMEPLAY::GET_HASH_KEY("WEAPON_MINIGUN"), -1, true,true);
		PED::SET_PED_CAN_SWITCH_WEAPON(ped, true);
		PED::SET_PED_ACCURACY(ped,100);
		//ENTITY::SET_ENTITY_PROOFS(ped,true,true,true,true,true,true,true,true);
		AI::TASK_COMBAT_HATED_TARGETS_AROUND_PED(ped,50000,0);
		PED::SET_PED_COMBAT_ATTRIBUTES(ped,46,true);
		PED::SET_PED_KEEP_TASK(ped,true);
		PED::SET_PED_NEVER_LEAVES_GROUP(ped,player_group);
		PED::SET_CAN_ATTACK_FRIENDLY(ped,false,false);
		PED::SET_PED_COMBAT_ABILITY(ped, 100);
		PED::_0xD0D8BDBC(ped,player_group,true);
	}

	void remove(int num);

	/*bool waitToUpdateRecentPed(int num) {
		if (updateRecentPed == true) {
			if (bodyguard::recentlySpawnedPed != 0) {
				remove(num);
				updateRecentPed = false;
				setPed(num,bodyguard::recentlySpawnedPed);
			}
		}
	}*/
	void updatePed(int ped) {
		if (ped != 0) {
			//PlayerMods::components::setFace(ped,0);
			curEntityComponentValue = 0;//PlayerMods::components::getTexture(ped,0);
			remove(curEntity);
			setPed(curEntity,ped);
		}
	}

	void initEntity(char *model,int num) {
		//updateRecentPed = true;
		bodyguard::spawnNow(PLAYER::PLAYER_ID(),model,bodyguard::types::Player,false,updatePed);
	}

	int changePlayerPedTestPlayer;
	void changePlayerPedTestCallback(int ped) {
		NETWORK::_0x99F58A07(ped,changePlayerPedTestPlayer);
	}
	void changePlayerPedTest(int player) {
		changePlayerPedTestPlayer = player;
		bodyguard::spawnNow(player,"s_m_m_marine_01",bodyguard::types::Player,false,changePlayerPedTestCallback);
	}

	void setAnim(char *dict, char *anim, int num) {
		PedAnim::anim(getPed(num),dict,anim);
	}

	void removeAsBodyguard(int num) {
		if (PED::IS_PED_IN_GROUP(getPed(num)) == true) {
			PED::REMOVE_PED_FROM_GROUP(getPed(num));
			PED::SET_PED_COMBAT_ABILITY(getPed(num), 0);
		}
	}

	void setAsBodyguard(int player, int num) {
		removeAsBodyguard(num);
		setAsBodyguardd(getPed(num),player);
	}

	bool isBodyguard(int num) {
		return PED::IS_PED_IN_GROUP(getPed(num));
	}

	bool isAlive(int num) {
		return !ENTITY::IS_ENTITY_DEAD(getPed(num));
	}

	/*int getPedGroupLeader(int num) {
		PED::GET_PED_GROUP_INDEX(getPed(num));
	}*/

	void remove(int num) {
		if(isAlive(num) == true) {
			int p = getPed(num);
			removeAsBodyguard(num);
			forge::markEntityForDeletion(p);
		}
	}

	void attachToPlayer(int player, int num) {
		if (isAlive(num) == true) {
			OBJ::attachPropAlreadySpawned(player,PlayerMods::bones::Head,getPed(num));
		}
	}

	void attackPlayer(int player, int num) {
		int my_group = PLAYER::GET_PLAYER_GROUP(PLAYER::GET_PLAYER_PED(player));
		PED::SET_PED_AS_GROUP_LEADER(PLAYER::GET_PLAYER_PED(player), my_group);
		PED::SET_PED_AS_GROUP_MEMBER(getPed(num), my_group);
		PED::SET_PED_COMBAT_ABILITY(getPed(num), 100);
		PED::REGISTER_TARGET(getPed(num),PLAYER::GET_PLAYER_PED(player));
		PED::SET_CAN_ATTACK_FRIENDLY(getPed(num),true,true);
		PED::SET_PED_AS_ENEMY(getPed(num),true);
		AI::TASK_COMBAT_PED(getPed(num),PLAYER::GET_PLAYER_PED(player), 0, 1);
		PED::SET_PED_COMBAT_ATTRIBUTES(getPed(num),46,true);
		PED::REMOVE_PED_FROM_GROUP(getPed(num));
	}

	void loop() {
		//waitToUpdateRecentPed(curEntity);
		for (int i = 1; i < 6; i++) {
			if(isAlive(i) == true) {
				//PlayerMods::components::setFace(getPed(curEntity),curEntityComponentValue);
				netreq::reqent(curEntity);
			}
		}
	}
}
#endif
#pragma endregion
#pragma region weapon Mods
namespace weaponMods {



	/*Vector3 GetImpactCoords() {
		float Loc[3];
		if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID())) {
			if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), Loc)) {
				Vector3 Coords;
				Coords.x = Loc[0], Coords.y = Loc[1], Coords.z = Loc[2];
				return Coords;
			}
		}
	}*/
	/*void explodeCoords(int ped, float co[]) {
		//float co[] = {coords.x,coords.y,coords.z};
		OTHER::ADD_OWNED_EXPLOSION(ped,co, PlayerMods::EXPLOSION_BLIMP, 0.5f, true, false, 0.0f);
		float Loc[3];
		if (PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED(i))) {
			if (GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::GET_PLAYER_PED(i), Loc)) {
				char buf[50];
				snprintf$$(buf,sizeof(buf),"shot x: %.1f, y: %.1f, z: %.1f",Loc[0],Loc[1],Loc[2]);
				print2(buf,3000);
				OTHER::ADD_OWNED_EXPLOSION(PLAYER::GET_PLAYER_PED(i),Loc, 29, 0.5f, true, false, 0.5f);
			}
		}
	}*/
	
	opd_s GET_PED_LAST_WEAPON_IMPACT_COORD_t = { 0x468F40, TOC};
	bool(*GET_PED_LAST_WEAPON_IMPACT_COORD)(uint ped, float* v) = (bool(*)(uint, float*))&GET_PED_LAST_WEAPON_IMPACT_COORD_t;

	bool explosiveEnabled[] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};
	bool explosiveThing[] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};
	void runExplosiveBullets() {
		for (int i = 0; i < 18; i++) {
			if (explosiveEnabled[i] == true) {
				float* Loc;
				if (PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED(i))) {
					if (explosiveThing[i] == true) {
						explosiveThing[i] = false;
						if (GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::GET_PLAYER_PED(i), Loc)) {
							//char buf[50];
							snprintf$(global_temporary_buf,sizeof(global_temporary_buf),"shot x: %.1f, y: %.1f, z: %.1f",Loc[0],Loc[1],Loc[2]);
							print2(global_temporary_buf,3000);
							//float ll[] = {Loc[0],Loc[2],Loc[1]};
							//OTHER::ADD_EXPLOSION(ll, 29, 0.5f, true, false, 0.5f);
							FIRE::ADD_OWNED_EXPLOSION(PLAYER::GET_PLAYER_PED(i),Loc[0],Loc[1],Loc[2],29, 0.5f, true, false, 0.5f);
						}
					}
				} else {
					explosiveThing[i] = true;
				}
			}
		}
	}

	bool infiniteAmmoBool[] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};
	void infiniteAmmo(int player) {
		infiniteAmmoBool[player] = !infiniteAmmoBool[player];
		WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::GET_PLAYER_PED(player),infiniteAmmoBool[player]);
	}


	bool osok = false;
	void toggleOneShotOneKill() {
		osok = !osok;
		if (osok) {
			PLAYER::_0x362E69AD(PLAYER::PLAYER_ID(), 9999);//PLAYER::SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_ID(), 9999); 
			PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_ID(), 9999); 
		} else {
			PLAYER::_0x362E69AD(PLAYER::PLAYER_ID(), 1);//PLAYER::SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_ID(), 9999); 
			PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_ID(), 1); 
		}
	}
}
#pragma endregion
#pragma region debugger
namespace debugger {
	int recent = 0x10000;
	char *text = "Set Text";
	int chosenlength = 8;
	bool docheck = false;
	void toHex(int num, char hex_string[], int size) {
		const unsigned int HEX_BASE = 16 ;
		const char *hex_digits = "0123456789abcdef" ;
		for (int i = 0; i < size; i++)hex_string[i] = '0';
		hex_string[1] = 'x';
		int n = num;
		int q = size-1;
		while( n != 0)
		{
		    hex_string[q] = hex_digits[ n % HEX_BASE ] ;
		    n /= HEX_BASE ;
		    q--;
		}
	}

	int scan(char find[], int length,int startt = 0x10000, int endd = 0x10010390) {
		for (unsigned int i = startt; i <= endd; i++) {
			for (unsigned int j = 0; j < length; j++) {
				if (*(volatile unsigned int*)(i+j) == find[j]) {
					if (j == length-1)
						return i;
				} else {
					j = length;
				}
			}
		}
		return -1;
	}

	void findNext(char f[], int length) {
		int i = scan(f,length,0,20/*recent*/);
		if (i == -1) {
			printNoCheck("~r~Not found!");
			recent = 0x10000;
		} else {
			char hex[10];
			toHex(i,hex,10);
			//char buf[100];
			snprintf$(global_temporary_buf,100,"~g~String %s found at %s",f,hex);
			printNoCheck(global_temporary_buf);
			recent = i;
		}
	}
	void fineNextSafe(char *textt, int length) {
		text = textt;
		chosenlength = length;
		docheck = true;
	}
	void loop() {
		if (docheck == true) {
			printNoCheck("~b~Finding...");
			docheck = false;
			findNext(text,chosenlength);
		}
	}


}
#pragma endregion
#pragma region Player Ped Control
#ifdef playerpedcontrolnamespace
namespace PlayerPedControl {
	int player = 0;
	bool go = false;
	void loop() {
		if (go == true) {
			int ped = PLAYER::GET_PLAYER_PED(player);
			int netid = netreq::getnetidfroment(ped);
			netreq::reqent(ped);
			netreq::reqid(netid);
			if (netreq::hasent(ped))print("Has ped control of player\n");
			if (netreq::hasnetid(netid))print("Has network id control of player\n");
		}
	}
	void toggle(int playerid) {
		player = playerid;
		go = !go;
		if (go)print("Finding...\n");
		if (!go)print("Stopping...\n");
	}
	void disablePlayerPedControlProtection() {//not even used
		*(char*)0x3E9FA3 = 0x01;
		print("~g~Player Ped Control Now Enabled");
	}
	void enablePlayerPedControlProtection() {
		*(char*)0x3E9FA3 = 0x00;
		print("~r~Player Ped Control Now Disabled");
	}
}
#endif
#pragma endregion
#pragma region anti cheater
namespace anticheater {
	float modelMin[3],modelMax[3];
	void getPlayerSize() {
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()),modelMin, modelMax);
	}
	BOOL hit; Vector3 endCoords; Vector3 surfaceNormal; Entity entityHandle = 0;
	void knockoffnext()
	{
    //Vector3 camCoords = CAM::GET_GAMEPLAY_CAM_COORD();
    //Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
    Vector3 farCoords = PlayerMods::getPlayerLocation(PLAYER::PLAYER_ID());
	farCoords.x = farCoords.x + GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(-1,1);
	farCoords.y = farCoords.y + GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(-1,1);
	Vector3 camCoords = {farCoords.x,farCoords.y,farCoords.z-1};
	farCoords.z = farCoords.z + 5;
        //farCoords.x = camCoords.x + rotToDir(rot).x * 1000;
        //farCoords.y = camCoords.y + rotToDir(rot).y * 1000;
        //farCoords.z = camCoords.z + rotToDir(rot).z * 1000;
	GRAPHICS::DRAW_LINE(camCoords.x, camCoords.y, camCoords.z, farCoords.x, farCoords.y, farCoords.z,255,0,0,255);
    int ray = WORLDPROBE::_0x8251485D(camCoords.x, camCoords.y, camCoords.z, farCoords.x, farCoords.y, farCoords.z/*,5*/, -1, 0/*PLAYER::PLAYER_PED_ID()*/, 7);//_0x591EA833 is 3d. currently it is non 3d
    WORLDPROBE::_0xF3C2875A(ray, &hit, &endCoords, &surfaceNormal, &entityHandle);
    if (/*hit && (*/ENTITY::DOES_ENTITY_EXIST(entityHandle)/*)*/)
    {
		if (entityHandle != PLAYER::PLAYER_PED_ID()) {
			if (ENTITY::IS_ENTITY_A_VEHICLE(entityHandle)) 
			     print("veh");
			else if (ENTITY::IS_ENTITY_A_PED(entityHandle)) 
			     print("ped");
			else if (ENTITY::IS_ENTITY_AN_OBJECT(entityHandle)) 
			     print("obj");
			forge::markEntityForDeletion(entityHandle);
		}
    }
	}  
	/*bool removePropsBool = false;
	void removePropsLoop() {
		if (removePropsBool) {
			Vector3 c = PlayerMods::getPlayerLocation(PLAYER::PLAYER_ID());
			GAMEPLAY::_0x20E4FFD9(c.x, c.y, c.z, 1, false, false, false, false);
			GAMEPLAY::CLEAR_AREA_OF_OBJECTS(c.x,c.y,c.z,1,0);
			GAMEPLAY::CLEAR_AREA_OF_OBJECTS(c.x,c.y,c.z,1,2);
			GAMEPLAY::CLEAR_AREA_OF_OBJECTS(c.x,c.y,c.z,1,6);
			GAMEPLAY::CLEAR_AREA_OF_OBJECTS(c.x,c.y,c.z,1,16);
			GAMEPLAY::CLEAR_AREA_OF_OBJECTS(c.x,c.y,c.z,1,17);
		}
	}*/
}
#pragma endregion
#pragma region Weather and Time
namespace timeandweather {
	int hours = 0;
	int minutes = 0;
	int seconds = 0;
	bool timeFrozen = false;
}
#pragma endregion
#pragma region generators
#ifdef moneygenerator
namespace generators {
	class Money {
	private:
		int counter;
	public:
		Vector3 location;
		int player;
		bool hasBeenInitiated;
		bool enabled;
		float radius;
		int numberspawn;
		int speed;
		char prop[100];
		Money() {
			radius = 2;
			for (int i = 0; i < 100; i++)
				prop[i] = 0;
			strcpy(prop,"prop_money_bag_01");
			numberspawn = 5;
			speed = 10;
			player = PLAYER::PLAYER_ID();
			hasBeenInitiated = true;
		}
		void init(char *propp, Vector3 locationn, int pl = -1) {
			player = pl;
			location.x = locationn.x;
			location.y = locationn.y;
			location.z = locationn.z;
			radius = 2;
			for (int i = 0; i < 100; i++)
				prop[i] = 0;
			strncpy(prop,propp,100);
			numberspawn = 5;
			speed = 10;
			hasBeenInitiated = true;
		}
		void setLocation(float x, float y, float z) {
			location.x = x;
			location.y = y;
			location.z = z;
		}
		void setPlayer(int p) {
			player = p;
		}
		void removePlayer() {
			player = -1;
		}
		void spawnOne() {
			if (hasBeenInitiated) {
			Vector3 loc = {location.x,location.y,location.z};
			if (player != -1) {
				loc.x = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(player),true).x;
				loc.y = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(player),true).y;
				loc.z = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(player),true).z;
				location.x = loc.x;
				location.y = loc.y;
				location.z = loc.z;
			}
			loc.x+=GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(-1*radius,radius);
			loc.y+=GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(-1*radius,radius);
			loc.z+=1;
			OBJ::make_ambient_object(prop,loc,false);
			}
		}
		void generate() {
			counter++;
			if (counter >= speed) {
				counter = 0;
				for	(int i = 0; i < numberspawn; i++) {
					spawnOne();
				}
			}
		}
	};
	Money moneyGens[10];
	int currentGenerator = 0;
	void doAllMoneyGens() {
		for (int i = 0; i < 10; i++)
			if (moneyGens[i].enabled)
				moneyGens[i].generate();
		
	}
}
#endif
#pragma endregion
#pragma region structures
namespace structures {
	int bargeobj = 0;
	char* bargeprop = "prop_lev_des_barge_02";
	Vector3 oloc = {0,0,0};
	Vector3 nloc = {oloc.x-2,oloc.y-2,oloc.z-2};
	float x = 0;
	float y = 0;
	Vector3 rot = {0,0,0};
#ifdef creationSpawner
	void nextBarge(int previousObject) {
		if (ENTITY::DOES_ENTITY_EXIST(previousObject))
			ENTITY::SET_ENTITY_ROTATION(previousObject,180,0,0,1,1);
		else
			print("Creating base... Only click once!");
		if (y < 150) {
			Vector3 xloc = {nloc.x+x,nloc.y+y,nloc.z};
			OBJ::forceCreateObject(bargeprop,xloc,rot,true,nextBarge);
			y+=25;
		} else {
			y = 0;
			x+=11.5f;
			if (!(x < 72)) {
				x = 0;
				y = 0;
				print("Created secret base! Try having a party! Teleport people to you.");
				PlayerMods::teleportToCoords(0,0,7);
				return;
			} else  {
				Vector3 xloc = {nloc.x+x,nloc.y+y,nloc.z};
				OBJ::forceCreateObject(bargeprop,xloc,rot,true,nextBarge);
			}
		}
	}
#endif

	void forceTheObject(int entity) {
		forceEntity(entity,GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(-500,500),GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(-500,500),GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(0,1000),0,0,0);
	}
	void spawnBoxAroundPlayerTrollCallback(int entity) {
		ENTITY::SET_ENTITY_VISIBLE(entity,false);
		runlater::runlater(40,forceTheObject,entity);
	}
	void spawnBoxAroundPlayerTroll(int player) {
		Vector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(player),1);
		Vector3 xloc = {c.x,c.y,c.z-0.5f};
		OBJ::forceCreateObject(1765283457,xloc,rot,false, spawnBoxAroundPlayerTrollCallback);
	}

}
#pragma endregion
#pragma region textMessageModMenu
void removePlayerWantedLevel(int player);
namespace textMessageModMenu {

	void blipidhook() {
		//*(volatile unsigned int*)(0x157A618+0x00) = 0xXXXXXXXX;
		//*(volatile unsigned int*)(0x157A618+0x04) = 0xXXXXXXXX;
		//*(volatile unsigned int*)(0x157A618+0x08) = 0xXXXXXXXX;
		//*(volatile unsigned int*)(0x157A618+0x0C) = 0xXXXXXXXX;
		printf("This Script Name: %s\n",SCRIPT::GET_THIS_SCRIPT_NAME());
	}

	namespace globalData {
		enum PLAYERGLOBALMENU {
			PAUSEMENU = (1<<6),
			MINIMAP = (1<<15)
		};
		bool getPlayerMenuData(int player, unsigned int menu) {
			return Read_Global(2390201+223*player+72)&menu;
		}
		bool isPlayerDoingAnimation(int player) {
			Read_Global(2390201+223*player+46)&(1<<0);
		}
		bool doesPlayerHaveBullshark(int player) {
			Read_Global(2390201+223*player+180)&(1<<2);
		}
		bool isPlayerShooting(int player) {
			Read_Global(2390201+223*player+39)&(1<<0);
		}
		//1581767 + (player * 306)
		//2390201 + 223 * player
		//
		//kick player (doexsn't work)
		//1581767 + (player * 306) + 50 = 0x11111111
		//
		//id sync to player
		//unk_0x4D15FDB1(Global_2390201[player_id() <223>].imm_48, player_id(), 1);
	};

	/*


	//kick player from freemode.c
	void func_1530(var uParam0, var uParam1, var uParam2)
{
	int iVar0;
	int iVar1;
	float fVar2;
	bool bVar3;
	int iVar4;
	
	if (network_is_host())
	{
		iVar0 = network_get_num_connected_players();
		iVar1 = uParam0;
		if (*uParam1 != func_6663() && func_5666(*uParam1, 0, 0))
		{
			if (Global_1587565[*uParam1 <58>][iVar1] == 1)
			{
				if (Global_2390201[iVar1 <223>].imm_221)
				{
					Global_1587565[*uParam1 <58>][iVar1] = 0;
				}
				else
				{
					*uParam2++;
				}
			}
		}
		*uParam1++;
		if (*uParam1 >= 18)
		{
			Global_1315372 = iVar0 - 1;
			fVar2 = to_float(Global_1315372) * Global_262145.imm_6;
			Global_1315372 = floor(fVar2);
			bVar3 = true;
			if (bVar3)
			{
				if (Global_1315372 < 2)
				{
					Global_1315372 = 2;
				}
			}
			if ((*uParam2 >= Global_1315372 && *uParam2 > 0) && Global_1315372 > 0)
			{
				if (Global_1588610[iVar1] == 0)
				{
					Global_1588610[iVar1] = 1;
				}
				if (Global_1588610[iVar1] == 1)
				{
					if (network_is_session_started() && func_1531(iVar1))
					{
						if (iVar1 != player_id())
						{
							iVar4 = 0;
							while (iVar4 <= 17)
							{
								Global_1587565[iVar4 <58>].imm_39[iVar1] = 1;
								iVar4++;
							}
						}
						network_session_kick_player(uParam0);
						Global_1588610[iVar1] = 0;
					}
				}
			}
		}
	}
}
	*/

	/*
	x PED::IS_PED_RUNNING
	square PED::IS_PED_JUMPING
	triangle PED::IS_PED_GETTING_INTO_A_VEHICLE probably not a good one to use
	circle IS_PED_RELOADING
	r2 IS_PED_SHOOTING
	l2 IS_PLAYER_FREE_AIMING
	*/
	/*
	(char)ped_add+0x311971a2-0x31197000 == 1 = player is punching
	*/

	//(int)ped id + 0xE48: 0 when punching, 2 when not punching
	//(char)ped id + 0xE31: 0x40 when not aiming and 0x00 when aiming
	//open and close menu: check when you get in car
	namespace MENUS {
		enum MENUS {
			MAIN,
			PLAYERLIST,
			PLAYEROPTIONS,
			TELEPORTLOCATIONS,
			CARS
		};
	}
	int MENUSSIZES[] = {8,17,4,3,5};
	namespace buttons {
		const int x = 0x72C;//!= 0
		const int l2 = 0x1BF;//== 0
		const int r2 = 0x17A;//== 1
		const int square = 1;
		const int moving = 0x778;//!=0
		const int sweeper = 2;
		const int pistol = 3;
		const int baseball = 4;
		const int incar = 5;
		const int circle = 6;
	};

	struct pButtons {
		int x;
		int l2;
		int r2;
		int square;
		int moving;
		int sweeper;
		int pistol;
		int baseball;
		int incar;
		int circle;
		int getValue(int button) {
			switch(button) {
			case buttons::x:
				return x;
			case buttons::l2:
				return l2;
			case buttons::r2:
				return r2;
			case buttons::square:
				return square;
			case buttons::moving:
				return moving;
			case buttons::sweeper:
				return sweeper;
			case buttons::baseball:
				return baseball;
			case buttons::pistol:
				return pistol;
			case buttons::incar:
				return incar;
			case buttons::circle:
				return circle;
			}
			return 0;
		}
		void setValue(int button, int value) {
			switch(button) {
			case buttons::x:
				x = value;
				break;
			case buttons::l2:
				l2 = value;
				break;
			case buttons::r2:
				r2 = value;
				break;
			case buttons::square:
				square = value;
				break;
			case buttons::moving:
				moving = value;
				break;
			case buttons::sweeper:
				sweeper = value;
				break;
			case buttons::baseball:
				baseball = value;
				break;
			case buttons::pistol:
				pistol = value;
				break;
			case buttons::incar:
				incar = value;
				break;
			case buttons::circle:
				circle = value;
				break;
			}
		}
	};
	void sendInstructions(int player) {
		//char buf[64];
		//snprintf$(buf,sizeof(buf),"<font size='25'>MOD MENU\nPAUSE:open\nSHOOT:select\nDPADDOWN:scroll");
		snprintf$(global_temporary_buf,64,"~b~MOD MENU\nOpen:PAUSE\nSelect:SHOOT\nScroll:CHANGE PLAYER MOOD");
		//PlayerMods::msg("~r~FIRE EXTINGUISHER is invisible in the grenade slot!",player,true);
		PlayerMods::notify(global_temporary_buf,player,true);
	}

	int playerToDoSpecialInstructions;
	void specialInstructionsCallback(int interval) {
		printf("%i\n",interval);
		switch (interval) {
		case 0:
			PlayerMods::notify("~b~You have been given Paradise SPRX Mini Mod Menu!",playerToDoSpecialInstructions,true);
			break;
		case 1:
			PlayerMods::notify("Press pause and wait 5 seconds then unpause to open menu.",playerToDoSpecialInstructions,true);
			break;
		case 2:
			PlayerMods::notify("You will see the mod menu. It looks like a text message.",playerToDoSpecialInstructions,true);
			break;
		case 3:
			PlayerMods::notify("There are 4 options per page.",playerToDoSpecialInstructions,true);
			break;
		case 4:
			PlayerMods::notify("The selected option is marked with a '>' symbol.",playerToDoSpecialInstructions,true);
			break;
		case 5:
			PlayerMods::notify("Open interaction menu and change 'player mood' to scroll"/*"Press down 3 times to change the current option."*/,playerToDoSpecialInstructions,true);
			break;
		case 6:
			PlayerMods::notify("Shoot your pistol 1 time to select the current option.",playerToDoSpecialInstructions,true);
			break;
		default:
			printf("Returned!");
			return;
		}
		runlater::runlater(1000,specialInstructionsCallback,interval+1);
	}
	void doSpecialInstructions(int player) {
		playerToDoSpecialInstructions = player;
		specialInstructionsCallback(0);
		//runlater::runlater(500,specialInstructionsCallback,0);
	}

	//int maxOptions = 6;//amount of options. ex: 1 option would be 1.
	int interval = 0;
	struct player {
		bool enabled;
		bool opened;
		int selection;
		bool shootingBoolean;
		bool aimingBoolean;
		bool runningBoolean;
		int waitTime;
		int instructionsWaitTime;
		int carsSpawned;
		pButtons buttons;
		int selectedPlayer;
		int submenu;
		int scrollValue;
		void nextOption() {
			selection++;
			if (selection >= MENUSSIZES[submenu])
				selection = 0;
			if (submenu == MENUS::PLAYERLIST) {
				selectedPlayer++;
				while (GAMEPLAY::ARE_STRINGS_EQUAL(PLAYER::GET_PLAYER_NAME(selectedPlayer),"**invalid**") && selectedPlayer < 18)//0-15
					selectedPlayer++;
				//16... close menu
				if (selectedPlayer == 17)//17... set to 0
					selectedPlayer = 0;
			}
		}
		void previousOption() {
			selection--;
			if (selection < 0)
				selection = MENUSSIZES[submenu] - 1;
		}
		void waittimecounter(int thisPlayer) {
			instructionsWaitTime++;
			if (instructionsWaitTime > 2027) {
				sendInstructions(thisPlayer);
				instructionsWaitTime = 0;
			}
			waitTime--;
			if (waitTime < 0)
				waitTime = 0;
		}
	};
	player players[18];

	opd_s getEntityFromIndex_t = {0xA552E0,TOC};
	unsigned int (*getEntityFromIndex)(int entity) = (unsigned int(*)(int))&getEntityFromIndex_t;
	bool buttonPressed1(int player, int button){
		bool buttonPressed = 0;
		//square - open is pause menu
		//l2 - scroll down is show minimap
		//x - select is the animation flip off
		//circle - back is shoot bullets
		switch(button) {
		case buttons::x:
			buttonPressed = globalData::isPlayerDoingAnimation(player);
			break;
		case buttons::circle:
			buttonPressed = globalData::isPlayerShooting(player);
			break;
		case buttons::l2:
			buttonPressed = globalData::getPlayerMenuData(player,globalData::MINIMAP);
			break;
		case buttons::square:
			buttonPressed = globalData::getPlayerMenuData(player,globalData::PAUSEMENU);
			break;
		}

		/*unsigned int addr = getCNetGamePlayer(player);
		if (addr > 0x10000) {
			addr = *(volatile unsigned int*)(addr+0x78);
			if (addr > 0x10000) {
				addr = *(volatile unsigned int*)(addr+0x160);
				if (addr > 0x10000) {
					switch(button) {
					case buttons::x://this stays even when you hold x but not tapping x fast
						buttonPressed = *(float*)(addr+0x72c) == 1.0f;
						break;
					case buttons::circle://circle or r2
						buttonPressed = *(float*)(addr+0x72c) == -1.0f && *(char*)(addr+0x854+0x2) == 0x00;
						break;
					case buttons::square://only when jumping. Not currently used.
						buttonPressed = *(float*)(addr+0x72c) == -1.0f && *(char*)(addr+0x854+0x2) == 0x40;
						break;
					case buttons::l2://must be holding your fist
						buttonPressed = *(char*)(addr+0x270-9*4) == 0x04 && *(char*)(addr+0x270+11*0x4+0x3) == 0x4;
						break;
					}
				}
			}
		}

		return buttonPressed;*/

		/*
		unsigned int addr = getEntityFromIndex(PLAYER::GET_PLAYER_PED(player));
		//if (addr) {
			//addr = *(volatile unsigned int*)(addr+0xBD0);
			//if (addr) {
		int ped = PLAYER::GET_PLAYER_PED(player);
				switch(button) {
				case buttons::x:
					//buttonPressed = *(char*)(addr+buttons::x) != 0;//shit doesn't work
					buttonPressed = AI::IS_PED_SPRINTING(PLAYER::GET_PLAYER_PED(player));
					break;
				case buttons::l2:
					//buttonPressed = *(char*)(addr+buttons::l2) == 0;
					buttonPressed = PLAYER::IS_PLAYER_FREE_AIMING(player);//collides with shooting
					break;
				case buttons::r2:
					//buttonPressed = *(char*)(addr+buttons::r2) == 1;
					buttonPressed = PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED(player));
					break;
				case buttons::square:
					buttonPressed = PED::IS_PED_JUMPING(PLAYER::GET_PLAYER_PED(player));
					break;
				case buttons::moving:
					//buttonPressed = *(volatile int*)(addr+buttons::moving) != 0;
					break;
				case buttons::sweeper:
					buttonPressed = PED::IS_PED_SHOOTING(ped) && WEAPON::GET_SELECTED_PED_WEAPON(ped) == GAMEPLAY::GET_HASH_KEY("WEAPON_GUSENBERG");
					break;
				case buttons::baseball:
					//buttonPressed = PED::IS_PED_SHOOTING(ped) && WEAPON::GET_SELECTED_PED_WEAPON(ped) == GAMEPLAY::GET_HASH_KEY("WEAPON_FIREEXTINGUISHER");

					//(int)ped id + 0xE48: 0 when punching, 2 when not punching
					if (addr) {
						buttonPressed = *(char*)(addr+0xE48+0x3) == 0;
					}
					break;
				case buttons::pistol:
					//(char)ped id + 0xE31: 0x40 when not aiming and 0x00 when aiming
					//buttonPressed = PED::IS_PED_SHOOTING(ped) && WEAPON::GET_SELECTED_PED_WEAPON(ped) == GAMEPLAY::GET_HASH_KEY("WEAPON_PISTOL");
					if (addr) {
						buttonPressed = *(char*)(addr+0xE31) == 0                 && !(*(volatile int*)(addr+0xE48) == 0);
					}
					break;
				case buttons::incar:
					buttonPressed = PED::IS_PED_IN_ANY_VEHICLE(ped,1);
					break;
				}
			//}
		//}
				*/
		return buttonPressed;
	}

	void logButton(int player, int button) {
		bool pressed = buttonPressed1(player,button);
		if (!pressed) {
			players[player].buttons.setValue(button,0);
			return;
		}
		if (players[player].buttons.getValue(button) == 0) {
			players[player].buttons.setValue(button,1);
		} else {
			players[player].buttons.setValue(button,2);
		}
	}

	bool buttonPressed(int player, int button){
		return players[player].buttons.getValue(button) > 1;
	}

	bool buttonJustPressed(int player, int button) {
		/*bool pressed = buttonPressed(player,button);
		if (!pressed) {
			players[player].buttons.setValue(button,0);
			return false;
		}
		if (players[player].buttons.getValue(button) == 0) {
			players[player].buttons.setValue(button,1);
			return true;
		} else {
			return false;
		}*/
		return players[player].buttons.getValue(button) == 1;
	}

	int spawnVehicleCallbackPlayer = 0;
	void spawnVehicleCallback(int vehicle) {
		Vector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(spawnVehicleCallbackPlayer),false);
		ENTITY::SET_ENTITY_COORDS(vehicle,c.x,c.y,c.z,0,0,0,0);
		players[spawnVehicleCallbackPlayer].carsSpawned++;
	}
	//char temporaryBuf[30];
	char *getMenuOption(int player,int selection) {
		int submenu = players[player].submenu;
		switch(submenu) {
		case MENUS::MAIN:
			switch(selection) {
			case 0:
				return "Give Weapons";
			case 1:
				return "Teleport To Host";
			case 2:
				return "Spawn Money";
			case 3:
				return "Car List";
			case 4:
				return "Teleport Locations";
			case 5:
				return "Player List";
			case 6:
				return "Toggle Demi-God";
			case 7:
				return "Close Menu";
			default:
				//snprintf$(temporaryBuf,sizeof(temporaryBuf),"Invalid #%i",selection);
				//return temporaryBuf;
				return "";
			}
		case MENUS::PLAYERLIST:
			if (selection == 16)
				return "Back To Main Menu";
			if (selection > 16)
				return "";
			return PLAYER::GET_PLAYER_NAME(selection/*players[player].selectedPlayer*/);
			break;
		case MENUS::PLAYEROPTIONS:
			switch(selection) {
			case 0:
				return "Teleport To Player";
			case 1:
				return "Kill";
			case 2:
				return "Anon Kill";
			case 3:
				return "Back To Playerlist";
			default:
				//snprintf$(temporaryBuf,sizeof(temporaryBuf),"Invalid #%i",selection);
				//return temporaryBuf;
				return "";
			}
			break;
		case MENUS::TELEPORTLOCATIONS:
			switch(selection) {
			case 0:
				return "Teleport To Roof";
			case 1:
				return "Teleport To Mountain";
			case 2:
				return "Back To Main Menu";
			default:
				//snprintf$(temporaryBuf,sizeof(temporaryBuf),"Invalid #%i",selection);
				//return temporaryBuf;
				return "";
			}
			break;
		case MENUS::CARS:
			switch(selection) {
			case 0:
				return "Alien";
			case 1:
				return "Kuruma";
			case 2:
				return "Monster";
			case 3:
				return "Buzzard";
			case 4:
				return "Back";
			default:
				//snprintf$(temporaryBuf,sizeof(temporaryBuf),"Invalid #%i",selection);
				//return temporaryBuf;
				return "";
			}
			break;
		}
		return "Lol wtf happened";
	}

	void changeSubmenu(int player, int submenu) {
		players[player].selection = 0;
		players[player].submenu = submenu;
	}

	void runItem(int player, int selection) {
		int submenu = players[player].submenu;
		switch(submenu) {
		case MENUS::MAIN:
			switch(selection) {
			case 0:
				//PlayerMods::teleportToLoc(player,-73.92588, -818.455078, 326.174377);
				PlayerMods::giveWeapon(player,"WEAPON_STUNGUN");
				PlayerMods::giveWeapon(player,"WEAPON_HAMMER");
				PlayerMods::giveWeapon(player,"WEAPON_MOLOTOV");
				PlayerMods::giveWeapon(player,"WEAPON_BALL");
				PlayerMods::giveWeapon(player,"WEAPON_GUSENBERG");
				PlayerMods::giveWeapon(player,"WEAPON_MINIGUN");
				PlayerMods::notify("~g~Given weapons with infinite ammo!",player,true);
				break;
			case 1:
				PlayerMods::teleportToMe(player);
				break;
			case 2:
				//lobbyModMenu::dropMoneyBag(player);
				//lobbyModMenu::dropMoneyBag(player);
				//lobbyModMenu::dropMoneyBag(player);
				PlayerMods::toggleMoneyDropPlayer(player);
				break;
			case 3:
				changeSubmenu(player,MENUS::CARS);
				return;
				break;
			//case 4:
				//players[player].opened = false;
				//PlayerMods::msg("~r~Menu Closed!",player,true);
				//break;
			case 4:
				changeSubmenu(player,MENUS::TELEPORTLOCATIONS);
				return;
				break;
			case 5:
				changeSubmenu(player,MENUS::PLAYERLIST);
				players[player].selection = players[player].selectedPlayer;
				return;
				break;
			case 6:
				if(PlayerMods::togglePlayerGodmode(player)) {
					//godmode now enabled
					PlayerMods::notify("Demi-Godmode: ~g~Enabled",player);
				} else {
					//godmode disabled
					PlayerMods::notify("Demi-Godmode: ~r~Disabled",player);
				}
				break;
			case 7:
				players[player].opened = false;
				players[player].waitTime = 50;
				PlayerMods::notify("<font size='25'>Menu Closed\nPress PAUSE to open back up",player,true);
				break;
			default:
				PlayerMods::notify("Unknown Error",player,true);
				break;
			}
			break;
		case MENUS::PLAYERLIST:
			if (players[player].selectedPlayer<16) {
				changeSubmenu(player,MENUS::PLAYEROPTIONS);
				return;
			}
			else {
				changeSubmenu(player,MENUS::MAIN);
				return;
			}
			break;
		case MENUS::PLAYEROPTIONS:
			switch(selection) {
			case 0:
				static Vector3 uuix = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(players[player].selectedPlayer),1);
				PlayerMods::teleportToLoc(player,uuix.x,uuix.y,uuix.z);
				break;
			case 1:
				PlayerMods::playerExplodePlayerSilent(player,players[player].selectedPlayer);
				break;
			case 2:
				PlayerMods::explodePlayer(players[player].selectedPlayer);
				break;
			case 3:
				changeSubmenu(player,MENUS::PLAYERLIST);
				players[player].selection = players[player].selectedPlayer;
				return;
				break;
			}
			break;
		case MENUS::TELEPORTLOCATIONS:
			switch(selection) {
			case 0:
				PlayerMods::teleportToLoc(player,-73.92588, -818.455078, 326.174377);
				break;
			case 1:
				PlayerMods::teleportToLoc(player,496.75f, 5591.17f, 795.03f);
				break;
			case 2:
				changeSubmenu(player,MENUS::MAIN);
				return;
				break;
			}
			break;
		case MENUS::CARS:
			switch(selection) {
			case 0:
				if (players[player].carsSpawned < 10) {
					spawnVehicleCallbackPlayer = player;
					VehicleMods::spawnVehicle("dune2",spawnVehicleCallback);
				} else {
					PlayerMods::notify("~r~Max Cars Spawned!",player,true);
				}
				break;
			case 1:
				if (players[player].carsSpawned < 10) {
					spawnVehicleCallbackPlayer = player;
					VehicleMods::spawnVehicle("kuruma2",spawnVehicleCallback);
				} else {
					PlayerMods::notify("~r~Max Cars Spawned!",player,true);
				}
				break;
			case 2:
				if (players[player].carsSpawned < 10) {
					spawnVehicleCallbackPlayer = player;
					VehicleMods::spawnVehicle("monster",spawnVehicleCallback);
				} else {
					PlayerMods::notify("~r~Max Cars Spawned!",player,true);
				}
				break;
			case 3:
				if (players[player].carsSpawned < 10) {
					spawnVehicleCallbackPlayer = player;
					VehicleMods::spawnVehicle("buzzard",spawnVehicleCallback);
				} else {
					PlayerMods::notify("~r~Max Cars Spawned!",player,true);
				}
				break;
			case 4:
				changeSubmenu(player,MENUS::MAIN);
				return;
				break;
			default:
				
				break;
			}
			break;
		}
	}

	void togglePlayersMenu(int player) {
		players[player].enabled = !players[player].enabled;
		if (players[player].enabled) {
			//players[player].opened = true;
			sendInstructions(player);
			PlayerMods::removeGuns(player);
			//PlayerMods::giveWeapon(player,"WEAPON_GUSENBERG");
			PlayerMods::giveWeapon(player,"WEAPON_PISTOL");
			//WEAPON::SET_CURRENT_PED_WEAPON(PLAYER::GET_PLAYER_PED(player),GAMEPLAY::GET_HASH_KEY("WEAPON_PISTOL"),true);
			//PlayerMods::giveWeapon(player,"WEAPON_FIREEXTINGUISHER");
			players[player].carsSpawned = 0;
			players[player].waitTime = 200;//250
			players[player].scrollValue = PlayerMods::getPlayerMoodFromScroller(player);//set current mood
		} else {
			PlayerMods::giveAllWeaponsToPlayer(player);
			PlayerMods::notify("~r~Menu Taken Away! You have been given all weapons.",player,true);
		}
	}

	bool isPlayersMenuEnabled(int player) {
		return players[player].enabled;
	}

	bool isPlayerSendingPedData(int player) {
		return isPlayerPedDataBeingUpdated(getEntityFromIndex(PLAYER::GET_PLAYER_PED(player)));
	}

	void loop() {//was size 0x11c8 4552 4.552kb   now 0x520 1.312kb
		interval++;
		for (int i = 0; i < 18; i++) {
			if (players[i].enabled) {
				//strcpy((char*)1091842768/*0x411432D0*/,"~g~Paradise Mod Menu");
				//strcpy((char*)1091842840/*0x41143318*/,"~g~Paradise Mod Menu");
				if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i)) {
					//if (    isPlayerSendingPedData(i)    ) {
						//logButton(i,buttons::baseball);
						//logButton(i,buttons::pistol);

						//square - open is pause menu
						//l2 - scroll down is show minimap
						//x - scroll up is the animation flip off
						//circle - select shoot bullets
						logButton(i,buttons::x);
						logButton(i,buttons::l2);
						logButton(i,buttons::circle);
						//int previousMenuValue = players[i].buttons.getValue(buttons::square);//previous value it was opened
						logButton(i,buttons::square);
						//int currentMenuValue = players[i].buttons.getValue(buttons::square);//previous value it was opened
						//bool openNow = currentMenuValue = 0 && previousMenuValue > 0;
						players[i].waittimecounter(i);
						if (buttonJustPressed(i,buttons::square)) {
							players[i].opened = true;
							PlayerMods::playSoundOnPlayer(i,"loser","HUD_AWARDS");
						}
						if (players[i].opened) {
								bool update = false;
								if (buttonJustPressed(i,buttons::circle)) {
									//char buf[64];
									snprintf$(global_temporary_buf,64,"~g~%s Selected!",getMenuOption(i,players[i].selection));
									runItem(i,players[i].selection);
									PlayerMods::notify(global_temporary_buf,i,true);
									PlayerMods::playSoundOnPlayer(i,"Menu_Accept","Phone_SoundSet_Default");
									//OTHER_TEXT HUD_AWARDS is quiet but maybe too quiet
									//update = true;
								} 
								/*else if (buttonJustPressed(i,buttons::l2)) {
									players[i].nextOption();
									PlayerMods::playSoundOnPlayer(i,"Menu_Accept","Phone_SoundSet_Michael");
									update = true;
								}
								else if (buttonJustPressed(i,buttons::x)) {
									players[i].previousOption();
									PlayerMods::playSoundOnPlayer(i,"Menu_Accept","Phone_SoundSet_Michael");
									update = true;
								}*/
								int scrollValue = PlayerMods::getPlayerMoodFromScroller(i);//min is 0, max is 7
								if (scrollValue != players[i].scrollValue) {
									int dif = scrollValue-players[i].scrollValue;
									int a = abs(dif);
									int normal = dif/a;
									bool doScroll = false;
									if (a == 1 || a == 2 || a == 3 || a == 4) {//small changes but not too much
										doScroll = true;
									} else {
										//too high of changes, do the reverse
										doScroll = true;
										normal = normal * -1;
									}
									if (doScroll) {
										if (normal == 1) {
											players[i].nextOption();
										}
										if (normal == -1) {
											players[i].previousOption();
										}
										PlayerMods::playSoundOnPlayer(i,"Menu_Accept","Phone_SoundSet_Michael");
										update = true;
									}
									players[i].scrollValue = scrollValue;
								}

								while (strstr(getMenuOption(i,players[i].selection),"**Invalid**")) {
									players[i].selection++;
								}
								if (players[i].submenu == MENUS::PLAYERLIST) {
									players[i].selectedPlayer = players[i].selection;
								}
								if (update || players[i].waitTime == 0) {
									//char buf[64];

									//updated version
									char *formats[4] = {"> %s\n%s\n%s\n%s","%s\n> %s\n%s\n%s","%s\n%s\n> %s\n%s","%s\n%s\n%s\n> %s"};
									int selection = players[i].selection;
									int mod = selection%4;//0 would give 0, 1 would give 1, 2 would give 2, 3 would give 3, 4 would give 0...
									char *format = formats[mod];
									int firstMenu = selection-mod;//0 would give 0-0, 1 would give 1-1, ... 6 would give 6-2, ... 9 would give 9-1
									snprintf$(global_temporary_buf,64,format,getMenuOption(i,firstMenu),getMenuOption(i,firstMenu+1),getMenuOption(i,firstMenu+2),getMenuOption(i,firstMenu+3));

									/*char *s1 = "~y~>%s\n~s~%s\n%s\n%s";
									char *s2 = "%s\n~y~>%s\n~s~%s\n%s";
									char *s3 = "%s\n%s\n~y~>%s\n~s~%s";
									char *s4 = "%s\n%s\n%s\n~y~>%s";*/

									/*
									char *s1 = "> %s\n%s\n%s\n%s";
									char *s2 = "%s\n> %s\n%s\n%s";
									char *s3 = "%s\n%s\n> %s\n%s";
									char *s4 = "%s\n%s\n%s\n> %s";
									if (players[i].selection == 0)
										snprintf$(buf,sizeof(buf),s1,getMenuOption(i,0),getMenuOption(i,1),getMenuOption(i,2),getMenuOption(i,3));//31 or 32 spaces left for a menu option    \nL2/AIM:scroll\nO/PUNCH:select
									else if (players[i].selection == 1)
										snprintf$(buf,sizeof(buf),s2,getMenuOption(i,0),getMenuOption(i,1),getMenuOption(i,2),getMenuOption(i,3));
									else if (players[i].selection == 2)
										snprintf$(buf,sizeof(buf),s3,getMenuOption(i,0),getMenuOption(i,1),getMenuOption(i,2),getMenuOption(i,3));
									else if (players[i].selection == 3)
										snprintf$(buf,sizeof(buf),s4,getMenuOption(i,0),getMenuOption(i,1),getMenuOption(i,2),getMenuOption(i,3));
										
									else if (players[i].selection == 4)
										snprintf$(buf,sizeof(buf),s1,getMenuOption(i,4),getMenuOption(i,5),getMenuOption(i,6),getMenuOption(i,7));//31 or 32 spaces left for a menu option    \nL2/AIM:scroll\nO/PUNCH:select
									else if (players[i].selection == 5)
										snprintf$(buf,sizeof(buf),s2,getMenuOption(i,4),getMenuOption(i,5),getMenuOption(i,6),getMenuOption(i,7));
									else if (players[i].selection == 6)
										snprintf$(buf,sizeof(buf),s3,getMenuOption(i,4),getMenuOption(i,5),getMenuOption(i,6),getMenuOption(i,7));
									else if (players[i].selection == 7)
										snprintf$(buf,sizeof(buf),s4,getMenuOption(i,4),getMenuOption(i,5),getMenuOption(i,6),getMenuOption(i,7));
										
									else if (players[i].selection == 8)
										snprintf$(buf,sizeof(buf),s1,getMenuOption(i,8),getMenuOption(i,9),getMenuOption(i,10),getMenuOption(i,11));//31 or 32 spaces left for a menu option    \nL2/AIM:scroll\nO/PUNCH:select
									else if (players[i].selection == 9)
										snprintf$(buf,sizeof(buf),s2,getMenuOption(i,8),getMenuOption(i,9),getMenuOption(i,10),getMenuOption(i,11));
									else if (players[i].selection == 10)
										snprintf$(buf,sizeof(buf),s3,getMenuOption(i,8),getMenuOption(i,9),getMenuOption(i,10),getMenuOption(i,11));
									else if (players[i].selection == 11)
										snprintf$(buf,sizeof(buf),s4,getMenuOption(i,8),getMenuOption(i,9),getMenuOption(i,10),getMenuOption(i,11));
										
									else if (players[i].selection == 12)
										snprintf$(buf,sizeof(buf),s1,getMenuOption(i,12),getMenuOption(i,13),getMenuOption(i,14),getMenuOption(i,15));//31 or 32 spaces left for a menu option    \nL2/AIM:scroll\nO/PUNCH:select
									else if (players[i].selection == 13)
										snprintf$(buf,sizeof(buf),s2,getMenuOption(i,12),getMenuOption(i,13),getMenuOption(i,14),getMenuOption(i,15));
									else if (players[i].selection == 14)
										snprintf$(buf,sizeof(buf),s3,getMenuOption(i,12),getMenuOption(i,13),getMenuOption(i,14),getMenuOption(i,15));
									else if (players[i].selection == 15)
										snprintf$(buf,sizeof(buf),s4,getMenuOption(i,12),getMenuOption(i,13),getMenuOption(i,14),getMenuOption(i,15));
	
									else if (players[i].selection == 16)
										snprintf$(buf,sizeof(buf),s1,getMenuOption(i,16),getMenuOption(i,17),getMenuOption(i,18),getMenuOption(i,19));//31 or 32 spaces left for a menu option    \nL2/AIM:scroll\nO/PUNCH:select
									else if (players[i].selection == 17)
										snprintf$(buf,sizeof(buf),s2,getMenuOption(i,16),getMenuOption(i,17),getMenuOption(i,18),getMenuOption(i,19));
									else if (players[i].selection == 18)
										snprintf$(buf,sizeof(buf),s3,getMenuOption(i,16),getMenuOption(i,17),getMenuOption(i,18),getMenuOption(i,19));
									else if (players[i].selection == 19)
										snprintf$(buf,sizeof(buf),s4,getMenuOption(i,16),getMenuOption(i,17),getMenuOption(i,18),getMenuOption(i,19));
									//PlayerMods::msg("Paradise Mini Menu\nPUNCH: open\nO: select\nL2/AIM: scroll",i,true);
									*/
									PlayerMods::notify(global_temporary_buf,i,true);
									players[i].waitTime = 50;
								}
						}
					/*} else {
						players[i].waittimecounter();
						if (players[i].waitTime == 0) {
							PlayerMods::msg("~r~<font size='25'>Too far away from host! Get closer.",i,true);
						}
					}*/
				} else {
					players[i].enabled = false;
				}
			}

		}
		if (interval > 250) {
			interval = 0;
		}
	}

	

	int getPlayerByName(char *pname) {
		//char name[64];
		char* name = global_temporary_buf;
		memset(name,0,64);
		strncpy(name,pname,strlen(pname));
		toLower(name);
		int tpplayer = -1;
		for(int i = 0; i < 18; i++) {
			char nn[20];
			memset(nn,0,20);
			char *pp = PLAYER::GET_PLAYER_NAME(i);
			strncpy(nn,pp,strlen(pp));
			toLower(nn);
			printf("User sent: '%s', compared to '%s'\n",name,nn);
			if (strstr(nn,name)) {
				tpplayer = i;
				break;
			}
		}
		return tpplayer;
	}

	bool CMDMenuEnabled[20];
	void runCMD(int playerindex,char *message1) {
		//freeze somewhere between here
		char message[100];
        strcpy(message,message1);
		toLower(message);
		int len = strlen(message1);
        message[len] = ' ';
        message[len+1] = 0;
		char arg1[50];
		char arg2[50];
		char arg3[50];
		char arg4[50];
		char arg5[50];
		memset(arg1,0,50);
		memset(arg2,0,50);
		memset(arg3,0,50);
		memset(arg4,0,50);
		memset(arg5,0,50);
		char *a1=0,*a2=0,*a3=0,*a4=0,*a5=0;
		a1 = strstr(message," ");
		if (a1)
		a2 = strstr(a1+1," ");
		if (a2)
		a3 = strstr(a2+1," ");
		if (a3)
		a4 = strstr(a3+1," ");
		if (a4)
		a5 = strstr(a4+1," ");

		if (a1) {
			strncpy(arg1,message,a1-message);
			if (a2) {
				strncpy(arg2,a1+1,a2-a1-1);
				if (a3) {
					strncpy(arg3,a2+1,a3-a2-1);
					if (a4) {
						strncpy(arg4,a3+1,a4-a3-1);
						if (a5) {
							strncpy(arg5,a4+1,a5-a4-1);
						}
					}
				}
			}
		}

		if (strstr(arg1,"help")) {
			PlayerMods::msg("~b~-PARADISE CMD-\nINSTRUCTIONS:\nPARADISESPRX.NET/CMD",playerindex,true);
		}
		if (strstr(arg1,"veh")) {

			int model = GAMEPLAY::GET_HASH_KEY(arg2);
			if (STREAMING::IS_MODEL_VALID(model)) {
				spawnVehicleCallbackPlayer = playerindex;
				VehicleMods::spawnVehicle(arg2,spawnVehicleCallback);
			} else {
				PlayerMods::msg("~r~ERROR:\n~s~Invalid model",playerindex);
			}
		}
		if (strstr(arg1,"tp") && !strstr(arg1,"tpp")) {
			PlayerMods::teleportToMe(playerindex);
		}
		if (strstr(arg1,"tpp")) {
			int tpplayer = getPlayerByName(arg2);
			if (tpplayer != -1) {
				Vector3 uuix = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(tpplayer),1);
				PlayerMods::teleportToLoc(playerindex,uuix.x,uuix.y,uuix.z);
			} else {
				PlayerMods::msg("~r~ERROR:\n~s~Invalid player",playerindex);
			}
		}
		if (strstr(arg1,"gun") && !strstr(arg1,"guns")) {
			PlayerMods::giveWeapon(playerindex,arg2,-1);
		}
		if (strstr(arg1,"guns")) {
			PlayerMods::giveAllWeaponsToPlayer(playerindex);
		}
		if (strstr(arg1,"$")) {
			PlayerMods::toggleMoneyDropPlayer(playerindex);
		}
		if (strstr(arg1,"pimp")) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(playerindex),true)) {
				lobbyModMenu::maxOutCar(playerindex);
			} else {
				PlayerMods::msg("~r~ERROR:\n~s~Not in vehicle",playerindex);
			}
		}
		if (strstr(arg1,"exp")) {
			int tpplayer = getPlayerByName(arg2);
			if (tpplayer != -1) {
				PlayerMods::explodePlayer(tpplayer);
			} else {
				PlayerMods::msg("~r~ERROR:\n~s~Invalid player",playerindex);
			}
		}
		if (strstr(arg1,"kill")) {
			int tpplayer = getPlayerByName(arg2);
			if (tpplayer != -1) {
				PlayerMods::playerExplodePlayerSilent(playerindex,tpplayer);
			} else {
				PlayerMods::msg("~r~ERROR:\n~s~Invalid player",playerindex);
			}
		}
		if (strstr(arg1,"summon")) {
			int model = GAMEPLAY::GET_HASH_KEY(arg2);
			if (STREAMING::IS_MODEL_VALID(model)) {
				bodyguard::spawnNow(playerindex,arg2,bodyguard::types::Player,false);
			} else {
				PlayerMods::msg("~r~ERROR:\n~s~Invalid model",playerindex);
			}
		}
		if (strstr(arg1,"forge")) {
			int model = GAMEPLAY::GET_HASH_KEY(arg2);
			if (STREAMING::IS_MODEL_VALID(model)) {
				Vector3 tmp = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(playerindex),true);
				Vector3 ooo = {0,0,0};
				OBJ::forceCreateObject(arg2,tmp,ooo,false);
			} else {
				PlayerMods::msg("~r~ERROR:\n~s~Invalid model",playerindex);
			}
		}
		if (strstr(arg1,"god")) {//this worked
			if(PlayerMods::togglePlayerGodmode(playerindex)) {
				//godmode now enabled
				PlayerMods::msg("Demi-Godmode: ~g~Enabled",playerindex);
			} else {
				//godmode disabled
				PlayerMods::msg("Demi-Godmode: ~r~Disabled",playerindex);
			}
		}
		if (strstr(arg1,"aimbot")) {
			PlayerMods::togglePlayerAimbot(playerindex);
			if(PlayerMods::isAimbotEnabled(playerindex)) {
				//godmode now enabled
				PlayerMods::msg("Aimbot: ~g~Enabled",playerindex);
			} else {
				//godmode disabled
				PlayerMods::msg("Aimbot: ~r~Disabled",playerindex);
			}
		}
		if (strstr(arg1,"cop")) {
			removePlayerWantedLevel(playerindex);
			PlayerMods::msg("Wanted Level Down",playerindex);
		}
	}
	/*void runCMD(int playerindex,char *message) {
		char arg1[50];
		char arg2[50];
		char arg3[50];
		char arg4[50];
		char arg5[50];
		char *arg1 = strstr(message," ");
		spawnVehicleCallbackPlayer = playerindex;
		VehicleMods::spawnVehicle("dune2",spawnVehicleCallback);
	}*/
	void CMDMenuLoop() {
		playerTextMessage ptm = getUnseenTextMessagePlayer(); 
		if (ptm.playerindex != -1) {
			printf("Player: %s\nMessage: %s\n\n",ptm.name,ptm.message);
			if (textMessageModMenu::CMDMenuEnabled[ptm.playerindex]) {
				runCMD(ptm.playerindex,ptm.message);
			}
		}
	}

}
#pragma endregion
#pragma region allProps
/*
namespace allObjects {
	int currentProp = 0;
	bool enabled = false;
	int action = 0;
	int player = 0;
	int maxProps = 1000000;
	int timeout = 0;
	void doAction() {
		if (ENTITY::DOES_ENTITY_EXIST(currentProp)) {
		netreq::reqent(currentProp);
		currentProp++;//take this off later m8
		switch(action) {
		case 1://gotta change it to 0
			if (netreq::hasent(currentProp)) {
				OBJ::attachPropAlreadySpawned(player,0x796E,currentProp);
				timeout = 0;
				currentProp++;
			} else {
				timeout++;
			}
			break;
		}
		if (timeout > 50) {
			currentProp++;
			timeout = 0;
		}
		} else {
			currentProp++;
		}
	}
	void loop() {
		if (enabled) {
			printf("%i\n",currentProp);
			if (currentProp > maxProps) {
				print("Ended!");
				enabled = false;
				currentProp = 0;
				return;
			}
			while (!ENTITY::DOES_ENTITY_EXIST(currentProp) && currentProp < maxProps) {
				currentProp++;
				printf("%i\n",currentProp);
			}
			doAction();
		}
	}
	void start(int splayer) {
		player = splayer;
		enabled = true;
		currentProp = 0;
	}
	void end() {
		timeout = 0;
		currentProp = 0;
		enabled = false;
	}
}*/
#pragma endregion

#pragma region reversedStuff
opd_s serverSend_t = {0x1626C64,TOC};//completely broken idk how to fix
int(*serverSend)(unsigned int r3, unsigned int r4, unsigned int r5) = (int(*)(unsigned int,unsigned int,unsigned int))&serverSend_t;
struct serverSendType{
	unsigned int pointer1;
	unsigned int pointer2;
	char type[20];//completely unknown size. This is an educated guess
	short networkID;//MAYBE NOT FOR SURE
};
struct serverSendData{
	unsigned int unk1;
	unsigned int unk2;
	unsigned int unk3;
	unsigned int unk4;
	unsigned int unk5;
	unsigned int unk6;
	unsigned int unk7;
	char message[64];//probably 64
};
void sendMsg(unsigned int r3, unsigned int r4, unsigned int r5) {
	/*
	r3: pointer to structure
	aka the value at r3 (0x2259F54) is the address of the structure below
	structure {
	unsigned int pointer1;
	unsigned int pointer2;
	char type[20];//Almost 100% sure it is 20
	short networkID;//MAYBE NOT FOR SURE
	}
	type = "MsgTextMessage";
	pointer1 = 0x1C70690;//pointer to a structure
	pointer2 = 0x1C76428;//pointer to a function (response?)
	//0x3235

	r4: address of the structure
	0xD003F544
	structure {
	unsigned int unk1;0
	unsigned int unk2;4
	unsigned int unk3;8
	unsigned int unk4;c
	unsigned int unk5;10
	unsigned int unk6;14
	unsigned int unk7;18
	char message[64];//probably 64  0x1c
	}
	unk1 = 0xD003F690;//seems to be the same as the stack pointer aka r1
	unk2 = 0;
	unk3 = 0x1EB0;//same as r5
	unk4 = 0;
	unk5 = 0;
	unk6 = 0;
	unk7 = 1;
	message = "Your text message";

	r5:
	001EB0... same as unk3 in r4
	*/
}
opd_s getOpenEvent_t = {0x47E2D4,TOC};
unsigned int (*getOpenEvent)(unsigned int addr, unsigned int pHandle13Address, int pHandleSize, char *eventType) = (unsigned int(*)(unsigned int, unsigned int, int, char*))&getOpenEvent_t;

/*
r3 is value at off_1CF72D4    CONFIRMED
r4 = message+0x0 (terminating) pointer to  CONFIRMED
r5 is my data? aka sub_12F017C   R5 IS 0x41143310 CONFIRMED (sorta) or just 0x0022422A8 but idk if it is static
r6 is other player data CONFIRMED ADDRESS OF TEXT MESSAGE EVENT
*/
opd_s sub_13DF210_t = {0x13DF210,TOC};
unsigned int (*sub_13DF210)(unsigned int off_1CF72D4, char *message, unsigned int u_0x41143310, unsigned int text_message_event) = (unsigned int(*)(unsigned int, char*, unsigned int, unsigned int))&sub_13DF210_t;

opd_s sub_12F017C_t = {0x12F017C,TOC};
unsigned int (*sub_12F017C)(unsigned int r3) = (unsigned int(*)(unsigned int))&sub_12F017C_t;

unsigned int createEventOfType(unsigned int addr, int player, char *eventType) {//returns the address it is created at
	int playerAddr = 0x10070200+(player*0xD);
	NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, (networkHandleMgr*)playerAddr, 0xD);
	getOpenEvent(addr,playerAddr,0xD,eventType);
	return addr;
}
unsigned int eventAddr() {
	return 0x10070200+(20*0xD);
}
unsigned int createTextMessageEvent(int player) {
	unsigned int addr = 0x10070200+(20*0xD);
	return createEventOfType(addr,player,"NETWORK_SEND_TEXT_MESSAGE");
}

void sendJobshareCash(int player, int amount) {
	unsigned int evt = createEventOfType(eventAddr(),player,"NETWORK_GIVE_PLAYER_JOBSHARE_CASH");
}

void testCreateTextMessageEvent(int player) {
	unsigned int textMessageEvent = createTextMessageEvent(player);
	unsigned int r5 = sub_12F017C(*(volatile unsigned int*)(0x1CF72D4));//does some stuff?
	printf("\nEvent Address: %i\nR5 Address: %i\n",createTextMessageEvent(player),r5);
	sub_13DF210(*(volatile unsigned int*)(0x1CF72D4),"Hello There\0",r5/*0x22422A8*/,textMessageEvent);
}

/*

//this actually sends the text message that is stored in the unk_2259F54
seg001:00000000013E26E4                 lis       r3, unk_2259F54@ha
seg001:00000000013E26E8                 addic     r3, r3, unk_2259F54@l
seg001:00000000013E26EC                 bl        sub_17746A4

opd_s sub_17746A4_t = {0x17746A4,TOC};
unsigned int (*sub_17746A4)(unsigned int r3) = (unsigned int(*)(unsigned int))&sub_17746A4_t;
void forceExecuteTextMessages() {
	sub_17746A4(0x2259F54);
}



sub_D04078(unk_2259170,1,"MsgKickPlayer",dword_1FFE474,1);
sub_D03248();

*/
#pragma endregion
char *ItoSH(int num);
void teleportPlayerCallback(int r3, int senderData, int recieverData, int r6, int r7, int r8, int r9) {
	//printf("r3: %s, senderData: %s, recieverData: %s, r6: %s, r7: %s, r8: %s, r9: %s\n",ItoSH(r3),ItoSH(senderData),ItoSH(recieverData),ItoSH(r6),ItoSH(r7),ItoSH(r8),ItoSH(r9));
	printf("\n\n\n\n\nr3: %X, senderData: %X, recieverData: %X, r6: %X, r7: %X, r8: %X, r9: %X\n",r3,senderData,recieverData,r6,r7,r8,r9);
	printf("More data: *(volatile int*)(r3+0xC): %X, *(char*)(r3+0x10): %X, *(char*)(r3+0x18): %X, *(char*)(r3+0x8): %X\n",*(volatile int*)(r3+0xC),*(char*)(r3+0x10),*(char*)(r3+0x18),*(char*)(r3+0x8));
	//notes on r3:
	//*(volatile int*)(r3+0xC) is used
	/*

	r3 = unknownvalue  (aka r3);
	r4 = *(volatile int*)(r3+0xC);

	if (*(char*)(r3+0x18) == 0)
		r5 = *(char*)(r3+0x10);
	else
		r5 = *(char*)(r3+0x8);
	if (r4 > r5)
		return 0;
	r5 = r3;
	*(volatile int*)(r5+0xC) = r4;
	return 1;

	*/
	opd_s getEntityFromIndex_t = {0xA552E0,TOC};
	unsigned int (*getEntityFromIndex)(int entity) = (unsigned int(*)(int))&getEntityFromIndex_t;
	char buf[100];
	char *name = (char*)(*(volatile int*)(senderData+0x78)+0x10);
	//int player = textMessageModMenu::getPlayerByName((char*)(*(volatile int*)(senderData+0x78)+0x10));//this is their real name
	int player = *(volatile int*)(*(volatile int*)(senderData+0x8)+0x8);
	snprintf$(buf,sizeof(buf),"%s PedAddress: %X, NetID: %X\n",name,getEntityFromIndex(PLAYER::GET_PLAYER_PED(player)),NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(PLAYER::GET_PLAYER_PED(player)));
	printf(buf);
	if (player != -1) {
		playerModderData[player]+=1;
	}
	//__asm__("lwz %r3, 0(0)");
	//sys_interrupt_thread_eoi();
	//system_call_0(88);
}


namespace graphicsMods {
	//BEDEB4 createHashData makes these
	void setFogModifier(int value) {
		*(char*)(0x1E03EF0+0x3) = value;//0x22 is normal, 0x5 is trippy af, 0x9 is dope
	}
	void setFogParam(int value) {
		*(char*)(0x1E03EEC+0x3) = value;
	}
	void setMpVehicleDensity(int value) {
		*(char*)(0x1CD2D8C+0x3) = value;//0 means none, 0x14 default
		//0x1CD2D88 is singleplayer
	}
	void enableShadows(bool enable) {
		//1 by default, 0 for off
		*(volatile unsigned int*)(0x22028C0+0x500) = enable;//122C228                 lis       r4, aShadowrender@ha # "ShadowRender"
		               //0x22028C0+0x4E0 is gWaterHeight
	}
	void setMSAA(int value) {
		*(volatile unsigned int*)0x1F86F58 = value;//default is 0
	}
#define LOWPOLYCARSPED (0x12382BC)
	void setLowPolyCars(bool yes) {
		if (yes) {
			*(volatile unsigned int*)LOWPOLYCARSPED = 0x60000000;//this sets it for pedesriands
			*(volatile unsigned int*)0x13AE8A8 = 0x60000000;//sets for other players
			*(unsigned short*)(0x13AE8AC+0x2) = 0;//sets for other player part 2
		} else {
			*(volatile unsigned int*)LOWPOLYCARSPED = 0xC03E0A20;
			*(volatile unsigned int*)0x13AE8A8 = 0x41810228;
			*(unsigned short*)(0x13AE8AC+0x2) = 0x40A0;
		}
	}

	enum renderBits {
		//default is 21
		bit_renderMapUltra = (1<<0),
		bit_renderMapHigh = (1<<1),//like med but with a bit more details
		bit_renderMapMed = (1<<2),
		bit_renderMapLow = (1<<3),
		bit_renderMapLowNoGround = (1<<4),//like low but no ground so less detail overall
		bit_renderEntities = (1<<5),
		bit_renderEntitiesOnlyLights = (1<<6)//only rendered lights?
		//everything more is like the only lights one
		//28 would be low with entities
		//21 would be ultra with entities
	};
#define MAPRESS_GLOBAL (addrstruct().renderResulutionParams^dataDecryptor()) //(0x1DE12C0)
	bool renderEntitiesBool = true;
	void setCustomMapResParam(unsigned int param) {
		*(volatile unsigned int*)(MAPRESS_GLOBAL+0x44) = param;
	}
	void setCustomMapRes(bool yes) {
		*(char*)(MAPRESS_GLOBAL+0x48) = yes;
		//*(volatile unsigned int*)(MAPRESS_GLOBAL+0x44) = yes?bit_renderMapLow|bit_renderEntities:bit_renderMapUltra|bit_renderEntities;//mode type, overritten here 0x377514
		*(volatile unsigned int*)0x377514 = 0x60000000;//make it not set back to 21
		if (*(volatile unsigned int*)(MAPRESS_GLOBAL+0x44) == 0) {
			//set to default
			setCustomMapResParam(bit_renderMapUltra|bit_renderEntities);
		}
	}

	void toggleResBit(unsigned int bit, bool value) {
		unsigned int cur = *(volatile unsigned int*)(MAPRESS_GLOBAL+0x44);
		if (value) {
			cur = cur | bit;
		} else {
			cur = ~bit & cur;
		}
		setCustomMapResParam(cur);
	}

	void setLowRes() {
		setLowPolyCars(true);
		enableShadows(false);
		setCustomMapRes(true);
		setCustomMapResParam(bit_renderMapLow);
		toggleResBit(bit_renderEntities,renderEntitiesBool);
	}
	void setMediumRes() {
		setLowPolyCars(true);
		enableShadows(false);
		setCustomMapRes(true);
		setCustomMapResParam(bit_renderMapMed);
		toggleResBit(bit_renderEntities,renderEntitiesBool);
	}
	void setHighRes() {
		setLowPolyCars(false);
		enableShadows(true);
		setCustomMapRes(false);//we can't simulate what the game does by overriting with custom so just set to off
		//setCustomMapResParam(bit_renderMapUltra|bit_renderMapHigh);
		//toggleResBit(bit_renderEntities,renderEntitiesBool);
	}
	
	/*
	docs
	vehicle max creation distance offscreen 0x1CD2DFC (float)
	vehicle cull range 0x1CD2E04 (float)  251 is ddefauly, setting it to 1 deletes all cars as they spawn lmao
	offscreen cull 0x1CD2E08
	*/
};
namespace specialAttach {
	/*
	create an invisible ped + object
	attach the object to the invisible ped
	create a scene and put the invisible ped in it
	attach scene to player
	bam, object attached to player and they cannot take it off
	The code below does NOT include this idea, will add it later
	*/
	int player;
	void attachObjectBypassCallback(int object) {
		ENTITY::SET_ENTITY_COLLISION(object,false,false);
		STREAMING::REQUEST_ANIM_DICT(PlayerMods::dict);
		if (STREAMING::HAS_ANIM_DICT_LOADED(PlayerMods::dict)) {
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(player), 1);
			int sceneID = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE(coords.x,coords.y,coords.z, 0, 0, 0, 2, 0, 1, 1.0f, 0.0f, 1.0f);
			NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(object, sceneID, PlayerMods::dict, PlayerMods::anim, 1000.0f, -1000.0f, 269, 0, 1000.0f);
			//NETWORK::NETWORK_ADD_ENTITY_TO_SYNCHRONISED_SCENE(object, sceneID, PlayerMods::dict, PlayerMods::anim, 1000.0f, -1000.0f, 0);
			NETWORK::NETWORK_ATTACH_SYNCHRONISED_SCENE_TO_ENTITY(sceneID,PLAYER::GET_PLAYER_PED(player),0);
			NETWORK::NETWORK_START_SYNCHRONISED_SCENE(sceneID);
		}
	}
	void attach(int playerid, char *prop) {
		STREAMING::REQUEST_ANIM_DICT(PlayerMods::dict);
		player = playerid;
		Vector3 zerorot = {0,0,0};
		OBJ::forceCreateObject(prop,ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(player),1),zerorot,false,attachObjectBypassCallback,false);
	}
};

namespace networkhax {
	//unk_0x30B51753 is something with heist but seems to call some network stuff

	void doNetworkThingy(int pedID) {
		unsigned int pedAddress = getEntityFromIndex(pedID);
		unsigned int r4 = *(volatile unsigned int*)(0x1DE3318);  //0xA00A9444??? YES IT DOESN'T CHANGE, VALUE ALWAYS A00A9444
		unsigned int r5;
		if (pedAddress < 0x10000)
			return;
		r5 = *(volatile unsigned int*)(pedAddress);
		if (pedAddress < 0x10000)
			return;
		r5 = *(volatile unsigned int*)(r5+0x8);
		if (pedAddress < 0x10000)
			return;
		r5 = *(volatile unsigned int*)(r5+0x0);
		printf("R3 (Ped Addr): 0x%X\nR4: 0x%X\nR5L (Function Address): 0x%X\n\n",pedAddress,r4,r5);
		/*
		R3 (Ped Addr): 0x31197000
		R4: 0xA00A9444
		R5L (Function Address): 0x16F16D8
		*/
	}
};


//namespace pools{
	//ScriptEntityPool creation is in function 0xA55138. You can see li r5, 0xFA in there too. 
/*
PoolType getAddressOfNetworkPool() {//used for grabbing a lot of stuff idk. Often used with sub_A56394 in CREATE_ functions
	opd_s _0x47DEC4_ = {0x47DEC4,TOC};
	unsigned int(*_0x47DEC4)() = (unsigned int(*)())&_0x47DEC4_;
	return *(PoolType*)(_0x47DEC4()+0x24);
}*/
//r3 of sub_A54D9C are the pool addresses
//sub_A54B34 is another pool function
//unsigned int poolAddresses[] = {0x1CC5790,0x1CF0634,0x1CEFE50,0x1C95CF8,0x1C8FF5C,0x1C962F0,0x1CE4F88,0x1C7E61C};


	enum PoolType {
		//0x380F2C is a function that accesses every pool I currently know of
		ScriptEntityPool = 0x1CC5790,//contains entities spawned by scripts (not all of them though idk y)  *(volatile int*)(*(volatile int*)*(volatile int*)0x1CC5790+0x8*0xFA+0x8)+0x10 is the start of another 0xfa pool   and *(volatile int*)(*(volatile int*)*(volatile int*)0x1CC5790+0x8*0xFA+0x8)+0x10+0xFA*8 is the end of the pool
		UnknownPool0 = 0x1CF0634,//only native linking it is unk_0x5ab26c2b... very small pool
		PedPoolMaybe = 0x1CEFE50,//maybe some ped stuff? has a lot of things involved. Used in GET_CLOSEST_PED   entry size is huge, 0x1290 = 4752
		InteriorPool = 0x1C95CF8,//used often in interior functions
		CamPool = 0x1C8FF5C,//used often in cam functions
		NetworkPool = 0x1C962F0,//pool used by network natives   *(volatile int*)*(volatile int*)0x1C962F0+0xf4*0
		IncidentPool = 0x1CE4F88,//used by incident natives
		UnknownPool1 = 0x1C7E61C,//stunt jump?
		UnknownPool2 = 0x1DE2C34,//not allocated
		UnknownPool3 = 0x1C95CFC,
		UnknownPool4 = 0x1CA253C,//probably train pool (CTrain objects contained in it)
		UnknownPool5 = 0x1C95C3C,//CTimeModelInfo?
		UnknownPool6 = 0x1C96250,
		UnknownPool7 = 0x1CE6804,//14CBaseModelInfo found in it
		EventPool = 0x1CC4A54,//used in allocateEvent
		BIG_ENTITY_POOL = 0x1CC37F0,//contains 1000 different things (size 0x3E8)
		CNetObjPool = 0x1CF7674,//idk exactly but it is used to grab the cnetobj, element size 0x450
		Pool_CGamePlayerBroadcastDataHandler_Remote = 0x1CF7318
	};


//pool structures for BIG_ENTITY_POOL = 0x1CC37F0, maybe the most useful pool
struct entityDataForThatPool {
	unsigned int entityAddress;//this is the same value you would get from getEntityFromIndex
};
struct attachedEntityDataForThatPool {
	unsigned int entityAddress;//this is the same value you would get from getEntityFromIndex
};
struct BIG_ENTITY_POOL_DATA {//size of 0x3E8
	char unk[0x10];//0x0
	Vector3 position;//0x10
	char unk1[0x4];//0x1c
	entityDataForThatPool *entityData;//0x20  //if this is 0, no entity
	char unk2[0x10];
	attachedEntityDataForThatPool *entityAttachedToDataStructure;//0x34
	char unk3[0x18];
	/*unsigned int getEntity() {
		if (entityData != 0){
			return entityData->entityAddress;
		}
		return 0;
	}*/
	CObj *getEntity() {
		if (entityData != 0) {
			return (CObj*)(entityData->entityAddress);
		}
		return 0;
	}
	unsigned int getEntityAttachedTo() {
		if (entityAttachedToDataStructure != 0){
			return entityAttachedToDataStructure->entityAddress;
		}
		return 0;
	}
};


//this is the pool structure for ScriptEntityPool = 0x1CC5790, basically just outdated code (use isIndexOccupied instead of isValid mainly)
struct poolEntity {
    unsigned int unknown;//equals 0xffffffff when entity was deleted
    unsigned int addr;
    bool isValid() {
        return !(unknown == 0xFFFFFFFF) && unknown > 0xFA;
    }
    unsigned int getAddress() {
        return addr;
    }//0x7D0 (idk why I wrote this value here lol)
};


struct entityPoolSingles {
	//the type being poolEntityy does not matter, it should actuallyy be a void * but for compattability with other old code I kept it the same
    poolEntity individuals[1];//1 because size don't matter, it's size of the  0xFA for the one pool
};
struct entityPool {
    entityPoolSingles *entities;//0x0  size of 0x7D0
    unsigned int indexFlags;//0x4 says which slots are in use
    unsigned int maxPoolSize;//0x8  ie 0xFA for ScriptEntityPool and 0x3E8 for BIG_ENTITY_POOL
    unsigned int entrySize;//0xc  ie 8 for ScriptEntityPool and 0x50 for BIG_ENTITY_POOL
    int poolSizeCurrent;//0x10   Baed on getNextOpenPoolSlot, I think this is the pointer to the lowest open slot
	int negativeOneIfFull;//0x14 based on getNextOpenPoolSlot, it seems to also store a -1 if it is full
	enum indexflags {
		//spaceNotBlank = (1<<1),
		notValid = (1<<7)//0x80 aka 1000 0000
		//81 means not valie
		//82 means deleted (used to be there)
	};
    poolEntity getEntity(int index) {//only used for the script entity pool, useless otherwise
        return entities->individuals[index];
    }
	unsigned int getDataPointerFromPool(unsigned int poolIndex) {
		unsigned int dataPointer = ((unsigned int)entities)+(poolIndex*entrySize);
		return dataPointer;
	}
	char getIndexData(unsigned int index) {
		return *(char*)(indexFlags+index);
	}
	bool isIndexOccupied(unsigned int index) {
		return !(bool)(getIndexData(index)&notValid);
	}
	//I don't think I ever completed this function, but it's not too useful anyways
	entityPoolSingles *getNextPool(entityPoolSingles *entities) {//currentPoolAddress would be entities
		unsigned int addr1 = (unsigned int)entities+maxPoolSize*entrySize+0x8;
		unsigned int addr2 = (*(volatile unsigned int*)addr1)+0x10;
		entityPoolSingles *newPool = (entityPoolSingles*)addr2;
		printf("Original pool: 0x%X, new Pool: 0x%X\n",entities,newPool);
		return newPool;
	}
	bool isPoolFull() {
		if (poolSizeCurrent == -1 || negativeOneIfFull == -1) {//0xFFFFFFFF
			return true;
		}
		return false;
	}
};
 
entityPool *getEntityPool(PoolType pool = ScriptEntityPool) {
    return (entityPool*)*(volatile int*)((unsigned int)pool);
}

//used in 0xA552E0 getEntityFromIndex
opd_s getAddressOfScriptIndexPoolItem_t = {0xA54D9C,TOC};
unsigned int (*getAddressOfScriptIndexPoolItem)(entityPool *pool, unsigned int index) = (unsigned int(*)(entityPool *, unsigned int index))&getAddressOfScriptIndexPoolItem_t;

unsigned int getEntityFromIndext2(int entityIndex) {
	//just reversed 0xA552E0 getEntityFromIndex, not anything special
	unsigned int addr = getAddressOfScriptIndexPoolItem(getEntityPool(ScriptEntityPool),entityIndex);
	if (addr == 0)
		return 0;
	return *(volatile unsigned int*)(addr+0x4);
}

void detachEntity(unsigned int entityAddress) {
	//patches the function so we can parse the entity address as an arg and not the script entity index
	unsigned int fix = *(volatile unsigned int*)(0x3B081C);
	*(volatile unsigned int*)(0x3B081C) = 0x60000000;
	ENTITY::DETACH_ENTITY(entityAddress,true,true);
	*(volatile unsigned int*)(0x3B081C) = fix;
}

void setEntityCoords(unsigned int entityAddress, float x, float y, float z, float rx, float ry, float rz) {
	//ENTITY::SET_ENTITY_COORDS(index,50000,0,0,0,0,0,true);
	unsigned int save = *(volatile unsigned int*)0x3B2E48;
	*(volatile unsigned int*)0x3B2E48 = 0x60000000;
	ENTITY::SET_ENTITY_COORDS(entityAddress,x,y,z,rx,ry,rz,true);
	*(volatile unsigned int*)0x3B2E48 = save;
}

void setEntityCollision(unsigned int entityAddress, bool collide, bool keepPhysics) {
	unsigned int save = *(volatile unsigned int*)0x3B2AE0;
	*(volatile unsigned int*)0x3B2AE0 = 0x60000000;
	ENTITY::SET_ENTITY_COLLISION(entityAddress,collide,keepPhysics);
	*(volatile unsigned int*)0x3B2AE0 = save;
}

void deleteEntity(unsigned int entityAddress) {
	//patches the function so we can parse the entity address as an arg and not the script entity index
	Entity ent = entityAddress;
	unsigned int fix = *(volatile unsigned int*)(0x3B0740);
	*(volatile unsigned int*)(0x3B0740) = 0x60000000;
	ENTITY::DELETE_ENTITY(&ent);//it wants a pointer to the value so it can store the new value in it afterwards... whatever
	*(volatile unsigned int*)(0x3B0740) = fix;
}

/*void detachEntity(unsigned int entityAddress) {
//THIS ONE IS NOT AS COMPLETE AS THE REAL ONE, SO JUST MAKE THE REAL ONCE SKIP TURNING THE ENTITY INFO INTO AN ADDRESS
//it's not fully reverse so it causes the game to freeze on some objects
	unsigned int addr,r5;
	r5 = *(volatile unsigned int*)entityAddress;
	r5 = *(volatile unsigned int*)(r5+0x1EC);
	addr = *(volatile unsigned int*)(r5);
	if (addr > 0x10000) {
		printf("Gonna detach!\n");
		opd_s detach_func_t = {addr,TOC};
		void (*detach_func)(unsigned int entityAddress) = (void(*)(unsigned int))&detach_func_t;
		detach_func(entityAddress);
	} else {
		printf("Error getting detach function...\n");
	}
}*/
/*
not used
void detachEntityViaPoolFunctions(unsigned int entity) {
	unsigned int entityAddr = getEntityFromIndext2(entity);
	printf("Entity addr: 0x%X\n",entityAddr);
	if (entityAddr != 0)
		detachEntity(entityAddr);
}*/
void nullFunc2(unsigned int, unsigned int){}
//               entity        entity that entity is attached to
//void (*saveFunc)(unsigned int, unsigned int);
void runOnAllPoolObjects(void(*callback)(unsigned int, unsigned int)) {
	entityPool *pool = getEntityPool(BIG_ENTITY_POOL);
	for (int i = 0; i < pool->maxPoolSize-1; i++) {
		if (pool->isIndexOccupied(i)) {
			BIG_ENTITY_POOL_DATA* data = (BIG_ENTITY_POOL_DATA*)pool->getDataPointerFromPool(i);
			unsigned int entityAddress = (unsigned int)data->getEntity();
			if (entityAddress > 0x10000) {
				unsigned int entityAttachedTo = data->getEntityAttachedTo();
				if (entityAttachedTo > 0x10000) {
					callback(entityAddress,entityAttachedTo);
				} else {
					callback(entityAddress,0);//not attached to anything
				}
			}
		}
	}
}

//callback has 1 arg and that is the address of the item in the pool
//returns the pointer to the pool item
//example:
/*
void callbackFunction(unsigned int address) {
	BIG_ENTITY_POOL_DATA* data = (BIG_ENTITY_POOL_DATA*)address;
	//do stuff with it
}
executeOnPool(BIG_ENTITY_POOL,callbackFunction);
*/
volatile void executeOnPool(PoolType poolAddr, void(*callback)(unsigned int)) {
	entityPool *pool = getEntityPool(poolAddr);
	for (int i = 0; i < pool->maxPoolSize-1; i++) {
		if (pool->isIndexOccupied(i)) {
			unsigned int ptr = pool->getDataPointerFromPool(i);
			callback(ptr);
		}
	}
}

void fuckUpSyncsCallback(unsigned int addr) {//*(volatile int*)*(volatile int*)0x1CF7318+s+0xF8*i
	CGamePlayerBroadcastDataHandler_Remote *a = (CGamePlayerBroadcastDataHandler_Remote *)addr;
	a->sizeOfSyncData = 0xFFFFFFF;
}

void fuckUpSyncs() {
	executeOnPool(Pool_CGamePlayerBroadcastDataHandler_Remote,fuckUpSyncsCallback);
}

ui64 playerBroadcastVariablesSendDetour(CGamePlayerBroadcastDataHandler_Remote *r3, CNetGamePlayer *r4, ui64 r5, ui64 r6, ui64 r7, ui64 r8) {
	//class data usually 0x192A148 CGamePlayerBroadcastDataHandler_Local but could also be CGameHostBroadcastDataHandler
	/*if ((unsigned int)(r3->classData) == 0x1929F30) {
		printf("Data is CGameHostBroadcastDataHandler\n");
	}*/
	//r3->pointerToDataSyncLocation = (void*)((unsigned int)r3->pointerToDataSyncLocation+0xF0);
	/*	printf("0x%X  ",(unsigned int)r3->classData);
		if (VALID_ADDR(r4))
			if (VALID_ADDR(r4->playerInfo))
				if(VALID_ADDR(r4->playerInfo->name))
					printf("%s",r4->playerInfo->name);
		printf("\n");*/
	

	ui64 retVal = call<ui64>(0x9FB3C8)(r3,r4,r5,r6,r7,r8);
	//r3->pointerToDataSyncLocation = (void*)((unsigned int)r3->pointerToDataSyncLocation-0xF0);
	return retVal;
}

/*void setupPlayerBroadcastVariablesSendDetour() {
	//playerBroadcastVariablesSend is the function at 0x9FB3C8, r3 through r8 args
	*(unsigned int*)(0x1C4F598+0x0) = *(unsigned int*)((unsigned int)playerBroadcastVariablesSendDetour+0x0);
	*(unsigned int*)(0x1C4F598+0x4) = *(unsigned int*)((unsigned int)playerBroadcastVariablesSendDetour+0x4);
}*/

void setCNetObjPlayerSpawner(CNetObj *obj, int playerToSetTo) {
	//0x14 & 0x18 & 0x1C seem to be not used...
	unsigned int addr = (unsigned int)obj;
	if (*(volatile unsigned int*)(obj+0x14) == 0) {
		*(volatile unsigned int*)(obj+0x14) = playerToSetTo+1;
	}
	/*if (*(volatile unsigned int*)(obj+0x18) == 0) {
		*(volatile unsigned int*)(obj+0x18) = playerToSetTo+1;
	}
	if (*(volatile unsigned int*)(obj+0x1C) == 0) {
		*(volatile unsigned int*)(obj+0x1C) = playerToSetTo+1;
	}*/
}
int getCNetObjPlayerSpawner(CNetObj *obj) {
	//0x14 & 0x18 & 0x1C seem to be not used...
	unsigned int addr = (unsigned int)obj;
	if (*(volatile unsigned int*)(obj+0x14) > 0 && *(volatile unsigned int*)(obj+0x14) < 32) {
		return *(volatile unsigned int*)(obj+0x14)-1;
	}
	/*if (*(volatile unsigned int*)(obj+0x18) > 0 && *(volatile unsigned int*)(obj+0x18) < 32) {
		return *(volatile unsigned int*)(obj+0x18)-1;
	}
	if (*(volatile unsigned int*)(obj+0x1C) > 0 && *(volatile unsigned int*)(obj+0x1C) < 32) {
		return *(volatile unsigned int*)(obj+0x1C)-1;
	}*/
	return -1;
}

namespace poolManipulations {

	bool doesEntityAddressExist(unsigned int address) {
		unsigned int backup = *(volatile unsigned int*)0x3AA038;
		*(volatile unsigned int*)0x3AA038 = 0x60000000;
		bool ret = ENTITY::DOES_ENTITY_EXIST(address);
		*(volatile unsigned int*)0x3AA038 = backup;
		return ret;
	}

	void requestControlOfEntityAddress(unsigned int address) {
		unsigned int backup = *(volatile unsigned int*)0x3EA030;
		*(volatile unsigned int*)0x3EA030 = 0x60000000;
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(address);
		*(volatile unsigned int*)0x3EA030 = backup;
	}

	bool hasControlOfEntityAddress(unsigned int address) {
		unsigned int backup = *(volatile unsigned int*)0x3EA190;
		*(volatile unsigned int*)0x3EA190 = 0x60000000;
		bool ret = NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(address);
		*(volatile unsigned int*)0x3EA190 = backup;
		return ret;
	}

	void setEntityAddressAsMissionEntity(unsigned int address, int arg1, int arg2) {
		unsigned int backup = *(volatile unsigned int*)0x3B2368;
		*(volatile unsigned int*)0x3B2368 = 0x60000000;
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(address,arg1,arg2);
		*(volatile unsigned int*)0x3B2368 = backup;
	}
	
	/*void deleteAllEntitiesCallback(unsigned int entityAddress, unsigned int entityAttachedTo) {
	//this just crashes the game, no need for it
		int scriptIndexEntity = entityToIndex(entityAddress);
		int scriptIndexEntityAttachedTo = entityToIndex(entityAttachedTo);
		if (scriptIndexEntity != 0)
			netreq::reqent(scriptIndexEntity);
		if (scriptIndexEntityAttachedTo != 0)
			netreq::reqent(scriptIndexEntityAttachedTo);

		//this just flat out deletes all entities
		detachEntity(entityAddress);
		deleteEntity(entityAddress);
	}*/
	int entityToWorkFromIndex = 0;//entity index of things to remove from
	/*void detachAllEntitiesCallback(unsigned int entityAddress, unsigned int entityAttachedTo) {
		int scriptIndexEntity = entityToIndex(entityAddress);//get script index of entity, if it exists
		int scriptIndexEntityAttachedTo = entityToIndex(entityAttachedTo);//get script index of attached entity, if exists
		if (entityToWorkFromIndex != scriptIndexEntityAttachedTo)//make sure we are detaching from the proper person
			return;
		if (scriptIndexEntity == WEAPON::_0x5D73CD20(entityToWorkFromIndex))//make sure we are not detaching their gun
			return;
		if (scriptIndexEntity != 0)//if it is a script entity, try to get control of it
			netreq::reqent(scriptIndexEntity);
		if (scriptIndexEntityAttachedTo != 0)//try to get control of the attached one? Not necessary but kept here cuz whatever
			netreq::reqent(scriptIndexEntityAttachedTo);

		detachEntity(entityAddress);//detach entity
	}*/
	/*
	freezes game with some objects so don't bother using
	void deleteAllAttachedEntities(unsigned int entityAddress, unsigned int entityAttachedTo) {
		int scriptIndexEntity = entityToIndex(entityAddress);
		int scriptIndexEntityAttachedTo = entityToIndex(entityAttachedTo);
		if (entityToWorkFromIndex != scriptIndexEntityAttachedTo)//make sure we are detaching from the proper person
			return;
		if (scriptIndexEntity == WEAPON::_0x5D73CD20(entityToWorkFromIndex))//make sure we are not detaching their gun
			return;
		if (scriptIndexEntity != 0)
			netreq::reqent(scriptIndexEntity);
		if (scriptIndexEntityAttachedTo != 0)
			netreq::reqent(scriptIndexEntityAttachedTo);

		if (scriptIndexEntity != 0) {
			if (netreq::hasent(scriptIndexEntity)) {
				if (entityAttachedTo != 0) {
					detachEntity(entityAddress);
					deleteEntity(entityAddress);
				}
			}
		}
	}*/
	/*void deleteAllEntities() {
		runOnAllPoolObjects(deleteAllEntitiesCallback);
	}*/
	/*void deleteAllAttachedEntities(int entityToDeleteFromIndex) {
		entityToWorkFromIndex = entityToDeleteFromIndex;
		runOnAllPoolObjects(deleteAllAttachedEntities);
	}*/

	bool isAddressAnEntity(unsigned int address) {
		if (address > 0x10000) {
			char typeOfEntity = *(char*)(address+0x14);
			switch(typeOfEntity) {
			case 4://ped
				return true;
			case 3://vehicle
				return true;
			case 5://object
				return true;
			}
		}
		return false;
	}

	bool isAddressAnObject(unsigned int address) {
		if (address > 0x10000) {
			char typeOfEntity = *(char*)(address+0x14);
			switch(typeOfEntity) {
			case 5://object
				return true;
			}
		}
		return false;
	}
	bool isAddressAPed(unsigned int address) {
		if (address > 0x10000) {
			char typeOfEntity = *(char*)(address+0x14);
			switch(typeOfEntity) {
			case 4://ped
				return true;
			}
		}
		return false;
	}
	bool isAddressAVehicle(unsigned int address) {
		if (address > 0x10000) {
			char typeOfEntity = *(char*)(address+0x14);
			switch(typeOfEntity) {
			case 3://vehicle
				return true;
			}
		}
		return false;
	}

	void callbackFunctionForDrawLineToAllObject(unsigned int address) {
		Vector3 myCoords = PlayerMods::getPlayerLocation(PLAYER::PLAYER_ID());
		BIG_ENTITY_POOL_DATA* data = (BIG_ENTITY_POOL_DATA*)address;
		if (isAddressAnEntity((unsigned int)data->getEntity()))
			minecraft::drawLine(myCoords,data->position);
	}
	/*
	moved to math
	__attribute__((naked)) float fast_squareRoot(float num) {
		__asm("fsqrts %f1, %f1");
		__asm("blr");
	}
	void distance(Vector3 a, Vector3 b) {
		float x = a.x-b.x;
		float y = a.y-b.y;
		float z = a.z-b.z;
		x *= x;
		y *= y;
		z *= z;
		return fast_squareRoot(x+y+z);
	}*/
	float drawNameDistance = 30.0f;
	void callbackFunctionForDrawNameOnAllObject(unsigned int address) {
		Vector3 myCoords = PlayerMods::getPlayerLocation(PLAYER::PLAYER_ID());
		BIG_ENTITY_POOL_DATA* data = (BIG_ENTITY_POOL_DATA*)address;
		if (isAddressAnEntity((unsigned int)data->getEntity())) {
			//minecraft::drawLine(myCoords,data->position);
			if (math::distance(myCoords,data->position)/*GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(data->position.x,data->position.y,data->position.z,myCoords.x,myCoords.y,myCoords.z,true)*/ < drawNameDistance) {
				//float x=0,y=0;
				//GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(data->position.x,data->position.y,data->position.z,&x,&y);
				//UI::_GET_SCREEN_COORD_FROM_WORLD_COORD(data->position.x,data->position.y,data->position.z,&x,&y);
				GRAPHICS::SET_DRAW_ORIGIN(data->position.x,data->position.y,data->position.z,false);

				char buf[30];
				snprintf(buf,sizeof(buf),"~b~[~w~0x%X~b~]",data->getEntity()->modelInfo->modelHash);
				//printf("%s\n",buf);
				drawText(buf,0,0,0/*x,y*/,0.35f,0.35f,255,255,255,255,true,false);

				GRAPHICS::CLEAR_DRAW_ORIGIN();
			}
		}
	}
	bool drawLineBool = false;
	void drawLineToAllObjects() {
		executeOnPool(BIG_ENTITY_POOL,callbackFunctionForDrawLineToAllObject);
	}
	bool drawNameBool = false;
	void drawNameOnAllObjects() {
		executeOnPool(BIG_ENTITY_POOL,callbackFunctionForDrawNameOnAllObject);
	}
	
	void callbackDeleteAllEntities(unsigned int address) {
		BIG_ENTITY_POOL_DATA* data = (BIG_ENTITY_POOL_DATA*)address;
		//printf("Data location: 0x%X\n",address);
		CObj *entAddr = data->getEntity();
		if (!VALID_ADDR(entAddr))
			return;
		if (!VALID_ADDR(entAddr->cNetObj)) {
			//printf("Not networked! 0x%X\n",entAddr);
			return;
		}

		int index = entityToIndex(entAddr);

		netreq::reqent(index);
		//if (netreq::hasent(index)) {
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(index,0,1);
			ENTITY::DELETE_ENTITY(&index);
			//printf("deleted 0x%X\n",entAddr);
		//}
		
		//unsigned int attentAddr = data->getEntityAttachedTo();
		//if (entAddr < 0x10000)
			//return;


		/*unsigned int playerPedAddress = getEntityFromIndex(PLAYER::PLAYER_PED_ID());
		if (entAddr == playerPedAddress)
			return;
		unsigned int playerWeaponAddress = getEntityFromIndex(WEAPON::_0x5D73CD20(PLAYER::PLAYER_PED_ID()));
		if (entAddr == playerWeaponAddress)
			return;*/



		//WEAPON::_0x5D73CD20(
		//if (isAddressAnEntity(entAddr)) {
		//int index = entityToIndex(entAddr);
		//if (index == 0)
			//return;
		//printf("Called entity to index\n");
		//if (/*ENTITY::DOES_ENTITY_EXIST(index)*/doesEntityAddressExist(entAddr)) {
			/*if (isAddressAPed(entAddr)) {
				if (PED::IS_PED_A_PLAYER(index)) {
					printf("Ped is a player\n");
					return;
				}
			}
			if (isAddressAnObject(entAddr)) {
				for (int i = 0; i < 18; i++) {
					int pped = PLAYER::GET_PLAYER_PED(i);
					if (WEAPON::_0x5D73CD20(pped) == index) {
						printf("The entity is a weapon... %i\n",index);
						return;
					}
				}
			}*/
			//if (NETWORK::NETWORK_DOES_ENTITY_EXIST_WITH_NETWORK_ID(index)) {
				//printf("Network id exists\n");
				//netreq::reqent(index);
				//requestControlOfEntityAddress(entAddr);
				//if (hasControlOfEntityAddress(entAddr)/*netreq::hasent(index)*/) {
					//printf("Deleting entity %i\n",index);
					//ENTITY::SET_ENTITY_AS_MISSION_ENTITY(index,0,1);

					//setEntityAddressAsMissionEntity(entAddr,0,1);

					//detachEntity(entAddr);
					//setEntityCoords(entAddr,50000,0,0,0,0,0);
					//setEntityCollision(entAddr,false,false);

					//ENTITY::DELETE_ENTITY(&index);
					//deleteEntity(entAddr);
					//deleteEntity(entAddr);
				//}
			//}
		//}
		//}
		
		/*
		if (isAddressAVehicle(entAddr)) {
			int index = entityToIndex(entAddr);
			netreq::reqent(index);
			if (netreq::hasent(index)) {
				printf("Deleting vehicle entity %i\n",index);
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(index,0,1);
				ENTITY::DELETE_ENTITY(&index);
				//deleteEntity(entAddr);
			}
			return;
		}
		if (isAddressAPed(entAddr)) {
			int index = entityToIndex(entAddr);
			if (!PED::IS_PED_A_PLAYER(index)) {//make sure it's not a player
				netreq::reqent(index);
				if (netreq::hasent(index)) {
					printf("Deleting ped entity %i\n",index);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(index,0,1);
					ENTITY::DELETE_ENTITY(&index);
					//deleteEntity(entAddr);
				}
			}
			return;
		}
		if (isAddressAnObject(entAddr) && isAddressAnEntity(attentAddr)) {
			int index = entityToIndex(entAddr);
			netreq::reqent(index);
			if (netreq::hasent(index)) {
				printf("Deleting attached object %i\n",index);
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(index,0,1);
				ENTITY::DELETE_ENTITY(&index);
				//deleteEntity(entAddr);
			}
		}*/
	}
	void deleteAllEntities() {
		executeOnPool(BIG_ENTITY_POOL,callbackDeleteAllEntities);
	}


	struct detachEntitySave {
		int entityID;
		char owner;
		int time;
	};

	detachEntitySave savedEntities[50];
	int getFreeAttachedEntitySlot() {
		for (int i = 0; i < sizeof(savedEntities)/sizeof(detachEntitySave); i++) {
			if (savedEntities[i].entityID == 0)
				return i;
		}
		return -1;
	}

	int getSavedEntityTime(int entityID) {
		for (int i = 0; i < sizeof(savedEntities) / sizeof(detachEntitySave); i++) {
			if (savedEntities[i].entityID == entityID) {
				return savedEntities[i].time;
			}
		}
		return -1;
	}

	int getSavedEntityPlayer(int entityID) {
		for (int i = 0; i < sizeof(savedEntities)/sizeof(detachEntitySave); i++) {
			if (savedEntities[i].entityID == entityID) {
				savedEntities[i].entityID = 0;//set to be open
				savedEntities[i].time = 0;
				return savedEntities[i].owner;
			}
		}
		return -1;
	}

	bool hasEntityBeenSaved(int entityID) {
		for (int i = 0; i < sizeof(savedEntities)/sizeof(detachEntitySave); i++) {
			if (savedEntities[i].entityID == entityID)
				return true;
		}
		return false;
	}

	void addSavedEntity(int entityID, char owner) {
		for (int i = 0; i < sizeof(savedEntities) / sizeof(detachEntitySave); i++) {
			if (savedEntities[i].entityID == entityID) {
				savedEntities[i].time++;
			}
		}
		if (owner == -1)
			return;
		if (!hasEntityBeenSaved(entityID)) {
			int slot = getFreeAttachedEntitySlot();
			if (slot != -1) {
				savedEntities[slot].entityID = entityID;
				savedEntities[slot].owner = owner;
			}
		}
	}

	void callbackDeleteAllAttachedEntities(unsigned int address) {
		
		BIG_ENTITY_POOL_DATA* data = (BIG_ENTITY_POOL_DATA*)address;
		unsigned int entAddr = (unsigned int)data->getEntity();
		unsigned int attentAddr = data->getEntityAttachedTo();
		if (entAddr < 0x10000)
			return;
		if (attentAddr < 0x10000)
			return;
		//if (isAddressAnEntity(entAddr) && isAddressAnEntity(attentAddr)) {
		int index = entityToIndex(entAddr);
		int attindex = entityToIndex(attentAddr);
		if (ENTITY::DOES_ENTITY_EXIST(index) && ENTITY::DOES_ENTITY_EXIST(attindex)) {
			if (!ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(index,attindex))//they are not attached
				return;
			if (entityToWorkFromIndex != attindex)//not the correct entity to detach from
				return;
			if (index == WEAPON::_0x5D73CD20(entityToWorkFromIndex))//make sure we are not detaching their gun
				return;
			int playerid = -1;
			if (*(volatile int*)(entAddr+0x4C) == 0)//online entity does not exist, so yea... an example of when this happens is when reloading, and it is in ur hand
				return;
			playerid = *(char*)(*(volatile int*)(entAddr+0x4C)+0x25);//0x27 is whether 0x25 is me or not
			//*(volatile unsigned int*)0xA0C02C = 0x60000000;//also check out 0xA18984
			addSavedEntity(index,playerid);
			netreq::reqent(index);
			//printf("Trying to delete entity %i owner %i\n",index,playerid);
			bool bypassCheck = false;
			if (getSavedEntityTime(index) > 3) {
				//printf("Timeout on entity %i. Trying Removing locally\n",index);
				bypassCheck = true;
			}
			if (netreq::hasent(index) || bypassCheck) {
				//printf("Deleting entity %i\n",index);
				ENTITY::DETACH_ENTITY(index,true,true);
				/*CObj *cobj = getCObjFromIndex(index);
				if (VALID_ADDR(cobj))
					if (VALID_ADDR(cobj->cNetObj))
						playerid = getCNetObjPlayerSpawner(cobj->cNetObj);
				printf("detaching object. Playerid found: %i\n",playerid);*/
				//playerid = -1;
				playerid = getSavedEntityPlayer(index);
				if (playerid != PLAYER::PLAYER_ID() && playerid != -1) {
					//ENTITY::SET_ENTITY_VISIBLE(index,true);
					OBJ::attachPropAlreadySpawned(playerid,PlayerMods::bones::Head,index);
					//char textBuf[100];
					snprintf(global_temporary_buf,sizeof(global_temporary_buf),"%s attached objects to you!",PLAYER::GET_PLAYER_NAME(playerid));
					print2(global_temporary_buf,2000);

					if (bypassCheck == true) {
						//ENTITY::SET_ENTITY_COORDS(index, 5000, 0, 0, 0, 0, 0, true);
						ENTITY::SET_ENTITY_COLLISION(index, false, false);
						//ENTITY::SET_ENTITY_VISIBLE(index, false);//this is the only one that works... doesn't actually delete it. You can see by turning on and off invisibility it comes back.
						//ENTITY::SET_ENTITY_AS_MISSION_ENTITY(index, 0, 1);
						ENTITY::DELETE_ENTITY(&index, true);
					}

					//printf("attaching to player id %i\n",playerid);
				} else {
					//ENTITY::SET_ENTITY_COORDS(index,5000,0,0,0,0,0,true);
					ENTITY::SET_ENTITY_COLLISION(index,false,false);
					//ENTITY::SET_ENTITY_VISIBLE(index,false);
					//ENTITY::SET_ENTITY_AS_MISSION_ENTITY(index,0,1);
					ENTITY::DELETE_ENTITY(&index);
					//printf("no player found to attach back to\n");
				}
				//*(volatile unsigned int*)0xA0C02C = 0x987D0025;
			}
		}
		//}
	}

	void detachAllEntities(int entityToDetachFromIndex) {
		entityToWorkFromIndex = entityToDetachFromIndex;
		executeOnPool(BIG_ENTITY_POOL,callbackDeleteAllAttachedEntities);
	}


	void callbackInvisibleAllAttachedEntities(unsigned int address) {
		BIG_ENTITY_POOL_DATA* data = (BIG_ENTITY_POOL_DATA*)address;
		unsigned int entAddr = (unsigned int)data->getEntity();
		unsigned int attentAddr = data->getEntityAttachedTo();
		if (entAddr < 0x10000)
			return;
		if (attentAddr < 0x10000)
			return;
		int index = entityToIndex(entAddr);
		int attindex = entityToIndex(attentAddr);
		if (ENTITY::DOES_ENTITY_EXIST(index) && ENTITY::DOES_ENTITY_EXIST(attindex)) {
			if (!ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(index,attindex))//they are not attached
				return;
			if (entityToWorkFromIndex != attindex)//not the correct entity to detach from
				return;
			if (index == WEAPON::_0x5D73CD20(entityToWorkFromIndex))//make sure we are not detaching their gun
				return;
			netreq::reqent(index);
			if (netreq::hasent(index)) {
				ENTITY::SET_ENTITY_VISIBLE(index,false);
			}
		}
	}

	void invisibleAllEntities(int entityToInvisibleFromIndex) {
		entityToWorkFromIndex = entityToInvisibleFromIndex;
		executeOnPool(BIG_ENTITY_POOL,callbackInvisibleAllAttachedEntities);
	}

	void callbackAttachAllEntitiesToPed(unsigned int address) {
		BIG_ENTITY_POOL_DATA* data = (BIG_ENTITY_POOL_DATA*)address;
		unsigned int entAddr = (unsigned int)data->getEntity();
		if (entAddr < 0x10000)
			return;
		if (!isAddressAnEntity(entAddr))
			return;
		//int index = entityToIndex(entAddr);
		if (doesEntityAddressExist(entAddr)/*ENTITY::DOES_ENTITY_EXIST(index)*/ && entAddr != getEntityFromIndex(PLAYER::PLAYER_PED_ID())) {
			//if (NETWORK::NETWORK_DOES_ENTITY_EXIST_WITH_NETWORK_ID(index)) {
				//netreq::reqent(index);
				requestControlOfEntityAddress(entAddr);
				if (hasControlOfEntityAddress(entAddr)) {
					//printf("Attaching entity %i\n",index);
					float coord[3] = {0,0,0};
					float rot[3];
					rot[0] = 0;//GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(0,360);
					rot[1] = 0;//GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(0,360);
					rot[2] = 0;//GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(0,360);
					OBJ::attachPropAlreadySpawnedAddress(entityToWorkFromIndex,PlayerMods::bones::Head,entAddr,coord,rot);
				}
			//}
		}
	}

	void attachAllObjectsToPed(int player) {
		entityToWorkFromIndex = player;
		executeOnPool(BIG_ENTITY_POOL,callbackAttachAllEntitiesToPed);
	}

	bool clearLagBool = false;

}

namespace jailMod {
	//Vector3 jailCell1 = {460.358,-994.6392,24.9147};
	//Vector3 jailCell2 = {459.2472,-998.0555,24.9147};
	Vector3 jailCell1 = {458.4394,-1000.930,24.9147};
	Vector3 wardenLocation = {451.2907,-974.4039,30.6896};
	Vector3 freeLocation = {431.0396,-983.2396,30.7107};
	unsigned int playerInJail = 0;
	bool isPlayerInJail(int player) {
		return (bool)(playerInJail&(1<<player));
	}
	void setPlayerInJail(int player) {
		if (isPlayerInJail(player) == false) {
			//printf("before send\n");
			PlayerMods::notify("~r~<font size='25'>You are now in jail!",player);
			//printf("after send\n");
		}
		playerInJail |= (1<<player);
	}
	void setPlayerOutOfJail(int player) {
		if (isPlayerInJail(player)) {
			PlayerMods::teleportToLoc(player,freeLocation.x,freeLocation.y,freeLocation.z);
			PlayerMods::notify("~b~<font size='25'>You are now free!",player);
		}
		playerInJail &= ~(1<<player);
	}
	void teleportToWardenLocation() {
		PlayerMods::teleportToCoords(wardenLocation.x,wardenLocation.y,wardenLocation.z);
	}
	unsigned int timerCheck = 0;
	void loop() {
		timerCheck++;
		unsigned int i = timerCheck%(18*4);
		//if (timerCheck % 50 == 0) {
			//for (int i = 0; i < 18; i++) {
		if (i < 18) {
			//printf("0x%X\n",&jailCell1);
			if (isPlayerInJail(i)) {
				//printf("About to get loc\n");
				Vector3 loc = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(i),true);//PlayerMods::getPlayerLocation(i);//ok
				//printf("Got loc\n");
				Vector3 d = {loc.x-jailCell1.x,loc.y-jailCell1.y,loc.z-jailCell1.z};
				//printf("Calculated loc\n");
				if (math::dist(d.x,d.y,d.z) > 4) {
					//printf("Putting in jail\n");
					PlayerMods::teleportToLoc(i,jailCell1.x,jailCell1.y,jailCell1.z);
					PlayerMods::removeGuns(i);
					//printf("Put in jail\n");
				}
			}
		}
			//}
		//}
	}
};



namespace particles {
	void loadParticle(char *dictionary = "scr_rcbarry2") {
		STREAMING::_REQUEST_DLC_PTFX_ASSET(dictionary);//REQUEST_NAMED_PTFX_ASSET
	}
	int createParticleAtCoord(float x, float y, float z, char *dictionary = "scr_rcbarry2", char *name = "scr_clown_appears") {
		//printf("Creating particle\n");
		STREAMING::_REQUEST_DLC_PTFX_ASSET(dictionary);//REQUEST_NAMED_PTFX_ASSET
		GRAPHICS::_0x9C720B61(dictionary);//_USE_PARTICLE_FX_ASSET_NEXT_CALL
		return GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2(name, x,y,z,0,0,0,1,false,false,false);
	}
	void deleteParticle(int particleID) {
		//printf("Deleting particle\n");
		GRAPHICS::STOP_PARTICLE_FX_LOOPED(particleID,false);
		GRAPHICS::REMOVE_PARTICLE_FX(particleID,false);
	}
};
namespace portalGun {
	struct Portal;
	//void createPortal(Portal *portal, char *objectHash,Vector3 pos);
	//void deletePortal(Portal *portal);
	void spawnPortalPed(Portal *portal);
	struct Portal {
		bool created;
		//int objectID;
		int particleID;
		int pedID;
		Vector3 position;
		bool doingWork;//not really used anymore
		int createParticleTimer;
		bool isEntityTouchingPortal(int entityID) {
			if (ENTITY::DOES_ENTITY_EXIST(entityID)) {
				if (doingWork == false) {
					Vector3 ec = ENTITY::GET_ENTITY_COORDS(entityID,true);
					Vector3 dif = {ec.x-position.x,ec.y-position.y,ec.z-position.z};
					if (math::dist(dif.x,dif.y,dif.z) < 1.5f) {
						return true;
					}
					/*if (ENTITY::IS_ENTITY_TOUCHING_ENTITY(entityID,objectID)) {
						return true;
					}*/
					
				}
			}
			return false;
		}
		void constantlyRan() {
			if (created) {
				createParticleTimer++;
				if (createParticleTimer > 30) {
					particles::deleteParticle(particleID);
					particleID = particles::createParticleAtCoord(position.x,position.y,position.z);
					createParticleTimer = 0;
				}
			}
			if (ENTITY::DOES_ENTITY_EXIST(pedID))
				ENTITY::SET_ENTITY_COORDS(pedID,position.x,position.y,position.z,0,0,0,true);
		}
		void teleportEntityToPortal(int entity) {
			if (doingWork == false) {
				netreq::reqent(entity);
				if (ENTITY::IS_ENTITY_A_PED(entity)) {
					if (PED::IS_PED_A_PLAYER(entity)) {
						for (int i = 0; i < 18; i++) {
							if (PLAYER::GET_PLAYER_PED(i) == entity) {
								if (i == PLAYER::PLAYER_ID()) {
									break;//do regular teleporting
								} else {
									PlayerMods::teleportToLoc(i,position.x,position.y+2,position.z);
								}
								return;
							}
						}
					}
				}
				ENTITY::SET_ENTITY_COORDS(entity,position.x,position.y+2,position.z,0,0,0,true);
			}
		}
		void create(char *objectHash,float x, float y, float z) {
			if (doingWork == false) {
				if (created == false) {
					position.x = x;
					position.y = y;
					position.z = z;
					//Vector3 rot = {0,0,0};
					//doingWork = true;
					//OBJ::forceCreateObject(objectHash,position,rot,true,createCallback,false);
					//createPortal(this,objectHash,position);
					particleID = particles::createParticleAtCoord(x,y,z);
					created = true;
				} else {
					destroy();
					create(objectHash,x,y,z);
				}
			}
		}
		void destroy() {
			if (doingWork == false) {
				if (created == true) {
					//doingWork = true;
					particles::deleteParticle(particleID);
					forge::markEntityForDeletion(pedID);
					//deletePortal(this);
					position.x = 0;
					position.y = 0;
					position.z = 0;
					created = false;
				}
			}
		}
		/*void destroyCallback() {
			created = false;
			doingWork = false;
		}*/
		/*void createCallback(int id) {
			objectID = id;
			ENTITY::SET_ENTITY_PROOFS(id,true,true,true,true,true,true,true,true);
			ENTITY::FREEZE_ENTITY_POSITION(id,true);
			created = true;
			doingWork = false;
		}*/
		void createInsidePed() {
			spawnPortalPed(this);
		}
	};
	Portal *savePortalForCreate;
	/*void createPortalCallback(int objectID) {
		savePortalForCreate->createInsidePed();
		savePortalForCreate->createCallback(objectID);
	}
	void createPortal(Portal *portal, char *objectHash,Vector3 pos) {
		savePortalForCreate = portal;
		Vector3 rot = {0,0,0};
		OBJ::forceCreateObject(objectHash,pos,rot,true,createPortalCallback,false);
	}*/
	/*void deletePortalCallback(int id) {
		int ped = savePortalForCreate->pedID;
		PED::DELETE_PED(&ped);
		savePortalForCreate->destroyCallback();
	}
	void deletePortal(Portal *portal) {
		savePortalForCreate = portal;
		forge::markEntityForDeletion(portal->objectID,deletePortalCallback);
	}*/

	void spawnPortalPedCallback(int pedID) {
		savePortalForCreate->pedID = pedID;
		savePortalForCreate->doingWork = false;
		ENTITY::SET_ENTITY_COORDS(pedID,savePortalForCreate->position.x,savePortalForCreate->position.y,savePortalForCreate->position.z,0,0,0,true);
		ENTITY::SET_ENTITY_VISIBLE(pedID,false);
		ENTITY::SET_ENTITY_PROOFS(pedID,true,true,true,true,true,true,true,true);
		ENTITY::SET_ENTITY_INVINCIBLE(pedID,true);
		ENTITY::FREEZE_ENTITY_POSITION(pedID,true);
	}
	void spawnPortalPed(Portal *portal) {
		if (portal->doingWork == false) {
			portal->doingWork = true;
			savePortalForCreate = portal;
			portal->position.z-=1;
			bodyguard::spawnNow(portal->position,"a_c_pigeon",28,spawnPortalPedCallback);
			portal->position.z+=1;
		}
	}

	Portal portalBegin;
	Portal portalEnd;
	void runEntityPortal(int entityID) {
		if (portalBegin.created && portalEnd.created) {
			if (portalBegin.isEntityTouchingPortal(entityID)) {
				portalEnd.teleportEntityToPortal(entityID);
			}
			if (portalEnd.isEntityTouchingPortal(entityID)) {
				portalBegin.teleportEntityToPortal(entityID);
			}
		}
	}
	void loopPortals() {
		static int updateArrayTimer = 0;
		static int entitiesNearBegin[50];
		static int entitiesNearEnd[50];
		static int entitiesNearBeginCount = 0;
		static int entitiesNearEndCount = 0;
		updateArrayTimer++;
		if (updateArrayTimer > 20)
			updateArrayTimer = 0;
		portalBegin.constantlyRan();
		portalEnd.constantlyRan();
		if (portalBegin.created && portalEnd.created) {
			if (!ENTITY::DOES_ENTITY_EXIST(portalBegin.pedID)) {
				portalBegin.createInsidePed();
				//printf("Begin portal ped does not exist!\n");
				return;
			}
			if (!ENTITY::DOES_ENTITY_EXIST(portalEnd.pedID)) {
				portalEnd.createInsidePed();
				//printf("End portal ped does not exist!\n");
				return;
			}
			//ok run physics
			//printf("Running teleport and stuff\n");
			if (updateArrayTimer == 10) {
				//printf("Updating entity list 1\n");
				entitiesNearBeginCount = getEntitiesNearPed(portalBegin.pedID,entitiesNearBegin,12);
			}
			if (updateArrayTimer == 20) {
				//printf("Updating entity list 2\n");
				entitiesNearEndCount = getEntitiesNearPed(portalEnd.pedID,entitiesNearEnd,12);
				updateArrayTimer = 0;
			}
			//printf("Begin: %i\n",entitiesNearBeginCount);
			for (int i = 0; i < entitiesNearBeginCount; i++) {
				//printf("%i\n",entitiesNearBegin[i]);
				runEntityPortal(entitiesNearBegin[i]);
			}
			//printf("End: %i\n",entitiesNearEndCount);
			for (int i = 0; i < entitiesNearEndCount; i++) {
				//printf("%i\n",entitiesNearEnd[i]);
				runEntityPortal(entitiesNearEnd[i]);
			}
		}
	}
	bool enabled = false;
	char *beginPortalText = "Spawn Blue Portal";
	char *endPortalText = "Spawn Grey Portal";
	char *portalToSpawnText = "Spawn Blue Portal";
	int portalToSpawn = 0;//0 is begin portal, 1 is end portal
	void loop() {
		if (enabled) {
			particles::loadParticle();
			Vector3 spawnPosition;
			if (getBulletEndPosition(&spawnPosition)) {
				//spawn portal
				if (portalToSpawn == 0) {
					//spawn begin portal = blue

					if (portalBegin.created) {
						portalBegin.destroy();
						//printf("Deleting portal\n");
					} else {
						//printf("Creating portal\n");
						portalBegin.create("v_ilev_exball_blue",spawnPosition.x,spawnPosition.y,spawnPosition.z);
					}
				}
				if (portalToSpawn == 1) {
					//spawn end portal = grey
					if (portalEnd.created) {
						portalEnd.destroy();
						//printf("Deleting portal\n");
					} else {
						//printf("Creating portal\n");
						portalEnd.create("v_ilev_exball_grey",spawnPosition.x,spawnPosition.y,spawnPosition.z);
					}
				}
			}
			if (PLAYER::IS_PLAYER_FREE_AIMING(PLAYER::PLAYER_ID())) {
				//print2(portalToSpawnText,10);
				if (portalImageOverritten) {
					if (portalToSpawn == 0) {
						drawing::DrawSprite("mpinventory","deathmatch"/*"in_world_circle"*/,0.5f,0.5f,0.05f,0.05f,0,255,255,255/*39,167,216*/,255);
					} else {
						drawing::DrawSprite("mpinventory","deathmatch",0.5f,0.5f,0.05f,0.05f,180,255,255,255/*255,154,0*/,255);
					}
				}
				if (pressedButtons::r1jpressed == true) {
					//change portal type
					if (portalToSpawn == 0) {
						portalToSpawn = 1;
						portalToSpawnText = endPortalText;
					} else {
						portalToSpawn = 0;
						portalToSpawnText = beginPortalText;
					}
				}
			}
			/*if (pressedButtons::l1jpressed == true) {
				//delete portals
				portalBegin.destroy();
				portalEnd.destroy();
			}*/
		}
		//portal gun doesn't need to be enabled to do the portals
		loopPortals();
	}
};
/*
opd_s _0x9FCE50_t = {0x9FCE50,TOC};//if r3 = 0 it freezes
unsigned int (*_0x9FCE50)(unsigned int r3, unsigned int r4) = (unsigned int(*)(unsigned int, unsigned int))&_0x9FCE50_t;

char _0x9FCE50Data[4*4];
unsigned int _0x9FCE50Detour(unsigned int r3, unsigned int r4) {
	memcpy((void*)0x9FCE50,_0x9FCE50Data,4*4);
	unsigned int ret = _0x9FCE50(r3,r4);//run it and unpatch the one function
	if (ret == 0) {
		printf("It was equal to 0\n");
		*(volatile unsigned int*)0x12BD494 = 0x48000020;
	} else {
		printf("It was else\n");
		*(volatile unsigned int*)0x12BD494 = 0x3C6001CC;
	}
	PatchInJump2(0x9FCE50,(int)_0x9FCE50Detour,false);
	return ret;
}

void fixRequestControlWithPools() {
	//*(volatile unsigned int*)0x9FCE8C = 0x48000134;
	*(volatile unsigned int*)0x9FCFB4 = 0x60000000;//this trips the debugger
	memcpy(_0x9FCE50Data,(void*)0x9FCE50,4*4);
	PatchInJump2(0x9FCE50,(int)_0x9FCE50Detour,false);
}*/


/*
commend:
breakpoint at: 0x12D141C
r3 = DAFB10F9 for friendly, 893E1390  for helpful
r4 = F, then 10
r5 = 00222E250 --- look in commend picture folder in pictures
r6 = 2 but not used
Function             
Unknown  0x012D1384
Unknown  0x000C3FB0
Unknown  0x00A8A790
???  0x001255E0
Unknown  0x00126084
Unknown  0x001261DC
Unknown  0x01667424
Unknown  0x01667538
Unknown  0x00A64720
Unknown  0x00026580
Unknown  0x00035790
Unknown  0x00A61698
Unknown  0x000104C4
Unknown  0x00AE7FA0
Unknown  0x00010494
Unknown  0x00010C54
Unknown  0x00010B40

Function             
Unknown  0x000C3C94
Unknown  0x000C46CC  //here is where it be called from
???  0x001255E0
Unknown  0x00126084
Unknown  0x001261DC
Unknown  0x01667424
Unknown  0x01667538
Unknown  0x00A64720
Unknown  0x00026580
Unknown  0x00035790
Unknown  0x00A61698
Unknown  0x000104C4
Unknown  0x00AE7FA0
Unknown  0x00010494
Unknown  0x00010C54
Unknown  0x00010B40

*/

/*
void NETWORK_INCREMENT_STAT(int player, unsigned int hash, unsigned int amount) {
	opd_s NETWORK_INCREMENT_STAT_t = {0x12D141C,TOC};
	void (*NETWORK_INCREMENT_STAT1)(unsigned int hash, unsigned int amount, unsigned int playerDataPointer) = (void(*)(unsigned int, unsigned int, unsigned int))&NETWORK_INCREMENT_STAT_t;
	NETWORK_INCREMENT_STAT1(hash,amount,getCNetGamePlayer(player));
}

void incrementRPForPlayer(int player, int rp) {
	NETWORK_INCREMENT_STAT(player,GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"),rp);
}
void incrementRPForPlayer2(int player, int rp) {
	NETWORK_INCREMENT_STAT(player,GAMEPLAY::GET_HASH_KEY("MP1_CHAR_XP_FM"),rp);
}
void incrementKillsForPlayer(int player, int amount) {
	NETWORK_INCREMENT_STAT(player,GAMEPLAY::GET_HASH_KEY("MPPLY_KILLS_PLAYERS"),amount);
}*/

//struct NativeArgs {
	//ScriptArg args[100];
//};
/*
ScriptArg(*theStatFunc)(NativeArg_s *args);
void addNative(ScriptArg(*func)(NativeArg_s *args),unsigned int hash) {
	opd_s _9B7A50_t = {0x9B7A50,TOC};
	void (*_9B7A50)(unsigned int hash, ScriptArg(*func)(NativeArg_s *args)) = (void(*)(unsigned int, ScriptArg(*)(NativeArg_s *args)))&_9B7A50_t;
	_9B7A50(hash,func);
}
void addNative(ScriptArg(*func)(NativeArg_s *args),char *name) {
	//addNative(func,jenkins(name,strlen(name)));
	
}*/




#define BUFSIZE 4096
#define TESTDATA "<hi name=\"hi\"><data1>yo</data1></hi>"


namespace XMLObject {
	

//Placement is start of each object to spawn
//Type = 3 for placement
//FrozenPos for frozen or not
//ModelHash for model hash
//IsVisible for visible
//PositionRotation X,Y,Z,Pitch,Roll,Yaw
//Attachment isAttached="true" AttachedTo BoneIndex 


	char *text;
	
	
	unsigned int objectHash;
	bool frozen;
	bool IsVisible;
	float x,y,z,rx,ry,rz;
	
	
	void runNextElement() {
	
	}
	

	void start(char *xmlData) {
		text = xmlData;
		
	}

}



unsigned int search(unsigned int start, unsigned int end, char *data, unsigned int lengthOfData) {
	unsigned int offset = 0;
	unsigned int begin = 0;
	for (unsigned int addr = start; addr < end; addr++) {
		if (*(char*)addr == data[offset]) {
			offset++;
			if (offset == lengthOfData) {
				return begin+1;
			}
		} else {
			begin = addr;
			offset = 0;
		}
	}
	return 0;
}

void replace(unsigned int start, unsigned int end, char *find, char *replaceWith, unsigned int length) {
	unsigned int addr = start;
	while (addr != 0) {
		addr = search(addr,end,find,length);
		if (addr != 0) {
			for (int i = 0; i < length; i++) {
				*(char*)(addr+i) = *(char*)(replaceWith+i);
			}
			addr+=length;
		}
	}
}

void spoofip() {
	unsigned int mycurip = *(volatile unsigned int*)0x0FA9A2E;
	unsigned int replaceWith = 0x06060606;
	replace(0x01A274E4,0x01C274E4,(char*)&mycurip,(char*)&replaceWith,4);
}

unsigned int getWeirdTimeValue() {
	//reversed from loc_3EE460
	unsigned int weirdPointer = *(volatile unsigned int*)0x1CF72A8;
	opd_s sub_A1B410_t = {0xA1B410,TOC};
	unsigned int (*sub_A1B410)(unsigned int r3) = (unsigned int(*)(unsigned int))&sub_A1B410_t;
	unsigned int value1 = sub_A1B410(weirdPointer);
	if (value1 == 0) {
		return 0;
	}
	//value1 is not 0
	opd_s sub_D1ED70_t = {0xD1ED70,TOC};
	unsigned int (*sub_D1ED70)(unsigned int r3) = (unsigned int(*)(unsigned int))&sub_D1ED70_t;
	return sub_D1ED70(weirdPointer);
}

void RESPAWN_PLAYER_PED_EVENT_local(float *coords, unsigned int r4, unsigned int weirdTime, unsigned int r5, unsigned int r6, unsigned int r7, unsigned int r8, unsigned int r9, float f1, float f2, float f3){}//0x12C3224 looks like it only works on yourself

void changeRadioStation(int player, int radioStation) {
	/*
	r3 = getPlayerPedByIndex(player);
		r3 = *(volatile unsigned int*)(r3+0xBD0);
		r31 = *(volatile unsigned int*)(r3+0x160);
		r4 = *(volatile unsigned int*)(r31+0x4c);
	*/
	unsigned int r3 = getPlayerPedByIndex(player);//a CPed
	//r3 = *(volatile unsigned int*)(r3+0xBD0); //CPlayerInfo
	//unsigned int pedNetworkData = *(volatile unsigned int*)(r3+0x160);//this is just the same as the other
	unsigned int dataForThisFunction = *(volatile unsigned int*)(r3+0x7C);//a different CPed
	//printf("Name of player ped class: %s\nName of class at 0x7C: %s\n Name of class at 0x4C: %s\nent+0xBD0: 0x%X\n",getClassName(r3),getClassName(dataForThisFunction),getClassName(*(volatile unsigned int*)(r3+0x4C)),*(volatile unsigned int*)(r3+0xBD0));
	//printf("pedNetworkData: 0x%X, player ped address: 0x%X\n",pedNetworkData,getPlayerPedByIndex(player));//yes these are the same actually
	//unsigned int pedNetworkData = *(volatile unsigned int*)(getEntityFromIndex(PLAYER::GET_PLAYER_PED(player)) + 0x4C);  NOT THIS ONE EVEN THOUGH 0x4C IS USED ON BOTH OF THEM
	opd_s radioEvent_t = {0x12C7E10,TOC};
	void (*radioEvent)(unsigned int ped, int station) = (void(*)(unsigned int, int))&radioEvent_t;
	radioEvent(dataForThisFunction,radioStation);
	
}




opd_s NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES_t = {0x3E893C,TOC};
void (*NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES)(void *g_pointer, unsigned int size) = (void(*)(void *,unsigned int))&NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES_t;

void setGlobalAsOtherPlayers(int globalNumber, int sizeOfGlobal) {
	//sizeOfGlobal * 0x4 has to be evenly divisible by 0x12 for it to work properly
	unsigned int addr = Read_Global_Address(globalNumber);
	if (addr != 0) {
		NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES((void*)addr,sizeOfGlobal);
		//printf("Set 0x%X size 0x%X*4 to be global for players\n",addr,sizeOfGlobal);
	}
}

void setGlobalAsHost(int globalNumber, int sizeOfGlobal) {
	unsigned int addr = Read_Global_Address(globalNumber);
	if (addr != 0) {
		NETWORK::NETWORK_REGISTER_HOST_BROADCAST_VARIABLES(addr,sizeOfGlobal);
		//printf("Set 0x%X size 0x%X*4 to be global host\n",addr,sizeOfGlobal);
	}
}

bool syncAreaOfMem(int globalStart, unsigned int sizeOfGlobals);
void setGlobalAsNet(int globalNumber, int sizeOfGlobal) {
	//setGlobalAsOtherPlayers(globalNumber,sizeOfGlobal);
	//setGlobalAsHost(globalNumber,sizeOfGlobal);
	syncAreaOfMem(globalNumber, sizeOfGlobal);
}

void setGlobalHostBroadcast(int global, int sizeInGlobal);
template <typename T>
void setGlobalValueForAll(int globalNumber, T value) {//this is the last function that shows up in the optimized version
	//printf("gonna set\n");
	//setGlobalAsNet(globalNumber,1);
	setGlobalHostBroadcast(globalNumber,1);
	//printf("set it!\n");
	unsigned int addr = Read_Global_Address(globalNumber);
	*(T*)(addr) = value;
	//printf("set all properly\n");
	
}


void removeMyselfFromBadsport() {
	Write_Global(262145+79, 0);
	Write_Global(262145+80, 0); 
	Write_Global(262145+81, 0);
	Write_Global(262145+119, 0);
	Write_Global(262145+120, 0);
	Write_Global(262145+121, 0);
	Write_Global(262145+122, 0);
	Write_Global(262145+123, 0);
	Write_Global(262145+124, 0);
	Write_Global(262145+125, 0);
	Write_Global(262145+126, 0);
	Write_Global(262145+127, 0); 
	Write_Global(262145+128, 0);
}

void removeMyselfFromBadsport2() {
	Write_Global(262145+79, 1);
	Write_Global(262145+80, 1); 
	Write_Global(262145+81, 1);
	Write_Global(262145+119, 1);
	Write_Global(262145+120, 1);
	Write_Global(262145+121, 1);
	Write_Global(262145+122, 1);
	Write_Global(262145+123, 1);
	Write_Global(262145+124, 1);
	Write_Global(262145+125, 1);
	Write_Global(262145+126, 1);
	Write_Global(262145+127, 1); 
	Write_Global(262145+128, 1);
}

void setAllOutOfBadsport() {
	/*setGlobalValueForAll(262145+79, 0);
	setGlobalValueForAll(262145+80, 0); 
	setGlobalValueForAll(262145+81, 0);
	setGlobalValueForAll(262145+119, 0);
	setGlobalValueForAll(262145+120, 0);
	setGlobalValueForAll(262145+121, 0);
	setGlobalValueForAll(262145+122, 0);
	setGlobalValueForAll(262145+123, 0);
	setGlobalValueForAll(262145+124, 0);
	setGlobalValueForAll(262145+125, 0);
	setGlobalValueForAll(262145+126, 0);
	setGlobalValueForAll(262145+127, 0); 
	setGlobalValueForAll(262145+128, 0);*/
	setGlobalHostBroadcast(262145+79,81-79+1);
	setGlobalHostBroadcast(262145+119,128-119+1);
	removeMyselfFromBadsport2();
}

//vehicle spawning shit
/*
callstack from breakpoint at 0x176431C

Function             
Unknown  0x0176428C
Unknown  0x01341874  //I have this one marked and setting a blr here doesn't work
Unknown  0x0136D33C  //haven't tried a blr here, however this gets called too often to be a vehicle specific thing
???  0x0133CFA8      //this looks to be like a manager of different kinds I think
Unknown  0x00A081CC
Unknown  0x00A08490
Unknown  0x00A09798
Unknown  0x0160DADC
Unknown  0x00A15C2C
Unknown  0x00D1407C
Unknown  0x00D14188
Unknown  0x00D14264
Unknown  0x00D14B30
Unknown  0x012F2EE0
Unknown  0x0150E570
Unknown  0x01667424
Unknown  0x01667538
Unknown  0x00A64720
Unknown  0x00026580
Unknown  0x00035790
Unknown  0x00A61698
Unknown  0x000104C4
Unknown  0x00AE7FA0
Unknown  0x00010494
Unknown  0x00010C54
Unknown  0x00010B40


*/

/*
stat_get_masked_int(unsigned int arg1, unsigned int *arg2, unsigned int arg3, unsigned int arg4, unsigned int arg5)
arg1 = stat hash
arg2 = integer pointer (stores a small integer in it)
arg3 = 2 (an integer)
arg4 = 1 (an integer)  8 in the scripts
arg5 = 0xFFFFFFFFFFFFFFFF

*/


void eventFreeze(int player, short eventToSpoofTo, int argumentValue) {
	/*opd_s cw_t = {0x12C2ECC,TOC};
	void(*cw)(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int r6) = (void(*)(unsigned int, unsigned int, unsigned int, unsigned int))&cw_t;
	cw(1,0xE,*(volatile unsigned int*)(0x2148E84+0xD04),0);*/

	//radio station event, cuz it works per player
	unsigned int r3 = getPlayerPedByIndex(player);
	r3 = *(volatile unsigned int*)(r3+0xBD0);
	unsigned int pedNetworkData = *(volatile unsigned int*)(r3+0x160);
	short originalEvent = *(short*)(0x12C7E48+0x2);
	*(short*)(0x12C7E48+0x2) = eventToSpoofTo;
	opd_s radioEvent_t = {0x12C7E10,TOC};
	void (*radioEvent)(unsigned int ped, int station) = (void(*)(unsigned int, int))&radioEvent_t;
	radioEvent(pedNetworkData,argumentValue);
	*(short*)(0x12C7E48+0x2) = originalEvent;
}


//opd_s updateEventDataWithServer_t = {0x9FCE50,TOC};   already in prx from ages ago
//bool (*updateEventDataWithServer)(unsigned int eventAddr, unsigned int r4) = (bool(*)(unsigned int,unsigned int))&updateEventDataWithServer_t;

opd_s sub_A02A74_t = {0xA02A74,TOC};//only used 3 times
unsigned int(*sub_A02A74)(unsigned int unknownEventData, unsigned int eventID) = (unsigned int(*)(unsigned int, unsigned int))&sub_A02A74_t;

opd_s executeEventOnAllPlayers_t = {0xA02AC0,TOC};
void (*executeEventOnAllPlayers)(unsigned int eventData, unsigned int eventID) = (void(*)(unsigned int, unsigned int))&executeEventOnAllPlayers_t;
/*
bool (*updateEventDataWithServer)(unsigned int eventDataPointer, int unknown2);
int (*allocateEvent)(int event_addr, int type,int unk1, int unk2, int unk3);
unsigned int (*getUnknownPoolData)(entityPool *poolPointer);
int (*executeEventOnOnePlayer)(int eventDataPointer, int event_addr);
*/
//cw(1,0xE,*(volatile unsigned int*)(0x2148E84+0xD04),0);

void GAME_WEATHER_EVENT_local(int one, int weatherType, unsigned int unkValue, int zero) {//weather
	unsigned int someEventData = *(volatile unsigned int*)0x1CF72B0;
	bool properlyInitializedEvent = updateEventDataWithServer(someEventData,0);
	if (properlyInitializedEvent == false)
		return;
	unsigned int eventPool = *(volatile unsigned int*)0x1CC4A54;
	unsigned int eventStructure = getUnknownPoolData(getEntityPool(EventPool));
	allocateEvent(eventStructure,0xA,0,1,0);
	*(volatile unsigned int*)(eventStructure + 0x1C ) = zero;
	*(volatile unsigned int*)(eventStructure + 0x20 ) = one;
	*(volatile unsigned int*)(eventStructure + 0x24 ) = weatherType;
	*(volatile unsigned int*)(eventStructure + 0x28 ) = unkValue;
	*(volatile unsigned int*)(eventStructure + 0x00 ) = 0x19265E0;
	int weirdValue = sub_A02A74(someEventData,0xA);
	if (weirdValue != 0) {
		unsigned int r5;
		r5 = *(volatile unsigned int*)weirdValue;
		r5 = *(volatile unsigned int*)(r5 + 0x48);
		r5 = *(volatile unsigned int*)(r5 + 0x0);
		opd_s weirdFunc_t = {r5,TOC};
		unsigned int (*weirdFunc)(unsigned int r3, unsigned int r4) = (unsigned int(*)(unsigned int, unsigned int))&weirdFunc_t;
		unsigned int valToCheck = weirdFunc(weirdValue,eventStructure);
		if (valToCheck != 0)
			executeEventOnAllPlayers(someEventData,0xA);
	}
	executeEventOnOnePlayer(someEventData,eventStructure);
}

void setTime(int player, int hours, int minutes, int seconds) {
	NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(hours,minutes,seconds);
	opd_s _0x12C2A00_t = {0x12C2A00,TOC};
	void (*_0x12C2A00)(unsigned int num, CNetGamePlayer *networkData) = (void(*)(unsigned int, CNetGamePlayer *))&_0x12C2A00_t;
	//_0x12C2A00(2,*(volatile unsigned int*)( *(volatile unsigned int*)0x1CC4A34 + 0x2a4 ));
	//unsigned int value = *(volatile unsigned int*)( *(volatile unsigned int*)0x1CC4A34 + 0x2a4 );
	//printf("Time class name: %s\n",getClassName(value));
	for (int i = 0; i < 10; i++)
		_0x12C2A00(i,getCNetGamePlayer(player));
	//_0x12C2A00(4,getCNetGamePlayer(player));
	//_0x12C2A00(2,getCNetGamePlayer(player));
	//_0x12C2A00(8,getCNetGamePlayer(player));
}

/*
class ScriptSpam {
private:
	int currentScriptId;
	int playerBitset;
	int cplayer;
	bool loopBoolean;
	ScriptArg args[2];
public:
	ScriptSpam() {
		loopBoolean = 0;
		playerBitset = 0;
		cplayer = 0;
		currentScriptId = 0;
	}
	void setPlayer(int player) {
		cplayer = player;
		playerBitset = 1<<player;
	}
	void setAllPlayers() {
		cplayer = 0;
		playerBitset = ~(1<<PLAYER::PLAYER_ID());//every bit except me
	}
	void stop() {
		loopBoolean = false;
	}
	void start() {
		currentScriptId = 0;
		loopBoolean = true;
	}
	void sendNextScript() {
		args[0].i = currentScriptId++;
		args[1].i = cplayer;
		PlayerMods::eventCreator::callScriptEvent(args,2,playerBitset);
	}
	void loop() {
		if (loopBoolean) {
			sendNextScript();
			if (currentScriptId > 500) {
				stop();
				print2("Done!",2000);
			}
		}
	}
};
*/



//136D334 updateCNetObjData can check if r4 is the same type as the hash
//freeze objects: https://pastebin.com/W6hweZSz




//this code never fucking works
void hookFunctionStart(int Address, int saveStub, int Destination){
	saveStub = *(volatile int*)saveStub;
	int BranchtoAddress = Address + (4 * 4);
	int StubData[8];
	StubData[0] = 0x3D600000 + ((BranchtoAddress >> 16) & 0xFFFF);
	if (BranchtoAddress & 0x8000) StubData[0] += 1;
	StubData[1] = 0x396B0000 + (BranchtoAddress & 0xFFFF);
	StubData[2] = 0x7D6903A6;
	write_process_sc(&StubData[3], (void*)Address, 4 * 4);
	StubData[7] = 0x4E800420;
	write_process_sc((void*)saveStub, StubData, 8 * 4);
	PatchInJumpAddr(Address, Destination,false);
}



/*
__ALWAYS_INLINE */
/*void hookFunctionStartOnlyForThisExactFunction(int Address, unsigned int saveStub, int Destination){
	saveStub = *(volatile unsigned int*)saveStub;
	int BranchtoAddress = Address + (4*4);
	int StubData[8];
	StubData[0] = 0x3D600000 + ((BranchtoAddress >> 16) & 0xFFFF);
	if(BranchtoAddress & 0x8000) StubData[0] += 1;
	StubData[1] = 0x396B0000 + (BranchtoAddress & 0xFFFF);
	StubData[2] = 0x7D6903A6;
	memcpy(&StubData[3], (void*)Address, 4*4);
	StubData[7] = 0x4E800420;
	printf("saveStub: 0x%X\n",saveStub);
	StubData[4] = 0xFBA1FFE8;//this is a fix because it's a local function but luckily that function is only 1 line
	write_process_sc((void*)saveStub, StubData, 8*4);
	printf("DDONE\n");
	PatchInJumpAddr(Address, Destination,false);
}

opd_s updateCNetObjData_t = {0x136D334,TOC};
unsigned int (*updateCNetObjData)(unsigned int r3, unsigned int r4) = (unsigned int(*)(unsigned int, unsigned int))&updateCNetObjData_t;

int updateCNetObjData_stub(unsigned int r3, unsigned int r4) {
	 return updateCNetObjData(r3,r4);//just a filler, doesn't matter what it here
}*/

#ifdef oldProtectionCodeForVehicle
unsigned int getCAutomobileSyncTreeFromCNetObjAutomobile(unsigned int r3_CNetObjAutomobile) {
	unsigned int getCAutomobileSyncTreeaddr = 0;
	getCAutomobileSyncTreeaddr = *(volatile unsigned int*)r3_CNetObjAutomobile;
	getCAutomobileSyncTreeaddr = *(volatile unsigned int*)(getCAutomobileSyncTreeaddr+0x14);
	getCAutomobileSyncTreeaddr = *(volatile unsigned int*)getCAutomobileSyncTreeaddr;
	//printf("getCAutomobileSyncTreeaddr: 0x%X\n",getCAutomobileSyncTreeaddr);
	opd_s getCAutomobileSyncTree_t = {getCAutomobileSyncTreeaddr,TOC};
	unsigned int(*getCAutomobileSyncTree)(unsigned int r3_CNetObjAutomobile) = (unsigned int(*)(unsigned int))&getCAutomobileSyncTree_t;
	return getCAutomobileSyncTree(r3_CNetObjAutomobile);
}


/*
types of vehicles:
Hash: 0xB779A091, Class: 17CNetObjAutomobile, Type: 0x0, Class Address: 0x1936530
Hash: 0x6CBD1D6D, Class: 12CNetObjPlane, Type: 0x1, Class Address: 0x1938828
Hash: 0x2F03547B, Class: 11CNetObjHeli, Type: 0x6, Class Address: 0x1937A48
Hash: 0xABB0C0, Class: 11CNetObjBike, Type: 0x9, Class Address: 0x1936A58
Hash: 0x4339CD69, Class: 11CNetObjBike, Type: 0xA, Class Address: 0x1936A58 //different than the other bike, this is a bicicle
Hash: 0xC1CE1183, Class: 11CNetObjBoat, Type: 0xB, Class Address: 0x1936F80
Hash: 0x2DFF622F, Class: 16CNetObjSubmarine, Type: 0xD, Class Address: 0x1939E80
*/

unsigned int getTypeFromName(char *className) {
	if (strstr(className,"Automobile")) {
		return 0;
	}
	if (strstr(className,"Plane")) {
		return 1;
	}
	if (strstr(className,"Heli")) {
		return 6;
	}
	if (strstr(className,"Bike")) {
		return 9;
	}
	if (strstr(className,"Boat")) {
		return 0xB;
	}
	if (strstr(className,"Submarine")) {
		return 0xD;
	}
	return 0;
}


bool freezeVehicleDetected = false;
//returns true if it is not the right one
bool checkModelType(unsigned int r4_CNetObjAutomobile, unsigned int shouldBe, unsigned int val_CVehicleModelInfo, bool spoofTheModel) {
	//unsigned int CObj = *(volatile unsigned int*)(r4_CNetObjAutomobile+0x2C);//not valid at this time
	unsigned int is = *(volatile unsigned int*)r4_CNetObjAutomobile;
	if (is != shouldBe) {
		//*(volatile unsigned int*)r4_CNetObjAutomobile = shouldBe;
		//*(volatile unsigned int*)CObj = CObjClassAddress;
		if (spoofTheModel)
			*(volatile unsigned int*)(val_CVehicleModelInfo+0x1B8) = getTypeFromName(getClassName(r4_CNetObjAutomobile));
		freezeVehicleDetected = true;
		//printf("\n\nFREEZE DETECTED\n\n\n");
		/*for (unsigned int i = 0x14; i <= 0x64; i+=4) {
			*(volatile unsigned int*)(r4_CNetObjAutomobile+i) = 0;
		}*/
		return true;
	}
	return false;
}

bool fixCNetObjWithModel(unsigned int r3_CVehicleModelData, unsigned int r4_CNetObjAutomobile, bool spoofTheModel = true) {
	char *className = getClassName(r4_CNetObjAutomobile);//this is the one that is wrong
	unsigned int val_CVehicleModelInfo = r3_CVehicleModelData;
	if (val_CVehicleModelInfo > 0x10000) {
		unsigned int thisType = *(volatile unsigned int*)(val_CVehicleModelInfo+0x1B8);
		switch (thisType) {
		case 0x0:
			return checkModelType(r4_CNetObjAutomobile,0x1936530,val_CVehicleModelInfo,spoofTheModel/*0x1917DC0*/);//17CNetObjAutomobile
			break;
		case 0x1:
			return checkModelType(r4_CNetObjAutomobile,0x1938828,val_CVehicleModelInfo,spoofTheModel/*0x1919300*/);//12CNetObjPlane
			break;
		case 0x6:
			return checkModelType(r4_CNetObjAutomobile,0x1937A48,val_CVehicleModelInfo,spoofTheModel/*0x1918908*/);//11CNetObjHeli
			break;
		case 0x9:
			return checkModelType(r4_CNetObjAutomobile,0x1936A58,val_CVehicleModelInfo,spoofTheModel/*0x191A608*/);//11CNetObjBike
			break;
		case 0xA:
			return checkModelType(r4_CNetObjAutomobile,0x1936A58,val_CVehicleModelInfo,spoofTheModel/*0x1918250*/);//11CNetObjBike (type = bicicle)
			break;
		case 0xB:
			return checkModelType(r4_CNetObjAutomobile,0x1936F80,val_CVehicleModelInfo,spoofTheModel/*0x1919960*/);//11CNetObjBoat
			break;
		case 0xD:
			return checkModelType(r4_CNetObjAutomobile,0x1939E80,val_CVehicleModelInfo,spoofTheModel/*0x1919C58*/);//16CNetObjSubmarine
			break;
		}
	}
	return false;
}

/*
bool fixCNetObjSyncTree(unsigned int r3_CAutomobileSyncTree, unsigned int r4_CNetObjAutomobile) {
	unsigned int hash = *(volatile unsigned int*)(*(volatile unsigned int*)(r3_CAutomobileSyncTree+0x1c)+0x74);//get this because I need the model info
	unsigned int val_CVehicleModelInfo = modelHashToAddress(hash);
	return fixCNetObjWithModel(val_CVehicleModelInfo,r4_CNetObjAutomobile);
}

bool fixCNetObjSyncTree(unsigned int r3_CNetObjAutomobile) {
	return fixCNetObjSyncTree(getCAutomobileSyncTreeFromCNetObjAutomobile(r3_CNetObjAutomobile),r3_CNetObjAutomobile);
}*/

bool fixCNetObjWithModel(unsigned int r3_CNetObjAutomobile, bool spoofTheModel = true) {
	unsigned int model = *(volatile unsigned int*)(r3_CNetObjAutomobile+0x2C);
	model = *(volatile unsigned int*)(model+0x10);//should be correct
	//printf(".");
	return fixCNetObjWithModel(model,r3_CNetObjAutomobile,spoofTheModel);
}


opd_s CNetworkObjectMgrSyncer_t = {0x133D6EC,TOC};
unsigned int(*CNetworkObjectMgrSyncer)(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int r6, unsigned int r7, unsigned int r8) = (unsigned int(*)(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int))&CNetworkObjectMgrSyncer_t;
//133D6EC CNetworkObjectMgrSyncer
/*
opd_s getCNetObjFromIndex_t = {0x9F8C38,TOC};
unsigned int (*getCNetObjFromIndex)(unsigned int CNetworkObjectMgr, unsigned short index, unsigned int zero) = (unsigned int(*)(unsigned int, unsigned short, unsigned int))&getCNetObjFromIndex_t;
//9F8C38 getCNetObjFromIndex

void fixAllCNetObj() {
	static int highest = 0xfff;//good starting number

	int localHighest = highest;
	for (int i = 0; i < localHighest; i++) {
		unsigned int CNetObj = getCNetObjFromIndex(*(volatile unsigned int*)0x1CF72AC,i,0);
		if (CNetObj != 0) {
			fixCNetObj(CNetObj);
			localHighest = i;
		}
	}
	localHighest = localHighest + 1;

	highest = 0xfff;//localHighest;

	printf("Highest One = 0x%X\n",highest);
}
*/

unsigned int CNetworkObjectMgrSyncer_detour(unsigned int r3_CNetworkObjectMgr, unsigned int r4_CNetGamePlayer, unsigned int r5_CNetGamePlayer, unsigned int r6_unk, unsigned int r7_unk, unsigned int r8_unk) {
	opd_s sub_A08900_t = {0xA08900,TOC};
	unsigned int (*sub_A08900)(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int r6) = (unsigned int(*)(unsigned int, unsigned int, unsigned int, unsigned int))&sub_A08900_t;
	opd_s sub_9F8C38_t = {0x9F8C38,TOC};
	unsigned int (*sub_9F8C38)(unsigned int r3, unsigned int r4, unsigned int r5) = (unsigned int(*)(unsigned int, unsigned int, unsigned int))&sub_9F8C38_t;

	unsigned int r4_CNetObjAutomobile = 0;//this is actually any CNetObj lmao
	r4_CNetObjAutomobile = sub_A08900(r3_CNetworkObjectMgr,r7_unk,r4_CNetGamePlayer,1);
	if (r4_CNetObjAutomobile == 0)
		r4_CNetObjAutomobile = sub_9F8C38(r3_CNetworkObjectMgr,r7_unk,1);
	bool callOrig = true;
	if (r4_CNetObjAutomobile != 0) {
		unsigned int cent = *(volatile unsigned int*)(r4_CNetObjAutomobile+0x2C);
		if (cent > 0x10000) {
			//printf("fixing via model\n");
			bool isWrongModel = fixCNetObjWithModel(r4_CNetObjAutomobile,false);
			if (isWrongModel) {
				callOrig = false;
				printf("FREEZE SPOT BAD\n");
			} else {
				callOrig = true;
			}
		} else {
			//printf("fixing via sync tree\n");
			//fixCNetObjSyncTree(r4_CNetObjAutomobile);
			callOrig = true;
			printf("umm this is a spot\n");
		}
	}
	if (callOrig) {
		//printf("Calling func\n");
		return CNetworkObjectMgrSyncer(r3_CNetworkObjectMgr,r4_CNetGamePlayer,r5_CNetGamePlayer,r6_unk,r7_unk,r8_unk);
	} else {
		printf("--Bypassing func\n");
		return 0;
	}
}

void CNetworkObjectMgrSyncer_detour_start() {
	//0x01C707F0 is opd
	*(volatile unsigned int*)(0x01C707F0+0x0) = *(volatile unsigned int*)((unsigned int)CNetworkObjectMgrSyncer_detour + 0x0);
	*(volatile unsigned int*)(0x01C707F0+0x4) = *(volatile unsigned int*)((unsigned int)CNetworkObjectMgrSyncer_detour + 0x4);
}

/*
after the fix, it took a bit but froze here:
0x0133B084...
0x0133B084 = 0x48000080;//b 0x80
then went to 0xDB9430 which is part of sub_DB9340
so...
0xDB9340 = 0x4E800020;

0x00368610 then here
*/

//returns true if freeze is imminent, false if you are safe
/*
bool CNetObjAutomobile_freezecheck(unsigned int r3_CAutomobileSyncTree, unsigned int r4_CNetObjAutomobile) {

	bool callOriginal = true;
	unsigned int hash = *(volatile unsigned int*)(*(volatile unsigned int*)(r3_CAutomobileSyncTree+0x1c)+0x74);
	//CNetObjPlane (1) and CNetObjHeli (6) are the ones to check for
	char *className = getClassName(r4_CNetObjAutomobile);
	if (strstr(className,"CNetObjPlane")) {
		//class is a plane...
		unsigned int thisAddress = modelHashToAddress(hash);
		if (thisAddress > 0x10000) {
			unsigned int thisType = *(volatile unsigned int*)(thisAddress+0x1B8);
			if (thisType != 1)
				callOriginal = false;
		}
	}

	if (strstr(className,"CNetObjHeli")) {
		//class is a heli...
		unsigned int thisAddress = modelHashToAddress(hash);
		if (thisAddress > 0x10000) {
			unsigned int thisType = *(volatile unsigned int*)(thisAddress+0x1B8);
			if (thisType != 6) {
				callOriginal = false;
			}
		}
	}

	return !callOriginal;

	//updateCNetObjData_stub(r3_CAutomobileSyncTree,r4_CNetObjAutomobile);
}*/
/*
bool CNetObjAutomobile_freezecheck(unsigned int r3_CNetObjAutomobile) {
	return CNetObjAutomobile_freezecheck(getCAutomobileSyncTreeFromCNetObjAutomobile(r3_CNetObjAutomobile),r3_CNetObjAutomobile);
}*/

/*
void updateCNetObjData_reverse(unsigned int r3_CAutomobileSyncTree, unsigned int r4_CNetObjAutomobile) {
	if (fixCNetObjSyncTree(r3_CAutomobileSyncTree,r4_CNetObjAutomobile) == true) {
		*(volatile unsigned int*)0x134AF70 = 0x4E800020;
		printf("\n\n\n\n\n\nFREEZE OBJECT!\n\n\n\n\n\n\n");
		//*(volatile unsigned int*)0xEDF834 = 0x4E800020;//unsure exactly
		//*(volatile unsigned int*)0xEE2084 = 0x38600000;//check if helicopter is rappelling
		//*(volatile unsigned int*)(0xEE2084+0x4) = 0x4E800020;//check if helicopter is rappelling
		
		0x013BBF64 = nop
		0x013AE670 = nop
		0x013AE7A4 = nop
		0x013AE7C0= nop
		0x013AE288 = nop
		
		return;
	}

	//fixCNetObj(r3_CAutomobileSyncTree,r4_CNetObjAutomobile);

	if (r4_CNetObjAutomobile == 0)
		return;
	unsigned int call1addr = 0;
	call1addr = *(volatile unsigned int*)r4_CNetObjAutomobile;
	call1addr = *(volatile unsigned int*)(call1addr+0x108);
	call1addr = *(volatile unsigned int*)call1addr;
	opd_s call1_t = {call1addr,TOC};
	unsigned int(*call1)(unsigned int r3_CNetObjAutomobile, unsigned int r4) = (unsigned int(*)(unsigned int, unsigned int))&call1_t;
	unsigned int call1val = call1(r4_CNetObjAutomobile,0);

	unsigned int call2addr = 0;
	call2addr = *(volatile unsigned int*)r4_CNetObjAutomobile;
	call2addr = *(volatile unsigned int*)(call2addr+0xE8);
	call2addr = *(volatile unsigned int*)call2addr;
	opd_s call2_t = {call2addr,TOC};
	void(*call2)(unsigned int r3_CNetObjAutomobile) = (void(*)(unsigned int))&call2_t;
	call2(r4_CNetObjAutomobile);

	opd_s sub_A175DC_t = {0xA175DC,TOC};
	void (*sub_A175DC)(unsigned int r3_CAutomobileSyncTre, unsigned int r4_CNetObjAutomobil, unsigned int *storeValue, unsigned int probablyNothingButZeroAnyways) = (void(*)(unsigned int, unsigned int, unsigned int *, unsigned int))&sub_A175DC_t;
	unsigned int storeValue1 = 0;
	sub_A175DC(r3_CAutomobileSyncTree,r4_CNetObjAutomobile,&storeValue1,0);

	unsigned int r3 = *(volatile unsigned int*)(r4_CNetObjAutomobile+0x64);
	r3 = r3 | storeValue1;
	*(volatile unsigned int*)(r4_CNetObjAutomobile+0x64) = r3;

	r3 = *(volatile unsigned int*)(r3_CAutomobileSyncTree+0x8);
	if (r3 == 0)
		return;
	if (call1val == 0)
		return;

	call1addr = 0;
	call1addr = *(volatile unsigned int*)r4_CNetObjAutomobile;
	call1addr = *(volatile unsigned int*)(call1addr+0x108);
	call1addr = *(volatile unsigned int*)call1addr;
	call1_t.sub = call1addr;
	call1val = call1(r4_CNetObjAutomobile,0);//this one is called again at address 0x136D3E4
	if (call1val == 0)
		return;
	char r3_c = *(unsigned char*)(r4_CNetObjAutomobile+0x27);
	if (r3_c == 0)//at address 0x136D3F8
		return;

	unsigned int call3addr = 0;
	call3addr = *(volatile unsigned int*)r4_CNetObjAutomobile;
	call3addr = *(volatile unsigned int*)(call3addr+0xEC);
	call3addr = *(volatile unsigned int*)call3addr;
	opd_s call3_t = {call3addr,TOC};
	void(*call3)(unsigned int r3_CNetObjAutomobile) = (void(*)(unsigned int))&call3_t;
	call3(r4_CNetObjAutomobile);

	unsigned int call4addr = 0;
	call4addr = *(volatile unsigned int*)r4_CNetObjAutomobile;
	call4addr = *(volatile unsigned int*)(call4addr+0x110);
	call4addr = *(volatile unsigned int*)call4addr;
	opd_s call4_t = {call4addr,TOC};
	void(*call4)(unsigned int r3_CNetObjAutomobile) = (void(*)(unsigned int))&call4_t;
	call4(r4_CNetObjAutomobile);

	return;
}

void updateCNetObjData_detour_start() {
	//0x137
	//-0x2CBC = 0xD344
	//0x137D344
	//hookFunctionStartOnlyForThisExactFunction(0x136D334,(unsigned int)updateCNetObjData_stub,(int)updateCNetObjData_detour);
	PatchInJumpAddr(0x136D334,(int)updateCNetObjData_reverse,false);
}
*/


/*
//136D334 updateCNetObjData
opd_s updateCNetObjData_t = {0x136D334,TOC};
unsigned int (*updateCNetObjData)(unsigned int r3, unsigned int r4) = (unsigned int(*)(unsigned int, unsigned int))&updateCNetObjData_t;
unsigned char updateCNetObjData_data[4*4];
unsigned int updateCNetObjData_detour(unsigned int r3_CAutomobileSyncTree, unsigned int r4_CNetObjAutomobile);
unsigned int updateCNetObjData_detour(unsigned int r3_CAutomobileSyncTree, unsigned int r4_CNetObjAutomobile) {
	static int reccursionValue = 0;
	reccursionValue++;
	//fix it back to normal
	memcpy((void*)0x136D334,updateCNetObjData_data,4*4);

	//do calculations
	bool callOriginal = true;
	unsigned int hash = *(volatile unsigned int*)(*(volatile unsigned int*)(r3_CAutomobileSyncTree+0x1c)+0x74);
	//CNetObjPlane (1) and CNetObjHeli (6) are the ones to check for
	char *className = getClassName(r4_CNetObjAutomobile);
	if (strstr(className,"CNetObjPlane")) {
		//class is a plane...
		unsigned int thisAddress = modelHashToAddress(hash);
		if (thisAddress > 0x10000) {
			unsigned int thisType = *(volatile unsigned int*)(thisAddress+0x1B8);
			if (thisType != 1)
				callOriginal = false;
		}
	}

	if (strstr(className,"CNetObjHeli")) {
		//class is a heli...
		unsigned int thisAddress = modelHashToAddress(hash);
		if (thisAddress > 0x10000) {
			unsigned int thisType = *(volatile unsigned int*)(thisAddress+0x1B8);
			if (thisType != 6) {
				callOriginal = false;
			}
		}
	}
	//printf("Reccursion value: %i call: %i\n",reccursionValue,callOriginal);
	//call it
	if (reccursionValue > 1) {
		printf("OMG! Reccursion greater than 1\n");
		PatchInJumpAddr(0x136D334,(int)updateCNetObjData_detour,false);
		return 0;
	}
	unsigned int retvalue = 0;
	if (callOriginal)
		retvalue = updateCNetObjData(r3_CAutomobileSyncTree,r4_CNetObjAutomobile);
	else
		printf("Improper! %s\n",className);
	reccursionValue = 0;
	//repatch it
	PatchInJumpAddr(0x136D334,(int)updateCNetObjData_detour,false);
	return retvalue;
}

void updateCNetObjData_detour_start() {
	memcpy(updateCNetObjData_data,(void*)0x136D334,4*4);
	PatchInJumpAddr(0x136D334,(int)updateCNetObjData_detour,false);
}
*/


/*
at 133D6EC CNetworkObjectMgrSyncer:

unsigned int r4_CNetObjAutomobile = sub_A08900(r3_CNetworkObjectMgr,r7_unk,r4_CNetGamePlayer,1);
if (r4_CNetObjAutomobile == 0)
	r4_CNetObjAutomobile = sub_9F8C38(r3_CNetworkObjectMgr,r7_unk,1);
if (r4_CNetObjAutomobile == 0)
	return;//there is no automobile to check

unsigned int r3_CAutomobileSyncTree = getCAutomobileSyncTreeFromCNetObjAutomobile(r4_CNetObjAutomobile);

if (CNetObjAutomobile_freezecheck(r3_CAutomobileSyncTree,r4_CNetObjAutomobile) == true) {
	printf("\n\n\n\n\n\nFREEZE OBJECT!\n\n\n\n\n\n\n");
	return;
}

*/

/*
maybe if I check getEntityFromIndex and return 0 if it is a bad object...
*/
/*
struct N4rage18CNetworkSyncDataULILj18EEE {
	unsigned int classData;
	char data[24*4];
};

struct CNetObj {//size 0x450
	unsigned int classData;//0x0
	unsigned int unk1;//0x4
	N4rage18CNetworkSyncDataULILj18EEE sync;//0x8
	//class2 ;//0x6C
};*/
/*
opd_s sub_133BBAC_t = {0x133BBAC,TOC};
void (*sub_133BBAC)(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int r6, unsigned int r7, unsigned int r8, unsigned int r9) = (void(*)(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int))&sub_133BBAC_t;

//133BE34 createCNetObj

void createCNetObj_reverse(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int r6, unsigned int r7, unsigned int r8, unsigned int r9) {
	printf("Created CNetObj\n");
	unsigned int CNetObj = r3;
	sub_133BBAC(r3,r4,r5,r6,r7,r8,r9);
	unsigned int unk_1936528 = 0x1936528;
	r3 = 0x1936528;
	r4 = r3 + 8;
	r5 = r3 + 0x3FC;
	r6 = r3 + 0x380;
	r7 = r3 + 0x44C;
	*(volatile unsigned int*)(CNetObj+0x0) = r4;
	r8 = r3 + 0x3E4;
	r4 = r3 + 0x3BC;
	*(volatile unsigned int*)(CNetObj+0xDC) = r5;
	*(volatile unsigned int*)(CNetObj+0x6C) = r6;
	r3 = r3 + 0x4C4;
	*(volatile unsigned int*)(CNetObj+0x170) = r7;
	*(volatile unsigned int*)(CNetObj+0x84) = r4;
	*(volatile unsigned int*)(CNetObj+0xD0) = r8;
	*(volatile unsigned int*)(CNetObj+0x42C) = r3;
	//fixCNetObj(CNetObj);//need to make it not use the shit
}*/
/*
void createCNetObj_reverse_start() {
	//*(volatile unsigned int*)0x13BBF90 = 0x4E800020;
	PatchInJumpAddr(0x133BE34,(int)createCNetObj_reverse,false);
}*/

opd_s processHelicopterShit_t = {0x13BBF90,TOC};
void(*processHelicopterShit)(unsigned int r3_CNetObjHeli) = (void(*)(unsigned int))&processHelicopterShit_t;
opd_s helicopterSpawnWhenClose_t = {0x13BC154,TOC};
void(*helicopterSpawnWhenClose)(unsigned int r3_CNetObjHeli) = (void(*)(unsigned int))&helicopterSpawnWhenClose_t;

bool spoofOnShortRange = true;

void processHelicopterShit_detour(unsigned int r3_CNetObjHeli) {
	bool isGoingToFreezeMe = fixCNetObjWithModel(r3_CNetObjHeli,spoofOnShortRange);
	if (isGoingToFreezeMe) {
		//printf("\n\n[process] Freeze imminent!\n\n\n");
		*(volatile unsigned int*)0x353DA0 = 0x4E800020;//This one has code in it that will freeze you but blr'ing it doesn't seem to make any difference at all except in prologue some things didn't render
		*(volatile unsigned int*)0x134AB10 = 0x4E800020;
		//far freeze next froze here: 0x0167A4D4
	} else {
		processHelicopterShit(r3_CNetObjHeli);//froze when calling this when the freeze is done close by
	}
	//printf("[process] After\n");
}

void helicopterSpawnWhenClose_detour(unsigned int r3_CNetObjHeli) {
	bool isGoingToFreezeMe = fixCNetObjWithModel(r3_CNetObjHeli,false);
	if (isGoingToFreezeMe) {
		//printf("\n\n[spawn] Freeze imminent!\n\n\n");
		spoofOnShortRange = true;
	} else {
		spoofOnShortRange = true;
	}
	helicopterSpawnWhenClose(r3_CNetObjHeli);//must be called or freeze
	//printf("[spawn] After\n");
	//froze here 0x0036865C next and by noping all the functions associated with this you can unfreeze (but it makes your body go all floaty lol)
}

void processHelicopterShit_patch() {
	/**(volatile unsigned int*)(0x1C728E0+0x0) = *(volatile unsigned int*)((unsigned int)processHelicopterShit_detour + 0x0);
	*(volatile unsigned int*)(0x1C728E0+0x4) = *(volatile unsigned int*)((unsigned int)processHelicopterShit_detour + 0x4);
	*(volatile unsigned int*)(0x1C728E8+0x0) = *(volatile unsigned int*)((unsigned int)helicopterSpawnWhenClose_detour + 0x0);
	*(volatile unsigned int*)(0x1C728E8+0x4) = *(volatile unsigned int*)((unsigned int)helicopterSpawnWhenClose_detour + 0x4);*/
	CNetworkObjectMgrSyncer_detour_start();
}
#endif

/*


Freeze console when close:
r0=00000000D003DBA0        r8=0000000000000001       r16=0000000001877D68       r24=0000000000000004
r1=00000000D003DB10        r9=0000000000000000       r17=0000000000000000       r25=000000000183D654
r2=0000000001C85330       r10=800000000000E80C       r18=0000000000000000       r26=0000000000000004
r3=00000000D003DB80       r11=0000000000000000       r19=0000000000000001       r27=0000000000000001
r4=0000000000000000       r12=80000000003E7580       r20=0000000000000000       r28=0000000000000008
r5=00000000013D73D8       r13=0000000010007060       r21=0000000040044000       r29=00000000401189A0
r6=0000000000001D30       r14=0000000000000001       r22=000000000000010F       r30=0000000000000000
r7=0000000000000000       r15=0000000000307436       r23=000000000222DE70       r31=00000000401189A0

cr=44000042     xer=0000000000000000        ctr=00000000013D73D8        lr=0000000000A1D194       fpscr=AEB04500

pc=00000000013D73DC            lwz  r5,0x1C(r4)


Function             
Unknown  0x013D7310
Unknown  0x00A1D164
Unknown  0x013BC15C  helicopterFreezeAnotherLol
Unknown  0x00A12898  maybe try blring this NOPE didn't work
Unknown  0x01339678
???  0x0133CFC4
Unknown  0x00A081CC
Unknown  0x00A08490
Unknown  0x00A09798
Unknown  0x0160DADC
Unknown  0x00A15C2C
Unknown  0x00D1407C
Unknown  0x00D14188
Unknown  0x00D14264
Unknown  0x00D14B30
Unknown  0x012F2EE0
Unknown  0x0150E570
Unknown  0x01667424
Unknown  0x01667538
Unknown  0x00A64720
Unknown  0x00026580
Unknown  0x00035790
Unknown  0x00A61698
Unknown  0x000104C4
Unknown  0x00AE7FA0
Unknown  0x00010494
Unknown  0x00010C54
Unknown  0x00010B40


freeze console when far away:

r0=0000000000EDF9F0        r8=0000000000000020       r16=0000000000000000       r24=000000000000006C
r1=00000000D003E250        r9=0000000000000190       r17=0000000000000000       r25=0000000001EA3B64
r2=0000000001C85330       r10=000000000000BF57       r18=0000000000000000       r26=0000000000000000
r3=0000000040ABC710       r11=FFFFFFFFFFFFFFFF       r19=0000000000000000       r27=0000000040ABCDB0
r4=00000000447A0000       r12=00000000D003E268       r20=0000000000000000       r28=0000000040ABC710
r5=000000000217E1CC       r13=0000000010007060       r21=0000000000000000       r29=0000000000000008
r6=0000000000000000       r14=0000000000000000       r22=0000000000000000       r30=00000000447A0000
r7=0000000000000000       r15=0000000000000000       r23=0000000000000000       r31=00000000311A29A0

cr=48000048     xer=0000000000000000        ctr=00000000013B9140        lr=0000000000EDF650       fpscr=BEB04500

pc=0000000000EDF664            lwz  r4,0x12C(r30)




Function             
Unknown  0x00EDF650
Unknown  0x00EDF650
Unknown  0x013BBF98
Unknown  0x00368528
Unknown  0x009DDDDC
Unknown  0x009DDF0C
Unknown  0x00368B80
Unknown  0x00380A14
Unknown  0x01667424
Unknown  0x01667538
Unknown  0x00A64720
Unknown  0x00026580
Unknown  0x00035790
Unknown  0x00A61698
Unknown  0x000104C4
Unknown  0x00AE7FA0
Unknown  0x00010494
Unknown  0x00010C54
Unknown  0x00010B40



*/

/*
admin kick protection:
search value: 0x0x84643284
*(volatile int*)0x830C8F2C = NOP;//Admin Kick Protection



sub_1760210 entity


void FreezeCarImport(){
	WriteBytes(0x13BF800, ON, 4);

}

void FreezeCarDefault(){
	WriteBytes(0x13BF800, OFF, 4);
}


*/



/*
intercept here:
0x1767C8C where r4 is cnetobjheli
next freeze here: 0x0167A4D4 then 0x0156802C and nop both and it unfroze

*/
bool EVENT_HANDLE_DEFAULT(CNetGamePlayer *sender, CNetGamePlayer *receiver, eventArgumentData *eventData) {
	return false;
}

bool disableAllScriptEvents = false;
bool disableModderScriptEvents = true;
bool moneyProtection = true;
//bool teleportProtectionEnabled = true;
//char scriptEventDialogText[100];
bool SCRIPTED_GAME_EVENT_HANDLE(CNetGamePlayer *sender, CNetGamePlayer *receiver, eventArgumentData *eventData) {
	//	unsigned int addressOfArgs = *(volatile unsigned int*)r3 + 0x4;  //r3+10*0x4;  there is an unknown value for the first arg in the list
	unsigned int *args = eventData->getArr(0x4);
	unsigned int argCount = eventData->getUInt(0)/4;
	char *senderName =sender->playerInfo->name;
	int senderPlayerId = sender->nonPhysicalPlayerData->playerIndex;
	//printf("Got scripted game event: %s event id: %i, player: %i, args: %i %i %i %i\n",senderName,args[0],args[1],args[2],args[3],args[4],args[5]);

	char* scriptEventDialogText = global_temporary_buf;

	if (args[0] == 0x2/* && *(volatile int*)(addressOfArgs+0x4) == PLAYER::PLAYER_ID()*/ && args[2] == 0x35) {
		//this is kick player
		snprintf$(scriptEventDialogText,100,"%s tried to kick you!",senderName);
		modifiedPlayerEbootsArray[sender->nonPhysicalPlayerData->playerIndex] = true;
		print2(scriptEventDialogText,5000);
		//return 0;
		args[0] = 0;
		disableAllScriptEvents = true;
	}
	if (args[0] == 0x2/* && *(volatile int*)(addressOfArgs+0x4) == PLAYER::PLAYER_ID()*/ && args[2] == 0x34) {
		//this is fake leave
		snprintf$(scriptEventDialogText,100,"%s tried to make you fake leave!",senderName);
		modifiedPlayerEbootsArray[sender->nonPhysicalPlayerData->playerIndex] = true;
		print2(scriptEventDialogText,5000);
		//return 0;
		args[0] = 0;
		disableAllScriptEvents = true;
	}
	if (args[0] == 0x2/* && *(volatile int*)(addressOfArgs+0x4) == PLAYER::PLAYER_ID()*/ && args[2] == 0x2e) {
		//this is reset view
		snprintf$(scriptEventDialogText,100,"%s tried to reset your view!",senderName);
		modifiedPlayerEbootsArray[sender->nonPhysicalPlayerData->playerIndex] = true;
		print2(scriptEventDialogText,5000);
		//return 0;
		args[0] = 0;
		disableAllScriptEvents = true;
	}
	if (args[0] == 0xD8) {
		//this is give rp
		snprintf$(scriptEventDialogText,100,"%s tried to give you %i rp!",senderName,args[2]);
		modifiedPlayerEbootsArray[sender->nonPhysicalPlayerData->playerIndex] = true;
		print2(scriptEventDialogText,5000);
		//*(volatile int*)(addressOfArgs+0x8) = 0;//rp amount
		args[0] = 0;
		//return 0;
		disableAllScriptEvents = true;
	}

	if (args[0] == 0xDA || args[0] == 0xDB /*219*/) {
		//this is money
		if (moneyProtection) {
			//Write_Global(262145+4812,0);//set the amount to zero instead of returning
			snprintf$(scriptEventDialogText,100,"%s tried to give you money with money protection enabled!",senderName);
			modifiedPlayerEbootsArray[sender->nonPhysicalPlayerData->playerIndex] = true;
			print2(scriptEventDialogText,2000);
			//return 0;
			args[0] = 0;
			disableAllScriptEvents = true;
		} else {
			//Write_Global(262145+4812,20000);
		}
	}
	if (args[0] == 312) {
		args[0] = 0;//this is pay hospital bill
		snprintf$(scriptEventDialogText,100,"%s tried to make u pay hospital bill!",senderName);
		print2(scriptEventDialogText,2000);
		//IlIlITeslaIlIlI event id: 312, player: 0, args: 1000000 0 1614467072 17
	}
	if (args[0] == 203) {
		//give off radar? idk but it causes me to fake leave
	}

	
	if (args[0] == 202) {//v1
		//print2("a");
		disableAllScriptEvents = true;
	}
	if (args[0] == 66) {//v2
		//print2("b");
		disableAllScriptEvents = true;
	}
	if (args[0] == 318) {//v3
		//print2("c");
		disableAllScriptEvents = true;
	}
	if (args[0] == 20) {//v4
		//print2("d");
		disableAllScriptEvents = true;
	}
	if (args[0] == 328) {//echoStartValueOfIt
		//print2("e");
		disableAllScriptEvents = true;
	}
	if (args[0] == 290) {//v6
		//print2("f");
		//this one actually got called normally one time idk why lol but I do need to block it cuz it is v6
		disableAllScriptEvents = true;
	}
	if (args[0] == 317) {//v5
		//print2("g");
		disableAllScriptEvents = true;
	}


	//weather event crash
	if (args[0] == 16) {//crashScriptHost
		disableAllScriptEvents = true;
	}

	if (args[0] == 0x16C) {
		//this is apartment
		snprintf$(scriptEventDialogText,100,"%s tried to force you into their apartment!",senderName);
		print2(scriptEventDialogText,5000);
		//return 0;
		args[0] = 0;
		disableAllScriptEvents = true;
	}
	if (args[0] == 55) {
		snprintf$(scriptEventDialogText,100,"%s tried to kick you from your car!",senderName);
		print2(scriptEventDialogText,5000);
		args[0] = 0;
		//don't disable all script events. I feel that this one is used when they remove u from car non-modder
	}
	if (args[0] == 0x3) {
		if (args[2] == 0x14) {
			//multiplayer intro
			snprintf$(scriptEventDialogText,100,"%s tried to force you into multiplayer intro cutscene!",senderName);
			modifiedPlayerEbootsArray[sender->nonPhysicalPlayerData->playerIndex] = true;
			print2(scriptEventDialogText,5000);
			args[0] = 0;
			disableAllScriptEvents = true;
		}
		if (args[2] == 0x3A) {
			//flight school
			snprintf$(scriptEventDialogText,100,"%s tried to force you into multiplayer intro flight school!",senderName);
			modifiedPlayerEbootsArray[sender->nonPhysicalPlayerData->playerIndex] = true;
			print2(scriptEventDialogText,5000);
			args[0] = 0;
			disableAllScriptEvents = true;
		}
		if (args[2] == 0x37 || args[2] == 0x36 || args[2] == 0x35 || args[2] == 0x38/*freeze one*/ ) {
			//this is job
			snprintf$(scriptEventDialogText,100,"%s tried to force you to join a job!",senderName);
			modifiedPlayerEbootsArray[sender->nonPhysicalPlayerData->playerIndex] = true;
			print2(scriptEventDialogText,5000);
			//return 0;
			args[0] = 0;
			disableAllScriptEvents = true;
		}
	}
	/*if (args[0] = 150) {
		if ((args[2] == 255 && args[3] == 255) || (args[3] == 88)) {
			snprintf$(scriptEventDialogText,100,"%s tried to fake leave you!",senderName);//this is actually stats
			print2(scriptEventDialogText,5000);
			//return 0;
			args[0] = 0;
			disableAllScriptEvents = true;
		}
	}*/
	if (args[0] != 2027)//this is the one I know I need to receive, so don't wanna calcel this one on accident
	{
		if (disableAllScriptEvents)
			args[0] = 0;//just disable them completely the game functions fine without them
		if (modifiedPlayerEbootsArray[sender->nonPhysicalPlayerData->playerIndex] == true) {
			if (disableModderScriptEvents) {
				args[0] = 0;
			}
		}
	}
	return true;
}
bool NETWORK_INCREMENT_STAT_EVENT_HANDLE(CNetGamePlayer *sender, CNetGamePlayer *receiver, eventArgumentData *eventData) {
	char *senderName = sender->playerInfo->name;
	int senderPlayerId = sender->nonPhysicalPlayerData->playerIndex;

	unsigned int *statHash = eventData->getpUInt(0);
	int *statValue = eventData->getpInt(1);
	char* scriptEventDialogText = global_temporary_buf;
	snprintf$(scriptEventDialogText,sizeof(scriptEventDialogText),"%s tried to set stat 0x%X with value 0x%X",senderName,*statHash,*statValue);
	print2(scriptEventDialogText,5000);
	printf("%s: hash 0x%X value 0x%X %i\n",senderName,*statHash,*statValue,*statValue);
	*statHash = 0;//stat name
	*statValue = 0;//stat value
	return true;
}
bool NETWORK_REQUEST_SYNCED_SCENE_EVENT_HANDLE(CNetGamePlayer *sender, CNetGamePlayer *receiver, eventArgumentData *eventData) {
	/*printf("\nStart synced scene:\n");
	printf("Sender: %s\n",sender->playerInfo->name);
	printf("Data: ");
	for (int i = 0; i < 12; i++) {
		printf("%X ",eventData->getUInt(i));
	}
	printf("\n");*/
	return false;
}
bool GAME_WEATHER_EVENT_HANDLE(CNetGamePlayer *sender, CNetGamePlayer *receiver, eventArgumentData *eventData) {
	char *senderName = sender->playerInfo->name;
	int senderPlayerId = sender->nonPhysicalPlayerData->playerIndex;

	//snprintf$(scriptEventDialogText,sizeof(scriptEventDialogText),"%s tried to change your weather!",senderName);
	//print2(scriptEventDialogText,5000);
	//printf("%s 0x%X 0x%X 0x%X 0x%X\n",scriptEventDialogText,eventData->getUInt(0),eventData->getUInt(1),eventData->getUInt(2),eventData->getUInt(3));
	return false;//set to false to make it disabled
}
bool GAME_CLOCK_EVENT_HANDLE(CNetGamePlayer *sender, CNetGamePlayer *receiver, eventArgumentData *eventData) {
	char *senderName = sender->playerInfo->name;
	int senderPlayerId = sender->nonPhysicalPlayerData->playerIndex;

	//snprintf$(scriptEventDialogText,sizeof(scriptEventDialogText),"%s tried to change your time!",senderName);
	//print2(scriptEventDialogText,5000);
	//printf("%s 0x%X 0x%X 0x%X 0x%X\n",scriptEventDialogText,eventData->getUInt(0),eventData->getUInt(1),eventData->getUInt(2),eventData->getUInt(3));
	return false;//disable the event set to false
}

bool GIVE_PICKUP_REWARDS_EVENT_HANDLE(CNetGamePlayer* sender, CNetGamePlayer* receiver, eventArgumentData* eventData) {
	//this is for one of semjases new freezes
	char* senderName = sender->playerInfo->name;
	int senderPlayerId = sender->nonPhysicalPlayerData->playerIndex;
	//char buf[100];
	//snprintf(buf, sizeof(buf), "~r~%s tried to freeze you!");
	//print(buf);
	return false;//disable the event set to false
}

void hexticForceKick(int player);
bool KICK_VOTES_EVENT_HANDLE(CNetGamePlayer* sender, CNetGamePlayer* receiver, eventArgumentData* eventData) {
	//this is for one of semjases new freezes
	char* senderName = sender->playerInfo->name;
	int senderPlayerId = sender->nonPhysicalPlayerData->playerIndex;
	/*hexticForceKick(senderPlayerId);
	static char buf[100];
	snprintf(buf, sizeof(buf), "~r~Auto kicking %s!");
	print2(buf);*/
	return false;//disable the event set to false
}

struct EVENT_PROTECTION_STRUCT {
	bool (*func)(CNetGamePlayer *sender, CNetGamePlayer *receiver, eventArgumentData *eventData);
};
bool eventProtectionsBool[EVENT_LIST_SIZE];
EVENT_PROTECTION_STRUCT eventProtectionsFunctions[EVENT_LIST_SIZE];
void initEventProtectionsFunctions() {
	//initiate all with default handle
	for (int i = EVENT_LIST_SIZE-1; i >= 0; i--) {
		eventProtectionsFunctions[i].func = EVENT_HANDLE_DEFAULT;
	}
	//set out few special ones
	eventProtectionsFunctions[SCRIPTED_GAME_EVENT].func = SCRIPTED_GAME_EVENT_HANDLE;
	eventProtectionsFunctions[NETWORK_INCREMENT_STAT_EVENT].func = NETWORK_INCREMENT_STAT_EVENT_HANDLE;
	eventProtectionsFunctions[NETWORK_REQUEST_SYNCED_SCENE_EVENT].func = NETWORK_REQUEST_SYNCED_SCENE_EVENT_HANDLE;
	eventProtectionsFunctions[GAME_WEATHER_EVENT].func = GAME_WEATHER_EVENT_HANDLE;
	eventProtectionsFunctions[GAME_CLOCK_EVENT].func = GAME_CLOCK_EVENT_HANDLE;
	eventProtectionsFunctions[GIVE_PICKUP_REWARDS_EVENT].func = GIVE_PICKUP_REWARDS_EVENT_HANDLE;
	eventProtectionsFunctions[KICK_VOTES_EVENT].func = KICK_VOTES_EVENT_HANDLE;

	//set some to be on by default
	eventProtectionsBool[SCRIPTED_GAME_EVENT] = true;
	eventProtectionsBool[NETWORK_INCREMENT_STAT_EVENT] = true;
	eventProtectionsBool[REPORT_CASH_SPAWN_EVENT] = true;
	eventProtectionsBool[NETWORK_PTFX_EVENT] = true;
	eventProtectionsBool[KICK_VOTES_EVENT] = true;
	eventProtectionsBool[NETWORK_CLEAR_PED_TASKS_EVENT] = true;
	eventProtectionsBool[NETWORK_REQUEST_SYNCED_SCENE_EVENT] = true;
	//eventProtectionsBool[NETWORK_START_SYNCED_SCENE_EVENT] = true;
	//eventProtectionsBool[NETWORK_UPDATE_SYNCED_SCENE_EVENT] = true;
	//eventProtectionsBool[NETWORK_STOP_SYNCED_SCENE_EVENT] = true;
	eventProtectionsBool[REQUEST_CONTROL_EVENT] = true;//dis for when other people request control of your shit
	eventProtectionsBool[REMOVE_WEAPON_EVENT] = true;
	eventProtectionsBool[REMOVE_ALL_WEAPONS_EVENT] = true;
	eventProtectionsBool[EXPLOSION_EVENT] = true;
	eventProtectionsBool[START_PROJECTILE_EVENT] = true;
	eventProtectionsBool[ALTER_WANTED_LEVEL_EVENT] = true;
	eventProtectionsBool[GAME_WEATHER_EVENT] = true;
	eventProtectionsBool[GAME_CLOCK_EVENT] = true;
	eventProtectionsBool[NETWORK_SPECIAL_FIRE_EQUIPPED_WEAPON] = true;//block the weapon freeze? This was freeze on joiin from guy
	eventProtectionsBool[GIVE_PICKUP_REWARDS_EVENT] = true;//block the new semjases freeze
}
/*
default enable:
SCRIPTED_GAME_EVENT
REQUEST_CONTROL_EVENT
GIVE_CONTROL_EVENT
NETWORK_PTFX_EVENT
*/
bool handleEvent(CNetGamePlayer *sender, CNetGamePlayer *receiver, unsigned int eventID, eventArgumentInfo *eventInfo) {
	//printf("eventInfo: 0x%X\n",(unsigned int)eventInfo);
	//eventArgumentData *eventData = eventInfo->args;
	if (eventProtectionsBool[eventID]) {
		return eventProtectionsFunctions[eventID].func(sender,receiver,eventInfo->data);//eventInfo->data ain't correct...
	}
	return true;
}






//A033F4 eventHandler
unsigned int eventHandlerData[4];
unsigned int eventHandlerDataPatch[4];
/*unsigned int eventHandlerSaveStub(unsigned long long r3, unsigned long long r4, unsigned long long r5, unsigned long long r6, unsigned long long r7, unsigned long long r8, unsigned long long r9, unsigned long long r10) {
	unsigned int a = r4;
	unsigned int c = a * r3;
	unsigned int d = *(volatile unsigned int*)c;
	__asm("li %r3, 0x3");
	__asm("li %r3, 0x3");
	__asm("li %r3, 0x3");
	__asm("li %r3, 0x3");
	__asm("li %r3, 0x3");
	__asm("li %r3, 0x3");
	__asm("li %r3, 0x3");
	__asm("li %r3, 0x3");
	__asm("li %r3, 0x3");
	__asm("li %r3, 0x3");
	__asm("li %r3, 0x3");
	return d;
}*/
/*__ALWAYS_INLINE unsigned int getBranchToAddress() {

}
__ALWAYS_INLINE unsigned int getEventID() {
	__asm__("mr %r3, %r28");
}
__ALWAYS_INLINE unsigned int getR25() {
	__asm__("mr %r3, %r25");
}*/

/*opd_s sub_A021CC_t = {0xA021CC,TOC};
ui64 (*sub_A021CC)(ui64 r3, ui64 r4) = (ui64(*)(ui64,ui64))&sub_A021CC_t;
void eventHandler(ui64 r3, ui64 r4, ui64 r5, ui64 r6, ui64 r7, ui64 r8, ui64 r9, ui64 r10) {
	unsigned char eventID = r6;
	if (eventID >= 0x5A)
		return;
	sub_A021CC(r3,eventID);
	if (*(char*)(r4+0x29) == 0xFF) {
		//Player does not have a valid physical p...
		//todo
		return;
	}
	if (   *(volatile unsigned int*)(*(volatile unsigned int*)(0x1CC4A34)+0x8C) == r5) {
		//do more checks i.e continue on to 0xA0348C
		//idk all the code inside this check. ignore

	}

	//0xA034FC starts here

}*/
opd_s eventHandler_t = {0xA033F4,TOC};
void(*eventHandler)(unsigned long long r3, unsigned long long r4, unsigned long long r5, unsigned long long r6, unsigned long long r7, unsigned long long r8, unsigned long long r9, unsigned long long r10) = (void(*)(unsigned long long, unsigned long long, unsigned long long, unsigned long long, unsigned long long, unsigned long long, unsigned long long, unsigned long long))&eventHandler_t;
unsigned int getAddressFromEventIndex(unsigned int eventID, unsigned int r25) {
	unsigned int val1 = (eventID<<2) + r25 + 0x13AD4;
	//now we are starting at line 0xA03514
	unsigned int opdPTR = *(volatile unsigned int*)val1;
	if (val1 != 0) {
		return *(volatile unsigned int*)opdPTR;//this should always hit
	}
	return 0;//this should never hit
}
__attribute__((noinline)) void eventHandlerDetour(/*unsigned long long zero, */unsigned long long r3, unsigned long long r4, unsigned long long r5, unsigned long long r6, unsigned long long r7, unsigned long long r8, unsigned long long r25Val, unsigned long long eventID) {
	//printf("EventID: 0x%X\nr25: 0x%X\n",eventID,r25Val);
	volatile unsigned int eventAddress = getAddressFromEventIndex(eventID,r25Val);
	//printf("event address: 0x%X\n\n",eventAddress);
	opd_s eventFunc_t = {eventAddress,TOC};
	void(*eventFunc)(ui64 r3, ui64 r4, ui64 r5, ui64 r6, ui64 r7, ui64 r8) = (void(*)(ui64,ui64,ui64,ui64,ui64,ui64))&eventFunc_t;
	if (eventAddress != 0) {
		eventArgumentInfo *eventInfo = (eventArgumentInfo*)r3;
		CNetGamePlayer *sender = (CNetGamePlayer*)r4;
		CNetGamePlayer *receiver = (CNetGamePlayer*)r5;
		bool shouldCall = handleEvent(sender,receiver,eventID,eventInfo);
		if (shouldCall) {
			//printf("Calling: 0x%X\n",eventAddress);//eventAddress is correct here...
			eventFunc(r3,r4,r5,r6,r7,r8);//crashes on this
		}
	}
}


__attribute__((naked)) void eventHandlerPatchDetour(unsigned long long r3, unsigned long long r4, unsigned long long r5, unsigned long long r6, unsigned long long r7, unsigned long long r8, unsigned long long r9, unsigned long long r10) {
	//unsigned long long  values[2];
	//DO NOT EVER MODIFY THIS FUNCTION OR THE REGISTERS MAY MESS UP. THEY CHANGE WHENEVER THEY PLEASE LOL
	//this is what it looks like and should stay looking like in ida: https://pastebin.com/mp678yQL
	/*static int recurringCall = 0;
	if (recurringCall > 0) 
		return;
	recurringCall++;*/
	
	//NEED TO MOVE r31 INTO r5 BECAUSE THAT PART OF THE CODE WAS OVERRITTEN
	//__asm__("mr %r3, %r31");
	/*__asm("lis       %r11, A0");
	__asm("addic     %r11, %r11, A0");
	__asm("addc      %r11, %r1, %r11");
	__asm("std       r3, 0(%r11)");*/
	//but we can simplify it because r11 is only used once in the compiler for some reason:
	//__asm("nop");

	/*
	__asm("std       %r31, 0(%r11)");//so this moved r31 into r3 :)
	//__asm("nop");
	//__asm__("mr %r28, %r10");//r10 isn't actually an argument so we can overrite it
	//the last stored variable is r10 so we can easily just overrite that the wayy it does
	__asm("std       %r28, 0(%r3)");//puts r28 into r10
	//__asm("nop");
	//I also need r25 for the calculation of the address to branch to...
	//store r25 in r9 (cuz r9 isn't used)... r9 is D0
	__asm("lis       %r11, 0");
	__asm("addic     %r11, %r11, 0xE0");//used to be D0 but changed to E0 idk why
	__asm("addc      %r11, %r1, %r11");
	__asm("std       %r25, 0(%r11)");//stores r25 into r9
	//__asm("nop");

	*/
	
	//r9 = r25Val
	//r10 = eventID (which is in r28)
	//the zero should force it to put it into local vars I think
	/*__asm("nop");
	__asm("mr %r9, %r25");
	__asm("mr %r10, %r28");
	__asm("mr %r30, %r25");
	__asm("mr %r31, %r28");
	__asm("nop");*/

	/*\
	this would work if I nopped the 2 codes right after the segment
	__asm("nop");
	//__asm("mr %r9, %r25");
	//__asm("mr %r10, %r28");
	__asm("ld %r9, 0x78(%r1)");//r25 into r9
	__asm("ld %r10, 0x90(%r1)");//r28 into r10
	__asm("nop");
	values[0] = r9;
	values[1] = r10;*/
	//__asm("std %r25, 0x70(%r1)");
	//__asm("std %r28, 0x78(%r1)");
	//r9 = values[0];//arg_70 which is r25
	//r10 = values[1];//arg_78 which is r28


	//store link register
	__asm("stdu %r1, -0xB0(%r1)");
	__asm("mflr %r0");
	__asm("std %r0, 0xC0(%r1)");

	//actual fucking code
	__asm("mr %r9, %r25");
	__asm("mr %r10, %r28");
	__asm("mr %r3, %r31");
	__asm("bl ._Z18eventHandlerDetouryyyyyyyy");

	//retreive link register
	__asm("ld %r0, 0xC0(%r1)");
	__asm("mtlr %r0");
	__asm("addi %r1, %r1, 0xB0");
	__asm("blr");


	//eventHandlerDetour(r3,r4,r5,r6,r7,r8,r9,r10);//so these are all correct
	//unsigned int eventID = r10;
	//printf("r3: 0x%X\nr10: 0x%X\n\n",(unsigned int)r3,r10);
	//eventID is stored in r28
	
	
	/*char localData[4*30];
	__asm ("mov 0(localData), %r3");*/
	
	/**(volatile unsigned int*)(0xA033F4+0x0) = eventHandlerData[0];
	*(volatile unsigned int*)(0xA033F4+0x4) = eventHandlerData[1];
	*(volatile unsigned int*)(0xA033F4+0x8) = eventHandlerData[2];
	*(volatile unsigned int*)(0xA033F4+0xC) = eventHandlerData[3];*/
	//memcpy((void*)0xA033F4,eventHandlerData,4*4);

	//unsigned int eventID = r6;
	//printf("Event ID: 0x%X\n",eventID);
	//eventArgumentInfo *eventInfo = (eventArgumentInfo*)r10;//was r10 previously
	//printf("Event Info: 0x%X\n",r10);
	//CNetGamePlayer *sender = (CNetGamePlayer*)r4;//CNetGamePlayer
	//CNetGamePlayer *receiver = (CNetGamePlayer*)r5;//CNetGamePlayer
	//bool shouldCall = handleEvent(sender,receiver,eventID,eventInfo);
	//if (shouldCall) {

		//eventHandler(r3,r4,r5,r6,r7,r8,r9,r10);
		//recurringCall = 0;
		//eventHandlerSaveStub(r3,r4,r5,r6,r7,r8,r9,r10);
	//}

	/**(volatile unsigned int*)(0xA033F4+0x0) = eventHandlerDataPatch[0];
	*(volatile unsigned int*)(0xA033F4+0x4) = eventHandlerDataPatch[1];
	*(volatile unsigned int*)(0xA033F4+0x8) = eventHandlerDataPatch[2];
	*(volatile unsigned int*)(0xA033F4+0xC) = eventHandlerDataPatch[3];*/
	//memcpy((void*)0xA033F4,eventHandlerDataPatch,4*4);
	//printf("Done from in the hook\n");
}

//#define __stw( a, offset, p ) __extension__ ({ __asm__(  "stw %0, %1( %2 )" : : "r"( a ), "I"( offset ), "b"( p ) : "memory" ); })
void patchEventHandlerToPreserver28() {
	//this function makes it so at 0xA0356C r28 is not changed so r28 will contain the event ID
	*(volatile unsigned int*)0xA03510 = 0x7CC32814;
	*(volatile unsigned int*)0xA03514 = 0x80C60000;
	*(volatile unsigned int*)0xA03518 = 0x2C060000;
	*(volatile unsigned int*)0xA0354C = 0x81260000;
	//unsigned int var = 0;
	//__asm__(  "stw %r28, 0( %0 )" : "b"( var )  );
}

void makeEventHandlerGoToMyDetour() {
	unsigned int Destination = *(volatile unsigned int*)((unsigned int)eventHandlerPatchDetour);//read address from opd struct

	unsigned int lisr11 = (0x3D600000) + ((Destination >> 16) & 0xFFFF);			// lis %r11, dest>>16
	if (Destination & 0x8000)											// if bit 16 is 1...
		lisr11 += 1;
	unsigned int addi = (0x396B0000) + (Destination & 0xFFFF);					// addi %r11, %r11, dest&OxFFFF
	unsigned int mtctrr11 = (0x7D6903A6);											// mtctr %r11
	
	*(volatile unsigned int*)0xA0354C = lisr11;
	*(volatile unsigned int*)0xA03550 = addi;//this overrites the code that moves r31 into r3 so we gotta fix that at the top of the func later
	*(volatile unsigned int*)0xA03558 = mtctrr11;
}

void eventHandlerDetourStart() {
	initEventProtectionsFunctions();
	//printf("Done init\n");
	patchEventHandlerToPreserver28();
	makeEventHandlerGoToMyDetour();
	//*(volatile unsigned int*)0xA0348C = 0x480000E4;//fix the stupid freeze
	//memcpy(eventHandlerData,(void*)0xA033F4,4*4);
	//PatchInJumpAddr(0xA033F4,(int)eventHandlerDetour,false);
	//memcpy(eventHandlerDataPatch,(void*)0xA033F4,4*4);
	//hookFunctionStart(0xA033F4,(int)eventHandlerSaveStub,(int)eventHandlerDetour);
	//printf("done hook\n");
}

/*
this turns to 0 when I turn off badsport
return Global_1581767[uParam0 <306>].imm_178.imm_52;

int func_1701(var uParam0)
{
	var uVar0;
	var uVar1;
	
	uVar0 = uParam0;
	if (stat_get_bool(uVar0, &uVar1, -1))
	{
		return uVar1;
	}
	return 0;
}
Global_1581767[uVar0 <306>].imm_178.imm_52 = func_1701(-2044554322);

*/

/*
admin kick:
https://github.com/citizenfx/fivem/blob/master/data/client/citizen/common/data/ui/pausemenu.xml
RemoteIsRockstarDev
//places 0x171 is used:
//some spots above this too
16718C                 stb       r31, 0x171(r5)
71234C                 stb       r29, 0x171(r31) # rockstar dev
714928                 stb       r3, 0x171(r30)
071864C                 lbz       r3, 0x171(r31)
718684                 stb       r3, 0x171(r31)
718698                 stb       r30, 0x171(r31)
9C0ACC                 stb       r4, 0x171(r3)
BFE1F8                 stb       r30, 0x171(r31)
1057F24                 stb       r3, 0x171(r30)
010583F4                 stb       r19, 0x171(r24)
1059CE4                 stb       r3, 0x171(r4)
105AE28                 stb       r24, 0x171(r23)
010CE4A0                 stb       r3, 0x171(r31)
10CE4BC                 stb       r29, 0x171(r31)
10F5D98                 lbz       r3, 0x171(r29)
10F5DB0                 lbz       r3, 0x171(r29)
10F988C                 lbz       r3, 0x171(r30)
10F98A8                 lbz       r3, 0x171(r30)
10FA07C                 lbz       r3, 0x171(r28)
10FA094                 lbz       r3, 0x171(r28)
010FA7A0                 lbz       r3, 0x171(r30)
133EC38                 stb       r29, 0x171(r30)
133F1BC                 stb       r31, 0x171(r30)
133FCD4                 lbz       r3, 0x171(r31) //this one defo has somethng to do with dev. I set 0x133FCD0 to be 1 cuz it called often, this does set mine to be dev but unsure what else it do
133FCE8                 stb       r4, 0x171(r31)
13CB458                 stb       r3, 0x171(r30)

all stb:
16718C                 stb       r31, 0x171(r5)
71234C                 stb       r29, 0x171(r31) # rockstar dev
714928                 stb       r3, 0x171(r30)
718684                 stb       r3, 0x171(r31)  //can force this one to put 1 easily
718698                 stb       r30, 0x171(r31)  //part of the one above
9C0ACC                 stb       r4, 0x171(r3)
BFE1F8                 stb       r30, 0x171(r31)
1057F24                 stb       r3, 0x171(r30)
010583F4                 stb       r19, 0x171(r24)
1059CE4                 stb       r3, 0x171(r4)   //stored a 1 into it
105AE28                 stb       r24, 0x171(r23)
010CE4A0                 stb       r3, 0x171(r31) 
10CE4BC                 stb       r29, 0x171(r31) //set 0x10CE460 to put a 1
133EC38                 stb       r29, 0x171(r30)
133F1BC                 stb       r31, 0x171(r30)
133FCE8                 stb       r4, 0x171(r31) //this one defo has somethng to do with dev. I set 0x133FCD0 to be 1 cuz it called often, this does set mine to be dev but unsure what else it do
13CB458                 stb       r3, 0x171(r30)

//so fixes:
*(char*)(0x133FCD0+0x3) = 1;
*(char*)(0x10CE460+0x3) = 1;
*(char*)(0x71868C+0x3) = 1;
*/

int CGameScriptHandlerNetComponent__setMemorySyncPlayers_setAreaAsSyncedHost(unsigned int CGameArrayMgr, void *syncArea, unsigned int areaSize, CGameScriptHandlerNetwork *cGameScriptHandlerNetwork, unsigned char currentIndex) {
	return call<int>(0xA00234)(CGameArrayMgr,syncArea,areaSize,cGameScriptHandlerNetwork,currentIndex);
}

//these next few functions are very good
void setSyncAreaPlayers(void *area, unsigned int areaSize) {
	if (I_AM_ONLINE && VALID_ADDR(freemodeScriptCGameScriptHandlerNetwork)) {
		CGameScriptHandlerNetwork *freemode = freemodeScriptCGameScriptHandlerNetwork;
		if (VALID_ADDR(freemode->cGameScriptHandlerNetComponentSyncOne)) {
			//unsigned char val = (*(unsigned char*)(freemode->cGameScriptHandlerNetComponentSyncOne+0xAB))++;//post increment is important
			//printf("Calling with val %i\n",val);
			//CGameScriptHandlerNetComponent__setMemorySyncPlayers_setAreaAsSyncedHost(getG_CGameArrayMgr(),area,areaSize,freemode,val);
			//*(volatile int*)0xA5A514 = 0x3BA00000;//patch log part
			//host is 0xA5A4F0
			//players is 0xA5A674
			call<int>(0xA5A674)(freemode->cGameScriptHandlerNetComponentSyncOne,area,areaSize);//this crashes at 0x130D0F4 when area if already synced
			//*(volatile int*)0xA5A514 = 0x83BD0024;
			printf("Done it\n");
		} else {
			printf("Not valid cgamescripothandler\n");
		}
	} else {
		printf("yain't online\n");
	}
}

void setSyncAreaHost(void *area, unsigned int areaSize) {
	if (I_AM_ONLINE && VALID_ADDR(freemodeScriptCGameScriptHandlerNetwork)) {
		CGameScriptHandlerNetwork *freemode = freemodeScriptCGameScriptHandlerNetwork;
		if (VALID_ADDR(freemode->cGameScriptHandlerNetComponentSyncOne)) {
			//unsigned char val = (*(unsigned char*)(freemode->cGameScriptHandlerNetComponentSyncOne+0xAB))++;//post increment is important
			//printf("Calling with val %i\n",val);
			//CGameScriptHandlerNetComponent__setMemorySyncPlayers_setAreaAsSyncedHost(getG_CGameArrayMgr(),area,areaSize,freemode,val);
			//*(volatile int*)0xA5A514 = 0x3BA00000;//patch log part
			//host is 0xA5A4F0
			//players is 0xA5A674
			call<int>(0xA5A4F0)(freemode->cGameScriptHandlerNetComponentSyncOne,area,areaSize);//this crashes at 0x130D0F4 when area if already synced
			//*(volatile int*)0xA5A514 = 0x83BD0024;
			printf("Done it\n");
		} else {
			printf("Not valid cgamescripothandler\n");
		}
	} else {
		printf("yain't online\n");
	}
}

void setGlobalHostBroadcast(int global, int sizeInGlobal) {
	setSyncAreaHost((void*)Read_Global_Address(global),sizeInGlobal*4);//currently using this function it does not freeze but does not do anythinng useful
}

void setGlobalPlayerBroadcast(int global, int sizeInGlobal) {
	setSyncAreaPlayers((void*)Read_Global_Address(global),sizeInGlobal*4);//currently using this function it does not freeze but does not do anythinng useful
}

void registerGlobalHostAsArray(int global, int sizeInGlobal) {
	int syncedSize = sizeInGlobal+1;
	Write_Global(global, sizeInGlobal);
	setGlobalHostBroadcast(global,syncedSize);
}


/*
void testSnowSync() {
	if (assureHostOfFreemode()) {
		setGlobalHostBroadcast(262145+4715,2);
		Write_Global(262145+4715,1);
		print2("tried!");
	} else {
		print2("~r~failed");
	}
}*/


void overriteGlobalSync(unsigned char replaceAt) {
	//2 is array size of 223
	//3 is array size of 306
	//0xAC is synced players
	//0xAB is synced host
	unsigned char actualVal = (*(unsigned char*)(freemodeScriptCGameScriptHandlerNetwork->cGameScriptHandlerNetComponentSyncOne+0xAB));
	(*(unsigned char*)(freemodeScriptCGameScriptHandlerNetwork->cGameScriptHandlerNetComponentSyncOne+0xAB)) = replaceAt;//spoof to certain one
	//setGlobalHostBroadcast(262145+4715,1);
	//(*(unsigned char*)(freemodeScriptCGameScriptHandlerNetwork->cGameScriptHandlerNetComponentSyncOne+0xAB)) = actualVal;
}

void causeCrashLol() {
	overriteGlobalSync(2);
	overriteGlobalSync(3);
}

void callFreezeMethod() {
	if (VALID_ADDR(freemodeScriptCGameScriptHandlerNetwork)) {
		call<int>(0xA00304)(getG_CGameArrayMgr(),Read_Global_Address(262145+4715),4,freemodeScriptCGameScriptHandlerNetwork,1);
	} else {
		print2("Invalid freemode script\n");
	}
}


bool didit = true;
void registerPlayerBroadcastVariablesHookFunc() {
	//static int ptimer = 0;
	//when this function is called, shit is network safe.
	//Example: network_register_player_broadcast_variables(&Global_1581767, 5509);//306*18+1    230 is badsport
	//setAllOutOfBadsport();
	//if (GAMEPLAY::GET_GAME_TIMER()-ptimer > 1000) {
		//setGlobalAsOtherPlayers(262145+4715,1);//causing it to freeze here: 0x009FBA00
							  //1581767

	if (didit) {
		//set trap so we can see the argument
		//*(unsigned int*)0xA00428 = TRAP;
		//this line will trigger the freeze
		NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES((void*)Read_Global_Address(262145+4715),1);//doing this and messing up the order works
		
		didit = false;
		printf("injected\n");
	}

		//setGlobalAsOtherPlayers(269839,500);
		//setAllOutOfBadsport();
		//for (int i = 0; i < 500; i++)
		//	Write_Global(269839+i,1);
		/**(volatile unsigned int*)0x9FBA00 = 0x4800020C;
		*(volatile unsigned int*)0x0130D4CC = 0x60000000;
		*(volatile unsigned int*)0x0130D36C = 0x60000000;
		*(volatile unsigned int*)0x9FBBC8 = 0x60000000;
		*(volatile unsigned int*)0x9FBBCC = 0x60000000;*/
		//*(volatile unsigned int*)0x9FB8F8 = 0x4E800020;//causes globals to not update from other people
		//ptimer = GAMEPLAY::GET_GAME_TIMER();
		//printf("set %i as networked global!\n",262145+4715);
	//}
	//__asm("twu       %r1, %r1");//0x7FE10808
	//TRAP();
}

void registerPlayerBroadcastVariablesHook(unsigned int data) {
	unsigned int args = *(volatile unsigned int*)(data+0x8);
	unsigned int arg1 = *(volatile unsigned int*)args;
	unsigned int arg2 = *(volatile unsigned int*)(args+0x4);
	//printf("broadcast vars: 0x%X, 0x%X %s\n",arg1,arg2,SCRIPT::GET_THIS_SCRIPT_NAME());
	NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES((void*)arg1,arg2);
	//NETWORK::NETWORK_REGISTER_HOST_BROADCAST_VARIABLES(arg1,arg2);
	//printf("Called orig setter\n");
	registerPlayerBroadcastVariablesHookFunc();
}
void setupRegisterPlayerBroadcastVariablesHook() {
	//printf("setup player vars hook\n");
	PatchInJumpAddr(0x15891D0,(int)registerPlayerBroadcastVariablesHook,false);
	//important fix
	*(volatile unsigned int*)0x9FBA00 = 0x60000000;
	*(volatile unsigned int*)0x9FBBC8 = 0x60000000;
	*(volatile unsigned int*)0x9FBBCC = 0x60000000;
	//spam freeze fix (jk these 2 also did it):
	*(volatile unsigned int*)0x0130D36C = 0x60000000;
	*(volatile unsigned int*)0x0130D4CC = 0x60000000;
	/**(volatile unsigned int*)0x0130D0F4 = 0x60000000;*/
}
/*
opd_s IS_DLC_PRESENT_t = {0x3E3028,TOC};
bool(*IS_DLC_PRESENT)(unsigned int hash) = (bool(*)(unsigned int))&IS_DLC_PRESENT_t;
bool is_dlc_present_hook(unsigned int hash) {
	bool callOrig = false;
	if (hash == 0x96F02EE6) {
		if (strncmp(SCRIPT::GET_THIS_SCRIPT_NAME(), "maintransition", strlen("maintransition"))) {
			return true;
		} else {
			callOrig = true;
		}
	}
	if (callOrig) {

	}

	return 0;
}*/

#define shouldSpawnPeds ((bool*)0x193ECB0)
unsigned int shouldSpawnPedsp1 = 0x6A18A9D7;
#define shouldSpawnPedsP2 *(char*)(0x6B8B4567^shouldSpawnPedsp1)

void pedSpawnDetour(ui64 r3, ui64 r4) {
	r3 = r3 - 0x170;
	if (ENTITY_BLOCKER == false) {//don't do it if entity blocker is on
		if (!shouldSpawnPedsP2)
			call<int>(0x13806D0)(r3,r4);
	}
}

void setupPedSpawnDetour() {
	*(volatile unsigned int*)(0x1C71F70+0x0) = *(volatile unsigned int*)((int)pedSpawnDetour+0x0);
	*(volatile unsigned int*)(0x1C71F70+0x4) = *(volatile unsigned int*)((int)pedSpawnDetour+0x4);
}





/*
for desynced functions
create untraceable variable
#include <iostream>
#include <stdio.h>

#define address 0x1933F34
#define functionName "changeModelPlayerId"
#define type "char"

int main()
{
	srand (time(NULL));
    unsigned int key1 = rand();
    unsigned int key2 = address^key1;
    printf("#define %s_ptr ((%s*)0x%X)\n",functionName,type,address);
    printf("unsigned int %s_key = 0x%X;\n",functionName,key1);
    printf("#define %s_safe *(%s*)(0x%X^%s_key)\n",functionName,type,key2,functionName);
}


*/


unsigned int kjdsfhngkjadfskn = 0x3926A3A;//0x1945E4F is the actula val
#define shouldDoBypassSize() (*(char*)(kjdsfhngkjadfskn^0x2063475))
#define shouldBypassSize ((bool*)(0x1945E4F))
/*
want func_1474( to return 8 in freemode.c
404 = Global_1312622
*/
__ALWAYS_INLINE void setShitToBeSpectator() {
	if (!shouldDoBypassSize())
		return;
	//Write_Global(1315344+Read_Global(1312622),1);
	//printf("set shit to be spec\n");
	//printf("pid: 0x%X vs 0x%X\n",(addrstruct().getPlayerIdAddr^dataDecryptor()),0x4241D4);
	int pid = call<int>((addrstruct().getPlayerIdAddr^dataDecryptor())/*0x4241D4*/)();
	call<int>((addrstruct().setSCTVSlotsAddr^dataDecryptor())&0xFFFFFF/*0x3E4298*/)(((addrstruct().setSCTVSlotsAddr^dataDecryptor())&0xFF000000)>>(8*3)/*4*/);
	call<int>((addrstruct().setPlayerTeamAddr^dataDecryptor())&0xFFFFFF/*0x421B34*/)(pid,((addrstruct().setPlayerTeamAddr^dataDecryptor())&0xFF000000)>>(8*3)/*8*/);
	//printf("set shit to be spec finished\n");
}
//char setPlayerTeamHookBytesOrig[4*4];
//char setPlayerTeamHookBytesNew[4*4];
bool doNotUsePresence = false;
void NETWORK_SET_RICH_PRESENCE_2_hook(NativeArg_s *args) {
	//printf("Presense: %i %s\n",args->ArgValues[0].i,args->ArgValues[1].str);
	if (doNotUsePresence == false) {
		//patch the function so it doesn't use gxt2:
		*(unsigned int*)0x3EBFF0 = 0x7FC3F378;//for uunk_0x17E6777 which is used for setting what game ur playing  mr %r3, %r30
		//*(unsigned int*)0x3EC000 = 0x60000000;
		*(unsigned int*)0x3EBFD4 = 0x60000000;//check iif gtx exists patch

		args->ArgValues[1].str = "using Paradise SPRX";
		args->ArgValues[0].i = 1;
	}
	call<int>(0x3EBF30)(args->ArgValues[0].i,args->ArgValues[1].str);
}
void set_player_team_hook(/*int player, int team*/NativeArg_s *args) {
	//printf("Called set team hook\n");
	setShitToBeSpectator();
	//printf("set that shit\n");
	//int origVal = team;//args->ArgValues[1].i;
	int pid = call<int>((addrstruct().getPlayerIdAddr^dataDecryptor())/*0x4241D4*/)();
	if (args->ArgValues[0].i/*player*/ == pid) {
		//printf("Spoofed me\n");
		if (shouldDoBypassSize())
			args->ArgValues[1].i/*team*/ = ((addrstruct().setPlayerTeamAddr^dataDecryptor())&0xFF000000)>>(8*3)/*8*/;
	}
	//printf("bout to memcpy");
	//memcpy((void*)((addrstruct().setPlayerTeamAddr^dataDecryptor())&0xFFFFFF)/*0x421B34*/,setPlayerTeamHookBytesOrig,4*4);
	//printf("copied it... calling\n");
	call<int>((addrstruct().setPlayerTeamAddr^dataDecryptor())&0xFFFFFF/*0x421B34*/)(args->ArgValues[0].i,args->ArgValues[1].i);
	//printf("called it... copy again\n");
	//memcpy((void*)((addrstruct().setPlayerTeamAddr^dataDecryptor())&0xFFFFFF)/*0x421B34*/,setPlayerTeamHookBytesNew,4*4);
	//printf("Finished hook\n");
	//printf("set player %i team to %i orig %i\n",args->ArgValues[0].i,args->ArgValues[1].i,origVal);
}
__ALWAYS_INLINE void initPlayerTeamHook() {
	//memcpy(setPlayerTeamHookBytesOrig,(void*)((addrstruct().setPlayerTeamAddr^dataDecryptor())&0xFFFFFF)/*0x421B34*/,4*4);
	PatchInJumpAddr((addrstruct().setPlayerTeamAddr2^dataDecryptor())/*&0xFFFFFF*//*0x421B34*/  /*other 0x159A284*/,(int)set_player_team_hook,false);
	//memcpy(setPlayerTeamHookBytesNew,(void*)((addrstruct().setPlayerTeamAddr^dataDecryptor())&0xFFFFFF)/*0x421B34*/,4*4);
	//printf("Init the player team hook!\n");
}



int maxPlayersInLobby = 18;
void hostClosed(NativeArg_s *args) {
	//printf("host closed called, players: %i\n",args->ArgValues[1].i);
	args->ArgValues[1].i = maxPlayersInLobby;
	args->ReturnValue[0] = call<bool>(0x3E4014)(args->ArgValues[0].i,args->ArgValues[1].i);
}
void hostFriend(NativeArg_s *args) {
	//printf("host friend called, players: %i\n",args->ArgValues[1].i);
	args->ArgValues[1].i = maxPlayersInLobby;
	args->ReturnValue[0] = call<bool>(0x3E4060)(args->ArgValues[0].i,args->ArgValues[1].i);
}

__ALWAYS_INLINE void setupHookSessions() {
	PatchInJumpAddr(0x1586CBC,(int)hostClosed,false);
	PatchInJumpAddr(0x1586CF8,(int)hostFriend,false);
}
/*
void finalizeFreezeLobbyPed2(int a) {
	PED::SET_PED_RANDOM_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(),0);
	printf("Done! You are safe now",2000);
}

void finalizeFreezeLobbyPed(int a) {
	PlayerMods::changeModelNow("mp_m_freemode_01",finalizeFreezeLobbyPed2);
}

void initializeFreezeLobbyPed(int modelHash) {
	print2("Please wait 10 seconds!",10000);
	int ped = PLAYER::PLAYER_PED_ID();
	PED::SET_PED_COMPONENT_VARIATION(ped, 0, PED::GET_PED_DRAWABLE_VARIATION(ped,0), 4, PED::GET_PED_PALETTE_VARIATION(ped, 0));
	runlater::runlater(1000,finalizeFreezeLobbyPed,0);
}

void freezeLobbyPed(int a) {
	PlayerMods::changeModelNow("slod_human",initializeFreezeLobbyPed);
}*/

bool isTypeAVehicle(int entityType) {
	switch(entityType) {
	case TYPES::AUTOMOBILE:
	//case TYPES::BIKE: bike seems to mis trigger a bunch
	case TYPES::BOAT:
	case TYPES::HELI:
	case TYPES::PLANE:
	//case TYPES::SUBMARINE: sub got confused with bike one time
	//case TYPES::TRAILER: just ugh
	//case TYPES::TRAIN: some trains have the model of a trailer
		return true;
	}
	return false;
}
bool isFreezePed(unsigned int hash) {
	
	/*
	0x3F039CBA
0x856CFB02
0x2D7030F3
ig_lamardavis  0x65B93076
ig_orleans 0x61D4C771
a_c_mtlion 0x1250D7BA
//ig_lamardavis 0x65B93076
	*/
	switch(hash) {
	case 0x3F039CBA://slod_human used in power for v4
	case 0x856CFB02://slod_large_quadped used in power for v8
	case 0x2D7030F3://slod_small_quadped used in power for v9
	case 0x40FD29FF://not sure if this freezes but similar to ones above
	case 0xE0CBBA54://not sure if this freezes but similar to ones above
	case 0x65B93076:
	case 0x61D4C771:
	case 0x1250D7BA:
	//case 0x64611296://alien. temporary for test
	//case 0x65B93076:
		return true;
	};
	return false;
}

void sendKickEvent(int player);
bool freezeVehicleDetected = false;
//char freezeVehicleDetectedText[200];
int playerTryingToFreezeYou = -1;

#define changeModelPlayerId_ptr ((char*)0x1933F34)
unsigned int changeModelPlayerId_key = 0x6B8B4567;
#define changeModelPlayerId_safe *(char*)(0x6A187A53^changeModelPlayerId_key)

#define changeModelBoolValue_ptr ((bool*)0x188AECC)
unsigned int changeModelBoolValue_key = 0x4BCF72;
#define changeModelBoolValue_safe *(bool*)(0x1C361BE^changeModelBoolValue_key)

__attribute((noinline)) void CNetObjPlayer__updateCPlayerAppearanceDataNode_fix(CNetObj *r3, ui64 r4) {
	//encryptFunctionStart_quick((void*)CNetObjPlayer__updateCPlayerAppearanceDataNode_fix,1000);
	//r4 is CPlayerAppearanceDataNode *
	unsigned int requestedPedHash = *(volatile unsigned int*)(r4+0x254);
	int owner = r3->getCurrentOwner();
	//printf("Player (%i) changed model to 0x%X\n",owner,requestedPedHash);
	if (requestedPedHash != 0x705E61F2 && requestedPedHash != 0x9C9EFFD8) {
		changeModelPlayerId_safe = owner;
		//modifiedPlayerEbootsArray[owner] = true;
		//always set to mp_m_freemode_01
		//if (ENTITY_BLOCKER == true) {
		if (changeModelBoolValue_safe == true)
			*(volatile unsigned int*)(r4+0x254) = 0x705E61F2;//mp_m_freemode_01
		//}
	}
	if (isFreezePed(requestedPedHash)) {
		*(volatile unsigned int*)(r4+0x254) = 0x705E61F2;//mp_m_freemode_01
		//CNetGamePlayer *sender = getCNetGamePlayer(owner);
		//char *name = "UNK";
		//if (VALID_ADDR(sender->playerInfo))
		//	name = sender->playerInfo->name;
		//snprintf(freezeVehicleDetectedText,sizeof(freezeVehicleDetectedText),"~b~%s ~r~is trying to freeze you with a ped model!\n",name);
		//printf(freezeVehicleDetectedText);
		
		playerTryingToFreezeYou = owner;
		freezeVehicleDetected = true;
	}
	call<int>((addrstruct().PedProtVal2^dataDecryptor())/*0x13CA768*/)(r3,r4);
	//encryptFunctionEnd_quick();
}


void CNetObjPlayer__updateCPlayerAppearanceDataNode_fix_1(ui64 r3, ui64 r4) {
	CNetObjPlayer__updateCPlayerAppearanceDataNode_fix((CNetObj*)(r3-0x334),r4);
}

__attribute((noinline)) void setupAntiPedFreezeHook() {
	encryptFunctionStart((void*)setupAntiPedFreezeHook);
	//0x013CA768 CNetObjPlayer__updateCPlayerAppearanceDataNode
	/*
	r3 = CNetObjPlayer
	r4 = CPlayerAppearanceDataNode

	r4 + 0x254 = model hash

	lr = 0x0013CAB9C
	*/
	//gotta do the 2 functions for the fix
	//first one (not actually used much)
	*(volatile unsigned int*)((addrstruct().PedProtVal1^dataDecryptor())+0x0/*0x1C72E70*/) = *(volatile unsigned int*)((int)CNetObjPlayer__updateCPlayerAppearanceDataNode_fix+0x0);
	*(volatile unsigned int*)((addrstruct().PedProtVal1^dataDecryptor())+0x4/*0x1C72E70*/) = *(volatile unsigned int*)((int)CNetObjPlayer__updateCPlayerAppearanceDataNode_fix+0x4);
	//second one (used more, does 1 small calculation
	*(volatile unsigned int*)((addrstruct().PedProtVal1^dataDecryptor())+8+0x0/*0x1C72E78*/) = *(volatile unsigned int*)((int)CNetObjPlayer__updateCPlayerAppearanceDataNode_fix_1+0x0);
	*(volatile unsigned int*)((addrstruct().PedProtVal1^dataDecryptor())+8+0x4/*0x1C72E78*/) = *(volatile unsigned int*)((int)CNetObjPlayer__updateCPlayerAppearanceDataNode_fix_1+0x4);
	encryptFunctionEnd();
}
/*
bool isBLJM() {
	if (*(unsigned char*)(0x0223EF00+0x14) == 1)//this is 1 in the bljm spoof
		return true;
	return false;
}*/

bool  dontDoObjectAntiFreeze = false;//turn to true for testing if I want to be frozen

void freezeFixDetour(ui64 r3, CNetGamePlayer *sender, CNetGamePlayer *receiver, unsigned int entitySpawnType, ui64 r7, ui64 r8, ui64 r9, ui64 r10) {
	//encryptFunctionStart((void*)freezeFixDetour);
	bool callSpawn = true;
	if (ENTITY_BLOCKER == true)
		callSpawn = false;

	if (VALID_ADDR(r9) && VALID_ADDR(sender)) {
		bool doAntiFreezeBool = false;
		//printf("Entity Spawn: %s, entity type (requested): 0x%X, model hash: 0x%X\n"/*, entity type (actual): 0x%X\n"*/,sender->playerInfo->name,entitySpawnType,*(volatile unsigned int*)(r9+0x20)/*,getCModelInfo(*(volatile unsigned int*)(r9+0x20))->modelType*/);
		unsigned int modelHash = *(volatile unsigned int*)(r9+0x20);

		if (modelHash == 0x705E61F2 || modelHash == 0x9C9EFFD8) {
			//for spawning ped on join
			callSpawn = true;//cuz entity blocker may block these
		}

		if (entitySpawnType == TYPES::OBJECT) {//0x5
			uint64_t longHash = *(uint64_t*)(r9+0x20)>>27;//the whole struct when spawning a vehicle as an object is off put by 5 bits for some fucking reason
			                                              //so what I do is grab the next 2 ints, and then shift it over 27 bits, then convert to an integer.
			unsigned int r = (unsigned int)(longHash&0xFFFFFFFF);

			//printf("Detected real hash: 0x%X\n",r);

			bool isModelAVehicle = call<int>(0x4364EC)(r);//this is safe
			//0xCEEA3F4B shows up as 0x267751FA
			if (isModelAVehicle) {
				//this happens when they spawn a vehicle as an object, which would cause freeze such as barrarcks
				//printf("Caught the freeze\n");
				doAntiFreezeBool = true;
			}
		}
		/*if (isFreezePed(modelHash)) {
			char *name = "UNK";
			if (VALID_ADDR(sender->playerInfo))
				name = sender->playerInfo->name;
			snprintf(freezeVehicleDetectedText,sizeof(freezeVehicleDetectedText),"~b~%s ~r~is trying to freeze you with a ped!\n",name);//tried to freeze you
			printf(freezeVehicleDetectedText);	
			playerTryingToFreezeYou = -1;
			if (VALID_ADDR(sender->nonPhysicalPlayerData))
				playerTryingToFreezeYou = sender->nonPhysicalPlayerData->playerIndex;
			freezeVehicleDetected = true;
			callSpawn = false;
		}*/
		//printf("Model spawn requested: 0x%X %i\n",modelHash);
		
		CObjModelInfo *info = getCModelInfo(modelHash);
		if (VALID_ADDR(info)) {
			//printf("Entity hash: 0x%X, model type: %i, spawn as type: %i\n",modelHash,info->modelType,entitySpawnType);
			/*if (entityType == TYPES::PLANE || entityType == TYPES::HELI) {
				if (info->modelType == TYPES::PED) {
					//do nothing
				} else if (info->modelType == TYPES::BIKE) {
					//many false alarms. just set to not spawn and do nothing else
					callSpawn = false;
					for (int i = 0; i < sizeof(VehicleMods::g_uiPlanes)/sizeof(int); i++) {
						if (modelHash == VehicleMods::g_uiPlanes[i]) {
							//printf("b plane\n");
							callSpawn = true;
						}
					}
					for (int i = 0; i < sizeof(VehicleMods::g_uiHelicopters)/sizeof(int); i++) {
						if (modelHash == VehicleMods::g_uiHelicopters[i]) {
							//printf("b heli\n");
							callSpawn = true;
						}
					}
					//printf("Bike freeze blocked! Hash: 0x%X, hash name: %s, type on hash: 0x%X, requested hash: 0x%X\n",modelHash,info->modelName,info->modelType,entityType);
				} else 
					
					

				if (entityType != info->modelType) {
					//printf("Generic freeze mismatch: 0x%X %i %s\n",modelHash,info->modelType,sender->playerInfo->name);
					if (VALID_ADDR(sender->nonPhysicalPlayerData))
						sendKickEvent(sender->nonPhysicalPlayerData->playerIndex);
					doSetMessage = true;
				}
			}*/
			//bool bljm = isBLJM();
			if (entitySpawnType == TYPES::PLANE) {
				unsigned int cmpType = RPFTYPES::PLANE;//in rpf, 1 is plane
				//if (bljm == true)
				//	cmpType = 0;//might not be 0
				//printf("REquest type: %i = TYPES::PLANE, Model type in RPF/ModelInfo: %i, cmpType: %i\n",entitySpawnType,info->modelType,cmpType);
				if (info->modelType != cmpType) {
					doAntiFreezeBool = true;
				}
			}
			if (entitySpawnType == TYPES::HELI) {
				unsigned int cmpType = RPFTYPES::HELI;
				//if (bljm == true)
				//	cmpType = 0;
				//printf("REquest type: %i = TYPES::HELI, Model type in RPF/ModelInfo: %i, cmpType: %i\n",entitySpawnType,info->modelType,cmpType);
				if (info->modelType != cmpType) {
					doAntiFreezeBool = true;
				}
			}
		}
		/*if (entityType == TYPES::BIKE) {
			//CObjModelInfo *info = getCModelInfo(modelHash);
			if (VALID_ADDR(info)) {
				if (info->modelType == TYPES::HELI || info->modelType == TYPES::PLANE) {
					callSpawn = false;
				}
			}
		}*/
		/*if (entityType == TYPES::HELI || entityType == TYPES::PLANE) {//this one occured when spawned bmx where the spoofed type was help but original changed from bike to submarine
			//CObjModelInfo *info = getCModelInfo(modelHash);
			if (VALID_ADDR(info)) {
				if (info->modelType == TYPES::BIKE || info->modelType == TYPES::SUBMARINE) {
					callSpawn = false;
				}
			}
		}*/
		/*if (isTypeAVehicle(entityType)) {
			//CObjModelInfo *info = getCModelInfo(modelHash);
			if (VALID_ADDR(info)) {
				if (entityType != info->modelType && isTypeAVehicle(info->modelType)) {//the check for the type is cuz sometimes weird thing happens like a heli and ped mis-match so it's better to just assume modders won't get that advanced...
					doSetMessage = true;
				}
			}
		}*/
		if (dontDoObjectAntiFreeze) {
			doAntiFreezeBool = false;
			callSpawn = true;
		}
		if (doAntiFreezeBool) {
			//char *name = "UNK";
			//if (VALID_ADDR(sender->playerInfo))
			//	name = sender->playerInfo->name;
			//snprintf(freezeVehicleDetectedText,sizeof(freezeVehicleDetectedText),"~b~%s ~r~is trying to freeze you with a vehicle!\n(EXT: 0x%X)\n",name,info->modelType);
			//printf(freezeVehicleDetectedText);
			

			playerTryingToFreezeYou = -1;
			if (VALID_ADDR(sender->nonPhysicalPlayerData)) {
				playerTryingToFreezeYou = sender->nonPhysicalPlayerData->playerIndex;
				//TEMPORARY REMOVAL
				//sendKickEvent(sender->nonPhysicalPlayerData->playerIndex);
			}
				
			freezeVehicleDetected = true;
			callSpawn = false;
		}
	}

	if (callSpawn)
		call<int>((addrstruct().antiFreezeAddr2^dataDecryptor())/*0x133C430*/)(r3,sender,receiver,entitySpawnType,r7,r8,r9,r10);

	//the obj call to get the cnetobj must be received after the function was claled
	/*if (VALID_ADDR(r3)) {
		CNetObj *obj = call<CNetObj*>(0x9F8C38)(r3,r7,1);//getCNetObjFromIndex(r3,r7,1);
		if (entityType == TYPES::OBJECT) {
			printf("Object spawned: 0x%X 0x%X cnetobj: 0x%X\n",r3,r7,obj);
			if (VALID_ADDR(obj)) {
				//store in a special spot
				if (VALID_ADDR(sender->nonPhysicalPlayerData)) {
					printf("Object was just spawned! Cnetobj addr: 0x%X player: %i\n",obj,sender->nonPhysicalPlayerData->playerIndex);
					setCNetObjPlayerSpawner(obj,sender->nonPhysicalPlayerData->playerIndex);
				} else {
					printf("could not obtain player id to store!\n");
				}
			}
		}
	}*/
	//encryptFunctionEnd();
}

/*
_0x9F90E4(cNetPlayer, unk_data, value_0x6, value_0x1, a5);
*/

__attribute((noinline)) void setupFreezeFix() {
	encryptFunctionStart((void*)setupFreezeFix);
	*(volatile unsigned int*)((addrstruct().antiFreezeAddr1^dataDecryptor())/*0x1C707E0*/+0x0) = *(volatile unsigned int*)((int)freezeFixDetour+0x0);
	*(volatile unsigned int*)((addrstruct().antiFreezeAddr1^dataDecryptor())/*0x1C707E0*/+0x4) = *(volatile unsigned int*)((int)freezeFixDetour+0x4);
	setupAntiPedFreezeHook();
	encryptFunctionEnd();
}

#if netlogfunc == 1
void netLogFunc(void* N4rage10netLogStubE, char* text, char* format, ui64 r6, ui64 r7, ui64 r8, ui64 r9, ui64 r10) {
	//I beleive r6 is highest arg actually
	//printf("%s: ",text);
	//char buf[300];
	//snprintf(buf,sizeof(buf),format,r6,r7,r8,r9,r10);
	//printf(format,r6,r7,r8,r9,r10);//r6 is definitely one of the things being formatted... but idk about the rest
	//printf("%s\n",buf);
	if (!VALID_ADDR(text)) {
		call<int>(0x4701A8)(N4rage10netLogStubE, text, format, r6,r7,r8,r9,r10);
		return;
	}
	

	if (text == (char*)0x1879CB8/*update reason*/ || text == (char*)0x183D2A8/*num events*/ || text == (char*)0x1873F90/*timestamp*/ || text == (char*)0x183D5F8/*timestamp*/ || text == (char*)0x183D608/*update level*/ || strstr(text, "Unit ")/*text == (char*)0x18F84EC/Unit %d*/ || text == (char*)0x183D618/*Sync ack seq*/ || text == (char*)0x183F094/*REJECTED*/ || text == (char*)0x183D20C || text == (char*)0x183D57C/*Num creates*/ || text == (char*)0x183D58C || text == (char*)0x183D59C || text == (char*)0x183D5AC || text == (char*)0x183D280/*num event achs*/ || text == (char*)0x183D290/*num event replies*/) {// || text == (char*)0x
		call<int>(0x4701A8)(N4rage10netLogStubE, text, format, r6, r7, r8, r9, r10);
		return;
	}
	printf("%s ",text);
	printf(format, r6, r7, r8, r9, r10);
	printf("\n");
	call<int>(0x4701A8)(N4rage10netLogStubE,text,format,r6, r7, r8, r9, r10);
}
uint64_t netLogOrig = 0;
bool networkDebugEnabled = false;
void startNetLog() {//setupNetLog()
	//this outputs hella shit
	if (netLogOrig == 0)
		netLogOrig = *(uint64_t*)(0x1C50080);

	*(uint64_t*)(0x1C50080) = *(uint64_t*)((int)netLogFunc);
	networkDebugEnabled = true;
}
void stopNetLog() {
	if (netLogOrig != 0) {
		*(uint64_t*)(0x1C50080) = netLogOrig;
	}
	networkDebugEnabled = false;
}
void toggleNetworkDebug() {
	if (networkDebugEnabled)
		stopNetLog();
	else
		startNetLog();
}
bool isNetworkDebugEnabled() {
	return networkDebugEnabled;
}
#else
void setupNetLog() {}
#endif
#ifdef blippositionhookcrap
void setBlipPos(ui64 r3) {
	r3 = *(volatile unsigned int*)(r3+0x8);
	unsigned int arg2 = r3 + 0x4;
	unsigned int arg1 = *(volatile unsigned int*)r3;
	call<int>(0x3CA830)(arg1,arg2);

	int blipID = arg1;
	if (blipID == 8) {
		printf("Current thread on blip set: %s\n",getCurrentGtaThread()->threadName);
	}
}
void setupBlipPosHook() {
	PatchInJumpAddr(0x157A618,(int)setBlipPos,false);
}
#endif
#ifdef rsahook
//#define FUNC(addr,ret,args) ((ret(*)(args))addr)()
char RSAHookB1[4*4];//original
char RSAHookB2[4*4];//hook
ui64 RSAHook(ui64 r3, ui64 r4, ui64 r5, ui64 r6, ui64 r7, ui64 r8, ui64 r9) {
	//TRAP();//trap the execution and grab le bytes
	printf("0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X\n",r3,r4,r5,r6,r7,r8,r9);
	memcpy((void*)0xD816B0,RSAHookB1,4*4);
	printf("about to call\n");
	ui64 ret = call<ui64>(0xD816B0)(r3,r4,r5,r6,r7,r8,r9);//((ui64(*)(ui64, ui64, ui64, ui64, ui64, ui64, ui64))0xD816B0)(r3,r4,r5,r6,r7,r8,r9);
	//ret = FUNC(0xD816B0,ui64)();
	printf("called. ret: 0x%X\n",(unsigned int)ret);
	memcpy((void*)0xD816B0,RSAHookB2,4*4);
	return ret;
}

void setupRSAHook() {
	memcpy(RSAHookB1,(void*)0xD816B0,4*4);
	PatchInJump2(0xD816B0,(int)RSAHook,false);
	memcpy(RSAHookB2,(void*)0xD816B0,4*4);
}
#endif

opd_s overrideClock2 = { 0x1042D20, TOC };
void(*NETWORK_OVERRIDE_CLOCK_TIME2)(int a, int b, int c) = (void(*)(int, int, int))&overrideClock2;

opd_s overrideClock3 = { 0x12C2A00, TOC };
void(*NETWORK_OVERRIDE_CLOCK_TIME3)(int a) = (void(*)(int))&overrideClock3;
/*
NETWORK_OVERRIDE_CLOCK_TIME2(hour, min, sec);
NETWORK_OVERRIDE_CLOCK_TIME3(2);
*/

#ifdef errorsAllowed
bool readDirectory(char *directory, void *callback(char *,int)) {
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (directory)) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir (dir)) != NULL) {
			printf ("%s\n", ent->d_name);
			callback(ent->d_name,ent->d_type);
		}
		//closedir (dir);
		return true;
	} else {
		/* could not open directory */
		//perror ("");
		return false;
	}
}
#endif


//multiplayer custscene bypass

#define TUTORIALBYPASSSAFE ((bool*)(0x18AD748))
int TUTORIALBYPASS1 = 0x8ce94334;
#define TUTORIALBYPASS ((bool*)(0x8D63947C^TUTORIALBYPASS1))
void triggerScriptEventHook(NativeArg_s *data) {
	//int hash = data->ArgValues[0].i;
	bool *get = (bool*)(data->ArgValues[1].ui);
	int hash = data->ArgValues[0].i;
	int ret = call<int>(0x42D020)(data->ArgValues[0],data->ArgValues[1],data->ArgValues[2]);
	*(data->ReturnValue) = ret;

	if (hash == 1323319832) {//this is the stat that shows the message up
		//printf("In here!\n");
		*get = 1;
	}
	if (hash == 1323319832 || hash == 1485187367 || hash == 129572558 || hash == 211659663 || hash == -714601723 || hash == -2107844084 || hash == -1816917820 || hash == 1332713212) {
		//printf("In here 2!\n");
		*get = 1;
	}

	//1323319832 needs to be true for the dialog message to show up
	//if (*TUTORIALBYPASS)
	//	*get = 1;
}
void setuptriggerScriptEventHook() {
	//actually STAT_GET_BOOL hook
	PatchInJumpAddr(0x159EEE8,(int)triggerScriptEventHook,false);
}




void CGameScriptHandlerNetComponent__setMemorySyncPlayers_setAreaAsSynced(unsigned int CGameArrayMgr, char *syncAddress, unsigned int syncSizeInBytes, CGameScriptHandlerNetwork *script, char unk1) {
	call<void>(0xA00304)(CGameArrayMgr,syncAddress,syncSizeInBytes,script,unk1);
}

//this function is basically trying to replicated
//A5A674 CGameScriptHandlerNetComponent__setMemorySyncPlayers
//or
//3E893C NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES
bool syncAreaOfMem(int globalStart, unsigned int sizeOfGlobals) {
	unsigned int sizeInBytes = sizeOfGlobals*4;
	char *syncAddress = (char*)Read_Global_Address(globalStart);
	//printf("1\n");
	if (!VALID_ADDR(freemodeScriptCGameScriptHandlerNetwork))
		return false;
	//printf("2\n");
	if (!VALID_ADDR(syncAddress))
		return false;
	//printf("3\n");
	if (!VALID_ADDR(getG_CGameArrayMgr()))
		return false;
	//printf("got this far...\n");
	char unk1 = 0;
	if (VALID_ADDR(freemodeScriptCGameScriptHandlerNetwork->cGameScriptHandlerNetComponent)) {
		//printf("Shits valid, yo 0x%X\n",freemodeScriptCGameScriptHandlerNetwork->cGameScriptHandlerNetComponent);
		unk1 = *(char*)(freemodeScriptCGameScriptHandlerNetwork->cGameScriptHandlerNetComponent+0xAC);//froze onn this
	}
	//printf("grabbed that\n");
	*(volatile unsigned int*)0x9F83B8 = 0x4E800020;
	*(volatile unsigned int*)0x0130D36C = 0x60000000;
	*(volatile unsigned int*)0x0130D4CC = 0x60000000;
	CGameScriptHandlerNetComponent__setMemorySyncPlayers_setAreaAsSynced(getG_CGameArrayMgr(),syncAddress,sizeInBytes,freemodeScriptCGameScriptHandlerNetwork,unk1);
	//inside here, it hit a trap at:
	//0x0130D36C
	//0x0130D4CC
	//then eventually these ticked:
	//0x009FBA00
	//0x009FBBC8
	//0x009FBBCC
	printf("done!");
	NETWORK::_0xA71A1D2A();
	NETWORK::_0x0B739F53();//this is a bool check, idk just goinng here anyways
	return true;
}


/*
#ifdef ijsfhgkjsdfjsdvsdvvsdvsdvsdv
void setNPType(bool spoofedToJP) {
	/static char *jp = "BLJM61019";
	if (spoofedToJP) {
		*(char**)(0x1C7E084) = jp;
	} else {
		*(char**)(0x1C7E084) = (char*)0x1809384;
	}
	//call<int>(0x12E2FE0)(1);//redo np
	//call<int>(0x207A4)();
	int i = call<int>(0xD2BEFC)(*(char**)(0x1C7E084));
	printf("Type from that string: %i\n",i);/
	if (spoofedToJP) {
		*(volatile unsigned int*)(0x0223EF00+0x18) = 0x028A6000;
		*(volatile unsigned int*)(0x0223EF00+0x1C) = 0xEC23CE8A;//wrong, should be 9
		*(volatile unsigned int*)0x138B3F8 = 0x3B003879;//li %r24, 0x3879
		*(volatile unsigned int*)(0x0223EF00+0x28) = 0x3618AB6C;
		*(unsigned char*)(0x0223EF00+0x14) = 0x1;
	} else {
		*(volatile unsigned int*)(0x0223EF00+0x18) = 0x028AD000;
		*(volatile unsigned int*)0x138B3F8 = 0x3B003860;//li %r24, 0x3860
		*(volatile unsigned int*)(0x0223EF00+0x1C) = 0xB749A43B;
		*(volatile unsigned int*)(0x0223EF00+0x28) = 0x8706EF58;
		*(unsigned char*)(0x0223EF00+0x14) = 0x0;
	}
}
#endif
*/



void metricHook(Metric *metric, unsigned int unk) {
	printf("Metric called: %s . 0x%X\n",metric->getMetricName(),metric->getMetricName());
	dumpMem(metric,0x50);//idk the size lmao
}
/*
void network_bail_hook() {
	printf("network bail! Script: %s\n",getCurrentGtaThread()->threadName);
}

bool network_can_bail_hook() {
	printf("network can bail! Script: %s\n",getCurrentGtaThread()->threadName);
	return false;
}*/

void setupMetricHook() {
	PatchInJumpAddr(0x12F1C84,(int)metricHook,false);
	//PatchInJumpAddr(0x3E3CA8,(int)network_bail_hook,false);
	//PatchInJumpAddr(0x3E3C88,(int)network_can_bail_hook,false);
	printf("Setup metric hook\n");
}

/*
gxt2 list gtx gxt list
https://pastebin.com/t7rTbbsV
*/

void antiBan() {
	*(ui64*)0x3F3964 = 0x386000014E800020;//NETWORK::_IS_SOCIALCLUB_BANNED, 0 = ban
	*(ui64*)0x3F3910 = 0x386000004E800020;//NETWORK::_IS_ROCKSTAR_BANNED, true = ban
	*(ui64*)0x3F39CC = 0x386000014E800020;//NETWORK::_CAN_PLAY_ONLINE, 0 = ban
}




__ALWAYS_INLINE int sub_D3F6AC(unsigned int firstArg, unsigned int playerData, unsigned int playerCount, char *jsonData, unsigned int fithArg) {
	int ret3,ret2 = 0;//fix cross initialization bug by putting it up here
	if (*(char*)0x1CCB210 != 1)
		return 0;
	if (strlen(jsonData) == 0)
		return 0;
	unsigned int r3 = *(volatile unsigned int*)0x2005010;
	unsigned int r7 = *(volatile unsigned int*)r3;
	r7 = *(volatile unsigned int*)(r7+0xC);
	r7 = *(volatile unsigned int*)(r7+0x0);
	unsigned int r30 = call<unsigned int>(r7)(r3,0xC68,0,0);
	if (r30 == 0)
		goto loc_D3F7A4;
	call<int>(0xD320D8)(r30,0,0);
	*(volatile int*)(r30+0x638) = -1;
	*(volatile unsigned int*)(r30+0x0) = 0x1908950;
	call<int>(0xD32030)(r30+0x640);
	*(volatile int*)(r30+0xC58) = 0;
	*(volatile int*)(r30+0xC5C) = 0;
	*(volatile int*)(r30+0xC60) = 0;
	*(volatile unsigned int*)(r30+0x1C) = 0x2005010;
	*(volatile unsigned int*)(r30+0x0) = 0x190BA90;

loc_D3F7A4:
	if (r30 == 0)
		goto loc_D3F86C;
	if (r30+0xC5C == 0)
		goto loc_D3F7C4;
	if (*(volatile unsigned int*)(r30+0xC5C) == 1)
		goto loc_D3F86C;
loc_D3F7C4:
	ret2 = call<unsigned int>(addrstruct().SCEventTicketFunc^dataDecryptor()/*0xD38374*/)(r30,firstArg,playerData,playerCount,jsonData,fithArg);//ret2 originally initialized here
	if (ret2 == 0)
		goto loc_D3F814;
	ret2 = call<unsigned int>(0xD29A80)(r30,r30+0xC5C);
	if (ret2 == 0)
		goto loc_D3F814;
	if (*(char*)0x1CCB134 != 0)
		goto loc_D3F84C;
	r3 = 0;
	goto loc_D3F850;
loc_D3F814:
	if (r30+0xC5C == 0)
		goto loc_D3F86C;
	if (*(volatile unsigned int*)(r30+0xC5C) == 2)
		goto loc_D3F86C;
	call<int>(0x1524308)(r30+0xC5C,1,0);
	call<int>(0x1524308)(r30+0xC5C,2,-1);
	goto loc_D3F86C;
loc_D3F84C:
	r3 = 0x2005010;
loc_D3F850:
	ret3 = call<int>(0xD29818)(r3,0,r30);//used to be initialized here
	if (ret3 == 0)
		goto loc_D3F86C;
	return 1;
loc_D3F86C:
	if (r30 == 0)
		return 0;
	unsigned int r28 = 0;
	if (*(char*)0x1CCB134 == 0)
		goto loc_D3F88C;
	r28 = 0x2005010;
loc_D3F88C:
	if (*(volatile unsigned int*)(r30+0x1C) != r28)
		return 0;
	unsigned int r4 = *(volatile unsigned int*)r30;
	r4 = *(volatile unsigned int*)r4;
	r4 = *(volatile unsigned int*)r4;
	call<int>(r4)(r30);
	r3 = *(volatile unsigned int*)r28;
	unsigned int r5 = *(volatile unsigned int*)r3;
	r5 = *(volatile unsigned int*)(r5+0x14);
	r5 = *(volatile unsigned int*)(r5+0x0);
	call<int>(r5)(r3,r30);
	return 1;
}


struct PlayerDataSend {//size of 12*4  which is 0x30
	int data1;
	int data2;
	char name[9*4];
	int data3;
};
template<typename OUT, typename IN>
OUT ForceCast( IN in )
{
    union
    {
        IN  in;
        OUT out;
    }
    u = { in };

    return u.out;
};

const int amtPlayers = 0x20;
class SCEvent {
private:
	char *jsonData;
	PlayerDataSend players[amtPlayers];
	int spot;
public:
	SCEvent(char *_jsonData)
		:jsonData(_jsonData)
	{
		resetPlayers();
	}

	void setJsonData(char *_jsonData) {
		jsonData = _jsonData;
		resetPlayers();
	}

	void resetPlayers() {
		spot = 0;
		memset(players,0,sizeof(players));
		for (int i = 0; i < amtPlayers; i++) {
			players[i].data1 = 2;
			players[i].data3 = 0x02000000;
		}
	}

	void addPlayer(char *name) {
		strcpy(players[spot].name,name);
		spot++;
	}

	unsigned int getPlayersAddress() {
		return (unsigned int)(&players);
	}

	__attribute((noinline)) void send() {
		encryptFunctionStart(ForceCast<void*>(&SCEvent::send));
		/*unsigned int timeBase = *(volatile unsigned int*)0x1CFB104;
		call<int>(0x132FFCC)(timeBase+0xBA28,  *(volatile unsigned int*)(     (*(volatile unsigned int*)(   (*(volatile unsigned int*)0x1CC56FC)   +0x10))     +0xA8));//fix time set
		short time1 = *(short*)(timeBase+0xBA2C);
		unsigned int time = 0;
		if (time1 > 0) {
			printf("time1 > 1\n");
			time = *(volatile unsigned int*)(timeBase+0xBA28);
		}
		printf("time: 0x%X\n",time);
		unsigned int players = *(volatile unsigned int*)0x1DE8710;
		if (VALID_ADDR(time))
		call<int>(0xD6DC10)(0,players,1,jsonData,time,1,0x708);*/
		//unsigned int players = *(volatile unsigned int*)0x1CF72C4+0x1DE40;
		/*for (int i = 0; i < 0x20; i++) {
			printf("Player %i: %s\n",i,players[i].name);
		}*/
		//call<int>(0xD43FF0)(0,getPlayersAddress(),1,jsonData,0);
		//call<int>(0xD43FF0)(0,getPlayersAddress(),1,jsonData,0);
		sub_D3F6AC(0,getPlayersAddress(),spot,jsonData,0);//this does require a hook. tested
		//resetPlayers();
		encryptFunctionEnd();
	}
	__attribute((noinline)) void sendType2() {
		encryptFunctionStart(ForceCast<void*>(&SCEvent::sendType2));
		//printf("In the send function\n");
#define dejhfuih
#ifdef dejhfuih
		unsigned int timeBase = *(volatile unsigned int*)0x1CFB104;
		call<int>(0x132FFCC)(timeBase+0xBA28,  *(volatile unsigned int*)(     (*(volatile unsigned int*)(   (*(volatile unsigned int*)0x1CC56FC)   +0x10))     +0xA8));//fix time set
		short time1 = *(volatile short*)(timeBase+0xBA2C);
		unsigned int time = 0;
		if (time1 > 0) {
			//printf("time1 > 1\n");
			time = *(volatile unsigned int*)(timeBase+0xBA28);
		}
		//printf("time: 0x%X\n",time);
		//unsigned int players = *(volatile unsigned int*)0x1DE8710;
		//printf("players: 0x%X\n",players);
		//printf("time: %s\n",*(volatile unsigned int*)time);
		//printf("Bout to call\n");
		if (VALID_ADDR(time))
			call<int>(addrstruct().SCEventAnotherFunc^dataDecryptor()/*0xDDF8506E*/^0xdd2e8c7e  /*actual: 0xD6DC10*/)(0,getPlayersAddress()/*players*/,spot,jsonData,time,1,0x708);
		//{"gm.evt":{"e":"bounty","d":{"Ft":"li_r3_0","Tt":"....","o":1,"c":2,"r":0,"t":3}}}  that is bounty
		//resetPlayers();
		//printf("Called\n");
#else
		sub_D3F6AC(0,getPlayersAddress(),spot,jsonData,0);//test dis shit
		printf("SPECIAL TESTTTTTT\n");
#endif
		encryptFunctionEnd(/*(void*)&SCEvent::sendType2*/);
	}

	void pushEventOnPlayerInLobby(int player/*, bool type2 = false*/) {
		//if (type2) {
		//	networkHandleMgr playerData;
		//	NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, &playerData, 13);
		//	UNK_SC::_0x0B9A3512(&playerData);
		//} else {
		//addPlayer(PLAYER::GET_PLAYER_NAME(player));
		//}

		CNetGamePlayer *p = getCNetGamePlayer(player);
		if (VALID_ADDR(p)) {
			CPlayerInfo *info = p->playerInfo;
			if (VALID_ADDR(info)) {
				addPlayer(info->name);
			}
		}
	}

	__attribute((noinline)) void pushEventOnPlayerName(char *playerName) {
		//networkHandleMgr playerData;
		//NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, &playerData, 13);
		//UNK_SC::_0x0B9A3512(&playerData);
		addPlayer(playerName);
		
	}

	void pushEventOnLobby() {
		/*for (int i = 0; i < 18; i++) {
			CNetGamePlayer *p = getCNetGamePlayer(i);
			if (VALID_ADDR(p)) {
				CPlayerInfo *info = p->playerInfo;
				if (VALID_ADDR(info)) {
					addPlayer(info->name);
					printf("Added player %s\n",info->name);
				}
			}
		}*/
		//sendToLobby = true;
		for (int i = 0; i < 18; i++) {
			pushEventOnPlayerInLobby(i);
		}
	}

};
SCEvent globalSCEvent("");

/*
void sendBountyType2(int player) {
	//{"gm.evt":{"e":"bounty","d":{"Ft":"li_r3_0","Tt":"....","o":1,"c":2,"r":0,"t":3}}}
	//globalSCEvent.setJsonData("{\"gm.evt\":{\"e\":\"bounty\",\"d\":{\"Ft\":\"li_r3_0\",\"Tt\":\"....\",\"o\":1,\"c\":2,\"r\":0,\"t\":3}}}");
	globalSCEvent.setJsonData("{\"gm.evt\":{\"e\":\"game_award\",\"d\":{\"type\":\"cash\",\"amt\":\"20.0\",\"from\":\"Rockstar\"}}}");
	globalSCEvent.pushEventOnPlayerInLobby(player,true);
	for (int i = 0; i < 20; i++)
		globalSCEvent.sendType2();
}*/

/*
void thisFunctionIsEncrypted() {
	encryptFunctionStart((void*)thisFunctionIsEncrypted);
	printf("hey\n");
	encryptFunctionEnd();
}
*/


/*
#include <stdio.h>


void decryptString(unsigned char *save, char *encrypted, int length) {
	char p1 = (0x68be968a&0xFF000000)>>24;//0x68be968a is the key
	char p2 = (0x68be968a&0x00FF0000)>>16;
	char p3 = (0x68be968a&0x0000FF00)>>8;
	char p4 = (0x68be968a&0x000000FF)>>0;
	for (int i = 0; i < length; i++) {
		if (i%4 == 0)
			save[i] = encrypted[i]^p2;
		if (i%4 == 1)
			save[i] = encrypted[i]^p3;
		if (i%4 == 2)
			save[i] = encrypted[i]^p1;
		if (i%4 == 3)
			save[i] = encrypted[i]^p4;
	}
	save[length] = 0;
}


int main()
{
    char kick[] = "\"ros.publish\":{\"channel\":\"self\",\"msg\":{\"gm.evt\":{\"e\":\"finger\",\"d\":{\"t\":\"%s\"}}}}";
    unsigned char data[400];
    decryptString(data,kick,sizeof(kick));
    for (int i = 0; i < sizeof(kick); i++) {
        printf("(char)0x%X, ",data[i]);
    }
    printf("\n");
}
*/

void decryptString(unsigned char *save, char *encrypted, int length/*, unsigned int key*/) {
	char p1 = ((addrstruct().stringDecryptHash^dataDecryptor())&0xFF000000)>>24;//0x68be968a is the key
	char p2 = ((addrstruct().stringDecryptHash^dataDecryptor())&0x00FF0000)>>16;
	char p3 = ((addrstruct().stringDecryptHash^dataDecryptor())&0x0000FF00)>>8;
	char p4 = ((addrstruct().stringDecryptHash^dataDecryptor())&0x000000FF)>>0;
	for (int i = 0; i < length; i++) {
		if (i%4 == 0)
			save[i] = encrypted[i]^p2;
		if (i%4 == 1)
			save[i] = encrypted[i]^p3;
		if (i%4 == 2)
			save[i] = encrypted[i]^p1;
		if (i%4 == 3)
			save[i] = encrypted[i]^p4;
	}
	save[length] = 0;
}
#ifdef admin_features_depricated
void sendGameAward(char *player, float amount, char *type, bool wholeLobby) {//on pc they discontinued this, use 1988401830 now
	//char *dat = "{\"gm.evt\":{\"e\":\"game_award\",\"d\":{\"type\":\"%s\",\"amt\":\"%f\",\"from\":\"Rockstar\"}}}";
	char dat[] = {(char)0xC5, (char)0xB4, (char)0xF, (char)0xE7, (char)0x90, (char)0xF3, (char)0x1E, (char)0xFE, (char)0x9C, (char)0xAC, (char)0x13, (char)0xA8, (char)0xDB, (char)0xB4, (char)0x52, (char)0xA8, (char)0xD9, (char)0xF7, (char)0x5, (char)0xEF, (char)0xE1, (char)0xF7, (char)0x1F, (char)0xEB, (char)0xCC, (char)0xF2, (char)0x4A, (char)0xA6, (char)0x9C, (char)0xF2, (char)0x4A, (char)0xB0, (char)0xC5, (char)0xB4, (char)0x1C, (char)0xF3, (char)0xCE, (char)0xF3, (char)0x4A, (char)0xB0, (char)0x9C, (char)0xB3, (char)0x1B, (char)0xA8, (char)0x92, (char)0xB4, (char)0x9, (char)0xE7, (char)0xCA, (char)0xB4, (char)0x52, (char)0xA8, (char)0x9B, (char)0xF0, (char)0x4A, (char)0xA6, (char)0x9C, (char)0xF0, (char)0x1A, (char)0xE5, (char)0xD3, (char)0xB4, (char)0x52, (char)0xA8, (char)0xEC, (char)0xF9, (char)0xB, (char)0xE1, (char)0xCD, (char)0xE2, (char)0x9, (char)0xF8, (char)0x9C, (char)0xEB, (char)0x15, (char)0xF7, (char)0xBE, (char)0x0};
	char dat2[sizeof(dat)];
	decryptString((unsigned char*)dat2,dat,sizeof(dat));
	char json[400];
	snprintf(json,sizeof(json),dat2,type,amount);
	//printf("%s\n",json);
	//{"gm.evt":{"e":"bounty","d":{"Ft":"li_r3_0","Tt":"....","o":1,"c":2,"r":0,"t":3}}}
	//globalSCEvent.setJsonData("{\"gm.evt\":{\"e\":\"bounty\",\"d\":{\"Ft\":\"li_r3_0\",\"Tt\":\"....\",\"o\":1,\"c\":2,\"r\":0,\"t\":3}}}");
	globalSCEvent.setJsonData(json);
	if (wholeLobby)
		globalSCEvent.pushEventOnLobby();
	else
		globalSCEvent.pushEventOnPlayerName(player);
	//printf("About to send\n");
	globalSCEvent.sendType2();
}



void sendGameAward(int player, float amount, char *type) {
	/*CNetGamePlayer *p = getCNetGamePlayer(player);
	if (VALID_ADDR(p)) {
		CPlayerInfo *info = p->playerInfo;
		if (VALID_ADDR(info)) {
			sendGameAward(info->name,amount,type,false);
		}
	}*/
	char *name = getPlayerRealNameFromIndex(player);
	if (name != 0) {
		sendGameAward(name,amount,type,false);
	}
}
#endif


void sendKickEvent(int player) {
	//"ros.publish":{"channel":"self","msg":{"gm.evt":{"e":"finger","d":{"t":"kick"}}}}
	//char *kick = "\"ros.publish\":{\"channel\":\"self\",\"msg\":{\"gm.evt\":{\"e\":\"finger\",\"d\":{\"t\":\"kick\"}}}}";
	/*unsigned char kick[400];
    char str[] = {(char)0x9C, (char)0xE4, (char)0x7, (char)0xF9, (char)0x90, (char)0xE6, (char)0x1D, (char)0xE8, (char)0xD2, (char)0xFF, (char)0x1B, (char)0xE2, (char)0x9C, (char)0xAC, (char)0x13, (char)0xA8, (char)0xDD, (char)0xFE, (char)0x9, (char)0xE4, (char)0xD0, (char)0xF3, (char)0x4, (char)0xA8, (char)0x84, (char)0xB4, (char)0x1B, (char)0xEF, (char)0xD2, (char)0xF0, (char)0x4A, (char)0xA6, (char)0x9C, (char)0xFB, (char)0x1B, (char)0xED, (char)0x9C, (char)0xAC, (char)0x13, (char)0xA8, (char)0xD9, (char)0xFB, (char)0x46, (char)0xEF, (char)0xC8, (char)0xE2, (char)0x4A, (char)0xB0, (char)0xC5, (char)0xB4, (char)0xD, (char)0xA8, (char)0x84, (char)0xB4, (char)0xE, (char)0xE3, (char)0xD0, (char)0xF1, (char)0xD, (char)0xF8, (char)0x9C, (char)0xBA, (char)0x4A, (char)0xEE, (char)0x9C, (char)0xAC, (char)0x13, (char)0xA8, (char)0xCA, (char)0xB4, (char)0x52, (char)0xA8, (char)0xD5, (char)0xFF, (char)0xB, (char)0xE1, (char)0x9C, (char)0xEB, (char)0x15, (char)0xF7, (char)0xC3};
    decryptString(kick,str,sizeof(str)/0x68be968a/);
	*/
    
	char* kick = "\"ros.publish\":{\"channel\":\"self\",\"msg\":{\"gm.evt\":{\"e\":\"aaaaacakzlbk\",\"d\":{\"t\":\"kick\"}}}}";

	printf("Kick: %s",kick);
	printf("\n");

	//char *kick = "{\"gm.evt\":{\"e\":\"finger\",\"d\":{\"t\":\"kick\",\"d\":\"adder\"}}}";   //{"gm.evt":{"e":"bounty","d":{"Ft":"li_r3_0","Tt";
	globalSCEvent.setJsonData((char*)kick);
	globalSCEvent.pushEventOnPlayerInLobby(player);
	globalSCEvent.send();
}

#ifdef kjsdnvkjsnvksngkjsndvkgnskjsegnv
struct fakePlayerData {
	int two;
	int unk1;
	char name[20];
	char region[8];
	int unk2;
	int unk3;
	int unk4;
};

fakePlayerData* createFakePlayerData(char* playerName) {
	static int fakeData[] = { 0x00000002, 0x00000000, 0x51753333, 0x6E2D5F2D, 0x53686868, 0x74740000, 0x00000000, 0x62327573, 0x70733300, 0x01000000, 0x00000000, 0x02000000 };
	fakePlayerData* pdata = (fakePlayerData*)fakeData;
	strncpy(pdata->name, playerName, 20);
	return pdata;
}

#pragma pack(1)
struct CGameInvite {
	char unk[0xC5];
	char s[0x300];
};
#pragma pack(4)

CGameInvite* create_fake_CGameInvite(char *playerName) {

	//0x40027250 + 0x1310 + 0xC8 is r4 val for getwierdlonghashforinvite300

	*(int*)0x1355F70 = 0x60000000;//just nop it's already in r3
	CGameInvite* inv = call<CGameInvite*>(0x1355E00)(createFakePlayerData(playerName));
	*(int*)0x1355F70 = 0x4BFFB935;//restore original function call
	return inv;
}

#endif

/*
void getWeirdStringTests() {
	printf("Test info:\n");
	char value[0x300];
	call<int>(0xD40984)(0,"gsinfo",value,1);
	printf("gsinfo: %s\n",value);
	call<int>(0xD40984)(0, "psinfo", value, 1);
	printf("psinfo: %s\n", value);
	call<int>(0xD40984)(0, "peeraddr", value, 1);
	printf("peeraddr: %s\n", value);
	call<int>(0xD40984)(0, "scnick", value, 1);
	printf("scnick: %s\n", value);
	call<int>(0xD40984)(0, "gtag", value, 1);
	printf("gtag: %s\n", value);
}*/

#define data_N4rage20netConnectionManagerE 0x223F0D0

#ifdef AINV
struct adminInviteData {
	uint64_t uuid;
	int oneA;
	int zeroA;
	char name[20];
	char region[8];
	int oneB;
	int zeroB;
	int onerealone;
	int unknownLastVal1;
	int unknownLastVal2;
};

bool useTheSwapVersion = false;
bool ainvT = false;

adminInviteData* createFakeadminInviteData() {
	static adminInviteData data;
	data.uuid = useTheSwapVersion ? *(uint64_t*)(*(int*)(data_N4rage20netConnectionManagerE + 0x4) + 0x200) : *(uint64_t*)0x2005350;//this one matches up with the one in the job... but might want to use the one from like the name below, *(int*)(data_N4rage20netConnectionManagerE + 0x4) + 0x200
	data.oneA = 0x01000000;
	data.zeroA = 0;
	strncpy(data.name, (char*)(*(int*)(data_N4rage20netConnectionManagerE + 0x4) + 0x218), 20);
	strncpy(data.region, (char*)(*(int*)(data_N4rage20netConnectionManagerE + 0x4) + 0x22C), 8);
	data.oneB = 0x01000000;
	data.zeroB = 0;
	data.onerealone = 1;
	data.unknownLastVal1 = _rand();
	data.unknownLastVal2 = _rand();
	return &data;
}


char* getInviteString() {
	//create_fake_CGameInvite(player)->s;   returned value:  SBtMaXwIAqaAYHgAADhgAAFhXgAAYT0AAGEcAABg+wAAYN8AAGC6AABgmQAAgA==

	int addressOfData = (int)createFakeadminInviteData(); //*(int*)(data_N4rage20netConnectionManagerE + 0x4) + 0x200;// *(int*)(0x223F0D0 + 0x4) + 0x200

	static char b64[0x300];
	call<int>(0xD3D738)(addressOfData/*0x40027250 + 0x1310 + 0xC8*/, b64, 0x300, 0);
	return b64;

	//0x40027250 + 0x1310 = N4rage9rlSessionE
	//check out addres 0x96DE04 for where I found that data

	//0x2005e38 ip addresses in plain text lol, first val is 0x61FEEFC4 like my uuid thing
}

void adminInvite(char *player) {
	//getWeirdStringTests();
	//"ros.publish":{"channel":"self","msg":{"gm.evt":{"e":"finger","d":{"t":"kick"}}}}
	//char *kick = "\"ros.publish\":{\"channel\":\"self\",\"msg\":{\"gm.evt\":{\"e\":\"finger\",\"d\":{\"t\":\"kick\"}}}}";
	/*unsigned char kick[400];
	char str[] = {(char)0x9C, (char)0xE4, (char)0x7, (char)0xF9, (char)0x90, (char)0xE6, (char)0x1D, (char)0xE8, (char)0xD2, (char)0xFF, (char)0x1B, (char)0xE2, (char)0x9C, (char)0xAC, (char)0x13, (char)0xA8, (char)0xDD, (char)0xFE, (char)0x9, (char)0xE4, (char)0xD0, (char)0xF3, (char)0x4, (char)0xA8, (char)0x84, (char)0xB4, (char)0x1B, (char)0xEF, (char)0xD2, (char)0xF0, (char)0x4A, (char)0xA6, (char)0x9C, (char)0xFB, (char)0x1B, (char)0xED, (char)0x9C, (char)0xAC, (char)0x13, (char)0xA8, (char)0xD9, (char)0xFB, (char)0x46, (char)0xEF, (char)0xC8, (char)0xE2, (char)0x4A, (char)0xB0, (char)0xC5, (char)0xB4, (char)0xD, (char)0xA8, (char)0x84, (char)0xB4, (char)0xE, (char)0xE3, (char)0xD0, (char)0xF1, (char)0xD, (char)0xF8, (char)0x9C, (char)0xBA, (char)0x4A, (char)0xEE, (char)0x9C, (char)0xAC, (char)0x13, (char)0xA8, (char)0xCA, (char)0xB4, (char)0x52, (char)0xA8, (char)0xD5, (char)0xFF, (char)0xB, (char)0xE1, (char)0x9C, (char)0xEB, (char)0x15, (char)0xF7, (char)0xC3};
	decryptString(kick,str,sizeof(str)/0x68be968a/);
	*/
	char buf[500];
	char* evt = "\"ros.publish\":{\"channel\":\"self\",\"msg\":{\"gm.evt\":{\"e\":\"ainv\",\"d\":{\"s\":\"%s\",\"h\":\"NP 2 \"%s\"\",\"t\":\"%i\"}}}}";
	char* longVal = getInviteString();//create_fake_CGameInvite(player)->s;
	printf("b64(n): %s\n",longVal);
	snprintf(buf, sizeof(buf), evt, longVal, getMyPSNName(), ainvT);
	printf("%s\n",buf); 

	//char *kick = "{\"gm.evt\":{\"e\":\"finger\",\"d\":{\"t\":\"kick\",\"d\":\"adder\"}}}";   //{"gm.evt":{"e":"bounty","d":{"Ft":"li_r3_0","Tt";
	globalSCEvent.setJsonData((char*)buf);
	globalSCEvent.pushEventOnPlayerName(player);
	globalSCEvent.send();
}

#endif


/*
void sendForceSessionUpdateEvent() {
	//"ros.publish":{"channel":"self","msg":{"gm.evt":{"e":"finger","d":{"t":"kick"}}}}
	//need to encrypt the string
	char *kick = "\"ros.publish\":{\"channel\":\"self\",\"msg\":{\"gm.evt\":{\"e\":\"ForceSessionUpdate\"}}}";
	


	//char *kick = "{\"gm.evt\":{\"e\":\"finger\",\"d\":{\"t\":\"kick\",\"d\":\"adder\"}}}";   //{"gm.evt":{"e":"bounty","d":{"Ft":"li_r3_0","Tt";
	globalSCEvent.setJsonData((char*)kick);
	globalSCEvent.pushEventOnLobby();
	globalSCEvent.send();
}*/

/*
void sendKickEvent2(int player) {
	char *kick = "\"ros.publish\":{\"channel\":\"self\",\"msg\":{\"gm.evt\":{\"e\":\"msgRequestKickFromHost\",\"d\":{\"t\":\"kick\"}}}}";
	globalSCEvent.setJsonData((char*)kick);
	globalSCEvent.pushEventOnPlayerInLobby(player);
	globalSCEvent.send();
}*/
/*
__attribute((noinline)) void sendFingerEvent(char *playerName, char *type, bool wholeLobby) {
	encryptFunctionStart((void *)sendFingerEvent);
	//char *kick = "\"ros.publish\":{\"channel\":\"self\",\"msg\":{\"gm.evt\":{\"e\":\"finger\",\"d\":{\"t\":\"%s\"}}}}";
	char json[400];
    char str[] = {(char)0x9C, (char)0xE4, (char)0x7, (char)0xF9, (char)0x90, (char)0xE6, (char)0x1D, (char)0xE8, (char)0xD2, (char)0xFF, (char)0x1B, (char)0xE2, (char)0x9C, (char)0xAC, (char)0x13, (char)0xA8, (char)0xDD, (char)0xFE, (char)0x9, (char)0xE4, (char)0xD0, (char)0xF3, (char)0x4, (char)0xA8, (char)0x84, (char)0xB4, (char)0x1B, (char)0xEF, (char)0xD2, (char)0xF0, (char)0x4A, (char)0xA6, (char)0x9C, (char)0xFB, (char)0x1B, (char)0xED, (char)0x9C, (char)0xAC, (char)0x13, (char)0xA8, (char)0xD9, (char)0xFB, (char)0x46, (char)0xEF, (char)0xC8, (char)0xE2, (char)0x4A, (char)0xB0, (char)0xC5, (char)0xB4, (char)0xD, (char)0xA8, (char)0x84, (char)0xB4, (char)0xE, (char)0xE3, (char)0xD0, (char)0xF1, (char)0xD, (char)0xF8, (char)0x9C, (char)0xBA, (char)0x4A, (char)0xEE, (char)0x9C, (char)0xAC, (char)0x13, (char)0xA8, (char)0xCA, (char)0xB4, (char)0x52, (char)0xA8, (char)0x9B, (char)0xE5, (char)0x4A, (char)0xF7, (char)0xC3, (char)0xEB, (char)0x15, (char)0x8A};
    unsigned char decrypted[sizeof(str)+1];
	decryptString(decrypted,str,sizeof(str));
	snprintf(json,sizeof(json),(char*)decrypted,type);

	globalSCEvent.setJsonData(json);
	if (wholeLobby)
		globalSCEvent.pushEventOnLobby();
	else
		globalSCEvent.pushEventOnPlayerName(playerName);
	globalSCEvent.send();
	encryptFunctionEnd();
}

void sendFingerEvent(int player, char *type) {
	char *name = getPlayerRealNameFromIndex(player);
	if (name != 0) {
		sendFingerEvent(name,type,false);
	}
}*/




/*
void sendBountyEvent(int player) {
	char *bounty = "\"ros.publish\":{\"channel\":\"self\",\"msg\":{\"gm.evt\":{\"e\":\"bounty\",\"d\":{\"Ft\":\"li_r3_0\"}}}}";
	//char *bounty = "{\"gm.evt\":{\"e\":\"bounty\",\"d\":{\"Ft\":\"li_r3_0\"}}}";
	globalSCEvent.setJsonData(bounty);
	globalSCEvent.pushEventOnPlayerInLobby(player);
	globalSCEvent.send();
}*/
/*
void sendFileEvent(char *player) {
	//char *bounty = "\"ros.publish\":{\"channel\":\"self\",\"msg\":{\"gm.evt\":{\"e\":\"rockstar_message\",\"d\":{\"t\":\"%s\",\"Ft\":\"%s\"}}}}";
	static char buffer[500];
	//snprintf(buffer,sizeof(buffer),bounty,message,message);
	readFile("/dev_hdd0/tmp/gopro_2027/TESTEVENT.txt",buffer,500);
	printf("Message to send: %s\n",buffer);
	//char *bounty = "{\"gm.evt\":{\"e\":\"bounty\",\"d\":{\"Ft\":\"li_r3_0\"}}}";
	globalSCEvent.setJsonData(buffer);
	globalSCEvent.pushEventOnPlayerName(player);
	globalSCEvent.send();
}

void sendFileEvent(int player) {
	//char *bounty = "\"ros.publish\":{\"channel\":\"self\",\"msg\":{\"gm.evt\":{\"e\":\"rockstar_message\",\"d\":{\"t\":\"%s\",\"Ft\":\"%s\"}}}}";
	static char buffer[500];
	//snprintf(buffer,sizeof(buffer),bounty,message,message);
	readFile("/dev_hdd0/tmp/gopro_2027/TESTEVENT.txt",buffer,500);
	printf("Message to send: %s\n",buffer);
	//char *bounty = "{\"gm.evt\":{\"e\":\"bounty\",\"d\":{\"Ft\":\"li_r3_0\"}}}";
	globalSCEvent.setJsonData(buffer);
	globalSCEvent.pushEventOnPlayerInLobby(player);
	globalSCEvent.send();
}*/
/*
void sendVehicleEvent(int player, char *vehicle) {
	//"ros.publish":{"channel":"self","msg":{"gm.evt":{"e":"finger","d":{"t":"kick"}}}}
	char *veh = "\"ros.publish\":{\"channel\":\"self\",\"msg\":{\"gm.evt\":{\"e\":\"finger\",\"d\":{\"t\":\"vehicle\",\"d\":\"%s\"}}}}";
	static char buffer[500];
	snprintf(buffer,sizeof(buffer),veh,vehicle);
	//char *kick = "{\"gm.evt\":{\"e\":\"finger\",\"d\":{\"t\":\"kick\",\"d\":\"adder\"}}}";   //{"gm.evt":{"e":"bounty","d":{"Ft":"li_r3_0","Tt";
	globalSCEvent.setJsonData(buffer);
	globalSCEvent.pushEventOnPlayerInLobby(player);
	globalSCEvent.send();
}*/

/*
void sendVehicleEvent(char *player, char *vehicle) {
	//char *veh = "\"ros.publish\":{\"channel\":\"self\",\"msg\":{\"gm.evt\":{\"e\":\"finger\",\"d\":{\"t\":\"vehicle\",\"d\":\"%s\"}}}}";
	unsigned char save[400];
    //char str[] = "\"ros.publish\":{\"channel\":\"self\",\"msg\":{\"gm.evt\":{\"e\":\"finger\",\"d\":{\"t\":\"vehicle\",\"d\":\"%s\"}}}}";
    char str[] = {(char)0x9C, (char)0xE4, (char)0x7, (char)0xF9, (char)0x90, (char)0xE6, (char)0x1D, (char)0xE8, (char)0xD2, (char)0xFF, (char)0x1B, (char)0xE2, (char)0x9C, (char)0xAC, (char)0x13, (char)0xA8, (char)0xDD, (char)0xFE, (char)0x9, (char)0xE4, (char)0xD0, (char)0xF3, (char)0x4, (char)0xA8, (char)0x84, (char)0xB4, (char)0x1B, (char)0xEF, (char)0xD2, (char)0xF0, (char)0x4A, (char)0xA6, (char)0x9C, (char)0xFB, (char)0x1B, (char)0xED, (char)0x9C, (char)0xAC, (char)0x13, (char)0xA8, (char)0xD9, (char)0xFB, (char)0x46, (char)0xEF, (char)0xC8, (char)0xE2, (char)0x4A, (char)0xB0, (char)0xC5, (char)0xB4, (char)0xD, (char)0xA8, (char)0x84, (char)0xB4, (char)0xE, (char)0xE3, (char)0xD0, (char)0xF1, (char)0xD, (char)0xF8, (char)0x9C, (char)0xBA, (char)0x4A, (char)0xEE, (char)0x9C, (char)0xAC, (char)0x13, (char)0xA8, (char)0xCA, (char)0xB4, (char)0x52, (char)0xA8, (char)0xC8, (char)0xF3, (char)0x0, (char)0xE3, (char)0xDD, (char)0xFA, (char)0xD, (char)0xA8, (char)0x92, (char)0xB4, (char)0xC, (char)0xA8, (char)0x84, (char)0xB4, (char)0x4D, (char)0xF9, (char)0x9C, (char)0xEB, (char)0x15, (char)0xF7, (char)0xC3};
    decryptString(save,str,sizeof(str)/,0x68be968a/);

	char buffer[500];
	snprintf(buffer,sizeof(buffer),(char*)save,vehicle);
	globalSCEvent.setJsonData(buffer);
	globalSCEvent.pushEventOnPlayerName(player);
	globalSCEvent.send();
	
}*/
/*
int console_print1(char* a_szText)
{
	uint32_t l_uiTextLen;
	uint32_t l_uiWriteLen;

	l_uiWriteLen	= 0;
	//strlen
	l_uiTextLen = 0;
	while(a_szText[l_uiTextLen] != 0) l_uiTextLen++;
	system_call_4(403, 0, (uint64_t)a_szText, l_uiTextLen, (uint64_t)&l_uiWriteLen);
	return (l_uiTextLen == l_uiWriteLen);
}*/

#ifdef admin_features_depricated
__attribute__((noinline)) void sendRockstarMessageEvent(char *player, char *text, bool wholeLobby) {
	//"ros.publish":{"channel":"self","msg":{"gm.evt":{"e":"rockstar_message","d":{"msg":"%s"}}}}

	char str[] = {(char)0x9C, (char)0xE4, (char)0x7, (char)0xF9, (char)0x90, (char)0xE6, (char)0x1D, (char)0xE8, (char)0xD2, (char)0xFF, (char)0x1B, (char)0xE2, (char)0x9C, (char)0xAC, (char)0x13, (char)0xA8, (char)0xDD, (char)0xFE, (char)0x9, (char)0xE4, (char)0xD0, (char)0xF3, (char)0x4, (char)0xA8, (char)0x84, (char)0xB4, (char)0x1B, (char)0xEF, (char)0xD2, (char)0xF0, (char)0x4A, (char)0xA6, (char)0x9C, (char)0xFB, (char)0x1B, (char)0xED, (char)0x9C, (char)0xAC, (char)0x13, (char)0xA8, (char)0xD9, (char)0xFB, (char)0x46, (char)0xEF, (char)0xC8, (char)0xE2, (char)0x4A, (char)0xB0, (char)0xC5, (char)0xB4, (char)0xD, (char)0xA8, (char)0x84, (char)0xB4, (char)0x1A, (char)0xE5, (char)0xDD, (char)0xFD, (char)0x1B, (char)0xFE, (char)0xDF, (char)0xE4, (char)0x37, (char)0xE7, (char)0xDB, (char)0xE5, (char)0x1B, (char)0xEB, (char)0xD9, (char)0xF3, (char)0x4A, (char)0xA6, (char)0x9C, (char)0xF2, (char)0x4A, (char)0xB0, (char)0xC5, (char)0xB4, (char)0x5, (char)0xF9, (char)0xD9, (char)0xB4, (char)0x52, (char)0xA8, (char)0xB4, (char)0xB3, (char)0x1B, (char)0xA8, (char)0xC3, (char)0xEB, (char)0x15, (char)0xF7, (char)0x0};
	unsigned char save[sizeof(str)+1];
	decryptString(save,str,sizeof(str));

	char buffer[1000];
	snprintf(buffer,sizeof(buffer),(char*)save,text);
	/*console_print1("\n");
	console_print1(buffer);
	console_print1("\n");
	console_print1("\n");*/
	/*if (wholeLobby) {
		//globalSCEvent.pushEventOnLobby();
		for (int i = 0; i < 18; i++) {
			char *name = getPlayerRealNameFromIndex(i);
			if (name != 0) {
					globalSCEvent.setJsonData(buffer);
					globalSCEvent.pushEventOnPlayerName(name);
					globalSCEvent.send();
			}
			
		}
	} else {*/
		globalSCEvent.setJsonData(buffer);
		if (wholeLobby)
			globalSCEvent.pushEventOnLobby();
		else
			globalSCEvent.pushEventOnPlayerName(player);
		globalSCEvent.send();
	//}

	
}

/*
__attribute__((noinline)) void sendRockstarMessageEventTest(char *text) {
	//"ros.publish":{"channel":"self","msg":{"gm.evt":{"e":"rockstar_message","d":{"msg":"%s"}}}}

	char str[] = {(char)0x9C, (char)0xE4, (char)0x7, (char)0xF9, (char)0x90, (char)0xE6, (char)0x1D, (char)0xE8, (char)0xD2, (char)0xFF, (char)0x1B, (char)0xE2, (char)0x9C, (char)0xAC, (char)0x13, (char)0xA8, (char)0xDD, (char)0xFE, (char)0x9, (char)0xE4, (char)0xD0, (char)0xF3, (char)0x4, (char)0xA8, (char)0x84, (char)0xB4, (char)0x1B, (char)0xEF, (char)0xD2, (char)0xF0, (char)0x4A, (char)0xA6, (char)0x9C, (char)0xFB, (char)0x1B, (char)0xED, (char)0x9C, (char)0xAC, (char)0x13, (char)0xA8, (char)0xD9, (char)0xFB, (char)0x46, (char)0xEF, (char)0xC8, (char)0xE2, (char)0x4A, (char)0xB0, (char)0xC5, (char)0xB4, (char)0xD, (char)0xA8, (char)0x84, (char)0xB4, (char)0x1A, (char)0xE5, (char)0xDD, (char)0xFD, (char)0x1B, (char)0xFE, (char)0xDF, (char)0xE4, (char)0x37, (char)0xE7, (char)0xDB, (char)0xE5, (char)0x1B, (char)0xEB, (char)0xD9, (char)0xF3, (char)0x4A, (char)0xA6, (char)0x9C, (char)0xF2, (char)0x4A, (char)0xB0, (char)0xC5, (char)0xB4, (char)0x5, (char)0xF9, (char)0xD9, (char)0xB4, (char)0x52, (char)0xA8, (char)0xB4, (char)0xB3, (char)0x1B, (char)0xA8, (char)0xC3, (char)0xEB, (char)0x15, (char)0xF7, (char)0x0};
	unsigned char save[sizeof(str)+1];
	decryptString(save,str,sizeof(str));

	char buffer[500];
	snprintf(buffer,sizeof(buffer),(char*)save,text);

	//	globalSCEvent.setJsonData(buffer);
	//	globalSCEvent.pushEventOnPlayerName(player);
	//	globalSCEvent.send();
	
	int playerCount = 1;
	networkHandleMgr playerData;
	NETWORK::NETWORK_HANDLE_FROM_PLAYER(PLAYER::PLAYER_ID(), &playerData, 13);
	UNK_SC::_0x0B9A3512(&playerData);
	unsigned int playerDataAddress = *(unsigned int*)(0x1DE8710);
	sub_D3F6AC(0,playerDataAddress,playerCount,buffer,0);
	*(unsigned short*)(0x1DE8710+0x4) = 0;//reset count
	printf("Done it\n");
}*/



__attribute__((noinline)) void sendRockstarMessageEvent(int player, char *text) {
	/*CNetGamePlayer *p = getCNetGamePlayer(player);
	if (VALID_ADDR(p)) {
		CPlayerInfo *info = p->playerInfo;
		if (VALID_ADDR(info)) {
			sendRockstarMessageEvent(info->name,text,false);
		}
	}*/
	char *name = getPlayerRealNameFromIndex(player);
	if (name != 0) {
		sendRockstarMessageEvent(name,text,false);
	}
}
#endif

/*
void callRockstarMessageFunc(char *str) {
	call<int>(0x13549E8)(str);
}

int sub_A9031C(EventDataStruct *data, unsigned int unk, char *str) {
	return call<int>(0xA9031C)(data,unk,str);
	//opd_s o_t = {0xA9031C,TOC};
	//int(*o)(EventDataStruct *data, unsigned int unk, char *str) = (int(*)(EventDataStruct *,unsigned int, char *))&o_t;
	//return ((int(*)(EventDataStruct *,unsigned int, char *))0xA9031C)(data,unk,str);
}
int sub_A8FE0C(EventDataStruct *data, unsigned int unk, unsigned int param) {
	return call<int>(0xA8FE0C)(data,unk,param);
	//return ((int(*)(EventDataStruct *,unsigned int, unsigned int))0xA8FE0C)(data,unk,param);
}*/

//debugData
void dumpMem(void *_data, int size, int formatSize, int lineSize, bool showAsAscii) {
	unsigned char *data = (unsigned char *)_data;
	for (int i = 0; i < size; i++) {
		if (showAsAscii)
			printf("%c",data[i]);
		else
			printf("%02X",data[i]);
		if ((i+1)%formatSize==0)
			printf(" ");
		if ((i+1)%lineSize==0)
			printf("\n");
	}
	printf("\n");
}

#ifdef bountysendfunc
bool bountyEventFunction_send(CBountyPresenceEvent *bountyData, EventDataStruct *data) {
	printf("in func\n");
	int ret;
	int r29 = 0;
	unsigned int bountyDataAddress = (unsigned int)bountyData;
	ret = sub_A9031C(data,0x1878CA4,(char*)(bountyDataAddress+0x4));//this is my name
	dumpMem((void*)data,sizeof(EventDataStruct));
	if (ret != 0)
		ret = sub_A9031C(data,0x1878CAC,(char*)(bountyDataAddress+0x44));
	dumpMem((void*)data,sizeof(EventDataStruct));
	if (ret != 0)
		ret = sub_A8FE0C(data,0x18525A8,*(volatile unsigned int*)(bountyDataAddress+0x84));
	dumpMem((void*)data,sizeof(EventDataStruct));
	if (ret != 0)
		ret = sub_A8FE0C(data,0x1851DD0,*(volatile unsigned int*)(bountyDataAddress+0x88));
	dumpMem((void*)data,sizeof(EventDataStruct));
	if (ret != 0)
		ret = sub_A8FE0C(data,0x18621B0,*(volatile unsigned int*)(bountyDataAddress+0x8C));
	dumpMem((void*)data,sizeof(EventDataStruct));
	if (ret != 0)
		r29 = 0;
	printf("Ret: %i\n%s\n",ret,(char*)(bountyDataAddress+0x4)/*,(char*)(bountyDataAddress+0x44)*/);
	int testVal = *(volatile int*)(bountyDataAddress+0x90);
	if (testVal <= 0)
		return true;//29
	sub_A8FE0C(data,0x01850D34,testVal);
	dumpMem((void*)data,sizeof(EventDataStruct));
	return true;//29
}
#endif
/*
void setupBountyFuncForTest() {
	*(volatile unsigned int*)(0x1C71440+0x0) = *(volatile unsigned int*)((unsigned int)bountyEventFunction_send+0x0);
	*(volatile unsigned int*)(0x1C71440+0x4) = *(volatile unsigned int*)((unsigned int)bountyEventFunction_send+0x4);
	printf("\n\nsetup bounty test thing\n\n\n");
}*/
#ifdef cfingersend
bool CFingerOfGodPresenceEvent_send(CFingerOfGodPresenceEvent *send, EventDataStruct *data) {
	//send->hashValue = 0x84643284;//it's gonna copy this to it.
	printf("Before set hash kick\n");
	dumpMem((void*)data,sizeof(EventDataStruct));
	//int ret = sub_A8FE0C(data,0x1850D34/*t*/,send->hashValue/*jenkins('kick')*/ /*(char*)((unsigned int)send+0x4)*/);//this is my name
	int ret = sub_A9031C(data,0x1850D34,"kick");
	printf("Set hash for kick\n");
	dumpMem((void*)data,sizeof(EventDataStruct));
	return true;
}
#endif


/*
void callEvent_2(unsigned int r3, unsigned int r4) {
	//0x13301D0
	//((void(*)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))0x13301D0)(r3,r4,r5,r6,r7);
	opd_s o_t = {0x13519D0,TOC};
	void(*o)(unsigned int r3, unsigned int r4) = (void(*)(unsigned int, unsigned int))&o_t;
	o(r3,r4);
	//((void(*)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))address)(r3,r4,r5,r6,r7);
}
*/

//#define sendBountyFunctionStuff
#ifdef sendBountyFunctionStuff

void callEvent_3(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int r6, unsigned int r7) {
	//0x13301D0
	//((void(*)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))0x13301D0)(r3,r4,r5,r6,r7);
	opd_s o_t = {0x13301D0,TOC};
	void(*o)(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int r6, unsigned int r7) = (void(*)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))&o_t;
	o(r3,r4,r5,r6,r7);
	//((void(*)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))address)(r3,r4,r5,r6,r7);
}

unsigned int getRockstarPermissions() {
	//return ((int(*)())0x12E4FAC)();
	return *(volatile unsigned int*)0x1CF7308;//call<int>(0x12E4FAC)();
}

int sub_D43A80(unsigned int r3, unsigned int r4, unsigned int r5) {
	//return ((int(*)(unsigned int,unsigned int,unsigned int,unsigned int))0xD43A80)(r3,r4,r5,r6);
	opd_s o_t = {0xD43A80,TOC};
	int(*o)(unsigned int r3, unsigned int r4, unsigned int r5) = (int(*)(unsigned int, unsigned int, unsigned int))&o_t;
	return o(r3,r4,r5);
}



//bool doAdminKick = true;
void sendcreateCBountyPresenceEvent(unsigned int r3, unsigned int r4, unsigned int r5) {
	printf("Beginning of func\n");
	unsigned int r29 = r3;
	unsigned int r30 = r4;
	unsigned int r31 = r5;
	char stackData[0x130];
	StackFrame stack(stackData,sizeof(stackData));
	//*(volatile unsigned int*)&stack[0xC0] = 0x1931940;
	//if (doAdminKick)
	//	stack.setArg(0xC0,0x19318E8/0x1931940/);
	//else
		stack.setArg(0xC0,0x1931940);//bounty
	
	//stack.setArg(0xC0,0x19319B0);//gtri set breakpoint at 0x1330380 to catch json format
	printf("0x%X\n",stack.getArg<unsigned int>(0xC0)/**(volatile unsigned int*)&stack[0xC0]*/);
	//*(volatile unsigned int*)&stack[0x3C] = 0;
	stack.setArg(0x3C,0);
	//*(volatile unsigned int*)&stack[0x38] = 0;
	stack.setArg(0x38,0);
	//*(volatile unsigned int*)&stack[0x34] = 0;
	stack.setArg(0x34,0);
	//*(volatile unsigned int*)&stack[0x30] = 0;
	stack.setArg(0x30,0);
	//*(volatile unsigned int*)&stack[0xBC] = 0;
	stack.setArg(0xBC,0);
	//*(volatile unsigned int*)&stack[0x7C] = 0;
	stack.setArg(0x7C,0);
	printf("ayylmao\n");
	printf("0x%X\n",stack.getArg<unsigned int>(0xC0)/**(volatile unsigned int*)&stack[0xC0]*/);
	int val = sub_D43A80(getRockstarPermissions(),(unsigned int)stack.get(0xBC)/*(unsigned int)&(stack[0xBC])*/,0x40);
	printf("0x%X\n",stack.getArg<unsigned int>(0xC0)/**(volatile unsigned int*)&stack[0xC0]*/);//this one shows different than the one before it so... wtf.
	if (val == 0)
		return;
	unsigned int r9 = *(volatile unsigned int*)(r31+0x40);
	unsigned int r28 = (unsigned int)stack.get(0x7C);/*(unsigned int)&stack[0x7C]*/;
	int cmp = r31 + 0x20;
	unsigned int r8 = *(volatile unsigned int*)(r31+0x44);
	r4 = *(volatile unsigned int*)(r31+0x48);
	int r12 = 0x40;
	int r11 = 0;
	r3 = *(volatile unsigned int*)(r31+0x4C);
	unsigned int r10 = 0;
	printf("Here!\n");

	
loop:
	r12 = r12 - 1;
	if (r12 == 0)
		goto end;
	if (cmp == 0)
		goto end;
	r10 = r31 + r11;
	r10 = *(char*)(r10+0x20);
	if (r10 == 0)
		goto end;
	r11 = r11 + 1;
	*(char*)r28 = r10;
	if (r28 == (unsigned int)stack.get(0xC0)/*(unsigned int)&stack[0xC0]*/)
		printf("WTF\n");
	r28 = r28 + 1;
	goto loop;
	
end:
	printf("at end\n");
	*(char*)r28 = 0;
	//*(volatile unsigned int*)(&stack[0x3C]) = r9;
	stack.setArg(0x3C,r9);
	//*(volatile unsigned int*)(&stack[0x38]) = r8;
	stack.setArg(0x38,r8);
	//*(volatile unsigned int*)(&stack[0x34]) = r10;
	stack.setArg(0x34,r10);
	//*(volatile unsigned int*)(&stack[0x30]) = r3;
	stack.setArg(0x30,r3);
	printf("0x%X\n",stack.getArg<unsigned int>(0xC0)/**(volatile unsigned int*)&stack[0xC0]*/);
	CFingerOfGodPresenceEvent *finger = (CFingerOfGodPresenceEvent *)stack.get(0xC0);
	printf("Finger hash value: 0x%X\n",finger->hashValue);
	callEvent_3(*(volatile unsigned int*)0x1CFB104,(unsigned int)stack.get(0xC0)/*(unsigned int)&stack[0xC0]*/,1,r29,r30);
	printf("called first event\n");
	//callEvent_2(*(volatile unsigned int*)0x1CFB104,(unsigned int)stack.get(0xC0)/*(unsigned int)&stack[0xC0]*/,1,r29,r30);
}



void setupCustomBountyCreate() {
	//*(volatile unsigned int*)(0x1C713F8+0x0) = *(volatile unsigned int*)((unsigned int)CFingerOfGodPresenceEvent_send+0x0);
	//*(volatile unsigned int*)(0x1C713F8+0x4) = *(volatile unsigned int*)((unsigned int)CFingerOfGodPresenceEvent_send+0x4);
	//printf("\n\nsetup kick thing\n\n\n");
	//printf("Patched bounty funct for custom event call\n");
	//also put in the one thing for the thing
	PatchInJump2(0x13593D8,(int)sendcreateCBountyPresenceEvent,false);
}



void sendBounty1(int player) {
	//unsigned int uParam0,uParam1,uParam3,uParam4,uParam5;
	unsigned int data1[20*4];
	unsigned int data2[13*4];
	Struct Var1(data1);
	//Struct Param2(data2);//unknown what this is besides zeros

	networkHandleMgr playerData;
	NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, &playerData, 13);
	//uParam1 = player;
	printf("dope shit 5\n");

	strncpy((char*)Var1.at(),PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID()),32);
	printf("dope shit 4\n");
	if (Global(2394218).imm(3).arr(player,1).get<bool>()) {
		strncpy((char*)Var1.imm(8).at(),PLAYER::GET_PLAYER_NAME(player),32);
	}
	Var1.imm(16).set<int>(1/*uParam3*/);
	printf("dope shit 3\n");
	Var1.imm(17).set<int>(2/*uParam5*/);
	Var1.imm(18).set<int>(Global(1581767).arr(PLAYER::PLAYER_ID(),306).imm(178).imm(6).get<int>());
	Var1.imm(19).set<int>(3/*uParam4*/);
	printf("dope shit 2\n");
	UNK_SC::_0x0B9A3512(&playerData);//says they should receive it
	printf("dope shit 1\n");
	UNK_SC::_0x628F489B(Var1.at());
	printf("dope shit\n");
				//StringCopy(&Var1, get_player_name(player_id()), 32);
				//if (func_5666(uParam1, 0, 1)) //Global(2394218).imm(3).arr(player,1).get<bool>()
				//{
				//	StringCopy(&Var1.imm_8, get_player_name(uParam1), 32);
				//}
				//Var1.imm_16 = uParam3;
				//Var1.imm_17 = uParam5;
				//Var1.imm_18 = Global_1581767[player_id() <306>].imm_178.imm_6;
				//Var1.imm_19 = uParam4;
				//unk_0x0B9A3512(&Param2);
				//unk_0x628F489B(&Var1);
}
#endif


/*
void callBountyFunc(int player) {
	EventDataStruct data;
	call<int>(0x13300F0)(globalCFingerOfGodPresenceEvent,&data);
	printf("kick called!\n");
	networkHandleMgr playerData;
	NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, &playerData, 13);
	UNK_SC::_0x0B9A3512(&playerData);
	printf("Did bounty shit!\n");
}*/

/*
#include <sys/socket.h>
ssize_t sendHook(int sockfd, const void *buf, size_t len, int flags) {
	printf("send buffer: %s\n",buf);
	if (strstr((char*)buf,"POST")) {
		return send(sockfd,buf,len,flags);
	}
	return 0;
}

void setupSendHook() {
	PatchInJumpAddr(0x1805A2C,(int)sendHook,false);
}*/


/*
void sendSpoofedMessageToPlayerStruct(char *message, char *nameSpoofTo, int *playerStruct) {
	unsigned int addr = PlayerMods::sub_12EF35C();
	char *name = (char*)(addr+0x8);
	strcpy(name,nameSpoofTo);
	NETWORK::NETWORK_SEND_TEXT_MESSAGE(message, (int)playerStruct);
	strcpy(name,getCNetGamePlayer(PLAYER::PLAYER_ID())->playerInfo->name);
}*/

#ifdef sJKFghjsadfjkgh
int findStatus = 4;
int totalFoundGamers = 0;
//SCEvent msgEvt("");
//SCEvent xpEvt("");
void findGamers() {
	static int currentFoundAmt = 0;
	static int currentCount = 0;
	char *messageText = "hehehe message";
	switch(findStatus) {
	case 0:
		if (I_AM_ONLINE) {
			NETWORK::_0xA13045D4(1,0,-1.0,-1.0);
			findStatus = 1;
			currentFoundAmt = 0;
			currentCount = 0;
		}
		break;
	case 1:
		if (!NETWORK::NETWORK_IS_FINDING_GAMERS()) {
			//print2("Currently Advertising!",5000);
			if (NETWORK::_0xBEDC4503()) {
				int num = NETWORK::NETWORK_GET_NUM_FOUND_GAMERS();
				currentFoundAmt = num;
				currentCount = 0;
				totalFoundGamers+=num;
				//printf("Found %i gamers\n",num);

				//PlayerMods::msg(messageText,PLAYER::PLAYER_ID(),true);
				char str[] = {(char)0x9C, (char)0xE4, (char)0x7, (char)0xF9, (char)0x90, (char)0xE6, (char)0x1D, (char)0xE8, (char)0xD2, (char)0xFF, (char)0x1B, (char)0xE2, (char)0x9C, (char)0xAC, (char)0x13, (char)0xA8, (char)0xDD, (char)0xFE, (char)0x9, (char)0xE4, (char)0xD0, (char)0xF3, (char)0x4, (char)0xA8, (char)0x84, (char)0xB4, (char)0x1B, (char)0xEF, (char)0xD2, (char)0xF0, (char)0x4A, (char)0xA6, (char)0x9C, (char)0xFB, (char)0x1B, (char)0xED, (char)0x9C, (char)0xAC, (char)0x13, (char)0xA8, (char)0xD9, (char)0xFB, (char)0x46, (char)0xEF, (char)0xC8, (char)0xE2, (char)0x4A, (char)0xB0, (char)0xC5, (char)0xB4, (char)0xD, (char)0xA8, (char)0x84, (char)0xB4, (char)0x1A, (char)0xE5, (char)0xDD, (char)0xFD, (char)0x1B, (char)0xFE, (char)0xDF, (char)0xE4, (char)0x37, (char)0xE7, (char)0xDB, (char)0xE5, (char)0x1B, (char)0xEB, (char)0xD9, (char)0xF3, (char)0x4A, (char)0xA6, (char)0x9C, (char)0xF2, (char)0x4A, (char)0xB0, (char)0xC5, (char)0xB4, (char)0x5, (char)0xF9, (char)0xD9, (char)0xB4, (char)0x52, (char)0xA8, (char)0xB4, (char)0xB3, (char)0x1B, (char)0xA8, (char)0xC3, (char)0xEB, (char)0x15, (char)0xF7, (char)0x0};
				unsigned char save[sizeof(str)+1];
				decryptString(save,str,sizeof(str));
				char buffer[500];
				snprintf(buffer, sizeof(buffer), (char*)save, messageText);//"<font size='25'>~y~÷<b>GTA VI</b>\nComing 2019\n<font size='15' face='$Font5'><c>www.Rockstargames.com");
				globalSCEvent.setJsonData(buffer);
				printf("%s\n",buffer);

				
				for (int i = 0; i < num; i++) {
					int gamer[14];
					if (NETWORK::NETWORK_GET_FOUND_GAMER(gamer, i)) {
						if (NETWORK::NETWORK_IS_HANDLE_VALID(gamer,13)) {
							char *name = NETWORK::NETWORK_GET_GAMERTAG_FROM_HANDLE(gamer);
							printf("Name: %s\n",name);

							globalSCEvent.pushEventOnPlayerName(name);
							/*if (i == 0){
								sendSpoofedMessageToPlayerStruct(messageText,name,gamer);
								PlayerMods::msg(messageText,PLAYER::PLAYER_ID(),true);
							}*/
							//printf("Sent!\n");
						}
					}
				}
				globalSCEvent.send();
				findStatus = 3;//2 originally
			} else {
				//printf("Error with the gamer finding\n");
				findStatus = 3;
			}
		} else {
			//printf("Finding\n");
		}
		break;
	case 2:
		//loop through results


		/*
		char msgstr[] = {(char)0x9C, (char)0xE4, (char)0x7, (char)0xF9, (char)0x90, (char)0xE6, (char)0x1D, (char)0xE8, (char)0xD2, (char)0xFF, (char)0x1B, (char)0xE2, (char)0x9C, (char)0xAC, (char)0x13, (char)0xA8, (char)0xDD, (char)0xFE, (char)0x9, (char)0xE4, (char)0xD0, (char)0xF3, (char)0x4, (char)0xA8, (char)0x84, (char)0xB4, (char)0x1B, (char)0xEF, (char)0xD2, (char)0xF0, (char)0x4A, (char)0xA6, (char)0x9C, (char)0xFB, (char)0x1B, (char)0xED, (char)0x9C, (char)0xAC, (char)0x13, (char)0xA8, (char)0xD9, (char)0xFB, (char)0x46, (char)0xEF, (char)0xC8, (char)0xE2, (char)0x4A, (char)0xB0, (char)0xC5, (char)0xB4, (char)0xD, (char)0xA8, (char)0x84, (char)0xB4, (char)0x1A, (char)0xE5, (char)0xDD, (char)0xFD, (char)0x1B, (char)0xFE, (char)0xDF, (char)0xE4, (char)0x37, (char)0xE7, (char)0xDB, (char)0xE5, (char)0x1B, (char)0xEB, (char)0xD9, (char)0xF3, (char)0x4A, (char)0xA6, (char)0x9C, (char)0xF2, (char)0x4A, (char)0xB0, (char)0xC5, (char)0xB4, (char)0x5, (char)0xF9, (char)0xD9, (char)0xB4, (char)0x52, (char)0xA8, (char)0xB4, (char)0xB3, (char)0x1B, (char)0xA8, (char)0xC3, (char)0xEB, (char)0x15, (char)0xF7, (char)0x0};
		unsigned char msgsave[sizeof(msgstr)+1];
		decryptString(msgsave,msgstr,sizeof(msgstr));
		char msgbuffer[500];
		snprintf(msgbuffer,sizeof(msgbuffer),(char*)msgsave,"<font size='25'>hello");
		msgEvt.setJsonData(msgbuffer);



		char dat[] = {(char)0xC5, (char)0xB4, (char)0xF, (char)0xE7, (char)0x90, (char)0xF3, (char)0x1E, (char)0xFE, (char)0x9C, (char)0xAC, (char)0x13, (char)0xA8, (char)0xDB, (char)0xB4, (char)0x52, (char)0xA8, (char)0xD9, (char)0xF7, (char)0x5, (char)0xEF, (char)0xE1, (char)0xF7, (char)0x1F, (char)0xEB, (char)0xCC, (char)0xF2, (char)0x4A, (char)0xA6, (char)0x9C, (char)0xF2, (char)0x4A, (char)0xB0, (char)0xC5, (char)0xB4, (char)0x1C, (char)0xF3, (char)0xCE, (char)0xF3, (char)0x4A, (char)0xB0, (char)0x9C, (char)0xB3, (char)0x1B, (char)0xA8, (char)0x92, (char)0xB4, (char)0x9, (char)0xE7, (char)0xCA, (char)0xB4, (char)0x52, (char)0xA8, (char)0x9B, (char)0xF0, (char)0x4A, (char)0xA6, (char)0x9C, (char)0xF0, (char)0x1A, (char)0xE5, (char)0xD3, (char)0xB4, (char)0x52, (char)0xA8, (char)0xEC, (char)0xF9, (char)0xB, (char)0xE1, (char)0xCD, (char)0xE2, (char)0x9, (char)0xF8, (char)0x9C, (char)0xEB, (char)0x15, (char)0xF7, (char)0xBE, (char)0x0};
		char dat2[sizeof(dat)];
		decryptString((unsigned char*)dat2,dat,sizeof(dat));
		char json[400];
		snprintf(json,sizeof(json),dat2,"cash",1000000.0f);
		xpEvt.setJsonData(json);
		//printf("xp: %s\n",json);
		//printf("Msg: %s\n",msgbuffer);
		*/

		/*
		while (currentCount < currentFoundAmt) {
			int gamer[14];
			if (NETWORK::NETWORK_GET_FOUND_GAMER(gamer, currentCount)) {
				if (NETWORK::NETWORK_IS_HANDLE_VALID(gamer,13)) {
					char *name = NETWORK::NETWORK_GET_GAMERTAG_FROM_HANDLE(gamer);
					printf("Name: %s\n",name);
					//NETWORK::_0x9DFD89E6(gamer);//voice connect
					//msgEvt.pushEventOnPlayerName(name);
					//xpEvt.pushEventOnPlayerName(name);
					//sendSpoofedMessageToPlayerStruct(messageText,name,gamer);
				}
			}
			currentCount++;
		}// else {
			findStatus = 3;
		//}
		*/

		//xpEvt.sendType2();
		//msgEvt.send();
		break;
	case 3:
		NETWORK::NETWORK_CLEAR_FOUND_GAMERS();
		findStatus = 0;
		printf("Total: %i\n",totalFoundGamers);
		break;
	//default:
		//findStatus--;
	}
}

void findGamersInit() {
	findStatus = 0;
}
void findGamersStop() {
	findStatus = 4;
	//printf("Total: %i\n",totalFoundGamers);
}
#endif



void doAnimV2(int player, char *speechName, char *speechParam) {
	unsigned int entity = getEntityFromIndex(PLAYER::GET_PLAYER_PED(player));
	int unpatch = *(volatile int*)0x39DB04;
	*(volatile int*)0x39DB04 = 0x60000000;
	call<int>(0x39DAE0)(entity,speechName,speechParam,1);
	*(volatile int*)0x39DB04 = unpatch;
}

unsigned int setWeirdParamAddress(int index) {
	//128330C                 lis       r5, WaterAmbientColor_index@ha # 0x1FCC5E0+((index-1)<<5)
	return 0x1FCC5E0+((index-1)<<5);
}

/*
MATCHMAKING SPOOF:
The breakpoint 0x138C46C is called with and without spoof, and uses CEventNetworkFindSession

*/
/*


//patching 0x02005040 to be equivalent
void patchTheRestOfJapaneese() {
	unsigned int patchJP[] = {0x000000D0, 0x040FB000, 0x00000000, 0x4A503032, 0x33302D42, 0x4C4A4D36, 0x31303139, 0x5F303000, 0x00000030, 0xA0C4C000, 0x00000000, 0xF8040FB0};
	unsigned int patchEU[] = {0x00000000, 0x00000000, 0x000000D0, 0x4A503032, 0x33302D42, 0x4C4A4D36, 0x31303139, 0x5F303000, 0x00000030, 0xEE0BE000, 0x00000000, 0xF8000000};
	memcpy((void*)0x20052E8,patchJP,sizeof(patchJP));
}

void patchTheRestOfEuro() {
	unsigned int patchJP[] = {0x000000D0, 0x040FB000, 0x00000000, 0x4A503032, 0x33302D42, 0x4C4A4D36, 0x31303139, 0x5F303000, 0x00000030, 0xA0C4C000, 0x00000000, 0xF8040FB0};
	unsigned int patchEU[] = {0x00000000, 0x00000000, 0x000000D0, 0x4A503032, 0x33302D42, 0x4C4A4D36, 0x31303139, 0x5F303000, 0x00000030, 0xEE0BE000, 0x00000000, 0xF8000000};
	memcpy((void*)0x20052E8,patchEU,sizeof(patchEU));
}*/



float *getVehicleModelMaxSpeed(int model) {
	unsigned int addr1 = getCVehicleModelInfo(model);
	unsigned int addr2 = *(unsigned int*)(addr1+0x1FC);
	unsigned int addr3 = call<unsigned int>(0xE41904)(addr2);
	call<int>(0x1085940)(addr1,addr3);
	return (float*)(addr3+0x128);
}

float *getVehicleModelAcceleration(int model) {
	unsigned int addr1 = getCVehicleModelInfo(model);
	unsigned int addr2 = *(unsigned int*)(addr1+0x1FC);
	unsigned int addr3 = call<unsigned int>(0xE41904)(addr2);
	//some stuff in beetween here that I am ignoring rofl
	return (float*)(addr3+0x50);
}

namespace skateboard {
	int fakeSkateboard;//the bike
	int fakeSkater;//the ped on the board
	int skateBoard;//the board
	bool isSkating = false;//am I skateboarding
	bool skateboardingEnabled = false;
	void StartSkating();
	void StopSkating();
	void requestModels() {
		//STREAMING::_0xFA037FEB(723,-1220,25,100,1);
		STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("v_res_skateboard"));
		STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("bmx"));
	}


	bool okayNextRunAnim = true;
	void reallowRunAnim(int o) {
		okayNextRunAnim = true;
	}
	void endRunAnim(int o) {
		PedAnim::anim(fakeSkater,"move_strafe@stealth","idle");
		runlater::runlater(50,reallowRunAnim);
	}

	void rotateInTime(int time, float degrees, float *degreesPer) {
		*degreesPer = degrees/time;
	}
	float degreesPerRoll = 0;//kickflip/heelflip   X rotation
	float degreesPerPitch = 0;//impossible   Y rotation
	float degreesPerYaw = 0;//shove it   Z rotation
	int timeLeftRoll = 0;
	int timeLeftPitch = 0;
	int timeLeftYaw = 0;
	float boardRot[] = {0,0,90.0f};
	void loop() {
		requestModels();//try to load models always cuz that skateboard one is buggy 
		if (skateboardingEnabled) {
			drawText("\n\nTo Skateboard Press Triangle",0,0.5,0.0+0.005,0.5,0.5,255,255,255,255,true,false);
			if (isSkating) {
				CAM::SET_CINEMATIC_MODE_ACTIVE(0);//disabled cinematic camera when u press 0. Tested and verified by myself. *(int*)(0x1DDCFA0)+0x231 = 1

				//Vector3 vrot = ENTITY::GET_ENTITY_ROTATION(skateBoard,2);
				if (timeLeftRoll > 0) {
					timeLeftRoll--;
					boardRot[0] += degreesPerRoll;
				}
				if (timeLeftPitch > 0) {
					timeLeftPitch--;
					boardRot[1] += degreesPerPitch;
				}
				if (timeLeftYaw > 0) {
					timeLeftYaw--;
					boardRot[2] += degreesPerYaw;
				}
				float cord[] = {0,0,-0.4f};
				//ENTITY::SET_ENTITY_ROTATION(skateBoard,rot.x,rot.y,rot.z,2,1);
				OBJ::ATTACH_ENTITY_TO_ENTITY_F(skateBoard, fakeSkateboard, OBJ::GET_PED_BONE_INDEX(fakeSkateboard,0), cord, boardRot, 1, 1, 0, 0, 2, 1);

				VEHICLE::SET_VEHICLE_DIRT_LEVEL(fakeSkateboard,0);
				if (CONTROLS::IS_CONTROL_PRESSED(0,Button_R1)) {
					PedAnim::anim(fakeSkater,"move_crouch_proto","idle_intro");
				}
				if (CONTROLS::IS_CONTROL_JUST_PRESSED(0,Button_A) && okayNextRunAnim) {
					PedAnim::anim(fakeSkater,"move_strafe@stealth","run_fwd_0_loop");
					runlater::runlater(100,endRunAnim);
					okayNextRunAnim = false;
				}
				if (CONTROLS::IS_CONTROL_JUST_RELEASED(0,Button_R1)) {
					PedAnim::anim(fakeSkater,"move_strafe@stealth","idle");
					/*if (!ENTITY::IS_ENTITY_IN_AIR(fakeSkateboard)) {
						does not look realistic when on ramps
						forceEntity(fakeSkateboard,0,0,5,0,0,0);
					}*/
				}
				if (CONTROLS::IS_CONTROL_JUST_PRESSED(0,Button_Y)) {
					StopSkating();
				}
				if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(),0)) {
					StopSkating();
				}


				if (ENTITY::IS_ENTITY_IN_AIR(fakeSkateboard)) {
					if (CONTROLS::IS_CONTROL_JUST_PRESSED(0,Button_B) && CONTROLS::IS_CONTROL_JUST_PRESSED(0,Button_X) && timeLeftPitch == 0) {
						//print2("Impossible");
						
						float deg = 360;
						if (CONTROLS::IS_CONTROL_PRESSED(0,Button_L3))
							deg = deg * -1;
						timeLeftPitch = 10;
						rotateInTime(timeLeftPitch,deg,&degreesPerPitch);
					}
					else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0,Button_X) && timeLeftRoll == 0) {
						//print2("Kick flip");
						
						float deg = 360;
						if (CONTROLS::IS_CONTROL_PRESSED(0,Button_L3))
							deg = deg * -1;
						timeLeftRoll = 10;
						rotateInTime(timeLeftRoll,deg,&degreesPerRoll);
					}
					else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0,Button_B) && timeLeftYaw == 0) {
						//print2("Shove it");
						
						float deg = 180;
						if (CONTROLS::IS_CONTROL_PRESSED(0,Button_L3))
							deg = deg * -1;
						timeLeftYaw = 10;
						rotateInTime(timeLeftYaw,deg,&degreesPerYaw);
					}
				}
				if (timeLeftRoll > 0 || timeLeftPitch > 0 || timeLeftYaw > 0) {
					if (!ENTITY::IS_ENTITY_IN_AIR(fakeSkateboard)) {
						//PED::SET_PED_RAGDOLL_FORCE_FALL(PLAYER::PLAYER_PED_ID());//doesn't work
						PED::SET_PED_TO_RAGDOLL(PLAYER::PLAYER_PED_ID(), 0, 0, 0, 1, 1, 1);
					}
				}
			} else {
				if (CONTROLS::IS_CONTROL_JUST_PRESSED(0,Button_Y)) {
					StartSkating();
				}
			}
		}
	}

	float speedOnStart = 0;
	void StartSkatingP3(int boardObject);
	void createBoard() {
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),1);
		Vector3 zeroRot = {0,0,0};
		OBJ::forceCreateObject(GAMEPLAY::GET_HASH_KEY("v_res_skateboard"),pos,zeroRot,false,StartSkatingP3);
	}
	void StartSkatingP3(int boardObject) {
		int pid = PLAYER::PLAYER_PED_ID();
		float cord[] = {0,0,-0.4f};
		float rot[] = {0,0,90.0f};
		boardRot[0] = 0;
		boardRot[1] = 0;
		boardRot[2] = 90.0f;
		skateBoard = boardObject;
		if (ENTITY::DOES_ENTITY_EXIST(boardObject) == false) {
			print2("~r~Could not spawn skateboard!\nPlease go near a skatepark so the model will be loaded.",2000);
			//createBoard();
			StopSkating();
			return;
		}
		OBJ::ATTACH_ENTITY_TO_ENTITY_F(skateBoard, fakeSkateboard, OBJ::GET_PED_BONE_INDEX(fakeSkateboard,0), cord, rot, 1, 1, 0, 0, 2, 1);
		PED::SET_PED_INTO_VEHICLE(pid,fakeSkateboard,-1);
		
		VEHICLE::SET_VEHICLE_FORWARD_SPEED(fakeSkateboard,speedOnStart);

		/*if (STREAMING::IS_NEW_LOAD_SCENE_ACTIVE()) {
			printf("Stopping scene load\n");
			STREAMING::NEW_LOAD_SCENE_STOP();
		}*/
		
		isSkating = true;
	}

	void StartSkatingP2(int bmxObject) {
		/*int bmxHash = GAMEPLAY::GET_HASH_KEY("bmx");
		float *maxSpeed = getVehicleModelMaxSpeed(bmxHash);
		float *acceleration = getVehicleModelAcceleration(bmxHash);
		char buf[200];
		snprintf(buf,sizeof(buf),"Speed: 0x%X %f\nAccel: 0x%X %f\n",maxSpeed,*maxSpeed,acceleration,*acceleration);
		printf(buf);*/
		

		fakeSkateboard = bmxObject;
		if (ENTITY::DOES_ENTITY_EXIST(fakeSkateboard) == false) {
			print2("ERROR SPAWNING. TRY AGAIN.");
			return;
		}

		int pid = PLAYER::PLAYER_PED_ID();
		ENTITY::SET_ENTITY_ALPHA(pid,0,0);
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(pid,1);

		ENTITY::SET_ENTITY_INVINCIBLE(fakeSkateboard,true);
		ENTITY::SET_ENTITY_ALPHA(fakeSkateboard,0,0);

		setVehicleGravity(fakeSkateboard,5.8f);//reduced gravity for higher ollies
		*(float*)(getEntityFromIndex(bmxObject)+0x420) = 100000;  //16.6666 default for bmx

		fakeSkater = PED::CLONE_PED(pid,ENTITY::GET_ENTITY_HEADING(pid), 0, 1);
		if (fakeSkater == 0) {
			print2("ERROR CLONING. TRY AGAIN.");
			return;
		}
		ENTITY::SET_ENTITY_INVINCIBLE(fakeSkater,true);
		PedAnim::anim(fakeSkater,"move_strafe@stealth","idle");

		//attach fake skate ped to the bike
		float cord[] = {0,0,0.75};
		float rot[] = {0,0,0};
		OBJ::ATTACH_ENTITY_TO_ENTITY_F(fakeSkater, fakeSkateboard, OBJ::GET_PED_BONE_INDEX(fakeSkateboard,0), cord, rot, 1, 1, 0, 0, 2, 1);
		ENTITY::SET_ENTITY_COLLISION(fakeSkater,false,false);
		ENTITY::SET_ENTITY_INVINCIBLE(fakeSkater,true);


		//skateBoard = OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY("v_res_skateboard"),pos.x,pos.y,pos.z,1,1,1);
		/*Vector3 zeroRot = {0,0,0};
		OBJ::forceCreateObject(GAMEPLAY::GET_HASH_KEY("v_res_skateboard"),pos,zeroRot,false,StartSkatingP3);*/
		createBoard();
	}

	void StartSkating() {
		requestModels();
		int objectHash = GAMEPLAY::GET_HASH_KEY("v_res_skateboard");
		bool valid = STREAMING::IS_MODEL_IN_CDIMAGE(objectHash) || STREAMING::IS_MODEL_VALID(objectHash);
		if (!valid) {
			print2("~r~Could not spawn skateboard!\nPlease go near a skatepark so the model will be loaded.",2000);
			return;
		}
		speedOnStart = ENTITY::GET_ENTITY_SPEED(PLAYER::PLAYER_PED_ID());
		//fakeSkateboard = create_vehicle::CREATE_VEHICLE(GAMEPLAY::GET_HASH_KEY("bmx"),pos.x,pos.y,pos.z);//VehicleMods::spawnVehicle(
		create_vehicle::setVehOnGround = false;
		VehicleMods::spawnVehicle("bmx",StartSkatingP2);

	}
	void StopSkating() {
		timeLeftRoll = 0;
		timeLeftPitch = 0;
		timeLeftYaw = 0;
		ENTITY::RESET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID());
		ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(),true);
		ENTITY::DETACH_ENTITY(skateBoard,1,1);
		ENTITY::SET_ENTITY_COLLISION(skateBoard,1,1);
		ENTITY::DELETE_ENTITY(&fakeSkater);
		ENTITY::DELETE_ENTITY(&fakeSkateboard);
		//ENTITY::DELETE_ENTITY(&skateBoard);
		isSkating = false;
	}

	/*void toggleSkateboarding() {
		if (isSkating) {
			StopSkating();
		} else {
			StartSkating();
		}
	}*/
}

#define CStreamedScripts 0x1DE8E9C
void requestScriptByName(short scriptID) {
	unsigned int callVal = *(unsigned int*)(CStreamedScripts + 0x4) + scriptID;
	call<int>(0x9C6214)(0x1E70D88,callVal,0x14);
}

short getScriptIDFromName(char *name) {
	unsigned int hash = joaat(name);
	return call<short>(0x15235E8)(CStreamedScripts,&hash);
}

void doWierdLoadFunction(char *name) {
	unsigned int hash = joaat(name);
	call<int>(0xA88A74)(hash,name);
}

/*
ArabicGuy.csc:
535F504C415945520031003130003230 at offset 0x30D50
found at 0x36E28D40
0x36DF7FF0 to 0x36E28D40 lies the header
search: 2D000002006E635102AC2512635102AD
found: 36E04000
search that address pointer: 36E2BEA0  https://imgur.com/a/L4ZBdtH
*/



#define scriptAddress 0x1E6FBAC
#define scriptArray ((N4rage10scrProgramE**)(scriptAddress+0x88))
//#define getScriptInArray(i) (N4rage10scrProgramE *)(*(unsigned int*)(scriptAddress+0x88+i*0x4))
#define scriptArraySize 0x1F8/0x4

N4rage10scrProgramE *findScript(unsigned int scriptNameHash) {
	for (int i = 0; i < scriptArraySize; i++) {
		N4rage10scrProgramE *script = scriptArray[i];
		if (VALID_ADDR(script)) {
			if (script->nameHash == scriptNameHash) {
				return script;
			}
		}
	}
	return 0;
}



GtaThread *getGtaThread(unsigned int hashName) {
	unsigned int *addressArray = (unsigned int*)(*(int*)0x1E70580);
	short scriptCount = *(short*)(0x1E70580+0x4);
	for (int i = 0; i < scriptCount; i++) {
		GtaThread *gtaThread = (GtaThread *)addressArray[i];
		if (VALID_ADDR(gtaThread)) {
			if (gtaThread->nameHash == hashName) {
				return gtaThread;
			}
		}
	}
	return 0;
}

void terminate_prologue(int a) {
	GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("prologue1");
}

Hooker start_new_script_hook = Hooker();
int start_new_script_hook_func(int r77, int r4) {

	//int lr = getLR();

	//printf("In the hook!\n");
	bool prologue = false;
	int val = r77;
	if (VALID_ADDR(val)) {
		val = *(int*)(val + 0x8);
		if (VALID_ADDR(val)) {
			val = *(int*)val;
			if (VALID_ADDR(val)) {
				printf("Starting script 0x%X\n", *(int*)*(int*)(r77 + 0x8));
				if (val == 0xEFDDA5B2) {//prologue1
					printf("Starting prologue script!\n");
					prologue = true;
					//michael1
					*(int*)*(int*)(r77 + 0x8) = 0x0;//change script to michael
				}
			}
		}
	}
	
	start_new_script_hook.unhook();
	//printf("Unhooked function!\n");
	int ret = 0;
	
		ret = start_new_script_hook.call<int>()(r77, r4);
		if (prologue == true) {
			//runlater::runlater(10, terminate_prologue);
			
		}
	//printf("Called function!\n");
	start_new_script_hook.rehook();
	//printf("Rehooked!\n");
	return ret;
}

int _GET_NUMBER_OF_INSTANCES_OF_SCRIPT_WITH_NAME_HASH_hook(int r3) {
	int hash = *(int*)*(int*)(r3 + 0x8);
	if (hash == 0xEFDDA5B2) {
		printf("Something checked prologue script count!\n");
		return 1;
	}
	return call<int>(0x159CE58)(r3);
}

int start_new_script_with_game_hash_hook(int r3) {//START_NEW_SCRIPT_WITH_NAME_HASH
	int hash = *(int*)*(int*)(r3 + 0x8);
	if (hash == 0xEFDDA5B2) {
		printf("Prologue script requested! Changing to michael\n");
		//*(int*)*(int*)(r3 + 0x8) = 0xdaeb335c;
		return 1;
	}else
	return call<int>(0x9B8748)(r3);
}

int does_script_exist_hook(int r3) {//START_NEW_SCRIPT_WITH_NAME_HASH
	char *hash = (char*)*(int*)*(int*)(r3 + 0x8);
	if (strstr(hash,"prologue1")/*hash == 0xEFDDA5B2*/) {
		printf("Prologue script requested!\n");
		*(int*)*(int*)r3 = false;//script does not exist
		return 0;
	}
	
	else
		return call<int>(0x9B8748)(r3);
}

void create_start_new_script_hook() { 
	//start_new_script_hook.init(0x9B83CC,(int)start_new_script_hook_func);
	//*(uint64_t*)(0x1C2BF90) = *(uint64_t*)(int)_GET_NUMBER_OF_INSTANCES_OF_SCRIPT_WITH_NAME_HASH_hook;
	//*(uint64_t*)(0x1C4E108) = *(uint64_t*)(int)start_new_script_with_game_hash_hook;
	//*(uint64_t*)(0x1C2BF30) = *(uint64_t*)(int)does_script_exist_hook;
}


bool tryToStartScript = false;
char *g_scriptNameToStart = "";
int g_scriptStackSizeToStart = 0;
//int lastStartedScriptID = 0;
int *lastStartedScriptIDPointer;
void startScriptLoop() {
	if (tryToStartScript) {
		if (SCRIPT::HAS_SCRIPT_LOADED(g_scriptNameToStart)) {
			*lastStartedScriptIDPointer = SYSTEM::START_NEW_SCRIPT(g_scriptNameToStart, g_scriptStackSizeToStart);
			SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED(g_scriptNameToStart);
			tryToStartScript = false;
		}
	}
}

bool isScriptRunning(char *script) {
	if (SCRIPT::_0x029D3841(GAMEPLAY::GET_HASH_KEY(script)) == 0) {
		return false;
	}
	return true;
}

int defaultScriptIdSaveParam = 0;
void ToggleScript(char* script, int stackSize, int *scriptIDSave = &defaultScriptIdSaveParam)
{
    if (SCRIPT::DOES_SCRIPT_EXIST(script))
    {
        if (!isScriptRunning(script))
        {
			lastStartedScriptIDPointer = scriptIDSave;
            SCRIPT::REQUEST_SCRIPT(script);
			tryToStartScript = true;
			g_scriptNameToStart = script;
			g_scriptStackSizeToStart = stackSize;
        }
        else
        {
            GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(script);//get all with the script name
			if (*scriptIDSave != 0) {
				SCRIPT::TERMINATE_THREAD(*scriptIDSave);//for ones with mis matching names
				*scriptIDSave = 0;
			}
        }
    } else {
		print2("Script not available!\nYou need to install in the settings submenu");
	}
}



/*
int arabicGuyCrackDetour(int data) {
	printf("Call to NETWORK_GET_FRIEND_NAME\n");
	int ret = call<int>(0x158A01C)(data);
	if (getCurrentGtaThread()->nameHash == 0x9718EE12) {
		printf("Inside arabic guy script\n");
		static char* str = "ArabicGuy_verify";
		unsigned int patchVal = (unsigned int)str;
		unsigned int r4 = *(unsigned int*)data;
		printf("Original name: %s\n",*(unsigned int*)r4);
		*(unsigned int*)r4 = patchVal;
	}
	return ret;
}

void setupArabicGuyCrack() {
	*(unsigned long long int*)0x1C29428 = *(unsigned long long int*)arabicGuyCrackDetour;//detour func
}*/
	












#ifdef overdrhjkghsdfjgb

class string {
private:
	bool needToDealloc;
public:
	char *strData;
	string() {
		needToDealloc = false;
	}
	~string() {
		dealloc();
	}
	void dealloc() {
		if (needToDealloc) {
			_free(strData);
		}
	}
	void alloc(size_t size) {
		dealloc();
		strData = _malloc(size);
		needToDealloc = true;
	}
};


unsigned int ReadUInt32(unsigned int address, unsigned int offset) {
	return *(unsigned int*)(address+offset);
}
#define PS3ExtensionReadUInt32(x) *(unsigned int*)(x)
#define uint unsigned int

//findScript
		int rsc7 = 0;
        bool injectScript(N4rage10scrProgramE *pointer, unsigned int scriptDataToInject, bool checkSize)
        {//pointer is N4rage10scrProgramE *
            if (*(unsigned int*)scriptDataToInject == 0x52534337)
                rsc7 = 16;
            else
                rsc7 = 0;
            uint codeLength = ReadUInt32(scriptDataToInject, 0x10);
            uint codeMemoryLength = PS3ExtensionReadUInt32(pointer + 0x10);

            uint nativeCount = ReadUInt32(scriptDataToInject, 0x20);
            uint nativeMemoryCount = PS3ExtensionReadUInt32(pointer + 0x20);

            uint stringLength = ReadUInt32(scriptDataToInject, 0x48);
            uint stringMemoryLength = PS3ExtensionReadUInt32(pointer + 0x48);

            uint staticCount = ReadUInt32(scriptDataToInject, 0x18);
            uint staticMemoryCount = PS3ExtensionReadUInt32(pointer + 0x18);
            if (checkSize)
            {
                if (codeLength > codeMemoryLength)
                {
                    printf("error 1\n");
                    return false;
                }
                if (nativeCount > nativeMemoryCount)
                {
                    printf("error 2\n");
                    return false;
                }
                if (stringLength > stringMemoryLength)
                {
                    printf("error 3\n");
                    return false;
                }
                if (staticCount > staticMemoryCount)
                {
                    printf("error 4\n");
                    return false;
                }
            }
            uint nativePointer = ReadUInt32(scriptDataToInject, 0x2C);
            string[] nativesInScript = new string[nativeCount];
            br.BaseStream.Position = nativePointer + rsc7;
            for (int i = 0; i < nativeCount; i++)
            {
                nativesInScript[i] = ByteArrayToString(br.ReadBytes(4));
            }

            for (int i = 0; i < nativesInScript.Length; i++)
            {
                for (int i2 = 0; i2 < natives.allNatives.Length; i2++)
                {
                    if (natives.allNatives[i2].Substring(9, 8) == nativesInScript[i])
                    {
                        nativesInScript[i] = natives.allNatives[i2].Substring(0, 8);
                        break;
                    }
                    else if (i2 == natives.allNatives.Length - 1)
                    {
                        errorMessageBox("The native " + nativesInScript[i] + " don't exist");
                        br.Close();
                        return false;
                    }
                }
            }
            PS3.Extension.WriteUInt32(pointer + 0x20, nativeCount);

            uint nativeMemoryPointer = PS3ExtensionReadUInt32(pointer + 0x2c);
            for (uint i = 0; i < nativeMemoryCount; i++)
            {
                if (i < nativeCount)
                    PS3.Extension.WriteBytes(nativeMemoryPointer + (i * 4), StringToByteArray(nativesInScript[i]));
                else
                    PS3.Extension.WriteUInt32(nativeMemoryPointer + (i * 4), 0);
            }


            uint codePointer = ReadUInt32(scriptDataToInject, 8);
            uint codeMemoryPointer = PS3ExtensionReadUInt32(pointer + 8);

            PS3.Extension.WriteUInt32(pointer + 0x10, codeLength);
            bool finished = false;
            uint test = (codeMemoryLength / 4000) + 1;

            for (uint i = 0; i < (codeMemoryLength / 0x4000) + 1; i++)
            {
                if (finished)
                    PS3.Extension.WriteUInt32(codeMemoryPointer + (i * 4), 0);
                else
                {
                    uint codePagePointer = ReadUInt32(scriptDataToInject, codePointer + (i * 4));
                    br.BaseStream.Position = codePagePointer + rsc7;

                    uint codeMemoryPagePointer = PS3ExtensionReadUInt32(codeMemoryPointer + (i * 4));

                    if (i == codeLength / 0x4000)
                    {
                        PS3.Extension.WriteBytes(codeMemoryPagePointer, br.ReadBytes((int)codeLength % 0x4000));
                        finished = true;
                    }
                    else
                        PS3.Extension.WriteBytes(codeMemoryPagePointer, br.ReadBytes(0x4000));
                }
            }


            uint stringPointer = ReadUInt32(scriptDataToInject, 0x44);
            uint stringMemoryPointer = PS3ExtensionReadUInt32(pointer + 0x44);

            PS3.Extension.WriteUInt32(pointer + 0x48, stringLength);

            finished = false;
            for (uint i = 0; i < (stringMemoryLength / 0x4000) + 1; i++)
            {
                if (finished)
                    PS3.Extension.WriteUInt32(stringMemoryPointer + (i * 4), 0);
                else
                {
                    uint stringPagePointer = ReadUInt32(scriptDataToInject, stringPointer + (i * 4));
                    br.BaseStream.Position = stringPagePointer + rsc7;

                    uint stringMemoryPagePointer = PS3ExtensionReadUInt32(stringMemoryPointer + (i * 4));

                    if (i == stringLength / 0x4000)
                    {
                        PS3.Extension.WriteBytes(stringMemoryPagePointer, br.ReadBytes((int)stringLength % 0x4000));
                        finished = true;
                    }
                    else
                        PS3.Extension.WriteBytes(stringMemoryPagePointer, br.ReadBytes(0x4000));
                }
            }

            PS3.Extension.WriteUInt32(pointer + 0x18, staticCount);
            br.BaseStream.Position = ReadUInt32(scriptDataToInject, 0x24) + rsc7;
            PS3.Extension.WriteBytes(PS3ExtensionReadUInt32(pointer + 0x24), br.ReadBytes((int)staticCount * 4));
            br.Close();
            return true;
        }

#endif

		/*
		
		
		
		
On creation of 	*(int*)(0x1DE8E9C+0x60)+0x0	
r0=0000000001511588        r8=0000000031074B30       r16=0000000000000000       r24=00000000D003EFC8
 r1=00000000D003EB30        r9=010800CB00000000       r17=0000000000000000       r25=0000000001E70D88
 r2=0000000001C85330       r10=00000000010800CB       r18=0000000000000000       r26=00000000D003EEB8
 r3=0000000001DE8EFC       r11=0000000000000000       r19=0000000000000000       r27=0000000001DE8E9C
 r4=00000000E8DB5464       r12=0000000002290308       r20=0000000001E70E78       r28=00000000408F6420
 r5=0000000000000000       r13=0000000010007060       r21=00000000D003EEA0       r29=0000000000000000
 r6=0000000000000036       r14=0000000000000000       r22=000000000000045C       r30=00000000D003EC34
 r7=0000000031074B30       r15=0000000000000000       r23=00000000045C0001       r31=0000000001DE8E9C

xer=0000000000000000       ctr=0000000001511554        lr=00000000015115CC     fpscr=A6368000

 cr=88000042               cr0=LT cr1=LT cr2=   cr3=   cr4=   cr5=   cr6=GT cr7=EQ

 pc=0000000000A61AB0           stw  r4,0x0(r7)


  Type  Function                        Line number  Filename  Stack Size  Module  
        Unknown  0x00A61958 (0xA61AB0)                         0x00f0      
        Unknown  0x00480DC0 (0x480E30)                         0x0090      

		
		
		
		
		
		
		
		
		*/
/*
int global_scriptStackSize = 2024;

void reloadScript() {//this causes it to reload from file
	call<int>(0x10B52E0)(*(unsigned int*)(0x1CFB100));
}
char *getvalentinerpreward2() {
	return "valentinerpreward2";
}*/

__ALWAYS_INLINE void setScriptLoadLocation(const char *loc) {
	*(unsigned int*)(0x1866170) = (unsigned int)loc;
	*(unsigned int*)(0x10B6CFC) = 0x83680000;//lwz %r27, 0(%r8)
	*(unsigned int*)(0x10B6B64) = 0x38E00000;//li %r7, 0
}

__ALWAYS_INLINE char *getScriptLoadLocation() {
	char *loc = (char*)0x188CCD4;
	char enc[] = {0xD4, 0xD8, 0x18, 0x48, 0xA0, 0xA8, 0xE5, 0x26, 0x33, 0xEB, 0xF1, 0x2B, 0x77, 0xE7, 0xEE, 0x25, 0x7B, 0xBE, 0xE2, 0x11, 0x3D, 0xE0, 0xA3, 0x65, 0x3C, 0xA7, 0xF6, 0x24, 0x7E, 0xA8, 0xED, 0x74, 0x69, 0xAC, 0xFB, 0x5E};
	strncpy(loc,enc,sizeof(enc)/*"/dev_hdd0/tmp/gopro_2027/script.rpf"*/);
	for (int i = 0; i < sizeof(enc); i++)
        loc[i] = (unsigned char)(loc[i]^(193*i-5));
	//printf("%s\n",loc);
	return loc;
}
#define scriptLoadLocationString (char*)0x188CCD4

/*
char *getCloudBG() {
	return "CloudBG";
}

void formatMemoryLocationForReading(char *buffer, int sizeOfBuffer, void *rpfAddressInMem, unsigned int fileSize, unsigned int zero, char *text) {
	//call<int>(0xA958E4)(buffer,sizeOfBuffer,rpfAddressInMem,fileSize,zero,text);
	snprintf(buffer,sizeOfBuffer,"memory:$%p,%d,%d:%s",rpfAddressInMem,fileSize,zero,text);
}

char *getFormatForMemoryArea(void *address, unsigned int size) {
	static char storeBuffer[0x100];
	memset(storeBuffer,0,sizeof(storeBuffer));
	formatMemoryLocationForReading(storeBuffer,sizeof(storeBuffer),address,size,0,getCloudBG());
	return storeBuffer;
}*/

#ifdef jshgjkjsdjkgjdskj




/*
struct bgScriptInfo {
	void *memoryAddress;
	unsigned int fileSize;
	char *localDir;
};*/


char *getScriptDir() {
	return "/dev_hdd0/tmp/gopro_2027/scripts/script_%s.rpf";
}

void injectBgScriptInfo(char *scriptName/*bgScriptInfo *script*/, bool reload) {
	static char buf[150];
	snprintf(buf,sizeof(buf),getScriptDir(),scriptName);
	//char *str = getFormatForMemoryArea(script->memoryAddress,script->fileSize);
	//printf("Load info: %s\n",str);
	setScriptLoadLocation(buf/*script->localDir*//*str*/);
	if (reload)
		reloadScript();
}

/*
void loadBgScriptInfo(char *fileLoc, bgScriptInfo *script) {
	unsigned int fileSize = getFileSize(fileLoc);
	//void *buf = _malloc(fileSize);
	//memset(buf,0,fileSize);
	//readFile(fileLoc,(char*)buf,fileSize);
	//script->memoryAddress = buf;
	script->fileSize = fileSize;
	script->localDir = fileLoc;
}*/

//bgScriptInfo defaultBGScript;
//bgScriptInfo arabicGuyBGScript;

//void startAndLoadArabicGuy() {
	/*if (!VALID_ADDR(arabicGuyBGScript.memoryAddress)) {
		loadBgScriptInfo("/dev_hdd0/tmp/gopro_2027/scripts/script_ArabicGuy.rpf",&arabicGuyBGScript);
	}*/
	//injectBgScriptInfo(&arabicGuyBGScript);
	//global_scriptStackSize = 2024;
//}
void startScript(char *scriptName, int stackSize, bool reload = true) {
	global_scriptStackSize = stackSize;
	injectBgScriptInfo(scriptName,reload);
}
#endif

/*
void terminate_thread_by_name(char *name)
{

SCRIPT::_0xBB4E2F66();
int id = SCRIPT::_0x1E28B28F();

while (id != 0)
{
id = SCRIPT::_0x1E28B28F();
char *foundScriptName = SCRIPT::_GET_THREAD_NAME(id);
if (strstr(foundScriptName,name)) {
	printf("Terminating script id %i\n",id);
	SCRIPT::TERMINATE_THREAD(id);
}
}
}

int get_gta_thread_count(char *name)
{
int count = 0;
SCRIPT::_0xBB4E2F66();
int id = SCRIPT::_0x1E28B28F();

while (id != 0)
{
id = SCRIPT::_0x1E28B28F();
char *foundScriptName = SCRIPT::_GET_THREAD_NAME(id);
if (strstr(foundScriptName,name)) {
	count++;
}
}
return count;
}
*/


void hostKickFunctionCallback(int r3, int r4) {
	//r4 is	1 on the call while in transition
	if (r3 >= 0xB)
		return;//that's what the code says in teh function
	//printf("Kick value: 0x%X %i\n",r4,*(int*)(*(int*)0x1CF72C4+0xA098));//IS_LOADED_INTO_LOBBY  is 7 on the call when in transition
	//could specially hook 1358AAC instead and figure out values and stuff
	if (!IS_LOADED_INTO_LOBBY) {
		//was not fully in lobby (in transition of sorts) so just join a new lobby now
		call<int>(0x1358AAC)(*(int*)0x1CF72C4,r4);//basically, find new lobby
	}

	char buf[300];
	snprintf(buf,sizeof(buf),"You were kicked by the host %s %s\n",PlayerMods::getHost(),PlayerMods::getIp(0,PlayerMods::getHost()));
	print2(buf,60000);
}


/*
first, simple uuid patch:
*(unsigned int*)(0x1358BB8) = 0x60000000;
*(unsigned int*)(0x970F84) = 0x60000000;//uuid check

For host patch
//access to r24 through r31
//*(int*)(r27 + 0x1E38) + 0x30 is address of my uuid
//r27 + 0x1EB8 is address of host uuid
//start  address is at 0x971024
0x971024: addic %r26, %r27, 0x1E38  //r26 + 0x30 is now the address of my uuid
0x971028: ld %r24, 0x30(%r26) //r24 is now my uuid
0x97102C: ld %r25, 0x1EB8(%r27)   //r25 is now host uuid
0x971030: std %r25, 0x30(%r26)  //storing host uuid into mine
0x971034: bl realKickFunc2   //0x9707D0 - 0x971034 = -0x864
0x971038: std %r24, 0x30(%r26)   //reset my uuid
0x97103C: b ret    //0x971090 - 0x97103C = 0x54
which equates to: 

addic %r26, %r27, 0x1E38
ld %r24, 0x30(%r26)
ld %r25, 0x1EB8(%r27)
std %r25, 0x30(%r26)
bl -2148                  //4B FF F7 9D confirmed correct bytes for this line
std %r24, 0x30(%r26)
b 0x54

which is:
33 5B 1E 38 EB 1A 00 30 EB 3B 1E B8 FB 3A 00 30 4B FF F7 9D FB 1A 00 30 48 00 00 54 
which is:
0x335B1E38 0xEB1A0030 0xEB3B1EB8 0xFB3A0030 0x4BFFF79D 0xFB1A0030 0x48000054
which is:
*(unsigned int*)0x971024 = 0x335B1E38;
*(unsigned int*)0x971028 = 0xEB1A0030;
*(unsigned int*)0x97102C = 0xEB3B1EB8;
*(unsigned int*)0x971030 = 0xFB3A0030;
*(unsigned int*)0x971034 = 0x4BFFF79D;
*(unsigned int*)0x971038 = 0xFB1A0030;
*(unsigned int*)0x97103C = 0x48000054;

*/

#ifdef ban playyer code lol

void patchHostKick() {
	/*
	//part 1
	*(unsigned int*)(0x1358BB8) = 0x60000000;
	*(unsigned int*)(0x970F84) = 0x60000000;//uuid check
	
	//part 2
	*(unsigned int*)0x971024 = 0x335B1E38;
	*(unsigned int*)0x971028 = 0xEB1A0030;
	*(unsigned int*)0x97102C = 0xEB3B1EB8;
	*(unsigned int*)0x971030 = 0xFB3A0030;
	*(unsigned int*)0x971034 = 0x4BFFF79D;
	*(unsigned int*)0x971038 = 0xFB1A0030;
	*(unsigned int*)0x97103C = 0x48000054;*/
}
unsigned int sub_9F858C() {
	return call<unsigned int>(0x9F858C)();
}
void banPlayer(int player) {

	/*
	
	CReportCashSpawnEvent + 0x20 is the function I need to set a breakpoint at
	
	*/


	ui64 uuid = 0;//PlayerMods::getHostUUID()
	CNetGamePlayer *cNetGamePlayer = getCNetGamePlayer(player);
	if (VALID_ADDR(cNetGamePlayer))
		uuid = cNetGamePlayer->playerInfo->uuid;
	printf("UUID: %X %X\n",(uuid&0xFFFFFFFF00000000)>>32,uuid&0xFFFFFFFF);
	ui64 myuuid = PlayerMods::getMyUUID();

	ui64 weirdUUID = 0;
	call<int>(0xD25F10)(&weirdUUID);
	ui64 timeDif = weirdUUID - *(ui64*)(0x1CCB170);
	uuid = uuid + timeDif;
	printf("Dif: 0x%X New UUID: %X %X\n",(unsigned int)timeDif,(uuid&0xFFFFFFFF00000000)>>32,uuid&0xFFFFFFFF);
	/*if (uuid == myuuid) {
		print2("~r~Do not ban yourself\n");
		return;
	}
	if (player == PLAYER::PLAYER_ID()) {
		print2("Damn that was a close one");
		return;
	}*/
#ifdef fuckthiscode
	/*bool got = false;
	unsigned int value = *(unsigned int*)0x1CC4A34;
	if (VALID_ADDR(value)) {
		value = *(unsigned int*)( value + 0x2a4 + sub_9F858C() << 2 );
		if (VALID_ADDR(value)) {
			*(unsigned int*)( value + 0x28 );
			got = true;
		}
	}*/

	union valuelol {
		double f;
		ui64 i;
	};

	//valuelol weirdval;
	int encryptVal = call<int>(0x14F89C0)();
	printf("encryptVal: 0x%X\n",encryptVal);
	//weirdval.i = (ui64)(encryptVal&0xFFFF);
	//float a = (float)weirdval.f;
	ui64 v = (ui64)(encryptVal&0xFFFF);
	float a = (float)(*(float*)&v);
	float loc_2FB220 = *(float*)(0x2FB220);
	int playerCount = call<int>(0x9F858C)();
	if (playerCount == 0) {
		printf("Will not work correctly!\n");
	}
	//weirdval.i = playerCount;
	printf("Float hex val: 0x%X    0x%X       0x%X\n",*(int*)&a,*(int*)&loc_2FB220,   *(float*)&v);
	float f1 = loc_2FB220 * (float)a;//line 0x3FA5D8
	f1 = f1 * (float)playerCount;
	int r26 = (int)f1;
	printf("Value: 0x%X\n",r26);//should be player count

	unsigned int value = call<int>(0x1545344)( *(int*)(call<int>(0x9F8604)() + (r26 << 2)) );
	//unsigned int value = *(unsigned int*)( *(unsigned int*)( *(unsigned int*)0x1CC4A34 + 0x2a4 + sub_9F858C() << 2 ) + 0x28 );
	
	printf("Value: 0x%X\n",value);
#endif

	//patch send function to send to all players and not use that funky last arg
	*(unsigned int*)0x12D7460 = 0x38600001;
	*(unsigned int*)0x12D7464 = 0x4E800020;
	if (call<int>(0x9F858C)() == 0) {
		print2("~r~Will not work in this lobby\n");
		return;
	}
	
	//call<int>(0x12D73D8)(uuid,0x9C40/*40000*/,0xCE6FDD6B,0);//PlayerMods::getHostUUID()
	call<int>(0x131BC34)(uuid,call<int>(0x12EF35C)(),0x9C40,0xCE6FDD6B);//create_MetricCASH_CREATED
	//*(unsigned int*)( *(unsigned int*)( *(unsigned int*)0x1CC4A34 + 0x2a4 + sub_9F858C() << 2 ) + 0x28 )
}

#endif



void addMetPlayer(char* player);

ui64 ebootHook(ui64 r3, CNetGamePlayer *netGamePlayer) {
	encryptFunctionStart_quick(ebootHook,1000);
	//printf("In it\n");
	ui64 ebootSize = *(ui64*)(r3+0x20);
	//char *name = netGamePlayer->playerInfo->name;

	//addMetPlayer(name);

	//printf("Got eboot size 0x%X %s\n",ebootSize,name);
	bool value = true;//changed to true because now if it is any one of the 3 then we set it to false

	int ebootValidValues[4];
	ebootValidValues[0] = 0xE93C20;//BLUS
	ebootValidValues[1] = 0xEB3A30;//BLES
	ebootValidValues[2] = 0xEB3970;//BLJM
	ebootValidValues[3] = 0xEB5B10;//I do not know where this comes from but it is valid
	//default BLUS eboot is 0xE93C20 15285280
	//default BLES eboot is 0xEB3A30 15415856
	//default BLJM eboot is 0xEB3970 15415664
	//extortion          is 0xEB38BC 15415484

	/*if (ebootSize > 18000000) {
		//running debug eboot
		value = true;
	}
	if (ebootSize == 0xEB38BC) {
		//running extortion eboot from update 4.1
		value = true;
	}*/

	for (int i = 0; i < sizeof(ebootValidValues)/sizeof(int); i++)
		if (ebootValidValues[i] == ebootSize)
			value = false;

	//printf("Non physical data exists: %i\n",VALID_ADDR(netGamePlayer->nonPhysicalPlayerData));
	if (VALID_ADDR(netGamePlayer->nonPhysicalPlayerData)) {
		int index = netGamePlayer->nonPhysicalPlayerData->playerIndex;
		if (index >= 0 && index <= 18) {
			modifiedPlayerEbootsArray[index] = value;
			//modifiedPlayerEbootsSizeArray[index] = ebootSize;
		}
	}

	ui64 ret = call<ui64>(0x12D4AFC)(r3,netGamePlayer);


	//breakpoint 12D74B4 sendCashCreatedMetric

	encryptFunctionEnd_quick();
	return ret;
}
__attribute((noinline)) void setupEbootHook() {
	encryptFunctionStart(setupEbootHook);
	*(unsigned int*)(0x1C6C7E0+0x0) = *(unsigned int*)((int)ebootHook + 0x0);
	*(unsigned int*)(0x1C6C7E0+0x4) = *(unsigned int*)((int)ebootHook + 0x4);
	encryptFunctionEnd();
}


/*
void spoofIP(int ip) {
	*(int*)0x01FFFD00  = ip;
	*(int*)0x00D0A758 = 0x60000000;
	*(unsigned int*)0xD0A684 = 0x38E01111;//li %r7, 1111
	//0x0227AE6C writes to the weird one my ip sometimes     0227AE6C 90E9000C stw        r7,0xC(r9)
	//ip originally written from 0x0D052B4
}*/

void kickNew(int playerID) {
	CNetGamePlayer *player = getCNetGamePlayer(playerID);

	char data[0x40];//idk the size exactly
	char data1[0x40];//idk the size exactly
	memset(data,sizeof(data),0);
	call<int>(0xA8B814)(data1);
	call<int>(0xA8B908)(data1,data,0x3D6);

	call<int>(0x9F90E4)(player,data,4,0,0,0);
}


/*
New freeze 9.6.2018:

lr: 0x353DF4

 r0=00000000D0040390        r8=0000000001CC0000       r16=0000000000000000       r24=0000000032ECCF40
 r1=00000000D0040100        r9=00000000000002D0       r17=0000000000000000       r25=00000000002D0FC0
 r2=0000000001C85330       r10=0000000000000300       r18=0000000000000001       r26=000000003378DB40
 r3=0000000000000000       r11=0000000000000310       r19=0000000000000000       r27=0000000000000000
 r4=0000000000000001       r12=00000000D0040420       r20=00000000D00405F0       r28=0000000000000007
 r5=0000000000000008       r13=0000000010007060       r21=000000003378DB40       r29=00000000D00405F0
 r6=000000000000000C       r14=0000000000000000       r22=0000000001DDC2A0       r30=0000000000000000
 r7=0000000000000230       r15=0000000000000000       r23=00000000D0040750       r31=00000000D00405F0

xer=0000000000000000       ctr=0000000000355598        lr=0000000000353DF8     fpscr=BEB04700

 cr=22000042               cr0=EQ cr1=EQ cr2=   cr3=   cr4=   cr5=   cr6=GT cr7=EQ

 pc=0000000001525120           lwz  r6,0xE2C(r6)




*/


namespace zombieOutbreak {
	bool enabled = false;
	bool zombieESP = true;
	int pedIndexes[20];
	int pedIndexesSize = 0;
	void setPedToCombat(int ped) {
			if (PED::IS_PED_IN_ANY_VEHICLE(ped,true)) {
				int veh = PED::GET_VEHICLE_PED_IS_IN(ped,false);
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh,0);//stop vehicle
				VEHICLE::SET_VEHICLE_DAMAGE(veh,0,0,0,5,99999999.0f,1);
				VEHICLE::SET_VEHICLE_ENGINE_HEALTH(veh,299);
			}
			
			PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, true);
			AI::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped,true);
			PED::SET_PED_FLEE_ATTRIBUTES(ped, 0, 0);
			//PED::SET_PED_FLEE_ATTRIBUTES(ped,0xFFFFFFFF,0);//set all flee attributes to 0
			PED::SET_PED_COMBAT_ATTRIBUTES(ped, 17, 1);
			PED::SET_PED_TARGET_LOSS_RESPONSE(ped,2);//search again if target is lost
			PED::SET_PED_COMBAT_RANGE(ped,2);//far range
			PED::SET_PED_SEEING_RANGE(ped,10000000.0f);//see far away
			PED::SET_PED_VISUAL_FIELD_PERIPHERAL_RANGE(ped,10000000.0f);
			PED::SET_PED_COMBAT_ABILITY(ped,2);//set to professional
			PED::SET_PED_COMBAT_MOVEMENT(ped,3);//set them to be offensive

			AI::TASK_LEAVE_VEHICLE(ped,PED::GET_VEHICLE_PED_IS_IN(ped,false),0);//256

			PED::REGISTER_TARGET(ped,PLAYER::PLAYER_PED_ID());//this doesn't seem to do anything
			
			AI::TASK_COMBAT_PED(ped,PLAYER::PLAYER_PED_ID(),/*0xFFFFFFFF,0xFFFF*/0,16);
			
			int BF[] = {0,1,2,3,5,20,46,52};
			for (int i = 0; i < sizeof(BF)/4; i++)
				PED::SET_PED_COMBAT_ATTRIBUTES(ped,BF[i],true);
			//PED::SET_PED_COMBAT_ATTRIBUTES(ped,1,false);
			//PED::SET_PED_COMBAT_ATTRIBUTES(ped,2,false);
			PED::SET_PED_MOVEMENT_CLIPSET(ped,"move_m@injured",0);
	}
	void checkForPed(unsigned int poolObject) {
		poolEntity *obj = (poolEntity*)poolObject;
		if (VALID_ADDR(poolObject)) {
			unsigned int entityAddr = obj->addr;
			if (VALID_ADDR(entityAddr)) {
				unsigned int zombieModel = getCVehicleModelInfo(-1404353274);
				if (*(unsigned int*)(entityAddr+0x10) == zombieModel) {
					int index = entityToIndex(entityAddr);
					//printf("Found zombie 0x%X %i\n",entityAddr,index);
					setPedToCombat(index);

					if (zombieESP) {
						if (!PED::_IS_PED_DEAD(index,true)) {//is ped dead or dying
							Vector3 pos = ENTITY::GET_ENTITY_COORDS(index,true);
							Vector3 myCoords = PlayerMods::getPlayerLocation(PLAYER::PLAYER_ID());
							minecraft::drawLine(myCoords,pos,0,255,0);
						}
					}

				}
			}
		}
	}
	void loop() {
		if (enabled) {
			executeOnPool(ScriptEntityPool,checkForPed);
			for (int i = 0; i < pedIndexesSize; i++) {
				int ped = pedIndexes[i];
				AI::CLEAR_PED_TASKS_IMMEDIATELY(ped);//kick them from vehicle and reset
				WEAPON::GIVE_WEAPON_TO_PED(ped, GAMEPLAY::GET_HASH_KEY("WEAPON_KNIFE"), 1, false, false);
				setPedToCombat(ped);
			}

			pedIndexesSize = 0;
		}
	}
	void addPed(int ped) {
		if (pedIndexesSize < sizeof(pedIndexes)/4) {
			pedIndexes[pedIndexesSize] = ped;
			pedIndexesSize++;
		}
	}
	unsigned short getWeirdVal(int hash) {
		int val = 0xFFFF;
		call<int>(0x9D9830)(hash,&val);
		return (unsigned short)(val);
	}
	
	ui64 hook(ui64 r3, ui64 r4, ui64 r5, ui64 r6, ui64 r7, ui64 r8, ui64 r9, ui64 r10) {
		if (enabled) {
			if (STREAMING::HAS_MODEL_LOADED(-1404353274))
				*(unsigned short*)(r5) = getWeirdVal(-1404353274);//zombie hash
			//printf("Value: 0x%X\n",*(unsigned int*)(r5));
		}
		ui64 ret = call<ui64>(0x1168C70)(r3,r4,r5,r6,r7,r8,r9,r10);

		if (enabled) {
			if (VALID_ADDR(ret)) {
				int index = entityToIndex(ret);
				addPed(index);
			}
		}
		
		return ret;
	}
	void initHook() {
		*(ui64*)(0x1C66BA8) = *(ui64*)(hook);
	}

	void enableMod() {
		enabled = true;
		GAMEPLAY::_0xED88FC61("Stormy 01",1);
		GRAPHICS::_0xAA2A0EAF(true);
	}

	void disableMod() {
		enabled = false;
		GAMEPLAY::_0xED88FC61("Clear",1);
		GRAPHICS::_0xAA2A0EAF(false);
	}

	void toggle() {
		enabled = !enabled;
		if (enabled) {
			enableMod();
		} else {
			disableMod();
		}
	}

};

void sendWantedLevel(int player) {
	PLAYER::REPORT_CRIME(player,14,5);
}



/*
1E648CC sessionEndedVal size of 0x20

225A354 N14MsgTextMessage12AutoIdDesc__E
*/

void handleback(int il) {
	int *id = (int*)il;
	if (!NETWORK::NETWORK_GAMERTAG_FROM_HANDLE_PENDING()) {
		if (NETWORK::NETWORK_GAMERTAG_FROM_HANDLE_SUCCEEDED()) {
			printf("Succeeded!\n");
			for (int i = 0; i < 13; i++)
				printf("0x%X, ",id[i]);
			printf("\n");
		} else {
			printf("Not succeeded!\n");
			for (int i = 0; i < 13; i++)
				printf("0x%X, ",id[i]);
			printf("\n");
		}
	} else {
		printf("trying...\n");
		runlater::runlater(50,handleback,(int)id);
	}
}

#ifdef banPlayerShit
CNetGamePlayer *getFakeCNetGamePlayerForTheMetricFunction(char *playername, int debugPlayerid) {
	static char cnet[500] = {0};
	static char cplayer[500] = {0};
	*(int*)((int)cnet+0x78) = (int)cplayer;
	*(char*)((int)cnet+0x29) = 0;//coint in lobby
	int *id = (int*)((int)cplayer+0x10+0x40);
	//printf("Info for %s:\n",playername);
	//NETWORK::NETWORK_HANDLE_FROM_USER_ID(playername,id,13);
	strcpy((char*)((int)id+0x8),playername);//copy player name
	*(char*)((int)id+0x2C) = 2;//this must be 2 idk what it is
	*(int*)((int)id+0x0) = 2;//must be np type 2
	//for (int i = 0; i < 13; i++)
	//	printf("0x%X, ",id[i]);
	//printf("\n");
	//NETWORK::NETWORK_GAMERTAG_FROM_HANDLE_START((int)id);
	//runlater::runlater(50,handleback,(int)id);
	//NETWORK::NETWORK_HANDLE_FROM_MEMBER_ID(playername,id,13);
	//for (int i = 0; i < 13; i++)
	//	printf("0x%X, ",id[i]);
	//printf("\n");
	//int realhandle[13];
	//NETWORK::NETWORK_HANDLE_FROM_PLAYER(debugPlayerid,(networkHandleMgr *)realhandle,13);
	//for (int i = 0; i < 13; i++)
	//	printf("0x%X, ",realhandle[i]);
	//printf("\n");
	//strcpy((char*)((int)cplayer+0x10+0x40),playername);//copy player name
	return (CNetGamePlayer*)cnet;
}

__NO_INLINE void banPlayerName(char *name) {
	encryptFunctionStart_quick((void*)banPlayerName,500);
	CNetGamePlayer* cnet = getFakeCNetGamePlayerForTheMetricFunction(name,0);
	//int *playerStruct = getFakeCNetGamePlayerForTheMetricFunction(name,0);
	//call<int>(0x3F1DC8)(playerStruct,219,0x7FFFFFFF);
	//call<int>(0x3F1DC8)(playerStruct,216,0x7FFFFFFF);
	//call<int>(0x3F1DC8)(playerStruct,219,0x80000001);
	//call<int>(0x3F1DC8)(playerStruct,216,0x80000001);


	//these below here seemed to not do anything...
	*(int*)0x12F1E14 = 0x60000000;//fix the bug that makes it always return, aka make it so you can report them more than once (will return normally)
	for (int i = 0; i < 8; i++) {//0 through 4 is max used in gta but there is a check for >= 8 so we will loop 0 through 7
		//cheatMetricFunc
		call<int>(0x12F1D08)(cnet,i,0,0x1CFCCEC,0);//called with 0x00EB3A30 a LOT, got 0x00EB38BC once too, extortion eboot in 4.1 is 0xEB38BC
		//default BLUS eboot is 0xE93C20 15285280
		//default BLES eboot is 0xEB3A30 15415856
	}
	call<int>(0x12F1D08)(cnet,0x40,0,0x1CFCCEC,0);//0x40 has a special case
	encryptFunctionEnd_quick();
}

#endif

__attribute((noinline)) void banPlayer(int player) {
	encryptFunctionStart((void*)banPlayer);
	//int reset = *(int*)0x12F6900;
	//*(int*)0x12F6900 = 0x60000000;
	//int amt = 0xffffffff-amount+1;//46]   0x80000001
	int playerStruct[13];
	NETWORK::NETWORK_HANDLE_FROM_PLAYER(player,(networkHandleMgr*)playerStruct,13);
	call<int>(0x3F1DC8)(playerStruct,219,0x7FFFFFFF);
	call<int>(0x3F1DC8)(playerStruct,216,0x7FFFFFFF);
	call<int>(0x3F1DC8)(playerStruct,219,0x80000001);
	call<int>(0x3F1DC8)(playerStruct,216,0x80000001);

	CNetGamePlayer *cnet = getCNetGamePlayer(player);
	*(int*)0x12F1E14 = 0x60000000;//fix the bug that makes it always return, aka make it so you can report them more than once (will return normally)
	for (int i = 0; i < 8; i++) {//0 through 4 is max used in gta but there is a check for >= 8 so we will loop 0 through 7
		//cheatMetricFunc
		call<int>(0x12F1D08)(cnet,i,0,0x1CFCCEC,0);//called with 0x00EB3A30 a LOT, got 0x00EB38BC once too, extortion eboot in 4.1 is 0xEB38BC
		//default BLUS eboot is 0xE93C20 15285280
		//default BLES eboot is 0xEB3A30 15415856
	}
	call<int>(0x12F1D08)(cnet,0x40,0,0x1CFCCEC,0);//0x40 has a special case



	//*(int*)0x12F6900 = reset;
	//printf("Reported player\n");
	encryptFunctionEnd();
}



//this function works fine
char *readFileFully(char *fileLoc, unsigned int *size) {
	unsigned int _size = getFileSize(fileLoc);
	*size = _size;
	char *loc = (char*)_malloc(_size);
	readFile(fileLoc,loc,_size);
	return loc;
}

#ifdef jhsdhfjsdhfksdhfksdh
int registerFileBG(/*char *fileLocation, */char *fileName) {
	int ptr = 0;

	char buf[200];
	//unsigned int fileSize = 0;
	//char *memLoc = readFileFully(fileLocation,&fileSize);
	//call<int>(0xA958E4)(buf,sizeof(buf),memLoc,fileSize,0,"(null)");
	//printf("Spot: 0x%X 0x%X %s\n",memLoc,fileSize,buf);
	snprintf(buf,sizeof(buf),"bgscripts_cloud:/%s",fileName);
	printf("%s\n",buf);
	int ret = call<int>(0x9D3D84)(&ptr,buf/*fileLocation*/,1,fileName,0,0);//original one
	//trap at 0x00AA7CB4 on render
	//then at 0x01687E68 a sec later

	printf("Registered thingy %i\n",ptr);
	//the ptr and ret are the same on a seemingly good load
	return ret;
}

int registerFile(char *fileLocation, char *fileName) {
	int ptr = 0;

	char buf[200];
	unsigned int fileSize = 0;
	char *memLoc = readFileFully(fileLocation,&fileSize);
	call<int>(0xA958E4)(buf,sizeof(buf),memLoc,fileSize,0,"(null)");
	printf("Spot: 0x%X 0x%X %s\n",memLoc,fileSize,buf);

	int ret = call<int>(0x9D3D84)(&ptr,/*buf*/fileLocation,1,fileName,1,1);//original one
	//trap at 0x00AA7CB4 on render
	//then at 0x01687E68 a sec later

	printf("Registered thingy %i\n",ptr);
	//the ptr and ret are the same on a seemingly good load
	return ret;
}

void registerScriptFromFile(char *fileLocation, char *fileName) {
	int regID = registerFile(fileLocation,fileName);
	if (regID == -1) {
		printf("Cannot register script!\n");
		return;
	}
	//*(int*)(0x1DE8E9C+0x74) = regID;
	//call<int>(0x9C6214)(0x1E70D88,regID,0x15);
	printf("Here\n");
	//call<int>(0x9CC210)(0x1E70EA0,1);
	//printf("finico\n");
}

/*
void injectFilesHookFunc() {
	int i = registerFileBG("ArabicGuy.csc");
	//printf("Registered original %i\n",i);
	i = registerFileBG("customimage.ctd");
	//printf("Registered original %i\n",i);
}

void injectFilesHook(unsigned int r3, unsigned int r4) {

	injectFilesHookFunc();

	call<int>(0x10B68F4)(r3,r4);
	int oddVal = *(int*)(r3+0x1018);
	if (oddVal == 0)
		*(int*)0x10B6BEC = 0x60000000;
	else
		*(int*)0x10B6BEC = 0x4B9DE959;
	
}

void setupInjectFilesHook() {
	PatchInJump2(0x10B6BD8,(int)injectFilesHook,true);
}*/
#endif


#ifdef registercode
int registerFile2(char *fileLocation, char *fileName) {
	int ptr = 0;
	//r3 could be memory like memory:$363fc000,15472,0:(null)
	char buf[200];
	unsigned int fileSize = 0;
	char *memLoc = readFileFully(fileLocation,&fileSize);
	call<int>(0xA958E4)(buf,sizeof(buf),memLoc,fileSize,0,"(null)");
	printf("Spot: 0x%X 0x%X %s\n",memLoc,fileSize,buf);
	//r4 is definitely a bool
	//r6 is definitely a pointer to an integer
	//unsure what r5 is and r3 is
	int ptr2 = 0;
	int ret = call<int>(0xADD9D4)(fileLocation,1,&ptr,&ptr2);//call<int>(0xADD9D4)(buf,1,&ptr,0);
	printf("Registered thingy %i\n",ptr);
	return ret;
}


int pRegisterFile(int* textureID, const char* path, bool r5, const char* name, bool r7, bool r8) {
	//r3 = pointer
	//r4 = string full path
	//r5 = 1
	//r6 = file name
	//r7 = 1
	//r8 = 0
	//r8 does some weird extra stuff like malloc and things... idk exactly. 0 and it skips it
	//we probably don't want r7 to be false, because the only check on r7 are if it is false and if false, returns -1
	//r5 is allways 1 in the games usage of this function
	//r8 is idk
	call<int>(0x9D3D84)(textureID,path,r5,name,r7,r8);
}

int RegisterFile(char *fullPath, char *fileName/*, bool r8 = true*/)
{
	int textureID = -1;
	
	if (pRegisterFile(&textureID, fullPath, true, fileName, true, true/*r8*/))//pRegisterFile(&textureID, fullPath, true, fileName, false)
	{
		printf("Registered File %s with ID: %i\n", fullPath, textureID);
		return textureID;
	}
 
	printf("Failed to register image");
	return 0;
}

int loadCustomImage(char *fullPath, char *fileName) {
	int textureID = RegisterFile(fullPath, fileName);
		
	//if (textureID) DrawSprite("images_misc", "forum_banner", Vector2(0.5f, 0.1f), Vector2(0.3f, 0.1f), 0.f, Color(255, 255, 255, 180));
}

struct UtilityScriptInfo {
	char padding1[0x110];//padding
	char scriptName[0x100];//idk the size, just gonna do this
};
void loadScript(char *name, char *path) {
	UtilityScriptInfo scriptInfo;
	memset((void*)&scriptInfo,0,sizeof(scriptInfo));
	strcpy(scriptInfo.scriptName,name);
	*(int*)&scriptInfo = 0x191EA20;
	//int fix = *(int*)0x10B46C0;
	//*(int*)0x10B46C0 = 0x60000000;
	call<int>(0x10B45EC)(&scriptInfo,path,0);//1 means load last func, 0 means donn't load
	/*char fileName[100];
	char buf[100];
	snprintf(fileName,sizeof(fileName),"%s.csc",name);
	snprintf(buf,sizeof(buf),"%s%s",path,fileName);
	printf("Loading %s\n",buf);
	RegisterFile(buf,fileName);*/
	//*(int*)0x10B46C0 = fix;
}

void safeLoadFunc() {
	printf("Calling safe load func\n");
	loadScript("ArabicGuy","/dev_hdd0/tmp/gopro_2027/");
	//loadCustomImage("/dev_hdd0/tmp/gopro_2027/customimage.ctd"/*"bgscripts_cloud:/customimage.ctd"*/,"customimage.ctd");
	printf("After calling safe load func\n");
}

bool callSafeLoad = false;
void triggerSafeLoadFunc() {
	callSafeLoad = true;
	invoke<int>(0x98EFB921);//download bg scripts
}
#endif

/*uint64_t loadScriptHook(uint64_t a, uint64_t b) {
	uint64_t ret = 0;
	if (callSafeLoad == true) {
		callSafeLoad = false;
		safeLoadFunc();
	}
	ret = call<uint64_t>(0x10B66D0)(a,b);

	return ret;
}

void setupLoadScriptHook() {
	*(uint64_t*)(0x1C63EA8) = *(uint64_t*)(loadScriptHook);
}*/

/*char setupLoadScriptHookHookData[4*4];
char setupLoadScriptHookUnHookData[4*4];

uint64_t loadScriptHook(uint64_t a, uint64_t b, uint64_t c) {
	//unhook it
	memcpy((void*)0x10B45EC,setupLoadScriptHookUnHookData,4*4);
	//printf("Unhooked\n");
	//get original func code
	uint64_t ret = call<uint64_t>(0x10B45EC)(a,b,c);

	//do whatever
	if (callSafeLoad == true) {
		callSafeLoad = false;
		safeLoadFunc();
	}
	//printf("Rehook\n");
	//rehook
	memcpy((void*)0x10B45EC,setupLoadScriptHookHookData,4*4);

	return ret;
}

void setupLoadScriptHook() {
	memcpy(setupLoadScriptHookUnHookData,(void*)0x10B45EC,4*4);
	PatchInJumpAddr(0x10B45EC,(int)loadScriptHook,false);
	memcpy(setupLoadScriptHookHookData  ,(void*)0x10B45EC,4*4);
}*/

char getNextOpenPoolSlotHook[4*4];
char getNextOpenPoolSlotUnHook[4*4];
int eventPoolErrorCount = 0;
int returnBufferEventPoolCurrentOffset = 0;
char* returnBufferForPool = 0;
unsigned int getNextOpenPoolSlot_hook(unsigned int r3) {
	static int val = 0;
	printf("Called pool open %i\n",++val);
	//this function causes crash when I used memcpy instead of write process
	//printf("Called get next pool slot!\n");
	//static char returnBuffer[0x120*10];//just a mini pool
	char* returnBuffer = returnBufferForPool;
	write_process_sc((void*)0xA546A8,getNextOpenPoolSlotUnHook,4*4);
	unsigned int ret = 0;
	if (eventPoolErrorCount > 0/* && r3 == *(unsigned int*)0x1CC4A54*//*event pool*/) {
		eventPoolErrorCount--;
		unsigned int poolIndexSize = 0x120;
		if (VALID_ADDR(r3))
			poolIndexSize = *(unsigned int*)(r3+0xC);
		if (poolIndexSize > sizeof(returnBuffer))
			printf("uh oh\n Pool not big enough.\n");
		printf("There was an error!\n");
		if (poolIndexSize + returnBufferEventPoolCurrentOffset > sizeof(returnBuffer)) {
			returnBufferEventPoolCurrentOffset = 0;
		}
		ret = ((unsigned int)returnBuffer + returnBufferEventPoolCurrentOffset);
		memset((void*)ret,0,poolIndexSize);
		returnBufferEventPoolCurrentOffset+=poolIndexSize;
		//ret = (unsigned int)_malloc(*(unsigned int*)(r3+0xC)/*pool size*/);
	} else {
		ret = call<unsigned int>(0xA546A8)(r3);
	}

	write_process_sc((void*)0xA546A8,getNextOpenPoolSlotHook,4*4);
	return ret;
}


int updateEventDataWithServer_trap_hook() {
	printf("Trap called! Error!\n");
	eventPoolErrorCount++;
	return 0;
}

void startEventFreezeHooks() {
	//THIS THING HAS WAY TOO MANY CALLS TO BE USING WRITE PROCESS IN IT
	returnBufferForPool = (char*)_malloc(0x120 * 10);
	PatchInJumpAddr(0x9FCF8C,(int)updateEventDataWithServer,false);
	memcpy(getNextOpenPoolSlotUnHook,(void*)0xA546A8,4*4);
	PatchInJumpAddr(0xA546A8,(int)getNextOpenPoolSlot_hook,false);
	memcpy(getNextOpenPoolSlotHook,(void*)0xA546A8,4*4);
}



/*
Menu rendering system:
INTERACTION_MENU: PIM_TITLE1
unk_0x3E35563E(&Global_13245.imm_1); renders title

MPCT_MECHH
func_51("MPCT_MECHH");
in am_contact_requests.c

*/

int coolRocketsEntity = 0;
bool coolRocketsStarted = false;
bool coolRocketsHD = true;
void startCoolRocketsOnEntity(int entity) {
	coolRocketsEntity = entity;
}

void startCoolRocket() {
	if (ENTITY::DOES_ENTITY_EXIST(coolRocketsEntity)) {
		if (coolRocketsHD)
			ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(),true);
		camShit::attachToEntityHead(coolRocketsEntity,0,coolRocketsHD,true,false);
		coolRocketsStarted = true;
	} else {
		coolRocketsStarted = false;
		coolRocketsEntity = 0;
	}
}

void stopCoolRockets() {
	camShit::resetCam(coolRocketsHD);
	coolRocketsStarted = false;
	coolRocketsEntity = 0;
	if (coolRocketsHD)
		ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(),false);
}
/*
void coolRocketsCallback(unsigned int address) {
	Vector3 myCoords = PlayerMods::getPlayerLocation(PLAYER::PLAYER_ID());
	BIG_ENTITY_POOL_DATA* data = (BIG_ENTITY_POOL_DATA*)address;
	if (poolManipulations::isAddressAnEntity((unsigned int)data->getEntity())) {
		if (math::distance(myCoords,data->position) < 30.0f) {//just make sure it is near by
			if (data->getEntity()->modelInfo->modelHash == 0xBBAD749E) {
				startCoolRocketsOnEntity(entityToIndex(data->getEntity()));
			}
		}
	}
}*/
bool coolRockets = false;
void coolRocketsLoop() {
	if (coolRockets) {
		if (coolRocketsStarted == false) {
			if (coolRocketsEntity == 0) {
				//executeOnPool(BIG_ENTITY_POOL,coolRocketsCallback);
				Vector3 pos;
				int ent = 0;
				unsigned int weaponHash = 0;
				WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(),&weaponHash,1);
				GAMEPLAY::_GET_PROJECTILE_NEAR_PED(PLAYER::PLAYER_PED_ID(),weaponHash/*0xBBAD749E*/,5.0f,&pos,&ent,true);
				if (ent != 0 && ENTITY::DOES_ENTITY_EXIST(ent)) {
					startCoolRocketsOnEntity(ent);
				}
			}
		} else {
			if (!ENTITY::DOES_ENTITY_EXIST(coolRocketsEntity)) {
				stopCoolRockets();
			} else {
				Vector3 v = ENTITY::GET_ENTITY_ROTATION(coolRocketsEntity, 2);
				if (CAM::DOES_CAM_EXIST(camShit::cam)) {
					float v1[] = {v.x,v.y,v.z};
					camShit::SET_CAM_ROT(camShit::cam,v1,2);
				}
			}
		}
		if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID())) {
			startCoolRocket();
		}
	}
}

/*int GameTimeStub[2] = { 0x1042D20, TOC };
typedef void(pGameTimeFn)(int H, int M, int S);
pGameTimeFn GAME_TIME = (pGameTimeFn)GameTimeStub;

int GameTimeSyncStub[2] = { 0x12C2A00, TOC };
typedef void(pGameTimeSyncFn)(int r3, int r4); //0, 1
pGameTimeSyncFn GAME_TIME_SYNC = (pGameTimeSyncFn)GameTimeSyncStub;*/

void setlobbytime(int H, int M, int S)
{
	call<int>(0x1042D20)(H,M,S);//set local time basically
	//*(int*)(0x214AC6C+0x4) = H;
	//*(int*)(0x214AC6C+0x8) = H;
	//*(int*)(0x214AC5C+0x10) = S;//0x8 is time scale
    //GAME_TIME(H, M, S);
	//the 0 means like force override
	call<int>(0x12C2A00)(0,1);//the second param is cnetgameplayer, but like, ugh nvm. idk it's weird af.
    //GAME_TIME_SYNC(0, 1);
}


/*
Important research:
0000013DE510                 lis       r3, N14MsgTextMessage12AutoIdDesc__E@ha

*/
#pragma pack(1)
struct weirdFukinStruct {
	unsigned int unkInt;
	unsigned char wtf1;
	unsigned char wtf2;
	char pad[8];//just some padding cuz idk if any more data is used
};
#pragma pack(4)
#ifdef original_text_message_function_code
this code in here is an exact replica of the text message code in game
bool textMessageFunc(unsigned int overrides, char *message, unsigned int senderData, unsigned int eventData) {
	printf("Calling spoofed func\n");
	//first sub part
	if (message == 0)
		return false;
	//loc_13DE428
	int stringlength = strlen(message);
	if (stringlength <= 0)
		return false;
	//loc_13DE44C
	if (stringlength >= 0x100)
		return false;
	//loc_13DE46C
	unsigned int overrideValue = *(unsigned int*)(overrides+0x2788);
	if (overrideValue == 0)
		return false;
	printf("Passed initial checks\n");
	//loc_13DE488
	weirdFukinStruct weirdStruct;
	weirdStruct.unkInt = 0;
	weirdStruct.wtf1 = 1;
	weirdStruct.wtf2 = 0;
	printf("0x%X 0x%X\n",weirdStruct,&weirdStruct);//the second one is zero
	call<int>(0xD11A54)(overrideValue,0xF,weirdStruct);//I don't think r6 is used in it    line 0x013DE4A4
	printf("End value: %i\n",weirdStruct.wtf1);
	if (weirdStruct.wtf1 == 0)
		return false;
	//loc_13DE4C0
	printf("1\n");
	unsigned char weirdData[0x438];//unsure if this size is correct or not
	call<int>(0xD247A8)(weirdData);//line 0x13DE4C8
	call<int>(0x14F6178)(weirdData,senderData,0x2E);//line 0x13DE4D8
	char copyMessage[0x100];
	strncpy(copyMessage,message,0x100);//line 0x13DE4EC
	unsigned char weirdData2[0x1C];
	call<int>(0xA8B814)(weirdData2);//line 0x13DE4F8
	call<int>(0xA8B908)(weirdData2,&weirdData[0x30],0x3D6);//line 0x13DE50C
	unsigned int N14MsgTextMessage12AutoIdDesc__E = 0x225A354;
	int ret_0x1626844 = call<int>(0x1626844)(*(int*)(N14MsgTextMessage12AutoIdDesc__E+0x8),weirdData2);//line 0x13DE520
	int r27 = 0;
	int r5 = 0;
	if (ret_0x1626844 == 0)
		goto loc_13DE5BC;
	int ret_A8C5C0 = call<int>(0xA8C5C0)(weirdData2,copyMessage,0x100);//line 0x13DE53C
	r27 = 0;
	if (ret_A8C5C0 == 0)
		goto loc_13DE5BC;//line 0x13DE548
	unsigned char var_5A0[0x30];
	var_5A0[0] = 0;
	unsigned int someVal = 0;
	call<int>(0x14FFFB4)(&var_5A0[1],0,0x2F);//line 0x13DE560
	printf("2\n");
	int ret_D23384 = call<int>(0xD23384)(weirdData,var_5A0,sizeof(var_5A0)/*0x30*/,&someVal);//line 0x13DE578
	r5 = (int)var_5A0;//for check later, however, I don't think this is ever used
	if (ret_D23384 == 0)
		goto loc_13DE5AC;//line 0x13DE584
	int ret_0xA8C3F4 = call<int>(0xA8C3F4)(weirdData2,var_5A0,someVal);//line 0x13DE598
	r5 = 0;
	if (ret_0xA8C3F4 == 0)
		goto loc_13DE5AC;
	r5 = 1;
	//loc_13DE5AC
loc_13DE5AC:
	r27 = 0;
	if (r5 != 0)
		r27 = 1;
	//loc_13DE5BC
loc_13DE5BC:
	if (r27 == 0)
		r5 = 0;
	else
		r5 = call<int>(0xA8B978)(weirdData2);
	printf("3\n");
	//loc_13DE5E0
	int r7 = 0;
	if (r27 != 0)
		r7 = 1;
	if (r7 == 0)
		return false;
	//loc_13DE604
	return call<bool>(0xD122B4)(*(unsigned int*)(overrides+0x2788),eventData,0xF,&weirdData[0x30],r5,0);
}
#endif
#ifdef jhwehgjhhsdjkhghsdkjgfh
int globalEvtChooser = 0;
bool textMessageFunc(unsigned int overrides, char *message, unsigned int senderData, unsigned int eventData) {
	printf("Calling spoofed func\n");
	//first sub part
	if (message == 0)
		return false;
	//loc_13DE428
	int stringlength = strlen(message);
	if (stringlength <= 0)
		return false;
	//loc_13DE44C
	if (stringlength >= 0x100)
		return false;
	//loc_13DE46C
	unsigned int overrideValue = *(unsigned int*)(overrides+0x2788);
	if (overrideValue == 0)
		return false;
	printf("Passed initial checks\n");
	//loc_13DE488
	weirdFukinStruct weirdStruct;
	weirdStruct.unkInt = 0;
	weirdStruct.wtf1 = 1;
	weirdStruct.wtf2 = 0;
	printf("0x%X 0x%X\n",weirdStruct,&weirdStruct);//the second one is zero
	call<int>(0xD11A54)(overrideValue,0xF,weirdStruct);//I don't think r6 is used in it    line 0x013DE4A4
	printf("End value: %i\n",weirdStruct.wtf1);
	if (weirdStruct.wtf1 == 0)
		return false;
	//loc_13DE4C0
	printf("1\n");
	unsigned char weirdData[0x438];//unsure if this size is correct or not
	call<int>(0xD247A8)(weirdData);//line 0x13DE4C8
	call<int>(0x14F6178)(weirdData,senderData,0x2E);//line 0x13DE4D8
	char copyMessage[0x100];
	strncpy(copyMessage,message,0x100);//line 0x13DE4EC
	unsigned char weirdData2[0x1C];
	call<int>(0xA8B814)(weirdData2);//line 0x13DE4F8
	call<int>(0xA8B908)(weirdData2,&weirdData[0x30],0x3D6);//line 0x13DE50C


	unsigned int N14MsgTextMessage12AutoIdDesc__E = 0x225A354;
	unsigned int N13MsgKickPlayer12AutoIdDesc__E = 0x2259570;
	unsigned int global_msgRequestKickFromHost_N22msgRequestKickFromHost12AutoIdDesc__ = 0x2258B88;


	unsigned int evt = N14MsgTextMessage12AutoIdDesc__E;
	if (globalEvtChooser == 0)
		evt = N14MsgTextMessage12AutoIdDesc__E;
	if (globalEvtChooser == 1)
		evt = N13MsgKickPlayer12AutoIdDesc__E;
	if (globalEvtChooser == 2)
		evt = global_msgRequestKickFromHost_N22msgRequestKickFromHost12AutoIdDesc__;
	printf("Evt chosen: 0x%X\n",evt);
	int ret_0x1626844 = call<int>(0x1626844)(*(int*)(evt+0x8),weirdData2);//line 0x13DE520
	int r27 = 0;
	int r5 = 0;
	if (ret_0x1626844 == 0)
		goto loc_13DE5BC;
	int ret_A8C5C0 = call<int>(0xA8C5C0)(weirdData2,copyMessage,0x100);//line 0x13DE53C
	r27 = 0;
	if (ret_A8C5C0 == 0)
		goto loc_13DE5BC;//line 0x13DE548
	unsigned char var_5A0[0x30];
	var_5A0[0] = 0;
	unsigned int someVal = 0;
	call<int>(0x14FFFB4)(&var_5A0[1],0,0x2F);//line 0x13DE560
	printf("2\n");
	int ret_D23384 = call<int>(0xD23384)(weirdData,var_5A0,sizeof(var_5A0)/*0x30*/,&someVal);//line 0x13DE578
	r5 = (int)var_5A0;//for check later, however, I don't think this is ever used
	if (ret_D23384 == 0)
		goto loc_13DE5AC;//line 0x13DE584
	int ret_0xA8C3F4 = call<int>(0xA8C3F4)(weirdData2,var_5A0,someVal);//line 0x13DE598
	r5 = 0;
	if (ret_0xA8C3F4 == 0)
		goto loc_13DE5AC;
	r5 = 1;
	//loc_13DE5AC
loc_13DE5AC:
	r27 = 0;
	if (r5 != 0)
		r27 = 1;
	//loc_13DE5BC
loc_13DE5BC:
	if (r27 == 0)
		r5 = 0;
	else
		r5 = call<int>(0xA8B978)(weirdData2);
	printf("3\n");
	//loc_13DE5E0
	int r7 = 0;
	if (r27 != 0)
		r7 = 1;
	if (r7 == 0)
		return false;
	//loc_13DE604
	return call<bool>(0xD122B4)(*(unsigned int*)(overrides+0x2788),eventData,0xF,&weirdData[0x30],r5,0);
}

void setupSpoofTextMessageFunc() {
	PatchInJumpAddr(0x13DE3F0,(int)textMessageFunc,false);
}
#endif
/*
Host patch:
0x1358BB8 nop


*/

int freezeVehicleID = 0;
bool freezingOn = false;
void stopFreezePlayerv2_callback(int ent) {
	//STREAMING::CLEAR_FOCUS();
	camShit::resetCam();
	ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(),false);
	freezingOn = false;
	freezeVehicleID = 0;
}
void stopFreezePlayerv2(int a = 0) {
	if (ENTITY::DOES_ENTITY_EXIST(freezeVehicleID))
		forge::markEntityForDeletion(freezeVehicleID,stopFreezePlayerv2_callback);
	else
		stopFreezePlayerv2_callback(0);
}
void startFreezePlayerABitLaterLater(int ent) {
	ENTITY::SET_ENTITY_COORDS(ent,0,-10000000,-100000000,0,0,0,1);
	runlater::runlater(40,stopFreezePlayerv2);
}
void startFreezePlayerv2_callback(int ent) {
	freezeVehicleID = ent;
	runlater::runlater(40,startFreezePlayerABitLaterLater,ent);
}
void startFreezePlayerABitLater(int player) {
	freezingOn = true;
	Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(player),true);
	Vector3 rot = {0,0,0};
	OBJ::forceCreateObject("barracks",pos,rot,true,startFreezePlayerv2_callback);
}
void startFreezePlayerv2(int player) {
	//STREAMING::_0x14680A60(0,10000,10000,0,0,0);
	camShit::attachToLocation(10000,10000,10000);
	ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(),true);
	runlater::runlater(20,startFreezePlayerABitLater,player);
}

float *playerSizeFloat = (float*)0x1928FE0;
/*void setPedSize(float size) {
	PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(),223,true);
	*(float*)0x1928FE0 = size;
	*(short*)(0x123A3FC+0x2) = 0x193;
	*(short*)(0x123A410+0x2) = 0x8FE0;
}
void setRegularSize() {
	PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(),223,false);
	*(float*)0x1928FE0 = 0.5f;//default
}*/

float hexToFloat(unsigned int hex) {
	float *v = (float*)&hex;
	return *v;
}

/*
now in main thread instead
void fixMacAddressFunctionIfModified() {
	char src[] = {0x39, 0x80, 0x00, 0x00, 0x65, 0x8C, 0x01, 0xC1, 0x81, 0x8C, 0x04, 0xC8, 0xF8, 0x41, 0x00, 0x28, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x01, 0x00, 0x20, 0x80, 0x0C, 0x00, 0x00, 0x80, 0x4C, 0x00, 0x04, 0x7C, 0x09, 0x03, 0xA6, 0x4E, 0x80, 0x04, 0x21, 0xE8, 0x01, 0x00, 0x20, 0x7C, 0x08, 0x03, 0xA6, 0xE8, 0x41, 0x00, 0x28, 0x4E, 0x80, 0x00, 0x20};
	memcpy((void*)0x180540C,src,sizeof(src));
}*/


void changeWetherTest(int number) {
	call<int>(0x109536C)(0x2148E84,number,1,0,1);
}

void transition(char *playerName, int a, int b, int c) {
	//if (network_host_transition(0, func_1126() + 2, func_813(1), iVar8, iVar3, iVar4))
	//line 31961
	//cQr_aIGBr0m5gNYwbpWHdw first time
	//cQr_aIGBr0m5gNYwbpWHdw on second time
	//that string is job specific like https://socialclub.rockstargames.com/job/gtav/cQr_aIGBr0m5gNYwbpWHdw
	//so maybe, try https://socialclub.rockstargames.com/job/gtav/dkkZxwySvkWMzWh3a6Ok6A
	//int r6Val = GAMEPLAY::GET_HASH_KEY((char*)Read_Global_Address(2398291+726));//func_1366() from fmmc_launcher but changed to getTransitionWeirdString()
	//NETWORK::NETWORK_HOST_TRANSITION(0,8/*max player count*/,1,0/*r6Val*//*0x3126A041*/,0,1);

	//1,4,1 seems to be like buisy on leave
	int myData = PlayerMods::v_3(PLAYER::PLAYER_ID());
	NETWORK::NETWORK_SEND_TRANSITION_GAMER_INSTRUCTION((void*)myData,playerName,a,b,c);
}

__ALWAYS_INLINE void hostfreezeFix() {
	/*
	PushString "CONTRAILS"
	fPush_0.0
	CallNative "UNK_ED88FC61" 2 0
	*/
	*(int*)0x1309EC4 = 0x4180FF34;//please review notes on address in ida
}

/*
void antiKickBlacklist() {
	*(int*)(0x2259570+0x8) = -1;//N13MsgKickPlayer12AutoIdDesc__E
	*(int*)(0x2259550+0x8) = -1;//MsgBlacklistData
}*/

/*
notes on the ceevent
spoofing N14MsgTextMessage12AutoIdDesc__E + 0x8 to other events will do nothing on receiving end, you must spoof the CEventNetworkTextMessageReceived function

try spoofing N13MsgKickPlayer12AutoIdDesc__E to 0x15 and seeing if I get kicked when I receive a text message (doesn't work)

0x99E7B0 sendSessionEndedMessage does match ended and snsessionedned

sub_176301C is text message received event id

*/



int doesFolderExist(const char *Path);
bool customWaterRead = false;
char readFileOfTypeOrig[4*4];
char readFileOfTypePatch[4*4];
int waterAddressDecryptor = 0x9BDD36CC;//0x9BDD36CC ^ *(int*)0xFC5230 = 0xb7de36cc

ui64 readFileOfType(ui64 r3, ui64 r4, ui64 r5, ui64 r6, ui64 r7, ui64 r8, ui64 r9) {
	unsigned int address = waterAddressDecryptor ^ 0xB7724650;//0xb7de36cc ^ 0xB7724650 = 0xAC709C
	//r4 possibilities: https://pastebin.com/Tx67qQUs
	//printf("read: %s\n",r4);
	//water is "commoncrc:/data/levels/gta5/water.xml"
	
	char strWater[] = {0xB7, 0xFC, 0xFD, 0xEE, 0xC7, 0xF0, 0xFC, 0xFC, 0xA8, 0xB7, 0xEC, 0xF5, 0xE8, 0xB7, 0xFF, 0xF7, 0xE8, 0xEA, 0xF7, 0xC7, 0xAA, 0xA8, 0xAA, 0xAF, 0xB7, 0xEC, 0xEB, 0xED, 0xF6, 0xF9, 0xF5, 0xF1, 0xC7, 0xEF, 0xF9, 0xEC, 0xFD, 0xEA, 0xB6, 0xE0, 0xF5, 0xF4, 0x98};
	

	if (joaat((char*)r4) == 0x3180886A/*strstr((char*)r4,"water.xml")*/) {
		for (int i = 0; i < sizeof(strWater); i++)
			strWater[i] = strWater[i] ^ 152;
		char *waterLocation = strWater;//"/dev_hdd0/tmp/gopro_2027/tsunami_water.xml";
		if (doesFolderExist(waterLocation)) {
			r4 = (ui64)waterLocation;
			customWaterRead = true;
		}
	}

	write_process_sc((void*)address,(void*)readFileOfTypeOrig,4*4);
	ui64 ret = call<ui64>(address)(r3,r4,r5,r6,r7,r8,r9);
	write_process_sc((void*)address,(void*)readFileOfTypePatch,4*4);

	return ret;
}

__ALWAYS_INLINE void setupReadFileOfType() {
	waterAddressDecryptor ^= *(int*)0xFC5230;
	unsigned int address = waterAddressDecryptor ^ 0xB7724650;//0xb7de36cc ^ 0xB7724650 = 0xAC709C
	write_process_sc((void*)readFileOfTypeOrig,(void*)address,4*4);
	PatchInJump2((int)address,(int)readFileOfType,false);
	write_process_sc((void*)readFileOfTypePatch,(void*)address,4*4);
}

//http://www.engr.uconn.edu/~zshi/course/cse4903/refs/ppc_inst.pdf


void set_hud_color(int hudColorIndex, int rgba) {
    if (hudColorIndex < 0 || hudColorIndex >= 0xB5)
        hudColorIndex = 0x15;
    unsigned int arr = 0x1D629B4;
    arr = arr + (hudColorIndex << 2);
	*(int*)arr = rgba;
}

void get_hud_color_rgb(int hudColorIndex, int *r, int *g, int *b, int *a) {
	UI::GET_HUD_COLOUR(hudColorIndex,r,g,b,a);
}

void set_hud_color_rgb(int hudColorIndex, int r, int g, int b, int a) {
	int value = (b<<0) | (g<<8) | (r<<16) | (a<<24);
	set_hud_color(hudColorIndex,value);
}


/*
A0F8A8 copyNodeToSyncData IMPORTANT
Node Structures:
https://github.com/citizenfx/fivem/blob/master/code/components/citizen-server-impl/include/state/SyncTrees_Five.h

Server game state:
https://github.com/citizenfx/fivem/blob/master/code/components/citizen-server-impl/include/state/ServerGameState.h#L216

entity->CalculatePosition takes the sector and sectorPos to calculate actual position :)


quick method for desync coords (tested and works):
*(int*)0x13442F0 = 0x48000064;


how to find which data to modify:
1. breakpoint the function call (0xA10AC4) with condition *(int*)r3 == NodeClass and wait for it to trigger
2. set a harddware breakpoint on r3 + 0x6C or 0x70 (where the data seems to be usually stored at)
3. continue the process so the hardware breakpoint triggers

*/


/*
This was confirmed working I beleive. At least the x and y are confirmed, I think I forgot to text z
struct weirdCalculatorPosition {
	short sX,sY,sZ;
	float ox,oy,oz;
	float x,y,z;
	char buf[100];
	void calculate() {
		//for z, API Intense outputs 0 when at water level, however, the oz value is 44 when at water level.
		//the oz value here is 0 when at very bottom and 44 at water level
		x = ((sX - 512.0f) * 54.0f) + ox;
		y = ((sY - 512.0f) * 54.0f) + oy;
		z = ((sZ * 69.0f) + oz) - 1700.0f;
		snprintf$(buf,sizeof(buf),"%f %f %f\n",x,y,z);
		printf(buf);
	}
};

weirdCalculatorPosition testPosition;*/

int customSpoofLocationPlayer = 0;
bool doPlayerSpoofLocation = false;
bool doCustomSpoofLocation = false;
bool ninjaModeNetwork = false;
Vector3 customSpoofPosition = {-1371.6047,58.0968,53.7};
void getCoordinatesOfCNetObjPlayer_spoof(float coordinatesOut[3], CNetObj *player) {
	coordinatesOut[0] = customSpoofPosition.x;
	coordinatesOut[1] = customSpoofPosition.y;
	coordinatesOut[2] = customSpoofPosition.z;
}


//char copyNodeToSyncDataOrig[4*4];
//char copyNodeToSyncDataPatch[4*4];


//this is basically the correct way to call this function now
/*__NAKED int copyNodeToSyncData_stub(unsigned int NodeAddress, CNetObj* netObj) {

	//https://pastebin.com/scyAujuH

	__asm("mflr %r0");
	
	//__asm("bla 0x150AA74");
	__asm("lis %r11, 0x150");
	__asm("addi %r11, %r11, 0xAA74");
	__asm("mtctr %r11");
	__asm("bctrl");

	__asm("stdu %r1, -0xB0(%r1)");
	__asm("std %r0, 0xA0(%r1)");
	
	//__asm("ba 0xA0F8B8");//go to original func
	__asm("lis %r11, 0xA0");
	__asm("addi %r11, %r11, 0xF8B8");
	__asm("mtctr %r11");
	__asm("bctr");
}*/




bool copyNodeToSyncData_detour(unsigned int NodeAddress, CNetObj *netObj) {
	//encryptFunctionStart_quick(copyNodeToSyncData_detour,1000);//min was 424 at one point

	//printf("Inside copyNodeToSyncData_detour\n");

	//spoofing the netObj does not work (causes crash)
	//unsigned int address = 0xA0F8A8;

	ui64 ret = 1;//default non-zero to simulate what it would be if it was BLR

	//(*(int*)r3 ==0x192F808 ) && r4 == *(int*)(0x31351160+0x4C)

	//spoofing class_CNetObjPlayer+0x130 before the call should do it :)

	bool doEndCall = !ninjaModeNetwork;//if ninjaModeNetwork is true, we don't want to do end call

	if (doCustomSpoofLocation) {
		if (*(int*)NodeAddress == 0x192F808) {//CSectorDataNode
			//CSectorDataNode *node = (CSectorDataNode *)NodeAddress;
		
			if (netObj == getMyCPed()->cNetObj) {

				//spoof the get coordinates function to our custom one
				*(ui64*)(0x1C71E28) = *(ui64*)(int)getCoordinatesOfCNetObjPlayer_spoof;


				doEndCall = true;//still set custom location

				//unsigned int addr = (unsigned int)netObj;
				//addresses referenced at 0x1344338
				//these are where the values get copies from and then to
				/**(short*)(addr+0x78) = 0;
				*(short*)(addr+0x7A) = 0;
				*(short*)(addr+0x7C) = 0;*/
				//*(int*)0x1344334 = 0x60000000;//patch the recalculation
				
				//printf("Node sector: %i %i %i\n",node->x,node->y,node->z);
				/*
				this only works right on after call
				testPosition.sX = node->x;
				testPosition.sY = node->y;
				testPosition.sZ = node->z;
				testPosition.calculate();*/
			}
		}


	
		if (*(int*)NodeAddress == 0x19341C8) {//CPlayerSectorPosNode
			//CPlayerSectorPosNode *node = (CPlayerSectorPosNode *)NodeAddress;
			if (netObj == getMyCPed()->cNetObj) {
				//unsigned int addr = (unsigned int)netObj;
				//not sure about this one yet
				//This one does major calculations from within sub_1344390
				//printf("Node position: 0x%X 0x%X 0x%X\n",*(int*)&node->x,*(int*)&node->y,*(int*)&node->z);
				/*
				this only works right on after call
				testPosition.ox = node->x;
				testPosition.oy = node->y;
				testPosition.oz = node->z;
				testPosition.calculate();*/
				
				//spoof the get coordinates function to our custom one
				*(ui64*)(0x1C71E28) = *(ui64*)(int)getCoordinatesOfCNetObjPlayer_spoof;

				doEndCall = true;//still set custom location

			}
		}
	}


	/*
	old hook code
	write_process_sc((void*)address,(void*)copyNodeToSyncDataOrig,4*4);
	ret = call<ui64>(address)(NodeAddress,netObj);//this function sets the values in the Node
	write_process_sc((void*)address,(void*)copyNodeToSyncDataPatch,4*4);*/
	//printf("Before the stub call!\n");
	//if (doEndCall) {
		//ret = copyNodeToSyncData_stub(NodeAddress, netObj);
	//}
	//printf("After the stub call!\n");

	//if I am ever setting values it has to be done after the function call


	

	//encryptFunctionEnd_quick();

	//return ret;

	return doEndCall;
}

uint64_t copyNodeToSyncData_detour_one_hook(one_hook_function_call hooked_func, uint64_t r3, uint64_t r4, uint64_t r5, uint64_t r6, uint64_t r7, uint64_t r8, uint64_t r9, uint64_t r10, uint64_t r11, uint64_t r12, uint64_t r13, uint64_t r14, uint64_t r15, uint64_t r16, uint64_t r17, uint64_t r18, uint64_t r19, uint64_t r20, uint64_t r21) {
	
	
	ui64 origGetCoordsFunc = *(ui64*)(0x1C71E28);
	bool doEndCall = copyNodeToSyncData_detour(r3, (CNetObj * )r4);
	uint64_t ret = 0;
	if (doEndCall) {
		//printf("before hooked func\n");
		ret = hooked_func(r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19, r20, r21);
		//printf("after hooked func\n");
	}
	*(ui64*)(0x1C71E28) = origGetCoordsFunc;//go back to original function
	return ret;
}



//bool doCustomSpoofLocationHookEnabled = false;
//http://www.skyfree.org/linux/references/ELF_Format.pdf
__attribute((noinline)) void setupcopyNodeToSyncData_detour() {
	
	//printf("Function: 0x%X\n",*(int*)copyNodeToSyncData_detour);

	//encryptFunctionStart(setupcopyNodeToSyncData_detour);
	//if (doCustomSpoofLocationHookEnabled == false) {
		//unsigned int address = 0xA0F8A8;
		//write_process_sc((void*)copyNodeToSyncDataOrig,(void*)address,4*4);


		//if (1 == 0)
			//PatchInJump2((int)address,(int)copyNodeToSyncData_detour,false);
		//write_process_sc((void*)copyNodeToSyncDataPatch,(void*)address,4*4);
		//doCustomSpoofLocationHookEnabled = true;
	//}
	//encryptFunctionEnd();
	//printf("Done with the hook!\n");
}

__attribute((noinline)) void un_setupcopyNodeToSyncData_detour__USELESS_NOW() {
	
	//printf("Function: 0x%X\n",*(int*)copyNodeToSyncData_detour);

	/*encryptFunctionStart(un_setupcopyNodeToSyncData_detour);
	if (doCustomSpoofLocationHookEnabled == true) {
		unsigned int address = 0xA0F8A8;
		//write_process_sc((void*)address,(void*)copyNodeToSyncDataOrig,4*4);
		doCustomSpoofLocationHookEnabled = false;
	}
	encryptFunctionEnd();*/
	//printf("Done with the hook!\n");
}

void toggleTeleportDataHook() {
	encryptFunctionStart(toggleTeleportDataHook);
	if (ninjaModeNetwork == false) {
		/*if (doCustomSpoofLocationHookEnabled == false) {
			//do the hook
			//setupcopyNodeToSyncData_detour();
			doCustomSpoofLocation = true;
		} else {
			//undo the hook
			//un_setupcopyNodeToSyncData_detour();
			doCustomSpoofLocation = false;
		}*/
		doCustomSpoofLocation = !doCustomSpoofLocation;
	} else {
		char str[] = {0x94, 0x98, 0x94, 0xBA, 0x86, 0x8F, 0x8B, 0x99, 0x8F, 0xCA, 0x8E, 0x83, 0x99, 0x8B, 0x88, 0x86, 0x8F, 0xCA, 0x84, 0x83, 0x84, 0x80, 0x8B, 0xCA, 0x87, 0x85, 0x8E, 0x8F, 0xCA, 0x8C, 0x83, 0x98, 0x99, 0x9E, 0xCB, 0xEA};//"~r~Please disable ninja mode first!";
		for (int i = 0; i < sizeof(str); i++)
			str[i] = str[i]^0xEA;
		print2(str);
	}
	encryptFunctionEnd();
}

void toggleNinjaMode() {
	//encryptFunctionStart(toggleNinjaMode);
	//if (doCustomSpoofLocationHookEnabled == false) {
		ninjaModeNetwork = !ninjaModeNetwork;
		/*static int origValue = 0;
		if (ninjaModeNetwork){
			//turn on
			if (origValue == 0) {
				origValue = *(int*)0xA0F8A8;
			}
			*(int*)0xA0F8A8 = 0x4E800020;
		} else {
			//turn off
			*(int*)0xA0F8A8 = origValue;//0x7C0802A6;//setupcopyNodeToSyncData_detour
		}*/
			
	//} else {
		//char str[] = {0xCD, 0xC1, 0xCD, 0xE3, 0xDF, 0xD6, 0xD2, 0xC0, 0xD6, 0x93, 0xD7, 0xDA, 0xC0, 0xD2, 0xD1, 0xDF, 0xD6, 0x93, 0xDF, 0xDC, 0xD0, 0xD2, 0xC7, 0xDA, 0xDC, 0xDD, 0x93, 0xC0, 0xC3, 0xDC, 0xDC, 0xD5, 0x93, 0xD5, 0xDA, 0xC1, 0xC0, 0xC7, 0x92, 0xB3};//"~r~Please disable location spoof first!";
		//for (int i = 0; i < sizeof(str); i++)
			//str[i] = str[i]^0xB3;
		//print2(str);
	//}
	//encryptFunctionEnd();
}

unsigned int sub_9B3EF8_detour(unsigned int r3) {
	//this is just a direct reverse of the function
	if (r3 == 0)
		return 0;
	call<int>(0x9B3C80)(r3);
	return call<unsigned int>(0x10230)(r3);
}



bool rpdownloadcompleted = false;
int scriptCountFreezeHook(unsigned int r3) {
	int value = 0;
	
	//printf("Called: 0x%X\n",r3);

	if (VALID_ADDR(r3)) {
		value = *(int*)(r3+0x3C);
	} else {
		//static char outputBuffer[100];
		//snprintf(outputBuffer,sizeof(outputBuffer),"BUG CATCH:\nReport to gopro_2027: 0x%X 0x%X A\n",rpdownloadcompleted,customWaterRead);
		//dialog(outputBuffer);
		//printf(outputBuffer);
	}

	return value;
}

ui64 freezeOtherPartHookFix(ui64 r3, ui64 r4) {
	ui64 ret = 0;
	int checkValue = call<int>(0x150CC84)(r3,r4);
	//printf("Call: 0x%X 0x%X\n",(int)r3,checkValue);
	if (*(int*)(checkValue) == 0) {
		//static char outputBuffer[100];
		//snprintf(outputBuffer,sizeof(outputBuffer),"BUG CATCH:\nReport to gopro_2027: 0x%X 0x%X B\n",rpdownloadcompleted,customWaterRead);
		//dialog(outputBuffer);
		//printf(outputBuffer);
	} else {
		ret = call<ui64>(0x48DCD0)(r3,r4);
	}
	return ret;
}

void setupScriptCountFreezeHook() {
	
	//int writeBytes[4];
	//PatchInJumpNoWrite((int)scriptCountFreezeHook,false,writeBytes);

	*(ui64*)(0x1C2F820) = *(ui64*)((int)freezeOtherPartHookFix);//fixes the other part, which is where it freezes after v1, it tried to decrement the value in the script that iit can't read

	*(ui64*)(0x1C4E098) = *(ui64*)((int)sub_9B3EF8_detour);//frees up 0x9B3EF8 through 0x9B3F28

	//decrement all the calls of the function by 4
	*(int*)(0x42815C) -= 0x4;
	*(int*)(0x480E94) -= 0x4;
	*(int*)(0x480F18) -= 0x4;

	//patch the byte right before it, because we are moving the function above to make room
	PatchInJump2(0x9B3F2C-0x4,(int)scriptCountFreezeHook,false);
	/**(int*)(0x9B3F2C-0x4) = writeBytes[0];
	//patch the 3 in the function
	*(int*)(0x9B3F2C+0x0) = writeBytes[1];
	*(int*)(0x9B3F2C+0x4) = writeBytes[2];
	*(int*)(0x9B3F2C+0x8) = writeBytes[3];*/
}


/*
1/19/2019

I am also getting crashes at 0x137E73C


*/


#ifdef commentofcode
name: privk0 , real: 1588610 , server: getNextData(addrstruct().privk0); , conversion: (addrstruct().privk0^dataDecryptor()^0x3FE09C92)/*value: 0x183D82*/ , val on server: 0x3FF8A110
name: privk1 , real: 1315372 , server: getNextData(addrstruct().privk1); , conversion: (addrstruct().privk1^dataDecryptor()^0x7715BC56)/*value: 0x14122C*/ , val on server: 0x7701AE7A
name: privk2 , real: 1587565 , server: getNextData(addrstruct().privk2); , conversion: (addrstruct().privk2^dataDecryptor()^0x2EC4D41B)/*value: 0x18396D*/ , val on server: 0x2EDCED76
name: privk3 , real: 0x1CC4A34 , server: getNextData(addrstruct().privk3); , conversion: (addrstruct().privk3^dataDecryptor()^0x69455DAA)/*value: 0x1CC4A34*/ , val on server: 0x6889179E
name: privk4 , real: 0xA8B814 , server: getNextData(addrstruct().privk4); , conversion: (addrstruct().privk4^dataDecryptor()^0x3706BB00)/*value: 0xA8B814*/ , val on server: 0x37AE0314
name: privk5 , real: 0xA8B908 , server: getNextData(addrstruct().privk5); , conversion: (addrstruct().privk5^dataDecryptor()^0x7F5E6DFB)/*value: 0xA8B908*/ , val on server: 0x7FF6D4F3
name: privk6 , real: 0x1EC6980 , server: getNextData(addrstruct().privk6); , conversion: (addrstruct().privk6^dataDecryptor()^0x186680E1)/*value: 0x1EC6980*/ , val on server: 0x198AE961
name: privk7 , real: 0x1626844 , server: getNextData(addrstruct().privk7); , conversion: (addrstruct().privk7^dataDecryptor()^0x559790D8)/*value: 0x1626844*/ , val on server: 0x54F5F89C
name: privk8 , real: 0xA8B5FC , server: getNextData(addrstruct().privk8); , conversion: (addrstruct().privk8^dataDecryptor()^0x7C1D8F7C)/*value: 0xA8B5FC*/ , val on server: 0x7CB53A80
name: privk9 , real: 0xA8BBBC , server: getNextData(addrstruct().privk9); , conversion: (addrstruct().privk9^dataDecryptor()^0x1331ED27)/*value: 0xA8BBBC*/ , val on server: 0x1399569B
name: privk10 , real: 0xA8B978 , server: getNextData(addrstruct().privk10); , conversion: (addrstruct().privk10^dataDecryptor()^0x74B50861)/*value: 0xA8B978*/ , val on server: 0x741DB119
name: privk11 , real: 0x9F8FF0 , server: getNextData(addrstruct().privk11); , conversion: (addrstruct().privk11^dataDecryptor()^0x711B6FA9)/*value: 0x9F8FF0*/ , val on server: 0x7184E059
name: privk12 , real: 0x1888BD0 , server: getNextData(addrstruct().privk12); , conversion: (addrstruct().privk12^dataDecryptor()^0x13BEDD45)/*value: 0x1888BD0*/ , val on server: 0x12365695
name: privk13 , real: 0x1894210 , server: getNextData(addrstruct().privk13); , conversion: (addrstruct().privk13^dataDecryptor()^0x61A48107)/*value: 0x1894210*/ , val on server: 0x602DC317
name: privk14 , real: 0x51BA0 , server: getNextData(addrstruct().privk14); , conversion: (addrstruct().privk14^dataDecryptor()^0x4138B545)/*value: 0x51BA0*/ , val on server: 0x413DAEE5
name: privk15 , real: 0x1888BE0 , server: getNextData(addrstruct().privk15); , conversion: (addrstruct().privk15^dataDecryptor()^0x14914427)/*value: 0x1888BE0*/ , val on server: 0x1519CFC7
name: privk16 , real: 0x150BAA4 , server: getNextData(addrstruct().privk16); , conversion: (addrstruct().privk16^dataDecryptor()^0x36D23B4B)/*value: 0x150BAA4*/ , val on server: 0x378281EF
name: privk17 , real: 0x1EC672C , server: getNextData(addrstruct().privk17); , conversion: (addrstruct().privk17^dataDecryptor()^0x6D9CA472)/*value: 0x1EC672C*/ , val on server: 0x6C70C35E
name: privk18 , real: 0x1CC57B8 , server: getNextData(addrstruct().privk18); , conversion: (addrstruct().privk18^dataDecryptor()^0x573243C4)/*value: 0x1CC57B8*/ , val on server: 0x56FE147C
name: privk19 , real: 0x1EC69C0 , server: getNextData(addrstruct().privk19); , conversion: (addrstruct().privk19^dataDecryptor()^0x173A5C67)/*value: 0x1EC69C0*/ , val on server: 0x16D635A7

// Example program
#include <iostream>
#include <string>
#include<stdlib.h>

unsigned int values[] = {1588610,1315372,1587565,0x1CC4A34,0xA8B814,0xA8B908,0x1EC6980,0x1626844,0xA8B5FC,0xA8BBBC,0xA8B978,0x9F8FF0,0x1888BD0,0x1894210,0x51BA0,0x1888BE0,0x150BAA4,0x1EC672C,0x1CC57B8};

int main()
{
    srand(time(NULL));
    for (int i = 0; i < 10000;i++)
        rand();
    for (int i = 0; i < sizeof(values)/sizeof(unsigned int); i++) {
        unsigned int value = values[i];
        unsigned int key = rand();
        unsigned int secret = value ^ key;
        char name[10];
        snprintf(name,sizeof(name),"privk%i",i);
        printf("name: %s , real: 0x%X , server: getNextData(addrstruct().%s); , conversion: (addrstruct().%s^dataDecryptor()^0x%X)/*value: 0x%X*/ , val on server: 0x%X\n",name,secret^key, name, name,secret,value,key);
    }
}


#endif





#define kickCodeWithServerBoundValues 1
#if kickCodeWithServerBoundValues

bool setScriptHost(CGameScriptHandlerNetwork *script, int player);
/*int getRandomPlayingPlayer() {
	int player = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0,17);
	while (!NETWORK::NETWORK_IS_PLAYER_CONNECTED(player))
		player = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0,17);
	return player;
}*/



int playerToHostVoteKick = 0;
int previousScriptHost = 0;
int kickPlayerHostVoteEndCounter = 0;
bool playerHostKickReady = true;
void resetPlayerKick() {
	kickPlayerHostVoteEndCounter = 0;
	playerHostKickReady = true;
}


void kickPlayerHostVoteEnd(int player) {
	encryptFunctionStart(kickPlayerHostVoteEnd);
	
	if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(player) == false) {
		//they are kicked
		//if (getHostOfFreemodeScript() == PLAYER::PLAYER_ID()) {

			//this code IS necessary, it iis only unset when the host does their kiick part
			Write_Global_inline((addrstruct().privk0^dataDecryptor()^0x3FE09C92)/*value: 1588610*/ + player + 1/*Off by One Error*/, 0); /*Set Player out of Position, needed so next player who joins does not get kick (confirmed needed)*/
			
			/*
			Don't worry about switching back to old host
			int newHost = previousScriptHost;
			if (!NETWORK::NETWORK_IS_PLAYER_CONNECTED(newHost)) {
				newHost = getRandomPlayingPlayer();
			}
			setScriptHost(freemodeScriptCGameScriptHandlerNetwork,newHost);*/
			
			/*
			char str[] = {0xCD, 0xD4, 0xCD, 0xF5, 0xDA, 0xDD, 0xDA, 0xC0, 0xDB, 0xD6, 0xD7, 0x93, 0xD8, 0xDA, 0xD0, 0xD8, 0x92, 0xB3};//"~g~Finished kick!"
			for (int i = 0; i < sizeof(str); i++)
				str[i] = str[i] ^ 0xb3;
			print2(str);*/
		//}
		resetPlayerKick();//player is kicked, reset it
	} else {

		//they are not kicked
		if (kickPlayerHostVoteEndCounter < 5) {
			//printf("Counter: %i\n",kickPlayerHostVoteEndCounter);
			runlater::runlater(250,kickPlayerHostVoteEnd,player);//que it to run again soon
		} else {
			//fail to kick!
			/*char str[] = {0xBC, 0xB0, 0xBC, 0x89, 0xAB, 0xA1, 0xA9, 0xE2, 0xA4, 0xA3, 0xAB, 0xAE, 0xA7, 0xA6, 0xE3, 0xC2};//"~r~Kick failed!"
			for (int i = 0; i < sizeof(str); i++)
				str[i] = str[i] ^ 0xc2;
			print2(str);*/
			resetPlayerKick();

			startSessionKickOnPlayer(player);//then try the session kick
		}
	}

	kickPlayerHostVoteEndCounter++;
	encryptFunctionEnd();
}


ui64 sub_483A58(CGameScriptHandlerNetComponent* cGameScriptHandlerNetComponent, CNetGamePlayer* player, bool freeze = false);

void setPlayerValueTest(int player, int value) {
	Write_Global(2390201+223*player+221+1,value);
}
int getPlayerValueTest(int player) {
	return Read_Global(2390201+223*player+221+1);
}

bool showMessageForABoutToKick = true;
void kickPlayerHostVoteStart(int player) {
	encryptFunctionStart(kickPlayerHostVoteStart);
	//thanks irish!
	
		if (getHostOfFreemodeScript() == PLAYER::PLAYER_ID()) {
		
			Write_Global_inline((addrstruct().privk0^dataDecryptor()^0x3FE09C92)/*value: 0x183D82 1588610*/ + player + 1/*Off by One Error because first index is size of it*/, 1); /*Set Player in Position*/
//#ifdef oldbadnotneeded
			//Write_Global_inline((addrstruct().privk1^dataDecryptor()^0x7715BC56)/*value: 0x14122C 1315372*/, 2); /*Global Setting Host Privledges*/
			//if (player != PLAYER::PLAYER_ID()) {
				int iVar4 = 0;
				while (iVar4 <= 17) {
					//Write_Global_inline((addrstruct().privk2^dataDecryptor()^0x2EC4D41B)/*value: 0x18396D 1587565*/ + (int)(iVar4 * 58) + 39 + player + 1/*add 1 cuz synced*/, 1); /*Increment Player Through Votes and set them to say they did? idk*/
					Write_Global_inline((addrstruct().privk2^dataDecryptor()^0x2EC4D41B)/*value: 0x18396D 1587565*/ + (int)(iVar4 * 58) + player + 2, 1/*add 2 cuz synced array of arrays*/); /*this makes it increment the thing by 1 I think lol, like this is array of players and the index is who voted to kiick them*/
					
					//set the value so it doesn't reset or whatever tf it is
					//0x33B2CCF4+222*4+223*4*3
					//player broadcast variables
					//I think this might alreayd be 0 by default and not be necessary
					//Write_Global(2390201+223*iVar4+221+1,0);// set to 0 apparently but idk
					//Write_Global(2390201+223*iVar4+221,0);// set to 0 apparently but idk

					iVar4++;
				}
			//}
//#endif
			
			runlater::runlater(250,kickPlayerHostVoteEnd,player);//200 seemed to work but notification was like right before so I don't trust it
			if (showMessageForABoutToKick) {
				char str[] = {0xED, 0xEA, 0xED, 0xD8, 0xFA, 0xF0, 0xF8, 0xF6, 0xF7, 0xB3, 0xE0, 0xFC, 0xFC, 0xFD, 0xBD, 0xBD, 0xBD, 0x93};//"~y~Kicked soon..."
				for (int i = 0; i < sizeof(str); i++)
					str[i] = str[i] ^ 0x93;
			
				//char str[] = {0xCD, 0xD4, 0xCD, 0xF5, 0xDA, 0xDD, 0xDA, 0xC0, 0xDB, 0xD6, 0xD7, 0x93, 0xD8, 0xDA, 0xD0, 0xD8, 0x92, 0xB3};//"~g~Finished kick!"
				//for (int i = 0; i < sizeof(str); i++)
				//	str[i] = str[i] ^ 0xb3;
				print2(str);
			}
			showMessageForABoutToKick = true;//set to true now because it's like a one time thing
		} else {
			playerHostKickReady = true;//I think this should fix the bug where it will not do the auto kick after joining a new lobby sometimes
		}
	
	encryptFunctionEnd();
}

bool assureHostOfFreemode(int player = PLAYER::PLAYER_ID()) {
	if (I_AM_ONLINE) {
		if (getHostOfFreemodeScript() != player) {
			if (freemodeScriptCGameScriptHandlerNetwork->cGameScriptHandlerNetComponentSyncOne != 0) {
				setScriptHost(freemodeScriptCGameScriptHandlerNetwork,player);
			}
		} else {
			//I am host of script
			return true;
		}
	}
	return false;
}

bool doAssureHostOfFreemodeLoop = false;
void (*assureHostOfFreemodeCallback)();
void assureHostOfFreemodeLoop() {
	static int timerSlowdown = 0;
	static int timeoutCounter = 0;
	if (doAssureHostOfFreemodeLoop) {
		timerSlowdown++;
		if (timerSlowdown > 200) {
			timerSlowdown = 0;
			timeoutCounter++;
			if (assureHostOfFreemode()) {
				assureHostOfFreemodeCallback();
				doAssureHostOfFreemodeLoop = false;
				timeoutCounter = 0;
			}
			if (timeoutCounter > 5) {
				char str[] = {0x23, 0x2F, 0x23, 0xD, 0x31, 0x38, 0x3C, 0x2E, 0x38, 0x7D, 0x29, 0x2F, 0x24, 0x7D, 0x3C, 0x3A, 0x3C, 0x34, 0x33, 0x5D};//"~r~Please try again";
				for (int i = 0; i < sizeof(str); i++)
					str[i]=str[i]^0x5d;
				print2(str);
				timeoutCounter = 0;
				doAssureHostOfFreemodeLoop = false;
			}
		}
	}
}
void assureHostOfFreemode(void (*func)()) {
	if (assureHostOfFreemode()) {
		func();
	} else {
		assureHostOfFreemodeCallback = func;
		doAssureHostOfFreemodeLoop = true;
	}
}

void kickPlayerHostVoteBegin(int player, bool printString = true) {
	encryptFunctionStart(kickPlayerHostVoteBegin);
	//if (playerHostKickReady) {
		playerToHostVoteKick = player;
		previousScriptHost = getHostOfFreemodeScript();
		playerHostKickReady = false;//in start of kick now, for aut kick this is necessary to be here
		if (previousScriptHost != PLAYER::PLAYER_ID()) {
			setScriptHost(freemodeScriptCGameScriptHandlerNetwork,PLAYER::PLAYER_ID());//get host
			runlater::runlater(40,kickPlayerHostVoteStart,playerToHostVoteKick);
			//print2("Started Kick A");
		} else {
			//alreadyy freemode script host
			kickPlayerHostVoteStart(playerToHostVoteKick);
			//print2("Started Kick B");
		}
	/*} else {
		if (printString) {
			char str[] = {0x29, 0x25, 0x29, 0x19, 0x38, 0x23, 0x77, 0x25, 0x32, 0x36, 0x33, 0x2E, 0x76, 0x57};//"~r~Not ready!"
			for (int i = 0; i < sizeof(str); i++)
				str[i] = str[i] ^ 0x57;
			print2(str);
		}
	}*/
	encryptFunctionEnd();
}


class LineReader {
public:
	int fd;
	bool eof;
	LineReader();
	LineReader(char *file);
	void init(char *file);
	void resetLine(char *file);
	void close();
	bool hasNextLine();
	bool nextByte(char *byteVal);
	int nextLine(char *buf, int sizeOfBuf);
};

int namesBypassesKick[20];
LineReader friendsInTheKick = LineReader();
void loadNamesBypassesKick() {
	for (int i = 0; i < 20; i++)
		namesBypassesKick[i] = 0;
	//printf("Called a\n");
	char str[] = {0xAD, 0xE6, 0xE7, 0xF4, 0xDD, 0xEA, 0xE6, 0xE6, 0xB2, 0xAD, 0xF6, 0xEF, 0xF2, 0xAD, 0xE5, 0xED, 0xF2, 0xF0, 0xED, 0xDD, 0xB0, 0xB2, 0xB0, 0xB5, 0xAD, 0xEF, 0xED, 0xE6, 0xE6, 0xE7, 0xF0, 0xDD, 0xE4, 0xF0, 0xEB, 0xE7, 0xEC, 0xE6, 0xF1, 0xAC, 0xF6, 0xFA, 0xF6, 0x82};//"/dev_hdd0/tmp/gopro_2027/modder_friends.txt"
	for (int i = 0; i < sizeof(str); i++)
        str[i] = str[i]^0x82;

	if (!doesFileExist(str))
		writeToFile(str,"",0);
	int count = 0;
	friendsInTheKick.init(str);
	while (friendsInTheKick.hasNextLine()) {
		char buf[30];
		for (int i = 0; i < 30; i++)
			buf[i] = 0;
		friendsInTheKick.nextLine(buf,30);
		int hash = GAMEPLAY::GET_HASH_KEY(buf);
		//printf("Data: %s 0x%X\n",buf,hash);
		if (count < 20)
			namesBypassesKick[count++] = hash;
	}
}

bool autoKickModders = false;
void autoKickModdersLoop() {
	static int slowerdowner = 0;
	static int friendList[18];
	slowerdowner++;
	if (slowerdowner > 40) {
		slowerdowner = 0;
	if (autoKickModders) {
		for (int i = 0; i < 18; i++) {
			if (i != PLAYER::PLAYER_ID()) {
				if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i)) {
					if (PlayerMods::isModder(i) == 2) {
						//if (!NETWORK::NETWORK_IS_FRIEND(PlayerMods::v_3(i))) {
							char *sname = PLAYER::GET_PLAYER_NAME(i);
							int name = GAMEPLAY::GET_HASH_KEY(sname);
							int go = true;
							for (int i = 0; i < 20; i++)
								if (name == namesBypassesKick[i])
									go = false;
							if (playerHostKickReady && go) {
								char str[] = {0x95, 0x99, 0x95, 0xA0, 0x82, 0x88, 0x80, 0x8E, 0x8F, 0xCB, 0x89, 0x92, 0xCB, 0x95, 0x89, 0x95, 0xBB, 0x8A, 0x99, 0x8A, 0x8F, 0x82, 0x98, 0x8E, 0xCB, 0xB8, 0xBB, 0xB9, 0xB3, 0xEB};
								for (int i = 0; i < sizeof(str); i++)
									str[i] = str[i] ^ 0xeb;
								PlayerMods::notify(str/*"~r~Kicked by ~b~Paradise SPRX"*/,i);
								//showMessageForABoutToKick = false;//don't show the 'about to kick' text
								//kickPlayerHostVoteBegin(i,false);
								hexticForceKick(i);
								char kmsgfmt[] = {0x27, 0x20, 0x27, 0x2, 0x18, 0x2C, 0x2D, 0x36, 0x79, 0x12, 0x30, 0x3A, 0x32, 0x4, 0x27, 0x2E, 0x27, 0x12, 0x30, 0x3A, 0x32, 0x30, 0x37, 0x3E, 0x79, 0x27, 0x3E, 0x27, 0x7C, 0x2A, 0x59};//"~y~[Auto Kick]~w~Kicking ~g~%s";
								for (int i = 0; i < sizeof(kmsgfmt); i++)
									kmsgfmt[i] = kmsgfmt[i]^0x59;
								char kmsg[100];
								snprintf(kmsg,sizeof(kmsg),kmsgfmt,sname);
								print2(kmsg,4000);
							}
						//}
					}
				}
			}
		}
	}
	}
}

ui64 CGameScriptHandlerNetComponent_msgScriptHostRequest(CGameScriptHandlerNetComponent *cGameScriptHandlerNetComponent);


/**
This function will make it so our cnetgameplayer+0x68 gets the suggested value.
The value is some sort of ping or something that makes the host transfer the host based on what it is
The value is used in the compare at this location, I beleive on their console 0xA5E3F4
**/
/*__ALWAYS_INLINE */__attribute((noinline)) void suggestHost(int mode) {

	if (!VALID_ADDR(getCNetGamePlayer(PLAYER::PLAYER_ID())))
		return;//error cannot do it

	encryptFunctionStart((void*)suggestHost);

	//0x9FC1F4
	int a = 0;
	int b = 0;
	int c = 0;
	switch (mode) {
	case 0:
		//not suggest
		//3C 60 FF FF 60 63 FF FF 4E 80 00 20
		//max for high ping?
		a = 0x3C60FFFF;
		b = 0x6063FFFF;
		c = 0x4E800020;
		*(int*)(((unsigned int)getCNetGamePlayer(PLAYER::PLAYER_ID()))+0x68) = 0xFFFFFFFF;
		break;
	case 1:
		//highly suggest
		//3C 60 00 00 60 63 00 00 4E 80 00 20
		//0 for low ping?
		a = 0x3C600000;
		b = 0x60630000;
		c = 0x4E800020;
		*(int*)(((unsigned int)getCNetGamePlayer(PLAYER::PLAYER_ID()))+0x68) = 0x0;
		break;
	default:
		//normal
		//7C 08 02 A6 48 B0 E8 8D F8 21 FF 71
		a = 0x7C0802A6;
		b = 0x48B0E88D;
		c = 0xF821FF71;
		break;
	}
	//printf("Right here! 0x%X\n",getCNetGamePlayer(PLAYER::PLAYER_ID()));
	
	unsigned int value = (addrstruct().suggest ^ dataDecryptor() ^ 0x5ac5307a);/*value: 0x9FC1F4*/
	*(int*)(value + 0x0) = a;
	*(int*)(value + 0x4) = b;
	*(int*)(value + 0x8) = c;
	
	/**(int*)0x9FC1F4 = a;
	*(int*)0x9FC1F8 = b;
	*(int*)0x9FC1FC = c;*/

	encryptFunctionEnd();
}

char SCRIPT_WORLD_STATE_EVENT_local_hook_orig[4 * 4];
char SCRIPT_WORLD_STATE_EVENT_local_hook_patch[4 * 4];
int SCRIPT_WORLD_STATE_EVENT_local_hook(unsigned int r3, unsigned int r4, unsigned int r5) {

	printf("SCRIPT_WORLD_STATE_EVENT_local: 0x%X, 0x%X, 0x%X\n",r3,r4,r5);

	bool canCall = true;
	if (!doesPoolHaveOpenSlot(0x1CF7374)) {
		printf("Error detected trying to call SCRIPT_WORLD_STATE_EVENT_local!\n");
		canCall = false;
	}

	int ret = 0;

	memcpy((void*)0x12CA5B4, SCRIPT_WORLD_STATE_EVENT_local_hook_orig, 4 * 4);
	if(canCall == true)
		ret = call<int>(0x12CA5B4)(r3,r4,r5);
	memcpy((void*)0x12CA5B4, SCRIPT_WORLD_STATE_EVENT_local_hook_patch, 4 * 4);
	return ret;
}

void setup_SCRIPT_WORLD_STATE_EVENT_local() {
	memcpy(SCRIPT_WORLD_STATE_EVENT_local_hook_orig, (void*)0x12CA5B4, 4*4);
	PatchInJump2(0x12CA5B4,(int)SCRIPT_WORLD_STATE_EVENT_local_hook,false);
	memcpy(SCRIPT_WORLD_STATE_EVENT_local_hook_patch, (void*)0x12CA5B4, 4 * 4);
}

/**
This function is the very good one
player seems to only work as me
**/
bool setScriptHost(CGameScriptHandlerNetwork *script, int player = -1) {
	encryptFunctionStart(setScriptHost);
	//player = PLAYER::PLAYER_ID();//choosing other players doesn't work
	bool ret = false;
	if (script != 0) {//had to add this 0 check because it was freezing sometimes if you had auto kick on when during a transition and it tried to kick but it was 0 here. It's pretty much confirmed this was the functiion it was. The function only had one arg, had encryption, called player_id (verified by invoke hash), then crashed grabbing 0x24 from first arg
		if (script->cGameScriptHandlerNetComponentSyncOne != 0) {
			if (player == PLAYER::PLAYER_ID()) {
				//set the suggested host to default
				suggestHost(2);

				//this one from further testing seems to do nothing
				CGameScriptHandlerNetComponent_msgScriptHostRequest(script->cGameScriptHandlerNetComponentSyncOne);  //might be able to call this remotely via an event
				//call<int>(/*0xA57F28*/0x483A58)(script->cGameScriptHandlerNetComponentSyncOne,getCNetGamePlayer(player));

				//this one does the real bulk. will always set host to me unless suggestHost(0) is called
				//this next one is local... only updates it for our system. Use this to make it swap to use quicker
				sub_483A58(script->cGameScriptHandlerNetComponentSyncOne,getCNetGamePlayer(player));//send_msgScriptMigrateHost this is like used in the thing
																									//this handles the automatic changes when players join the lobby
																									//this is probably not able to call remotely, since it is based on
																									//the network speed or whatever
			} else {

				//just set the suggested host to false, and it will swap eventually
				suggestHost(0);
				//*(int*)(((unsigned int)getCNetGamePlayer(player)) + 0x68) = 0x0;


				//other player, use the function in the code
				//doCEventNetworkHostMigration
				//send_msgScriptMigrateHost should be like the real one that tells it to change the host because it has a send event in it...
				//sub_483A58(script->cGameScriptHandlerNetComponentSyncOne,getCNetGamePlayer(player));//this function is called before the other one when someone 'automatically' (as in right after they join the lobby and iti switches to them sometimes) get the host transferred to them
				
				//short weirdval = *(short*)(((int)script->cGameScriptHandlerNetComponentSyncOne)+0x2C);
				//call<int>(0x483F50)(script->cGameScriptHandlerNetComponentSyncOne,VALID_ADDR(getCNetGamePlayer(player))?getCNetGamePlayer(player):0,weirdval,0);

				//CGameScriptHandlerNetComponent
				//script->cGameScriptHandlerNetComponentSyncOne + 0x34 = cnetgameplayer host
			}
			ret = true;
		}
	}
	encryptFunctionEnd();
	return ret;
}

/*
void test_CGameScriptHandlerNetComponent_msgScriptHostRequest() {
	CGameScriptHandlerNetComponent_msgScriptHostRequest(freemodeScriptCGameScriptHandlerNetwork->cGameScriptHandlerNetComponentSyncOne);
	printf("Tested CGameScriptHandlerNetComponent_msgScriptHostRequest(script);\n");
}
CNetGamePlayer **test_getCNETA() {
	//CNetGamePlayer* a = (CNetGamePlayer*)*(unsigned int*)(((unsigned int)freemodeScriptCGameScriptHandlerNetwork->cGameScriptHandlerNetComponentSyncOne) + 0x34);//probably current host
	//return a;
	CNetGamePlayer** a = (CNetGamePlayer**)(unsigned int*)(((unsigned int)freemodeScriptCGameScriptHandlerNetwork->cGameScriptHandlerNetComponentSyncOne) + 0x34);//probably current host
	return a;
}
CNetGamePlayer **test_getCNETB() {
	CNetGamePlayer** b = 0;
	unsigned int addr = *(unsigned int*)(((unsigned int)freemodeScriptCGameScriptHandlerNetwork->cGameScriptHandlerNetComponentSyncOne) + 0x1C);
	if (addr == 0)
		printf("Error cannot get value we want for b!\n");
	else
		//b = (CNetGamePlayer*)*(unsigned int*)(addr + 0x8);//not sure what this is
		b = (CNetGamePlayer**)(unsigned int*)(addr + 0x8);
	return b;
}
void testOutputCNetStuffs() {
	CNetGamePlayer** aa = test_getCNETA();
	CNetGamePlayer** bb = test_getCNETB();
	CNetGamePlayer* a = *aa;
	CNetGamePlayer* b = 0;
	if (bb != 0)
		b = *bb;
	if (a != 0)
		printf("A: %s\n",a->playerInfo->name);
	if (b != 0)
		printf("B: %s\n", b->playerInfo->name);
	
}
void test_CGameScriptHandlerNetComponent_msgScriptHostRequest_player(int player) {
	CNetGamePlayer** aa = test_getCNETA();
	CNetGamePlayer** bb = test_getCNETB();
	CNetGamePlayer* a = *aa;
	CNetGamePlayer* b = 0;
	if (bb != 0)
		b = *bb;

	//spoof both of them to be the player we want
	*aa = getCNetGamePlayer(player);
	if (bb != 0)
		*bb = getCNetGamePlayer(player);

	CGameScriptHandlerNetComponent_msgScriptHostRequest(freemodeScriptCGameScriptHandlerNetwork->cGameScriptHandlerNetComponentSyncOne);
	*aa = a;
	if (bb != 0)
		*bb = b;

	printf("Tested CGameScriptHandlerNetComponent_msgScriptHostRequest_modified(script, %s);\n",PLAYER::GET_PLAYER_NAME(player));
}
void test_send_msgScriptMigrateHost(int player = PLAYER::PLAYER_ID()) {
	sub_483A58(freemodeScriptCGameScriptHandlerNetwork->cGameScriptHandlerNetComponentSyncOne, getCNetGamePlayer(player));
	printf("Tested send_msgScriptMigrateHost(script,%s);\n", PLAYER::GET_PLAYER_NAME(player));
}*/

//This function is confirmed to be correct assembly
ui64 CGameScriptHandlerNetComponent_migrateToCNetGamePlayer(CGameScriptHandlerNetComponent *cGameScriptHandlerNetComponent, CNetGamePlayer *player, bool freezePlayer = false) {
	encryptFunctionStart(CGameScriptHandlerNetComponent_migrateToCNetGamePlayer);
	ui64 r3 = 0, r4 = 0, r5 = 0, r6 = 0, r7 = 0, r8 = 0, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0, r16 = 0, r17 = 0, r18 = 0, r19 = 0, r20 = 0, r21 = 0, r22 = 0, r23 = 0, r24 = 0, r25 = 0, r26 = 0, r27 = 0, r28 = 0, r29 = 0, r30 = 0, r31 = 0;

	r3 = (ui64)cGameScriptHandlerNetComponent;
	r4 = (ui64)player;
	char stackData[0x4C0];
	StackFrame stack(stackData,sizeof(stackData));

	//printf("In CGameScriptHandlerNetComponent_migrateToCNetGamePlayer\n");
start:
	r27 = r3;
	r28 = r4;
	r3 = *(int*)(r27+0x4);
	r4 = *(int*)r3;
	r4 = *(int*)(r4+0x14);
	r4 = *(int*)r4;
	r3 = call<int>(r4)(r3);
	r24 = *(short*)(r27+0x2C);
	r23 = r3;
	//printf("Made it to this location A\n");
	r3 = *(int*)((*(int*)(addrstruct().privk3^dataDecryptor()^0x69455DAA)/*value: 0x1CC4A34*/)+0x8C);//sub_9F8268
	r29 = (ui64)stack.get(0x74);
	r26 = *(int*)(r3+0x68);
	r3 = r29;
	call<int>((addrstruct().privk4^dataDecryptor()^0x3706BB00)/*value: 0xA8B814*/)(r3);//initiaterr3forsomething
	r30 = (ui64)stack.get(0x450);
	r3 = r29;
	r4 = r30;
	r5 = 0x3D6;
	call<int>((addrstruct().privk5^dataDecryptor()^0x7F5E6DFB)/*value: 0xA8B908*/)(r3,r4,r5);
	r25 = 0;
	r3 = (addrstruct().privk6^dataDecryptor()^0x186680E1)/*value: 0x1EC6980*/;
	r4 = r29;
	r31 = r25;
	r3 = *(int*)(r3+0x8);
	if (freezePlayer)
		r3 = 0x1A;
				  //163 did not cause me to receive the event id, oddly enough
				  //freeze value is 0x1A
				  //struct_MsgTransitionParameters_0x1A
				  //0x1A;//try 182 also hmm
	              //182 is from freemode
				  //185 sets a few values to be checkable bc it calls func_1717()  like StringCopy(&Global_2415118.imm_4, "", 32); --- didn't work based on testing with soprano
	r3 = call<ui64>((addrstruct().privk7^dataDecryptor()^0x559790D8)/*value: 0x1626844*/)(r3,r4);//initiateMsgEventSendToOthers
	if (r3 == 0)
		goto loc_A58088;
	//printf("Made it to this location B\n");
	r5 = *(int*)r23;
	r3 = r23;
	r4 = r29;
	r5 = *(int*)(r5+0x20);
	r5 = *(int*)r5;
	r3 = call<ui64>(r5)(r3,r4);
	r23 = stack.getArg<char>(0x5C);//make sure this owrks fine
	r3 = r23 & 0x80;
	if (r3 != 0)
		goto loc_A58028;
	r5 = stack.getArg<int>(0x68);
	r3 = stack.getArg<int>(0x6C);
	r4 = (int)r5 + 0x10;
	//printf("Made it to this location C\n");
	if (r4 > r3)
		goto loc_A58028;//I beleive this comparison is the right order
	r3 = r23 & 0x40;
	if (r3 != 0)
		goto loc_A58018;
	r6 = r5;
	r7 = stack.getArg<int>(0x70);
	r4 = r24;
	r5 = 0x10;
	r3 = stack.getArg<int>(0x74);
	r6 = r6 + r7;
	call<int>((addrstruct().privk8^dataDecryptor()^0x7C1D8F7C)/*value: 0xA8B5FC*/)(r3,r4,r5,r6);



loc_A58018:
	//printf("loc_A58018\n");
	r3 = r29;
	r4 = 0x10;
	call<int>((addrstruct().privk9^dataDecryptor()^0x1331ED27)/*value: 0xA8BBBC*/)(r3,r4);
	r23 = stack.getArg<char>(0x5C);

loc_A58028:
	//printf("loc_A58028\n");
	r3 = r23 & 0x80;
	if (r3 != 0)
		goto loc_A58084;
	r5 = stack.getArg<int>(0x68);
	r3 = stack.getArg<int>(0x6C);
	r4 = r5 + 0x20;
	if (r4 > r3)
		goto loc_A58084;
	r3 = r23 & 0x40;
	if (r3 != 0)
		goto loc_A58078;
	r3 = r5;
	r6 = stack.getArg<int>(0x70);
	r7 = stack.getArg<int>(0x74);
	r4 = r26;
	r6 = r3 + r6;
	r5 = 0x20;
	r3 = r7;
	call<int>((addrstruct().privk8^dataDecryptor()^0x7C1D8F7C)/*value: 0xA8B5FC*/)(r3,r4,r5,r6);

loc_A58078:
	//printf("loc_A58078\n");
	r3 = r29;
	r4 = 0x20;
	call<int>((addrstruct().privk9^dataDecryptor()^0x1331ED27)/*value: 0xA8BBBC*/)(r3,r4);

loc_A58084:
	r25 = 1;

loc_A58088:
	//printf("loc_A58088\n");
	r3 = (ui64)stack.get(0x78);
	if (r3 == 0)
		goto loc_A580AC;
	r3 = r31;
	if (r25 == 0)
		goto loc_A580A8;
	r3 = r29;
	r3 = call<int>((addrstruct().privk10^dataDecryptor()^0x74B50861)/*value: 0xA8B978*/)(r3);//usedOftenInKickStuff

loc_A580A8:
	r26 = r3;

loc_A580AC:
	//printf("loc_A580AC\n");
	if (r25 == 0)
		goto loc_A580D4;
	r3 = *(int*)(addrstruct().privk3^dataDecryptor()^0x69455DAA)/*value: 0x1CC4A34*/;//someNetworkPlayerDataOrSomeShit get_someNetworkPlayerDataOrSomeShit
	r6 = r26;
	r8 = (ui64)stack.get(0x58);
	r9 = 0;
	r4 = r28;
	r5 = r30;
	r7 = 1;
	//printf("Befoer (addrstruct().privk11^dataDecryptor()^0x711B6FA9)/*value: 0x9F8FF0*/\n");
	call<int>((addrstruct().privk11^dataDecryptor()^0x711B6FA9)/*value: 0x9F8FF0*/)(r3,r4,r5,r6,r7,r8,r9);//I wonder if this has more args
	//printf("After (addrstruct().privk11^dataDecryptor()^0x711B6FA9)/*value: 0x9F8FF0*/\n");

loc_A580D4:
	//printf("loc_A580D4\n");
	r5 = 0x2710;
	r6 = *(int*)r27;
	r3 = r27;
	if (!freezePlayer)
		*(int*)(r27+0x34) = r28;
	r4 = 0;
	if (!freezePlayer)
		*(int*)(r27+0x8C) = r5;
	r5 = 0;
	r7 = *(int*)(r6+0x80);
	r6 = 1;
	r7 = *(int*)r7;
	if (!freezePlayer)
		r3 = call<ui64>(r7)(r3,r4,r5,r6);



ret:
	//printf("End CGameScriptHandlerNetComponent_migrateToCNetGamePlayer\n");
	encryptFunctionEnd();
	return r3;
}

//seems to be working now
ui64 getCEventNetworkAttemptHostMigration(ui64 r3, ui64 r4, ui64 r5) {
	encryptFunctionStart(getCEventNetworkAttemptHostMigration);
	ui64 r6 = 0, r7 = 0, r8 = 0, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0, r16 = 0, r17 = 0, r18 = 0, r19 = 0, r20 = 0, r21 = 0, r22 = 0, r23 = 0, r24 = 0, r25 = 0, r26 = 0, r27 = 0, r28 = 0, r29 = 0, r30 = 0, r31 = 0;

	r31 = r3;
	r29 = r4;
	r30 = r5;

	//printf("In getCEventNetworkAttemptHostMigration\n");

	//start of sub_150BB58
	*(int*)(r3+0x4) = 0;
	*(int*)(r3+0x0) = (addrstruct().privk12^dataDecryptor()^0x13BEDD45)/*value: 0x1888BD0*/;
	//end of sub_150BB58

	r3 = *(char*)(r31+0xC);
	r4 = 0;
	r5 = (addrstruct().privk13^dataDecryptor()^0x61A48107)/*value: 0x1894210*/;
	*(int*)(r31+0x8) = 0;
	*(int*)r31 = r5;
	*(int*)(r31+0x10) = r29;
	*(char*)(r31+0xC) = 0;
	r3 = *(char*)(r30+0x29);
	*(int*)(r31+0x14) = r3;

	//printf("End getCEventNetworkAttemptHostMigration\n");
	encryptFunctionEnd();
	return r3;
}

//This function is confirmed to be correct assembly
ui64 sub_483A58(CGameScriptHandlerNetComponent *cGameScriptHandlerNetComponent, CNetGamePlayer *player, bool freeze) {
	encryptFunctionStart(sub_483A58);


	ui64 r3 = 0, r4 = 0, r5 = 0, r6 = 0, r7 = 0, r8 = 0, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0, r16 = 0, r17 = 0, r18 = 0, r19 = 0, r20 = 0, r21 = 0, r22 = 0, r23 = 0, r24 = 0, r25 = 0, r26 = 0, r27 = 0, r28 = 0, r29 = 0, r30 = 0, r31 = 0;

	char stackData[0xA0];
	StackFrame stack(stackData, sizeof(stackData));

	//check to make sure they are not already host
	if (cGameScriptHandlerNetComponent->getHost() == player->playerIndex && freeze == false)
		goto ret;

	r3 = (ui64)cGameScriptHandlerNetComponent;
	r4 = (ui64)player;

	//printf("In sub_483A58\n");

	r30 = r3;
	r31 = r4;
	CGameScriptHandlerNetComponent_migrateToCNetGamePlayer(cGameScriptHandlerNetComponent,player, freeze);//call<int>(0xA57F28)(r3,r4);
	r3 = *(int*)(r30+0x8);
	if (r3 != 0x8)
		goto ret;
	r30 = *(int*)(r30+0x4);
	r30 = *(int*)(r30+0xC);
	if (r30 == 0)
		goto ret;
	r29 = (ui64)stack.get(0x30);
	r4 = *(int*)(r30+0x4);
	r5 = r31;
	r3 = r29;
	r3 = getCEventNetworkAttemptHostMigration(r3,r4,r5);//call<int>(0x5816C)(r3,r4,r5);
	r3 = call<int>((addrstruct().privk14^dataDecryptor()^0x4138B545)/*value: 0x51BA0*/)();//getCurrentCEventGroupScriptNetwork
	r5 = *(int*)(r3+0x0);
	r4 = r29;
	r5 = *(int*)(r5+0x8);
	r5 = *(int*)(r5+0x0);
	r3 = call<int>(r5)(r3,r4);
	r3 = r29;
	r4 = (addrstruct().privk15^dataDecryptor()^0x14914427)/*value: 0x1888BE0*/;// N4rage14fwRefAwareBaseE
	stack.setArg<int>(0x30,r4);
	r3 = call<int>((addrstruct().privk16^dataDecryptor()^0x36D23B4B)/*value: 0x150BAA4*/)(r3);//callTriggerScriptEventSelf
ret:
	//printf("End sub_483A58\n");
	encryptFunctionEnd();
	return r3;
}




__ALWAYS_INLINE int isCNetGamePlayerMe(int r3) {
	int v = *(int*)(r3+0x6C);
	v = v & 0x80;//get the highest bit in the last byte
	return (v>>7);//shift to front
}

//This function is confirmed to be correct assembly
ui64 CGameScriptHandlerNetComponent_msgScriptHostRequest(CGameScriptHandlerNetComponent *cGameScriptHandlerNetComponent) {

	//return call<ui64>(0xA5660C)(cGameScriptHandlerNetComponent);


	encryptFunctionStart(CGameScriptHandlerNetComponent_msgScriptHostRequest);


	//printf("Calling CGameScriptHandlerNetComponent_msgScriptHostRequest on %s\n",cGameScriptHandlerNetComponent->cGameScriptHandlerNetwork->gtaThread->threadName);
	
	ui64 r3 = 0, r4 = 0, r5 = 0, r6 = 0, r7 = 0, r8 = 0, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0, r16 = 0, r17 = 0, r18 = 0, r19 = 0, r20 = 0, r21 = 0, r22 = 0, r23 = 0, r24 = 0, r25 = 0, r26 = 0, r27 = 0, r28 = 0, r29 = 0, r30 = 0, r31 = 0;

	r3 = (ui64)cGameScriptHandlerNetComponent;

	char stackData[0x4A0];
	StackFrame stack(stackData,sizeof(stackData));
	
	r31 = r3;

	if (*(int*)(r3+0x8C)<=0)
		goto loc_A56650;
	r3 = (addrstruct().privk17^dataDecryptor()^0x6D9CA472)/*value: 0x1EC672C*/;//frameData
	r5 = *(int*)(r3+0x10);
	r5 = (int)((int)r4 - (int)r5);
	r4 = 0;
	if (r5 <= 0)
		goto loc_A5664C;
	r4 = r5;

loc_A5664C:
	//printf("loc_A5664C\n");
	*(int*)(r31+0x8C) = r4;


loc_A56650:
	//printf("loc_A56650\n");
	r3 = *(int*)(r31 + 0x34);
	if (r3 == 0)
		goto loc_A56720;
	r3 = isCNetGamePlayerMe(r3);//call<int>(0x9F8FD8)(r3);//isCNetGamePlayerMe
	if (r3 == 0)
		goto loc_A56720;
	r3 = *(int*)(r31+0xC);
	if (r3 != 0)
		goto ret;
	r4 = *(char*)(r31+0xAD);
	r3 = (r4 & 1);
	if (r3 == 0)
		goto loc_A566E4;
	r3 = *(int*)(r31+0x8C);
	if (r3 != 0)
		goto ret;
	r3 = *(int*)((addrstruct().privk18^dataDecryptor()^0x573243C4)/*value: 0x1CC57B8*/);//current_CGameScriptHandlerMgr
	r3 = *(int*)(r3+0x24);
	if (r3 == 0)
		goto loc_A566D0;
	r3 = *(int*)(r31+0x4);
	r4 = *(int*)(r3+0x0);
	r4 = *(int*)(r4+0x14);//opd struct
	r4 = *(int*)(r4+0x0);
	r3 = call<ui64>(r4)(r3);//at 0xA566B8
	r4 = *(int*)(r3+0x0);
	r4 = *(int*)(r4+0x18);
	r4 = *(int*)(r4+0x0);
	r3 = call<ui64>(r4)(r3);

loc_A566D0:
	//printf("loc_A566D0\n");
	r4 = 0;
	r3 = r31;
	*(int*)(r31+0x34) = r4;
	//r3 = call<int>(0xA563E4)(r3);//doN4rage19msgScriptVerifyHost12AutoIdDesc__E
	//This function above isn't necessary anyways so just ignore it
	goto ret;

loc_A566E4:
	//printf("loc_A566E4\n");
	//extrwi    r3, r4, 1,24
	r3 = r4 & 0xFF;//get last 8 bits (32-24)
	r3 = r3 >> 7;//shift it right 8-1 bits
	//end of extrwi command
	if (r3 != 0)
		goto ret;
	r5 = *(int*)r31;
	r3 = r31;
	r7 = *(short*)(r31+0x2C);
	r6 = 1;
	r4 = *(int*)(r31+0x34);
	r8 = *(int*)(r5+0x80);
	r5 = r7 + 1;
	r5 = r5 & 0xFFFF;//clrlwi    r5, r5, 16
	r7 = *(int*)r8;
	r3 = call<int>(r7)(r3,r4,r5,r6);
	goto ret;

loc_A56720:
	//printf("loc_A56720\n");
	r3 = *(char*)(r31+0xAD);
	//extrwi    r3, r3, 1,29
	r3 = r4 & 0x7;//get last 3 bits (0x7 = 0b111)  (32-29)
	r3 = r3 >> 2;//shift it right 3-1 bits
	//end of extrwi command
	if (r3 == 0) {
		//printf("going to ret 1\n");//this was the one called
		//goto ret; turn this off to get it to work :)
	}
	r4 = *(int*)(r31+0x1C);
	if (r4 == 0)
		goto loc_A56758;
	r3 = *(int*)(r4+0x8);
	if (r3 == 0)
		goto loc_A56758;
	r3 = isCNetGamePlayerMe(r3);//call<int>(0x9F8FD8)(r3);//isCNetGamePlayerMe
	r4 = *(int*)(r31+0x1C);
	if (r3 != 0) {
		//printf("going to ret 2\n");//this one was not called
		goto ret;
	}

loc_A56758:
	//printf("loc_A56758\n");
	if (r4 == 0)
		goto ret;
	r3 = *(int*)(r4+0x8);
	if (r3 == 0)
		goto ret;
	r3 = *(int*)(r31+0x8C);
	if (r3 != 0)
		goto ret;
	r3 = *(int*)(r31+0x4);
	r4 = *(int*)r3;
	r4 = *(int*)(r4+0x14);
	r4 = *(int*)r4;
	r3 = call<ui64>(r4)(r3);//at 0xA5678C
	r4 = *(int*)(r31+0x1C);
	r26 = r3;
	r30 = 0;
	if (r4 == 0)
		goto loc_A567A8;
	r30 = *(int*)(r4+0x8);




loc_A567A8:
	//printf("loc_A567A8\n");
	r28 = (ui64)stack.get(0x54);
	r3 = r28;
	call<int>((addrstruct().privk4^dataDecryptor()^0x3706BB00)/*value: 0xA8B814*/)(r3);//initiaterr3forsomething
	r29 = (ui64)stack.get(0x430);
	r3 = r28;
	r4 = r29;
	r5 = 0x3D6;
	call<int>((addrstruct().privk5^dataDecryptor()^0x7F5E6DFB)/*value: 0xA8B908*/)(r3,r4,r5);//at 0xA567C4
	r3 = (addrstruct().privk19^dataDecryptor()^0x173A5C67)/*value: 0x1EC69C0*/;// g_N4rage20msgScriptHostRequest12AutoIdDes
	r4 = r28;
	r3 = *(int*)(r3+0x8);//the id of the host request
	r3 = call<ui64>((addrstruct().privk7^dataDecryptor()^0x559790D8)/*value: 0x1626844*/)(r3,r4);//initiateMsgEventSendToOthers

	//printf("Calling host request on %s\n",cGameScriptHandlerNetComponent->cGameScriptHandlerNetwork->gtaThread->threadName);

	r27 = 0;
	if (r3 == 0) {
		goto loc_A56808;
	}
	r5 = *(int*)r26;
	r3 = r26;
	r4 = r28;
	r5 = *(int*)(r5+0x20);
	r5 = *(int*)r5;
	call<int>(r5)(r3,r4);//at 0xA56800
	r27 = 1;


loc_A56808:
	//printf("loc_A56808\n");
	r3 = (ui64)stack.get(0x58);
	if (r3 == 0)
		goto loc_A5682C;
	r3 = 0;
	if (r27 == 0)
		goto loc_A56828;
	r3 = r28;
	r3 = call<int>((addrstruct().privk10^dataDecryptor()^0x74B50861)/*value: 0xA8B978*/)(r3);//usedOftenInKickStuff

loc_A56828:
	//printf("loc_A56828\n");
	r26 = r3;

loc_A5682C:
	//printf("loc_A5682C\n");
	if (r27 == 0)
		goto loc_A56854;
	r3 = *(int*)((addrstruct().privk3^dataDecryptor()^0x69455DAA)/*value: 0x1CC4A34*/);//call<ui64>(0x9F8E10)();//sub_9F8E10 get_someNetworkPlayerDataOrSomeShit
	r6 = r26;//clrldi    r6, r26, 32 I think just says r6 = 0
	r8 = (ui64)stack.get(0x38);
	r9 = 0;
	r4 = r30;
	r5 = r29;
	r7 = 1;
	r3 = call<ui64>((addrstruct().privk11^dataDecryptor()^0x711B6FA9)/*value: 0x9F8FF0*/)(r3,r4,r5,r6,r7,r8,r9);//sub_9F8FF0

loc_A56854:
	//printf("loc_A56854\n");
	r3 = 0xFA;
	*(int*)(r31+0x8C) = r3;


ret:

	encryptFunctionEnd();

	//printf("ret\n");
	return r3;

}

#endif





#if kickCodeNonServerBoundValues

bool setScri ptHost(CGameScriptHandlerNetwork *script, int player);
/*int getRandomPlayingPlayer() {
	int player = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0,17);
	while (!NETWORK::NETWORK_IS_PLAYER_CONNECTED(player))
		player = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0,17);
	return player;
}*/

int getHostOfF reemodeScript() {
	encryptFunctionStart(getHostOfFreemodeScript);
	char freemode[] = {0x3D, 0x29, 0x3E, 0x3E, 0x36, 0x34, 0x3F, 0x3E, 0x5B};//"freemode"
	for (int i = 0; i < sizeof(freemode); i++)
		freemode[i] ^= 0x5b;
	int ret = NETWORK::NETWORK_GET_HOST_OF_SCRIPT(freemode, -1, 0);
	encryptFunctionEnd();
	return ret;
}

int playerToHostVoteKick = 0;
int previousScriptHost = 0;

void kickPlayer HostVoteEnd(int player) {
	encryptFunctionStart(kickPlayerHostVoteEnd);
	if (getHostOfFreemodeScript() == PLAYER::PLAYER_ID()) {
		Write_Global(1588610 + player + 1/*Off by One Error*/, 0); /*Set Player out of Position, needed so next player who joins does not get kick (confirmed needed)*/
		
		/*
		Don't worry about switching back to old host
		int newHost = previousScriptHost;
		if (!NETWORK::NETWORK_IS_PLAYER_CONNECTED(newHost)) {
			newHost = getRandomPlayingPlayer();
		}
		setScriptHost(freemodeScriptCGameScriptHandlerNetwork,newHost);*/

		char str[] = {0xCD, 0xD4, 0xCD, 0xF5, 0xDA, 0xDD, 0xDA, 0xC0, 0xDB, 0xD6, 0xD7, 0x93, 0xD8, 0xDA, 0xD0, 0xD8, 0x92, 0xB3};//"~g~Finished kick!"
		for (int i = 0; i < sizeof(str); i++)
			str[i] = str[i] ^ 0xb3;
		print2(str);
	}
	encryptFunctionEnd();
}


ui64 sub_ 483A58(CGameScriptHandlerNetComponent *cGameScriptHandlerNetComponent, CNetGamePlayer *player);

void kickPlay erHostVoteStart(int player) {
	encryptFunctionStart(kickPlayerHostVoteStart);
	//thanks irish!
	if (getHostOfFreemodeScript() == PLAYER::PLAYER_ID()) {
		Write_Global(1315372, 2); /*Global Setting Host Privledges*/
		Write_Global(1588610 + player + 1/*Off by One Error*/, 1); /*Set Player in Position*/
		if (player != PLAYER::PLAYER_ID()) {
			int iVar4 = 0;
			while (iVar4 <= 17) {
				Write_Global(1587565 + (int)(iVar4 * 58) + 39 + player + 1, 1); /*Increment Player Through Votes*/
				iVar4++;
			}
		}
		
		runlater::runlater(250,kickPlayerHostVoteEnd,player);//200 seemed to work but notification was like right before so I don't trust it
		char str[] = {0xED, 0xEA, 0xED, 0xD8, 0xFA, 0xF0, 0xF8, 0xF6, 0xF7, 0xB3, 0xE0, 0xFC, 0xFC, 0xFD, 0xBD, 0xBD, 0xBD, 0x93};//"~y~Kicked soon..."
		for (int i = 0; i < sizeof(str); i++)
			str[i] = str[i] ^ 0x93;
		
		//char str[] = {0xCD, 0xD4, 0xCD, 0xF5, 0xDA, 0xDD, 0xDA, 0xC0, 0xDB, 0xD6, 0xD7, 0x93, 0xD8, 0xDA, 0xD0, 0xD8, 0x92, 0xB3};//"~g~Finished kick!"
		//for (int i = 0; i < sizeof(str); i++)
		//	str[i] = str[i] ^ 0xb3;
		print2(str);
	}/* else {
		print2("~r~Not host!");
	}*/
	encryptFunctionEnd();
}

void kickPlayerH ostVoteBegin(int player) {
	encryptFunctionStart(kickPlayerHostVoteBegin);
	playerToHostVoteKick = player;
	previousScriptHost = getHostOfFreemodeScript();
	if (previousScriptHost != PLAYER::PLAYER_ID()) {
		setScriptHost(freemodeScriptCGameScriptHandlerNetwork,PLAYER::PLAYER_ID());//get host
		runlater::runlater(40,kickPlayerHostVoteStart,playerToHostVoteKick);
		//print2("Started Kick A");
	} else {
		//alreadyy freemode script host
		kickPlayerHostVoteStart(playerToHostVoteKick);
		//print2("Started Kick B");
	}
	encryptFunctionEnd();
}

ui64 CGameScriptHa ndlerNetComponent_msgScriptHostRequest(CGameScriptHandlerNetComponent *cGameScriptHandlerNetComponent);

/**
This function is the very good one
player seems to only work as me
**/
bool setScript Host(CGameScriptHandlerNetwork *script, int player = -1) {
	encryptFunctionStart(setScriptHost);
	player = PLAYER::PLAYER_ID();//choosing other players doesn't work
	bool ret = false;
	if (script->cGameScriptHandlerNetComponentSyncOne != 0) {
		CGameScriptHandlerNetComponent_msgScriptHostRequest(script->cGameScriptHandlerNetComponentSyncOne);
		//call<int>(/*0xA57F28*/0x483A58)(script->cGameScriptHandlerNetComponentSyncOne,getCNetGamePlayer(player));
		sub_483A58(script->cGameScriptHandlerNetComponentSyncOne,getCNetGamePlayer(player));
		ret = true;
	}
	encryptFunctionEnd();
	return ret;
}

//This function is confirmed to be correct assembly
ui64 CGameScriptH andlerNetComponent_migrateToCNetGamePlayer(CGameScriptHandlerNetComponent *cGameScriptHandlerNetComponent, CNetGamePlayer *player) {
	encryptFunctionStart(CGameScriptHandlerNetComponent_migrateToCNetGamePlayer);
	ui64 r3 = 0, r4 = 0, r5 = 0, r6 = 0, r7 = 0, r8 = 0, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0, r16 = 0, r17 = 0, r18 = 0, r19 = 0, r20 = 0, r21 = 0, r22 = 0, r23 = 0, r24 = 0, r25 = 0, r26 = 0, r27 = 0, r28 = 0, r29 = 0, r30 = 0, r31 = 0;

	r3 = (ui64)cGameScriptHandlerNetComponent;
	r4 = (ui64)player;
	char stackData[0x4C0];
	StackFrame stack(stackData,sizeof(stackData));

	//printf("In CGameScriptHandlerNetComponent_migrateToCNetGamePlayer\n");
start:
	r27 = r3;
	r28 = r4;
	r3 = *(int*)(r27+0x4);
	r4 = *(int*)r3;
	r4 = *(int*)(r4+0x14);
	r4 = *(int*)r4;
	r3 = call<int>(r4)(r3);
	r24 = *(short*)(r27+0x2C);
	r23 = r3;
	//printf("Made it to this location A\n");
	r3 = *(int*)((*(int*)0x1CC4A34)+0x8C);//sub_9F8268
	r29 = (ui64)stack.get(0x74);
	r26 = *(int*)(r3+0x68);
	r3 = r29;
	call<int>(0xA8B814)(r3);//initiaterr3forsomething
	r30 = (ui64)stack.get(0x450);
	r3 = r29;
	r4 = r30;
	r5 = 0x3D6;
	call<int>(0xA8B908)(r3,r4,r5);
	r25 = 0;
	r3 = 0x1EC6980;
	r4 = r29;
	r31 = r25;
	r3 = *(int*)(r3+0x8);
	r3 = call<ui64>(0x1626844)(r3,r4);//initiateMsgEventSendToOthers
	if (r3 == 0)
		goto loc_A58088;
	//printf("Made it to this location B\n");
	r5 = *(int*)r23;
	r3 = r23;
	r4 = r29;
	r5 = *(int*)(r5+0x20);
	r5 = *(int*)r5;
	r3 = call<ui64>(r5)(r3,r4);
	r23 = stack.getArg<char>(0x5C);//make sure this owrks fine
	r3 = r23 & 0x80;
	if (r3 != 0)
		goto loc_A58028;
	r5 = stack.getArg<int>(0x68);
	r3 = stack.getArg<int>(0x6C);
	r4 = (int)r5 + 0x10;
	//printf("Made it to this location C\n");
	if (r4 > r3)
		goto loc_A58028;//I beleive this comparison is the right order
	r3 = r23 & 0x40;
	if (r3 != 0)
		goto loc_A58018;
	r6 = r5;
	r7 = stack.getArg<int>(0x70);
	r4 = r24;
	r5 = 0x10;
	r3 = stack.getArg<int>(0x74);
	r6 = r6 + r7;
	call<int>(0xA8B5FC)(r3,r4,r5,r6);



loc_A58018:
	//printf("loc_A58018\n");
	r3 = r29;
	r4 = 0x10;
	call<int>(0xA8BBBC)(r3,r4);
	r23 = stack.getArg<char>(0x5C);

loc_A58028:
	//printf("loc_A58028\n");
	r3 = r23 & 0x80;
	if (r3 != 0)
		goto loc_A58084;
	r5 = stack.getArg<int>(0x68);
	r3 = stack.getArg<int>(0x6C);
	r4 = r5 + 0x20;
	if (r4 > r3)
		goto loc_A58084;
	r3 = r23 & 0x40;
	if (r3 != 0)
		goto loc_A58078;
	r3 = r5;
	r6 = stack.getArg<int>(0x70);
	r7 = stack.getArg<int>(0x74);
	r4 = r26;
	r6 = r3 + r6;
	r5 = 0x20;
	r3 = r7;
	call<int>(0xA8B5FC)(r3,r4,r5,r6);

loc_A58078:
	//printf("loc_A58078\n");
	r3 = r29;
	r4 = 0x20;
	call<int>(0xA8BBBC)(r3,r4);

loc_A58084:
	r25 = 1;

loc_A58088:
	//printf("loc_A58088\n");
	r3 = (ui64)stack.get(0x78);
	if (r3 == 0)
		goto loc_A580AC;
	r3 = r31;
	if (r25 == 0)
		goto loc_A580A8;
	r3 = r29;
	r3 = call<int>(0xA8B978)(r3);//usedOftenInKickStuff

loc_A580A8:
	r26 = r3;

loc_A580AC:
	//printf("loc_A580AC\n");
	if (r25 == 0)
		goto loc_A580D4;
	r3 = *(int*)0x1CC4A34;//someNetworkPlayerDataOrSomeShit get_someNetworkPlayerDataOrSomeShit
	r6 = r26;
	r8 = (ui64)stack.get(0x58);
	r9 = 0;
	r4 = r28;
	r5 = r30;
	r7 = 1;
	//printf("Befoer 0x9F8FF0\n");
	call<int>(0x9F8FF0)(r3,r4,r5,r6,r7,r8,r9);//I wonder if this has more args
	//printf("After 0x9F8FF0\n");

loc_A580D4:
	//printf("loc_A580D4\n");
	r5 = 0x2710;
	r6 = *(int*)r27;
	r3 = r27;
	*(int*)(r27+0x34) = r28;
	r4 = 0;
	*(int*)(r27+0x8C) = r5;
	r5 = 0;
	r7 = *(int*)(r6+0x80);
	r6 = 1;
	r7 = *(int*)r7;
	r3 = call<ui64>(r7)(r3,r4,r5,r6);



ret:
	//printf("End CGameScriptHandlerNetComponent_migrateToCNetGamePlayer\n");
	encryptFunctionEnd();
	return r3;
}

//seems to be working now
ui64 getCEventNetwo rkAttemptHostMigration(ui64 r3, ui64 r4, ui64 r5) {
	encryptFunctionStart(getCEventNetworkAttemptHostMigration);
	ui64 r6 = 0, r7 = 0, r8 = 0, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0, r16 = 0, r17 = 0, r18 = 0, r19 = 0, r20 = 0, r21 = 0, r22 = 0, r23 = 0, r24 = 0, r25 = 0, r26 = 0, r27 = 0, r28 = 0, r29 = 0, r30 = 0, r31 = 0;

	r31 = r3;
	r29 = r4;
	r30 = r5;

	//printf("In getCEventNetworkAttemptHostMigration\n");

	//start of sub_150BB58
	*(int*)(r3+0x4) = 0;
	*(int*)(r3+0x0) = 0x1888BD0;
	//end of sub_150BB58

	r3 = *(char*)(r31+0xC);
	r4 = 0;
	r5 = 0x1894210;
	*(int*)(r31+0x8) = 0;
	*(int*)r31 = r5;
	*(int*)(r31+0x10) = r29;
	*(char*)(r31+0xC) = 0;
	r3 = *(char*)(r30+0x29);
	*(int*)(r31+0x14) = r3;

	//printf("End getCEventNetworkAttemptHostMigration\n");
	encryptFunctionEnd();
	return r3;
}

//This function is confirmed to be correct assembly
ui64 sub_483A 58(CGameScriptHandlerNetComponent *cGameScriptHandlerNetComponent, CNetGamePlayer *player) {
	encryptFunctionStart(sub_483A58);
	ui64 r3 = 0, r4 = 0, r5 = 0, r6 = 0, r7 = 0, r8 = 0, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0, r16 = 0, r17 = 0, r18 = 0, r19 = 0, r20 = 0, r21 = 0, r22 = 0, r23 = 0, r24 = 0, r25 = 0, r26 = 0, r27 = 0, r28 = 0, r29 = 0, r30 = 0, r31 = 0;

	r3 = (ui64)cGameScriptHandlerNetComponent;
	r4 = (ui64)player;
	char stackData[0xA0];
	StackFrame stack(stackData,sizeof(stackData));

	//printf("In sub_483A58\n");

	r30 = r3;
	r31 = r4;
	CGameScriptHandlerNetComponent_migrateToCNetGamePlayer(cGameScriptHandlerNetComponent,player);//call<int>(0xA57F28)(r3,r4);
	r3 = *(int*)(r30+0x8);
	if (r3 != 0x8)
		goto ret;
	r30 = *(int*)(r30+0x4);
	r30 = *(int*)(r30+0xC);
	if (r30 == 0)
		goto ret;
	r29 = (ui64)stack.get(0x30);
	r4 = *(int*)(r30+0x4);
	r5 = r31;
	r3 = r29;
	r3 = getCEventNetworkAttemptHostMigration(r3,r4,r5);//call<int>(0x5816C)(r3,r4,r5);
	r3 = call<int>(0x51BA0)();//getCurrentCEventGroupScriptNetwork
	r5 = *(int*)(r3+0x0);
	r4 = r29;
	r5 = *(int*)(r5+0x8);
	r5 = *(int*)(r5+0x0);
	r3 = call<int>(r5)(r3,r4);
	r3 = r29;
	r4 = 0x1888BE0;// N4rage14fwRefAwareBaseE
	stack.setArg<int>(0x30,r4);
	r3 = call<int>(0x150BAA4)(r3);//callTriggerScriptEventSelf
ret:
	//printf("End sub_483A58\n");
	encryptFunctionEnd();
	return r3;
}




__ALWAYS_INLINE int isCNetG amePlayerMe(int r3) {
	int v = *(int*)(r3+0x6C);
	v = v & 0x80;//get the highest bit in the last byte
	return (v>>7);//shift to front
}

//This function is confirmed to be correct assembly
ui64 CGameScriptHandlerNetComponent_ msgScriptHostRequest(CGameScriptHandlerNetComponent *cGameScriptHandlerNetComponent) {

	encryptFunctionStart(CGameScriptHandlerNetComponent_msgScriptHostRequest);


	//printf("Calling CGameScriptHandlerNetComponent_msgScriptHostRequest on %s\n",cGameScriptHandlerNetComponent->cGameScriptHandlerNetwork->gtaThread->threadName);
	
	ui64 r3 = 0, r4 = 0, r5 = 0, r6 = 0, r7 = 0, r8 = 0, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0, r16 = 0, r17 = 0, r18 = 0, r19 = 0, r20 = 0, r21 = 0, r22 = 0, r23 = 0, r24 = 0, r25 = 0, r26 = 0, r27 = 0, r28 = 0, r29 = 0, r30 = 0, r31 = 0;

	r3 = (ui64)cGameScriptHandlerNetComponent;

	char stackData[0x4A0];
	StackFrame stack(stackData,sizeof(stackData));
	
	r31 = r3;

	if (*(int*)(r3+0x8C)<=0)
		goto loc_A56650;
	r3 = 0x1EC672C;//frameData
	r5 = *(int*)(r3+0x10);
	r5 = (int)((int)r4 - (int)r5);
	r4 = 0;
	if (r5 <= 0)
		goto loc_A5664C;
	r4 = r5;

loc_A5664C:
	//printf("loc_A5664C\n");
	*(int*)(r31+0x8C) = r4;


loc_A56650:
	//printf("loc_A56650\n");
	r3 = *(int*)(r31 + 0x34);
	if (r3 == 0)
		goto loc_A56720;
	r3 = isCNetGamePlayerMe(r3);//call<int>(0x9F8FD8)(r3);//isCNetGamePlayerMe
	if (r3 == 0)
		goto loc_A56720;
	r3 = *(int*)(r31+0xC);
	if (r3 != 0)
		goto ret;
	r4 = *(char*)(r31+0xAD);
	r3 = (r4 & 1);
	if (r3 == 0)
		goto loc_A566E4;
	r3 = *(int*)(r31+0x8C);
	if (r3 != 0)
		goto ret;
	r3 = *(int*)(0x1CC57B8);//current_CGameScriptHandlerMgr
	r3 = *(int*)(r3+0x24);
	if (r3 == 0)
		goto loc_A566D0;
	r3 = *(int*)(r31+0x4);
	r4 = *(int*)(r3+0x0);
	r4 = *(int*)(r4+0x14);//opd struct
	r4 = *(int*)(r4+0x0);
	r3 = call<ui64>(r4)(r3);//at 0xA566B8
	r4 = *(int*)(r3+0x0);
	r4 = *(int*)(r4+0x18);
	r4 = *(int*)(r4+0x0);
	r3 = call<ui64>(r4)(r3);

loc_A566D0:
	//printf("loc_A566D0\n");
	r4 = 0;
	r3 = r31;
	*(int*)(r31+0x34) = r4;
	//r3 = call<int>(0xA563E4)(r3);//doN4rage19msgScriptVerifyHost12AutoIdDesc__E
	//This function above isn't necessary anyways so just ignore it
	goto ret;

loc_A566E4:
	//printf("loc_A566E4\n");
	//extrwi    r3, r4, 1,24
	r3 = r4 & 0xFF;//get last 8 bits (32-24)
	r3 = r3 >> 7;//shift it right 8-1 bits
	//end of extrwi command
	if (r3 != 0)
		goto ret;
	r5 = *(int*)r31;
	r3 = r31;
	r7 = *(short*)(r31+0x2C);
	r6 = 1;
	r4 = *(int*)(r31+0x34);
	r8 = *(int*)(r5+0x80);
	r5 = r7 + 1;
	r5 = r5 & 0xFFFF;//clrlwi    r5, r5, 16
	r7 = *(int*)r8;
	r3 = call<int>(r7)(r3,r4,r5,r6);
	goto ret;

loc_A56720:
	//printf("loc_A56720\n");
	r3 = *(char*)(r31+0xAD);
	//extrwi    r3, r3, 1,29
	r3 = r4 & 0x7;//get last 3 bits (0x7 = 0b111)  (32-29)
	r3 = r3 >> 2;//shift it right 3-1 bits
	//end of extrwi command
	if (r3 == 0) {
		//printf("going to ret 1\n");//this was the one called
		//goto ret; turn this off to get it to work :)
	}
	r4 = *(int*)(r31+0x1C);
	if (r4 == 0)
		goto loc_A56758;
	r3 = *(int*)(r4+0x8);
	if (r3 == 0)
		goto loc_A56758;
	r3 = isCNetGamePlayerMe(r3);//call<int>(0x9F8FD8)(r3);//isCNetGamePlayerMe
	r4 = *(int*)(r31+0x1C);
	if (r3 != 0) {
		//printf("going to ret 2\n");//this one was not called
		goto ret;
	}

loc_A56758:
	//printf("loc_A56758\n");
	if (r4 == 0)
		goto ret;
	r3 = *(int*)(r4+0x8);
	if (r3 == 0)
		goto ret;
	r3 = *(int*)(r31+0x8C);
	if (r3 != 0)
		goto ret;
	r3 = *(int*)(r31+0x4);
	r4 = *(int*)r3;
	r4 = *(int*)(r4+0x14);
	r4 = *(int*)r4;
	r3 = call<ui64>(r4)(r3);//at 0xA5678C
	r4 = *(int*)(r31+0x1C);
	r26 = r3;
	r30 = 0;
	if (r4 == 0)
		goto loc_A567A8;
	r30 = *(int*)(r4+0x8);




loc_A567A8:
	//printf("loc_A567A8\n");
	r28 = (ui64)stack.get(0x54);
	r3 = r28;
	call<int>(0xA8B814)(r3);//initiaterr3forsomething
	r29 = (ui64)stack.get(0x430);
	r3 = r28;
	r4 = r29;
	r5 = 0x3D6;
	call<int>(0xA8B908)(r3,r4,r5);//at 0xA567C4
	r3 = 0x1EC69C0;// g_N4rage20msgScriptHostRequest12AutoIdDes
	r4 = r28;
	r3 = *(int*)(r3+0x8);//the id of the host request
	r3 = call<ui64>(0x1626844)(r3,r4);//initiateMsgEventSendToOthers

	//printf("Calling host request on %s\n",cGameScriptHandlerNetComponent->cGameScriptHandlerNetwork->gtaThread->threadName);

	r27 = 0;
	if (r3 == 0) {
		goto loc_A56808;
	}
	r5 = *(int*)r26;
	r3 = r26;
	r4 = r28;
	r5 = *(int*)(r5+0x20);
	r5 = *(int*)r5;
	call<int>(r5)(r3,r4);//at 0xA56800
	r27 = 1;


loc_A56808:
	//printf("loc_A56808\n");
	r3 = (ui64)stack.get(0x58);
	if (r3 == 0)
		goto loc_A5682C;
	r3 = 0;
	if (r27 == 0)
		goto loc_A56828;
	r3 = r28;
	r3 = call<int>(0xA8B978)(r3);//usedOftenInKickStuff

loc_A56828:
	//printf("loc_A56828\n");
	r26 = r3;

loc_A5682C:
	//printf("loc_A5682C\n");
	if (r27 == 0)
		goto loc_A56854;
	r3 = *(int*)(0x1CC4A34);//call<ui64>(0x9F8E10)();//sub_9F8E10 get_someNetworkPlayerDataOrSomeShit
	r6 = r26;//clrldi    r6, r26, 32 I think just says r6 = 0
	r8 = (ui64)stack.get(0x38);
	r9 = 0;
	r4 = r30;
	r5 = r29;
	r7 = 1;
	r3 = call<ui64>(0x9F8FF0)(r3,r4,r5,r6,r7,r8,r9);//sub_9F8FF0

loc_A56854:
	//printf("loc_A56854\n");
	r3 = 0xFA;
	*(int*)(r31+0x8C) = r3;


ret:

	encryptFunctionEnd();

	//printf("ret\n");
	return r3;

}

#endif


//};




#ifdef notusedcodelol
	/*
void requestScriptHost(CGameScriptHandlerNetComponent *script) {
	//printf("Freemode: CGameScriptHandlerNetComponent: 0x%X\n",script);
	//CGameScriptHandlerNetComponent_msgScriptHostRequest
	call<int>(0xA5660C)(script);
}*/

bool requestFreemodeScriptHost() {
	encryptFunctionStart(requestFreemodeScriptHost);
	bool ret = false;
	if (VALID_ADDR(freemodeScriptCGameScriptHandlerNetwork)) {
		CGameScriptHandlerNetComponent *netComponent = freemodeScriptCGameScriptHandlerNetwork->cGameScriptHandlerNetComponent;
		if (VALID_ADDR(netComponent)) {
			//printf("Regular one is valid!\n");
			CGameScriptHandlerNetComponent_msgScriptHostRequest(netComponent);
			ret = true;
		} else {
			//printf("cGameScriptHandlerNetComponent invalid, trying other one\n");
			netComponent = freemodeScriptCGameScriptHandlerNetwork->cGameScriptHandlerNetComponentSyncOne;
			if (VALID_ADDR(netComponent)) {
				//printf("Sync one is valid!\n");
				CGameScriptHandlerNetComponent_msgScriptHostRequest(netComponent);
				ret = true;
			} else {
				//printf("No valid net component\n");
			}
		}
	} else {
		//printf("freemodeScriptCGameScriptHandlerNetwork not valid!\n");
	}
	
	encryptFunctionEnd();
	return ret;
}


bool kickPlayerHostVoteGetHostToo(int player) {
	encryptFunctionStart(kickPlayerHostVoteGetHostToo);
	bool ret = false;
	char freemode[] = {0x3D, 0x29, 0x3E, 0x3E, 0x36, 0x34, 0x3F, 0x3E, 0x5B};//"freemode"
	for (int i = 0; i < sizeof(freemode); i++)
		freemode[i] ^= 0x5b;
	int scriptHostID = NETWORK::NETWORK_GET_HOST_OF_SCRIPT(freemode, -1, 0);
	if (scriptHostID == PLAYER::PLAYER_ID()) {
		kickPlayerHostVote(player);
		ret = true;
	} else {
		requestFreemodeScriptHost();
	}

	encryptFunctionEnd();
	return ret;
}
#endif



#ifdef failurOfAMigreateCode
bool keepFreemodeScriptToSelf = true;

ui64 sub_483A58_detour(CGameScriptHandlerNetComponent *r3, CNetGamePlayer *r4) {
	ui64 ret = 0;

	encryptFunctionStart_quick(sub_483A58_detour,1000);
	printf("A %s\n",r3->cGameScriptHandlerNetwork->gtaThread->threadName);
	bool isfr = r3->cGameScriptHandlerNetwork->gtaThread->nameHash == 0xC875557D;
	if (keepFreemodeScriptToSelf && isfr) {
		printf("Freemode script migrate requested A\n");
	} else {
		ret = call<ui64>(0x483A58)(r3,r4);
	}

	encryptFunctionEnd_quick();

	return ret;
}

ui64 CGameScriptHandlerNetComponent_migrateToCNetGamePlayer_detour(CGameScriptHandlerNetComponent *r3, CNetGamePlayer *r4) {
	ui64 ret = 0;

	encryptFunctionStart_quick(CGameScriptHandlerNetComponent_migrateToCNetGamePlayer_detour,1000);
	printf("B %s\n",r3->cGameScriptHandlerNetwork->gtaThread->threadName);
	bool isfr = r3->cGameScriptHandlerNetwork->gtaThread->nameHash == 0xC875557D;
	if (keepFreemodeScriptToSelf && isfr) {
		printf("Freemode script migrate requested B\n");
	} else {
		ret = call<ui64>(0xA57F28)(r3,r4);
	}

	encryptFunctionEnd_quick();

	return ret;
}

void setupAntiFreemodeScriptTransfer() {
	//encryptFunctionStart(setupAntiFreemodeScriptTransfer);
	*(ui64*)(0x1C2F558) = *(ui64*)((int)sub_483A58_detour);
	*(ui64*)(0x1C52440) = *(ui64*)((int)CGameScriptHandlerNetComponent_migrateToCNetGamePlayer_detour);
	//encryptFunctionEnd();
}
#endif

/*
void setupTheShit() {
	PatchInJump2(0xA5660C,(int)CGameScriptHandlerNetComponent_msgScriptHostRequest,false);
}*/

#ifdef xboxshit
namespace xbox_36_force_host {

struct CGameScriptHandlerNetComponent {};

struct CGameScriptHandlerNetwork {
	char data[0x24];
	CGameScriptHandlerNetComponent *cGameScriptHandlerNetComponent;//0x24
};

void xbox_requestHostOfScript(CGameScriptHandlerNetComponent *cGameScriptHandlerNetComponent) {
    int backup = *(int*)0x835385F0;
    *(int*)0x835385F0 = 0x60000000;//patch the jump in the spot
    ((void(*)(CGameScriptHandlerNetComponent *v)) 0x835384C0 )(cGameScriptHandlerNetComponent);
    *(int*)0x835385F0 = backup;
}

CGameScriptHandlerNetwork *freemodeScriptCGameScriptHandlerNetwork = 0;


void forceHost() {
	if (freemodeScriptCGameScriptHandlerNetwork != 0)
		xbox_requestHostOfScript(freemodeScriptCGameScriptHandlerNetwork->cGameScriptHandlerNetComponent);
}

CGameScriptHandlerNetwork *getCurrentCGameScriptHandlerNetwork() {
	return ((CGameScriptHandlerNetwork*(*)()) 0x82918CC0 )();
}

void hook() {
	if (!strcmp(SCRIPT::GET_THIS_SCRIPT_NAME()/*scrThread->ThreadName*/, "freemode")){
		freemodeScriptCGameScriptHandlerNetwork = getCurrentCGameScriptHandlerNetwork();
	}
}

}

#endif


#ifdef irishcodeforthekick

if (DoKickVotesEvent)
                {
                    if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(tempKickVotesEvent))
                    {
                        if (NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0) != PLAYER::PLAYER_ID()){
 
                            DoKickForceScriptTimer++;
                            if (DoKickForceScriptTimer > 250){
                                BETA_OPTIONS::KICK_OPTIONS::forceFreemodeScriptHost();
                                DoKickForceScriptTimer = 0;
                            }
                        } else {
 
                            DO_START_NOTIFI("Invoking Kick Online Player ~o~[ENFORCER]");
                            SetGlobal(1315372, 2, 0); /*Global Setting Host Privledges*/
                            SetGlobal(1588610 + tempKickVotesEvent + 1/*Off by One Error*/, 1, 0); /*Set Player in Position*/
                            if (tempKickVotesEvent != PLAYER::PLAYER_ID())
                            {
                                int iVar4 = 0;
                                while (iVar4 <= 17)
                                {
                                    SetGlobal(1587565 + (uint)(iVar4 * 58) + 39 + tempKickVotesEvent + 1, 1, 0); /*Increment Player Through Votes*/
                                    iVar4++;
                                }
                            }
                        }
 
                        DoKickVotesEventsTimer++;
                        if (DoKickVotesEventsTimer > 1500)
                        {
                            SetGlobal(1588610 + tempKickVotesEvent + 1/*Off by One Error*/, 0, 0); /*Set Player out of Position*/
                            DoKickForceScriptTimer = 0;
                            DoKickVotesEventsTimer = 0;
                            DoKickVotesEvent = false;
                            DO_START_NOTIFI("Kick Online Player ~o~[ENFORCER] ~s~failed...");
                        }
                    } else {
                        SetGlobal(1588610 + tempKickVotesEvent + 1/*Off by One Error*/, 0, 0); /*Set Player out of Position*/
                        DoKickForceScriptTimer = 0;
                        DoKickVotesEventsTimer = 0;
                        DoKickVotesEvent = false;
                    }
                }

#endif

#define oldversionofthenowuselessstuff

#ifdef oldversionofthenowuselessstuff   //this is old freeze player v3

bool shouldDoPlayerModifyBroadcastData = false;
CNetGamePlayer *playerModifyBroadcastDataPlayerCNetGamePlayer;
int playerModifyBroadcastDataAddress = 0;
int playerModifyBroadcastDataValue = 0;
bool playerModifyBroadcastDataCallIt = true;
void resetValuesThingForBroadcast(int i) {
	char str[] = {0x37, 0x2E, 0x37, 0xD, 0x26, 0x27, 0x2C, 0x68, 0x49};
	for (int i = 0; i < sizeof(str); i++)
			str[i]=str[i]^0x49;
	printf(str);//"~g~Done!"
	shouldDoPlayerModifyBroadcastData = false;//turn it off
}
__NO_INLINE void startPlayerModifyBroadcastData(int player, int global, int value, int triggerGlobal, int triggerGlobalValue, bool doCallAfter = true) {
	encryptFunctionStart_quick(startPlayerModifyBroadcastData,1000);
	if (assureHostOfFreemode()) {
		Write_Global_inline(triggerGlobal,triggerGlobalValue);//trigger it to call the update function
		playerModifyBroadcastDataPlayerCNetGamePlayer = getCNetGamePlayer(player);
		playerModifyBroadcastDataAddress = Read_Global_Address(global);
		playerModifyBroadcastDataValue = value;
		playerModifyBroadcastDataCallIt = doCallAfter;
		shouldDoPlayerModifyBroadcastData = true;
		runlater::runlater(1000,resetValuesThingForBroadcast);//use this cuz it may be called multiple times so add delay before turn off
	} else {
		char str[] = {0x23, 0x2F, 0x23, 0xD, 0x31, 0x38, 0x3C, 0x2E, 0x38, 0x7D, 0x29, 0x2F, 0x24, 0x7D, 0x3C, 0x3A, 0x3C, 0x34, 0x33, 0x5D};//"~r~Please try again";
		for (int i = 0; i < sizeof(str); i++)
			str[i]=str[i]^0x5d;
		print2(str);
	}
	encryptFunctionEnd_quick();
}

//1591180
__NO_INLINE void testTheWeirdFunctionCheck(int player) {//freeze v3 player
	encryptFunctionStart(testTheWeirdFunctionCheck);
	//set this to false to make it freeze them
	startPlayerModifyBroadcastData(player,1591180,0,1591181,GAMEPLAY::GET_RANDOM_INT_IN_RANGE(50,1027),false);//don't do call after, causes freeze
	encryptFunctionEnd();
}

#endif

/*
void testHostVariableSetThingy(int player) {
	//1591180
	startPlayerModifyBroadcastData(player,1591180,GAMEPLAY::GET_RANDOM_INT_IN_RANGE(1,50)    ,1591181,GAMEPLAY::GET_RANDOM_INT_IN_RANGE(50,1027));
	
}*/

#define funnValueIAmUsingForEncrypt (addrstruct().SCEventAnotherFunc^dataDecryptor()/*0xDDF8506E*/)

__NO_INLINE void lobbyFreezeV3_end(int a) {
	encryptFunctionStart_quick(lobbyFreezeV3_end,200);//120
	*(int*)(funnValueIAmUsingForEncrypt^0xDD67871A/*0x009FD774*/) = (funnValueIAmUsingForEncrypt^0x9366544F/*0x4E9E0421*/);
	//print2("Finished\n");
	encryptFunctionEnd_quick();
}

__NO_INLINE void lobbyFreezeV3() {
	encryptFunctionStart_quick(lobbyFreezeV3,500);//352
	if (assureHostOfFreemode()) {
		//freezes at 0x009FBA00
		//Freemode host is not required but you will get fake leave effect afterwards if you are not already freemode host before doing freeze
		//note that after doing some testing with this, it now makes freemode script crash after every time I try to do drop kick or similar
		*(int*)(funnValueIAmUsingForEncrypt^0xDD67871A/*0x009FD774*/) = 0x60000000;//patch the read unit broadcast call
		runlater::runlater(300,lobbyFreezeV3_end);
	} else {
		char str[] = {0x23, 0x2F, 0x23, 0xD, 0x31, 0x38, 0x3C, 0x2E, 0x38, 0x7D, 0x29, 0x2F, 0x24, 0x7D, 0x3C, 0x3A, 0x3C, 0x34, 0x33, 0x5D};//"~r~Please try again";
		for (int i = 0; i < sizeof(str); i++)
			str[i]=str[i]^0x5d;
		print2(str);
	}
	encryptFunctionEnd_quick();
}

/*
void fakeLeavePlayerNew(int player) {
	//using 1588610 global
	//writing to 1588610 causes fake leave

	startPlayerModifyBroadcastData(player,1588610,0,1588610+1+player,GAMEPLAY::GET_RANDOM_INT_IN_RANGE(3,1027));//just chose 5 because it shouldn't cause kick, only 1 should cause kick
}*/



//Global_1315298 set this on people for special crap :)

#define SESSION_ERR_KICK


#ifdef SESSION_ERR_KICK

bool kickPlayerBySessionError = false;
int kickPlayerBySessionErrorPlayerID = 0;
__NO_INLINE void startSessionKickOnPlayerCallback() {
	encryptFunctionStart_quick(startSessionKickOnPlayerCallback,100);
	unsigned int Global_2387877_address = (*(int*)0x1E70394+0x1BE94);
	//force it to call the update code, but this value won't cause any harm
	if (*(int*)Global_2387877_address == 3)
		*(int*)Global_2387877_address = 4;
	else
		*(int*)Global_2387877_address = 3;
	kickPlayerBySessionError = true;//set it to start lookin!
	encryptFunctionEnd_quick();
}
__NO_INLINE void startSessionKickOnPlayer(int player) {
	encryptFunctionStart_quick(startSessionKickOnPlayer,100);
	kickPlayerBySessionErrorPlayerID = player;
	assureHostOfFreemode(startSessionKickOnPlayerCallback);
	encryptFunctionEnd_quick();
}
#endif


bool fakeLeaveV2OnPlayerInQue = false;
int fakeLeaveV2OnPlayerPlayerID = 0;
void doFakeLeaveV2_allowNext(int){fakeLeaveV2OnPlayerInQue = false;};
__NO_INLINE void doFakeLeaveV2_callback() {
	encryptFunctionStart_quick(doFakeLeaveV2_callback,1000);
	unsigned int Global_1588610_address = (*(int*)0x1E70388+0xF608);
	unsigned int Global_1572928_address = (*(int*)0x1E70388+0x100);
	if (fakeLeaveV2OnPlayerInQue == false) {
		//1588610 set to 0x13 and then back to 0x12 later in the code right after the send
		//make it so it sends the update (part 1)
		if (*(int*)Global_1588610_address == 0x13)
			*(int*)Global_1588610_address = 0x12;
		else
			*(int*)Global_1588610_address = 0x13;
		//part 2
		if (*(int*)Global_1572928_address == 0x3)
			*(int*)Global_1572928_address = 0x2;
		else
			*(int*)Global_1572928_address = 0x3;


		fakeLeaveV2OnPlayerInQue = true;//tell it to send bad version to player
	}
	runlater::runlater(100,doFakeLeaveV2_allowNext);
	encryptFunctionEnd_quick();
}

__NO_INLINE void doFakeLeaveV2(int player) {
	encryptFunctionStart_quick(doFakeLeaveV2,100);
	fakeLeaveV2OnPlayerPlayerID = player;
	assureHostOfFreemode(doFakeLeaveV2_callback);
	encryptFunctionEnd_quick();
}



__ALWAYS_INLINE void modifySendPlayerVariablesBefore(CGameHostBroadcastDataHandler *cGameHostBroadcastDataHandler, CNetGamePlayer *player, bool isNewOne = false) {
	
#ifdef SESSION_ERR_KICK
	//session error kick
	unsigned int Global_2387877_address = (*(int*)0x1E70394+0x1BE94);
	if (kickPlayerBySessionError && (player->playerIndex == kickPlayerBySessionErrorPlayerID)) {
		if ((int)cGameHostBroadcastDataHandler->pointerToDataSyncLocation == Global_2387877_address) {
			//printf("global_2387877(1): 0x%X\n",cGameHostBroadcastDataHandler);
			//printf("Address writing to: 0x%X\n",cGameHostBroadcastDataHandler->getAddressOfCopiedOverData());
			//int val = *(int*)(cGameHostBroadcastDataHandler->getAddressOfCopiedOverData());
			//printf("Val before the run: %i\n",val);
			*(int*)(cGameHostBroadcastDataHandler->getAddressOfCopiedOverData()) = 5;//5 causes the kick
		}
	}
#endif
	
	//fake leave
	unsigned int Global_1588610_address = (*(int*)0x1E70388+0xF608);
	if ((int)cGameHostBroadcastDataHandler->pointerToDataSyncLocation == Global_1588610_address) {
		int orig = *(int*)(cGameHostBroadcastDataHandler->getAddressOfCopiedOverData());
		//printf("Right here! 0x%X 0x%X %i\n",*(int*)Global_1588610_address,orig,player->playerIndex);
		if (fakeLeaveV2OnPlayerInQue && (player->playerIndex == fakeLeaveV2OnPlayerPlayerID)) {
			//printf("Doing the modification!\n");
			//if (isNewOne)
			//	printf("Came from the second one! This could be why it works now\n");
			*(int*)(cGameHostBroadcastDataHandler->getAddressOfCopiedOverData()) = 0x0;//anything between 0 and 0x11 causes the bug, 0x12 is default and above works fine... 0x11 does not work sometimes
		}
	}
	//fake leave part 2 (extra measures)
	//Global_1572928 value 0 or 1, regular 2 or 3 works
	unsigned int Global_1572928_address = (*(int*)0x1E70388+0x100);
	if ((int)cGameHostBroadcastDataHandler->pointerToDataSyncLocation == Global_1572928_address) {
		if (fakeLeaveV2OnPlayerInQue && (player->playerIndex == fakeLeaveV2OnPlayerPlayerID)) {
			*(int*)(cGameHostBroadcastDataHandler->getAddressOfCopiedOverData()) = 0x0;//anything between 0 and 0x1 causes the bug, 0x2 is default and above works fine... 0x11 does not work sometimes
		}
	}


}
__ALWAYS_INLINE void modifySendPlayerVariablesAfter(CGameHostBroadcastDataHandler *cGameHostBroadcastDataHandler, CNetGamePlayer *player) {
#ifdef SESSION_ERR_KICK
	//session error kick
	unsigned int Global_2387877_address = (*(int*)0x1E70394+0x1BE94);
	if (kickPlayerBySessionError && (player->playerIndex == kickPlayerBySessionErrorPlayerID)) {
		if ((int)cGameHostBroadcastDataHandler->pointerToDataSyncLocation == Global_2387877_address) {
			//int val = *(int*)(cGameHostBroadcastDataHandler->getAddressOfCopiedOverData());
			//printf("Val after the run: %i\n",val);
			*(int*)(cGameHostBroadcastDataHandler->getAddressOfCopiedOverData()) = 4;//4 is default
			*(int*)Global_2387877_address = 4;//reset the value back to default as it was before
			kickPlayerBySessionError = false;
		}
	}
#endif

	//fake leave
	unsigned int Global_1588610_address = (*(int*)0x1E70388+0xF608);
	if ((int)cGameHostBroadcastDataHandler->pointerToDataSyncLocation == Global_1588610_address) {
		if (fakeLeaveV2OnPlayerInQue && (player->playerIndex == fakeLeaveV2OnPlayerPlayerID)) {
			*(int*)(cGameHostBroadcastDataHandler->getAddressOfCopiedOverData()) = *(int*)Global_1588610_address;//set value in copied data back to 0x12 for next player who will receive it
			//*(int*)Global_1588610_address = 0x12;//reset the value on me to orig   I THINK THIS CAUSES IT TO RESENT THE NORMAL VALUE AND THEN NOT CAUSE THEM TO FAKE LEAVE SOMETIMES
			//fakeLeaveV2OnPlayerInQue = false;//reset it so can call again next time  NEED TO DO SOMEWHERE ELSE BECAUSE THE FIRST CALL IS NOT THE FINAL ONE AGH
			//printf("End of it!\n");
		}
	}
	//fake leave part 2 (extra measures)
	//Global_1572928 value 0 or 1, regular 2 or 3 works
	unsigned int Global_1572928_address = (*(int*)0x1E70388+0x100);
	if ((int)cGameHostBroadcastDataHandler->pointerToDataSyncLocation == Global_1572928_address) {
		if (fakeLeaveV2OnPlayerInQue && (player->playerIndex == fakeLeaveV2OnPlayerPlayerID)) {
			*(int*)(cGameHostBroadcastDataHandler->getAddressOfCopiedOverData()) = *(int*)Global_1572928_address;
		}
	}
}

//#define fuckplayerfreezev3   //this version doesn't work all the time
#ifdef fuckplayerfreezev3
bool freezePlayerV3Boolean = false;
bool freezePlayerV3Player = 0;
void doPlayerFreezeV3_callback(int) {
	freezePlayerV3Boolean = false;
	print2("Done!\n");
}
__NO_INLINE void doPlayerFreezeV3_() {
	encryptFunctionStart_quick(doPlayerFreezeV3_,200);
	unsigned int Global_1591181_address = (*(int*)0x1E70388+0x11E34);
	*(int*)Global_1591181_address = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(50,1027);
	freezePlayerV3Boolean = true;
	runlater::runlater(200,doPlayerFreezeV3_callback);
	encryptFunctionEnd_quick();
}
__NO_INLINE void doPlayerFreezeV3(int player) {
	encryptFunctionStart(doPlayerFreezeV3);
	freezePlayerV3Player = player;
	assureHostOfFreemode(doPlayerFreezeV3_);
	encryptFunctionEnd();
}
#endif

__NO_INLINE void playerBroadcastVariablesSend_(CGameHostBroadcastDataHandler *cGameHostBroadcastDataHandler, CNetGamePlayer *player, ui64 r5, ui64 r6, ui64 r7, ui64 r8) {
	encryptFunctionStart_quick(playerBroadcastVariablesSend_,1000);
	bool shouldCall = true;
#ifdef oldversionofthenowuselessstuff
	bool resetValue = false;
	int origValueAtAddress = 0;
	//printf("Called send broadcast function. Check bypass: %i\n",shouldDoPlayerModifyBroadcastData);
	if (shouldDoPlayerModifyBroadcastData) {
		if (player == playerModifyBroadcastDataPlayerCNetGamePlayer) {
			if (playerModifyBroadcastDataAddress >= (int)cGameHostBroadcastDataHandler->pointerToDataSyncLocation && playerModifyBroadcastDataAddress < ((int)cGameHostBroadcastDataHandler->pointerToDataSyncLocation + cGameHostBroadcastDataHandler->sizeOfSyncData*4)) {
				//playerModifyBroadcastDataAddress is in the range of the data in this CGameHostBroadcastDataHandler
				origValueAtAddress = *(int*)playerModifyBroadcastDataAddress;
				*(int*)playerModifyBroadcastDataAddress = playerModifyBroadcastDataValue;
				resetValue = true;
				//printf("Diid the sick patch!\n");
				shouldCall = playerModifyBroadcastDataCallIt;

				/*
				freeze fix
				0x009FBBC8
				0x009FBBCC

				*/
			}
		}
	}
#endif
	//printf("Before call!\n");
	/*
	A1994C playerBroadcastVariablesUpdateVariablesToOtherPlayers is the actual important function
	
	
	*/

#ifdef fuckplayerfreezev3
	if (freezePlayerV3Boolean) {
		if (player->playerIndex == freezePlayerV3Player) {
			shouldCall = false;
		}
	}
#endif

	modifySendPlayerVariablesBefore(cGameHostBroadcastDataHandler,player);

	//modifyHostDataBeforeSend(cGameHostBroadcastDataHandler,player);


	if (shouldCall)
		call<int>(funnValueIAmUsingForEncrypt^0xDD59C9FE/*0xA19990*/)(cGameHostBroadcastDataHandler,player,r5,r6,r7,r8);

	modifySendPlayerVariablesAfter(cGameHostBroadcastDataHandler,player);


	//modifyHostDataAfterSend(cGameHostBroadcastDataHandler,player);

	/*

	THESE ARE 100% THE SPOTS IIT IS READ FROM

	0x024E6EF4   -- This one is for me. If I nop this, the other players can still see the real values
	or
	0x14F631C  <-- THIS IS 100% THE SPOT WE NEED TO RESEARCH INTO. JUST SET A READ BREAKPOINT ON GLOBAL 1591180
	
	*/
#ifdef oldversionofthenowuselessstuff
	if (resetValue) {
		//shouldDoPlayerModifyBroadcastData = false;
		//printf("Reset value!\n");
		*(int*)playerModifyBroadcastDataAddress = origValueAtAddress;//reset the value
	}
#endif
	encryptFunctionEnd_quick();
}

__NO_INLINE void playerBroadcastVariablesSend(CGameHostBroadcastDataHandler *cGameHostBroadcastDataHandler, CNetGamePlayer *player, ui64 r5, ui64 r6, ui64 r7, ui64 r8) {
	//This one has the CGamePlayerBroadcastDataHandler_Local as an arg but the one with the playerBroadcastVariablesSend_ does not
	encryptFunctionStart_quick(playerBroadcastVariablesSend,1000);//change to 100 later and try
	modifySendPlayerVariablesBefore(cGameHostBroadcastDataHandler,player,true);
	call<int>(funnValueIAmUsingForEncrypt^0xDD67E3A6/*0x9FB3C8*/)(cGameHostBroadcastDataHandler,player,r5,r6,r7,r8);
	modifySendPlayerVariablesAfter(cGameHostBroadcastDataHandler,player);
	encryptFunctionEnd_quick();
}

__NO_INLINE void setupBroadcastVariablePatch() {
	encryptFunctionStart(setupBroadcastVariablePatch);
	*(ui64*)(funnValueIAmUsingForEncrypt^0xDC3CAA86/*0x1C4FAE8*/) = *(ui64*)((int)playerBroadcastVariablesSend_);
	*(ui64*)(funnValueIAmUsingForEncrypt^0xDC3CA5F6/*0x1C4F598*/) = *(ui64*)((int)playerBroadcastVariablesSend);
	encryptFunctionEnd();
}


/*
0x009FBBC8
0x009FBBCC



0x96E31C = 3B 40 00 00
*/

#ifdef hostchangeteststuff
void switchHost() {//0x96E49C
	int r27 = *(int*)0x1CF72C4 + 0x50;//initial value
	int r3 = -1;
	int r5 = *(int*)r27;
	int r4 = 0x1768;
	int r6 = 0;
	*(ui64*)(r27 + 0x1EB8) = r3;
	int r7 = *(int*)r5;
	r3 = r5;
	r5 = 0;
	r7 = *(int*)(r7+0xC);
	r7 = *(int*)r7;
	printf("Got here\n");
	r3 = call<int>(r7)(r3,r4,r5,r6);//r6 and r5 are 0
	int r28 = r3;
	if (r3 == 0) {
		printf("End early lol\n");
		goto loc_96E4F4;
	}
	printf("About to be here\n");
	call<int>(0x99EDFC)(r3);//createN4rage20snMigrateSessionTaskE_1
	r3 = 0x18F2D40;//N4rage19rlFireAndForgetTaskINS_20snMigrateSessionTaskEEE
	*(int*)(r28+0x1760) = 0;
	*(int*)(r28+0x1764) = 0;
	*(int*)r28 = r3;


loc_96E4F4:


	printf("End! Setting up the rest of the thing.\n");

	if (r28 != 0) {
		printf("Going to set up more shit\n");
		*(int*)(r28+0x64) = 1;//make it jump to down below!
		*(int*)(r28+0x68) = 3;//make it not do the first jump on conclusion function at 0x99FAD4
		//now 0x99F570 should be called
	}

	/*
	if (r28 == 0)
		goto loc_96E5D8;
	int r26 = r28 + 0x1760;
	if (r26 == 0)
		goto loc_96E514;
	r3 = *(int*)(r28+0x1760);
	if (r3 == 0)
		goto loc_96E5D8;

loc_96E514:
	r3 = *(int*)(r28+0x54);
	if (r3 != 0)
		goto loc_96E5A4;
	r3 = r28;
	//r6 = r29;
	*(int*)(r28+0x54) = r27;
	r4 = r27;
	//r5 = r30;

loc_96E5A4:
loc_96E5D8:
	printf("This should not happen!\n");
	*/

}

void hostChangeTest() {
	char stack[0x790];//no idea whats in it
	for (int i = 0; i < 0x20; i++) {
		printf("v: %i\n",i);
		call<int>(0xD26030)(((ui64)&stack) + 0x38*i);//init the function
	}
	printf("Here\n");
	int callVal = call<int>(0x96E624)(*(int*)0x1CF72C4 + 0x50,&stack);//player count I think
	printf("Boi 0x%X %i\n",callVal,callVal);


	//patch 0x96E308 to return snMigrateSessionTask
	*(int*)0x96E618 = 0x7F83E378;//mr        %r3, %r28
	int snMigrateSessionTask = call<int>(0x96E308)(*(int*)0x1CF72C4 + 0x50,&stack,callVal/* 0 forces it to call callVal*/);
	//unpatch 0x96E308 to return the original value
	*(int*)0x96E618 = 0x63E30000;

	if (VALID_ADDR(snMigrateSessionTask)) {
		printf("Valid snMigrateSessionTask!\n");
		*(int*)(snMigrateSessionTask+0x64) = 1;//make it jump to down below!
		*(int*)(snMigrateSessionTask+0x68) = 3;//make it not do the first jump on conclusion function at 0x99FAD4
	} else {
		printf("Not valid snMigrateSessionTask!\n");
	}

	//need to call snMsgMigrateHostRequest_migrateMeToHost
	printf("Finished\n");
}

void hostChangeTest2() {
	//this is like what happens when you join a lobby
	call<int>(0x139A46C)(*(int*)0x1CF72C4);
}

#endif

bool shouldRenderMenu() {
	static int lastCount = 0;
	int newCount = *(int*)(0x1EC672C+0x4);
	if (newCount != lastCount) {
		if (strstr("freemode",SCRIPT::GET_THIS_SCRIPT_NAME()) != 0) {
			lastCount = newCount;
			return true;
		}
	}
	return false;
}


__NO_INLINE void freezePlayerV4(int player) {
	//Created 4/25/2020
	encryptFunctionStart(freezePlayerV4);
	CNetGamePlayer* cnet = getCNetGamePlayer(player);
	if (VALID_ADDR(cnet))
		sub_483A58/*CGameScriptHandlerNetComponent_migrateToCNetGamePlayer*/(freemodeScriptCGameScriptHandlerNetwork->cGameScriptHandlerNetComponentSyncOne, cnet, true);
	encryptFunctionEnd();
}



int getPoolSizeByHash(int hash) {
	return call<int>(0xA5356C)(*(int*)0x1CC56FC,hash,1);
}

struct ConfigNetScriptBroadcastData {
	int SizeOfData;
	int MaxParticipants;
	int NumInstances;
};
ConfigNetScriptBroadcastData *get_PlayerBroadcastData_ConfigNetScriptBroadcastData(int index) {
	if (VALID_ADDR(*(int*)0x1CC56FC)) {
		if (VALID_ADDR(*(int*)(*(int*)0x1CC56FC+0x10))) {
			//ConfigNetScriptBroadcastData in gameconfig.xml
			//*(int*)(*(int*)0x1CC56FC+0x10)+0x13C+0xC*i
			int address = *(int*)(*(int*)0x1CC56FC+0x10)+0x13C+0xC*index;
			return (ConfigNetScriptBroadcastData *)address;
		}
	}
	return 0;
}



#ifdef sjhdhgiusfdhgviudjhfgjihjdsfgijjfsdij
void CGameScriptHandlerNetComponent__setMemorySyncPlayers_detour(CGameScriptHandlerNetComponent *script, unsigned int dataAddress, size_t size_in_bytes) {
	printf("Called CGameScriptHandlerNetComponent__setMemorySyncPlayers!\n");
	bool unwrite = false;
	if (dataAddress == (Read_Global_Address(1587565)+0x4)) {
		printf("Fixing it up!\n");
		/**(int*)0x0130D36C = 0x60000000;//nop the trap that it hits because of duplicate player id or whatever
		unwrite = true;
		int val = 0x39000000;
		int pid = PLAYER::PLAYER_ID();
		val = val | pid;
		*(int*)0xA003F8 = val;*/
		*(int*)0x130D178 = 0x60000000;//patch the jump to the remote so it stays on local
		*(int*)0x130D188 = 0x60000000;//same
		*(int*)0x130D180 = 0x60000000;//iscnetgameplayerme patch it to not call
	}

	call<int>(0xA5A674)(script,dataAddress,size_in_bytes);

	if (unwrite) {
		//*(int*)0xA003F8 = 0x63880000;
		*(int*)0x130D178 = 0x418201FC;
		*(int*)0x130D188 = 0x418201EC;
		*(int*)0x130D180 = 0x4B6EBE59;
	}
}


/*void NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES_hook(int r3) {
	int g_addr = *(int*)*(int*)(r3+0x8);
	if (g_addr == Read_Global_Address(1587565)) {
		printf("Got the patch one! Calling host instead\n");
		call<int>(0x15891A0)(r3);
		printf("Called host broadcast var\n");
	} else {
		printf("Calling orig\n");
		call<int>(0x15891D0)(r3);

	}
}*/



/*void setScriptValueSizeWeirdThing() {
	int floatStoreHashValueStruct = *(int*)0x1CC56FC;
	if (floatStoreHashValueStruct != 0) {
		int cGameConfig = *(int*)(floatStoreHashValueStruct+0x10);
		if (cGameConfig != 0) {
			*(int*)(cGameConfig + 0x1B4) = 0x20;//0xA aka 10 by default...
			printf("Set value in cgameconfig!\n");
			return;
		}
	}
	printf("failed to Set value in cgameconfig!\n");
}*/




void allocateMemoryToCGamePlayerBroadcastDataHandler_RemotePool_detour(int mgr/*CGameArrayMgr **/) {
	get_PlayerBroadcastData_ConfigNetScriptBroadcastData(4)->NumInstances += 1;//set to 18 so it creates enough of the _Local for us
	printf("Changed the count to 18!\n");
	call<int>(0x130C530)(mgr);
	get_PlayerBroadcastData_ConfigNetScriptBroadcastData(4)->NumInstances -= 1;//set to 18 so it creates enough of the _Local for us
	printf("End of here\n");
}


void CGameScriptHandlerNetComponent__setMemorySyncPlayers_setAreaAsSyncedToAllPlayers_detour(int CGameArrayMgr, unsigned int syncData, int syncDataSize, CGameScriptHandlerNetwork *cgsn, int indexPreviouslyGotten) {
	int nc = (int)cgsn->cGameScriptHandlerNetComponentSyncOne;
	if (nc == 0)
		return;
	char playerCount = *(char*)(nc+0x90);
	if (playerCount == 0) {
		printf("Player count is 0\n");
		return;
	}
	if (playerCount != 0x12) {
		printf("Error! not 0x12\n");
		playerCount = 0x12;
	}
	int sizePerPlayer = syncDataSize/playerCount;
	for (int i = 0; i < playerCount; i++) {
		//CNetGamePlayer *cnetforplayer = call<CNetGamePlayer*>(0xA5818C)(cgsn->cGameScriptHandlerNetComponentSyncOne,i);
		//skip over log stuff
		bool doUndo = false;
		if ((i == 0 || i == PLAYER::PLAYER_ID()) && syncData == (Read_Global_Address(1587565)+0x4)) {
			//host is 0 on our test
			
			*(int*)0x130D178 = 0x60000000;//patch the jump to the remote so it stays on local
			*(int*)0x130D188 = 0x60000000;//same
			*(int*)0x130D180 = 0x60000000;//iscnetgameplayerme patch it to not call
			doUndo = true;
		}
		CGamePlayerBroadcastDataHandler_Local *val = call<CGamePlayerBroadcastDataHandler_Local*>(*(int*)(*(int*)(*(int*)CGameArrayMgr+0x34)+0x0))(CGameArrayMgr,syncData+i*sizePerPlayer,sizePerPlayer,cgsn,indexPreviouslyGotten,i);
		if (doUndo == true) {
			*(int*)0x130D178 = 0x418201FC;
			*(int*)0x130D188 = 0x418201EC;
			*(int*)0x130D180 = 0x4B6EBE59;
		}
		//*(int*)(((int)&val)+0xB0) = i;
		//cal also be remote. 0xB0 on remote is the only spot the player numbber is used and idk if it means anything
		if (val == 0)
			continue;
		call<int>(*(int*)(*(int*)(*(int*)CGameArrayMgr+0x18)+0x0))(CGameArrayMgr,val);
	}
}


void setup_CGameScriptHandlerNetComponent__setMemorySyncPlayers_hook() {
	char newSize = 0xF0;
	//*(char*)(0x130C8CC+0x0+0x3) = newSize;//patch it from 0x10 to 0xF0
	//*(char*)(0x130C8CC+0x4+0x3) = newSize;//patch it from 0x10 to 0xF0 second part
	//*(char*)(0x130C8CC+0x3) = newSize;//this one is different. It sets the allocated size to add 0xF0 max on next. This makes the allocated array space guarenteed much larger
	//*(char*)(0x130C668+0x3) = newSize;
	//*(char*)(0x130C670+0x3) = newSize;
	//*(char*)(0x130C72C+0x3) = newSize;
	//*(char*)(0x130C730+0x3) = newSize;
	//*(char*)(0x130C808+0x3) = newSize;
	//*(char*)(0x130C810+0x3) = newSize;
	//*(char*)(0x130C8CC+0x3) = newSize;
	//*(char*)(0x130C8D0+0x3) = newSize;
	/*need to know which index uses Global_1587565*/
	
	//get_PlayerBroadcastData_ConfigNetScriptBroadcastData(8)->NumInstances += 18;
	//get_PlayerBroadcastData_ConfigNetScriptBroadcastData(7)->NumInstances += 18;
	//should be index 4 I think it's 232 per player
	//get_PlayerBroadcastData_ConfigNetScriptBroadcastData(4)->NumInstances += 1;
	/*
	 <Item>
              <SizeOfData value="270"/>
              <MaxParticipants value="18"/>
              <NumInstances value="2"/>
            </Item>
	Almost 100% sure that is for the global 1587565  which is index 4
	
	*/

	//*(ui64*)0x1C6D6F8 = *(ui64*)((int)allocateMemoryToCGamePlayerBroadcastDataHandler_RemotePool_detour);//add more of the locals

	//*(ui64*)0x1C524E0 = *(ui64*)((int)CGameScriptHandlerNetComponent__setMemorySyncPlayers_detour);//make the one global do all _Local instead of only 1 for my player (old method)
	//*(int*)0x1C291A0 = *(int*)((int)NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES_hook);

	//PatchInJumpAddr(0xA00304,(int)CGameScriptHandlerNetComponent__setMemorySyncPlayers_setAreaAsSyncedToAllPlayers_detour,false);
}
#endif
/*void fixThePlayerSyncPoolForMe_callback(int entityAddress) {

}
void fixThePlayerSyncPoolForMe() {
	executeOnPool(,fixThePlayerSyncPoolForMe_callback);
}*/


/*
CGamePlayerBroadcastDataHandler_Local = me send to them
CGamePlayerBroadcastDataHandler_Remote = them send to me

GOAL:
get
130D244                 bl        get_37CGamePlayerBroadcastDataHandler_Local
to not return 0 when we register on self or whatever

*/

void printDone() {
	char buf[] = {0x1C, 0x5, 0x1C, 0x26, 0xD, 0xC, 0x7, 0x43, 0x62};//"~g~Done!"
	for (int i = 0; i < sizeof(buf); i++)
		buf[i] = buf[i]^0x62;
	print2(buf);
}


#ifdef kiinda_bad_lobby_modifying_broadcast_vars

//int queFakeLeaveOnLobby = 0;
CGameHostBroadcastDataHandler *global_1588610_sync = 0;
CGameHostBroadcastDataHandler *global_2387877_sync = 0;

//int timerOnThecode = 1000;
bool readyForTheFixOfIt = true;
void reset_global_1588610_sync(int i) {
	encryptFunctionStart_quick(reset_global_1588610_sync,500);
	if (global_1588610_sync != 0) {
		*(int*)&global_1588610_sync->pointerToDataSyncLocation -= 0x4;
		//printf("Finished!\n");
		printDone();
	}
	readyForTheFixOfIt = true;
	encryptFunctionEnd_quick();
}
void doLobbyFakeLeaveNewCallback() {
	encryptFunctionStart_quick(doLobbyFakeLeaveNewCallback,1000);
	if (readyForTheFixOfIt) {
		if (global_1588610_sync != 0) {
			*(int*)&global_1588610_sync->pointerToDataSyncLocation += 0x4;
			runlater::runlater(100,reset_global_1588610_sync);//100 originally
			//printf("Started!\n");
			readyForTheFixOfIt = false;
		}
	}
	encryptFunctionEnd_quick();
}

void doLobbyFakeLeaveNew() {
	encryptFunctionStart_quick(doLobbyFakeLeaveNew,100);
	assureHostOfFreemode(doLobbyFakeLeaveNewCallback);
	encryptFunctionEnd_quick();
}


//char global_2387877_buf[302*4+4];
//int global_2387877_orig = 0;
bool ready_for_giveSessionErrorToLobby = true;
__NO_INLINE void reset_giveSessionErrorToLobbyCallback(int) {
	encryptFunctionStart_quick(reset_giveSessionErrorToLobbyCallback,1000);
	ready_for_giveSessionErrorToLobby = true;
	if (global_2387877_sync != 0) {
		if (global_2387877_sync->pointerToDataSyncLocation != 0) {//gets set to 0 if it crashes or I get kicked
			*(int*)global_2387877_sync->pointerToDataSyncLocation = 0;//unset the error
			//*(int*)&global_2387877_sync->pointerToDataSyncLocation = *(int*)&global_2387877_sync->pointerToDataSyncLocation + 0x4;
			global_2387877_sync->pointerToDataSyncLocation = (int*)((int)global_2387877_sync->pointerToDataSyncLocation - 0xC);
			//*(int*)&global_2387877_sync->pointerToDataSyncLocation = global_2387877_orig;
			printDone();
		}
	}
	encryptFunctionEnd_quick();
}

__NO_INLINE void giveSessionErrorToLobbyCallback() {
	encryptFunctionStart_quick(giveSessionErrorToLobbyCallback,1000);

	if (global_2387877_sync != 0) {
		//global_2387877_orig = (int)global_2387877_sync->pointerToDataSyncLocation;
		//memcpy(global_2387877_buf,global_2387877_sync->pointerToDataSyncLocation,sizeof(global_2387877_buf));
		//global_2387877_buf[0] = 5;//crash
		//*(int*)&global_2387877_sync->pointerToDataSyncLocation = (int)global_2387877_buf;
		global_2387877_sync->pointerToDataSyncLocation = (int*)((int)global_2387877_sync->pointerToDataSyncLocation + 0xC);
		global_2387877_sync->pointerToDataSyncLocation[0] = 5;//sets the error
		//printf("Value now: %i\n",Read_Global(2387877));
		ready_for_giveSessionErrorToLobby = false;
		runlater::runlater(1000,reset_giveSessionErrorToLobbyCallback);//1000 originally
	}
	encryptFunctionEnd_quick();
}

__NO_INLINE void giveSessionErrorToLobby() {
	encryptFunctionStart_quick(giveSessionErrorToLobby,1000);
	if (ready_for_giveSessionErrorToLobby == true)
	assureHostOfFreemode(giveSessionErrorToLobbyCallback);
	encryptFunctionEnd_quick();
}


//this is used to modify the 
__NO_INLINE void playerBroadcastVariablesUpdateVariablesToOtherPlayers_detour(CGameHostBroadcastDataHandler *arg) {
	encryptFunctionStart_quick(playerBroadcastVariablesUpdateVariablesToOtherPlayers_detour,1000);
	//bool resetValue = false;
	//int origVal = 0;
	//if (queFakeLeaveOnLobby > 0) {
		/*if (arg->classData->getClassDataAddress() == 0x01929F30) {
			//CGameHostBroadcastDataHandler
			//not used yet
		}*/

	
	unsigned int Global_2387877_address = (*(int*)0x1E70394+0x1BE94);
	if ((int)arg->pointerToDataSyncLocation == Global_2387877_address/*Read_Global_Address(2387877)*/) {
		global_2387877_sync = arg;
		//printf("global_2387877: 0x%X\n",arg);
	}


	int Ptr = *(volatile int*)0x1E70388 + 0xF608;//global 1588610
		if ((int)arg->pointerToDataSyncLocation == Ptr/*Read_Global_Address(1588610)*/) {

			global_1588610_sync = arg;
			//printf("global_1588610: 0x%X\n",arg);

			//printf("In here\n");

			//printf("Val: 0x%X\n",arg);//CGameHostBroadcastDataHandler address of it

			//resetValue = true;
			//origVal = arg->sizeOfSyncData;
			//arg->sizeOfSyncData = 0x40;//0x40 causes the bug

			//queFakeLeaveOnLobby--;
		}
	//}
	//printf("Called!\n");
	call<int>(0xA1994C)(arg);
	//if (resetValue) {
	//	arg->sizeOfSyncData = origVal;
	//}
	encryptFunctionEnd_quick();
}

__NO_INLINE void setup_playerBroadcastVariablesUpdateVariablesToOtherPlayers_hook() {
	encryptFunctionStart(setup_playerBroadcastVariablesUpdateVariablesToOtherPlayers_hook);
	*(ui64*)0x1C4FAE0 = *(ui64*)((int)playerBroadcastVariablesUpdateVariablesToOtherPlayers_detour);
	encryptFunctionEnd();
}

#endif

/*
char *createLoadValueIntoR3(unsigned int value) {
	if (value > 0x7FFFFFFF)
		return 0;//won't work
	int buf[4*2];
	unsigned short P1 = value >> 16;
	unsigned short P2 = value & 0xFFFF;
	if (P2 > 0x7FFF) {
		P1 += 1;
		P2 = P2 - 0x1000;
	}
	//3C 60 7F FF 38 63 7F FF 
	buf[0] = 0x3C607FFF;//
	return (char*)buf;
}*/

#define ksjudhgijudsfrhjgijsdfjgijoksdfjgjkhjkh
#ifdef ksjudhgijudsfrhjgijsdfjgijoksdfjgjkhjkh
void msgKickPlayer(int player, bool msgRequestKickFromHostIfFalse) {
	//msgRequestKickFromHost is what it calls by default

	if (msgRequestKickFromHostIfFalse) {
		//copy MsgKickPlayer from kickFunctionForHostKick
		*(int*)0x1358FB0 = *(int*)0x1358D40;
		*(int*)0x1358FB8 = *(int*)0x1358D48;
		//from the testing, this does not triigger them to get kicked :/
	}

	/*ui64 r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, r29, r30, r31;
	r3= r4= r5= r6= r7= r8= r9= r10= r11= r12= r13= r14= r15= r16= r17= r18= r19= r20= r21= r22= r23= r24= r25= r26= r27= r28= r29= r30= r31=0;
	Stack stack(0x4F0);*/
	//done by modifying the admin kick function thing
	*(int*)0x1358EC8 = 0x480000B8;//b 0xB8
	*(int*)0x1358F80 = 0x60000000;   //0x38600000|player;//li %r3, player
	if (VALID_ADDR(getCNetGamePlayer(player))) {
		call<int>(0x1358EB8)(getCNetGamePlayer(player));
		//printf("Kicked %i\n",player);
	}
	*(int*)0x1358EC8 = 0x3C80DD24;
	*(int*)0x1358F80 = 0x4BF9DDFD;
	if (msgRequestKickFromHostIfFalse) {
		*(int*)0x1358FB0 = 0x3C600226;
		*(int*)0x1358FB8 = 0x30638B88;
	}
}

/*void kickHostNewSpecial() {
	for (int i = 0; i < 0x12; i++) {
		msgKickPlayer(i);
	}
}*/

#endif


/*
Global_2468303 this one has the best possibility for exploit

  C:\Users\Tyler\Desktop\scriptsWglobals\freemode.c (9 hits)
	Line 5956: 				iVar2[Global_2468303.imm_38[iVar3]] = 0;
	Line 242032: 				if (vmag(Global_2465243[Global_2467960[iVar0 <19>].imm_3 <97>].imm_36[Global_2468303.imm_38[iVar0] <3>]) > 0f)
	Line 242044: 						iVar3 = Global_2465243[Global_2467960[iVar0 <19>].imm_3 <97>].imm_88[Global_2468303.imm_38[iVar0]] + 2000;
	Line 242048: 						iVar3 = Global_2465243[Global_2467960[iVar0 <19>].imm_3 <97>].imm_88[Global_2468303.imm_38[iVar0]];
	Line 242050: 					unk_0xBA6C085B(Global_2464294.imm_495, create_cam_with_params("DEFAULT_SCRIPTED_CAMERA", Global_2465243[Global_2467960[iVar0 <19>].imm_3 <97>].imm_36[Global_2468303.imm_38[iVar0] <3>], Global_2465243[Global_2467960[iVar0 <19>].imm_3 <97>].imm_46[Global_2468303.imm_38[iVar0] <3>], Global_2465243[Global_2467960[iVar0 <19>].imm_3 <97>].imm_76[Global_2468303.imm_38[iVar0]], 1, 2), iVar3, 3);
	Line 242051: 					unk_0xBA6C085B(Global_2464294.imm_495, create_cam_with_params("DEFAULT_SCRIPTED_CAMERA", Global_2465243[Global_2467960[iVar0 <19>].imm_3 <97>].imm_56[Global_2468303.imm_38[iVar0] <3>], Global_2465243[Global_2467960[iVar0 <19>].imm_3 <97>].imm_66[Global_2468303.imm_38[iVar0] <3>], Global_2465243[Global_2467960[iVar0 <19>].imm_3 <97>].imm_80[Global_2468303.imm_38[iVar0]], 1, 2), iVar3, 3);
	Line 242054: 					unk_0x2B0F05CD("HAND_SHAKE", Global_2465243[Global_2467960[iVar0 <19>].imm_3 <97>].imm_84[Global_2468303.imm_38[iVar0]]);
	Line 242068: 					iVar3 = Global_2465243[Global_2467960[iVar0 <19>].imm_3 <97>].imm_88[Global_2468303.imm_38[iVar0]] + 2000;
	Line 242072: 					iVar3 = Global_2465243[Global_2467960[iVar0 <19>].imm_3 <97>].imm_88[Global_2468303.imm_38[iVar0]];





figure out event 301 so I can call this:
void func_6204(var uParam0)
{
	struct<7> Var0;
	
	if (get_event_data(1, uParam0, &Var0, 7))
	{
		if (func_451(Var0.imm_2, Var0.imm_5, Var0.imm_6, Var0.imm_1, 0, 0))
		{
			func_6205(Var0.imm_1, 0);
		}
		else
		{
			func_6205(Var0.imm_1, 1);
			Global_2387877.imm_167[Var0.imm_1 <3>] = {Var0.imm_2};
			Global_2387877.imm_222[Var0.imm_1] = Var0.imm_5;
			Global_2387877.imm_241[Var0.imm_1] = Var0.imm_6;
			Global_2387877.imm_260[Var0.imm_1] = get_network_time();
			Global_2387877.imm_279[Var0.imm_1] = 1;
		}
	}
}

*/



#ifdef kshdfjihswrfiuhweruifhweuifhweuifhuwiehfeuwihuih
void makeSyncPlayerDoOne(bool on) {

	//this is for the setup of the function

	//1587565 is the global for the kick
	if (on) {

		*(int*)0xA0034C = 0x7CBA2B78;//mr %r26, %r5 to make it player size instead of playyer size / player count

		int val = 0x39000000;
		int pid = PLAYER::PLAYER_ID();
		val = val | pid;
		*(int*)0xA003F8 = val;//make it have my player id

		*(int*)0xA00440 = 0x60000000;//stop the loop
	} else {
		*(int*)0xA0034C = 0x7F45CB96;
		*(int*)0xA003F8 = 0x63880000;
		*(int*)0xA00440 = 0x4180FF24;
	}
}

ui64 CGameScriptHandlerNetComponent__setMemorySyncPlayers_detour(ui64 r3, ui64 r4, ui64 r5) {
	int global_address = r4;
	bool reset = false;
	if (r4 == Read_Global_Address(1587565)+0x4) {
		//printf("Modifying global 0x%X\n",1587565);
		makeSyncPlayerDoOne(true);
		reset = true;
	}
	ui64 ret = call<ui64>(0xA5A674)(r3,r4,r5);
	if (reset) {
		makeSyncPlayerDoOne(false);
	}
}

void setup_CGameScriptHandlerNetComponent__setMemorySyncPlayers_hook() {
	*(ui64*)(0x1C524E0) = *(ui64*)(CGameScriptHandlerNetComponent__setMemorySyncPlayers_detour);
}
#endif

void kickLocal(int playerID) {
	uint64_t* hostUUID = (uint64_t*)(*(unsigned int*)(*(unsigned int*)(0x1CF72C4) + 0x40) + 0x1EB8);
	uint64_t realHostUUID = *hostUUID;
	*hostUUID = getCNetGamePlayer(playerID)->playerInfo->uuid;
	NETWORK::NETWORK_SESSION_KICK_PLAYER(playerID);
	*hostUUID = realHostUUID;
}

//unsigned char sub133D6ECOrig[4 * 4];
//unsigned char sub133D6ECHook[4 * 4];
uint32_t MY_sub_133D6EC_(uint32_t CNetworkObjectMgr, CNetGamePlayer *CNetGamePlayer_client, uint32_t CNetGamePlayer_self, uint32_t syncTreetype, uint32_t r7, uint32_t r8, uint32_t r9, uint32_t r10)
{
	
	uint32_t sync_pool = call<uint32_t>(0x13398D4)(CNetworkObjectMgr, syncTreetype);
	//printf("sync_pool: 0x%X\n", sync_pool);
	if (sync_pool == 0) // you usually freeze if the pool is null becuase it tries to do r3 = *(int *)(r28 +  0x8); to the pool
	{
		// next freezes here 0xA0F0A4 

		CPlayerInfo* cPlayerInfo = (CPlayerInfo * )*(unsigned int*)((unsigned int)CNetGamePlayer_client + 0x78);//apparently this is also cplayerinfo
		char* name = cPlayerInfo ? cPlayerInfo->name : (char*)"Someone";
		
		kickLocal(CNetGamePlayer_client->playerIndex);

		char buf[100];
		snprintf(buf, sizeof(buf), "%s tried to freeze you and lobby... Auto kicking them\n", name);

		print2(buf); // works but crashes after a few seconds

		//*(uint32_t *)(0x133D720) = 0x48000354; // skip to the end of the function
		return 1; // don't call anything else becuase it's invalid // I think it crashes becuase the original doesn't get called event when invalid data
	}


	/*memcpy((void*)0x133D6EC, sub133D6ECOrig, 4 * 4);
	__dcbst((void*)0x133D6EC);
	__sync();
	__isync();*/
	uint32_t ret = call<uint32_t>(0x133D6EC)(CNetworkObjectMgr, CNetGamePlayer_client, CNetGamePlayer_self, syncTreetype, r7, r8, r9, r10); // returns 0x2
	/*__dcbst((void*)0x133D6EC);
	__sync();
	__isync();
	memcpy((void*)0x133D6EC, sub133D6ECHook, 4 * 4);*/
	//printf("ret: 0x%X\n", ret);

	// *(uint32_t*)(0x133D720) = 0x38800002; // reset patch

	return ret;
}

void setupSub133D6EC_() {
	//memcpy(sub133D6ECOrig, (void*)0x133D6EC, 4 * 4);
	//PatchInJumpAddr(0x133D6EC, (int)MY_sub_133D6EC, false);
	//memcpy(sub133D6ECHook, (void*)0x133D6EC, 4 * 4);
	*(uint64_t*)0x1C707F0 = *(uint64_t*)MY_sub_133D6EC_;
}
/* 
void textMessageFreeze(int player) {
	PlayerMods::msg("~r~o<img src='img:///' height='5000' width='5000'/>\n",player);
}*/

#include "rce.h";

void forceNextHost() {
	//printf("About to kick host!\n");
	int hostIndex = PlayerMods::getHostID();
	if (hostIndex == -1) {
		print2("Invalid host found!");
		return;
	}
	if (hostIndex == PLAYER::PLAYER_ID()) {
		print2("You are already host!");
		return;
	}
	//static int value = 0;
	//printf("Kicking host %s\n",PLAYER::GET_PLAYER_NAME(hostIndex));
	//*(int*)0x1CCB170 = 0;//set this to 0 apparently helps lol 
	//*(uint32_t*)0xD25EBC = 0x3C600000 + ((((unsigned int)&value) & 0xFFFF0000) >> 16);//changes it to load r3 as 0x2542078  2005370
	//*(uint32_t*)0xD25EC4 = 0x80630000 + (((unsigned int)&value)&0xFFFF);
	//*(int*)0xD25EC4 = 0x38600000;//just li r3 0 instead

	PlayerMods::spoofMyUUIDToPlayers(hostIndex);


	//call<int>(0x12F3D50)(getCNetGamePlayer(hostIndex));

	//printf("Setup the force host\n");
	kickPlayerNonHost(hostIndex);
}

char subAE7990Orig[4 * 4];
char subAE7990Hook[4 * 4];
ui64 MY_sub_0xAE7990(ui64 r3, ui64 r4, ui64 r5, ui64 r6, char* r7, ui64 r8, ui64 r9) {
	int ret = 0;
	printf("[PARADISE] Creating Thread %s stack size 0x%X\n",r7,r5);

	memcpy((void*)0xAE7990, subAE7990Orig, 4 * 4);
	ret = call<int>(0xAE7990)(r3,r4,r5,r6,r7,r8,r9); // returns 0x2
	
	memcpy((void*)0xAE7990, subAE7990Hook, 4 * 4);

}
void createThreadHookStart() {
	//0xAE7990
	memcpy(subAE7990Orig, (void*)0xAE7990, 4 * 4);
	PatchInJump2(0xAE7990, (int)MY_sub_0xAE7990, false);
	memcpy(subAE7990Hook, (void*)0xAE7990, 4 * 4);
}

void stopNetLog_0(int zero) {
	stopNetLog();
}

void hexticForceKick(int player) {
	//startNetLog();
	if (PlayerMods::getHostID() == player) {
		print2("~r~Cannot kick host!");
		return;
	}
	if (call<int>(0x9F8268) == 0) {
		//printf("ISSUE HERE\n");
		return;
	}
	/*if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED(player)) == 0) {
		printf("WOW BAD\n");
		return;
	}*/ 
	//int unkval = call<int>(0x9F88E0)(player);//0x222EFE0 for example but i beleive this is cnet
											 //it's the same function as getCNetGamePlayer_ except it uses a different data set weeeiirddd...
	int cnet = (int)getCNetGamePlayer(player);
	if (cnet/*unkval*/ == 0) {
		//printf("INVALID CNET\n");
		return;
	}
	//printf("unk: 0x%X, cnet: 0x%X\n",unkval,cnet);
	//printf("About to kick...\n");
	//call<int>(0x12F3D50)(getCNetGamePlayer(player));//this line is probably not necessary
	call<int>(0x1340964)(*(int*)0x1CF72BC/*CNetworkPlayerMgr*/, cnet/*unkval*/);//calls 0x12F3D50 like above + some more
	//PlayerMods::msg("Kicked!", player);
	//printf("Player was kicked!\n");
	//print3("Kicked them!");
	//stopNetLog();
	//runlater::runlater(5, stopNetLog_0);
}

void forceKickAntiLoop() {
	for (int i = 0; i < 18; i++) {
		CNetGamePlayer* cnet = getCNetGamePlayer(i);
		if (VALID_ADDR(cnet)) {
			int val = *(int*)((int)cnet + 0x4 * 11 * 8 + 0x4 * 7);
			if (val == 0x01000000) {
				static char buf[100];
				snprintf(buf,sizeof(buf), "Detected possible force kick, %s\n", PLAYER::GET_PLAYER_NAME(i));
				//print2(buf);
				//hexticForceKick(i);
				//PlayerMods::msg("~r~Retaliation kick by ~b~Paradise SPRX",i);
			}
		}
	}
}

/*
//I changed it to return stored value
int createEventAndIncrement_replicate(unsigned int r3, unsigned int r4) {
	unsigned int r5;
	r5 = *(unsigned int*)r3;
	*(unsigned int*)(r4 + 0x18) = r5;
	*(unsigned int*)r3 = r4;
	r5 = *(char*)(r4 + 0x1C);
	r4 = *(unsigned int*)(r3 + 8);
	if (r5 != 0) {
		r5 = *(unsigned int*)(r3 + 0xC);
		r5 = r5 + 1;
		*(unsigned int*)(r3 + 0xC) = r5;
	}
	r4 = r4 + 1;
	*(unsigned int*)(r3 + 0x8) = r4;
	return r4;
}

void createEventAndIncrement_hook(unsigned int g_thing, unsigned int evt) {
	int eventid = createEventAndIncrement_replicate(g_thing, evt);
	char* className = getClassName(g_thing);
	printf("Event: %i 0x%X msg_%i_%s\n",eventid,g_thing,eventid,className);
}

void setup_createEventAndIncrement_hook() {
	int Address = 0xD04260;
	int Destination = (int)createEventAndIncrement_hook;
	int FuncBytes[4];													// Use this data to copy over the address.
	Destination = *(volatile int*)Destination;									// Get the actual destination address (pointer to void).
	FuncBytes[0] = (0x3D600000) + ((Destination >> 16) & 0xFFFF);			// lis %r11, dest>>16
	if (Destination & 0x8000)											// if bit 16 is 1...
		FuncBytes[0] += 1;
	FuncBytes[1] = (0x396B0000) + (Destination & 0xFFFF);					// addi %r11, %r11, dest&OxFFFF
	FuncBytes[2] = (0x7D6903A6);											// mtctr %r11
	FuncBytes[3] = (0x4E800420);											// bctr
	memcpy((void*)Address, (void*)Destination, 4 * 4);
	__dcbst((void*)Address); // Data Cache Block Store | Allows a program to copy the contents of a modified block to main memory.
	__sync(); // Synchronize | Ensure the dcbst instruction has completed.
	__isync(); // Instruction Synchronize | Refetches any instructions that might have been fetched prior to this instruction.

}*/

struct N4rage21sysMemSimpleAllocatorE {
	ClassData *classData;
};
struct N4rage12netEventBaseE {
	ClassData *classData;
	int dataA;
	int dataB;
	int C;
	int D;
	int E;
	int F;
	int G;
	int dataH;
	bool isFreeze() {
		return dataH == 3;//0x177 on valid sometimes
	}
};
	
struct N4rage13netConnection7InFrameE {//r26 in the data below
	ClassData *classData;
	int ink0;
	N4rage21sysMemSimpleAllocatorE *allocater;
	N4rage12netEventBaseE *netEventBase;
};


void networkEventHandlerForStuffLikeKick__hook(unsigned int r3, unsigned int r4, unsigned int r5) {
	//encryptFunctionStart_quick(networkEventHandlerForStuffLikeKick__hook, 1000);
	bool callit = true;
	
	
	int evtid = -1;

	int fiveVal = call<int>(*(int*)(*(int*)(*(int*)r5 + 0xC)+0x0))(r5);

	//printf("Value we got: %i\n",fiveVal);

	if (fiveVal == 5) {

		unsigned int r26 = *(unsigned int*)(r5 + 0x28);//r26 is N4rage13netConnection7InFrameE which is also r5 sooo idk
		int val = call<int>(0x16276C4)(&evtid, *(unsigned int*)(r26 + 0x48), *(unsigned int*)(r26 + 0x44));
		
		if (val != 0) { 
			int someWeirdID = 0;//*(int*)(r26 + 0x4 * 13);//0xE0 or 0x67 normally on job invite, but it is 0 for the freeze
			N4rage13netConnection7InFrameE *connFrame = (N4rage13netConnection7InFrameE*)r26;

			char *freezeval_ptr = (char*)(*(int*)(r26 + 0x48));
			//int val1 = *(int*)(ptr + 0x0);
			//int val2 = *(int*)(ptr + 0x4);

			char freezeval_arr[] = { 0xC9, 0x18, 0x35, 0x90, 0xEA, 0xAA, 0xFA };

			if (evtid != 3 && evtid != 0x20 && evtid != 0x3E && evtid != 0x37 && evtid != 0x3D) {//this is a bug but actually keep this for confusion
				//printf("Event 0x%X\n", evtid);
				// && connFrame->netEventBase->isFreeze()
				//                         0xC9183590            0xEAAAFA02
				//bool freezeVal = val1 == 0xC9183590 && val2 == 0xEAAAFA00;
				

				//if (freezeVal)printf("Detected the freeze with the freeze values\n");

				if (evtid == 0x1A) {//sig for freeze, got other values for the other methods
					//printf("Got event 1A\n");
					//printf("r26: 0x%X\n",r26);
					//printf("r3, r4, r5, r26, val: 0x%X 0x%X 0x%X 0x%X 0x%X\n", *(unsigned int*)0x1CF72C4, r4, r5, r26, val);
					//__asm("trap");
					//print2("Anti freeze!");


					bool freezeVal = true;
					for (int i = 0; i < sizeof(freezeval_arr); i++) {
						if (freezeval_ptr[i] != freezeval_arr[i])
							freezeVal = false;//they are not equal, so no freeze detected
					}

					if (freezeVal) {//tge sigs match for the broken freeze
						callit = false;//actually... need some sort of check and idk what values to check lol
					}
				}
				if (evtid == 0xD/**(int*)0x2259578*/) {
					//MsgKickPlayer

					if (!IS_LOADED_INTO_LOBBY) {//only do it if you are in the lobby, otherwise you were kicked while in a transition

					}
					else {

						char buf[300];
						snprintf(buf, sizeof(buf), "You were kicked by the host %s %s\n", PlayerMods::getHost(), PlayerMods::getIp(0, PlayerMods::getHost()));
						print2(buf, 60000);

						callit = false;
					}
				}
				if (evtid == 0x9/**(int*)0x2259558*/) {
					//MsgBlacklist

					//printf("You were blacklisted by the host!");

					callit = false;
				}
			}
		}
	}

	if (callit)
		call<unsigned int>(0x138E0C8)(*(unsigned int*)0x1CF72C4, r4, r5);
	//else
	//	printf("NOT CALLED\n");
	//encryptFunctionEnd_quick();
}

void setup_networkEventHandlerForStuffLikeKick__hook() {
	//printf("Setting up hook!\n");
	PatchInJump2(0x138F9DC, (int)networkEventHandlerForStuffLikeKick__hook, false);
}

/*bool disable_0x138F9DC = false;
bool disable_0xD1511C = false;
bool disable_0xA15C24 = false;
bool disable_0xD1EE1C = false;*/
bool disable_all_events = false;

__NO_INLINE bool eventFunction_special(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int eventAddress) {

	bool callit = true;

	//if (eventAddress != 0xA15C24 && eventAddress != 0xD1511C && eventAddress != 0x138F9DC)
		//printf("Call: 0x%X ( 0x%X , 0x%X , 0x%X );\n", eventAddress, r3, r4, r5);

	/*if (eventAddress == 0xA15C24) {//handlePlayerMovementReceive_nonPhysicalDataMsg 
		//if you nop this then people can't punch you
	}*/

	/*
	Call: 0x138F9DC( 0x40034F00, 0x223F0D0 , 0x40005630 );  networkEventHandlerForStuffLikeKick_
	Call: 0xD1511C ( 0x20055F0 , 0x223F0D0 , 0x40005630 );//unknown
	Call: 0xD1511C ( 0x222D9C0 , 0x223F0D0 , 0x40005630 );//0x222D9C0 = 17CNetworkPlayerMgr.
	Call: 0xA15C24 ( 0x222D970 , 0x223F0D0 , 0x40005630 ); //handlePlayerMovementReceive_nonPhysicalDataMsg   this one definitely contains the punch info
	Call: 0xD1EE1C ( 0x222D8D8 , 0x223F0D0 , 0x40005630 ); //0x222D8D8 = N4rage11netTimeSyncE
	costantly called
	*/

	/*if (disable_0x138F9DC && (eventAddress == 0x138F9DC))
		return false;
	if (disable_0xD1511C && (eventAddress == 0xD1511C))
		return false;
	if (disable_0xA15C24 && (eventAddress == 0xA15C24))
		return false;
	if (disable_0xD1EE1C && (eventAddress == 0xD1EE1C))//netTimeSyncMsg_func
		return false; */
	if (disable_all_events/* && eventAddress == 0xA15C24*/)
		return false; 
	  
	return callit; 
}

__NO_INLINE unsigned int eventFunction_special_Hook(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int eventAddress) {
	//need to move r27 into r4 and r28 into r5 and r3 is normal, call on eventAddress
	/*unsigned int r4 = getR27();
	unsigned int r5 = getR28();
	unsigned int eventAddress = eventAddress_;
	unsigned int r3 = r3_;*/
	 
	/*
Call: 0x138F9DC ( 0x40034F00 , 0x223F0D0 , 0x40005360 );   //not this one
Call: 0xD1511C  ( 0x20055F0  , 0x223F0D0 , 0x40005360 );
Call: 0xD1511C  ( 0x222D9C0  , 0x223F0D0 , 0x40005360 );
Call: 0xA15C24  ( 0x222D970  , 0x223F0D0 , 0x40005360 );
Call: 0xD1EE1C  ( 0x222D8D8  , 0x223F0D0 , 0x40005360 );
	*/



	if (eventFunction_special(r3,r4,r5,eventAddress))
		return call<unsigned int>(eventAddress)(r3,r4,r5);
	return 0;
}

__NAKED unsigned int eventFunction_special_Hook_nakey(unsigned int r3, unsigned int r4, unsigned int r5, unsigned int eventAddress) {
	__asm__("mr %r4, %r27");
	__asm__("mr %r5, %r28");
	//__asm__("b ._Z21eventFunction_specialjjjj");
	__asm__("b ._Z26eventFunction_special_Hookjjjj");
}


__NO_INLINE void eventFunction_special_Hook_setup() {
	encryptFunctionStart(eventFunction_special_Hook_setup);
	PatchInJump2(0xD1412C, (int)eventFunction_special_Hook_nakey, true);//linked is true
	encryptFunctionEnd();
}


/*
char getAndStoreEventIdIntoR3_hook_orig[4 * 4];
char getAndStoreEventIdIntoR3_hook_patch[4 * 4];

int getAndStoreEventIdIntoR3_hook(int *eventID, unsigned int r4, unsigned int r5) {
	write_process((void*)0x16276C4, getAndStoreEventIdIntoR3_hook_orig, 4 * 4);
	sync_mem(0x16276C4);
	int val = call<int>(0x16276C4)(eventID,r4,r5);
	if (val != 0) {
		printf("Event received: 0x%X\n",*eventID);
		if (*eventID == 0x1A) {
			val = 0;
		}
	}
	write_process((void*)0x16276C4, getAndStoreEventIdIntoR3_hook_patch, 4 * 4);
	sync_mem(0x16276C4);
	return val;
}

void setup_getAndStoreEventIdIntoR3_hook() {
	write_process(getAndStoreEventIdIntoR3_hook_orig, (void*)0x16276C4, 4 * 4);
	PatchInJump2(0x16276C4, (int)getAndStoreEventIdIntoR3_hook, false);
	write_process(getAndStoreEventIdIntoR3_hook_patch, (void*)0x16276C4, 4 * 4);
}*/


namespace blackHole {
	class BlackHole {
	public:
		float x, y, z;
		float radius;

		BlackHole(float x, float y, float z, float radius) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->radius = radius;
		}

		void render() {

		}
	};
}





LineReader statFileReader = LineReader();
void runStatFile(char *file, void(*func)(int type, int stat, int value)) {
	//file format:
	//type:stat:value\n
	if (!doesFileExist(file)) {
		print2("File does not exist!");
		return;
	}
	statFileReader.init(file);
	char buf[100];
	int lineCount = 1;
	while (statFileReader.hasNextLine()) {
		for (int i = 0; i < sizeof(buf); i++)
			buf[i] = 0;
		statFileReader.nextLine(buf, sizeof(buf));
		
		char *statStr = strstr(buf, ":");//first spot
		if (statStr > 0) {
			statStr[0] = 0;
			statStr = statStr + 1;
			char* valueStr = strstr(statStr, ":");//first spot
			if (valueStr > 0) {
				valueStr[0] = 0;
				valueStr = valueStr + 1;
				int type = StoI(buf);
				int value = StoI(valueStr);
				int hash = GAMEPLAY::GET_HASH_KEY(statStr);
				printf("%i %s %i\n",type,statStr,value);
				func(type, hash, value);
			}
			else {
				snprintf(buf, sizeof(buf), "Error on line %i, second delimeter (:) not found... continuing to next line. format: type:stat:value", lineCount);
				print2(buf, 10000);
			}
		}
		else {
			snprintf(buf,sizeof(buf),"Error on line %i, first delimeter (:) not found... continuing to next line. format: type:stat:value", lineCount);
			print2(buf, 10000);
		}
		lineCount++;
	}
	statFileReader.close();
}




LineReader nativeFileReader = LineReader();
void runNativeFile(char* file, int(*callNative)(unsigned int native, int r3, int r4, int r5, int r6, int r7, int r8, int r9)) {
	//file format:
	//type:stat:value\n
	if (!doesFileExist(file)) {
		print2("File does not exist!");
		return;
	}
	nativeFileReader.init(file);
	char buf[100];
	int lineCount = 1;
	while (nativeFileReader.hasNextLine()) {
		for (int i = 0; i < sizeof(buf); i++)
			buf[i] = 0;
		nativeFileReader.nextLine(buf, sizeof(buf));

		char* statStr = strstr(buf, ":");//first spot
		if (statStr > 0) {
			statStr[0] = 0;
			statStr = statStr + 1;
			char* valueStr = strstr(statStr, ":");//first spot
			if (valueStr > 0) {
				valueStr[0] = 0;
				valueStr = valueStr + 1;
				int type = StoI(buf);
				int value = StoI(valueStr);
				int hash = GAMEPLAY::GET_HASH_KEY(statStr);
				printf("%i %s %i\n", type, statStr, value);
				//func(type, hash, value);
			}
			else {
				snprintf(buf, sizeof(buf), "Error on line %i, second delimeter (:) not found... continuing to next line. format: type:stat:value", lineCount);
				print2(buf, 10000);
			}
		}
		else {
			snprintf(buf, sizeof(buf), "Error on line %i, first delimeter (:) not found... continuing to next line. format: type:stat:value", lineCount);
			print2(buf, 10000);
		}
		lineCount++;
	}
	nativeFileReader.close();
}



void hookFunctionStart2(int Address, int saveStub, int Destination) { //Works on every game

	saveStub = *(int*)saveStub;

	int BranchtoAddress = Address + (4 * 4);

	int StubData[8];

	StubData[0] = 0x3D600000 + ((BranchtoAddress >> 16) & 0xFFFF);

	if (BranchtoAddress & 0x8000) StubData[0] += 1;

	StubData[1] = 0x396B0000 + (BranchtoAddress & 0xFFFF);

	StubData[2] = 0x7D6903A6;

	write_process_sc(&StubData[3], (void*)Address, 4 * 4);

	StubData[7] = 0x4E800420;

	write_process_sc((void*)saveStub, StubData, 8 * 4);

	PatchInJump2(Address, Destination, false);

}

void VM_ResumeStub(unsigned int r3, unsigned int r4, unsigned int r5) {

	__asm("li %r3, 0x3");
	__asm("li %r3, 0x3");
	__asm("li %r3, 0x3");
	__asm("li %r3, 0x3");
	__asm("li %r3, 0x3");
	__asm("li %r3, 0x3");
	__asm("li %r3, 0x3");
	__asm("li %r3, 0x3");

}

int patchValCamber[] = { 0x3F800000, 0x00000000, 0x80000000 };
int patchValCamberBackup[] = { 0,0,0 };
int myvehiceladdr = 0;
bool doTheThing = false;
void VM_ResumeHook(unsigned int r3, unsigned int r4, unsigned int r5) { // If this doesn't work, hook int VM_Execute() - 0x2E6444 with hookFunctionStart
	printf("Camber hook\n");

	if (VALID_ADDR(myvehiceladdr)) {
		printf("0x%X 0x%X\n", *(int*)(myvehiceladdr + 0xCA0) + 0x0, r3);
	}

	doTheThing = false;
	if (VALID_ADDR(myvehiceladdr)) {
		if (r3 == *(int*)(myvehiceladdr + 0xCA0) + 0x0) {
			doTheThing = true;
			printf("Doing Patch\n");
		}
	}

	if (doTheThing) {
		for (int i = 0; i < 3; i++)
			patchValCamberBackup[i] = *(int*)(r3 + i * 4);

		for (int i = 0; i < 3; i++)
			*(int*)(r3 + i * 4) = patchValCamber[i];
	}

	 //You would call GScr_Earthquake here. Obv not in the loop. Make sure you implement a check in here to make it //   get called once

	VM_ResumeStub(r3,r4,r5);

	printf("Called here\n");
	if (doTheThing) {
		for (int i = 0; i < 3; i++)
			*(int*)(r3 + i * 4) = patchValCamberBackup[i];
	}
}

void setup_sub_E45240_hook() {
	//fix camber
	printf("Setup hook\n");
	hookFunctionStart2(0xE45240, (int)VM_ResumeStub, (int)VM_ResumeHook);
	printf("Hook setup");
}



char camberHook_backup[4 * 4];
char camberHook_patch[4 * 4];

void camberHook(unsigned int r3, unsigned int r4, unsigned int r5) {
	printf("Opere herere\n");
	if (VALID_ADDR(myvehiceladdr)) {
		printf("0x%X 0x%X\n", *(int*)(myvehiceladdr + 0xCA0) + 0x0, r3);
	}

	printf("Camber hook aa\n");
	for (int i = 0; i < 3; i++)
		patchValCamberBackup[i] = *(int*)(r3 + i * 4);

	for (int i = 0; i < 3; i++)
		*(int*)(r3 + i * 4) = patchValCamber[i];
	
	//You would call GScr_Earthquake here. Obv not in the loop. Make sure you implement a check in here to make it //   get called once
	write_process_sc((void*)0xE45240, camberHook_backup, 4 * 4);
	printf("bb\n");
	call<int>(0xE45240)(r3, r4, r5);
	printf("bc\n");
	write_process_sc((void*)0xE45240, camberHook_patch, 4 * 4);


	printf("Called here aa\n");
	for (int i = 0; i < 3; i++)
		*(int*)(r3 + i * 4) = patchValCamberBackup[i];
}
void setup_camberHook() {
	memcpy(camberHook_backup,(void*) 0xE45240,4*4);
	PatchInJump2(0xE45240,(int)camberHook,false);
	memcpy(camberHook_patch, (void*)0xE45240, 4 * 4);
}


void sub_13D4B2C_hook(unsigned int r3, unsigned int r4) {
	//printf("Scorpion Hooked Function\n");
	bool callit = true;
	unsigned int val = *(unsigned int*)(r4 + 0xF4);
	val = *(unsigned int*)(val + 0x1C);
	if (val == 0) {
		val = *(unsigned int*)(r4 + 0xF4);
		val = *(unsigned int*)(r4 + 0x30);
		if (!VALID_ADDR(val + 0xC)) {
			print3("Scorpion Freeze Detected!");
			printf("[debug] Scoripion Freeze Detected!\n");
			callit = false;
		}
	}
	if (callit)
		call<int>(0x13D4B2C)(r3, r4);
}

void setup_sub_13D4B2C_hook() {
	//*(uint64_t*)(0x1C73168) = *(uint64_t*)((int)sub_13D4B2C_hook);
	//*(int*)(0xA892FC) = 0x60000000;//this will always freeze if it is branched here which is stupid so nop it
	//freezing in sub_A892D4
}


uint32_t MY_sub_133D6EC(uint32_t cNetworkObjectMgr, uint32_t CNetGamePlayer_client, uint32_t CNetGamePlayer_self, uint32_t syncTreetype, uint32_t r7, uint32_t r8, uint32_t r9, uint32_t r10)
{
	// **IMPORTANT** this can still freeze you if they do it while you're in the clouds joining thier session

	//uint32_t sync_pool = GetSyncPool(cNetworkObjectMgr, syncTreetype);
	uint32_t sync_pool = call<uint32_t>(0x13398D4)(cNetworkObjectMgr, syncTreetype);
	if (sync_pool == 0) // you freeze if the pool is null becuase it tries to do r3 = *(int *)(r28 +  0x8); to the pool
	{
		if (CNetGamePlayer_client)
		{
			uint32_t playerInfo = *(volatile uint32_t*)(CNetGamePlayer_client + 0x78);
			char* name = 0;
			if (VALID_ADDR(playerInfo)) {
				name = (char*)(playerInfo + 0x10);
			}
			else {
				name = "Someone";
			}
			uint8_t player = *(volatile uint8_t*)(CNetGamePlayer_client + 0x29);

			static char buf[100];
			

			snprintf(buf,sizeof(buf),"%s (%i) tried to freeze you! They have been kicked.", name, player);

			print3(buf);
			 
			hexticForceKick(player);
			PlayerMods::kickPlayerLocally(player);
			//hexticForceKick(player);

			// after this is patched it will freeze somewhere else
			// next freezes here 0xA0F0A4 
		}
		 
		// don't call anything else becuase it's invalid
		return 6;

		// return 1 player no loger in roaming bubble 
		// return 6 Can't apply data - no game object
		// return 6 Can't apply data
		// return 2 Object is being reassigned
		// return 2 Wrong owner
	}

	return call<int>(0x133D6EC)(cNetworkObjectMgr, CNetGamePlayer_client, CNetGamePlayer_self, syncTreetype, r7, r8, r9, r10);
}

void setupSub133D6EC() {
	*(uint64_t*)0x1C707F0 = *(uint64_t*)MY_sub_133D6EC;
}






































int Type = 0;
char* PendingGsInfoRequestID = "";
bool PendingGsInfoRequest = false;
uint32_t PendingTimeout = 0;
bool hasFoundgsInfo = false;

int func_r7 = 0;
int func_r8 = 0;
int func_r9 = 0;
int func_r10 = 1;


bool IsMallocSafe(void* ptr)
{
	if (!ptr)
	{
		return false;
	}

	return true;
}
void WriteString(int address, char* value) { strncpy((char*)address, value, strlen(value)); *(char*)(address + strlen(value)) = 0; }
uint32_t makeNPIDManual(char* name) // it needs to be free after its used
{
	//this should be correct...

	//this is r3 of 0x1355E00

	//example data: 00000002 00000000 46345261 42695373 2D5F2D2D 582D7800 00000000 00000000 00000000 00000000 00000000 02000000


	size_t size = 60;
	static char buf[60];
	uint32_t free_memory = (uint32_t)&buf;
	if (IsMallocSafe((void*)free_memory))
	{
		memset((void*)free_memory, 0, size);
		*(uint32_t*)(free_memory) = 0x00000002;  // 0x01000000
		WriteString(free_memory + 0x8, name);
		*(uint32_t*)(free_memory + 0x2C) = 0x02000000; // 0x00000001
		return free_memory;
	}
	return 0;
}

 

struct GsSession
{
	uint64_t m_peerToken;
	uint32_t m_npid;
	char data[0x100];
};



__NO_INLINE void JoinPlayerViaSessionInfoFunc(uint32_t player_array, int playerCount, GsSession* peer_token, void* jobInfo, uint32_t r7, uint32_t r8, uint32_t r9, uint32_t r10) {
	encryptFunctionStart((void*)JoinPlayerViaSessionInfoFunc);
	//int JoinPlayerViaSessionInfoOpd[2] = { 0x1355E00, TOC };
	//typedef void(*JoinPlayerViaSessionInfoFn)(uint32_t player_array, int playerCount, GsSession* peer_token, void* jobInfo, uint32_t r7, uint32_t r8, uint32_t r9, uint32_t r10);
	//JoinPlayerViaSessionInfoFn JoinPlayerViaSessionInfoFunc_ = (JoinPlayerViaSessionInfoFn)JoinPlayerViaSessionInfoOpd;
	call<int>(0x1355E00)(player_array,playerCount,peer_token,jobInfo,r7,r8,r9,r10);
	encryptFunctionEnd();
}



__NO_INLINE bool GetSessionInfoFromGs(GsSession* info, const char* gs, int Unk_zero) {
	encryptFunctionStart((void*)GetSessionInfoFromGs);
	//int GetSessionInfoFromGsOpd[2] = { 0xD3D7BC, TOC };
	//typedef bool(*GetSessionInfoFromGsFn)(GsSession* info, const char* gs, int Unk_zero);
	//GetSessionInfoFromGsFn GetSessionInfoFromGs_ = (GetSessionInfoFromGsFn)GetSessionInfoFromGsOpd;
	bool val = call<bool>(0xD3D7BC)(info, gs, Unk_zero);
	encryptFunctionEnd();
	return val; 
} 


__NO_INLINE void SendSessionInfoRequest(uint32_t npId, uint32_t count) {
	encryptFunctionStart((void*)SendSessionInfoRequest);
	//int SendSessionInfoRequestOpd[2] = { 0x1308CBC, TOC };//this triggers a N4rage19rlGetGamerStateTaskE
	//typedef void(*SendSessionInfoRequestFn)(uint32_t npId, uint32_t count);
	//SendSessionInfoRequestFn SendSessionInfoRequest_ = (SendSessionInfoRequestFn)SendSessionInfoRequestOpd;
	call<int>(0x1308CBC)(npId,count);
	encryptFunctionEnd();
} 


uint32_t RlGameInfoItem(char* itemName, uint32_t itemsStart, uint32_t len)
{
	
	//int hasFound;
	uint32_t i = 0;
	if (0 < len)
	{
		i = 0;
		do
		{
			//printf("Right here buddyooo");
			bool hasFound = strstr(itemName, (char*)itemsStart) != 0; // crashes if you use strcasecmp from SDK
			bool hasFound2 = strstr((char*)itemsStart, itemName) != 0;
			//printf("Zooo wee mama!\n");
			if (hasFound || hasFound2)
			{
				return i;
			}

			i = i + 1;
			itemsStart = itemsStart + 200; // next item
		} while (i < len);
	}

	return -1;
}

__NO_INLINE char* GetRlGameInfoString(char* itemName) // this functions is inlined on ps3
{
	char* retVal = NULL;
	encryptFunctionStart((void*)GetRlGameInfoString);
	uint32_t RlGameInfoPtr = 0x205C9B0;
	uint32_t itemsStart = RlGameInfoPtr + 0x20;
	uint32_t itemCount = *(uint32_t*)(RlGameInfoPtr + 0x14);
	const int item_size = 200; // 0xC8
	//printf("Here a!\n");
	uint32_t foundAt = RlGameInfoItem(itemName, itemsStart, itemCount);
	//printf("Here b!\n");
	if (foundAt != -1)
	{
		retVal = (char*)((itemsStart + (foundAt * item_size)) + 0x40);
	}
	encryptFunctionEnd();
	return retVal;
}


char* GsInfo = 0;


char* gsinfoReturnValue = (char*)0x10045000;



// Call this to start joining them, this is the only thing you need to call to join them

/*
void JoinPlayer(char* psn)
{

	gsinfoReturnValue[0] = 0;//nullify the string

	//printf("JoinPlayer\n");
	GsInfo = NULL;

	Type = 2;
	PendingGsInfoRequestID = psn;
	PendingGsInfoRequest = true;
	PendingTimeout = time(0) + 10;

	//uint32_t npid = makeNPID Manual(psn);//I think this npid is incorrect
	//if (IsMallocSafe((void*)npid))
	//{
		// call into get info
		NETWORK::_0x3F7EDBBD(); // 0x86E0660E4F5C956D 0x3F7EDBBD

		//printf("SendSessionInfoRequest\n");
		//SendSessionInfoRequest(npid, 1);//N4rage19rlGetGamerStateTaskE

		int networkStruct[13];

		NETWORK::NETWORK_HANDLE_FROM_USER_ID(psn, networkStruct, 13);
		//NETWORK::NETWORK_HANDLE_FROM_MEMBER_ID(psn, networkStruct, 13);//seems to work identically to the one above

		NETWORK::_0x42BD0780(networkStruct);//tell it to use this player
		NETWORK::_0xBEB98840();//execute it, same as SendSessionInfoRequest basically

		//printf("Successfully sent request to join %s\n", PendingGsInfoRequestID);
		//free((void*)npid);
	//}
}*/






void HandleJoinMe();
int lastUsedJoinTime = 0;
// Makes our player join them by getting their session info first
void JoinMe(char* psn)
{
	bool isFriend = false;
	int friendCount = NETWORK::NETWORK_GET_FRIEND_COUNT();
	for (int i = 0; i < friendCount; i++) {
		char* name = NETWORK::NETWORK_GET_FRIEND_NAME(i);
		if (strstr(name, psn)) {
			isFriend = true;
		}
	}


#ifdef doWaitTineForceJoin
	if (isFriend == false) {
		//do check for randoms
		int curTime = time(0);
		if (curTime > lastUsedJoinTime) {
			//okay to go
			lastUsedJoinTime = curTime + 60 * 10;
		}
		else {
			//not okay to go
			int waitTime = lastUsedJoinTime - curTime;
			 
			int minutes = waitTime / 60;
			int seconds = waitTime - (minutes * 60);

			uint64_t waitmsg_[7]; waitmsg_[0] = 0x7E727E506C656173; waitmsg_[1] = 0x6520776169742025; waitmsg_[2] = 0x69206D696E757465; waitmsg_[3] = 0x7320256920736563; waitmsg_[4] = 0x6F6E647320626566; waitmsg_[5] = 0x6F72652075736521; waitmsg_[6] = 0x0000000000000000;//~r~Please wait %i minutes %i seconds before use!
			char* waitmsg = (char*)waitmsg_;


			snprintf(global_temporary_buf, sizeof(global_temporary_buf), waitmsg, minutes,seconds);
			print2(global_temporary_buf);
			return;
		}
	}
#endif

	gsinfoReturnValue[0] = 0;//nullify the string

	//printf("JoinMe\n");
	GsInfo = NULL;
	Type = 1;
	PendingGsInfoRequestID = psn;
	//PendingGsInfoRequest = true;
	//PendingTimeout = time(0) + 10;

	//printf("Attempting to force %s into your session...\n", psn);




	//printf("MAKING THEM JOIN YOU!\n");
	HandleJoinMe();
	//PendingGsInfoRequest = false;


}


// These get called from the looped code below



JsonArg *JsonToJsonArg(char* json, int maxSize) {
	static JsonArg arg;
	arg.jsonString = json;
	arg.jsonStringBufferSize = maxSize;
	arg.unk1 = -1;
	arg.unk2 = -1;
	arg.unk3 = 0;
	arg.jsonStringLength = strlen(json);
	//printf("Created json string arg\n");
	return &arg; 
}

int getStringArg(JsonArg* str, char* find, char* dst, int length) {
	return call<int>(0xA91D04)(str, find, dst, length);
}

char *tmpBufferaaaa = (char*)(0x10045000 + 0x304);

char* extractGsInfo(char* gsInfo, char *buf = tmpBufferaaaa) {
	uint64_t gsinfo_[1]; gsinfo_[0] = 0x6773696E666F0000;//gsinfo
	char* gsinfo = (char*)gsinfo_;
	getStringArg(JsonToJsonArg(gsInfo, 0x100), gsinfo, buf, 0x300);
	return buf;
}

char* extract_id(char* gsInfo, char *buf = tmpBufferaaaa) {
	//printf("Extracting ID\n");
	int _id_[1]; _id_[0] = 0x5F696400;//_id
	char* _id = (char*)_id_;

	getStringArg(JsonToJsonArg(gsInfo, 0x100), _id, buf, 0x300);
	//printf("Got the string arg\n");
	return buf;
}

/*void HandleJoinPlayer()
{


	//END OF ME JOINING THEM

	//printf("HandleJoinPlayer %s\n", PendingGsInfoRequestID);
	PendingGsInfoRequest = false;

	GsSession SessionInfo;
	memset(&SessionInfo, 0, sizeof(SessionInfo));
	//printf("GetSessionInfoFromGs: %s\n", GsInfo);
	GetSessionInfoFromGs(&SessionInfo, GsInfo, 0);
	//printf("SessionInfo 0x%X 0x%X\n", SessionInfo, &SessionInfo);//&SessionInfo is 0 for some reason...
	//printf("m_peerToken 0x%016llX\n", SessionInfo.m_peerToken);
	//printf("m_npid 0x%X\n", SessionInfo.m_npid); 

	if (SessionInfo.m_peerToken == 0) {
		print2("~r~Player is not in an online session!");
		return;
	}

	uint32_t npid = makeNPIDManual((char*)getMyPSNName());//(char*)getMyPSNName()    when this was set as their psn name it froze me
	if (IsMallocSafe((void*)npid))
	{
		//printf("JoinPlayerViaSessionInfoFunc\n");
		int job[10] = { 0 };
		memset(job, 0, sizeof(job));
		JoinPlayerViaSessionInfoFunc(npid, 1, &SessionInfo, (void*)job, func_r7, func_r8, func_r9, func_r10);
		//printf("Joining %s...\n", PendingGsInfoRequestID);
		//free((void*)npid);
		print2("~g~Joining them!");
	}
}*/

bool doSpoofNameForJoinFix = false;
char doSpoofNameForJoinFixName[20];
 
void timeoutHandleJoinPlayerWithGSInfoName(int a) {
	doSpoofNameForJoinFix = false;
}

void HandleJoinPlayerWithGSInfo(char* foundgsinfo, char *psn = "") {

	doSpoofNameForJoinFix = true;
	strncpy(doSpoofNameForJoinFixName, psn, 20);
	runlater_time::runlater(60, timeoutHandleJoinPlayerWithGSInfoName);//tell it to use spoofed data for a minute

	GsSession SessionInfo;
	memset(&SessionInfo, 0, sizeof(SessionInfo));
	GetSessionInfoFromGs(&SessionInfo, foundgsinfo, 0);
	if (SessionInfo.m_peerToken == 0) {
		//print2("~r~Player is not in an online session!");
		return;
	}

	uint32_t npid = makeNPIDManual((char*)getMyPSNName());
	if (IsMallocSafe((void*)npid))
	{
		int job[10] = { 0 };
		memset(job, 0, sizeof(job));
		JoinPlayerViaSessionInfoFunc(npid, 1, &SessionInfo, (void*)job, func_r7, func_r8, func_r9, func_r10);
		//print2("~g~Joining them!");
	}
}

__NO_INLINE void HandleJoinMe()//this works fine now
{ 
	encryptFunctionStart((void*)HandleJoinMe);

	//FORCE PLAYER TO JOIN ME PART 2 END

	//printf("HandleJoinMe\n"); 
	if (NETWORK::NETWORK_IS_SESSION_ACTIVE()) {

		PendingGsInfoRequest = false;

		GsSession SessionInfo;
		memset(&SessionInfo, 0, sizeof(SessionInfo));

		uint64_t gsinfo_[1]; gsinfo_[0] = 0x6773696E666F0000;//gsinfo
		char* gsinfo = (char*)gsinfo_;


		char* gsInfoString = GetRlGameInfoString(gsinfo);
		//printf("GetSessionInfoFromGs: %s\n", gsInfoString);
		GetSessionInfoFromGs(&SessionInfo, gsInfoString, 0);
		//printf("SessionInfo 0x%X 0x%X\n", SessionInfo, &SessionInfo);
		//printf("m_peerToken 0x%016llX\n", SessionInfo.m_peerToken);
		//printf("m_npid 0x%X\n", SessionInfo.m_npid); 


		if (SessionInfo.m_peerToken != 0) {
			//print2("~r~Player is not in an online session!");
			//return;
		//}


			uint32_t npid = makeNPIDManual(PendingGsInfoRequestID);//(char*)getMyPSNName()
			if (IsMallocSafe((void*)npid))
			{
				//printf("JoinPlayerViaSessionInfoFunc\n");
				int job[10] = { 0 };
				memset(job, 0, sizeof(job));
				JoinPlayerViaSessionInfoFunc(npid, 1, &SessionInfo, job, func_r7, func_r8, func_r9, func_r10);//r7=0,r8=0,r9=0,r10=1, must be in lobby able to join
				//printf("Successfully sent request to force %s into your session!\n", PendingGsInfoRequestID);
				//print2("~g~Sent Request To Force Them To Join You!");
				//free((void*)npid);
			}
		}
	}
	encryptFunctionEnd();
}






/*
void PendingJoinRequestLoop()
{
	if (PendingGsInfoRequest)
	{
			if (PendingTimeout < time(0)) 
			{
				PendingGsInfoRequest = false;
				print2("Failed to resolve players session, they may be offline\n");
				hasFoundgsInfo = false;
				return;
			}
			if (hasFoundgsInfo) {
				if (Type == 2)
				{
					//if (gsinfoReturnValue != NULL)
					//{
					//char* foundName = PendingGsInfoRequest;//need to extract the _id from this

					if (strstr(gsinfoReturnValue, PendingGsInfoRequestID) != 0) {//player name found inside of gsinfo string

						//printf("%s found inside %s\n", PendingGsInfoRequestID, gsinfoReturnValue);

						//char* id = extract_id(gsinfoReturnValue);
						//printf("id found: %s\n", id);

						GsInfo = extractGsInfo(gsinfoReturnValue);
						//printf("GsInfo found: %s\n", GsInfo);

						//HandleJoinPlayer();
						HandleJoinPlayerWithGSInfo(GsInfo);

						PendingGsInfoRequest = false;
						hasFoundgsInfo = false;
					}
					else {
						//printf("Player id mis match!\n");
						PendingGsInfoRequest = false;
						hasFoundgsInfo = false;
					}
					//	}
				}
				else
				{

					PendingGsInfoRequest = false;
					hasFoundgsInfo = false;

					//nothing...
				}
			}
	}
}
*/






//eturn ReadSessionInfoResponse1Original(r3);
//}

void updateMetPlayerStatus(char *json);

bool MY_ReadSessionInfoResponse1(int N4rage26rlSessionByGamerHandleTaskE)//0xD5B3E4
{
	/*bool Return = true;

	if (r3 && *(uint32_t*)(r3 + 0x14E4))
	{
		const char* ResponseData = *(const char**)(r3 + 0x1490);
		if (ResponseData)
		{
			printf("ResponseData1: %s\n", ResponseData);


		}
	}*/
	if (N4rage26rlSessionByGamerHandleTaskE) {
		strncpy(gsinfoReturnValue, (char*)(N4rage26rlSessionByGamerHandleTaskE+ 0x44C/*0x90 for 0x132A2BC other thing*/), 0x300);

		//printf(gsinfoReturnValue);
		if (PendingGsInfoRequest) {
			hasFoundgsInfo = true;
		}


		updateMetPlayerStatus(gsinfoReturnValue);

		//now check met players


		//printf("\n");
	}
}

//name: privk_132AE30 , real: 0x132AE30 , server: getNextData(addrstruct().privk_132AE30); , conversion: (addrstruct().privk_132AE30^dataDecryptor()^0x1C82DE14)/*value: 0x132AE30*/ , val on server: 0x1DB07024

char hook_0x132AE30_orig[4 * 4];
char hook_0x132AE30_patch[4 * 4];
void hook_0x132AE30(int r3) {
	MY_ReadSessionInfoResponse1(r3);
	memcpy((void*)(addrstruct().privk_132AE30 ^ dataDecryptor() ^ 0x1C82DE14)/*value: 0x132AE30*/, hook_0x132AE30_orig, 4 * 4);
	call<int>((addrstruct().privk_132AE30 ^ dataDecryptor() ^ 0x1C82DE14)/*value: 0x132AE30*/)(r3);
	memcpy((void*)(addrstruct().privk_132AE30 ^ dataDecryptor() ^ 0x1C82DE14)/*value: 0x132AE30*/, hook_0x132AE30_patch, 4 * 4);
}


/*
char hook_0x132A2BC_orig[4 * 4];
char hook_0x132A2BC_patch[4 * 4];
void hook_0x132A2BC(int r3) {
	if (r3) {
		printf("rlSessionByGamerHandleTask: ");
		printf((char*)(r3 + 0x90));
		printf("\n");
	}
	memcpy((void*)0x132A2BC, hook_0x132A2BC_orig, 4 * 4);
	call<int>(0x132A2BC)(r3);
	memcpy((void*)0x132A2BC, hook_0x132A2BC_patch, 4 * 4);
}*/



__NO_INLINE void create_readsessioninfo_hook() {//0x132A2BC
	encryptFunctionStart((void*)create_readsessioninfo_hook);
	//0xD5B3E4  seems to not ever be called
	//0x132A2BC is called on "getting session details" so this should be correct
	//0x132A5D0 is called when you join a random session and it gets return values from the found session
	//0x132AE30 is for 
	memcpy(hook_0x132AE30_orig, (void*)(addrstruct().privk_132AE30 ^ dataDecryptor() ^ 0x1C82DE14)/*value: 0x132AE30*/, 4 * 4);
	PatchInJumpAddr((addrstruct().privk_132AE30 ^ dataDecryptor() ^ 0x1C82DE14)/*value: 0x132AE30*/, (int)hook_0x132AE30, false);
	memcpy(hook_0x132AE30_patch, (void*)(addrstruct().privk_132AE30 ^ dataDecryptor() ^ 0x1C82DE14)/*value: 0x132AE30*/, 4 * 4);

	//memcpy(hook_0x132A2BC_orig, (void*)0x132A2BC, 4 * 4);
	//PatchInJumpAddr(0x132A2BC, (int)hook_0x132A2BC, false);
	//memcpy(hook_0x132A2BC_patch, (void*)0x132A2BC, 4 * 4);
	encryptFunctionEnd();
}













//void findGamerSessionHook(int N4rage23rlFindGamerSessionsTaskE) {//0x132A5D0
	//this is called when you join a random session and it gets return values I think

//}


//ReadSessionInfoResponse1->Hook(0x132A2BC, MY_ReadSessionInfoResponse1); //0xD5B3E4
//ReadSessionInfoResponse2->Hook(0x132A5D0, MY_ReadSessionInfoResponse2);



template <typename T>
class ArrayList {
private:
	T* arr;
	int size;
	int count;
	
	void resize(int newSize) {
		T* tmpArray = arr;
		size = newSize;
		//arr = (T*)_malloc(newSize * sizeof(T));
		//arr = (T*)call<char*>(0x10310)(newSize * sizeof(T));//gta malloc
		arr = (T*)0x10030000;
		if (tmpArray != 0) {
			memcpy(arr, tmpArray, sizeof(T) * count);//copy old values over
			//_free(tmpArray);
		}
	}
	void grow() {
		resize(size * 2);//double in size 
	}
public:
	ArrayList() {
		arr = 0;
		size = 0;
		count = 0;
		resize(1);
	}
	~ArrayList() {
		//printf("\n\n\n\n\n\n\n\n\n\nDESTRUCTOR OF ARRAYLIST CALLED!\n\n\n\n\n\n\n\n\n");
		//_free(arr);
	}
	int indexOf(T entity) {
		for (int i = 0; i < count; i++) {
			if (entity.equals(arr[i])) {
				return i;
			}
		}
		return -1;
	}

	int getCount() {
		return count;
	}

	void clear() {
		count = 0;
	}

	T* get(int index) {
		return &arr[index];
	}

	void add(T entity) {
		
		int i = indexOf(entity);
		if (i != -1)
			return;//do not add, already in array

		if (count == size)
			grow();
		memcpy((void*)&arr[count],(void*)&entity,sizeof(entity));
		count++;
	}

	int remove(T entity) {

		int i = indexOf(entity);
		if (i == -1)
			return -1;//not found
		
				
		memcpy(&arr[i], &arr[i+1], sizeof(T) * (count-i-1));
		

		count--;

		return i;
	}
};

struct MetPlayer {
	char psn[20];
	char gsinfo[100];
	bool waitingOnUpdate;
	bool equals(MetPlayer p) {
		if (strstr(psn, p.psn) != 0 && strstr(p.psn, psn) != 0) {//only check psn, no need to check gsinfo
			return true;
		}
		return false;
	}
};


ArrayList<MetPlayer> MetPlayers = ArrayList<MetPlayer>();
#define METPLAYERS_MAX 99

void addMetPlayer(char *playerName) {
	if (MetPlayers.getCount() > METPLAYERS_MAX) {
		//print2("~r~Please clear list before adding more players");
		return;
	}
	if (strlen(playerName) == 0)
		return;
	MetPlayer p = { 0 };
	strncpy(p.psn,playerName,sizeof(p.psn)-1);
	p.waitingOnUpdate = false;
	MetPlayers.add(p);

}

char* getMetPlayerStatus(int i) {
	int len = strlen(MetPlayers.get(i)->gsinfo);
	if (len > 1)
		return "~g~GTA Online Session";
	if (len == 1) {
		return "~y~SP or Offline";
	}
	return "~r~Offline";
}

bool isPlayerMetInPublicLobby(int i) {
	int len = strlen(MetPlayers.get(i)->gsinfo);
	if (len > 1)
		return true;
	return false;
}

bool isPlayerMetInPublicLobbyOrSP(int i) {
	int len = strlen(MetPlayers.get(i)->gsinfo);
	if (len > 0)
		return true;
	return false;
}

void checkForPlayerStatusUpdate(int playerIndexMet) {
	if (MetPlayers.get(playerIndexMet)->waitingOnUpdate == false) {
		//it received a result
	}
	else {
		MetPlayers.get(playerIndexMet)->gsinfo[0] = 0;//nullify the string, length of 0
	}
}

__NO_INLINE void updatePlayerStatus(int playerIndexMet) {
	encryptFunctionStart((void*)updatePlayerStatus);
	NETWORK::_0x3F7EDBBD(); //reset net

	int networkStruct[13];

	NETWORK::NETWORK_HANDLE_FROM_USER_ID(MetPlayers.get(playerIndexMet)->psn, networkStruct, 13);

	NETWORK::_0x42BD0780(networkStruct);//tell it to use this player
	NETWORK::_0xBEB98840();//execute it, same as SendSessionInfoRequest basically

	MetPlayers.get(playerIndexMet)->waitingOnUpdate = true;

	//MetPlayers.get(playerIndexMet)->gsinfo[0] = 0;//if it finds new results, it will update it momentarily

	runlater_time::runlater(2/*seconds*/, checkForPlayerStatusUpdate, playerIndexMet);
	encryptFunctionEnd();
}


/*void updateAllMetPlayersStatus() {
	
	NETWORK::_0x3F7EDBBD(); //reset net

	int networkStruct[13];

	for (int i = 0; i < MetPlayers.getCount(); i++) {
		NETWORK::NETWORK_HANDLE_FROM_USER_ID(MetPlayers.get(i)->psn, networkStruct, 13);

		NETWORK::_0x42BD0780(networkStruct);//tell it to use this player
		NETWORK::_0xBEB98840();//execute it, same as SendSessionInfoRequest basically
	}
	
}*/

void updateMetPlayerStatus(char* json) {

	char* id = extract_id(json);
	//printf("id found: %s\n", id);//NP 2 "markcussssss1, need to remove the np 2 before copying

	//GsInfo = extractGsInfo(json);
	//printf("GsInfo found: %s\n", GsInfo);

	for (int i = 0; i < MetPlayers.getCount(); i++) {

		if (strstr(id,MetPlayers.get(i)->psn) != 0) {
			char* gs = extractGsInfo(json);
			//printf("GsInfo found: %s\n", gs);
			if (strlen(gs) == 0)//singleplayer 
				gs = "o";//set it to be a string length of 1 so we can see they are online but not in a lobby
			strncpy(MetPlayers.get(i)->gsinfo, gs, sizeof(MetPlayers.get(i)->gsinfo) - 1);
			MetPlayers.get(i)->waitingOnUpdate = false;
			return;//exit loop
		}
	} 
}



namespace FindRandomGamers {

	int findStatus = 4;
	int currentFoundAmt = 0;
	int currentCount = 0;

	__NO_INLINE void fg_0() {
		encryptFunctionStart((void*)fg_0);
		if (I_AM_ONLINE) {
			NETWORK::_0xA13045D4(1, 0, -1.0, -1.0);
			findStatus = 1;
			currentFoundAmt = 0;
			currentCount = 0;
		}
		encryptFunctionEnd();
	}

	__NO_INLINE void fg_1() {
		encryptFunctionStart((void*)fg_1);
		if (NETWORK::_0xBEDC4503()) {
			int num = NETWORK::NETWORK_GET_NUM_FOUND_GAMERS();
			currentFoundAmt = num;
			currentCount = 0;
			//printf("Found %i gamers\n",num);





			for (int i = 0; i < num; i++) {
				int gamer[14];
				if (NETWORK::NETWORK_GET_FOUND_GAMER(gamer, i)) {
					if (NETWORK::NETWORK_IS_HANDLE_VALID(gamer, 13)) {
						char* name = NETWORK::NETWORK_GET_GAMERTAG_FROM_HANDLE(gamer);
						//printf("Name: %s\n", name);
						addMetPlayer(name);

					}
				}
			}
			findStatus = 3;//2 originally
		}
		else {
			//printf("Error with the gamer finding\n");
			findStatus = 3;
		}
		encryptFunctionEnd();
	}

	__NO_INLINE void fg_3() {
		encryptFunctionStart((void*)fg_3);
		NETWORK::NETWORK_CLEAR_FOUND_GAMERS();
		findStatus = 4;
		encryptFunctionEnd();
	}

	void findRandomGamers() {
		switch (findStatus) {
		case 0:
			fg_0();
			break;
		case 1:
			int fg_addr = *(int*)0x1CF730C;
			if (fg_addr != 0) {
				
				if (*(int*)fg_addr != 1/*!NETWORK::NETWORK_IS_FINDING_GAMERS()*/) {
					fg_1();
				}
				else {
					//printf("Finding\n");
				}
			}
			else {
				fg_1();//another check for it i guess lmao, when it equals 0 it returns false so nop of it is true
			}
			break;
		case 3:
			fg_3();
			break;
		}
	}

	void findRandomGamersStart() {
		if (MetPlayers.getCount() > METPLAYERS_MAX) {
			print2("~r~Please clear list before adding more players");
		}
		else {
			findStatus = 0;
		}
	}
	void findRandomGamersStop() {
		findStatus = 4;
	}
}

//newStruct has to be size of 0x30
void network_handle_to_useable_data(void *handle, void *newStruct) {
	call<int>(0xD247A8)(newStruct);
	call<int>(0x47E2D4)(newStruct,handle, 0xD, "");
	//printf("Made data WPOOOOOOOOOOOOOO\n");
}

//#ifdef oldjoinfixomg
void joinsessionacceptfix_hook(int checkVal, unsigned int r4, unsigned int r3) {
	if (checkVal == 0)
		return;

	//bool doSpoofNameForJoinFix = false;
	//char doSpoofNameForJoinFixName[20];

	//char* evtName = (char*)(r3 + 0x8);
	//char origName[20];
	//strncpy(origName,evtName,20);

	unsigned int spoofedNetworkHandleVal = r3;

	char weirdThingy[0x30];

	if (doSpoofNameForJoinFix) {
		//strncpy(evtName, doSpoofNameForJoinFixName, 20);
		int newMemberHandle[13];
		NETWORK::NETWORK_HANDLE_FROM_USER_ID(doSpoofNameForJoinFixName, newMemberHandle, 13);
		network_handle_to_useable_data(newMemberHandle, weirdThingy);
		spoofedNetworkHandleVal = (unsigned int)weirdThingy;
		
		//doSpoofNameForJoinFix = false;//will get reset 10 seconds after
	}

	call<int>(0xD23384)(spoofedNetworkHandleVal,r4, 0x34, 0);//storeEventDataIntoCEventNetwork
}
//#endif

void NETWORK_IS_GAMER_IN_MY_SESSION_hook(unsigned int r3) {//not used, the function above is used instead as a solution
	if (doSpoofNameForJoinFix) {

		*(int*)*(int*)r3 = false;
	}
	else {
		call<int>(0x1589E44)(r3);
	}
}
 
void NETWORK_SESSION_GET_INVITER_hook(unsigned int r3) {//unused... no need to spoof inviter, I'm making it say I wasn't invited instead as if I joined a random session
	if (doSpoofNameForJoinFix) {
		r3 = *(int*)*(int*)(r3 + 0x8);//first arg
		NETWORK::NETWORK_HANDLE_FROM_USER_ID(doSpoofNameForJoinFixName, (int*)r3, 13);
	}
	else {
		call<int>(0x15874E8)(r3);
	} 
}

void NETWORK_BAIL_hook() {//unused... don't wanna block the bails in case there is a legitimate bail reason
	if (doSpoofNameForJoinFix) {

	}
	else {
		call<int>(0x1586A48)();
	}
}

void NETWORK_SESSION_WAS_INVITED_hook(unsigned int r3) {
	if (doSpoofNameForJoinFix) {

		*(int*)*(int*)r3 = false;//say I wasn't invited so it doesn't check if they are still there
	}
	else {
		call<int>(0x15874C0)(r3);
	}
}
 
__NO_INLINE void joinsessionacceptfix() {
	encryptFunctionStart((void*)joinsessionacceptfix);
//#ifdef fuckkkyyyyynotgonnamesswiththisbigcodeanymore

	//Patch the 'CEventNetworkInviteAccepted' function
	//encryptFunctionStart((void*)joinsessionacceptfix);
	*(int*)0x1739A4C = 0x30980010;//addic     r4, r24, 0x10
	*(int*)0x1739A50 = 0x7F25CB78;//mr        r5, r25
	PatchInJump2(0x1739A54, (int)joinsessionacceptfix_hook, true);//make it linked
	//encryptFunctionEnd();

	//Patch the 'CEventNetworkInviteConfirmed' function
	//0x1739974
	*(int*)0x1739974 = 0x30980010;//addic     r4, r24, 0x10
	*(int*)0x1739978 = 0x7F25CB78;//mr        r5, r25
	PatchInJump2(0x173997C, (int)joinsessionacceptfix_hook, true);//make it linked

//#endif
	 
	//*(uint64_t*)(0x1C293D8) = *(uint64_t*)((int)NETWORK_IS_GAMER_IN_MY_SESSION_hook);//make it think they are not already in our session, this is alternative for code above, not sure which one is better

	//*(uint64_t*)(0x1C28CE0) = *(uint64_t*)((int)NETWORK_SESSION_GET_INVITER_hook);//I'm not sure this fixes the issue...
	//*(uint64_t*)(0x1C28B18) = *(uint64_t*)((int)NETWORK_BAIL_hook);//this would patch any bails such as private lobbies, but also possibly cause infinite loading
	*(uint64_t*)(0x1C28CD8) = *(uint64_t*)((int)NETWORK_SESSION_WAS_INVITED_hook);//make it think I wasn't invited so it doesn't check if they are in the lobby
	encryptFunctionEnd();
}


float attack_damage = 1.0f;
Vector3 attack_offset = { 0,0,0 };
int attack_value = 0x9;

void sendAttackEventOnPlayer_fullstack_technicallythecorrectone(int attackerped, int victimped, float damage, float *attackFromCoords, int attackVal, unsigned int weaponHash) {
	//call<void>(0x12C02A0)(getCObjFromIndex(attackerped), getCObjFromIndex(victimped), damage/*f1*/, attackFromCoords, attackVal, 1/*r7*/, weaponHash, (int64_t)-1, (int64_t)-1);
	opd_s func_ = { 0x12C02A0 , TOC};
	void(*func)(CObj * attackerped, CObj* victimped, float *coords, int attackVal, int one, unsigned int weaponHash, int64_t neg1, int64_t neg1Two, int64_t neg1_stack70, uint64_t stack78, uint64_t stack80, uint64_t stack88, uint64_t stack90, uint64_t stack98, uint64_t stackA0, uint64_t stackA8, uint64_t stackB0, float f1 ) = (void(*)(CObj * attackerped, CObj * victimped, float* coords, int attackVal, int one, unsigned int weaponHash, int64_t neg1, int64_t neg1Two, int64_t neg1_stack70, uint64_t stack78, uint64_t stack80, uint64_t stack88, uint64_t stack90, uint64_t stack98, uint64_t stackA0, uint64_t stackA8, uint64_t stackB0, float f1)) & func_;
	//__asm("li %r11, 0");
	//__asm("li %r12, 0"); 
	//func(getCObjFromIndex(attackerped), getCObjFromIndex(victimped), attackFromCoords, attackVal, 1/*r7*/, weaponHash, (int64_t)-1, (int64_t)-1/*r1+0x70*/, 0/*r1+0x78*/, 0/*r1+0x80*/,    0x1001/*r1+0x88   0x8C*/, 0x1002/*r1+0x90   0x94*/, 0x1003, 0x1004, 0x1005, 0x1006, 0x1007, damage/*f1*/);
	func(getCObjFromIndex(attackerped), getCObjFromIndex(victimped), attackFromCoords, attackVal, 1/*r7*/, weaponHash, (int64_t)-1, -1/*this is actually the last value?? idk lmao*/, (int64_t)-1/*r1+0x70*/, 0x20A/*r1+0x78*/, 0x9EAA26F9/*r1+0x80*/, /*0x2*/0xD/*r1+0x88 */, 0x510392ED/*r1+0x90*/, 0x0/*0x98*/, 0x0/*0xA0*/, 0x0/*0xA8*/, 0x0/*0xB0*/, damage/*f1*/);
	//                                                                                                                                        0x70:FFFFFFFFFFFFFFFF 0x78:000000000000020A 0x80:000000009EAA26F9 0x88:0000000000000002 0x90:00000000510392ED 0x98:0000000000000000 0xA0:0000000000000000 0xA8:0000000000000000 0xB0:0000000000000000             0000000032487B80 0000000000000000 0000000001CFB548 0000000033224B40 0000000001CFB548
}

void sendAttackEventOnPlayer(int attackerped, int victimped, float damage, float* attackFromCoords, int attackVal, unsigned int weaponHash) {
	opd_s func_ = { 0x12C02A0 , TOC };
	void(*func)(CObj * attackerped, CObj * victimped, float* coords, int attackVal, int one, unsigned int weaponHash, int64_t neg1, int64_t neg1Two, float f1) = (void(*)(CObj * attackerped, CObj * victimped, float* coords, int attackVal, int one, unsigned int weaponHash, int64_t neg1, int64_t neg1Two, float f1)) & func_;
	
	func(getCObjFromIndex(attackerped), getCObjFromIndex(victimped), attackFromCoords, attackVal, 1/*r7*/, weaponHash, (int64_t)-1, -1, damage/*f1*/);
}

char WEAPON_DAMAGE_EVENT_local_hook_orig[4 * 4];
char WEAPON_DAMAGE_EVENT_local_hook_patch[4 * 4];
struct Punch {
	CObj* attackerped;
	CObj* victimped;
	float coords[3];
	int attackVal;
	int one;
	unsigned int weaponHash;
	int64_t neg1;
	int64_t neg1Two;
	int64_t neg1_stack70;
	uint64_t stack78;
	uint64_t stack80;
	uint64_t stack88;
	uint64_t stack90;
	uint64_t stack98;
	uint64_t stackA0;
	uint64_t stackA8;
	uint64_t stackB0;
	float f1;
};
Punch lastPunch;
int lastAttackedPed;

bool animepunch_bool = false;
bool doAnimePunchSequence = false;
void startPunch();

__NO_INLINE void WEAPON_DAMAGE_EVENT_local_hook(CObj* attackerped, CObj* victimped, float* coords, int attackVal, int one, unsigned int weaponHash, int64_t neg1, int64_t neg1Two, int64_t neg1_stack70, uint64_t stack78, uint64_t stack80, uint64_t stack88, uint64_t stack90, uint64_t stack98, uint64_t stackA0, uint64_t stackA8, uint64_t stackB0, float f1) {


	//if (doAnimePunchSequence == true) {
		//this should never happen... make abort sequence
		//printf("ERROR ABORT SEQUENCE\n");
		//doAnimePunchSequence = false;
		//return;
	//}

	//bool do_rehook = true;

	bool cancelpunch = false;

	if (weaponHash == GAMEPLAY::GET_HASH_KEY("weapon_unarmed")) {
		lastAttackedPed = entityToIndex(victimped);
		lastPunch.attackerped = attackerped;
		lastPunch.victimped = victimped;
		lastPunch.coords[0] = coords[0];
		lastPunch.coords[1] = coords[1];
		lastPunch.coords[2] = coords[2];
		lastPunch.attackVal = attackVal;
		lastPunch.one = one;
		lastPunch.weaponHash = weaponHash;
		lastPunch.neg1 = neg1;
		lastPunch.neg1Two = neg1Two;
		lastPunch.neg1_stack70 = neg1_stack70;
		lastPunch.stack78 = stack78;
		lastPunch.stack80 = stack80;
		lastPunch.stack88 = stack88;
		lastPunch.stack90 = stack90;
		lastPunch.stack98 = stack98;
		lastPunch.stackA0 = stackA0;
		lastPunch.stackA8 = stackA8;
		lastPunch.stackB0 = stackB0;
		lastPunch.f1 = f1;

		if (animepunch_bool) {
			startPunch();
			cancelpunch = true;
			//do_rehook = false;
		}

	}

	//memcpy((void*)0x12C02A0, WEAPON_DAMAGE_EVENT_local_hook_orig, 4 * 4);

	opd_s func_ = { 0x12C02A0 , TOC };
	void(*func)(CObj * attackerped, CObj * victimped, float* coords, int attackVal, int one, unsigned int weaponHash, int64_t neg1, int64_t neg1Two, int64_t neg1_stack70, uint64_t stack78, uint64_t stack80, uint64_t stack88, uint64_t stack90, uint64_t stack98, uint64_t stackA0, uint64_t stackA8, uint64_t stackB0, float f1) = (void(*)(CObj * attackerped, CObj * victimped, float* coords, int attackVal, int one, unsigned int weaponHash, int64_t neg1, int64_t neg1Two, int64_t neg1_stack70, uint64_t stack78, uint64_t stack80, uint64_t stack88, uint64_t stack90, uint64_t stack98, uint64_t stackA0, uint64_t stackA8, uint64_t stackB0, float f1)) & func_;
	if (cancelpunch == false) {
		func(attackerped, victimped, coords, attackVal, one, weaponHash, neg1, neg1Two, neg1_stack70, stack78, stack80, stack88, stack90, stack98, stackA0, stackA8, stackB0, f1);
	}
	//if (do_rehook) {
	//	memcpy((void*)0x12C02A0, WEAPON_DAMAGE_EVENT_local_hook_patch, 4 * 4);
	//}


	
}

void executeLastPunch() {
	if (VALID_ADDR(lastPunch.attackerped) && VALID_ADDR(lastPunch.victimped)) {
		opd_s func_ = { 0x12C02A0 , TOC };
		void(*func)(CObj * attackerped, CObj * victimped, float* coords, int attackVal, int one, unsigned int weaponHash, int64_t neg1, int64_t neg1Two, int64_t neg1_stack70, uint64_t stack78, uint64_t stack80, uint64_t stack88, uint64_t stack90, uint64_t stack98, uint64_t stackA0, uint64_t stackA8, uint64_t stackB0, float f1) = (void(*)(CObj * attackerped, CObj * victimped, float* coords, int attackVal, int one, unsigned int weaponHash, int64_t neg1, int64_t neg1Two, int64_t neg1_stack70, uint64_t stack78, uint64_t stack80, uint64_t stack88, uint64_t stack90, uint64_t stack98, uint64_t stackA0, uint64_t stackA8, uint64_t stackB0, float f1)) & func_;
		func(lastPunch.attackerped, lastPunch.victimped, lastPunch.coords, lastPunch.attackVal, lastPunch.one, lastPunch.weaponHash, lastPunch.neg1, lastPunch.neg1Two, lastPunch.neg1_stack70, lastPunch.stack78, lastPunch.stack80, lastPunch.stack88, lastPunch.stack90, lastPunch.stack98, lastPunch.stackA0, lastPunch.stackA8, lastPunch.stackB0, lastPunch.f1);
	}
}


__NAKED void WEAPON_DAMAGE_EVENT_local_hook_middleman(CObj* attackerped, CObj* victimped, float* coords, int attackVal, int one, unsigned int weaponHash, int64_t neg1, int64_t neg1Two, int64_t neg1_stack70, uint64_t stack78, uint64_t stack80, uint64_t stack88, uint64_t stack90, float f1) {//technically the arguments dont matter at all...
	//r24 is r1
	//just re-writing the lines I overwrote basically, was able to preserve r1 into r24... WAIT... I don't even need to do that
	//__asm__("std %r11,0x98(%r24)");
	__asm__("std %r28,0xA0(%r1)");
	__asm__("std %r12,0xA8(%r1)");
	__asm__("std %r26,0xB0(%r1)");
	__asm__("b ._Z30WEAPON_DAMAGE_EVENT_local_hookP4CObjS0_Pfiijxxxyyyyyyyyf");//if I don't have the '.' before it, then it references the opd segment. Interesting
	//__asm__("b ._Z26eventFunction_special_Hookjjjj");
}

void setup_WEAPON_DAMAGE_EVENT_local_hook() {
	//memcpy(WEAPON_DAMAGE_EVENT_local_hook_orig, (void*)0x12C02A0, 4 * 4);
	//PatchInJump2(0x12C02A0, (int)WEAPON_DAMAGE_EVENT_local_hook, false);
	//memcpy(WEAPON_DAMAGE_EVENT_local_hook_patch, (void*)0x12C02A0, 4 * 4);
	//*(int*)0xFBA9D4 = 0xF8210098;//std %r1,0x98(%r1)      std       r11, 0x410+var_378(r1) # 0x98
	//*(int*)0xFBA9D4 = 0x7C380B78;//mr %r24, %r1
	PatchInJump2(0xFBA9D8, (int)WEAPON_DAMAGE_EVENT_local_hook_middleman, true);
	if ((int)setup_WEAPON_DAMAGE_EVENT_local_hook == 0x65) {
		WEAPON_DAMAGE_EVENT_local_hook(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);//just make sure this function gets loaded into memory lmao
	}
}

void endPunch(int a) {
	//memcpy((void*)0x12C02A0, WEAPON_DAMAGE_EVENT_local_hook_patch, 4 * 4);//rehook
	//ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), false);
	doAnimePunchSequence = false;
}

void startPunch() {
	if (doAnimePunchSequence == false) {
		//memcpy((void*)0x12C02A0, WEAPON_DAMAGE_EVENT_local_hook_orig, 4 * 4);//unhook to use normal func for awhile
		doAnimePunchSequence = true;
		//ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), true);
		//AI::TASK_PAUSE(PLAYER::PLAYER_PED_ID(),2000);
		runlater::runlater(200, endPunch);
	}
}

void animepunch_loop() {
	if (doAnimePunchSequence) {
		executeLastPunch();
		//PED::_0x187B9070(PLAYER::PLAYER_PED_ID(), true, true);
		//AI::TASK_PUT_PED_DIRECTLY_INTO_MELEE(PLAYER::PLAYER_PED_ID(), lastAttackedPed, 0.0f, -1.0f, 0.0f, 0);
		//print2("PUNCHING"); 
	}
}




#define NUM_HOOKS 2

//two free memory locations (16 bytes)
#define ONE_HOOK_LR *(unsigned int*)0x1944820
#define ONE_HOOK_BRANCHDATA *(unsigned int*)0x1944828
#define ONE_HOOK_R2 *(unsigned int*)0x1944830


uint64_t one_hook_dummy_func(uint64_t r3, uint64_t r4, uint64_t r5, uint64_t r6, uint64_t r7, uint64_t r8, uint64_t r9, uint64_t r10, uint64_t r11, uint64_t r12, uint64_t r13, uint64_t r14, uint64_t r15, uint64_t r16, uint64_t r17, uint64_t r18, uint64_t r19, uint64_t r20, uint64_t r21) {
	return 0;
}

struct hook_pairs {
	unsigned int hookaddress;
	unsigned int firstinstruction;
	unsigned int functionToCallInSprxOPD;
	//one_hook_function_call callFunc = &one_hook_dummy_func;
};

hook_pairs one_hooks[NUM_HOOKS];

#define one_hook_stub \
	__asm("lis %r11, 0x194");\
	__asm("addi %r11, %r11, 0x4830");\
	__asm("lwz %r2, 0x0(%r11)");\
	__asm("addi %r11, %r11, -0x8");\
	__asm("lwz %r11, 0x0(%r11)");\
	__asm("mtctr %r11");\
	__asm("bctr");//braches to hooked function



//need to add another one of these functions if the function you are hooking does not start with one of these two instructions
__NAKED uint64_t one_hook_stub_mflrr0(uint64_t r3, uint64_t r4, uint64_t r5, uint64_t r6, uint64_t r7, uint64_t r8, uint64_t r9, uint64_t r10, uint64_t r11, uint64_t r12, uint64_t r13, uint64_t r14, uint64_t r15, uint64_t r16, uint64_t r17, uint64_t r18, uint64_t r19, uint64_t r20, uint64_t r21) {
	__asm("mflr %r0");

	one_hook_stub;
}

__NAKED uint64_t one_hook_stub_r170(uint64_t r3, uint64_t r4, uint64_t r5, uint64_t r6, uint64_t r7, uint64_t r8, uint64_t r9, uint64_t r10, uint64_t r11, uint64_t r12, uint64_t r13, uint64_t r14, uint64_t r15, uint64_t r16, uint64_t r17, uint64_t r18, uint64_t r19, uint64_t r20, uint64_t r21) {
	__asm("stdu %r1, -0x70(%r1)");

	one_hook_stub;
}

/*
uint64_t(*
get_hook_function(int hookIndex)
)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t)

{
	//opd_s func_ = { *(int*)functionToCallInSprxOPD , *(int*)(functionToCallInSprxOPD + 0x4) };
	//uint64_t(*func)(uint64_t r3, uint64_t r4, uint64_t r5, uint64_t r6, uint64_t r7, uint64_t r8, uint64_t r9, uint64_t r10, uint64_t r11, uint64_t r12, uint64_t r13, uint64_t r14, uint64_t r15, uint64_t r16, uint64_t r17, uint64_t r18, uint64_t r19, uint64_t r20, uint64_t r21) = (uint64_t(*)(uint64_t r3, uint64_t r4, uint64_t r5, uint64_t r6, uint64_t r7, uint64_t r8, uint64_t r9, uint64_t r10, uint64_t r11, uint64_t r12, uint64_t r13, uint64_t r14, uint64_t r15, uint64_t r16, uint64_t r17, uint64_t r18, uint64_t r19, uint64_t r20, uint64_t r21)) & func_;

	return one_hooks[hookIndex].callFunc;
}*/


int one_hook(uint64_t r3, uint64_t r4, uint64_t r5, uint64_t r6, uint64_t r7, uint64_t r8, uint64_t r9, uint64_t r10, uint64_t r11, uint64_t r12, uint64_t r13, uint64_t r14, uint64_t r15, uint64_t r16, uint64_t r17, uint64_t r18, uint64_t r19, uint64_t r20, uint64_t r21) {
	unsigned int lr_val = ONE_HOOK_LR;

	//printf("LR found: 0x%X\n",lr_val);//lr val was the original bytes for some reason 0x636C6544.....

	unsigned int branched_from = ONE_HOOK_LR - 0x4;                     //0xA10AC4
	unsigned int dif = *(unsigned int*)(branched_from) & 0x3FFFFFF;      //0xFFEDE5
	unsigned int extra = dif % 4;//should return 0, 1, 2, or 3          //0x1
	dif = dif - extra;//now dif should be the proper dif                //0xFFEDE5 - 0x1 = 0xFFEDE4

	int check = dif >> 25;
	if (check == 1) {
		dif = dif | 0xFC000000;//extend the negative from 26 bits to 32 bits if it is negative
	}

	unsigned int branched_to = dif + branched_from;//should be correct! //0xFFEDE4 + 0xA10AC4 = 0x1A0F8A8
	
	unsigned int hooked_address = branched_to;
	//printf("hooked address discovered: 0x%X\n",hooked_address);

	//unsigned int instruction = 0; 
	//unsigned int functionToCallInSprxOPD = 0;
	//one_hook_function_call callFunc = &one_hook_dummy_func;
	int hookIndex = -1;
	for (int i = 0; i < NUM_HOOKS; i++) {
		if (one_hooks[i].hookaddress == hooked_address) {
			//instruction = one_hooks[i].firstinstruction;
			//functionToCallInSprxOPD = one_hooks[i].functionToCallInSprxOPD;
			hookIndex = i;
		}
	}

	 
	ONE_HOOK_BRANCHDATA = hooked_address + 4;//go to the next instruction after it

	one_hook_function_call callFunc = one_hook_dummy_func;

	int ret = 0;
	//if (shouldCallOrig) {
		//printf("About to call on instruction: 0x%X\n", instruction);
	if (hookIndex != -1) {
		if (one_hooks[hookIndex].firstinstruction == 0x7C0802A6)//mflr %r0
			callFunc = &one_hook_stub_mflrr0;
		//ret = one_hook_stub_mflrr0(r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19, r20, r21);
		else if (one_hooks[hookIndex].firstinstruction == 0xF821FF91)//stdu %r1, -0x70(%r1)
			callFunc = &one_hook_stub_r170;
		//ret = one_hook_stub_r170(r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19, r20, r21);
		else {
			//printf("Hook at 0x%X does not have a registered stub for instruction 0x%X !!\n", hooked_address, one_hooks[hookIndex].firstinstruction);
		}
	}
	else {
		//printf("Hook at 0x%X does not exist at all (invalid index) !!\n", hooked_address);
	}
	//}

	if (hookIndex != -1) {
		//need to fix the function first before we call it
		

		opd_s func_ = { *(int*)one_hooks[hookIndex].functionToCallInSprxOPD , *(int*)(one_hooks[hookIndex].functionToCallInSprxOPD + 0x4) };
		uint64_t(*func)(one_hook_function_call hooked_func,uint64_t r3, uint64_t r4, uint64_t r5, uint64_t r6, uint64_t r7, uint64_t r8, uint64_t r9, uint64_t r10, uint64_t r11, uint64_t r12, uint64_t r13, uint64_t r14, uint64_t r15, uint64_t r16, uint64_t r17, uint64_t r18, uint64_t r19, uint64_t r20, uint64_t r21) = (uint64_t(*)(one_hook_function_call,uint64_t r3, uint64_t r4, uint64_t r5, uint64_t r6, uint64_t r7, uint64_t r8, uint64_t r9, uint64_t r10, uint64_t r11, uint64_t r12, uint64_t r13, uint64_t r14, uint64_t r15, uint64_t r16, uint64_t r17, uint64_t r18, uint64_t r19, uint64_t r20, uint64_t r21)) & func_;

		ret = func(callFunc,r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19, r20, r21);
	}
	
	
	

	return ret;
} 

__NAKED int one_hook_intermediate() {
	__asm("mflr %r0");//this will link back to the previous func
	__asm("stdu %r1, -0x70(%r1)");
	__asm("std %r0, 0x60(%r1)");

	//now locate the link register from the previous function
	//branched to - branched from = dif (lower 3 bytes of instruction)
	//branched to = dif + branched from
	__asm("lis %r11, 0x194");//assume r11 is never used
	__asm("addi %r11, %r11, 0x4820");//ONE_HOOK_LR
	__asm("stw %r0, 0x0(%r11)");//stores the lr to get back to the original call point into the spot we like

	//__asm("lis %r11, 0x194");//assume r11 is never used
	//__asm("addi %r11, %r11, 0x4830");//ONE_HOOK_R2
	__asm("addi %r11, %r11, 0x10");//ONE_HOOK_R2 is ONE_HOOK_LR + 0x10
	__asm("stw %r2, 0x0(%r11)");//stores the lr to get back to the original call point into the spot we like


	__asm("bl ._Z8one_hookyyyyyyyyyyyyyyyyyyy");



	__asm("ld %r0, 0x60(%r1)");
	__asm("mtlr %r0");//this will be the link register to the
	__asm("addi %r1, %r1, 0x70");
	__asm("blr");//goes all the way back to the function that called our hooked function
}


bool onehookhasbeensetup = false;
void setup_one_hook() {
	//address we are putting it at is X
	//anything between X and X+Y is guarenteed to hit a trap, so it's probably never executed. We assume that and also add a cmall check just in case it is if necessary
	
	//0x38A048 has 10 instructions to work with
	//0xA104F0 has 11 instructions to work with
	//with a slgiht modification (below), 0xA104E8 can be used with 13 instructions and never be ran under normal circumstances
	*(int*)0xA104E4 = 0x48000038;//change this to always branch and squeeze out 2 more instructions

	//bytes based off this function: 0x474054 entityToIndex
	//unsigned char bytes_storelr[] = { 0xF8, 0x21, 0xFF, 0x91, 0x7C, 0x08, 0x02, 0xA6, 0xF8, 0x01, 0x00, 0x80 };//3 instructions
	//unsigned char bytes_retreivelrandbranch[] = { 0xE8, 0x01, 0x00, 0x80, 0x7C, 0x08, 0x03, 0xA6, 0x38, 0x21, 0x00, 0x70, 0x4E, 0x80, 0x00, 0x20 };//4 instructions

	//memcpy(0xA104E8 + 4*0, bytes_storelr, 4*3);//3 instructions
	PatchInJump2(0xA104E8/* + 4*3*/, (int)one_hook_intermediate, false);//4 instructions
	//memcpy(0xA104E8 + 4*7, bytes_retreivelrandbranch, 4 * 4);//4 instructions

	//this code will 

} 

void create_hook_one(unsigned int address, unsigned int hookinsprx) {
	static int hook_counter = 0;
	one_hooks[hook_counter].hookaddress = address;
	one_hooks[hook_counter].firstinstruction = *(unsigned int*)address;
	one_hooks[hook_counter].functionToCallInSprxOPD = hookinsprx;
	hook_counter++;


	//initialize the setup if not done yet
	if (onehookhasbeensetup == false) {
		onehookhasbeensetup = true;
		setup_one_hook();
	}

	//this cannot cannot be a bl, or else the link register for the previous function will be lost
	//must be unlinked
	unsigned int branch_to = 0xA104E8;//address we did patchinjump to
	unsigned int branch_from = address;
	unsigned int instruction = 0;
	int dif = branch_to - branch_from;
	instruction = 0x48000000 + ((dif) & 0x3FFFFFF);//b instruction forwards and backwards. Last 26 bits are the value :)
	*(int*)address = instruction;
	//printf("[Hook] set address 0x%X to instruction 0x%X\n",address,instruction);

/*
info:

	  11000000000000000000000000 = 26 bits (data of value in b instruction)
	  11111111111111111111111111 = 26 bits (full data of value) = 0x3FFFFFF
 1110 11000000000000000000000000 = 3b000000
 1110 00000000000000000000000000 = 38000000
10010 11111111111110110111100101 = 4BFFEDE5 (branch a little bit backwards)
10010 00000000000000000100010100 = 48000114 (branch just a bit foward)
10010 00000000000000000000000000 = b instruction
*/
	

}

uint64_t EXPLOSION_EVENT_local_hook(one_hook_function_call hooked_func, uint64_t r3, uint64_t r4, uint64_t r5, uint64_t r6, uint64_t r7, uint64_t r8, uint64_t r9, uint64_t r10, uint64_t r11, uint64_t r12, uint64_t r13, uint64_t r14, uint64_t r15, uint64_t r16, uint64_t r17, uint64_t r18, uint64_t r19, uint64_t r20, uint64_t r21) {
	//printf("You created an explosion!\n");
	return hooked_func(r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20,r21);
}

void setup_hooks() {
	//printf("Creating hooks...");
	create_hook_one(0x12C5728, (int)EXPLOSION_EVENT_local_hook);
	create_hook_one(0xA0F8A8, (int)copyNodeToSyncData_detour_one_hook);
	//printf("Done creating hooks.");
	//if ((int)setup_hooks == 50) {
		//one_hook_stub(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	//}
}




void BypassArmanian()
{
	scrProgram* armenian1 = NULL;
	scrProgramTableEntry* item;

	item = scriptTable->FindScript(0x724BF803); // armenian1
	if (item == NULL)
	{
		printf("ERROR: finding address 2\n");
		return;
	}
	if (item->IsLoaded()) // crashes here when removed.. ask gopro tomorrow..
		printf("\nArmanian Script is loaded into memory.\n");
	armenian1 = item->m_program;
	printf("armenian1: 0x%X\n", armenian1);





	int32_t iLocal_514 = armenian1->GetLocal(3101);
	printf("armenian1 %d\n", iLocal_514);


	const char* notyourdopePatch = "\x6F\x2C\x04\x02\xA7\x25\x32\x2C\x04\x00\x09\x2C\x00\x02\xA8";



	for (int i = 0; i < armenian1->GetNumCodePages(); i++)
	{
		uintptr_t hasPrologueBypassAddr = FindPattern((uintptr_t)armenian1->GetCodeAddress(i), (uintptr_t)armenian1->GetCodePageSize(i), (uint8_t*)"\x6F\x2C\x04\x02\xA7", "xxxxx");

		if (hasPrologueBypassAddr)
		{
			printf("Prologue Bypass already exist at 0x%X\n", hasPrologueBypassAddr);
			break;
		}

		uintptr_t occurrences[2];
		uintptr_t sigAddress = FindPattern((uintptr_t)armenian1->GetCodeAddress(i), (uintptr_t)armenian1->GetCodePageSize(i), (uint8_t*)"\x2C\x01\x00\x2B\x56\x00\x10\x6E\x6E\x6E\x6E", "xx?xx?xxxxx", occurrences, 2);
		if (!sigAddress)
			continue;

		printf("Prologue Bypass here 0x%X  0x%X\n", occurrences[0], occurrences[1]);

		memcpy((void*)occurrences[1], (void*)notyourdopePatch, 15);
	}

}


bool HAS_FORCE_CLEANUP_OCCURRED_hook(NativeArg_s* arg) {
	GtaThread* currentGtaThread = getCurrentGtaThread();
	int currentGtaThreadHash = *(int*)(((int)getCurrentGtaThread()) + 0xB0);
	if (currentGtaThreadHash == 0xefdda5b2) {
		//the script is prologue and it is at the beginning of the script
		//BypassPrologue();
		currentGtaThread->setLocal(85, 1);// 1
		currentGtaThread->setLocal(1227, 16); // 16
	}
	if (currentGtaThreadHash == 0x724bf803) {

		scrProgram* program = getScrProgram(0x724bf803);
		uint32_t claire = (uint32_t)program->GetCodeAddress(0);
		const char* notyourdopePatch = "\x6F\x2C\x04\x02\xA7\x25\x32\x2C\x04\x00\x09\x2C\x00\x02\xA8";
		memcpy((void*)(claire + 0xB2B), notyourdopePatch, 15);
		//printf("claire is : 0x%X", claire);
		//the script is armenian and it is at the beginning of the script
		//BypassArmanian();
		currentGtaThread->setLocal(3101, 11);// 11
	}

	call<int>(0x159B2B8)(arg);
}

void setup_HAS_FORCE_CLEANUP_OCCURRED_hook() {
	*(uint64_t*)(0x1C2BB38) = *(uint64_t*)((int)HAS_FORCE_CLEANUP_OCCURRED_hook);
}