//#include <stdio.h>
//#include <stdlib.h>
#include <cstring>
#include <cell/cell_fs.h>
//#define _malloc(x) malloc(x)
//#define _free(x) free(x)
/*int StoI(char *str) {
    return atoi(str);
}
float StoF(char *str) {
    return atof(str);
}*/
#define lineBufSize 200
char *cellFsfgets(int FD, char *buf, unsigned int bufSize) {

	char store[1];
	int count = 0;
	uint64_t read = 0;
	cellFsRead(FD,store,1,&read);
    while (read > 0) {
		cellFsRead(FD,store,1,&read);
		if (store[0] == '\n' || store[0] == 0 || count >= bufSize-1)
			break;
		buf[count] = store[0];
		count++;
	}
	buf[count] = 0;//null terminating character
	return buf;
}
struct Line {
    unsigned int offSet;
};

#define CELL_FILE_STREAMER
#ifdef CELL_FILE_STREAMER
class FileStreamer {
    private:
        char *fileName;
        unsigned int fileSize;
        int FD;
        Line *lines;
        unsigned int lineCount;
    public:
		void read_bytes(int FD, char *store, int size, uint64_t *readSize) {
			cellFsRead(FD,store,size,readSize);
			currentOffsetInFile += *readSize;//update currentOffsetInFile with added movement
		}
        FileStreamer(char *fileLoc) {
			createFileStreamer(fileLoc);
        }
        ~FileStreamer() {
            printf("Closing file %s and deallocating\n",fileName);
			clearFileStreamer();
        }
		void createFileStreamer(char *fileLoc) {//this is what needs to be called to re-allocate
			currentLineNumber = -1;
			readInCurrentLine = false;
			currentOffsetInFile = 0;
			if (fileLoc == 0) {
				FD = 0;
				return;//just don't do anything, expected for nothing to be used if it is 0
			}
			if (FD != 0) {
				clearFileStreamer();
			}
            open(fileLoc);
            findLines();
			resetPos();
		}
		bool isOpened() {
			return FD == 0 ? false : true;
		}
		void clearFileStreamer() {
			printf("Deallocating the data\n");
			if (lines != 0)
				_free(lines);
			lines = 0;
			close();
		}
        unsigned int getLineCount() {
            return lineCount;
        }
		unsigned int currentOffsetInFile;
        void setPos(unsigned int offset) {
			uint64_t pos;
            //cellFsLseek(FD,0,0,&pos);//not sure if this is necessary
			pos = 0;
			int dif = offset - currentOffsetInFile;
			currentOffsetInFile = offset;
            cellFsLseek(FD,dif,SEEK_CUR,&pos);//SEEK_SET originally, to go from offset of start of file
        }
        void resetPos() {
            uint64_t pos;
            cellFsLseek(FD,0,SEEK_SET,&pos);
        }
        void open(char *fileLoc) {
            fileName = fileLoc;
            int ret = cellFsOpen(fileLoc, 0, &FD, NULL, 0);
			uint64_t pos;
            cellFsLseek(FD,0,SEEK_END,&pos);
            CellFsStat sb;
			ret = cellFsFstat(FD,&sb);
			fileSize = sb.st_size;
            resetPos();
        }
        void close() {
			printf("Debug: cellFsClose() on File Streamer\n");
			if (FD != 0)
				cellFsClose(FD);
            FD = 0;
        }
        unsigned int countNewLines() {
			if (FD == 0)
				return 0;
            resetPos();
            char store[1];
            unsigned int count = 0;
			uint64_t read = 0;
			read_bytes(FD,store,1,&read);
            while (read > 0) {
				read_bytes(FD,store,1,&read);
                if (store[0] == '\n')
                    count++;
            }
            return count+1;//cuz the first line like won't be read cuz it starts after it... idk it's just safe
        }
        void findLines() {
			if (FD == 0)
				return;
            lineCount = countNewLines();
			//printf("Before line malloc\n");
            lines = (Line*)_malloc(sizeof(Line)*lineCount);//malloc is used in this function
			if (lines == 0) {
				printf("Allocation failed!\n");
				FD = 0;
				return;
			} else {
				//printf("Allocation successful! %i 0x%X\n",lineCount*sizeof(Line),lines);
			}
			//printf("after line malloc\n");
            resetPos();
            char store[1];
            unsigned int count = 0;
            unsigned int ptr = 0;
            lines[0].offSet = 0;
			uint64_t read = 0;
			read_bytes(FD,store,1,&read);
            while (read/*fread(store,1,1,FD)*/ > 0) {
				read_bytes(FD,store,1,&read);
                ptr++;
                if (store[0] == '\n')
                    lines[++count].offSet = ptr;
            }
        }

		char currentLineBuffer[lineBufSize];
		int currentLineNumber;
		bool readInCurrentLine;

		/**
		Returns if line is ready to be read
		**/
		bool queLine(int lineNum) {
			if (lineNum != currentLineNumber) {
				currentLineNumber = lineNum;
				readInCurrentLine = true;
				return false;
			}
			if (readInCurrentLine == true)
				return false;
			return true;
		}

		bool readInLineThread() {//this needs to be ran in a separate thread
			if (readInCurrentLine == true) {

				setPos(lines[currentLineNumber].offSet);
				int beforePosition = currentOffsetInFile;
				cellFsfgets(FD,currentLineBuffer,sizeof(currentLineBuffer));

				uint64_t pos;
				cellFsLseek(FD,0,SEEK_CUR,&pos);
				//printf("End Position: 0x%X\n",pos);

				int dif = pos-beforePosition;
				currentOffsetInFile = currentOffsetInFile + dif;//move currentOffsetInFile to new current location

				readInCurrentLine = false;

				return true;
			}
			return false;
		}

        char *readLine(int lineNum, char *buf, unsigned int bufSize) {
			if (lineNum != currentLineNumber) {
				printf("Mismatch in line read!\n");
				return buf;
			}
			if (readInCurrentLine == true) {
				printf("Should not be reading yet!\n");
				return buf;
			}
			if (FD == 0) {
				printf("Could not read line!\n");
				return buf;
			}
			/*
            setPos(lines[lineNum].offSet);
			//printf("setting position to %i %i\n",lineNum,lines[lineNum].offSet);
            return cellFsfgets(FD,buf,bufSize);//fgets(buf,bufSize,FD);//FIX THIS ASAP
			*/
			memcpy(buf,currentLineBuffer,bufSize);
        }
        /*void printAll() {
            for (int i = 0; i < lineCount; i++) {
                char buf[lineBufSize];
                printf("Line %i: %s",i,readLine(i,buf,lineBufSize));//the \n are also read (idk y though)
            }
            printf("\n");
        }*/
		/*
        unsigned int searchLine(char *lookFor, unsigned int start = 0, unsigned int end = 0xFFFFFFFF) {
			if (FD == 0)
				return -1;
            if (end == 0xFFFFFFFF)
                end = lineCount;
            char buf[400];
            for (int i = start; i < end; i++) {
                readLine(i,buf,sizeof(buf));
                if (strstr(buf,lookFor)) {//buf contains lookFor
                    return i;
                }
            }
            return -1;//not found
        }*/
};
#else
class FileStreamer {
    private:
        char *fileName;
        unsigned int fileSize;
        FILE *FD;
        Line *lines;
        unsigned int lineCount;
    public:
        FileStreamer(char *fileLoc) {
            open(fileLoc);
            findLines();
        }
        ~FileStreamer() {
            printf("Closing file %s and deallocating\n",fileName);
            free(lines);
            close();
        }
        unsigned int getLineCount() {
            return lineCount;
        }
        void setPos(unsigned int offset) {
            fseek(FD,0,0);//not sure if this is necessary
            fseek(FD,offset,SEEK_SET);
        }
        void resetPos() {
            setPos(0);
        }
        void open(char *fileLoc) {
            fileName = fileLoc;
            FD = fopen(fileName,"r");
            fseek(FD,0,SEEK_END);
            fileSize = ftell(FD);
            resetPos();
        }
        void close() {
            fclose(FD);
            FD = 0;
        }
        unsigned int countNewLines() {
            resetPos();
            char store[1];
            unsigned int count = 0;
            while (fread(store,1,1,FD) > 0) {
                if (store[0] == '\n')
                    count++;
            }
            return count+1;//cuz the first line like won't be read cuz it starts after it... idk it's just safe
        }
        void findLines() {
            lineCount = countNewLines();
            lines = (Line*)malloc(sizeof(Line)*lineCount);//malloc is used in this function
            resetPos();
            char store[1];
            unsigned int count = 0;
            unsigned int ptr = 0;
            lines[0].offSet = 0;
            while (fread(store,1,1,FD) > 0) {
                ptr++;
                if (store[0] == '\n')
                    lines[++count].offSet = ptr;
            }
        }
        char *readLine(int lineNum, char *buf, unsigned int bufSize) {
            setPos(lines[lineNum].offSet);
            return fgets(buf,bufSize,FD);
        }
        void printAll() {
            for (int i = 0; i < lineCount; i++) {
                char buf[lineBufSize];
                printf("Line %i: %s",i,readLine(i,buf,lineBufSize));//the \n are also read (idk y though)
            }
            printf("\n");
        }
        unsigned int searchLine(char *lookFor, unsigned int start = 0, unsigned int end = 0xFFFFFFFF) {
            if (end == 0xFFFFFFFF)
                end = lineCount;
            char buf[400];
            for (int i = start; i < end; i++) {
                readLine(i,buf,sizeof(buf));
                if (strstr(buf,lookFor)) {//buf contains lookFor
                    return i;
                }
            }
            return -1;//not found
        }
};
#endif


struct InstructionReturn {
    unsigned int nextLine;
};

//return true when ok, false when error
bool getSplit(char *string, char splitBy, int index, char *store, unsigned int storeSize) {
    char *cur = string;
    int found = 0;
    int stringLength = strlen(string);
    for (int i = 0; i < stringLength; i++) {
        if (string[i] == splitBy) {
            if (found == index) {
                int len = storeSize;
                string[i] = 0;
                strncpy(store,cur,storeSize);
                string[i] = splitBy;
                return true;
            }
            found++;
            cur = &(string[i+1]);
        }
    }
    strncpy(store,cur,storeSize);
    if (found < index) {
        return false;
    } else {
        return true;
    }
}

void substr(char *save, char *str, unsigned int startIndex, unsigned int endIndex) {
    int len = endIndex-startIndex;
    for (int i = 0; i < len; i++) {
        save[i] = str[i+startIndex];
    }
    save[len] = 0;
}

void substr(char *save, char *start, char *end) {
    int len = end-start;
    for (int i = 0; i < len; i++)
        save[i] = start[i];
    save[len] = 0;
}

bool streq(char *str1, char *str2) {
    char *a = strstr(str1,str2);
    char *b = strstr(str2,str1);
    if (a != 0 && b != 0)
        return true;
    return false;
}




class XMLReader {
private:
    FileStreamer fs;
    char *fileLoc;
public:
    XMLReader(char *fileLoc) :
    fs(fileLoc)
    {
		//printf("in xml reader\n");
        this->fileLoc = fileLoc;
    }
    void clearXMLReader() {
        fs.clearFileStreamer();//  this is automatically called when the destructore for XMLReader is called because it knows it's in here automatically
    }
	FileStreamer *getStreamer() {
		return &fs;
	}

	bool isOpened() {
		fs.isOpened();
	}
    
    int getIndentAtLine(int line) {
        char lineBuf[lineBufSize];
        fs.readLine(line,lineBuf,sizeof(lineBuf));
        //printf("line goteen: %s\n",lineBuf);
        char *foundAt = strchr(lineBuf,'<');
        if (foundAt != 0) {
            int ret = (int)(foundAt-(char*)lineBuf);
            return ret;
        } else {
            return -1;
        }
    }

	void getFullLine(int line, char *store, int size) {
        fs.readLine(line,store,size);
	}

    //gets the thing in between the <> but gets rid of extras if there are extra attributes. Returns false if the line did not contain such data
    bool getIDAtLine(int line, char *store) {
        char lineBuf[lineBufSize];
		//printf("Gonna read this line for id\n");
        fs.readLine(line,lineBuf,sizeof(lineBuf));
		//printf("Line i read for id: %s\n",lineBuf);
		char *spoot = strchr(lineBuf,'<');
		if (spoot == false)
			return false;
        char *start = spoot+1;
        char *end = strchr(lineBuf,'>');
        char insideBuffer[lineBufSize];
        if (start == 0 || end == 0) {
            return false;
        }
        substr(insideBuffer,start,end);
        char *spaceFound = strchr(start,' ');
        if (spaceFound != 0) {
            substr(insideBuffer,start,spaceFound);
        }
        char *cpy = insideBuffer;
        if (cpy[0] == '/')
            cpy = cpy + 1;
        strcpy(store,cpy);
        return true;
    }

    bool doesLineContainData(int line) {
        char lineBuf[lineBufSize];
        fs.readLine(line,lineBuf,sizeof(lineBuf));
        char *f1 = strchr(lineBuf,'<');
        char *f2 = strchr(f1+1,'<');
        if (f1 != 0 && f2 != 0)
            return true;
        return false;
    }

    bool getLineData(int line, char *store) {
        char lineBuf[lineBufSize];
		//printf("hewwo\n");
        fs.readLine(line,lineBuf,sizeof(lineBuf));
		//printf("Read the line my dude\n");
        char *f1 = strchr(lineBuf,'<');
		if (f1 == false)
			return false;
		//printf("read the first one! %s ... %s\n",lineBuf, f1);
        char *f2 = strchr(f1+1,'<');//end spot is what this should be
		//printf("figured out there is stufffs\n");
        if (f1 == 0 || f2 == 0)
            return false;
        //line has data so keep going
		//printf("verified line has data\n");
        char *start = strchr(f1+1,'>');
        if (start == 0)
            return false;
        start = start + 1;//get it to actual start
        substr(store,start,f2);
        return true;
    }

    bool isLineEnd(int line) {
        if (doesLineContainData(line) == false) {
            char lineBuf[lineBufSize];
            fs.readLine(line,lineBuf,sizeof(lineBuf));
            char *slash = strchr(lineBuf,'/');
            if (slash != 0)
                return true;
            else
                return false;
        } else {
            return false;//line has data, not simply and end one
        }
    }

    /*void printAll() {
        fs.printAll();
    }*/
    unsigned int getLineCount() {
        return fs.getLineCount();
    }
	bool lineReady(int line) {
		return fs.queLine(line);
	}
	bool fsQue() {
		return fs.readInLineThread();
	}
};

struct SpoonerSpawnInfo {
    unsigned int ModelHash;
    unsigned int Type;
    bool FrozenPos;
    float X,Y,Z;
    float Pitch,Roll,Yaw;
	bool IsVisible;
	bool IsInvincible;
	bool IsCollisionProof;
};

class Spooner;
Spooner *spoonerForCallbackSpawnFunc;
void spoonerCallbackSpawnFunc(int entity);

class Spooner {
private:
    XMLReader reader;
    int currentLine;
    SpoonerSpawnInfo currentSpawnData;
    char currentLineText[lineBufSize];
    bool looping;
    bool waitForSpawnToBeComplete;
	Vector3 ReferenceCoords;
	bool doingReferenceCoords;
	bool doingPositionRotation;
public:
    Spooner(char *fileLoc)
    : reader(fileLoc)
    {
		//printf("In spooner creation!\n");
        currentLine = 1;//the first line is xml declaration type
        looping = false;
		waitForSpawnToBeComplete = false;
        memset(currentLineText,0,sizeof(currentLineText));
        waitForSpawnToBeComplete = false;
    }

	XMLReader *getReader() {
		return &reader;
	}
	/*
	void clearSpooner() {
		reader.clearXMLReader();
		waitForSpawnToBeComplete = false;
		looping = false;
	}*/
	bool isRunning() {
		return looping;
	}

	/*void printAll() {
		reader.printAll();
	}*/

    void interpretLine() {
		//printf("interpreting line\n");
        char ID[lineBufSize];
        char data[lineBufSize];
		char printBuf[200];
		memset(printBuf,0,sizeof(printBuf));
        bool hasID = reader.getIDAtLine(currentLine,ID);
		//printf("Read de lines %s\n",ID);
        bool hasData = reader.getLineData(currentLine,data);
		//printf("Read de lines 1\n");
        if (hasID) {
			//printf("had id\n");
            if (hasData) {
				//printf("had data\n");
                if (streq(ID,"Note")) {
                    printf("Note: %s\n",data);
					print2(data,2000);
                }
                if (streq(ID,"IPL")) {
                    //load IPL of name data
                    printf("Spawning IPL %s\n",data);
					STREAMING::REQUEST_IPL(data);
                }
                if (streq(ID,"ModelHash")) {
                    currentSpawnData.ModelHash = StoI(data);
                }
                if (streq(ID,"Type")) {
                    currentSpawnData.Type = StoI(data);
                }
                if (streq(ID,"FrozenPos")) {
                    if (streq(data,"true")) {
                        currentSpawnData.FrozenPos = true;
                    } else {
                        currentSpawnData.FrozenPos = false;
                    }
                }
                if (streq(ID,"X")) {
					if (doingReferenceCoords)
						ReferenceCoords.x = StoF(data);
					if(doingPositionRotation)
						currentSpawnData.X = StoF(data);
                }
                if (streq(ID,"Y")) {
					if (doingReferenceCoords)
						ReferenceCoords.y = StoF(data);
					if(doingPositionRotation)
						currentSpawnData.Y = StoF(data);
                }
                if (streq(ID,"Z")) {
					//printf("Z coord: %s f: %f\n",data,StoF(data));
					if (doingReferenceCoords)
						ReferenceCoords.z = StoF(data);
					if(doingPositionRotation)
						currentSpawnData.Z = StoF(data);
                }
                if (streq(ID,"Pitch")) {
					if(doingPositionRotation)
						currentSpawnData.Pitch = StoF(data);
                }
                if (streq(ID,"Roll")) {
					if(doingPositionRotation)
						currentSpawnData.Roll = StoF(data);
                }
                if (streq(ID,"Yaw")) {
					if(doingPositionRotation)
						currentSpawnData.Yaw = StoF(data);
                }
            } else {
				//no data
                if (reader.isLineEnd(currentLine)) {
                    //means it is auto formatted to remove the /
                    if (streq(ID,"Placement")) {
                        //spawn the object!
                        snprintf(printBuf,sizeof(printBuf),"Spawning object: %i %i %i %f %f %f %f %f %f\n",currentSpawnData.ModelHash,currentSpawnData.Type,currentSpawnData.FrozenPos,currentSpawnData.X,currentSpawnData.Y,currentSpawnData.Z,currentSpawnData.Pitch,currentSpawnData.Roll,currentSpawnData.Yaw);
						printf(printBuf);
						Vector3 pos = {currentSpawnData.X/*+ReferenceCoords.x*/,currentSpawnData.Y/*+ReferenceCoords.y*/,currentSpawnData.Z/*+ReferenceCoords.z*/};
						Vector3 rot = {currentSpawnData.Pitch,currentSpawnData.Roll,currentSpawnData.Yaw};
						spoonerForCallbackSpawnFunc = this;
						if (currentSpawnData.Type == 3)
							OBJ::forceCreateObject(currentSpawnData.ModelHash,pos,rot,currentSpawnData.FrozenPos,spoonerCallbackSpawnFunc,false);
						pauseInterpretation();
					}
					if (streq(ID,"ReferenceCoords")) {
						//teleport to le coords
						doingReferenceCoords = false;
						snprintf(printBuf,sizeof(printBuf),"Teleport to %f %f %f\n",ReferenceCoords.x,ReferenceCoords.y,ReferenceCoords.z);
						printf(printBuf);
						PlayerMods::teleportToCoords(ReferenceCoords.x,ReferenceCoords.y,ReferenceCoords.z);
					}
					if (streq(ID,"PositionRotation")) {
						doingPositionRotation = false;
					}
                } else {
					//begin line
					if (streq(ID,"ReferenceCoords")) {
						printf("Found reference coords\n");
						doingReferenceCoords = true;
					}
					if (streq(ID,"PositionRotation")) {
						doingPositionRotation = true;
					}
				}
            }
        } else {
            //well idk what to do here lol
        }
        currentLine++;
		//printf("Done interpreting line\n");
    }

    void spawnCallback(int previouslySpawnedEntity) {
		//looping = true;//continue to next
		printf("Callback called!\n");
		waitForSpawnToBeComplete = false;
		if (previouslySpawnedEntity != -1) {
			//do stuff
		}
    }

	void stop() {
		looping = false;
	}

    void pauseInterpretation() {
        //called when getting to the end of a 'Placement' section
		//looping = false;//stop until object is done spawning
		waitForSpawnToBeComplete = true;
    }

    void resetSpawnData() {
        currentSpawnData.ModelHash = 0;
        currentSpawnData.Type = 0;
        currentSpawnData.FrozenPos = 0;
        currentSpawnData.X = 0;
        currentSpawnData.Y = 0;
        currentSpawnData.Z = 0;
        currentSpawnData.Pitch = 0;
        currentSpawnData.Roll = 0;
        currentSpawnData.Yaw = 0;
    }

	void resetAll() {
		doingReferenceCoords = false;
		doingPositionRotation = false;
		ReferenceCoords.x = 0;
		ReferenceCoords.y = 0;
		ReferenceCoords.z = 0;
		resetSpawnData();
	}

	//returns true if started
    bool begin() {
		if (reader.isOpened()) {
			looping = true;
			currentLine = 1;
			waitForSpawnToBeComplete = false;
			return true;
		} else {
			return false;
		}
    }

    void loop() {
        if (looping) {
			reader.fsQue();
			if (reader.lineReady(currentLine)) {
				if (currentLine < reader.getLineCount()) {
				    if (waitForSpawnToBeComplete == false) {
				        interpretLine();
				    }
				} else {
				    looping = false;
				    print2("Done!\n");
					
				}
			}
        } else {

		}
		//endEncryptunc();//I removed xml so this ain't show anymore
		//btw this was here because class functions are put at bottom of sprx
    }

};


void spoonerCallbackSpawnFunc(int entity) {
	spoonerForCallbackSpawnFunc->spawnCallback(entity);
}



Spooner globalSpooner = Spooner(0);
bool spoonerQueFunction() {
	return globalSpooner.getReader()->fsQue();
}
bool setGlobalSpooner(char *newFile) {
	if (doesFileExist(newFile)) {
		//if (globalSpooner != 0)
		//	globalSpooner->clearSpooner();
		globalSpooner.getReader()->getStreamer()->createFileStreamer(newFile);
		globalSpooner.resetAll();
		printf("Retreived lines properly! Starting!\n");
		//static Spooner sp = Spooner(newFile);
		//globalSpooner = &sp;
		
		return true;
	} else {
		return false;
	}
}

void startGlobalSpooner() {
	bool started = globalSpooner.begin();
	if (!started) {
		print2("Could not start! Probably issues allocationd data.",2000);
	}
}

void loopGlobalSpooner() {
	globalSpooner.loop();
}






























































class VehicleSpooner;
VehicleSpooner *vehicleSpoonerForCallbackSpawnFunc;
void vehicleSpoonerSpawnVehicleCallbackSpawnFunc(int entity);
void vehicleSpoonerSpawnEntityCallbackSpawnFunc(int entity);

class VehicleSpooner {
private:
    XMLReader reader;
    int currentLine;
    SpoonerSpawnInfo currentSpawnData;
    char currentLineText[lineBufSize];
    bool looping;
    bool waitForSpawnToBeComplete;
	Vector3 ReferenceCoords;
	//bool doingReferenceCoords;
	//bool doingPositionRotation;
	int vehicleAttachToEntity;
	int AttachmentLevel;
	int boneIndex;
public:
    VehicleSpooner(char *fileLoc)
    : reader(fileLoc)
    {
		//printf("In spooner creation!\n");
        currentLine = 1;//the first line is xml declaration type
        looping = false;
		waitForSpawnToBeComplete = false;
        memset(currentLineText,0,sizeof(currentLineText));
        waitForSpawnToBeComplete = false;
		vehicleAttachToEntity = -1;
		AttachmentLevel = 0;
    }

	XMLReader *getReader() {
		return &reader;
	}

	bool isRunning() {
		return looping;
	}

	/*void printAll() {
		reader.printAll();
	}*/

    void interpretLine() {
		//printf("interpreting line\n");
        char ID[lineBufSize];
        char data[lineBufSize];
		char printBuf[200];
		memset(printBuf,0,sizeof(printBuf));
        bool hasID = reader.getIDAtLine(currentLine,ID);
		//printf("Read de lines %s\n",ID);
        bool hasData = reader.getLineData(currentLine,data);
		//printf("Read de lines 1\n");

		char fullLine[lineBufSize];
		reader.getFullLine(currentLine,fullLine,sizeof(fullLine));
		if (strstr(fullLine,"<SpoonerAttachments")) {
						//spawn the car
						vehicleSpoonerForCallbackSpawnFunc = this;
						printf("Spawning vehicle with hash 0x%X\n",currentSpawnData.ModelHash);
						VehicleMods::spawnVehicle(currentSpawnData.ModelHash,vehicleSpoonerSpawnVehicleCallbackSpawnFunc,vehicleSpoonerSpawnVehicleCallbackSpawnFunc);
						pauseInterpretation();
					}

        if (hasID) {
			//printf("had id\n");
            if (hasData) {
				//printf("had data\n");
                if (streq(ID,"Note")) {
                    printf("Note: %s\n",data);
					print2(data,2000);
                }
                if (streq(ID,"IPL")) {
                    //load IPL of name data
                    printf("Spawning IPL %s\n",data);
					STREAMING::REQUEST_IPL(data);
                }
                if (streq(ID,"ModelHash")) {
                    currentSpawnData.ModelHash = StoI(data);
                }
				if (streq(ID,"IsCollisionProof")) {
					 if (streq(data,"true")) {
                        currentSpawnData.IsCollisionProof = true;
                    } else {
                        currentSpawnData.IsCollisionProof = false;
                    }
				}
				if (streq(ID,"IsVisible")) {
                    if (streq(data,"true")) {
                        currentSpawnData.IsVisible = true;
                    } else {
                        currentSpawnData.IsVisible = false;
                    }
                }
				if (streq(ID,"IsInvincible")) {
                    if (streq(data,"true")) {
                        currentSpawnData.IsInvincible = true;
                    } else {
                        currentSpawnData.IsInvincible = false;
                    }
                }
                if (streq(ID,"Type")) {
                    currentSpawnData.Type = StoI(data);
                }
                if (streq(ID,"FrozenPos")) {
                    if (streq(data,"true")) {
                        currentSpawnData.FrozenPos = true;
                    } else {
                        currentSpawnData.FrozenPos = false;
                    }
                }
                if (streq(ID,"X")) {
						currentSpawnData.X = StoF(data);
                }
                if (streq(ID,"Y")) {
						currentSpawnData.Y = StoF(data);
                }
                if (streq(ID,"Z")) {
					//printf("Z coord: %s f: %f\n",data,StoF(data));
						currentSpawnData.Z = StoF(data);
                }
                if (streq(ID,"Pitch")) {
						currentSpawnData.Pitch = StoF(data);
                }
                if (streq(ID,"Roll")) {
						currentSpawnData.Roll = StoF(data);
                }
                if (streq(ID,"Yaw")) {
						currentSpawnData.Yaw = StoF(data);
                }
				if (streq(ID,"BoneIndex")) {
					boneIndex = StoI(data);
					printf("Bone attaching to: %i\n",boneIndex);
				}
            } else {
				//no data
                if (reader.isLineEnd(currentLine)) {
                    //means it is auto formatted to remove the /
                    if (streq(ID,"Attachment")) {
						AttachmentLevel--;
						if (AttachmentLevel == 0) {
							//spawn the object!
							snprintf(printBuf,sizeof(printBuf),"Spawning object: %i %i %i %f %f %f %f %f %f\n",currentSpawnData.ModelHash,currentSpawnData.Type,currentSpawnData.FrozenPos,currentSpawnData.X,currentSpawnData.Y,currentSpawnData.Z,currentSpawnData.Pitch,currentSpawnData.Roll,currentSpawnData.Yaw);
							printf(printBuf);
							Vector3 pos = ENTITY::GET_ENTITY_COORDS(vehicleAttachToEntity,true);//{currentSpawnData.X/*+ReferenceCoords.x*/,currentSpawnData.Y/*+ReferenceCoords.y*/,currentSpawnData.Z/*+ReferenceCoords.z*/};
							Vector3 rot = {currentSpawnData.Pitch,currentSpawnData.Roll,currentSpawnData.Yaw};
							vehicleSpoonerForCallbackSpawnFunc = this;
							if (currentSpawnData.Type == 3)//prop
								OBJ::forceCreateObject(currentSpawnData.ModelHash,pos,rot,currentSpawnData.FrozenPos,vehicleSpoonerSpawnEntityCallbackSpawnFunc);
							if (currentSpawnData.Type == 2)//vehicle
								VehicleMods::spawnVehicle(currentSpawnData.ModelHash,vehicleSpoonerSpawnEntityCallbackSpawnFunc);
							pauseInterpretation();
						}
					}
					
                } else {
					//begin line
					if (streq(ID,"Attachment")) {
						AttachmentLevel++;
					}
				}
            }
        } else {
            //well idk what to do here lol
        }
        currentLine++;
		//printf("Done interpreting line\n");
    }

    void spawnCallback(int previouslySpawnedEntity) {
		//looping = true;//continue to next
		printf("Callback called!\n");
		waitForSpawnToBeComplete = false;
		if (previouslySpawnedEntity != -1) {
			Vector3 pos = {currentSpawnData.X/*+ReferenceCoords.x*/,currentSpawnData.Y/*+ReferenceCoords.y*/,currentSpawnData.Z/*+ReferenceCoords.z*/};
			Vector3 rot = {currentSpawnData.Pitch,currentSpawnData.Roll,currentSpawnData.Yaw};
			OBJ::attachPropAlreadySpawnedObject(vehicleAttachToEntity,boneIndex,previouslySpawnedEntity,pos,rot,false);
			if (currentSpawnData.IsCollisionProof == true) {
				ENTITY::SET_ENTITY_COLLISION(previouslySpawnedEntity,true,true);
				currentSpawnData.IsCollisionProof = false;
			}
			ENTITY::SET_ENTITY_VISIBLE(previouslySpawnedEntity,currentSpawnData.IsVisible);
			ENTITY::SET_ENTITY_INVINCIBLE(previouslySpawnedEntity,currentSpawnData.IsInvincible);
		}
    }

	void stop() {
		looping = false;
	}

	void spawnVehicle(int previouslySpawnedEntity) {
		printf("Spawned main vehicle!\n");
		waitForSpawnToBeComplete = false;
		if (previouslySpawnedEntity != -1) {
			//do stuff
			if (currentSpawnData.IsVisible == false)
				ENTITY::SET_ENTITY_VISIBLE(previouslySpawnedEntity,false);
			if (currentSpawnData.IsInvincible == true)
				ENTITY::SET_ENTITY_INVINCIBLE(previouslySpawnedEntity,true);
			vehicleAttachToEntity = previouslySpawnedEntity;
			VehicleMods::setIntoVehicle(vehicleAttachToEntity);
		} else {
			print2("~r~Could not spawn base vehicle!",5000);
			looping = false;
		}
	}

    void pauseInterpretation() {
        //called when getting to the end of a 'Placement' section
		//looping = false;//stop until object is done spawning
		waitForSpawnToBeComplete = true;
    }

    void resetSpawnData() {
        currentSpawnData.ModelHash = 0;
        currentSpawnData.Type = 0;
        currentSpawnData.FrozenPos = 0;
        currentSpawnData.X = 0;
        currentSpawnData.Y = 0;
        currentSpawnData.Z = 0;
        currentSpawnData.Pitch = 0;
        currentSpawnData.Roll = 0;
        currentSpawnData.Yaw = 0;
		currentSpawnData.IsCollisionProof = false;
		currentSpawnData.IsVisible = true;
		boneIndex = 0;
		printf("Reset spawn info!\n");
    }

	void resetAll() {
		ReferenceCoords.x = 0;
		ReferenceCoords.y = 0;
		ReferenceCoords.z = 0;
		AttachmentLevel = 0;
		vehicleAttachToEntity = -1;
		resetSpawnData();
	}

	//returns true if started
    bool begin() {
		if (reader.isOpened()) {
			looping = true;
			currentLine = 1;
			waitForSpawnToBeComplete = false;
			return true;
		} else {
			return false;
		}
    }

    void loop() {
        if (looping) {
			reader.fsQue();
			if (reader.lineReady(currentLine)) {
				if (currentLine < reader.getLineCount()) {
				    if (waitForSpawnToBeComplete == false) {
				        interpretLine();
				    }
				} else {
				    looping = false;
				    print2("Done!\n");
				}
			}
        } else {

		}
    }

};

void vehicleSpoonerSpawnVehicleCallbackSpawnFunc(int entity) {
	vehicleSpoonerForCallbackSpawnFunc->spawnVehicle(entity);
}

void vehicleSpoonerSpawnEntityCallbackSpawnFunc(int entity) {
	vehicleSpoonerForCallbackSpawnFunc->spawnCallback(entity);
}


VehicleSpooner globalVehicleSpooner = VehicleSpooner(0);
bool vehicleSpoonerQueFunction() {
	return globalVehicleSpooner.getReader()->fsQue();
}
bool setGlobalVehicleSpooner(char *newFile) {
	if (doesFileExist(newFile)) {
		//if (globalSpooner != 0)
		//	globalSpooner->clearSpooner();
		globalVehicleSpooner.getReader()->getStreamer()->createFileStreamer(newFile);
		globalVehicleSpooner.resetAll();
		printf("Retreived lines properly! Starting!\n");
		//static Spooner sp = Spooner(newFile);
		//globalSpooner = &sp;
		
		return true;
	} else {
		return false;
	}
}

void startGlobalVehicleSpooner() {
	bool started = globalVehicleSpooner.begin();
	if (!started) {
		print2("Could not start veh spooner! Probably issues allocationd data.",2000);
	}
}

void loopGlobalVehicleSpooner() {
	globalVehicleSpooner.loop();
}




























//directory reading

bool readDir(const char *dirName, void(*callback)(char* path,int type)) {
	int fd = 0;
	CellFsDirent entry;
	u64 read = 0;
	s64 err = 0;
	if (err = cellFsOpendir (dirName,&fd) >= 0) {
		while (err = cellFsReaddir (fd,&entry,&read) >= 0) {
			
			if (entry.d_namlen == 0)
				break;
			if (!(strstr(".",entry.d_name) || strstr("..",entry.d_name)))
				callback(entry.d_name,entry.d_type);
			read++;
		}
		cellFsClosedir (fd);
		return true;
	} else {
		printf("Error opening dir! 0x%X\n",err);
		return false;
	}
}

























void set3DMode(bool enabled);
//bool doForceHostBool = false;

struct XMLSettings {
	/*bool godmode;
	float noclipSpeed;
	int colorR,colorG,colorB;
	bool noCops;
	float menuScale;
	bool objectAttachmentProtection;
	bool blockAllObjectSpawning;
	bool blockClonesAndPeds;
	bool showTalkingPlayers;
	bool undetectableGodmode;*/
	bool rainbowMode;
};

XMLSettings globalXMLSettings;

class SettingsReader {
private:
    XMLReader reader;
    int currentLine;
    SpoonerSpawnInfo currentSpawnData;
    char currentLineText[lineBufSize];
    bool looping;
public:
    SettingsReader(char *fileLoc)
    : reader(fileLoc)
    {
		//printf("In spooner creation!\n");
        currentLine = 1;//the first line is xml declaration type
        looping = false;
        memset(currentLineText,0,sizeof(currentLineText));
    }

	XMLReader *getReader() {
		return &reader;
	}

	bool isRunning() {
		return looping;
	}

	/*void printAll() {
		reader.printAll();
	}*/

    void interpretLine() {
		//printf("interpreting line\n");
        char ID[lineBufSize];
        char data[lineBufSize];
		char printBuf[200];
		memset(printBuf,0,sizeof(printBuf));
        bool hasID = reader.getIDAtLine(currentLine,ID);
		//printf("Read de lines %s\n",ID);
        bool hasData = reader.getLineData(currentLine,data);
		//printf("Read de lines 1\n");

        if (hasID) {
			//printf("had id\n");
            if (hasData) {
				printf("Data: %s, Val: %s\n",ID,data);
				if (streq(ID,"Godmode")) {
					/*if (streq(data,"true")) {
                        globalXMLSettings.godmode = true;
                    } else {
                        globalXMLSettings.godmode = false;
                    }*/
					GodMode::godmodeEnabled = StoBool(data);
				}
				if (streq(ID,"NoclipSpeed")) {
					noclip::speed = StoF(data);
				}
				if (streq(ID,"ColorRed")) {
					//globalXMLSettings.colorR = StoI(data);
					COLOR_FOREGROUND.x = StoI(data);
				}
				if (streq(ID,"ColorGreen")) {
					COLOR_FOREGROUND.y = StoI(data);
				}
				if (streq(ID,"ColorBlue")) {
					COLOR_FOREGROUND.z = StoI(data);
				}

				if (streq(ID,"TextRed")) {
					//globalXMLSettings.colorR = StoI(data);
					optionsRed = StoI(data);
				}
				if (streq(ID,"TextGreen")) {
					optionsGreen = StoI(data);
				}
				if (streq(ID,"TextBlue")) {
					optionsBlue = StoI(data);
				}

				if (streq(ID,"BackgroundOpacity")) {
					backgroundOpacity = StoI(data);
				}

				if (streq(ID,"NoCops")) {
					PlayerMods::wantedLevelEnabled = StoBool(data);
				}
				if (streq(ID,"MenuScale")) {
					textSize = StoF(data);
				}
				if (streq(ID,"ObjectAttachmentProtection")) {
					detachAllObjectsEnabled = StoBool(data);
				}
				if (streq(ID,"BlockAllObjectSpawning")) {
					*ENTITY_BLOCKER_BOOL = StoBool(data);
				}
				if (streq(ID,"BlockClonesAndPeds")) {
					*shouldSpawnPeds = StoBool(data);
				}
				if (streq(ID,"ShowTalkingPlayers")) {
					PlayerMods::showTalkingPlayersBool = StoBool(data);
				}
				if (streq(ID,"UndetectableGodmode")) {
					demiGodmode = StoBool(data);
				}
				if (streq(ID,"RainbowMode")) {
					globalXMLSettings.rainbowMode = StoBool(data);
				}
				if (streq(ID,"3DMode")) {
					set3DMode(StoBool(data));
				}
				if (streq(ID,"ParadiseChat")) {
					RTMTool::chatEnabled = StoBool(data);
				}
				if (streq(ID, "ParadiseChatUsePSNName")) {
					RTMTool::usePSN = StoBool(data);
				}
				if (streq(ID,"NoAdvertise")) {
					doNotUsePresence = StoBool(data);
				}
				/*if (streq(ID, "ForceHost")) {
					if (StoBool(data)) {
						doForceHostBool = true;
					}
				}*/
				/*if (streq(ID,"")) {
					globalXMLSettings.o = StoI(data);
				}*/
                /*if (streq(ID,"ModelHash")) {
                    currentSpawnData.ModelHash = StoI(data);
                }
				if (streq(ID,"IsVisible")) {
                    if (streq(data,"true")) {
                        currentSpawnData.IsVisible = true;
                    } else {
                        currentSpawnData.IsVisible = false;
                    }
                }
				
                if (streq(ID,"Yaw")) {
						currentSpawnData.Yaw = StoF(data);
                }*/
            } else {
				//no data
                if (reader.isLineEnd(currentLine)) {
                    //means it is auto formatted to remove the /
                    
					
                } else {
					//begin line
					
				}
            }
        } else {
            //well idk what to do here lol
        }
        currentLine++;
		//printf("Done interpreting line\n");
    }



	void stop() {
		looping = false;
	}



	//returns true if started
    bool begin() {
		if (reader.isOpened()) {
			printf("Reader opened\n");
			looping = true;
			currentLine = 1;
			return true;
		} else {
			return false;
		}
    }

    void loop() {
        if (looping) {
			reader.fsQue();
			if (reader.lineReady(currentLine)) {
				if (currentLine < reader.getLineCount()) {
					interpretLine();
				} else {
				    looping = false;
				    printf("Done!\n");
				}
			}
        } else {

		}
		
    }

};








void readSettingsFileData() {
	SettingsReader globalSettingsReader = SettingsReader("/dev_hdd0/tmp/gopro_2027/settings.xml");
	//globalSettingsReader.getReader()->getStreamer()->createFileStreamer("/dev_hdd0/tmp/gopro_2027/settings.xml");
	bool started = globalSettingsReader.begin();
	if (!started) {
		print2("Could not start settings reader! Probably issues allocationd data.",2000);
	}
	while (globalSettingsReader.isRunning()) {
		globalSettingsReader.loop();
	}
	printf("Done reading settings!\n");

	/*noclip::speed = globalXMLSettings.noclipSpeed;
	GodMode::godmodeEnabled = globalXMLSettings.godmode;
	COLOR_FOREGROUND.x = globalXMLSettings.colorR;
	COLOR_FOREGROUND.y = globalXMLSettings.colorG;
	COLOR_FOREGROUND.z = globalXMLSettings.colorB;
	textSize = globalXMLSettings.menuScale;
	detachAllObjectsEnabled = globalXMLSettings.objectAttachmentProtection;
	*ENTITY_BLOCKER_BOOL = globalXMLSettings.blockAllObjectSpawning;
	*shouldSpawnPeds = globalXMLSettings.blockClonesAndPeds;
	PlayerMods::showTalkingPlayersBool = globalXMLSettings.showTalkingPlayers;
	demiGodmode = globalXMLSettings.undetectableGodmode;*/
}

