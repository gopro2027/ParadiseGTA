/*Alexander Blade*/

#pragma once

// Generated 07 May 2015

#include "nativeCaller.h"

#pragma push_options
#pragma optimize ("O2",on)




namespace PLAYER
{
	static Ped GET_PLAYER_PED(Player player) { return invoke<Ped>(0x6E31E993, player); } // 0x6E31E993
	static Ped GET_PLAYER_PED_SCRIPT_INDEX(Player player) { return invoke<Ped>(0x6AC64990, player); } // 0x6AC64990
	static void SET_PLAYER_MODEL(Player player, Hash modelHash) { invoke<Void>(0x774A4C54, player, modelHash); } // 0x774A4C54
	static void CHANGE_PLAYER_PED(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xBE515485, p0, p1, p2, p3); } // 0xBE515485
	static void GET_PLAYER_RGB_COLOUR(Player player, int* Red, int* Green, int* Blue) { invoke<Void>(0x6EF43BBB, player, Red, Green, Blue); } // 0x6EF43BBB
	static int GET_NUMBER_OF_PLAYERS() { return invoke<int>(0x4C1B8867); } // 0x4C1B8867
	static int GET_PLAYER_TEAM(Player player) { return invoke<int>(0x9873E404, player); } // 0x9873E404
	static void SET_PLAYER_TEAM(Player player, int Team) { invoke<Void>(0x725ADCF2, player, Team); } // 0x725ADCF2
	static char* GET_PLAYER_NAME(Player player) {//NETWORK_PLAYER_GET_NAME also
		char *name = invoke<char*>(0x406B4B20, player);
		/*if (strstr(name, "**Invalid**")/ || strstr("**invalid**")/) {
			CNetGamePlayer* cnet = getCNetGamePlayer(player);
			if (VALID_ADDR(cnet)) {
				CPlayerInfo* info = cnet->playerInfo;
				if (VALID_ADDR(info)) {
					char* rName = info->name;
					name = rName;
				}
			}
		}*/
		//return "invalid_name_spoof";
		return name;
	} // 0x406B4B20
	static float GET_WANTED_LEVEL_RADIUS(Player player) { return invoke<float>(0x1CF7D7DA, player); } // 0x1CF7D7DA
	static Vector3 GET_PLAYER_WANTED_CENTRE_POSITION(Player player) { return invoke<Vector3>(0x821F2D2C, player); } // 0x821F2D2C
	static void SET_PLAYER_WANTED_CENTRE_POSITION(Player player, float x, float y, float z) { invoke<Void>(0xF261633A, player, x, y, z); } // 0xF261633A
	static int GET_WANTED_LEVEL_THRESHOLD(int wantedLevel) { return invoke<int>(0xD9783F6B, wantedLevel); } // 0xD9783F6B
	static void SET_PLAYER_WANTED_LEVEL(Player player, Hash wantedLevel, BOOL p2) { invoke<Void>(0xB7A0914B, player, wantedLevel, p2); } // 0xB7A0914B
	static void SET_PLAYER_WANTED_LEVEL_NO_DROP(Player player, BOOL wantedLevel, Any p2) { invoke<Void>(0xED6F44F5, player, wantedLevel, p2); } // 0xED6F44F5
	static void SET_PLAYER_WANTED_LEVEL_NOW(Player player, BOOL p1) { invoke<Void>(0xAF3AFD83, player, p1); } // 0xAF3AFD83
	static BOOL ARE_PLAYER_FLASHING_STARS_ABOUT_TO_DROP(Player player) { return invoke<BOOL>(0xE13A71C7, player); } // 0xE13A71C7
	static BOOL ARE_PLAYER_STARS_GREYED_OUT(Player player) { return invoke<BOOL>(0x5E72AB72, player); } // 0x5E72AB72
	static void SET_DISPATCH_COPS_FOR_PLAYER(Player player, BOOL Enable) { invoke<Void>(0x48A18913, player, Enable); } // 0x48A18913
	static BOOL IS_PLAYER_WANTED_LEVEL_GREATER(Player player, int wantedLevel) { return invoke<BOOL>(0x589A2661, player, wantedLevel); } // 0x589A2661
	static void CLEAR_PLAYER_WANTED_LEVEL(Player player) { invoke<Void>(0x54EA5BCC, player); } // 0x54EA5BCC
	static BOOL IS_PLAYER_DEAD(Player player) { return invoke<BOOL>(0x140CA5A8, player); } // 0x140CA5A8
	static BOOL IS_PLAYER_PRESSING_HORN(Player player) { return invoke<BOOL>(0xED1D1662, player); } // 0xED1D1662
	static void SET_PLAYER_CONTROL(Player playerId, BOOL Toggle, int possiblyFlags) { invoke<Void>(0xD17AFCD8, playerId, Toggle, possiblyFlags); } // 0xD17AFCD8
	static int GET_PLAYER_WANTED_LEVEL(Player player) { return invoke<int>(0xBDCDD163, player); } // 0xBDCDD163
	static void SET_MAX_WANTED_LEVEL(int maxWantedLevel) { invoke<Void>(0x665A06F5, maxWantedLevel); } // 0x665A06F5
	static void SET_POLICE_RADAR_BLIPS(BOOL Toggle) { invoke<Void>(0x8E114B10, Toggle); } // 0x8E114B10
	static void SET_POLICE_IGNORE_PLAYER(Player player, BOOL Toggle) { invoke<Void>(0xE6DE71B7, player, Toggle); } // 0xE6DE71B7
	static BOOL IS_PLAYER_PLAYING(Player player) { return invoke<BOOL>(0xE15D777F, player); } // 0xE15D777F
	static void SET_EVERYONE_IGNORE_PLAYER(Player player, BOOL Toggle) { invoke<Void>(0xC915285E, player, Toggle); } // 0xC915285E
	static void SET_ALL_RANDOM_PEDS_FLEE(Player player, int p1) { invoke<Void>(0x49EAE968, player, p1); } // 0x49EAE968
	static void SET_ALL_RANDOM_PEDS_FLEE_THIS_FRAME(Player player) { invoke<Void>(0xBF974891, player); } // 0xBF974891
	static void _0x274631FE(Player Player, BOOL Toggle) { invoke<Void>(0x274631FE, Player, Toggle); } // 0x274631FE
	static void _0x02DF7AF4(Any p0) { invoke<Void>(0x02DF7AF4, p0); } // 0x02DF7AF4
	static void SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(int playerIndex, BOOL p1) { invoke<Void>(0xA3D675ED, playerIndex, p1); } // 0xA3D675ED
	static void SET_WANTED_LEVEL_MULTIPLIER(float Multiplier) { invoke<Void>(0x1359292F, Multiplier); } // 0x1359292F
	static void SET_WANTED_LEVEL_DIFFICULTY(Player player, float difficulty) { invoke<Void>(0xB552626C, player, difficulty); } // 0xB552626C
	static void RESET_WANTED_LEVEL_DIFFICULTY(Player player) { invoke<Void>(0xA64C378D, player); } // 0xA64C378D
	static void START_FIRING_AMNESTY(Any p0) { invoke<Void>(0x5F8A22A6, p0); } // 0x5F8A22A6
	static void REPORT_CRIME(Player player, int p0, int p1) { invoke<Void>(0xD8EB3A44, player, p0, p1); } // 0xD8EB3A44
	static void _0x59B5C2A2(Any p0, Any p1) { invoke<Void>(0x59B5C2A2, p0, p1); } // 0x59B5C2A2
	static void _0x6B34A160(Any p0) { invoke<Void>(0x6B34A160, p0); } // 0x6B34A160
	static void _0xB9FB142F(Any p0) { invoke<Void>(0xB9FB142F, p0); } // 0xB9FB142F
	static void _0x85725848(Any p0) { invoke<Void>(0x85725848, p0); } // 0x85725848
	static void _0x3A7E5FB6(float* p0f) { invoke<Void>(0x3A7E5FB6, p0f); } // 0x3A7E5FB6
	static void _0xD15C4B1C(Any p0) { invoke<Void>(0xD15C4B1C, p0); } // 0xD15C4B1C
	static void _0xBF6993C7(Any p0) { invoke<Void>(0xBF6993C7, p0); } // 0xBF6993C7
	static void _0x47CAB814() { invoke<Void>(0x47CAB814); } // 0x47CAB814
	static BOOL CAN_PLAYER_START_MISSION(Any p0) { return invoke<BOOL>(0x39E3CB3F, p0); } // 0x39E3CB3F
	static BOOL IS_PLAYER_READY_FOR_CUTSCENE(Any p0) { return invoke<BOOL>(0xBB77E9CD, p0); } // 0xBB77E9CD
	static BOOL IS_PLAYER_TARGETTING_ENTITY(Player Player, Entity Entity) { return invoke<BOOL>(0xF3240B77, Player, Entity); } // 0xF3240B77
	static Any GET_PLAYER_TARGET_ENTITY(Player player, Entity* entity) { return invoke<Any>(0xF6AAA2D7, player, entity); } // 0xF6AAA2D7
	static BOOL IS_PLAYER_FREE_AIMING(Player player) { return invoke<BOOL>(0x1DEC67B7, player); } // 0x1DEC67B7
	static BOOL IS_PLAYER_FREE_AIMING_AT_ENTITY(Player player, Entity entity) { return invoke<BOOL>(0x7D80EEAA, player, entity); } // 0x7D80EEAA
	static BOOL _GET_AIMED_ENTITY(Player player, Entity* entity) { return invoke<BOOL>(0x8866D9D0, player, entity); } // 0x8866D9D0
	static void _0x74D42C03(Any p0, Any p1) { invoke<Void>(0x74D42C03, p0, p1); } // 0x74D42C03
	static void SET_PLAYER_CAN_DO_DRIVE_BY(Any p0, Any p1) { invoke<Void>(0xF4D99685, p0, p1); } // 0xF4D99685
	static void SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(Any p0, Any p1) { invoke<Void>(0x71B305BB, p0, p1); } // 0x71B305BB
	static void SET_PLAYER_CAN_USE_COVER(Any p0, Any p1) { invoke<Void>(0x13CAFAFA, p0, p1); } // 0x13CAFAFA
	static int GET_MAX_WANTED_LEVEL() { return invoke<int>(0x457F1E44); } // 0x457F1E44
	static BOOL IS_PLAYER_TARGETTING_ANYTHING(Player player) { return invoke<BOOL>(0x456DB50D, player); } // 0x456DB50D
	static void SET_PLAYER_SPRINT(Any p0, Any p1) { invoke<Void>(0x7DD7900C, p0, p1); } // 0x7DD7900C
	static void RESET_PLAYER_STAMINA(Any Player) { invoke<Void>(0xC0445A9C, Player); } // 0xC0445A9C
	static void RESTORE_PLAYER_STAMINA(Any p0, Any p1) { invoke<Void>(0x62A93608, p0, p1); } // 0x62A93608
	static Any _0x47017C90(Any p0) { return invoke<Any>(0x47017C90, p0); } // 0x47017C90
	static Any GET_PLAYER_SPRINT_TIME_REMAINING(Any p0) { return invoke<Any>(0x40E80543, p0); } // 0x40E80543
	static Any GET_PLAYER_UNDERWATER_TIME_REMAINING(Any p0) { return invoke<Any>(0x1317125A, p0); } // 0x1317125A
	static int GET_PLAYER_GROUP(Player Player) { return invoke<int>(0xA5EDCDE8, Player); } // 0xA5EDCDE8
	static Any GET_PLAYER_MAX_ARMOUR(Player Player) { return invoke<Any>(0x02A50657, Player); } // 0x02A50657
	static BOOL IS_PLAYER_CONTROL_ON(Player Player) { return invoke<BOOL>(0x618857F2, Player); } // 0x618857F2
	static BOOL IS_PLAYER_SCRIPT_CONTROL_ON(Any p0) { return invoke<BOOL>(0x61B00A84, p0); } // 0x61B00A84
	static BOOL IS_PLAYER_CLIMBING(Any p0) { return invoke<BOOL>(0x4A9E9AE0, p0); } // 0x4A9E9AE0
	static BOOL IS_PLAYER_BEING_ARRESTED(Any p0, Any p1) { return invoke<BOOL>(0x7F6A60D3, p0, p1); } // 0x7F6A60D3
	static void _0x453C7CAB(Any p0) { invoke<Void>(0x453C7CAB, p0); } // 0x453C7CAB
	static Any GET_PLAYERS_LAST_VEHICLE() { return invoke<Any>(0xE2757AC1); } // 0xE2757AC1
	static Any GET_PLAYER_INDEX() { return invoke<Any>(0x309BBDC1); } // 0x309BBDC1
	static Any INT_TO_PLAYERINDEX(Any p0) { return invoke<Any>(0x98DD98F1, p0); } // 0x98DD98F1
	static Any _0x98F3B274(Any p0) { return invoke<Any>(0x98F3B274, p0); } // 0x98F3B274
	static Any GET_TIME_SINCE_PLAYER_HIT_VEHICLE(Any p0) { return invoke<Any>(0x6E9B8B9E, p0); } // 0x6E9B8B9E
	static Any GET_TIME_SINCE_PLAYER_HIT_PED(Any p0) { return invoke<Any>(0xB6209195, p0); } // 0xB6209195
	static Any GET_TIME_SINCE_PLAYER_DROVE_ON_PAVEMENT(Any p0) { return invoke<Any>(0x8836E732, p0); } // 0x8836E732
	static float GET_TIME_SINCE_PLAYER_DROVE_AGAINST_TRAFFIC(float time) { return invoke<float>(0x9F27D00E, time); } // 0x9F27D00E
	static BOOL IS_PLAYER_FREE_FOR_AMBIENT_TASK(Any p0) { return invoke<BOOL>(0x85C7E232, p0); } // 0x85C7E232
	static Any PLAYER_ID() { return invoke<Any>(0x8AEA886C); } // 0x8AEA886C
	static Any PLAYER_PED_ID() { return invoke<Any>(0xFA92E226); } // 0xFA92E226
	static Any _0x8DD5B838() { return invoke<Any>(0x8DD5B838); } // 0x8DD5B838
	static Any _0x4B37333C(Any p0) { return invoke<Any>(0x4B37333C, p0); } // 0x4B37333C
	static void FORCE_CLEANUP(Any p0) { invoke<Void>(0xFDAAEA2B, p0); } // 0xFDAAEA2B
	static void _0x04256C73(Any p0, Any p1) { invoke<Void>(0x04256C73, p0, p1); } // 0x04256C73
	static void _0x882D3EB3(Any p0, Any p1) { invoke<Void>(0x882D3EB3, p0, p1); } // 0x882D3EB3
	static Any _0x39AA9FC8() { return invoke<Any>(0x39AA9FC8); } // 0x39AA9FC8
	static void SET_PLAYER_MAY_ONLY_ENTER_THIS_VEHICLE(Any p0, Any p1) { invoke<Void>(0xA454DD29, p0, p1); } // 0xA454DD29
	static void _0xAF7AFCC4(Any p0) { invoke<Void>(0xAF7AFCC4, p0); } // 0xAF7AFCC4
	static Any GIVE_ACHIEVEMENT_TO_PLAYER(int achievement) { return invoke<Any>(0x822BC992, achievement); } // 0x822BC992
	static BOOL HAS_ACHIEVEMENT_BEEN_PASSED(int achievement) { return invoke<BOOL>(0x136A5BE9, achievement); } // 0x136A5BE9
	static BOOL IS_PLAYER_ONLINE() { return invoke<BOOL>(0x9FAB6729); } // 0x9FAB6729
	static BOOL IS_PLAYER_LOGGING_IN_NP() { return invoke<BOOL>(0x8F72FAD0); } // 0x8F72FAD0
	static void DISPLAY_SYSTEM_SIGNIN_UI(Any p0) { invoke<Void>(0x4264CED2, p0); } // 0x4264CED2
	static BOOL IS_SYSTEM_UI_BEING_DISPLAYED() { return invoke<BOOL>(0xE495B6DA); } // 0xE495B6DA
	static void SET_PLAYER_INVINCIBLE(Player player, BOOL toggle) { invoke<Void>(0xDFB9A2A2, player, toggle); } // 0xDFB9A2A2
	static Any GET_PLAYER_INVINCIBLE(Any p0) { return invoke<Any>(0x680C90EE, p0); } // 0x680C90EE
	static void _0x00563E0D(Any p0, Any p1) { invoke<Void>(0x00563E0D, p0, p1); } // 0x00563E0D
	static void REMOVE_PLAYER_HELMET(Player player, BOOL p2) { invoke<Void>(0x6255F3B4, player, p2); } // 0x6255F3B4
	static void GIVE_PLAYER_RAGDOLL_CONTROL(Any p0, Any p1) { invoke<Void>(0xC7B4D7AC, p0, p1); } // 0xC7B4D7AC
	static void SET_PLAYER_LOCKON(Any p0, Any p1) { invoke<Void>(0x0B270E0F, p0, p1); } // 0x0B270E0F
	static void SET_PLAYER_TARGETING_MODE(Any Player) { invoke<Void>(0x61CAE253, Player); } // 0x61CAE253
	static void CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_PED(Any p0) { invoke<Void>(0x1D31CBBD, p0); } // 0x1D31CBBD
	static BOOL HAS_PLAYER_DAMAGED_AT_LEAST_ONE_PED(Any p0) { return invoke<BOOL>(0x14F52453, p0); } // 0x14F52453
	static void _0x7E3BFBC5(Any p0) { invoke<Void>(0x7E3BFBC5, p0); } // 0x7E3BFBC5
	static Any _0xA3707DFC(Any p0) { return invoke<Any>(0xA3707DFC, p0); } // 0xA3707DFC
	static void SET_AIR_DRAG_MULTIPLIER_FOR_PLAYERS_VEHICLE(Any p0, Any p1) { invoke<Void>(0xF20F72E5, p0, p1); } // 0xF20F72E5
	static void _0xB986FF47(Any p0, Any p1) { invoke<Void>(0xB986FF47, p0, p1); } // 0xB986FF47
	static void _0x825423C2(Any p0, float p1) { invoke<Void>(0x825423C2, p0, p1); } // 0x825423C2
	static Any GET_TIME_SINCE_LAST_ARREST() { return invoke<Any>(0x62824EF4); } // 0x62824EF4
	static Any GET_TIME_SINCE_LAST_DEATH() { return invoke<Any>(0x24BC5AC0); } // 0x24BC5AC0
	static void ASSISTED_MOVEMENT_CLOSE_ROUTE() { invoke<Void>(0xF23277F3); } // 0xF23277F3
	static void ASSISTED_MOVEMENT_FLUSH_ROUTE() { invoke<Void>(0xD04568B9); } // 0xD04568B9
	static void SET_PLAYER_FORCED_AIM(Player p0, BOOL p1) { invoke<Void>(0x94E42E2E, p0, p1); } // 0x94E42E2E
	static void SET_PLAYER_FORCED_ZOOM(Any p0, Any p1) { invoke<Void>(0xB0C576CB, p0, p1); } // 0xB0C576CB
	static void _0x374F42F0(Any p0, Any p1) { invoke<Void>(0x374F42F0, p0, p1); } // 0x374F42F0
	static void DISABLE_PLAYER_FIRING(Player Player, BOOL Toggle) { invoke<Void>(0x30CB28CB, Player, Toggle); } // 0x30CB28CB
	static void _0xCCD937E7(Any p0, Any p1) { invoke<Void>(0xCCD937E7, p0, p1); } // 0xCCD937E7
	static void SET_PLAYER_MAX_ARMOUR(Player Player, BOOL Toggle) { invoke<Void>(0xC6C3C53B, Player, Toggle); } // 0xC6C3C53B
	static void SPECIAL_ABILITY_DEACTIVATE(Any p0) { invoke<Void>(0x80C2AB09, p0); } // 0x80C2AB09
	static void _0x0751908A(Any p0) { invoke<Void>(0x0751908A, p0); } // 0x0751908A
	static void SPECIAL_ABILITY_RESET(Any p0) { invoke<Void>(0xA7D8BCD3, p0); } // 0xA7D8BCD3
	static void _0x4136829A(Any p0) { invoke<Void>(0x4136829A, p0); } // 0x4136829A
	static void _0x6F463F56(Any p0, Any p1, Any p2) { invoke<Void>(0x6F463F56, p0, p1, p2); } // 0x6F463F56
	static void _0xAB55D8F3(Any p0, Any p1, Any p2) { invoke<Void>(0xAB55D8F3, p0, p1, p2); } // 0xAB55D8F3
	static void _0xF440C04D(Any p0, Any p1, Any p2) { invoke<Void>(0xF440C04D, p0, p1, p2); } // 0xF440C04D
	static void _0x5FEE98A2(Any p0, Any p1) { invoke<Void>(0x5FEE98A2, p0, p1); } // 0x5FEE98A2
	static void _0x72429998(Any p0, Any p1, Any p2) { invoke<Void>(0x72429998, p0, p1, p2); } // 0x72429998
	static void RESET_SPECIAL_ABILITY_CONTROLS_CINEMATIC(Any p0, Any p1, Any p2) { invoke<Void>(0x8C7E68C1, p0, p1, p2); } // 0x8C7E68C1
	static void _0xB71589DA(Any p0, Any p1) { invoke<Void>(0xB71589DA, p0, p1); } // 0xB71589DA
	static void _0x9F80F6DF(Any p0, Any p1) { invoke<Void>(0x9F80F6DF, p0, p1); } // 0x9F80F6DF
	static void SPECIAL_ABILITY_LOCK(Any p0) { invoke<Void>(0x1B7BB388, p0); } // 0x1B7BB388
	static void SPECIAL_ABILITY_UNLOCK(Any p0) { invoke<Void>(0x1FDB2919, p0); } // 0x1FDB2919
	static BOOL IS_SPECIAL_ABILITY_UNLOCKED(Any p0) { return invoke<BOOL>(0xC9C75E82, p0); } // 0xC9C75E82
	static BOOL IS_SPECIAL_ABILITY_ACTIVE(Any p0) { return invoke<BOOL>(0x1B17E334, p0); } // 0x1B17E334
	static BOOL IS_SPECIAL_ABILITY_METER_FULL(Any p0) { return invoke<BOOL>(0x2E19D7F6, p0); } // 0x2E19D7F6
	static void ENABLE_SPECIAL_ABILITY(Any p0, Any p1) { invoke<Void>(0xC86C1B4E, p0, p1); } // 0xC86C1B4E
	static BOOL IS_SPECIAL_ABILITY_ENABLED(Any p0) { return invoke<BOOL>(0xC01238CC, p0); } // 0xC01238CC
	static void SET_SPECIAL_ABILITY_MULTIPLIER(Any p0) { invoke<Void>(0xFF1BC556, p0); } // 0xFF1BC556
	static void _0x5D0FE25B(Any p0) { invoke<Void>(0x5D0FE25B, p0); } // 0x5D0FE25B
	static Any _0x46E7E31D(Any p0) { return invoke<Any>(0x46E7E31D, p0); } // 0x46E7E31D
	static Any _0x1E359CC8(Any p0, Any p1) { return invoke<Any>(0x1E359CC8, p0, p1); } // 0x1E359CC8
	static Any _0x8CB53C9F(Any p0, Any p1) { return invoke<Any>(0x8CB53C9F, p0, p1); } // 0x8CB53C9F
	static void START_PLAYER_TELEPORT(Any p0, float p1, float p2, float p3, float p4, Any p5, Any p6, Any p7) { invoke<Void>(0xC552E06C, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xC552E06C
	static void STOP_PLAYER_TELEPORT() { invoke<Void>(0x86AB8DBB); } // 0x86AB8DBB
	static BOOL IS_PLAYER_TELEPORT_ACTIVE() { return invoke<BOOL>(0x3A11D118); } // 0x3A11D118
	static float GET_PLAYER_CURRENT_STEALTH_NOISE(Vehicle* p0) { return invoke<float>(0xC3B02362, p0); } // 0xC3B02362
	static void _0x45514731(Any p0, Any p1) { invoke<Void>(0x45514731, p0, p1); } // 0x45514731
	static void SET_PLAYER_WEAPON_DAMAGE_MODIFIER(Player player, float DamageAmount) { invoke<Void>(0xB02C2F39, player, DamageAmount); } // 0xB02C2F39
	static void _0xAE446344(Player player, float multiplier) { invoke<Void>(0xAE446344, player, multiplier); } // 0xAE446344
	static void _0x362E69AD(Any p0, Any p1) { invoke<Void>(0x362E69AD, p0, p1); } // 0x362E69AD
	static void _0x9F3D577F(Any p0, Any p1) { invoke<Void>(0x9F3D577F, p0, p1); } // 0x9F3D577F
	static void SET_PLAYER_VEHICLE_DAMAGE_MODIFIER(Player Player, float DamageAmount) { invoke<Void>(0x823ECA63, Player, DamageAmount); } // 0x823ECA63
	static void _0xA16626C7(Any p0, Any p1) { invoke<Void>(0xA16626C7, p0, p1); } // 0xA16626C7
	static void SET_PLAYER_PARACHUTE_TINT_INDEX(Any p0, Any p1) { invoke<Void>(0x8EA12EDB, p0, p1); } // 0x8EA12EDB
	static void GET_PLAYER_PARACHUTE_TINT_INDEX(Any p0, Any p1) { invoke<Void>(0x432B0509, p0, p1); } // 0x432B0509
	static void _0x70689638(Any p0, Any p1) { invoke<Void>(0x70689638, p0, p1); } // 0x70689638
	static void _0x77B8EF01(Any p0, Any p1) { invoke<Void>(0x77B8EF01, p0, p1); } // 0x77B8EF01
	static void SET_PLAYER_PARACHUTE_PACK_TINT_INDEX(Any p0, Any p1) { invoke<Void>(0xD79D5D1B, p0, p1); } // 0xD79D5D1B
	static void _0x4E418E13(Any p0, Any p1) { invoke<Void>(0x4E418E13, p0, p1); } // 0x4E418E13
	static void _0xA3E4798E(Any p0) { invoke<Void>(0xA3E4798E, p0); } // 0xA3E4798E
	static Any _0x30DA1DA1(Any p0) { return invoke<Any>(0x30DA1DA1, p0); } // 0x30DA1DA1
	static void _0x832DEB7A(Any p0, Any p1) { invoke<Void>(0x832DEB7A, p0, p1); } // 0x832DEB7A
	static void _0x14FE9264(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x14FE9264, p0, p1, p2, p3); } // 0x14FE9264
	static void _0xF66E5CDD(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xF66E5CDD, p0, p1, p2, p3); } // 0xF66E5CDD
	static void _0x725C6174(Any p0, Any p1) { invoke<Void>(0x725C6174, p0, p1); } // 0x725C6174
	static void _0xF8A62EFC(Any p0, Any p1) { invoke<Void>(0xF8A62EFC, p0, p1); } // 0xF8A62EFC
	static void SET_PLAYER_NOISE_MULTIPLIER(Player Player, float Multipliyer) { invoke<Void>(0x15786DD1, Player, Multipliyer); } // 0x15786DD1
	static void _0x8D2D89C4(Any p0, Any p1) { invoke<Void>(0x8D2D89C4, p0, p1); } // 0x8D2D89C4
	static Any _0x1C70B2EB(Any p0, Any p1) { return invoke<Any>(0x1C70B2EB, p0, p1); } // 0x1C70B2EB
	static void SIMULATE_PLAYER_INPUT_GAIT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x0D77CC34, p0, p1, p2, p3, p4, p5); } // 0x0D77CC34
	static void RESET_PLAYER_INPUT_GAIT(Any p0) { invoke<Void>(0x4A701EE1, p0); } // 0x4A701EE1
	static void _0xA97C2059(Any p0, Any p1) { invoke<Void>(0xA97C2059, p0, p1); } // 0xA97C2059
	static void _0xA25D767E(Any p0, Any p1) { invoke<Void>(0xA25D767E, p0, p1); } // 0xA25D767E
	static void _0x3D26105F(Any p0, Any p1) { invoke<Void>(0x3D26105F, p0, p1); } // 0x3D26105F
	static Any _0x1D371529(Any p0) { return invoke<Any>(0x1D371529, p0); } // 0x1D371529
	static void _0xE30A64DC(Any p0) { invoke<Void>(0xE30A64DC, p0); } // 0xE30A64DC
	static void SET_PLAYER_SIMULATE_AIMING(Any p0, Any p1) { invoke<Void>(0xF1E0CAFC, p0, p1); } // 0xF1E0CAFC
	static void _0xF7A0F00F(Any p0, Any p1) { invoke<Void>(0xF7A0F00F, p0, p1); } // 0xF7A0F00F
	static void _0xB8209F16(Any p0) { invoke<Void>(0xB8209F16, p0); } // 0xB8209F16
	static void _0x8D9FD4D1(Any p0) { invoke<Void>(0x8D9FD4D1, p0); } // 0x8D9FD4D1
	static void _0xECD12E60(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0xECD12E60, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xECD12E60
	static void _0x96100EA4() { invoke<Void>(0x96100EA4); } // 0x96100EA4
	static Any _0x4A01B76A(Any p0) { return invoke<Any>(0x4A01B76A, p0); } // 0x4A01B76A
	static Any _0x013B4F72(Any p0) { return invoke<Any>(0x013B4F72, p0); } // 0x013B4F72
	static Any _0x9DF75B2A(Any p0, Any p1, Any p2) { return invoke<Any>(0x9DF75B2A, p0, p1, p2); } // 0x9DF75B2A
	static void _0x64DDB07D(Any p0, Any p1, Any p2) { invoke<Void>(0x64DDB07D, p0, p1, p2); } // 0x64DDB07D
	static void _0xA97C2F6C() { invoke<Void>(0xA97C2F6C); } // 0xA97C2F6C
	static BOOL IS_PLAYER_RIDING_TRAIN(Player Player) { return invoke<BOOL>(0x9765E71D, Player); } // 0x9765E71D
	static Any _0xFEA40B6C(Any p0) { return invoke<Any>(0xFEA40B6C, p0); } // 0xFEA40B6C
	static void _0xAD8383FA(Any p0, Any p1) { invoke<Void>(0xAD8383FA, p0, p1); } // 0xAD8383FA
	static void _0x9254249D(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x9254249D, p0, p1, p2, p3, p4); } // 0x9254249D
	static void _0xFD60F5AB(Any p0) { invoke<Void>(0xFD60F5AB, p0); } // 0xFD60F5AB
	static void _0x5D382498(Any p0, Any p1) { invoke<Void>(0x5D382498, p0, p1); } // 0x5D382498
	static void _0x6FF034BB(Any p0) { invoke<Void>(0x6FF034BB, p0); } // 0x6FF034BB
	static void _0xA877FF5E(Any p0, Any p1) { invoke<Void>(0xA877FF5E, p0, p1); } // 0xA877FF5E
	static void _0xBB62AAC5(Any p0) { invoke<Void>(0xBB62AAC5, p0); } // 0xBB62AAC5
	static void _0x8C6E611D(Any p0) { invoke<Void>(0x8C6E611D, p0); } // 0x8C6E611D
	static void _0x2849D4B2(Any p0) { invoke<Void>(0x2849D4B2, p0); } // 0x2849D4B2
}

namespace ENTITY
{
	static BOOL DOES_ENTITY_EXIST(Entity entity) { return invoke<BOOL>(0x3AC90869, entity); } // 0x3AC90869
	static Any _0xACFEB3F9(Any p0, Any p1) { return invoke<Any>(0xACFEB3F9, p0, p1); } // 0xACFEB3F9
	static BOOL DOES_ENTITY_HAVE_DRAWABLE(Entity Entity) { return invoke<BOOL>(0xA5B33300, Entity); } // 0xA5B33300
	static BOOL DOES_ENTITY_HAVE_PHYSICS(Entity Entity) { return invoke<BOOL>(0x9BCD2979, Entity); } // 0x9BCD2979
	static BOOL HAS_ENTITY_ANIM_FINISHED(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0x1D9CAB92, p0, p1, p2, p3); } // 0x1D9CAB92
	static BOOL HAS_ENTITY_BEEN_DAMAGED_BY_ANY_OBJECT(Entity Entity) { return invoke<BOOL>(0x6B74582E, Entity); } // 0x6B74582E
	static BOOL HAS_ENTITY_BEEN_DAMAGED_BY_ANY_PED(Entity Entity) { return invoke<BOOL>(0x53FD4A25, Entity); } // 0x53FD4A25
	static BOOL HAS_ENTITY_BEEN_DAMAGED_BY_ANY_VEHICLE(Entity Entity) { return invoke<BOOL>(0x878C2CE0, Entity); } // 0x878C2CE0
	static BOOL HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(Any p0, Any p1, Any p2) { return invoke<BOOL>(0x07FC77E0, p0, p1, p2); } // 0x07FC77E0
	static BOOL HAS_ENTITY_CLEAR_LOS_TO_ENTITY(Any p0, Any p1, Any p2) { return invoke<BOOL>(0x53576FA7, p0, p1, p2); } // 0x53576FA7
	static BOOL HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(Any p0, Any p1) { return invoke<BOOL>(0x210D87C8, p0, p1); } // 0x210D87C8
	static BOOL HAS_ENTITY_COLLIDED_WITH_ANYTHING(Entity Entity) { return invoke<BOOL>(0x662A2F41, Entity); } // 0x662A2F41
	static Any _0xC0E3AA47(Any p0) { return invoke<Any>(0xC0E3AA47, p0); } // 0xC0E3AA47
	static Vector3 _0xAB415C07(Any p0) { return invoke<Vector3>(0xAB415C07, p0); } // 0xAB415C07
	static void _0x58D9775F(Any p0) { invoke<Void>(0x58D9775F, p0); } // 0x58D9775F
	static Any GET_ENTITY_ANIM_CURRENT_TIME(Any p0, Any p1, Any p2) { return invoke<Any>(0x83943F41, p0, p1, p2); } // 0x83943F41
	static Any GET_ENTITY_ANIM_TOTAL_TIME(Any p0, Any p1, Any p2) { return invoke<Any>(0x433A9D18, p0, p1, p2); } // 0x433A9D18
	static Entity GET_ENTITY_ATTACHED_TO(Entity Entity) { return invoke<Any>(0xFE1589F9, Entity); } // 0xFE1589F9
	static Vector3 GET_ENTITY_COORDS(Entity entity, BOOL unkBool) { return invoke<Vector3>(0x1647F1CB, entity, unkBool); } // 0x1647F1CB
	static Vector3 GET_ENTITY_FORWARD_VECTOR(Entity entity) { return invoke<Vector3>(0x84DCECBF, entity); } // 0x84DCECBF
	static Any GET_ENTITY_FORWARD_X(Entity Entity) { return invoke<Any>(0x49FAE914, Entity); } // 0x49FAE914
	static Any GET_ENTITY_FORWARD_Y(Entity Entity) { return invoke<Any>(0x9E2F917C, Entity); } // 0x9E2F917C
	static float GET_ENTITY_HEADING(Entity Entity) { return invoke<float>(0x972CC383, Entity); } // 0x972CC383
	static Any GET_ENTITY_HEALTH(Entity Entity) { return invoke<Any>(0x8E3222B7, Entity); } // 0x8E3222B7
	static Any GET_ENTITY_MAX_HEALTH(Entity Entity) { return invoke<Any>(0xC7AE6AA1, Entity); } // 0xC7AE6AA1
	static void SET_ENTITY_MAX_HEALTH(Entity Entity, BOOL Toggle) { invoke<Void>(0x96F84DF8, Entity, Toggle); } // 0x96F84DF8
	static Any GET_ENTITY_HEIGHT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0xEE443481, p0, p1, p2, p3, p4, p5); } // 0xEE443481
	static Any GET_ENTITY_HEIGHT_ABOVE_GROUND(Entity Entity) { return invoke<Any>(0x57F56A4D, Entity); } // 0x57F56A4D
	static void GET_ENTITY_MATRIX(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xEB9EB001, p0, p1, p2, p3, p4); } // 0xEB9EB001
	static Any GET_ENTITY_MODEL(Entity Entity) { return invoke<Any>(0xDAFCB3EC, Entity); } // 0xDAFCB3EC
	static Vector3 GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(Any p0, float p1, float p2, float p3) { return invoke<Vector3>(0x6477EC9E, p0, p1, p2, p3); } // 0x6477EC9E
	static Vector3 GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Entity Entity, float xCoord, float yCoord, float zCoord) { return invoke<Vector3>(0xABCF043A, Entity, xCoord, yCoord, zCoord); } // 0xABCF043A
	static float GET_ENTITY_PITCH(Entity Entity) { return invoke<float>(0xFCE6ECE5, Entity); } // 0xFCE6ECE5
	static void GET_ENTITY_QUATERNION(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x5154EC90, p0, p1, p2, p3, p4); } // 0x5154EC90
	static float GET_ENTITY_ROLL(Entity Entity) { return invoke<float>(0x36610842, Entity); } // 0x36610842
	static Vector3 GET_ENTITY_ROTATION(Any p0, Any p1) { return invoke<Vector3>(0x8FF45B04, p0, p1); } // 0x8FF45B04
	static Vector3 GET_ENTITY_ROTATION_VELOCITY(Any p0) { return invoke<Vector3>(0x9BF8A73F, p0); } // 0x9BF8A73F
	static Any GET_ENTITY_SCRIPT(Any p0, Any p1) { return invoke<Any>(0xB7F70784, p0, p1); } // 0xB7F70784
	static float GET_ENTITY_SPEED(Entity entity) { return invoke<float>(0x9E1E4798, entity); } // 0x9E1E4798
	static Vector3 GET_ENTITY_SPEED_VECTOR(Any p0, Any p1) { return invoke<Vector3>(0x3ED2B997, p0, p1); } // 0x3ED2B997
	static Any GET_ENTITY_UPRIGHT_VALUE(Any p0) { return invoke<Any>(0xF4268190, p0); } // 0xF4268190
	static Vector3 GET_ENTITY_VELOCITY(Entity entity) { return invoke<Vector3>(0xC14C9B6B, entity); } // 0xC14C9B6B
	static Any _0xBC5A9C58(Any p0) { return invoke<Any>(0xBC5A9C58, p0); } // 0xBC5A9C58
	static Any _0xC46F74AC(Any p0) { return invoke<Any>(0xC46F74AC, p0); } // 0xC46F74AC
	static Any _0xC69CF43D(Any p0) { return invoke<Any>(0xC69CF43D, p0); } // 0xC69CF43D
	static Vector3 _0x7C6339DF(Any p0, Any p1) { return invoke<Vector3>(0x7C6339DF, p0, p1); } // 0x7C6339DF
	static Any GET_NEAREST_PLAYER_TO_ENTITY(Entity Entity) { return invoke<Any>(0xCE17FDEC, Entity); } // 0xCE17FDEC
	static Any _0xB1808F56(Any p0, Any p1) { return invoke<Any>(0xB1808F56, p0, p1); } // 0xB1808F56
	static int GET_ENTITY_TYPE(Entity Entity) { return invoke<int>(0x0B1BD08D, Entity); } // 0x0B1BD08D
	static BOOL IS_AN_ENTITY(Entity Entity) { return invoke<BOOL>(0xD4B9715A, Entity); } // 0xD4B9715A
	static BOOL IS_ENTITY_A_PED(Entity Entity) { return invoke<BOOL>(0x55D33EAB, Entity); } // 0x55D33EAB
	static BOOL IS_ENTITY_A_MISSION_ENTITY(Entity Entity) { return invoke<BOOL>(0x2632E124, Entity); } // 0x2632E124
	static BOOL IS_ENTITY_A_VEHICLE(Entity Entity) { return invoke<BOOL>(0xBE800B01, Entity); } // 0xBE800B01
	static BOOL IS_ENTITY_AN_OBJECT(Any p0) { return invoke<BOOL>(0x3F52E561, p0); } // 0x3F52E561
	static BOOL IS_ENTITY_AT_COORD(Entity entity, float x, float y, float z, float xSize, float ySize, float zSize, int p7, int p8, int p9) { return invoke<BOOL>(0xD749B606, entity, x, y, z, xSize, ySize, zSize, p7, p8, p9); } // 0xD749B606
	static BOOL IS_ENTITY_AT_ENTITY(Entity entity1, Entity entity2, float xSize, float ySize, float zSize, int p5, int p6, int p7) { return invoke<BOOL>(0xDABDCB52, entity1, entity2, xSize, ySize, zSize, p5, p6, p7); } // 0xDABDCB52
	static BOOL IS_ENTITY_ATTACHED(Any p0) { return invoke<BOOL>(0xEC1479D5, p0); } // 0xEC1479D5
	static BOOL IS_ENTITY_ATTACHED_TO_ANY_OBJECT(Any p0) { return invoke<BOOL>(0x0B5DE340, p0); } // 0x0B5DE340
	static BOOL IS_ENTITY_ATTACHED_TO_ANY_PED(Any p0) { return invoke<BOOL>(0x9D7A609C, p0); } // 0x9D7A609C
	static BOOL IS_ENTITY_ATTACHED_TO_ANY_VEHICLE(Any p0) { return invoke<BOOL>(0xDE5C995E, p0); } // 0xDE5C995E
	static BOOL IS_ENTITY_ATTACHED_TO_ENTITY(Any p0, Any p1) { return invoke<BOOL>(0xB0ABFEA8, p0, p1); } // 0xB0ABFEA8
	static BOOL IS_ENTITY_DEAD(Entity entity) { return invoke<BOOL>(0xB6F7CBAC, entity); } // 0xB6F7CBAC
	static BOOL IS_ENTITY_IN_AIR(Entity entity) { return invoke<BOOL>(0xA4157987, entity); } // 0xA4157987
	static BOOL IS_ENTITY_IN_ANGLED_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return invoke<BOOL>(0x883622FA, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x883622FA
	static BOOL IS_ENTITY_IN_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<BOOL>(0x8C2DFA9D, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x8C2DFA9D
	static BOOL IS_ENTITY_IN_ZONE(Any p0, Any p1) { return invoke<BOOL>(0x45C82B21, p0, p1); } // 0x45C82B21
	static BOOL IS_ENTITY_IN_WATER(Entity entity) { return invoke<BOOL>(0x4C3C2508, entity); } // 0x4C3C2508
	static Any _0x0170F68C(Any p0) { return invoke<Any>(0x0170F68C, p0); } // 0x0170F68C
	static void _0x40C84A74(Any p0, Any p1) { invoke<Void>(0x40C84A74, p0, p1); } // 0x40C84A74
	static BOOL IS_ENTITY_ON_SCREEN(Any p0) { return invoke<BOOL>(0xC1FEC5ED, p0); } // 0xC1FEC5ED
	static BOOL IS_ENTITY_PLAYING_ANIM(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0x0D130D34, p0, p1, p2, p3); } // 0x0D130D34
	static BOOL IS_ENTITY_STATIC(Any p0) { return invoke<BOOL>(0x928E12E9, p0); } // 0x928E12E9
	static BOOL IS_ENTITY_TOUCHING_ENTITY(Entity p0, Entity p1) { return invoke<BOOL>(0x6B931477, p0, p1); } // 0x6B931477
	static Any _0x307E7611(Any p0, Any p1) { return invoke<Any>(0x307E7611, p0, p1); } // 0x307E7611
	static BOOL IS_ENTITY_UPRIGHT(Any p0, Any p1) { return invoke<BOOL>(0x3BCDF4E1, p0, p1); } // 0x3BCDF4E1
	static BOOL IS_ENTITY_UPSIDEDOWN(Any p0) { return invoke<BOOL>(0x5ACAA48F, p0); } // 0x5ACAA48F
	static BOOL IS_ENTITY_VISIBLE(Entity entity) { return invoke<BOOL>(0x120B4ED5, entity); } // 0x120B4ED5
	static BOOL IS_ENTITY_VISIBLE_TO_SCRIPT(Any p0) { return invoke<BOOL>(0x5D240E9D, p0); } // 0x5D240E9D
	static BOOL IS_ENTITY_OCCLUDED(Any p0) { return invoke<BOOL>(0x46BC5B40, p0); } // 0x46BC5B40
	static Any _0xEA127CBC(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xEA127CBC, p0, p1, p2, p3, p4); } // 0xEA127CBC
	static BOOL IS_ENTITY_WAITING_FOR_WORLD_COLLISION(Any p0) { return invoke<BOOL>(0x00AB7A4A, p0); } // 0x00AB7A4A
	static void _0x28924E98(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0x28924E98, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x28924E98
	static void APPLY_FORCE_TO_ENTITY(Entity entity, BOOL p1, float Force_X, float Force_Y, float Force_Z, float Rot_X, float Rot_Y, float Rot_Z, BOOL p8, BOOL p9, BOOL p10, BOOL p11, int p12, BOOL p13) { invoke<Void>(0xC1C0855A, entity, p1, Force_X, Force_Y, Force_Z, Rot_X, Rot_Y, Rot_Z, p8, p9, p10, p11, p12, p13); } // 0xC1C0855A
	static void ATTACH_ENTITY_TO_ENTITY(Entity entity1, Entity entity2, int boneIndex, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, BOOL p9, BOOL useSoftPinning, BOOL collision, BOOL isPed, int vertexIndex, BOOL fixedRot) { invoke<Void>(0xEC024237, entity1,  entity2,boneIndex, xPos, yPos,  zPos, xRot, yRot, zRot, p9,  useSoftPinning, collision, isPed, vertexIndex, fixedRot); } // 0xEC024237
	static void ATTACH_ENTITY_TO_ENTITY_PHYSICALLY(Entity entity1, Entity entity2, float unknown1, float unknown2, float x1, float y1, float z1, float x2, float y2, float z2, float rot_x, float rot_y, float rot_z, Any unknown3, Any unknown4, Any unknown5, Any unknown6, Any unknown7, Any unknown8) { invoke<Void>(0x0547417F, entity1, entity2, unknown1, unknown2, x1, y1, z1, x2, y2, z2, rot_x, rot_y, rot_z, unknown3, unknown4, unknown5, unknown6, unknown7, unknown8); } // 0x0547417F
	static void _0x6909BA59(Any p0) { invoke<Void>(0x6909BA59, p0); } // 0x6909BA59
	static Any _0xE4ECAC22(Any p0, char *p1) { return invoke<Any>(0xE4ECAC22, p0, p1); } // 0xE4ECAC22
	static void CLEAR_ENTITY_LAST_DAMAGE_ENTITY(Entity entity) { invoke<Void>(0x2B83F43B, entity); } // 0x2B83F43B
	static void DELETE_ENTITY(Entity* EntityHandle, bool bypassOwnerCheck = false) { 
		if (bypassOwnerCheck)
			*(char*)0x10FAEBF = 0;
		invoke<Void>(0xFAA3D236, EntityHandle); 
		if (bypassOwnerCheck)
			*(char*)0x10FAEBF = 1;
	} // 0xFAA3D236
	static void DETACH_ENTITY(Any p0, Any p1, Any p2) { invoke<Void>(0xC8EFCB41, p0, p1, p2); } // 0xC8EFCB41
	static void FREEZE_ENTITY_POSITION(Entity entity, BOOL Toggle) { invoke<Void>(0x65C16D57, entity, Toggle); } // 0x65C16D57
	static void _0xD3850671(Any p0, Any p1) { invoke<Void>(0xD3850671, p0, p1); } // 0xD3850671
	static Any PLAY_ENTITY_ANIM(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<Any>(0x878753D5, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x878753D5
	static Any PLAY_SYNCHRONIZED_ENTITY_ANIM(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<Any>(0x012760AA, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x012760AA
	static Any _0xEB4CBA74(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { return invoke<Any>(0xEB4CBA74, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0xEB4CBA74
	static Any _0x7253D5B2(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x7253D5B2, p0, p1, p2, p3, p4, p5); } // 0x7253D5B2
	static Any STOP_ENTITY_ANIM(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xC4769830, p0, p1, p2, p3); } // 0xC4769830
	static Any STOP_SYNCHRONIZED_ENTITY_ANIM(Any p0, Any p1, Any p2) { return invoke<Any>(0xE27D2FC1, p0, p1, p2); } // 0xE27D2FC1
	static Any _0x66571CA0(Any p0, Any p1) { return invoke<Any>(0x66571CA0, p0, p1); } // 0x66571CA0
	static Any _0xC41DDA62(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xC41DDA62, p0, p1, p2, p3, p4); } // 0xC41DDA62
	static void SET_ENTITY_ANIM_CURRENT_TIME(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x99D90735, p0, p1, p2, p3); } // 0x99D90735
	static void SET_ENTITY_ANIM_SPEED(int p0, char* p1, char* p2, float p3) { invoke<Void>(0x3990C90A, p0, p1, p2, p3); } // 0x3990C90A
	static void SET_ENTITY_AS_MISSION_ENTITY(Entity entityHandle, BOOL value, BOOL p2) { invoke<Void>(0x5D1F9E0F, entityHandle, value, p2); } // 0x5D1F9E0F
	static void SET_ENTITY_AS_NO_LONGER_NEEDED(Entity* entityHandle) { invoke<Void>(0xADF2267C, entityHandle); } // 0xADF2267C
	static void SET_PED_AS_NO_LONGER_NEEDED(Ped* pedHandle) { invoke<Void>(0x9A388380, pedHandle); } // 0x9A388380
	static void SET_VEHICLE_AS_NO_LONGER_NEEDED(Vehicle* vehicleHandle) { invoke<Void>(0x9B0E10BE, vehicleHandle); } // 0x9B0E10BE
	static void SET_OBJECT_AS_NO_LONGER_NEEDED(Object* objectHandle) { invoke<Void>(0x3F6B949F, objectHandle); } // 0x3F6B949F
	static void SET_ENTITY_CAN_BE_DAMAGED(Entity Entity, BOOL Toggle) { invoke<Void>(0x60B6E744, Entity, Toggle); } // 0x60B6E744
	static void SET_ENTITY_CAN_BE_DAMAGED_BY_RELATIONSHIP_GROUP(Any p0, Any p1, Any p2) { invoke<Void>(0x34165B5D, p0, p1, p2); } // 0x34165B5D
	static void SET_ENTITY_CAN_BE_TARGETED_WITHOUT_LOS(Any p0, Any p1) { invoke<Void>(0x3B13797C, p0, p1); } // 0x3B13797C
	static void SET_ENTITY_COLLISION(Entity entity, BOOL p1, BOOL p2) { invoke<Void>(0x139FD37D, entity, p1, p2); } // 0x139FD37D
	static BOOL _0xCCF1E97BEFDAE480(Entity entity) { return invoke<BOOL>(0xE8C0C629, entity); } // 0xCCF1E97BEFDAE480
	static void SET_ENTITY_COORDS(Entity entity, float X, float Y, float Z, float XAxes, float YAxes, float ZAxes, BOOL unk) { invoke<Void>(0xDF70B41B, entity, X, Y, Z, XAxes, YAxes, ZAxes, unk); } // 0xDF70B41B
	static void SET_ENTITY_COORDS_NO_OFFSET(Entity entity, float xCoord, float yCoord, float zCoord, BOOL p4, BOOL p5, BOOL p6) { invoke<Void>(0x4C83DE8D, entity, xCoord, yCoord, zCoord, p4, p5, p6); } // 0x4C83DE8D
	static void SET_ENTITY_DYNAMIC(Entity entity, BOOL ToggleDynamics) { invoke<Void>(0x236F525B, entity, ToggleDynamics); } // 0x236F525B
	static void SET_ENTITY_HEADING(Entity entity, float Heading) { invoke<Void>(0xE0FF064D, entity, Heading); } // 0xE0FF064D
	static void SET_ENTITY_HEALTH(Entity entity, int Amount) { invoke<Void>(0xFBCD1831, entity, Amount); } // 0xFBCD1831
	static void SET_ENTITY_INVINCIBLE(Entity entity, BOOL Toggle) { invoke<Void>(0xC1213A21, entity, Toggle); } // 0xC1213A21
	static void SET_ENTITY_IS_TARGET_PRIORITY(Any p0, Any p1, Any p2) { invoke<Void>(0x9729EE32, p0, p1, p2); } // 0x9729EE32
	static void SET_ENTITY_LIGHTS(Any p0, Any p1) { invoke<Void>(0xE8FC85AF, p0, p1); } // 0xE8FC85AF
	static void SET_ENTITY_LOAD_COLLISION_FLAG(Entity entity, BOOL Toggle) { invoke<Void>(0xC52F295B, entity, Toggle); } // 0xC52F295B
	static Any _0x851687F9(Any p0) { return invoke<Any>(0x851687F9, p0); } // 0x851687F9
	static void SET_ENTITY_MAX_SPEED(Any p0, Any p1) { invoke<Void>(0x46AFFED3, p0, p1); } // 0x46AFFED3
	static void SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(Any p0, Any p1) { invoke<Void>(0x4B707F50, p0, p1); } // 0x4B707F50
	static void SET_ENTITY_ONLY_DAMAGED_BY_RELATIONSHIP_GROUP(Any p0, Any p1, Any p2) { invoke<Void>(0x202237E2, p0, p1, p2); } // 0x202237E2
	static void SET_ENTITY_PROOFS(Entity Entity, BOOL bulletProof, BOOL fireProof, BOOL explosionProof, BOOL collisionProof, BOOL meleeProof, Any p6, Any p7, Any p8) { invoke<Void>(0x7E9EAB66, Entity, bulletProof, fireProof, explosionProof, collisionProof, meleeProof, p6, p7, p8); } // 0x7E9EAB66
	static void SET_ENTITY_QUATERNION(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x83B6046F, p0, p1, p2, p3, p4); } // 0x83B6046F
	static void SET_ENTITY_RECORDS_COLLISIONS(Any p0, Any p1) { invoke<Void>(0x6B189A1A, p0, p1); } // 0x6B189A1A
	static void SET_ENTITY_ROTATION(Entity entity, float Pitch, float Roll, float Yaw, Any p4, Any p5) { invoke<Void>(0x0A345EFE, entity, Pitch, Roll, Yaw, p4, p5); } // 0x0A345EFE
	static void SET_ENTITY_VISIBLE(Entity entity, BOOL Toggle) { invoke<Void>(0xD043E8E1, entity, Toggle); } // 0xD043E8E1
	static void SET_ENTITY_VELOCITY(Entity entity, float xVel, float yVel, float zVel) { invoke<Void>(0xFF5A1988, entity, xVel, yVel, zVel); } // 0xFF5A1988
	static void SET_ENTITY_HAS_GRAVITY(Any p0, Any p1) { invoke<Void>(0xE2F262BF, p0, p1); } // 0xE2F262BF
	static void SET_ENTITY_LOD_DIST(Entity entity, int Distance) { invoke<Void>(0xD7ACC7AD, entity, Distance); } // 0xD7ACC7AD
	static Any _0x4DA3D51F(Any p0) { return invoke<Any>(0x4DA3D51F, p0); } // 0x4DA3D51F
	static void SET_ENTITY_ALPHA(Entity entity, int AlphaLVL, Any p2) { invoke<Void>(0xAE667CB0, entity, AlphaLVL, p2); } // 0xAE667CB0
	static Any GET_ENTITY_ALPHA(Entity entity) { return invoke<Any>(0x1560B017, entity); } // 0x1560B017
	static void RESET_ENTITY_ALPHA(Entity entity) { invoke<Void>(0x8A30761C, entity); } // 0x8A30761C
	static void _0xD8FF798A(Any p0, Any p1) { invoke<Void>(0xD8FF798A, p0, p1); } // 0xD8FF798A
	static void SET_ENTITY_RENDER_SCORCHED(Any p0, Any p1) { invoke<Void>(0xAAC9317B, p0, p1); } // 0xAAC9317B
	static void _0xC47F5B91(Any p0, Any p1) { invoke<Void>(0xC47F5B91, p0, p1); } // 0xC47F5B91
	static void CREATE_MODEL_SWAP(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x0BC12F9E, p0, p1, p2, p3, p4, p5, p6); } // 0x0BC12F9E
	static void REMOVE_MODEL_SWAP(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0xCE0AA8BC, p0, p1, p2, p3, p4, p5, p6); } // 0xCE0AA8BC
	static void CREATE_MODEL_HIDE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x7BD5CF2F, p0, p1, p2, p3, p4, p5); } // 0x7BD5CF2F
	static void _0x07AAF22C(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x07AAF22C, p0, p1, p2, p3, p4, p5); } // 0x07AAF22C
	static void REMOVE_MODEL_HIDE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x993DBC10, p0, p1, p2, p3, p4, p5); } // 0x993DBC10
	static void CREATE_FORCED_OBJECT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x335190A2, p0, p1, p2, p3, p4, p5); } // 0x335190A2
	static void REMOVE_FORCED_OBJECT(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xAED73ADD, p0, p1, p2, p3, p4); } // 0xAED73ADD
	static void SET_ENTITY_NO_COLLISION_ENTITY(Entity ent1, Entity ent2, BOOL toogle) { invoke<Void>(0x1E11BFE9, ent1, ent2, toogle); } // 0x1E11BFE9
	static void SET_ENTITY_MOTION_BLUR(Any p0, Any p1) { invoke<Void>(0xE90005B8, p0, p1); } // 0xE90005B8
	static void _0x44767B31(Any p0, Any p1) { invoke<Void>(0x44767B31, p0, p1); } // 0x44767B31
	static void _0xE224A6A5(Any p0, Any p1) { invoke<Void>(0xE224A6A5, p0, p1); } // 0xE224A6A5
}

namespace PED
{
	static Ped CREATE_PED(int type, Hash pedHash, float x, float y, float z, float heading, BOOL networkHandle, BOOL returnPEDHandle) { return invoke<Ped>(0x0389EF71, type, pedHash, x, y, z, heading, networkHandle, returnPEDHandle); } // 0x0389EF71
	static void DELETE_PED(Ped* ped) { invoke<Void>(0x13EFB9A0, ped); } // 0x13EFB9A0
	static Ped CLONE_PED(Ped Priest, float Heading, BOOL networkhandle, BOOL createpedhandle) { return invoke<Ped>(0x8C8A8D6E, Priest, Heading, networkhandle, createpedhandle); } // 0x8C8A8D6E
	static void _0xFC70EEC7(Ped GamerHandle, Ped* pedHandle) { invoke<Void>(0xFC70EEC7, GamerHandle, pedHandle); } // 0xFC70EEC7
	static BOOL IS_PED_IN_VEHICLE(Ped pedHandle, Vehicle vehicleHandle, BOOL atGetIn) { return invoke<BOOL>(0x7DA6BC83, pedHandle, vehicleHandle, atGetIn); } // 0x7DA6BC83
	static BOOL IS_PED_IN_MODEL(Ped ped, Hash vehicleModel) { return invoke<BOOL>(0xA6438D4B, ped, vehicleModel); } // 0xA6438D4B
	static BOOL IS_PED_IN_ANY_VEHICLE(Ped pedHandle, BOOL atGetIn) { return invoke<BOOL>(0x3B0171EE, pedHandle, atGetIn); } // 0x3B0171EE
	static BOOL IS_COP_PED_IN_AREA_3D(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<BOOL>(0xB98DB96B, p0, p1, p2, p3, p4, p5); } // 0xB98DB96B
	static BOOL IS_PED_INJURED(Ped ped) { return invoke<BOOL>(0x2530A087, ped); } // 0x2530A087
	static BOOL IS_PED_HURT(Any p0) { return invoke<BOOL>(0x69DFA0AF, p0); } // 0x69DFA0AF
	static BOOL IS_PED_FATALLY_INJURED(Ped ped) { return invoke<BOOL>(0xBADA0093, ped); } // 0xBADA0093
	static BOOL _IS_PED_DEAD(Ped pedHandle, BOOL p1) { return invoke<BOOL>(0xCBDB7739, pedHandle, p1); } // 0xCBDB7739
	static BOOL IS_CONVERSATION_PED_DEAD(Any p0) { return invoke<BOOL>(0x1FA39EFE, p0); } // 0x1FA39EFE
	static BOOL IS_PED_AIMING_FROM_COVER(Player* p0) { return invoke<BOOL>(0xDEBAB2AF, p0); } // 0xDEBAB2AF
	static BOOL IS_PED_RELOADING(Ped ped) { return invoke<BOOL>(0x961E1745, ped); } // 0x961E1745
	static BOOL IS_PED_A_PLAYER(Ped ped) { return invoke<BOOL>(0x404794CA, ped); } // 0x404794CA
	static Any CREATE_PED_INSIDE_VEHICLE(Vehicle vehicle, int pedType, Hash modelHash, int seat, Any p4, Any p5) { return invoke<Any>(0x3000F092, vehicle, pedType, modelHash, seat, p4, p5); } // 0x3000F092
	static void SET_PED_DESIRED_HEADING(Any p0, Any p1) { invoke<Void>(0x961458F9, p0, p1); } // 0x961458F9
	static void _0x290421BE(Any p0) { invoke<Void>(0x290421BE, p0); } // 0x290421BE
	static BOOL IS_PED_FACING_PED(Any p0, Any p1, Any p2) { return invoke<BOOL>(0x0B775838, p0, p1, p2); } // 0x0B775838
	static BOOL IS_PED_IN_MELEE_COMBAT(Ped ped) { return invoke<BOOL>(0xFD7814A5, ped); } // 0xFD7814A5
	static BOOL IS_PED_STOPPED(Ped ped) { return invoke<BOOL>(0xA0DC0B87, ped); } // 0xA0DC0B87
	static BOOL IS_PED_SHOOTING_IN_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<BOOL>(0x741BF04F, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x741BF04F
	static BOOL IS_ANY_PED_SHOOTING_IN_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<BOOL>(0x91833867, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x91833867
	static BOOL IS_PED_SHOOTING(Ped ped) { return invoke<BOOL>(0xE7C3405E, ped); } // 0xE7C3405E
	static void SET_PED_ACCURACY(Ped ped, int accuracy) { invoke<Void>(0x6C17122E, ped, accuracy); } // 0x6C17122E
	static Any GET_PED_ACCURACY(Any p0) { return invoke<Any>(0x0A2A0AA0, p0); } // 0x0A2A0AA0
	static BOOL IS_PED_MODEL(Ped pedHandle, Hash modelHash) { return invoke<BOOL>(0x5F1DDFCB, pedHandle, modelHash); } // 0x5F1DDFCB
	static void EXPLODE_PED_HEAD(Ped ped, Hash WeaponHash) { invoke<Void>(0x05CC1380, ped, WeaponHash); } // 0x05CC1380
	static void REMOVE_PED_ELEGANTLY(Ped PedHandle) { invoke<Void>(0x4FFB8C6C, PedHandle); } // 0x4FFB8C6C
	static void ADD_ARMOUR_TO_PED(Ped PedHandle, int Amount) { invoke<Void>(0xF686B26E, PedHandle, Amount); } // 0xF686B26E
	static void SET_PED_ARMOUR(Any p0, Any p1) { invoke<Void>(0x4E3A0CC4, p0, p1); } // 0x4E3A0CC4
	static void SET_PED_INTO_VEHICLE(Ped PedHandle, Vehicle VehicleHandle, int SeatIndex) { invoke<Void>(0x07500C79, PedHandle, VehicleHandle, SeatIndex); } // 0x07500C79
	static void _0x58A80BD5(Any p0, Any p1) { invoke<Void>(0x58A80BD5, p0, p1); } // 0x58A80BD5
	static BOOL CAN_CREATE_RANDOM_PED(Any p0) { return invoke<BOOL>(0xF9ABE88F, p0); } // 0xF9ABE88F
	static Ped CREATE_RANDOM_PED(float X, float Y, float Z) { return invoke<Ped>(0x5A949543, X, Y, Z); } // 0x5A949543
	static Ped CREATE_RANDOM_PED_AS_DRIVER(Vehicle vehicleHandle, BOOL p1) { return invoke<Ped>(0xB927CE9A, vehicleHandle, p1); } // 0xB927CE9A
	static BOOL CAN_CREATE_RANDOM_DRIVER() { return invoke<BOOL>(0x99861609); } // 0x99861609
	static Any _0x7018BE31() { return invoke<Any>(0x7018BE31); } // 0x7018BE31
	static void SET_PED_MOVE_ANIMS_BLEND_OUT(Any p0) { invoke<Void>(0x20E01957, p0); } // 0x20E01957
	static void SET_PED_CAN_BE_DRAGGED_OUT(Any p0, Any p1) { invoke<Void>(0xAA7F1131, p0, p1); } // 0xAA7F1131
	static void _0x6CD58238(Any p0) { invoke<Void>(0x6CD58238, p0); } // 0x6CD58238
	static BOOL IS_PED_MALE(Any p0) { return invoke<BOOL>(0x90950455, p0); } // 0x90950455
	static BOOL IS_PED_HUMAN(Any p0) { return invoke<BOOL>(0x194BB7B0, p0); } // 0x194BB7B0
	static Vehicle GET_VEHICLE_PED_IS_IN(Ped pedHandle, BOOL getLastVehicle) { return invoke<Vehicle>(0xAFE92319, pedHandle, getLastVehicle); } // 0xAFE92319
	static void RESET_PED_LAST_VEHICLE(Any p0) { invoke<Void>(0x5E3B5942, p0); } // 0x5E3B5942
	static void SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(Any p0) { invoke<Void>(0x039C82BB, p0); } // 0x039C82BB
	static void SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(Any p0, Any p1) { invoke<Void>(0x2909ABF0, p0, p1); } // 0x2909ABF0
	static void _0xB48C0C04() { invoke<Void>(0xB48C0C04); } // 0xB48C0C04
	static void _0x25EA2AA5(Any p0, Any p1, Any p2) { invoke<Void>(0x25EA2AA5, p0, p1, p2); } // 0x25EA2AA5
	static void SET_PED_NON_CREATION_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x7A97283F, p0, p1, p2, p3, p4, p5); } // 0x7A97283F
	static void CLEAR_PED_NON_CREATION_AREA() { invoke<Void>(0x6F7043A3); } // 0x6F7043A3
	static void _0x8C555ADD() { invoke<Void>(0x8C555ADD); } // 0x8C555ADD
	static BOOL IS_PED_ON_MOUNT(Any p0) { return invoke<BOOL>(0x43103006, p0); } // 0x43103006
	static Any GET_MOUNT(Any p0) { return invoke<Any>(0xDD31EC4E, p0); } // 0xDD31EC4E
	static BOOL IS_PED_ON_VEHICLE(Any p0) { return invoke<BOOL>(0xA1AE7CC7, p0); } // 0xA1AE7CC7
	static BOOL IS_PED_ON_SPECIFIC_VEHICLE(Ped ped, Vehicle specificVehicle) { return invoke<BOOL>(0x63CB4603, ped, specificVehicle); } // 0x63CB4603
	static void SET_PED_MONEY(Ped pedHandle, int amount) { invoke<Void>(0x40D90BF2, pedHandle, amount); } // 0x40D90BF2
	static Any GET_PED_MONEY(Ped pedHandle) { return invoke<Any>(0xEB3C4C7E, pedHandle); } // 0xEB3C4C7E
	static void _0xD41C9AED(Any p0, Any p1) { invoke<Void>(0xD41C9AED, p0, p1); } // 0xD41C9AED
	static void _0x30B98369(Any p0) { invoke<Void>(0x30B98369, p0); } // 0x30B98369
	static void _0x02A080C8(Any p0) { invoke<Void>(0x02A080C8, p0); } // 0x02A080C8
	static void SET_PED_SUFFERS_CRITICAL_HITS(Any p0, Any p1) { invoke<Void>(0x6F6FC7E6, p0, p1); } // 0x6F6FC7E6
	static void _0x1572022A(Any p0, Any p1) { invoke<Void>(0x1572022A, p0, p1); } // 0x1572022A
	static BOOL IS_PED_SITTING_IN_VEHICLE(Any p0, Any p1) { return invoke<BOOL>(0xDDDE26FA, p0, p1); } // 0xDDDE26FA
	static BOOL IS_PED_SITTING_IN_ANY_VEHICLE(Ped Ped) { return invoke<BOOL>(0x0EA9CA03, Ped); } // 0x0EA9CA03
	static BOOL IS_PED_ON_FOOT(Ped Ped) { return invoke<BOOL>(0xC60D0785, Ped); } // 0xC60D0785
	static BOOL IS_PED_ON_ANY_BIKE(Any p0) { return invoke<BOOL>(0x4D885B2E, p0); } // 0x4D885B2E
	static BOOL IS_PED_PLANTING_BOMB(Any p0) { return invoke<BOOL>(0x0EDAC574, p0); } // 0x0EDAC574
	static Vector3 GET_DEAD_PED_PICKUP_COORDS(Any p0, Any p1, Any p2) { return invoke<Vector3>(0x129F9DC1, p0, p1, p2); } // 0x129F9DC1
	static BOOL IS_PED_IN_ANY_BOAT(Any p0) { return invoke<BOOL>(0x1118A947, p0); } // 0x1118A947
	static BOOL IS_PED_IN_ANY_SUB(Any p0) { return invoke<BOOL>(0xE65F8059, p0); } // 0xE65F8059
	static BOOL IS_PED_IN_ANY_HELI(Any p0) { return invoke<BOOL>(0x7AB5523B, p0); } // 0x7AB5523B
	static BOOL IS_PED_IN_ANY_PLANE(Any p0) { return invoke<BOOL>(0x51BBCE7E, p0); } // 0x51BBCE7E
	static BOOL IS_PED_IN_FLYING_VEHICLE(Any p0) { return invoke<BOOL>(0xCA072485, p0); } // 0xCA072485
	static void SET_PED_DIES_IN_WATER(Any p0, Any p1) { invoke<Void>(0x604C872B, p0, p1); } // 0x604C872B
	static void SET_PED_DIES_IN_SINKING_VEHICLE(Any p0, Any p1) { invoke<Void>(0x8D4D9ABB, p0, p1); } // 0x8D4D9ABB
	static int GET_PED_ARMOUR(Ped PedHandle) { return invoke<int>(0x2CE311A7, PedHandle); } // 0x2CE311A7
	static void SET_PED_STAY_IN_VEHICLE_WHEN_JACKED(Any p0, Any p1) { invoke<Void>(0xB014A09C, p0, p1); } // 0xB014A09C
	static void SET_PED_CAN_BE_SHOT_IN_VEHICLE(Any p0, Any p1) { invoke<Void>(0x5DB7B3A9, p0, p1); } // 0x5DB7B3A9
	static Any GET_PED_LAST_DAMAGE_BONE(Any p0, Any p1) { return invoke<Any>(0xAB933841, p0, p1); } // 0xAB933841
	static void CLEAR_PED_LAST_DAMAGE_BONE(Any p0) { invoke<Void>(0x56CB715E, p0); } // 0x56CB715E
	static void SET_AI_WEAPON_DAMAGE_MODIFIER(Any p0) { invoke<Void>(0x516E30EE, p0); } // 0x516E30EE
	static void RESET_AI_WEAPON_DAMAGE_MODIFIER() { invoke<Void>(0x6E965420); } // 0x6E965420
	static void _0x0F9A401F(Any p0) { invoke<Void>(0x0F9A401F, p0); } // 0x0F9A401F
	static void _0x97886238() { invoke<Void>(0x97886238); } // 0x97886238
	static void _0xCC9D7F1A(Any p0, Any p1) { invoke<Void>(0xCC9D7F1A, p0, p1); } // 0xCC9D7F1A
	static void SET_PED_CAN_BE_TARGETTED(Any p0, Any p1) { invoke<Void>(0x75C49F74, p0, p1); } // 0x75C49F74
	static void SET_PED_CAN_BE_TARGETTED_BY_TEAM(Any p0, Any p1, Any p2) { invoke<Void>(0xB103A8E1, p0, p1, p2); } // 0xB103A8E1
	static void SET_PED_CAN_BE_TARGETTED_BY_PLAYER(Any p0, Any p1, Any p2) { invoke<Void>(0xD050F490, p0, p1, p2); } // 0xD050F490
	static void _0x7DA12905(Any p0, Any p1) { invoke<Void>(0x7DA12905, p0, p1); } // 0x7DA12905
	static void SET_TIME_EXCLUSIVE_DISPLAY_TEXTURE(Any p0, Any p1) { invoke<Void>(0x7F67671D, p0, p1); } // 0x7F67671D
	static BOOL IS_PED_IN_ANY_POLICE_VEHICLE(Any p0) { return invoke<BOOL>(0x84FA790D, p0); } // 0x84FA790D
	static void _0xA819680B(Any p0) { invoke<Void>(0xA819680B, p0); } // 0xA819680B
	static Any _0xCD71F11B(Ped ped) { return invoke<Any>(0xCD71F11B, ped); } // 0xCD71F11B
	static BOOL IS_PED_FALLING(Ped PedHandle) { return invoke<BOOL>(0xABF77334, PedHandle); } // 0xABF77334
	static BOOL IS_PED_JUMPING(Ped Ped) { return invoke<BOOL>(0x07E5BC0E, Ped); } // 0x07E5BC0E
	static BOOL IS_PED_CLIMBING(Ped Ped) { return invoke<BOOL>(0xBCE03D35, Ped); } // 0xBCE03D35
	static Any _0xC3169BDA(Any p0) { return invoke<Any>(0xC3169BDA, p0); } // 0xC3169BDA
	static BOOL IS_PED_DIVING(Any p0) { return invoke<BOOL>(0x7BC5BF3C, p0); } // 0x7BC5BF3C
	static Any _0xB19215F6(Any p0) { return invoke<Any>(0xB19215F6, p0); } // 0xB19215F6
	static Any GET_PED_PARACHUTE_STATE(Any p0) { return invoke<Any>(0x7D4BC475, p0); } // 0x7D4BC475
	static Any _0x01F3B035(Any p0) { return invoke<Any>(0x01F3B035, p0); } // 0x01F3B035
	static void SET_PED_PARACHUTE_TINT_INDEX(Any p0, Any p1) { invoke<Void>(0x5AEFEC3A, p0, p1); } // 0x5AEFEC3A
	static void GET_PED_PARACHUTE_TINT_INDEX(Any p0, Any p1) { invoke<Void>(0xE9E7FAC5, p0, p1); } // 0xE9E7FAC5
	static void _0x177EFC79(Any p0, Any p1) { invoke<Void>(0x177EFC79, p0, p1); } // 0x177EFC79
	static void SET_PED_DUCKING(Any p0, Any p1) { invoke<Void>(0xB90353D7, p0, p1); } // 0xB90353D7
	static BOOL IS_PED_DUCKING(Any p0) { return invoke<BOOL>(0x9199C77D, p0); } // 0x9199C77D
	static BOOL IS_PED_IN_ANY_TAXI(Any p0) { return invoke<BOOL>(0x16FD386C, p0); } // 0x16FD386C
	static void SET_PED_ID_RANGE(Any p0, Any p1) { invoke<Void>(0xEF3B4ED9, p0, p1); } // 0xEF3B4ED9
	static void _0x9A2180FF(Any p0, Any p1) { invoke<Void>(0x9A2180FF, p0, p1); } // 0x9A2180FF
	static void _0xF30658D2(Any p0, Any p1) { invoke<Void>(0xF30658D2, p0, p1); } // 0xF30658D2
	static void _0x43709044(Any p0) { invoke<Void>(0x43709044, p0); } // 0x43709044
	static void SET_PED_SEEING_RANGE(Any p0, float p1) { invoke<Void>(0x4BD72FE8, p0, p1); } // 0x4BD72FE8
	static void SET_PED_HEARING_RANGE(Any p0, Any p1) { invoke<Void>(0xB32087E0, p0, p1); } // 0xB32087E0
	static void SET_PED_VISUAL_FIELD_MIN_ANGLE(Any p0, Any p1) { invoke<Void>(0x72E2E18B, p0, p1); } // 0x72E2E18B
	static void SET_PED_VISUAL_FIELD_MAX_ANGLE(Any p0, Any p1) { invoke<Void>(0x0CEA0F9A, p0, p1); } // 0x0CEA0F9A
	static void SET_PED_VISUAL_FIELD_MIN_ELEVATION_ANGLE(Any p0, Any p1) { invoke<Void>(0x5CC2F1B8, p0, p1); } // 0x5CC2F1B8
	static void SET_PED_VISUAL_FIELD_MAX_ELEVATION_ANGLE(Any p0, Any p1) { invoke<Void>(0x39D9102F, p0, p1); } // 0x39D9102F
	static void SET_PED_VISUAL_FIELD_PERIPHERAL_RANGE(Any p0, float p1) { invoke<Void>(0xFDF2F7C2, p0, p1); } // 0xFDF2F7C2
	static void _0xE57202A1(Any p0, Any p1) { invoke<Void>(0xE57202A1, p0, p1); } // 0xE57202A1
	static void SET_PED_STEALTH_MOVEMENT(Any p0, Any p1, Any p2) { invoke<Void>(0x67E28E1D, p0, p1, p2); } // 0x67E28E1D
	static Any GET_PED_STEALTH_MOVEMENT(Any p0) { return invoke<Any>(0x40321B83, p0); } // 0x40321B83
	static Any CREATE_GROUP(int Zombies) { return invoke<Any>(0x8DC0368D, Zombies); } // 0x8DC0368D
	static void SET_PED_AS_GROUP_LEADER(Ped PedHandle, int Zombies) { invoke<Void>(0x7265BEA2, PedHandle, Zombies); } // 0x7265BEA2
	static void SET_PED_AS_GROUP_MEMBER(Ped PedHandle, int groupId) { invoke<Void>(0x0EE13F92, PedHandle, groupId); } // 0x0EE13F92
	static void _0xD0D8BDBC(Any p0, Any p1, Any p2) { invoke<Void>(0xD0D8BDBC, p0, p1, p2); } // 0xD0D8BDBC
	static void REMOVE_GROUP(int Group) { invoke<Void>(0x48D72B88, Group); } // 0x48D72B88
	static void REMOVE_PED_FROM_GROUP(Ped PedHandle) { invoke<Void>(0x82697713, PedHandle); } // 0x82697713
	static BOOL IS_PED_GROUP_MEMBER(Ped PedHandle, int Group) { return invoke<BOOL>(0x876D5363, PedHandle, Group); } // 0x876D5363
	static Any _0x9678D4FF(Any p0) { return invoke<Any>(0x9678D4FF, p0); } // 0x9678D4FF
	static void SET_GROUP_SEPARATION_RANGE(Any p0, Any p1) { invoke<Void>(0x7B820CD5, p0, p1); } // 0x7B820CD5
	static void _0x2F0D0973(Any p0, Any p1) { invoke<Void>(0x2F0D0973, p0, p1); } // 0x2F0D0973
	static BOOL IS_PED_PRONE(Any p0) { return invoke<BOOL>(0x02C2A6C3, p0); } // 0x02C2A6C3
	static BOOL IS_PED_IN_COMBAT(Any p0, Any p1) { return invoke<BOOL>(0xFE027CB5, p0, p1); } // 0xFE027CB5
	static Any _0xCCD525E1(Any p0, Any p1) { return invoke<Any>(0xCCD525E1, p0, p1); } // 0xCCD525E1
	static BOOL IS_PED_DOING_DRIVEBY(Any p0) { return invoke<BOOL>(0xAC3CEB9C, p0); } // 0xAC3CEB9C
	static BOOL IS_PED_JACKING(Any p0) { return invoke<BOOL>(0x3B321816, p0); } // 0x3B321816
	static BOOL IS_PED_BEING_JACKED(Any p0) { return invoke<BOOL>(0xD45D605C, p0); } // 0xD45D605C
	static BOOL IS_PED_BEING_STUNNED(Any p0, Any p1) { return invoke<BOOL>(0x0A66CE30, p0, p1); } // 0x0A66CE30
	static Any GET_PEDS_JACKER(Any p0) { return invoke<Any>(0xDE1DBB59, p0); } // 0xDE1DBB59
	static Any GET_JACK_TARGET(Any p0) { return invoke<Any>(0x1D196361, p0); } // 0x1D196361
	static BOOL IS_PED_FLEEING(Any p0) { return invoke<BOOL>(0x85D813C6, p0); } // 0x85D813C6
	static BOOL IS_PED_IN_COVER(Any p0, Any p1) { return invoke<BOOL>(0x972C5A8B, p0, p1); } // 0x972C5A8B
	static BOOL IS_PED_IN_COVER_FACING_LEFT(Any p0) { return invoke<BOOL>(0xB89DBB80, p0); } // 0xB89DBB80
	static BOOL IS_PED_GOING_INTO_COVER(Any p0) { return invoke<BOOL>(0xA3589628, p0); } // 0xA3589628
	static Any SET_PED_PINNED_DOWN(Any p0, Any p1, Any p2) { return invoke<Any>(0xCC78999D, p0, p1, p2); } // 0xCC78999D
	static Any _0xACF162E0(Any p0) { return invoke<Any>(0xACF162E0, p0); } // 0xACF162E0
	static Any _0x99968B37(Any p0) { return invoke<Any>(0x99968B37, p0); } // 0x99968B37
	static Any _0x84ADF9EB(Any p0) { return invoke<Any>(0x84ADF9EB, p0); } // 0x84ADF9EB
	static Any GET_PED_CAUSE_OF_DEATH(Any p0) { return invoke<Any>(0x63458C27, p0); } // 0x63458C27
	static Any GET_PED_TIME_OF_DEATH(Any p0) { return invoke<Any>(0xDF6D5D54, p0); } // 0xDF6D5D54
	static Any _0xEF0B78E6(Any p0) { return invoke<Any>(0xEF0B78E6, p0); } // 0xEF0B78E6
	static Any _0xFB18CB19(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xFB18CB19, p0, p1, p2, p3, p4); } // 0xFB18CB19
	static void SET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(Any p0, Any p1) { invoke<Void>(0x423B7BA2, p0, p1); } // 0x423B7BA2
	static void SET_PED_RELATIONSHIP_GROUP_HASH(Ped pedHandle, Any groupHandle) { invoke<Void>(0x79F8C18C, pedHandle, groupHandle); } // 0x79F8C18C
	static void SET_RELATIONSHIP_BETWEEN_GROUPS(int RelationStatus, Any Group1, Any Group2) { invoke<Void>(0xD4A215BA, RelationStatus, Group1, Group2); } // 0xD4A215BA
	static void CLEAR_RELATIONSHIP_BETWEEN_GROUPS(int RelationStatus, Any Group1, Any Group2) { invoke<Void>(0x994B8C2D, RelationStatus, Group1, Group2); } // 0x994B8C2D
	static Any ADD_RELATIONSHIP_GROUP(char* crewName, Any p1) { return invoke<Any>(0x8B635546, crewName, p1); } // 0x8B635546
	static void REMOVE_RELATIONSHIP_GROUP(Any p0) { invoke<Void>(0x4A1DC59A, p0); } // 0x4A1DC59A
	static int GET_RELATIONSHIP_BETWEEN_PEDS(Ped ped1, Ped ped2) { return invoke<int>(0xE254C39C, ped1, ped2); } // 0xE254C39C
	static Any GET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(Any p0) { return invoke<Any>(0x714BD6E4, p0); } // 0x714BD6E4
	static Any GET_PED_RELATIONSHIP_GROUP_HASH(Player playerId) { return invoke<Any>(0x354F283C, playerId); } // 0x354F283C
	static int GET_RELATIONSHIP_BETWEEN_GROUPS(Any p0, Any p1) { return invoke<int>(0x4E372FE2, p0, p1); } // 0x4E372FE2
	static void SET_PED_CAN_BE_TARGETED_WITHOUT_LOS(Any p0, Any p1) { invoke<Void>(0x7FDDC0A6, p0, p1); } // 0x7FDDC0A6
	static void SET_PED_TO_INFORM_RESPECTED_FRIENDS(Any p0, Any p1, Any p2) { invoke<Void>(0xD78AC46C, p0, p1, p2); } // 0xD78AC46C
	static BOOL IS_PED_RESPONDING_TO_EVENT(Any p0, Any p1) { return invoke<BOOL>(0x7A877554, p0, p1); } // 0x7A877554
	static void SET_PED_FIRING_PATTERN(Ped ped, Hash patternHash) { invoke<Void>(0xB4629D66, ped, patternHash); } // 0xB4629D66
	static void SET_PED_SHOOT_RATE(Ped ped, int shootRate) { invoke<Void>(0xFB301746, ped, shootRate); } // 0xFB301746
	static void SET_COMBAT_FLOAT(Any p0, Any p1, Any p2) { invoke<Void>(0xD8B7637C, p0, p1, p2); } // 0xD8B7637C
	static Any GET_COMBAT_FLOAT(Any p0, Any p1) { return invoke<Any>(0x511D7EF8, p0, p1); } // 0x511D7EF8
	static void GET_GROUP_SIZE(Any p0, Any p1, Any p2) { invoke<Void>(0xF7E1A691, p0, p1, p2); } // 0xF7E1A691
	static BOOL DOES_GROUP_EXIST(int Group) { return invoke<BOOL>(0x935C978D, Group); } // 0x935C978D
	static int GET_PED_GROUP_INDEX(Ped pedHandle) { return invoke<int>(0x134E0785, pedHandle); } // 0x134E0785
	static BOOL IS_PED_IN_GROUP(Ped pedHandle) { return invoke<BOOL>(0x836D9795, pedHandle); } // 0x836D9795
	static Any _0xDE7442EE(Any p0) { return invoke<Any>(0xDE7442EE, p0); } // 0xDE7442EE
	static void SET_GROUP_FORMATION(int group, int formationType) { invoke<Void>(0x08FAC739, group, formationType); } // 0x08FAC739
	static void SET_GROUP_FORMATION_SPACING(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xB1E086FF, p0, p1, p2, p3); } // 0xB1E086FF
	static void _0x267FCEAD(Any p0) { invoke<Void>(0x267FCEAD, p0); } // 0x267FCEAD
	static Vehicle GET_VEHICLE_PED_IS_USING(Ped PedHandle) { return invoke<Vehicle>(0x6DE3AADA, PedHandle); } // 0x6DE3AADA
	static Any SET_EXCLUSIVE_PHONE_RELATIONSHIPS(Any p0) { return invoke<Any>(0x56E0C163, p0); } // 0x56E0C163
	static void SET_PED_GRAVITY(Any p0, Any p1) { invoke<Void>(0x3CA16652, p0, p1); } // 0x3CA16652
	static void APPLY_DAMAGE_TO_PED(Ped pedHandle, Any damageAmount, BOOL p2) { invoke<Void>(0x4DC27FCF, pedHandle, damageAmount, p2); } // 0x4DC27FCF
	static void SET_PED_ALLOWED_TO_DUCK(Any p0, Any p1) { invoke<Void>(0xC4D122F8, p0, p1); } // 0xC4D122F8
	static void SET_PED_NEVER_LEAVES_GROUP(Ped PedHandle, int Group) { invoke<Void>(0x0E038813, PedHandle, Group); } // 0x0E038813
	static Any GET_PED_TYPE(Ped PedHandle) { return invoke<Any>(0xB1460D43, PedHandle); } // 0xB1460D43
	static void SET_PED_AS_COP(int PedHandle, BOOL Toggle) { invoke<Void>(0x84E7DE9F, PedHandle, Toggle); } // 0x84E7DE9F
	static void SET_PED_MAX_HEALTH(Any p0, Any p1) { invoke<Void>(0x5533F60B, p0, p1); } // 0x5533F60B
	static Any GET_PED_MAX_HEALTH(Any p0) { return invoke<Any>(0xA45B6C8D, p0); } // 0xA45B6C8D
	static void SET_PED_MAX_TIME_IN_WATER(Any p0, Any p1) { invoke<Void>(0xFE0A106B, p0, p1); } // 0xFE0A106B
	static void SET_PED_MAX_TIME_UNDERWATER(Any p0, Any p1) { invoke<Void>(0x082EF240, p0, p1); } // 0x082EF240
	static void _0x373CC405(Any p0, Any p1) { invoke<Void>(0x373CC405, p0, p1); } // 0x373CC405
	static void SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(Ped PedHandle, int p1) { invoke<Void>(0x8A251612, PedHandle, p1); } // 0x8A251612
	static Any _0xC9D098B3(Any p0) { return invoke<Any>(0xC9D098B3, p0); } // 0xC9D098B3
	static void KNOCK_PED_OFF_VEHICLE(Ped PedHandle) { invoke<Void>(0xACDD0674, PedHandle); } // 0xACDD0674
	static void SET_PED_COORDS_NO_GANG(Ped ped, float XCoord, float YCoord, float ZCoord) { invoke<Void>(0x9561AD98, ped, XCoord, YCoord, ZCoord); } // 0x9561AD98
	static Any GET_PED_AS_GROUP_MEMBER(Any p0, Any p1) { return invoke<Any>(0x9AA3CC8C, p0, p1); } // 0x9AA3CC8C
	static void SET_PED_KEEP_TASK(Ped ped, BOOL Toggle) { invoke<Void>(0xA7EC79CE, ped, Toggle); } // 0xA7EC79CE
	static void _0x397F06E3(Any p0, Any p1) { invoke<Void>(0x397F06E3, p0, p1); } // 0x397F06E3
	static BOOL IS_PED_SWIMMING(Any p0) { return invoke<BOOL>(0x7AB43DB8, p0); } // 0x7AB43DB8
	static BOOL IS_PED_SWIMMING_UNDER_WATER(Any p0) { return invoke<BOOL>(0x0E8D524F, p0); } // 0x0E8D524F
	static void SET_PED_COORDS_KEEP_VEHICLE(Ped ped, float XCoord, float YCoord, float ZCoord) { invoke<Void>(0xD66AE1D3, ped, XCoord, YCoord, ZCoord); } // 0xD66AE1D3
	static void SET_PED_DIES_IN_VEHICLE(Any p0, Any p1) { invoke<Void>(0x6FE1E440, p0, p1); } // 0x6FE1E440
	static void SET_CREATE_RANDOM_COPS(Any p0) { invoke<Void>(0x23441648, p0); } // 0x23441648
	static void _0x82E548CC(Any p0) { invoke<Void>(0x82E548CC, p0); } // 0x82E548CC
	static void _0xEDC31475(Any p0) { invoke<Void>(0xEDC31475, p0); } // 0xEDC31475
	static BOOL CAN_CREATE_RANDOM_COPS() { return invoke<BOOL>(0xAA73DAD9); } // 0xAA73DAD9
	static void SET_PED_AS_ENEMY(Ped pedHandle, BOOL p1) { invoke<Void>(0xAE620A1B, pedHandle, p1); } // 0xAE620A1B
	static void SET_PED_CAN_SMASH_GLASS(Any p0, Any p1, Any p2) { invoke<Void>(0x149C60A8, p0, p1, p2); } // 0x149C60A8
	static BOOL IS_PED_IN_ANY_TRAIN(Any p0) { return invoke<BOOL>(0x759EF63A, p0); } // 0x759EF63A
	static BOOL IS_PED_GETTING_INTO_A_VEHICLE(int playerID) { return invoke<BOOL>(0x90E805AC, playerID); } // 0x90E805AC
	static BOOL IS_PED_TRYING_TO_ENTER_A_LOCKED_VEHICLE(Any p0) { return invoke<BOOL>(0x46828B4E, p0); } // 0x46828B4E
	static void SET_ENABLE_HANDCUFFS(Ped PedHandle, BOOL Toggle) { invoke<Void>(0xAC9BBA23, PedHandle, Toggle); } // 0xAC9BBA23
	static void SET_ENABLE_BOUND_ANKLES(Any p0, Any p1) { invoke<Void>(0x9208D689, p0, p1); } // 0x9208D689
	static void _0x7BF61471(Any p0, Any p1) { invoke<Void>(0x7BF61471, p0, p1); } // 0x7BF61471
	static void SET_CAN_ATTACK_FRIENDLY(Player p0, Ped p1, Any p2) { invoke<Void>(0x47C60963, p0, p1, p2); } // 0x47C60963
	static Any GET_PED_ALERTNESS(Any p0) { return invoke<Any>(0xF83E4DAF, p0); } // 0xF83E4DAF
	static void SET_PED_ALERTNESS(Any p0, Any p1) { invoke<Void>(0x2C32D9AE, p0, p1); } // 0x2C32D9AE
	static void SET_PED_GET_OUT_UPSIDE_DOWN_VEHICLE(Any p0, Any p1) { invoke<Void>(0x89AD49FF, p0, p1); } // 0x89AD49FF
	static void SET_PED_MOVEMENT_CLIPSET(Any p0, char *p1, Any p2) { invoke<Void>(0xA817CDEB, p0, p1, p2); } // 0xA817CDEB
	static void RESET_PED_MOVEMENT_CLIPSET(Any p0, Any p1) { invoke<Void>(0xB83CEE93, p0, p1); } // 0xB83CEE93
	static void SET_PED_STRAFE_CLIPSET(Any p0, Any p1) { invoke<Void>(0x0BACF010, p0, p1); } // 0x0BACF010
	static void RESET_PED_STRAFE_CLIPSET(Any p0) { invoke<Void>(0xF1967A12, p0); } // 0xF1967A12
	static void SET_PED_WEAPON_MOVEMENT_CLIPSET(Any p0, Any p1) { invoke<Void>(0xF8BE54DC, p0, p1); } // 0xF8BE54DC
	static void RESET_PED_WEAPON_MOVEMENT_CLIPSET(Any p0) { invoke<Void>(0xC60C9ACD, p0); } // 0xC60C9ACD
	static void _0xD4C73595(Any p0, Any p1) { invoke<Void>(0xD4C73595, p0, p1); } // 0xD4C73595
	static void _0xAEC9163B(Any p0) { invoke<Void>(0xAEC9163B, p0); } // 0xAEC9163B
	static void SET_PED_IN_VEHICLE_CONTEXT(Any p0, Any p1) { invoke<Void>(0x27F25C0E, p0, p1); } // 0x27F25C0E
	static void RESET_PED_IN_VEHICLE_CONTEXT(Any p0) { invoke<Void>(0x3C94D88A, p0); } // 0x3C94D88A
	static Any _0x3C30B447(Any p0, Any p1, Any p2) { return invoke<Any>(0x3C30B447, p0, p1, p2); } // 0x3C30B447
	static void _0x895E1D67(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x895E1D67, p0, p1, p2, p3, p4); } // 0x895E1D67
	static void _0x5736FB23(Any p0, Any p1) { invoke<Void>(0x5736FB23, p0, p1); } // 0x5736FB23
	static void SET_PED_ALTERNATE_MOVEMENT_ANIM(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xBA84FD8C, p0, p1, p2, p3, p4, p5); } // 0xBA84FD8C
	static void CLEAR_PED_ALTERNATE_MOVEMENT_ANIM(Any p0, Any p1, Any p2) { invoke<Void>(0x7A7F5BC3, p0, p1, p2); } // 0x7A7F5BC3
	static void SET_PED_GESTURE_GROUP(Any p0, Any p1) { invoke<Void>(0x170DA109, p0, p1); } // 0x170DA109
	static Vector3 _0xC59D4268(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<Vector3>(0xC59D4268, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xC59D4268
	static Vector3 _0x5F7789E6(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<Vector3>(0x5F7789E6, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x5F7789E6
	static int GET_PED_DRAWABLE_VARIATION(Ped pedID, int componentID) { return invoke<int>(0x29850FE2, pedID, componentID); } // 0x29850FE2
	static int GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(Ped pedID, int componentID) { return invoke<int>(0x9754C27D, pedID, componentID); } // 0x9754C27D
	static int GET_PED_TEXTURE_VARIATION(Ped pedID, int componentID) { return invoke<int>(0xC0A8590A, pedID, componentID); } // 0xC0A8590A
	static int GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(Ped pedID, int componentID, int drawableID) { return invoke<int>(0x83D9FBE7, pedID, componentID, drawableID); } // 0x83D9FBE7
	static int _0xC9780B95(Any p0, Any p1) { return invoke<int>(0xC9780B95, p0, p1); } // 0xC9780B95
	static Any REMOVE_NIGHTVISION_MELEE(Any p0, Any p1, Any p2) { return invoke<Any>(0x4892B882, p0, p1, p2); } // 0x4892B882
	static int GET_PED_PALETTE_VARIATION(Any p0, Any p1) { return invoke<int>(0xEF1BC082, p0, p1); } // 0xEF1BC082
	static BOOL IS_PED_COMPONENT_VARIATION_VALID(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0x952ABD9A, p0, p1, p2, p3); } // 0x952ABD9A
	static void SET_PED_COMPONENT_VARIATION(Ped PedHandle, int componentID, int drawableID, int textureID, int paletteID) { invoke<Void>(0xD4F7B05C, PedHandle, componentID, drawableID, textureID, paletteID); } // 0xD4F7B05C
	static void SET_PED_RANDOM_COMPONENT_VARIATION(Ped pedHandle, BOOL p1) { invoke<Void>(0x4111BA46, pedHandle, p1); } // 0x4111BA46
	static void SET_PED_RANDOM_PROPS(Ped PedHandle) { invoke<Void>(0xE3318E0E, PedHandle); } // 0xE3318E0E
	static void SET_PED_DEFAULT_COMPONENT_VARIATION(Ped PedHandle) { invoke<Void>(0xC866A984, PedHandle); } // 0xC866A984
	static void SET_PED_BLEND_FROM_PARENTS(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x837BD370, p0, p1, p2, p3, p4); } // 0x837BD370
	static void _0xC21C8A56(Any p0) { invoke<Void>(0xC21C8A56, p0); } // 0xC21C8A56
	static void _0x5D2FC042(Any p0, Any p1, Any p2) { invoke<Void>(0x5D2FC042, p0, p1, p2); } // 0x5D2FC042
	static void SET_PED_HEAD_BLEND_DATA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { invoke<Void>(0x60746B88, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x60746B88
	static void UPDATE_PED_HEAD_BLEND_DATA(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x5CB76219, p0, p1, p2, p3); } // 0x5CB76219
	static void SET_PED_HEAD_OVERLAY(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xD28DBA90, p0, p1, p2, p3); } // 0xD28DBA90
	static Any _0xFF43C18D(Any p0) { return invoke<Any>(0xFF43C18D, p0); } // 0xFF43C18D
	static BOOL HAS_PED_HEAD_BLEND_FINISHED(Any p0) { return invoke<BOOL>(0x2B1BD9C5, p0); } // 0x2B1BD9C5
	static void _0x894314A4(Any p0) { invoke<Void>(0x894314A4, p0); } // 0x894314A4
	static void _0x57E5B3F9(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x57E5B3F9, p0, p1, p2, p3, p4); } // 0x57E5B3F9
	static void _0xC6F36292(Any p0) { invoke<Void>(0xC6F36292, p0); } // 0xC6F36292
	static Any _0x211DEFEC(Any p0) { return invoke<Any>(0x211DEFEC, p0); } // 0x211DEFEC
	static Any _0x095D3BD8(Any p0) { return invoke<Any>(0x095D3BD8, p0); } // 0x095D3BD8
	static void _0x45F3BDFB(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x45F3BDFB, p0, p1, p2, p3); } // 0x45F3BDFB
	static Any _0xC6517D52(Any p0) { return invoke<Any>(0xC6517D52, p0); } // 0xC6517D52
	static void _0x6435F67F(Any p0) { invoke<Void>(0x6435F67F, p0); } // 0x6435F67F
	static void _0xC0E23671(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xC0E23671, p0, p1, p2, p3); } // 0xC0E23671
	static Any _0x3B0CA391(Any p0) { return invoke<Any>(0x3B0CA391, p0); } // 0x3B0CA391
	static void _0xFD103BA7(Any p0) { invoke<Void>(0xFD103BA7, p0); } // 0xFD103BA7
	static Any GET_PED_PROP_INDEX(Ped PedHandle, int ComponentID) { return invoke<Any>(0x746DDAC0, PedHandle, ComponentID); } // 0x746DDAC0
	static void SET_PED_PROP_INDEX(Ped PedHandle, int ComponentID, int drawableID, int TextureID, int PaletteID) { invoke<Void>(0x0829F2E2, PedHandle, ComponentID, drawableID, TextureID, PaletteID); } // 0x0829F2E2
	static void KNOCK_OFF_PED_PROP(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x08D8B180, p0, p1, p2, p3, p4); } // 0x08D8B180
	static void CLEAR_PED_PROP(Ped PedHandle, int PropID) { invoke<Void>(0x2D23D743, PedHandle, PropID); } // 0x2D23D743
	static void CLEAR_ALL_PED_PROPS(Ped PedHandle) { invoke<Void>(0x81DF8B43, PedHandle); } // 0x81DF8B43
	static Any GET_PED_PROP_TEXTURE_INDEX(Any p0, Any p1) { return invoke<Any>(0x922A6653, p0, p1); } // 0x922A6653
	static void _0x7BCD8991(Any p0) { invoke<Void>(0x7BCD8991, p0); } // 0x7BCD8991
	static void _0x080275EE(Any p0) { invoke<Void>(0x080275EE, p0); } // 0x080275EE
	static void SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Any p0, Any p1) { invoke<Void>(0xDFE34E4A, p0, p1); } // 0xDFE34E4A
	static void SET_PED_BOUNDS_ORIENTATION(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xCFA20D68, p0, p1, p2, p3, p4, p5); } // 0xCFA20D68
	static void REGISTER_TARGET(Any p0, Any p1) { invoke<Void>(0x50A95442, p0, p1); } // 0x50A95442
	static void REGISTER_HATED_TARGETS_AROUND_PED(Ped PedHandle, float AreaToAttack) { invoke<Void>(0x7F87559E, PedHandle, AreaToAttack); } // 0x7F87559E
	static Ped GET_RANDOM_PED_AT_COORD(float x, float y, float z, float xRadius, float yRadius, float zRadius, int p6) { return invoke<Ped>(0xDC8239EB, x, y, z, xRadius, yRadius, zRadius, p6); } // 0xDC8239EB
	static Ped GET_CLOSEST_PED(float x, float y, float z, float Radius, BOOL p4, BOOL p5, int handle, BOOL p7, BOOL p8, int p9) { return invoke<Ped>(0x8F6C1F55, x, y, z, Radius, p4, p5, handle, p7, p8, p9); } // 0x8F6C1F55
	static void SET_SCENARIO_PEDS_TO_BE_RETURNED_BY_NEXT_COMMAND(Any p0) { invoke<Void>(0x85615FD0, p0); } // 0x85615FD0
	static Any _0x18DD76A1(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<Any>(0x18DD76A1, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x18DD76A1
	static void _0x6D55B3B3(Any p0, Any p1) { invoke<Void>(0x6D55B3B3, p0, p1); } // 0x6D55B3B3
	static void SET_DRIVER_ABILITY(Any p0, Any p1) { invoke<Void>(0xAAD4012C, p0, p1); } // 0xAAD4012C
	static void SET_DRIVER_AGGRESSIVENESS(Any p0, Any p1) { invoke<Void>(0x8B02A8FB, p0, p1); } // 0x8B02A8FB
	static BOOL CAN_PED_RAGDOLL(Any p0) { return invoke<BOOL>(0xC0EFB7A3, p0); } // 0xC0EFB7A3
	static Any SET_PED_TO_RAGDOLL(Ped ped, int Xforce, int Yforce, int Zforce, BOOL p4, BOOL p5, BOOL p6) { return invoke<Any>(0x83CB5052, ped, Xforce, Yforce, Zforce, p4, p5, p6); } // 0x83CB5052
	static Any SET_PED_TO_RAGDOLL_WITH_FALL(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13) { return invoke<Any>(0xFA12E286, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); } // 0xFA12E286
	static void SET_PED_RAGDOLL_ON_COLLISION(Ped PedHandle, BOOL Toggle) { invoke<Void>(0x2654A0F4, PedHandle, Toggle); } // 0x2654A0F4
	static BOOL IS_PED_RAGDOLL(Any p0) { return invoke<BOOL>(0xC833BBE1, p0); } // 0xC833BBE1
	static BOOL IS_PED_RUNNING_RAGDOLL_TASK(Any p0) { return invoke<BOOL>(0x44A153F2, p0); } // 0x44A153F2
	static void SET_PED_RAGDOLL_FORCE_FALL(Ped ped) { invoke<Void>(0x20A5BDE0, ped); } // 0x20A5BDE0
	static void RESET_PED_RAGDOLL_TIMER(Any p0) { invoke<Void>(0xF2865370, p0); } // 0xF2865370
	static void SET_PED_CAN_RAGDOLL(Ped PedHandle, BOOL Toggle) { invoke<Void>(0xCF1384C4, PedHandle, Toggle); } // 0xCF1384C4
	static BOOL IS_PED_RUNNING_MOBILE_PHONE_TASK(Any p0) { return invoke<BOOL>(0xFB2AFED1, p0); } // 0xFB2AFED1
	static Any _0x97353375(Any p0) { return invoke<Any>(0x97353375, p0); } // 0x97353375
	static void _0x9C8F830D(Any p0, Any p1) { invoke<Void>(0x9C8F830D, p0, p1); } // 0x9C8F830D
	static void _0x77CBA290(Any p0, Any p1) { invoke<Void>(0x77CBA290, p0, p1); } // 0x77CBA290
	static void SET_PED_ANGLED_DEFENSIVE_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0x3EFBDD9B, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x3EFBDD9B
	static void SET_PED_SPHERE_DEFENSIVE_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0xBD96D8E8, p0, p1, p2, p3, p4, p5, p6); } // 0xBD96D8E8
	static void _0x40638BDC(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x40638BDC, p0, p1, p2, p3, p4, p5, p6); } // 0x40638BDC
	static void _0x4763B2C6(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x4763B2C6, p0, p1, p2, p3, p4, p5, p6); } // 0x4763B2C6
	static void SET_PED_DEFENSIVE_AREA_ATTACHED_TO_PED(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { invoke<Void>(0x74BDA7CE, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x74BDA7CE
	static void _0xB66B0C9A(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xB66B0C9A, p0, p1, p2, p3, p4); } // 0xB66B0C9A
	static void REMOVE_PED_DEFENSIVE_AREA(Any p0, Any p1) { invoke<Void>(0x34AAAFA5, p0, p1); } // 0x34AAAFA5
	static Vector3 GET_PED_DEFENSIVE_AREA_POSITION(Any p0, Any p1) { return invoke<Vector3>(0xCB65198D, p0, p1); } // 0xCB65198D
	static void _0xF3B7EFBF(Any p0, Any p1) { invoke<Void>(0xF3B7EFBF, p0, p1); } // 0xF3B7EFBF
	static void _0xA0134498(Any p0) { invoke<Void>(0xA0134498, p0); } // 0xA0134498
	static void REVIVE_INJURED_PED(Any p0) { invoke<Void>(0x14D3E6E3, p0); } // 0x14D3E6E3
	static void RESURRECT_PED(Any p0) { invoke<Void>(0xA4B82097, p0); } // 0xA4B82097
	static void SET_PED_NAME_DEBUG(Any p0, Any p1) { invoke<Void>(0x20D6273E, p0, p1); } // 0x20D6273E
	static Vector3 GET_PED_EXTRACTED_DISPLACEMENT(Any p0, Any p1) { return invoke<Vector3>(0x5231F901, p0, p1); } // 0x5231F901
	static void SET_PED_DIES_WHEN_INJURED(Ped ped, BOOL toggle) { invoke<Void>(0xE94E24D4, ped, toggle); } // 0xE94E24D4
	static void SET_PED_ENABLE_WEAPON_BLOCKING(Ped ped, BOOL toggle) { invoke<Void>(0x4CAD1A4A, ped, toggle); } // 0x4CAD1A4A
	static void _0x141CC936(Any p0, Any p1) { invoke<Void>(0x141CC936, p0, p1); } // 0x141CC936
	static void RESET_PED_VISIBLE_DAMAGE(Ped ped) { invoke<Void>(0xC4BC4841, ped); } // 0xC4BC4841
	static void _0x1E54DB12(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x1E54DB12, p0, p1, p2, p3, p4); } // 0x1E54DB12
	static void APPLY_PED_BLOOD(Ped ped, int i1, float f1, float f2, float f3, char* s1) { invoke<Void>(0x376CE3C0, ped, i1, f1, f2, f3, s1); } // 0x376CE3C0
	static void _0x8F3F3A9C(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x8F3F3A9C, p0, p1, p2, p3, p4); } // 0x8F3F3A9C
	static void _0xFC13CE80(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0xFC13CE80, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xFC13CE80
	static void APPLY_PED_DAMAGE_DECAL(Ped p0, int p1, float p2, float p3, float p4, float p5, float p6, int p7, BOOL p8, char* p9) { invoke<Void>(0x8A13A41F, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x8A13A41F
	static void APPLY_PED_DAMAGE_PACK(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x208D0CB8, p0, p1, p2, p3); } // 0x208D0CB8
	static void CLEAR_PED_BLOOD_DAMAGE(Ped PedHandle) { invoke<Void>(0xF7ADC960, PedHandle); } // 0xF7ADC960
	static void _0xF210BE69(Ped p0, int p1) { invoke<Void>(0xF210BE69, p0, p1); } // 0xF210BE69
	static void _0x0CB6C4ED(Any p0, Any p1, Any p2) { invoke<Void>(0x0CB6C4ED, p0, p1, p2); } // 0x0CB6C4ED
	static void _0x70AA5B7D(Any p0, Any p1, Any p2) { invoke<Void>(0x70AA5B7D, p0, p1, p2); } // 0x70AA5B7D
	static Any _0x47187F7F(Any p0) { return invoke<Any>(0x47187F7F, p0); } // 0x47187F7F
	static void CLEAR_PED_WETNESS(Ped ped) { invoke<Void>(0x629F15BD, ped); } // 0x629F15BD
	static void SET_PED_WETNESS_HEIGHT(Ped ped, float height) { invoke<Void>(0x7B33289A, ped, height); } // 0x7B33289A
	static void SET_PED_WETNESS_ENABLED_THIS_FRAME(Any p0) { invoke<Void>(0xBDE749F7, p0); } // 0xBDE749F7
	static void _0xA993915F(Ped ped) { invoke<Void>(0xA993915F, ped); } // 0xA993915F
	static void SET_PED_SWEAT(Ped ped, float sweat) { invoke<Void>(0x76A1DB9F, ped, sweat); } // 0x76A1DB9F
	static void _0x70559AC7(Ped ped, Hash ShirtType, Hash ShirtDecal) { invoke<Void>(0x70559AC7, ped, ShirtType, ShirtDecal); } // 0x70559AC7
	static Any _0x3543019E(Any p0, Any p1) { return invoke<Any>(0x3543019E, p0, p1); } // 0x3543019E
	static void CLEAR_PED_DECORATIONS(Ped PedHandle) { invoke<Void>(0xD4496BF3, PedHandle); } // 0xD4496BF3
	static void _0xEFD58EB9(Any p0) { invoke<Void>(0xEFD58EB9, p0); } // 0xEFD58EB9
	static BOOL WAS_PED_SKELETON_UPDATED(Any p0) { return invoke<BOOL>(0xF7E2FBAD, p0); } // 0xF7E2FBAD
	static Vector3 GET_PED_BONE_COORDS(Ped ped, int i1, float f1, float f2, float f3) { return invoke<Vector3>(0x4579CAB1, ped, i1, f1, f2, f3); } // 0x4579CAB1
	static void CREATE_NM_MESSAGE(Any p0, Any p1) { invoke<Void>(0x1CFBFD4B, p0, p1); } // 0x1CFBFD4B
	static void GIVE_PED_NM_MESSAGE(Any p0) { invoke<Void>(0x737C3689, p0); } // 0x737C3689
	static Any ADD_SCENARIO_BLOCKING_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<Any>(0xA38C0234, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xA38C0234
	static void REMOVE_SCENARIO_BLOCKING_AREAS() { invoke<Void>(0x4DDF845F); } // 0x4DDF845F
	static void REMOVE_SCENARIO_BLOCKING_AREA(Any p0, Any p1) { invoke<Void>(0x4483EF06, p0, p1); } // 0x4483EF06
	static void SET_SCENARIO_PEDS_SPAWN_IN_SPHERE_AREA(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x80EAD297, p0, p1, p2, p3, p4); } // 0x80EAD297
	static BOOL IS_PED_USING_SCENARIO(Any p0, Any p1) { return invoke<BOOL>(0x0F65B0D4, p0, p1); } // 0x0F65B0D4
	static BOOL IS_PED_USING_ANY_SCENARIO(Any p0) { return invoke<BOOL>(0x195EF5B7, p0); } // 0x195EF5B7
	static Any _0x59DE73AC(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x59DE73AC, p0, p1, p2, p3); } // 0x59DE73AC
	static void _0xC08FE5F6(Any p0, Any p1) { invoke<Void>(0xC08FE5F6, p0, p1); } // 0xC08FE5F6
	static Any _0x58C0F6CF(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x58C0F6CF, p0, p1, p2, p3); } // 0x58C0F6CF
	static Any _0x761F8F48(Any p0, Any p1) { return invoke<Any>(0x761F8F48, p0, p1); } // 0x761F8F48
	static void _0x033F43FA(Any p0) { invoke<Void>(0x033F43FA, p0); } // 0x033F43FA
	static void _0x4C684C81(Any p0) { invoke<Void>(0x4C684C81, p0); } // 0x4C684C81
	static Any _0x7B4C3E6F(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x7B4C3E6F, p0, p1, p2, p3); } // 0x7B4C3E6F
	static void _0x5BC276AE(Any p0, Any p1) { invoke<Void>(0x5BC276AE, p0, p1); } // 0x5BC276AE
	static void PLAY_FACIAL_ANIM(Any p0, Any p1, Any p2) { invoke<Void>(0x1F6CCDDE, p0, p1, p2); } // 0x1F6CCDDE
	static void SET_FACIAL_IDLE_ANIM_OVERRIDE(Any p0, Any p1, Any p2) { invoke<Void>(0x9BA19C13, p0, p1, p2); } // 0x9BA19C13
	static void CLEAR_FACIAL_IDLE_ANIM_OVERRIDE(Any p0) { invoke<Void>(0x5244F4E2, p0); } // 0x5244F4E2
	static void SET_PED_CAN_PLAY_GESTURE_ANIMS(Any p0, Any p1) { invoke<Void>(0xE131E3B3, p0, p1); } // 0xE131E3B3
	static void SET_PED_CAN_PLAY_VISEME_ANIMS(Any p0, Any p1, Any p2) { invoke<Void>(0xA2FDAF27, p0, p1, p2); } // 0xA2FDAF27
	static void _0xADB2511A(Any p0, Any p1) { invoke<Void>(0xADB2511A, p0, p1); } // 0xADB2511A
	static void SET_PED_CAN_PLAY_AMBIENT_ANIMS(Any p0, Any p1) { invoke<Void>(0xF8053081, p0, p1); } // 0xF8053081
	static void SET_PED_CAN_PLAY_AMBIENT_BASE_ANIMS(Any p0, Any p1) { invoke<Void>(0x5720A5DD, p0, p1); } // 0x5720A5DD
	static void _0xB7CD0A49(Any p0) { invoke<Void>(0xB7CD0A49, p0); } // 0xB7CD0A49
	static void _0x343B4DE0(Any p0, Any p1) { invoke<Void>(0x343B4DE0, p0, p1); } // 0x343B4DE0
	static void SET_PED_CAN_HEAD_IK(Any p0, Any p1) { invoke<Void>(0xD3B04476, p0, p1); } // 0xD3B04476
	static void SET_PED_CAN_LEG_IK(Any p0, Any p1) { invoke<Void>(0x9955BC6F, p0, p1); } // 0x9955BC6F
	static void _0x8E5D4EAB(Any p0, Any p1) { invoke<Void>(0x8E5D4EAB, p0, p1); } // 0x8E5D4EAB
	static void _0x7B0040A8(Any p0, Any p1) { invoke<Void>(0x7B0040A8, p0, p1); } // 0x7B0040A8
	static void _0x0FDA62DE(Any p0, Any p1) { invoke<Void>(0x0FDA62DE, p0, p1); } // 0x0FDA62DE
	static void SET_PED_CAN_USE_AUTO_CONVERSATION_LOOKAT(Any p0, Any p1) { invoke<Void>(0x584C5178, p0, p1); } // 0x584C5178
	static BOOL IS_PED_HEADTRACKING_PED(Any p0, Any p1) { return invoke<BOOL>(0x2A5DF721, p0, p1); } // 0x2A5DF721
	static BOOL IS_PED_HEADTRACKING_ENTITY(Any p0, Any p1) { return invoke<BOOL>(0x233C9ACF, p0, p1); } // 0x233C9ACF
	static void SET_PED_PRIMARY_LOOKAT(Any p0, Any p1) { invoke<Void>(0x6DEF6F1C, p0, p1); } // 0x6DEF6F1C
	static void _0xFC942D7C(Any p0, Any p1) { invoke<Void>(0xFC942D7C, p0, p1); } // 0xFC942D7C
	static void _0x89EEE07B(Any p0, Any p1) { invoke<Void>(0x89EEE07B, p0, p1); } // 0x89EEE07B
	static void SET_PED_CONFIG_FLAG(Any p0, Any p1, Any p2) { invoke<Void>(0x9CFBE10D, p0, p1, p2); } // 0x9CFBE10D
	static void SET_PED_RESET_FLAG(Any p0, Any p1, Any p2) { invoke<Void>(0xCFF6FF66, p0, p1, p2); } // 0xCFF6FF66
	static Any GET_PED_CONFIG_FLAG(Any p0, Any p1, Any p2) { return invoke<Any>(0xABE98267, p0, p1, p2); } // 0xABE98267
	static Any GET_PED_RESET_FLAG(Any p0, Any p1) { return invoke<Any>(0x2FC10D11, p0, p1); } // 0x2FC10D11
	static void SET_PED_GROUP_MEMBER_PASSENGER_INDEX(Any p0, Any p1) { invoke<Void>(0x2AB3670B, p0, p1); } // 0x2AB3670B
	static void SET_PED_CAN_EVASIVE_DIVE(Any p0, Any p1) { invoke<Void>(0x542FEB4D, p0, p1); } // 0x542FEB4D
	static BOOL IS_PED_EVASIVE_DIVING(Any p0, Any p1) { return invoke<BOOL>(0xD82829DC, p0, p1); } // 0xD82829DC
	static void SET_PED_SHOOTS_AT_COORD(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xFD64EAE5, p0, p1, p2, p3, p4); } // 0xFD64EAE5
	static void SET_PED_MODEL_IS_SUPPRESSED(Any p0, Any p1) { invoke<Void>(0x7820CA43, p0, p1); } // 0x7820CA43
	static void STOP_ANY_PED_MODEL_BEING_SUPPRESSED() { invoke<Void>(0x5AD7DC55); } // 0x5AD7DC55
	static void SET_PED_CAN_BE_TARGETED_WHEN_INJURED(Any p0, Any p1) { invoke<Void>(0x6FD9A7CD, p0, p1); } // 0x6FD9A7CD
	static void SET_PED_GENERATES_DEAD_BODY_EVENTS(Ped ped, BOOL Toggle) { invoke<Void>(0xE9B97A2B, ped, Toggle); } // 0xE9B97A2B
	static void _0xFF1F6AEB(Any p0, Any p1) { invoke<Void>(0xFF1F6AEB, p0, p1); } // 0xFF1F6AEB
	static void SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(Any p0, Any p1) { invoke<Void>(0xE9BD733A, p0, p1); } // 0xE9BD733A
	static void GIVE_PED_HELMET(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x1862A461, p0, p1, p2, p3); } // 0x1862A461
	static void REMOVE_PED_HELMET(Any p0, Any p1) { invoke<Void>(0x2086B1F0, p0, p1); } // 0x2086B1F0
	static void SET_PED_HELMET(Any p0, Any p1) { invoke<Void>(0xED366E53, p0, p1); } // 0xED366E53
	static void SET_PED_HELMET_FLAG(Any p0, Any p1) { invoke<Void>(0x12677780, p0, p1); } // 0x12677780
	static void SET_PED_HELMET_PROP_INDEX(Any p0, Any p1) { invoke<Void>(0xA316D13F, p0, p1); } // 0xA316D13F
	static void SET_PED_HELMET_TEXTURE_INDEX(Any p0, Any p1) { invoke<Void>(0x5F6C3328, p0, p1); } // 0x5F6C3328
	static BOOL IS_PED_WEARING_HELMET(Ped PedHandle) { return invoke<BOOL>(0x0D680D49, PedHandle); } // 0x0D680D49
	static void _0x24A1284E(Any p0) { invoke<Void>(0x24A1284E, p0); } // 0x24A1284E
	static Any _0x8A3A3116(Any p0) { return invoke<Any>(0x8A3A3116, p0); } // 0x8A3A3116
	static Any _0x74EB662D(Any p0) { return invoke<Any>(0x74EB662D, p0); } // 0x74EB662D
	static Any _0xFFF149FE(Any p0) { return invoke<Any>(0xFFF149FE, p0); } // 0xFFF149FE
	static void SET_PED_TO_LOAD_COVER(Any p0, Any p1) { invoke<Void>(0xCF94BA97, p0, p1); } // 0xCF94BA97
	static void SET_PED_CAN_COWER_IN_COVER(Any p0, Any p1) { invoke<Void>(0x5194658B, p0, p1); } // 0x5194658B
	static void SET_PED_CAN_PEEK_IN_COVER(Ped PedHandle, BOOL Toggle) { invoke<Void>(0xC1DAE216, PedHandle, Toggle); } // 0xC1DAE216
	static void SET_PED_PLAYS_HEAD_ON_HORN_ANIM_WHEN_DIES_IN_VEHICLE(Any p0, Any p1) { invoke<Void>(0x7C563CD2, p0, p1); } // 0x7C563CD2
	static void SET_PED_LEG_IK_MODE(Any p0, Any p1) { invoke<Void>(0xFDDB042E, p0, p1); } // 0xFDDB042E
	static void SET_PED_MOTION_BLUR(Any p0, Any p1) { invoke<Void>(0xA211A128, p0, p1); } // 0xA211A128
	static void SET_PED_CAN_SWITCH_WEAPON(int PedID, BOOL CAN_SWITCH) { invoke<Void>(0xB5F8BA28, PedID, CAN_SWITCH); } // 0xB5F8BA28
	static void SET_PED_DIES_INSTANTLY_IN_WATER(Ped PedHandle, BOOL Toggle) { invoke<Void>(0xFE2554FC, PedHandle, Toggle); } // 0xFE2554FC
	static void _0x77BB7CB8(Any p0, Any p1) { invoke<Void>(0x77BB7CB8, p0, p1); } // 0x77BB7CB8
	static void STOP_PED_WEAPON_FIRING_WHEN_DROPPED(Any p0) { invoke<Void>(0x4AC3421E, p0); } // 0x4AC3421E
	static void SET_SCRIPTED_ANIM_SEAT_OFFSET(Any p0, Any p1) { invoke<Void>(0x7CEFFA45, p0, p1); } // 0x7CEFFA45
	static void SET_PED_COMBAT_MOVEMENT(Any p0, Any p1) { invoke<Void>(0x12E62F9E, p0, p1); } // 0x12E62F9E
	static Any GET_PED_COMBAT_MOVEMENT(Any p0) { return invoke<Any>(0xF3E7730E, p0); } // 0xF3E7730E
	static void SET_PED_COMBAT_ABILITY(Ped ped, int p1) { invoke<Void>(0x6C23D329, ped, p1); } // 0x6C23D329
	static void SET_PED_COMBAT_RANGE(Ped ped, float range) { invoke<Void>(0x8818A959, ped, range); } // 0x8818A959
	static Any GET_PED_COMBAT_RANGE(Any p0) { return invoke<Any>(0x9B9B7163, p0); } // 0x9B9B7163
	static void SET_PED_COMBAT_ATTRIBUTES(Any p0, Any p1, Any p2) { invoke<Void>(0x81D64248, p0, p1, p2); } // 0x81D64248
	static void SET_PED_TARGET_LOSS_RESPONSE(Any p0, Any p1) { invoke<Void>(0xCFA613FF, p0, p1); } // 0xCFA613FF
	static Any _0x139C0875(Any p0) { return invoke<Any>(0x139C0875, p0); } // 0x139C0875
	static BOOL IS_PED_PERFORMING_STEALTH_KILL(Any p0) { return invoke<BOOL>(0x9ADD7B21, p0); } // 0x9ADD7B21
	static BOOL _0x9BE7C860(Ped PedHandle) { return invoke<BOOL>(0x9BE7C860, PedHandle); } // 0x9BE7C860
	static BOOL IS_PED_BEING_STEALTH_KILLED(Any p0) { return invoke<BOOL>(0xD044C8AF, p0); } // 0xD044C8AF
	static Any _0xAFEC26A4(Any p0) { return invoke<Any>(0xAFEC26A4, p0); } // 0xAFEC26A4
	static BOOL WAS_PED_KILLED_BY_STEALTH(Any p0) { return invoke<BOOL>(0x2EA4B54E, p0); } // 0x2EA4B54E
	static BOOL WAS_PED_KILLED_BY_TAKEDOWN(Any p0) { return invoke<BOOL>(0xBDD3CE69, p0); } // 0xBDD3CE69
	static Any _0x3993092B(Any p0) { return invoke<Any>(0x3993092B, p0); } // 0x3993092B
	static void SET_PED_FLEE_ATTRIBUTES(Any p0, Any p1, Any p2) { invoke<Void>(0xA717A875, p0, p1, p2); } // 0xA717A875
	static void SET_PED_COWER_HASH(Any p0, Any p1) { invoke<Void>(0x16F30DF4, p0, p1); } // 0x16F30DF4
	static void _0xA6F2C057(Any p0, Any p1) { invoke<Void>(0xA6F2C057, p0, p1); } // 0xA6F2C057
	static void SET_PED_STEERS_AROUND_PEDS(Ped ped, BOOL DoesSteer) { invoke<Void>(0x797CAE4F, ped, DoesSteer); } // 0x797CAE4F
	static void SET_PED_STEERS_AROUND_OBJECTS(Ped ped, BOOL DoesSteer) { invoke<Void>(0x3BD9B0A6, ped, DoesSteer); } // 0x3BD9B0A6
	static void SET_PED_STEERS_AROUND_VEHICLES(Ped ped, BOOL DoesSteer) { invoke<Void>(0x533C0651, ped, DoesSteer); } // 0x533C0651
	static void _0x2276DE0D(Any p0, Any p1) { invoke<Void>(0x2276DE0D, p0, p1); } // 0x2276DE0D
	static void _0x59C52BE6(Any p0) { invoke<Void>(0x59C52BE6, p0); } // 0x59C52BE6
	static void _0x1D87DDC1(Any p0, Any p1) { invoke<Void>(0x1D87DDC1, p0, p1); } // 0x1D87DDC1
	static void _0xB52BA5F5(Any p0) { invoke<Void>(0xB52BA5F5, p0); } // 0xB52BA5F5
	static BOOL IS_ANY_PED_NEAR_POINT(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0xFBD9B050, p0, p1, p2, p3); } // 0xFBD9B050
	static void _0x187B9070(Any p0, Any p1, Any p2) { invoke<Void>(0x187B9070, p0, p1, p2); } // 0x187B9070
	static Any _0x45037B9B(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x45037B9B, p0, p1, p2, p3, p4); } // 0x45037B9B
	static void _0x840D24D3(Any p0) { invoke<Void>(0x840D24D3, p0); } // 0x840D24D3
	static void GET_PED_FLOOD_INVINCIBILITY(Any p0, Any p1) { invoke<Void>(0x31C31DAA, p0, p1); } // 0x31C31DAA
	static void _0x9194DB71(Any p0, Any p1) { invoke<Void>(0x9194DB71, p0, p1); } // 0x9194DB71
	static BOOL IS_TRACKED_PED_VISIBLE(Any p0) { return invoke<BOOL>(0x33248CC1, p0); } // 0x33248CC1
	static Any _0x5B1B70AA(Any p0) { return invoke<Any>(0x5B1B70AA, p0); } // 0x5B1B70AA
	static BOOL IS_PED_TRACKED(Any p0) { return invoke<BOOL>(0x7EB613D9, p0); } // 0x7EB613D9
	static BOOL HAS_PED_RECEIVED_EVENT(Any p0, Any p1) { return invoke<BOOL>(0xECD73DB0, p0, p1); } // 0xECD73DB0
	static Any _0x74A0F291(Any p0, Any p1) { return invoke<Any>(0x74A0F291, p0, p1); } // 0x74A0F291
	static Any GET_PED_BONE_INDEX(Ped PedHandle, int BoneIndex) { return invoke<Any>(0x259C6BA2, PedHandle, BoneIndex); } // 0x259C6BA2
	static Any GET_PED_RAGDOLL_BONE_INDEX(Any p0, Any p1) { return invoke<Any>(0x849F0716, p0, p1); } // 0x849F0716
	static void SET_PED_ENVEFF_SCALE(Any p0, Any p1) { invoke<Void>(0xFC1CFC27, p0, p1); } // 0xFC1CFC27
	static Any GET_PED_ENVEFF_SCALE(Any p0) { return invoke<Any>(0xA3421E39, p0); } // 0xA3421E39
	static void SET_ENABLE_PED_ENVEFF_SCALE(Any p0, Any p1) { invoke<Void>(0xC70F4A84, p0, p1); } // 0xC70F4A84
	static void _0x3B882533(Any p0, Any p1) { invoke<Void>(0x3B882533, p0, p1); } // 0x3B882533
	static void _0x87A0C174(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x87A0C174, p0, p1, p2, p3); } // 0x87A0C174
	static void _0x7BD26837(Any p0, Any p1) { invoke<Void>(0x7BD26837, p0, p1); } // 0x7BD26837
	static void _0x98E29ED0(Any p0, Any p1) { invoke<Void>(0x98E29ED0, p0, p1); } // 0x98E29ED0
	static Any _0xD315978E(Any p0) { return invoke<Any>(0xD315978E, p0); } // 0xD315978E
	static Any CREATE_SYNCHRONIZED_SCENE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0xFFDDF8FA, p0, p1, p2, p3, p4, p5, p6); } // 0xFFDDF8FA
	static Any _0xF3876894(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xF3876894, p0, p1, p2, p3, p4); } // 0xF3876894
	static BOOL IS_SYNCHRONIZED_SCENE_RUNNING(Any p0) { return invoke<BOOL>(0x57A282F1, p0); } // 0x57A282F1
	static void SET_SYNCHRONIZED_SCENE_ORIGIN(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x2EC2A0B2, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x2EC2A0B2
	static void SET_SYNCHRONIZED_SCENE_PHASE(Any p0, Any p1) { invoke<Void>(0xF5AB0D98, p0, p1); } // 0xF5AB0D98
	static Any GET_SYNCHRONIZED_SCENE_PHASE(Any p0) { return invoke<Any>(0xB0B2C852, p0); } // 0xB0B2C852
	static void SET_SYNCHRONIZED_SCENE_RATE(Any p0, Any p1) { invoke<Void>(0xF10112FD, p0, p1); } // 0xF10112FD
	static Any GET_SYNCHRONIZED_SCENE_RATE(Any p0) { return invoke<Any>(0x89365F0D, p0); } // 0x89365F0D
	static void SET_SYNCHRONIZED_SCENE_LOOPED(Any p0, Any p1) { invoke<Void>(0x32ED9F82, p0, p1); } // 0x32ED9F82
	static BOOL IS_SYNCHRONIZED_SCENE_LOOPED(Any p0) { return invoke<BOOL>(0x47D87A84, p0); } // 0x47D87A84
	static void _0x2DE48DA1(Any p0, Any p1) { invoke<Void>(0x2DE48DA1, p0, p1); } // 0x2DE48DA1
	static Any _0x72CF2514(Any p0) { return invoke<Any>(0x72CF2514, p0); } // 0x72CF2514
	static void ATTACH_SYNCHRONIZED_SCENE_TO_ENTITY(Any p0, Any p1, Any p2) { invoke<Void>(0xE9BA6189, p0, p1, p2); } // 0xE9BA6189
	static void DETACH_SYNCHRONIZED_SCENE(Any p0) { invoke<Void>(0x52A1CAB2, p0); } // 0x52A1CAB2
	static void _0xBF7F9035(Any p0) { invoke<Void>(0xBF7F9035, p0); } // 0xBF7F9035
	static Any FORCE_PED_MOTION_STATE(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x164DDEFF, p0, p1, p2, p3, p4); } // 0x164DDEFF
	static void SET_PED_MAX_MOVE_BLEND_RATIO(Any p0, Any p1) { invoke<Void>(0xEAD0269A, p0, p1); } // 0xEAD0269A
	static void SET_PED_MIN_MOVE_BLEND_RATIO(Any p0, Any p1) { invoke<Void>(0x383EC364, p0, p1); } // 0x383EC364
	static void SET_PED_MOVE_RATE_OVERRIDE(Any p0, Any p1) { invoke<Void>(0x900008C6, p0, p1); } // 0x900008C6
	static Any _0x79543043(Any p0, Any p1) { return invoke<Any>(0x79543043, p0, p1); } // 0x79543043
	static int GET_PED_NEARBY_VEHICLES(Ped PedHandle, int* sizeAndVehs) { return invoke<int>(0xCB716F68, PedHandle, sizeAndVehs); } // 0xCB716F68
	static int GET_PED_NEARBY_PEDS(Ped PedHandle, int* PToArray, int p2) { return invoke<int>(0x4D3325F4, PedHandle, PToArray, p2); } // 0x4D3325F4
	static Any _0xF9FB4B71(Any p0) { return invoke<Any>(0xF9FB4B71, p0); } // 0xF9FB4B71
	static BOOL IS_PED_USING_ACTION_MODE(Any p0) { return invoke<BOOL>(0x5AE7EDA2, p0); } // 0x5AE7EDA2
	static void SET_PED_USING_ACTION_MODE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x8802F696, p0, p1, p2, p3); } // 0x8802F696
	static void SET_PED_CAPSULE(Any p0, Any p1) { invoke<Void>(0xB153E1B9, p0, p1); } // 0xB153E1B9
	static Any REGISTER_PEDHEADSHOT(Any p0) { return invoke<Any>(0xFFE2667B, p0); } // 0xFFE2667B
	static Any _0x4DD03628(Any p0) { return invoke<Any>(0x4DD03628, p0); } // 0x4DD03628
	static void UNREGISTER_PEDHEADSHOT(Any p0) { invoke<Void>(0x0879AE45, p0); } // 0x0879AE45
	static BOOL IS_PEDHEADSHOT_VALID(Any p0) { return invoke<BOOL>(0x0B1080C4, p0); } // 0x0B1080C4
	static BOOL IS_PEDHEADSHOT_READY(Any p0) { return invoke<BOOL>(0x761CD02E, p0); } // 0x761CD02E
	static Any GET_PEDHEADSHOT_TXD_STRING(Any p0) { return invoke<Any>(0x76D28E96, p0); } // 0x76D28E96
	static void SET_PEDHEADSHOT_CUSTOM_LIGHTING(Any p0) { invoke<Void>(0xAB688DAB, p0); } // 0xAB688DAB
	static void SET_PEDHEADSHOT_CUSTOM_LIGHT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0xF48A9155, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xF48A9155
	static Any _0x10F2C023(Any p0) { return invoke<Any>(0x10F2C023, p0); } // 0x10F2C023
	static void _0x0DBB2FA7(Any p0) { invoke<Void>(0x0DBB2FA7, p0); } // 0x0DBB2FA7
	static Any _0x810158F8() { return invoke<Any>(0x810158F8); } // 0x810158F8
	static Any _0x05023F8F() { return invoke<Any>(0x05023F8F); } // 0x05023F8F
	static Any _0xAA39FD6C() { return invoke<Any>(0xAA39FD6C); } // 0xAA39FD6C
	static void _0xEF9142DB(Any p0, Any p1) { invoke<Void>(0xEF9142DB, p0, p1); } // 0xEF9142DB
	static void _0x0688DE64(Any p0) { invoke<Void>(0x0688DE64, p0); } // 0x0688DE64
	static void _0x909A1D76(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x909A1D76, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x909A1D76
	static void _0x4AAD0ECB(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0x4AAD0ECB, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x4AAD0ECB
	static void _0x492C9E46() { invoke<Void>(0x492C9E46); } // 0x492C9E46
	static Any _0x814A28F4() { return invoke<Any>(0x814A28F4); } // 0x814A28F4
	static Any _0x0B60D2BA() { return invoke<Any>(0x0B60D2BA); } // 0x0B60D2BA
	static Any _0x6B83ABDF() { return invoke<Any>(0x6B83ABDF); } // 0x6B83ABDF
	static Any _0xF46B4DC8() { return invoke<Any>(0xF46B4DC8); } // 0xF46B4DC8
	static void _0x36A4AC65(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x36A4AC65, p0, p1, p2, p3); } // 0x36A4AC65
	static void _0xBA699DDF(Any p0, Any p1) { invoke<Void>(0xBA699DDF, p0, p1); } // 0xBA699DDF
	static void SET_IK_TARGET(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0x6FE5218C, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x6FE5218C
	static void _0xFB4000DC(Any p0) { invoke<Void>(0xFB4000DC, p0); } // 0xFB4000DC
	static void REQUEST_ACTION_MODE_ASSET(Any p0) { invoke<Void>(0x572BA553, p0); } // 0x572BA553
	static BOOL HAS_ACTION_MODE_ASSET_LOADED(Any p0) { return invoke<BOOL>(0xF7EB2BF1, p0); } // 0xF7EB2BF1
	static void REMOVE_ACTION_MODE_ASSET(Any p0) { invoke<Void>(0x3F480F92, p0); } // 0x3F480F92
	static void REQUEST_STEALTH_MODE_ASSET(Any p0) { invoke<Void>(0x280A004A, p0); } // 0x280A004A
	static BOOL HAS_STEALTH_MODE_ASSET_LOADED(Any p0) { return invoke<BOOL>(0x39245667, p0); } // 0x39245667
	static void REMOVE_STEALTH_MODE_ASSET(Any p0) { invoke<Void>(0x8C0B243A, p0); } // 0x8C0B243A
	static void SET_PED_LOD_MULTIPLIER(Any p0, Any p1) { invoke<Void>(0x1D2B5C70, p0, p1); } // 0x1D2B5C70
	static void _0x2F9550C2(Any p0, Any p1, Any p2) { invoke<Void>(0x2F9550C2, p0, p1, p2); } // 0x2F9550C2
	static void _0x37DBC2AD(Any p0, Any p1) { invoke<Void>(0x37DBC2AD, p0, p1); } // 0x37DBC2AD
	static void _0xC0F1BC91(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xC0F1BC91, p0, p1, p2, p3); } // 0xC0F1BC91
	static Any _0x1A464167(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x1A464167, p0, p1, p2, p3, p4); } // 0x1A464167
	static Any _0xD0567D41(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0xD0567D41, p0, p1, p2, p3, p4, p5); } // 0xD0567D41
	static void _0x4BBE5E2C(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x4BBE5E2C, p0, p1, p2, p3, p4); } // 0x4BBE5E2C
	static void _0xA89A53F2(Any p0) { invoke<Void>(0xA89A53F2, p0); } // 0xA89A53F2
}

namespace VEHICLE
{
	static Vehicle CREATE_VEHICLE(Hash VehicleHash, float xCoord, float yCoord, float zCoord, float Heading, BOOL networkHandle, BOOL vehiclehandle) { return invoke<Vehicle>(0xDD75460A, VehicleHash, xCoord, yCoord, zCoord, Heading, networkHandle, vehiclehandle); } // 0xDD75460A
	static void DELETE_VEHICLE(Vehicle* vehicle) { invoke<Void>(0x9803AF60, vehicle); } // 0x9803AF60
	static void _0xBB54ECCA(Vehicle p0, BOOL p1) { invoke<Void>(0xBB54ECCA, p0, p1); } // 0xBB54ECCA
	static void SET_VEHICLE_ALLOW_NO_PASSENGERS_LOCKON(Any p0, Any p1) { invoke<Void>(0x8BAAC437, p0, p1); } // 0x8BAAC437
	static int _0xFBDE9FD8(Vehicle p0) { return invoke<int>(0xFBDE9FD8, p0); } // 0xFBDE9FD8
	static BOOL IS_VEHICLE_MODEL(Vehicle hash, BOOL toggle) { return invoke<BOOL>(0x013B10B6, hash, toggle); } // 0x013B10B6
	static BOOL DOES_SCRIPT_VEHICLE_GENERATOR_EXIST(Any p0) { return invoke<BOOL>(0xF6BDDA30, p0); } // 0xF6BDDA30
	static Any CREATE_SCRIPT_VEHICLE_GENERATOR(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14, Any p15, Any p16) { return invoke<Any>(0x25A9A261, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16); } // 0x25A9A261
	static void DELETE_SCRIPT_VEHICLE_GENERATOR(Any p0) { invoke<Void>(0xE4328E3F, p0); } // 0xE4328E3F
	static void SET_SCRIPT_VEHICLE_GENERATOR(Any p0, Any p1) { invoke<Void>(0x40D73747, p0, p1); } // 0x40D73747
	static void SET_ALL_VEHICLE_GENERATORS_ACTIVE_IN_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0xB4E0E69A, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xB4E0E69A
	static void SET_ALL_VEHICLE_GENERATORS_ACTIVE() { invoke<Void>(0xAB1FDD76); } // 0xAB1FDD76
	static void SET_ALL_LOW_PRIORITY_VEHICLE_GENERATORS_ACTIVE(Any p0) { invoke<Void>(0x87F767F2, p0); } // 0x87F767F2
	static void _0x935A95DA(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x935A95DA, p0, p1, p2, p3); } // 0x935A95DA
	static void _0x6C73E45A() { invoke<Void>(0x6C73E45A); } // 0x6C73E45A
	static BOOL SET_VEHICLE_ON_GROUND_PROPERLY(Vehicle vehicle) { return invoke<BOOL>(0xE14FDBA6, vehicle); } // 0xE14FDBA6
	static Any SET_ALL_VEHICLES_SPAWN(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xA0909ADB, p0, p1, p2, p3); } // 0xA0909ADB
	static BOOL IS_VEHICLE_STUCK_ON_ROOF(Vehicle Hash) { return invoke<BOOL>(0x18D07C6C, Hash); } // 0x18D07C6C
	static void ADD_VEHICLE_UPSIDEDOWN_CHECK(Any p0) { invoke<Void>(0x3A13D384, p0); } // 0x3A13D384
	static void REMOVE_VEHICLE_UPSIDEDOWN_CHECK(Any p0) { invoke<Void>(0xF390BA1B, p0); } // 0xF390BA1B
	static BOOL IS_VEHICLE_STOPPED(Any p0) { return invoke<BOOL>(0x655F072C, p0); } // 0x655F072C
	static int GET_VEHICLE_NUMBER_OF_PASSENGERS(Vehicle Vehicle) { return invoke<int>(0x1EF20849, Vehicle); } // 0x1EF20849
	static int GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(Vehicle Vehicle) { return invoke<int>(0x0A2FC08C, Vehicle); } // 0x0A2FC08C
	static int _GET_VEHICLE_MODEL_MAX_NUMBER_OF_PASSENGERS(Hash VehicleModel) { return invoke<int>(0x838F7BF7, VehicleModel); } // 0x838F7BF7
	static BOOL _769E5CF2(Vehicle Vehicle, int i1) { return invoke<BOOL>(0x769E5CF2, Vehicle, i1); } // 0x769E5CF2
	static void SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(Any p0) { invoke<Void>(0xF4187E51, p0); } // 0xF4187E51
	static void SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(Any p0) { invoke<Void>(0x543F712B, p0); } // 0x543F712B
	static void SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(Any p0) { invoke<Void>(0xDD46CEBE, p0); } // 0xDD46CEBE
	static void _0x09462665(Any p0) { invoke<Void>(0x09462665, p0); } // 0x09462665
	static void _0xDAE2A2BE(Any p0) { invoke<Void>(0xDAE2A2BE, p0); } // 0xDAE2A2BE
	static void SET_FAR_DRAW_VEHICLES(Any p0) { invoke<Void>(0x9F019C49, p0); } // 0x9F019C49
	static void SET_NUMBER_OF_PARKED_VEHICLES(int value) { invoke<Void>(0x206A58E8, value); } // 0x206A58E8
	static void SET_VEHICLE_DOORS_LOCKED(Vehicle hash, int door) { invoke<Void>(0x4CDD35D0, hash, door); } // 0x4CDD35D0
	static void SET_PED_TARGETTABLE_VEHICLE_DESTROY(Any p0, Any p1, Any p2) { invoke<Void>(0xD61D182D, p0, p1, p2); } // 0xD61D182D
	static void DISABLE_VEHICLE_IMPACT_EXPLOSION_ACTIVATION(Any p0, Any p1) { invoke<Void>(0xC54156A9, p0, p1); } // 0xC54156A9
	static void SET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(Any p0, Any p1, Any p2) { invoke<Void>(0x49829236, p0, p1, p2); } // 0x49829236
	static Any GET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(Any p0, Any p1) { return invoke<Any>(0x1DC50247, p0, p1); } // 0x1DC50247
	static void SET_VEHICLE_DOORS_LOCKED_FOR_ALL_PLAYERS(Any p0, Any p1) { invoke<Void>(0x891BA8A4, p0, p1); } // 0x891BA8A4
	static void _0xE4EF6514(Any p0, Any p1) { invoke<Void>(0xE4EF6514, p0, p1); } // 0xE4EF6514
	static void SET_VEHICLE_DOORS_LOCKED_FOR_TEAM(Any p0, Any p1, Any p2) { invoke<Void>(0x4F85E783, p0, p1, p2); } // 0x4F85E783
	static void EXPLODE_VEHICLE(Vehicle vehicle, BOOL b1, BOOL b2) { invoke<Void>(0xBEDEACEB, vehicle, b1, b2); } // 0xBEDEACEB
	static void SET_VEHICLE_OUT_OF_CONTROL(Any p0, Any p1, Any p2) { invoke<Void>(0x3764D734, p0, p1, p2); } // 0x3764D734
	static void SET_VEHICLE_TIMED_EXPLOSION(Any p0, Any p1, Any p2) { invoke<Void>(0xDB8CB8E2, p0, p1, p2); } // 0xDB8CB8E2
	static void _0x811373DE(Any p0) { invoke<Void>(0x811373DE, p0); } // 0x811373DE
	static Any _0xA4E69134() { return invoke<Any>(0xA4E69134); } // 0xA4E69134
	static void _0x65255524() { invoke<Void>(0x65255524); } // 0x65255524
	static Any _0xE39DAF36(Any p0) { return invoke<Any>(0xE39DAF36, p0); } // 0xE39DAF36
	static void SET_TAXI_LIGHTS(Vehicle vehicle, BOOL state) { invoke<Void>(0x68639D85, vehicle, state); } // 0x68639D85
	static BOOL IS_TAXI_LIGHT_ON(Vehicle vehicle) { return invoke<BOOL>(0x6FC4924A, vehicle); } // 0x6FC4924A
	static BOOL IS_VEHICLE_IN_GARAGE_AREA(Any p0, Any p1) { return invoke<BOOL>(0xA90EC257, p0, p1); } // 0xA90EC257
	static void SET_VEHICLE_COLOURS(Any p0, Any p1, Any p2) { invoke<Void>(0x57F24253, p0, p1, p2); } // 0x57F24253
	static void SET_VEHICLE_FULLBEAM(Vehicle vehicle, BOOL state) { invoke<Void>(0x9C49CC15, vehicle, state); } // 0x9C49CC15
	static void STEER_UNLOCK_BIAS(Any p0, Any p1) { invoke<Void>(0xA59E3DCD, p0, p1); } // 0xA59E3DCD
	static void SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle vehicle, int r, int g, int b) { invoke<Void>(0x8DF9F9BC, vehicle, r, g, b); } // 0x8DF9F9BC
	static void GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle vehicle, int r, int g, int b) { invoke<Void>(0x1C2B9FEF, vehicle, r, g, b); } // 0x1C2B9FEF
	static void CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle vehicle) { invoke<Void>(0x51E1E33D, vehicle); } // 0x51E1E33D
	static BOOL GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(Vehicle vehicle) { return invoke<BOOL>(0xD7EC8760, vehicle); } // 0xD7EC8760
	static void SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle vehicle, int r, int g, int b) { invoke<Void>(0x9D77259E, vehicle, r, g, b); } // 0x9D77259E
	static void GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x3FF247A2, p0, p1, p2, p3); } // 0x3FF247A2
	static void CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle vehicle) { invoke<Void>(0x7CE00B29, vehicle); } // 0x7CE00B29
	static BOOL GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(Vehicle vehicle) { return invoke<BOOL>(0x288AD228, vehicle); } // 0x288AD228
	static void _0x8332730C(Any p0, Any p1) { invoke<Void>(0x8332730C, p0, p1); } // 0x8332730C
	static Any _0xD5F1EEE1(Any p0) { return invoke<Any>(0xD5F1EEE1, p0); } // 0xD5F1EEE1
	static void SET_CAN_RESPRAY_VEHICLE(Vehicle vehicle, BOOL state) { invoke<Void>(0x37677590, vehicle, state); } // 0x37677590
	static void _0x54E9EE75(Any p0, Any p1) { invoke<Void>(0x54E9EE75, p0, p1); } // 0x54E9EE75
	static void _0x4A46E814(Vehicle vehicle, BOOL p1, float X, float Y, float z) { invoke<Void>(0x4A46E814, vehicle, p1, X, Y, z); } // 0x4A46E814
	static void SET_BOAT_ANCHOR(Vehicle vehicle, BOOL p1) { invoke<Void>(0xA3906284, vehicle, p1); } // 0xA3906284
	static void _0x0ED84792(Any p0, Any p1) { invoke<Void>(0x0ED84792, p0, p1); } // 0x0ED84792
	static void _0xA739012A(Any p0, Any p1) { invoke<Void>(0xA739012A, p0, p1); } // 0xA739012A
	static void _0x66FA450C(Any p0, Any p1) { invoke<Void>(0x66FA450C, p0, p1); } // 0x66FA450C
	static void _0x35614622(Any p0, Any p1) { invoke<Void>(0x35614622, p0, p1); } // 0x35614622
	static void SET_VEHICLE_SIREN(Vehicle vehicle, BOOL siren) { invoke<Void>(0x4AC1EFC7, vehicle, siren); } // 0x4AC1EFC7
	static BOOL IS_VEHICLE_SIREN_ON(Vehicle vehicle) { return invoke<BOOL>(0x25EB5873, vehicle); } // 0x25EB5873
	static void SET_VEHICLE_STRONG(Vehicle vehicle, BOOL p0) { invoke<Void>(0xC758D19F, vehicle, p0); } // 0xC758D19F
	static void REMOVE_VEHICLE_STUCK_CHECK(Any p0) { invoke<Void>(0x81594917, p0); } // 0x81594917
	static void GET_VEHICLE_COLOURS(Vehicle vehicle, int* col1, int* col2) { invoke<Void>(0x40D82D88, vehicle, col1, col2); } // 0x40D82D88
	static BOOL IS_VEHICLE_SEAT_FREE(Vehicle vehicle, int seatIndex) { return invoke<BOOL>(0xDAF42B02, vehicle, seatIndex); } // 0xDAF42B02
	static Ped GET_PED_IN_VEHICLE_SEAT(Vehicle vehicle, int index) { return invoke<Ped>(0x388FDE9A, vehicle, index); } // 0x388FDE9A
	static Any _0xF7C6792D(Any p0, Any p1) { return invoke<Any>(0xF7C6792D, p0, p1); } // 0xF7C6792D
	static Any GET_VEHICLE_LIGHTS_STATE(Any p0, Any p1, Any p2) { return invoke<Any>(0x7C278621, p0, p1, p2); } // 0x7C278621
	static BOOL IS_VEHICLE_TYRE_BURST(Vehicle vehicle, int wheelID, Any p2) { return invoke<BOOL>(0x48C80210, vehicle, wheelID, p2); } // 0x48C80210
	static void SET_VEHICLE_FORWARD_SPEED(Vehicle vehicle, float speed) { invoke<Void>(0x69880D14, vehicle, speed); } // 0x69880D14
	static void _0xCBC7D3C8(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xCBC7D3C8, p0, p1, p2, p3); } // 0xCBC7D3C8
	static void _0x943A6CFC(Any p0, Any p1) { invoke<Void>(0x943A6CFC, p0, p1); } // 0x943A6CFC
	static Any SET_PED_ENABLED_BIKE_RINGTONE(Any p0, Any p1) { return invoke<Any>(0x7FB25568, p0, p1); } // 0x7FB25568
	static Any _0x593143B9(Any p0) { return invoke<Any>(0x593143B9, p0); } // 0x593143B9
	static Any _0x70DD5E25(Any p0) { return invoke<Any>(0x70DD5E25, p0); } // 0x70DD5E25
	static Any _0xFBF5536A(Any p0, Any p1) { return invoke<Any>(0xFBF5536A, p0, p1); } // 0xFBF5536A
	static void _0x20AB5783(Any p0, Any p1) { invoke<Void>(0x20AB5783, p0, p1); } // 0x20AB5783
	static void _0x0F11D01F(Any p0) { invoke<Void>(0x0F11D01F, p0); } // 0x0F11D01F
	static void _0xAE040377(Any p0, Any p1) { invoke<Void>(0xAE040377, p0, p1); } // 0xAE040377
	static void _0x4C0E4031(Any p0, Any p1) { invoke<Void>(0x4C0E4031, p0, p1); } // 0x4C0E4031
	static Any _0x6346B7CC(Any p0) { return invoke<Any>(0x6346B7CC, p0); } // 0x6346B7CC
	static void _0xCCB41A55(Any p0, Any p1) { invoke<Void>(0xCCB41A55, p0, p1); } // 0xCCB41A55
	static void SET_VEHICLE_TYRE_BURST(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x89D28068, p0, p1, p2, p3); } // 0x89D28068
	static void SET_VEHICLE_DOORS_SHUT(Vehicle vehicle, int index) { invoke<Void>(0xBB1FF6E7, vehicle, index); } // 0xBB1FF6E7
	static void SET_VEHICLE_TYRES_CAN_BURST(Vehicle vehicle, BOOL value) { invoke<Void>(0xA198DB54, vehicle, value); } // 0xA198DB54
	static BOOL GET_VEHICLE_TYRES_CAN_BURST(Vehicle vehicle) { return invoke<BOOL>(0x4D76CD2F, vehicle); } // 0x4D76CD2F
	static void SET_VEHICLE_WHEELS_CAN_BREAK(Vehicle vehicle, BOOL enabled) { invoke<Void>(0x829ED654, vehicle, enabled); } // 0x829ED654
	static void SET_VEHICLE_DOOR_OPEN(Vehicle vehicle, int doorIndex, BOOL loose, BOOL openInstantly) { invoke<Void>(0xBB75D38B, vehicle, doorIndex, loose, openInstantly); } // 0xBB75D38B
	static void REMOVE_VEHICLE_WINDOW(Vehicle vehicle, int windowIndex) { invoke<Void>(0xBB8104A3, vehicle, windowIndex); } // 0xBB8104A3
	static void ROLL_DOWN_WINDOWS(Vehicle vehicle) { invoke<Void>(0x51A16DC6, vehicle); } // 0x51A16DC6
	static void ROLL_DOWN_WINDOW(Vehicle vehicle, int windowIndex) { invoke<Void>(0xF840134C, vehicle, windowIndex); } // 0xF840134C
	static void ROLL_UP_WINDOW(Vehicle vehicle, int windowIndex) { invoke<Void>(0x83B7E06A, vehicle, windowIndex); } // 0x83B7E06A
	static void SMASH_VEHICLE_WINDOW(Vehicle vehicle, int index) { invoke<Void>(0xDDD9A8C2, vehicle, index); } // 0xDDD9A8C2
	static void FIX_VEHICLE_WINDOW(Vehicle vehicle, int index) { invoke<Void>(0x6B8E990D, vehicle, index); } // 0x6B8E990D
	static void _DETACH_VEHICLE_WINDSCREEN(Vehicle vehicleHandle) { invoke<Void>(0xCC95C96B, vehicleHandle); } // 0xCC95C96B
	static void _0xFDA7B6CA(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xFDA7B6CA, p0, p1, p2, p3); } // 0xFDA7B6CA
	static void SET_VEHICLE_LIGHTS(Any p0, Any p1) { invoke<Void>(0xE8930226, p0, p1); } // 0xE8930226
	static void _0x4221E435(Any p0, Any p1) { invoke<Void>(0x4221E435, p0, p1); } // 0x4221E435
	static void SET_VEHICLE_ALARM(Vehicle vehicle, BOOL state) { invoke<Void>(0x24877D84, vehicle, state); } // 0x24877D84
	static void START_VEHICLE_ALARM(Vehicle vehicle) { invoke<Void>(0x5B451FF7, vehicle); } // 0x5B451FF7
	static BOOL IS_VEHICLE_ALARM_ACTIVATED(Vehicle vehicle) { return invoke<BOOL>(0xF2630A4C, vehicle); } // 0xF2630A4C
	static void SET_VEHICLE_INTERIORLIGHT(Vehicle vehicle, BOOL Toggle) { invoke<Void>(0x9AD1FE1E, vehicle, Toggle); } // 0x9AD1FE1E
	static void SET_VEHICLE_LIGHT_MULTIPLIER(Vehicle vehicle, float multiplier) { invoke<Void>(0x48039D6A, vehicle, multiplier); } // 0x48039D6A
	static void ATTACH_VEHICLE_TO_TRAILER(Any p0, Any p1, Any p2) { invoke<Void>(0x2133977F, p0, p1, p2); } // 0x2133977F
	static void _0x12AC1A16(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { invoke<Void>(0x12AC1A16, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0x12AC1A16
	static void _0x40C4763F(Any p0, Any p1, Any p2) { invoke<Void>(0x40C4763F, p0, p1, p2); } // 0x40C4763F
	static void DETACH_VEHICLE_FROM_TRAILER(Any p0) { invoke<Void>(0xB5DBF91D, p0); } // 0xB5DBF91D
	static BOOL IS_VEHICLE_ATTACHED_TO_TRAILER(Vehicle vehicle) { return invoke<BOOL>(0xE142BBCC, vehicle); } // 0xE142BBCC
	static void _0xE74E85CE(Any p0, Any p1) { invoke<Void>(0xE74E85CE, p0, p1); } // 0xE74E85CE
	static void _0x06C47A6F(Any p0) { invoke<Void>(0x06C47A6F, p0); } // 0x06C47A6F
	static void SET_VEHICLE_TYRE_FIXED(Vehicle vehicle, int tyreIndex) { invoke<Void>(0xA42EFA6B, vehicle, tyreIndex); } // 0xA42EFA6B
	static void SET_VEHICLE_NUMBER_PLATE_TEXT(Vehicle vehicle, char* plateText) { invoke<Void>(0x400F9556, vehicle, plateText); } // 0x400F9556
	static char* GET_VEHICLE_NUMBER_PLATE_TEXT(Vehicle vehicle) { return invoke<char*>(0xE8522D58, vehicle); } // 0xE8522D58
	static Any GET_NUMBER_OF_VEHICLE_NUMBER_PLATES() { return invoke<Any>(0xD24BC1AE); } // 0xD24BC1AE
	static void SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Vehicle vehicle, int PlateType) { invoke<Void>(0xA1A1890E, vehicle, PlateType); } // 0xA1A1890E
	static int GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Vehicle vehicle) { return invoke<int>(0x499747B6, vehicle); } // 0x499747B6
	static void SET_RANDOM_TRAINS(Any p0) { invoke<Void>(0xD461CA7F, p0); } // 0xD461CA7F
	static Any CREATE_MISSION_TRAIN(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xD4C2EAFD, p0, p1, p2, p3, p4); } // 0xD4C2EAFD
	static void SWITCH_TRAIN_TRACK(Any p0, Any p1) { invoke<Void>(0x68BFDD61, p0, p1); } // 0x68BFDD61
	static void _0xD5774FB7(Any p0, Any p1) { invoke<Void>(0xD5774FB7, p0, p1); } // 0xD5774FB7
	static void DELETE_ALL_TRAINS() { invoke<Void>(0x83DE7ABF); } // 0x83DE7ABF
	static void SET_TRAIN_SPEED(Any p0, Any p1) { invoke<Void>(0xDFC35E4D, p0, p1); } // 0xDFC35E4D
	static void SET_TRAIN_CRUISE_SPEED(Any p0, Any p1) { invoke<Void>(0xB507F51D, p0, p1); } // 0xB507F51D
	static void SET_RANDOM_BOATS(Any p0) { invoke<Void>(0xB505BD89, p0); } // 0xB505BD89
	static void SET_GARBAGE_TRUCKS(Any p0) { invoke<Void>(0xD9ABB0FF, p0); } // 0xD9ABB0FF
	static BOOL DOES_VEHICLE_HAVE_STUCK_VEHICLE_CHECK(Any p0) { return invoke<BOOL>(0x5D91D9AC, p0); } // 0x5D91D9AC
	static Any GET_VEHICLE_RECORDING_ID(Any p0, Any p1) { return invoke<Any>(0x328D601D, p0, p1); } // 0x328D601D
	static void REQUEST_VEHICLE_RECORDING(Any p0, Any p1) { invoke<Void>(0x91AFEFD9, p0, p1); } // 0x91AFEFD9
	static BOOL HAS_VEHICLE_RECORDING_BEEN_LOADED(Any p0, Any p1) { return invoke<BOOL>(0xF52CD7F5, p0, p1); } // 0xF52CD7F5
	static void REMOVE_VEHICLE_RECORDING(Any p0, Any p1) { invoke<Void>(0xD3C05B00, p0, p1); } // 0xD3C05B00
	static Vector3 _0xF31973BB(Any p0, Any p1) { return invoke<Vector3>(0xF31973BB, p0, p1); } // 0xF31973BB
	static Vector3 GET_POSITION_OF_VEHICLE_RECORDING_AT_TIME(Any p0, Any p1, Any p2) { return invoke<Vector3>(0x7178558D, p0, p1, p2); } // 0x7178558D
	static Vector3 _0x4D1C15C2(Any p0, Any p1) { return invoke<Vector3>(0x4D1C15C2, p0, p1); } // 0x4D1C15C2
	static Vector3 GET_ROTATION_OF_VEHICLE_RECORDING_AT_TIME(Any p0, Any p1, Any p2) { return invoke<Vector3>(0xD96DEC68, p0, p1, p2); } // 0xD96DEC68
	static Any GET_TOTAL_DURATION_OF_VEHICLE_RECORDING_ID(Any p0) { return invoke<Any>(0x7116785E, p0); } // 0x7116785E
	static Any GET_TOTAL_DURATION_OF_VEHICLE_RECORDING(Any p0, Any p1) { return invoke<Any>(0x5B35EEB7, p0, p1); } // 0x5B35EEB7
	static Any GET_POSITION_IN_RECORDING(Any p0) { return invoke<Any>(0x7DCD644C, p0); } // 0x7DCD644C
	static Any GET_TIME_POSITION_IN_RECORDING(Any p0) { return invoke<Any>(0xF8C3E4A2, p0); } // 0xF8C3E4A2
	static void START_PLAYBACK_RECORDED_VEHICLE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xCF614CA8, p0, p1, p2, p3); } // 0xCF614CA8
	static void START_PLAYBACK_RECORDED_VEHICLE_WITH_FLAGS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x4E721AD2, p0, p1, p2, p3, p4, p5); } // 0x4E721AD2
	static void _0x01B91CD0(Any p0, Any p1) { invoke<Void>(0x01B91CD0, p0, p1); } // 0x01B91CD0
	static void STOP_PLAYBACK_RECORDED_VEHICLE(Any p0) { invoke<Void>(0xAE99C57C, p0); } // 0xAE99C57C
	static void PAUSE_PLAYBACK_RECORDED_VEHICLE(Any p0) { invoke<Void>(0xCCF54912, p0); } // 0xCCF54912
	static void UNPAUSE_PLAYBACK_RECORDED_VEHICLE(Any p0) { invoke<Void>(0x59060F75, p0); } // 0x59060F75
	static BOOL IS_PLAYBACK_GOING_ON_FOR_VEHICLE(Any p0) { return invoke<BOOL>(0x61F7650D, p0); } // 0x61F7650D
	static BOOL IS_PLAYBACK_USING_AI_GOING_ON_FOR_VEHICLE(Any p0) { return invoke<BOOL>(0x63022C58, p0); } // 0x63022C58
	static Any GET_CURRENT_PLAYBACK_FOR_VEHICLE(Any p0) { return invoke<Any>(0xA3F44390, p0); } // 0xA3F44390
	static void SKIP_TO_END_AND_STOP_PLAYBACK_RECORDED_VEHICLE(Any p0) { invoke<Void>(0x8DEA18C8, p0); } // 0x8DEA18C8
	static void SET_PLAYBACK_SPEED(Any p0, float speed) { invoke<Void>(0x684E26E4, p0, speed); } // 0x684E26E4
	static void START_PLAYBACK_RECORDED_VEHICLE_USING_AI(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x8DE8E24E, p0, p1, p2, p3, p4); } // 0x8DE8E24E
	static void SKIP_TIME_IN_PLAYBACK_RECORDED_VEHICLE(Any p0, Any p1) { invoke<Void>(0xCF3EFA4B, p0, p1); } // 0xCF3EFA4B
	static void SET_PLAYBACK_TO_USE_AI(Any p0, Any p1) { invoke<Void>(0xB536CCD7, p0, p1); } // 0xB536CCD7
	static void SET_PLAYBACK_TO_USE_AI_TRY_TO_REVERT_BACK_LATER(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x0C8ABAA4, p0, p1, p2, p3); } // 0x0C8ABAA4
	static void _0x943A58EB(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x943A58EB, p0, p1, p2, p3, p4); } // 0x943A58EB
	static void _0x5C9F477C(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x5C9F477C, p0, p1, p2, p3); } // 0x5C9F477C
	static void _0xCD83C393(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xCD83C393, p0, p1, p2, p3); } // 0xCD83C393
	static void _0x2EF8435C(Any p0, Any p1) { invoke<Void>(0x2EF8435C, p0, p1); } // 0x2EF8435C
	static void EXPLODE_VEHICLE_IN_CUTSCENE(Any p0, Any p1) { invoke<Void>(0xA85207B5, p0, p1); } // 0xA85207B5
	static void ADD_VEHICLE_STUCK_CHECK_WITH_WARP(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0xC8B789AD, p0, p1, p2, p3, p4, p5, p6); } // 0xC8B789AD
	static void SET_VEHICLE_MODEL_IS_SUPPRESSED(Any p0, Any p1) { invoke<Void>(0x42A08C9B, p0, p1); } // 0x42A08C9B
	static Entity GET_RANDOM_VEHICLE_IN_SPHERE(float p0, float p1, float p2, float p3, int p4, int p5) { return invoke<Entity>(0x57216D03, p0, p1, p2, p3, p4, p5); } // 0x57216D03
	static Entity GET_RANDOM_VEHICLE_FRONT_BUMPER_IN_SPHERE(float p0, float p1, float p2, float p3, int p4, int p5, int p6) { return invoke<Entity>(0xDCADEB66, p0, p1, p2, p3, p4, p5, p6); } // 0xDCADEB66
	static Entity GET_RANDOM_VEHICLE_BACK_BUMPER_IN_SPHERE(float p0, float p1, float p2, float p3, int p4, int p5, int p6) { return invoke<Entity>(0xD6343F6B, p0, p1, p2, p3, p4, p5, p6); } // 0xD6343F6B
	static Vehicle GET_CLOSEST_VEHICLE(float x, float y, float z, float radius, Hash hash, int unk1) { return invoke<Vehicle>(0xD7E26B2C, x, y, z, radius, hash, unk1); } // 0xD7E26B2C
	static Any GET_TRAIN_CARRIAGE(Any p0, Any p1) { return invoke<Any>(0x2544E7A6, p0, p1); } // 0x2544E7A6
	static void DELETE_MISSION_TRAIN(Any p0) { invoke<Void>(0x86C9497D, p0); } // 0x86C9497D
	static void SET_MISSION_TRAIN_AS_NO_LONGER_NEEDED(Any p0, Any p1) { invoke<Void>(0x19808560, p0, p1); } // 0x19808560
	static void SET_MISSION_TRAIN_COORDS(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xD6D70803, p0, p1, p2, p3); } // 0xD6D70803
	static BOOL IS_THIS_MODEL_A_BOAT(Hash model) { return invoke<BOOL>(0x10F6085C, model); } // 0x10F6085C
	static BOOL IS_THIS_MODEL_A_PLANE(Hash model) { return invoke<BOOL>(0x3B3907BB, model); } // 0x3B3907BB
	static BOOL IS_THIS_MODEL_A_HELI(Hash model) { return invoke<BOOL>(0x8AF7F568, model); } // 0x8AF7F568
	static BOOL IS_THIS_MODEL_A_CAR(Hash model) { return invoke<BOOL>(0x60E4C22F, model); } // 0x60E4C22F
	static BOOL IS_THIS_MODEL_A_TRAIN(Hash model) { return invoke<BOOL>(0xF87DCFFD, model); } // 0xF87DCFFD
	static BOOL IS_THIS_MODEL_A_BIKE(Hash model) { return invoke<BOOL>(0x7E702CDD, model); } // 0x7E702CDD
	static BOOL IS_THIS_MODEL_A_BICYCLE(Hash model) { return invoke<BOOL>(0x328E6FF5, model); } // 0x328E6FF5
	static BOOL IS_THIS_MODEL_A_QUADBIKE(Hash model) { return invoke<BOOL>(0xC1625277, model); } // 0xC1625277
	static void SET_HELI_BLADES_FULL_SPEED(Any p0) { invoke<Void>(0x033A9408, p0); } // 0x033A9408
	static void SET_HELI_BLADES_SPEED(Vehicle vehicle, float speed) { invoke<Void>(0x5C7D4EA9, vehicle, speed); } // 0x5C7D4EA9
	static void _0x1128A45B(Any p0, Any p1, Any p2) { invoke<Void>(0x1128A45B, p0, p1, p2); } // 0x1128A45B
	static void SET_VEHICLE_CAN_BE_TARGETTED(Vehicle vehicle, BOOL state) { invoke<Void>(0x64B70B1D, vehicle, state); } // 0x64B70B1D
	static void _0x486C1280(Any p0, Any p1) { invoke<Void>(0x486C1280, p0, p1); } // 0x486C1280
	static void SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(Vehicle vehicle, BOOL state) { invoke<Void>(0xC5D94017, vehicle, state); } // 0xC5D94017
	static void _0x009AB49E(Any p0, Any p1) { invoke<Void>(0x009AB49E, p0, p1); } // 0x009AB49E
	static void _0x758C5E2E(Any p0, Any p1) { invoke<Void>(0x758C5E2E, p0, p1); } // 0x758C5E2E
	static float GET_VEHICLE_DIRT_LEVEL(Vehicle vehicle) { return invoke<float>(0xFD15C065, vehicle); } // 0xFD15C065
	static void SET_VEHICLE_DIRT_LEVEL(Vehicle Vehicle, float DirtLVL) { invoke<Void>(0x2B39128B, Vehicle, DirtLVL); } // 0x2B39128B
	static Any _0xDAC523BC(Any p0) { return invoke<Any>(0xDAC523BC, p0); } // 0xDAC523BC
	static BOOL IS_VEHICLE_DOOR_FULLY_OPEN(Vehicle vehicle, int doorIndex) { return invoke<BOOL>(0xC2385B6F, vehicle, doorIndex); } // 0xC2385B6F
	static void SET_VEHICLE_ENGINE_ON(Vehicle veh, BOOL engineState, BOOL p3) { invoke<Void>(0x7FBC86F1, veh, engineState, p3); } // 0x7FBC86F1
	static void SET_VEHICLE_UNDRIVEABLE(Vehicle vehicle, BOOL state) { invoke<Void>(0x48D02A4E, vehicle, state); } // 0x48D02A4E
	static void SET_VEHICLE_PROVIDES_COVER(Any p0, Any p1) { invoke<Void>(0xEFC01CA9, p0, p1); } // 0xEFC01CA9
	static void SET_VEHICLE_DOOR_CONTROL(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x572DD360, p0, p1, p2, p3); } // 0x572DD360
	static void SET_VEHICLE_DOOR_LATCHED(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x4EB7BBFC, p0, p1, p2, p3, p4); } // 0x4EB7BBFC
	static Any GET_VEHICLE_DOOR_ANGLE_RATIO(Any p0, Any p1) { return invoke<Any>(0x0E399C26, p0, p1); } // 0x0E399C26
	static void SET_VEHICLE_DOOR_SHUT(Vehicle vehicle, int doorIndex, BOOL closeInstantly) { invoke<Void>(0x142606BD, vehicle, doorIndex, closeInstantly); } // 0x142606BD
	static void SET_VEHICLE_DOOR_BROKEN(Vehicle veh, int doorIndex, BOOL unk) { invoke<Void>(0x8147FEA7, veh, doorIndex, unk); } // 0x8147FEA7
	static void SET_VEHICLE_CAN_BREAK(Vehicle vehicle, BOOL Toggle) { invoke<Void>(0x90A810D1, vehicle, Toggle); } // 0x90A810D1
	static BOOL DOES_VEHICLE_HAVE_ROOF(Vehicle vehicle) { return invoke<BOOL>(0xDB817403, vehicle); } // 0xDB817403
	static BOOL IS_BIG_VEHICLE(Vehicle vehicle) { return invoke<BOOL>(0x9CDBA8DE, vehicle); } // 0x9CDBA8DE
	static Any GET_NUMBER_OF_VEHICLE_COLOURS(Any p0) { return invoke<Any>(0xF2442EE2, p0); } // 0xF2442EE2
	static void SET_VEHICLE_COLOUR_COMBINATION(Any p0, Any p1) { invoke<Void>(0xA557AEAD, p0, p1); } // 0xA557AEAD
	static Any GET_VEHICLE_COLOUR_COMBINATION(Any p0) { return invoke<Any>(0x77AC1B4C, p0); } // 0x77AC1B4C
	static void SET_VEHICLE_IS_CONSIDERED_BY_PLAYER(Any p0, Any p1) { invoke<Void>(0x14413319, p0, p1); } // 0x14413319
	static void _0xA6D8D7A5(Any p0, Any p1) { invoke<Void>(0xA6D8D7A5, p0, p1); } // 0xA6D8D7A5
	static void _0xACAB8FF3(Any p0, Any p1) { invoke<Void>(0xACAB8FF3, p0, p1); } // 0xACAB8FF3
	static void _0xF0E5C41D(Any p0, Any p1) { invoke<Void>(0xF0E5C41D, p0, p1); } // 0xF0E5C41D
	static void _0x2F98B4B7(Any p0, Any p1) { invoke<Void>(0x2F98B4B7, p0, p1); } // 0x2F98B4B7
	static void GET_RANDOM_VEHICLE_MODEL_IN_MEMORY(BOOL b0, Hash* p1, int* p2) { invoke<Void>(0xE2C45631, b0, p1, p2); } // 0xE2C45631
	static Any GET_VEHICLE_DOOR_LOCK_STATUS(Any p0) { return invoke<Any>(0x0D72CEF2, p0); } // 0x0D72CEF2
	static BOOL IS_VEHICLE_DOOR_DAMAGED(Vehicle veh, int doorID) { return invoke<BOOL>(0x4999E3C3, veh, doorID); } // 0x4999E3C3
	static void _0x065B92B3(Any p0, Any p1, Any p2) { invoke<Void>(0x065B92B3, p0, p1, p2); } // 0x065B92B3
	static Any _0xB3A2CC4F(Any p0, Any p1) { return invoke<Any>(0xB3A2CC4F, p0, p1); } // 0xB3A2CC4F
	static BOOL IS_VEHICLE_BUMPER_BROKEN_OFF(Any p0, Any p1) { return invoke<BOOL>(0xAF25C027, p0, p1); } // 0xAF25C027
	static BOOL IS_COP_VEHICLE_IN_AREA_3D(Any x1, Any x2, Any y1, Any y2, Any z1, Any z2) { return invoke<BOOL>(0xFB16C6D1, x1, x2, y1, y2, z1, z2); } // 0xFB16C6D1
	static BOOL IS_VEHICLE_ON_ALL_WHEELS(Vehicle vehicle) { return invoke<BOOL>(0x10089F8E, vehicle); } // 0x10089F8E
	static Any GET_VEHICLE_LAYOUT_HASH(Any p0) { return invoke<Any>(0xE0B35187, p0); } // 0xE0B35187
	static void SET_RENDER_TRAIN_AS_DERAILED(Any p0, Any p1) { invoke<Void>(0x899D9092, p0, p1); } // 0x899D9092
	static void SET_VEHICLE_EXTRA_COLOURS(Any p0, Any p1, Any p2) { invoke<Void>(0x515DB2A0, p0, p1, p2); } // 0x515DB2A0
	static void GET_VEHICLE_EXTRA_COLOURS(int vehicle, int *pearl, int *wheelcolor) { invoke<Void>(0x80E4659B, vehicle, pearl, wheelcolor); } // 0x80E4659B
	static void STOP_ALL_GARAGE_ACTIVITY() { invoke<Void>(0x17A0BCE5); } // 0x17A0BCE5
	static void SET_VEHICLE_FIXED(Vehicle Vehicle) { invoke<Void>(0x17469AA1, Vehicle); } // 0x17469AA1
	static void SET_VEHICLE_DEFORMATION_FIXED(Vehicle Vehicle) { invoke<Void>(0xDD2920C8, Vehicle); } // 0xDD2920C8
	static void _0x88F0F7E7(Any p0, Any p1) { invoke<Void>(0x88F0F7E7, p0, p1); } // 0x88F0F7E7
	static void _0x90D6EE57(Any p0, Any p1) { invoke<Void>(0x90D6EE57, p0, p1); } // 0x90D6EE57
	static void _0xC40192B5(Any p0, Any p1) { invoke<Void>(0xC40192B5, p0, p1); } // 0xC40192B5
	static void SET_DISABLE_VEHICLE_PETROL_TANK_DAMAGE(Any p0, Any p1) { invoke<Void>(0xAD3E05F2, p0, p1); } // 0xAD3E05F2
	static void _0x1784BA1A(Any p0, Any p1) { invoke<Void>(0x1784BA1A, p0, p1); } // 0x1784BA1A
	static void _0x40C323AE(Any p0, Any p1) { invoke<Void>(0x40C323AE, p0, p1); } // 0x40C323AE
	static void _0x847F1304(Any p0, Any p1) { invoke<Void>(0x847F1304, p0, p1); } // 0x847F1304
	static void _0xCBD98BA1(Any p0, Any p1) { invoke<Void>(0xCBD98BA1, p0, p1); } // 0xCBD98BA1
	static void REMOVE_VEHICLES_FROM_GENERATORS_IN_AREA(Any x1, Any x2, Any y1, Any y2, Any z1, Any z2) { invoke<Void>(0x42CC15E0, x1, x2, y1, y2, z1, z2); } // 0x42CC15E0
	static void SET_VEHICLE_STEER_BIAS(Any p0, Any p1) { invoke<Void>(0x7357C1EB, p0, p1); } // 0x7357C1EB
	static BOOL IS_VEHICLE_EXTRA_TURNED_ON(Any p0, Any p1) { return invoke<BOOL>(0x042098B5, p0, p1); } // 0x042098B5
	static void SET_VEHICLE_EXTRA(Vehicle vehicle, int ExtraID, int Toggle) { invoke<Void>(0x642D065C, vehicle, ExtraID, Toggle); } // 0x642D065C
	static BOOL DOES_EXTRA_EXIST(Any p0, Any p1) { return invoke<BOOL>(0x409411CC, p0, p1); } // 0x409411CC
	static void SET_CONVERTIBLE_ROOF(Any p0, Any p1) { invoke<Void>(0xC87B6A51, p0, p1); } // 0xC87B6A51
	static void LOWER_CONVERTIBLE_ROOF(Any p0, Any p1) { invoke<Void>(0xC5F72EAE, p0, p1); } // 0xC5F72EAE
	static void RAISE_CONVERTIBLE_ROOF(Any p0, Any p1) { invoke<Void>(0xA4E4CBA3, p0, p1); } // 0xA4E4CBA3
	static Any GET_CONVERTIBLE_ROOF_STATE(Any p0) { return invoke<Any>(0x1B09714D, p0); } // 0x1B09714D
	static BOOL IS_VEHICLE_A_CONVERTIBLE(Any p0, Any p1) { return invoke<BOOL>(0x6EF54490, p0, p1); } // 0x6EF54490
	static BOOL IS_VEHICLE_STOPPED_AT_TRAFFIC_LIGHTS(Any p0) { return invoke<BOOL>(0x69200FA4, p0); } // 0x69200FA4
	static void SET_VEHICLE_DAMAGE(Any p0, float p1, float p2, float p3, float p4, float p5, Any p6) { invoke<Void>(0x21B458B2, p0, p1, p2, p3, p4, p5, p6); } // 0x21B458B2
	static float GET_VEHICLE_ENGINE_HEALTH(Vehicle vehicle) { return invoke<float>(0x8880038A, vehicle); } // 0x8880038A
	static void SET_VEHICLE_ENGINE_HEALTH(Vehicle vehicle, float health) { invoke<Void>(0x1B760FB5, vehicle, health); } // 0x1B760FB5
	static float GET_VEHICLE_PETROL_TANK_HEALTH(Vehicle vehicle) { return invoke<float>(0xE41595CE, vehicle); } // 0xE41595CE
	static void SET_VEHICLE_PETROL_TANK_HEALTH(Vehicle vehicle, float health) { invoke<Void>(0x660A3692, vehicle, health); } // 0x660A3692
	static BOOL IS_VEHICLE_STUCK_TIMER_UP(Any p0, Any p1, Any p2) { return invoke<BOOL>(0x2FCF58C1, p0, p1, p2); } // 0x2FCF58C1
	static void RESET_VEHICLE_STUCK_TIMER(Any p0, Any p1) { invoke<Void>(0xEF2A6016, p0, p1); } // 0xEF2A6016
	static BOOL IS_VEHICLE_DRIVEABLE(Any p0, Any p1) { return invoke<BOOL>(0x41A7267A, p0, p1); } // 0x41A7267A
	static void SET_VEHICLE_HAS_BEEN_OWNED_BY_PLAYER(Any p0, Any p1) { invoke<Void>(0xB4D3DBFB, p0, p1); } // 0xB4D3DBFB
	static void SET_VEHICLE_NEEDS_TO_BE_HOTWIRED(Any p0, Any p1) { invoke<Void>(0xD8260751, p0, p1); } // 0xD8260751
	static void START_VEHICLE_HORN(Vehicle p0, int p1, int p2, BOOL p3) { invoke<Void>(0x0DF5ADB3, p0, p1, p2, p3); } // 0x0DF5ADB3
	static void _0x968E5770(Any p0, Any p1) { invoke<Void>(0x968E5770, p0, p1); } // 0x968E5770
	static void SET_VEHICLE_HAS_STRONG_AXLES(Any p0, Any p1) { invoke<Void>(0x0D1CBC65, p0, p1); } // 0x0D1CBC65
	static Any GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(Any p0) { return invoke<Any>(0xEC86DF39, p0); } // 0xEC86DF39
	static Vector3 GET_VEHICLE_DEFORMATION_AT_POS(Any p0, Any p1, Any p2, Any p3) { return invoke<Vector3>(0xABF02075, p0, p1, p2, p3); } // 0xABF02075
	static void SET_VEHICLE_LIVERY(Vehicle vehicle, int LiveryIndex) { invoke<Void>(0x7AD87059, vehicle, LiveryIndex); } // 0x7AD87059
	static Any GET_VEHICLE_LIVERY(Any p0) { return invoke<Any>(0xEC82A51D, p0); } // 0xEC82A51D
	static Any GET_VEHICLE_LIVERY_COUNT(Any p0) { return invoke<Any>(0xFB0CA947, p0); } // 0xFB0CA947
	static BOOL IS_VEHICLE_WINDOW_INTACT(Any p0, Any p1) { return invoke<BOOL>(0xAC4EF23D, p0, p1); } // 0xAC4EF23D
	static Any _0xBB619744(Any p0) { return invoke<Any>(0xBB619744, p0); } // 0xBB619744
	static Any _0x648E685A(Any p0) { return invoke<Any>(0x648E685A, p0); } // 0x648E685A
	static void RESET_VEHICLE_WHEELS(Any p0, Any p1) { invoke<Void>(0xD5FFE779, p0, p1); } // 0xD5FFE779
	static BOOL IS_HELI_PART_BROKEN(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0xF4E4C439, p0, p1, p2, p3); } // 0xF4E4C439
	static Any _0xF01E2AAB(Any p0) { return invoke<Any>(0xF01E2AAB, p0); } // 0xF01E2AAB
	static Any _0xA41BC13D(Any p0) { return invoke<Any>(0xA41BC13D, p0); } // 0xA41BC13D
	static Any _0x8A68388F(Any p0) { return invoke<Any>(0x8A68388F, p0); } // 0x8A68388F
	static BOOL WAS_COUNTER_ACTIVATED(Any p0, Any p1) { return invoke<BOOL>(0x2916D69B, p0, p1); } // 0x2916D69B
	static void SET_VEHICLE_NAME_DEBUG(Any p0, Any p1) { invoke<Void>(0xA712FF5C, p0, p1); } // 0xA712FF5C
	static void SET_VEHICLE_EXPLODES_ON_HIGH_EXPLOSION_DAMAGE(Any p0, Any p1) { invoke<Void>(0x38CC692B, p0, p1); } // 0x38CC692B
	static void _0xC306A9A3(Any p0, Any p1) { invoke<Void>(0xC306A9A3, p0, p1); } // 0xC306A9A3
	static void _0x95A9ACCB(Vehicle vehicle, BOOL p1) { invoke<Void>(0x95A9ACCB, vehicle, p1); } // 0x95A9ACCB
	static void _0x24F873FB(Any p0, Any p1) { invoke<Void>(0x24F873FB, p0, p1); } // 0x24F873FB
	static Any _0xA6F02670(Any p0) { return invoke<Any>(0xA6F02670, p0); } // 0xA6F02670
	static BOOL IS_ANY_VEHICLE_NEAR_POINT(Any p0, Any x, Any y, Any z) { return invoke<BOOL>(0x2867A834, p0, x, y, z); } // 0x2867A834
	static void REQUEST_VEHICLE_HIGH_DETAIL_MODEL(Any p0) { invoke<Void>(0x9DA21956, p0); } // 0x9DA21956
	static void REMOVE_VEHICLE_HIGH_DETAIL_MODEL(Any p0) { invoke<Void>(0x382BE070, p0); } // 0x382BE070
	static BOOL IS_VEHICLE_HIGH_DETAIL(Any p0) { return invoke<BOOL>(0x55D41928, p0); } // 0x55D41928
	static void REQUEST_VEHICLE_ASSET(Hash VehicleHash, int p1) { invoke<Void>(0x902B4F06, VehicleHash, p1); } // 0x902B4F06
	static BOOL HAS_VEHICLE_ASSET_LOADED(Any p0) { return invoke<BOOL>(0x8DAAC3CB, p0); } // 0x8DAAC3CB
	static void REMOVE_VEHICLE_ASSET(Any p0) { invoke<Void>(0x9620E9C6, p0); } // 0x9620E9C6
	static void _0x88236E22(Any p0, Any p1) { invoke<Void>(0x88236E22, p0, p1); } // 0x88236E22
	static void ATTACH_VEHICLE_TO_TOW_TRUCK(Entity entity, Entity entity2, int instant, float x, float y, float z) { invoke<Void>(0x8151571A, entity, entity2, instant, x, y, z); } // 0x8151571A
	static void DETACH_VEHICLE_FROM_TOW_TRUCK(Any p0, Any p1) { invoke<Void>(0xC666CF33, p0, p1); } // 0xC666CF33
	static Any DETACH_VEHICLE_FROM_ANY_TOW_TRUCK(Any p0) { return invoke<Any>(0x3BF93651, p0); } // 0x3BF93651
	static BOOL IS_VEHICLE_ATTACHED_TO_TOW_TRUCK(Any p0, Any p1) { return invoke<BOOL>(0x9699CFDC, p0, p1); } // 0x9699CFDC
	static Any GET_ENTITY_ATTACHED_TO_TOW_TRUCK(Any p0) { return invoke<Any>(0x11EC7844, p0); } // 0x11EC7844
	static Any SET_VEHICLE_AUTOMATICALLY_ATTACHES(Any p0, Any p1, Any p2) { return invoke<Any>(0x4273A8D3, p0, p1, p2); } // 0x4273A8D3
	static void _0xED23C8A3(Any p0, Any p1, Any p2) { invoke<Void>(0xED23C8A3, p0, p1, p2); } // 0xED23C8A3
	static void _0xB1A52EF7(Any p0, Any p1, Any p2) { invoke<Void>(0xB1A52EF7, p0, p1, p2); } // 0xB1A52EF7
	static void _0xF30C566F(Any p0, Any p1) { invoke<Void>(0xF30C566F, p0, p1); } // 0xF30C566F
	static void _0xA7DF64D7(Any p0, Any p1) { invoke<Void>(0xA7DF64D7, p0, p1); } // 0xA7DF64D7
	static void _0xDD7936F5(Any p0, Any p1) { invoke<Void>(0xDD7936F5, p0, p1); } // 0xDD7936F5
	static Any _0x34E02FCD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<Any>(0x34E02FCD, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x34E02FCD
	static void SET_VEHICLE_BURNOUT(Any p0, Any p1) { invoke<Void>(0x9B6EF0EA, p0, p1); } // 0x9B6EF0EA
	static BOOL IS_VEHICLE_IN_BURNOUT(Vehicle vehicle) { return invoke<BOOL>(0x6632BC12, vehicle); } // 0x6632BC12
	static void SET_VEHICLE_REDUCE_GRIP(Vehicle Vehicle, BOOL Toggle) { invoke<Void>(0x90D3A0D9, Vehicle, Toggle); } // 0x90D3A0D9
	static void SET_VEHICLE_INDICATOR_LIGHTS(Vehicle vehicle, int turnSignal, BOOL Toggle) { invoke<Void>(0xA6073B5D, vehicle, turnSignal, Toggle); } // 0xA6073B5D
	static void SET_VEHICLE_BRAKE_LIGHTS(Vehicle vehicle, BOOL Toggle) { invoke<Void>(0x6D9BA11E, vehicle, Toggle); } // 0x6D9BA11E
	static void SET_VEHICLE_HANDBRAKE(Vehicle vehicle, BOOL Toggle) { invoke<Void>(0xBA729A25, vehicle, Toggle); } // 0xBA729A25
	static void _0x37BC6ACB() { invoke<Void>(0x37BC6ACB); } // 0x37BC6ACB
	static Any _0x71D898EF() { return invoke<Any>(0x71D898EF); } // 0x71D898EF
	static void _0x0B0523B0(Any p0) { invoke<Void>(0x0B0523B0, p0); } // 0x0B0523B0
	static Any GET_VEHICLE_TRAILER_VEHICLE(Any p0, Any p1) { return invoke<Any>(0xAE84D758, p0, p1); } // 0xAE84D758
	static void _0x0B200CE2(Any p0, Any p1) { invoke<Void>(0x0B200CE2, p0, p1); } // 0x0B200CE2
	static void SET_VEHICLE_RUDDER_BROKEN(Any p0, Any p1) { invoke<Void>(0x3FAC3CD4, p0, p1); } // 0x3FAC3CD4
	static void _0x0858678C(Any p0, Any p1) { invoke<Void>(0x0858678C, p0, p1); } // 0x0858678C
	static Any _0x7D1A0616(Any p0) { return invoke<Any>(0x7D1A0616, p0); } // 0x7D1A0616
	static Any GET_VEHICLE_MAX_BRAKING(Any p0) { return invoke<Any>(0x03B926F6, p0); } // 0x03B926F6
	static Any GET_VEHICLE_MAX_TRACTION(Any p0) { return invoke<Any>(0x7E5A1587, p0); } // 0x7E5A1587
	static Any GET_VEHICLE_ACCELERATION(Any p0) { return invoke<Any>(0x00478321, p0); } // 0x00478321
	static Any _0x8F291C4A(Any p0) { return invoke<Any>(0x8F291C4A, p0); } // 0x8F291C4A
	static Any GET_VEHICLE_MODEL_MAX_BRAKING(Any p0) { return invoke<Any>(0x7EF02883, p0); } // 0x7EF02883
	static Any _0xF3A7293F(Any p0) { return invoke<Any>(0xF3A7293F, p0); } // 0xF3A7293F
	static Any GET_VEHICLE_MODEL_MAX_TRACTION(Any p0) { return invoke<Any>(0x7F985597, p0); } // 0x7F985597
	static Any GET_VEHICLE_MODEL_ACCELERATION(Any p0) { return invoke<Any>(0x29CB3537, p0); } // 0x29CB3537
	static Any _0x37FBA7BC(Any p0) { return invoke<Any>(0x37FBA7BC, p0); } // 0x37FBA7BC
	static Any _0x95BB67EB(Any p0) { return invoke<Any>(0x95BB67EB, p0); } // 0x95BB67EB
	static Any _0x87C5D271(Any p0) { return invoke<Any>(0x87C5D271, p0); } // 0x87C5D271
	static Any _0xCE67162C(Any p0) { return invoke<Any>(0xCE67162C, p0); } // 0xCE67162C
	static Any GET_VEHICLE_CLASS_MAX_TRACTION(Any p0) { return invoke<Any>(0x5B4FDC16, p0); } // 0x5B4FDC16
	static Any GET_VEHICLE_CLASS_MAX_AGILITY(Any p0) { return invoke<Any>(0x45F2BD83, p0); } // 0x45F2BD83
	static Any GET_VEHICLE_CLASS_MAX_ACCELERATION(Any p0) { return invoke<Any>(0x3E220A9B, p0); } // 0x3E220A9B
	static Any GET_VEHICLE_CLASS_MAX_BRAKING(Any p0) { return invoke<Any>(0xD08CC1A5, p0); } // 0xD08CC1A5
	static Any _0xD6685803(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0xD6685803, p0, p1, p2, p3, p4, p5); } // 0xD6685803
	static Any _0x0C0332A6(Any p0) { return invoke<Any>(0x0C0332A6, p0); } // 0x0C0332A6
	static void _0x6574041D(Any p0) { invoke<Void>(0x6574041D, p0); } // 0x6574041D
	static void _0xF8EC5751(Any p0) { invoke<Void>(0xF8EC5751, p0); } // 0xF8EC5751
	static BOOL IS_VEHICLE_SEARCHLIGHT_ON(Vehicle vehicle) { return invoke<BOOL>(0xADAF3513, vehicle); } // 0xADAF3513
	static void SET_VEHICLE_SEARCHLIGHT(Any p0, Any p1, Any p2) { invoke<Void>(0xE2C0DD8A, p0, p1, p2); } // 0xE2C0DD8A
	static Any _0xAB0E79EB(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xAB0E79EB, p0, p1, p2, p3, p4); } // 0xAB0E79EB
	static BOOL CAN_SHUFFLE_SEAT(Any p0, Any p1) { return invoke<BOOL>(0xB3EB01ED, p0, p1); } // 0xB3EB01ED
	static Any GET_NUM_MOD_KITS(Any p0) { return invoke<Any>(0xE4903AA0, p0); } // 0xE4903AA0
	static void SET_VEHICLE_MOD_KIT(Vehicle vehicle, int unknown) { invoke<Void>(0xB8132158, vehicle, unknown); } // 0xB8132158
	static Any GET_VEHICLE_MOD_KIT(Any p0) { return invoke<Any>(0x9FE60927, p0); } // 0x9FE60927
	static Any GET_VEHICLE_MOD_KIT_TYPE(Any p0) { return invoke<Any>(0xE5F76765, p0); } // 0xE5F76765
	static int GET_VEHICLE_WHEEL_TYPE(Vehicle vehicle) { return invoke<int>(0xDA58D7AE, vehicle); } // 0xDA58D7AE
	static void SET_VEHICLE_WHEEL_TYPE(Vehicle vehicle, int WheelType) { invoke<Void>(0x64BDAAAD, vehicle, WheelType); } // 0x64BDAAAD
	static Any GET_NUM_MOD_COLORS(Any p0, Any p1) { return invoke<Any>(0x73722CD9, p0, p1); } // 0x73722CD9
	static void SET_VEHICLE_MOD_COLOR_1(Vehicle vehicle, int r, int g, int b) { invoke<Void>(0xCBE9A54D, vehicle, r, g, b); } // 0xCBE9A54D
	static void SET_VEHICLE_MOD_COLOR_2(Any p0, Any p1, Any p2) { invoke<Void>(0xC32613C2, p0, p1, p2); } // 0xC32613C2
	static void GET_VEHICLE_MOD_COLOR_1(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xE625510A, p0, p1, p2, p3); } // 0xE625510A
	static void GET_VEHICLE_MOD_COLOR_2(Any p0, Any p1, Any p2) { invoke<Void>(0x9B76BB8E, p0, p1, p2); } // 0x9B76BB8E
	static Any _0x9A0840FD(Any p0, Any p1) { return invoke<Any>(0x9A0840FD, p0, p1); } // 0x9A0840FD
	static Any _0x9BDC0B49(Any p0) { return invoke<Any>(0x9BDC0B49, p0); } // 0x9BDC0B49
	static Any _0x112D637A(Any p0) { return invoke<Any>(0x112D637A, p0); } // 0x112D637A
	static void SET_VEHICLE_MOD(Vehicle vehicle, int ModType, int ModIndex, BOOL Variation) { invoke<Void>(0xB52E5ED5, vehicle, ModType, ModIndex, Variation); } // 0xB52E5ED5
	static int GET_VEHICLE_MOD(Vehicle vehicle, int Modtype) { return invoke<int>(0xDC520069, vehicle, Modtype); } // 0xDC520069
	static BOOL GET_VEHICLE_MOD_VARIATION(Vehicle vehicle, int ModType) { return invoke<BOOL>(0xC1B92003, vehicle, ModType); } // 0xC1B92003
	static int GET_NUM_VEHICLE_MODS(Vehicle vehicle, int ModType) { return invoke<int>(0x8A814FF9, vehicle, ModType); } // 0x8A814FF9
	static void REMOVE_VEHICLE_MOD(Any p0, Any p1) { invoke<Void>(0x9CC80A43, p0, p1); } // 0x9CC80A43
	static void TOGGLE_VEHICLE_MOD(Vehicle vehicle, int Mod, BOOL Toggle) { invoke<Void>(0xD095F811, vehicle, Mod, Toggle); } // 0xD095F811
	static BOOL IS_TOGGLE_MOD_ON(Any p0, Any p1) { return invoke<BOOL>(0xF0E1689F, p0, p1); } // 0xF0E1689F
	static char* GET_MOD_TEXT_LABEL(Vehicle vehicle, int ModType, int ModValue) { return invoke<char*>(0x0BA39CA7, vehicle, ModType, ModValue); } // 0x0BA39CA7
	static char* GET_MOD_SLOT_NAME(Vehicle vehicle, int ModType) { return invoke<char*>(0x5E113483, vehicle, ModType); } // 0x5E113483
	static Any GET_LIVERY_NAME(Any p0, Any p1) { return invoke<Any>(0xED80B5BE, p0, p1); } // 0xED80B5BE
	static Any GET_VEHICLE_MOD_MODIFIER_VALUE(Any p0, Any p1, Any p2) { return invoke<Any>(0x73AE5505, p0, p1, p2); } // 0x73AE5505
	static Any _0x94850968(Any p0, Any p1, Any p2) { return invoke<Any>(0x94850968, p0, p1, p2); } // 0x94850968
	static void PRELOAD_VEHICLE_MOD(Any p0, Any p1, Any p2) { invoke<Void>(0x6EA5F4A8, p0, p1, p2); } // 0x6EA5F4A8
	static BOOL HAS_PRELOAD_MODS_FINISHED(Any p0) { return invoke<BOOL>(0xA8A0D246, p0); } // 0xA8A0D246
	static void RELEASE_PRELOAD_MODS(Any p0) { invoke<Void>(0xD442521F, p0); } // 0xD442521F
	static void SET_VEHICLE_TYRE_SMOKE_COLOR(Vehicle vehicle, int r, int g, int b) { invoke<Void>(0x3EDEC0DB, vehicle, r, g, b); } // 0x3EDEC0DB
	static void GET_VEHICLE_TYRE_SMOKE_COLOR(Vehicle vehicle, int R, int G, int B) { invoke<Void>(0x75280015, vehicle, R, G, B); } // 0x75280015
	static void SET_VEHICLE_WINDOW_TINT(Vehicle vehicle, int Tint) { invoke<Void>(0x497C8787, vehicle, Tint); } // 0x497C8787
	static int GET_VEHICLE_WINDOW_TINT(Vehicle vehicle) { return invoke<int>(0x13D53892, vehicle); } // 0x13D53892
	static Any GET_NUM_VEHICLE_WINDOW_TINTS() { return invoke<Any>(0x625C7B66); } // 0x625C7B66
	static void GET_VEHICLE_COLOR(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x03BC8F1B, p0, p1, p2, p3); } // 0x03BC8F1B
	static Any _0x749DEEA2(Any p0) { return invoke<Any>(0x749DEEA2, p0); } // 0x749DEEA2
	static Any GET_VEHICLE_CAUSE_OF_DESTRUCTION(Any p0) { return invoke<Any>(0x7F8C20DD, p0); } // 0x7F8C20DD
	static Any _0xA0777943(Any p0) { return invoke<Any>(0xA0777943, p0); } // 0xA0777943
	static Any _0xF178390B(Any p0) { return invoke<Any>(0xF178390B, p0); } // 0xF178390B
	static void _0xE943B09C(Vehicle vehicle, int multiplier) { invoke<Void>(0xE943B09C, vehicle, multiplier); } // 0xE943B09C
	static void _0xDF594D8D(Any p0, Any p1) { invoke<Void>(0xDF594D8D, p0, p1); } // 0xDF594D8D
	static void _0x4D840FC4(Any p0, Any p1) { invoke<Void>(0x4D840FC4, p0, p1); } // 0x4D840FC4
	static Any _0x5AB26C2B(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0x5AB26C2B, p0, p1, p2, p3, p4, p5, p6); } // 0x5AB26C2B
	static void _0xEF05F807(Any p0) { invoke<Void>(0xEF05F807, p0); } // 0xEF05F807
	static Any _0xD656E7E5(Any p0) { return invoke<Any>(0xD656E7E5, p0); } // 0xD656E7E5
	static void _0x642DA5AA(Vehicle vehicle, float p1) { invoke<Void>(0x642DA5AA, vehicle, p1); } // 0x642DA5AA
	static void _0x04F5546C(Any p0, Any p1) { invoke<Void>(0x04F5546C, p0, p1); } // 0x04F5546C
	static void SET_VEHICLE_IS_WANTED(Vehicle p0, BOOL p1) { invoke<Void>(0xDAA388E8, p0, p1); } // 0xDAA388E8
	static void _0xA25CCB8C(Any p0, Any p1) { invoke<Void>(0xA25CCB8C, p0, p1); } // 0xA25CCB8C
	static void _0x00966934(Any p0, Any p1) { invoke<Void>(0x00966934, p0, p1); } // 0x00966934
	static void _0x113DF5FD(Any p0, Any p1) { invoke<Void>(0x113DF5FD, p0, p1); } // 0x113DF5FD
	static Any _0x7C8D6464(Any p0) { return invoke<Any>(0x7C8D6464, p0); } // 0x7C8D6464
	static void DISABLE_PLANE_AILERON(Any p0, Any p1, Any p2) { invoke<Void>(0x7E84C45C, p0, p1, p2); } // 0x7E84C45C
	static Any _0x7DC6D022(Any p0) { return invoke<Any>(0x7DC6D022, p0); } // 0x7DC6D022
	static void _0xA03E42DF(Any p0, Any p1) { invoke<Void>(0xA03E42DF, p0, p1); } // 0xA03E42DF
	static void _0x15D40761(Any p0, Any p1, Any p2) { invoke<Void>(0x15D40761, p0, p1, p2); } // 0x15D40761
	static void _0x1984F88D(Any p0, Any p1) { invoke<Void>(0x1984F88D, p0, p1); } // 0x1984F88D
	static void _0x3FBE904F(Any p0) { invoke<Void>(0x3FBE904F, p0); } // 0x3FBE904F
	static void _0xD1B71A25(Any p0) { invoke<Void>(0xD1B71A25, p0); } // 0xD1B71A25
	static Any _0xFEB0C0C8() { return invoke<Any>(0xFEB0C0C8); } // 0xFEB0C0C8
	static void _0x08CD58F9(Any p0, Any p1) { invoke<Void>(0x08CD58F9, p0, p1); } // 0x08CD58F9
	static void _0x8C4B63E2(Any p0, Any p1) { invoke<Void>(0x8C4B63E2, p0, p1); } // 0x8C4B63E2
	static void SET_VEHICLE_LOD_MULTIPLIER(Any p0, Any p1) { invoke<Void>(0x569E5AE3, p0, p1); } // 0x569E5AE3
	static void _0x1604C2F5(Any p0, Any p1) { invoke<Void>(0x1604C2F5, p0, p1); } // 0x1604C2F5
	static Any _0x8CDB0C09(Any p0) { return invoke<Any>(0x8CDB0C09, p0); } // 0x8CDB0C09
	static Any _0xABC99E21(Any p0) { return invoke<Any>(0xABC99E21, p0); } // 0xABC99E21
	static void _0x900C878C(Any p0, Any p1) { invoke<Void>(0x900C878C, p0, p1); } // 0x900C878C
	static void _0xB3200F72(Any p0, Any p1) { invoke<Void>(0xB3200F72, p0, p1); } // 0xB3200F72
	static void _0xBAE491C7(Any p0, Any p1) { invoke<Void>(0xBAE491C7, p0, p1); } // 0xBAE491C7
	static void _0xF0E59BC1() { invoke<Void>(0xF0E59BC1); } // 0xF0E59BC1
	static void _0x929801C6(Any p0) { invoke<Void>(0x929801C6, p0); } // 0x929801C6
	static void SET_VEHICLE_SHOOT_AT_TARGET(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x2343FFDF, p0, p1, p2, p3, p4); } // 0x2343FFDF
	static Any _0x4A557117(Any p0, Any p1) { return invoke<Any>(0x4A557117, p0, p1); } // 0x4A557117
	static void _0xE0FC6A32(Any p0, Any p1) { invoke<Void>(0xE0FC6A32, p0, p1); } // 0xE0FC6A32
	static void _0x7D0DE7EA(Any p0, Any p1) { invoke<Void>(0x7D0DE7EA, p0, p1); } // 0x7D0DE7EA
	static Any GET_VEHICLE_PLATE_TYPE(Vehicle vehicle) { return invoke<Any>(0x65CA9286, vehicle); } // 0x65CA9286
	static void TRACK_VEHICLE_VISIBILITY(Any p0) { invoke<Void>(0x78122DC1, p0); } // 0x78122DC1
	static BOOL IS_VEHICLE_VISIBLE(Any p0) { return invoke<BOOL>(0x7E0D6056, p0); } // 0x7E0D6056
	static void SET_VEHICLE_GRAVITY(Vehicle Vehicle, BOOL Toggle) { invoke<Void>(0x07B2A6DC, Vehicle, Toggle); } // 0x07B2A6DC
	static void _0xD2B8ACBD(Any p0) { invoke<Void>(0xD2B8ACBD, p0); } // 0xD2B8ACBD
	static Any _0xA4A75FCF(Any p0) { return invoke<Any>(0xA4A75FCF, p0); } // 0xA4A75FCF
	static void _0x50F89338(Any p0, Any p1) { invoke<Void>(0x50F89338, p0, p1); } // 0x50F89338
	static void _0xEB7D7C27(Any p0, Any p1) { invoke<Void>(0xEB7D7C27, p0, p1); } // 0xEB7D7C27
	static Any _0x5EB00A6A(Any p0) { return invoke<Any>(0x5EB00A6A, p0); } // 0x5EB00A6A
	static void SET_VEHICLE_ENGINE_CAN_DEGRADE(Any p0, Any p1) { invoke<Void>(0x081DAC12, p0, p1); } // 0x081DAC12
	static void _0x5BD8D82D(Any p0, Any p1, Any p2) { invoke<Void>(0x5BD8D82D, p0, p1, p2); } // 0x5BD8D82D
	static void _0x450AD03A(Any p0) { invoke<Void>(0x450AD03A, p0); } // 0x450AD03A
	static Any _0xBD085DCA(Any p0) { return invoke<Any>(0xBD085DCA, p0); } // 0xBD085DCA
	static Any _0xABBDD5C6(Any p0) { return invoke<Any>(0xABBDD5C6, p0); } // 0xABBDD5C6
	static void _0x9B581DE7(Any p0, Any p1) { invoke<Void>(0x9B581DE7, p0, p1); } // 0x9B581DE7
	static BOOL IS_VEHICLE_STOLEN(Vehicle p0) { return invoke<BOOL>(0x20B61DDE, p0); } // 0x20B61DDE
	static void SET_VEHICLE_IS_STOLEN(Vehicle vehicle, BOOL isStolen) { invoke<Void>(0x70912E42, vehicle, isStolen); } // 0x70912E42
	static void _0xED159AE6(Any p0, Any p1) { invoke<Void>(0xED159AE6, p0, p1); } // 0xED159AE6
	static Any _0xAF8CB3DF(Any p0) { return invoke<Any>(0xAF8CB3DF, p0); } // 0xAF8CB3DF
	static void _0x45F72495(Any p0) { invoke<Void>(0x45F72495, p0); } // 0x45F72495
	static void DETACH_VEHICLE_FROM_CARGOBOB(Any p0, Any p1) { invoke<Void>(0x83D3D331, p0, p1); } // 0x83D3D331
	static Any DETACH_VEHICLE_FROM_ANY_CARGOBOB(Any p0) { return invoke<Any>(0x50E0EABE, p0); } // 0x50E0EABE
	static BOOL IS_VEHICLE_ATTACHED_TO_CARGOBOB(Any p0, Any p1) { return invoke<BOOL>(0x5DEEC76C, p0, p1); } // 0x5DEEC76C
	static Any GET_VEHICLE_ATTACHED_TO_CARGOBOB(Any p0) { return invoke<Any>(0x301A1D24, p0); } // 0x301A1D24
	static void ATTACH_VEHICLE_TO_CARGOBOB(Entity entity, Entity entity2, int instant, float X, float y, float z) { invoke<Void>(0x607DC9D5, entity, entity2, instant, X, y, z); } // 0x607DC9D5
	static Any _0xAF769B81(Any p0) { return invoke<Any>(0xAF769B81, p0); } // 0xAF769B81
	static void _0x4D3C9A99(Any p0) { invoke<Void>(0x4D3C9A99, p0); } // 0x4D3C9A99
	static void GET_CLOSEST_VEHICLE_TURNING_BLOODSPRAY(Any p0) { invoke<Void>(0xA8211EE9, p0); } // 0xA8211EE9
	static void GET_VEHICLE_HAS_BACK_RECURSIVE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x3A8AB081, p0, p1, p2, p3); } // 0x3A8AB081
	static BOOL DOES_VEHICLE_HAVE_WEAPONS(Vehicle vehicle) { return invoke<BOOL>(0xB2E1E1FB, vehicle); } // 0xB2E1E1FB
	static void _0x2EC19A8B(Any p0, Any p1) { invoke<Void>(0x2EC19A8B, p0, p1); } // 0x2EC19A8B
	static void DISABLE_VEHICLE_WEAPON(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xA688B7D1, p0, p1, p2, p3); } // 0xA688B7D1
	static void _0x123E5B90(Any p0, Any p1) { invoke<Void>(0x123E5B90, p0, p1); } // 0x123E5B90
	static void _0xEBC225C1(Any p0, Any p1) { invoke<Void>(0xEBC225C1, p0, p1); } // 0xEBC225C1
	static Any GET_VEHICLE_CLASS(Vehicle vehicle) { return invoke<Any>(0xC025338E, vehicle); } // 0xC025338E
	static Any GET_VEHICLE_CLASS_FROM_NAME(Any p0) { return invoke<Any>(0xEA469980, p0); } // 0xEA469980
	static void SET_PLAYERS_LAST_VEHICLE(Vehicle vehicle) { invoke<Void>(0xDE86447D, vehicle); } // 0xDE86447D
	static void _0x5130DB1E(Any p0, Any p1) { invoke<Void>(0x5130DB1E, p0, p1); } // 0x5130DB1E
	static void _0xB6BE07E0(Any p0, Any p1) { invoke<Void>(0xB6BE07E0, p0, p1); } // 0xB6BE07E0
	static void _0x4BB5605D(Any p0, Any p1) { invoke<Void>(0x4BB5605D, p0, p1); } // 0x4BB5605D
	static void _0x51E0064F(Any p0, Any p1) { invoke<Void>(0x51E0064F, p0, p1); } // 0x51E0064F
	static void _0xAEF9611C(Any p0, Any p1) { invoke<Void>(0xAEF9611C, p0, p1); } // 0xAEF9611C
	static void _0x585E49B6(Any p0, Any p1) { invoke<Void>(0x585E49B6, p0, p1); } // 0x585E49B6
	static void _0x6E67FD35(Any p0, Any p1) { invoke<Void>(0x6E67FD35, p0, p1); } // 0x6E67FD35
	static void SET_VEHICLE_FRICTION_OVERRIDE(Any p0, Any p1) { invoke<Void>(0x32AFD42E, p0, p1); } // 0x32AFD42E
	static void SET_VEHICLE_MAX_STR_TRAP(Any p0, Any p1) { invoke<Void>(0x670913A4, p0, p1); } // 0x670913A4
	static void GET_VEHICLE_DEFORMATION_GET_TREE(Any p0, Any p1) { invoke<Void>(0x98A10A86, p0, p1); } // 0x98A10A86
	static void _0xBC649C49(Any p0, Any p1) { invoke<Void>(0xBC649C49, p0, p1); } // 0xBC649C49
	static void _0x8DD9AA0C(Any p0) { invoke<Void>(0x8DD9AA0C, p0); } // 0x8DD9AA0C
	static BOOL DOES_VEHICLE_EXIST_WITH_DECORATOR(Any p0) { return invoke<BOOL>(0x39E68EDD, p0); } // 0x39E68EDD
	static void _0xAA8BD440(Any p0, Any p1) { invoke<Void>(0xAA8BD440, p0, p1); } // 0xAA8BD440
	static void _0x004926A3(Any p0, Any p1) { invoke<Void>(0x004926A3, p0, p1); } // 0x004926A3
	static void _0xC195803B(Any p0, Any p1) { invoke<Void>(0xC195803B, p0, p1); } // 0xC195803B
	static void _0xB5CC548B(Any p0) { invoke<Void>(0xB5CC548B, p0); } // 0xB5CC548B
	static Any _0x2B2FCC28(Any p0) { return invoke<Any>(0x2B2FCC28, p0); } // 0x2B2FCC28
	static void _0x920C2517(Any p0, Any p1) { invoke<Void>(0x920C2517, p0, p1); } // 0x920C2517
	static Any _0xB73A1486(Any p0) { return invoke<Any>(0xB73A1486, p0); } // 0xB73A1486
}

namespace OBJECT
{
	static Any CREATE_OBJECT(Hash ObjectHash, float XCoord, float YCoord, float ZCoord, int p4, BOOL p5, BOOL dynamic) { return invoke<Any>(0x2F7AA05C, ObjectHash, XCoord, YCoord, ZCoord, p4, p5, dynamic); } // 0x2F7AA05C
	static Any CREATE_OBJECT_2(Hash ObjectHash, float *coord) { return invoke<Any>(0x2F7AA05C, ObjectHash, coord); } // 0x2F7AA05C
	static Any CREATE_OBJECT_NO_OFFSET(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0x58040420, p0, p1, p2, p3, p4, p5, p6); } // 0x58040420
	static void DELETE_OBJECT(Object* Object) { invoke<Void>(0xD6EF9DA7, Object); } // 0xD6EF9DA7
	static Any PLACE_OBJECT_ON_GROUND_PROPERLY(Object Object) { return invoke<Any>(0x8F95A20B, Object); } // 0x8F95A20B
	static Any SLIDE_OBJECT(Object object, float toX, float toY, float toZ, float speedX, float speedY, float speedZ, BOOL collisionCheck) { return invoke<Any>(0x63BFA7A0, object, toX, toY, toZ, speedX, speedY, speedZ, collisionCheck); } // 0x63BFA7A0
	static void SET_OBJECT_TARGETTABLE(Object object, BOOL targettable) { invoke<Void>(0x3F88CD86, object, targettable); } // 0x3F88CD86
	static void _0x483C5C88(Any p0, Any p1) { invoke<Void>(0x483C5C88, p0, p1); } // 0x483C5C88
	static Object GET_CLOSEST_OBJECT_OF_TYPE(float x, float y, float z, float p3, Hash type, BOOL p5) { return invoke<Object>(0x45619B33, x, y, z, p3, type, p5); } // 0x45619B33
	static BOOL HAS_OBJECT_BEEN_BROKEN(Any p0) { return invoke<BOOL>(0xFE21F891, p0); } // 0xFE21F891
	static BOOL HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_BROKEN(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<BOOL>(0x6FC0353D, p0, p1, p2, p3, p4, p5); } // 0x6FC0353D
	static Any _0x7DB578DD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x7DB578DD, p0, p1, p2, p3, p4, p5); } // 0x7DB578DD
	static Vector3 _0x87A42A12(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Vector3>(0x87A42A12, p0, p1, p2, p3, p4, p5, p6); } // 0x87A42A12
	static Any _0x65213FC3(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<Any>(0x65213FC3, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x65213FC3
	static void SET_STATE_OF_CLOSEST_DOOR_OF_TYPE(Hash type, float x, float y, float z, BOOL locked, float heading, BOOL p6) { invoke<Void>(0x38C951A4, type, x, y, z, locked, heading, p6); } // 0x38C951A4
	static void GET_STATE_OF_CLOSEST_DOOR_OF_TYPE(Hash type, float x, float y, float z, BOOL locked, float* heading) { invoke<Void>(0x4B44A83D, type, x, y, z, locked, heading); } // 0x4B44A83D
	static void _0x4E0A260B(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x4E0A260B, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x4E0A260B
	static void ADD_DOOR_TO_SYSTEM(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x9D2D778D, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x9D2D778D
	static void REMOVE_DOOR_FROM_SYSTEM(Object door) { invoke<Void>(0x00253286, door); } // 0x00253286
	static void _0xDF83DB47(Any p0, float p1, BOOL p2, BOOL p3) { invoke<Void>(0xDF83DB47, p0, p1, p2, p3); } // 0xDF83DB47
	static Any _0xD42A41C2(Any p0) { return invoke<Any>(0xD42A41C2, p0); } // 0xD42A41C2
	static Any _0xD649B7E1(Any p0) { return invoke<Any>(0xD649B7E1, p0); } // 0xD649B7E1
	static void _0x4F44AF21(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x4F44AF21, p0, p1, p2, p3); } // 0x4F44AF21
	static void _0x47531446(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x47531446, p0, p1, p2, p3); } // 0x47531446
	static void _0x34883DE3(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x34883DE3, p0, p1, p2, p3); } // 0x34883DE3
	static Any _0xB74C3BD7(Any p0) { return invoke<Any>(0xB74C3BD7, p0); } // 0xB74C3BD7
	static void _0xB4A9A558(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xB4A9A558, p0, p1, p2, p3); } // 0xB4A9A558
	static void _0xECE58AE0(Any p0, Any p1) { invoke<Void>(0xECE58AE0, p0, p1); } // 0xECE58AE0
	static void _0xF736227C(Any p0, Any p1) { invoke<Void>(0xF736227C, p0, p1); } // 0xF736227C
	static Any _0x5AFCD8A1(Any p0) { return invoke<Any>(0x5AFCD8A1, p0); } // 0x5AFCD8A1
	static BOOL IS_DOOR_CLOSED(Object door) { return invoke<BOOL>(0x48659CD7, door); } // 0x48659CD7
	static void _0x9BF33E41(Any p0) { invoke<Void>(0x9BF33E41, p0); } // 0x9BF33E41
	static void _0xF592AD10() { invoke<Void>(0xF592AD10); } // 0xF592AD10
	static Any _0x17FF9393(Any p0) { return invoke<Any>(0x17FF9393, p0); } // 0x17FF9393
	static Any _0xE9AE494F(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xE9AE494F, p0, p1, p2, p3, p4); } // 0xE9AE494F
	static BOOL IS_GARAGE_EMPTY(Any p0, Any p1, Any p2) { return invoke<BOOL>(0xA8B37DEA, p0, p1, p2); } // 0xA8B37DEA
	static Any _0xC33ED360(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xC33ED360, p0, p1, p2, p3); } // 0xC33ED360
	static Any _0x41924877(Any p0, Any p1, Any p2) { return invoke<Any>(0x41924877, p0, p1, p2); } // 0x41924877
	static Any _0x4BD59750(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x4BD59750, p0, p1, p2, p3, p4); } // 0x4BD59750
	static Any _0x7B44D659(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x7B44D659, p0, p1, p2, p3, p4); } // 0x7B44D659
	static Any _0x142C8F76(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x142C8F76, p0, p1, p2, p3); } // 0x142C8F76
	static Any _0x95A9AB2B(Any p0, Any p1, Any p2) { return invoke<Any>(0x95A9AB2B, p0, p1, p2); } // 0x95A9AB2B
	static void _0xA565E27E(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xA565E27E, p0, p1, p2, p3, p4); } // 0xA565E27E
	static void _0x43BB7E48(Any p0, Any p1) { invoke<Void>(0x43BB7E48, p0, p1); } // 0x43BB7E48
	static void _0x6158959E() { invoke<Void>(0x6158959E); } // 0x6158959E
	static BOOL DOES_OBJECT_OF_TYPE_EXIST_AT_COORDS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<BOOL>(0x23FF2BA4, p0, p1, p2, p3, p4, p5); } // 0x23FF2BA4
	static BOOL IS_POINT_IN_ANGLED_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { return invoke<BOOL>(0x73BCFFDC, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0x73BCFFDC
	static void _0x19B17769(Any p0, Any p1) { invoke<Void>(0x19B17769, p0, p1); } // 0x19B17769
	static void SET_OBJECT_PHYSICS_PARAMS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { invoke<Void>(0xE8D11C58, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0xE8D11C58
	static Any GET_OBJECT_FRAGMENT_DAMAGE_HEALTH(Any p0, Any p1) { return invoke<Any>(0xF0B330AD, p0, p1); } // 0xF0B330AD
	static void SET_ACTIVATE_OBJECT_PHYSICS_AS_SOON_AS_IT_IS_UNFROZEN(Any p0, Any p1) { invoke<Void>(0x3E263AE1, p0, p1); } // 0x3E263AE1
	static BOOL IS_ANY_OBJECT_NEAR_POINT(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<BOOL>(0xE9E46941, p0, p1, p2, p3, p4); } // 0xE9E46941
	static BOOL IS_OBJECT_NEAR_POINT(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<BOOL>(0x50A62C43, p0, p1, p2, p3, p4); } // 0x50A62C43
	static void _0xE3261B35(Any p0) { invoke<Void>(0xE3261B35, p0); } // 0xE3261B35
	static void _0x1E82C2AE(Any p0, Any p1, Any p2) { invoke<Void>(0x1E82C2AE, p0, p1, p2); } // 0x1E82C2AE
	static void TRACK_OBJECT_VISIBILITY(Any p0) { invoke<Void>(0x46D06B9A, p0); } // 0x46D06B9A
	static BOOL IS_OBJECT_VISIBLE(Any p0) { return invoke<BOOL>(0xF4FD8AE4, p0); } // 0xF4FD8AE4
	static void _0xF4A1A14A(Any p0, Any p1) { invoke<Void>(0xF4A1A14A, p0, p1); } // 0xF4A1A14A
	static void _0xAF016CC1(Any p0, Any p1) { invoke<Void>(0xAF016CC1, p0, p1); } // 0xAF016CC1
	static void _0x3A68AA46(Any p0, Any p1) { invoke<Void>(0x3A68AA46, p0, p1); } // 0x3A68AA46
	static Any _0xA286DE96(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xA286DE96, p0, p1, p2, p3, p4); } // 0xA286DE96
	static void _0x21F51560(Any p0, Any p1) { invoke<Void>(0x21F51560, p0, p1); } // 0x21F51560
	static Any _0xF1B8817A(Any p0) { return invoke<Any>(0xF1B8817A, p0); } // 0xF1B8817A
	static Any _0xE08C834D(Any p0) { return invoke<Any>(0xE08C834D, p0); } // 0xE08C834D
	static Any _0x020497DE(Any p0) { return invoke<Any>(0x020497DE, p0); } // 0x020497DE
	static Any CREATE_PICKUP(Hash typeHash, float posX, float posY, float posZ, int p4, int amount, BOOL p6, Hash customModelHash) { return invoke<Any>(0x5E14DF68, typeHash, posX, posY, posZ, p4, amount, p6, customModelHash); } // 0x5E14DF68
	static Any CREATE_PICKUP_ROTATE(Hash typeHash, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, int p7, int amount, Any p9, Any p10, Hash customModelHash) { return invoke<Any>(0xF015BFE2, typeHash, posX, posY, posZ, rotX, rotY, rotZ, p7, amount, p9, p10, customModelHash); } // 0xF015BFE2
	static Any CREATE_AMBIENT_PICKUP(Hash AmbientHash, float XCoord, float YCoord, float ZCoord, int p4, int amount, int modelHash, BOOL p7, BOOL p8) { return invoke<Any>(0x17B99CE7, AmbientHash, XCoord, YCoord, ZCoord, p4, amount, modelHash, p7, p8); } // 0x17B99CE7
	static Any CREATE_PORTABLE_PICKUP(unsigned int p0, float p1, float p2, float p3, bool p4, unsigned int p5) { return invoke<Any>(0x8C886BE5, p0, p1, p2, p3, p4, p5); } // 0x8C886BE5
	static Any _0x56A02502(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x56A02502, p0, p1, p2, p3, p4, p5); } // 0x56A02502
	static void ATTACH_PORTABLE_PICKUP_TO_PED(Any p0, Any p1) { invoke<Void>(0x184F6AB3, p0, p1); } // 0x184F6AB3
	static void DETACH_PORTABLE_PICKUP_FROM_PED(Any p0) { invoke<Void>(0x1D094562, p0); } // 0x1D094562
	static void _0x7EFBA039(Any p0, Any p1) { invoke<Void>(0x7EFBA039, p0, p1); } // 0x7EFBA039
	static void _0xA3CDF152(Any p0) { invoke<Void>(0xA3CDF152, p0); } // 0xA3CDF152
	static Vector3 GET_SAFE_PICKUP_COORDS(Any X, Any Y, Any Z, Any p3, Any p4) { return invoke<Vector3>(0x618B5F67, X, Y, Z, p3, p4); } // 0x618B5F67
	static Vector3 GET_PICKUP_COORDS(Any p0) { return invoke<Vector3>(0xC2E1E2C5, p0); } // 0xC2E1E2C5
	static void REMOVE_ALL_PICKUPS_OF_TYPE(Any p0) { invoke<Void>(0x40062C53, p0); } // 0x40062C53
	static BOOL HAS_PICKUP_BEEN_COLLECTED(Any p0) { return invoke<BOOL>(0x0BE5CCED, p0); } // 0x0BE5CCED
	static void REMOVE_PICKUP(Any p0) { invoke<Void>(0x64A7A0E0, p0); } // 0x64A7A0E0
	static void CREATE_MONEY_PICKUPS(float* XCoord, float* YCoord, float* ZCoord, int Vaule, Any p4, Any p5) { invoke<Void>(0x36C9A5EA, XCoord, YCoord, ZCoord, Vaule, p4, p5); } // 0x36C9A5EA
	static BOOL DOES_PICKUP_EXIST(Any p0) { return invoke<BOOL>(0x9C6DA0B3, p0); } // 0x9C6DA0B3
	static BOOL DOES_PICKUP_OBJECT_EXIST(Any p0) { return invoke<BOOL>(0xE0B32108, p0); } // 0xE0B32108
	static Any _0x6052E62E(Any p0) { return invoke<Any>(0x6052E62E, p0); } // 0x6052E62E
	static Any _0xF139681B(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xF139681B, p0, p1, p2, p3, p4); } // 0xF139681B
	static void SET_PICKUP_REGENERATION_TIME(Any p0, Any p1) { invoke<Void>(0xAB11267D, p0, p1); } // 0xAB11267D
	static void _0x7FADB4B9(Any p0, Any p1, Any p2) { invoke<Void>(0x7FADB4B9, p0, p1, p2); } // 0x7FADB4B9
	static void _0x3A8F1BF7(Any p0, Any p1) { invoke<Void>(0x3A8F1BF7, p0, p1); } // 0x3A8F1BF7
	static void SET_TEAM_PICKUP_OBJECT(Any p0, Any p1, Any p2) { invoke<Void>(0x77687DC5, p0, p1, p2); } // 0x77687DC5
	static void _0xCBB5F9B6(Any p0, Any p1, Any p2) { invoke<Void>(0xCBB5F9B6, p0, p1, p2); } // 0xCBB5F9B6
	static void _0x276A7807(Any p0, Any p1, Any p2) { invoke<Void>(0x276A7807, p0, p1, p2); } // 0x276A7807
	static Any _0x000E92DC(Any p0) { return invoke<Any>(0x000E92DC, p0); } // 0x000E92DC
	static void _0x9879AC51(Any p0) { invoke<Void>(0x9879AC51, p0); } // 0x9879AC51
	static void _0xDB18FA01(Any p0) { invoke<Void>(0xDB18FA01, p0); } // 0xDB18FA01
	static void _0xA7E936FD(Any p0, Any p1) { invoke<Void>(0xA7E936FD, p0, p1); } // 0xA7E936FD
	static void _0xB241806C() { invoke<Void>(0xB241806C); } // 0xB241806C
	static void _0xD1BAAFB7(Any p0) { invoke<Void>(0xD1BAAFB7, p0); } // 0xD1BAAFB7
	static void _0x63B02FAD(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x63B02FAD, p0, p1, p2, p3); } // 0x63B02FAD
	static void _0x132B6D92(Any p0, Any p1) { invoke<Void>(0x132B6D92, p0, p1); } // 0x132B6D92
	static Any _0xEDD01937(Any p0) { return invoke<Any>(0xEDD01937, p0); } // 0xEDD01937
	static Any _0x6AE36192(Any p0) { return invoke<Any>(0x6AE36192, p0); } // 0x6AE36192
	static void SET_FORCE_OBJECT_THIS_FRAME(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x3DA41C1A, p0, p1, p2, p3); } // 0x3DA41C1A
	static void _0x2048A7DD(Any p0) { invoke<Void>(0x2048A7DD, p0); } // 0x2048A7DD
}

namespace AI
{
	static void TASK_PAUSE(Any p0, Any p1) { invoke<Void>(0x17A64668, p0, p1); } // 0x17A64668
	static void TASK_STAND_STILL(Any p0, Any p1) { invoke<Void>(0x6F80965D, p0, p1); } // 0x6F80965D
	static void TASK_JUMP(Ped pedHandle, BOOL p1) { invoke<Void>(0x0356E3CE, pedHandle, p1); } // 0x0356E3CE
	static void TASK_COWER(Ped pedHandle, int time) { invoke<Void>(0x9CF1C19B, pedHandle, time); } // 0x9CF1C19B
	static void TASK_HANDS_UP(Ped pedHandle, int time, Any p2, Any p3, Any p4) { invoke<Void>(0x8DCC19C5, pedHandle, time, p2, p3, p4); } // 0x8DCC19C5
	static void _0x3AA39BE9(Any p0, Any p1) { invoke<Void>(0x3AA39BE9, p0, p1); } // 0x3AA39BE9
	static void TASK_OPEN_VEHICLE_DOOR(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x8EE06BF4, p0, p1, p2, p3, p4); } // 0x8EE06BF4
	static void TASK_ENTER_VEHICLE(Ped pedHandle, Vehicle vehicleHandle, int timeout, int seat, float p4, Any p5, Any p6) { invoke<Void>(0xB8689B4E, pedHandle, vehicleHandle, timeout, seat, p4, p5, p6); } // 0xB8689B4E
	static void TASK_LEAVE_VEHICLE(Ped pedHandle, Vehicle vehicleHandle, int flags) { invoke<Void>(0x7B1141C6, pedHandle, vehicleHandle, flags); } // 0x7B1141C6
	static void TASK_SKY_DIVE(Any p0) { invoke<Void>(0xD3874AFA, p0); } // 0xD3874AFA
	static void TASK_PARACHUTE(Any p0, Any p1) { invoke<Void>(0xEC3060A2, p0, p1); } // 0xEC3060A2
	static void TASK_PARACHUTE_TO_TARGET(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xE0104D6C, p0, p1, p2, p3); } // 0xE0104D6C
	static void SET_PARACHUTE_TASK_TARGET(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x6ED3AD81, p0, p1, p2, p3); } // 0x6ED3AD81
	static void SET_PARACHUTE_TASK_THRUST(Any p0, Any p1) { invoke<Void>(0xD07C8AAA, p0, p1); } // 0xD07C8AAA
	static void TASK_RAPPEL_FROM_HELI(Any p0, Any p1) { invoke<Void>(0x2C7ADB93, p0, p1); } // 0x2C7ADB93
	static void TASK_VEHICLE_DRIVE_TO_COORD(Ped pedHandle, Vehicle vehicleHandle, float x, float y, float z, float speed, Any p6, Hash vehicleModel, int drivingMode, Any p9, Any p10) { invoke<Void>(0xE4AC0387, pedHandle, vehicleHandle, x, y, z, speed, p6, vehicleModel, drivingMode, p9, p10); } // 0xE4AC0387
	static void TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(Ped driver, Vehicle vehicle, float x, float y, float z, float speed, int driving_mode, int stop_range) { invoke<Void>(0x1490182A, driver, vehicle, x, y, z, speed, driving_mode, stop_range); } // 0x1490182A
	static void TASK_VEHICLE_DRIVE_WANDER(Ped driver, Vehicle vehicle, float unk1, Any unk2) { invoke<Void>(0x36EC0EB0, driver, vehicle, unk1, unk2); } // 0x36EC0EB0
	static void TASK_FOLLOW_TO_OFFSET_OF_ENTITY(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0x2DF5A6AC, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x2DF5A6AC
	static void TASK_GO_STRAIGHT_TO_COORD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x80A9E7A7, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x80A9E7A7
	static void TASK_GO_STRAIGHT_TO_COORD_RELATIVE_TO_ENTITY(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0xD26CAC68, p0, p1, p2, p3, p4, p5, p6); } // 0xD26CAC68
	static void TASK_ACHIEVE_HEADING(Any p0, Any p1, Any p2) { invoke<Void>(0x0A0E9B42, p0, p1, p2); } // 0x0A0E9B42
	static void TASK_FLUSH_ROUTE() { invoke<Void>(0x34219154); } // 0x34219154
	static void TASK_EXTEND_ROUTE(Any p0, Any p1, Any p2) { invoke<Void>(0x43271F69, p0, p1, p2); } // 0x43271F69
	static void TASK_FOLLOW_POINT_ROUTE(Any p0, Any p1, Any p2) { invoke<Void>(0xB837C816, p0, p1, p2); } // 0xB837C816
	static void TASK_GO_TO_ENTITY(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x374827C2, p0, p1, p2, p3, p4, p5, p6); } // 0x374827C2
	static void TASK_SMART_FLEE_COORD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0xB2E686FC, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xB2E686FC
	static void TASK_SMART_FLEE_PED(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xE52EB560, p0, p1, p2, p3, p4, p5); } // 0xE52EB560
	static void TASK_REACT_AND_FLEE_PED(Any p0, Any p1) { invoke<Void>(0x8A632BD8, p0, p1); } // 0x8A632BD8
	static void TASK_SHOCKING_EVENT_REACT(Any p0, Any p1) { invoke<Void>(0x9BD00ACF, p0, p1); } // 0x9BD00ACF
	static void TASK_WANDER_IN_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0xC6981FB9, p0, p1, p2, p3, p4, p5, p6); } // 0xC6981FB9
	static void TASK_WANDER_STANDARD(Ped pedHandle, int p1, int p2) { invoke<Void>(0xAF59151A, pedHandle, p1, p2); } // 0xAF59151A
	static void TASK_VEHICLE_PARK(Ped pedHandle, Vehicle vehicleHandle, float x, float y, float z, float heading, Any p6, Any p7, Any p8) { invoke<Void>(0x5C85FF90, pedHandle, vehicleHandle, x, y, z, heading, p6, p7, p8); } // 0x5C85FF90
	static void TASK_STEALTH_KILL(Ped killer, Ped target, Hash killType, float p3, BOOL p4) { invoke<Void>(0x0D64C2FA, killer, target, killType, p3, p4); } // 0x0D64C2FA
	static void TASK_PLANT_BOMB(int p0, float x, float y, float z, float degreeAngle) { invoke<Void>(0x33457535, p0, x, y, z, degreeAngle); } // 0x33457535
	static void TASK_FOLLOW_NAV_MESH_TO_COORD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0xFE4A10D9, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xFE4A10D9
	static void SET_PED_PATH_CAN_USE_CLIMBOVERS(Ped ped, BOOL Toggle) { invoke<Void>(0xB7B7D442, ped, Toggle); } // 0xB7B7D442
	static void SET_PED_PATH_CAN_USE_LADDERS(Ped ped, BOOL Toggle) { invoke<Void>(0x53A879EE, ped, Toggle); } // 0x53A879EE
	static void SET_PED_PATH_CAN_DROP_FROM_HEIGHT(int ped, BOOL Toggle) { invoke<Void>(0x394B7AC9, ped, Toggle); } // 0x394B7AC9
	static void _0x55E06443(Ped p0, float p1) { invoke<Void>(0x55E06443, p0, p1); } // 0x55E06443
	static void SET_PED_PATHS_WIDTH_PLANT(Any p0, Any p1) { invoke<Void>(0x9C606EE3, p0, p1); } // 0x9C606EE3
	static void SET_PED_PATH_PREFER_TO_AVOID_WATER(Any p0, Any p1) { invoke<Void>(0x0EA39A29, p0, p1); } // 0x0EA39A29
	static void SET_PED_PATH_AVOID_FIRE(Any p0, Any p1) { invoke<Void>(0xDCC5B934, p0, p1); } // 0xDCC5B934
	static void _0x2AFB14B8(Any p0) { invoke<Void>(0x2AFB14B8, p0); } // 0x2AFB14B8
	static Any GET_NAVMESH_ROUTE_DISTANCE_REMAINING(Any p0, Any p1, Any p2) { return invoke<Any>(0xD9281778, p0, p1, p2); } // 0xD9281778
	static Any GET_NAVMESH_ROUTE_RESULT(Any p0) { return invoke<Any>(0x96491602, p0); } // 0x96491602
	static void TASK_GO_TO_COORD_ANY_MEANS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0xF91DF93B, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xF91DF93B
	static void _0x094B75EF(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { invoke<Void>(0x094B75EF, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0x094B75EF
	static void _0x86DC03F9(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { invoke<Void>(0x86DC03F9, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0x86DC03F9
	static void TASK_PLAY_ANIM(Ped PedHandle, char* AnimSet, char* AnimationName, float Speed, float unk, int Loop, int LastAnimation, float PlaybackRate, BOOL xLock, BOOL yLock, BOOL zLock) { invoke<Void>(0x5AB552C6, PedHandle, AnimSet, AnimationName, Speed, unk, Loop, LastAnimation, PlaybackRate, xLock, yLock, zLock); } // 0x5AB552C6
	static void _0x3DDEB0E6(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14, Any p15) { invoke<Void>(0x3DDEB0E6, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15); } // 0x3DDEB0E6
	static void STOP_ANIM_TASK(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x2B520A57, p0, p1, p2, p3); } // 0x2B520A57
	static void TASK_SCRIPTED_ANIMATION(int p0, script21 *p1, script20* p2, script20 *p3, float p4, float p5) { invoke<Void>(0xFC2DCF47, p0, p1, p2, p3, p4, p5); } // 0xFC2DCF47
	static void PLAY_ENTITY_SCRIPTED_ANIM(int p0, char *p1, char* p2, char *p3, float p4, float p5) { invoke<Void>(0x02F72AE5, p0, p1, p2, p3, p4, p5); } // 0x02F72AE5
	static void STOP_ANIM_PLAYBACK(Any p0, Any p1, Any p2) { invoke<Void>(0xE5F16398, p0, p1, p2); } // 0xE5F16398
	static void SET_ANIM_WEIGHT(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x17229D98, p0, p1, p2, p3, p4); } // 0x17229D98
	static void SET_ANIM_RATE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x6DB46584, p0, p1, p2, p3); } // 0x6DB46584
	static void SET_ANIM_LOOPED(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x095D61A4, p0, p1, p2, p3); } // 0x095D61A4
	static void _0x1582162C(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x1582162C, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x1582162C
	static Any _0x500B6805(Any p0) { return invoke<Any>(0x500B6805, p0); } // 0x500B6805
	static Any _0x7B72AFD1(Any p0) { return invoke<Any>(0x7B72AFD1, p0); } // 0x7B72AFD1
	static Any _0xEF8C3959(Any p0) { return invoke<Any>(0xEF8C3959, p0); } // 0xEF8C3959
	static void TASK_VEHICLE_PLAY_ANIM(Any p0, Any p1, Any p2) { invoke<Void>(0x2B28F598, p0, p1, p2); } // 0x2B28F598
	static void TASK_LOOK_AT_COORD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x7B784DD8, p0, p1, p2, p3, p4, p5, p6); } // 0x7B784DD8
	static void TASK_LOOK_AT_ENTITY(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x991D6619, p0, p1, p2, p3, p4); } // 0x991D6619
	static void TASK_CLEAR_LOOK_AT(Any p0) { invoke<Void>(0x60EB4054, p0); } // 0x60EB4054
	static void OPEN_SEQUENCE_TASK(Object* taskSequence) { invoke<Void>(0xABA6923E, taskSequence); } // 0xABA6923E
	static void CLOSE_SEQUENCE_TASK(Object taskSequence) { invoke<Void>(0x1A7CEBD0, taskSequence); } // 0x1A7CEBD0
	static void TASK_PERFORM_SEQUENCE(Ped ped, Object taskSequence) { invoke<Void>(0x4D9FBD11, ped, taskSequence); } // 0x4D9FBD11
	static void CLEAR_SEQUENCE_TASK(Object* taskSequence) { invoke<Void>(0x47ED03CE, taskSequence); } // 0x47ED03CE
	static void SET_SEQUENCE_TO_REPEAT(Any p0, Any p1) { invoke<Void>(0xCDDF1508, p0, p1); } // 0xCDDF1508
	static Any GET_SEQUENCE_PROGRESS(Any p0) { return invoke<Any>(0xA3419909, p0); } // 0xA3419909
	static Any GET_IS_TASK_ACTIVE(Any p0, Any p1) { return invoke<Any>(0x86FDDF55, p0, p1); } // 0x86FDDF55
	static Any GET_SCRIPT_TASK_STATUS(Any p0, Any p1) { return invoke<Any>(0xB2477B23, p0, p1); } // 0xB2477B23
	static Any _0xAFA914EF(Any p0) { return invoke<Any>(0xAFA914EF, p0); } // 0xAFA914EF
	static void TASK_LEAVE_ANY_VEHICLE(Any p0, Any p1, Any p2) { invoke<Void>(0xDBDD79FA, p0, p1, p2); } // 0xDBDD79FA
	static void TASK_AIM_GUN_SCRIPTED(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x9D296BCD, p0, p1, p2, p3); } // 0x9D296BCD
	static void TASK_AIM_GUN_SCRIPTED_WITH_TARGET(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0xFD517CE3, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xFD517CE3
	static void _0x67E73525(Ped p0, Ped p1, float p2, float p3, float p4, BOOL p5) { invoke<Void>(0x67E73525, p0, p1, p2, p3, p4, p5); } // 0x67E73525
	static Any _0x249EB4EB(Any p0) { return invoke<Any>(0x249EB4EB, p0); } // 0x249EB4EB
	static void TASK_AIM_GUN_AT_ENTITY(Ped pedHandle, Entity entityHandle, int duration, BOOL unknown) { invoke<Void>(0xBE32B3B6, pedHandle, entityHandle, duration, unknown); } // 0xBE32B3B6
	static void TASK_TURN_PED_TO_FACE_ENTITY(Ped pedHandle, Entity entityHandle, int duration) { invoke<Void>(0x3C37C767, pedHandle, entityHandle, duration); } // 0x3C37C767
	static void TASK_AIM_GUN_AT_COORD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0xFBF44AD3, p0, p1, p2, p3, p4, p5, p6); } // 0xFBF44AD3
	static void TASK_SHOOT_AT_COORD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x601C22E3, p0, p1, p2, p3, p4, p5); } // 0x601C22E3
	static void TASK_SHUFFLE_TO_NEXT_VEHICLE_SEAT(Any p0, Any p1) { invoke<Void>(0xBEAF8F67, p0, p1); } // 0xBEAF8F67
	static void CLEAR_PED_TASKS(Ped pedHandle) { invoke<Void>(0xDE3316AB, pedHandle); } // 0xDE3316AB
	static void CLEAR_PED_SECONDARY_TASK(Ped pedHandle) { invoke<Void>(0xA635F451, pedHandle); } // 0xA635F451
	static void TASK_EVERYONE_LEAVE_VEHICLE(Any p0) { invoke<Void>(0xC1971F30, p0); } // 0xC1971F30
	static void TASK_GOTO_ENTITY_OFFSET(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x1A17A85E, p0, p1, p2, p3, p4, p5, p6); } // 0x1A17A85E
	static void TASK_GOTO_ENTITY_OFFSET_XY(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0xBC1E3D0A, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xBC1E3D0A
	static void TASK_TURN_PED_TO_FACE_COORD(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x30463D73, p0, p1, p2, p3, p4); } // 0x30463D73
	static void TASK_VEHICLE_TEMP_ACTION(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x0679DFB8, p0, p1, p2, p3); } // 0x0679DFB8
	static void TASK_VEHICLE_MISSION(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0x20609E56, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x20609E56
	static void TASK_VEHICLE_MISSION_PED_TARGET(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0xC81C4677, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xC81C4677
	static void TASK_VEHICLE_MISSION_COORS_TARGET(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { invoke<Void>(0x6719C109, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x6719C109
	static void TASK_VEHICLE_ESCORT(Ped pedHandle, Vehicle vehicle, Vehicle targetVehicle, int p3, float speed, Any p5, float minDistance, int p7, float p8) { invoke<Void>(0x9FDCB250, pedHandle, vehicle, targetVehicle, p3, speed, p5, minDistance, p7, p8); } // 0x9FDCB250
	static void TASK_VEHICLE_CHASE(Ped pedHandle, Ped targetEntHandle) { invoke<Void>(0x55634798, pedHandle, targetEntHandle); } // 0x55634798
	static void TASK_VEHICLE_HELI_PROTECT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x0CB415EE, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x0CB415EE
	static void _0x2A83083F(Any p0, Any p1, Any p2) { invoke<Void>(0x2A83083F, p0, p1, p2); } // 0x2A83083F
	static void _0x04FD3EE7(Any p0, Any p1) { invoke<Void>(0x04FD3EE7, p0, p1); } // 0x04FD3EE7
	static void TASK_HELI_CHASE(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xAC290A21, p0, p1, p2, p3, p4); } // 0xAC290A21
	static void TASK_PLANE_CHASE(Any p0, Any p1, float p2, float p3, float p4) { invoke<Void>(0x12FA1C28, p0, p1, p2, p3, p4); } // 0x12FA1C28
	static void TASK_PLANE_LAND(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x5F7E23EA, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x5F7E23EA
	static void TASK_HELI_MISSION(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14) { invoke<Void>(0x0C143E97, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14); } // 0x0C143E97
	static void TASK_PLANE_MISSION(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { invoke<Void>(0x1D007E65, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0x1D007E65
	static void TASK_BOAT_MISSION(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { invoke<Void>(0x5865B031, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0x5865B031
	static void TASK_DRIVE_BY(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0x2B84D1C4, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x2B84D1C4
	static void SET_DRIVEBY_TASK_TARGET(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xDA6A6FC1, p0, p1, p2, p3, p4, p5); } // 0xDA6A6FC1
	static void _0x9B76F7E6(Ped ped) { invoke<Void>(0x9B76F7E6, ped); } // 0x9B76F7E6
	static Any _0xB23F46E6(Ped ped) { return invoke<Any>(0xB23F46E6, ped); } // 0xB23F46E6
	static Any _0x500D9244(Any p0) { return invoke<Any>(0x500D9244, p0); } // 0x500D9244
	static void _0x98713C68(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x98713C68, p0, p1, p2, p3, p4, p5); } // 0x98713C68
	static Any _0x291E938C(Any p0) { return invoke<Any>(0x291E938C, p0); } // 0x291E938C
	static void TASK_USE_MOBILE_PHONE(Any p0, Any p1) { invoke<Void>(0x225A38C8, p0, p1); } // 0x225A38C8
	static void TASK_USE_MOBILE_PHONE_TIMED(Any p0, Any p1) { invoke<Void>(0xC99C19F5, p0, p1); } // 0xC99C19F5
	static void TASK_CHAT_TO_PED(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0xA2BE1821, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xA2BE1821
	static void ADD_FOLLOW_NAVMESH_TO_PHONE_TASK(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x00D7303F, p0, p1, p2, p3, p4); } // 0x00D7303F
	static void TASK_WARP_PED_INTO_VEHICLE(Any p0, Any p1, Any p2) { invoke<Void>(0x65D4A35D, p0, p1, p2); } // 0x65D4A35D
	static void TASK_SHOOT_AT_ENTITY(int p0, Entity Entity, Any p2, Any p3) { invoke<Void>(0xAC0631C9, p0, Entity, p2, p3); } // 0xAC0631C9
	static void TASK_CLIMB(Any p0, Any p1) { invoke<Void>(0x90847790, p0, p1); } // 0x90847790
	static void TASK_CLIMB_LADDER(Any p0, Any p1) { invoke<Void>(0x35BB4EE0, p0, p1); } // 0x35BB4EE0
	static void CLEAR_PED_TASKS_IMMEDIATELY(Ped PedHandle) { invoke<Void>(0xBC045625, PedHandle); } // 0xBC045625
	static void TASK_PERFORM_SEQUENCE_FROM_PROGRESS(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xFA60601B, p0, p1, p2, p3); } // 0xFA60601B
	static void SET_NEXT_DESIRED_MOVE_STATE(Any p0) { invoke<Void>(0x4E937D57, p0); } // 0x4E937D57
	static void SET_PED_DESIRED_MOVE_BLEND_RATIO(Any p0, Any p1) { invoke<Void>(0xC65FC712, p0, p1); } // 0xC65FC712
	static Any GET_PED_DESIRED_MOVE_BLEND_RATIO(Any p0) { return invoke<Any>(0x5FEFAB72, p0); } // 0x5FEFAB72
	static void TASK_GOTO_ENTITY_AIMING(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xF1C493CF, p0, p1, p2, p3); } // 0xF1C493CF
	static void TASK_SET_DECISION_MAKER(Any p0, Any p1) { invoke<Void>(0x830AD50C, p0, p1); } // 0x830AD50C
	static void TASK_SET_SPHERE_DEFENSIVE_AREA(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x9F3C5D6A, p0, p1, p2, p3, p4); } // 0x9F3C5D6A
	static void TASK_CLEAR_DEFENSIVE_AREA(Any p0) { invoke<Void>(0x7A05BF0D, p0); } // 0x7A05BF0D
	static void TASK_PED_SLIDE_TO_COORD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x225380EF, p0, p1, p2, p3, p4, p5); } // 0x225380EF
	static void TASK_PED_SLIDE_TO_COORD_HDG_RATE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x38A995C1, p0, p1, p2, p3, p4, p5, p6); } // 0x38A995C1
	static Any ADD_COVER_POINT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<Any>(0xA0AF0B98, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xA0AF0B98
	static void REMOVE_COVER_POINT(Any p0) { invoke<Void>(0x0776888B, p0); } // 0x0776888B
	static BOOL _IS_COVER_POINT_AT_COORDS(float x, float y, float z) { return invoke<BOOL>(0x29F97A71, x, y, z); } // 0x29F97A71
	static Vector3 _0xC6B6CCC1(Any p0) { return invoke<Vector3>(0xC6B6CCC1, p0); } // 0xC6B6CCC1
	static void TASK_COMBAT_PED(Ped pedHandle, Player p1, Any p2, Any p3) { invoke<Void>(0xCB0D8932, pedHandle, p1, p2, p3); } // 0xCB0D8932
	static void TASK_COMBAT_PED_TIMED(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xF5CA2A45, p0, p1, p2, p3); } // 0xF5CA2A45
	static void TASK_SEEK_COVER_FROM_POS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x83F18EE9, p0, p1, p2, p3, p4, p5); } // 0x83F18EE9
	static void TASK_SEEK_COVER_FROM_PED(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xC1EC907E, p0, p1, p2, p3); } // 0xC1EC907E
	static void TASK_SEEK_COVER_TO_COVER_POINT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x3D026B29, p0, p1, p2, p3, p4, p5, p6); } // 0x3D026B29
	static void TASK_SEEK_COVER_TO_COORDS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0xFFFE754E, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xFFFE754E
	static void TASK_PUT_PED_DIRECTLY_INTO_COVER(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { invoke<Void>(0xC9F00E68, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0xC9F00E68
	static void TASK_EXIT_COVER(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xC829FAC9, p0, p1, p2, p3, p4); } // 0xC829FAC9
	static void TASK_PUT_PED_DIRECTLY_INTO_MELEE(Any p0, Any p1, float p2, float p3, float p4, Any p5) { invoke<Void>(0x79E1D27D, p0, p1, p2, p3, p4, p5); } // 0x79E1D27D
	static void TASK_TOGGLE_DUCK(Any p0, Any p1) { invoke<Void>(0x61CFBCBF, p0, p1); } // 0x61CFBCBF
	static void TASK_GUARD_CURRENT_POSITION(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x2FB099E9, p0, p1, p2, p3); } // 0x2FB099E9
	static void _0x7AF0133D(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x7AF0133D, p0, p1, p2, p3, p4, p5, p6); } // 0x7AF0133D
	static void TASK_GUARD_SPHERE_DEFENSIVE_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { invoke<Void>(0x86B76CB7, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x86B76CB7
	static void TASK_STAND_GUARD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xD130F636, p0, p1, p2, p3, p4, p5); } // 0xD130F636
	static void SET_DRIVE_TASK_CRUISE_SPEED(Any p0, Any p1) { invoke<Void>(0x3CEC07B1, p0, p1); } // 0x3CEC07B1
	static void SET_DRIVE_TASK_MAX_CRUISE_SPEED(Any p0, Any p1) { invoke<Void>(0x7FDF6131, p0, p1); } // 0x7FDF6131
	static void SET_DRIVE_TASK_DRIVING_STYLE(Any DRIVER_PED, Any DRIVING_STYLE) { invoke<Void>(0x59C5FAD7, DRIVER_PED, DRIVING_STYLE); } // 0x59C5FAD7
	static void ADD_COVER_BLOCKING_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0x3536946F, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x3536946F
	static void REMOVE_ALL_COVER_BLOCKING_AREAS() { invoke<Void>(0xCF9221A7); } // 0xCF9221A7
	static void TASK_START_SCENARIO_IN_PLACE(Any p0, char* p1, Any p2, Any p3) { invoke<Void>(0xE50D6DDE, p0, p1, p2, p3); } // 0xE50D6DDE
	static void TASK_START_SCENARIO_AT_POSITION(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0xAA2C4AC2, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xAA2C4AC2
	static void TASK_USE_NEAREST_SCENARIO_TO_COORD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x9C50FBF0, p0, p1, p2, p3, p4, p5); } // 0x9C50FBF0
	static void TASK_USE_NEAREST_SCENARIO_TO_COORD_WARP(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x1BE9D65C, p0, p1, p2, p3, p4, p5); } // 0x1BE9D65C
	static void TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xE32FFB22, p0, p1, p2, p3, p4, p5); } // 0xE32FFB22
	static void TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD_WARP(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xBAB4C0AE, p0, p1, p2, p3, p4, p5); } // 0xBAB4C0AE
	static BOOL DOES_SCENARIO_EXIST_IN_AREA(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<BOOL>(0xFA7F5047, p0, p1, p2, p3, p4); } // 0xFA7F5047
	static Any _0x0FB138A5(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x0FB138A5, p0, p1, p2, p3, p4, p5); } // 0x0FB138A5
	static BOOL IS_SCENARIO_OCCUPIED(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<BOOL>(0x697FC008, p0, p1, p2, p3, p4); } // 0x697FC008
	static Any _0x9BE9C691(Any p0) { return invoke<Any>(0x9BE9C691, p0); } // 0x9BE9C691
	static void _0x1984A5D1(Any p0, Any p1, Any p2) { invoke<Void>(0x1984A5D1, p0, p1, p2); } // 0x1984A5D1
	static BOOL DOES_SCENARIO_GROUP_EXIST(Any p0) { return invoke<BOOL>(0x5F072EB9, p0); } // 0x5F072EB9
	static BOOL IS_SCENARIO_GROUP_ENABLED(Any p0) { return invoke<BOOL>(0x90991122, p0); } // 0x90991122
	static void SET_SCENARIO_GROUP_ENABLED(Any p0, Any p1) { invoke<Void>(0x116997B1, p0, p1); } // 0x116997B1
	static void _0xBF55025D() { invoke<Void>(0xBF55025D); } // 0xBF55025D
	static void SET_EXCLUSIVE_SCENARIO_GROUP(Any p0) { invoke<Void>(0x59DB8F26, p0); } // 0x59DB8F26
	static void RESET_EXCLUSIVE_SCENARIO_GROUP() { invoke<Void>(0x17F9DFE8); } // 0x17F9DFE8
	static BOOL IS_SCENARIO_TYPE_ENABLED(Any p0) { return invoke<BOOL>(0xAE37E969, p0); } // 0xAE37E969
	static void SET_SCENARIO_TYPE_ENABLED(Any p0, Any p1) { invoke<Void>(0xDB18E5DE, p0, p1); } // 0xDB18E5DE
	static void _0xF58FDEB4() { invoke<Void>(0xF58FDEB4); } // 0xF58FDEB4
	static BOOL IS_PED_ACTIVE_IN_SCENARIO(Any p0) { return invoke<BOOL>(0x05038F1A, p0); } // 0x05038F1A
	static void TASK_COMBAT_HATED_TARGETS_IN_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xDF099E18, p0, p1, p2, p3, p4, p5); } // 0xDF099E18
	static void TASK_COMBAT_HATED_TARGETS_AROUND_PED(Player p0, float AreaToAttack, Any p2) { invoke<Void>(0x2E7064E4, p0, AreaToAttack, p2); } // 0x2E7064E4
	static void TASK_COMBAT_HATED_TARGETS_AROUND_PED_TIMED(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xF127AD6A, p0, p1, p2, p3); } // 0xF127AD6A
	static void TASK_THROW_PROJECTILE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xF65C20A7, p0, p1, p2, p3); } // 0xF65C20A7
	static void TASK_SWAP_WEAPON(Any p0, Any p1) { invoke<Void>(0xDAF4F8FC, p0, p1); } // 0xDAF4F8FC
	static void TASK_RELOAD_WEAPON(Any p0, Any p1) { invoke<Void>(0xCA6E91FD, p0, p1); } // 0xCA6E91FD
	static BOOL IS_PED_GETTING_UP(Any p0) { return invoke<BOOL>(0x320813E6, p0); } // 0x320813E6
	static void TASK_WRITHE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x0FDC54FC, p0, p1, p2, p3); } // 0x0FDC54FC
	static BOOL IS_PED_IN_WRITHE(Any p0) { return invoke<BOOL>(0x09E61921, p0); } // 0x09E61921
	static void OPEN_PATROL_ROUTE(Any p0) { invoke<Void>(0xF33F83CA, p0); } // 0xF33F83CA
	static void CLOSE_PATROL_ROUTE() { invoke<Void>(0x67305E59); } // 0x67305E59
	static void ADD_PATROL_ROUTE_NODE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0x21B48F10, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x21B48F10
	static void ADD_PATROL_ROUTE_LINK(Any p0, Any p1) { invoke<Void>(0xD8761BB3, p0, p1); } // 0xD8761BB3
	static void CREATE_PATROL_ROUTE() { invoke<Void>(0x0A6C7864); } // 0x0A6C7864
	static void DELETE_PATROL_ROUTE(Any p0) { invoke<Void>(0x2A4E6706, p0); } // 0x2A4E6706
	static void TASK_PATROL(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xB92E5AF6, p0, p1, p2, p3, p4); } // 0xB92E5AF6
	static void TASK_STAY_IN_COVER(Any p0) { invoke<Void>(0xA27A9413, p0); } // 0xA27A9413
	static void _0x50779A2C(Ped ped, float x, float y, float z) { invoke<Void>(0x50779A2C, ped, x, y, z); } // 0x50779A2C
	static void ADD_VEHICLE_SUBTASK_ATTACK_PED(Any p0, Any p1) { invoke<Void>(0x80461113, p0, p1); } // 0x80461113
	static void TASK_VEHICLE_SHOOT_AT_PED(Any p0, Any p1, Any p2) { invoke<Void>(0x59677BA0, p0, p1, p2); } // 0x59677BA0
	static void TASK_VEHICLE_AIM_AT_PED(Any p0, Any p1) { invoke<Void>(0x920AE6DB, p0, p1); } // 0x920AE6DB
	static void TASK_VEHICLE_SHOOT_AT_COORD(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xA7AAA4D6, p0, p1, p2, p3, p4); } // 0xA7AAA4D6
	static void TASK_VEHICLE_AIM_AT_COORD(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x010F47CE, p0, p1, p2, p3); } // 0x010F47CE
	static void TASK_VEHICLE_GOTO_NAVMESH(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x55CF3BCD, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x55CF3BCD
	static void TASK_GO_TO_COORD_WHILE_AIMING_AT_COORD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14) { invoke<Void>(0x1552DC91, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14); } // 0x1552DC91
	static void TASK_GO_TO_COORD_WHILE_AIMING_AT_ENTITY(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13) { invoke<Void>(0x9BD52ABD, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); } // 0x9BD52ABD
	static void TASK_GO_TO_COORD_AND_AIM_AT_HATED_ENTITIES_NEAR_COORD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14) { invoke<Void>(0x3F91358E, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14); } // 0x3F91358E
	static void TASK_GO_TO_ENTITY_WHILE_AIMING_AT_COORD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { invoke<Void>(0xD896CD82, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0xD896CD82
	static void TASK_GO_TO_ENTITY_WHILE_AIMING_AT_ENTITY(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0x68E36B7A, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x68E36B7A
	static void SET_HIGH_FALL_TASK(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xBBB26172, p0, p1, p2, p3); } // 0xBBB26172
	static void REQUEST_WAYPOINT_RECORDING(Any p0) { invoke<Void>(0xAFABFB5D, p0); } // 0xAFABFB5D
	static Any _0x87125F5D(Any p0) { return invoke<Any>(0x87125F5D, p0); } // 0x87125F5D
	static void REMOVE_WAYPOINT_RECORDING(Any p0) { invoke<Void>(0x624530B0, p0); } // 0x624530B0
	static Any _0xF5F9B71E(Any p0, Any p1) { return invoke<Any>(0xF5F9B71E, p0, p1); } // 0xF5F9B71E
	static Any _0x19266913(Any p0, Any p1, Any p2) { return invoke<Any>(0x19266913, p0, p1, p2); } // 0x19266913
	static Any _0xC765633A(Any p0, Any p1) { return invoke<Any>(0xC765633A, p0, p1); } // 0xC765633A
	static Any _0xC4CD35AF(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xC4CD35AF, p0, p1, p2, p3, p4); } // 0xC4CD35AF
	static void TASK_FOLLOW_WAYPOINT_RECORDING(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xADF9904D, p0, p1, p2, p3, p4); } // 0xADF9904D
	static BOOL IS_WAYPOINT_PLAYBACK_GOING_ON_FOR_PED(Any p0) { return invoke<BOOL>(0x85B7725F, p0); } // 0x85B7725F
	static Any GET_PED_WAYPOINT_PROGRESS(Any p0) { return invoke<Any>(0x3595B104, p0); } // 0x3595B104
	static Any GET_PED_WAYPOINT_DISTANCE(Any p0) { return invoke<Any>(0x084B35B0, p0); } // 0x084B35B0
	static Any SET_PED_WAYPOINT_ROUTE_OFFSET(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xF867F747, p0, p1, p2, p3); } // 0xF867F747
	static Any _0xE8422AC4(Any p0, Any p1) { return invoke<Any>(0xE8422AC4, p0, p1); } // 0xE8422AC4
	static Any WAYPOINT_PLAYBACK_GET_IS_PAUSED(Any p0) { return invoke<Any>(0xA6BB5717, p0); } // 0xA6BB5717
	static void WAYPOINT_PLAYBACK_PAUSE(Any p0, Any p1, Any p2) { invoke<Void>(0xFE39ECF8, p0, p1, p2); } // 0xFE39ECF8
	static void WAYPOINT_PLAYBACK_RESUME(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x50F392EF, p0, p1, p2, p3); } // 0x50F392EF
	static void WAYPOINT_PLAYBACK_OVERRIDE_SPEED(Any p0, Any p1, Any p2) { invoke<Void>(0x23E6BA96, p0, p1, p2); } // 0x23E6BA96
	static void WAYPOINT_PLAYBACK_USE_DEFAULT_SPEED(Any p0) { invoke<Void>(0x1BBB2CAC, p0); } // 0x1BBB2CAC
	static void _0x4DFD5FEC(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x4DFD5FEC, p0, p1, p2, p3); } // 0x4DFD5FEC
	static void WAYPOINT_PLAYBACK_START_AIMING_AT_PED(Any p0, Any p1, Any p2) { invoke<Void>(0x75E60CF6, p0, p1, p2); } // 0x75E60CF6
	static void WAYPOINT_PLAYBACK_START_AIMING_AT_COORD(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xF120A34E, p0, p1, p2, p3, p4); } // 0xF120A34E
	static void WAYPOINT_PLAYBACK_START_SHOOTING_AT_PED(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xBD5F0EB8, p0, p1, p2, p3); } // 0xBD5F0EB8
	static void WAYPOINT_PLAYBACK_START_SHOOTING_AT_COORD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xCDDB44D5, p0, p1, p2, p3, p4, p5); } // 0xCDDB44D5
	static void WAYPOINT_PLAYBACK_STOP_AIMING_OR_SHOOTING(Any p0) { invoke<Void>(0x6D7CF40C, p0); } // 0x6D7CF40C
	static void ASSISTED_MOVEMENT_REQUEST_ROUTE(char* route) { invoke<Void>(0x48262EDA, route); } // 0x48262EDA
	static void ASSISTED_MOVEMENT_REMOVE_ROUTE(Any p0) { invoke<Void>(0xB3CEC06F, p0); } // 0xB3CEC06F
	static Any _0x79B067AF(Any p0) { return invoke<Any>(0x79B067AF, p0); } // 0x79B067AF
	static void _0x01CAAFCC(Any p0, Any p1) { invoke<Void>(0x01CAAFCC, p0, p1); } // 0x01CAAFCC
	static void _0x8FB923EC(Any p0) { invoke<Void>(0x8FB923EC, p0); } // 0x8FB923EC
	static void TASK_VEHICLE_FOLLOW_WAYPOINT_RECORDING(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0x959818B6, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x959818B6
	static BOOL IS_WAYPOINT_PLAYBACK_GOING_ON_FOR_VEHICLE(Any p0) { return invoke<BOOL>(0x80DD15DB, p0); } // 0x80DD15DB
	static Any GET_VEHICLE_WAYPOINT_PROGRESS(Any p0) { return invoke<Any>(0xD3CCF64E, p0); } // 0xD3CCF64E
	static Any GET_VEHICLE_WAYPOINT_TARGET_POINT(Any p0) { return invoke<Any>(0x81049608, p0); } // 0x81049608
	static void VEHICLE_WAYPOINT_PLAYBACK_PAUSE(Any p0) { invoke<Void>(0x7C00B415, p0); } // 0x7C00B415
	static void VEHICLE_WAYPOINT_PLAYBACK_RESUME(Any p0) { invoke<Void>(0xBEB14C82, p0); } // 0xBEB14C82
	static void VEHICLE_WAYPOINT_PLAYBACK_USE_DEFAULT_SPEED(Any p0) { invoke<Void>(0x923C3AA4, p0); } // 0x923C3AA4
	static void VEHICLE_WAYPOINT_PLAYBACK_OVERRIDE_SPEED(Any p0, Any p1) { invoke<Void>(0xBE1E7BB4, p0, p1); } // 0xBE1E7BB4
	static void TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Any p0, Any p1) { invoke<Void>(0x1B54FB6B, p0, p1); } // 0x1B54FB6B
	static void TASK_FORCE_MOTION_STATE(Any p0, Any p1, Any p2) { invoke<Void>(0xCAD2EF77, p0, p1, p2); } // 0xCAD2EF77
	static void _0x6F5D215F(Any p0, char* p1, float p2, Any p3, char* p4, Any p5) { invoke<Void>(0x6F5D215F, p0, p1, p2, p3, p4, p5); } // 0x6F5D215F
	static void _0x71A5C5DB(int ped, char *anim, float x, float y, float z, float rotx, float roty, float rotz, int unknown1, float multiplier, bool unknown2, char *dict, int flags) { invoke<Void>(0x71A5C5DB, ped, anim, x, y, z, rotx, roty, rotz, unknown1, multiplier, unknown2, dict, flags); } // 0x71A5C5DB
	static Any _0x902656EB(Any p0) { return invoke<Any>(0x902656EB, p0); } // 0x902656EB
	static Any _0x92FDBAE6(Any p0) { return invoke<Any>(0x92FDBAE6, p0); } // 0x92FDBAE6
	static Any _0x885724DE(Any p0, Any p1) { return invoke<Any>(0x885724DE, p0, p1); } // 0x885724DE
	static Any _0x96C0277B(Any p0) { return invoke<Any>(0x96C0277B, p0); } // 0x96C0277B
	static void _0xA79BE783(Any p0, Any p1, Any p2) { invoke<Void>(0xA79BE783, p0, p1, p2); } // 0xA79BE783
	static void _0xF3538041(Any p0, Any p1, Any p2) { invoke<Void>(0xF3538041, p0, p1, p2); } // 0xF3538041
	static Any _0x1EBB6F3D(Any p0, Any p1) { return invoke<Any>(0x1EBB6F3D, p0, p1); } // 0x1EBB6F3D
	static Any _0x72FA5EF2(Any p0, Any p1) { return invoke<Any>(0x72FA5EF2, p0, p1); } // 0x72FA5EF2
	static Any _0xE9DAF877(Any p0) { return invoke<Any>(0xE9DAF877, p0); } // 0xE9DAF877
	static Any _0xD21639A8(Any p0) { return invoke<Any>(0xD21639A8, p0); } // 0xD21639A8
	static Any _0xE76A2353(Any p0) { return invoke<Any>(0xE76A2353, p0); } // 0xE76A2353
	static Any _0xDD616893(Any p0) { return invoke<Any>(0xDD616893, p0); } // 0xDD616893
	static BOOL IS_PED_STILL(Any p0) { return invoke<BOOL>(0x09E3418D, p0); } // 0x09E3418D
	static BOOL IS_PED_WALKING(Any p0) { return invoke<BOOL>(0x4B865C4A, p0); } // 0x4B865C4A
	static BOOL IS_PED_RUNNING(Any p0) { return invoke<BOOL>(0xE9A5578F, p0); } // 0xE9A5578F
	static BOOL IS_PED_SPRINTING(Any p0) { return invoke<BOOL>(0x4F3E0633, p0); } // 0x4F3E0633
	static BOOL IS_PED_STRAFING(Any p0) { return invoke<BOOL>(0xEFEED13C, p0); } // 0xEFEED13C
	static void TASK_SYNCHRONIZED_SCENE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0x4F217E7B, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x4F217E7B
	static void _0x4D210467(Ped ped, char* anim, char* p2, char* p3, char* p4, int p5, Vehicle vehicle, Any p7, Any p8) { invoke<Void>(0x4D210467, ped, anim, p2, p3, p4, p5, vehicle, p7, p8); } // 0x4D210467
	static void _0xF65F0F4F(Ped ped, Vehicle vehicle) { invoke<Void>(0xF65F0F4F, ped, vehicle); } // 0xF65F0F4F
	static void _0x1683FE66(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { invoke<Void>(0x1683FE66, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x1683FE66
	static void _0x6345EC80(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x6345EC80, p0, p1, p2, p3); } // 0x6345EC80
	static void TASK_ARREST_PED(Any p0, Any p1) { invoke<Void>(0xBC0F153D, p0, p1); } // 0xBC0F153D
	static BOOL IS_PED_RUNNING_ARREST_TASK(Any p0) { return invoke<BOOL>(0x6942DB7A, p0); } // 0x6942DB7A
	static BOOL IS_PED_BEING_ARRESTED(Any p0) { return invoke<BOOL>(0x5FF6C2ED, p0); } // 0x5FF6C2ED
	static void UNCUFF_PED(Any p0) { invoke<Void>(0xA23A1D61, p0); } // 0xA23A1D61
	static BOOL IS_PED_CUFFED(Any p0) { return invoke<BOOL>(0x511CE741, p0); } // 0x511CE741
}

namespace GAMEPLAY
{
	static int GET_ALLOCATED_STACK_SIZE() { return invoke<int>(0x4E9CA30A); } // 0x4E9CA30A
	static BOOL _SET_ALLOCATED_STACK_SIZE(int StackSize) { return invoke<BOOL>(0x11A178B8, StackSize); } // 0x11A178B8
	static void SET_RANDOM_SEED(Any p0) { invoke<Void>(0xDB3FEB5C, p0); } // 0xDB3FEB5C
	static void SET_TIME_SCALE(float Time) { invoke<Void>(0xA7F84694, Time); } // 0xA7F84694
	static void SET_MISSION_FLAG(Any p0) { invoke<Void>(0x57592D52, p0); } // 0x57592D52
	static Any GET_MISSION_FLAG() { return invoke<Any>(0x95115F97); } // 0x95115F97
	static void SET_RANDOM_EVENT_FLAG(Any p0) { invoke<Void>(0xA77F31E8, p0); } // 0xA77F31E8
	static Any GET_RANDOM_EVENT_FLAG() { return invoke<Any>(0x794CC92C); } // 0x794CC92C
	static void _0x8B2DE971(Any p0) { invoke<Void>(0x8B2DE971, p0); } // 0x8B2DE971
	static void _0xE77199F7(Any p0) { invoke<Void>(0xE77199F7, p0); } // 0xE77199F7
	static Any _0xA8171E9E() { return invoke<Any>(0xA8171E9E); } // 0xA8171E9E
	static Any _0x353E8056() { return invoke<Any>(0x353E8056); } // 0x353E8056
	static BOOL IS_PREV_WEATHER_TYPE(Any p0) { return invoke<BOOL>(0x250ADA61, p0); } // 0x250ADA61
	static BOOL IS_NEXT_WEATHER_TYPE(Any p0) { return invoke<BOOL>(0x99CB167F, p0); } // 0x99CB167F
	static void SET_WEATHER_TYPE_PERSIST(char* WeatherType) { invoke<Void>(0xC6C04C75, WeatherType); } // 0xC6C04C75

	int checkOnPlayerSpecificSend = 0;
	bool checkOnPlayer(unsigned int evt, CNetGamePlayer *player) {
		if (player->nonPhysicalPlayerData->playerIndex == checkOnPlayerSpecificSend) {
			//printf("Choosing to send specifically to %s",player->playerInfo->name);
			return true;
		}
		return false;
	}
	static void SET_WEATHER_TYPE_NOW_PERSIST(char* WeatherType, int player = -1) { 
		checkOnPlayerSpecificSend = player;
		ui64 orig = *(ui64*)(0x1C6BAB0);//log original function value
		if (checkOnPlayerSpecificSend != -1)
			*(ui64*)(0x1C6BAB0) = *(ui64*)(&checkOnPlayer);//patch to custom check if set to per player
		invoke<Void>(0xC869FE97, WeatherType); 
		*(ui64*)(0x1C6BAB0) = orig;//reset back to original func
	} // 0xC869FE97
	static void SET_WEATHER_TYPE_NOW(char* WeatherType) { invoke<Void>(0x361E9EAC, WeatherType); } // 0x361E9EAC
	static void _SET_WEATHER_TYPE_OVER_TIME(char* WeatherType, float Time) { invoke<Void>(0x386F0D25, WeatherType, Time); } // 0x386F0D25
	static void SET_RANDOM_WEATHER_TYPE() { invoke<Void>(0xE7AA1BC9); } // 0xE7AA1BC9
	static void CLEAR_WEATHER_TYPE_PERSIST() { invoke<Void>(0x6AB757D8); } // 0x6AB757D8
	static void _0x9A5C1D56(Any p0, Any p1, Any p2) { invoke<Void>(0x9A5C1D56, p0, p1, p2); } // 0x9A5C1D56
	static void _0x5CA74040(Any p0, Any p1, Any p2) { invoke<Void>(0x5CA74040, p0, p1, p2); } // 0x5CA74040
	static void SET_OVERRIDE_WEATHER(char* WeatherType) { invoke<Void>(0xD9082BB5, WeatherType); } // 0xD9082BB5
	static void CLEAR_OVERRIDE_WEATHER() { invoke<Void>(0x7740EA4E); } // 0x7740EA4E
	static void _0x625181DC(Any p0) { invoke<Void>(0x625181DC, p0); } // 0x625181DC
	static void _0xBEBBFDC8(Any p0) { invoke<Void>(0xBEBBFDC8, p0); } // 0xBEBBFDC8
	static void _0x6926AB03(Any p0) { invoke<Void>(0x6926AB03, p0); } // 0x6926AB03
	static void _0xD447439D(Any p0) { invoke<Void>(0xD447439D, p0); } // 0xD447439D
	static void _0x584E9C59(Any p0) { invoke<Void>(0x584E9C59, p0); } // 0x584E9C59
	static void _0x5656D578(Any p0) { invoke<Void>(0x5656D578, p0); } // 0x5656D578
	static void _0x0DE40C28(Any p0) { invoke<Void>(0x0DE40C28, p0); } // 0x0DE40C28
	static void _0x98C9138B(Any p0) { invoke<Void>(0x98C9138B, p0); } // 0x98C9138B
	static void _0xFB1A9CDE(Any p0) { invoke<Void>(0xFB1A9CDE, p0); } // 0xFB1A9CDE
	static void _0x1C0CAE89(Any p0) { invoke<Void>(0x1C0CAE89, p0); } // 0x1C0CAE89
	static void _0x4671AC2E(Any p0) { invoke<Void>(0x4671AC2E, p0); } // 0x4671AC2E
	static void _0xDA02F415(float p0) { invoke<Void>(0xDA02F415, p0); } // 0xDA02F415
	static void _0x5F3DDEC0(Any p0) { invoke<Void>(0x5F3DDEC0, p0); } // 0x5F3DDEC0
	static void _0x63A89684(Any p0) { invoke<Void>(0x63A89684, p0); } // 0x63A89684
	static void SET_WIND(Any p0) { invoke<Void>(0xC6294698, p0); } // 0xC6294698
	static void SET_WIND_SPEED(float Speed) { invoke<Void>(0x45705F94, Speed); } // 0x45705F94
	static Any GET_WIND_SPEED() { return invoke<Any>(0x098F0F3C); } // 0x098F0F3C
	static void SET_WIND_DIRECTION(Any p0) { invoke<Void>(0x381AEEE9, p0); } // 0x381AEEE9
	static Vector3 GET_WIND_DIRECTION() { return invoke<Vector3>(0x89499A0D); } // 0x89499A0D
	static Any GET_RAIN_LEVEL() { return invoke<Any>(0xC9F67F28); } // 0xC9F67F28
	static Any GET_SNOW_LEVEL() { return invoke<Any>(0x1B09184F); } // 0x1B09184F
	static void _0xDF38165E() { invoke<Void>(0xDF38165E); } // 0xDF38165E
	static void _0x8727A4C5(Any p0) { invoke<Void>(0x8727A4C5, p0); } // 0x8727A4C5
	static void _0x96B2FD08(Any p0) { invoke<Void>(0x96B2FD08, p0); } // 0x96B2FD08
	static void _0xED88FC61(char* p0, float p1) { invoke<Void>(0xED88FC61, p0, p1); } // 0xED88FC61
	static void _0xC9FA6E07(Any p0, Any p1) { invoke<Void>(0xC9FA6E07, p0, p1); } // 0xC9FA6E07
	static void _0x2D7787BC() { invoke<Void>(0x2D7787BC); } // 0x2D7787BC
	static int GET_GAME_TIMER() { return invoke<int>(0xA4EA0691); } // 0xA4EA0691
	static float GET_FRAME_TIME() { return invoke<float>(0x96374262); } // 0x96374262
	static float* GET_FRAME_COUNT() { return invoke<float*>(0xB477A015); } // 0xB477A015
	static float GET_RANDOM_FLOAT_IN_RANGE(float p0, float p1) { return invoke<float>(0x0562C4D0, p0, p1); } // 0x0562C4D0
	static int GET_RANDOM_INT_IN_RANGE(int StartRange, int EndRange) { return invoke<int>(0x4051115B, StartRange, EndRange); } // 0x4051115B
	static Any GET_GROUND_Z_FOR_3D_COORD(float x, float y, float z, float* groundZ) { return invoke<Any>(0xA1BFD5E0, x, y, z, groundZ); } // 0xA1BFD5E0
	static Any _0x64D91CED(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x64D91CED, p0, p1, p2, p3, p4); } // 0x64D91CED
	static float ASIN(float p0) { return invoke<float>(0x998E5CAD, p0); } // 0x998E5CAD
	static float ACOS(float p0) { return invoke<float>(0xF4038776, p0); } // 0xF4038776
	static float TAN(float p0) { return invoke<float>(0xD320CE5E, p0); } // 0xD320CE5E
	static float ATAN(float p0) { return invoke<float>(0x7A03CC8E, p0); } // 0x7A03CC8E
	static float ATAN2(float p0, float p1) { return invoke<float>(0x2508AC81, p0, p1); } // 0x2508AC81   returns degrees
	static Any GET_DISTANCE_BETWEEN_COORDS(float x1, float y1, float z1, float x2, float y2, float z2, BOOL unknown) { return invoke<Any>(0xF698765E, x1, y1, z1, x2, y2, z2, unknown); } // 0xF698765E
	static Any GET_ANGLE_BETWEEN_2D_VECTORS(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xDBF75E58, p0, p1, p2, p3); } // 0xDBF75E58
	static Any GET_HEADING_FROM_VECTOR_2D(Any p0, Any p1) { return invoke<Any>(0xD209D52B, p0, p1); } // 0xD209D52B
	static Any _0x89459F0A(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<Any>(0x89459F0A, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x89459F0A
	static Vector3 _0xCAECF37E(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<Vector3>(0xCAECF37E, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xCAECF37E
	static Any _0xC6CC812C(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { return invoke<Any>(0xC6CC812C, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0xC6CC812C
	static void SET_BIT(int* var, int bit) { invoke<Void>(0x4EFE7E6B, var, bit); } // 0x4EFE7E6B
	static void CLEAR_BIT(int* var, int bit) { invoke<Void>(0x8BC9E618, var, bit); } // 0x8BC9E618
	static int GET_HASH_KEY(char* ToHash) { return invoke<int>(0x98EFF6F1, ToHash); } // 0x98EFF6F1
	static void _0x87B92190(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { invoke<Void>(0x87B92190, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0x87B92190
	static BOOL IS_AREA_OCCUPIED(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { return invoke<BOOL>(0xC013972F, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0xC013972F
	static BOOL IS_POSITION_OCCUPIED(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return invoke<BOOL>(0x452E8D9E, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x452E8D9E
	static BOOL IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<BOOL>(0xC161558D, p0, p1, p2, p3, p4, p5, p6); } // 0xC161558D
	static void CLEAR_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x854E9AB8, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x854E9AB8
	//static void _0x20E4FFD9(float *p0, float p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x20E4FFD9, p0, p3, p4, p5, p6, p7); } // 0x20E4FFD9
	static void _CLEAR_AREA_OF_EVERYTHING(float x, float y, float z, float radius, BOOL p4, BOOL p5, BOOL p6, BOOL p7) { invoke<Void>(0x20E4FFD9, x, y, z, radius, p4, p5, p6, p7); } // 0x20E4FFD9
	static void CLEAR_AREA_OF_VEHICLES(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0x63320F3C, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x63320F3C
	static void CLEAR_ANGLED_AREA_OF_VEHICLES(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { invoke<Void>(0xF11A3018, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0xF11A3018
	static void CLEAR_AREA_OF_OBJECTS(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xBB720FE7, p0, p1, p2, p3, p4); } // 0xBB720FE7
	static void CLEAR_AREA_OF_PEDS(float* XCoord, float* YCoord, float* zCoord, float Area, Any p4) { invoke<Void>(0x25BE7FA8, XCoord, YCoord, zCoord, Area, p4); } // 0x25BE7FA8
	static void CLEAR_AREA_OF_COPS(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x95C53824, p0, p1, p2, p3, p4); } // 0x95C53824
	static void CLEAR_AREA_OF_PROJECTILES(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x18DB5434, p0, p1, p2, p3, p4); } // 0x18DB5434
	static void SET_SAVE_MENU_ACTIVE(Any p0) { invoke<Void>(0xF5CCF164, p0); } // 0xF5CCF164
	static Any _0x39771F21() { return invoke<Any>(0x39771F21); } // 0x39771F21
	static void SET_CREDITS_ACTIVE(Any p0) { invoke<Void>(0xEC2A0ECF, p0); } // 0xEC2A0ECF
	static void _0x75B06B5A(Any p0) { invoke<Void>(0x75B06B5A, p0); } // 0x75B06B5A
	static Any _0x2569C9A7() { return invoke<Any>(0x2569C9A7); } // 0x2569C9A7
	static void TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(char* ScriptName) { invoke<Void>(0x9F861FD4, ScriptName); } // 0x9F861FD4
	static void NETWORK_SET_SCRIPT_IS_SAFE_FOR_NETWORK_GAME() { invoke<Void>(0x878486CE); } // 0x878486CE
	static Any ADD_HOSPITAL_RESTART(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x4F3E3104, p0, p1, p2, p3, p4); } // 0x4F3E3104
	static void DISABLE_HOSPITAL_RESTART(Any p0, Any p1) { invoke<Void>(0x09F49C72, p0, p1); } // 0x09F49C72
	static Any ADD_POLICE_RESTART(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xE96C29FE, p0, p1, p2, p3, p4); } // 0xE96C29FE
	static void DISABLE_POLICE_RESTART(Any p0, Any p1) { invoke<Void>(0x0A280324, p0, p1); } // 0x0A280324
	static void _0x296574AE(Any p0) { invoke<Void>(0x296574AE, p0); } // 0x296574AE
	static void IGNORE_NEXT_RESTART(Any p0) { invoke<Void>(0xDA13A4B6, p0); } // 0xDA13A4B6
	static void _0xC9F6F0BC(Any p0) { invoke<Void>(0xC9F6F0BC, p0); } // 0xC9F6F0BC
	static void _0xCB074B9D(Any p0) { invoke<Void>(0xCB074B9D, p0); } // 0xCB074B9D
	static void SET_FADE_IN_AFTER_DEATH_ARREST(Any p0) { invoke<Void>(0xACDE6985, p0); } // 0xACDE6985
	static void SET_FADE_IN_AFTER_LOAD(Any p0) { invoke<Void>(0x6E00EB0B, p0); } // 0x6E00EB0B
	static Any REGISTER_SAVE_HOUSE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0x39C1849A, p0, p1, p2, p3, p4, p5, p6); } // 0x39C1849A
	static void SET_SAVE_HOUSE(Any p0, Any p1, Any p2) { invoke<Void>(0xC3240BB4, p0, p1, p2); } // 0xC3240BB4
	static Any OVERRIDE_SAVE_HOUSE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<Any>(0x47436C12, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x47436C12
	static Any _0xC4D71AB4(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xC4D71AB4, p0, p1, p2, p3); } // 0xC4D71AB4
	static void DO_AUTO_SAVE() { invoke<Void>(0x54C44B1A); } // 0x54C44B1A
	static Any _0xA8546914() { return invoke<Any>(0xA8546914); } // 0xA8546914
	static BOOL IS_AUTO_SAVE_IN_PROGRESS() { return invoke<BOOL>(0x36F75399); } // 0x36F75399
	static Any _0x78350773() { return invoke<Any>(0x78350773); } // 0x78350773
	static void _0x5A45B11A() { invoke<Void>(0x5A45B11A); } // 0x5A45B11A
	static void BEGIN_REPLAY_STATS(Any p0, Any p1) { invoke<Void>(0x17F4F44D, p0, p1); } // 0x17F4F44D
	static void _0x81216EE0(Any p0) { invoke<Void>(0x81216EE0, p0); } // 0x81216EE0
	static void END_REPLAY_STATS() { invoke<Void>(0xCB570185); } // 0xCB570185
	static Any _0xC58250F1() { return invoke<Any>(0xC58250F1); } // 0xC58250F1
	static Any _0x50C39926() { return invoke<Any>(0x50C39926); } // 0x50C39926
	static Any _0x710E5D1E() { return invoke<Any>(0x710E5D1E); } // 0x710E5D1E
	static Any _0xC7BD1AF0() { return invoke<Any>(0xC7BD1AF0); } // 0xC7BD1AF0
	static Any _0x22BE2423(Any p0) { return invoke<Any>(0x22BE2423, p0); } // 0x22BE2423
	static void CLEAR_REPLAY_STATS() { invoke<Void>(0xC47DFF02); } // 0xC47DFF02
	static Any _0xF62B3C48() { return invoke<Any>(0xF62B3C48); } // 0xF62B3C48
	static Any _0x3589452B() { return invoke<Any>(0x3589452B); } // 0x3589452B
	static Any _0x144AAF22() { return invoke<Any>(0x144AAF22); } // 0x144AAF22
	static BOOL IS_MEMORY_CARD_IN_USE() { return invoke<BOOL>(0x40CE4DFD); } // 0x40CE4DFD
	static void SHOOT_SINGLE_BULLET_BETWEEN_COORDS(float* StartPositionX, float* StartPositionY, float* StartPositionZ, float* HitPositionX, float* HitPositionY, float* HitPositionZ, Any p6, Any p7, Hash WeaponHash, Ped PedHandle, Any p10, Any p11, float Speed) { invoke<Void>(0xCB7415AC, StartPositionX, StartPositionY, StartPositionZ, HitPositionX, HitPositionY, HitPositionZ, p6, p7, WeaponHash, PedHandle, p10, p11, Speed); } // 0xCB7415AC
	static void _0x52ACCB7B(float x1, float y1, float z1, float x2, float y2, float z2, int damage, BOOL p7, Hash weaponHash, Ped ownerPed, BOOL isNotAudible, BOOL isInVisible, float speed, Entity entity) { invoke<Void>(0x52ACCB7B, x1, y1, z1, x2, y2, z2, damage, p7, weaponHash, ownerPed, isNotAudible, isInVisible, speed, entity); } // 0x52ACCB7B
	static void GET_MODEL_DIMENSIONS(Entity Entity, float* Minimum, float* Maximum) { invoke<Void>(0x91ABB8E0, Entity, Minimum, Maximum); } // 0x91ABB8E0
	static void SET_FAKE_WANTED_LEVEL(Any p0) { invoke<Void>(0x85B1C9FA, p0); } // 0x85B1C9FA
	static Any _0x0022A430() { return invoke<Any>(0x0022A430); } // 0x0022A430
	static BOOL IS_BIT_SET(int var, int bit) { return invoke<BOOL>(0x902E26AC, var, bit); } // 0x902E26AC
	static void USING_MISSION_CREATOR(Any p0) { invoke<Void>(0x20AB0B6B, p0); } // 0x20AB0B6B
	static void _0x082BA6F2(Any p0) { invoke<Void>(0x082BA6F2, p0); } // 0x082BA6F2
	static void SET_MINIGAME_IN_PROGRESS(Any p0) { invoke<Void>(0x348B9046, p0); } // 0x348B9046
	static BOOL IS_MINIGAME_IN_PROGRESS() { return invoke<BOOL>(0x53A95E13); } // 0x53A95E13
	static BOOL IS_THIS_A_MINIGAME_SCRIPT() { return invoke<BOOL>(0x7605EF6F); } // 0x7605EF6F
	static BOOL IS_SNIPER_INVERTED() { return invoke<BOOL>(0x5C3BF51B); } // 0x5C3BF51B
	static Any GET_CURRENT_LANGUAGE() { return invoke<Any>(0x761BE00B); } // 0x761BE00B
	static Any _0xBAF17315() { return invoke<Any>(0xBAF17315); } // 0xBAF17315
	static Any GET_PROFILE_SETTING(int p0) { return invoke<Any>(0xD374BEBC, p0); } // 0xD374BEBC
	static BOOL ARE_STRINGS_EQUAL(char* string1, char* string2) { return invoke<BOOL>(0x877C0BC5, string1, string2); } // 0x877C0BC5
	static Any COMPARE_STRINGS(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xFE25A58F, p0, p1, p2, p3); } // 0xFE25A58F
	static Any ABSI(Any p0) { return invoke<Any>(0xB44677C5, p0); } // 0xB44677C5
	static float ABSF(float p0) { return invoke<float>(0xAF6F6E0B, p0); } // 0xAF6F6E0B
	static BOOL IS_SNIPER_BULLET_IN_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<BOOL>(0x0483715C, p0, p1, p2, p3, p4, p5); } // 0x0483715C
	static BOOL IS_PROJECTILE_IN_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<BOOL>(0x78E1A557, p0, p1, p2, p3, p4, p5, p6); } // 0x78E1A557
	static BOOL IS_PROJECTILE_TYPE_IN_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<BOOL>(0x2B73BCF6, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x2B73BCF6
	static BOOL IS_PROJECTILE_TYPE_IN_ANGLED_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<BOOL>(0xD1AE2681, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xD1AE2681
	static Any _0xBE81F1E2(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0xBE81F1E2, p0, p1, p2, p3, p4, p5); } // 0xBE81F1E2
	static Any _0x1A40454B(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<Any>(0x1A40454B, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x1A40454B
	static Any _0x6BDE5CE4(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x6BDE5CE4, p0, p1, p2, p3, p4); } // 0x6BDE5CE4
	static BOOL _GET_PROJECTILE_NEAR_PED(Ped ped, Hash projHash, float radius, Vector3 *projPos, Entity *projEnt, BOOL ownedByPlayer) { return invoke<Any>(0x507BC6F7, ped, projHash, radius, projPos, projEnt, ownedByPlayer); } // 0x507BC6F7
	static BOOL IS_BULLET_IN_ANGLED_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<BOOL>(0xE2DB58F7, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xE2DB58F7
	static BOOL IS_BULLET_IN_AREA(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<BOOL>(0xB54F46CA, p0, p1, p2, p3, p4); } // 0xB54F46CA
	static BOOL IS_BULLET_IN_BOX(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<BOOL>(0xAB73ED26, p0, p1, p2, p3, p4, p5, p6); } // 0xAB73ED26
	static BOOL HAS_BULLET_IMPACTED_IN_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<BOOL>(0x902BC7D9, p0, p1, p2, p3, p4, p5); } // 0x902BC7D9
	static BOOL HAS_BULLET_IMPACTED_IN_BOX(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<BOOL>(0x2C2618CC, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x2C2618CC
	static BOOL IS_ORBIS_VERSION() { return invoke<BOOL>(0x40282018); } // 0x40282018
	static BOOL IS_DURANGO_VERSION() { return invoke<BOOL>(0x46FB06A5); } // 0x46FB06A5
	static BOOL IS_XBOX360_VERSION() { return invoke<BOOL>(0x24005CC8); } // 0x24005CC8
	static BOOL IS_PS3_VERSION() { return invoke<BOOL>(0x4C0D5303); } // 0x4C0D5303
	static BOOL IS_PC_VERSION() { return invoke<BOOL>(0x4D5D9EE3); } // 0x4D5D9EE3
	static BOOL IS_AUSSIE_VERSION() { return invoke<BOOL>(0x944BA1DC); } // 0x944BA1DC
	static BOOL IS_STRING_NULL(Any p0) { return invoke<BOOL>(0x8E71E00F, p0); } // 0x8E71E00F
	static BOOL IS_STRING_NULL_OR_EMPTY(char *string) { return invoke<BOOL>(0x42E9F2CA, string); } // 0x42E9F2CA
	static BOOL STRING_TO_INT(char* string, int* ToStore) { return invoke<BOOL>(0x590A8160, string, ToStore); } // 0x590A8160
	static void SET_BITS_IN_RANGE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x32094719, p0, p1, p2, p3); } // 0x32094719
	static Any GET_BITS_IN_RANGE(Any p0, Any p1, Any p2) { return invoke<Any>(0xCA03A1E5, p0, p1, p2); } // 0xCA03A1E5
	static Any ADD_STUNT_JUMP(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14, Any p15, Any p16) { return invoke<Any>(0xB630E5FF, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16); } // 0xB630E5FF
	static Any ADD_STUNT_JUMP_ANGLED(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14, Any p15, Any p16, Any p17, Any p18) { return invoke<Any>(0xB9B7E777, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18); } // 0xB9B7E777
	static void DELETE_STUNT_JUMP(Any p0) { invoke<Void>(0x840CB5DA, p0); } // 0x840CB5DA
	static void ENABLE_STUNT_JUMP_SET(Any p0) { invoke<Void>(0x9D1E7785, p0); } // 0x9D1E7785
	static void DISABLE_STUNT_JUMP_SET(Any p0) { invoke<Void>(0x644C9FA4, p0); } // 0x644C9FA4
	static void _0x3C806A2D(Any p0) { invoke<Void>(0x3C806A2D, p0); } // 0x3C806A2D
	static BOOL IS_STUNT_JUMP_IN_PROGRESS() { return invoke<BOOL>(0xF477D0B1); } // 0xF477D0B1
	static Any _0x021636EE() { return invoke<Any>(0x021636EE); } // 0x021636EE
	static Any _0x006F9BA2() { return invoke<Any>(0x006F9BA2); } // 0x006F9BA2
	static void CANCEL_STUNT_JUMP() { invoke<Void>(0xF43D9821); } // 0xF43D9821
	static void SET_GAME_PAUSED(BOOL Paused) { invoke<Void>(0x8230FF6C, Paused); } // 0x8230FF6C
	static void SET_THIS_SCRIPT_CAN_BE_PAUSED(Any p0) { invoke<Void>(0xA0C3CE29, p0); } // 0xA0C3CE29
	static void SET_THIS_SCRIPT_CAN_REMOVE_BLIPS_CREATED_BY_ANY_SCRIPT(Any p0) { invoke<Void>(0xD06F1720, p0); } // 0xD06F1720
	static Any _0xFF6191E1(Any p0, Any p1) { return invoke<Any>(0xFF6191E1, p0, p1); } // 0xFF6191E1
	static void _0x721B2492(Any p0) { invoke<Void>(0x721B2492, p0); } // 0x721B2492
	static void _0xE202879D(Any p0) { invoke<Void>(0xE202879D, p0); } // 0xE202879D
	static BOOL IS_FRONTEND_FADING() { return invoke<BOOL>(0x8FF6232C); } // 0x8FF6232C
	static void POPULATE_NOW() { invoke<Void>(0x72C20700); } // 0x72C20700
	static Any GET_INDEX_OF_CURRENT_LEVEL() { return invoke<Any>(0x6F203C6E); } // 0x6F203C6E
	static void SET_GRAVITY_LEVEL(Any p0) { invoke<Void>(0x2D833F4A, p0); } // 0x2D833F4A
	static void START_SAVE_DATA(Any p0, Any p1, Any p2) { invoke<Void>(0x881A694D, p0, p1, p2); } // 0x881A694D
	static void STOP_SAVE_DATA() { invoke<Void>(0x3B1C07C8); } // 0x3B1C07C8
	static Any _0x9EF0BC64(Any p0) { return invoke<Any>(0x9EF0BC64, p0); } // 0x9EF0BC64
	static void REGISTER_INT_TO_SAVE(Any p0, Any p1) { invoke<Void>(0xB930956F, p0, p1); } // 0xB930956F
	static void _0x9B38374A(Any p0, Any p1) { invoke<Void>(0x9B38374A, p0, p1); } // 0x9B38374A
	static void REGISTER_FLOAT_TO_SAVE(Any p0, Any p1) { invoke<Void>(0xDB06F7AD, p0, p1); } // 0xDB06F7AD
	static void REGISTER_BOOL_TO_SAVE(Any p0, Any p1) { invoke<Void>(0x5417E0E0, p0, p1); } // 0x5417E0E0
	static void REGISTER_TEXT_LABEL_TO_SAVE(Any p0, Any p1) { invoke<Void>(0x284352C4, p0, p1); } // 0x284352C4
	static void _0xE2089749(Any p0, Any p1) { invoke<Void>(0xE2089749, p0, p1); } // 0xE2089749
	static void _0xF91B8C33(Any p0, Any p1) { invoke<Void>(0xF91B8C33, p0, p1); } // 0xF91B8C33
	static void _0x74E8FAD9(Any p0, Any p1) { invoke<Void>(0x74E8FAD9, p0, p1); } // 0x74E8FAD9
	static void _0x6B4335DD(Any p0, Any p1) { invoke<Void>(0x6B4335DD, p0, p1); } // 0x6B4335DD
	static void _0xFB45728E(Any p0, Any p1, Any p2) { invoke<Void>(0xFB45728E, p0, p1, p2); } // 0xFB45728E
	static void STOP_SAVE_STRUCT() { invoke<Void>(0xC2624A28); } // 0xC2624A28
	static void _0x893A342C(Any p0, Any p1, Any p2) { invoke<Void>(0x893A342C, p0, p1, p2); } // 0x893A342C
	static void STOP_SAVE_ARRAY() { invoke<Void>(0x0CAD8217); } // 0x0CAD8217
	static void _0x0B710A51(Any p0, Any p1) { invoke<Void>(0x0B710A51, p0, p1); } // 0x0B710A51
	static void _0xE0F0684F(Any p0, Any p1) { invoke<Void>(0xE0F0684F, p0, p1); } // 0xE0F0684F
	static Any _0x3CE5BF6B(Any p0) { return invoke<Any>(0x3CE5BF6B, p0); } // 0x3CE5BF6B
	static Any CREATE_INCIDENT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0xFC5FF7B3, p0, p1, p2, p3, p4, p5, p6); } // 0xFC5FF7B3
	static Any CREATE_INCIDENT_WITH_ENTITY(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xBBC35B03, p0, p1, p2, p3, p4); } // 0xBBC35B03
	static void DELETE_INCIDENT(Any p0) { invoke<Void>(0x212BD0DC, p0); } // 0x212BD0DC
	static BOOL IS_INCIDENT_VALID(Any p0) { return invoke<BOOL>(0x31FD0BA4, p0); } // 0x31FD0BA4
	static void _0x0242D88E(Any p0, Any p1, Any p2) { invoke<Void>(0x0242D88E, p0, p1, p2); } // 0x0242D88E
	static void _0x1F38102E(Any p0, Any p1) { invoke<Void>(0x1F38102E, p0, p1); } // 0x1F38102E
	static Any FIND_SPAWN_POINT_IN_DIRECTION(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<Any>(0x71AEFD77, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x71AEFD77
	static Any _0x42BF09B3(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<Any>(0x42BF09B3, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x42BF09B3
	static void _0xFBDBE374(Any p0, Any p1) { invoke<Void>(0xFBDBE374, p0, p1); } // 0xFBDBE374
	static void ENABLE_TENNIS_MODE(Any p0, Any p1, Any p2) { invoke<Void>(0x0BD3F9EC, p0, p1, p2); } // 0x0BD3F9EC
	static BOOL IS_TENNIS_MODE(Any p0) { return invoke<BOOL>(0x04A947BA, p0); } // 0x04A947BA
	static void _0xC20A7D2B(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xC20A7D2B, p0, p1, p2, p3, p4, p5); } // 0xC20A7D2B
	static Any _0x8501E727(Any p0) { return invoke<Any>(0x8501E727, p0); } // 0x8501E727
	static Any _0x1A332D2D(Any p0) { return invoke<Any>(0x1A332D2D, p0); } // 0x1A332D2D
	static void _0x0C8865DF(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x0C8865DF, p0, p1, p2, p3, p4, p5); } // 0x0C8865DF
	static void _0x49F977A9(Any p0, Any p1, Any p2) { invoke<Void>(0x49F977A9, p0, p1, p2); } // 0x49F977A9
	static void _0x6F009E33(Any p0, Any p1, Any p2) { invoke<Void>(0x6F009E33, p0, p1, p2); } // 0x6F009E33
	static void RESET_DISPATCH_IDEAL_SPAWN_DISTANCE() { invoke<Void>(0xDA65ECAA); } // 0xDA65ECAA
	static void SET_DISPATCH_IDEAL_SPAWN_DISTANCE(Any p0) { invoke<Void>(0x6283BE32, p0); } // 0x6283BE32
	static void RESET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS(Any p0) { invoke<Void>(0x1479E85A, p0); } // 0x1479E85A
	static void SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS(Any p0, Any p1) { invoke<Void>(0xABADB709, p0, p1); } // 0xABADB709
	static void SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS_MULTIPLIER(Any p0, Any p1) { invoke<Void>(0x1C996BCD, p0, p1); } // 0x1C996BCD
	static Any _0xF557BAF9(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0xF557BAF9, p0, p1, p2, p3, p4, p5, p6); } // 0xF557BAF9
	static void REMOVE_DISPATCH_SPAWN_BLOCKING_AREA(Any p0) { invoke<Void>(0xA8D2FB92, p0); } // 0xA8D2FB92
	static void RESET_DISPATCH_SPAWN_BLOCKING_AREAS() { invoke<Void>(0x9A17F835); } // 0x9A17F835
	static void _0xE0C9307E() { invoke<Void>(0xE0C9307E); } // 0xE0C9307E
	static void _0xA0D8C749(Any p0, Any p1) { invoke<Void>(0xA0D8C749, p0, p1); } // 0xA0D8C749
	static void _0x24A4E0B2(Any p0, Any p1, Any p2) { invoke<Void>(0x24A4E0B2, p0, p1, p2); } // 0x24A4E0B2
	static void _0x66C3C59C() { invoke<Void>(0x66C3C59C); } // 0x66C3C59C
	static void _0xD9660339(Any p0) { invoke<Void>(0xD9660339, p0); } // 0xD9660339
	static void _0xD2688412(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { invoke<Void>(0xD2688412, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0xD2688412
	static void DISPLAY_ONSCREEN_KEYBOARD(BOOL p0, char* windowTitle, char* p2, char* defaultText, char* defaultConcat1, char* defaultConcat2, char* defaultConcat3, int maxInputLength) { invoke<Void>(0xAD99F2CE, p0, windowTitle, p2, defaultText, defaultConcat1, defaultConcat2, defaultConcat3, maxInputLength); } // 0xAD99F2CE
	static int UPDATE_ONSCREEN_KEYBOARD() { return invoke<int>(0x23D0A1CE); } // 0x23D0A1CE
	static char* GET_ONSCREEN_KEYBOARD_RESULT() { return invoke<char*>(0x44828FB3); } // 0x44828FB3
	static void _0x3301EA47(Any p0) { invoke<Void>(0x3301EA47, p0); } // 0x3301EA47
	static void _0x42B484ED(Any p0, Any p1) { invoke<Void>(0x42B484ED, p0, p1); } // 0x42B484ED
	static void _0x8F60366E(Any p0, Any p1) { invoke<Void>(0x8F60366E, p0, p1); } // 0x8F60366E
	static void SET_EXPLOSIVE_AMMO_THIS_FRAME(Player player) { invoke<Void>(0x2EAFA1D1, player); } // 0x2EAFA1D1
	static void SET_FIRE_AMMO_THIS_FRAME(Player player) { invoke<Void>(0x7C18FC8A, player); } // 0x7C18FC8A
	static void SET_EXPLOSIVE_MELEE_THIS_FRAME(Player player) { invoke<Void>(0x96663D56, player); } // 0x96663D56
	static void SET_SUPER_JUMP_THIS_FRAME(Player player) { invoke<Void>(0x86745EF3, player); } // 0x86745EF3
	static Any _0xC3C10FCC() { return invoke<Any>(0xC3C10FCC); } // 0xC3C10FCC
	static void _0x054EC103() { invoke<Void>(0x054EC103); } // 0x054EC103
	static Any _0x46B5A15C() { return invoke<Any>(0x46B5A15C); } // 0x46B5A15C
	static void _0x5D209F25() { invoke<Void>(0x5D209F25); } // 0x5D209F25
	static void _0x2D33F15A(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x2D33F15A, p0, p1, p2, p3); } // 0x2D33F15A
	static void _0xDF99925C() { invoke<Void>(0xDF99925C); } // 0xDF99925C
	static void _0xA27F4472(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xA27F4472, p0, p1, p2, p3); } // 0xA27F4472
	static Any _0x07FF553F(Any p0, Any p1, Any p2) { return invoke<Any>(0x07FF553F, p0, p1, p2); } // 0x07FF553F
}

namespace AUDIO
{
	static void PLAY_PED_RINGTONE(Any p0, Any p1, Any p2) { invoke<Void>(0x1D530E47, p0, p1, p2); } // 0x1D530E47
	static BOOL IS_PED_RINGTONE_PLAYING(Any p0) { return invoke<BOOL>(0xFE576EE4, p0); } // 0xFE576EE4
	static void STOP_PED_RINGTONE(Any p0) { invoke<Void>(0xFEEA107C, p0); } // 0xFEEA107C
	static BOOL IS_MOBILE_PHONE_CALL_ONGOING() { return invoke<BOOL>(0x4ED1400A); } // 0x4ED1400A
	static Any _0x16FB88B5() { return invoke<Any>(0x16FB88B5); } // 0x16FB88B5
	static void CREATE_NEW_SCRIPTED_CONVERSATION() { invoke<Void>(0xB2BC25F8); } // 0xB2BC25F8
	static void ADD_LINE_TO_CONVERSATION(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { invoke<Void>(0x96CD0513, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0x96CD0513
	static void ADD_PED_TO_CONVERSATION(Any p0, Any p1, Any p2) { invoke<Void>(0xF8D5EB86, p0, p1, p2); } // 0xF8D5EB86
	static void _0x73C6F979(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x73C6F979, p0, p1, p2, p3); } // 0x73C6F979
	static void _0x88203DDA(Any p0, Any p1) { invoke<Void>(0x88203DDA, p0, p1); } // 0x88203DDA
	static void SET_MICROPHONE_POSITION(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0xAD7BB191, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xAD7BB191
	static void _0x1193ED6E(Any p0) { invoke<Void>(0x1193ED6E, p0); } // 0x1193ED6E
	static void START_SCRIPT_PHONE_CONVERSATION(Any p0, Any p1) { invoke<Void>(0x38E42D07, p0, p1); } // 0x38E42D07
	static void PRELOAD_SCRIPT_PHONE_CONVERSATION(Any p0, Any p1) { invoke<Void>(0x9ACB213A, p0, p1); } // 0x9ACB213A
	static void START_SCRIPT_CONVERSATION(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xE5DE7D9D, p0, p1, p2, p3); } // 0xE5DE7D9D
	static void PRELOAD_SCRIPT_CONVERSATION(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xDDF5C579, p0, p1, p2, p3); } // 0xDDF5C579
	static void START_PRELOADED_CONVERSATION() { invoke<Void>(0xA170261B); } // 0xA170261B
	static Any _0x336F3D35() { return invoke<Any>(0x336F3D35); } // 0x336F3D35
	static BOOL IS_SCRIPTED_CONVERSATION_ONGOING() { return invoke<BOOL>(0xCB8FD96F); } // 0xCB8FD96F
	static BOOL IS_SCRIPTED_CONVERSATION_LOADED() { return invoke<BOOL>(0xE1870EA9); } // 0xE1870EA9
	static Any GET_CURRENT_SCRIPTED_CONVERSATION_LINE() { return invoke<Any>(0x9620E41F); } // 0x9620E41F
	static void PAUSE_SCRIPTED_CONVERSATION(Any p0) { invoke<Void>(0xE2C9C6F8, p0); } // 0xE2C9C6F8
	static void RESTART_SCRIPTED_CONVERSATION() { invoke<Void>(0x6CB24B56); } // 0x6CB24B56
	static Any STOP_SCRIPTED_CONVERSATION(Any p0) { return invoke<Any>(0xAB77DA7D, p0); } // 0xAB77DA7D
	static void SKIP_TO_NEXT_SCRIPTED_CONVERSATION_LINE() { invoke<Void>(0x85C98304); } // 0x85C98304
	static void INTERRUPT_CONVERSATION(Any p0, Any p1, Any p2) { invoke<Void>(0xF3A67AF3, p0, p1, p2); } // 0xF3A67AF3
	static Any _0xB58B8FF3(Any p0) { return invoke<Any>(0xB58B8FF3, p0); } // 0xB58B8FF3
	static void _0x789D8C6C(Any p0) { invoke<Void>(0x789D8C6C, p0); } // 0x789D8C6C
	static void REGISTER_SCRIPT_WITH_AUDIO(Any p0) { invoke<Void>(0xA6203643, p0); } // 0xA6203643
	static void UNREGISTER_SCRIPT_WITH_AUDIO() { invoke<Void>(0x66728EFE); } // 0x66728EFE
	static Any REQUEST_MISSION_AUDIO_BANK(Any p0, Any p1) { return invoke<Any>(0x916E37CA, p0, p1); } // 0x916E37CA
	static Any REQUEST_AMBIENT_AUDIO_BANK(Any p0, Any p1) { return invoke<Any>(0x23C88BC7, p0, p1); } // 0x23C88BC7
	static Any REQUEST_SCRIPT_AUDIO_BANK(Any p0, Any p1) { return invoke<Any>(0x21322887, p0, p1); } // 0x21322887
	static Any HINT_AMBIENT_AUDIO_BANK(Any p0, Any p1) { return invoke<Any>(0xF1850DDC, p0, p1); } // 0xF1850DDC
	static Any HINT_SCRIPT_AUDIO_BANK(Any p0, Any p1) { return invoke<Any>(0x41FA0E51, p0, p1); } // 0x41FA0E51
	static void RELEASE_MISSION_AUDIO_BANK() { invoke<Void>(0x8E8824C7); } // 0x8E8824C7
	static void RELEASE_AMBIENT_AUDIO_BANK() { invoke<Void>(0x8C938784); } // 0x8C938784
	static void RELEASE_NAMED_SCRIPT_AUDIO_BANK(Any p0) { invoke<Void>(0x16707ABC, p0); } // 0x16707ABC
	static void RELEASE_SCRIPT_AUDIO_BANK() { invoke<Void>(0x22F865E5); } // 0x22F865E5
	static void _0xA58BBF4F() { invoke<Void>(0xA58BBF4F); } // 0xA58BBF4F
	static Any GET_SOUND_ID() { return invoke<Any>(0x6AE0AD56); } // 0x6AE0AD56
	static void RELEASE_SOUND_ID(Any p0) { invoke<Void>(0x9C080899, p0); } // 0x9C080899
	static void PLAY_SOUND(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xB6E1917F, p0, p1, p2, p3, p4); } // 0xB6E1917F
	static void PLAY_SOUND_FRONTEND(int p0, char* SoundFrom, char* SoundSet) { invoke<Void>(0x2E458F74, p0, SoundFrom, SoundSet); } // 0x2E458F74
	static void _0xC70E6CFA(Any p0, Any p1) { invoke<Void>(0xC70E6CFA, p0, p1); } // 0xC70E6CFA
	static void PLAY_SOUND_FROM_ENTITY(int p0, char* p1, Entity entity, char* p3, Any p4, Any p5) { invoke<Void>(0x95AE00F8, p0, p1, entity, p3, p4, p5); } // 0x95AE00F8
	static void PLAY_SOUND_FROM_COORD(Any p0, char *p1, float p2, float p3, float p4, char *p5, Any p6, Any p7, Any p8) { invoke<Void>(0xCAD3E2D5, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xCAD3E2D5
	static void STOP_SOUND(Any p0) { invoke<Void>(0xCD7F4030, p0); } // 0xCD7F4030
	static Any GET_NETWORK_ID_FROM_SOUND_ID(Any p0) { return invoke<Any>(0x2576F610, p0); } // 0x2576F610
	static Any _0xD064D4DC(Any p0) { return invoke<Any>(0xD064D4DC, p0); } // 0xD064D4DC
	static void SET_VARIABLE_ON_SOUND(Any p0, Any p1, Any p2) { invoke<Void>(0x606EE5FA, p0, p1, p2); } // 0x606EE5FA
	static void SET_VARIABLE_ON_STREAM(Any p0, Any p1) { invoke<Void>(0xF67BB44C, p0, p1); } // 0xF67BB44C
	static void OVERRIDE_UNDERWATER_STREAM(Any p0, Any p1) { invoke<Void>(0x9A083B7E, p0, p1); } // 0x9A083B7E
	static void _0x62D026BE(Any p0, Any p1) { invoke<Void>(0x62D026BE, p0, p1); } // 0x62D026BE
	static BOOL HAS_SOUND_FINISHED(Any p0) { return invoke<BOOL>(0xE85AEC2E, p0); } // 0xE85AEC2E
	static void _PLAY_AMBIENT_SPEECH1(Ped pedHandle, char* speechName, char* speechParam) { invoke<Void>(0x5C57B85D, pedHandle, speechName, speechParam); } // 0x5C57B85D
	static void _PLAY_AMBIENT_SPEECH2(Ped pedHandle, char* speechName, char* speechParam) { invoke<Void>(0x444180DB, pedHandle, speechName, speechParam); } // 0x444180DB
	static void _0x8386AE28(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x8386AE28, p0, p1, p2, p3, p4); } // 0x8386AE28
	static void _0xA1A1402E(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xA1A1402E, p0, p1, p2, p3, p4, p5); } // 0xA1A1402E
	static void OVERRIDE_TREVOR_RAGE(Any p0) { invoke<Void>(0x05B9B5CF, p0); } // 0x05B9B5CF
	static void RESET_TREVOR_RAGE() { invoke<Void>(0xE80CF0D4); } // 0xE80CF0D4
	static void SET_PLAYER_ANGRY(Any p0, Any p1) { invoke<Void>(0x782CA58D, p0, p1); } // 0x782CA58D
	static void PLAY_PAIN(Any p0, Any p1, Any p2) { invoke<Void>(0x874BD6CB, p0, p1, p2); } // 0x874BD6CB
	static void RELEASE_WEAPON_AUDIO() { invoke<Void>(0x6096504C); } // 0x6096504C
	static void _0x59A3A17D(Any p0) { invoke<Void>(0x59A3A17D, p0); } // 0x59A3A17D
	static void _0x0E387BFE(Any p0) { invoke<Void>(0x0E387BFE, p0); } // 0x0E387BFE
	static void SET_AMBIENT_VOICE_NAME(Any p0, char* p1) { invoke<Void>(0xBD2EA1A1, p0, p1); } // 0xBD2EA1A1
	static void STOP_CURRENT_PLAYING_AMBIENT_SPEECH(Any p0) { invoke<Void>(0xBB8E64BF, p0); } // 0xBB8E64BF
	static BOOL IS_AMBIENT_SPEECH_PLAYING(Any p0) { return invoke<BOOL>(0x1972E8AA, p0); } // 0x1972E8AA
	static BOOL IS_SCRIPTED_SPEECH_PLAYING(Any p0) { return invoke<BOOL>(0x2C653904, p0); } // 0x2C653904
	static BOOL IS_ANY_SPEECH_PLAYING(Any p0) { return invoke<BOOL>(0x2B74A6D6, p0); } // 0x2B74A6D6
	static Any _0x8BD5F11E(Any p0, Any p1, Any p2) { return invoke<Any>(0x8BD5F11E, p0, p1, p2); } // 0x8BD5F11E
	static BOOL IS_PED_IN_CURRENT_CONVERSATION(Any p0) { return invoke<BOOL>(0x7B2F0743, p0); } // 0x7B2F0743
	static void SET_PED_IS_DRUNK(Any p0, Any p1) { invoke<Void>(0xD2EA77A3, p0, p1); } // 0xD2EA77A3
	static void _0x498849F3(Any p0, Any p1, Any p2) { invoke<Void>(0x498849F3, p0, p1, p2); } // 0x498849F3
	static Any _0x0CBAF2EF(Any p0) { return invoke<Any>(0x0CBAF2EF, p0); } // 0x0CBAF2EF
	static void SET_ANIMAL_MOOD(Any p0, Any p1) { invoke<Void>(0x3EA7C6CB, p0, p1); } // 0x3EA7C6CB
	static BOOL IS_MOBILE_PHONE_RADIO_ACTIVE() { return invoke<BOOL>(0x6E502A5B); } // 0x6E502A5B
	static void SET_MOBILE_PHONE_RADIO_STATE(Any p0) { invoke<Void>(0xE1E0ED34, p0); } // 0xE1E0ED34
	static Any GET_PLAYER_RADIO_STATION_INDEX() { return invoke<Any>(0x1C4946AC); } // 0x1C4946AC
	static Any GET_PLAYER_RADIO_STATION_NAME() { return invoke<Any>(0xD909C107); } // 0xD909C107
	static Any GET_RADIO_STATION_NAME(int radioStation) { return invoke<Any>(0x3DF493BC, radioStation); } // 0x3DF493BC
	static Any GET_PLAYER_RADIO_STATION_GENRE() { return invoke<Any>(0x872CF0EA); } // 0x872CF0EA
	static BOOL IS_RADIO_RETUNING() { return invoke<BOOL>(0xCF29097B); } // 0xCF29097B
	static void _0x53DB6994() { invoke<Void>(0x53DB6994); } // 0x53DB6994
	static void _0xD70ECC80() { invoke<Void>(0xD70ECC80); } // 0xD70ECC80
	static void SET_RADIO_TO_STATION_NAME(char* radioStation) { invoke<Void>(0x7B36E35E, radioStation); } // 0x7B36E35E
	static void SET_VEH_RADIO_STATION(Object hVehicle, char* radioStation) { invoke<Void>(0xE391F55F, hVehicle, radioStation); } // 0xE391F55F
	static void _0x7ABB89D2(Any p0) { invoke<Void>(0x7ABB89D2, p0); } // 0x7ABB89D2
	static void SET_EMITTER_RADIO_STATION(Any p0, Any p1) { invoke<Void>(0x87431585, p0, p1); } // 0x87431585
	static void SET_STATIC_EMITTER_ENABLED(Any p0, Any p1) { invoke<Void>(0x91F72E92, p0, p1); } // 0x91F72E92
	static void SET_RADIO_TO_STATION_INDEX(Any p0) { invoke<Void>(0x1D82766D, p0); } // 0x1D82766D
	static void SET_FRONTEND_RADIO_ACTIVE(Any p0) { invoke<Void>(0xB1172075, p0); } // 0xB1172075
	static void UNLOCK_MISSION_NEWS_STORY(Any p0) { invoke<Void>(0xCCD9ABE4, p0); } // 0xCCD9ABE4
	static Any GET_NUMBER_OF_PASSENGER_VOICE_VARIATIONS(Any p0) { return invoke<Any>(0x27305D37, p0); } // 0x27305D37
	static Any GET_AUDIBLE_MUSIC_TRACK_TEXT_ID() { return invoke<Any>(0xA2B88CA7); } // 0xA2B88CA7
	static void PLAY_END_CREDITS_MUSIC(Any p0) { invoke<Void>(0x8E88B3CC, p0); } // 0x8E88B3CC
	static void SKIP_RADIO_FORWARD() { invoke<Void>(0x10D36630); } // 0x10D36630
	static void FREEZE_RADIO_STATION(Any p0) { invoke<Void>(0x286BF543, p0); } // 0x286BF543
	static void UNFREEZE_RADIO_STATION(Any p0) { invoke<Void>(0x4D46202C, p0); } // 0x4D46202C
	static void SET_RADIO_AUTO_UNFREEZE(Any p0) { invoke<Void>(0xA40196BF, p0); } // 0xA40196BF
	static void SET_INITIAL_PLAYER_STATION(Any p0) { invoke<Void>(0x9B069233, p0); } // 0x9B069233
	static void SET_USER_RADIO_CONTROL_ENABLED(Any p0) { invoke<Void>(0x52E054CE, p0); } // 0x52E054CE
	static void SET_RADIO_TRACK(Any p0, Any p1) { invoke<Void>(0x76E96212, p0, p1); } // 0x76E96212
	static void SET_VEHICLE_RADIO_LOUD(Any p0, BOOL p1) { invoke<Void>(0x8D9EDD99, p0, p1); } // 0x8D9EDD99
	static Any _0xCBA99F4A(Any p0) { return invoke<Any>(0xCBA99F4A, p0); } // 0xCBA99F4A
	static void SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(BOOL Toggle) { invoke<Void>(0x990085F0, Toggle); } // 0x990085F0
	static Any _0x46B0C696() { return invoke<Any>(0x46B0C696); } // 0x46B0C696
	static Any _0x2A3E5E8B() { return invoke<Any>(0x2A3E5E8B); } // 0x2A3E5E8B
	static void SET_VEHICLE_RADIO_ENABLED(Any p0, Any p1) { invoke<Void>(0x6F812CAB, p0, p1); } // 0x6F812CAB
	static void _0x128C3873(Any p0, Any p1, Any p2) { invoke<Void>(0x128C3873, p0, p1, p2); } // 0x128C3873

	//static void _0x128C3873(char *radioStation, char *p1, BOOL p2) { invoke<Void>(0x128C3873, radioStation, p1, p2); } // 0x128C3873

	static void _0x1D766976(Any p0) { invoke<Void>(0x1D766976, p0); } // 0x1D766976
	static Any _0xCC91FCF5() { return invoke<Any>(0xCC91FCF5); } // 0xCC91FCF5
	static Any FIND_RADIO_STATION_INDEX(Any p0) { return invoke<Any>(0xECA1512F, p0); } // 0xECA1512F
	static void _0xB1FF7137(Any p0, Any p1) { invoke<Void>(0xB1FF7137, p0, p1); } // 0xB1FF7137
	static void _0xC8B514E2(Any p0) { invoke<Void>(0xC8B514E2, p0); } // 0xC8B514E2
	static void _0xBE998184(Any p0, Any p1) { invoke<Void>(0xBE998184, p0, p1); } // 0xBE998184
	static void _0x8AFC488D(Any p0, Any p1) { invoke<Void>(0x8AFC488D, p0, p1); } // 0x8AFC488D
	static void SET_AMBIENT_ZONE_STATE(Any p0, Any p1, Any p2) { invoke<Void>(0x2849CAC9, p0, p1, p2); } // 0x2849CAC9
	static void CLEAR_AMBIENT_ZONE_STATE(Any p0, Any p1) { invoke<Void>(0xCDFF3C82, p0, p1); } // 0xCDFF3C82
	static void SET_AMBIENT_ZONE_LIST_STATE(Any p0, Any p1, Any p2) { invoke<Void>(0xBF80B412, p0, p1, p2); } // 0xBF80B412
	static void CLEAR_AMBIENT_ZONE_LIST_STATE(Any p0, Any p1) { invoke<Void>(0x38B9B8D4, p0, p1); } // 0x38B9B8D4
	static void SET_AMBIENT_ZONE_STATE_PERSISTENT(Any p0, Any p1, Any p2) { invoke<Void>(0xC1FFB672, p0, p1, p2); } // 0xC1FFB672
	static void SET_AMBIENT_ZONE_LIST_STATE_PERSISTENT(Any p0, Any p1, Any p2) { invoke<Void>(0x5F5A2605, p0, p1, p2); } // 0x5F5A2605
	static BOOL IS_AMBIENT_ZONE_ENABLED(Any p0) { return invoke<BOOL>(0xBFABD872, p0); } // 0xBFABD872
	static void SET_CUTSCENE_AUDIO_OVERRIDE(Any p0) { invoke<Void>(0xCE1332B7, p0); } // 0xCE1332B7
	static void GET_PLAYER_HEADSET_SOUND_ALTERNATE(Any p0, Any p1) { invoke<Void>(0xD63CF33A, p0, p1); } // 0xD63CF33A
	static Any PLAY_POLICE_REPORT(char* p0, float p1) { return invoke<Any>(0x3F277B62, p0, p1); } // 0x3F277B62
	static void BLIP_SIREN(Any p0) { invoke<Void>(0xC0EB6924, p0); } // 0xC0EB6924
	static void OVERRIDE_VEH_HORN(Vehicle p0, BOOL p1, int p2) { invoke<Void>(0x2ACAB783, p0, p1, p2); } // 0x2ACAB783
	static BOOL IS_HORN_ACTIVE(Any p0) { return invoke<BOOL>(0x20E2BDD0, p0); } // 0x20E2BDD0
	static void SET_AGGRESSIVE_HORNS(int p0) { invoke<Void>(0x01D6EABE, p0); } // 0x01D6EABE
	static void _0x3C395AEE(Any p0) { invoke<Void>(0x3C395AEE, p0); } // 0x3C395AEE
	static void _0x8CE63FA1(Any p0, Any p1) { invoke<Void>(0x8CE63FA1, p0, p1); } // 0x8CE63FA1
	static BOOL IS_STREAM_PLAYING() { return invoke<BOOL>(0xF1F51A14); } // 0xF1F51A14
	static Any GET_STREAM_PLAY_TIME() { return invoke<Any>(0xB4F0AD56); } // 0xB4F0AD56
	static Any LOAD_STREAM(Any p0, Any p1) { return invoke<Any>(0x0D89599D, p0, p1); } // 0x0D89599D
	static Any LOAD_STREAM_WITH_START_OFFSET(Any p0, Any p1, Any p2) { return invoke<Any>(0xE5B5745C, p0, p1, p2); } // 0xE5B5745C
	static void _0xA1D7FABE(Any p0) { invoke<Void>(0xA1D7FABE, p0); } // 0xA1D7FABE
	static void PLAY_STREAM_FROM_VEHICLE(Any p0) { invoke<Void>(0xF8E4BDA2, p0); } // 0xF8E4BDA2
	static void PLAY_STREAM_FROM_OBJECT(Any p0) { invoke<Void>(0xC5266BF7, p0); } // 0xC5266BF7
	static void PLAY_STREAM_FRONTEND() { invoke<Void>(0x2C2A16BC); } // 0x2C2A16BC
	static void SPECIAL_FRONTEND_EQUAL(Any p0, Any p1, Any p2) { invoke<Void>(0x6FE5D865, p0, p1, p2); } // 0x6FE5D865
	static void STOP_STREAM() { invoke<Void>(0xD1E364DE); } // 0xD1E364DE
	static void STOP_PED_SPEAKING(Any p0, Any p1) { invoke<Void>(0xFF92B49D, p0, p1); } // 0xFF92B49D
	static void DISABLE_PED_PAIN_AUDIO(Any p0, Any p1) { invoke<Void>(0x3B8E2D5F, p0, p1); } // 0x3B8E2D5F
	static BOOL IS_AMBIENT_SPEECH_DISABLED(Any p0) { return invoke<BOOL>(0x109D1F89, p0); } // 0x109D1F89
	static void SET_SIREN_WITH_NO_DRIVER(Any p0, Any p1) { invoke<Void>(0x77182D58, p0, p1); } // 0x77182D58
	static void _0xDE8BA3CD(Any p0) { invoke<Void>(0xDE8BA3CD, p0); } // 0xDE8BA3CD
	static void SET_HORN_ENABLED(Any p0, Any p1) { invoke<Void>(0x6EB92D05, p0, p1); } // 0x6EB92D05
	static void SET_AUDIO_VEHICLE_PRIORITY(Any p0, Any p1) { invoke<Void>(0x271A9766, p0, p1); } // 0x271A9766
	static void _0x2F0A16D1(Any p0, Any p1) { invoke<Void>(0x2F0A16D1, p0, p1); } // 0x2F0A16D1
	static void USE_SIREN_AS_HORN(Any p0, Any p1) { invoke<Void>(0xC6BC16F3, p0, p1); } // 0xC6BC16F3
	static void _0x33B0B007(Any p0, Any p1) { invoke<Void>(0x33B0B007, p0, p1); } // 0x33B0B007
	static void _0x1C0C5E4C(Any p0, Any p1, Any p2) { invoke<Void>(0x1C0C5E4C, p0, p1, p2); } // 0x1C0C5E4C
	static Any _0x6E660D3F(Any p0) { return invoke<Any>(0x6E660D3F, p0); } // 0x6E660D3F
	static void _0x23BE6432(Any p0, Any p1) { invoke<Void>(0x23BE6432, p0, p1); } // 0x23BE6432
	static void _0xE81FAC68(Any p0, Any p1) { invoke<Void>(0xE81FAC68, p0, p1); } // 0xE81FAC68
	static void _0x9365E042(Any p0, Any p1) { invoke<Void>(0x9365E042, p0, p1); } // 0x9365E042
	static void _0x2A60A90E(Any p0, Any p1) { invoke<Void>(0x2A60A90E, p0, p1); } // 0x2A60A90E
	static void SET_VEHICLE_BOOST_ACTIVE(Vehicle vehicle, BOOL Toggle) { invoke<Void>(0x072F15F2, vehicle, Toggle); } // 0x072F15F2
	static void _0x934BE749(Any p0, Any p1) { invoke<Void>(0x934BE749, p0, p1); } // 0x934BE749
	static void _0xE61110A2(Any p0, Any p1) { invoke<Void>(0xE61110A2, p0, p1); } // 0xE61110A2
	static void PLAY_VEHICLE_DOOR_OPEN_SOUND(Any p0, Any p1) { invoke<Void>(0x84930330, p0, p1); } // 0x84930330
	static void PLAY_VEHICLE_DOOR_CLOSE_SOUND(Any p0, Any p1) { invoke<Void>(0xBA2CF407, p0, p1); } // 0xBA2CF407
	static void _0x563B635D(Any p0, Any p1) { invoke<Void>(0x563B635D, p0, p1); } // 0x563B635D
	static BOOL IS_GAME_IN_CONTROL_OF_MUSIC() { return invoke<BOOL>(0x7643170D); } // 0x7643170D
	static void SET_GPS_ACTIVE(Any p0) { invoke<Void>(0x0FC3379A, p0); } // 0x0FC3379A
	static void PLAY_MISSION_COMPLETE_AUDIO(char* p0) { invoke<Void>(0x3033EA1D, p0); } // 0x3033EA1D
	static BOOL IS_MISSION_COMPLETE_PLAYING() { return invoke<BOOL>(0x939982A1); } // 0x939982A1
	static Any _0xCBE09AEC() { return invoke<Any>(0xCBE09AEC); } // 0xCBE09AEC
	static void _0xD2858D8A(Any p0) { invoke<Void>(0xD2858D8A, p0); } // 0xD2858D8A
	static Any START_AUDIO_SCENE(Any p0) { return invoke<Any>(0xE48D757B, p0); } // 0xE48D757B
	static void STOP_AUDIO_SCENE(Any p0) { invoke<Void>(0xA08D8C58, p0); } // 0xA08D8C58
	static void STOP_AUDIO_SCENES() { invoke<Void>(0xF6C7342A); } // 0xF6C7342A
	static BOOL IS_AUDIO_SCENE_ACTIVE(Any p0) { return invoke<BOOL>(0xACBED05C, p0); } // 0xACBED05C
	static void SET_AUDIO_SCENE_VARIABLE(Any p0, Any p1, Any p2) { invoke<Void>(0x19BB3CE8, p0, p1, p2); } // 0x19BB3CE8
	static void _0xE812925D(Any p0) { invoke<Void>(0xE812925D, p0); } // 0xE812925D
	static void _0x2BC93264(Any p0, Any p1, Any p2) { invoke<Void>(0x2BC93264, p0, p1, p2); } // 0x2BC93264
	static void _0x308ED0EC(Any p0, Any p1) { invoke<Void>(0x308ED0EC, p0, p1); } // 0x308ED0EC
	static Any AUDIO_IS_SCRIPTED_MUSIC_PLAYING() { return invoke<Any>(0x86E995D1); } // 0x86E995D1
	static Any PREPARE_MUSIC_EVENT(Any p0) { return invoke<Any>(0x534A5C1C, p0); } // 0x534A5C1C
	static Any CANCEL_MUSIC_EVENT(Any p0) { return invoke<Any>(0x89FF942D, p0); } // 0x89FF942D
	static Any TRIGGER_MUSIC_EVENT(Any p0) { return invoke<Any>(0xB6094948, p0); } // 0xB6094948
	static Any _0x2705C4D5() { return invoke<Any>(0x2705C4D5); } // 0x2705C4D5
	static Any GET_MUSIC_PLAYTIME() { return invoke<Any>(0xD633C809); } // 0xD633C809
	static void _0x53FC3FEC(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x53FC3FEC, p0, p1, p2, p3); } // 0x53FC3FEC
	static void CLEAR_ALL_BROKEN_GLASS() { invoke<Void>(0xE6B033BF); } // 0xE6B033BF
	static void _0x95050CAD(Any p0, Any p1) { invoke<Void>(0x95050CAD, p0, p1); } // 0x95050CAD
	static void _0xE64F97A0(Any p0, Any p1) { invoke<Void>(0xE64F97A0, p0, p1); } // 0xE64F97A0
	static void _0xD87AF337() { invoke<Void>(0xD87AF337); } // 0xD87AF337
	static Any PREPARE_ALARM(Any p0) { return invoke<Any>(0x084932E8, p0); } // 0x084932E8
	static void START_ALARM(Any p0, Any p1) { invoke<Void>(0x703F524B, p0, p1); } // 0x703F524B
	static void STOP_ALARM(Any p0, Any p1) { invoke<Void>(0xF987BE8C, p0, p1); } // 0xF987BE8C
	static void STOP_ALL_ALARMS(Any p0) { invoke<Void>(0xC3CB9DC6, p0); } // 0xC3CB9DC6
	static BOOL IS_ALARM_PLAYING(Any p0) { return invoke<BOOL>(0x9D8E1D23, p0); } // 0x9D8E1D23
	static Any GET_VEHICLE_DEFAULT_HORN(Any p0) { return invoke<Any>(0xE84ABC19, p0); } // 0xE84ABC19
	static Any _0xFD4B5B3B(Any p0) { return invoke<Any>(0xFD4B5B3B, p0); } // 0xFD4B5B3B
	static void RESET_PED_AUDIO_FLAGS(Any p0) { invoke<Void>(0xDF720C86, p0); } // 0xDF720C86
	static void _0xC307D531(Any p0, Any p1) { invoke<Void>(0xC307D531, p0, p1); } // 0xC307D531
	static void _0x13EB5861(Any p0) { invoke<Void>(0x13EB5861, p0); } // 0x13EB5861
	static void _0x7BED1872(Any p0, Any p1) { invoke<Void>(0x7BED1872, p0, p1); } // 0x7BED1872
	static void SET_AUDIO_FLAG(Any p0, Any p1) { invoke<Void>(0x1C09C9E0, p0, p1); } // 0x1C09C9E0
	static Any PREPARE_SYNCHRONIZED_AUDIO_EVENT(Any p0, Any p1) { return invoke<Any>(0xE1D91FD0, p0, p1); } // 0xE1D91FD0
	static Any PREPARE_SYNCHRONIZED_AUDIO_EVENT_FOR_SCENE(Any p0, Any p1) { return invoke<Any>(0x7652DD49, p0, p1); } // 0x7652DD49
	static Any PLAY_SYNCHRONIZED_AUDIO_EVENT(Any p0) { return invoke<Any>(0x507F3241, p0); } // 0x507F3241
	static Any STOP_SYNCHRONIZED_AUDIO_EVENT(Any p0) { return invoke<Any>(0xADEED2B4, p0); } // 0xADEED2B4
	static void _0x55A21772(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x55A21772, p0, p1, p2, p3); } // 0x55A21772
	static void _0xA17F9AB0(Any p0, Any p1) { invoke<Void>(0xA17F9AB0, p0, p1); } // 0xA17F9AB0
	static void _0x62B43677(Any p0) { invoke<Void>(0x62B43677, p0); } // 0x62B43677
	static void _0x8AD670EC(Any p0, Any p1) { invoke<Void>(0x8AD670EC, p0, p1); } // 0x8AD670EC
	static void _0xD24B4D0C(Any p0) { invoke<Void>(0xD24B4D0C, p0); } // 0xD24B4D0C
	static void _0x7262B5BA() { invoke<Void>(0x7262B5BA); } // 0x7262B5BA
	static Any _0x93A44A1F() { return invoke<Any>(0x93A44A1F); } // 0x93A44A1F
	static void _0x13777A0B(Any p0) { invoke<Void>(0x13777A0B, p0); } // 0x13777A0B
	static void _0x1134F68B() { invoke<Void>(0x1134F68B); } // 0x1134F68B
	static void _0xE0047BFD(Any p0) { invoke<Void>(0xE0047BFD, p0); } // 0xE0047BFD
}

namespace CUTSCENE
{
	static void REQUEST_CUTSCENE(char* CutsceneName, int p1) { invoke<Void>(0xB5977853, CutsceneName, p1); } // 0xB5977853
	static void _0xD98F656A(Any p0, Any p1, Any p2) { invoke<Void>(0xD98F656A, p0, p1, p2); } // 0xD98F656A
	static void REMOVE_CUTSCENE() { invoke<Void>(0x8052F533); } // 0x8052F533
	static BOOL HAS_CUTSCENE_LOADED() { return invoke<BOOL>(0xF9998582); } // 0xF9998582
	static BOOL HAS_THIS_CUTSCENE_LOADED(Any p0) { return invoke<BOOL>(0x3C5619F2, p0); } // 0x3C5619F2
	static void _0x25A2CABC(Any p0) { invoke<Void>(0x25A2CABC, p0); } // 0x25A2CABC
	static Any _0xDD8878E9() { return invoke<Any>(0xDD8878E9); } // 0xDD8878E9
	static Any _0x7B93CDAA(Any p0) { return invoke<Any>(0x7B93CDAA, p0); } // 0x7B93CDAA
	static void _0x47DB08A9(Any p0, Any p1, Any p2) { invoke<Void>(0x47DB08A9, p0, p1, p2); } // 0x47DB08A9
	static void START_CUTSCENE(Any p0) { invoke<Void>(0x210106F6, p0); } // 0x210106F6
	static void START_CUTSCENE_AT_COORDS(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x58BEA436, p0, p1, p2, p3); } // 0x58BEA436
	static void STOP_CUTSCENE(Any p0) { invoke<Void>(0x5EE84DC7, p0); } // 0x5EE84DC7
	static void STOP_CUTSCENE_IMMEDIATELY() { invoke<Void>(0xF528A2AD); } // 0xF528A2AD
	static void SET_CUTSCENE_ORIGIN(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xB0AD7792, p0, p1, p2, p3, p4); } // 0xB0AD7792
	static Any GET_CUTSCENE_TIME() { return invoke<Any>(0x53F5B5AB); } // 0x53F5B5AB
	static Any GET_CUTSCENE_TOTAL_DURATION() { return invoke<Any>(0x0824EBE8); } // 0x0824EBE8
	static BOOL WAS_CUTSCENE_SKIPPED() { return invoke<BOOL>(0xC9B6949D); } // 0xC9B6949D
	static BOOL HAS_CUTSCENE_FINISHED() { return invoke<BOOL>(0x5DED14B4); } // 0x5DED14B4
	static BOOL IS_CUTSCENE_ACTIVE() { return invoke<BOOL>(0xCCE2FE9D); } // 0xCCE2FE9D
	static BOOL IS_CUTSCENE_PLAYING() { return invoke<BOOL>(0xA3A78392); } // 0xA3A78392
	static Any GET_CUTSCENE_SECTION_PLAYING() { return invoke<Any>(0x1026F0D6); } // 0x1026F0D6
	static Any GET_ENTITY_INDEX_OF_CUTSCENE_ENTITY(Any p0, Any p1) { return invoke<Any>(0x1D09ABC7, p0, p1); } // 0x1D09ABC7
	static Any _0x5AE68AE6() { return invoke<Any>(0x5AE68AE6); } // 0x5AE68AE6
	static void REGISTER_ENTITY_FOR_CUTSCENE(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x7CBC3EC7, p0, p1, p2, p3, p4); } // 0x7CBC3EC7
	static Any GET_ENTITY_INDEX_OF_REGISTERED_ENTITY(Any p0, Any p1) { return invoke<Any>(0x46D18755, p0, p1); } // 0x46D18755
	static void SET_CUTSCENE_TRIGGER_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x9D76D9DE, p0, p1, p2, p3, p4, p5); } // 0x9D76D9DE
	static BOOL CAN_SET_ENTER_STATE_FOR_REGISTERED_ENTITY(Any p0, Any p1) { return invoke<BOOL>(0x55C30B26, p0, p1); } // 0x55C30B26
	static BOOL CAN_SET_EXIT_STATE_FOR_REGISTERED_ENTITY(Any p0, Any p1) { return invoke<BOOL>(0x8FF5D3C4, p0, p1); } // 0x8FF5D3C4
	static BOOL CAN_SET_EXIT_STATE_FOR_CAMERA(Any p0) { return invoke<BOOL>(0xEDAE6C02, p0); } // 0xEDAE6C02
	static void _0x35721A08(Any p0) { invoke<Void>(0x35721A08, p0); } // 0x35721A08
	static void SET_CUTSCENE_FADE_VALUES(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xD19EF0DD, p0, p1, p2, p3); } // 0xD19EF0DD
	static void _0x8338DA1D(Any p0) { invoke<Void>(0x8338DA1D, p0); } // 0x8338DA1D
	static void _0x04377C10(Any p0) { invoke<Void>(0x04377C10, p0); } // 0x04377C10
	static Any _0xDBD88708() { return invoke<Any>(0xDBD88708); } // 0xDBD88708
	static void _0x28D54A7F(Any p0) { invoke<Void>(0x28D54A7F, p0); } // 0x28D54A7F
	static void REGISTER_SYNCHRONISED_SCRIPT_SPEECH() { invoke<Void>(0xB60CFBB9); } // 0xB60CFBB9
	static void SET_CUTSCENE_PED_COMPONENT_VARIATION(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x6AF994A1, p0, p1, p2, p3, p4); } // 0x6AF994A1
	static void _0x1E7DA95E(Any p0, Any p1, Any p2) { invoke<Void>(0x1E7DA95E, p0, p1, p2); } // 0x1E7DA95E
	static BOOL DOES_CUTSCENE_ENTITY_EXIST(Any p0, Any p1) { return invoke<BOOL>(0x58E67409, p0, p1); } // 0x58E67409
	static void _0x22E9A9DE(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x22E9A9DE, p0, p1, p2, p3, p4); } // 0x22E9A9DE
	static Any _0x4315A7C5() { return invoke<Any>(0x4315A7C5); } // 0x4315A7C5
}

namespace INTERIOR
{
	static Any GET_INTERIOR_GROUP_ID(Any p0) { return invoke<Any>(0x09D6376F, p0); } // 0x09D6376F
	static Vector3 GET_OFFSET_FROM_INTERIOR_IN_WORLD_COORDS(Any p0, Any p1, Any p2, Any p3) { return invoke<Vector3>(0x7D8F26A1, p0, p1, p2, p3); } // 0x7D8F26A1
	static BOOL IS_INTERIOR_SCENE() { return invoke<BOOL>(0x55226C13); } // 0x55226C13
	static BOOL IS_VALID_INTERIOR(Any p0) { return invoke<BOOL>(0x39C0B635, p0); } // 0x39C0B635
	static void CLEAR_ROOM_FOR_ENTITY(Any p0) { invoke<Void>(0x7DDADB92, p0); } // 0x7DDADB92
	static void FORCE_ROOM_FOR_ENTITY(Any p0, Any p1, Any p2) { invoke<Void>(0x10BD4435, p0, p1, p2); } // 0x10BD4435
	static Any GET_ROOM_KEY_FROM_ENTITY(Any p0) { return invoke<Any>(0xE4ACF8C3, p0); } // 0xE4ACF8C3
	static Any GET_KEY_FOR_ENTITY_IN_ROOM(Any p0) { return invoke<Any>(0x91EA80EF, p0); } // 0x91EA80EF
	static Any GET_INTERIOR_FROM_ENTITY(Any p0) { return invoke<Any>(0x5C644614, p0); } // 0x5C644614
	static void _0xE645E162(Any p0, Any p1) { invoke<Void>(0xE645E162, p0, p1); } // 0xE645E162
	static void _0xD79803B5(Any p0, Any p1) { invoke<Void>(0xD79803B5, p0, p1); } // 0xD79803B5
	static void _0x1F6B4B13(Any p0) { invoke<Void>(0x1F6B4B13, p0); } // 0x1F6B4B13
	static void _0x0E9529CC(Any p0) { invoke<Void>(0x0E9529CC, p0); } // 0x0E9529CC
	static Any _0x4FF3D3F5() { return invoke<Any>(0x4FF3D3F5); } // 0x4FF3D3F5
	static void _0x617DC75D() { invoke<Void>(0x617DC75D); } // 0x617DC75D
	static int GET_INTERIOR_AT_COORDS(float x, float y, float z) { return invoke<Any>(0xA17FBF37, x, y, z); } // 0xA17FBF37
	static void ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(Any p0, Any p1) { invoke<Void>(0xA2A73564, p0, p1); } // 0xA2A73564
	static void _0x3ADA414E(Any p0) { invoke<Void>(0x3ADA414E, p0); } // 0x3ADA414E
	static void UNPIN_INTERIOR(Any p0) { invoke<Void>(0xFCFF792A, p0); } // 0xFCFF792A
	static BOOL IS_INTERIOR_READY(Any p0) { return invoke<BOOL>(0xE1EF6450, p0); } // 0xE1EF6450
	static int _0x96525B06(float x, float y, float z, char* interior) { return invoke<int>(0x96525B06, x, y, z, interior); } // 0x96525B06
	static Any _0x7762249C(Any p0, Any p1, Any p2) { return invoke<Any>(0x7762249C, p0, p1, p2); } // 0x7762249C
	static Any GET_INTERIOR_FROM_COLLISION(Any p0, Any p1, Any p2) { return invoke<Any>(0x7ED33DC1, p0, p1, p2); } // 0x7ED33DC1
	static void _0xC80A5DDF(Any p0, Any p1) { invoke<Void>(0xC80A5DDF, p0, p1); } // 0xC80A5DDF
	static void _0xDBA768A1(Any p0, Any p1) { invoke<Void>(0xDBA768A1, p0, p1); } // 0xDBA768A1
	static Any _0x39A3CC6F(Any p0, Any p1) { return invoke<Any>(0x39A3CC6F, p0, p1); } // 0x39A3CC6F
	static void REFRESH_INTERIOR(Any p0) { invoke<Void>(0x9A29ACE6, p0); } // 0x9A29ACE6
	static void _0x1F375B4C(Any p0) { invoke<Void>(0x1F375B4C, p0); } // 0x1F375B4C
	static void DISABLE_INTERIOR(Any p0, Any p1) { invoke<Void>(0x093ADEA5, p0, p1); } // 0x093ADEA5
	static BOOL IS_INTERIOR_DISABLED(Any p0) { return invoke<BOOL>(0x81F34C71, p0); } // 0x81F34C71
	static void CAP_INTERIOR(Any p0, Any p1) { invoke<Void>(0x34E735A6, p0, p1); } // 0x34E735A6
	static BOOL IS_INTERIOR_CAPPED(Any p0) { return invoke<BOOL>(0x18B17C80, p0); } // 0x18B17C80
	static void _0x5EF9C5C2(Any p0) { invoke<Void>(0x5EF9C5C2, p0); } // 0x5EF9C5C2
}

namespace CAM
{
	static void RENDER_SCRIPT_CAMS(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x74337969, p0, p1, p2, p3, p4); } // 0x74337969
	static void _0xD3C08183(Any p0, Any p1, Any p2) { invoke<Void>(0xD3C08183, p0, p1, p2); } // 0xD3C08183
	static Any CREATE_CAM(char* camName, Any p1) { return invoke<Any>(0xE9BF2A7D, camName, p1); } // 0xE9BF2A7D
	static Any CREATE_CAM_WITH_PARAMS(char* camName, float* posX, float* posY, float* posZ, float* rotX, float* rotY, float* rotZ, float fov, int p8, int p9) { return invoke<Any>(0x23B02F15, camName, posX, posY, posZ, rotX, rotY, rotZ, fov, p8, p9); } // 0x23B02F15
	static Any CREATE_CAMERA(Any p0, Any p1) { return invoke<Any>(0x5D6739AE, p0, p1); } // 0x5D6739AE
	static Any CREATE_CAMERA_WITH_PARAMS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<Any>(0x0688BE9A, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x0688BE9A
	static void DESTROY_CAM(Any p0, Any p1) { invoke<Void>(0xC39302BD, p0, p1); } // 0xC39302BD
	static void DESTROY_ALL_CAMS(Any p0) { invoke<Void>(0x10C151CE, p0); } // 0x10C151CE
	static BOOL DOES_CAM_EXIST(Any p0) { return invoke<BOOL>(0x1EF89DC0, p0); } // 0x1EF89DC0
	static void SET_CAM_ACTIVE(Any p0, Any p1) { invoke<Void>(0x064659C2, p0, p1); } // 0x064659C2
	static BOOL IS_CAM_ACTIVE(Any p0) { return invoke<BOOL>(0x4B58F177, p0); } // 0x4B58F177
	static BOOL IS_CAM_RENDERING(Any p0) { return invoke<BOOL>(0x6EC6B5B2, p0); } // 0x6EC6B5B2
	static Any GET_RENDERING_CAM() { return invoke<Any>(0x0FCF4DF1); } // 0x0FCF4DF1
	static Vector3 GET_CAM_COORD(Any p0) { return invoke<Vector3>(0x7C40F09C, p0); } // 0x7C40F09C
	static Vector3 GET_CAM_ROT(Any p0, Any p1) { return invoke<Vector3>(0xDAC84C9F, p0, p1); } // 0xDAC84C9F
	static Any GET_CAM_FOV(ScrHandle Camera_handle) { return invoke<Any>(0xD6E9FCF5, Camera_handle); } // 0xD6E9FCF5
	static Any GET_CAM_NEAR_CLIP(Any p0) { return invoke<Any>(0xCFCD35EE, p0); } // 0xCFCD35EE
	static Any GET_CAM_FAR_CLIP(Any p0) { return invoke<Any>(0x09F119B8, p0); } // 0x09F119B8
	static Any GET_CAM_FAR_DOF(Any p0) { return invoke<Any>(0x98C5CCE9, p0); } // 0x98C5CCE9
	static void SET_CAM_PARAMS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { invoke<Void>(0x2167CEBF, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0x2167CEBF
	static void SET_CAM_COORD(int p0, float p1, float p2, float p3) { invoke<Void>(0x7A8053AF, p0, p1, p2, p3); } // 0x7A8053AF
	static void SET_CAM_ROT(Any p0, Vector3 v1, Any p4) { invoke<Void>(0xEE38B3C1, p0, v1, p4); } // 0xEE38B3C1
	static void SET_CAM_FOV(char* camName, float FovVaule) { invoke<Void>(0xD3D5D74F, camName, FovVaule); } // 0xD3D5D74F
	static void SET_CAM_NEAR_CLIP(Any p0, Any p1) { invoke<Void>(0x46DB13B1, p0, p1); } // 0x46DB13B1
	static void SET_CAM_FAR_CLIP(Any p0, Any p1) { invoke<Void>(0x0D23E381, p0, p1); } // 0x0D23E381
	static void SET_CAM_NEAR_DOF(Any p0, Any p1) { invoke<Void>(0xF28254DF, p0, p1); } // 0xF28254DF
	static void SET_CAM_FAR_DOF(Any p0, Any p1) { invoke<Void>(0x58515E8E, p0, p1); } // 0x58515E8E
	static void SET_CAM_DOF_STRENGTH(Any p0, Any p1) { invoke<Void>(0x3CC4EB3F, p0, p1); } // 0x3CC4EB3F
	static void SET_CAM_DOF_PLANES(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xAD6C2B8F, p0, p1, p2, p3, p4); } // 0xAD6C2B8F
	static void _0x8306C256(Any p0, Any p1) { invoke<Void>(0x8306C256, p0, p1); } // 0x8306C256
	static void SET_CAM_MOTION_BLUR_STRENGTH(Any p0, float p1) { invoke<Void>(0xFD6E0D67, p0, p1); } // 0xFD6E0D67
	static void _0x8BBF2950() { invoke<Void>(0x8BBF2950); } // 0x8BBF2950
	static void ATTACH_CAM_TO_ENTITY(Any p0, Any p1, float p2, float p3, float p4, Any p5) { invoke<Void>(0xAD7C45F6, p0, p1, p2, p3, p4, p5); } // 0xAD7C45F6
	static void ATTACH_CAM_TO_PED_BONE(int CameraHandle, Ped PedHandle, int BoneIndex, float X, float Y, float Z, float Heading) { invoke<Void>(0x506BB35C, CameraHandle, PedHandle, BoneIndex, X, Y, Z, Heading); } // 0x506BB35C
	static void DETACH_CAM(char* camName) { invoke<Void>(0xF4FBF14A, camName); } // 0xF4FBF14A
	static void SET_CAM_INHERIT_ROLL_VEHICLE(Any p0, Any p1) { invoke<Void>(0xE4BD5342, p0, p1); } // 0xE4BD5342
	static void POINT_CAM_AT_COORD(int p0, float p1, float p2, float p3) { invoke<Void>(0x914BC21A, p0, p1, p2, p3); } // 0x914BC21A
	static void POINT_CAM_AT_ENTITY(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x7597A0F7, p0, p1, p2, p3, p4, p5); } // 0x7597A0F7
	static void POINT_CAM_AT_PED_BONE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x09F47049, p0, p1, p2, p3, p4, p5, p6); } // 0x09F47049
	static void STOP_CAM_POINTING(Any p0) { invoke<Void>(0x5435F6A5, p0); } // 0x5435F6A5
	static void _0x0C74F9AF(Any p0, Any p1) { invoke<Void>(0x0C74F9AF, p0, p1); } // 0x0C74F9AF
	static void _0xE1A0B2F1(Any p0, Any p1) { invoke<Void>(0xE1A0B2F1, p0, p1); } // 0xE1A0B2F1
	static void _0x43220969(Any p0, Any p1) { invoke<Void>(0x43220969, p0, p1); } // 0x43220969
	static void SET_CAM_DEBUG_NAME(Any p0, Any p1) { invoke<Void>(0x9B00DF3F, p0, p1); } // 0x9B00DF3F
	static void ADD_CAM_SPLINE_NODE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0xAD3C7EAA, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xAD3C7EAA
	static void _0x30510511(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x30510511, p0, p1, p2, p3); } // 0x30510511
	static void _0xBA6C085B(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xBA6C085B, p0, p1, p2, p3); } // 0xBA6C085B
	static void _0xB4737F03(Any p0, Any p1, Any p2) { invoke<Void>(0xB4737F03, p0, p1, p2); } // 0xB4737F03
	static void SET_CAM_SPLINE_PHASE(Any p0, Any p1) { invoke<Void>(0xF0AED233, p0, p1); } // 0xF0AED233
	static Any GET_CAM_SPLINE_PHASE(Any p0) { return invoke<Any>(0x39784DD9, p0); } // 0x39784DD9
	static Any GET_CAM_SPLINE_NODE_PHASE(Any p0) { return invoke<Any>(0x7B9522F6, p0); } // 0x7B9522F6
	static void SET_CAM_SPLINE_DURATION(Any p0, Any p1) { invoke<Void>(0x3E91FC8A, p0, p1); } // 0x3E91FC8A
	static void _0x15E141CE(Any p0, Any p1) { invoke<Void>(0x15E141CE, p0, p1); } // 0x15E141CE
	static Any GET_CAM_SPLINE_NODE_INDEX(Any p0) { return invoke<Any>(0xF8AEB6BD, p0); } // 0xF8AEB6BD
	static void _0x21D275DA(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x21D275DA, p0, p1, p2, p3); } // 0x21D275DA
	static void _0xA3BD9E94(Any p0, Any p1, Any p2) { invoke<Void>(0xA3BD9E94, p0, p1, p2); } // 0xA3BD9E94
	static void OVERRIDE_CAM_SPLINE_VELOCITY(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x326A17E2, p0, p1, p2, p3); } // 0x326A17E2
	static void OVERRIDE_CAM_SPLINE_MOTION_BLUR(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x633179E6, p0, p1, p2, p3); } // 0x633179E6
	static void _0xC90B2DDC(Any p0, Any p1, Any p2) { invoke<Void>(0xC90B2DDC, p0, p1, p2); } // 0xC90B2DDC
	static BOOL IS_CAM_SPLINE_PAUSED(Any p0) { return invoke<BOOL>(0x60B34FF5, p0); } // 0x60B34FF5
	static void SET_CAM_ACTIVE_WITH_INTERP(int camTo, int camFrom, int duration, Any unk0, Any unk1) { invoke<Void>(0x7983E7F0, camTo, camFrom, duration, unk0, unk1); } // 0x7983E7F0
	static BOOL IS_CAM_INTERPOLATING(Any p0) { return invoke<BOOL>(0x7159CB5D, p0); } // 0x7159CB5D
	static void SHAKE_CAM(Any p0, Any p1, Any p2) { invoke<Void>(0x1D4211B0, p0, p1, p2); } // 0x1D4211B0
	static void ANIMATED_SHAKE_CAM(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xE1168767, p0, p1, p2, p3, p4); } // 0xE1168767
	static BOOL IS_CAM_SHAKING(Any p0) { return invoke<BOOL>(0x0961FD9B, p0); } // 0x0961FD9B
	static void SET_CAM_SHAKE_AMPLITUDE(Any p0, Any p1) { invoke<Void>(0x60FF6382, p0, p1); } // 0x60FF6382
	static void STOP_CAM_SHAKING(Any p0, Any p1) { invoke<Void>(0x40D0EB87, p0, p1); } // 0x40D0EB87
	static void _0x2B0F05CD(Any p0, Any p1) { invoke<Void>(0x2B0F05CD, p0, p1); } // 0x2B0F05CD
	static void _0xCB75BD9C(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xCB75BD9C, p0, p1, p2, p3); } // 0xCB75BD9C
	static Any _0x6AEFE6A5() { return invoke<Any>(0x6AEFE6A5); } // 0x6AEFE6A5
	static void _0x26FCFB96(Any p0) { invoke<Void>(0x26FCFB96, p0); } // 0x26FCFB96
	static Any PLAY_CAM_ANIM(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return invoke<Any>(0xBCEFB87E, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0xBCEFB87E
	static BOOL IS_CAM_PLAYING_ANIM(Any p0, Any p1, Any p2) { return invoke<BOOL>(0xB998CB49, p0, p1, p2); } // 0xB998CB49
	static void SET_CAM_ANIM_CURRENT_PHASE(Any p0, Any p1) { invoke<Void>(0x3CB1D17F, p0, p1); } // 0x3CB1D17F
	static Any GET_CAM_ANIM_CURRENT_PHASE(Any p0) { return invoke<Any>(0x345F72D0, p0); } // 0x345F72D0
	static Any PLAY_SYNCHRONIZED_CAM_ANIM(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x9458459E, p0, p1, p2, p3); } // 0x9458459E
	static void _0x56F9ED27(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x56F9ED27, p0, p1, p2, p3); } // 0x56F9ED27
	static void _0x71570DBA(Any p0, Any p1) { invoke<Void>(0x71570DBA, p0, p1); } // 0x71570DBA
	static void _0x60B345DE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x60B345DE, p0, p1, p2, p3); } // 0x60B345DE
	static void _0x44473EFC(Any p0) { invoke<Void>(0x44473EFC, p0); } // 0x44473EFC
	static Any _0xDA931D65(Any p0) { return invoke<Any>(0xDA931D65, p0); } // 0xDA931D65
	static BOOL IS_SCREEN_FADED_OUT() { return invoke<BOOL>(0x9CAA05FA); } // 0x9CAA05FA
	static BOOL IS_SCREEN_FADED_IN() { return invoke<BOOL>(0x4F37276D); } // 0x4F37276D
	static BOOL IS_SCREEN_FADING_OUT() { return invoke<BOOL>(0x79275A57); } // 0x79275A57
	static BOOL IS_SCREEN_FADING_IN() { return invoke<BOOL>(0xC7C82800); } // 0xC7C82800
	static void DO_SCREEN_FADE_IN(int ticks) { invoke<Void>(0x66C1BDEE, ticks); } // 0x66C1BDEE
	static void DO_SCREEN_FADE_OUT(int ticks) { invoke<Void>(0x89D01805, ticks); } // 0x89D01805
	static void SET_WIDESCREEN_BORDERS(int p0, int p1) { invoke<Void>(0x1A75DC9A, p0, p1); } // 0x1A75DC9A
	static Vector3 GET_GAMEPLAY_CAM_COORD() { return invoke<Vector3>(0x9388CF79); } // 0x9388CF79
	static Vector3 GET_GAMEPLAY_CAM_ROT(Any p0) { return invoke<Vector3>(0x13A010B5, p0); } // 0x13A010B5
	static Any GET_GAMEPLAY_CAM_FOV() { return invoke<Any>(0x4D6B3BFA); } // 0x4D6B3BFA
	static void _0xA6E73135(Any p0) { invoke<Void>(0xA6E73135, p0); } // 0xA6E73135
	static void _0x1126E37C(Any p0) { invoke<Void>(0x1126E37C, p0); } // 0x1126E37C
	static Any GET_GAMEPLAY_CAM_RELATIVE_HEADING() { return invoke<Any>(0xCAF839C2); } // 0xCAF839C2
	static void SET_GAMEPLAY_CAM_RELATIVE_HEADING(float heading) { invoke<Void>(0x20C6217C, heading); } // 0x20C6217C
	static Any GET_GAMEPLAY_CAM_RELATIVE_PITCH() { return invoke<Any>(0xFC5A4946); } // 0xFC5A4946
	static void SET_GAMEPLAY_CAM_RELATIVE_PITCH(float x, float Value2) { invoke<Void>(0x6381B963, x, Value2); } // 0x6381B963
	static void SHAKE_GAMEPLAY_CAM(Any p0, Any p1) { invoke<Void>(0xF2EFE660, p0, p1); } // 0xF2EFE660
	static BOOL IS_GAMEPLAY_CAM_SHAKING() { return invoke<BOOL>(0x3457D681); } // 0x3457D681
	static void SET_GAMEPLAY_CAM_SHAKE_AMPLITUDE(Any p0) { invoke<Void>(0x9219D44A, p0); } // 0x9219D44A
	static void STOP_GAMEPLAY_CAM_SHAKING(Any p0) { invoke<Void>(0xFD569E4E, p0); } // 0xFD569E4E
	static void _0x7D3007A2(Any p0) { invoke<Void>(0x7D3007A2, p0); } // 0x7D3007A2
	static BOOL IS_GAMEPLAY_CAM_RENDERING() { return invoke<BOOL>(0x0EF276DA); } // 0x0EF276DA
	static Any _0xC0B00C20() { return invoke<Any>(0xC0B00C20); } // 0xC0B00C20
	static Any _0x60C23785() { return invoke<Any>(0x60C23785); } // 0x60C23785
	static void _0x20BFF6E5(Any p0) { invoke<Void>(0x20BFF6E5, p0); } // 0x20BFF6E5
	static void _0xA61FF9AC() { invoke<Void>(0xA61FF9AC); } // 0xA61FF9AC
	static BOOL IS_GAMEPLAY_CAM_LOOKING_BEHIND() { return invoke<BOOL>(0x33C83F17); } // 0x33C83F17
	static void _0x2701A9AD(Any p0) { invoke<Void>(0x2701A9AD, p0); } // 0x2701A9AD
	static void _0xC4736ED3(Any p0) { invoke<Void>(0xC4736ED3, p0); } // 0xC4736ED3
	static void _0x6B0E9D57() { invoke<Void>(0x6B0E9D57); } // 0x6B0E9D57
	static BOOL IS_SPHERE_VISIBLE(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0xDD1329E2, p0, p1, p2, p3); } // 0xDD1329E2
	static BOOL IS_FOLLOW_PED_CAM_ACTIVE() { return invoke<BOOL>(0x9F9E856C); } // 0x9F9E856C
	static Any SET_FOLLOW_PED_CAM_CUTSCENE_CHAT(Any p0, Any p1) { return invoke<Any>(0x1425F6AC, p0, p1); } // 0x1425F6AC
	static void _0x8DC53629(Any p0, Any p1) { invoke<Void>(0x8DC53629, p0, p1); } // 0x8DC53629
	static void _0x1F9DE6E4() { invoke<Void>(0x1F9DE6E4); } // 0x1F9DE6E4
	static void _CLAMP_GAMEPLAY_CAM_YAW(float minimum, float maximum) { invoke<Void>(0x749909AC, minimum, maximum); } // 0x749909AC
	static void _CLAMP_GAMEPLAY_CAM_PITCH(float minimum, float maximum) { invoke<Void>(0xFA3A16E7, minimum, maximum); } // 0xFA3A16E7
	static void _ANIMATE_GAMEPLAY_CAM_ZOOM(float p0, float _distance) { invoke<Void>(0x77340650, p0, _distance); } // 0x77340650
	static void _0x4B22C5CB(Vehicle p0, int p1) { invoke<Void>(0x4B22C5CB, p0, p1); } // 0x4B22C5CB
	static Any GET_FOLLOW_PED_CAM_ZOOM_LEVEL() { return invoke<Any>(0x57583DF1); } // 0x57583DF1
	static Any GET_FOLLOW_PED_CAM_VIEW_MODE() { return invoke<Any>(0xA65FF946); } // 0xA65FF946
	static void SET_FOLLOW_PED_CAM_VIEW_MODE(Any p0) { invoke<Void>(0x495DBE8D, p0); } // 0x495DBE8D
	static BOOL IS_FOLLOW_VEHICLE_CAM_ACTIVE() { return invoke<BOOL>(0x8DD49B77); } // 0x8DD49B77
	static void _0x9DB5D391(Any p0) { invoke<Void>(0x9DB5D391, p0); } // 0x9DB5D391
	static void _0x92302899(Any p0, Any p1) { invoke<Void>(0x92302899, p0, p1); } // 0x92302899
	static Any GET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL() { return invoke<Any>(0x8CD67DE3); } // 0x8CD67DE3
	static void SET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL(Any p0) { invoke<Void>(0x8F55EBBE, p0); } // 0x8F55EBBE
	static Any GET_FOLLOW_VEHICLE_CAM_VIEW_MODE() { return invoke<Any>(0xA4B4DB03); } // 0xA4B4DB03
	static void SET_FOLLOW_VEHICLE_CAM_VIEW_MODE(Any p0) { invoke<Void>(0xC4FBBBD3, p0); } // 0xC4FBBBD3
	static Any _0xF3B148A6(Any p0) { return invoke<Any>(0xF3B148A6, p0); } // 0xF3B148A6
	static void _0x1DEBCB45(Any p0, Any p1) { invoke<Void>(0x1DEBCB45, p0, p1); } // 0x1DEBCB45
	static BOOL IS_AIM_CAM_ACTIVE() { return invoke<BOOL>(0xC24B4F6F); } // 0xC24B4F6F
	static Any _0x8F320DE4() { return invoke<Any>(0x8F320DE4); } // 0x8F320DE4
	static BOOL IS_FIRST_PERSON_AIM_CAM_ACTIVE() { return invoke<BOOL>(0xD6280468); } // 0xD6280468
	static void _0x1BAA7182() { invoke<Void>(0x1BAA7182); } // 0x1BAA7182
	static Any _0x33951005() { return invoke<Any>(0x33951005); } // 0x33951005
	static void _0x9F4AF763(float p0) { invoke<Void>(0x9F4AF763, p0); } // 0x9F4AF763
	static void _0x68BA0730(Any p0, Any p1) { invoke<Void>(0x68BA0730, p0, p1); } // 0x68BA0730
	static void _0x2F29F0D5(Any p0, Any p1) { invoke<Void>(0x2F29F0D5, p0, p1); } // 0x2F29F0D5
	static void _0x76DAC96C(Any p0, Any p1) { invoke<Void>(0x76DAC96C, p0, p1); } // 0x76DAC96C
	static void _0x0E21069D(Any p0) { invoke<Void>(0x0E21069D, p0); } // 0x0E21069D
	static void _0x71E9C63E(Any p0) { invoke<Void>(0x71E9C63E, p0); } // 0x71E9C63E
	static void _0xD1EEBC45(Any p0) { invoke<Void>(0xD1EEBC45, p0); } // 0xD1EEBC45
	static Vector3 _0x9C84BDA0() { return invoke<Vector3>(0x9C84BDA0); } // 0x9C84BDA0
	static Vector3 _0x1FFBEFC5(Any p0) { return invoke<Vector3>(0x1FFBEFC5, p0); } // 0x1FFBEFC5
	static Vector3 _0xACADF916(Any p0, Any p1) { return invoke<Vector3>(0xACADF916, p0, p1); } // 0xACADF916
	static Any _0x721B763B() { return invoke<Any>(0x721B763B); } // 0x721B763B
	static Any _0x23E3F106(Any p0) { return invoke<Any>(0x23E3F106, p0); } // 0x23E3F106
	static Any _0x457AE195() { return invoke<Any>(0x457AE195); } // 0x457AE195
	static Any _0x46CB3A49() { return invoke<Any>(0x46CB3A49); } // 0x46CB3A49
	static Any _0x19297A7A() { return invoke<Any>(0x19297A7A); } // 0x19297A7A
	static Any _0xF24777CA() { return invoke<Any>(0xF24777CA); } // 0xF24777CA
	static Any _0x38992E83() { return invoke<Any>(0x38992E83); } // 0x38992E83
	static void SET_GAMEPLAY_COORD_HINT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0xF27483C9, p0, p1, p2, p3, p4, p5, p6); } // 0xF27483C9
	static void SET_GAMEPLAY_PED_HINT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x7C27343E, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x7C27343E
	static void SET_GAMEPLAY_VEHICLE_HINT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x2C9A11D8, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x2C9A11D8
	static void _0x2ED5E2F8(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x2ED5E2F8, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x2ED5E2F8
	static void SET_GAMEPLAY_ENTITY_HINT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0x66C32306, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x66C32306
	static BOOL IS_GAMEPLAY_HINT_ACTIVE() { return invoke<BOOL>(0xAD8DA205); } // 0xAD8DA205
	static void STOP_GAMEPLAY_HINT(Any p0) { invoke<Void>(0x1BC28B7B, p0); } // 0x1BC28B7B
	static void _0xCAFEE798(Any p0) { invoke<Void>(0xCAFEE798, p0); } // 0xCAFEE798
	static void SET_GAMEPLAY_HINT_FOV(Any p0) { invoke<Void>(0x96FD173B, p0); } // 0x96FD173B
	static void _0x72E8CD3A(Any p0) { invoke<Void>(0x72E8CD3A, p0); } // 0x72E8CD3A
	static void _0x79472AE3(Any p0) { invoke<Void>(0x79472AE3, p0); } // 0x79472AE3
	static void _0xFC7464A0(Any p0) { invoke<Void>(0xFC7464A0, p0); } // 0xFC7464A0
	static void _0x3554AA0E(Any p0) { invoke<Void>(0x3554AA0E, p0); } // 0x3554AA0E
	static void GET_IS_MULTIPLAYER_BRIEF(Any p0) { invoke<Void>(0x2F0CE859, p0); } // 0x2F0CE859
	static void SET_CINEMATIC_BUTTON_ACTIVE(Any p0) { invoke<Void>(0x3FBC5D00, p0); } // 0x3FBC5D00
	static BOOL IS_CINEMATIC_CAM_RENDERING() { return invoke<BOOL>(0x80471AD9); } // 0x80471AD9
	static void SHAKE_CINEMATIC_CAM(Any p0, Any p1) { invoke<Void>(0x61815F31, p0, p1); } // 0x61815F31
	static BOOL IS_CINEMATIC_CAM_SHAKING() { return invoke<BOOL>(0x8376D939); } // 0x8376D939
	static void SET_CINEMATIC_CAM_SHAKE_AMPLITUDE(Any p0) { invoke<Void>(0x67510C4B, p0); } // 0x67510C4B
	static void STOP_CINEMATIC_CAM_SHAKING(Any p0) { invoke<Void>(0x71C12904, p0); } // 0x71C12904
	static void _0x5AC6DAC9() { invoke<Void>(0x5AC6DAC9); } // 0x5AC6DAC9
	static void _0x837F8581() { invoke<Void>(0x837F8581); } // 0x837F8581
	static void _0x65DDE8AF() { invoke<Void>(0x65DDE8AF); } // 0x65DDE8AF
	static void _0xD75CDD75() { invoke<Void>(0xD75CDD75); } // 0xD75CDD75
	static Any _0x96A07066() { return invoke<Any>(0x96A07066); } // 0x96A07066
	static void CREATE_CINEMATIC_SHOT(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xAC494E35, p0, p1, p2, p3); } // 0xAC494E35
	static BOOL IS_CINEMATIC_SHOT_ACTIVE(Any p0) { return invoke<BOOL>(0xA4049042, p0); } // 0xA4049042
	static void STOP_CINEMATIC_SHOT(Any p0) { invoke<Void>(0xD78358C5, p0); } // 0xD78358C5
	static void _0xFBB85E02(Any p0) { invoke<Void>(0xFBB85E02, p0); } // 0xFBB85E02
	static void _0x4938C82F() { invoke<Void>(0x4938C82F); } // 0x4938C82F
	static void SET_CINEMATIC_MODE_ACTIVE(Any p0) { invoke<Void>(0x2009E747, p0); } // 0x2009E747
	static Any _0x6739AD55() { return invoke<Any>(0x6739AD55); } // 0x6739AD55
	static void STOP_CUTSCENE_CAM_SHAKING(Any p0) { invoke<Void>(0xF07D603D, p0); } // 0xF07D603D
	static void _0x067BA6F5(Any p0) { invoke<Void>(0x067BA6F5, p0); } // 0x067BA6F5
	static Any _0xFD99BE2B(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<Any>(0xFD99BE2B, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xFD99BE2B
	static void _0xE206C450() { invoke<Void>(0xE206C450); } // 0xE206C450
	static void _0xB06CCD38(Any p0) { invoke<Void>(0xB06CCD38, p0); } // 0xB06CCD38
}

namespace WEAPON
{
	static void ENABLE_LASER_SIGHT_RENDERING(Any p0) { invoke<Void>(0xE3438955, p0); } // 0xE3438955
	static Any _0x324FA47A(Any p0) { return invoke<Any>(0x324FA47A, p0); } // 0x324FA47A
	static Any GET_WEAPONTYPE_MODEL(Any p0) { return invoke<Any>(0x44E1C269, p0); } // 0x44E1C269
	static Any GET_WEAPONTYPE_SLOT(Any p0) { return invoke<Any>(0x2E3759AF, p0); } // 0x2E3759AF
	static Any GET_WEAPONTYPE_GROUP(Any p0) { return invoke<Any>(0x5F2DE833, p0); } // 0x5F2DE833
	static void SET_CURRENT_PED_WEAPON(Ped PedHandle, Hash WeaponHash, BOOL EquipNow) { invoke<Void>(0xB8278882, PedHandle, WeaponHash, EquipNow); } // 0xB8278882
	static Any GET_CURRENT_PED_WEAPON(Ped ped, unsigned int* weapHash, BOOL p2) { return invoke<Any>(0xB0237302, ped, weapHash, p2); } // 0xB0237302
	static Any _0x5D73CD20(Any p0) { return invoke<Any>(0x5D73CD20, p0); } // 0x5D73CD20
	static Any GET_BEST_PED_WEAPON(Any p0, Any p1) { return invoke<Any>(0xB998D444, p0, p1); } // 0xB998D444
	static Any SET_CURRENT_PED_VEHICLE_WEAPON(Any p0, Any p1) { return invoke<Any>(0x8E6F2AF1, p0, p1); } // 0x8E6F2AF1
	static Any GET_CURRENT_PED_VEHICLE_WEAPON(Any p0, Any p1) { return invoke<Any>(0xF26C5D65, p0, p1); } // 0xF26C5D65
	static BOOL IS_PED_ARMED(Any p0, Any p1) { return invoke<BOOL>(0x0BFC892C, p0, p1); } // 0x0BFC892C
	static BOOL IS_WEAPON_VALID(Hash WeapHash) { return invoke<BOOL>(0x38CA2954, WeapHash); } // 0x38CA2954
	static BOOL HAS_PED_GOT_WEAPON(Any p0, Any p1, Any p2) { return invoke<BOOL>(0x43D2FA82, p0, p1, p2); } // 0x43D2FA82
	static Any _0x02A32CB0(Any p0) { return invoke<Any>(0x02A32CB0, p0); } // 0x02A32CB0
	static Any GET_PED_WEAPONTYPE_IN_SLOT(Any p0, Any p1) { return invoke<Any>(0x9BC64E16, p0, p1); } // 0x9BC64E16
	static Any GET_AMMO_IN_PED_WEAPON(Any p0, Any p1) { return invoke<Any>(0x0C755733, p0, p1); } // 0x0C755733
	static void ADD_AMMO_TO_PED(Ped handle, Hash weaponHash, int ammo) { invoke<Void>(0x7F0580C7, handle, weaponHash, ammo); } // 0x7F0580C7
	static void SET_PED_AMMO(Ped PedHandle, Hash WeaponHash, int ammo) { invoke<Void>(0xBF90DF1A, PedHandle, WeaponHash, ammo); } // 0xBF90DF1A
	static void SET_PED_INFINITE_AMMO(Ped Handle, BOOL Toggle, Hash WeaponHash) { invoke<Void>(0x9CB8D278, Handle, Toggle, WeaponHash); } // 0x9CB8D278
	static void SET_PED_INFINITE_AMMO_CLIP(Ped PedHandle, BOOL Toggle) { invoke<Void>(0x5A5E3B67, PedHandle, Toggle); } // 0x5A5E3B67
	static void GIVE_WEAPON_TO_PED(int pedHandle, Hash weaponAssetHash, int ammoCount, BOOL equipNow, BOOL isAmmoLoaded) { invoke<Void>(0xC4D88A85, pedHandle, weaponAssetHash, ammoCount, equipNow, isAmmoLoaded); } // 0xC4D88A85
	static void GIVE_DELAYED_WEAPON_TO_PED(Ped pedHandle, Hash weaponHash, int time, BOOL p3) { invoke<Void>(0x5868D20D, pedHandle, weaponHash, time, p3); } // 0x5868D20D
	static void REMOVE_ALL_PED_WEAPONS(Ped PedHandle, BOOL Toggle) { invoke<Void>(0xA44CE817, PedHandle, Toggle); } // 0xA44CE817
	static void REMOVE_WEAPON_FROM_PED(Ped Handle, Hash WeaponHash) { invoke<Void>(0x9C37F220, Handle, WeaponHash); } // 0x9C37F220
	static void HIDE_PED_WEAPON_FOR_SCRIPTED_CUTSCENE(Player PedHandle, BOOL Toggle) { invoke<Void>(0x00CFD6E9, PedHandle, Toggle); } // 0x00CFD6E9
	static void SET_PED_CURRENT_WEAPON_VISIBLE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x00BECD77, p0, p1, p2, p3); } // 0x00BECD77
	static void SET_PED_DROPS_WEAPONS_WHEN_DEAD(Any p0, Any p1) { invoke<Void>(0x8A444056, p0, p1); } // 0x8A444056
	static BOOL HAS_PED_BEEN_DAMAGED_BY_WEAPON(Any p0, Any p1, Any p2) { return invoke<BOOL>(0xCDFBBCC6, p0, p1, p2); } // 0xCDFBBCC6
	static void CLEAR_PED_LAST_WEAPON_DAMAGE(Ped PedHandle) { invoke<Void>(0x52C68832, PedHandle); } // 0x52C68832
	static BOOL HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON(Any p0, Any p1, Any p2) { return invoke<BOOL>(0x6DAABB39, p0, p1, p2); } // 0x6DAABB39
	static void CLEAR_ENTITY_LAST_WEAPON_DAMAGE(Any p0) { invoke<Void>(0xCEC2732B, p0); } // 0xCEC2732B
	static void SET_PED_DROPS_WEAPON(Any p0) { invoke<Void>(0x3D3329FA, p0); } // 0x3D3329FA
	static void SET_PED_DROPS_INVENTORY_WEAPON(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x81FFB874, p0, p1, p2, p3, p4, p5); } // 0x81FFB874
	static Any GET_MAX_AMMO_IN_CLIP(Ped ped, Hash WeapHash, BOOL p2) { return invoke<Any>(0x6961E2A4, ped, WeapHash, p2); } // 0x6961E2A4
	static Any GET_AMMO_IN_CLIP(Ped Handle, Hash WeaponHash, BOOL p2) { return invoke<Any>(0x73C100C3, Handle, WeaponHash, p2); } // 0x73C100C3
	static Any SET_AMMO_IN_CLIP(Ped Handle, Hash WeaponHash, int ammo) { return invoke<Any>(0xA54B0B10, Handle, WeaponHash, ammo); } // 0xA54B0B10
	static Any GET_MAX_AMMO(Ped ped, Hash WeapHash, int* ammo) { return invoke<Any>(0x0B294796, ped, WeapHash, ammo); } // 0x0B294796
	static void SET_PED_AMMO_BY_TYPE(Any p0, Any p1, Any p2) { invoke<Void>(0x311C52BB, p0, p1, p2); } // 0x311C52BB
	static Any GET_PED_AMMO_BY_TYPE(Any p0, Any p1) { return invoke<Any>(0x54077C4D, p0, p1); } // 0x54077C4D
	static void SET_PED_AMMO_TO_DROP(Any p0, Any p1) { invoke<Void>(0x2386A307, p0, p1); } // 0x2386A307
	static void _0xD6460EA2(Any p0) { invoke<Void>(0xD6460EA2, p0); } // 0xD6460EA2
	static Any _0x09337863(Any p0, Any p1) { return invoke<Any>(0x09337863, p0, p1); } // 0x09337863
	static Any GET_PED_LAST_WEAPON_IMPACT_COORD(Ped Handle, float* Coords) { return invoke<Any>(0x9B266079, Handle, Coords); } // 0x9B266079
	static void SET_PED_GADGET(Any p0, Any p1, Any p2) { invoke<Void>(0x8A256D0A, p0, p1, p2); } // 0x8A256D0A
	static Any _0x8DDD0B5B(Any p0, Any p1) { return invoke<Any>(0x8DDD0B5B, p0, p1); } // 0x8DDD0B5B
	static Any GET_SELECTED_PED_WEAPON(Any p0) { return invoke<Any>(0xD240123E, p0); } // 0xD240123E
	static void EXPLODE_PROJECTILES(Any p0, Any p1, Any p2) { invoke<Void>(0x35A0B955, p0, p1, p2); } // 0x35A0B955
	static void REMOVE_ALL_PROJECTILES_OF_TYPE(Any p0, Any p1) { invoke<Void>(0xA5F89919, p0, p1); } // 0xA5F89919
	static Any _0x3612110D(Any p0) { return invoke<Any>(0x3612110D, p0); } // 0x3612110D
	static Any _0xB2B2BBAA(Any p0) { return invoke<Any>(0xB2B2BBAA, p0); } // 0xB2B2BBAA
	static BOOL HAS_VEHICLE_GOT_PROJECTILE_ATTACHED(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0xA57E2E80, p0, p1, p2, p3); } // 0xA57E2E80
	static void GIVE_WEAPON_COMPONENT_TO_PED(Any p0, Any p1, Any p2) { invoke<Void>(0x3E1E286D, p0, p1, p2); } // 0x3E1E286D
	static void REMOVE_WEAPON_COMPONENT_FROM_PED(Any p0, Any p1, Any p2) { invoke<Void>(0x412AA00D, p0, p1, p2); } // 0x412AA00D
	static BOOL HAS_PED_GOT_WEAPON_COMPONENT(Any p0, Any p1, Any p2) { return invoke<BOOL>(0xDC0FC145, p0, p1, p2); } // 0xDC0FC145
	static BOOL IS_PED_WEAPON_COMPONENT_ACTIVE(Any p0, Any p1, Any p2) { return invoke<BOOL>(0x7565FB19, p0, p1, p2); } // 0x7565FB19
	static Any _0x82EEAF0F(Any p0) { return invoke<Any>(0x82EEAF0F, p0); } // 0x82EEAF0F
	static Any MAKE_PED_RELOAD(Any p0) { return invoke<Any>(0x515292C2, p0); } // 0x515292C2
	static void REQUEST_WEAPON_ASSET(Any p0, Any p1, Any p2) { invoke<Void>(0x65D139A5, p0, p1, p2); } // 0x65D139A5
	static BOOL HAS_WEAPON_ASSET_LOADED(Any p0) { return invoke<BOOL>(0x1891D5BB, p0); } // 0x1891D5BB
	static void REMOVE_WEAPON_ASSET(Any p0) { invoke<Void>(0x2C0DFE3C, p0); } // 0x2C0DFE3C
	static Any CREATE_WEAPON_OBJECT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0x62F5987F, p0, p1, p2, p3, p4, p5, p6); } // 0x62F5987F
	static void GIVE_WEAPON_COMPONENT_TO_WEAPON_OBJECT(Any p0, Any p1) { invoke<Void>(0xF7612A37, p0, p1); } // 0xF7612A37
	static void REMOVE_WEAPON_COMPONENT_FROM_WEAPON_OBJECT(Any p0, Any p1) { invoke<Void>(0xA6E7ED3C, p0, p1); } // 0xA6E7ED3C
	static BOOL HAS_WEAPON_GOT_WEAPON_COMPONENT(Any p0, Any p1) { return invoke<BOOL>(0x1D368510, p0, p1); } // 0x1D368510
	static void GIVE_WEAPON_OBJECT_TO_PED(Any p0, Any p1) { invoke<Void>(0x639AF3EF, p0, p1); } // 0x639AF3EF
	static Any _0xB1817BAA(Any p0, Any p1) { return invoke<Any>(0xB1817BAA, p0, p1); } // 0xB1817BAA
	static Any GET_WEAPON_OBJECT_FROM_PED(Any p0) { return invoke<Any>(0xDF939A38, p0); } // 0xDF939A38
	static void SET_PED_WEAPON_TINT_INDEX(Ped PedHandle, Hash WeaponHash, int ColorIndex) { invoke<Void>(0xEB2A7B23, PedHandle, WeaponHash, ColorIndex); } // 0xEB2A7B23
	static Any GET_PED_WEAPON_TINT_INDEX(Any p0, Any p1) { return invoke<Any>(0x3F9C90A7, p0, p1); } // 0x3F9C90A7
	static void SET_WEAPON_OBJECT_TINT_INDEX(Any p0, Any p1) { invoke<Void>(0x44ACC1DA, p0, p1); } // 0x44ACC1DA
	static Any GET_WEAPON_OBJECT_TINT_INDEX(Any p0) { return invoke<Any>(0xD91D9576, p0); } // 0xD91D9576
	static Any GET_WEAPON_TINT_COUNT(Any p0) { return invoke<Any>(0x99E4EAAB, p0); } // 0x99E4EAAB
	static Any GET_WEAPON_HUD_STATS(Any p0, Any p1) { return invoke<Any>(0xA9AD3D98, p0, p1); } // 0xA9AD3D98
	static Any GET_WEAPON_COMPONENT_HUD_STATS(Any p0, Any p1) { return invoke<Any>(0xBB5498F4, p0, p1); } // 0xBB5498F4
	static Any GET_WEAPON_CLIP_SIZE(Any p0) { return invoke<Any>(0x8D515E66, p0); } // 0x8D515E66
	static void _0xB4F44C6E(Any p0, Any p1, Any p2) { invoke<Void>(0xB4F44C6E, p0, p1, p2); } // 0xB4F44C6E
	static Any _0xEC2E5304(Any p0, Any p1) { return invoke<Any>(0xEC2E5304, p0, p1); } // 0xEC2E5304
	static void _0xE3BD00F9(Any p0) { invoke<Void>(0xE3BD00F9, p0); } // 0xE3BD00F9
	static Any _0xBAF7BFBE(Any p0) { return invoke<Any>(0xBAF7BFBE, p0); } // 0xBAF7BFBE
	static Any SET_WEAPON_SMOKEGRENADE_ASSIGNED(Any p0) { return invoke<Any>(0x76876154, p0); } // 0x76876154
	static Any _0xB0127EA7(Any p0) { return invoke<Any>(0xB0127EA7, p0); } // 0xB0127EA7
	static void SET_WEAPON_ANIMATION_OVERRIDE(Any p0, Any p1) { invoke<Void>(0xA5DF7484, p0, p1); } // 0xA5DF7484
	static Any GET_WEAPON_DAMAGE_TYPE(Any p0) { return invoke<Any>(0x013AFC13, p0); } // 0x013AFC13
	static void _0x64646F1D(Any p0) { invoke<Void>(0x64646F1D, p0); } // 0x64646F1D
	static Any _0x135E7AD4(Any p0) { return invoke<Any>(0x135E7AD4, p0); } // 0x135E7AD4
}

namespace ITEMSET
{
	static Any CREATE_ITEMSET(Any p0) { return invoke<Any>(0x0A113B2C, p0); } // 0x0A113B2C
	static void DESTROY_ITEMSET(Any p0) { invoke<Void>(0x83CE1A4C, p0); } // 0x83CE1A4C
	static BOOL IS_ITEMSET_VALID(Any p0) { return invoke<BOOL>(0xD201FC29, p0); } // 0xD201FC29
	static Any ADD_TO_ITEMSET(Any p0, Any p1) { return invoke<Any>(0x6B0FE61B, p0, p1); } // 0x6B0FE61B
	static void REMOVE_FROM_ITEMSET(Any p0, Any p1) { invoke<Void>(0xA9565228, p0, p1); } // 0xA9565228
	static Any GET_ITEMSET_SIZE(Any p0) { return invoke<Any>(0x2B31F41A, p0); } // 0x2B31F41A
	static Any GET_INDEXED_ITEM_IN_ITEMSET(Any p0, Any p1) { return invoke<Any>(0x3F712874, p0, p1); } // 0x3F712874
	static BOOL IS_IN_ITEMSET(Any p0, Any p1) { return invoke<BOOL>(0x0D4B9730, p0, p1); } // 0x0D4B9730
	static void CLEAN_ITEMSET(Any p0) { invoke<Void>(0x919A4858, p0); } // 0x919A4858
}

namespace STREAMING
{
	static void LOAD_ALL_OBJECTS_NOW() { invoke<Void>(0xC9DBDA90); } // 0xC9DBDA90
	static void LOAD_SCENE(float p0, float p1, float p2) { invoke<Void>(0xB72403F5, p0, p1, p2); } // 0xB72403F5
	static Any NETWORK_UPDATE_LOAD_SCENE() { return invoke<Any>(0xC76E023C); } // 0xC76E023C
	static void NETWORK_STOP_LOAD_SCENE() { invoke<Void>(0x24857907); } // 0x24857907
	static BOOL IS_NETWORK_LOADING_SCENE() { return invoke<BOOL>(0x6DCFC021); } // 0x6DCFC021
	static void SET_INTERIOR_ACTIVE(Any p0, Any p1) { invoke<Void>(0xE1013910, p0, p1); } // 0xE1013910
	static void REQUEST_MODEL(Hash model) { invoke<Void>(0xFFF1B500, model); } // 0xFFF1B500
	static void _0x48CEB6B4(Any p0) { invoke<Void>(0x48CEB6B4, p0); } // 0x48CEB6B4
	static BOOL HAS_MODEL_LOADED(Hash model) { return invoke<BOOL>(0x62BFDB37, model); } // 0x62BFDB37
	static void _0x939243FB(Any p0, Any p1) { invoke<Void>(0x939243FB, p0, p1); } // 0x939243FB
	static void SET_MODEL_AS_NO_LONGER_NEEDED(Hash Model) { invoke<Void>(0xAE0F069E, Model); } // 0xAE0F069E
	static BOOL IS_MODEL_IN_CDIMAGE(Any p0) { return invoke<BOOL>(0x1094782F, p0); } // 0x1094782F
	static BOOL IS_MODEL_VALID(Any p0) { return invoke<BOOL>(0xAF8F8E9D, p0); } // 0xAF8F8E9D
	static BOOL IS_MODEL_A_VEHICLE(Any p0) { return invoke<BOOL>(0xFFFC85D4, p0); } // 0xFFFC85D4
	static void REQUEST_COLLISION_AT_COORD(float x, float y, float z) { invoke<Void>(0xCD9805E7, x, y, z); } // 0xCD9805E7
	static void REQUEST_COLLISION_FOR_MODEL(Hash vehicleHash) { invoke<Void>(0x3930C042, vehicleHash); } // 0x3930C042
	static BOOL HAS_COLLISION_FOR_MODEL_LOADED(Any p0) { return invoke<BOOL>(0x41A094F8, p0); } // 0x41A094F8
	static void REQUEST_ADDITIONAL_COLLISION_AT_COORD(Any p0, Any p1, Any p2) { invoke<Void>(0xC2CC1DF2, p0, p1, p2); } // 0xC2CC1DF2
	static Any _0xCD31C872(Any p0) { return invoke<Any>(0xCD31C872, p0); } // 0xCD31C872
	static void REQUEST_ANIM_DICT(char* AminSet) { invoke<Void>(0xDCA96950, AminSet); } // 0xDCA96950
	static BOOL HAS_ANIM_DICT_LOADED(char* AminSet) { return invoke<BOOL>(0x05E6763C, AminSet); } // 0x05E6763C
	static void REMOVE_ANIM_DICT(Any p0) { invoke<Void>(0x0AE050B5, p0); } // 0x0AE050B5
	static void REQUEST_ANIM_SET(Any p0) { invoke<Void>(0x2988B3FC, p0); } // 0x2988B3FC
	static BOOL HAS_ANIM_SET_LOADED(Any p0) { return invoke<BOOL>(0x4FFF397D, p0); } // 0x4FFF397D
	static void REMOVE_ANIM_SET(Any p0) { invoke<Void>(0xD04A817A, p0); } // 0xD04A817A
	static void REQUEST_CLIP_SET(char* p0) { invoke<Void>(0x546C627A, p0); } // 0x546C627A
	static BOOL HAS_CLIP_SET_LOADED(char* p0) { return invoke<BOOL>(0x230D5455, p0); } // 0x230D5455
	static void REMOVE_CLIP_SET(char* p0) { invoke<Void>(0x1E21F7AA, p0); } // 0x1E21F7AA
	static void REQUEST_IPL(char* iplName) { invoke<Void>(0x3B70D1DB, iplName); } // 0x3B70D1DB
	static void REMOVE_IPL(char* iplName) { invoke<Void>(0xDF7CBD36, iplName); } // 0xDF7CBD36
	static BOOL IS_IPL_ACTIVE(char* iplName) { return invoke<BOOL>(0xB2C33714, iplName); } // 0xB2C33714
	static void SET_STREAMING(Any p0) { invoke<Void>(0x27EF6CB2, p0); } // 0x27EF6CB2
	static void SET_GAME_PAUSES_FOR_STREAMING(Any p0) { invoke<Void>(0x9211A28A, p0); } // 0x9211A28A
	static void SET_REDUCE_PED_MODEL_BUDGET(Any p0) { invoke<Void>(0xAFCB2B86, p0); } // 0xAFCB2B86
	static void SET_REDUCE_VEHICLE_MODEL_BUDGET(Any p0) { invoke<Void>(0xCDB4FB7E, p0); } // 0xCDB4FB7E
	static void SET_DITCH_POLICE_MODELS(Any p0) { invoke<Void>(0x3EA7FCE4, p0); } // 0x3EA7FCE4
	static Any GET_NUMBER_OF_STREAMING_REQUESTS() { return invoke<Any>(0xC2EE9A02); } // 0xC2EE9A02
	static void REQUEST_PTFX_ASSET() { invoke<Void>(0x2C649263); } // 0x2C649263
	static BOOL HAS_PTFX_ASSET_LOADED() { return invoke<BOOL>(0x3EFF96BE); } // 0x3EFF96BE
	static void REMOVE_PTFX_ASSET() { invoke<Void>(0xC10F178C); } // 0xC10F178C
	static void _REQUEST_DLC_PTFX_ASSET(char* FX) { invoke<Void>(0xCFEA19A9, FX); } // 0xCFEA19A9
	static Any _HAS_DLC_PTFX_LOADED(char* FX) { return invoke<Any>(0x9ACC6446, FX); } // 0x9ACC6446
	static void _REMOVE_DLC_PTFX_ASSET(char* FX) { invoke<Void>(0xC44762A1, FX); } // 0xC44762A1
	static void SET_VEHICLE_POPULATION_BUDGET(Any p0) { invoke<Void>(0x1D56993C, p0); } // 0x1D56993C
	static void SET_PED_POPULATION_BUDGET(Any p0) { invoke<Void>(0xD2D026CD, p0); } // 0xD2D026CD
	static void CLEAR_FOCUS() { invoke<Void>(0x34D91E7A); } // 0x34D91E7A
	static void _0x14680A60(float p0, float p1, float p2, float p3, float p4, float p5) { invoke<Void>(0x14680A60, p0, p1, p2, p3, p4, p5); } // 0x14680A60
	static void SET_FOCUS_ENTITY(Any p0) { invoke<Void>(0x18DB04AC, p0); } // 0x18DB04AC
	static BOOL IS_ENTITY_FOCUS(Any p0) { return invoke<BOOL>(0xB456D707, p0); } // 0xB456D707
	static void _0x403CD434(Any p0, Any p1) { invoke<Void>(0x403CD434, p0, p1); } // 0x403CD434
	static void _0xA07BAEB9(Any p0) { invoke<Void>(0xA07BAEB9, p0); } // 0xA07BAEB9
	static Any _0x10B6AB36(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x10B6AB36, p0, p1, p2, p3, p4, p5); } // 0x10B6AB36
	static Any _0x72344191(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<Any>(0x72344191, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x72344191
	static Any _0xC0157255(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0xC0157255, p0, p1, p2, p3, p4, p5, p6); } // 0xC0157255
	static void _0xE80F8ABE(Any p0) { invoke<Void>(0xE80F8ABE, p0); } // 0xE80F8ABE
	static Any _0x1B3521F4(Any p0) { return invoke<Any>(0x1B3521F4, p0); } // 0x1B3521F4
	static Any _0x42CFE9C0(Any p0) { return invoke<Any>(0x42CFE9C0, p0); } // 0x42CFE9C0
	static Any _0x56253356() { return invoke<Any>(0x56253356); } // 0x56253356
	static Any NEW_LOAD_SCENE_START(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<Any>(0xDF9C38B6, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xDF9C38B6
	static Any _0xFA037FEB(float p0, float p1, float p2, float p3, Any p4) { return invoke<Any>(0xFA037FEB, p0, p1, p2, p3, p4); } // 0xFA037FEB
	static void NEW_LOAD_SCENE_STOP() { invoke<Void>(0x7C05B1F6); } // 0x7C05B1F6
	static BOOL IS_NEW_LOAD_SCENE_ACTIVE() { return invoke<BOOL>(0xAD234B7F); } // 0xAD234B7F
	static BOOL IS_NEW_LOAD_SCENE_LOADED() { return invoke<BOOL>(0x3ECD839F); } // 0x3ECD839F
	static Any _0xEAA51103() { return invoke<Any>(0xEAA51103); } // 0xEAA51103
	static void START_PLAYER_SWITCH(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x0829E975, p0, p1, p2, p3); } // 0x0829E975
	static void STOP_PLAYER_SWITCH() { invoke<Void>(0x2832C010); } // 0x2832C010
	static Any STOP_PLAYER_REMAIN_ARCADE() { return invoke<Any>(0x56135ACC); } // 0x56135ACC
	static Any GET_PLAYER_SWITCH_TYPE() { return invoke<Any>(0x280DC015); } // 0x280DC015
	static Any GET_IDEAL_PLAYER_SWITCH_TYPE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0xD5A450F1, p0, p1, p2, p3, p4, p5); } // 0xD5A450F1
	static Any GET_PLAYER_SWITCH_STATE() { return invoke<Any>(0x39A0E1F2); } // 0x39A0E1F2
	static Any GET_PLAYER_SHORT_SWITCH_STATE() { return invoke<Any>(0x9B7BA38F); } // 0x9B7BA38F
	static void _0xF0BD420D(Any p0) { invoke<Void>(0xF0BD420D, p0); } // 0xF0BD420D
	static Any _0x02BA7AC2() { return invoke<Any>(0x02BA7AC2); } // 0x02BA7AC2
	static void _0x47352E14(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0x47352E14, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x47352E14
	static void _0x279077B0(Any p0) { invoke<Void>(0x279077B0, p0); } // 0x279077B0
	static void _0x55CB21F9() { invoke<Void>(0x55CB21F9); } // 0x55CB21F9
	static void _0x1084F2F4() { invoke<Void>(0x1084F2F4); } // 0x1084F2F4
	static void _0x5B1E995D() { invoke<Void>(0x5B1E995D); } // 0x5B1E995D
	static void _0x4B4B9A13() { invoke<Void>(0x4B4B9A13); } // 0x4B4B9A13
	static Any _0x408F7148() { return invoke<Any>(0x408F7148); } // 0x408F7148
	static void _0xFB4D062D(Any p0, Any p1, Any p2) { invoke<Void>(0xFB4D062D, p0, p1, p2); } // 0xFB4D062D
	static void _0x2349373B(Any p0) { invoke<Void>(0x2349373B, p0); } // 0x2349373B
	static Any _0x74C16879() { return invoke<Any>(0x74C16879); } // 0x74C16879
	static Any SET_PLAYER_INVERTED_UP() { return invoke<Any>(0x569847E3); } // 0x569847E3
	static Any _0xC7A3D279() { return invoke<Any>(0xC7A3D279); } // 0xC7A3D279
	static Any DESTROY_PLAYER_IN_PAUSE_MENU() { return invoke<Any>(0x90F64284); } // 0x90F64284
	static Any _0x7154B6FD() { return invoke<Any>(0x7154B6FD); } // 0x7154B6FD
	static void _0xE5612C1A(Any p0) { invoke<Void>(0xE5612C1A, p0); } // 0xE5612C1A
	static void _0x9CD6A451(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x9CD6A451, p0, p1, p2, p3); } // 0x9CD6A451
	static void _0x4267DA87() { invoke<Void>(0x4267DA87); } // 0x4267DA87
	static void _0x9FA4AF99(Any p0) { invoke<Void>(0x9FA4AF99, p0); } // 0x9FA4AF99
	static void _0x9EF0A9CF(Any p0, Any p1) { invoke<Void>(0x9EF0A9CF, p0, p1); } // 0x9EF0A9CF
	static void _0xF2CDD6A8() { invoke<Void>(0xF2CDD6A8); } // 0xF2CDD6A8
	static Any _0x17B0A1CD() { return invoke<Any>(0x17B0A1CD); } // 0x17B0A1CD
	static void _0x3DA7AA5D() { invoke<Void>(0x3DA7AA5D); } // 0x3DA7AA5D
	static Any _0xDAB4BAC0() { return invoke<Any>(0xDAB4BAC0); } // 0xDAB4BAC0
	static void PREFETCH_SRL(Any p0) { invoke<Void>(0x37BE2FBB, p0); } // 0x37BE2FBB
	static BOOL IS_SRL_LOADED() { return invoke<BOOL>(0x670FA2A6); } // 0x670FA2A6
	static void BEGIN_SRL() { invoke<Void>(0x24F49427); } // 0x24F49427
	static void END_SRL() { invoke<Void>(0x1977C56A); } // 0x1977C56A
	static void SET_SRL_TIME(Any p0) { invoke<Void>(0x30F8A487, p0); } // 0x30F8A487
	static void _0x814D0752(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x814D0752, p0, p1, p2, p3, p4, p5); } // 0x814D0752
	static void _0x62F02485(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x62F02485, p0, p1, p2, p3); } // 0x62F02485
	static void _0xA6459CAA(Any p0) { invoke<Void>(0xA6459CAA, p0); } // 0xA6459CAA
	static void _0xF8F515E4(Any p0) { invoke<Void>(0xF8F515E4, p0); } // 0xF8F515E4
	static void SET_HD_AREA(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x80BAA035, p0, p1, p2, p3); } // 0x80BAA035
	static void CLEAR_HD_AREA() { invoke<Void>(0x7CAC6FA0); } // 0x7CAC6FA0
	static void _0xE243B2AF() { invoke<Void>(0xE243B2AF); } // 0xE243B2AF
	static void _0x897A510F() { invoke<Void>(0x897A510F); } // 0x897A510F
	static Any _0xC0E83320(Any p0) { return invoke<Any>(0xC0E83320, p0); } // 0xC0E83320
	static void _0x1C576388(Any p0) { invoke<Void>(0x1C576388, p0); } // 0x1C576388
	static Any _0x3E9C4CBE() { return invoke<Any>(0x3E9C4CBE); } // 0x3E9C4CBE
}

namespace SCRIPT
{
	static void REQUEST_SCRIPT(char* ScriptName) { invoke<Void>(0xE26B2666, ScriptName); } // 0xE26B2666
	static void SET_SCRIPT_AS_NO_LONGER_NEEDED(char* ScriptName) { invoke<Void>(0x6FCB7795, ScriptName); } // 0x6FCB7795
	static BOOL HAS_SCRIPT_LOADED(char* ScriptName) { return invoke<BOOL>(0x5D67F751, ScriptName); } // 0x5D67F751
	static BOOL DOES_SCRIPT_EXIST(char* ScriptName) { return invoke<BOOL>(0xDEAB87AB, ScriptName); } // 0xDEAB87AB
	static void _0x1C68D9DC(Any p0) { invoke<Void>(0x1C68D9DC, p0); } // 0x1C68D9DC
	static void _0x96C26F66(Any p0) { invoke<Void>(0x96C26F66, p0); } // 0x96C26F66
	static Any _0x06674818(Any p0) { return invoke<Any>(0x06674818, p0); } // 0x06674818
	static void TERMINATE_THREAD(int ThreadID) { invoke<Void>(0x253FD520, ThreadID); } // 0x253FD520
	static BOOL IS_THREAD_ACTIVE(int ThreadID) { return invoke<BOOL>(0x78D7A5A0, ThreadID); } // 0x78D7A5A0
	static char* _GET_THREAD_NAME(int ThreadID) { return invoke<char*>(0xBE7ACD89, ThreadID); } // 0xBE7ACD89
	static void _0xBB4E2F66() { invoke<Void>(0xBB4E2F66); } // 0xBB4E2F66
	static Any _0x1E28B28F() { return invoke<Any>(0x1E28B28F); } // 0x1E28B28F
	static int GET_ID_OF_THIS_THREAD() { return invoke<int>(0xDE524830); } // 0xDE524830
	static void TERMINATE_THIS_THREAD() { invoke<Void>(0x3CD9CBB7); } // 0x3CD9CBB7
	static int _0x029D3841(Hash ScriptHash) { return invoke<int>(0x029D3841, ScriptHash); } // 0x029D3841
	static char* GET_THIS_SCRIPT_NAME() { return invoke<char*>(0xA40FD5D9); } // 0xA40FD5D9
	static Any _0x2BEE1F45() { return invoke<Any>(0x2BEE1F45); } // 0x2BEE1F45
	static Any GET_NUMBER_OF_EVENTS(Any p0) { return invoke<Any>(0xA3525D60, p0); } // 0xA3525D60
	static Any GET_EVENT_EXISTS(Any p0, Any p1) { return invoke<Any>(0xA1B447B5, p0, p1); } // 0xA1B447B5
	static Any GET_EVENT_AT_INDEX(Any p0, Any p1) { return invoke<Any>(0xB49C1442, p0, p1); } // 0xB49C1442
	static Any GET_EVENT_DATA(Any p0, Any p1, int* p2, Any p3) { return invoke<Any>(0x4280F92F, p0, p1, p2, p3); } // 0x4280F92F

	static void TRIGGER_SCRIPT_EVENT(int always1, ScriptArg *argsStruct, int argsStructCount, int playerbitset) { invoke<Void>(0x54763B35, always1, argsStruct, argsStructCount, playerbitset); } // 0x54763B35
	static void SHUTDOWN_LOADING_SCREEN() { invoke<Void>(0xA2826D17); } // 0xA2826D17
	static void SET_NO_LOADING_SCREEN(BOOL p0) { invoke<Void>(0xC8055034, p0); } // 0xC8055034
	static void _0xB03BCCDF() { invoke<Void>(0xB03BCCDF); } // 0xB03BCCDF
}

namespace UI
{
	static void _0xCB7C8994(char* p0) { invoke<Void>(0xCB7C8994, p0); } // 0xCB7C8994
	static void _0x903F5EE4(int p0) { invoke<Void>(0x903F5EE4, p0); } // 0x903F5EE4
	static void _0x94119534() { invoke<Void>(0x94119534); } // 0x94119534
	static void _0x71077FBD() { invoke<Void>(0x71077FBD); } // 0x71077FBD
	static Any _0xB8B3A5D0() { return invoke<Any>(0xB8B3A5D0); } // 0xB8B3A5D0
	static void _0xA7C8594B(Any p0) { invoke<Void>(0xA7C8594B, p0); } // 0xA7C8594B
	static void _0x1DA7E41A(Any p0) { invoke<Void>(0x1DA7E41A, p0); } // 0x1DA7E41A
	static void _0x1E63088A() { invoke<Void>(0x1E63088A); } // 0x1E63088A
	static void _0x5205C6F5() { invoke<Void>(0x5205C6F5); } // 0x5205C6F5
	static void _0xECA8ACB9(Any p0) { invoke<Void>(0xECA8ACB9, p0); } // 0xECA8ACB9
	static void _0x520FCB6D() { invoke<Void>(0x520FCB6D); } // 0x520FCB6D
	static void _0xC8BAB2F2() { invoke<Void>(0xC8BAB2F2); } // 0xC8BAB2F2
	static void _0x4D0449C6() { invoke<Void>(0x4D0449C6); } // 0x4D0449C6
	static void _0xD3F40140() { invoke<Void>(0xD3F40140); } // 0xD3F40140
	static Any _0xC5223796() { return invoke<Any>(0xC5223796); } // 0xC5223796
	static void _0x709B4BCB() { invoke<Void>(0x709B4BCB); } // 0x709B4BCB
	static void _0x4A4A40A4() { invoke<Void>(0x4A4A40A4); } // 0x4A4A40A4
	static Any _0x294405D4() { return invoke<Any>(0x294405D4); } // 0x294405D4
	static void _0xF881AB87() { invoke<Void>(0xF881AB87); } // 0xF881AB87
	static void _0x1D6859CA() { invoke<Void>(0x1D6859CA); } // 0x1D6859CA
	static void _0xCF14D7F2(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xCF14D7F2, p0, p1, p2, p3); } // 0xCF14D7F2
	static void _0x24A97AF8(Any p0) { invoke<Void>(0x24A97AF8, p0); } // 0x24A97AF8
	static void _0x44018EDB(Any p0) { invoke<Void>(0x44018EDB, p0); } // 0x44018EDB
	static void _0xA4524B23() { invoke<Void>(0xA4524B23); } // 0xA4524B23
	static void _0xAFA1148B() { invoke<Void>(0xAFA1148B); } // 0xAFA1148B
	static void _0x3CD4307C() { invoke<Void>(0x3CD4307C); } // 0x3CD4307C
	static void _0x574EE85C(char* type) { invoke<Void>(0x574EE85C, type); } // 0x574EE85C
	static Any _0xED130FA1(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0xED130FA1, p0, p1, p2, p3, p4, p5, p6); } // 0xED130FA1
	static int _SET_NOTIFICATION_MESSAGE(char *picName1, char *picName2, BOOL flash, int iconType, char *sender, char *subject) { return invoke<Any>(0xE7E3C98B, picName1, picName2, flash, iconType, sender, subject); } // 0xE7E3C98B
	static Any _0x0EB382B7(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0x0EB382B7, p0, p1, p2, p3, p4, p5, p6); } // 0x0EB382B7
	static Any _0x3E807FE3(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<Any>(0x3E807FE3, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x3E807FE3
	static Any _0xDEB491C8(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<Any>(0xDEB491C8, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xDEB491C8
	static int _DRAW_NOTIFICATION(BOOL blink, BOOL p1) { return invoke<int>(0x08F7AF78, blink, p1); } // 0x08F7AF78
	static Any _0x57B8D0D4(Any p0, Any p1) { return invoke<Any>(0x57B8D0D4, p0, p1); } // 0x57B8D0D4
	static Any _0x02BCAF9B(Any p0, Any p1) { return invoke<Any>(0x02BCAF9B, p0, p1); } // 0x02BCAF9B
	static Any _0x02DED2B8(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x02DED2B8, p0, p1, p2, p3, p4); } // 0x02DED2B8
	static Any _0xA9CCEF66(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<Any>(0xA9CCEF66, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xA9CCEF66
	static Any _0x88B9B909(Any p0, Any p1, int *p2, Any p3, Any p4, Any p5, networkClanMgr p6, char *p7, Any p8, Any p9, Any p10) { return invoke<Any>(0x88B9B909, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x88B9B909
	static Any _0xE05E7052(Any p0, Any p1, Any p2) { return invoke<Any>(0xE05E7052, p0, p1, p2); } // 0xE05E7052
	static Any _0x4FA43BA4(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x4FA43BA4, p0, p1, p2, p3); } // 0x4FA43BA4
	static Any _0x8C90D22F(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x8C90D22F, p0, p1, p2, p3, p4, p5); } // 0x8C90D22F
	static Any _0x8E319AB8(Any p0, Any p1) { return invoke<Any>(0x8E319AB8, p0, p1); } // 0x8E319AB8
	static Any _0x76FB0F21(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x76FB0F21, p0, p1, p2, p3); } // 0x76FB0F21
	static Any _0x5E93FBFA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x5E93FBFA, p0, p1, p2, p3, p4, p5); } // 0x5E93FBFA
	static void _0xF42C43C7(char* type) { invoke<Void>(0xF42C43C7, type); } // 0xF42C43C7
	static void _0x38F82261(int Time, int unk) { invoke<Void>(0x38F82261, Time, unk); } // 0x38F82261
	static void _0xDD524A11(Any p0) { invoke<Void>(0xDD524A11, p0); } // 0xDD524A11
	static Any _0x672EFB45() { return invoke<Any>(0x672EFB45); } // 0x672EFB45
	static void _SET_TEXT_ENTRY(char* text) { invoke<Void>(0x3E35563E, text); } // 0x3E35563E BEGIN_TEXT_COMMAND_DISPLAY_TEXT
	static void _DRAW_TEXT(float x, float y) { invoke<Void>(0x6F8350CE, x+globalAddX, y+globalAddY); } // 0x6F8350CE
	static void _0x51E7A037(char *p0) { invoke<Void>(0x51E7A037, p0); } // 0x51E7A037
	static float _0xD12A643A(Any p0) { return invoke<float>(0xD12A643A, p0); } // 0xD12A643A
	static void _SET_TEXT_GXT_ENTRY(char *p0) { invoke<Void>(0x94B82066, p0); } // 0x94B82066
	static Any _0xAA318785(Any p0, Any p1) { return invoke<Any>(0xAA318785, p0, p1); } // 0xAA318785
	static void _SET_TEXT_COMPONENT_FORMAT(char *p0) { invoke<Void>(0xB245FC10, p0); } // 0xB245FC10
	static void _0xB59B530D(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xB59B530D, p0, p1, p2, p3); } // 0xB59B530D
	static void _0x00E20F2D(Any p0) { invoke<Void>(0x00E20F2D, p0); } // 0x00E20F2D
	static Any _0xF63A13EC(Any p0) { return invoke<Any>(0xF63A13EC, p0); } // 0xF63A13EC
	static void _0xF4C211F6(Any p0) { invoke<Void>(0xF4C211F6, p0); } // 0xF4C211F6
	static void _0xE8E59820(Any p0) { invoke<Void>(0xE8E59820, p0); } // 0xE8E59820
	static void _0x0E103475(Any p0) { invoke<Void>(0x0E103475, p0); } // 0x0E103475
	static void _0x2944A6C5(Any p0) { invoke<Void>(0x2944A6C5, p0); } // 0x2944A6C5
	static void _0x550665AE(Any p0) { invoke<Void>(0x550665AE, p0); } // 0x550665AE
	static void _0x67785AF2() { invoke<Void>(0x67785AF2); } // 0x67785AF2
	static void _0xBF855650(Any p0) { invoke<Void>(0xBF855650, p0); } // 0xBF855650
	static void _0x6E7FDA1C(Any p0) { invoke<Void>(0x6E7FDA1C, p0); } // 0x6E7FDA1C
	static void ADD_TEXT_COMPONENT_INTEGER(int text) { invoke<Void>(0xFE272A57, text); } // 0xFE272A57
	static void ADD_TEXT_COMPONENT_FLOAT(float text, float DecimalPlaces) { invoke<Void>(0x24D78013, text, DecimalPlaces); } // 0x24D78013
	static void _ADD_TEXT_COMPONENT_ITEM_STRING(char *p0) { invoke<Void>(0xDCE05406, p0); } // 0xDCE05406
	static void _0x150E03B6(Any p0) { invoke<Void>(0x150E03B6, p0); } // 0x150E03B6
	static void _0x5DE98F0A(Any p0) { invoke<Void>(0x5DE98F0A, p0); } // 0x5DE98F0A
	static void _ADD_TEXT_COMPONENT_STRING(char* text) { invoke<Void>(/*(addrstruct().textData^dataDecryptor())*/0x27A244D8, text); } // 0x27A244D8
	static void ADD_TEXT_COMPONENT_SUBSTRING_TIME(Any p0, Any p1) { invoke<Void>(0x135B3CD0, p0, p1); } // 0x135B3CD0
	static void _0x12929BDF(Any p0, Any p1) { invoke<Void>(0x12929BDF, p0, p1); } // 0x12929BDF
	static void _0x65E1D404(Any p0, Any p1) { invoke<Void>(0x65E1D404, p0, p1); } // 0x65E1D404
	static void _ADD_TEXT_COMPONENT_STRING2(char* text) { invoke<Void>(0xC736999E, text); } // 0xC736999E
	static void _ADD_TEXT_COMPONENT_STRING3(char* text) { invoke<Void>(0x0829A799, text); } // 0x0829A799
	static void _0x6F1A1901(Any p0) { invoke<Void>(0x6F1A1901, p0); } // 0x6F1A1901
	static char *_0x34A396EE(char *text, int position, int length) { return invoke<char *>(0x34A396EE, text, position, length); } // 0x34A396EE
	static Any _0x0183A66C(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x0183A66C, p0, p1, p2, p3); } // 0x0183A66C
	static Any _0xFA6373BB(Any p0, Any p1, Any p2) { return invoke<Any>(0xFA6373BB, p0, p1, p2); } // 0xFA6373BB
	static char * _0x95C4B5AD(char * p0) { return invoke<char *>(0x95C4B5AD, p0); } // 0x95C4B5AD
	static void CLEAR_PRINTS() { invoke<Void>(0x216CB1C5); } // 0x216CB1C5
	static void CLEAR_BRIEF() { invoke<Void>(0x9F75A929); } // 0x9F75A929
	static void CLEAR_ALL_HELP_MESSAGES() { invoke<Void>(0x9E5D9198); } // 0x9E5D9198
	static void CLEAR_THIS_PRINT(Any p0) { invoke<Void>(0x06878327, p0); } // 0x06878327
	static void CLEAR_SMALL_PRINTS() { invoke<Void>(0xA869A238); } // 0xA869A238
	static BOOL DOES_TEXT_BLOCK_EXIST(Any p0) { return invoke<BOOL>(0x96F74838, p0); } // 0x96F74838
	static void REQUEST_ADDITIONAL_TEXT(char *gxt, int slot) { invoke<Void>(0x9FA9175B, gxt, slot); } // 0x9FA9175B
	static void _0xF4D27EBE(Any p0, Any p1) { invoke<Void>(0xF4D27EBE, p0, p1); } // 0xF4D27EBE
	static BOOL HAS_ADDITIONAL_TEXT_LOADED(Any p0) { return invoke<BOOL>(0xB0E56045, p0); } // 0xB0E56045
	static void CLEAR_ADDITIONAL_TEXT(Any p0, Any p1) { invoke<Void>(0x518141E0, p0, p1); } // 0x518141E0
	static BOOL IS_STREAMING_ADDITIONAL_TEXT(Any p0) { return invoke<BOOL>(0xF079E4EB, p0); } // 0xF079E4EB
	static BOOL HAS_THIS_ADDITIONAL_TEXT_LOADED(Any p0, Any p1) { return invoke<BOOL>(0x80A52040, p0, p1); } // 0x80A52040
	static BOOL IS_MESSAGE_BEING_DISPLAYED() { return invoke<BOOL>(0x6A77FE8D); } // 0x6A77FE8D
	static BOOL DOES_TEXT_LABEL_EXIST(Any p0) { return invoke<BOOL>(0x6ECAE560, p0); } // 0x6ECAE560
	static Any GET_LENGTH_OF_STRING_WITH_THIS_TEXT_LABEL(Any p0) { return invoke<Any>(0xA4CA7BE5, p0); } // 0xA4CA7BE5
	static int GET_LENGTH_OF_LITERAL_STRING(char* string) { return invoke<int>(0x99379D55, string); } // 0x99379D55
	static Any _0x7DBC0764(Any p0) { return invoke<Any>(0x7DBC0764, p0); } // 0x7DBC0764
	static Any GET_STREET_NAME_FROM_HASH_KEY(Any p0) { return invoke<Any>(0x1E8E310C, p0); } // 0x1E8E310C
	static BOOL IS_HUD_PREFERENCE_SWITCHED_ON() { return invoke<BOOL>(0xC3BC1B4F); } // 0xC3BC1B4F
	static BOOL IS_RADAR_PREFERENCE_SWITCHED_ON() { return invoke<BOOL>(0x14AEAA28); } // 0x14AEAA28
	static BOOL IS_SUBTITLE_PREFERENCE_SWITCHED_ON() { return invoke<BOOL>(0x63BA19F5); } // 0x63BA19F5
	static void DISPLAY_HUD(BOOL Toggle) { invoke<Void>(0xD10E4E31, Toggle); } // 0xD10E4E31
	static void _0xC380AC85() { invoke<Void>(0xC380AC85); } // 0xC380AC85
	static void _0xC47AB1B0() { invoke<Void>(0xC47AB1B0); } // 0xC47AB1B0
	static void DISPLAY_RADAR(BOOL Toggle) { invoke<Void>(0x52816BD4, Toggle); } // 0x52816BD4
	static BOOL IS_HUD_HIDDEN() { return invoke<BOOL>(0x40BADA1D); } // 0x40BADA1D
	static BOOL IS_RADAR_HIDDEN() { return invoke<BOOL>(0x1AB3B954); } // 0x1AB3B954
	static void SET_BLIP_ROUTE(Object blip, int enabled) { invoke<Void>(0x3E160C90, blip, enabled); } // 0x3E160C90
	static void SET_BLIP_ROUTE_COLOUR(Any p0, Any p1) { invoke<Void>(0xDDE7C65C, p0, p1); } // 0xDDE7C65C
	static void ADD_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS(Any p0) { invoke<Void>(0xB58B25BD, p0); } // 0xB58B25BD
	static void _0x9854485F(Any p0) { invoke<Void>(0x9854485F, p0); } // 0x9854485F
	static void RESPONDING_AS_TEMP(Any p0) { invoke<Void>(0xDCA3F423, p0); } // 0xDCA3F423
	static void SET_RADAR_ZOOM(int p0) { invoke<Void>(0x2A50D1A6, p0); } // 0x2A50D1A6
	static void _0x25EC28C0(Any p0, Any p1) { invoke<Void>(0x25EC28C0, p0, p1); } // 0x25EC28C0
	static void _0x09CF1CE5(Any p0) { invoke<Void>(0x09CF1CE5, p0); } // 0x09CF1CE5
	static void _0xE8D3A910() { invoke<Void>(0xE8D3A910); } // 0xE8D3A910
	static void GET_HUD_COLOUR(int p0, int* p1, int* p2, int* p3, int* p4) { invoke<Void>(0x63F66A0B, p0, p1, p2, p3, p4); } // 0x63F66A0B
	static void _0x0E41E45C(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x0E41E45C, p0, p1, p2, p3); } // 0x0E41E45C
	static void _0x6BE3ACA8(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x6BE3ACA8, p0, p1, p2, p3); } // 0x6BE3ACA8
	static void _0x3B216749(Any p0, Any p1) { invoke<Void>(0x3B216749, p0, p1); } // 0x3B216749
	static void _0xF6E7E92B(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xF6E7E92B, p0, p1, p2, p3, p4); } // 0xF6E7E92B
	static void FLASH_ABILITY_BAR(Any p0) { invoke<Void>(0x3648960D, p0); } // 0x3648960D
	static void SET_ABILITY_BAR_VALUE(Any p0, Any p1) { invoke<Void>(0x24E53FD8, p0, p1); } // 0x24E53FD8
	static void FLASH_WANTED_DISPLAY(BOOL p0) { invoke<Void>(0x629F866B, p0); } // 0x629F866B
	static float _0x3330175B(float size, int font) { return invoke<float>(0x3330175B, size, font); } // 0x3330175B
	static void SET_TEXT_SCALE(float p0, float p1) { invoke<Void>(0xB6E15B23, p0, p1); } // 0xB6E15B23
	static void SET_TEXT_COLOUR(int R, int G, int B, int A) { invoke<Void>(0xE54DD2C8, R, G, B, A); } // 0xE54DD2C8
	static void SET_TEXT_CENTRE(Any p0) { invoke<Void>(0xE26D39A1, p0); } // 0xE26D39A1
	static void SET_TEXT_RIGHT_JUSTIFY(bool right) { invoke<Void>(0x45B60520, right); } // 0x45B60520
	static void _0x68CDFA60(Any p0) { invoke<Void>(0x68CDFA60, p0); } // 0x68CDFA60
	static void SET_TEXT_WRAP(float p0, float p1) { invoke<Void>(0x6F60AB54, p0+globalAddX, p1+globalAddY); } // 0x6F60AB54
	static void SET_TEXT_LEADING(Any p0) { invoke<Void>(0x98CE21D4, p0); } // 0x98CE21D4
	static void SET_TEXT_PROPORTIONAL(Any p0) { invoke<Void>(0xF49D8A08, p0); } // 0xF49D8A08
	static void SET_TEXT_FONT(Any p0) { invoke<Void>(0x80BC530D, p0); } // 0x80BC530D
	static void SET_TEXT_DROP_SHADOW() { invoke<Void>(0xE2A11511); } // 0xE2A11511
	static void SET_TEXT_DROPSHADOW(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xE6587517, p0, p1, p2, p3, p4); } // 0xE6587517
	static void SET_TEXT_OUTLINE() { invoke<Void>(0xC753412F); } // 0xC753412F
	static void SET_TEXT_EDGE(int p0, int p1, int p2, int p3, int p4) { invoke<Void>(0x3F1A5DAB, p0, p1, p2, p3, p4); } // 0x3F1A5DAB
	static void SET_TEXT_RENDER_ID(Any p0) { invoke<Void>(0xC5C3B7F3, p0); } // 0xC5C3B7F3
	static Any GET_DEFAULT_SCRIPT_RENDERTARGET_RENDER_ID() { return invoke<Any>(0x8188935F); } // 0x8188935F
	static Any REGISTER_NAMED_RENDERTARGET(Any p0, Any p1) { return invoke<Any>(0xFAE5D6F0, p0, p1); } // 0xFAE5D6F0
	static BOOL IS_NAMED_RENDERTARGET_REGISTERED(Any p0) { return invoke<BOOL>(0x284057F5, p0); } // 0x284057F5
	static Any RELEASE_NAMED_RENDERTARGET(Any p0) { return invoke<Any>(0xD3F6C892, p0); } // 0xD3F6C892
	static void LINK_NAMED_RENDERTARGET(Any p0) { invoke<Void>(0x6844C4B9, p0); } // 0x6844C4B9
	static Any GET_NAMED_RENDERTARGET_RENDER_ID(Any p0) { return invoke<Any>(0xF9D7A401, p0); } // 0xF9D7A401
	static BOOL IS_NAMED_RENDERTARGET_LINKED(Any p0) { return invoke<BOOL>(0x8B52601F, p0); } // 0x8B52601F
	static void CLEAR_HELP(int Enable) { invoke<Void>(0xE6D85741, Enable); } // 0xE6D85741
	static BOOL IS_HELP_MESSAGE_ON_SCREEN() { return invoke<BOOL>(0x4B3C9CA9); } // 0x4B3C9CA9
	static Any _0x812CBE0E() { return invoke<Any>(0x812CBE0E); } // 0x812CBE0E
	static BOOL IS_HELP_MESSAGE_BEING_DISPLAYED() { return invoke<BOOL>(0xA65F262A); } // 0xA65F262A
	static BOOL IS_HELP_MESSAGE_FADING_OUT() { return invoke<BOOL>(0x3E50AE92); } // 0x3E50AE92
	static Any _0x87871CE0() { return invoke<Any>(0x87871CE0); } // 0x87871CE0
	static Any _GET_BLIP_INFO_ID_ITERATOR() { return invoke<Any>(0xB9827942); } // 0xB9827942
	static Any GET_NUMBER_OF_ACTIVE_BLIPS() { return invoke<Any>(0x144020FA); } // 0x144020FA
	static Any GET_NEXT_BLIP_INFO_ID(Any p0) { return invoke<Any>(0x9356E92F, p0); } // 0x9356E92F
	static Any GET_FIRST_BLIP_INFO_ID(Any p0) { return invoke<Any>(0x64C0273D, p0); } // 0x64C0273D
	static Vector3 GET_BLIP_INFO_ID_COORD(Any p0) { return invoke<Vector3>(0xB7374A66, p0); } // 0xB7374A66
	static Any GET_BLIP_INFO_ID_DISPLAY(Any p0) { return invoke<Any>(0xD0FC19F4, p0); } // 0xD0FC19F4
	static Any GET_BLIP_INFO_ID_TYPE(Any p0) { return invoke<Any>(0x501D7B4E, p0); } // 0x501D7B4E
	static Any GET_BLIP_INFO_ID_ENTITY_INDEX(Any p0) { return invoke<Any>(0xA068C40B, p0); } // 0xA068C40B
	static Any GET_BLIP_INFO_ID_PICKUP_INDEX(Any p0) { return invoke<Any>(0x86913D37, p0); } // 0x86913D37
	static Object GET_BLIP_FROM_ENTITY(Entity entity) { return invoke<Object>(0x005A2A47, entity); } // 0x005A2A47
	static Any ADD_BLIP_FOR_RADIUS(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x4626756C, p0, p1, p2, p3); } // 0x4626756C
	static Any ADD_BLIP_FOR_ENTITY(Entity entity) { return invoke<Any>(0x30822554, entity); } // 0x30822554
	static Any ADD_BLIP_FOR_PICKUP(Any p0) { return invoke<Any>(0x16693C3A, p0); } // 0x16693C3A
	static Any ADD_BLIP_FOR_COORD(float x, float y, float z) { return invoke<Any>(0xC6F43D0E, x, y, z); } // 0xC6F43D0E
	static void _0xBF25E7B2(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xBF25E7B2, p0, p1, p2, p3, p4); } // 0xBF25E7B2
	static void _0xE7E1E32B(Any p0) { invoke<Void>(0xE7E1E32B, p0); } // 0xE7E1E32B
	static void SET_BLIP_COORDS(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x680A34D4, p0, p1, p2, p3); } // 0x680A34D4
	static Vector3 GET_BLIP_COORDS(Any p0) { return invoke<Vector3>(0xEF6FF47B, p0); } // 0xEF6FF47B
	static void SET_BLIP_SPRITE(Object blip, int spriteId) { invoke<Void>(0x8DBBB0B9, blip, spriteId); } // 0x8DBBB0B9
	static Any GET_BLIP_SPRITE(Any p0) { return invoke<Any>(0x72FF2E73, p0); } // 0x72FF2E73
	static void SET_BLIP_NAME_FROM_TEXT_FILE(int BlipID, char* blipname) { invoke<Void>(0xAC8A5461, BlipID, blipname); } // 0xAC8A5461
	static void SET_BLIP_NAME_TO_PLAYER_NAME(Any p0, Any p1) { invoke<Void>(0x03A0B8F9, p0, p1); } // 0x03A0B8F9
	static void SET_BLIP_ALPHA(Any p0, Any p1) { invoke<Void>(0xA791FCCD, p0, p1); } // 0xA791FCCD
	static Any GET_BLIP_ALPHA(Any p0) { return invoke<Any>(0x297AF6C8, p0); } // 0x297AF6C8
	static void SET_BLIP_FADE(Any p0, Any p1, Any p2) { invoke<Void>(0xA5999031, p0, p1, p2); } // 0xA5999031
	static void SET_BLIP_ROTATION(Any p0, Any p1) { invoke<Void>(0x6B8F44FE, p0, p1); } // 0x6B8F44FE
	static void SET_BLIP_FLASH_TIMER(Any p0, Any p1) { invoke<Void>(0x8D5DF611, p0, p1); } // 0x8D5DF611
	static void SET_BLIP_FLASH_INTERVAL(Any p0, Any p1) { invoke<Void>(0xEAF67377, p0, p1); } // 0xEAF67377
	static void SET_BLIP_COLOUR(int BlipID, int Color) { invoke<Void>(0xBB3C5A41, BlipID, Color); } // 0xBB3C5A41
	static void SET_BLIP_SECONDARY_COLOUR(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xC6384D32, p0, p1, p2, p3); } // 0xC6384D32
	static Any GET_BLIP_COLOUR(Any p0) { return invoke<Any>(0xDD6A1E54, p0); } // 0xDD6A1E54
	static Any GET_BLIP_HUD_COLOUR(Any p0) { return invoke<Any>(0xE88B4BC2, p0); } // 0xE88B4BC2
	static BOOL IS_BLIP_SHORT_RANGE(Any p0) { return invoke<BOOL>(0x1226765A, p0); } // 0x1226765A
	static BOOL IS_BLIP_ON_MINIMAP(Any p0) { return invoke<BOOL>(0x258CBA3A, p0); } // 0x258CBA3A
	static Any _0x3E47F357(Any p0) { return invoke<Any>(0x3E47F357, p0); } // 0x3E47F357
	static void _0x43996428(Any p0, Any p1) { invoke<Void>(0x43996428, p0, p1); } // 0x43996428
	static void SET_BLIP_HIGH_DETAIL(Any p0, Any p1) { invoke<Void>(0xD5842BFF, p0, p1); } // 0xD5842BFF
	static void SET_BLIP_AS_MISSION_CREATOR_BLIP(Any p0, Any p1) { invoke<Void>(0x802FB686, p0, p1); } // 0x802FB686
	static BOOL IS_MISSION_CREATOR_BLIP(Any p0) { return invoke<BOOL>(0x24ACC4E9, p0); } // 0x24ACC4E9
	static Any DISABLE_BLIP_NAME_FOR_VAR() { return invoke<Any>(0xFFD7476C); } // 0xFFD7476C
	static Any _0xC5EB849A() { return invoke<Any>(0xC5EB849A); } // 0xC5EB849A
	static void _0xA2CAAB4F(Any p0) { invoke<Void>(0xA2CAAB4F, p0); } // 0xA2CAAB4F
	static void SET_BLIP_FLASHES(Any p0, Any p1) { invoke<Void>(0xC0047F15, p0, p1); } // 0xC0047F15
	static void SET_BLIP_FLASHES_ALTERNATE(int BlipID, BOOL p1) { invoke<Void>(0x1A81202B, BlipID, p1); } // 0x1A81202B
	static BOOL IS_BLIP_FLASHING(Any p0) { return invoke<BOOL>(0x52E111D7, p0); } // 0x52E111D7
	static void SET_BLIP_AS_SHORT_RANGE(Any p0, Any p1) { invoke<Void>(0x5C67725E, p0, p1); } // 0x5C67725E
	static void SET_BLIP_SCALE(int BlipID, float Scale) { invoke<Void>(0x1E6EC434, BlipID, Scale); } // 0x1E6EC434
	static void SET_BLIP_PRIORITY(Any p0, Any p1) { invoke<Void>(0xCE87DA6F, p0, p1); } // 0xCE87DA6F
	static void SET_BLIP_DISPLAY(Object blip, Any p1) { invoke<Void>(0x2B521F91, blip, p1); } // 0x2B521F91
	static void SET_BLIP_CATEGORY(Any p0, Any p1) { invoke<Void>(0xEF72F533, p0, p1); } // 0xEF72F533
	static void REMOVE_BLIP(int BlipID) { invoke<Void>(0xD8C3C1CD, BlipID); } // 0xD8C3C1CD
	static void SET_BLIP_AS_FRIENDLY(int BlipID, BOOL toggle) { invoke<Void>(0xF290CFD8, BlipID, toggle); } // 0xF290CFD8
	static void PULSE_BLIP(Any p0) { invoke<Void>(0x44253855, p0); } // 0x44253855
	static void SHOW_NUMBER_ON_BLIP(Any p0, Any p1) { invoke<Void>(0x7BFC66C6, p0, p1); } // 0x7BFC66C6
	static void HIDE_NUMBER_ON_BLIP(Any p0) { invoke<Void>(0x0B6D610D, p0); } // 0x0B6D610D
	static void _0x1D99F676(Any p0, Any p1) { invoke<Void>(0x1D99F676, p0, p1); } // 0x1D99F676
	static void _0x3DCF0092(Any p0, Any p1) { invoke<Void>(0x3DCF0092, p0, p1); } // 0x3DCF0092
	static void _0xD1C3D71B(Any p0, Any p1) { invoke<Void>(0xD1C3D71B, p0, p1); } // 0xD1C3D71B
	static void _0x8DE82C15(Any p0, Any p1) { invoke<Void>(0x8DE82C15, p0, p1); } // 0x8DE82C15
	static void _0x4C8F02B4(Any p0, Any p1) { invoke<Void>(0x4C8F02B4, p0, p1); } // 0x4C8F02B4
	static void _0xABBE1E45(Any p0, Any p1) { invoke<Void>(0xABBE1E45, p0, p1); } // 0xABBE1E45
	static void _0x6AA6A1CC(Any p0, Any p1) { invoke<Void>(0x6AA6A1CC, p0, p1); } // 0x6AA6A1CC
	static void _0xC575F0BC(Any p0, Any p1) { invoke<Void>(0xC575F0BC, p0, p1); } // 0xC575F0BC
	static void _0x40E25DB8(Any p0, Any p1) { invoke<Void>(0x40E25DB8, p0, p1); } // 0x40E25DB8
	static BOOL DOES_BLIP_EXIST(Any p0) { return invoke<BOOL>(0xAE92DD96, p0); } // 0xAE92DD96
	static void SET_WAYPOINT_OFF() { invoke<Void>(0xB3496E1B); } // 0xB3496E1B
	static void _0x62BABF2C() { invoke<Void>(0x62BABF2C); } // 0x62BABF2C
	static void REFRESH_WAYPOINT() { invoke<Void>(0xB395D753); } // 0xB395D753
	static BOOL IS_WAYPOINT_ACTIVE() { return invoke<BOOL>(0x5E4DF47B); } // 0x5E4DF47B
	static void SET_NEW_WAYPOINT(Any p0, Any p1) { invoke<Void>(0x8444E1F0, p0, p1); } // 0x8444E1F0
	static void SET_BLIP_BRIGHT(Any p0, Any p1) { invoke<Void>(0x72BEE6DF, p0, p1); } // 0x72BEE6DF
	static void SET_BLIP_SHOW_CONE(Any p0, Any p1) { invoke<Void>(0xFF545AD8, p0, p1); } // 0xFF545AD8
	static void _0x41B0D022(Any p0) { invoke<Void>(0x41B0D022, p0); } // 0x41B0D022
	static Any SET_MINIMAP_COMPONENT(Any p0, Any p1) { return invoke<Any>(0x419DCDC4, p0, p1); } // 0x419DCDC4
	static Any GET_MAIN_PLAYER_BLIP_ID() { return invoke<Any>(0xAB93F020); } // 0xAB93F020
	static void HIDE_LOADING_ON_FADE_THIS_FRAME() { invoke<Void>(0x35087963); } // 0x35087963
	static void SET_RADAR_AS_INTERIOR_THIS_FRAME(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x6F2626E1, p0, p1, p2, p3, p4); } // 0x6F2626E1
	static void SET_RADAR_AS_EXTERIOR_THIS_FRAME() { invoke<Void>(0x39ABB10E); } // 0x39ABB10E
	static void _0x54E75C7D(Any p0, Any p1) { invoke<Void>(0x54E75C7D, p0, p1); } // 0x54E75C7D
	static Any _0x199DED14() { return invoke<Any>(0x199DED14); } // 0x199DED14
	static void _0x1A4318F7() { invoke<Void>(0x1A4318F7); } // 0x1A4318F7
	static void _0xCE36E3FE() { invoke<Void>(0xCE36E3FE); } // 0xCE36E3FE
	static void _0x334EFD46() { invoke<Void>(0x334EFD46); } // 0x334EFD46
	static void SET_WIDESCREEN_FORMAT(Any p0) { invoke<Void>(0xF016E08F, p0); } // 0xF016E08F
	static void DISPLAY_AREA_NAME(Any p0) { invoke<Void>(0x489FDD41, p0); } // 0x489FDD41
	static void DISPLAY_CASH(Any p0) { invoke<Void>(0x0049DF83, p0); } // 0x0049DF83
	static void DISPLAY_AMMO_THIS_FRAME(Any p0) { invoke<Void>(0x60693CEE, p0); } // 0x60693CEE
	static void DISPLAY_SNIPER_SCOPE_THIS_FRAME() { invoke<Void>(0xBC6C73CB); } // 0xBC6C73CB
	static void HIDE_HUD_AND_RADAR_THIS_FRAME() { invoke<Void>(0xB75D4AD2); } // 0xB75D4AD2
	static void _0x5476B9FD(Any p0) { invoke<Void>(0x5476B9FD, p0); } // 0x5476B9FD
	static void _0xF4F3C796() { invoke<Void>(0xF4F3C796); } // 0xF4F3C796
	static void _0x7BFFE82F() { invoke<Void>(0x7BFFE82F); } // 0x7BFFE82F
	static void SET_MULTIPLAYER_BANK_CASH() { invoke<Void>(0x2C842D03); } // 0x2C842D03
	static void REMOVE_MULTIPLAYER_BANK_CASH() { invoke<Void>(0x728B4EF4); } // 0x728B4EF4
	static void SET_MULTIPLAYER_HUD_CASH(Any p0, Any p1) { invoke<Void>(0xA8DB435E, p0, p1); } // 0xA8DB435E
	static void REMOVE_MULTIPLAYER_HUD_CASH() { invoke<Void>(0x07BF4A7D); } // 0x07BF4A7D
	static void HIDE_HELP_TEXT_THIS_FRAME() { invoke<Void>(0xF3807BED); } // 0xF3807BED
	static void DISPLAY_HELP_TEXT_THIS_FRAME(char *p0, Any p1) { invoke<Void>(0x18E3360A, p0, p1); } // 0x18E3360A
	static void _0x1EFFB02A(BOOL forcedShow) { invoke<Void>(0x1EFFB02A, forcedShow); } // 0x1EFFB02A
	static void _0xB26FED2B() { invoke<Void>(0xB26FED2B); } // 0xB26FED2B
	static Any _0x22E9F555() { return invoke<Any>(0x22E9F555); } // 0x22E9F555
	static void _0x83B608A0(Any p0) { invoke<Void>(0x83B608A0, p0); } // 0x83B608A0
	static void _0xE70D1F43(Any p0) { invoke<Void>(0xE70D1F43, p0); } // 0xE70D1F43
	static void SET_GPS_FLAGS(Any p0, Any p1) { invoke<Void>(0x60539BAB, p0, p1); } // 0x60539BAB
	static void CLEAR_GPS_FLAGS() { invoke<Void>(0x056AFCE6); } // 0x056AFCE6
	static void _0xFB9BABF5(Any p0) { invoke<Void>(0xFB9BABF5, p0); } // 0xFB9BABF5
	static void CLEAR_GPS_RACE_TRACK() { invoke<Void>(0x40C59829); } // 0x40C59829
	static void _0x7F93799B(Any p0, Any p1, Any p2) { invoke<Void>(0x7F93799B, p0, p1, p2); } // 0x7F93799B
	static void _0xEEBDFE55(Any p0, Any p1, Any p2) { invoke<Void>(0xEEBDFE55, p0, p1, p2); } // 0xEEBDFE55
	static void _0xDA0AF00E(Any p0, Any p1, Any p2) { invoke<Void>(0xDA0AF00E, p0, p1, p2); } // 0xDA0AF00E
	static void _0xCF2E3E24() { invoke<Void>(0xCF2E3E24); } // 0xCF2E3E24
	static void _0xC3DCBEDB(Any p0, Any p1, Any p2) { invoke<Void>(0xC3DCBEDB, p0, p1, p2); } // 0xC3DCBEDB
	static void _0xFE485135(Any p0, Any p1, Any p2) { invoke<Void>(0xFE485135, p0, p1, p2); } // 0xFE485135
	static void _0xE87CBE4C(Any p0) { invoke<Void>(0xE87CBE4C, p0); } // 0xE87CBE4C
	static void _0x0D9969E4() { invoke<Void>(0x0D9969E4); } // 0x0D9969E4
	static void CLEAR_GPS_PLAYER_WAYPOINT() { invoke<Void>(0x0B9C7FC2); } // 0x0B9C7FC2
	static void SET_GPS_FLASHES(Any p0) { invoke<Void>(0xE991F733, p0); } // 0xE991F733
	static void FLASH_MINIMAP_DISPLAY() { invoke<Void>(0xB8359952); } // 0xB8359952
	static void _0x79A6CAF6(Any p0) { invoke<Void>(0x79A6CAF6, p0); } // 0x79A6CAF6
	static void TOGGLE_STEALTH_RADAR(Any p0) { invoke<Void>(0xC68D47C4, p0); } // 0xC68D47C4
	static void KEY_HUD_COLOUR(Any p0, Any p1) { invoke<Void>(0xD5BFCADB, p0, p1); } // 0xD5BFCADB
	static void SET_MISSION_NAME(Any p0, Any p1) { invoke<Void>(0x68DCAE10, p0, p1); } // 0x68DCAE10
	static void _0x8D9A1734(Any p0, Any p1) { invoke<Void>(0x8D9A1734, p0, p1); } // 0x8D9A1734
	static void _0xD2161E77(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0xD2161E77, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xD2161E77
	static void SET_MINIMAP_BLOCK_WAYPOINT(Any p0) { invoke<Void>(0xA41C3B62, p0); } // 0xA41C3B62
	static void _0x02F5F1D1(Any p0) { invoke<Void>(0x02F5F1D1, p0); } // 0x02F5F1D1
	static void _0xD8D77733(Any p0) { invoke<Void>(0xD8D77733, p0); } // 0xD8D77733
	static Any _0xA4098ACC() { return invoke<Any>(0xA4098ACC); } // 0xA4098ACC
	static Any _0x65B705F6(Any p0, Any p1, Any p2) { return invoke<Any>(0x65B705F6, p0, p1, p2); } // 0x65B705F6
	static void _0xE010F081(Any p0, Any p1, Any p2) { invoke<Void>(0xE010F081, p0, p1, p2); } // 0xE010F081
	static void _0x5133A750(Any p0) { invoke<Void>(0x5133A750, p0); } // 0x5133A750
	static void _0x20FD3E87() { invoke<Void>(0x20FD3E87); } // 0x20FD3E87
	static void LOCK_MINIMAP_ANGLE(Any p0) { invoke<Void>(0xDEC733E4, p0); } // 0xDEC733E4
	static void UNLOCK_MINIMAP_ANGLE() { invoke<Void>(0x742043F9); } // 0x742043F9
	static void LOCK_MINIMAP_POSITION(Any p0, Any p1) { invoke<Void>(0xB9632A91, p0, p1); } // 0xB9632A91
	static void UNLOCK_MINIMAP_POSITION() { invoke<Void>(0x5E8E6F54); } // 0x5E8E6F54
	static void _0x0308EDF6(Any p0) { invoke<Void>(0x0308EDF6, p0); } // 0x0308EDF6
	static void _0x7FB6FB2A(Any p0, Any p1, Any p2) { invoke<Void>(0x7FB6FB2A, p0, p1, p2); } // 0x7FB6FB2A
	static void _0xF07D8CEF(Any p0) { invoke<Void>(0xF07D8CEF, p0); } // 0xF07D8CEF
	static void _0x827F14DE(Any p0) { invoke<Void>(0x827F14DE, p0); } // 0x827F14DE
	static void _0x08EB83D2(Any p0, Any p1) { invoke<Void>(0x08EB83D2, p0, p1); } // 0x08EB83D2
	static BOOL IS_HUD_COMPONENT_ACTIVE(int p0) { return invoke<BOOL>(0x6214631F, p0); } // 0x6214631F
	static BOOL IS_SCRIPTED_HUD_COMPONENT_ACTIVE(Any p0) { return invoke<BOOL>(0x2B86F382, p0); } // 0x2B86F382
	static void HIDE_SCRIPTED_HUD_COMPONENT_THIS_FRAME(Any p0) { invoke<Void>(0x31ABA127, p0); } // 0x31ABA127
	static Any _0xE8C8E535(Any p0) { return invoke<Any>(0xE8C8E535, p0); } // 0xE8C8E535
	static void HIDE_HUD_COMPONENT_THIS_FRAME(Any p0) { invoke<Void>(0xDB2D0762, p0); } // 0xDB2D0762
	static void SHOW_HUD_COMPONENT_THIS_FRAME(Any p0) { invoke<Void>(0x95E1546E, p0); } // 0x95E1546E
	static void _0x52746FE1() { invoke<Void>(0x52746FE1); } // 0x52746FE1
	static void RESET_RETICULE_VALUES() { invoke<Void>(0xBE27AA3F); } // 0xBE27AA3F
	static void RESET_HUD_COMPONENT_VALUES(Any p0) { invoke<Void>(0xD15B46DA, p0); } // 0xD15B46DA
	static void SET_HUD_COMPONENT_POSITION(Any p0, Any p1, Any p2) { invoke<Void>(0x2F3A0D15, p0, p1, p2); } // 0x2F3A0D15
	static Vector3 GET_HUD_COMPONENT_POSITION(Any p0) { return invoke<Vector3>(0x080DCED6, p0); } // 0x080DCED6
	static void _0x5BBCC934() { invoke<Void>(0x5BBCC934); } // 0x5BBCC934
	static Any _GET_SCREEN_COORD_FROM_WORLD_COORD(float p0, float p1, float p2, float *p3, float *p4) { return invoke<Any>(0xFE9A39F8, p0, p1, p2, p3, p4); } // 0xFE9A39F8
	static void _0x10DE5150() { invoke<Void>(0x10DE5150); } // 0x10DE5150
	static void _0x67649EE0() { invoke<Void>(0x67649EE0); } // 0x67649EE0
	static Any _0x9D2C94FA() { return invoke<Any>(0x9D2C94FA); } // 0x9D2C94FA
	static Any _0x45472FD5(Any p0) { return invoke<Any>(0x45472FD5, p0); } // 0x45472FD5
	static void _0x198F32D7(Any p0, Any p1, Any p2) { invoke<Void>(0x198F32D7, p0, p1, p2); } // 0x198F32D7
	static void _0x93045157(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x93045157, p0, p1, p2, p3); } // 0x93045157
	static void _0x18B012B7(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x18B012B7, p0, p1, p2, p3); } // 0x18B012B7
	static void _0x97852A82(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x97852A82, p0, p1, p2, p3, p4, p5); } // 0x97852A82
	static void CLEAR_FLOATING_HELP(Any p0, Any p1) { invoke<Void>(0xB181F88F, p0, p1); } // 0xB181F88F
	static void _0xC969F2D0(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0xC969F2D0, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xC969F2D0
	static Any _0xEFD2564A() { return invoke<Any>(0xEFD2564A); } // 0xEFD2564A
	static Any _0xF5CD2AA4(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0xF5CD2AA4, p0, p1, p2, p3, p4, p5); } // 0xF5CD2AA4
	static void _0x3D081FE4(Any p0) { invoke<Void>(0x3D081FE4, p0); } // 0x3D081FE4
	static Any _0x60118951(Any p0) { return invoke<Any>(0x60118951, p0); } // 0x60118951
	static Any ADD_TREVOR_RANDOM_MODIFIER(Any p0) { return invoke<Any>(0x63959059, p0); } // 0x63959059
	static void _0xD41DF479(Any p0, Any p1, Any p2) { invoke<Void>(0xD41DF479, p0, p1, p2); } // 0xD41DF479
	static void _0x767DED29(Any p0, Any p1) { invoke<Void>(0x767DED29, p0, p1); } // 0x767DED29
	static void _0xB01A5434(Any p0, Any p1) { invoke<Void>(0xB01A5434, p0, p1); } // 0xB01A5434
	static void _0x7E3AA40A(Any p0, Any p1, Any p2) { invoke<Void>(0x7E3AA40A, p0, p1, p2); } // 0x7E3AA40A
	static void _0x5777EC77(Any p0, Any p1) { invoke<Void>(0x5777EC77, p0, p1); } // 0x5777EC77
	static void _0xF4418611(Any p0, Any p1, Any p2) { invoke<Void>(0xF4418611, p0, p1, p2); } // 0xF4418611
	static void _0x0EBB003F(Any p0, Any p1) { invoke<Void>(0x0EBB003F, p0, p1); } // 0x0EBB003F
	static void _0x627A559B(Any p0, Any p1) { invoke<Void>(0x627A559B, p0, p1); } // 0x627A559B
	static Any _0xF11414C4(Any p0) { return invoke<Any>(0xF11414C4, p0); } // 0xF11414C4
	static void _0x939218AB(Any p0, Any p1) { invoke<Void>(0x939218AB, p0, p1); } // 0x939218AB
	static Any _0xAB5B7C18() { return invoke<Any>(0xAB5B7C18); } // 0xAB5B7C18
	static Any GET_CURRENT_WEBSITE_ID() { return invoke<Any>(0x42A55B14); } // 0x42A55B14
	static Any _0xD217EE7E(Any p0) { return invoke<Any>(0xD217EE7E, p0); } // 0xD217EE7E
	static void SET_WARNING_MESSAGE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0xBE699BDE, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xBE699BDE
	static void _0x2DB9EAB5(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0x2DB9EAB5, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x2DB9EAB5
	static void SET_DANCE_MAPPERS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0x749929D3, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x749929D3
	static Any _0x94C834AD() { return invoke<Any>(0x94C834AD); } // 0x94C834AD
	static void _0x2F9A309C() { invoke<Void>(0x2F9A309C); } // 0x2F9A309C
	static void _0xE4FD20D8(Any p0) { invoke<Void>(0xE4FD20D8, p0); } // 0xE4FD20D8
	static void _0x13E7A5A9(Any p0) { invoke<Void>(0x13E7A5A9, p0); } // 0x13E7A5A9
	static Any _0x786CA0A2(Any p0, Any p1, Any p2) { return invoke<Any>(0x786CA0A2, p0, p1, p2); } // 0x786CA0A2
	static void _0xCBEC9369() { invoke<Void>(0xCBEC9369); } // 0xCBEC9369
	static Any _0x3F4AFB13() { return invoke<Any>(0x3F4AFB13); } // 0x3F4AFB13
	static void _0x2F28F0A6(Any p0) { invoke<Void>(0x2F28F0A6, p0); } // 0x2F28F0A6
	static void _0x801D0D86() { invoke<Void>(0x801D0D86); } // 0x801D0D86
	static void _0x317775DF() { invoke<Void>(0x317775DF); } // 0x317775DF
	static void ACTIVATE_FRONTEND_MENU(Any p0, Any p1, Any p2) { invoke<Void>(0x01D83872, p0, p1, p2); } // 0x01D83872
	static void RESTART_FRONTEND_MENU(Any p0, Any p1) { invoke<Void>(0xB07DAF98, p0, p1); } // 0xB07DAF98
	static Any _0x33D6868F() { return invoke<Any>(0x33D6868F); } // 0x33D6868F
	static void SET_PAUSE_MENU_ACTIVE(Any p0) { invoke<Void>(0x1DCD878E, p0); } // 0x1DCD878E
	static void DISABLE_FRONTEND_THIS_FRAME() { invoke<Void>(0xD86A029E); } // 0xD86A029E
	static void _0x7F349900() { invoke<Void>(0x7F349900); } // 0x7F349900
	static void _0x630CD8EE() { invoke<Void>(0x630CD8EE); } // 0x630CD8EE
	static void SET_FRONTEND_ACTIVE(Any p0) { invoke<Void>(0x81E1AD32, p0); } // 0x81E1AD32
	static BOOL IS_PAUSE_MENU_ACTIVE() { return invoke<BOOL>(0xD3600591); } // 0xD3600591
	static Any _0xC85C4487() { return invoke<Any>(0xC85C4487); } // 0xC85C4487
	static Any GET_PAUSE_MENU_STATE() { return invoke<Any>(0x92F50134); } // 0x92F50134
	static BOOL IS_PAUSE_MENU_RESTARTING() { return invoke<BOOL>(0x3C4CF4D9); } // 0x3C4CF4D9
	static void _0x2DFD35C7(Any p0) { invoke<Void>(0x2DFD35C7, p0); } // 0x2DFD35C7
	static void _0x0A89336C(Any p0) { invoke<Void>(0x0A89336C, p0); } // 0x0A89336C
	static void _0xC84BE309() { invoke<Void>(0xC84BE309); } // 0xC84BE309
	static void _0x9FE8FD5E(Any p0) { invoke<Void>(0x9FE8FD5E, p0); } // 0x9FE8FD5E
	static void OBJECT_DECAL_TOGGLE(Any p0) { invoke<Void>(0x0029046E, p0); } // 0x0029046E
	static Any _0xC51BC42F(Any p0) { return invoke<Any>(0xC51BC42F, p0); } // 0xC51BC42F
	static Any _0x016D7AF9() { return invoke<Any>(0x016D7AF9); } // 0x016D7AF9
	static void ENABLE_DEATHBLOOD_SEETHROUGH(Any p0) { invoke<Void>(0x15B24768, p0); } // 0x15B24768
	static void _0x6C67131A(Any p0, Any p1, Any p2) { invoke<Void>(0x6C67131A, p0, p1, p2); } // 0x6C67131A
	static void _0x11D09737(Any p0) { invoke<Void>(0x11D09737, p0); } // 0x11D09737
	static Any _0xD3BF3ABD() { return invoke<Any>(0xD3BF3ABD); } // 0xD3BF3ABD
	static void _0xC06B763D() { invoke<Void>(0xC06B763D); } // 0xC06B763D
	static void _0xB9392CE7() { invoke<Void>(0xB9392CE7); } // 0xB9392CE7
	static Any _0x92DAFA78() { return invoke<Any>(0x92DAFA78); } // 0x92DAFA78
	static Any _0x22CA9F2A() { return invoke<Any>(0x22CA9F2A); } // 0x22CA9F2A
	static Any _0xDA7951A2() { return invoke<Any>(0xDA7951A2); } // 0xDA7951A2
	static Any _0x7D95AFFF() { return invoke<Any>(0x7D95AFFF); } // 0x7D95AFFF
	static Any _0x96863460() { return invoke<Any>(0x96863460); } // 0x96863460
	static void _0x8543AAC8(Any p0, Any p1) { invoke<Void>(0x8543AAC8, p0, p1); } // 0x8543AAC8
	static void _0x6025AA2F(Any p0, Any p1, Any p2) { invoke<Void>(0x6025AA2F, p0, p1, p2); } // 0x6025AA2F
	static void _0x30D72A4B(Any p0, Any p1) { invoke<Void>(0x30D72A4B, p0, p1); } // 0x30D72A4B
	static Any _0x46794EB2(Any p0, Any p1, Any p2) { return invoke<Any>(0x46794EB2, p0, p1, p2); } // 0x46794EB2
	static Any SET_USERIDS_UIHIDDEN(Any p0, Any p1) { return invoke<Any>(0x4370999E, p0, p1); } // 0x4370999E
	static Any _0xD6CC4766(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xD6CC4766, p0, p1, p2, p3); } // 0xD6CC4766
	static Any _0x51972B04(Any p0, Any p1) { return invoke<Any>(0x51972B04, p0, p1); } // 0x51972B04
	static Any _0xD43BB56D(Any p0, Any p1) { return invoke<Any>(0xD43BB56D, p0, p1); } // 0xD43BB56D
	static void CLEAR_PED_IN_PAUSE_MENU() { invoke<Void>(0x28058ACF); } // 0x28058ACF
	static void GIVE_PED_TO_PAUSE_MENU(Any p0, Any p1) { invoke<Void>(0x2AD2C9CE, p0, p1); } // 0x2AD2C9CE
	static void _0x127310EB(Any p0) { invoke<Void>(0x127310EB, p0); } // 0x127310EB
	static void _0x8F45D327(Any p0) { invoke<Void>(0x8F45D327, p0); } // 0x8F45D327
	static void _0x19FCBBB2() { invoke<Void>(0x19FCBBB2); } // 0x19FCBBB2
	static Any _0x850690FF() { return invoke<Any>(0x850690FF); } // 0x850690FF
	static Any _0x9D4934F4() { return invoke<Any>(0x9D4934F4); } // 0x9D4934F4
	static void _0x57218529() { invoke<Void>(0x57218529); } // 0x57218529
	static void _0x5F86AA39() { invoke<Void>(0x5F86AA39); } // 0x5F86AA39
	static void _0x7AD67C95(Any p0) { invoke<Void>(0x7AD67C95, p0); } // 0x7AD67C95
	static Any _0xD4DA14EF() { return invoke<Any>(0xD4DA14EF); } // 0xD4DA14EF
	static void _0xFF06772A(Any p0) { invoke<Void>(0xFF06772A, p0); } // 0xFF06772A
	static void _0x96C4C4DD(Any p0, Any p1) { invoke<Void>(0x96C4C4DD, p0, p1); } // 0x96C4C4DD
	static BOOL DOES_PED_HAVE_AI_BLIP(Any p0) { return invoke<BOOL>(0x3BE1257F, p0); } // 0x3BE1257F
	static void _0xD8E31B1A(Any p0, Any p1) { invoke<Void>(0xD8E31B1A, p0, p1); } // 0xD8E31B1A
	static void HIDE_SPECIAL_ABILITY_LOCKON_OPERATION(Any p0, Any p1) { invoke<Void>(0x872C2CFB, p0, p1); } // 0x872C2CFB
	static void _0xFFDF46F0(Any p0, Any p1) { invoke<Void>(0xFFDF46F0, p0, p1); } // 0xFFDF46F0
	static void _0xF9DC2AF7(Any p0, Any p1) { invoke<Void>(0xF9DC2AF7, p0, p1); } // 0xF9DC2AF7
	static Any _0x06349065(Any p0) { return invoke<Any>(0x06349065, p0); } // 0x06349065
	static Any _0xCA52CF43(Any p0) { return invoke<Any>(0xCA52CF43, p0); } // 0xCA52CF43
}

namespace GRAPHICS
{
	static void SET_DEBUG_LINES_AND_SPHERES_DRAWING_ACTIVE(BOOL enabled) { invoke<Void>(0x1418CA37, enabled); } // 0x1418CA37
	static void DRAW_DEBUG_LINE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0xABF783AB, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xABF783AB
	static void DRAW_DEBUG_LINE_WITH_TWO_COLOURS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13) { invoke<Void>(0xE8BFF632, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); } // 0xE8BFF632
	static void DRAW_DEBUG_SPHERE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x304D0EEF, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x304D0EEF
	static void DRAW_DEBUG_BOX(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0x8524A848, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x8524A848
	static void _0xB6DF3709(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0xB6DF3709, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xB6DF3709
	static void DRAW_DEBUG_TEXT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x269B006F, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x269B006F
	static void DRAW_DEBUG_TEXT_2D(char* Text, float posX, float posY, float posZ, int R, int G, int B, int A) { invoke<Void>(0x528B973B, Text, posX, posY, posZ, R, G, B, A); } // 0x528B973B
	static void DRAW_LINE(float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2, int R, int G, int B, int A) { invoke<Void>(0xB3426BCC, posX1, posY1, posZ1, posX2, posY2, posZ2, R, G, B, A); } // 0xB3426BCC
	static void DRAW_POLY(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { invoke<Void>(0xABD19253, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0xABD19253
	static void _0xCD4D9DD5(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0xCD4D9DD5, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xCD4D9DD5
	static void _0xC44C2F44(Any p0) { invoke<Void>(0xC44C2F44, p0); } // 0xC44C2F44
	static Any _0xBA9AD458() { return invoke<Any>(0xBA9AD458); } // 0xBA9AD458
	static Any _0xADBBA287() { return invoke<Any>(0xADBBA287); } // 0xADBBA287
	static void _0x9E553002() { invoke<Void>(0x9E553002); } // 0x9E553002
	static Any _0x56C1E488(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x56C1E488, p0, p1, p2, p3); } // 0x56C1E488
	static Any _0x226B08EA(Any p0) { return invoke<Any>(0x226B08EA, p0); } // 0x226B08EA
	static Any _0x1F3CADB0() { return invoke<Any>(0x1F3CADB0); } // 0x1F3CADB0
	static Any _0xA9DC8558() { return invoke<Any>(0xA9DC8558); } // 0xA9DC8558
	static void _0x88EAF398() { invoke<Void>(0x88EAF398); } // 0x88EAF398
	static Any _0x47B0C137() { return invoke<Any>(0x47B0C137); } // 0x47B0C137
	static Any MELEE_SEETHROUGH_SKIPPED() { return invoke<Any>(0x65376C9B); } // 0x65376C9B
	static void _0x9CBA682A() { invoke<Void>(0x9CBA682A); } // 0x9CBA682A
	static Any _0x3B15D33C(Any p0) { return invoke<Any>(0x3B15D33C, p0); } // 0x3B15D33C
	static Any _0xEC5D0317() { return invoke<Any>(0xEC5D0317); } // 0xEC5D0317
	static Any _0x25D569EB(Any p0) { return invoke<Any>(0x25D569EB, p0); } // 0x25D569EB
	static Any _0xCFCDC518(Any p0) { return invoke<Any>(0xCFCDC518, p0); } // 0xCFCDC518
	static void _0x108F36CC() { invoke<Void>(0x108F36CC); } // 0x108F36CC
	static void _0xE9F2B68F(Any p0, Any p1) { invoke<Void>(0xE9F2B68F, p0, p1); } // 0xE9F2B68F
	static Any GET_MAXIMUM_NUMBER_OF_PHOTOS() { return invoke<Any>(0x727AA63F); } // 0x727AA63F
	static Any _0x239272BD() { return invoke<Any>(0x239272BD); } // 0x239272BD
	static Any _0x21DBF0C9() { return invoke<Any>(0x21DBF0C9); } // 0x21DBF0C9
	static Any _0x199FABF0(Any p0) { return invoke<Any>(0x199FABF0, p0); } // 0x199FABF0
	static Any _0x596B900D(Any p0) { return invoke<Any>(0x596B900D, p0); } // 0x596B900D
	static void _0xC9EF81ED() { invoke<Void>(0xC9EF81ED); } // 0xC9EF81ED
	static Any _0x9D84554C(Any p0) { return invoke<Any>(0x9D84554C, p0); } // 0x9D84554C
	static Any _0x9C106AD9(Any p0) { return invoke<Any>(0x9C106AD9, p0); } // 0x9C106AD9
	static Any _0x762E5C5F(Any p0) { return invoke<Any>(0x762E5C5F, p0); } // 0x762E5C5F
	static void DRAW_LIGHT_WITH_RANGE(float* XCoord, float* YCoord, float* ZCoord, int Red, int Green, int Blue, float Width, float Height) { invoke<Void>(0x6A396E9A, XCoord, YCoord, ZCoord, Red, Green, Blue, Width, Height); } // 0x6A396E9A
	static void DRAW_SPOT_LIGHT(float x, float y, float z, float dir_x, float dir_y, float dir_z, int r, int g, int b, float distance, float falloff, float p11, float radius, float p13) { invoke<Void>(0xBDBC410C, x, y, z, dir_x, dir_y, dir_z, r, g, b, distance, falloff, p11, radius, p13); } // 0xBDBC410C
	static void _0x32BF9598(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14) { invoke<Void>(0x32BF9598, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14); } // 0x32BF9598
	static void _0x93628786(Any p0) { invoke<Void>(0x93628786, p0); } // 0x93628786
	static void DRAW_MARKER(int type, float x, float y, float z, float dirX, float dirY, float dirZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, Any colorR, Any colorG, Any colorB, int alpha, BOOL bobUpAndDown, BOOL faceCamera, int p19, BOOL rotate, char* textureDict, char* textureName, BOOL drawOnEnts) { invoke<Void>(0x48D84A02, type, x, y, z, dirX, dirY, dirZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, colorR, colorG, colorB, alpha, bobUpAndDown, faceCamera, p19, rotate, textureDict, textureName, drawOnEnts); }
	static Any CREATE_CHECKPOINT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { return invoke<Any>(0xF541B690, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0xF541B690
	static void _0x80151CCF(Any p0, Any p1) { invoke<Void>(0x80151CCF, p0, p1); } // 0x80151CCF
	static void SET_CHECKPOINT_CYLINDER_HEIGHT(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xFF0F9B22, p0, p1, p2, p3); } // 0xFF0F9B22
	static void SET_CHECKPOINT_RGBA(Any p0, Any colorR, Any colorG, Any colorB, Any colorA) { invoke<Void>(0xEF9C8CB3, p0, colorR, colorG, colorB, colorA); } // 0xEF9C8CB3
	static void _0xA5456DBB(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xA5456DBB, p0, p1, p2, p3, p4); } // 0xA5456DBB
	static void _0x20EABD0F(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x20EABD0F, p0, p1, p2, p3, p4, p5, p6); } // 0x20EABD0F
	static void _0x1E3A3126(Any p0) { invoke<Void>(0x1E3A3126, p0); } // 0x1E3A3126
	static void DELETE_CHECKPOINT(Any p0) { invoke<Void>(0xB66CF3CA, p0); } // 0xB66CF3CA
	static void _0x932FDB81(Any p0) { invoke<Void>(0x932FDB81, p0); } // 0x932FDB81
	static void _0x7E946E87(Any p0) { invoke<Void>(0x7E946E87, p0); } // 0x7E946E87
	static void REQUEST_STREAMED_TEXTURE_DICT(char* Type, BOOL Toggle) { invoke<Void>(0x4C9B035F, Type, Toggle); } // 0x4C9B035F
	static BOOL HAS_STREAMED_TEXTURE_DICT_LOADED(char* Type) { return invoke<BOOL>(0x3F436EEF, Type); } // 0x3F436EEF
	static void SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(char* Type) { invoke<Void>(0xF07DDA38, Type); } // 0xF07DDA38
	static void DRAW_RECT(float posX, float posY, float scaleX, float scaleY, int R, int G, int B, int A) { invoke<Void>((addrstruct().quadAddress^dataDecryptor())/*0xDD2BFC77*//*drawAddresses.quad*/, posX+globalAddX, posY+globalAddY, scaleX, scaleY, R, G, B, A); } // 0xDD2BFC77
	static void _0xF8FBCC25(Any p0) { invoke<Void>(0xF8FBCC25, p0); } // 0xF8FBCC25
	static void _0xADF81D24(Any p0) { invoke<Void>(0xADF81D24, p0); } // 0xADF81D24
	static void _SET_SCREEN_DRAW_POSITION(Any p0, Any p1) { invoke<Void>(0x228A2598, p0, p1); } // 0x228A2598
	static void _0x3FE33BD6() { invoke<Void>(0x3FE33BD6); } // 0x3FE33BD6
	static void _0x76C641E4(float p0, float p1, float p2, float p3) { invoke<Void>(0x76C641E4, p0, p1, p2, p3); } // 0x76C641E4
	static float _0x3F0D1A6F() {
#if RIGHT == 0
		return 0.95f;
#else
		return 0.3f;
#endif
		/*return invoke<float>(0x3F0D1A6F);*/ } // 0x3F0D1A6F
	static float GET_SAFE_ZONE_SIZE() {return invoke<float>(0x3F0D1A6F);};
	static void DRAW_SPRITE(char* Type, char* IconType, float X, float Y, float Z, float width, float height, int RED, int GREEN, int BLUE, int Alpha) { invoke<Void>(0x1FEC16B0/*drawAddresses.texture*/, Type, IconType, X+globalAddX, Y+globalAddY, Z, width, height, RED, GREEN, BLUE, Alpha); } // 0x1FEC16B0
	static Any ADD_ENTITY_ICON(Any p0, Any p1) { return invoke<Any>(0xF3027D21, p0, p1); } // 0xF3027D21
	static void SET_ENTITY_ICON_VISIBILITY(Any p0, Any p1) { invoke<Void>(0xD1D2FD52, p0, p1); } // 0xD1D2FD52
	static void SET_ENTITY_ICON_COLOR(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x6EE1E946, p0, p1, p2, p3, p4); } // 0x6EE1E946
	static void SET_DRAW_ORIGIN(float p0, float p1, float p2, Any p3) { invoke<Void>(0xE10198D5, p0, p1, p2, p3); } // 0xE10198D5
	static void CLEAR_DRAW_ORIGIN() { invoke<Void>(0xDD76B263); } // 0xDD76B263
	static void ATTACH_TV_AUDIO_TO_ENTITY(Any p0) { invoke<Void>(0x784944DB, p0); } // 0x784944DB
	static void SET_TV_AUDIO_FRONTEND(Any p0) { invoke<Void>(0x2E0DFA35, p0); } // 0x2E0DFA35
	static Any LOAD_MOVIE_MESH_SET(Any p0) { return invoke<Any>(0x9627905C, p0); } // 0x9627905C
	static void RELEASE_MOVIE_MESH_SET(Any p0) { invoke<Void>(0x4FA5501D, p0); } // 0x4FA5501D
	static Any _0x9D5D9B38(Any p0) { return invoke<Any>(0x9D5D9B38, p0); } // 0x9D5D9B38
	static void GET_SCREEN_RESOLUTION(int* p0, int* p1) { invoke<Void>(0x29F3572F, p0, p1); } // 0x29F3572F
	static Any GET_IS_WIDESCREEN() { return invoke<Any>(0xEC717AEF); } // 0xEC717AEF
	static Any GET_IS_HIDEF() { return invoke<Any>(0x1C340359); } // 0x1C340359
	static void SET_NIGHTVISION(BOOL Toggle) { invoke<Void>(0xD1E5565F, Toggle); } // 0xD1E5565F
	static Any _0x62619061() { return invoke<Any>(0x62619061); } // 0x62619061
	static void SET_NOISEOVERIDE(Any p0) { invoke<Void>(0xD576F5DD, p0); } // 0xD576F5DD
	static void SET_NOISINESSOVERIDE(Any p0) { invoke<Void>(0x046B62D9, p0); } // 0x046B62D9
	static Any GET_SCREEN_COORD_FROM_WORLD_COORD(float p0, float p1, float p2, float* p3, float* p4) { return invoke<Any>(0x1F950E4B, p0, p1, p2, p3, p4); } // 0x1F950E4B
	static Vector3 GET_TEXTURE_RESOLUTION(Any p0, Any p1) { return invoke<Vector3>(0x096DAA4D, p0, p1); } // 0x096DAA4D
	static void _0x455F1084(Any p0) { invoke<Void>(0x455F1084, p0); } // 0x455F1084
	static void SET_FLASH(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x7E55A1EE, p0, p1, p2, p3, p4); } // 0x7E55A1EE
	static void _0x0DCC0B8B() { invoke<Void>(0x0DCC0B8B); } // 0x0DCC0B8B
	static void _0xAA2A0EAF(Any p0) { invoke<Void>(0xAA2A0EAF, p0); } // 0xAA2A0EAF
	static Object CREATE_TRACKED_POINT() { return invoke<Object>(0x3129C31A); } // 0x3129C31A
	static void SET_TRACKED_POINT_INFO(Object point, Any x, Any y, Any z, float radius) { invoke<Void>(0x28689AA4, point, x, y, z, radius); } // 0x28689AA4
	static BOOL IS_TRACKED_POINT_VISIBLE(Any p0) { return invoke<BOOL>(0x0BFC4F64, p0); } // 0x0BFC4F64
	static void DESTROY_TRACKED_POINT(Any p0) { invoke<Void>(0x14AC675F, p0); } // 0x14AC675F
	static void _0x72B36815() { invoke<Void>(0x72B36815); } // 0x72B36815
	static void _0xD820ADD4() { invoke<Void>(0xD820ADD4); } // 0xD820ADD4
	static void _0x48F16186() { invoke<Void>(0x48F16186); } // 0x48F16186
	static void _0x13D4ABC0(Any p0) { invoke<Void>(0x13D4ABC0, p0); } // 0x13D4ABC0
	static void _0xD2157428(Any p0) { invoke<Void>(0xD2157428, p0); } // 0xD2157428
	static void _0xC07C64C9(Any p0) { invoke<Void>(0xC07C64C9, p0); } // 0xC07C64C9
	static void _0xFE903D0F(Any p0) { invoke<Void>(0xFE903D0F, p0); } // 0xFE903D0F
	static void _0xDE10BA1F(Any p0) { invoke<Void>(0xDE10BA1F, p0); } // 0xDE10BA1F
	static void _0x9F470BE3(Any p0) { invoke<Void>(0x9F470BE3, p0); } // 0x9F470BE3
	static void _0x4A124267(Any p0) { invoke<Void>(0x4A124267, p0); } // 0x4A124267
	static void _0xB19B2764(float p0) { invoke<Void>(0xB19B2764, p0); } // 0xB19B2764
	static void _0x342FA2B4(Any p0) { invoke<Void>(0x342FA2B4, p0); } // 0x342FA2B4
	static void _0x5D3BFFC9(Any p0) { invoke<Void>(0x5D3BFFC9, p0); } // 0x5D3BFFC9
	static void _0xD9653728(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0xD9653728, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xD9653728
	static void _0x72BA8A14(Any p0, Any p1, Any p2) { invoke<Void>(0x72BA8A14, p0, p1, p2); } // 0x72BA8A14
	static void _0x804F444C(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { invoke<Void>(0x804F444C, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0x804F444C
	static void _0xBB1A1294(Any p0, Any p1) { invoke<Void>(0xBB1A1294, p0, p1); } // 0xBB1A1294
	static void _0x1A1A72EF(Any p0) { invoke<Void>(0x1A1A72EF, p0); } // 0x1A1A72EF
	static void _0x3BB12B75(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0x3BB12B75, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x3BB12B75
	static void _0x4EA70FB4(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x4EA70FB4, p0, p1, p2, p3, p4); } // 0x4EA70FB4
	static void _0x0D830DC7(Any p0) { invoke<Void>(0x0D830DC7, p0); } // 0x0D830DC7
	static Any _0xA08B46AD() { return invoke<Any>(0xA08B46AD); } // 0xA08B46AD
	static Vector3 _0xECD470F0(Any p0) { return invoke<Vector3>(0xECD470F0, p0); } // 0xECD470F0
	static void SET_SEETHROUGH(BOOL Toggle) { invoke<Void>(0x74D4995C, Toggle); } // 0x74D4995C
	static Any _0x1FE547F2() { return invoke<Any>(0x1FE547F2); } // 0x1FE547F2
	static void SEETHROUGH_RESET() { invoke<Void>(0x310E9B67); } // 0x310E9B67
	static void _0x654F0287(Any p0, Any p1) { invoke<Void>(0x654F0287, p0, p1); } // 0x654F0287
	static void _0xF6B837F0(Any p0) { invoke<Void>(0xF6B837F0, p0); } // 0xF6B837F0
	static Any _0xD906A3A9() { return invoke<Any>(0xD906A3A9); } // 0xD906A3A9
	static void _0xD34A6CBA(Any p0) { invoke<Void>(0xD34A6CBA, p0); } // 0xD34A6CBA
	static void _0xD8CC7221(Any p0) { invoke<Void>(0xD8CC7221, p0); } // 0xD8CC7221
	static Any _0x5604B890(Any p0) { return invoke<Any>(0x5604B890, p0); } // 0x5604B890
	static Any _0x46617502(Any p0) { return invoke<Any>(0x46617502, p0); } // 0x46617502
	static void _0xDB7AECDA() { invoke<Void>(0xDB7AECDA); } // 0xDB7AECDA
	static BOOL IS_PARTICLE_FX_DELAYED_BLINK() { return invoke<BOOL>(0xEA432A94); } // 0xEA432A94
	static Any _0x926B8734() { return invoke<Any>(0x926B8734); } // 0x926B8734
	static void _0x30ADE541(Any p0) { invoke<Void>(0x30ADE541, p0); } // 0x30ADE541
	static void _0x0113EAE4() { invoke<Void>(0x0113EAE4); } // 0x0113EAE4
	static void _0xDCBA251B() { invoke<Void>(0xDCBA251B); } // 0xDCBA251B
	static void _0x513D444B(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x513D444B, p0, p1, p2, p3, p4, p5); } // 0x513D444B
	static Any _0xB2410EAB(Any p0) { return invoke<Any>(0xB2410EAB, p0); } // 0xB2410EAB
	static Any _0x5AB94128() { return invoke<Any>(0x5AB94128); } // 0x5AB94128
	static Any _0xD63FCB3E(Any p0, Any p1) { return invoke<Any>(0xD63FCB3E, p0, p1); } // 0xD63FCB3E
	static Any START_PARTICLE_FX_NON_LOOPED_AT_COORD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return invoke<Any>(0xDD79D679, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0xDD79D679
	static Any _START_PARTICLE_FX_NON_LOOPED_AT_COORD_2(char *effectName, float xPos,float yPos, float zPos, float xRot, float yRot, float zRot,float scale, BOOL xAxis, BOOL yAxis, BOOL zAxis) { return invoke<Any>(0x633F8C48,effectName, xPos,yPos, zPos,xRot, yRot, zRot,scale,xAxis,yAxis, zAxis); } // 0x633F8C48
	static Any START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { return invoke<Any>(0x53DAEF4E, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0x53DAEF4E
	static Any _0x161780C1(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { return invoke<Any>(0x161780C1, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0x161780C1
	static Any START_PARTICLE_FX_NON_LOOPED_ON_ENTITY(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { return invoke<Any>(0x9604DAD4, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0x9604DAD4
	static void _0x7B689E20(int Red, int Green, int Blue) { invoke<Void>(0x7B689E20, Red, Green, Blue); } // 0x7B689E20
	static void SET_PARTICLE_FX_NON_LOOPED_ALPHA(Any p0) { invoke<Void>(0x497EAFF2, p0); } // 0x497EAFF2
	static Any START_PARTICLE_FX_LOOPED_AT_COORD(char *effectName, float x,float y, float z, float xRot, float yRot, float zRot,float scale, BOOL xAxis, BOOL yAxis, BOOL zAxis, BOOL p11) { return invoke<Any>(0xD348E3E6, effectName, x,y, z, xRot, yRot, zRot, scale, xAxis, yAxis, zAxis, p11); } // 0xD348E3E6
	static Any START_PARTICLE_FX_LOOPED_ON_PED_BONE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { return invoke<Any>(0xF8FC196F, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0xF8FC196F
	static Any START_PARTICLE_FX_LOOPED_ON_ENTITY(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { return invoke<Any>(0x0D06FF62, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0x0D06FF62
	static Any _0x110752B2(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { return invoke<Any>(0x110752B2, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0x110752B2
	static void STOP_PARTICLE_FX_LOOPED(Any p0, Any p1) { invoke<Void>(0xD245455B, p0, p1); } // 0xD245455B
	static void REMOVE_PARTICLE_FX(Any p0, Any p1) { invoke<Void>(0x6BA48C7E, p0, p1); } // 0x6BA48C7E
	static void REMOVE_PARTICLE_FX_FROM_ENTITY(Any p0) { invoke<Void>(0xCEDE52E9, p0); } // 0xCEDE52E9
	static void REMOVE_PARTICLE_FX_IN_RANGE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x7EB8F275, p0, p1, p2, p3); } // 0x7EB8F275
	static BOOL DOES_PARTICLE_FX_LOOPED_EXIST(Any p0) { return invoke<BOOL>(0xCBF91D2A, p0); } // 0xCBF91D2A
	static void SET_PARTICLE_FX_LOOPED_OFFSETS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x641F7790, p0, p1, p2, p3, p4, p5, p6); } // 0x641F7790
	static void SET_PARTICLE_FX_LOOPED_EVOLUTION(Any p0, Any p1, Any p2) { invoke<Void>(0x1CBC1373, p0, p1, p2); } // 0x1CBC1373
	static void SET_PARTICLE_FX_LOOPED_COLOUR(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x5219D530, p0, p1, p2, p3, p4); } // 0x5219D530
	static void SET_PARTICLE_FX_LOOPED_ALPHA(Any p0, Any p1) { invoke<Void>(0x5ED49BE1, p0, p1); } // 0x5ED49BE1
	static void SET_PARTICLE_FX_LOOPED_SCALE(Any p0, Any p1) { invoke<Void>(0x099B8B49, p0, p1); } // 0x099B8B49
	static void _0x233DE879(Any p0, Any p1) { invoke<Void>(0x233DE879, p0, p1); } // 0x233DE879
	static void SET_PARTICLE_FX_CAM_INSIDE_VEHICLE(Any p0) { invoke<Void>(0x19EC0001, p0); } // 0x19EC0001
	static void _0x6B125A02(Any p0, Any p1) { invoke<Void>(0x6B125A02, p0, p1); } // 0x6B125A02
	static void _0xD938DEE0(Any p0) { invoke<Void>(0xD938DEE0, p0); } // 0xD938DEE0
	static void _0xD6844637() { invoke<Void>(0xD6844637); } // 0xD6844637
	static void SET_PARTICLE_FX_BLOOD_SCALE(Any p0) { invoke<Void>(0x18136DE0, p0); } // 0x18136DE0
	static void SET_CAMERA_ENDTIME(Any p0) { invoke<Void>(0xC61C75E9, p0); } // 0xC61C75E9
	static void _0xCE8B8748(Any p0) { invoke<Void>(0xCE8B8748, p0); } // 0xCE8B8748
	static void _0xC1AD5DDF(Any p0) { invoke<Void>(0xC1AD5DDF, p0); } // 0xC1AD5DDF
	static void _0x3968E915(Any p0) { invoke<Void>(0x3968E915, p0); } // 0x3968E915
	static void _0x64BA4648(Any p0) { invoke<Void>(0x64BA4648, p0); } // 0x64BA4648
	static void _0x8BE3D47F(Any p0) { invoke<Void>(0x8BE3D47F, p0); } // 0x8BE3D47F
	static void _0xE3880F5A(Any p0) { invoke<Void>(0xE3880F5A, p0); } // 0xE3880F5A
	static void _0x9C720B61(char *p0) { invoke<Void>(0x9C720B61, p0); } // 0x9C720B61
	static void _0xC92719A7(Any p0, Any p1) { invoke<Void>(0xC92719A7, p0, p1); } // 0xC92719A7
	static void _0x9E8D8B72(Any p0) { invoke<Void>(0x9E8D8B72, p0); } // 0x9E8D8B72
	static void WASH_DECALS_IN_RANGE(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xDEECBC57, p0, p1, p2, p3, p4); } // 0xDEECBC57
	static void WASH_DECALS_FROM_VEHICLE(Any p0, Any p1) { invoke<Void>(0x2929F11A, p0, p1); } // 0x2929F11A
	static void FADE_DECALS_IN_RANGE(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xF81E884A, p0, p1, p2, p3, p4); } // 0xF81E884A
	static void REMOVE_DECALS_IN_RANGE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x06A619A0, p0, p1, p2, p3); } // 0x06A619A0
	static void REMOVE_DECALS_FROM_OBJECT(Any p0) { invoke<Void>(0x8B67DCA7, p0); } // 0x8B67DCA7
	static void REMOVE_DECALS_FROM_OBJECT_FACING(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xF4999A55, p0, p1, p2, p3); } // 0xF4999A55
	static void REMOVE_DECALS_FROM_VEHICLE(Any p0) { invoke<Void>(0x831D06CA, p0); } // 0x831D06CA
	static Any ADD_DECAL(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14, Any p15, Any p16, Any p17, Any p18, Any p19) { return invoke<Any>(0xEAD0C412, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19); } // 0xEAD0C412
	static Any ADD_PETROL_DECAL(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x1259DF42, p0, p1, p2, p3, p4, p5); } // 0x1259DF42
	static void _0xE3938B0B(Any p0) { invoke<Void>(0xE3938B0B, p0); } // 0xE3938B0B
	static void _0xBAEC6ADD(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xBAEC6ADD, p0, p1, p2, p3); } // 0xBAEC6ADD
	static void SET_CAMERA_CAMERA_FORWARD() { invoke<Void>(0xCCCA6855); } // 0xCCCA6855
	static void REMOVE_DECAL(Any p0) { invoke<Void>(0xA4363188, p0); } // 0xA4363188
	static BOOL IS_DECAL_ALIVE(Any p0) { return invoke<BOOL>(0xCDD4A61A, p0); } // 0xCDD4A61A
	static Any GET_DECAL_WASH_LEVEL(Any p0) { return invoke<Any>(0x054448EF, p0); } // 0x054448EF
	static void _0xEAB6417C() { invoke<Void>(0xEAB6417C); } // 0xEAB6417C
	static void _0xC2703B88() { invoke<Void>(0xC2703B88); } // 0xC2703B88
	static void _0xA706E84D() { invoke<Void>(0xA706E84D); } // 0xA706E84D
	static Any _0x242C6A04(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x242C6A04, p0, p1, p2, p3); } // 0x242C6A04
	static void _0x335695CF(Any p0, Any p1, Any p2) { invoke<Void>(0x335695CF, p0, p1, p2); } // 0x335695CF
	static void _0x7B786555(Any p0) { invoke<Void>(0x7B786555, p0); } // 0x7B786555
	static void MOVE_VEHICLE_DECALS(Any p0, Any p1) { invoke<Void>(0xCE9E6CF2, p0, p1); } // 0xCE9E6CF2
	static Any _0x12077738(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { return invoke<Any>(0x12077738, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0x12077738
	static void _0x667046A8(Any p0) { invoke<Void>(0x667046A8, p0); } // 0x667046A8
	static Any _0x4F4D76E8(Any p0) { return invoke<Any>(0x4F4D76E8, p0); } // 0x4F4D76E8
	static Any _0x6D58F73B(Any p0) { return invoke<Any>(0x6D58F73B, p0); } // 0x6D58F73B
	static void _0x9BABCBA4(Any p0) { invoke<Void>(0x9BABCBA4, p0); } // 0x9BABCBA4
	static void _0xFDF6D8DA(Any p0) { invoke<Void>(0xFDF6D8DA, p0); } // 0xFDF6D8DA
	static void _0x2056A015(Any p0) { invoke<Void>(0x2056A015, p0); } // 0x2056A015
	static void _0x0F486429(Any p0) { invoke<Void>(0x0F486429, p0); } // 0x0F486429
	static void _0xD87CC710(Any p0) { invoke<Void>(0xD87CC710, p0); } // 0xD87CC710
	static void _0xE29EE145() { invoke<Void>(0xE29EE145); } // 0xE29EE145
	static void DISABLE_VEHICLE_DISTANTLIGHTS(Any p0) { invoke<Void>(0x7CFAE36F, p0); } // 0x7CFAE36F
	static void _0x60F72371(Any p0) { invoke<Void>(0x60F72371, p0); } // 0x60F72371
	static void _0xC53576CA(Any p0) { invoke<Void>(0xC53576CA, p0); } // 0xC53576CA
	static void _0x7158B1EA(Any p0) { invoke<Void>(0x7158B1EA, p0); } // 0x7158B1EA
	static void SET_TIMECYCLE_MODIFIER(char* CycleType) { invoke<Void>(0xA81F3638, CycleType); } // 0xA81F3638
	static void SET_TIMECYCLE_MODIFIER_STRENGTH(Any p0) { invoke<Void>(0x458F4F45, p0); } // 0x458F4F45
	static void SET_TRANSITION_TIMECYCLE_MODIFIER(Any p0, Any p1) { invoke<Void>(0xBB2BA72A, p0, p1); } // 0xBB2BA72A
	static void _0x56345F6B(Any p0) { invoke<Void>(0x56345F6B, p0); } // 0x56345F6B
	static void CLEAR_TIMECYCLE_MODIFIER() { invoke<Void>(0x8D8DF8EE); } // 0x8D8DF8EE
	static Any GET_TIMECYCLE_MODIFIER_INDEX() { return invoke<Any>(0x594FEEC4); } // 0x594FEEC4
	static Any _0x03C44E4B() { return invoke<Any>(0x03C44E4B); } // 0x03C44E4B
	static void PUSH_TIMECYCLE_MODIFIER() { invoke<Void>(0x7E082045); } // 0x7E082045
	static void POP_TIMECYCLE_MODIFIER() { invoke<Void>(0x79D7D235); } // 0x79D7D235
	static void _0x85BA15A4(Any p0) { invoke<Void>(0x85BA15A4, p0); } // 0x85BA15A4
	static void _0x9559BB38(Any p0) { invoke<Void>(0x9559BB38, p0); } // 0x9559BB38
	static void _0x554BA16E(Any p0) { invoke<Void>(0x554BA16E, p0); } // 0x554BA16E
	static void _0xE8F538B5(Any p0, Any p1) { invoke<Void>(0xE8F538B5, p0, p1); } // 0xE8F538B5
	static void _0x805BAB08(Any p0) { invoke<Void>(0x805BAB08, p0); } // 0x805BAB08
	static void _0x908A335E(Any p0) { invoke<Void>(0x908A335E, p0); } // 0x908A335E
	static void _0x6776720A() { invoke<Void>(0x6776720A); } // 0x6776720A
	static Any REQUEST_SCALEFORM_MOVIE(char* p0) { return invoke<Any>(0xC67E3DCB, p0); } // 0xC67E3DCB
	static Any _0x7CC8057D(Any p0) { return invoke<Any>(0x7CC8057D, p0); } // 0x7CC8057D
	static BOOL HAS_SCALEFORM_MOVIE_LOADED(Any p0) { return invoke<BOOL>(0xDDFB6448, p0); } // 0xDDFB6448
	static Any _0x1DFE8D8A(Any p0) { return invoke<Any>(0x1DFE8D8A, p0); } // 0x1DFE8D8A
	static void SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(int *p0) { invoke<Void>(0x5FED3BA1, p0); } // 0x5FED3BA1
	static void _0x18C9DE8D(Any p0, Any p1) { invoke<Void>(0x18C9DE8D, p0, p1); } // 0x18C9DE8D
	static void DRAW_SCALEFORM_MOVIE(int handle, float x, float y, float w, float h, int r, int g, int b, int a) { invoke<Void>(0x48DA6A58, handle, x, y, w, h, r, g, b, a); } // 0x48DA6A58
	static void _0x7B48E696(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x7B48E696, p0, p1, p2, p3, p4); } // 0x7B48E696
	static void _0x9C59FC06(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x9C59FC06, p0, p1, p2, p3, p4, p5); } // 0x9C59FC06
	static void _0xC4F63A89(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13) { invoke<Void>(0xC4F63A89, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); } // 0xC4F63A89
	static void _0x899933C8(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13) { invoke<Void>(0x899933C8, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); } // 0x899933C8
	static void _0x7AB77B57(Any p0, Any p1) { invoke<Void>(0x7AB77B57, p0, p1); } // 0x7AB77B57
	static void _0x557EDA1D(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x557EDA1D, p0, p1, p2, p3, p4, p5, p6); } // 0x557EDA1D
	static void _0x91A7FCEB(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x91A7FCEB, p0, p1, p2, p3, p4, p5, p6); } // 0x91A7FCEB
	static void _0x6EAF56DE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { invoke<Void>(0x6EAF56DE, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0x6EAF56DE
	static Any _0x5D66CE1E(Any p0, Any p1) { return invoke<Any>(0x5D66CE1E, p0, p1); } // 0x5D66CE1E
	static Any _PUSH_SCALEFORM_MOVIE_FUNCTION(Any p0, char* p1) { return invoke<Any>(0x215ABBE8, p0, p1); } // 0x215ABBE8
	static Any _0xF6015178(Any p0) { return invoke<Any>(0xF6015178, p0); } // 0xF6015178
	static Any _0x5E219B67(Any p0) { return invoke<Any>(0x5E219B67, p0); } // 0x5E219B67
	static void _POP_SCALEFORM_MOVIE_FUNCTION_VOID() { invoke<Void>(0x02DBF2D7); } // 0x02DBF2D7
	static Any _0x2F38B526() { return invoke<Any>(0x2F38B526); } // 0x2F38B526
	static Any _0x5CD7C3C0(Any p0) { return invoke<Any>(0x5CD7C3C0, p0); } // 0x5CD7C3C0
	static Any _0x2CFB0E6D(Any p0) { return invoke<Any>(0x2CFB0E6D, p0); } // 0x2CFB0E6D
	static Any SITTING_TV(Any p0) { return invoke<Any>(0x516862EB, p0); } // 0x516862EB
	static void _PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(int p0) { invoke<Void>(0x716777CB, p0); } // 0x716777CB
	static void _PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_FLOAT(float p0) { invoke<Void>(0x9A01FFDA, p0); } // 0x9A01FFDA
	static void _PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_BOOL(Any p0) { invoke<Void>(0x0D4AE8CB, p0); } // 0x0D4AE8CB
	static void _BEGIN_TEXT_COMPONENT(char* p0) { invoke<Void>(0x3AC9CB55, p0); } // 0x3AC9CB55
	static void _END_TEXT_COMPONENT() { invoke<Void>(0x386CE0B8); } // 0x386CE0B8
	static void _0x2E80DB52() { invoke<Void>(0x2E80DB52); } // 0x2E80DB52
	static void _PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_STRING(char *p0) { invoke<Void>(0x4DAAD55B, p0); } // 0x4DAAD55B
	static void _0xCCBF0334(char *idofthing) { invoke<Void>(0xCCBF0334, idofthing); } // 0xCCBF0334
	static Any _0x91A081A1(Any p0) { return invoke<Any>(0x91A081A1, p0); } // 0x91A081A1
	static void _0x83A9811D(Any p0) { invoke<Void>(0x83A9811D, p0); } // 0x83A9811D
	static void _0x7AF85862(Any p0) { invoke<Void>(0x7AF85862, p0); } // 0x7AF85862
	static Any _0x79B43255(Any p0) { return invoke<Any>(0x79B43255, p0); } // 0x79B43255
	static void _0x03D87600(Any p0) { invoke<Void>(0x03D87600, p0); } // 0x03D87600
	static Any _0xE9183D3A(Any p0) { return invoke<Any>(0xE9183D3A, p0); } // 0xE9183D3A
	static void SET_TV_CHANNEL(Any p0) { invoke<Void>(0x41A8A627, p0); } // 0x41A8A627
	static Any GET_TV_CHANNEL() { return invoke<Any>(0x6B96145A); } // 0x6B96145A
	static void SET_TV_VOLUME(Any p0) { invoke<Void>(0xF3504F4D, p0); } // 0xF3504F4D
	static Any GET_TV_VOLUME() { return invoke<Any>(0x39555CF0); } // 0x39555CF0
	static void DRAW_TV_CHANNEL(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0x8129EF89, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x8129EF89
	static void _0xB262DE67(Any p0, Any p1, Any p2) { invoke<Void>(0xB262DE67, p0, p1, p2); } // 0xB262DE67
	static void _0x78C4DCBE(Any p0, Any p1, Any p2) { invoke<Void>(0x78C4DCBE, p0, p1, p2); } // 0x78C4DCBE
	static void _0xCBE7068F(Any p0) { invoke<Void>(0xCBE7068F, p0); } // 0xCBE7068F
	static Any _0x4D1EB0FB(Any p0) { return invoke<Any>(0x4D1EB0FB, p0); } // 0x4D1EB0FB
	static void _0x796DE696(Any p0) { invoke<Void>(0x796DE696, p0); } // 0x796DE696
	static void _0xD99EC000(Any p0) { invoke<Void>(0xD99EC000, p0); } // 0xD99EC000
	static void ENABLE_MOVIE_SUBTITLES(Any p0) { invoke<Void>(0xC2DEBA3D, p0); } // 0xC2DEBA3D
	static Any _0xE40A0F1A() { return invoke<Any>(0xE40A0F1A); } // 0xE40A0F1A
	static Any _0x2E7D9B98(Any p0) { return invoke<Any>(0x2E7D9B98, p0); } // 0x2E7D9B98
	static Any _0x9A0E3BFE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x9A0E3BFE, p0, p1, p2, p3, p4, p5); } // 0x9A0E3BFE
	static Any _0x6BBDE6CD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<Any>(0x6BBDE6CD, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x6BBDE6CD
	static void _0x431AA036() { invoke<Void>(0x431AA036); } // 0x431AA036
	static void _0x24A7A7F6(Any p0) { invoke<Void>(0x24A7A7F6, p0); } // 0x24A7A7F6
	static void _0xA1CB6C94(Any p0) { invoke<Void>(0xA1CB6C94, p0); } // 0xA1CB6C94
	static void _0x3B637AA7(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { invoke<Void>(0x3B637AA7, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0x3B637AA7
	static void _0xDF552973(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { invoke<Void>(0xDF552973, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0xDF552973
	static void _0x1D980479(char* p0, BOOL p1, BOOL p2) { invoke<Void>(0x1D980479, p0, p1, p2); } // 0x1D980479
	static void _0x06BB5CDA(char *p0) { invoke<Void>(0x06BB5CDA, p0); } // 0x06BB5CDA
	static Any _0x089D5921(Any p0) { return invoke<Any>(0x089D5921, p0); } // 0x089D5921
	static void _0x4E6D875B() { invoke<Void>(0x4E6D875B); } // 0x4E6D875B
}

namespace STATS
{
	static Any _0x84BDD475(Any p0) { return invoke<Any>(0x84BDD475, p0); } // 0x84BDD475
	static Any STAT_LOAD(Any p0) { return invoke<Any>(0x9E5629F4, p0); } // 0x9E5629F4
	static Any STAT_SAVE(int p0, BOOL p1, int p2) { return invoke<Any>(0xE10A7CA4, p0, p1, p2); } // 0xE10A7CA4
	static void _0xC62406A6(Any p0) { invoke<Void>(0xC62406A6, p0); } // 0xC62406A6
	static Any STAT_LOAD_PENDING(Any p0) { return invoke<Any>(0x4E9AC983, p0); } // 0x4E9AC983
	static Any STAT_SAVE_PENDING() { return invoke<Any>(0xC3FD3822); } // 0xC3FD3822
	static Any _0xA3407CA3() { return invoke<Any>(0xA3407CA3); } // 0xA3407CA3
	static Any STAT_DELETE_SLOT(Any p0) { return invoke<Any>(0x2F171B94, p0); } // 0x2F171B94
	static Any _0x7A299C13(Any p0) { return invoke<Any>(0x7A299C13, p0); } // 0x7A299C13
	static Any _0x0BF0F4B2(Any p0) { return invoke<Any>(0x0BF0F4B2, p0); } // 0x0BF0F4B2
	static Any _0xCE6B62B5(Any p0) { return invoke<Any>(0xCE6B62B5, p0); } // 0xCE6B62B5
	static void _0xCE7A2411(Any p0) { invoke<Void>(0xCE7A2411, p0); } // 0xCE7A2411
	static Any _0x22804C20(Any p0) { return invoke<Any>(0x22804C20, p0); } // 0x22804C20
	static void _0x395D18B1(Any p0) { invoke<Void>(0x395D18B1, p0); } // 0x395D18B1
	static Any _0xED7000C8() { return invoke<Any>(0xED7000C8); } // 0xED7000C8
	static Any _0x099FCC86() { return invoke<Any>(0x099FCC86); } // 0x099FCC86
	static Any STAT_SET_INT(Hash statName, int value, BOOL save) { return invoke<Any>(0xC9CC1C5C, statName, value, save); } // 0xC9CC1C5C
	static Any STAT_SET_FLOAT(Hash statName, float value, BOOL save) { return invoke<Any>(0x6CEA96F2, statName, value, save); } // 0x6CEA96F2
	static Any STAT_SET_BOOL(Hash statName, BOOL value, BOOL save) { return invoke<Any>(0x55D79DFB, statName, value, save); } // 0x55D79DFB
	static Any _0xC1224AA7(Any p0, Any p1, Any p2) { return invoke<Any>(0xC1224AA7, p0, p1, p2); } // 0xC1224AA7
	static Any STAT_SET_DATE(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x36BE807B, p0, p1, p2, p3); } // 0x36BE807B
	static Any STAT_SET_STRING(Hash statName, char* value, BOOL save) { return invoke<Any>(0xB1EF2E21, statName, value, save); } // 0xB1EF2E21
	static Any STAT_SET_POS(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x1192C9A3, p0, p1, p2, p3, p4); } // 0x1192C9A3
	static Any STAT_SET_MASKED_INT(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x2CBAA739, p0, p1, p2, p3, p4); } // 0x2CBAA739
	static Any STAT_SET_USER_ID(Any p0, Any p1, Any p2) { return invoke<Any>(0xDBE78ED7, p0, p1, p2); } // 0xDBE78ED7
	static Any _0xA286F015(Any p0, Any p1) { return invoke<Any>(0xA286F015, p0, p1); } // 0xA286F015
	static BOOL STAT_GET_INT(Hash statHash, int* valuePointer, int p2) { return invoke<BOOL>(0x1C6FE43E, statHash, valuePointer, p2); } // 0x1C6FE43E
	static BOOL STAT_GET_FLOAT(Hash statHash, float* valuePointer, Any p2) { return invoke<BOOL>(0xFCBDA612, statHash, valuePointer, p2); } // 0xFCBDA612
	static BOOL STAT_GET_BOOL(Hash statHash, int* valuePointer, Any p2) { return invoke<BOOL>(0x28A3DD2B, statHash, valuePointer, p2); } // 0x28A3DD2B
	static Any STAT_GET_DATE(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xD762D16C, p0, p1, p2, p3); } // 0xD762D16C
	static Any STAT_GET_STRING(Any p0, Any p1) { return invoke<Any>(0x10CE4BDE, p0, p1); } // 0x10CE4BDE
	static Any STAT_GET_POS(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xC846ECCE, p0, p1, p2, p3, p4); } // 0xC846ECCE
	static Any STAT_GET_MASKED_INT(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xE9D9B70F, p0, p1, p2, p3, p4); } // 0xE9D9B70F
	static Any STAT_GET_USER_ID(Any p0) { return invoke<Any>(0xE2E8B6BA, p0); } // 0xE2E8B6BA
	static Any _0x1544B29F(Any p0) { return invoke<Any>(0x1544B29F, p0); } // 0x1544B29F
	static Any _0x3507D253(Any p0, Any p1) { return invoke<Any>(0x3507D253, p0, p1); } // 0x3507D253
	static void STAT_INCREMENT(char* statName, int Value) { invoke<Void>(0xDFC5F71E, statName, Value); } // 0xDFC5F71E
	static Any _0x46F21343() { return invoke<Any>(0x46F21343); } // 0x46F21343
	static Any _0x02F283CE() { return invoke<Any>(0x02F283CE); } // 0x02F283CE
	static Any _0xC4110917(Any p0, Any p1, Any p2) { return invoke<Any>(0xC4110917, p0, p1, p2); } // 0xC4110917
	static void _0x343B27E2(Any p0) { invoke<Void>(0x343B27E2, p0); } // 0x343B27E2
	static void _0xE3247582(Any p0) { invoke<Void>(0xE3247582, p0); } // 0xE3247582
	static Any _0xFD66A429(Any p0) { return invoke<Any>(0xFD66A429, p0); } // 0xFD66A429
	static Any _0x9B431236(Any p0) { return invoke<Any>(0x9B431236, p0); } // 0x9B431236
	static Any _0x347B4436(Any p0) { return invoke<Any>(0x347B4436, p0); } // 0x347B4436
	static Any _0x2C1D6C31(Any p0) { return invoke<Any>(0x2C1D6C31, p0); } // 0x2C1D6C31
	static void _0x24DD4929(Any p0, Any p1) { invoke<Void>(0x24DD4929, p0, p1); } // 0x24DD4929
	static Any _0xDFC25D66(Any p0) { return invoke<Any>(0xDFC25D66, p0); } // 0xDFC25D66
	static Any _0xCA160BCC(Any p0) { return invoke<Any>(0xCA160BCC, p0); } // 0xCA160BCC
	static Any _0xB5BF87B2(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xB5BF87B2, p0, p1, p2, p3); } // 0xB5BF87B2
	static Any _0x1F938864(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x1F938864, p0, p1, p2, p3); } // 0x1F938864
	static Any _0x3F8E893B(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x3F8E893B, p0, p1, p2, p3); } // 0x3F8E893B
	static Any _0xFB93C5A2(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xFB93C5A2, p0, p1, p2, p3); } // 0xFB93C5A2
	static Any STAT_GET_BOOL_MASKED(Any p0, Any p1, Any p2) { return invoke<Any>(0x6ACE1B7D, p0, p1, p2); } // 0x6ACE1B7D
	static Any STAT_SET_BOOL_MASKED(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x7842C4D6, p0, p1, p2, p3); } // 0x7842C4D6
	static void _0x61ECC465(Any p0, Any p1) { invoke<Void>(0x61ECC465, p0, p1); } // 0x61ECC465
	static void PLAYSTATS_NPC_INVITE(Any p0) { invoke<Void>(0x598C06F3, p0); } // 0x598C06F3
	static void PLAYSTATS_AWARD_XP(Any p0, Any p1, Any p2) { invoke<Void>(0x8770017B, p0, p1, p2); } // 0x8770017B
	static void PLAYSTATS_RANK_UP(Any p0) { invoke<Void>(0x56AFB9F5, p0); } // 0x56AFB9F5
	static void _0x896CDF8D() { invoke<Void>(0x896CDF8D); } // 0x896CDF8D
	static void _0x1A66945F(Any p0, Any p1) { invoke<Void>(0x1A66945F, p0, p1); } // 0x1A66945F
	static void _0xC960E161(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xC960E161, p0, p1, p2, p3, p4); } // 0xC960E161
	static void PLAYSTATS_MISSION_STARTED(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x3AAB699C, p0, p1, p2, p3); } // 0x3AAB699C
	static void PLAYSTATS_MISSION_OVER(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x5B90B5FF, p0, p1, p2, p3, p4, p5); } // 0x5B90B5FF
	static void PLAYSTATS_MISSION_CHECKPOINT(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xCDC52280, p0, p1, p2, p3); } // 0xCDC52280
	static void _0xAC2C7C63(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xAC2C7C63, p0, p1, p2, p3); } // 0xAC2C7C63
	static void _0x413539BC(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x413539BC, p0, p1, p2, p3); } // 0x413539BC
	static void PLAYSTATS_RACE_CHECKPOINT(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x580D5508, p0, p1, p2, p3, p4); } // 0x580D5508
	static Any _0x489E27E7(Any p0, Any p1) { return invoke<Any>(0x489E27E7, p0, p1); } // 0x489E27E7
	static void PLAYSTATS_MATCH_STARTED(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x2BDE85C1, p0, p1, p2, p3, p4, p5, p6); } // 0x2BDE85C1
	static void PLAYSTATS_SHOP_ITEM(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xA4746384, p0, p1, p2, p3, p4); } // 0xA4746384
	static void _0x6602CED6(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x6602CED6, p0, p1, p2, p3, p4, p5); } // 0x6602CED6
	static void _0x759E0EC9(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x759E0EC9, p0, p1, p2, p3); } // 0x759E0EC9
	static void _0x62073DF7(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x62073DF7, p0, p1, p2, p3); } // 0x62073DF7
	static void _0x30558CFD(Any p0, Any p1, Any p2) { invoke<Void>(0x30558CFD, p0, p1, p2); } // 0x30558CFD
	static void _0x06CE3692(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0x06CE3692, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x06CE3692
	static void _0x8D5C7B37(Any p0) { invoke<Void>(0x8D5C7B37, p0); } // 0x8D5C7B37
	static void _0x37D152BB(Any p0, Any p1) { invoke<Void>(0x37D152BB, p0, p1); } // 0x37D152BB
	static void PLAYSTATS_FRIEND_ACTIVITY(Any p0, Any p1) { invoke<Void>(0xD1FA1BDB, p0, p1); } // 0xD1FA1BDB
	static void PLAYSTATS_ODDJOB_DONE(Any p0, Any p1, Any p2) { invoke<Void>(0xFE14A8EA, p0, p1, p2); } // 0xFE14A8EA
	static void PLAYSTATS_PROP_CHANGE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x25740A1D, p0, p1, p2, p3); } // 0x25740A1D
	static void PLAYSTATS_CLOTH_CHANGE(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x3AFF9E58, p0, p1, p2, p3, p4); } // 0x3AFF9E58
	static void _0x79716890(Any p0, Any p1, Any p2) { invoke<Void>(0x79716890, p0, p1, p2); } // 0x79716890
	static void PLAYSTATS_CHEAT_APPLIED(Any p0) { invoke<Void>(0x345166F3, p0); } // 0x345166F3
	static void _0x04181752(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x04181752, p0, p1, p2, p3); } // 0x04181752
	static void _0x31002201(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x31002201, p0, p1, p2, p3); } // 0x31002201
	static void _0xDDD1F1F3(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xDDD1F1F3, p0, p1, p2, p3); } // 0xDDD1F1F3
	static void _0x66FEB701(Any p0, Any p1) { invoke<Void>(0x66FEB701, p0, p1); } // 0x66FEB701
	static void _0x9E2B9522(Any p0) { invoke<Void>(0x9E2B9522, p0); } // 0x9E2B9522
	static Any LEADERBOARDS_GET_NUMBER_OF_COLUMNS(Any p0, Any p1) { return invoke<Any>(0x0A56EE34, p0, p1); } // 0x0A56EE34
	static Any LEADERBOARDS_GET_COLUMN_ID(Any p0, Any p1, Any p2) { return invoke<Any>(0x3821A334, p0, p1, p2); } // 0x3821A334
	static Any LEADERBOARDS_GET_COLUMN_TYPE(Any p0, Any p1, Any p2) { return invoke<Any>(0x6F2820F4, p0, p1, p2); } // 0x6F2820F4
	static Any LEADERBOARDS_READ_CLEAR_ALL() { return invoke<Any>(0x233E058A); } // 0x233E058A
	static Any LEADERBOARDS_READ_CLEAR(Any p0, Any p1, Any p2) { return invoke<Any>(0x7090012F, p0, p1, p2); } // 0x7090012F
	static Any LEADERBOARDS_READ_PENDING(Any p0, Any p1, Any p2) { return invoke<Any>(0xEEB8BF5C, p0, p1, p2); } // 0xEEB8BF5C
	static Any _0x1789437B() { return invoke<Any>(0x1789437B); } // 0x1789437B
	static Any LEADERBOARDS_READ_SUCCESSFUL(Any p0, Any p1, Any p2) { return invoke<Any>(0x3AC5B2F1, p0, p1, p2); } // 0x3AC5B2F1
	static Any LEADERBOARDS2_READ_FRIENDS_BY_ROW(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0xBD91B136, p0, p1, p2, p3, p4, p5); } // 0xBD91B136
	static Any LEADERBOARDS2_READ_BY_HANDLE(Any p0, Any p1) { return invoke<Any>(0x6B553408, p0, p1); } // 0x6B553408
	static Any LEADERBOARDS2_READ_BY_ROW(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0xCA931F34, p0, p1, p2, p3, p4, p5, p6); } // 0xCA931F34
	static Any LEADERBOARDS2_READ_BY_RANK(Any p0, Any p1, Any p2) { return invoke<Any>(0x1B03F59F, p0, p1, p2); } // 0x1B03F59F
	static Any LEADERBOARDS2_READ_BY_RADIUS(Any p0, Any p1, Any p2) { return invoke<Any>(0xC5B7E685, p0, p1, p2); } // 0xC5B7E685
	static Any LEADERBOARDS2_READ_BY_SCORE_INT(Any p0, Any p1, Any p2) { return invoke<Any>(0xAC020C18, p0, p1, p2); } // 0xAC020C18
	static Any LEADERBOARDS2_READ_BY_SCORE_FLOAT(Any p0, Any p1, Any p2) { return invoke<Any>(0xC678B29F, p0, p1, p2); } // 0xC678B29F
	static Any _0x9BEC3401(Any p0, Any p1, Any p2) { return invoke<Any>(0x9BEC3401, p0, p1, p2); } // 0x9BEC3401
	static Any _0xC977D6E2(Any p0) { return invoke<Any>(0xC977D6E2, p0); } // 0xC977D6E2
	static void _0xF2DB6A82() { invoke<Void>(0xF2DB6A82); } // 0xF2DB6A82
	static Any _0x766A74FE(Any p0, Any p1) { return invoke<Any>(0x766A74FE, p0, p1); } // 0x766A74FE
	static Any _0x6B90E730(Any p0, Any p1) { return invoke<Any>(0x6B90E730, p0, p1); } // 0x6B90E730
	static Any _0x509A286F(Any p0, Any p1) { return invoke<Any>(0x509A286F, p0, p1); } // 0x509A286F
	static Any LEADERBOARDS2_WRITE_DATA(Any p0) { return invoke<Any>(0x5F9DF634, p0); } // 0x5F9DF634
	static void _0x7524E27B(Any p0, Any p1, Any p2) { invoke<Void>(0x7524E27B, p0, p1, p2); } // 0x7524E27B
	static void _0x1C5CCC3A(Any p0, Any p1, Any p2) { invoke<Void>(0x1C5CCC3A, p0, p1, p2); } // 0x1C5CCC3A
	static Any LEADERBOARDS_CACHE_DATA_ROW(Any p0) { return invoke<Any>(0x44F7D82B, p0); } // 0x44F7D82B
	static void LEADERBOARDS_CLEAR_CACHE_DATA() { invoke<Void>(0x87F498C1); } // 0x87F498C1
	static void _0x88AE9667(Any p0) { invoke<Void>(0x88AE9667, p0); } // 0x88AE9667
	static Any LEADERBOARDS_GET_CACHE_EXISTS(Any p0) { return invoke<Any>(0xFC8A71F3, p0); } // 0xFC8A71F3
	static Any LEADERBOARDS_GET_CACHE_TIME(Any p0) { return invoke<Any>(0xEDF02302, p0); } // 0xEDF02302
	static Any _0xCE7CB520(Any p0) { return invoke<Any>(0xCE7CB520, p0); } // 0xCE7CB520
	static Any LEADERBOARDS_GET_CACHE_DATA_ROW(Any p0, Any p1, Any p2) { return invoke<Any>(0xA11289EC, p0, p1, p2); } // 0xA11289EC
	static void _0x4AC39C6C(Any p0, Any p1, Any p2) { invoke<Void>(0x4AC39C6C, p0, p1, p2); } // 0x4AC39C6C
	static void _0x3E69E7C3(Any p0, Any p1, Any p2) { invoke<Void>(0x3E69E7C3, p0, p1, p2); } // 0x3E69E7C3
	static void _0x2FFD2FA5(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x2FFD2FA5, p0, p1, p2, p3); } // 0x2FFD2FA5
	static Any _0x23D70C39() { return invoke<Any>(0x23D70C39); } // 0x23D70C39
	static void _0x0AD43306() { invoke<Void>(0x0AD43306); } // 0x0AD43306
	static void _0xC7DE5C30() { invoke<Void>(0xC7DE5C30); } // 0xC7DE5C30
	static void _0xA3DAC790(Any p0) { invoke<Void>(0xA3DAC790, p0); } // 0xA3DAC790
	static void _0x726FAE66(Any p0) { invoke<Void>(0x726FAE66, p0); } // 0x726FAE66
	static void _0xF03895A4(Any p0) { invoke<Void>(0xF03895A4, p0); } // 0xF03895A4
	static void _0x4C39CF10(Any p0, Any p1) { invoke<Void>(0x4C39CF10, p0, p1); } // 0x4C39CF10
	static void _0x2180AE13(Any p0, Any p1) { invoke<Void>(0x2180AE13, p0, p1); } // 0x2180AE13
	static void _0xEE292B91(Any p0, Any p1) { invoke<Void>(0xEE292B91, p0, p1); } // 0xEE292B91
	static void _0xA063CABD() { invoke<Void>(0xA063CABD); } // 0xA063CABD
	static Any _0x62C19A3D(Any p0, Any p1) { return invoke<Any>(0x62C19A3D, p0, p1); } // 0x62C19A3D
	static void _0x3B4EF322() { invoke<Void>(0x3B4EF322); } // 0x3B4EF322
	static Any _0x54E775E0() { return invoke<Any>(0x54E775E0); } // 0x54E775E0
	static Any _0xE3F0D62D(Any p0) { return invoke<Any>(0xE3F0D62D, p0); } // 0xE3F0D62D
}

namespace BRAIN
{
	static void ADD_SCRIPT_TO_RANDOM_PED(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xECC76C3D, p0, p1, p2, p3); } // 0xECC76C3D
	static void REGISTER_OBJECT_SCRIPT_BRAIN(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xB6BCC608, p0, p1, p2, p3, p4, p5); } // 0xB6BCC608
	static BOOL IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE(Any p0) { return invoke<BOOL>(0xBA4CAA56, p0); } // 0xBA4CAA56
	static void REGISTER_WORLD_POINT_SCRIPT_BRAIN(Any p0, Any p1, Any p2) { invoke<Void>(0x725D91F7, p0, p1, p2); } // 0x725D91F7
	static BOOL IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE() { return invoke<BOOL>(0x2CF305A0); } // 0x2CF305A0
	static void ENABLE_SCRIPT_BRAIN_SET(Any p0) { invoke<Void>(0x2765919F, p0); } // 0x2765919F
	static void DISABLE_SCRIPT_BRAIN_SET(Any p0) { invoke<Void>(0xFBD13FAD, p0); } // 0xFBD13FAD
	static void _0x19B27825() { invoke<Void>(0x19B27825); } // 0x19B27825
	static void _0xF3A3AB08() { invoke<Void>(0xF3A3AB08); } // 0xF3A3AB08
	static void _0x949FE53E(Any p0) { invoke<Void>(0x949FE53E, p0); } // 0x949FE53E
	static void _0x29CE8BAA(Any p0) { invoke<Void>(0x29CE8BAA, p0); } // 0x29CE8BAA
}

namespace MOBILE
{
	static void CREATE_MOBILE_PHONE(Any p0) { invoke<Void>(0x5BBC5E23, p0); } // 0x5BBC5E23
	static void DESTROY_MOBILE_PHONE() { invoke<Void>(0x1A65037B); } // 0x1A65037B
	static void SET_MOBILE_PHONE_SCALE(float p0) { invoke<Void>(0x09BCF1BE, p0); } // 0x09BCF1BE
	static void SET_MOBILE_PHONE_ROTATION(float p0, float p1, float p2, Any p3) { invoke<Void>(0x209C28CF, p0, p1, p2, p3); } // 0x209C28CF
	static void GET_MOBILE_PHONE_ROTATION(Any p0, Any p1) { invoke<Void>(0x17A29F23, p0, p1); } // 0x17A29F23
	static void SET_MOBILE_PHONE_POSITION(float x, float y, float z) { invoke<Void>(0x841800B3, x,y,z); } // 0x841800B3
	static void GET_MOBILE_PHONE_POSITION(Any p0) { invoke<Void>(0xB2E1E1A0, p0); } // 0xB2E1E1A0
	static void SCRIPT_IS_MOVING_MOBILE_PHONE_OFFSCREEN(Any p0) { invoke<Void>(0x29828690, p0); } // 0x29828690
	static BOOL CAN_PHONE_BE_SEEN_ON_SCREEN() { return invoke<BOOL>(0x5F978584); } // 0x5F978584
	static void CELL_CAM_ACTIVATE(Any p0, Any p1) { invoke<Void>(0x234C1AE9, p0, p1); } // 0x234C1AE9
	static void _0x4479B304(Any p0) { invoke<Void>(0x4479B304, p0); } // 0x4479B304
	static void _0xC273BB4D(Any p0) { invoke<Void>(0xC273BB4D, p0); } // 0xC273BB4D
	static void _0x66DCD9D2(Any p0) { invoke<Void>(0x66DCD9D2, p0); } // 0x66DCD9D2
	static Any CELL_CAM_IS_CHAR_VISIBLE_NO_FACE_CHECK(Any p0) { return invoke<Any>(0xBEA88097, p0); } // 0xBEA88097
	static void GET_MOBILE_PHONE_RENDER_ID(int *p0) { invoke<Void>(0x88E4FECE, p0); } // 0x88E4FECE
}

namespace APP
{
	static Any APP_DATA_VALID() { return invoke<Any>(0x72BDE002); } // 0x72BDE002
	static Any APP_GET_INT(Any p0) { return invoke<Any>(0x2942AAD2, p0); } // 0x2942AAD2
	static Any APP_GET_FLOAT(Any p0) { return invoke<Any>(0xD87F3A1C, p0); } // 0xD87F3A1C
	static Any APP_GET_STRING(Any p0) { return invoke<Any>(0x849CEB80, p0); } // 0x849CEB80
	static void APP_SET_INT(Any p0, Any p1) { invoke<Void>(0x1B509C32, p0, p1); } // 0x1B509C32
	static void APP_SET_FLOAT(Any p0, Any p1) { invoke<Void>(0xF3076135, p0, p1); } // 0xF3076135
	static void APP_SET_STRING(Any p0, Any p1) { invoke<Void>(0x23DF19A8, p0, p1); } // 0x23DF19A8
	static void APP_SET_APP(Any p0) { invoke<Void>(0x8BAC4146, p0); } // 0x8BAC4146
	static void APP_SET_BLOCK(Any p0) { invoke<Void>(0xC2D54DD9, p0); } // 0xC2D54DD9
	static void APP_CLEAR_BLOCK() { invoke<Void>(0xDAB86A18); } // 0xDAB86A18
	static void APP_CLOSE_APP() { invoke<Void>(0x03767C7A); } // 0x03767C7A
	static void APP_CLOSE_BLOCK() { invoke<Void>(0xED97B202); } // 0xED97B202
	static Any _0xD368BA15() { return invoke<Any>(0xD368BA15); } // 0xD368BA15
	static Vehicle APP_HAS_SYNCED_DATA(Vehicle p0) { return invoke<Vehicle>(0x1DE2A63D, p0); } // 0x1DE2A63D
	static void APP_SAVE_DATA() { invoke<Void>(0x84A3918D); } // 0x84A3918D
	static Any _0x784D550B() { return invoke<Any>(0x784D550B); } // 0x784D550B
	static Any APP_DELETE_APP_DATA(Any p0) { return invoke<Any>(0x2A2FBD1C, p0); } // 0x2A2FBD1C
}

namespace TIME
{
	static void SET_CLOCK_TIME(Any p0, Any p1, Any p2) { invoke<Void>(0x26F6AF14, p0, p1, p2); } // 0x26F6AF14
	static void PAUSE_CLOCK(Any p0) { invoke<Void>(0xB02D6124, p0); } // 0xB02D6124
	static void _0x57B8DA7C(Any p0, Any p1, Any p2) { invoke<Void>(0x57B8DA7C, p0, p1, p2); } // 0x57B8DA7C
	static void ADD_TO_CLOCK_TIME(Any p0, Any p1, Any p2) { invoke<Void>(0xCC40D20D, p0, p1, p2); } // 0xCC40D20D
	static Any GET_CLOCK_HOURS() { return invoke<Any>(0x7EF8316F); } // 0x7EF8316F
	static Any GET_CLOCK_MINUTES() { return invoke<Any>(0x94AAC486); } // 0x94AAC486
	static Any GET_CLOCK_SECONDS() { return invoke<Any>(0x099C927E); } // 0x099C927E
	static void SET_CLOCK_DATE(Any p0, Any p1, Any p2) { invoke<Void>(0x96891C94, p0, p1, p2); } // 0x96891C94
	static Any GET_CLOCK_DAY_OF_WEEK() { return invoke<Any>(0x84E4A289); } // 0x84E4A289
	static Any GET_CLOCK_DAY_OF_MONTH() { return invoke<Any>(0xC7A5ACB7); } // 0xC7A5ACB7
	static Any GET_CLOCK_MONTH() { return invoke<Any>(0x3C48A3D5); } // 0x3C48A3D5
	static Any GET_CLOCK_YEAR() { return invoke<Any>(0xB8BECF15); } // 0xB8BECF15
	static Any _0x3B74095C() { return invoke<Any>(0x3B74095C); } // 0x3B74095C
	static void GET_POSIX_TIME(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xE15A5281, p0, p1, p2, p3, p4, p5); } // 0xE15A5281
	static void GET_LOCAL_TIME(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x124BCFA2, p0, p1, p2, p3, p4, p5); } // 0x124BCFA2
}

namespace PATHFIND
{
	static void SET_ROADS_IN_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0xEBC7B918, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xEBC7B918
	static void SET_ROADS_IN_ANGLED_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0xBD088F4B, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xBD088F4B
	static void SET_PED_PATHS_IN_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x2148EA84, p0, p1, p2, p3, p4, p5, p6); } // 0x2148EA84
	static Any GET_SAFE_COORD_FOR_PED(float x, float y, float z, Any p3, Object* outVector, Any p5) { return invoke<Any>(0xB370270A, x, y, z, p3, outVector, p5); } // 0xB370270A
	static int GET_CLOSEST_VEHICLE_NODE(float x, float y, float z, float* nodeX, int p4, float p5, float p6) { return invoke<int>(0x6F5F1E6C, x, y, z, nodeX, p4, p5, p6); } // 0x6F5F1E6C
	static Any GET_CLOSEST_MAJOR_VEHICLE_NODE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x04B5F15B, p0, p1, p2, p3, p4, p5); } // 0x04B5F15B
	static Any GET_CLOSEST_VEHICLE_NODE_WITH_HEADING(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<Any>(0x8BD5759B, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x8BD5759B
	static Any GET_NTH_CLOSEST_VEHICLE_NODE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<Any>(0xF125BFCC, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xF125BFCC
	static Any GET_NTH_CLOSEST_VEHICLE_NODE_ID(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0x3F358BEA, p0, p1, p2, p3, p4, p5, p6); } // 0x3F358BEA
	static Any GET_NTH_CLOSEST_VEHICLE_NODE_WITH_HEADING(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<Any>(0x7349C856, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x7349C856
	static Any GET_NTH_CLOSEST_VEHICLE_NODE_ID_WITH_HEADING(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<Any>(0xC1AEB88D, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xC1AEB88D
	static Any GET_NTH_CLOSEST_VEHICLE_NODE_FAVOUR_DIRECTION(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { return invoke<Any>(0x928A4DEC, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0x928A4DEC
	static Any GET_VEHICLE_NODE_PROPERTIES(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xCC90110B, p0, p1, p2, p3, p4); } // 0xCC90110B
	static BOOL IS_VEHICLE_NODE_ID_VALID(Any p0) { return invoke<BOOL>(0x57DFB1EF, p0); } // 0x57DFB1EF
	static void GET_VEHICLE_NODE_POSITION(Any p0, Any p1) { invoke<Void>(0xE38E252D, p0, p1); } // 0xE38E252D
	static Any _0xEE4B1219(Any p0) { return invoke<Any>(0xEE4B1219, p0); } // 0xEE4B1219
	static Any _0x56737A3C(Any p0) { return invoke<Any>(0x56737A3C, p0); } // 0x56737A3C
	static Any GET_CLOSEST_ROAD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return invoke<Any>(0x567B0E11, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x567B0E11
	static Any LOAD_ALL_PATH_NODES(Any p0) { return invoke<Any>(0xC66E28C3, p0); } // 0xC66E28C3
	static void _0xD6A3B458(Any p0) { invoke<Void>(0xD6A3B458, p0); } // 0xD6A3B458
	static Any _0x86E80A17(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x86E80A17, p0, p1, p2, p3); } // 0x86E80A17
	static Any _0x2CDA5012(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x2CDA5012, p0, p1, p2, p3); } // 0x2CDA5012
	static void SET_ROADS_BACK_TO_ORIGINAL(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x86AC4A85, p0, p1, p2, p3, p4, p5); } // 0x86AC4A85
	static void SET_ROADS_BACK_TO_ORIGINAL_IN_ANGLED_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x9DB5D209, p0, p1, p2, p3, p4, p5, p6); } // 0x9DB5D209
	static void _0x3C5085E4(Any p0) { invoke<Void>(0x3C5085E4, p0); } // 0x3C5085E4
	static void _0xD0F51299(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0xD0F51299, p0, p1, p2, p3, p4, p5, p6); } // 0xD0F51299
	static void SET_PED_PATHS_BACK_TO_ORIGINAL(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x3F1ABDA4, p0, p1, p2, p3, p4, p5); } // 0x3F1ABDA4
	static Any GET_RANDOM_VEHICLE_NODE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<Any>(0xAD1476EA, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xAD1476EA
	static void GET_STREET_NAME_AT_COORD(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xDEBEEFCF, p0, p1, p2, p3, p4); } // 0xDEBEEFCF
	static Any GENERATE_DIRECTIONS_TO_COORD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0xED35C094, p0, p1, p2, p3, p4, p5, p6); } // 0xED35C094
	static void SET_IGNORE_NO_GPS_FLAG(Any p0) { invoke<Void>(0xB72CF194, p0); } // 0xB72CF194
	static void _0x90DF7A4C(Any p0) { invoke<Void>(0x90DF7A4C, p0); } // 0x90DF7A4C
	static void SET_GPS_DISABLED_ZONE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x720B8073, p0, p1, p2, p3, p4, p5); } // 0x720B8073
	static Any _0x4B770634() { return invoke<Any>(0x4B770634); } // 0x4B770634
	static Any _0x286F82CC() { return invoke<Any>(0x286F82CC); } // 0x286F82CC
	static Any _0xF6422F9A(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xF6422F9A, p0, p1, p2, p3, p4); } // 0xF6422F9A
	static BOOL IS_POINT_ON_ROAD(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0xCF198055, p0, p1, p2, p3); } // 0xCF198055
	static void ADD_NAVMESH_REQUIRED_REGION(Any p0, Any p1, Any p2) { invoke<Void>(0x12B086EA, p0, p1, p2); } // 0x12B086EA
	static void REMOVE_NAVMESH_REQUIRED_REGIONS() { invoke<Void>(0x637BB680); } // 0x637BB680
	static void DISABLE_NAVMESH_IN_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x6E37F132, p0, p1, p2, p3, p4, p5, p6); } // 0x6E37F132
	static BOOL ARE_ALL_NAVMESH_REGIONS_LOADED() { return invoke<BOOL>(0x34C4E789); } // 0x34C4E789
	static BOOL IS_NAVMESH_LOADED_IN_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<BOOL>(0x4C2BA99E, p0, p1, p2, p3, p4, p5); } // 0x4C2BA99E
	static Any ADD_NAVMESH_BLOCKING_OBJECT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<Any>(0x2952BA56, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x2952BA56
	static void UPDATE_NAVMESH_BLOCKING_OBJECT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0x4E9776D0, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x4E9776D0
	static void REMOVE_NAVMESH_BLOCKING_OBJECT(Any p0) { invoke<Void>(0x098602B0, p0); } // 0x098602B0
	static Any _0x4B67D7EE(Any p0) { return invoke<Any>(0x4B67D7EE, p0); } // 0x4B67D7EE
	static Any _0x3FE8C5A0(Any p0, Any p1) { return invoke<Any>(0x3FE8C5A0, p0, p1); } // 0x3FE8C5A0
	static Any _0x3ED21C90(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x3ED21C90, p0, p1, p2, p3); } // 0x3ED21C90
	static Any _0xA07C5B7D(Any p0, Any p1) { return invoke<Any>(0xA07C5B7D, p0, p1); } // 0xA07C5B7D
	static Any _0x76751DD4(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x76751DD4, p0, p1, p2, p3); } // 0x76751DD4
	static Any CALCULATE_TRAVEL_DISTANCE_BETWEEN_POINTS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0xB114489B, p0, p1, p2, p3, p4, p5); } // 0xB114489B
}

namespace CONTROLS
{
	static BOOL IS_CONTROL_ENABLED(int Index, int Control) { return invoke<BOOL>(0x9174AF84, Index, Control); } // 0x9174AF84
	static BOOL IS_CONTROL_PRESSED(int Index, int Control) { return invoke<BOOL>(0x517A4384, Index, Control) || invoke<BOOL>(0x32A93544, Index, Control); } // 0x517A4384
	static BOOL IS_CONTROL_RELEASED(int Index, int Control) { return invoke<BOOL>(0x1F91A06E, Index, Control); } // 0x1F91A06E
	static BOOL IS_CONTROL_JUST_PRESSED(int Index, int Control) { return invoke<BOOL>(0x4487F579, Index, Control) || invoke<BOOL>(0xEE6ABD32, Index, Control); } // 0x4487F579
	static BOOL IS_CONTROL_JUST_RELEASED(int Index, int Control) { return invoke<BOOL>(0x2314444B, Index, Control); } // 0x2314444B
	static Any GET_CONTROL_VALUE(Any p0, Any p1) { return invoke<Any>(0xC526F3C6, p0, p1); } // 0xC526F3C6
	static Any GET_CONTROL_NORMAL(Any p0, Any p1) { return invoke<Any>(0x5DE226A5, p0, p1); } // 0x5DE226A5
	static Any _0xC49343BB(Any p0, Any p1) { return invoke<Any>(0xC49343BB, p0, p1); } // 0xC49343BB
	static BOOL IS_DISABLED_CONTROL_PRESSED(int Index, int Control) { return invoke<BOOL>(0x32A93544, Index, Control); } // 0x32A93544
	static BOOL IS_DISABLED_CONTROL_JUST_PRESSED(int Index, int Control) { return invoke<BOOL>(0xEE6ABD32, Index, Control); } // 0xEE6ABD32
	static BOOL IS_DISABLED_CONTROL_JUST_RELEASED(int Index, Any Control) { return invoke<BOOL>(0xD6A679E1, Index, Control); } // 0xD6A679E1
	static Any GET_DISABLED_CONTROL_NORMAL(Any p0, Any p1) { return invoke<Any>(0x66FF4FAA, p0, p1); } // 0x66FF4FAA
	static Any _0xF2A65A4C(Any p0, Any p1) { return invoke<Any>(0xF2A65A4C, p0, p1); } // 0xF2A65A4C
	static Any _0x0E8EF929(Any p0) { return invoke<Any>(0x0E8EF929, p0); } // 0x0E8EF929
	static Any _0x3551727A(Any p0, Any p1, Any p2) { return invoke<Any>(0x3551727A, p0, p1, p2); } // 0x3551727A
	static Any _0x3EE71F6A(Any p0, Any p1, Any p2) { return invoke<Any>(0x3EE71F6A, p0, p1, p2); } // 0x3EE71F6A
	static void SET_PAD_SHAKE(Any p0, Any p1, Any p2) { invoke<Void>(0x5D38BD2F, p0, p1, p2); } // 0x5D38BD2F
	static void STOP_PAD_SHAKE(Any p0) { invoke<Void>(0x8F75657E, p0); } // 0x8F75657E
	static void _0x7D65EB6E(Any p0, Any p1) { invoke<Void>(0x7D65EB6E, p0, p1); } // 0x7D65EB6E
	static void SET_CONTROL_SHAKE(Any p0, Any p1, Any p2) { invoke<Void>(0xF63D817A, p0, p1, p2); } // 0xF63D817A
	static BOOL IS_LOOK_INVERTED() { return invoke<BOOL>(0x313434B2); } // 0x313434B2
	static Any GET_LOCAL_PLAYER_AIM_STATE() { return invoke<Any>(0x81802053); } // 0x81802053
	static void SET_PLAYERPAD_SHAKES_WHEN_CONTROLLER_DISABLED(Any p0) { invoke<Void>(0xA86BD91F, p0); } // 0xA86BD91F
	static void SET_INPUT_EXCLUSIVE(int Index, int Control) { invoke<Void>(0x4E8E29E6, Index, Control); } // 0x4E8E29E6
	static void DISABLE_CONTROL_ACTION(int Index, int Control) { invoke<Void>(0x3800C0DC, Index, Control); } // 0x3800C0DC
	static void ENABLE_CONTROL_ACTION(int Index, int Control) { invoke<Void>(0xD2753551, Index, Control); } // 0xD2753551
	static void DISABLE_ALL_CONTROL_ACTIONS(int Index) { invoke<Void>(0x16753CF4, Index); } // 0x16753CF4
	static void ENABLE_ALL_CONTROL_ACTIONS(int Index) { invoke<Void>(0xFC2F119F, Index); } // 0xFC2F119F
	static Any _0xD2C80B2E(char* p0) { return invoke<Any>(0xD2C80B2E, p0); } // 0xD2C80B2E
	static Any _0xBBFC9050(Any p0) { return invoke<Any>(0xBBFC9050, p0); } // 0xBBFC9050
	static void _0x42140FF9() { invoke<Void>(0x42140FF9); } // 0x42140FF9
	static void _0x2CEDE6C5(Any p0) { invoke<Void>(0x2CEDE6C5, p0); } // 0x2CEDE6C5
}

namespace DATAFILE
{
	static void _0x621388FF(Any p0) { invoke<Void>(0x621388FF, p0); } // 0x621388FF
	static Any _0xB41064A4(Any p0) { return invoke<Any>(0xB41064A4, p0); } // 0xB41064A4
	static Any _0x9DB63CFF(Any p0) { return invoke<Any>(0x9DB63CFF, p0); } // 0x9DB63CFF
	static Any _0xF09157B0(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0xF09157B0, p0, p1, p2, p3, p4, p5, p6); } // 0xF09157B0
	static Any _0xD96860FC(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xD96860FC, p0, p1, p2, p3, p4); } // 0xD96860FC
	static Any _0x459F2683(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0x459F2683, p0, p1, p2, p3, p4, p5, p6); } // 0x459F2683
	static Any _0xDBB83E2B(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xDBB83E2B, p0, p1, p2, p3, p4); } // 0xDBB83E2B
	static Any _0xBB6321BD(Any p0, Any p1, Any p2) { return invoke<Any>(0xBB6321BD, p0, p1, p2); } // 0xBB6321BD
	static Any _0xE8D56DA2(Any p0) { return invoke<Any>(0xE8D56DA2, p0); } // 0xE8D56DA2
	static Any _0xCB6A351E(Any p0, Any p1) { return invoke<Any>(0xCB6A351E, p0, p1); } // 0xCB6A351E
	static Any _0xA4D1B30E(Any p0) { return invoke<Any>(0xA4D1B30E, p0); } // 0xA4D1B30E
	static Any _0xB8515B2F(Any p0) { return invoke<Any>(0xB8515B2F, p0); } // 0xB8515B2F
	static Any _0x660C468E(Any p0) { return invoke<Any>(0x660C468E, p0); } // 0x660C468E
	static void DATAFILE_CREATE() { invoke<Void>(0x95F8A221); } // 0x95F8A221
	static void DATAFILE_DELETE() { invoke<Void>(0xDEF31B0A); } // 0xDEF31B0A
	static void _0x4E03F632() { invoke<Void>(0x4E03F632); } // 0x4E03F632
	static void _0xF11F956F() { invoke<Void>(0xF11F956F); } // 0xF11F956F
	static Any PRELOAD_FIND() { return invoke<Any>(0x86DDF9C2); } // 0x86DDF9C2
	static Any _0x768CBB35(Any p0) { return invoke<Any>(0x768CBB35, p0); } // 0x768CBB35
	static Any _0x0B4087F7(Any p0) { return invoke<Any>(0x0B4087F7, p0); } // 0x0B4087F7
	static Any _0x5DCD0796() { return invoke<Any>(0x5DCD0796); } // 0x5DCD0796
	static void _0x9B29D99B(Any p0, Any p1, Any p2) { invoke<Void>(0x9B29D99B, p0, p1, p2); } // 0x9B29D99B
	static void _0xEFCF554A(Any p0, Any p1, Any p2) { invoke<Void>(0xEFCF554A, p0, p1, p2); } // 0xEFCF554A
	static void _0xE972CACF(Any p0, Any p1, Any p2) { invoke<Void>(0xE972CACF, p0, p1, p2); } // 0xE972CACF
	static void _0xD437615C(Any p0, Any p1, Any p2) { invoke<Void>(0xD437615C, p0, p1, p2); } // 0xD437615C
	static void _0x75FC6C3C(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x75FC6C3C, p0, p1, p2, p3, p4); } // 0x75FC6C3C
	static Any _0x96A8E05F(Any p0, Any p1) { return invoke<Any>(0x96A8E05F, p0, p1); } // 0x96A8E05F
	static Any _0x03939B8D(Any p0, Any p1) { return invoke<Any>(0x03939B8D, p0, p1); } // 0x03939B8D
	static Any _0x8876C872(Any p0, Any p1) { return invoke<Any>(0x8876C872, p0, p1); } // 0x8876C872
	static Any _0xA6C68693(Any p0, Any p1) { return invoke<Any>(0xA6C68693, p0, p1); } // 0xA6C68693
	static Any _0xA92C1AF4(Any p0, Any p1) { return invoke<Any>(0xA92C1AF4, p0, p1); } // 0xA92C1AF4
	static Any _0x942160EC(Any p0, Any p1) { return invoke<Any>(0x942160EC, p0, p1); } // 0x942160EC
	static Vector3 _0xE84A127A(Any p0, Any p1) { return invoke<Vector3>(0xE84A127A, p0, p1); } // 0xE84A127A
	static Any _0xC9C13D8D(Any p0, Any p1) { return invoke<Any>(0xC9C13D8D, p0, p1); } // 0xC9C13D8D
	static Any _0x1F2F7D00(Any p0, Any p1) { return invoke<Any>(0x1F2F7D00, p0, p1); } // 0x1F2F7D00
	static Any _0x2678342A(Any p0, Any p1) { return invoke<Any>(0x2678342A, p0, p1); } // 0x2678342A
	static void _0x08174B90(Any p0, Any p1) { invoke<Void>(0x08174B90, p0, p1); } // 0x08174B90
	static void _0xF29C0B36(Any p0, Any p1) { invoke<Void>(0xF29C0B36, p0, p1); } // 0xF29C0B36
	static void _0xE4302123(Any p0, Any p1) { invoke<Void>(0xE4302123, p0, p1); } // 0xE4302123
	static void _0xF3C01350(Any p0, Any p1) { invoke<Void>(0xF3C01350, p0, p1); } // 0xF3C01350
	static void _0x16F464B6(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x16F464B6, p0, p1, p2, p3); } // 0x16F464B6
	static Any _0xC174C71B(Any p0) { return invoke<Any>(0xC174C71B, p0); } // 0xC174C71B
	static Any _0xA2E5F921(Any p0, Any p1) { return invoke<Any>(0xA2E5F921, p0, p1); } // 0xA2E5F921
	static Any _0xBB120CFC(Any p0, Any p1) { return invoke<Any>(0xBB120CFC, p0, p1); } // 0xBB120CFC
	static Any FOCUS_USE_SPLINE(Any p0, Any p1) { return invoke<Any>(0x08AD2CC2, p0, p1); } // 0x08AD2CC2
	static Any OVERIDE_TEXTURENAMES(Any p0, Any p1) { return invoke<Any>(0x93F985A6, p0, p1); } // 0x93F985A6
	static Vector3 _0x80E3DA55(Any p0, Any p1) { return invoke<Vector3>(0x80E3DA55, p0, p1); } // 0x80E3DA55
	static Any _0xECE81278(Any p0, Any p1) { return invoke<Any>(0xECE81278, p0, p1); } // 0xECE81278
	static Any _0xA8A21766(Any p0) { return invoke<Any>(0xA8A21766, p0); } // 0xA8A21766
	static Any _0xFA2402C8(Any p0, Any p1) { return invoke<Any>(0xFA2402C8, p0, p1); } // 0xFA2402C8
}

namespace FIRE
{
	static Any START_SCRIPT_FIRE(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xE7529357, p0, p1, p2, p3, p4); } // 0xE7529357
	static void REMOVE_SCRIPT_FIRE(Any p0) { invoke<Void>(0x6B21FE26, p0); } // 0x6B21FE26
	static Any START_ENTITY_FIRE(Entity Entity) { return invoke<Any>(0x8928428E, Entity); } // 0x8928428E
	static void STOP_ENTITY_FIRE(Entity Entity) { invoke<Void>(0xCE8C9066, Entity); } // 0xCE8C9066
	static BOOL IS_ENTITY_ON_FIRE(Any p0) { return invoke<BOOL>(0x8C73E64F, p0); } // 0x8C73E64F
	static Any GET_NUMBER_OF_FIRES_IN_RANGE(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x654D93B7, p0, p1, p2, p3); } // 0x654D93B7
	static void STOP_FIRE_IN_RANGE(float p0, float p1, float p2, float p3) { invoke<Void>(0x725C7205, p0, p1, p2, p3); } // 0x725C7205
	static Any GET_CLOSEST_FIRE_POS(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xC4977B47, p0, p1, p2, p3); } // 0xC4977B47
	static void ADD_EXPLOSION(float XCoordinate, float YCoordinate, float ZCoordinate, int ExplosionType, float ExplosionRadius, BOOL isAudible, BOOL isVisible, float CameraShake) { invoke<Void>(0x10AF5258, XCoordinate, YCoordinate, ZCoordinate, ExplosionType, ExplosionRadius, isAudible, isVisible, CameraShake); } // 0x10AF5258
	static void ADD_OWNED_EXPLOSION(Ped PedHandle, float XCoordinate, float YCoordinate, float ZCoordinate, int ExlosionType, float ExplosionRadius, BOOL IsAudible, BOOL IsVisible, float CamerShake) { invoke<Void>(0x27EE0D67, PedHandle, XCoordinate, YCoordinate, ZCoordinate, ExlosionType, ExplosionRadius, IsAudible, IsVisible, CamerShake); } // 0x27EE0D67
	static void _0xCF358946(float* XCoord, float* YCoord, float* ZCoord, int unk, Hash ExplsionFX, float ExlosionRadius, BOOL isAudible, BOOL isVisible, float unk2) { invoke<Void>(0xCF358946, XCoord, YCoord, ZCoord, unk, ExplsionFX, ExlosionRadius, isAudible, isVisible, unk2); } // 0xCF358946
	static BOOL IS_EXPLOSION_IN_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<BOOL>(0xFB40075B, p0, p1, p2, p3, p4, p5, p6); } // 0xFB40075B
	static BOOL IS_EXPLOSION_IN_SPHERE(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<BOOL>(0xD455A7F3, p0, p1, p2, p3, p4); } // 0xD455A7F3
	static BOOL IS_EXPLOSION_IN_ANGLED_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<BOOL>(0x0128FED9, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x0128FED9
	static Any _0xAEC0D176(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<Any>(0xAEC0D176, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xAEC0D176
}

namespace DECISIONEVENT
{
	static void SET_DECISION_MAKER(Any p0, Any p1) { invoke<Void>(0x19CEAC9E, p0, p1); } // 0x19CEAC9E
	static void CLEAR_DECISION_MAKER_EVENT_RESPONSE(Any p0, Any p1) { invoke<Void>(0x07ABD94D, p0, p1); } // 0x07ABD94D
	static void _0x57506EA6(Any p0, Any p1) { invoke<Void>(0x57506EA6, p0, p1); } // 0x57506EA6
	static void _0x62A3161D(Any p0, Any p1) { invoke<Void>(0x62A3161D, p0, p1); } // 0x62A3161D
	static Any ADD_SHOCKING_EVENT_AT_POSITION(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x0B30F779, p0, p1, p2, p3, p4); } // 0x0B30F779
	static Any ADD_SHOCKING_EVENT_FOR_ENTITY(Any p0, Any p1, Any p2) { return invoke<Any>(0xA81B5B71, p0, p1, p2); } // 0xA81B5B71
	static BOOL IS_SHOCKING_EVENT_IN_SPHERE(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<BOOL>(0x2F98823E, p0, p1, p2, p3, p4); } // 0x2F98823E
	static Any REMOVE_SHOCKING_EVENT(Any p0) { return invoke<Any>(0xF82D5A87, p0); } // 0xF82D5A87
	static void REMOVE_ALL_SHOCKING_EVENTS(Any p0) { invoke<Void>(0x64DF6282, p0); } // 0x64DF6282
	static void _0xA0CE89C8() { invoke<Void>(0xA0CE89C8); } // 0xA0CE89C8
	static void _0x4CC674B5() { invoke<Void>(0x4CC674B5); } // 0x4CC674B5
	static void _0xA0FDCB82(Any p0) { invoke<Void>(0xA0FDCB82, p0); } // 0xA0FDCB82
	static void _0x80340396() { invoke<Void>(0x80340396); } // 0x80340396
}

namespace ZONE
{
	static Any GET_ZONE_AT_COORDS(float x, float y, float z) { return invoke<Any>(0xC9018181, x, y, z); } // 0xC9018181
	static Any _0x8EC68304(Any p0) { return invoke<Any>(0x8EC68304, p0); } // 0x8EC68304
	static Any GET_ZONE_POPSCHEDULE(Any p0) { return invoke<Any>(0x20AB2FC9, p0); } // 0x20AB2FC9
	static char* GET_NAME_OF_ZONE(float x, float y, float z) { return invoke<char*>(0x7875CE91, x, y, z); } // 0x7875CE91
	static void SET_ZONE_ENABLED(Any p0, Any p1) { invoke<Void>(0x04E21B03, p0, p1); } // 0x04E21B03
	static Any GET_ZONE_SCUMMINESS(Any p0) { return invoke<Any>(0xB2FB5C4C, p0); } // 0xB2FB5C4C
	static void _0x3F0A3680(Any p0, Any p1) { invoke<Void>(0x3F0A3680, p0, p1); } // 0x3F0A3680
	static void _0x7A72A24E(Any p0) { invoke<Void>(0x7A72A24E, p0); } // 0x7A72A24E
	static Any _0xB5C5C99B(Any p0, Any p1, Any p2) { return invoke<Any>(0xB5C5C99B, p0, p1, p2); } // 0xB5C5C99B
}

namespace ROPE
{
	static Object ADD_ROPE(float position_x, float position_y, float position_z, float angle_x, float angle_y, float angle_z, float length, int type, float max_length, float min_length, float p10, BOOL p11, BOOL p12, BOOL p13, float p14, BOOL breakable, int p16) { return invoke<Object>(0xA592EC74, position_x, position_y, position_z, angle_x, angle_y, angle_z, length, type, max_length, min_length, p10, p11, p12, p13, p14, breakable, p16); } // 0xA592EC74
	static void DELETE_ROPE(Object *rope) { invoke<Void>(0x748D72AF, rope); } // 0x748D72AF
	static void DELETE_CHILD_ROPE(Object rope) { invoke<Void>(0xB19B4706, rope); } // 0xB19B4706
	static BOOL DOES_ROPE_EXIST(Object *rope) { return invoke<BOOL>(0x66E4A3AC, rope); } // 0x66E4A3AC
	static void _0x51523B8C(Any p0, Any p1) { invoke<Void>(0x51523B8C, p0, p1); } // 0x51523B8C
	static void LOAD_ROPE_DATA(Object rope, char* rope_preset) { invoke<Void>(0x9E8F1644, rope, rope_preset); } // 0x9E8F1644
	static void PIN_ROPE_VERTEX(Object rople, int vertex, float x, float y, float z) { invoke<Void>(0xAE1D101B, rople, vertex, x, y, z); } // 0xAE1D101B
	static void UNPIN_ROPE_VERTEX(Object rope, int vertex) { invoke<Void>(0xB30B552F, rope, vertex); } // 0xB30B552F
	static int GET_ROPE_VERTEX_COUNT(Object rope) { return invoke<int>(0x5131CD2C, rope); } // 0x5131CD2C
	static void ATTACH_ENTITIES_TO_ROPE(Object rope, Entity ent1, Entity ent2, float ent1_x, float ent1_y, float ent1_z, float ent2_x, float ent2_y, float ent2_z, float length, BOOL p10, BOOL p11, BOOL p12, BOOL p13) { invoke<Void>(0x7508668F, rope, ent1, ent2, ent1_x, ent1_y, ent1_z, ent2_x, ent2_y, ent2_z, length, p10, p11, p12, p13); } // 0x7508668F
	static void ATTACH_ROPE_TO_ENTITY(Any rope, Entity entity, float x, float y, float z, BOOL p5) { invoke<Void>(0xB25D9536, rope, entity, x, y, z, p5); } // 0xB25D9536
	static void DETACH_ROPE_FROM_ENTITY(Any rope, Entity entity) { invoke<Void>(0x3E720BEE, rope, entity); } // 0x3E720BEE
	static void _0xEAF291A0(Any p0) { invoke<Void>(0xEAF291A0, p0); } // 0xEAF291A0
	static void _0x80DB77A7(Any p0, Any p1) { invoke<Void>(0x80DB77A7, p0, p1); } // 0x80DB77A7
	static void _0xC67D5CF6(Any p0, Any p1) { invoke<Void>(0xC67D5CF6, p0, p1); } // 0xC67D5CF6
	static Any _0x7A18BB9C(Any p0) { return invoke<Any>(0x7A18BB9C, p0); } // 0x7A18BB9C
	static Vector3 GET_ROPE_LAST_VERTEX_COORD(Object rope) { return invoke<Vector3>(0x91F6848B, rope); } // 0x91F6848B
	static Vector3 GET_ROPE_VERTEX_COORD(Object rope, int vertex) { return invoke<Vector3>(0x84374452, rope, vertex); } // 0x84374452
	static void _0x5187BED3(Any p0) { invoke<Void>(0x5187BED3, p0); } // 0x5187BED3
	static void _0x46826B53(Any p0) { invoke<Void>(0x46826B53, p0); } // 0x46826B53
	static void _0xFC0DB4C3(Any p0) { invoke<Void>(0xFC0DB4C3, p0); } // 0xFC0DB4C3
	static void _0x2EEDB18F(Any p0) { invoke<Void>(0x2EEDB18F, p0); } // 0x2EEDB18F
	static void _0x43E92628(Any p0) { invoke<Void>(0x43E92628, p0); } // 0x43E92628
	static void ROPE_LOAD_TEXTURES() { invoke<Void>(0xBA97CE91); } // 0xBA97CE91
	static Any _0x5FDC1047() { return invoke<Any>(0x5FDC1047); } // 0x5FDC1047
	static void ROPE_UNLOAD_TEXTURES() { invoke<Void>(0x584463E0); } // 0x584463E0
	static Any _0x67522E25(Any p0) { return invoke<Any>(0x67522E25, p0); } // 0x67522E25
	static void _0x106BA127(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13) { invoke<Void>(0x106BA127, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); } // 0x106BA127
	static void _0x7C6F7668(Any p0, Any p1, Any p2) { invoke<Void>(0x7C6F7668, p0, p1, p2); } // 0x7C6F7668
	static void _0x686672DD(Any p0, Any p1) { invoke<Void>(0x686672DD, p0, p1); } // 0x686672DD
	static Any _0xFD309DC8(Any p0) { return invoke<Any>(0xFD309DC8, p0); } // 0xFD309DC8
	static void ROPE_FORCE_LENGTH(Object rope, float length) { invoke<Void>(0xABF3130F, rope, length); } // 0xABF3130F
	static void ROPE_RESET_LENGTH(Object rope, float length) { invoke<Void>(0xC8A423A3, rope, length); } // 0xC8A423A3
	static void _0xA2A5C9FE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0xA2A5C9FE, p0, p1, p2, p3, p4, p5, p6); } // 0xA2A5C9FE
	static void SET_DAMPING(Any p0, Any p1, Any p2) { invoke<Void>(0xCFB37773, p0, p1, p2); } // 0xCFB37773
	static void ACTIVATE_PHYSICS(Object rope) { invoke<Void>(0x031711B8, rope); } // 0x031711B8
	static void _0x59910AB2(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x59910AB2, p0, p1, p2, p3); } // 0x59910AB2
	static Vector3 _0x49A11F0D(Any p0) { return invoke<Vector3>(0x49A11F0D, p0); } // 0x49A11F0D
	static void _0xA5B55421(Any p0) { invoke<Void>(0xA5B55421, p0); } // 0xA5B55421
	static void BREAK_ENTITY_GLASS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { invoke<Void>(0xD0E0402F, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0xD0E0402F
	static void SET_DISABLE_BREAKING(Object rope, BOOL enabled) { invoke<Void>(0xEE77C326, rope, enabled); } // 0xEE77C326
	static void _0x97269DC8(Any p0, Any p1) { invoke<Void>(0x97269DC8, p0, p1); } // 0x97269DC8
}

namespace WATER
{
	static Any GET_WATER_HEIGHT(float x, float y, float p2, float p3) { return invoke<Any>(0xD864E17C, x, y, p2, p3); } // 0xD864E17C
	static Any GET_WATER_HEIGHT_NO_WAVES(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x262017F8, p0, p1, p2, p3); } // 0x262017F8
	static Any _0xAA4AE00C(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0xAA4AE00C, p0, p1, p2, p3, p4, p5, p6); } // 0xAA4AE00C
	static Any _0x4A962D55(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<Any>(0x4A962D55, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x4A962D55
	static Any _0x4C71D143(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x4C71D143, p0, p1, p2, p3, p4); } // 0x4C71D143
	static void MODIFY_WATER(float p0, float p1, float p2, Any p3) { invoke<Void>(0xC49E005A, p0, p1, p2, p3); } // 0xC49E005A
}

namespace WORLDPROBE
{
	static Any _0xEFAF4BA6(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<Any>(0xEFAF4BA6, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xEFAF4BA6
	static Any _0x8251485D(float x1, float y1, float z1, float x2, float y2, float z2, int flags, Entity entity, int p8) { return invoke<Any>(0x8251485D, x1, y1, z1, x2, y2, z2, flags, entity, p8); } // 0x8251485D
	static Any _0xCEEAD94B(Any p0, Any p1, Any p2) { return invoke<Any>(0xCEEAD94B, p0, p1, p2); } // 0xCEEAD94B
	static Any _0x249BC876(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { return invoke<Any>(0x249BC876, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0x249BC876
	static Any _0x13BC46C0(Any p0, Any p1, Any p2) { return invoke<Any>(0x13BC46C0, p0, p1, p2); } // 0x13BC46C0
	static Any _0x591EA833(float x1, float y1, float z1, float x2, float y2, float z2,float radius, int flags, Entity entity, int p8) { return invoke<Any>(0x591EA833, x1, y1, z1, x2, y2, z2,radius, flags, entity, p8); } // 0x591EA833
	static Any _0x4559460A(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<Any>(0x4559460A, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x4559460A
	static Any _0xF3C2875A(int rayHandle, BOOL *hit, Vector3 *endCoords, Vector3 *surfaceNormal, Entity *entityHit) { return invoke<Any>(0xF3C2875A, rayHandle, hit, endCoords, surfaceNormal, entityHit); } // 0xF3C2875A
	static Any _0x4301E10C(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x4301E10C, p0, p1, p2, p3, p4, p5); } // 0x4301E10C
	static void _0xEC2AAF06(Any p0) { invoke<Void>(0xEC2AAF06, p0); } // 0xEC2AAF06
}

namespace NETWORK
{
	static bool _0x99F58A07(int ped, int player) { return invoke<bool>(0x99F58A07,ped,player); };
	static Any NETWORK_IS_SIGNED_IN() { return invoke<Any>(0xADD0B40F); } // 0xADD0B40F
	static Any NETWORK_IS_SIGNED_ONLINE() { return invoke<Any>(0x6E5BDCE2); } // 0x6E5BDCE2
	static Any _0x3FB40673() { return invoke<Any>(0x3FB40673); } // 0x3FB40673
	static Any NETWORK_IS_CLOUD_AVAILABLE() { return invoke<Any>(0xC7FF5AFC); } // 0xC7FF5AFC
	static Any _0x66EC713F() { return invoke<Any>(0x66EC713F); } // 0x66EC713F
	static Any _0x358D1D77() { return invoke<Any>(0x358D1D77); } // 0x358D1D77
	static Any NETWORK_IS_HOST() { return invoke<Any>(0xE46AC10F); } // 0xE46AC10F
	static Any NETWORK_HAVE_ONLINE_PRIVILEGES() { return invoke<Any>(0xEF63BFDF); } // 0xEF63BFDF
	static Any _0x1F88819D(Any p0) { return invoke<Any>(0x1F88819D, p0); } // 0x1F88819D
	static Any _0x2D817A5E(Any p0, Any p1) { return invoke<Any>(0x2D817A5E, p0, p1); } // 0x2D817A5E
	static Any _0xBB54AA3D(Any p0, Any p1, Any p2) { return invoke<Any>(0xBB54AA3D, p0, p1, p2); } // 0xBB54AA3D
	static Any _0xA79E5B05(Any p0, Any p1, Any p2) { return invoke<Any>(0xA79E5B05, p0, p1, p2); } // 0xA79E5B05
	static Any _0xEB864288() { return invoke<Any>(0xEB864288); } // 0xEB864288
	static Any _0xAB07CBBE() { return invoke<Any>(0xAB07CBBE); } // 0xAB07CBBE
	static Any _0x60E1FEDF() { return invoke<Any>(0x60E1FEDF); } // 0x60E1FEDF
	static void NETWORK_BAIL() { invoke<Void>(0x87D79A04); } // 0x87D79A04
	static void _0x96E28FE2() { invoke<Void>(0x96E28FE2); } // 0x96E28FE2
	static Any _0xA520B982(Any p0) { return invoke<Any>(0xA520B982, p0); } // 0xA520B982
	static Any _0x05518C0F() { return invoke<Any>(0x05518C0F); } // 0x05518C0F
	static Any NETWORK_CAN_ENTER_MULTIPLAYER() { return invoke<Any>(0x4A23B9C9); } // 0x4A23B9C9
	static Any NETWORK_SESSION_ENTER(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x543CD2BE, p0, p1, p2, p3, p4, p5); } // 0x543CD2BE
	static Any _0x4E53202A(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x4E53202A, p0, p1, p2, p3); } // 0x4E53202A
	static Any _0xD7624E6B(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xD7624E6B, p0, p1, p2, p3, p4); } // 0xD7624E6B
	static Any _0x3F75CC38(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x3F75CC38, p0, p1, p2, p3); } // 0x3F75CC38
	static Any NETWORK_SESSION_HOST(Any p0, Any p1, Any p2) { return invoke<Any>(0x6716460F, p0, p1, p2); } // 0x6716460F
	static Any _0x8AC9EA19(Any p0, Any p1) { return invoke<Any>(0x8AC9EA19, p0, p1); } // 0x8AC9EA19
	static Any NETWORK_SESSION_HOST_FRIENDS_ONLY(Any p0, Any p1) { return invoke<Any>(0x26864403, p0, p1); } // 0x26864403
	static Any _0x56E75FE4() { return invoke<Any>(0x56E75FE4); } // 0x56E75FE4
	static Any _0xA95299B9() { return invoke<Any>(0xA95299B9); } // 0xA95299B9
	static Any _0x3D2C1916() { return invoke<Any>(0x3D2C1916); } // 0x3D2C1916
	static Any _0xDB67785D() { return invoke<Any>(0xDB67785D); } // 0xDB67785D
	static Any NETWORK_SESSION_END(Any p0, Any p1) { return invoke<Any>(0xBCACBEA2, p0, p1); } // 0xBCACBEA2
	static void NETWORK_SESSION_KICK_PLAYER(Any p0) { invoke<Void>(0x1E20138A, p0); } // 0x1E20138A
	static Any _0x8A559D26(Any p0) { return invoke<Any>(0x8A559D26, p0); } // 0x8A559D26
	static void _0x3C3E2AB6(Any p0) { invoke<Void>(0x3C3E2AB6, p0); } // 0x3C3E2AB6
	static void _0x5F29A7E0(Any p0, Any p1) { invoke<Void>(0x5F29A7E0, p0, p1); } // 0x5F29A7E0
	static Any _0x36EAD960(Any p0) { return invoke<Any>(0x36EAD960, p0); } // 0x36EAD960
	static void _0x5BE529F7(Any p0) { invoke<Void>(0x5BE529F7, p0); } // 0x5BE529F7
	static void _0x454C7B67(Any p0) { invoke<Void>(0x454C7B67, p0); } // 0x454C7B67
	static void _0xE5961511(Any p0) { invoke<Void>(0xE5961511, p0); } // 0xE5961511
	static void _0xAE396263(Any p0) { invoke<Void>(0xAE396263, p0); } // 0xAE396263
	static void _0x913FD7D6(Any p0) { invoke<Void>(0x913FD7D6, p0); } // 0x913FD7D6
	static void _0xB3D9A67F(Any p0) { invoke<Void>(0xB3D9A67F, p0); } // 0xB3D9A67F
	static void _0x6CC062FC(Any p0) { invoke<Void>(0x6CC062FC, p0); } // 0x6CC062FC
	static void _0x57F9BC83() { invoke<Void>(0x57F9BC83); } // 0x57F9BC83
	static void _0xF3768F90(Any p0) { invoke<Void>(0xF3768F90, p0); } // 0xF3768F90
	static void _0x0EC62629(Any p0, Any p1) { invoke<Void>(0x0EC62629, p0, p1); } // 0x0EC62629
	static void _0x5E557307() { invoke<Void>(0x5E557307); } // 0x5E557307
	static void _0x74E8C53E(Any p0, Any p1, Any p2) { invoke<Void>(0x74E8C53E, p0, p1, p2); } // 0x74E8C53E
	static void _0x959E43A3(Any p0) { invoke<Void>(0x959E43A3, p0); } // 0x959E43A3
	static Any _0x7771AB83(Any p0) { return invoke<Any>(0x7771AB83, p0); } // 0x7771AB83
	static Any _0xA13045D4(int p0, float p1, float p2, float p3) { return invoke<Any>(0xA13045D4, p0, p1, p2, p3); } // 0xA13045D4
	static Any NETWORK_IS_FINDING_GAMERS() { return invoke<Any>(0xA6DAA79F); } // 0xA6DAA79F
	static Any _0xBEDC4503() { return invoke<Any>(0xBEDC4503); } // 0xBEDC4503
	static Any NETWORK_GET_NUM_FOUND_GAMERS() { return invoke<Any>(0xF4B80C7E); } // 0xF4B80C7E
	static Any NETWORK_GET_FOUND_GAMER(int *p0, Any p1) { return invoke<Any>(0xA08C9141, p0, p1); } // 0xA08C9141
	static void NETWORK_CLEAR_FOUND_GAMERS() { invoke<Void>(0x6AA9A154); } // 0x6AA9A154
	static Any _0x42BD0780(Any *p0) { return invoke<Any>(0x42BD0780, p0); } // 0x42BD0780
	static Any _0xBEB98840() { return invoke<Any>(0xBEB98840); } // 0xBEB98840
	static Any _0x08029970() { return invoke<Any>(0x08029970); } // 0x08029970
	static Any _0xC871E745() { return invoke<Any>(0xC871E745); } // 0xC871E745
	static Any _0xB5ABC4B4(Any p0, Any p1) { return invoke<Any>(0xB5ABC4B4, p0, p1); } // 0xB5ABC4B4
	static void _0x3F7EDBBD() { invoke<Void>(0x3F7EDBBD); } // 0x3F7EDBBD
	static void NETWORK_IS_PLAYER_ANIMATION_DRAWING_SYNCHRONIZED() { invoke<Void>(0x3D6360B5); } // 0x3D6360B5
	static void NETWORK_SESSION_CANCEL_INVITE() { invoke<Void>(0x20317535); } // 0x20317535
	static void _0x3FD49D3B() { invoke<Void>(0x3FD49D3B); } // 0x3FD49D3B
	static Any NETWORK_HAS_PENDING_INVITE() { return invoke<Any>(0x0C207D6E); } // 0x0C207D6E
	static Any _0xFBBAC350() { return invoke<Any>(0xFBBAC350); } // 0xFBBAC350
	static Any _0x0907A6BF() { return invoke<Any>(0x0907A6BF); } // 0x0907A6BF
	static Any _0x6A0BEA60() { return invoke<Any>(0x6A0BEA60); } // 0x6A0BEA60
	static void NETWORK_SESSION_GET_INVITER(Any p0) { invoke<Void>(0xE9C6B3FD, p0); } // 0xE9C6B3FD
	static Any _0x3EA9D44C() { return invoke<Any>(0x3EA9D44C); } // 0x3EA9D44C
	static void NETWORK_SUPPRESS_INVITE(Any p0) { invoke<Void>(0x323DC78C, p0); } // 0x323DC78C
	static void NETWORK_BLOCK_INVITES(Any p0) { invoke<Void>(0xD156FD1A, p0); } // 0xD156FD1A
	static void _0x32B7A076() { invoke<Void>(0x32B7A076); } // 0x32B7A076
	static void _0x0FCE995D(Any p0) { invoke<Void>(0x0FCE995D, p0); } // 0x0FCE995D
	static void _0xA639DCA2(Any p0) { invoke<Void>(0xA639DCA2, p0); } // 0xA639DCA2
	static Any _0x70ED476A() { return invoke<Any>(0x70ED476A); } // 0x70ED476A
	static void _0x50507BED() { invoke<Void>(0x50507BED); } // 0x50507BED
	static void NETWORK_SESSION_HOST_SINGLE_PLAYER(Any p0) { invoke<Void>(0xF3B1CA85, p0); } // 0xF3B1CA85
	static void NETWORK_SESSION_LEAVE_SINGLE_PLAYER() { invoke<Void>(0xC692F86A); } // 0xC692F86A
	static Any NETWORK_IS_GAME_IN_PROGRESS() { return invoke<Any>(0x09B88E3E); } // 0x09B88E3E
	static Any NETWORK_IS_SESSION_ACTIVE() { return invoke<Any>(0x715CB8C4); } // 0x715CB8C4
	static Any NETWORK_IS_IN_SESSION() { return invoke<Any>(0x4BC4105E); } // 0x4BC4105E
	static Any NETWORK_IS_SESSION_STARTED() { return invoke<Any>(0x9D854A37); } // 0x9D854A37
	static Any NETWORK_IS_SESSION_BUSY() { return invoke<Any>(0x8592152D); } // 0x8592152D
	static Any NETWORK_CAN_SESSION_END() { return invoke<Any>(0xE1FCCDBA); } // 0xE1FCCDBA
	static void _0x7017257D(Any p0) { invoke<Void>(0x7017257D, p0); } // 0x7017257D
	static Any _0x4977AC28() { return invoke<Any>(0x4977AC28); } // 0x4977AC28
	static void _0xE6EEF8AF(Any p0) { invoke<Void>(0xE6EEF8AF, p0); } // 0xE6EEF8AF
	static void _0x6BB93227(Any p0, Any p1) { invoke<Void>(0x6BB93227, p0, p1); } // 0x6BB93227
	static Any _0xE642F2FD() { return invoke<Any>(0xE642F2FD); } // 0xE642F2FD
	static void NETWORK_SESSION_VOICE_HOST() { invoke<Void>(0x345C2980); } // 0x345C2980
	static void NETWORK_SESSION_VOICE_LEAVE() { invoke<Void>(0xE566C7DA); } // 0xE566C7DA
	static void _0x9DFD89E6(int *p0) { invoke<Void>(0x9DFD89E6, p0); } // 0x9DFD89E6
	static void NETWORK_SET_KEEP_FOCUSPOINT(Any p0, Any p1) { invoke<Void>(0x075321B5, p0, p1); } // 0x075321B5
	static void _0x6EFC2FD0(Any p0) { invoke<Void>(0x6EFC2FD0, p0); } // 0x6EFC2FD0
	static Any _0x60AA4AA1() { return invoke<Any>(0x60AA4AA1); } // 0x60AA4AA1
	static Any _0x132CA01E() { return invoke<Any>(0x132CA01E); } // 0x132CA01E
	static Any NETWORK_SEND_TEXT_MESSAGE(char* Text, int FreeMemPointer) { return invoke<Any>(0xAFFEA720, Text, FreeMemPointer); } // 0xAFFEA720
	static void NETWORK_SET_ACTIVITY_SPECTATOR(Any p0) { invoke<Void>(0xFC9AD060, p0); } // 0xFC9AD060
	static Any NETWORK_IS_ACTIVITY_SPECTATOR() { return invoke<Any>(0xAF329720); } // 0xAF329720
	static void NETWORK_SET_ACTIVITY_SPECTATOR_MAX(Any p0) { invoke<Void>(0x74E0BC0A, p0); } // 0x74E0BC0A
	static Any NETWORK_GET_ACTIVITY_PLAYER_NUM(Any p0) { return invoke<Any>(0x31F951FD, p0); } // 0x31F951FD
	static Any NETWORK_IS_ACTIVITY_SPECTATOR_FROM_HANDLE(Any p0) { return invoke<Any>(0x58F1DF7D, p0); } // 0x58F1DF7D
	static Any NETWORK_HOST_TRANSITION(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x146764FB, p0, p1, p2, p3, p4, p5); } // 0x146764FB
	static Any _0x2FF65C0B(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x2FF65C0B, p0, p1, p2, p3); } // 0x2FF65C0B
	static Any _0x47D61C99(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x47D61C99, p0, p1, p2, p3); } // 0x47D61C99
	static Any _0x5CE60A11(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x5CE60A11, p0, p1, p2, p3, p4, p5); } // 0x5CE60A11
	static Any _0x0D7E5CF9() { return invoke<Any>(0x0D7E5CF9); } // 0x0D7E5CF9
	static void _0x36A5F2DA() { invoke<Void>(0x36A5F2DA); } // 0x36A5F2DA
	static Any _0x95FFACF8() { return invoke<Any>(0x95FFACF8); } // 0x95FFACF8
	static Any _0xB97A966B() { return invoke<Any>(0xB97A966B); } // 0xB97A966B
	static void _0x7EF353E1(Any p0) { invoke<Void>(0x7EF353E1, p0); } // 0x7EF353E1
	static void _0xF60986FC(Any p0) { invoke<Void>(0xF60986FC, p0); } // 0xF60986FC
	static void NETWORK_SET_TRANSITION_CREATOR_HANDLE(Any p0) { invoke<Void>(0x1DD01FE7, p0); } // 0x1DD01FE7
	static void NETWORK_CLEAR_TRANSITION_CREATOR_HANDLE() { invoke<Void>(0x8BB336F7); } // 0x8BB336F7
	static Any NETWORK_INVITE_GAMERS_TO_TRANSITION(Any p0, Any p1) { return invoke<Any>(0x5332E645, p0, p1); } // 0x5332E645
	static void NETWORK_SET_GAMER_INVITED_TO_TRANSITION(Any p0) { invoke<Void>(0x17F1C69D, p0); } // 0x17F1C69D
	static Any NETWORK_LEAVE_TRANSITION() { return invoke<Any>(0x3A3599B7); } // 0x3A3599B7
	static Any NETWORK_LAUNCH_TRANSITION() { return invoke<Any>(0xE3570BA2); } // 0xE3570BA2
	static void _0xB59D74CA() { invoke<Void>(0xB59D74CA); } // 0xB59D74CA
	static Any NETWORK_DO_TRANSITION_TO_GAME(Any p0, Any p1) { return invoke<Any>(0x1B2114D2, p0, p1); } // 0x1B2114D2
	static Any NETWORK_DO_TRANSITION_TO_NEW_GAME(Any p0, Any p1, Any p2) { return invoke<Any>(0x58AFBE63, p0, p1, p2); } // 0x58AFBE63
	static Any NETWORK_DO_TRANSITION_TO_FREEMODE(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xC7CB8ADF, p0, p1, p2, p3); } // 0xC7CB8ADF
	static Any NETWORK_DO_TRANSITION_TO_NEW_FREEMODE(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xAD13375E, p0, p1, p2, p3, p4); } // 0xAD13375E
	static Any NETWORK_IS_TRANSITION_TO_GAME() { return invoke<Any>(0x17146B2B); } // 0x17146B2B
	static Any NETWORK_GET_TRANSITION_MEMBERS(Any p0, Any p1) { return invoke<Any>(0x31F19263, p0, p1); } // 0x31F19263
	static void _0xCEE79711(Any p0, Any p1) { invoke<Void>(0xCEE79711, p0, p1); } // 0xCEE79711
	static void _0xE0C28DB5(Any p0, Any p1, Any p2) { invoke<Void>(0xE0C28DB5, p0, p1, p2); } // 0xE0C28DB5
	static Any NETWORK_SEND_TRANSITION_GAMER_INSTRUCTION(void *p0, char* p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x468B0884, p0, p1, p2, p3, p4); } // 0x468B0884
	static Any NETWORK_MARK_TRANSITION_GAMER_AS_FULLY_JOINED(Any p0) { return invoke<Any>(0x03383F57, p0); } // 0x03383F57
	static Any NETWORK_IS_TRANSITION_HOST() { return invoke<Any>(0x0C0900BC); } // 0x0C0900BC
	static Any NETWORK_IS_TRANSITION_HOST_FROM_HANDLE(Any p0) { return invoke<Any>(0x0E2854C4, p0); } // 0x0E2854C4
	static Any NETWORK_GET_TRANSITION_HOST(Any p0) { return invoke<Any>(0x73098D40, p0); } // 0x73098D40
	static Any NETWORK_IS_IN_TRANSITION() { return invoke<Any>(0xC3CDB626); } // 0xC3CDB626
	static Any NETWORK_IS_TRANSITION_STARTED() { return invoke<Any>(0x7917E111); } // 0x7917E111
	static Any NETWORK_IS_TRANSITION_BUSY() { return invoke<Any>(0xA357A2C6); } // 0xA357A2C6
	static Any _0x8262C70E() { return invoke<Any>(0x8262C70E); } // 0x8262C70E
	static void _0xC71E607B() { invoke<Void>(0xC71E607B); } // 0xC71E607B
	static void _0x82D32D07() { invoke<Void>(0x82D32D07); } // 0x82D32D07
	static Any _0xC901AA9F() { return invoke<Any>(0xC901AA9F); } // 0xC901AA9F
	static void _0xCCA9C022(Any p0) { invoke<Void>(0xCCA9C022, p0); } // 0xCCA9C022
	static void _0x1E5F6AEF(Any p0, Any p1) { invoke<Void>(0x1E5F6AEF, p0, p1); } // 0x1E5F6AEF
	static void _0x0532DDD2(Any p0) { invoke<Void>(0x0532DDD2, p0); } // 0x0532DDD2
	static Any NETWORK_HAS_PLAYER_STARTED_TRANSITION(Any p0) { return invoke<Any>(0x4ABD1E59, p0); } // 0x4ABD1E59
	static Any _0xCDEBCCE7(Any p0) { return invoke<Any>(0xCDEBCCE7, p0); } // 0xCDEBCCE7
	static Any NETWORK_JOIN_TRANSITION(Any p0) { return invoke<Any>(0xB054EC4B, p0); } // 0xB054EC4B
	static Any _0x4F41DF6B(Any p0) { return invoke<Any>(0x4F41DF6B, p0); } // 0x4F41DF6B
	static Any NETWORK_IS_ACTIVITY_SESSION() { return invoke<Any>(0x577DAA8A); } // 0x577DAA8A
	static void _0x18F03AFD(Any p0) { invoke<Void>(0x18F03AFD, p0); } // 0x18F03AFD
	static Any _0x8B99B72B(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x8B99B72B, p0, p1, p2, p3); } // 0x8B99B72B
	static Any _0x877C0E1C(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x877C0E1C, p0, p1, p2, p3); } // 0x877C0E1C
	static Any _0x5E832444(Any p0) { return invoke<Any>(0x5E832444, p0); } // 0x5E832444
	static Any _0x3FDA00F3() { return invoke<Any>(0x3FDA00F3); } // 0x3FDA00F3
	static Any NETWORK_ACCEPT_PRESENCE_INVITE(Any p0) { return invoke<Any>(0xE5DA4CED, p0); } // 0xE5DA4CED
	static Any _0x93C665FA(Any p0) { return invoke<Any>(0x93C665FA, p0); } // 0x93C665FA
	static Any _0xD50DF46C(Any p0) { return invoke<Any>(0xD50DF46C, p0); } // 0xD50DF46C
	static Any _0x19EC65D9(Any p0) { return invoke<Any>(0x19EC65D9, p0); } // 0x19EC65D9
	static Any NETWORK_GET_PRESENCE_INVITE_HANDLE(Any p0, Any p1) { return invoke<Any>(0xB2451429, p0, p1); } // 0xB2451429
	static Any _0xC5E0C989(Any p0) { return invoke<Any>(0xC5E0C989, p0); } // 0xC5E0C989
	static Any _0xA4302183(Any p0) { return invoke<Any>(0xA4302183, p0); } // 0xA4302183
	static Any _0x51B2D848(Any p0) { return invoke<Any>(0x51B2D848, p0); } // 0x51B2D848
	static Any _0x4677C656(Any p0) { return invoke<Any>(0x4677C656, p0); } // 0x4677C656
	static Any _0xF5E3401C(Any p0) { return invoke<Any>(0xF5E3401C, p0); } // 0xF5E3401C
	static Any _0x7D593B4C(Any p0) { return invoke<Any>(0x7D593B4C, p0); } // 0x7D593B4C
	static Any _0xE96CFE7D() { return invoke<Any>(0xE96CFE7D); } // 0xE96CFE7D
	static Any _0xAB969F00() { return invoke<Any>(0xAB969F00); } // 0xAB969F00
	static Any _0x3242F952() { return invoke<Any>(0x3242F952); } // 0x3242F952
	static void _0x9773F36A() { invoke<Void>(0x9773F36A); } // 0x9773F36A
	static void NETWORK_REMOVE_TRANSITION_INVITE(Any p0) { invoke<Void>(0xFDE84CB7, p0); } // 0xFDE84CB7
	static void _0xF7134E73() { invoke<Void>(0xF7134E73); } // 0xF7134E73
	static void _0xC47352E7() { invoke<Void>(0xC47352E7); } // 0xC47352E7
	static Any NETWORK_INVITE_GAMERS(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x52FB8074, p0, p1, p2, p3); } // 0x52FB8074
	static Any _0xEC651BC0(Any p0) { return invoke<Any>(0xEC651BC0, p0); } // 0xEC651BC0
	static Any NETWORK_GET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU(Any p0) { return invoke<Any>(0x72BA00CE, p0); } // 0x72BA00CE
	static Any NETWORK_SET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU(Any p0) { return invoke<Any>(0xFD95899E, p0); } // 0xFD95899E
	static void _0x0808D4CC(Any p0, Any p1) { invoke<Void>(0x0808D4CC, p0, p1); } // 0x0808D4CC
	static void _0x11378777(Any p0) { invoke<Void>(0x11378777, p0); } // 0x11378777
	static Any FILLOUT_PM_PLAYER_LIST(Any p0, Any p1, Any p2) { return invoke<Any>(0xCE40F423, p0, p1, p2); } // 0xCE40F423
	static Any FILLOUT_PM_PLAYER_LIST_WITH_NAMES(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xB8DF604E, p0, p1, p2, p3); } // 0xB8DF604E
	static Any USING_NETWORK_WEAPONTYPE(Any p0) { return invoke<Any>(0xF49C1533, p0); } // 0xF49C1533
	static Any _0xA812B6CB() { return invoke<Any>(0xA812B6CB); } // 0xA812B6CB
	static Any _0xF30E5814(Any p0, Any p1) { return invoke<Any>(0xF30E5814, p0, p1); } // 0xF30E5814
	static Any _0xC6609191() { return invoke<Any>(0xC6609191); } // 0xC6609191
	static Any _0x51367B34(Any p0) { return invoke<Any>(0x51367B34, p0); } // 0x51367B34
	static Any NETWORK_IS_IN_PARTY() { return invoke<Any>(0xF9D7D67D); } // 0xF9D7D67D
	static Any NETWORK_IS_PARTY_MEMBER(Any p0) { return invoke<Any>(0x1D0C929D, p0); } // 0x1D0C929D
	static Any _0x9156EFC0() { return invoke<Any>(0x9156EFC0); } // 0x9156EFC0
	static Any _0x8FA6EE0E() { return invoke<Any>(0x8FA6EE0E); } // 0x8FA6EE0E
	static void _0x7F70C15A() { invoke<Void>(0x7F70C15A); } // 0x7F70C15A
	static void _0x8179C48A(Any p0) { invoke<Void>(0x8179C48A, p0); } // 0x8179C48A
	static void _0x41702C8A(Any p0) { invoke<Void>(0x41702C8A, p0); } // 0x41702C8A
	static Any _0x208DD848() { return invoke<Any>(0x208DD848); } // 0x208DD848
	static Any _0xF9B6426D(Any p0, Any p1) { return invoke<Any>(0xF9B6426D, p0, p1); } // 0xF9B6426D
	static Any NETWORK_PLAYER_IS_CHEATER() { return invoke<Any>(0xA51DC214); } // 0xA51DC214
	static Any _0x1720ABA6() { return invoke<Any>(0x1720ABA6); } // 0x1720ABA6
	static Any _0xA19708E3() { return invoke<Any>(0xA19708E3); } // 0xA19708E3
	static Any _0xF9A51B92(Any p0, Any p1, Any p2) { return invoke<Any>(0xF9A51B92, p0, p1, p2); } // 0xF9A51B92
	static Any _0x4C2C6B6A(Any p0, Any p1, Any p2) { return invoke<Any>(0x4C2C6B6A, p0, p1, p2); } // 0x4C2C6B6A
	static void _0x4818ACD0(Any p0, Any p1) { invoke<Void>(0x4818ACD0, p0, p1); } // 0x4818ACD0
	static void NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(Any p0, Any p1, Any p2) { invoke<Void>(0x470810ED, p0, p1, p2); } // 0x470810ED
	static Any NETWORK_GET_THIS_SCRIPT_IS_NETWORK_SCRIPT() { return invoke<Any>(0xD9BF6549); } // 0xD9BF6549
	static Any _0xCCD8C02D() { return invoke<Any>(0xCCD8C02D); } // 0xCCD8C02D
	static Any _0x3E25A3C5() { return invoke<Any>(0x3E25A3C5); } // 0x3E25A3C5
	static Any NETWORK_GET_SCRIPT_STATUS() { return invoke<Any>(0x2BE9235A); } // 0x2BE9235A
	static void NETWORK_REGISTER_HOST_BROADCAST_VARIABLES(Any p0, Any p1) { invoke<Void>(0xDAF3B0AE, p0, p1); } // 0xDAF3B0AE
	static void NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES(Any p0, Any p1) { invoke<Void>(0xBE3D32B4, p0, p1); } // 0xBE3D32B4
	static void _0xA71A1D2A() { invoke<Void>(0xA71A1D2A); } // 0xA71A1D2A
	static Any _0x0B739F53() { return invoke<Any>(0x0B739F53); } // 0x0B739F53
	static Any NETWORK_GET_PLAYER_INDEX(Ped PedHandle) { return invoke<Any>(0xBE1C1506, PedHandle); } // 0xBE1C1506
	static Any NETWORK_GET_PARTICIPANT_INDEX(Any p0) { return invoke<Any>(0xC4D91094, p0); } // 0xC4D91094
	static Any _0x40DBF464(Any p0) { return invoke<Any>(0x40DBF464, p0); } // 0x40DBF464
	static int NETWORK_GET_NUM_CONNECTED_PLAYERS() { return invoke<int>(0xF7952E62); } // 0xF7952E62
	static Any NETWORK_IS_PLAYER_CONNECTED(Any p0) { return invoke<Any>(0x168EE2C2, p0); } // 0x168EE2C2
	static Any _0xF4F13B06() { return invoke<Any>(0xF4F13B06); } // 0xF4F13B06
	static Any NETWORK_IS_PARTICIPANT_ACTIVE(Any p0) { return invoke<Any>(0x4E2C348B, p0); } // 0x4E2C348B
	static Any NETWORK_IS_PLAYER_ACTIVE(Any p0) { return invoke<Any>(0x43657B17, p0); } // 0x43657B17
	static Any NETWORK_IS_PLAYER_A_PARTICIPANT(Any p0) { return invoke<Any>(0xB08B6992, p0); } // 0xB08B6992
	static Any NET_BUT() { return invoke<Any>(0x6970BA94); } // 0x6970BA94
	static Any NETWORK_GET_HOST_OF_THIS_SCRIPT() { return invoke<Any>(0x89EA7B54); } // 0x89EA7B54
	static Any NETWORK_GET_HOST_OF_SCRIPT(char * gamemode, Any p1, Any p2) { return invoke<Any>(0x9C95D0BB, gamemode, p1, p2); } // 0x9C95D0BB
	static void NETWORK_SET_MISSION_FINISHED() { invoke<Void>(0x3083FAD7); } // 0x3083FAD7
	static Any NETWORK_IS_SCRIPT_ACTIVE(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x4A65250C, p0, p1, p2, p3); } // 0x4A65250C
	static Any _0x8F7D9F46(Any p0, Any p1, Any p2) { return invoke<Any>(0x8F7D9F46, p0, p1, p2); } // 0x8F7D9F46
	static Any _0xDB8B5D71() { return invoke<Any>(0xDB8B5D71); } // 0xDB8B5D71
	static Any _0xCEA55F4C(Any p0, Any p1, Any p2) { return invoke<Any>(0xCEA55F4C, p0, p1, p2); } // 0xCEA55F4C
	static void _0x8DCFE77D() { invoke<Void>(0x8DCFE77D); } // 0x8DCFE77D
	static void _0x331D9A27() { invoke<Void>(0x331D9A27); } // 0x331D9A27
	static Any PARTICIPANT_ID() { return invoke<Any>(0x9C35A221); } // 0x9C35A221
	static Any PARTICIPANT_ID_TO_INT() { return invoke<Any>(0x907498B0); } // 0x907498B0
	static Any NETWORK_GET_DESTROYER_OF_NETWORK_ID(Any p0, Any p1) { return invoke<Any>(0x4FCA6436, p0, p1); } // 0x4FCA6436
	static Any _0x28A45454(Any p0, Any p1, Any p2) { return invoke<Any>(0x28A45454, p0, p1, p2); } // 0x28A45454
	static Any NETWORK_GET_ENTITY_KILLER_OF_PLAYER(Any p0, Any p1) { return invoke<Any>(0xA7E7E04F, p0, p1); } // 0xA7E7E04F
	static void NETWORK_RESURRECT_LOCAL_PLAYER(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xF1F9D4B4, p0, p1, p2, p3, p4, p5); } // 0xF1F9D4B4
	static void NETWORK_SET_LOCAL_PLAYER_INVINCIBLE_TIME(Any p0) { invoke<Void>(0xFEA9B85C, p0); } // 0xFEA9B85C
	static Any NETWORK_IS_LOCAL_PLAYER_INVINCIBLE() { return invoke<Any>(0x8DE13B36); } // 0x8DE13B36
	static void _0x8D27280E(Any p0, Any p1) { invoke<Void>(0x8D27280E, p0, p1); } // 0x8D27280E
	static void _0xB72F086D(Any p0) { invoke<Void>(0xB72F086D, p0); } // 0xB72F086D
	static Any _0xEDA68956(Any p0) { return invoke<Any>(0xEDA68956, p0); } // 0xEDA68956
	static Any NETWORK_GET_NETWORK_ID_FROM_ENTITY(Any p0) { return invoke<Any>(0x9E35DAB6, p0); } // 0x9E35DAB6
	static Any NETWORK_GET_ENTITY_FROM_NETWORK_ID(Any p0) { return invoke<Any>(0x5B912C3F, p0); } // 0x5B912C3F
	static Any _0xD7F934F4(Any p0) { return invoke<Any>(0xD7F934F4, p0); } // 0xD7F934F4
	static Any NETWORK_GET_ENTITY_IS_LOCAL(Any p0) { return invoke<Any>(0x813353ED, p0); } // 0x813353ED
	static void _0x31A630A4(Any p0) { invoke<Void>(0x31A630A4, p0); } // 0x31A630A4
	static void _0x5C645F64(Any p0) { invoke<Void>(0x5C645F64, p0); } // 0x5C645F64
	static Any NETWORK_DOES_NETWORK_ID_EXIST(Any p0) { return invoke<Any>(0xB8D2C99E, p0); } // 0xB8D2C99E
	static Any NETWORK_DOES_ENTITY_EXIST_WITH_NETWORK_ID(Any p0) { return invoke<Any>(0x1E2E3177, p0); } // 0x1E2E3177
	static Any NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(int netID) { return invoke<Any>(0x9262A60A, netID); } // 0x9262A60A
	static Any NETWORK_HAS_CONTROL_OF_NETWORK_ID(Entity entity) { return invoke<Any>(0x92E77D21, entity); } // 0x92E77D21
	static Any NETWORK_REQUEST_CONTROL_OF_ENTITY(Entity entity) { return invoke<Any>(0xA05FEBD7, entity); } // 0xA05FEBD7
	static Any NETWORK_REQUEST_CONTROL_OF_DOOR(Any p0) { return invoke<Any>(0xF60DAAF6, p0); } // 0xF60DAAF6
	static Any NETWORK_HAS_CONTROL_OF_ENTITY(Entity Entity) { return invoke<Any>(0x005FD797, Entity); } // 0x005FD797
	static Any NETWORK_HAS_CONTROL_OF_PICKUP(Any p0) { return invoke<Any>(0xF7784FC8, p0); } // 0xF7784FC8
	static Any NETWORK_HAS_CONTROL_OF_DOOR(Any p0) { return invoke<Any>(0x136326EC, p0); } // 0x136326EC
	static Any VEH_TO_NET(Vehicle vehicle) { return invoke<Any>(0xF17634EB, vehicle); } // 0xF17634EB
	static Any PED_TO_NET(Ped ped) { return invoke<Any>(0x86A0B759, ped); } // 0x86A0B759
	static Any OBJ_TO_NET(Object object) { return invoke<Any>(0x1E05F29F, object); } // 0x1E05F29F
	static Any NET_TO_VEH(Any p0) { return invoke<Any>(0x7E02FAEA, p0); } // 0x7E02FAEA
	static Any NET_TO_PED(Any p0) { return invoke<Any>(0x87717DD4, p0); } // 0x87717DD4
	static Any NET_TO_OBJ(Any p0) { return invoke<Any>(0x27AA14D8, p0); } // 0x27AA14D8
	static Any NET_TO_ENT(Any p0) { return invoke<Any>(0x5E149683, p0); } // 0x5E149683
	static void NETWORK_GET_LOCAL_HANDLE(Any p0, Any p1) { invoke<Void>(0x08023B16, p0, p1); } // 0x08023B16
	static void NETWORK_HANDLE_FROM_USER_ID(char* p0, int* p1, Any p2) { invoke<Void>(0x74C2C1B7, p0, p1, p2); } // 0x74C2C1B7
	static void NETWORK_HANDLE_FROM_MEMBER_ID(char* p0, int* p1, Any p2) { invoke<Void>(0x9BFC9FE2, p0, p1, p2); } // 0x9BFC9FE2
	static void NETWORK_HANDLE_FROM_PLAYER(Ped PedHandle, networkHandleMgr *FreeMemPointer, int p2) { invoke<Void>(0xD3498917, PedHandle, FreeMemPointer, p2); } // 0xD3498917
	static void NETWORK_HANDLE_FROM_FRIEND(Any p0, Any p1, Any p2) { invoke<Void>(0x3B0BB3A3, p0, p1, p2); } // 0x3B0BB3A3
	static Any NETWORK_GAMERTAG_FROM_HANDLE_START(Any p0) { return invoke<Any>(0xEBA00C2A, p0); } // 0xEBA00C2A
	static Any NETWORK_GAMERTAG_FROM_HANDLE_PENDING() { return invoke<Any>(0xF000828E); } // 0xF000828E
	static Any NETWORK_GAMERTAG_FROM_HANDLE_SUCCEEDED() { return invoke<Any>(0x89C2B5EA); } // 0x89C2B5EA
	static char *NETWORK_GET_GAMERTAG_FROM_HANDLE(int *p0) { return invoke<char*>(0xA18A1B26, p0); } // 0xA18A1B26
	static Any NETWORK_ARE_HANDLES_THE_SAME(Any p0, Any p1) { return invoke<Any>(0x45975AE3, p0, p1); } // 0x45975AE3
	static Any NETWORK_IS_HANDLE_VALID(int *p0, Any p1) { return invoke<Any>(0xF0996C6E, p0, p1); } // 0xF0996C6E
	static Any NETWORK_GET_PLAYER_FROM_GAMER_HANDLE(Any p0) { return invoke<Any>(0x2E96EF1E, p0); } // 0x2E96EF1E
	static Any NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(Any p0) { return invoke<Any>(0x62EF0A63, p0); } // 0x62EF0A63
	static Any NETWORK_IS_GAMER_IN_MY_SESSION(Any p0) { return invoke<Any>(0x59127716, p0); } // 0x59127716
	static void NETWORK_SHOW_PROFILE_UI(Any p0) { invoke<Void>(0xF00A20B0, p0); } // 0xF00A20B0
	static Any NETWORK_GET_GAME_REGION() { return invoke<Any>(0xEE4D173E); } // 0xEE4D173E
	static Any NETWORK_PLAYER_GET_NAME(Any p0) { return invoke<Any>(0xCE48F260, p0); } // 0xCE48F260
	static Any _0x4EC0D983(Any p0, Any p1) { return invoke<Any>(0x4EC0D983, p0, p1); } // 0x4EC0D983
	static BOOL NETWORK_PLAYER_IS_ROCKSTAR_DEV(Player player) { return invoke<BOOL>(0xF6659045, player); } // 0xF6659045
	static Any _0xD265B049(Any p0) { return invoke<Any>(0xD265B049, p0); } // 0xD265B049
	static Any NETWORK_IS_INACTIVE_PROFILE(Any p0) { return invoke<Any>(0x95481343, p0); } // 0x95481343
	static Any NETWORK_GET_MAX_FRIENDS() { return invoke<Any>(0x048171BC); } // 0x048171BC
	static Any NETWORK_GET_FRIEND_COUNT() { return invoke<Any>(0xA396ACDE); } // 0xA396ACDE
	static char* NETWORK_GET_FRIEND_NAME(Any p0) { return invoke<char*>(0x97420B6D, p0); } // 0x97420B6D
	static Any NETWORK_IS_FRIEND_ONLINE(char* p0) { return invoke<Any>(0xE0A42430, p0); } // 0xE0A42430
	static Any NETWORK_IS_FRIEND_IN_SAME_TITLE(Any p0) { return invoke<Any>(0xC54365C2, p0); } // 0xC54365C2
	static Any NETWORK_IS_FRIEND_IN_MULTIPLAYER(Any p0) { return invoke<Any>(0x400BDDD9, p0); } // 0x400BDDD9
	static Any NETWORK_IS_FRIEND(Any p0) { return invoke<Any>(0x2DA4C282, p0); } // 0x2DA4C282
	static Any NETWORK_IS_PENDING_FRIEND(Any p0) { return invoke<Any>(0x5C85FF81, p0); } // 0x5C85FF81
	static Any NETWORK_IS_ADDING_FRIEND() { return invoke<Any>(0xBB7EC8C4); } // 0xBB7EC8C4
	static Any NETWORK_ADD_FRIEND(Any p0, Any p1) { return invoke<Any>(0x20E5B3EE, p0, p1); } // 0x20E5B3EE
	static Any CLEAR_PLAYER_BAILED_FROM_PLAYERICLE(Any p0) { return invoke<Any>(0x94AE7172, p0); } // 0x94AE7172
	static Any GET_OBJ_ENTITY(Any p0) { return invoke<Any>(0xB802B671, p0); } // 0xB802B671
	static Any NETWORK_CAN_SET_WAYPOINT() { return invoke<Any>(0x009E68F3); } // 0x009E68F3
	static Any _0x5C0AB2A9(Any p0) { return invoke<Any>(0x5C0AB2A9, p0); } // 0x5C0AB2A9
	static Any _0x9A176B6E() { return invoke<Any>(0x9A176B6E); } // 0x9A176B6E
	static Any NETWORK_HAS_HEADSET() { return invoke<Any>(0xA7DC5657); } // 0xA7DC5657
	static void _0x5C05B7E1(Any p0) { invoke<Void>(0x5C05B7E1, p0); } // 0x5C05B7E1
	static Any VEHICLE_NET_ATTACH_CHAR_TO_CHAR_PHYSICALLY() { return invoke<Any>(0xAC00A5BE); } // 0xAC00A5BE
	static Any NETWORK_GAMER_HAS_HEADSET(Any p0) { return invoke<Any>(0xD036DA4A, p0); } // 0xD036DA4A
	static Any NETWORK_IS_GAMER_TALKING(Any p0) { return invoke<Any>(0x99B58DBC, p0); } // 0x99B58DBC
	static Any NETWORK_CAN_COMMUNICATE_WITH_GAMER(Any p0) { return invoke<Any>(0xD05EB7F6, p0); } // 0xD05EB7F6
	static Any NETWORK_IS_GAMER_MUTED_BY_ME(Any p0) { return invoke<Any>(0x001B4046, p0); } // 0x001B4046
	static Any _0x7685B333(Any p0) { return invoke<Any>(0x7685B333, p0); } // 0x7685B333
	static Any _0x3FDCC8D7(Any p0) { return invoke<Any>(0x3FDCC8D7, p0); } // 0x3FDCC8D7
	static Any _0xD19B312C(Any p0) { return invoke<Any>(0xD19B312C, p0); } // 0xD19B312C
	static Any NETWORK_IS_PLAYER_TALKING(Any p0) { return invoke<Any>(0xDA9FD9DB, p0); } // 0xDA9FD9DB
	static Any NETWORK_PLAYER_HAS_HEADSET(Any p0) { return invoke<Any>(0x451FB6B6, p0); } // 0x451FB6B6
	static Any NETWORK_IS_PLAYER_MUTED_BY_ME(Any p0) { return invoke<Any>(0x7A21050E, p0); } // 0x7A21050E
	static Any NETWORK_AM_I_MUTED_BY_PLAYER(Any p0) { return invoke<Any>(0xE128F2B0, p0); } // 0xE128F2B0
	static Any NETWORK_IS_PLAYER_BLOCKED_BY_ME(Any p0) { return invoke<Any>(0xAE4F4560, p0); } // 0xAE4F4560
	static Any NETWORK_AM_I_BLOCKED_BY_PLAYER(Any p0) { return invoke<Any>(0x953EF45E, p0); } // 0x953EF45E
	static Any NETWORK_GET_PLAYER_LOUDNESS(Any p0) { return invoke<Any>(0xF2F67014, p0); } // 0xF2F67014
	static void NETWORK_SET_TALKER_PROXIMITY(Any p0) { invoke<Void>(0x67555C66, p0); } // 0x67555C66
	static Any NETWORK_GET_TALKER_PROXIMITY() { return invoke<Any>(0x19991ADD); } // 0x19991ADD
	static void NETWORK_SET_VOICE_ACTIVE(Any p0) { invoke<Void>(0x8011247F, p0); } // 0x8011247F
	static void _0x1A3EA6CD(Any p0) { invoke<Void>(0x1A3EA6CD, p0); } // 0x1A3EA6CD
	static void _0xCAB21090(Any p0) { invoke<Void>(0xCAB21090, p0); } // 0xCAB21090
	static void NETWORK_SET_TEAM_ONLY_CHAT(Any p0) { invoke<Void>(0x3813019A, p0); } // 0x3813019A
	static void _0xC8CC9E75(Any p0, Any p1) { invoke<Void>(0xC8CC9E75, p0, p1); } // 0xC8CC9E75
	static void NETWORK_SET_OVERRIDE_SPECTATOR_MODE(Any p0) { invoke<Void>(0xA0FD42D3, p0); } // 0xA0FD42D3
	static void _0xC9DDA85B(Any p0) { invoke<Void>(0xC9DDA85B, p0); } // 0xC9DDA85B
	static void _0xD33AFF79(Any p0) { invoke<Void>(0xD33AFF79, p0); } // 0xD33AFF79
	static void _0x4FFEFE43(Any p0) { invoke<Void>(0x4FFEFE43, p0); } // 0x4FFEFE43
	static void _0x74EE2D8B(Any p0, Any p1) { invoke<Void>(0x74EE2D8B, p0, p1); } // 0x74EE2D8B
	static void _0x2F98B405(Any p0) { invoke<Void>(0x2F98B405, p0); } // 0x2F98B405
	static void _0x95F1C60D(Any p0, Any p1) { invoke<Void>(0x95F1C60D, p0, p1); } // 0x95F1C60D
	static void _0x6C344AE3(Any p0, Any p1) { invoke<Void>(0x6C344AE3, p0, p1); } // 0x95F1C60D
	static void _0x1BCD3DDF(Any p0) { invoke<Void>(0x1BCD3DDF, p0); } // 0x1BCD3DDF
	static void NETWORK_SET_VOICE_CHANNEL(Any p0) { invoke<Void>(0x3974879F, p0); } // 0x3974879F
	static void _0x9ECF722A() { invoke<Void>(0x9ECF722A); } // 0x9ECF722A
	static void IS_NETWORK_VEHICLE_BEEN_DAMAGED_BY_ANY_OBJECT(Any p0, Any p1, Any p2) { invoke<Void>(0xF1E84832, p0, p1, p2); } // 0xF1E84832
	static void _0x7F9B9052() { invoke<Void>(0x7F9B9052); } // 0x7F9B9052
	static void _0x7BBEA8CF(Any p0) { invoke<Void>(0x7BBEA8CF, p0); } // 0x7BBEA8CF
	static void _0xE797A4B6(Any p0) { invoke<Void>(0xE797A4B6, p0); } // 0xE797A4B6
	static void _0x92268BB5(int player, float* p1, float* p2) { invoke<Void>(0x92268BB5, player, p1, p2); } // 0x92268BB5
	static void SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME() { invoke<Void>(0x92B7351C); } // 0x92B7351C
	static void NETWORK_SET_FRIENDLY_FIRE_OPTION(Any p0) { invoke<Void>(0x6BAF95FA, p0); } // 0x6BAF95FA
	static void NETWORK_SET_RICH_PRESENCE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x932A6CED, p0, p1, p2, p3); } // 0x932A6CED
	static void _0x017E6777(int p0, char *p1) { invoke<Void>(0x017E6777, p0, p1); } // 0x017E6777
	static Any _0xE1F86C6A() { return invoke<Any>(0xE1F86C6A); } // 0xE1F86C6A
	//static void _0xBE6A30C3(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xBE6A30C3, p0, p1, p2, p3, p4, p5); } // 0xBE6A30C3
	//static void _0x22E03AD0(Any p0, Any p1) { invoke<Void>(0x22E03AD0, p0, p1); } // 0x22E03AD0
	void _NETWORK_RESPAWN_COORDS(Player player, float *coords, BOOL p4, BOOL p5){invoke<Void>(0xBE6A30C3,player,coords,p4,p5);} // 0x9769F811D1785B03 0xBE6A30C3
	void _NETWORK_RESPAWN_PLAYER(Player player, BOOL p1) {invoke<Void>(0x22E03AD0,player,p1);}// 0xBF22E0F32968E967 0x22E03AD0
	static void _0xCEAE5AFC(Any p0) { invoke<Void>(0xCEAE5AFC, p0); } // 0xCEAE5AFC
	static Any _0xF5F4BD95() { return invoke<Any>(0xF5F4BD95); } // 0xF5F4BD95
	static Any NETWORK_CLAN_PLAYER_IS_ACTIVE(networkHandleMgr *p0) { return invoke<Any>(0xAB8319A3, p0); } // 0xAB8319A3
	static Any NETWORK_CLAN_PLAYER_GET_DESC(networkClanMgr *crewdescription, Any p1, networkHandleMgr *playerhandle) { return invoke<Any>(0x6EE4A282, crewdescription, p1, playerhandle); } // 0x6EE4A282
	static Any _0x54E79E9C(networkClanMgr *p0, Any p1) { return invoke<Any>(0x54E79E9C, p0, p1); } // 0x54E79E9C
	static void _0xF633805A(Any p0, Any p1, Any p2) { invoke<Void>(0xF633805A, p0, p1, p2); } // 0xF633805A
	static Any _0x807B3450() { return invoke<Any>(0x807B3450); } // 0x807B3450
	static Any _0x3369DD1F(Any p0, Any p1) { return invoke<Any>(0x3369DD1F, p0, p1); } // 0x3369DD1F
	static Any NETWORK_CLAN_DOWNLOAD_MEMBERSHIP(Any p0) { return invoke<Any>(0x8E8CB520, p0); } // 0x8E8CB520
	static Any NETWORK_CLAN_DOWNLOAD_MEMBERSHIP_PENDING(Any p0) { return invoke<Any>(0x1FDB590F, p0); } // 0x1FDB590F
	static Any _0x83ED8E08() { return invoke<Any>(0x83ED8E08); } // 0x83ED8E08
	static Any _0x40202867(Any p0) { return invoke<Any>(0x40202867, p0); } // 0x40202867
	static Any NETWORK_CLAN_GET_MEMBERSHIP_COUNT(Any p0) { return invoke<Any>(0x25924010, p0); } // 0x25924010
	static Any NETWORK_CLAN_GET_MEMBERSHIP_VALID(Any p0, Any p1) { return invoke<Any>(0x48914F6A, p0, p1); } // 0x48914F6A
	static Any NETWORK_CLAN_GET_MEMBERSHIP(Any p0, Any p1, Any p2) { return invoke<Any>(0xCDC4A590, p0, p1, p2); } // 0xCDC4A590
	static Any NETWORK_CLAN_JOIN(Any p0) { return invoke<Any>(0x79C916C5, p0); } // 0x79C916C5
	static Any _0xBDA90BAC(Any p0, Any p1) { return invoke<Any>(0xBDA90BAC, p0, p1); } // 0xBDA90BAC
	static Any _0x8E952B12(Any p0, Any p1) { return invoke<Any>(0x8E952B12, p0, p1); } // 0x8E952B12
	static Any _0x966C90FD() { return invoke<Any>(0x966C90FD); } // 0x966C90FD
	static Any _0xBA672146(Any p0, Any p1) { return invoke<Any>(0xBA672146, p0, p1); } // 0xBA672146
	static Any _0x7963FA4D(Any p0) { return invoke<Any>(0x7963FA4D, p0); } // 0x7963FA4D
	static Any _0x88B13CDC(Any p0, Any p1) { return invoke<Any>(0x88B13CDC, p0, p1); } // 0x88B13CDC
	static void _0xD6E3D5EA(Any p0) { invoke<Void>(0xD6E3D5EA, p0); } // 0xD6E3D5EA
	static Any _0xE22445DA() { return invoke<Any>(0xE22445DA); } // 0xE22445DA
	static void _0x455DDF5C() { invoke<Void>(0x455DDF5C); } // 0x455DDF5C
	static Any _0x89DB0EC7(Any p0, Any p1) { return invoke<Any>(0x89DB0EC7, p0, p1); } // 0x89DB0EC7
	static Any _0xA4EF02F3() { return invoke<Any>(0xA4EF02F3); } // 0xA4EF02F3
	static Any _0x068A054E() { return invoke<Any>(0x068A054E); } // 0x068A054E
	static Any _0x9B8631EB(Any p0, Any p1) { return invoke<Any>(0x9B8631EB, p0, p1); } // 0x9B8631EB
	static void SET_NETWORK_ID_CAN_MIGRATE(Any p0, Any p1) { invoke<Void>(0x47C8E5FF, p0, p1); } // 0x47C8E5FF
	static void SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(int NetID, BOOL DoesExist) { invoke<Void>(0x68D486B2, NetID, DoesExist); } // 0x68D486B2
	static void _0x4D15FDB1(Any p0, Any p1, Any p2) { invoke<Void>(0x4D15FDB1, p0, p1, p2); } // 0x4D15FDB1
	static void NETWORK_SET_ENTITY_CAN_BLEND(Any p0, Any p1) { invoke<Void>(0xDE8C0DB8, p0, p1); } // 0xDE8C0DB8
	static void _0x09CBC4B0(Any p0, Any p1) { invoke<Void>(0x09CBC4B0, p0, p1); } // 0x09CBC4B0
	static void SET_NETWORK_ID_VISIBLE_IN_CUTSCENE(Any p0, Any p1, Any p2) { invoke<Void>(0x199E75EF, p0, p1, p2); } // 0x199E75EF
	static void _0x00AE4E17(Any p0, Any p1) { invoke<Void>(0x00AE4E17, p0, p1); } // 0x00AE4E17
	static Any _0xEA5176C0(Any p0) { return invoke<Any>(0xEA5176C0, p0); } // 0xEA5176C0
	static void SET_LOCAL_PLAYER_VISIBLE_IN_CUTSCENE(Any p0, Any p1) { invoke<Void>(0x59F3479B, p0, p1); } // 0x59F3479B
	static void SET_LOCAL_PLAYER_INVISIBLE_LOCALLY(Any p0) { invoke<Void>(0x764F6222, p0); } // 0x764F6222
	static void SET_LOCAL_PLAYER_VISIBLE_LOCALLY(Any p0) { invoke<Void>(0x324B56DB, p0); } // 0x324B56DB
	static void SET_PLAYER_INVISIBLE_LOCALLY(Any p0, Any p1) { invoke<Void>(0x18227209, p0, p1); } // 0x18227209
	static void SET_PLAYER_VISIBLE_LOCALLY(Any p0, Any p1) { invoke<Void>(0xBA2BB4B4, p0, p1); } // 0xBA2BB4B4
	static void FADE_OUT_LOCAL_PLAYER(Any p0) { invoke<Void>(0x8FA7CEBD, p0); } // 0x8FA7CEBD
	static void NETWORK_FADE_OUT_ENTITY(Any p0, Any p1, Any p2) { invoke<Void>(0x47EDEE56, p0, p1, p2); } // 0x47EDEE56
	static void NETWORK_FADE_IN_ENTITY(Any p0, Any p1) { invoke<Void>(0x9B9FCD02, p0, p1); } // 0x9B9FCD02
	static BOOL IS_PLAYER_IN_CUTSCENE(Any p0) { return invoke<BOOL>(0xE0A619BD, p0); } // 0xE0A619BD
	static void SET_ENTITY_VISIBLE_IN_CUTSCENE(Any p0, Any p1, Any p2) { invoke<Void>(0xDBFB067B, p0, p1, p2); } // 0xDBFB067B
	static void SET_ENTITY_LOCALLY_INVISIBLE(Any p0) { invoke<Void>(0x51ADCC5F, p0); } // 0x51ADCC5F
	static void SET_ENTITY_LOCALLY_VISIBLE(Any p0) { invoke<Void>(0x235A57B3, p0); } // 0x235A57B3
	static BOOL IS_DAMAGE_TRACKER_ACTIVE_ON_NETWORK_ID(Any p0) { return invoke<BOOL>(0x597063BA, p0); } // 0x597063BA
	static void ACTIVATE_DAMAGE_TRACKER_ON_NETWORK_ID(Any p0, Any p1) { invoke<Void>(0x95D07BA5, p0, p1); } // 0x95D07BA5
	static BOOL IS_SPHERE_VISIBLE_TO_ANOTHER_MACHINE(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0x23C5274E, p0, p1, p2, p3); } // 0x23C5274E
	static BOOL IS_SPHERE_VISIBLE_TO_PLAYER(int player, float x, float y, float z, float radius) { return invoke<BOOL>(0xE9FCFB32, player, x, y, z, radius); } // 0xE9FCFB32
	static void RESERVE_NETWORK_MISSION_OBJECTS(Any p0) { invoke<Void>(0x391DF4F3, p0); } // 0x391DF4F3
	static void RESERVE_NETWORK_MISSION_PEDS(Any p0) { invoke<Void>(0x54998C37, p0); } // 0x54998C37
	static void RESERVE_NETWORK_MISSION_VEHICLES(Any p0) { invoke<Void>(0x5062875E, p0); } // 0x5062875E
	static BOOL CAN_REGISTER_MISSION_OBJECTS(Any p0) { return invoke<BOOL>(0x7F85DFDE, p0); } // 0x7F85DFDE
	static BOOL CAN_REGISTER_MISSION_PEDS(Any p0) { return invoke<BOOL>(0xCCAA5CE9, p0); } // 0xCCAA5CE9
	static BOOL CAN_REGISTER_MISSION_VEHICLES(Any p0) { return invoke<BOOL>(0x818B6830, p0); } // 0x818B6830
	static BOOL CAN_REGISTER_MISSION_ENTITIES(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0x83794008, p0, p1, p2, p3); } // 0x83794008
	static Any GET_NUM_RESERVED_MISSION_OBJECTS(Any p0) { return invoke<Any>(0x16A80CD6, p0); } // 0x16A80CD6
	static Any GET_NUM_RESERVED_MISSION_PEDS(Any p0) { return invoke<Any>(0x6C25975C, p0); } // 0x6C25975C
	static Any GET_NUM_RESERVED_MISSION_VEHICLES(Any p0) { return invoke<Any>(0xA9A308F3, p0); } // 0xA9A308F3
	static Any _0x603FA104(Any p0) { return invoke<Any>(0x603FA104, p0); } // 0x603FA104
	static Any _0xD8FEC4F8(Any p0) { return invoke<Any>(0xD8FEC4F8, p0); } // 0xD8FEC4F8
	static Any _0x20527695(Any p0) { return invoke<Any>(0x20527695, p0); } // 0x20527695
	static Any _0x8687E285() { return invoke<Any>(0x8687E285); } // 0x8687E285
	static Any _0x744AC008() { return invoke<Any>(0x744AC008); } // 0x744AC008
	static Any _0xC3A12135() { return invoke<Any>(0xC3A12135); } // 0xC3A12135
	static Any _0x6A036061() { return invoke<Any>(0x6A036061); } // 0x6A036061
	static Any GET_NETWORK_TIME() { return invoke<Any>(0x998103C2); } // 0x998103C2
	static Any _0x98AA48E5() { return invoke<Any>(0x98AA48E5); } // 0x98AA48E5
	static Any _0x4538C4A2() { return invoke<Any>(0x4538C4A2); } // 0x4538C4A2
	static Any GET_TIME_OFFSET(Any p0, Any p1) { return invoke<Any>(0x2E079AE6, p0, p1); } // 0x2E079AE6
	static Any _0x50EF8FC6(Any p0, Any p1) { return invoke<Any>(0x50EF8FC6, p0, p1); } // 0x50EF8FC6
	static Any _0xBBB6DF61(Any p0, Any p1) { return invoke<Any>(0xBBB6DF61, p0, p1); } // 0xBBB6DF61
	static Any _0x8B4D1C06(Any p0, Any p1) { return invoke<Any>(0x8B4D1C06, p0, p1); } // 0x8B4D1C06
	static Any GET_TIME_DIFFERENCE(Any p0, Any p1) { return invoke<Any>(0x5666A837, p0, p1); } // 0x5666A837
	static Any _0x8218944E(Any p0) { return invoke<Any>(0x8218944E, p0); } // 0x8218944E
	static Any _0xF2FDF2E0() { return invoke<Any>(0xF2FDF2E0); } // 0xF2FDF2E0
	static void _0xBB7CCE49(Any p0, Any p1) { invoke<Void>(0xBB7CCE49, p0, p1); } // 0xBB7CCE49
	static void NETWORK_SET_IN_SPECTATOR_MODE(Any p0, Any p1) { invoke<Void>(0x5C4C8458, p0, p1); } // 0x5C4C8458
	static void _0x54058F5F(Any p0, Any p1, Any p2) { invoke<Void>(0x54058F5F, p0, p1, p2); } // 0x54058F5F
	static void _0xA7E36020(Any p0) { invoke<Void>(0xA7E36020, p0); } // 0xA7E36020
	static void _0x64235620(Any p0, Any p1) { invoke<Void>(0x64235620, p0, p1); } // 0x64235620
	static Any NETWORK_IS_IN_SPECTATOR_MODE() { return invoke<Any>(0x3EAD9DB8); } // 0x3EAD9DB8
	static void NETWORK_SET_IN_MP_CUTSCENE(Any p0, Any p1, Any p2) { invoke<Void>(0x8434CB43, p0, p1, p2); } // 0x8434CB43
	static Any NETWORK_IS_IN_MP_CUTSCENE() { return invoke<Any>(0x4BB33316); } // 0x4BB33316
	static Any NETWORK_IS_PLAYER_IN_MP_CUTSCENE(Any p0) { return invoke<Any>(0x56F961E4, p0); } // 0x56F961E4
	static void SET_NETWORK_VEHICLE_RESPOT_TIMER(Any p0, Any p1) { invoke<Void>(0x2C30912D, p0, p1); } // 0x2C30912D
	static void _0xEA235081(Any p0, Any p1) { invoke<Void>(0xEA235081, p0, p1); } // 0xEA235081
	static void USE_PLAYER_COLOUR_INSTEAD_OF_TEAM_COLOUR(Any p0) { invoke<Void>(0x4DD46DAE, p0); } // 0x4DD46DAE
	//static Any NETWORK_CREATE_SYNCHRONISED_SCENE(float p0, float p1, float p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<Any>(0xB06FE3FE, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xB06FE3FE
	//static void NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(Any p0, Any p1, char *p2, char *p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0xB386713E, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xB386713E
	static Any NETWORK_CREATE_SYNCHRONISED_SCENE(float p0, float p1, float p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, float p9, float p10, float p11) { return invoke<Any>((addrstruct().NETWORK_CREATE_SYNCHRONISED_SCENE^dataDecryptor())/*0xB06FE3FE*/, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0xB06FE3FE
	static void NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(Any p0, Any p1, char *p2, char *p3, float p4, float p5, int p6, Any p7, float p8) { invoke<Void>(0xB386713E, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xB386713E
	static void NETWORK_ADD_ENTITY_TO_SYNCHRONISED_SCENE(Entity entity, int netScene, char *animDict, char *animName, float speed, float speedMultiplier, int flag) { invoke<Void>(0x10DD636C, entity, netScene, animDict, animName, speed, speedMultiplier, flag); } // 0x10DD636C
	static void _0xBFFE8B5C(Any p0, Any p1, Any p2) { invoke<Void>(0xBFFE8B5C, p0, p1, p2); } // 0xBFFE8B5C
	static void NETWORK_ATTACH_SYNCHRONISED_SCENE_TO_ENTITY(Any p0, Any p1, Any p2) { invoke<Void>(0x3FE5B222, p0, p1, p2); } // 0x3FE5B222
	static void NETWORK_START_SYNCHRONISED_SCENE(Any p0) { invoke<Void>(0xA9DFDC40, p0); } // 0xA9DFDC40
	static void NETWORK_STOP_SYNCHRONISED_SCENE(Any p0) { invoke<Void>(0x97B1CDF6, p0); } // 0x97B1CDF6
	static Any _0x16AED87B(Any p0) { return invoke<Any>(0x16AED87B, p0); } // 0x16AED87B
	static Any _0x0679CE71(Any p0, Any p1) { return invoke<Any>(0x0679CE71, p0, p1); } // 0x0679CE71
	static Any _0xC62E77B3(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<Any>(0xC62E77B3, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xC62E77B3
	static Any _0x74D6B13C(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { return invoke<Any>(0x74D6B13C, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0x74D6B13C
	static Any _0x90700C7D(Any p0) { return invoke<Any>(0x90700C7D, p0); } // 0x90700C7D
	static void _0x44BFB619() { invoke<Void>(0x44BFB619); } // 0x44BFB619
	static void NETWORK_GET_RESPAWN_RESULT(Any p0, Any p1, Any p2) { invoke<Void>(0xDDFE9FBC, p0, p1, p2); } // 0xDDFE9FBC
	static Any _0x03287FD2(Any p0) { return invoke<Any>(0x03287FD2, p0); } // 0x03287FD2
	static void _0x408A9436() { invoke<Void>(0x408A9436); } // 0x408A9436
	static void _0xFFB2ADA1(Any p0, Any p1) { invoke<Void>(0xFFB2ADA1, p0, p1); } // 0xFFB2ADA1
	static void NETWORK_END_TUTORIAL_SESSION() { invoke<Void>(0xBA57E53E); } // 0xBA57E53E
	static Any NETWORK_IS_IN_TUTORIAL_SESSION() { return invoke<Any>(0x34DD7B28); } // 0x34DD7B28
	static Any _0x755A2B3E() { return invoke<Any>(0x755A2B3E); } // 0x755A2B3E
	static Any _0xA003C40B() { return invoke<Any>(0xA003C40B); } // 0xA003C40B
	static Any _0x5E1020CC(Any p0) { return invoke<Any>(0x5E1020CC, p0); } // 0x5E1020CC
	static Any _0xE66A0B40(Any p0, Any p1) { return invoke<Any>(0xE66A0B40, p0, p1); } // 0xE66A0B40
	static void _0x72052DB3(Any p0, Any p1) { invoke<Void>(0x72052DB3, p0, p1); } // 0x72052DB3
	static Any _0xB0313590(Any p0) { return invoke<Any>(0xB0313590, p0); } // 0xB0313590
	static void NETWORK_OVERRIDE_CLOCK_TIME(int Hours, int Minutes, int Seconds) { invoke<Void>(0xC077BCD6, Hours, Minutes, Seconds); } // 0xC077BCD6
	static void _0xC4AEAF49() { invoke<Void>(0xC4AEAF49); } // 0xC4AEAF49
	static Any _0x2465296D() { return invoke<Any>(0x2465296D); } // 0x2465296D
	static Any NETWORK_ADD_ENTITY_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x51030E5B, p0, p1, p2, p3, p4, p5); } // 0x51030E5B
	static Any _0x4C2C2B12(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x4C2C2B12, p0, p1, p2, p3, p4, p5); } // 0x4C2C2B12
	static Any NETWORK_REMOVE_ENTITY_AREA(Any p0) { return invoke<Any>(0xEAB97F25, p0); } // 0xEAB97F25
	static Any _0x69956127(Any p0) { return invoke<Any>(0x69956127, p0); } // 0x69956127
	static Any _0xCB1CD6D3(Any p0) { return invoke<Any>(0xCB1CD6D3, p0); } // 0xCB1CD6D3
	static Any _0xC6D53AA0(Any p0) { return invoke<Any>(0xC6D53AA0, p0); } // 0xC6D53AA0
	static void _0x155465EE(Any p0, Any p1) { invoke<Void>(0x155465EE, p0, p1); } // 0x155465EE
	static Any _0x29532731() { return invoke<Any>(0x29532731); } // 0x29532731
	static void _0xD760CAD5() { invoke<Void>(0xD760CAD5); } // 0xD760CAD5
	static Any _0x231CFD12() { return invoke<Any>(0x231CFD12); } // 0x231CFD12
	static Any NETWORK_DOES_TUNABLE_EXIST(Any p0, Any p1) { return invoke<Any>(0x9FCE9C9A, p0, p1); } // 0x9FCE9C9A
	static Any _0xE4B3726A(Any p0, Any p1, Any p2) { return invoke<Any>(0xE4B3726A, p0, p1, p2); } // 0xE4B3726A
	static Any _0x41E8912A(Any p0, Any p1, Any p2) { return invoke<Any>(0x41E8912A, p0, p1, p2); } // 0x41E8912A
	static Any _0x8A04E1FE(Any p0, Any p1) { return invoke<Any>(0x8A04E1FE, p0, p1); } // 0x8A04E1FE
	static Any _0xA78571CA(Any p0) { return invoke<Any>(0xA78571CA, p0); } // 0xA78571CA
	static Any _0x053BB329() { return invoke<Any>(0x053BB329); } // 0x053BB329
	static void NETWORK_RESET_BODY_TRACKER() { invoke<Void>(0x3914463F); } // 0x3914463F
	static Any _0x17CBC608() { return invoke<Any>(0x17CBC608); } // 0x17CBC608
	static Any _0xBFAA349B(Any p0) { return invoke<Any>(0xBFAA349B, p0); } // 0xBFAA349B
	static Any _0xBEB7281A(Any p0, Any p1) { return invoke<Any>(0xBEB7281A, p0, p1); } // 0xBEB7281A
	static Any NETWORK_EXPLODE_VEHICLE(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x0E1B38AE, p0, p1, p2, p3); } // 0x0E1B38AE
	static void _0xBC54371B(Any p0) { invoke<Void>(0xBC54371B, p0); } // 0xBC54371B
	static void _0x644141C5(int p0, float p1, float p2, float p3, float p4) { invoke<Void>(0x644141C5, p0, p1, p2, p3, p4); } // 0x644141C5
	static void NETWORK_SET_PROPERTY_ID(Any p0) { invoke<Void>(0x5A74E873, p0); } // 0x5A74E873
	static void _0x38BC35C8() { invoke<Void>(0x38BC35C8); } // 0x38BC35C8
	static void _0x53C9563C(Any p0) { invoke<Void>(0x53C9563C, p0); } // 0x53C9563C
	static void _0x6B97075B(Any p0) { invoke<Void>(0x6B97075B, p0); } // 0x6B97075B
	static Any _0x965EA007() { return invoke<Any>(0x965EA007); } // 0x965EA007
	static Any _0xEEFC8A55() { return invoke<Any>(0xEEFC8A55); } // 0xEEFC8A55
	static void _0x866D1B67(Any p0) { invoke<Void>(0x866D1B67, p0); } // 0x866D1B67
	static Any _0xED4A272F() { return invoke<Any>(0xED4A272F); } // 0xED4A272F
	static Any _0x4ACF110C(Any p0) { return invoke<Any>(0x4ACF110C, p0); } // 0x4ACF110C
	static Any _0x1AA3A0D5(Any p0) { return invoke<Any>(0x1AA3A0D5, p0); } // 0x1AA3A0D5
	static Any _0x37877757(Any p0) { return invoke<Any>(0x37877757, p0); } // 0x37877757
	static Any _0x1CF89DA5(Any p0) { return invoke<Any>(0x1CF89DA5, p0); } // 0x1CF89DA5
	static Any _0x16E53875(Any p0, Any p1) { return invoke<Any>(0x16E53875, p0, p1); } // 0x16E53875
	static void _0x365C50EE(Any p0, Any p1) { invoke<Void>(0x365C50EE, p0, p1); } // 0x365C50EE
	static Any _0x25E2DBA9() { return invoke<Any>(0x25E2DBA9); } // 0x25E2DBA9
	static void SET_STORE_ENABLED(Any p0) { invoke<Void>(0xC1F6443B, p0); } // 0xC1F6443B
	static Any _0x1FDC75DC(Any p0) { return invoke<Any>(0x1FDC75DC, p0); } // 0x1FDC75DC
	static void _0xCA7A0A49() { invoke<Void>(0xCA7A0A49); } // 0xCA7A0A49
	static Any _0x44A58B0A(Any p0) { return invoke<Any>(0x44A58B0A, p0); } // 0x44A58B0A
	static Any _0xD32FA11F() { return invoke<Any>(0xD32FA11F); } // 0xD32FA11F
	static void _0xA7FA70AE() { invoke<Void>(0xA7FA70AE); } // 0xA7FA70AE
	static void _0xCC7DCE24() { invoke<Void>(0xCC7DCE24); } // 0xCC7DCE24
	static Any _0x70F6D3AD() { return invoke<Any>(0x70F6D3AD); } // 0x70F6D3AD
	static Any _0x2B7B57B3(Any p0) { return invoke<Any>(0x2B7B57B3, p0); } // 0x2B7B57B3
	static Any _0xBAF52DD8(Any p0) { return invoke<Any>(0xBAF52DD8, p0); } // 0xBAF52DD8
	static Any _0x9B9AFFF1(Any p0) { return invoke<Any>(0x9B9AFFF1, p0); } // 0x9B9AFFF1
	static void _0xC38E9DB0() { invoke<Void>(0xC38E9DB0); } // 0xC38E9DB0
	static Any _0x32A4EB22() { return invoke<Any>(0x32A4EB22); } // 0x32A4EB22
	static Any _0x9262744C() { return invoke<Any>(0x9262744C); } // 0x9262744C
	static Any _0x08243B79(Any p0, Any p1) { return invoke<Any>(0x08243B79, p0, p1); } // 0x08243B79
	static Any _0x798D6C27() { return invoke<Any>(0x798D6C27); } // 0x798D6C27
	static Any _0xE69E8D0D() { return invoke<Any>(0xE69E8D0D); } // 0xE69E8D0D
	static Any _0x742075FE() { return invoke<Any>(0x742075FE); } // 0x742075FE
	static Any _0xCE569932() { return invoke<Any>(0xCE569932); } // 0xCE569932
	static Any _0x82146BE9() { return invoke<Any>(0x82146BE9); } // 0x82146BE9
	static void _0x133FF2D5() { invoke<Void>(0x133FF2D5); } // 0x133FF2D5
	static Any _0xCBA7242F(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0xCBA7242F, p0, p1, p2, p3, p4, p5); } // 0xCBA7242F
	static Any _0xDED82A6E(Any p0, Any p1, Any p2) { return invoke<Any>(0xDED82A6E, p0, p1, p2); } // 0xDED82A6E
	static Any _0x40CF0783(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x40CF0783, p0, p1, p2, p3); } // 0x40CF0783
	static Any _0x4609D596(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x4609D596, p0, p1, p2, p3); } // 0x4609D596
	static Any _0x4C2C0D1F(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x4C2C0D1F, p0, p1, p2, p3); } // 0x4C2C0D1F
	static Any _0x9EFBD5D1(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x9EFBD5D1, p0, p1, p2, p3); } // 0x9EFBD5D1
	static Any _0xA6D8B798(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xA6D8B798, p0, p1, p2, p3, p4); } // 0xA6D8B798
	static Any _0x67E74842(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x67E74842, p0, p1, p2, p3, p4); } // 0x67E74842
	static Any SET_BALANCE_ADD_MACHINE(Any p0, Any p1) { return invoke<Any>(0xE123C7AC, p0, p1); } // 0xE123C7AC
	static Any SET_BALANCE_ADD_MACHINES(Any p0, Any p1, Any p2) { return invoke<Any>(0x22C33603, p0, p1, p2); } // 0x22C33603
	static Any _0x37F5BD93(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x37F5BD93, p0, p1, p2, p3); } // 0x37F5BD93
	static Any _0x1CFB3F51(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x1CFB3F51, p0, p1, p2, p3); } // 0x1CFB3F51
	static Any _0x87D1E6BD(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x87D1E6BD, p0, p1, p2, p3); } // 0x87D1E6BD
	static void _0x021D5A94() { invoke<Void>(0x021D5A94); } // 0x021D5A94
	static Any _0x4908A514() { return invoke<Any>(0x4908A514); } // 0x4908A514
	static Any _0x50296140() { return invoke<Any>(0x50296140); } // 0x50296140
	static Any _0x3970B0DA() { return invoke<Any>(0x3970B0DA); } // 0x3970B0DA
	static Any _0xC1487110() { return invoke<Any>(0xC1487110); } // 0xC1487110
	static Any _0xCC2356E3() { return invoke<Any>(0xCC2356E3); } // 0xCC2356E3
	static Any _0x2DE69817() { return invoke<Any>(0x2DE69817); } // 0x2DE69817
	static Any _0x81BD8D3B() { return invoke<Any>(0x81BD8D3B); } // 0x81BD8D3B
	static Any _0x8E1D8F78() { return invoke<Any>(0x8E1D8F78); } // 0x8E1D8F78
	static void _0x0D35DD93() { invoke<Void>(0x0D35DD93); } // 0x0D35DD93
	static Any _0x8F3137E6(Any p0) { return invoke<Any>(0x8F3137E6, p0); } // 0x8F3137E6
	static Any _0xB9137BA7(Any p0) { return invoke<Any>(0xB9137BA7, p0); } // 0xB9137BA7
	static Any _0x9FEEAA9C(Any p0) { return invoke<Any>(0x9FEEAA9C, p0); } // 0x9FEEAA9C
	static Any _0x5E8A7559(Any p0) { return invoke<Any>(0x5E8A7559, p0); } // 0x5E8A7559
	static Any _0x331AEABF(Any p0) { return invoke<Any>(0x331AEABF, p0); } // 0x331AEABF
	static Any _0x0E5E8E5C(Any p0) { return invoke<Any>(0x0E5E8E5C, p0); } // 0x0E5E8E5C
	static Any _0xA5A0C695(Any p0) { return invoke<Any>(0xA5A0C695, p0); } // 0xA5A0C695
	static Any _0x91534C6E(Any p0) { return invoke<Any>(0x91534C6E, p0); } // 0x91534C6E
	static Any _0x744A9EA5(Any p0, Any p1) { return invoke<Any>(0x744A9EA5, p0, p1); } // 0x744A9EA5
	static void _0xA19A238D(Any p0, Any p1) { invoke<Void>(0xA19A238D, p0, p1); } // 0xA19A238D
	static Any _0xFF7D44E6(Any p0, Any p1) { return invoke<Any>(0xFF7D44E6, p0, p1); } // 0xFF7D44E6
	static Any _0xA2C5BD9D(Any p0) { return invoke<Any>(0xA2C5BD9D, p0); } // 0xA2C5BD9D
	static Any _0xA850DDE1(Any p0) { return invoke<Any>(0xA850DDE1, p0); } // 0xA850DDE1
	static Any _0x8F6754AE(Any p0) { return invoke<Any>(0x8F6754AE, p0); } // 0x8F6754AE
	static Any _0x1E34953F(Any p0, Any p1) { return invoke<Any>(0x1E34953F, p0, p1); } // 0x1E34953F
	static Any _0x771FE190(Any p0, Any p1) { return invoke<Any>(0x771FE190, p0, p1); } // 0x771FE190
	static Any _0x3276D9D3(Any p0, Any p1) { return invoke<Any>(0x3276D9D3, p0, p1); } // 0x3276D9D3
	static Any _0x41A0FB02(Any p0, Any p1) { return invoke<Any>(0x41A0FB02, p0, p1); } // 0x41A0FB02
	static Any _0x11DC0F27(Any p0) { return invoke<Any>(0x11DC0F27, p0); } // 0x11DC0F27
	static Any _0x0DEB3F5A(Any p0) { return invoke<Any>(0x0DEB3F5A, p0); } // 0x0DEB3F5A
	static Any _0x84315226(Any p0, Any p1) { return invoke<Any>(0x84315226, p0, p1); } // 0x84315226
	static Any _0x38FC2EEB(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x38FC2EEB, p0, p1, p2, p3, p4); } // 0x38FC2EEB
	static Any _0x1C4F9FDB(Any p0) { return invoke<Any>(0x1C4F9FDB, p0); } // 0x1C4F9FDB
	static Any _0xA69AE16C(Any p0) { return invoke<Any>(0xA69AE16C, p0); } // 0xA69AE16C
	static Any _0xF50BC67A(Any p0) { return invoke<Any>(0xF50BC67A, p0); } // 0xF50BC67A
	static Any _0xB3BBD241(Any p0) { return invoke<Any>(0xB3BBD241, p0); } // 0xB3BBD241
	static Any _0x70A2845C(Any p0, Any p1) { return invoke<Any>(0x70A2845C, p0, p1); } // 0x70A2845C
	static Any _0x346B506C(Any p0) { return invoke<Any>(0x346B506C, p0); } // 0x346B506C
	static void _0x0095DB71() { invoke<Void>(0x0095DB71); } // 0x0095DB71
	static Any _0xAD334B40(Any p0, Any p1, Any p2) { return invoke<Any>(0xAD334B40, p0, p1, p2); } // 0xAD334B40
	static Any _0x980D45D7(Any p0, Any p1, Any p2) { return invoke<Any>(0x980D45D7, p0, p1, p2); } // 0x980D45D7
	static Any _0x48CCC328(Any p0, Any p1, Any p2) { return invoke<Any>(0x48CCC328, p0, p1, p2); } // 0x48CCC328
	static Any _0x8E664EFD() { return invoke<Any>(0x8E664EFD); } // 0x8E664EFD
	static Any _0x611E0BE2() { return invoke<Any>(0x611E0BE2); } // 0x611E0BE2
	static Any _0xF0211AC1() { return invoke<Any>(0xF0211AC1); } // 0xF0211AC1
	static Any _0x1F0DD8AF() { return invoke<Any>(0x1F0DD8AF); } // 0x1F0DD8AF
	static void _0x405ECA16() { invoke<Void>(0x405ECA16); } // 0x405ECA16
	static Any _0x9567392B(Any p0, Any p1) { return invoke<Any>(0x9567392B, p0, p1); } // 0x9567392B
	static Any _0xF79FFF3C() { return invoke<Any>(0xF79FFF3C); } // 0xF79FFF3C
	static Any _0xA7F3F82B() { return invoke<Any>(0xA7F3F82B); } // 0xA7F3F82B
	static Any _0x410C61D1() { return invoke<Any>(0x410C61D1); } // 0x410C61D1
	static Any _0x0D4F845D(Any p0) { return invoke<Any>(0x0D4F845D, p0); } // 0x0D4F845D
	static void _0xE13C1F7F() { invoke<Void>(0xE13C1F7F); } // 0xE13C1F7F
	static void _0x213C6D36(Any p0) { invoke<Void>(0x213C6D36, p0); } // 0x213C6D36
	static void _0x511E6F50(Any p0) { invoke<Void>(0x511E6F50, p0); } // 0x511E6F50
	static Any _0xB4668B23(Any p0) { return invoke<Any>(0xB4668B23, p0); } // 0xB4668B23
	static Any _0x30B51753(Any p0, Any p1, Any p2) { return invoke<Any>(0x30B51753, p0, p1, p2); } // 0x30B51753
	static Any _0x02DAD93F() { return invoke<Any>(0x02DAD93F); } // 0x02DAD93F
	static Any _0x2D947814(Any p0) { return invoke<Any>(0x2D947814, p0); } // 0x2D947814
	static Any _0x37A28C26() { return invoke<Any>(0x37A28C26); } // 0x37A28C26
	static Any _0x11E8B5CD() { return invoke<Any>(0x11E8B5CD); } // 0x11E8B5CD
	static Any _0x429AEAB3() { return invoke<Any>(0x429AEAB3); } // 0x429AEAB3
	static Any TEXTURE_DOWNLOAD_REQUEST(int PlayerHandle, char *FilePath, char *Name, BOOL p3) { return invoke<Any>(0xAD546CC3, PlayerHandle, FilePath, Name, p3); } // 0xAD546CC3
	static Any _0x1856D008(Any p0, Any p1, Any p2) { return invoke<Any>(0x1856D008, p0, p1, p2); } // 0x1856D008
	static Any _0x68C9AF69(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x68C9AF69, p0, p1, p2, p3, p4, p5); } // 0x68C9AF69
	static void TEXTURE_DOWNLOAD_RELEASE(Any p0) { invoke<Void>(0xEE8D9E70, p0); } // 0xEE8D9E70
	static Any _0xE4547765(Any p0) { return invoke<Any>(0xE4547765, p0); } // 0xE4547765
	static Any TEXTURE_DOWNLOAD_GET_NAME(Any p0) { return invoke<Any>(0xA40EF65A, p0); } // 0xA40EF65A
	static Any _0x03225BA3(Any p0) { return invoke<Any>(0x03225BA3, p0); } // 0x03225BA3
	static Any _0x4DEBC227() { return invoke<Any>(0x4DEBC227); } // 0x4DEBC227
	static Any _0x5C065D55() { return invoke<Any>(0x5C065D55); } // 0x5C065D55
	static Any _0x0CA1167F() { return invoke<Any>(0x0CA1167F); } // 0x0CA1167F
	static Any _0x424C6E27() { return invoke<Any>(0x424C6E27); } // 0x424C6E27
	static Any _0xD3BBE42F() { return invoke<Any>(0xD3BBE42F); } // 0xD3BBE42F
	static Any _0xBDBB5948() { return invoke<Any>(0xBDBB5948); } // 0xBDBB5948
	static Any _0x97287D68() { return invoke<Any>(0x97287D68); } // 0x97287D68
	static Any _0xC6EA802E() { return invoke<Any>(0xC6EA802E); } // 0xC6EA802E
	static Any _0xFD261E30(Any p0) { return invoke<Any>(0xFD261E30, p0); } // 0xFD261E30
	static Any _0x8570DD34(Any p0, Any p1, Any p2) { return invoke<Any>(0x8570DD34, p0, p1, p2); } // 0x8570DD34
	static void _0x273C6180() { invoke<Void>(0x273C6180); } // 0x273C6180
	static void _0x371BBA08() { invoke<Void>(0x371BBA08); } // 0x371BBA08
	static void _0xA100CC97(Any p0) { invoke<Void>(0xA100CC97, p0); } // 0xA100CC97
	static void _0xBB2D33D3(Any p0, Any p1) { invoke<Void>(0xBB2D33D3, p0, p1); } // 0xBB2D33D3
}

namespace NETWORKCASH
{
	static Any NETWORK_CHECK_RECEIVE_PLAYER_CASH(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xD6B69D67, p0, p1, p2, p3, p4); } // 0xD6B69D67
	static void NETWORK_GIVE_PLAYER_JOBSHARE_CASH(Any p0, Any p1) { invoke<Void>(0xC6047FDB, p0, p1); } // 0xC6047FDB
	static void NETWORK_RECEIVE_PLAYER_JOBSHARE_CASH(Any p0, Any p1) { invoke<Void>(0x4ED71C1A, p0, p1); } // 0x4ED71C1A
	static void NETWORK_EARN_FROM_BOUNTY(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x127F2DAE, p0, p1, p2, p3); } // 0x127F2DAE
	static Any _0x5AA379D9(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x5AA379D9, p0, p1, p2, p3, p4); } // 0x5AA379D9
	static void NETWORK_BUY_ITEM(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0xA07B6368, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xA07B6368
	static void NETWORK_SPENT_BUY_WANTEDLEVEL(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xE7CB4F95, p0, p1, p2, p3); } // 0xE7CB4F95
	static void NETWORK_SPENT_PAY_VEHICLE_INSURANCE_PREMIUM(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x4E665BB2, p0, p1, p2, p3, p4); } // 0x4E665BB2
	static void NETWORK_SPENT_CALL_PLAYER(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x1A89B5FC, p0, p1, p2, p3); } // 0x1A89B5FC
	static void NETWORK_SPENT_BOUNTY(Any p0, Any p1, Any p2) { invoke<Void>(0x3401FC96, p0, p1, p2); } // 0x3401FC96
	static Any _0xC5D8B1E9(Any p0, Any p1) { return invoke<Any>(0xC5D8B1E9, p0, p1); } // 0xC5D8B1E9
	static Any _0x6F1C592C() { return invoke<Any>(0x6F1C592C); } // 0x6F1C592C
	static Any _0x8B755993(Any p0) { return invoke<Any>(0x8B755993, p0); } // 0x8B755993
	static Any _0x8F266745(Any p0) { return invoke<Any>(0x8F266745, p0); } // 0x8F266745
	static Any _0x531E4892(Any p0) { return invoke<Any>(0x531E4892, p0); } // 0x531E4892
	static Any _0xB96C7ABE(Any p0) { return invoke<Any>(0xB96C7ABE, p0); } // 0xB96C7ABE
	static void _0x66DA9935(Any p0, Any p1) { invoke<Void>(0x66DA9935, p0, p1); } // 0x66DA9935
	static void NETWORK_DELETE_CHARACTER(Any p0, Any p1, Any p2) { invoke<Void>(0xA9F7E9C3, p0, p1, p2); } // 0xA9F7E9C3
	static void _0x19F0C471(Any p0) { invoke<Void>(0x19F0C471, p0); } // 0x19F0C471
	static Any _0xA27B9FE8() { return invoke<Any>(0xA27B9FE8); } // 0xA27B9FE8
	static void _0x07C92F21(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x07C92F21, p0, p1, p2, p3); } // 0x07C92F21
	static Any _0x8474E6F0(Any p0, Any p1, Any p2) { return invoke<Any>(0x8474E6F0, p0, p1, p2); } // 0x8474E6F0
	static Any _0xE3802533(Any p0) { return invoke<Any>(0xE3802533, p0); } // 0xE3802533
	static void NETWORK_EARN_FROM_PICKUP(int amount) { invoke<Void>(0x70A0ED62, amount); } // 0x70A0ED62
	static void _0x33C20BC4(Any p0) { invoke<Void>(0x33C20BC4, p0); } // 0x33C20BC4
	static void _0x30B3EC0A(Any p0) { invoke<Void>(0x30B3EC0A, p0); } // 0x30B3EC0A
	static void _0xEAF04923(Any p0) { invoke<Void>(0xEAF04923, p0); } // 0xEAF04923
	static void NETWORK_EARN_FROM_BETTING(Any p0, Any p1) { invoke<Void>(0xA0F7F07C, p0, p1); } // 0xA0F7F07C
	static void NETWORK_EARN_FROM_JOB(int amount, Any p1) { invoke<Void>(0x0B6997FC, amount, p1); } // 0x0B6997FC
	static void _0x5E81F55C(Any p0, Any p1) { invoke<Void>(0x5E81F55C, p0, p1); } // 0x5E81F55C
	static void _0x2BEFB6C4(Any p0, Any p1, Any p2) { invoke<Void>(0x2BEFB6C4, p0, p1, p2); } // 0x2BEFB6C4
	static void _0xF11FC458(Any p0, Any p1) { invoke<Void>(0xF11FC458, p0, p1); } // 0xF11FC458
	static void NETWORK_EARN_FROM_HOLDUPS(Any p0) { invoke<Void>(0xE6B90E9C, p0); } // 0xE6B90E9C
	static void NETWORK_EARN_FROM_PROPERTY(Any p0, Any p1) { invoke<Void>(0x9BE4F7E1, p0, p1); } // 0x9BE4F7E1
	static void _0x866004A8(Any p0, Any p1) { invoke<Void>(0x866004A8, p0, p1); } // 0x866004A8
	static void _0xCC068380(Any p0) { invoke<Void>(0xCC068380, p0); } // 0xCC068380
	static void NETWORK_EARN_FROM_ROCKSTAR(Any p0) { invoke<Void>(0x5A3733CC, p0); } // 0x5A3733CC
	static void NETWORK_EARN_FROM_VEHICLE(Any p0, Any p1) { invoke<Void>(0xF803589D, p0, p1); } // 0xF803589D
	static void _0x96B8BEE8(Any p0, Any p1) { invoke<Void>(0x96B8BEE8, p0, p1); } // 0x96B8BEE8
	static void NETWORK_SPENT_TAXI(Any p0, Any p1, Any p2) { invoke<Void>(0x1F3DB3E3, p0, p1, p2); } // 0x1F3DB3E3
	static void _0xBE70849B(Any p0, Any p1, Any p2) { invoke<Void>(0xBE70849B, p0, p1, p2); } // 0xBE70849B
	static void _0x451A2644(Any p0, Any p1, Any p2) { invoke<Void>(0x451A2644, p0, p1, p2); } // 0x451A2644
	static void _0x224A3488(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x224A3488, p0, p1, p2, p3); } // 0x224A3488
	static void NETWORK_SPENT_BETTING(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xF8A07513, p0, p1, p2, p3, p4); } // 0xF8A07513
	static void _0x8957038E(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x8957038E, p0, p1, p2, p3); } // 0x8957038E
	static void NETWORK_BUY_HEALTHCARE(Any p0, Any p1, Any p2) { invoke<Void>(0x832150E5, p0, p1, p2); } // 0x832150E5
	static void NETWORK_BUY_AIRSTRIKE(Any p0, Any p1, Any p2) { invoke<Void>(0x40470683, p0, p1, p2); } // 0x40470683
	static void _0x047547D4(Any p0, Any p1, Any p2) { invoke<Void>(0x047547D4, p0, p1, p2); } // 0x047547D4
	static void NETWORK_SPENT_AMMO_DROP(Any p0, Any p1, Any p2) { invoke<Void>(0x4B643076, p0, p1, p2); } // 0x4B643076
	static void NETWORK_BUY_BOUNTY(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xCB89CBE0, p0, p1, p2, p3); } // 0xCB89CBE0
	static void NETWORK_BUY_PROPERTY(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x7D479AAB, p0, p1, p2, p3); } // 0x7D479AAB
	static void NETWORK_SPENT_HELI_PICKUP(Any p0, Any p1, Any p2) { invoke<Void>(0x27EEBCAB, p0, p1, p2); } // 0x27EEBCAB
	static void NETWORK_SPENT_BOAT_PICKUP(Any p0, Any p1, Any p2) { invoke<Void>(0xB241CABD, p0, p1, p2); } // 0xB241CABD
	static void _0xDE7D398C(Any p0, Any p1, Any p2) { invoke<Void>(0xDE7D398C, p0, p1, p2); } // 0xDE7D398C
	static void NETWORK_SPENT_CASH_DROP(Any p0, Any p1, Any p2) { invoke<Void>(0x87BD1D11, p0, p1, p2); } // 0x87BD1D11
	static void _0xE792C4A5(Any p0, Any p1, Any p2) { invoke<Void>(0xE792C4A5, p0, p1, p2); } // 0xE792C4A5
	static void _0xE6AAA0D5(Any p0, Any p1, Any p2) { invoke<Void>(0xE6AAA0D5, p0, p1, p2); } // 0xE6AAA0D5
	static void _0x99CF02C4(Any p0, Any p1, Any p2) { invoke<Void>(0x99CF02C4, p0, p1, p2); } // 0x99CF02C4
	static void _0x20DDCF2F(Any p0, Any p1, Any p2) { invoke<Void>(0x20DDCF2F, p0, p1, p2); } // 0x20DDCF2F
	static void _0x2F7836E2(Any p0, Any p1, Any p2) { invoke<Void>(0x2F7836E2, p0, p1, p2); } // 0x2F7836E2
	static void NETWORK_SPENT_CARWASH(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x8283E028, p0, p1, p2, p3, p4); } // 0x8283E028
	static void NETWORK_SPENT_CINEMA(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x1100CAF5, p0, p1, p2, p3); } // 0x1100CAF5
	static void NETWORK_SPENT_TELESCOPE(Any p0, Any p1, Any p2) { invoke<Void>(0xAE7FF044, p0, p1, p2); } // 0xAE7FF044
	static void NETWORK_SPENT_HOLDUPS(Any p0, Any p1, Any p2) { invoke<Void>(0x1B3803B1, p0, p1, p2); } // 0x1B3803B1
	static void _0x7E97C92C(Any p0, Any p1, Any p2) { invoke<Void>(0x7E97C92C, p0, p1, p2); } // 0x7E97C92C
	static void _0x78436D07(Any p0, Any p1, Any p2) { invoke<Void>(0x78436D07, p0, p1, p2); } // 0x78436D07
	static void _0x5AEE2FC1(Any p0, Any p1, Any p2) { invoke<Void>(0x5AEE2FC1, p0, p1, p2); } // 0x5AEE2FC1
	static void _0x54198922(Any p0, Any p1, Any p2) { invoke<Void>(0x54198922, p0, p1, p2); } // 0x54198922
	static void _0x3D96A21C(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x3D96A21C, p0, p1, p2, p3); } // 0x3D96A21C
	static void _0x2E51C61C(Any p0, Any p1, Any p2) { invoke<Void>(0x2E51C61C, p0, p1, p2); } // 0x2E51C61C
	static void _0xD57A5125(Any p0, Any p1, Any p2) { invoke<Void>(0xD57A5125, p0, p1, p2); } // 0xD57A5125
	static void _0xD9622D64(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xD9622D64, p0, p1, p2, p3); } // 0xD9622D64
	static Any _0x16184FB5() { return invoke<Any>(0x16184FB5); } // 0x16184FB5
	static Any _0x4F5B781C(Any p0) { return invoke<Any>(0x4F5B781C, p0); } // 0x4F5B781C
	static Any _0xADF8F882() { return invoke<Any>(0xADF8F882); } // 0xADF8F882
	static Any NETWORK_CAN_RECEIVE_PLAYER_CASH(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x41F5F10E, p0, p1, p2, p3); } // 0x41F5F10E
}

namespace DLC1
{
	static Any _0x71D0CF3E(Any p0) { return invoke<Any>(0x71D0CF3E, p0); } // 0x71D0CF3E
	static Any _0x2E9D628C(Any p0, Any p1, Any p2) { return invoke<Any>(0x2E9D628C, p0, p1, p2); } // 0x2E9D628C
	static void INIT_SHOP_PED_COMPONENT(Any p0) { invoke<Void>(0xB818C7FC, p0); } // 0xB818C7FC
	static void INIT_SHOP_PED_PROP(Any p0) { invoke<Void>(0xF5659E50, p0); } // 0xF5659E50
	static Any _0xC937FF3D(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xC937FF3D, p0, p1, p2, p3); } // 0xC937FF3D
	static Any _0x594E862C(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x594E862C, p0, p1, p2, p3, p4, p5); } // 0x594E862C
	static void GET_SHOP_PED_QUERY_COMPONENT(Any p0, Any p1) { invoke<Void>(0xC0718904, p0, p1); } // 0xC0718904
	static void GET_SHOP_PED_COMPONENT(Any p0, Any p1) { invoke<Void>(0xB39677C5, p0, p1); } // 0xB39677C5
	static void GET_SHOP_PED_QUERY_PROP(Any p0, Any p1) { invoke<Void>(0x1D3C1466, p0, p1); } // 0x1D3C1466
	static void GET_SHOP_PED_PROP(Any p0, Any p1) { invoke<Void>(0xDB0A7A58, p0, p1); } // 0xDB0A7A58
	static Any _0xC8A4BF12(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xC8A4BF12, p0, p1, p2, p3); } // 0xC8A4BF12
	static Any _0x7D876DC0(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x7D876DC0, p0, p1, p2, p3); } // 0x7D876DC0
	static Any _0x159751B4(Any p0) { return invoke<Any>(0x159751B4, p0); } // 0x159751B4
	static void _0xE4FF7103(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xE4FF7103, p0, p1, p2, p3, p4); } // 0xE4FF7103
	static Any _0xCE70F183(Any p0) { return invoke<Any>(0xCE70F183, p0); } // 0xCE70F183
	static Any _0xC560D7C0(Any p0) { return invoke<Any>(0xC560D7C0, p0); } // 0xC560D7C0
	static void GET_FORCED_COMPONENT(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x382C70BE, p0, p1, p2, p3, p4); } // 0x382C70BE
	static void GET_FORCED_PROP(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x22DAE257, p0, p1, p2, p3, p4); } // 0x22DAE257
	static Any _0x8E2C7FD5(Any p0, Any p1, Any p2) { return invoke<Any>(0x8E2C7FD5, p0, p1, p2); } // 0x8E2C7FD5
	static Any _0x1ECD23E7(Any p0, Any p1) { return invoke<Any>(0x1ECD23E7, p0, p1); } // 0x1ECD23E7
	static void GET_SHOP_PED_QUERY_OUTFIT(Any p0, Any p1) { invoke<Void>(0x2F8013A1, p0, p1); } // 0x2F8013A1
	static void _0xCAFE9209(Any p0, Any p1) { invoke<Void>(0xCAFE9209, p0, p1); } // 0xCAFE9209
	static Any GET_SHOP_PED_OUTFIT_PROP(Any p0, Any p1) { return invoke<Any>(0x6C767148, p0, p1); } // 0x6C767148
	static Any _0x2798F56F(Any p0) { return invoke<Any>(0x2798F56F, p0); } // 0x2798F56F
	static Any GET_SHOP_PED_OUTFIT_COMPONENT(Any p0, Any p1) { return invoke<Any>(0x99EE4570, p0, p1); } // 0x99EE4570
	static Any _0x6641A864(Any p0, Any p1, Any p2) { return invoke<Any>(0x6641A864, p0, p1, p2); } // 0x6641A864
	static Any _0x818534AC(Any p0, Any p1, Any p2) { return invoke<Any>(0x818534AC, p0, p1, p2); } // 0x818534AC
	static int GET_NUM_DLC_VEHICLES() { return invoke<int>(0x8EAF9CF6); } // 0x8EAF9CF6
	static Any GET_DLC_VEHICLE_MODEL(Any p0) { return invoke<Any>(0xA2201E09, p0); } // 0xA2201E09
	static Any GET_DLC_VEHICLE_DATA(Any p0, Any p1) { return invoke<Any>(0xCF428FA4, p0, p1); } // 0xCF428FA4
	static Any GET_DLC_VEHICLE_FLAGS(Any p0) { return invoke<Any>(0xAB12738C, p0); } // 0xAB12738C
	static Any _0x2B757E6C() { return invoke<Any>(0x2B757E6C); } // 0x2B757E6C
	static Any GET_DLC_WEAPON_DATA(Any p0, Any p1) { return invoke<Any>(0xD88EC8EA, p0, p1); } // 0xD88EC8EA
	static Any _0x476B23A9(Any p0) { return invoke<Any>(0x476B23A9, p0); } // 0x476B23A9
	static Any GET_DLC_WEAPON_COMPONENT_DATA(Any p0, Any p1, Any p2) { return invoke<Any>(0x4B83FCAF, p0, p1, p2); } // 0x4B83FCAF
	static Any _0x06396058(Any p0) { return invoke<Any>(0x06396058, p0); } // 0x06396058
	static Any _0x35BCA844(Any p0) { return invoke<Any>(0x35BCA844, p0); } // 0x35BCA844
	static Any _0x59352658(Any p0) { return invoke<Any>(0x59352658, p0); } // 0x59352658
}

namespace DLC2
{
	static BOOL IS_DLC_PRESENT(Hash DlcHash) { return invoke<BOOL>(0x1F321943, DlcHash); } // 0x1F321943
	static Any _0x881B1FDB() { return invoke<Any>(0x881B1FDB); } // 0x881B1FDB
	static Any _0xC2169164() { return invoke<Any>(0xC2169164); } // 0xC2169164
	static Any _0xF79A97F5() { return invoke<Any>(0xF79A97F5); } // 0xF79A97F5
	static Any _0xF69B729C() { return invoke<Any>(0xF69B729C); } // 0xF69B729C
	static Any _0x517B601B() { return invoke<Any>(0x517B601B); } // 0x517B601B
	static Any _0x6087C10C(Any p0, Any p1) { return invoke<Any>(0x6087C10C, p0, p1); } // 0x6087C10C
}

namespace SYSTEM
{
	static void WAIT(int ms) { invoke<Void>(0x7715C03B, ms); } // 0x7715C03B
	static int START_NEW_SCRIPT(char* ScriptName, int StackSize) { return invoke<int>(0x3F166D0E, ScriptName, StackSize); } // 0x3F166D0E
	static int START_NEW_SCRIPT_WITH_ARGS(char* ScriptName, Any Args, int ArgCount, int StackSize) { return invoke<int>(0x4A2100E4, ScriptName, Args, ArgCount, StackSize); } // 0x4A2100E4
	static Any _NULL_START_NEW_SCRIPT(int p0, int StackSize) { return invoke<Any>(0x8D15BE5D, p0, StackSize); } // 0x8D15BE5D
	static Any _NULL_START_NEW_SCRIPT_WITH_ARGS(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xE38A3AD4, p0, p1, p2, p3); } // 0xE38A3AD4
	static int TIMERA() { return invoke<int>(0x45C8C188); } // 0x45C8C188
	static int TIMERB() { return invoke<int>(0x330A9C0C); } // 0x330A9C0C
	static void SETTIMERA(int TimerA) { invoke<Void>(0x35785333, TimerA); } // 0x35785333
	static void SETTIMERB(int TimerB) { invoke<Void>(0x27C1B7C6, TimerB); } // 0x27C1B7C6
	static float TIMESTEP() { return invoke<float>(0x50597EE2); } // 0x50597EE2
	static float SIN(float p0) { return invoke<float>(0xBF987F58, p0); } // 0xBF987F58
	static float COS(float p0) { return invoke<float>(0x00238FE9, p0); } // 0x00238FE9
	static float SQRT(float p0) { return invoke<float>(0x145C7701, p0); } // 0x145C7701
	static float POW(float base, float exponent) { return invoke<float>(0x85D134F8, base, exponent); } // 0x85D134F8
	static float VMAG(float p0, float p1, float p2) { return invoke<float>(0x1FCF1ECD, p0, p1, p2); } // 0x1FCF1ECD
	static float VMAG2(float p0, float p1, float p2) { return invoke<float>(0xE796E629, p0, p1, p2); } // 0xE796E629
	static float VDIST(float X1, float Y1, float Z1, float X2, float Y2, float Z2) { return invoke<float>(0x3C08ECB7, X1, Y1, Z1, X2, Y2, Z2); } // 0x3C08ECB7
	static float VDIST2(float X1, float Y1, float Z1, float X2, float Y2, float Z2) { return invoke<float>(0xC85DEF1F, X1, Y1, Z1, X2, Y2, Z2); } // 0xC85DEF1F
	static int SHIFT_LEFT(int Value, int BitShift) { return invoke<int>(0x314CC6CD, Value, BitShift); } // 0x314CC6CD
	static int SHIFT_RIGHT(int Value, int BitShift) { return invoke<int>(0x352633CA, Value, BitShift); } // 0x352633CA
	static int FLOOR(float Value) { return invoke<int>(0x32E9BE04, Value); } // 0x32E9BE04
	static int CEIL(float Value) { return invoke<int>(0xD536A1DF, Value); } // 0xD536A1DF
	static int ROUND(float Value) { return invoke<int>(0x323B0E24, Value); } // 0x323B0E24
	static float TO_FLOAT(int Value) { return invoke<float>(0x67116627, Value); } // 0x67116627
}

namespace DECORATOR
{
	static Any _0xBBAEEF94(Any p0, Any p1, Any p2) { return invoke<Any>(0xBBAEEF94, p0, p1, p2); } // 0xBBAEEF94
	static Any _0x8E101F5C(Any p0, Any p1, Any p2) { return invoke<Any>(0x8E101F5C, p0, p1, p2); } // 0x8E101F5C
	static Any DECOR_SET_INT(Any p0, char *p1, Any p2) { return invoke<Any>(0xDB718B21, p0, p1, p2); } // 0xDB718B21
	static Any _0xDBCE51E0(Any p0, Any p1) { return invoke<Any>(0xDBCE51E0, p0, p1); } // 0xDBCE51E0
	static Any _0xDDDE59B5(Any p0, char *p1) { return invoke<Any>(0xDDDE59B5, p0, p1); } // 0xDDDE59B5
	static Any _0x74EF9C40(Any p0, Any p1) { return invoke<Any>(0x74EF9C40, p0, p1); } // 0x74EF9C40
	static Any _0xE0E2640B(Any p0, Any p1) { return invoke<Any>(0xE0E2640B, p0, p1); } // 0xE0E2640B
	static void _0x68BD42A9(Any p0, Any p1) { invoke<Void>(0x68BD42A9, p0, p1); } // 0x68BD42A9
	static Any _0x7CF0971D(Any p0, Any p1) { return invoke<Any>(0x7CF0971D, p0, p1); } // 0x7CF0971D
	static void _0x7F3F1C02() { invoke<Void>(0x7F3F1C02); } // 0x7F3F1C02
}

static int _0xF8D7AF3B(int playerIndex) {
	return invoke<int>(0xF8D7AF3B,playerIndex);
}

namespace UNK_SC
{
	static Any _0x6BE5DF29() { return invoke<Any>(0x6BE5DF29); } // 0x6BE5DF29
	static Any _0x5ECF955D(Any p0) { return invoke<Any>(0x5ECF955D, p0); } // 0x5ECF955D
	static Any _0xD1ED1D48(Any p0) { return invoke<Any>(0xD1ED1D48, p0); } // 0xD1ED1D48
	static Any _0x19EE0CCB(Any p0) { return invoke<Any>(0x19EE0CCB, p0); } // 0x19EE0CCB
	static Any SC_INBOX_MESSAGE_GET_DATA_INT(Any p0, Any p1, Any p2) { return invoke<Any>(0x88068C7C, p0, p1, p2); } // 0x88068C7C
	static Any SC_INBOX_MESSAGE_GET_DATA_FLOAT(Any p0, Any p1, Any p2) { return invoke<Any>(0x6A67FC31, p0, p1, p2); } // 0x6A67FC31
	static Any SC_INBOX_MESSAGE_GET_DATA_STRING(Any p0, Any p1, Any p2) { return invoke<Any>(0x15607620, p0, p1, p2); } // 0x15607620
	static Any _0xEBE420A4(Any p0) { return invoke<Any>(0xEBE420A4, p0); } // 0xEBE420A4
	static Any _0x2C959AF9(Any p0) { return invoke<Any>(0x2C959AF9, p0); } // 0x2C959AF9
	static void _0x0B9A3512(networkHandleMgr *playerData) { invoke<Void>(0x0B9A3512, playerData); } // 0x0B9A3512
	static void _0x75324674(Any p0) { invoke<Void>(0x75324674, p0); } // 0x75324674
	static Any SC_INBOX_MESSAGE_GET_UGCDATA(Any p0, Any p1) { return invoke<Any>(0x88CA3BFC, p0, p1); } // 0x88CA3BFC
	static Any _0x628F489B(unsigned int *p0) { return invoke<Any>(0x628F489B, p0); } // 0x628F489B
	static Any _0xAB3346B5(Any p0, Any p1) { return invoke<Any>(0xAB3346B5, p0, p1); } // 0xAB3346B5
	static void _0x095D5EBD(Any p0, Any p1) { invoke<Void>(0x095D5EBD, p0, p1); } // 0x095D5EBD
	static Any _0xDB75CDD1() { return invoke<Any>(0xDB75CDD1); } // 0xDB75CDD1
	static Any _0xC98160E1(Any p0, Any p1) { return invoke<Any>(0xC98160E1, p0, p1); } // 0xC98160E1
	static void _0x2B240E0A(Any p0, Any p1) { invoke<Void>(0x2B240E0A, p0, p1); } // 0x2B240E0A
	static void _0x9A703A2B(Any p0) { invoke<Void>(0x9A703A2B, p0); } // 0x9A703A2B
	static void _0xD094F11A() { invoke<Void>(0xD094F11A); } // 0xD094F11A
	static void _0xAF3C081B(Any p0) { invoke<Void>(0xAF3C081B, p0); } // 0xAF3C081B
	static void _0x2FB9F53C(Any p0) { invoke<Void>(0x2FB9F53C, p0); } // 0x2FB9F53C
	static Any _0x6C5738AB() { return invoke<Any>(0x6C5738AB); } // 0x6C5738AB
	static Any _0x468668F0() { return invoke<Any>(0x468668F0); } // 0x468668F0
	static Any _0x90C74343(Any p0, Any p1) { return invoke<Any>(0x90C74343, p0, p1); } // 0x90C74343
	static Any _0x3ACE6D6B(Any p0, Any p1) { return invoke<Any>(0x3ACE6D6B, p0, p1); } // 0x3ACE6D6B
	static Any _0x579B4510(Any p0, Any p1) { return invoke<Any>(0x579B4510, p0, p1); } // 0x579B4510
	static Any _0xDF45B2A7(Any p0) { return invoke<Any>(0xDF45B2A7, p0); } // 0xDF45B2A7
	static Any _0xDF084A6B(Any p0, Any p1) { return invoke<Any>(0xDF084A6B, p0, p1); } // 0xDF084A6B
	static Any _0xFFED3676(Any p0) { return invoke<Any>(0xFFED3676, p0); } // 0xFFED3676
	static Any _0xA796D7A7(Any p0) { return invoke<Any>(0xA796D7A7, p0); } // 0xA796D7A7
	static Any _0x09497F31(Any p0) { return invoke<Any>(0x09497F31, p0); } // 0x09497F31
	static Any _0x4D8A6521(Any p0) { return invoke<Any>(0x4D8A6521, p0); } // 0x4D8A6521
	static Any _0x7AA36406(Any p0, Any p1) { return invoke<Any>(0x7AA36406, p0, p1); } // 0x7AA36406
	static Any _0xF379DCE4(Any p0) { return invoke<Any>(0xF379DCE4, p0); } // 0xF379DCE4
	static Any _0x65D84665(Any p0) { return invoke<Any>(0x65D84665, p0); } // 0x65D84665
	static Any _0xD268255C(Any p0) { return invoke<Any>(0xD268255C, p0); } // 0xD268255C
	static Any _0xC96456BA() { return invoke<Any>(0xC96456BA); } // 0xC96456BA
	static Any _0x8E7AEEB7(Any p0) { return invoke<Any>(0x8E7AEEB7, p0); } // 0x8E7AEEB7
	static Any _0xE778B2A7(Any p0, Any p1, Any p2) { return invoke<Any>(0xE778B2A7, p0, p1, p2); } // 0xE778B2A7
	static Any _0xCE7D50A8(Any p0, Any p1, Any p2) { return invoke<Any>(0xCE7D50A8, p0, p1, p2); } // 0xCE7D50A8
	static Any _0xD26CCA46(Any p0, Any p1) { return invoke<Any>(0xD26CCA46, p0, p1); } // 0xD26CCA46
	static Any _0xA3EFE4A1(Any p0) { return invoke<Any>(0xA3EFE4A1, p0); } // 0xA3EFE4A1
	static Any _0x24D84334(Any p0) { return invoke<Any>(0x24D84334, p0); } // 0x24D84334
	static Any _0x8A023024(Any p0, Any p1) { return invoke<Any>(0x8A023024, p0, p1); } // 0x8A023024
	static Any _0x1C65B038() { return invoke<Any>(0x1C65B038); } // 0x1C65B038
	static Any _0x4D4C37B3() { return invoke<Any>(0x4D4C37B3); } // 0x4D4C37B3
	static Any _0xAED95A6F(Any p0, Any p1) { return invoke<Any>(0xAED95A6F, p0, p1); } // 0xAED95A6F
	static void _0x486867E6() { invoke<Void>(0x486867E6); } // 0x486867E6
}

namespace UNK
{
	static int _RETURN_ZERO() { return invoke<int>(0x106C8317); } // 0x106C8317
	static int _RETURN_ZERO2() { return invoke<int>(0xD87F3A9E); } // 0xD87F3A9E
	static void _0xC0B971EA(BOOL b) { invoke<Void>(0xC0B971EA, b); } // 0xC0B971EA
	static Any _0x94BCAC7C() { return invoke<Any>(0x94BCAC7C); } // 0x94BCAC7C
	static void _0x7D90EEE5(Any p0) { invoke<Void>(0x7D90EEE5, p0); } // 0x7D90EEE5
	static Any _0x734CFEDA() { return invoke<Any>(0x734CFEDA); } // 0x734CFEDA
	static void _0x8C227332(Any p0) { invoke<Void>(0x8C227332, p0); } // 0x8C227332
}
static void CRATE_DROP(int alwaysthiryone, int xp, int money/*max of 20k*/, int weaponhash, int alwayszero, int arg6/*a multiplier maybe?*/, int *arg7, bool arg8) { invoke<Void>(0x6602CED6, alwaysthiryone,xp,money,weaponhash,alwayszero,arg6,arg7,arg8); };
static void CRATE_CREATED(float x, float y, float z) { invoke<Void>(0xD003E648, x, y, z); } //something to do with crate drop! off_192C300 is data and this func was found in scripts


/*namespace std {
std::snprintf$ = (int(*)(char*, size_t, const char*, ...))&snprintf$_stub;
};*/

//void SET_VEHICLE_WINDOW_TINT(Vehicle vehicle, int Tint) { SET_VEHICLE_WINDOW_TINT(vehicle,Tint);/*invoke<Void>(0x497C8787, vehicle, Tint);*/ } // 0x497C8787


int _rand() {
	return GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 0x7FFFFFFF);
}


bool isPlayerValid(int player) {
	char* name = PLAYER::GET_PLAYER_NAME(player);
	bool isInvalid = GAMEPLAY::ARE_STRINGS_EQUAL(name, "**Invalid**") && strstr("**Invalid**", name);
	if (!isInvalid) {
		return true;
	}
	else {
		return false;
	}
}
bool isPlayerValid(char* name) {
	bool isInvalid = GAMEPLAY::ARE_STRINGS_EQUAL(name, "**Invalid**") && strstr("**Invalid**", name);
	if (!isInvalid) {
		return true;
	}
	else {
		return false;
	}
}

#pragma pop_options