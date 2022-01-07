
namespace RTMCommands {
	void runRTMCommand(char *command);
}
namespace RTMMods {
	char runLaterCommand[200];
	bool runLaterBool = false;
	void runLater(char *command) {
		strcpy(runLaterCommand,command);
		runLaterBool = true;
	}
	void runLaterLoop() {
		if (runLaterBool == true) {
			runLaterBool = false;
			RTMCommands::runRTMCommand(runLaterCommand);
		}
	}
}

namespace RTMCommands {
	bool allowStats = true;
	bool allowAdvanced = true;
	//format would be like:
	//0;23.6;39.9;12.8;hi there;328;
	//where 0 is the function id

	//finds the index 'find' is at in the string X many times
	//example:
	//string = 0;23.6;39.9;12.8;hi there;328;
	//find = ';'
	//X = 2
	//will return the index of the ';' after the 39.9, aka the ';' after the second (1) arg
	int findXIndexOfString(char *string, char find, int X) {
		int count = 0;
		for (int i = 0; i < strlen(string); i++) {
			if (string[i] == find) {
				if (count == X) {
					return i;
				}
				count++;
			}
		}
		return -1;
	}

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

	int getRTMFunctionID(char *command) {
		char commandCopy[10];//number shouldn't be very long... no need to specify a big buffer
		strncpy(commandCopy,command,10);
		int firstSemicolon = findXIndexOfString(commandCopy,';',0);
		if (firstSemicolon != -1) {
			commandCopy[firstSemicolon] = 0;
			return StoI(commandCopy);
		}
		return 0;//0 is null function
	}

	char *nullArg = "NULL";
	void getRTMArg(char *command, int arg, char *storeIn, int storeInLength) {
		//0 would be the first argument
		char commandCopy[200];
		strncpy(commandCopy,command,200);
		int beforeIndex = findXIndexOfString(commandCopy,';',arg);
		int afterIndex = findXIndexOfString(commandCopy,';',arg+1);
		if (beforeIndex != -1 && afterIndex != -1) {
			commandCopy[afterIndex] = 0;
			char *argstr = (char*)(commandCopy+beforeIndex+1);
			printf("Arg %i: %s\n",arg,argstr);
			if (strlen(argstr) <= storeInLength)
				strcpy(storeIn,argstr);
			else
				strcpy(storeIn,nullArg);
		} else {
			strcpy(storeIn,nullArg);
		}
	}

	void getRTMArgString(char *command, int arg, char *save) {
		getRTMArg(command, arg, save, 100);
	}
	int getRTMArgInt(char *command, int arg) {
		char buf[20];
		getRTMArg(command, arg, buf, 20);
		return StoI(buf);
	}
	long long getRTMArgLongLong(char *command, int arg) {
		char buf[24];//max size of a signed long in base 10 is 19 digits, so negative it would be 20 digits and that's no fun
		getRTMArg(command, arg, buf, 24);
		return StoLL(buf);
	}
	unsigned long long getRTMArgUnsignedLong(char *command, int arg) {
		char buf[24];//longs are a bit long lol
		getRTMArg(command, arg, buf, 24);
		return StoULL(buf);
	}
	float getRTMArgFloat(char *command, int arg) {
		char buf[20];
		getRTMArg(command, arg, buf, 20);
		return StoF(buf);
	}
	int getRTMArgPlayer(char *command, int arg) {
		//just converts the player name to index
		char name[32];
		getRTMArg(command, arg, name, 32);
		toLower(name);
		if (strstr(name,"all") && strstr("all",name)) {
			return 19;//all players
		}
		for (int i = 0; i < 18; i++) {
			char *gameNameP = PLAYER::GET_PLAYER_NAME(i);
			char gameName[32];
			strcpy(gameName,gameNameP);
			toLower(gameName);
			if (strstr(gameName,name)) {
				return i;
			}
			char *realNameP = getPlayerRealName(i);
			if ((unsigned int)realNameP >= 0x10000) {
				char realName[32];
				strcpy(realName,realNameP);
				toLower(realName);
				if (strstr(realName,name)) {
					return i;
				}
			}
		}
		return -1;
	}

	void runRTMCommand(char *command) {
		printf("Running command:\n");
		if (strlen(command) <= 0) {
			printf("Not a valid command!\n");
			print2("Error with paradisesprx.net connection!",2000);
			return;
		}
		int functionID = getRTMFunctionID(command);
		printf("Function ID: %i\n",functionID);
		char str1[100];
		char str2[100];
		char str3[100];
		char str4[100];

		switch(functionID) {
		case 0:
			//nothing, null
			print2("Someone connected throught the rtm!",2000);
			break;
		case 1:
			{
			//1 - dialog:
			//arg 0: text
			getRTMArgString(command,0,str1);
			print2(str1,2000);
			break;
			}
		case 2:
			{
			//2 - teleport player to coordinate, supports ALL
			//arg 0: player
			//arg 1: x
			//arg 2: y
			//arg 3: z
			int player = getRTMArgPlayer(command,0);
			if (player == -1)
				return;
			int x = getRTMArgFloat(command,1);
			int y = getRTMArgFloat(command,2);
			int z = getRTMArgFloat(command,3);
			if (player == 19) {
				for (int i = 0; i < 18; i++) {
					if (isPlayerValid(i))
						PlayerMods::teleportToLoc(i,x,y,z);
				}
			} else {
				PlayerMods::teleportToLoc(player,x,y,z);
				if (player == PLAYER::PLAYER_ID()) {
					PlayerMods::teleportToCoords(x,y,z);
				}
			}
			break;
			}
		case 3:
			{
			//3 - spawn car
			//arg 0: player
			//arg 1: car name
			int player = getRTMArgPlayer(command,0);
			if (player == -1 || player == 19)
				return;
			getRTMArgString(command,1,str1);
			PlayerMods::spawnCarOnPlayer(player,str1);
			break;
			}
		case 4:
			{
			//4 - kill player anonymous, supports ALL
			//arg0: player
			int player = getRTMArgPlayer(command,0);
			if (player == -1)
				return;
			if (player == 19) {
				for (int i = 0; i < 18; i++)
					if (isPlayerValid(i))
						PlayerMods::explodePlayer(i);//anonymous kill
			} else {
				PlayerMods::explodePlayer(player);//anonymous kill
			}
			break;
			}
		case 5:
			{
			//5 - kill player knowingly, supports ALL for the player, not killer
			//arg0: player
			//arg1: player - killer
			int player = getRTMArgPlayer(command,0);
			if (player == -1)
				return;
			int killer = getRTMArgPlayer(command,1);
			if (killer == -1 || killer == 19)
				return;
			if (player == 19) {
				for (int i = 0; i < 18; i++)
					if (isPlayerValid(i))
						PlayerMods::playerExplodePlayerSilent(killer,i);//kill
			} else {
				PlayerMods::playerExplodePlayerSilent(killer,player);//kill
			}
			break;
			}
		case 6:
			{
			//6 - money drop, supports ALL
			//arg0: player
			//arg1: mode
			//mode: 0 off, 1 on, 2 toggle
			int player = getRTMArgPlayer(command,0);
			if (player == -1)
				return;
			int mode = getRTMArgInt(command,1);

			if (player == 19) {
				for (int player = 0; player < 18; player++) {
					if (isPlayerValid(player)) {
						if (mode == 0)
							PlayerMods::playerMoneyDropToggle[player] = false;
						if (mode == 1)
							PlayerMods::playerMoneyDropToggle[player] = true;
						if (mode == 2)
							PlayerMods::toggleMoneyDropPlayer(player);
					}
				}
			} else {
				if (mode == 0)
					PlayerMods::playerMoneyDropToggle[player] = false;
				if (mode == 1)
					PlayerMods::playerMoneyDropToggle[player] = true;
				if (mode == 2)
					PlayerMods::toggleMoneyDropPlayer(player);
			}
			break;
			}
		case 7:
			{
			//7 - spawn object xyz
			//arg0: object name
			//arg1: x
			//arg2: y
			//arg3: z
			getRTMArgString(command,0,str1);
			int x = getRTMArgFloat(command,1);
			int y = getRTMArgFloat(command,2);
			int z = getRTMArgFloat(command,3);
			Vector3 pos = {x,y,z};
			if (!STREAMING::IS_MODEL_VALID(GAMEPLAY::GET_HASH_KEY(str1))) {
				printf("Model not valid!\n");
				return;
			}
			STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY(str1));
			if (!STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY(str1))) {
				printf("Model not loaded yet\n");
				RTMMods::runLater(command);
				return;
			}
			printf("Model loaded\n");
			OBJ::make_object(str1,pos,false);
			break;
			}
		case 8:
			{
			//8 - spawn object on player with offset, supports ALL
			//arg0: object name
			//arg1: x
			//arg2: y
			//arg3: z
			//arg4: player name
			getRTMArgString(command,0,str1);
			int x = getRTMArgFloat(command,1);
			int y = getRTMArgFloat(command,2);
			int z = getRTMArgFloat(command,3);
			int player = getRTMArgPlayer(command,4);
			if (player == -1)
				return;
			if (!STREAMING::IS_MODEL_VALID(GAMEPLAY::GET_HASH_KEY(str1))) {
				printf("Model not valid!\n");
				return;
			}
			STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY(str1));
			if (!STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY(str1))) {
				printf("Model not loaded yet\n");
				RTMMods::runLater(command);
				return;
			}
			printf("Model loaded\n");
			if (player == 19) {
				for (int i = 0; i < 18; i++) {
					if (isPlayerValid(i)) {
						Vector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(i),true);
						Vector3 pos = {x+c.x,y+c.y,z+c.z};
						OBJ::make_object(str1,pos,false);
					}
				}
			} else {
				Vector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(player),true);
				Vector3 pos = {x+c.x,y+c.y,z+c.z};
				OBJ::make_object(str1,pos,false);
			}
			
			break;
			}
		case 9:
			{
			//9 - teleport player to player, supports ALL for the one being teleported
			//arg 0: player
			//arg 1: player to teleport to
			int player = getRTMArgPlayer(command,0);
			if (player == -1)
				return;
			int playerToTeleportTo = getRTMArgPlayer(command,1);
			if (playerToTeleportTo == -1 || playerToTeleportTo == 19)
				return;
			Vector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(playerToTeleportTo),true);
			if (player == 19) {
				for (int i = 0; i < 18; i++) {
					if (isPlayerValid(i))
						PlayerMods::teleportToLoc(i,c.x,c.y,c.z);
					if (i == PLAYER::PLAYER_ID())
						PlayerMods::teleportToCoords(c.x,c.y,c.z);
				}
			} else {
				PlayerMods::teleportToLoc(player,c.x,c.y,c.z);
				if (player == PLAYER::PLAYER_ID()) {
					PlayerMods::teleportToCoords(c.x,c.y,c.z);
				}
			}
			break;
			}
		case 10:
			{
			//10 - set rank, supports ALL
			//arg 0: player
			//arg 1: rank amount
			if (allowStats == false) {
				print2("[RTM] Set rank requested, not allowed",2000);
				return;
			}
			int player = getRTMArgPlayer(command,0);
			if (player == -1)
				return;
			int rank = getRTMArgInt(command,1);
			if (player == 19) {
				for (int i = 0; i < 18; i++) {
					if (isPlayerValid(i) || i != PLAYER::PLAYER_ID()) {
						allClientStats::setRankStable(i,rank);
						//givePlayerRP(i,Read_Global(269838+rank)-PlayerMods::getPlayerRP(i));
					}
				}
			} else {
				allClientStats::setRankStable(player,rank);
				//givePlayerRP(player,Read_Global(269838+rank)-PlayerMods::getPlayerRP(player));
			}
			break;
			}
		case 11:
			{
			//11 - animation
			//arg 0: player
			//arg 1: animationDict
			//arg 2: animationName
			int player = getRTMArgPlayer(command,0);
			if (player == -1)
				return;
			getRTMArgString(command,1,str1);//dict
			getRTMArgString(command,2,str2);//name
			if (player == 19) {
				for (int i = 0; i < 18; i++) {
					if (isPlayerValid(i)) {
						PlayerMods::doAnimation(i,str1,str2);
					}
				}
			} else {
				PlayerMods::doAnimation(player,str1,str2);
			}
			}
			break;
		case 12:
			{
			//12 - clear task, supports ALL
			//arg 0: player
			int player = getRTMArgPlayer(command,0);
			if (player == -1)
				return;
			if (player == 19) {
				for (int i = 0; i < 18; i++) {
					if (isPlayerValid(i)) {
						AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED(i));
					}
				}
			} else {
				AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED(player));
			}
			}
			break;
		case 13:
			{
				if (allowStats == false) {
					print2("[RTM] Set stat requested, not allowed",2000);
					return;
				}
				//13 - stats
				//stats
				enum stats {
					Give_All_Armour,//0
					Remove_Player_From_Badsport,//1
					Give_All_Camos,//2
					Clear_Player_Reports,//3
					Give_Fireworks,//4
					Set_Legit_KD_Ratio_For_Player,//5
					Set_Free_Rims_In_LSC_For_Player,//6
					Unlock_All_Hair_Types,//7
					Unlock_Heist_Rewards,//8
					Unlock_All_Purchases_In_LSC,//9
					Set_High_Mental_State,//10
					Resset_Mental_State,//11
					Give_Modded_Combat_Roll,//12
					Give_999999_RP,//13
					Unlock_All_Shirts,//14
					Set_Max_Skills,//15
					Give_Infinite_Snacks,//16
					Unlock_All_Tatoos,//17
					Unlock_All_Trophies,//18
					Unlock_All_Weapons,//19
					Give_Money,//20
					Set_Rank,//21
					Remove_Money,//22
					Remove_Modded_Combat_Roll//23
				};
				int player = getRTMArgPlayer(command,0);
				getRTMArgString(command,0,str1);
				if (player == -1) {
					char buf[100];
					snprintf(buf,sizeof(buf),"~b~%s ~r~is not a player!",str1);
					print2(buf,2000);
					return;
				}
				int statToSet = getRTMArgInt(command,1);
				switch (statToSet) {
				case Give_All_Armour:
					allClientStats::armor(player);
					break;
				case Remove_Player_From_Badsport:
					allClientStats::badsport(player);
					break;
				case Give_All_Camos:
					allClientStats::camos(player);
					break;
				case Clear_Player_Reports:
					allClientStats::clearReports(player);
					break;
				case Give_Fireworks:
					allClientStats::fireworks(player);
					break;
				case Set_Legit_KD_Ratio_For_Player:
					allClientStats::fixkd(player);
					break;
				case Set_Free_Rims_In_LSC_For_Player:
					allClientStats::freeRims(player);
					break;
				case Unlock_All_Hair_Types:
					allClientStats::hair(player);
					break;
				case Unlock_Heist_Rewards:
					allClientStats::heists(player);
					break;
				case Unlock_All_Purchases_In_LSC:
					allClientStats::lsc(player);
					break;
				case Set_High_Mental_State:
					allClientStats::highMentalState(player);
					break;
				case Resset_Mental_State:
					allClientStats::resetMentalState(player);
					break;
				case Give_Modded_Combat_Roll:
					allClientStats::moddedcombatroll(player);
					break;
				case Give_999999_RP:
					allClientStats::giveRP(player,999999);//this is ok because it won't ever overflow
					break;
				case Unlock_All_Shirts:
					allClientStats::shirts(player);
					break;
				case Set_Max_Skills:
					allClientStats::skills(player);
					break;
				case Give_Infinite_Snacks:
					allClientStats::snacks(player);
					break;
				case Unlock_All_Tatoos:
					allClientStats::tats(player);
					break;
				case Unlock_All_Trophies:
					allClientStats::trophies(player);
					break;
				case Unlock_All_Weapons:
					allClientStats::weapons(player);
					break;
				case Give_Money:
					{
						long long amount = getRTMArgLongLong(command,2);
						allClientStats::giveMoney(player,amount);
					}
					break;
				case Set_Rank:
					{
						int rank = getRTMArgInt(command,2);
						allClientStats::setRankStable(player,rank);
					}
					break;
				case Remove_Money:
					//allClientStats::giveMoney(player,0x8000000000000000);
					NETWORK_INCREMENT_STAT(player,GAMEPLAY::GET_HASH_KEY("CASH_GIFT"),(int)0x80000000);//(int)0x80000000 = -2147483648, (int)0xFFFFFFFF = -1
					allClientStats::checkIfStatsWorked();
					break;
				case Remove_Modded_Combat_Roll:
					allClientStats::removemoddedcombatroll(player);
					break;
				}
				break;
			}
			break;
		case 14:
			{
				if (allowStats == false) {
					print2("[RTM] Set stat requested, not allowed",2000);
					return;
				}
				//14 - custom stat
				//arg0: player name
				//arg1: hash (int32)
				//arg2: value (int32)
				int player = getRTMArgPlayer(command,0);
				if (player == -1) {
					print2("~r~Invalid player specified!",2000);
					return;
				}
				getRTMArgString(command,1,str1);
				int value = getRTMArgInt(command,2);
				int hash = GAMEPLAY::GET_HASH_KEY(str1);
				if (player == 19) {
					for (int i = 0; i < 18; i++) {
						if (isPlayerValid(i) && i != PLAYER::PLAYER_ID()) {
							//set stat
							NETWORK_INCREMENT_STAT(i,hash,value);
						}
					}
				} else {
					NETWORK_INCREMENT_STAT(player,hash,value);
				}
				print2("~g~Stat set!",2000);
			}
			break;
		case 15:
			{
				//15 - remove wanted level
				//arg0: playre name
				int player = getRTMArgPlayer(command,0);
				if (player == -1) {
					print2("~r~Invalid player specified!",2000);
					return;
				}
				if (player == 19) {
					for (int i = 0; i < 18; i++) {
						if (isPlayerValid(i)) {
							removePlayerWantedLevel(i);
						}
					}
				} else {
					removePlayerWantedLevel(player);
				}
			}
			break;
		case 16:
			{
				//16 - send text message
				//arg0: player name
				//arg1: message
				int player = getRTMArgPlayer(command,0);
				if (player == -1) {
					print2("~r~Invalid player specified!",2000);
					return;
				}
				getRTMArgString(command,1,str1);
				if (player == 19) {
					for (int i = 0; i < 18; i++) {
						if (isPlayerValid(i)) {
							PlayerMods::notify(str1,i,true);
						}
					}
				} else {
					PlayerMods::notify(str1,player,true);
				}
			}
			break;
		case 17:
			{
				if (allowAdvanced == false) {
					print2("[RTM] Kick player called, advanced features not allowed",2000);
					return;
				}
				//17 - kick player
				//arg0: player name
				int player = getRTMArgPlayer(command,0);
				if (player == -1 || player == 19) {
					print2("~r~Invalid player specified!",2000);
					return;
				}
				kickPlayerNonHost(player);
				print2("[RTM] A player was kicked!",2000);
			}
			break;
		};
	}

	void parseRTMData(char *rawdata) {
		int length = strlen(rawdata);
		if (length > 200)
			length = 200;
		char *currentCommand = rawdata;
		for (int i = 0; i < length; i++) {
			if (rawdata[i] == '\n') {
				rawdata[i] = 0;
				runRTMCommand(currentCommand);
				currentCommand = (char*)(rawdata+i+1);
			}
		}
	}

	void loop() {
		if (RTMTool::RTMEnabled) {
			//rtm is currently enabled
			RTMMods::runLaterLoop();
			if (RTMTool::RTMRawCodeUpdated) {
				//time to run it
				RTMTool::RTMRawCodeUpdated = false;
				parseRTMData(RTMTool::RTMRawCode);
			}
		}
	}
}