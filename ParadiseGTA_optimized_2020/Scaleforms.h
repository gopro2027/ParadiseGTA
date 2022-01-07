#ifdef scaleformsfileused

enum BlipIcons
{
        BLIP_CIRCLE = 1,
        BLIP_COP = 3,
        BLIP_PLAYERARROW = 6,
        BLIP_NORTH = 7,
        BLIP_WAYPOINT = 8,
        BLIP_TRANSLUCENTCIRCLE = 9,
        BLIP_COPHELICOPTER = 15,
        BLIP_JET = 16,
        BLIP_CABLECAR = 36,
        BLIP_RACEFLAG = 38,
        BLIP_OWNEDPROPERTY = 40,
        BLIP_SPEECHBUBLE = 47,
        BLIP_SQUAREGARAGE = 50,
        BLIP_PILL = 51,
        BLIP_CONVIENCESTOREMP = 52,
        BLIP_TAXI = 56,
        BLIP_CONVIENCESTORE = 59,
        BLIP_SHERIF = 60,
        BLIP_PARAMEDIC = 61,
        BLIP_HELICOPTER = 64,
        BLIP_QUESTIONMARK = 66,
        BLIP_TRUCK = 67,
        BLIP_HOOK = 68,
        BLIP_BARBERSHOP = 71,
        BLIP_PAYNSPRAY = 72,
        BLIP_CLOTHINGSTORE = 73,
        BLIP_TATTOOSTORE = 75,
        BLIP_MICHAEL = 78,
        BLIP_SKULL = 84,
        BLIP_SANANDREASFLIGHTSCHOOL = 90,
        BLIP_BAR = 93,
        BLIP_PARACHUTING = 94,
        BLIP_CARWASH = 100,
        BLIP_DARTS = 103,
        BLIP_GOLF = 109,
        BLIP_AMMUNATION = 110,
        BLIP_SHOOTINGRANGE = 119,
        BLIP_STRIPCLUB = 121,
        BLIP_TENNIS = 122,
        BLIP_TRIATHLON = 126,
        BLIP_OFFROADMOTOATVRACE = 127,
        BLIP_SPEECHBUBLE2 = 133,
        BLIP_KEY = 134,
        BLIP_MOVIES = 135,
        BLIP_MUSIC = 136,
        BLIP_ASSAULTRIFLE = 150,
        BLIP_GRENADE = 152,
        BLIP_HEALTH = 153,
        BLIP_RPG = 157,
        BLIP_SHOTGUN = 158,
        BLIP_MAC10 = 159,
        BLIP_SNIPERRIFLE = 160,
        BLIP_POINTOFINTREST = 162,
        BLIP_PASSIVEPLAYER = 163,
        BLIP_PLAYERPAUSED = 164,
        BLIP_MINIGUN = 173,
        BLIP_GRENADELAUNCHER = 174,
        BLIP_BODYARMOR = 175,
        BLIP_YOGA = 197,
        BLIP_CAR = 225,
        BLIP_FAIRGROUNDRIDE = 266,
        BLIP_SPAGHETTIO = 270,
        BLIP_DOGBONE = 273,
        BLIP_DEADPLAYER = 274,
        BLIP_SIMEON = 293,
        BLIP_BOUNTY = 303,
        BLIP_MISSION = 304,
        BLIP_SURVIVAL = 305,
        BLIP_SPECIALCRATE = 306,
        BLIP_PLANEVEHICLE = 307,
        BLIP_SUBMARINE = 308,
        BLIP_DEATHMATCH = 310,
        BLIP_ARMWRESTLE = 311,
        BLIP_AMMUNATIONWITHRANGE = 313,
        BLIP_STUNTPLANETIMETRIAL = 314,
        BLIP_STREETRACE = 315,
        BLIP_SEARACE = 316,
        BLIP_MOTORCYCLE = 348,
        BLIP_HOUSEFORSALEMP = 350,
        BLIP_AMMODROP = 351,
        BLIP_HELIBLADESENEMY = 353,
        BLIP_GARAGE = 357,
        BLIP_MASKSHOP = 362,
        BLIP_GARAGEFORSALE = 369,
        BLIP_HELIPADFORSALE = 370,
        BLIP_DOCKFORSALE = 371,
        BLIP_HELIPADFORSALE2 = 372,
        BLIP_OWNEDPROPERTY2 = 374,
        BLIP_HOUSEFORSALE = 375,
        BLIP_BIKERACE = 376,
        BLIP_TEAMDEATHMATCH = 378,
        BLIP_VEHICLEDEATHMATCH = 380,
        BLIP_PAPARAZZO = 389,
        BLIP_BULLSHARKTESTOSTRONE = 403,
        BLIP_GANGATTACK = 406,
        BLIP_CAPTURE = 408,
        BLIP_LASTTEAMSTANDING = 409,
        BLIP_BOATVEHICLE = 410,
        BLIP_RPLOGO = 416,
        BLIP_PLAYERINHOUSE = 417,
        BLIP_BOUNTYINHOUSE = 418,
        BLIP_AMERICANFLAG = 419,
        BLIP_TANK = 421,
        BLIP_HELICOPTERBLADES = 422,
        BLIP_PLANE = 423,
        BLIP_JET2 = 424,
        BLIP_INSURGENT = 426,
        BLIP_BOAT = 427,
        BLIP_HEISTSROOM = 428,
        BLIP_DOLLARSIGN = 431,
};
 
enum BlipColors
{
        BLIPCOLOR_NONE = 0x0,
        BLIPCOLOR_RED = 0x1,
        BLIPCOLOR_GREEN = 0x2,
        BLIPCOLOR_BLUE = 0x3,
        BLIPCOLOR_PLAYER = 0x4,
        BLIPCOLOR_YELLOWMISSION = 0x5,
        BLIPCOLOR_FRIENDLYVEHICLE = 0x26,
        BLIPCOLOR_MICHAEL = 0x2A,
        BLIPCOLOR_FRANKLIN = 0x2B,
        BLIPCOLOR_TREAVOR = 0x2C,
        BLIPCOLOR_REDMISSION = 0x31,
        BLIPCOLOR_MISSIONVEHICLE = 0x36,
        BLIPCOLOR_YELLOWMISSION2 = 0x3C,
        BLIPCOLOR_MISSION = 0x42,
        BLIPCOLOR_WAYPOINT = 0x53
};
/*

NotificationText = 0x02066BDC,
NotificationState = 0x020672EC + 0x03,
ButtonsMonitoring = 0x01FD7D88 + 0x08;
*/
char MenuArray[500];
int MenuArrayPlace = 0;
char MenuArrayBreak[] = "~n~~s~";
void beginMenu() {
	//UI::CLEAR_ALL_HELP_MESSAGES();
	//*(volatile int*)(0x020672EC + 0x03) = 0x03;
	for (int i = 0; i < 500; i++)
		MenuArray[i] = 0;
}
void closeMiniMenu() {
	*(volatile int*)(0x020672EC + 0x03) = 0x02;
}
void openMiniMenu() {
	*(volatile int*)(0x020672EC + 0x03) = 0x03;
}
void pushMenu(char *text) {
	int j = 0;
	while (text[j] != 0) {
		if (MenuArrayPlace < 500) {
			MenuArray[MenuArrayPlace] = text[j];
			MenuArrayPlace++;
		}
		j++;
	}
	j = 0;
	while (MenuArrayBreak[j] != 0) {
		if (MenuArrayPlace < 500) {
			MenuArray[MenuArrayPlace] = MenuArrayBreak[j];
			MenuArrayPlace++;
		}
		j++;
	}
}
//int jjjkkkkjjj = -1;
void popMenu() {
	//UI::_SET_TEXT_COMPONENT_FORMAT("STRING");
	//UI::_ADD_TEXT_COMPONENT_STRING(MenuArray);
	//*(char**)0x02066BDC = MenuArray;
	//if (submenu != Closed) {
		for (int i = 0; i < 500; i++)
			*(char*)(0x02066BDC+i) = MenuArray[i];
		openMiniMenu();
	//} else {
		//closeMiniMenu();
	//}
	//*(volatile int*)(0x020672EC + 0x03) = 0x03;
	//jjjkkkkjjj++;
	//if (jjjkkkkjjj > 50) jjjkkkkjjj = -1;
	//MenuArrayPlace = 0;
}

/*void createMiniMenu(const char *arg, ... ){
	UI::_SET_TEXT_COMPONENT_FORMAT("STRING");
    va_list arguments;
    for (va_start(arguments, arg); arg != NULL; arg = va_arg(arguments, const char *)) {
        UI::_ADD_TEXT_COMPONENT_STRING((char*)arg);
		UI::_ADD_TEXT_COMPONENT_STRING("~n~~s~");
    }
    va_end(arguments);
	UI::_0xB59B530D(0, 0, 0, -1);
}*/

/*void BriefMessage(char *text) {
	UI::_SET_TEXT_COMPONENT_FORMAT("STRING");
	//UI::_ADD_TEXT_COMPONENT_ITEM_STRING(text);
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	UI::_ADD_TEXT_COMPONENT_STRING("~n~~s~");
	UI::_0xB59B530D(0, 0, 0, -1);
}*/

/*void drawMenu(char *first,...)
{
    va_list ap;
    int j;
    va_start(ap, first); //Requires the last fixed parameter (to get the address)
    for(j=0; j<20; j++) {
        char *k = va_arg(ap, char *); //Requires the type to cast to. Increments ap to the next argument.
		std::cout << k << " " << j << " " << std::endl;
	}
    va_end(ap);
}*/

class ScaleformBlip {
private:
	int blipid;
public:
	bool created;
	Blip getBlip() {
		return blipid;
	}
	void create() {
		blipid = UI::ADD_BLIP_FOR_COORD(-9999,-9999,-9999);
		created = true;
	}
	void setColor(int color) {
		UI::SET_BLIP_COLOUR(blipid,color);
	}
	void setAlpha(int a) {
		UI::SET_BLIP_ALPHA(blipid,a);
	}
	void setIcon(int icon) {
		UI::SET_BLIP_SPRITE(blipid,icon);
	}
	void removeBlip() {
		UI::REMOVE_BLIP(blipid);
		created = false;
	}
};
class Scaleform {
private:
	Blip blips[20];
	void set_text_component(char *text) {
		GRAPHICS::_BEGIN_TEXT_COMPONENT("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING(text);
		GRAPHICS::_END_TEXT_COMPONENT();
	}
	void removeBlips() {
		for (int i = 0; i < 20; i++) {
			UI::REMOVE_BLIP(blips[i]);
		}
	}
public:
	int sc;
	int ic;
	void init(char *type) {
		sc = GRAPHICS::REQUEST_SCALEFORM_MOVIE(type/*"TEXTFIELD"*//*"instructional_buttons"*/);
		GRAPHICS::_0x7B48E696(sc, 255, 255, 255, 0);
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(sc, "CLEAR_ALL");
		GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(sc, "SET_CLEAR_SPACE");
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(200);
		GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
		ic = 0;
	}
	void addText(char *text) {
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(sc, "SET_TEXT");
		GRAPHICS::_BEGIN_TEXT_COMPONENT("STRING");
			UI::_SET_TEXT_COMPONENT_FORMAT("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING(text);
		GRAPHICS::_END_TEXT_COMPONENT();
		//set_text_component(text);
		GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
		ic++;
	}
	void addBlip(ScaleformBlip blip) {
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(sc, "SET_TEXT");
		GRAPHICS::_BEGIN_TEXT_COMPONENT("STRING");
		UI::_0x5DE98F0A(blip.getBlip());
		//UI::_ADD_TEXT_COMPONENT_ITEM_STRING("~BLIP_GARAGE~");
		GRAPHICS::_END_TEXT_COMPONENT();
		GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
	}
	void addInstruction(int button, char *text) {
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(sc, "SET_DATA_SLOT");
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(ic);
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(button);
		set_text_component(text);
		GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
		ic++;
	}
	void setFontSize(float size) {
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(sc, "SET_TEXT_POINT_SIZE");
        GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_FLOAT(size);
        GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
	}
	void render(float x = 0.5f, float y = 0.5f, float width = 0.3f, float height = 0.4f) {
		//GRAPHICS::DRAW_SCALEFORM_MOVIE(sc,x,y,width,height,255,0,0,255);
		GRAPHICS::_SET_SCREEN_DRAW_POSITION(76, 84);//76, 84
        GRAPHICS::_0x76C641E4(0.0, 0.0, 0.0, 0.0);
		ic = 0;
	}
	void reset() {
		removeBlips();
	}
};

#endif







//scaleforms and functions: https://scaleform.devtesting.pizza/
namespace ScaleformLib {

	int RequestScaleformMovie(char *scaleform) {
		return GRAPHICS::REQUEST_SCALEFORM_MOVIE(scaleform);
	}

	bool HasScaleformMovieLoaded(int scaleform) {
		return GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(scaleform);
	}

	void PushScaleformMovieFunction(int scaleform, char *function) {
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(scaleform,function);
	}

	void PushScaleformMovieFunctionParameterInt(int value) {
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(value);
	}

	void PushScaleformMovieFunctionParameterString(char *value) {
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_STRING(value);
	}

	void PushScaleformMovieFunctionParameterFloat(float value) {
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_FLOAT(value);
	}

	void PopScaleformMovieFunctionVoid() {
		GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
	}

	void DrawScaleformMovie(int scaleformHandle, float x, float y, float width, float height, int red, int green, int blue, int alpha) {
		GRAPHICS::DRAW_SCALEFORM_MOVIE(scaleformHandle,x,y,width,height,red,green,blue,alpha);
	}
	
	namespace RAGE {
		float sharpness = 1.0f;//sharpness overall, causes lots of lag
		float unk1 = 100.0f;//fuzziness around the corners, 0 is very fuzzy, 100 is no fuzz, I guess this is like a smoothing value so the smaller the value is, the more smoothing it does and the higher it is, the more exact it is and no smoothing
		float unk2 = 0.0f;//doesn't seem to affect anything
		void Render3D(int scaleform, Vector3 position, Vector3 rotation, Vector3 scale) {
			//_DRAW_SCALEFORM_MOVIE_3D_NON_ADDITIVE
		    invoke<Void>(0x899933C8, scaleform, position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, unk1, sharpness, unk2, scale.x, scale.y, scale.z, 2);
        }
        /*void Render3DAdditive(int scaleform, Vector3 position, Vector3 rotation, Vector3 scale) {
			//DRAW_SCALEFORM_MOVIE_3D
            invoke<Void>(0xC4F63A89, scaleform, position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, 5.0f, 5.0f, 5.0f, scale.x, scale.y, scale.z, 2);
        }*/
	}

	void DrawScaleformMovie_3dNonAdditive(int scaleform, float posX,float posY, float posZ, float rotX, float rotY, float rotZ,float p7, float p8, float p9, float scaleX, float scaleY,float scaleZ, Any p13) {
		invoke<Void>(0xC4F63A89/*0x899933C8*/,scaleform,posX,posY,posZ,rotX,rotY,rotZ,p7,p8,p9,scaleX,scaleY,scaleZ,p13);
		invoke<Void>(0x899933C8,scaleform,posX,posY,posZ,rotX,rotY,rotZ,p7,p8,p9,scaleX,scaleY,scaleZ,p13);
	}

	void DrawScaleformMovie_3dNonAdditive(int scaleform_handle,Vector3 pos, Vector3 scale) {//local min, max = GetModelDimensions(GetEntityModel(vehicle), {}, {}) 
		Vector3 camRot = CAM::GET_GAMEPLAY_CAM_ROT(2);
		DrawScaleformMovie_3dNonAdditive(
			scaleform_handle, //scaleform
			pos.x, pos.y, pos.z, //position
			0, 0, -camRot.z, // rotation
			2.0, // unk
			1.0, //sharpness
			1.0, // unk,
			scale.x, scale.y, scale.z, // draw scale
			2 // unk
		);
	}

	

};

float scX = 0.5f;
float scY = 0.5f;
float scW = 0.25;
float scH = 0.25;
float scaleformScale = 4.4f;//3.3 looked good when flat

/*

broken scaleform is one of these: (in 170's)
pause_menu_pages_char_select
pause_menu_pages_corona
pause_menu_pages_corona_lobby
pause_menu_pages_corona_players
pause_menu_pages_corona_race
pause_menu_pages_crews
pause_menu_pages_friends
pause_menu_pages_friends_mp
pause_menu_pages_gallery
pause_menu_pages_game
*/
//char *scaleformsList[] = {"TEXTFIELD","alien_runes_overlay","app_job_list","app_mission_stats_view","app_numberpad","app_todo_list","app_todo_view","app_trackify","arm1_connected_baby","arm3_connected_lara","assassinations","atm","badger_blank_home","badger_blank_inprogress","badger_blank_lamar","badger_blank_lester","badger_blank_michael","badger_dialing_michael","binoculars","blow_torch","breaking_news","camera_gallery","camera_shutter","car_fixing","cellphone_alert_popup","cellphone_badger","cellphone_cutscene","cellphone_facade","cellphone_ifruit","cellphone_prologue","controller_test","countdown","custom_warning_screen","desktop_pc","digiscanner","dre1_badger_lj","ecg_monitor","epsilon_tract","exl2_blank_jimmy","exl2_connected_jimmy","facade_blank_home","facade_blank_inprogress","facade_blank_michael","facade_computer_desktopwide","fam2_playmusic","fam3_01_ncallingmartin","fam3_02_ncallingmartin","fam3_03_ncallingmartin","fam3_04_ncallingmartin","fam3_05_ncallingmartin","fam3_all_ncallingmartin","fame_or_shame_camera","fib3_daven","fib3_steveh","fib4_eyefindmap","fib5_lestertext","fib_pc","finb_connected_amanda","finc1_eyefind","finc1_merrysite","font_lib_efigs","font_lib_heists","font_lib_taxi","font_lib_typewriter","font_lib_web","graphic_design","gtav_online","hacking_pc","heist_agency","heist_docks","heist_endscreen","heist_finale","heist_jewellery","heist_paleto","heli_cam","hud","hud_area_name","hud_cash","hud_cash_change","hud_district_name","hud_drugs_purse_01","hud_drugs_purse_02","hud_drugs_purse_03","hud_drugs_purse_04","hud_mission_passed_message","hud_mp_cash","hud_mp_message","hud_player_switch_alert","hud_radio_stations_wheel","hud_reticle","hud_saving","hud_street_name","hud_vehicle_name","ifruit_blank_email","ifruit_blank_franklin","ifruit_blank_home","ifruit_blank_inprogress","ifruit_computer_desktopwide","ifruit_connected_franklin","instructional_buttons","jewel_heist_counter","jhpb_01_laptop","jhpb_02_laptop","jhpb_03_laptop","jos2_01_photogallery","jos2_02_photogallery","jos2_all_photogallery","lester_hack_pc","letter_scraps","lifeinvader_presentation","lifeinvader_tablet43","ls1_lester_eyefind","ls1_lester_preeyefind","ls1_lifeinvader_call","ls1_lifeinvader_home","ls1_lifeinvader_updates","mar1_tablet_havier","mar1_tablet_havierhori","mic3_lester","mic4_breakingnews","midsized_message","mission_complete","mission_quit","mission_target_complete","mp_award_freemode","mp_big_message_freemode","mp_bounty_board","mp_car_stats_01","mp_car_stats_02","mp_car_stats_03","mp_car_stats_04","mp_car_stats_05","mp_car_stats_06","mp_car_stats_07","mp_car_stats_08","mp_car_stats_09","mp_car_stats_10","mp_crew_tag","mp_freemode_checkpoint","mp_freemode_checkpoint_1","mp_freemode_checkpoint_10","mp_freemode_checkpoint_2","mp_freemode_checkpoint_3","mp_freemode_checkpoint_4","mp_freemode_checkpoint_5","mp_freemode_checkpoint_6","mp_freemode_checkpoint_7","mp_freemode_checkpoint_8","mp_freemode_checkpoint_9","mp_gamer_info","mp_icons","mp_killstrip_freemode","mp_matchmaking_card","mp_matchmaking_selector","mp_matchmaking_vehicle_info","mp_medal_freemode","mp_mission_details_card","mp_mission_name_freemode","mp_mission_name_freemode_1","mp_mission_name_freemode_2","mp_online_list_card","mp_player_card","mp_results_panel","mp_unlock_freemode","mp_vehicle_info","observatory_scope","ome1_powercell","pause_menu_header","pause_menu_pages_awards","pause_menu_pages_char_mom_dad","pause_menu_pages_char_select","pause_menu_pages_corona","pause_menu_pages_corona_lobby","pause_menu_pages_corona_players","pause_menu_pages_corona_race","pause_menu_pages_crews","pause_menu_pages_friends","pause_menu_pages_friends_mp","pause_menu_pages_gallery","pause_menu_pages_game","social_club_message","pause_menu_pages_info","pause_menu_pages_map","pause_menu_pages_missioncreator","pause_menu_pages_save","pause_menu_pages_settings","pause_menu_pages_stats","pause_menu_pages_store","pause_menu_pages_weapons","pause_menu_shared_components","pause_menu_shared_components_02","pause_menu_shared_components_03","pause_menu_shared_components_mp_01","pause_menu_sp_content","pause_menu_store_content","player_switch","player_switch_prologue","player_switch_stats_panel","psychology_report","race_position","rampage","rcmaude_laptop","remote_sniper_hud","remote_sniper_loading","rh2a_01_laptop","rh2a_02_laptop","rh2a_03_laptop","rh2a_04_laptop","rh2a_05_laptop","rh2a_06_laptop","rh2a_07_laptop","saving_footer","security_cam","security_camera","shit_skip","shop_menu","shop_menu_dlc","social_club_message","social_club_tv","splash_text","stat_update_icon","stat_update_list","store_background","store_blackout","store_instructional_buttons","stungun_tutorial","stunt_jumps","sub_cam","sub_pc","tattoo_buttons","taxi_display","teeth_pulling","traffic_cam","tv_frame","tv_static","uv_carslist","voting","wind_meter","yoga_buttons"};

//char *scaleformsList[50];

static bool initialized = false;
static int scaleform = -1;

char *scaleformName = "TEXTFIELD";//"social_club_message";

void reloadScaleform(char *sc) {
	GRAPHICS::SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(&scaleform);
	scaleformName = sc;
	initialized = false;
	scaleform = -1;
}

Vector3 coordsForScaleform = {0,0,0};
char* getMenuStringBuffer();
void testTextFieldLoop() {

	
	if (scaleform == -1)
		scaleform = ScaleformLib::RequestScaleformMovie(scaleformName/*"social_club_message"*/);
	if (ScaleformLib::HasScaleformMovieLoaded(scaleform) && initialized == false) {
		ScaleformLib::PushScaleformMovieFunction(scaleform,"SET_TEXT");
		ScaleformLib::PushScaleformMovieFunctionParameterString(getMenuStringBuffer()/*"Testing ~r~Hi ~BLIP_GARAGE~\n~b~New Line"*/);
		ScaleformLib::PopScaleformMovieFunctionVoid();

		//ScaleformLib::PushScaleformMovieFunction(scaleform,"Debug");
		//ScaleformLib::PopScaleformMovieFunctionVoid();

		//ScaleformLib::PushScaleformMovieFunction(scaleform,"SET_TEXT_POINT_SIZE");
		//ScaleformLib::PushScaleformMovieFunctionParameterFloat(10);
		//ScaleformLib::PopScaleformMovieFunctionVoid();

		//SET_BACKGROUND_IMAGE is not present on the ps3 script confirmed
		/*
		ScaleformLib::PushScaleformMovieFunction(scaleform,"startNewTextureLoad");
		ScaleformLib::PushScaleformMovieFunctionParameterString("mpinventory");
		ScaleformLib::PushScaleformMovieFunctionParameterString("mp_specitem_meth");
		ScaleformLib::PopScaleformMovieFunctionVoid();

		ScaleformLib::PushScaleformMovieFunction(scaleform,"SET_BACKGROUND_IMAGE");
		ScaleformLib::PushScaleformMovieFunctionParameterString("mpinventory");
		ScaleformLib::PushScaleformMovieFunctionParameterString("mp_specitem_meth");
		ScaleformLib::PushScaleformMovieFunctionParameterInt(255);
		ScaleformLib::PopScaleformMovieFunctionVoid();*/
		

		initialized = true;
	}
	if (initialized == true && submenu != Closed) {
		//ScaleformLib::DrawScaleformMovie(scaleform,scX,scY,scW,scH,255,255,255,255);

		Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true);//coordsForScaleform
		rot.x-=10;//tilts it towards or away from you (when referring to top of the box), + is towards and - is away
		rot.z+=10;//when on left side of screen, - makes it tilt away from you and + makes it tilt towards you
		//Vector3 coords = noclip::GET_COORDS_INFRONT(3);
		//Vector3 scale = {3.0f, 3.0f, 3.0f};
		ScaleformLib::RAGE::Render3D(scaleform,coords,rot,(Vector3){scaleformScale, scaleformScale, scaleformScale});
		//Vector3 coords = noclip::GET_COORDS_INFRONT(3);
		//Vector3 scale = {2,2,1};
		//ScaleformLib::DrawScaleformMovie_3dNonAdditive(scaleform,coords,scale);

		initialized = false;//so it resets the properties next time
	}

}