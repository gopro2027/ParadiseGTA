#ifdef PSCfileused

//#include <string.h>
//#include <iostream>
//#include <stdlib.h>     /* atoi */
//#include <cstdio>    /* snprintf$ */
char PSCscript[10000];
#define VARVALUELENGTH 100
#define VARNAMELENGTH 100
char *evaluationString=0;
char *currentPointer=0;
char *maxPointer=0;
char *beginningPointer=0;
char currentWord[100];
char peekWord[100];
class Var {
public:
	char value[VARVALUELENGTH];
	int type;
	char name[VARNAMELENGTH];
	int getType() {
		return type;
	}
	char *getValue() {
		return value;
	}
};
Var variables[100];
Var *getVariableLoc(char *name) {
	for (int i = 0; i < 100; i++)
		if (strstr(name,variables[i].name)&&strstr(variables[i].name,name))
			return &variables[i];
	Var temp;
	strcpy(temp.name,"NULLVAR");
	strcpy(temp.value,"0");
	temp.type = 0;
	return &temp;
}
Var getVariable(char *name) {
	for (int i = 0; i < 100; i++)
		if (strstr(name,variables[i].name)&&strstr(variables[i].name,name))
			return variables[i];
	Var temp;
	strcpy(temp.name,"NULLVAR");
	strcpy(temp.value,"0");
	temp.type = 0;
	return temp;
}
bool doesVarExist(char *name) {
	for (int i = 0; i < 100; i++) {
		if (strstr(name,variables[i].name)&&strstr(variables[i].name,name)) {
			return true;
		}
	}
	return false;
}
void setVariable(char *name, char *value, int size = 100) {
	for (int i = 0; i < 100; i++) {
		if (strstr(name,variables[i].name)&&strstr(variables[i].name,name)) {
			//printf("Setting Variable!\n");
			for (int j = 0; j < VARVALUELENGTH; j++)
				variables[i].value[j] = 0;
			strncpy(variables[i].value,value,size);
			//printf("Set Variable!\n");
			return;
		}
	}
	for (int i = 0; i < 100; i++) {
		if (strstr(variables[i].name,"NULLVAR")&&strstr("NULLVAR",variables[i].name)) {
			//printf("Creating Variable!\n");
			for (int j = 0; j < VARVALUELENGTH; j++)
				variables[i].value[j] = 0;
			for (int j = 0; j < VARNAMELENGTH; j++)
				variables[i].name[j] = 0;
			strncpy(variables[i].name,name,VARNAMELENGTH);
			strncpy(variables[i].value,value,size);
			//printf("Created Variable!\n");
			return;
		}
	}
}
char *gotos[100];
int gotosnum = 0;
void addgotoreturn(char *go) {
	if (gotosnum < 100) {
		gotos[gotosnum] = go;
		gotosnum++;
	}
}
/*char *getgotoreturn() {
	if (gotosnum > 0)
		return gotos[--gotosnum];
	return currentPointer;
}*/
/*class Goto {
public:
	char *address;
	char *getAddress() {
		return address;
	}
};
Goto gotos[100];*/
class Func {
public:
	char *name;
	int numargs;
	//the arguments will be an array of Vars
	int (*saveFunc)(Var**);//double array because it saves the location of it not just the value of it
};
Func functions[250];
int functionsCounter = 0;
void addFunction(char *name, int(*func)(Var**), int numargs) {
    Func f;
    f.name = name;
	f.numargs = numargs;
    f.saveFunc = func;
    functions[functionsCounter] = f;
    functionsCounter++;
}
//Var nullVar;
int callFunc(char *name, Var **args/*Var arg1 = nullVar,Var arg2 = nullVar,Var arg3 = nullVar,Var arg4 = nullVar,Var arg5 = nullVar,Var arg6 = nullVar,Var arg7 = nullVar,                  Var arg8 = nullVar,Var arg9 = nullVar,Var arg10 = nullVar,Var arg11 = nullVar,Var arg12 = nullVar,Var arg13 = nullVar*/) {
    for (int i = 0; i < 250; i++) {
        if (strstr(name,functions[i].name) && strstr(functions[i].name,name)) {
            return functions[i].saveFunc(args);
        }
    }
}
int getFuncArgsCount(char *name) {
    for (int i = 0; i < 250; i++) {
        if (strstr(name,functions[i].name) && strstr(functions[i].name,name)) {
            return functions[i].numargs;
        }
    }
}
void nextLine() {
	currentPointer++;
	while (currentPointer < maxPointer && *currentPointer != '\n' && *currentPointer != 0)
		currentPointer++;
	currentPointer++;
}
char *NextLinePointer(char *ptr = currentPointer) {
    char *p = ptr;
	while (*p != '\n' && *p != 0 && p < maxPointer) {
		p++;
	}
	return p;
}
void previousLine() {
	currentPointer--;
	while (currentPointer > beginningPointer && *currentPointer != '\n' && *currentPointer != 0)
		currentPointer--;
}
char next() {
    //if (currentPointer < maxPointer-1)
	    return *(++currentPointer);
	//return 0;
}
char previous() {
    //if (currentPointer > beginningPointer)
	    return *(--currentPointer);
	//return 0;
}
char next(char *ptr) {
    //if (ptr < maxPointer-1)
	    return *(++ptr);
	//return 0;
}
char previous(char *ptr) {
    //if (ptr > beginningPointer)
        return *(--ptr);
    //return 0;
}

bool hasNextLine() {
    //std::cout << NextLinePointer()-currentPointer << std::endl;
    //if (NextLinePointer()-currentPointer == 1)
        //return false;
    char *p = currentPointer;
	while (p < maxPointer-1 && *p != '\n' && *p != 0) {
		p++;
	}
	if (*p == '\n')
	    return true;
	return false;
}
char *nextWord() {//returns the word that currentPointer is currently inside. if it is at a space it gets the next word
	              //goes to the first letter of the next word. ex: "hi there pal" and currentPointer is at 'h' it puts it at the 't'
	char ch = 1;
	while (hasNextLine() && ch != ' ' && ch != 0 && ch != '\n')
		ch = previous();//goes to the previous space
	ch = next();//gets the start of the current word
	char *p = currentPointer;
	while (hasNextLine() && /*p < maxPointer && */*p != ' ' && *p != 0 && *p != '\n') {
		p++;//finding the end of the word
	}
	if (*p == '\n')
	    return 0;
	for (int i = 0; i < 100; i++)
	    currentWord[i] = 0;
	strncpy(currentWord,currentPointer,p-currentPointer);//at this point, currentPointer is at the start of the current word
	//std::cout << currentWord << std::endl;
	while (ch != ' ' && ch != 0 && ch != '\n' && currentPointer < maxPointer)
		ch = next();
	ch = next();
	return currentWord;
}
char *peekNextWord(char *start = currentPointer, bool addOne = false) {//returns the pointer of the next word, not the actual word, unlike the other one
    char *myptr = start;
	char ch = 1;
	while (hasNextLine() && myptr > beginningPointer && ch != ' ' && ch != 0 && ch != '\n')//find the start of the current word
		ch = previous(myptr);
	ch = next(myptr);
	char *p = myptr;
	while (hasNextLine() && p < maxPointer && *p != ' ' && *p != 0 && *p != '\n') {//find the end of the current word
		p++;
	}
	//if (*p == '\n')
	    //return p+1;
	for (int i = 0; i < 100; i++)
	    peekWord[i] = 0;
	int s = p-myptr;
	if (s > 99)s = 99;
	if (!addOne)
		strncpy(peekWord,myptr,s-1);
	else
		strncpy(peekWord,myptr,s);
	//std::cout << peekWord << std::endl;
	return p+1;
}
int AmountTillNextLine() {
    char *p = currentPointer;
	while (/*p < maxPointer-1 && */*p != '\n' && *p != 0) {
		p++;
	}
	//if (*p == '\n')
	    //return 0;
	return p-currentPointer;
}
void goToLine(int line) {
	char *ptr = beginningPointer;
	for (int i = 0; i < line; i++) {
		/*while (*ptr != '\n' && ptr < maxPointer  && *ptr != 0) {
			ptr++;
		}*/
		ptr = NextLinePointer()+1;
	}
	currentPointer = ptr;
}
Var *funcargs[100];
char functiontocallbuf[100];
int counter = 0;
void evaluatePSC(char *string, char *startGoto = NULL) {
	if (string[0] == 0)
		return;
	counter = 0;
	evaluationString = string;
	currentPointer = string;
	beginningPointer = string;
	maxPointer = string+strlen(string);
	int gotonextline = true;
	if (startGoto == NULL) {
		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < VARVALUELENGTH; j++)
				variables[i].value[j] = 0;
			for (int j = 0; j < VARNAMELENGTH; j++)
				variables[i].name[j] = 0;
			strcpy(variables[i].name,"NULLVAR");
			strcpy(variables[i].value,"0");
			variables[i].type = 0;
			gotosnum = 0;
		}
	} else {
		char find[100];
		snprintf$(find,100,"+ %s",startGoto);
		char *ptr = strstr(beginningPointer,find);
		if (ptr != NULL) {
			currentPointer = ptr;
			nextLine();
		} else {
			//printf("Hook not found!");
			return;
		}
		gotosnum = 0;
	}
	//nextLine();
    while (hasNextLine()) {
		gotonextline = 1;
        //check for an equal sign (gonna change later probably but maybe not idk)
		if (*currentPointer == '+'/* || *currentPointer == '['*/ || *currentPointer == '\'' || *currentPointer == '}') {//:
		    //function location and comment notifier
		}
		else if (*currentPointer == '-') {//+
			//return goto thingy
			if (gotosnum > 0) {
				currentPointer = gotos[--gotosnum];
				//nextWord();
			}
			
		}
		else if (*currentPointer == ':') {//-
		    char find[100];//hey  
			/*char *wo = peekNextWord();
			peekNextWord(wo,true);
			printf("\n");
			printf(peekWord);
		    //snprintf$(find,sizeof(find),"+ %s",peekWord);
			for (int k = strlen(peekWord); k > 0; k--) {
				find[k+1] = peekWord[k-1];
		    }
			find[0] = '+';
			find[1] = ' ';
			//printf(find);
			printf("\n");
			printf("SWAGGGG");*/
			int size = NextLinePointer()-currentPointer;
			size--;//remove 1
			for (int i = 0; i < 100; i++)
				find[i] = 0;
			strncpy(find,currentPointer,size);
			find[0] = '+';
			//printf("Find: %s\n",find);
			//find[strlen(find)-1] = 0;
			//for (int i = 0; i < strlen(find); i++)
				//printf("%i, ",(int)find[i]);
		    char *ptr = strstr(beginningPointer,find);
		    if (ptr != NULL) {
				addgotoreturn(currentPointer);
				currentPointer = ptr;
				nextWord();
		    } else {
		        //printf("Could not find pointer\n");
		    }
			//nextLine();
			//currentPointer++;
			//printf("On the next line\n");
		}
		/*else if (*currentPointer == ']') {//regular goto
		    char find[100];
			char *wo = peekNextWord();
			peekNextWord(wo,true);
			snprintf$(find,sizeof(find),"[ %s",peekWord);
		    char *ptr = strstr(beginningPointer,find);
		    if (ptr != NULL) {
				//addgotoreturn(currentPointer);//just taking this out for obvious reasons (this is just a goto, not a function)
				currentPointer = ptr;
				nextWord();
		    } else {
		        //printf("Could not find pointer\n");
		    }
		}*/
else if (*currentPointer == '{') {//if
    nextWord();//don't want to be on the [
    char *ptr = peekNextWord(currentPointer,false);//set to false for ps3? testing needed
    //char word[100];
    //strncpy(word,peekWord,100);
    //peekNextWord(ptr,true);
    //std::cout << getVariable(word).value << std::endl;
    //if ( strstr(getVariable(peekWord).value,getVariable(word).value)) && strstr(getVariable(word).value,getVariable(peekWord).value)) {
    if (!strstr("0",getVariable(peekWord).value)) {
        //true so dont do anything but continue
    } else {
        //skip to the end of if when false
        char *ptr = currentPointer;
        int b = 1;
        while (b) {
            ptr=NextLinePointer(ptr)+1;
            if (*ptr == '{') {
                b++;//handle nested ifs
            }
            if (*ptr == '}') {
                b--;
            }
        }
        currentPointer = ptr;
    }
}
else if (*currentPointer == '[') {//while
    nextWord();//don't want to be on the [
    char *ptr = peekNextWord(currentPointer,false);//set to false for ps3? testing needed
    //char word[100];
    //strncpy(word,peekWord,100);
    //peekNextWord(ptr,true);
    //std::cout << getVariable(word).value << std::endl;
    //if ( strstr(getVariable(peekWord).value,getVariable(word).value)) && strstr(getVariable(word).value,getVariable(peekWord).value)) {
    if (!strstr("0",getVariable(peekWord).value)) {
        //true so dont do anything but continue
    } else {
        //skip to the end of if when false
        char *ptr = currentPointer;
        int b = 1;
        while (b) {
            ptr=NextLinePointer(ptr)+1;
            if (*ptr == '[') {
                b++;//handle nested ifs
            }
            if (*ptr == ']') {
                b--;
            }
        }
        currentPointer = ptr;
    }
}
else if (*currentPointer == ']') {//while loops end
    //std::cout <<"yello"<<std::endl;
    //close while statement so go up top
    char *ptr = currentPointer-1;//ptr is now on previous line
    int b = 1;
    while (b) {
        ptr--;
        ptr--;//put oon end of prvs lne
        while (*ptr != '\n' && ptr > beginningPointer-1)
           ptr--;
        ptr++;//put on first word of a line
        if (*ptr == ']') {
            b++;//handle nested whiless
            //std::cout <<b<<std::endl;
        }
        if (*ptr == '[') {
            b--;
            //std::cout <<b<<std::endl;
        }
    }
    currentPointer = ptr-2;
}
		else {

        char *l = peekNextWord();
        char *i = peekNextWord(l);
        if (strstr("=",peekWord)) {
            //peekNextWord(i);//this sets peekWord to the value we need   DO WE NEED THIS ANYMORE? I TOOK I OFF
            //std::cout << nextWord() << " = "<< peekWord <<std::endl;
            
			int size = NextLinePointer()-i;
			size--;//remove 1
			if (size > 100)//this may need to be changed
				size = 100;
			char *wo = nextWord();
            //strncpy(variables[StoI(nextWord())].value, i/*peekWord*/,size);
			setVariable(wo,i,size);

			/*printf("\nVar Name: ");
			for (int i = 0; i < strlen(wo); i++)
				printf("%i, ",(int)wo[i]);
			printf("\n");
			printf("Var Set Value: ");
			for (int i = 0; i < size; i++)
				printf("%i, ",(int)getVariableLoc(wo)->value[i]);
			printf("\n");*/

            //strcpy(variables[StoI(nextWord())].value, peekWord);
        } else {
            //means we are calling a function
            for (int i = 0; i < 100; i++)
                functiontocallbuf[i] = 0;
                //std::cout << (currentPointer+1) << std::endl;
            currentPointer+=1;
            strncpy(functiontocallbuf,nextWord(),100);
            //char *q = currentPointer;
            //int i = 0;
            //q = peekNextWord(q);
            //std::cout << AmountTillNextLine() << std::endl;
            //std::cout << "yo" << std::endl;
            
            
            if (strstr("endProgram",functiontocallbuf)&&strstr(functiontocallbuf,"endProgram"))
				return;
            
            /*char *nw = currentPointer;
            nw = peekNextWord(nw);
            while (nw != 0) {
                std::cout << peekWord << std::endl;
                funcargs[i] = variables[atoi(peekWord)];
                i++;
                nw = peekNextWord(nw);
            }
            std::cout << peekWord << std::endl;*/
            char *nw = currentPointer;
            //nw = peekNextWord(nw,true);
            //int size = StoI(peekWord);
            //nw = peekNextWord(nw);
			//if (strstr())
			int size = getFuncArgsCount(functiontocallbuf);
            for (int i = 0; i < size; i++) {//0,1,2
                //i++;
				//if it is 1 arg then this will 1 - 2 which is -1 so it won't happen
				if (i == size-1) {//0 will be getting second arg (one)//1 gets 3rd (two)//2 gets invalid (skip it)
					nw = peekNextWord(nw);
				}
				else if (i < size) {//i < 2 so 0 and 1 for 3 args but since 1 is 3 - 2 it just does 0
					nw = peekNextWord(nw,true);
				}

				//std::cout << peekWord << std::endl;
				if (doesVarExist(peekWord)) {
					funcargs[i] = getVariableLoc(peekWord);//&variables[StoI(peekWord)];
				} else {
					//snprintf$(funcargs[i]->value,sizeof(funcargs[i]->value),"%s",peekWord);//this isn't gonna work
				}

				/*printf("\nfuncarg: ");
				for (int j = 0; j < strlen(peekWord)strlen(funcargs[i]->getValue()); j++)
					printf("%i, ",(int)peekWord funcargs[i]->getValue()[j]);
				printf("\n");*/

            }
            //std::cout << "hi"<<std::endl;
            
                /*
            do {
                //char *nw = nextWord();
                    funcargs[i] = variables[atoi(nw)];
                    std::cout <<nw << std::endl;
                    i++;
                    nw = nextWord();
            } while (AmountTillNextLine() > 0 && *nw != '\n');*/
            
            
             //std::cout <<functiontocallbuf << std::endl;
            
            //while (*(q-1) != '\n') {
                //funcargs[i] = variables[atoi(peekWord)];
                //q = peekNextWord(q);
                //i++;
            //}
            //previous();
            gotonextline = callFunc(functiontocallbuf,funcargs);
			currentPointer--;
			//printf(currentPointer);
            //nextLine();
        }
		}
		if (gotonextline == 1)
			nextLine();
		counter++;
		if (counter > 10000) {
			//print("~r~Error in scipt! Infinite loop. Breaking out");
			break;
		}
    }
}

namespace PSCFuncs {
	int printscript(Var **args) {
		//std::cout << "Console: "<<args[0]->getValue() << std::endl;
		print(args[0]->getValue());
		return 1;
	}
	int cmpwi(Var **args) {
		if (strstr(args[1]->getValue(),args[2]->getValue())&&strstr(args[2]->getValue(),args[1]->getValue())) {
			for (int i = 0; i < VARVALUELENGTH; i++)
				args[0]->value[i] = 0;
			strncpy(args[0]->value,"1",VARVALUELENGTH);
		} else {
			for (int i = 0; i < VARVALUELENGTH; i++)
				args[0]->value[i] = 0;
			strncpy(args[0]->value,"0",VARVALUELENGTH);
		}
		return 1;
	}

	int cmpstw(Var **args) {
		if (!strstr("0",args[0]->getValue())) {//if true
			//printf(currentPointer);
		} else {
			currentPointer = NextLinePointer()+1;//if false skip line
			//printf(currentPointer);
		}
		return 1;
	}

	int cmpstwfalse(Var **args) {
		if (!strstr("0",args[0]->getValue())) {//if true
			//nextLine();
			//printf(currentPointer);
			currentPointer = NextLinePointer()+1;//if true skip line
			//printf(currentPointer);
		}
		return 1;
	}

	int compare(Var **args) {
		if (strstr(args[0]->getValue(),args[1]->getValue()) && strstr(args[1]->getValue(),args[0]->getValue())  ) {//if true
			//go to next line like normal
		} else {
			currentPointer = NextLinePointer()+1;//if false, skip a line
			//printf(currentPointer);
		}
		return 1;
	}

	int comparen(Var **args) {
		if (strstr(args[0]->getValue(),args[1]->getValue()) && strstr(args[1]->getValue(),args[0]->getValue())  ) {//if true
			currentPointer = NextLinePointer()+1;//if true, skip a line
			//printf(currentPointer);
		}
		return 1;
	}

	int bla(Var **args) {
		goToLine(StoI(args[0]->getValue()));
		return 0;
	}

	int beq(Var **args) {
		if (!strstr("0",args[0]->getValue()))
			goToLine(StoI(args[1]->getValue()));
		return 0;
	}
	int bne(Var **args) {
		if (strstr("0",args[0]->getValue()))
			goToLine(StoI(args[1]->getValue()));
		return 0;
	}

	int addi(Var **args) { 
	    int n = StoI(args[1]->getValue())+StoI(args[2]->getValue());
		for (int i = 0; i < VARVALUELENGTH; i++) {
			args[0]->value[i] = 0;
		}
	    snprintf$(args[0]->value,VARVALUELENGTH,"%i",n);
	    //std::cout << args[0]->value << std::endl;
	    return 1;
	}
	int addFloat(Var **args) {
	    float n = StoF(args[1]->getValue())+StoF(args[2]->getValue());
		for (int i = 0; i < VARVALUELENGTH; i++) {
			args[0]->value[i] = 0;
		}
	    snprintf$(args[0]->value,VARVALUELENGTH,"%s",FtoS(n));
	    //std::cout << args[0]->value << std::endl;
	    return 1;
	}
	
	int muli(Var **args) {
	    int i = StoI(args[1]->getValue())*StoI(args[2]->getValue());
	    snprintf$(args[0]->value,VARVALUELENGTH,"%i",i);
	    //std::cout << args[0]->value << std::endl;
	    return 1;
	}
	int gotoGoto(Var **args) {
		char *ptr = beginningPointer;
		while (ptr < maxPointer) {
			if (*ptr == ':') {
				//printf("Found a ':'\n");
				peekNextWord(ptr);
				if (strstr(args[0]->value,peekWord)&&strstr(peekWord,args[0]->value)) {
					ptr = NextLinePointer()+1;
					currentPointer = ptr;
					//printf("Found pointer\n");
					return 0;
				}
			}
			//printf("Going to next line\n");
			ptr = NextLinePointer()+1;
		}
	}
	int nop(Var **args) {
		return 1;
	}
	int spawnObject(Var **args) {//propid, pos(offsetx,y,z)
		Vector3 pos = {StoI(args[1]->value)+OBJ::getPlayerPos().x,StoI(args[2]->value)+OBJ::getPlayerPos().y,StoI(args[3]->value)+OBJ::getPlayerPos().z};
		Vector3 rot = {0,0,0};
		OBJ::forceCreateObject(args[0]->value,pos,rot,false,false);
		return 1;
	}
	int spawnCar(Var **args) {
		VehicleMods::spawnVehicle(args[0]->value);
		return 1;
	}
	int getPlayerId(Var **args) {
		snprintf$(args[0]->value,VARVALUELENGTH,"%i",PLAYER::PLAYER_ID());
		return 1;
	}
	int getMyPlayerPed(Var **args) {
		snprintf$(args[0]->value,VARVALUELENGTH,"%i",PLAYER::PLAYER_PED_ID());
		return 1;
	}
	int getPlayerPed(Var **args) {
		snprintf$(args[0]->value,VARVALUELENGTH,"%i",PLAYER::GET_PLAYER_PED(StoI(args[1]->value)));
		return 1;
	}
	int attachObject(Var **args) {
		PlayerMods::forceAttachPropToPlayer(StoI(args[0]->getValue()),PlayerMods::bones::BONE_ROOT,args[1]->getValue());
		return 1;
	}

	void toLowerCase(char *key, size_t len) {
	    for(int i = 0; i < len; i++)
	    {
	        if (key[i] >= 65 && key[i] <= 90) {
	            key[i]+=32;
	        }
	    }
	}
	unsigned int jenkins_one_at_a_time_hash(char *key, size_t len)
	{
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
	    return hash;
	}
	bool timetoreset =  true;
	int callHash(Var **args) {
		toLowerCase(args[0]->getValue(),strlen(args[0]->getValue()));
		//printf("Hash of %s: %i\n",args[0]->getValue(),hash);
		if (strstr(args[0]->getValue(),"unk_") != NULL) {
			//printf("Full: %s\n",args[0]->getValue());
			//printf("Hex: %s\n",args[0]->getValue()+4);
			//includes the unk_
			unsigned int hash = StoIUHEX(args[0]->getValue()+4);
			CallHash(hash, NativeArg);
		} else {
			unsigned int hash = jenkins_one_at_a_time_hash(args[0]->getValue(),strlen(args[0]->getValue()));
			CallHash(hash/*StoI(args[0]->getValue())*/, NativeArg);
		}
		timetoreset = true;
		return 1;
	}
	int pushInt(Var **args) {
		if(timetoreset) {
			ResetArgs();
			timetoreset = false;
		}
		PushArg(StoI(args[0]->getValue()));
		return 1;
	}
	int pushFloat(Var **args) {
		if(timetoreset) {
			ResetArgs();
			timetoreset = false;
		}
		//atof("38");
		PushArg(StoF(args[0]->getValue()));
		//PushArg((float)StoI(args[0]->getValue()));
		return 1;
	}
	int pushCharPointer(Var **args) {
		if(timetoreset) {
			ResetArgs();
			timetoreset = false;
		}
		PushArg(args[0]->getValue());
		return 1;
	}
	int getReturnInt(Var **args) {
		for (int i = 0; i < VARVALUELENGTH; i++)
			args[0]->getValue()[i] = 0;
		snprintf$(args[0]->getValue(),VARVALUELENGTH,"%i",GetReturn<int>());
		return 1;
	}
	int getReturnFloat(Var **args) {
		for (int i = 0; i < VARVALUELENGTH; i++)
			args[0]->getValue()[i] = 0;
		snprintf$(args[0]->getValue(),VARVALUELENGTH,"%s",FtoS(GetReturn<float>()));
		//snprintf$(args[0]->getValue(),VARVALUELENGTH,"%i",(int)GetReturn<float>());
		return 1;
	}
	int getReturnCharArray(Var **args) {
		for (int i = 0; i < VARVALUELENGTH; i++)
			args[0]->getValue()[i] = 0;
		snprintf$(args[0]->getValue(),VARVALUELENGTH,"%s",GetReturn<char*>());
		return 1;
	}

	char tmpstr1[VARVALUELENGTH];
	char tmpstr2[VARVALUELENGTH];
	int addstr(Var **args) {
		for (int i = 0; i < VARVALUELENGTH; i++) {
			tmpstr1[i] = 0;
			tmpstr2[i] = 0;
		}
		strncpy(tmpstr1,args[1]->value,VARVALUELENGTH);
		strncpy(tmpstr2,args[2]->value,VARVALUELENGTH);
		snprintf$(args[0]->value,VARVALUELENGTH,"%s%s",tmpstr1,tmpstr2);
		return 1;
	}
	int set(Var **args) {
		for (int i = 0; i < VARVALUELENGTH; i++)
			args[0]->getValue()[i] = 0;
		strncpy(args[0]->getValue(),args[1]->getValue(),VARVALUELENGTH);
		return 1;
	}
	Var *saveEntity = NULL;
	void entitySpawn(int entity) {
		snprintf$(saveEntity->value,VARVALUELENGTH,"%s",ItoS(entity));
	}
	int spawnEntity(Var **args) {//first arg is entity type, second is the one to save the entity to
		saveEntity = args[1];
		snprintf$(saveEntity->value,VARVALUELENGTH,"%s","0");
		bodyguard::spawnNow(PLAYER::PLAYER_ID(),args[0]->getValue(),bodyguard::types::Player,false,entitySpawn);
		return 1;
	}
	int getPlayerX(Var **args) {//first arg is player, second arg is stored value
		int num = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(StoI(args[0]->value)),true).x;
		for (int i = 0; i < VARVALUELENGTH; i++)
			args[1]->getValue()[i] = 0;
		strncpy(args[1]->getValue(),ItoS(num),VARVALUELENGTH);
		return 1;
	}
	int getPlayerY(Var **args) {//first arg is player, second arg is stored value
		int num = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(StoI(args[0]->value)),true).y;
		for (int i = 0; i < VARVALUELENGTH; i++)
			args[1]->getValue()[i] = 0;
		strncpy(args[1]->getValue(),ItoS(num),VARVALUELENGTH);
		return 1;
	}
	int getPlayerZ(Var **args) {//first arg is player, second arg is stored value
		int num = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(StoI(args[0]->value)),true).z;
		for (int i = 0; i < VARVALUELENGTH; i++)
			args[1]->getValue()[i] = 0;
		strncpy(args[1]->getValue(),ItoS(num),VARVALUELENGTH);
		return 1;
	}
}

void PSCINIT() {
	printf("Loading custom functions\n");
	addFunction("nop",PSCFuncs::nop,0);
	addFunction("print",PSCFuncs::printscript,1);
    addFunction("addInt",PSCFuncs::addi,3);
	addFunction("addString",PSCFuncs::addstr,3);
	addFunction("addFloat",PSCFuncs::addFloat,3);
	addFunction("set",PSCFuncs::set,2);
	addFunction("mul",PSCFuncs::muli,3);
	//addFunction("branchIfTrue",PSCFuncs::beq,2);//not working
	//addFunction("branchIfFalse",PSCFuncs::bne,2);//not working
	addFunction("compare",PSCFuncs::cmpwi,3);//used to be areEqual
	addFunction("ifEqualContinue",PSCFuncs::compare,2);
	addFunction("ifNotEqualContinue",PSCFuncs::comparen,2);
	addFunction("ifTrue",PSCFuncs::cmpstw,1);//used to be ifTrueJump   go to next line if true, otherwise skip over
	addFunction("ifFalse",PSCFuncs::cmpstwfalse,1);//used to be ifFalseJump
	//addFunction("goToLine",PSCFuncs::bla,1);//not working
	addFunction("spawnCar",PSCFuncs::spawnCar,1);
	addFunction("spawnObject",PSCFuncs::spawnObject,4);
	addFunction("attachObject",PSCFuncs::attachObject,2);
	addFunction("PLAYER_ID",PSCFuncs::getPlayerId,1);
	addFunction("PLAYER_PED_ID",PSCFuncs::getMyPlayerPed,1);
	addFunction("GET_PLAYER_PED",PSCFuncs::getPlayerPed,2);
	addFunction("pushInt",PSCFuncs::pushInt,1);
	addFunction("pushString",PSCFuncs::pushCharPointer,1);
	addFunction("pushFloat",PSCFuncs::pushFloat,1);
	addFunction("callNative",PSCFuncs::callHash,1);
	addFunction("getString",PSCFuncs::getReturnCharArray,1);
	addFunction("getInt",PSCFuncs::getReturnInt,1);
	addFunction("getFloat",PSCFuncs::getReturnFloat,1);
	addFunction("spawnEntity",PSCFuncs::spawnEntity,2);
	addFunction("getPlayerX",PSCFuncs::getPlayerX,2);
	addFunction("getPlayerY",PSCFuncs::getPlayerY,2);
	addFunction("getPlayerZ",PSCFuncs::getPlayerZ,2);
	//addFunction("endProgram",PSCFuncs::endProgram,0);
	//addFunction("goto",PSCFuncs::gotoGoto,1);
	printf("Loaded custom functions\n");
}


/*char *script = "0 = 2\n1 = 10\n2 = 42\naddi 3 2 2 1\nprint 1 2\n5 = 2\n6 = 7\n7 = 345\nmuli 3 7 6 5\nprint 1 7\nprint 1 6\n";
int main()
{
    addFunction("print",printscript);
    addFunction("addi",addi);
	addFunction("muli",muli);
	evaluatePSC(script);
	
	return 0;
}

*/

#endif