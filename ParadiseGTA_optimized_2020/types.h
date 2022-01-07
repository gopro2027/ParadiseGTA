/*Alexander Blade*/

#pragma once

typedef void* Void;
typedef int Any;
typedef unsigned int uint;
typedef int Hash;
typedef int BOOL;
typedef int Entity;
typedef int Player;
typedef int FireId;
typedef int Ped;
typedef int Vehicle;
typedef int Cam;
typedef int CarGenerator;
typedef int Group;
typedef int Train;
typedef int Pickup;
typedef int Object;
typedef int Weapon;
typedef int Interior;
typedef int Blip;
typedef int Texture;
typedef int TextureDict;
typedef int CoverPoint;
typedef int Camera;
typedef int TaskSequence;
typedef int ColourIndex;
typedef int Sphere;
typedef int ScrHandle;
typedef struct
{
    int netHandle, //main network handle
        unk1, unk2, unk3, unk4, unk5, unk6, unk7, unk8, unk9, unk10, unk11, unk12;
} networkHandleMgr;
typedef struct
{
    int clanHandle, //main clan handle
        unk1, unk2, unk3, unk4, unk5, unk6, unk7, unk8, unk9, unk10, unk11, unk12, unk13,
        unk14, unk15, unk16, unk17, unk18, unk19, unk20,
        isCrewActive; //isCrewActive
    char crewRole[8]; //char *crewRole
    //char *creaTag; //char *creaTag
    int unk24, unk25, unk26, unk27, unk28, unk29,
        isLeader, //isLeader
        crewId, //crewId
        unk32, unk33, unk34;
} networkClanMgr;
typedef struct
{
    int memHandle;
    char *unk1;
} networkMembershipMgr;

union ScriptArg {unsigned int ui;float f;int i; char *str;};

	struct script21 {
		int imm_0;
		char *imm_1;
		char *imm_2;
		int imm_3;
		int imm_4;
		int imm_5;
		int imm_6;
		int imm_7;
		int imm_8;
		int imm_9;
		int imm_10;
		int imm_11;
		int imm_12;
		int imm_13;
		int imm_14;
		int imm_15;
		int imm_16;
		int imm_17;
		int imm_18;
		int imm_19;
		int imm_20;
		int imm_21;
	};

	struct script20 {
		int imm_0;
		int imm_1;
		int imm_2;
		int imm_3;
		int imm_4;
		int imm_5;
		int imm_6;
		int imm_7;
		int imm_8;
		int imm_9;
		int imm_10;
		int imm_11;
		int imm_12;
		int imm_13;
		int imm_14;
		int imm_15;
		int imm_16;
		int imm_17;
		int imm_18;
		int imm_19;
		int imm_20;
	};

//#define TOC 0x1C75288 1.25
#define TOC 0x1C85330

struct __opd_s__ { int32_t sub; int32_t toc; };
#define opd_s volatile __opd_s__