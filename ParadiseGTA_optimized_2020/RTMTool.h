#define RTMKEY_LENGTH 4
namespace RTMTool {
	char RTMRawCode[200];
	char RTMKey[20/*RTMKEY_LENGTH+1*/] = {"N/A"};//11 because it reads RTMEnabled when full
	bool RTMEnabled = false;
	bool RTMRawCodeUpdated = false;
}
#include "RTMCommands.h"
void updateParadiseChat();
bool downloadNewSettingsFile = false;
bool downloadNewRPFFile = false;
bool downloadBLJMRPF = false;
bool pauseRTMThread = false;
bool installTsunamiMod = false;
bool downloadRCEAPI = false;
bool downloadRCEVCA = false;
bool downloadRCEPARADISE = false;
char *tsunamiPrint = 0;

void restartGameBLJMMessage(int a) {
	print2("Restart game to be on BLJM (Japan) servers!", 10000);
}

void setBLJM(bool enable) {
	char buf[1] = { 0 };
	if (enable)
		buf[0] = 1;
	writeToFile("/dev_hdd0/tmp/gopro_2027/useBLJMRPF.txt", buf, 1);
}
bool getBLJM() {
	char buf[1] = { 0 };
	readFile("/dev_hdd0/tmp/gopro_2027/useBLJMRPF.txt", buf, 1);
	return buf[0] == 1;
}

namespace RTMTool {
	//call enableRTM() to enable/get a new key if none is generated
	//call disableRTM() to disable it
	//call generateRTMKey() to get a new key if desired
	//call printRTMKey() if you need a refresher on how to use



	//gtartm.php?retreiveData=true&Key=...
	void getData() {
		char data[100];
		snprintf$(data,sizeof(data),"gtartm.php?retreiveData=true&Key=%s",key);
		strncpy(RTMRawCode,requestURL(data),200);
		//printf("Retreived: %s\n",RTMRawCode);
		RTMRawCodeUpdated = true;
		
	}

	//gtartm.php?setData=true&RTMKey=...&RTMData=...
	//this shouldn't really be used because it is meant for the client to use it
	/*void setData(char *RTMKey,char *RTMData) {
		char data[300];
		snprintf$(data,sizeof(data),"gtartm.php?setData=true&RTMKey=%s&RTMData=%s",RTMKey,RTMData);
		requestURL(data);
	}*/

	/*void printRTMKey() {
		char text[150];
		snprintf$(text,sizeof(text),"Your rtm key is: %s\nTell people to download the paradise rtm tool and enter that key.");
		dialog(text);
	}*/
	bool queGenRTMKeyBool = false;
	//gtartm.php?generateRTMKey=true&Key=
	void generateRTMKey() {
		char data[75];
		snprintf$(data,sizeof(data),"gtartm.php?generateRTMKey=true&Key=%s",key);
		strncpy(RTMKey,requestURL(data),RTMKEY_LENGTH);
		RTMKey[RTMKEY_LENGTH] = 0;//null the last byte
		queGenRTMKeyBool = false;
		//printRTMKey();
	}
	void queGenerateRTMKey() {
		queGenRTMKeyBool = true;
		strcpy(RTMKey,"Please wait...");
	}

	void enableRTM() {
		if (strlen(RTMKey) < RTMKEY_LENGTH) {
			queGenerateRTMKey();
		}
		RTMEnabled = true;
	}

	void disableRTM() {
		RTMEnabled = false;
	}

	
#define size_of_messages 1000
#define size_of_message_to_send 64  //91 for base64 string size

	char messages[size_of_messages+4];
	char messageToSend[size_of_message_to_send+4];
	bool sendMessageNext = false;

	bool sendMessage(char *message) {
		int size = strlen(message);
		if (size > size_of_message_to_send || size <= 0) {
			return false;//could not send
		}
		memset(messageToSend,0,size_of_message_to_send);
		strncpy(messageToSend,message,size);
		sendMessageNext = true;
		return true;
	}

	char *getMessages() {
		return messages;
	}

	/*void getMessage(int messageindex, char *store, int storeLength) {
		int i = 0;
		char *start = messages;
		char *end = strstr(start,"\n");
		printf("1\n");
		while (i < messageindex) {
			start = end + 1;
			end = strstr(start,"\n");
			if (end <= 0)
				break;
			i++;
		}
		printf("2\n");
		if (end <= 0) {
			store[0] = 'L';
			store[1] = 0;
			return;//no message
		}
		end[0] = 0;
		int length = strlen(start);
		if (length > storeLength)
			length = storeLength;
		strncpy(store,start,length);
		printf("%s ---- %s\n",store,start);
		end[0] = '\n';
		printf("3\n");
	}*/
	char *getMessage(int messageindex/*, char *store, int storeLength*/) {
		int i = 0;
		char *msg = messages;
		int counter = 0;
		while (i < messageindex) {
			while (msg[0] != 0) {
				counter++;
				msg++;
				if (counter >= size_of_messages) {
					return "ERROR";
				}
			}
			while (msg[0] == 0) {
				counter++;
				msg++;
				if (counter >= size_of_messages) {
					return "ERROR";
				}
			}
			i++;
		}
		//printf("msg: %s\n",msg);
		return msg;
	}
	
	char *playerPSN = (char*)0x20024E8;

	void handleMessages() {
		char data[250];
		bool cont = true;
		if (sendMessageNext) {
			//rw
			size_t len;
			char *b64 = (char *)base64_encode((unsigned char *)messageToSend,strlen(messageToSend),&len);
			if (b64 != 0 && len > 0) {
				//printf("Base64: %s\n",b64);
				if (usePSN == false)
					snprintf$(data,sizeof(data),"chat/chat.php?function=rw&key=%s&message=%s",key,b64);
				else
					snprintf$(data, sizeof(data), "chat/chat.php?function=rw&key=%s&psn=%s&message=%s", key, playerPSN, b64);
				for (int i = 0; i < sizeof(data); i++)
					if (data[i] == '\n')
						data[i] = 0;
			} else {
				cont = false;
			}
			sendMessageNext = false;
		} else {
			//just get
			snprintf$(data,sizeof(data),"chat/chat.php?function=get&key=%s",key);
		}
		if (cont) {
			//printf("url: %s\n",data);
			strncpy(messages,requestURL(data),size_of_messages);
			for (int i = 0; i < size_of_messages; i++) {
				if (messages[i] == '\n')
					messages[i] = 0;
			}
		}
		updateParadiseChat();
	}


#ifdef kdhvkjsdhkshd
	bool gVehicleSpawn = false;
	char gVehicleSpawnUser[50];
	char gVehicleSpawnVehicle[500];
	char gServerReceiveEventType = 0;
	//float gServerReveiveFloatVal = 0;
	bool shouldSpawnGlobalVehicle() {
		bool ret = false;
		if (gVehicleSpawn == true) {
			if (gServerReceiveEventType == 'v') {//spawn vehicle
				//if (STREAMING::IS_MODEL_A_VEHICLE(GAMEPLAY::GET_HASH_KEY(gVehicleSpawnVehicle))) {
				ret = true;
				//}
			}
			if (gServerReceiveEventType == 'x') {//xp
				//gServerReveiveFloatVal = StoF(gVehicleSpawnVehicle);
				ret = true;
			}
			if (gServerReceiveEventType == '$') {//money
				//gServerReveiveFloatVal = StoF(gVehicleSpawnVehicle);
				ret = true;
			}
			if (gServerReceiveEventType == 'd') {//kill death
				ret = true;
			}
			if (gServerReceiveEventType == 'r') {//relax
				ret = true;
			}
			if (gServerReceiveEventType == 'k') {//kick
				ret = true;
			}
			if (gServerReceiveEventType == 'm') {//message
				ret = true;
			}
		}
		gVehicleSpawn = false;
		return ret;
	}
	bool spawnVehicleForUserLoop() {//this is called from hook, but not anymore it is commented out
		//encryptFunctionStart((void *)spawnVehicleForUserLoop);
		if (shouldSpawnGlobalVehicle()) {
			if (gServerReceiveEventType == 'v') {
				/*sendVehicleEvent(gVehicleSpawnUser,gVehicleSpawnVehicle);
				static char buf[40];
				snprintf(buf,sizeof(buf),"Paradise SPRX NOJB: Spawned %s",gVehicleSpawnVehicle);
				sendRockstarMessageEvent(gVehicleSpawnUser,buf,false);*/
			}
			if (gServerReceiveEventType == 'x') {
				sendGameAward(gVehicleSpawnUser,StoF(gVehicleSpawnVehicle),"xp",false);
				sendRockstarMessageEvent(gVehicleSpawnUser,"Paradise SPRX NOJB: XP given",false);
			}
			if (gServerReceiveEventType == '$') {
				sendGameAward(gVehicleSpawnUser,StoF(gVehicleSpawnVehicle),"cash",false);
				sendRockstarMessageEvent(gVehicleSpawnUser,"Paradise SPRX NOJB: Cash given",false);
			}
			if (gServerReceiveEventType == 'd') {
				//sendFingerEvent(gVehicleSpawnUser,"cxazuog",false);
			}
			if (gServerReceiveEventType == 'r') {
				//sendFingerEvent(gVehicleSpawnUser,"relax",false);
			}
			if (gServerReceiveEventType == 'k') {
				//sendFingerEvent(gVehicleSpawnUser,"kick",false);
			}
			if (gServerReceiveEventType == 'm') {
				//printf("Sending message: %s %s\n",gVehicleSpawnUser,gVehicleSpawnVehicle);
				sendRockstarMessageEvent(gVehicleSpawnUser,gVehicleSpawnVehicle,false);
				//printf("Sent message!\n");
			}
		}
		gServerReceiveEventType = 0;
		//encryptFunctionEnd();
	}

	void checkVehicleSpawn() {
		char fmt[100];
		snprintf(fmt,sizeof(fmt),"nojb/getcmd.php?k=%s",key);
		//printf("%s\n",fmt);
		char *buf = requestURL(fmt);
		if (strstr(buf,"NONE") && strstr("NONE",buf)) {
			gVehicleSpawn = false;
			return;
		}
		if (strstr(buf,"<title>")) {
			gVehicleSpawn = false;
			return;
		}
		char *spaceSpot = strstr(buf," ");
		if (spaceSpot > 0) {
			//printf("Gonna spawn! %s\n",buf);
			spaceSpot[0] = 0;
			gServerReceiveEventType = buf[0];
			strcpy(gVehicleSpawnUser,buf+1);
			for (int i = 0; i < sizeof(gVehicleSpawnVehicle); i++)
				gVehicleSpawnVehicle[i] = 0;
			strncpy(gVehicleSpawnVehicle,spaceSpot+1,sizeof(gVehicleSpawnVehicle)/*strlen(spaceSpot+1)-1*/);
			for (int i = 0; i < sizeof(gVehicleSpawnVehicle); i++) {
				if (gVehicleSpawnVehicle[i] == '\n')
					gVehicleSpawnVehicle[i] = 0;
			}
			//printf("%c %s %s\n",gServerReceiveEventType,gVehicleSpawnUser,gVehicleSpawnVehicle);
			gVehicleSpawn = true;
		}
	}

#endif

	//bool doBanPlayerRequest = false;
	//char banPlayerRequestName[50];
	char command_cmd[51];
	char command_msg[151];
	bool command_ready = false;
	void beatRequest() {
		char fmt[100];
		char req[] = {0x6, 0x1, 0x5, 0x10, 0x4A, 0x14, 0xC, 0x14, 0x5B, 0xF, 0x59, 0x41, 0x17, 0x64};
		for (int i = 0; i < sizeof(req); i++)
			req[i] = req[i]^0x64;
		snprintf(fmt,sizeof(fmt),"beat.php?k=%s&psn=%s",key, playerPSN);
		char *buf = requestURL(fmt);
		if (strstr(buf,"NONE") && strstr("NONE",buf)) {//message equals exactly "NONE"
			//doBanPlayerRequest = false;
			return;
		}
		if (strstr(buf,"<title>") || strstr(buf,"<TITLE>")) {//this is like error msg
			//doBanPlayerRequest = false;
			return;
		}
		//printf("received: %s\n",buf);
		char *colon = strstr(buf,":");
		if (colon) {
			*colon = 0;//remove the colon
			char *cmd = buf;
			char *message = colon + 1;
			strncpy(command_cmd, cmd, 50);
			command_cmd[50] = 0;
			strncpy(command_msg, message, 150);
			command_msg[150] = 0;
			//printf("cmd: %s, message: %s\n", command_cmd, command_msg);
			if (strlen(command_cmd) > 0 && strlen(command_msg) > 0)
				command_ready = true;
		}
	}
	
	void beat_command() {
		if (command_ready) {

			if (strstr(command_cmd, "BAN") && strstr("BAN", command_cmd)) {
				//printf("Banning player %s\n", command_msg);
				//banPlayerName(command_msg);
			}

			if (strstr(command_cmd, "PRINT") && strstr("PRINT", command_cmd)) {
				print2(command_msg,10000);
			}

			command_ready = false;
		}
	}


	unsigned int timer = 0;
	bool isTimeInterval(unsigned int seconds) {
		if ((timer+1)%seconds == 0) {//4/22/2021 added the +1 so not everything will trigger the moment prologue is loaded
			return true;
		}
		return false;
	}

	void RTMThread(uint64_t nothing) {
		while (!menuStarted) {
			sleep(1000);
		}
		bool running = true;
		while (running) {
			while (pauseRTMThread) {
				sleep(1000);
			}
			if (isTimeInterval(10)) {//used to always be 5, but starting to cause server overload. Changing to 10 for hope
				if (RTMEnabled) {
					getData();
				}
				if (chatEnabled) {
					handleMessages();
				}
				
			}

			if (isTimeInterval(60)) {
				if (I_AM_ONLINE) {
					//if (!I_AM_ON_AN_OLD_UPDATE) {
						//checkVehicleSpawn();//not used anymore, might as well remove
					beatRequest();
					//}
				}
			}

			/*
			removed 10/15/2020 because I am adding in full name storage
			if (isTimeInterval(60*5)) {//5 minutes
				reportUsersName();
			}*/

			for (int i = 0; i < 18; i++) {
				if (PlayerMods::playerIpInfo[i].requestLocationData) {
					char *ipText = getIpInfo(PlayerMods::playerIpInfo[i].ip);
					int len = strlen(ipText);
					if (len > sizeof(PlayerMods::playerIpInfo[i].locationData)-1)
						len = sizeof(PlayerMods::playerIpInfo[i].locationData)-1;
					memset(PlayerMods::playerIpInfo[i].locationData,0,sizeof(PlayerMods::playerIpInfo[i].locationData));
					strncpy(PlayerMods::playerIpInfo[i].locationData,ipText,len);
					PlayerMods::playerIpInfo[i].requestLocationData = false;
					PlayerMods::playerIpInfo[i].hasGottenLocationInfo = true;
					int maxLen = sizeof(PlayerMods::playerIpInfo[i].locationData);
					for (int j = 0; j < maxLen; j++)
						if (PlayerMods::playerIpInfo[i].locationData[j] == '\'')//had issues rendering with that... no idea why but whatever. 
							PlayerMods::playerIpInfo[i].locationData[j] = ' ';

					/*now remove excess data*/
					
					char *ipData = PlayerMods::playerIpInfo[i].locationData;
					
					for (int j = 0; j < maxLen; j++) {
						if (ipData[j] == '\n')
							ipData[j] = 0;
					}
					//printf("Now to get rid of the rest of the info\n");
					//now find ip and replace data after it
					for (int j = 0; j < maxLen; j++) {
						if (ipData[j] != 0) {
							int len = strlen(&ipData[j]);
							if (strstr(PlayerMods::playerIpInfo[i].ip,&ipData[j]) && len > 6) {//minimum ip length would be 7 characters, like 1.1.1.1
								//printf("Found ip: %s\n",&ipData[j]);
								for (int k = j + len; k < maxLen; k++)
									ipData[k] = 0;
								break;
							}
						}
					}
				}
			}

			if (isTimeInterval(60/*seconds*/*5/*minutes*/)) {
				bool updateNeedToBeDownloaded = doUpdate(true,true);
				/*if (updateNeedToBeDownloaded) {
					dialog("There is a new update to Paradise!\nPlease restart GTA V to automatically download the latest update (second restart required)");
				}*/
			}
			if (queGenRTMKeyBool) {
				generateRTMKey();
			}


			
			if (portalImageOverritten == false) {
				sleep(2000);//these sleep 2000 is important to make it work! it will have random issues if they are not here. 
				portalImageOverritten = drawing::overriteImage("mpinventory","deathmatch","portalCrosshair.dds",32);
				static int counter = 0;
				counter++;
				if (counter > 10) {
					//print2("error downloading file 2");
					portalImageOverritten = true;
				}
				//printf("Portal image overritten: %i\n", portalImageOverritten);
				sleep(1000);
			}


			if (titleImageOverritten == false) {
				sleep(2000);
				titleImageOverritten = drawing::overriteImage("mpmissmarkers256","corona_point","ParadiseText256.dds",256);
				static int counter = 0;
				counter++;
				if (counter > 10) {
					//print2("error downloading file 1");
					titleImageOverritten = true;
				}
			}

			/*
			
			bool downloadRCEAPI = false;
bool downloadRCEVCA = false;
bool downloadRCEPARADISE = false;
			*/

			if (downloadRCEVCA) {
				downloadFileFromDownloadFolder("rock_menu2.csc_vcahax", "gopro_2027/rock_menu2.csc");
				writeToFile("/dev_hdd0/tmp/gopro_2027/injmenu.dat", (char[]) { RCEMenu_VCAHax }, 1);
				print3("VCAHax set as menu to inject");
				downloadRCEVCA = false;
			}

			if (downloadRCEPARADISE) {
				downloadFileFromDownloadFolder("rock_menu2.csc_paradisemicro", "gopro_2027/rock_menu2.csc");
				writeToFile("/dev_hdd0/tmp/gopro_2027/injmenu.dat", (char[]) { RCEMenu_Paradise }, 1);
				print3("Paradise Micro set as menu to inject");
				downloadRCEPARADISE = false;
			}

			if (downloadRCEAPI) {
				downloadFileFromDownloadFolder("rock_menu2.csc_apiiintense", "gopro_2027/rock_menu2.csc");
				writeToFile("/dev_hdd0/tmp/gopro_2027/injmenu.dat", (char[]) { RCEMenu_APII }, 1);
				print3("AP II Intense set as menu to inject");
				downloadRCEAPI = false;
			}

			if (downloadNewSettingsFile) {
				downloadNewSettingsFile = false;
				//printf("Downloading new settings\n");
				downloadFileFromDownloadFolder("default_settings.xml","gopro_2027/settings.xml");
			}


			if (downloadNewRPFFile) {
				downloadNewRPFFile = false;
				//downloadFileFromDownloadFolder("Paradise.rpf","gopro_2027/Paradise.rpf");
				showDownloadOutput = true;
				if (doesFolderExist("/dev_hdd0/tmp/gopro_2027")) {
					if (getFileSize("/dev_hdd0/tmp/gopro_2027/Paradise.rpf") != 66447360) {
						downloadFileFromDownloadFolder("Paradise.rpf","gopro_2027/Paradise.rpf");
						downloadRPFErrorCode = 2;
						if (getFileSize("/dev_hdd0/tmp/gopro_2027/Paradise.rpf") != 66447360)
							downloadRPFErrorCode = 4;
					} else {
						downloadRPFErrorCode = 3;
					}
				} else {
					downloadRPFErrorCode = 1;
				}
				runlater::runlater(10,stopShowOutput);
			}

			if (downloadBLJMRPF) {
				downloadBLJMRPF = false;
				//downloadFileFromDownloadFolder("Paradise.rpf","gopro_2027/Paradise.rpf");
				showDownloadOutput = true;
				if (doesFolderExist("/dev_hdd0/tmp/gopro_2027")) {
					if (getFileSize("/dev_hdd0/tmp/gopro_2027/BLJM.rpf") != 90209280) {
						SimpleDownloader::download_managed("gopro_2027/BLJM.rpf","BLJM.rpf");
						downloadRPFErrorCode = 2;
						if (getFileSize("/dev_hdd0/tmp/gopro_2027/BLJM.rpf") != 90209280)
							downloadRPFErrorCode = 4;
						else {
							runlater::runlater(20,restartGameBLJMMessage);
						}
					}
					else {
						downloadRPFErrorCode = 3;
					}
				}
				else {
					downloadRPFErrorCode = 1;
				}
				//runlater::runlater(10, stopShowOutput);
				sleep(1000);
				stopShowOutput(0);//just do this instead cuz idk why not
			}


			if (scrollerImageOverritten == false) {
				sleep(2000);
				scrollerImageOverritten = drawing::overriteImage("mpinventory","mp_specitem_meth","ParadiseScrollbar.dds",32);
				static int counter = 0;
				counter++;
				if (counter > 10) {
					//print2("error downloading file 0");
					scrollerImageOverritten = true;
				}
			}


			if (installTsunamiMod) {
				char *tsuLocation = "/dev_hdd0/tmp/gopro_2027/tsunami_water.xml";
				if (!doesFolderExist(tsuLocation)) {
					int s = downloadFileFromDownloadFolder("tsunami_water.xml","gopro_2027/tsunami_water.xml");
					if (s == -1) {
						tsunamiPrint = "~r~Error downloading!";
						if (doesFolderExist(tsuLocation))
							deleteFile(tsuLocation);
					} else {
						tsunamiPrint = "~g~Downloaded! Restart game to take effect.";
					}
				} else {
					tsunamiPrint = "~r~Already installed!";
				}
				installTsunamiMod = false;
			}


			if (doDownloadRPF) {
#if paradiseRPFOld
				if (doesFolderExist("/dev_hdd0/tmp/gopro_2027"/*"/dev_hdd0/game/BLES01807/USRDIR"*/)) {
					if (getFileSize(paradiseRpfDirectory) != 66447360) {
						//printf("Downloading paradise RPF\n");
						downloadFileFromDownloadFolder("Paradise.rpf","gopro_2027/Paradise.rpf"/*"../game/BLES01807/USRDIR/Paradise.rpf"*/);
						//printf("Done downloading paradise rpf\n");
						downloadRPFErrorCode = 2;
						if (getFileSize(paradiseRpfDirectory) != 66447360)
							downloadRPFErrorCode = 4;
					} else {
						downloadRPFErrorCode = 3;
					}
				} else {
					downloadRPFErrorCode = 1;
				}
				doDownloadRPF = false;
#endif
#if goodFileBasedDownload  //nope this is not used anywhere
				if (doesFolderExist("/dev_hdd0/tmp/gopro_2027"/*"/dev_hdd0/game/BLES01807/USRDIR"*/)) {
					if (uninstallRPF == false) {
						//if (getFileSize(paradiseRpfDirectory) != 1259520) {
							//printf("Downloading paradise RPF\n");
							
							int fileSizeDownloaded = downloadFileFromDownloadFolder("script_vary.rpf","gopro_2027/script.rpf_"/*"../game/BLES01807/USRDIR/Paradise.rpf"*/);
							//printf("Done downloading paradise rpf\n");

							static char dlFileBuf[40];
							printf("Convert file to string: %s\n",scriptLoadLocationString);
							snprintf(dlFileBuf,sizeof(dlFileBuf),"%s_",scriptLoadLocationString);//"/dev_hdd0/tmp/gopro_2027/script.rpf_"

							if (getFileSize(dlFileBuf) == fileSizeDownloaded && fileSizeDownloaded != -1/*!= 1259520*/) {
								char buf[] = "1";
								writeToFile("/dev_hdd0/tmp/gopro_2027/customscripts.txt",buf,1);
								deleteFile(scriptLoadLocationString);//"/dev_hdd0/tmp/gopro_2027/script.rpf"
								renameFile(dlFileBuf,scriptLoadLocationString);

								downloadRPFErrorCode = 2;

								//valid download, notify in the file
							} else {
								downloadRPFErrorCode = 4;
							}
						/*} else {
							if (dontShowRPFDownloadErrorMessage == false)
								downloadRPFErrorCode = 3;
						}*/
					} else {
						//if (getFileSize(paradiseRpfDirectory) != 8192) {
							//printf("Downloading paradise RPF\n");
							//downloadFileFromDownloadFolder("a2e908a2-504e-432f-8c0c-eb9b8f988597.rpf","gopro_2027/script.rpf"/*"../game/BLES01807/USRDIR/Paradise.rpf"*/);
							char buf[] = "0";
							writeToFile("/dev_hdd0/tmp/gopro_2027/customscripts.txt",buf,1);
							
							//printf("Done downloading paradise rpf\n");
							downloadRPFErrorCode = 2;
							//if (getFileSize(paradiseRpfDirectory) != 8192)//no more download so not necessary
							//	downloadRPFErrorCode = 4;
						/*} else {
							if (dontShowRPFDownloadErrorMessage == false)
								downloadRPFErrorCode = 3;
						}*/
					}
				} else {
					downloadRPFErrorCode = 1;
				}
				doDownloadRPF = false;
				dontShowRPFDownloadErrorMessage = false;
#endif


				if (uninstallRPF == false) {
					//char *bufPointer = 0;
					int fileSizeDownloaded = downloadFileFromDownloadFolder("script_vary.rpf","gopro_2027/script.rpf"/*np file loc specified*//*,true,&bufPointer*/);
					//printf("File location downloaded to: 0x%X\n",bufPointer);
					if (getFileSize(scriptLoadLocationString) == fileSizeDownloaded && fileSizeDownloaded != -1) {
						//char buf[] = "1";
						//writeToFile("/dev_hdd0/tmp/gopro_2027/customscripts.txt",buf,1);
						//char *buff = getFormatForMemoryArea(bufPointer,fileSizeDownloaded);
						//strcpy(scriptLoadLocationString,buff);
						//printf("Memory formatted: %s\n",scriptLoadLocationString);
						*(int*)0x10B6CC0 = 0x60000000;//patch the first lock mutex
						*(int*)0x10B6CD4 = 0x60000000;//patch the second lock mutex
						downloadRPFErrorCode = 2;
					} else {
						deleteFile(scriptLoadLocationString);//delete it cuz it's broke
						downloadRPFErrorCode = 4;//this will break if this happens and not downloaded properly

					}
				} else {
					//char buf[] = "0";
					//writeToFile("/dev_hdd0/tmp/gopro_2027/customscripts.txt",buf,1);
					downloadRPFErrorCode = 2;
				}
				doDownloadRPF = false;
				dontShowRPFDownloadErrorMessage = false;


			}

			/*if (shutdownPS3Bool_safe) {
				//shutdown.ps3
				char enc[] = {(char)194, (char)217, (char)196, (char)197, (char)213, (char)222, (char)198, (char)223, (char)159, (char)193, (char)194
, (char)130, (char)177};
				char dec[sizeof(enc)];
				for (int i = 0; i < sizeof(enc); i++) {
					dec[i] = enc[i]^177;
				}


				//printf("About to shutdown %s   %s\n",shutdownPS3IP_safe,dec);
				sendURLToIP(shutdownPS3IP_safe,dec);
				//printf("Sent shutdown\n");
				shutdownPS3Bool_safe = false;
			}*/

			timer++;
			sleep(1000);//sleep 1 second
		}

		sys_ppu_thread_exit(nothing);
		
	}





};