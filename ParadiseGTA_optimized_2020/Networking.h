#include <sys/types.h>
#include <sys/socket.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h>
#include <cell/cell_fs.h>
#include <sys/stat.h>
#include <sys/time.h>
#include "STDLib.h"

//typedef struct hostent *gethos tbyname_t(const char *name);
//gethost byname_t* gethostby name_spec = (gethostby name_t*)0x00180571C;
//opd_s gethos tbyname_t = {0x00180571C,TOC};
//struct hostent *(*gethos tbyname_spec)(const char *name) = (struct hostent *(*)(const char *))&gethos tbyname_t;
void* _malloc(uint32_t a_uiSize);
void _free(void *a_Addr);
//char *gopro2027xyz();
//char *gopro2027xyzip();
char *serverparadisesprxcom();
char *serverparadisesprxcomip();
//char *serverparadisesprxcomip1();
void my_dialog2(int button, void *userdata);
//char menuTitle[500];
char forgeMenuTitle[60];
bool isthereanupdate = false;
bool useAlternateIP = false;//use 4 or 5

#define SERVER_PORT htons(80) //htons(433) 
int Socket;
struct hostent *Host;
struct sockaddr_in SocketAddress;
char *RequestBuffer;
void sleep(usecond_t time);
char networkSearchString[] = "\r\n\r\n";

__ALWAYS_INLINE ssize_t _recv(int s, void *buf, size_t len, int flags) {
	//unsigned int addr = *(volatile unsigned int*)(*(volatile unsigned int*)0x1C109A8+0x0);
	//unsigned int toc = *(volatile unsigned int*)(*(volatile unsigned int*)0x1C109A8+0x4);
	//opd_s recv_t = {addr,toc};
	opd_s recv_t = *(__opd_s__*)*(volatile unsigned int*)0x1C109A8;
	ssize_t(*rv)(int s, void *buf, size_t len, int flags) = (ssize_t(*)(int s, void *buf, size_t len, int flags))&recv_t;
	return rv(s,buf,len,flags);
}

int getIndexOf(char *string, char *find, int startindex = 0, bool addonlength = false) {
		for (int i = startindex; i < strlen(string); i++) {
			for (int j = 0; j < strlen(find); j++) {
				if (string[i+j] == find[j]) {
					if (j == strlen(find)-1) {
						if (addonlength)
							i+=strlen(find);
						return i;
					}
				} else {
					j = strlen(find);
				}
			}
		}
		return -1;
	}
	int substring2(char string[], int x, int y, bool clearrest = false) {
		int len = strlen(string);
		//underneath x
		for (int i = 0; i < x; i++) {
			if (i < len)
				string[i] = 0;
		}
		//above y
		for (int i = y; i < strlen(string); i++) {
			if (i < len)
				string[i] = 0;
		}
		//moving the rest down
		for (int i = x; i < y; i++) {
			if (i < len)
				string[i-x] = string[i];
		}
		//clearing the rest
		if (clearrest) {
			for (int i = y-x; i < len; i++) {
				if (i < len)
					string[i] = 0;
			}
		}
		return x;
	}

bool isdigit(char c) {
	if (c >= 48 && c <= 57)
		return true;
	return false;
}
bool isascii(char c) {
	if (c > 31)
		return true;
	return false;
}
bool isxdigit(char c) {
	if (c == 'x')
		return true;
	return false;
}
bool isspace(char c) {
	if (c == ' ')
		return true;
	return false;
}
bool islower(char c) {
	if (c >= 97 && c <= 122)
		return true;
	return false;
}
#ifdef isdfghjadisfgj
int
inet_aton(const char *cp, struct in_addr *addr) {
	unsigned long val;
	int base;
	int n;
	char c;
	unsigned char parts[4];
	unsigned char *pp = parts;
	int digit;

	c = *cp;
	for (;;) {
		/*
		 * Collect number up to ``.''.
		 * Values are specified as for C:
		 * 0x=hex, 0=octal, isdigit=decimal.
		 */
		if (!isdigit((unsigned char)c))
			return (0);
		val = 0; base = 10; digit = 0;
		if (c == '0') {
			c = *++cp;
			if (c == 'x' || c == 'X')
				base = 16, c = *++cp;
			else {
				base = 8;
				digit = 1 ;
			}
		}
		for (;;) {
			if (isascii(c) && isdigit((unsigned char)c)) {
				if (base == 8 && (c == '8' || c == '9'))
					return (0);
				val = (val * base) + (c - '0');
				c = *++cp;
				digit = 1;
			} else if (base == 16 && isascii(c) && 
				   isxdigit((unsigned char)c)) {
				val = (val << 4) |
					(c + 10 - (islower((unsigned char)c) ? 'a' : 'A'));
				c = *++cp;
				digit = 1;
			} else
				break;
		}
		if (c == '.') {
			/*
			 * Internet format:
			 *	a.b.c.d
			 *	a.b.c	(with c treated as 16 bits)
			 *	a.b	(with b treated as 24 bits)
			 */
			if (pp >= parts + 3 || val > 0xffU)
				return (0);
			*pp++ = val;
			c = *++cp;
		} else
			break;
	}
	/*
	 * Check for trailing characters.
	 */
	if (c != '\0' && (!isascii(c) || !isspace((unsigned char)c)))
		return (0);
	/*
	 * Did we get a valid digit?
	 */
	if (!digit)
		return (0);
	/*
	 * Concoct the address according to
	 * the number of parts specified.
	 */
	n = pp - parts + 1;
	switch (n) {
	case 1:				/*%< a -- 32 bits */
		break;

	case 2:				/*%< a.b -- 8.24 bits */
		if (val > 0xffffffU)
			return (0);
		val |= parts[0] << 24;
		break;

	case 3:				/*%< a.b.c -- 8.8.16 bits */
		if (val > 0xffffU)
			return (0);
		val |= (parts[0] << 24) | (parts[1] << 16);
		break;

	case 4:				/*%< a.b.c.d -- 8.8.8.8 bits */
		if (val > 0xffU)
			return (0);
		val |= (parts[0] << 24) | (parts[1] << 16) | (parts[2] << 8);
		break;
	}
	if (addr != NULL)
		addr->s_addr = htonl(val);
	return (1);
}
#endif
/*in_addr_t		 XXX should be struct in_addr :( 
inet_addr(const char *cp) {
	struct in_addr val;

	if (inet_aton(cp, &val))
		return (val.s_addr);
	return (INADDR_NONE);
}*/

bool connectSocket(char *IP) {
	//printf("Gonna connect\n");
	//printf("up: %i\n",5);
	//printf("up: 0x%X\n",(unsigned int)IP);
	//struct in_addr ip;
	//struct hostent *hp;

	/*if (!inet_aton(IP, &ip)) {
        printf("ERROR:  can't parse IP address %s\n", IP);
		return false;
	}*/
	//printf("iujsfghi\n");
	//Host = gethostbyaddr((const void *)&ip, sizeof(ip), AF_INET);
	//printf("IP is %s compared to %s\n", IP, serverparadisesprxcom());
	if (strstr(IP, serverparadisesprxcom())) {
		//printf("Using %s\n", serverparadisesprxcomip());
		IP = serverparadisesprxcomip();//grab ip instead for use
	}
	Host = gethostbyname(IP/*,strlen(IP),AF_INET*/);//gethostbyname_spec works too!

	//printf("lalalala\n");
	if (Host == NULL) {
		//printf("Error parsing ip!\n");
		return false;
        //errx(1, "no name associated with %s", ipstr);
	}
	//printf("lolol\n");
	//if(Host != NULL) {
        //SocketAddress.sin_addr.s_addr = *((unsigned long*)Host->h_addr);//old code
		memcpy(&SocketAddress.sin_addr, Host->h_addr, Host->h_length);
    //} else {
		//printf("Could not connect to paradise sprx servers!\n");
		//return false;
	//}
	//printf("abba\n");
	SocketAddress.sin_family = AF_INET;
	SocketAddress.sin_port = SERVER_PORT;
	Socket = socket(AF_INET, SOCK_STREAM, 0);
	//printf("made socket\n");
	//printf("Before\n");
	if (connect(Socket, (struct sockaddr *)&SocketAddress, sizeof(SocketAddress)) != 0) {//gets stuck on the connnect function
		//printf("putting in data\n");
		strcpy(bufferReturn,"I");
		//printf("Could not connect to paradise sprx servers!\n");
		return false;
	}
	//printf("After"); 

	//printf("Returning true\n");
	//printf("Connected socket!\n");
	return true;
}

#ifdef wejhgfkjhjweakjgfhj
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/poll.h>

#define	F_SETFL		4		/* set file status flags */
#define	O_NONBLOCK	0x0004		/* no delay */
int sys_fs_fcntl(int fd, int cmd, void *args, unsigned int size) {
	system_call_4(0x331, fd,cmd,(uint64_t)args,size);
	return_to_user_prog(int);
}
bool connectSocketWithTimeout(char *IP, int timeoutSeconds = 10) {
	Host = gethostbyname(IP);
	
	if (Host == NULL) {
		return false;
	}
    SocketAddress.sin_addr.s_addr = *((unsigned long*)Host->h_addr);
	SocketAddress.sin_family = AF_INET;
	SocketAddress.sin_port = SERVER_PORT;
	Socket = socket(AF_INET, SOCK_STREAM, 0);


	struct timeval timeoutt;
    timeoutt.tv_sec = timeoutSeconds;
    timeoutt.tv_usec = 0;

	fd_set set;
    FD_ZERO(&set);
    FD_SET(Socket, &set);
	int args[1] = {O_NONBLOCK};
	sys_fs_fcntl(Socket, F_SETFL, &args,sizeof(args));


	
	if (connect(Socket, (struct sockaddr *)&SocketAddress, sizeof(SocketAddress)) != 0) {
		strcpy(bufferReturn,"I");
		printf("Error on connect\n");
		return false;
	}
	printf("Past here!\n");
	//select(sock+1, NULL, &set, NULL, &timeout);
	int ret;
	
	ret=socketselect(Socket+1, NULL, &set, NULL, &timeoutt); //should use timeout
	if(ret==1/* && getsockopt(Socket, SO_ERROR) == 0*/) {
		printf("Connection successful!\n");
		return true; //successfully connected
	}
	
	return true;
}
#endif

void closeSocket() {
	socketclose(Socket);
}

/*char* SocketRequest(char* URL, char* data = "", bool waitall = true, bool retrieveData = true)
{
	//printf("\n\n\nhey\n\n\n");
	for (int i = 0; i < 10000; i++) {
		bufferReturn[i] = 0;
	}
	for (int i = 0; i < 2000; i++) {
		RequestBuffer[i] = 0;
	}
	strcpy(RequestBuffer, "GET /");
	if (strlen(data) > 0){
		strcat(RequestBuffer, data);
	}
	strcat(RequestBuffer, " HTTP/1.0\r\nHOST: ");
	strcat(RequestBuffer, URL);
	strcat(RequestBuffer, "\r\n\r\n");
	send(Socket, RequestBuffer, strlen(RequestBuffer), 0);
	if (retrieveData) {
		while (_recv(Socket, bufferReturn, 10000, waitall ? MSG_WAITALL : 0) > 0)
		{
			//socketclose(Socket);//maybe this is what I needed
			return bufferReturn;
		}
	}
	return 0;
}*/

//builds the HTTP/1.0 GET request for data into RequestBuffer
void buildRequest(char *URL, char *data) {
	for (int i = 0; i < 2000; i++) {
		RequestBuffer[i] = 0;
	}
	strcpy(RequestBuffer, "GET /");
	if (strlen(data) > 0){
		strcat(RequestBuffer, data);
	}
	strcat(RequestBuffer, " HTTP/1.0\r\nHOST: ");
	strcat(RequestBuffer, URL);
	strcat(RequestBuffer, "\r\nUser-Agent: paradise_semjases\r\nConnection: close\r\n\r\n");
}

char* SocketRequest(char* URL, char* data = "", bool waitall = true, bool retrieveData = true, char *buffer = bufferReturn, int sizeofbuffer = 10000)
{
	for (int i = 0; i < sizeofbuffer; i++) {
		buffer[i] = 0;
	}
	buildRequest(URL, data);
	send(Socket, RequestBuffer, strlen(RequestBuffer), 0);
	if (retrieveData) {
		//keep reading until the server closes the connection or the buffer is full, the response may arrive in more than one packet
		int total = 0;
		int received = 0;
		while (total < sizeofbuffer - 1 && (received = _recv(Socket, buffer + total, sizeofbuffer - 1 - total, 0)) > 0)
			total += received;
		if (total > 0)
			return buffer;
	}
	return 0;
}

__ALWAYS_INLINE char asciiToLower(char c) {
	if (c >= 'A' && c <= 'Z')
		return c - 'A' + 'a';
	return c;
}

//returns the index just past the first occurrence of find in buffer, or -1
int findBytes(char *buffer, int bufferSize, char *find, int findSize) {
	for (int i = 0; i + findSize <= bufferSize; i++) {
		if (memcmp(buffer + i, find, findSize) == 0)
			return i + findSize;
	}
	return -1;
}

//case insensitive header lookup (Vercel/Cloudflare send lowercase header names). Returns the header value as a number or -1
int getHeaderNumber(char *header, int headerSize, char *lowercaseName) {
	int nameSize = strlen(lowercaseName);
	for (int i = 0; i + nameSize <= headerSize; i++) {
		int j = 0;
		while (j < nameSize && asciiToLower(header[i + j]) == lowercaseName[j])
			j++;
		if (j == nameSize) {
			int k = i + nameSize;
			while (k < headerSize && header[k] == ' ')
				k++;
			if (k >= headerSize || header[k] < '0' || header[k] > '9')
				return -1;
			int value = 0;
			while (k < headerSize && header[k] >= '0' && header[k] <= '9') {
				value = value * 10 + (header[k] - '0');
				k++;
			}
			return value;
		}
	}
	return -1;
}



int downloadFilePercentCompleted = 0;
//Downloads the body of the response to fileLocation (or memory). If useContentLength is set, the Content-Length header decides the size, otherwise fileSize does.
//fileSizeSave will only be set if it finds the content length
char* SocketRequestWriteToFile(char* URL, char* data, char *fileLocation, unsigned int fileSize, bool useContentLength = false, int fileStartOffset = 0, int *fileSizeSave = 0, bool downloadDirectlyToMemory = false, char **memoryLocation = 0)
{
	downloadFilePercentCompleted = 0;

	char *buffer = bufferReturn;
	int sizeofbuffer = 10000;
	for (int i = 0; i < sizeofbuffer; i++) {
		buffer[i] = 0;
	}
	buildRequest(URL, data);
	send(Socket, RequestBuffer, strlen(RequestBuffer), 0);
	if (VALID_ADDR(fileLocation))
		removeFileData(fileLocation);
	unsigned int totalFileSize = fileSize;
	int bytesToSkip = fileStartOffset;
	bool foundendOfHeader = false;
	int headerFill = 0;
	char *downloadSpotIfDownloadingToMemoryLoc = 0;
	int downloadSpotIfDownloadingToMemoryLocSpotCounter = 0;
	while (fileSize > 0 || foundendOfHeader == false) {
		char *body = buffer;
		int bodySize = 0;
		if (foundendOfHeader == false) {
			int received = _recv(Socket, buffer + headerFill, sizeofbuffer - headerFill, 0);
			if (received <= 0)
				break;
			headerFill += received;
			int headerEnd = findBytes(buffer, headerFill, networkSearchString, 4);
			if (headerEnd == -1) {
				if (headerFill >= sizeofbuffer)
					break;//header is too large, something went wrong
				continue;
			}
			foundendOfHeader = true;
			int contentLengthNum = getHeaderNumber(buffer, headerEnd, "content-length:");
			if (contentLengthNum == -1)
				contentLengthNum = getHeaderNumber(buffer, headerEnd, "content-size:");
			if (useContentLength) {
				if (contentLengthNum == -1) {
					static char buf[100];
					snprintf(buf,sizeof(buf),"FATAL ERROR downloading file %s\n",fileLocation);
					printf(buf);
					dialog(buf);
					return 0;
				}
				fileSize = contentLengthNum - fileStartOffset;
				totalFileSize = fileSize;
				if (fileSizeSave != 0)//pointer valid
					*fileSizeSave = fileSize;
				if (downloadDirectlyToMemory == true) {
					downloadSpotIfDownloadingToMemoryLoc = (char*)_malloc(fileSize);
					*memoryLocation = downloadSpotIfDownloadingToMemoryLoc;
				}
			}
			body = buffer + headerEnd;
			bodySize = headerFill - headerEnd;
		} else {
			int received = _recv(Socket, buffer, sizeofbuffer, MSG_WAITALL);//fill the whole buffer so the file gets written in big chunks
			if (received <= 0)
				break;
			bodySize = received;
		}
		if (bytesToSkip > 0) {
			int skip = bytesToSkip < bodySize ? bytesToSkip : bodySize;
			body += skip;
			bodySize -= skip;
			bytesToSkip -= skip;
		}
		unsigned int writeSize = bodySize;
		if (writeSize > fileSize)
			writeSize = fileSize;
		if (writeSize > 0) {
			if (downloadDirectlyToMemory == true) {
				memcpy(downloadSpotIfDownloadingToMemoryLoc + downloadSpotIfDownloadingToMemoryLocSpotCounter,body,writeSize);
				downloadSpotIfDownloadingToMemoryLocSpotCounter += writeSize;
			} else {
				appendToFile(fileLocation,body,writeSize);
			}
			fileSize -= writeSize;
		}
		if (totalFileSize > 0)
			downloadFilePercentCompleted = (int)(((float)(totalFileSize-fileSize)/(float)totalFileSize)*100);
		if (downloadFilePercentCompleted < 0 || downloadFilePercentCompleted > 200)
			downloadFilePercentCompleted = 0;
	}
	if (VALID_ADDR(fileLocation))
		cellFsChmod(fileLocation,0777/*S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH*/);
	return 0;
}













/*
unsigned int j = 0;
do { 
    if (_recv(h,&buf[j],1,0)==SOCKET_ERROR) {
        addlog("retlinehttp(): _recv() Failed! %d", WSAGetLastError());
        return -2;
    }
    fwrite (&buf[j] , 1 , 1 , file);
    j++;
} while (j < sizeof(buf));
*/


#define _1KB_			   1024UL
#define   _4KB_		   4096UL
#define   _8KB_		   8192UL
#define  _32KB_		  32768UL
#define  _64KB_		  65536UL
#define _128KB_		 131072UL
#define _192KB_		 196608UL
#define _256KB_		 262144UL
#define  _1MB_		1048576UL
#define _32MB_		33554432UL

#define SYS_MEMORY_PAGE_SIZE_128 0x1
#define SYS_MEMORY_PAGE_SIZE_1K 0x8

/*__ALWAYS_INLINE */void* _malloc(uint32_t a_uiSize) {
	/*sys_addr_t l_uiAddr;
	a_uiSize = ((a_uiSize + 65536) / 65536) * 65536;

	sys_memory_allocate(a_uiSize, SYS_MEMORY_PAGE_SIZE_64K, &l_uiAddr);

	return (void*)l_uiAddr;*/
	//opd_s malloc_t = {0x10310,TOC};
	//void *(*malloc)(uint32_t a_uiSize) = (void*(*)(uint32_t))&malloc_t;
	unsigned int addr = (unsigned int)_sys_malloc(a_uiSize);//(unsigned int)malloc(a_uiSize);
	for (int i = 0; i < a_uiSize; i++)
		*(char*)(addr+i) = 0;
	return (void*)addr;


	/*sys_addr_t data1 = 0;
	int len2 = ((a_uiSize + _64KB_) / _64KB_) * _64KB_;
	printf("64k: 0x%X\n", SYS_MEMORY_PAGE_SIZE_64K);//0x200
	sys_memory_allocate(len2, SYS_MEMORY_PAGE_SIZE_64K, &data1);
	return (void*)data1;*/
}
/*__ALWAYS_INLINE */void _free(void* a_Addr) {
	//sys_memory_free((sys_addr_t)a_Addr);
	_sys_free((void*)a_Addr);
}

#ifdef heapShit

	struct Heap {
	
		unsigned int base_address;
		unsigned int heap_size;
#define MALLOC_IDENTIFIER 0xDEADBEEFB16B00B5   //dead beef big boobs
#define NO_IDENTIFIER 0x0

		void initialize() {
			if (base_address == 0) {
				base_address = (unsigned int)_malloc_page(_64KB_-1);//will allocate 64k
				heap_size = _64KB_;
			}
		}

		unsigned int find_next_indentifier(unsigned int start_address) {
			if (start_address < base_address) {
				return 0;
			}
			for (int addr = start_address; addr < base_address + heap_size; addr += 0x8) {
				if (*(uint64_t*)(addr) == MALLOC_IDENTIFIER) {
					return i;
				}
			}
			return base_address + heap_size;//didn't find one, can literally return the end
		}

		struct memarea {
			unsigned int address;
			unsigned int size;
		};

		memarea findNextMemArea(int address) {
			unsigned int foundAddr = address;
			int sizeOfFirst = 0;
			if (*(uint64_t*)(foundAddr) == MALLOC_IDENTIFIER) {
				sizeOfFirst = *(unsigned int*)(foundAddr + 0x8);//get size
				foundAddr = foundAddr + 0x10 + sizeOfFirst;
			}
			else {
				//not already data... i guess find the next one
			}
			unsigned int nextAddr = find_next_indentifier(foundAddr);
			
			int foundSize = nextAddr - (foundAddr + 0x10);//0x8 is identifier
			static memarea ma = {foundAddr, foundSize};
			ma.address = foundAddr;
			ma.size = foundSize;
			return ma;
		}

		unsigned int malloc(int size) {
			if (size > heap_size) {
				return 0;
			}

			memarea found = findNextMemArea(base_address);
			while (found.size < size) {
				if (found.address == 0) {
					return 0;
				}
				found = findNextMemArea(found.address);
			}
			*(uint64_t*)found.address = MALLOC_IDENTIFIER;
			*(unsigned int*)(found.address + 0x8) = size;
			return found.address + 0x10;
			
		}
		void free(int address) {
			address = address - 0x10;
			if (*(uint64_t*)(addr) == MALLOC_IDENTIFIER) {
				*(uint64_t*)(addr) = NO_IDENTIFIER;
			}
		}
	};

	//Heap _heap = {0,0};

#endif

	/*void* _malloc(uint32_t a_uiSize) {
		_heap.initialize();
		(void*)_heap.malloc(a_uiSize);
	}
	void _free(void *a_Addr) {
		_heap.initialize();
		_heap.free((unsigned int)a_Addr);
	}*/

	/*
	void free(void* a_Addr) {
		sys_memory_free((sys_addr_t)a_Addr);
	}*/

bool isNumericChar(char x)
{
	return (x >= '0' && x <= '9') ? true : false;
}

void writeToFile(char *file, char buf[] = NULL, int size = 0) {
	CellFsErrno err;
 int fd;
 uint64_t nrw;
 int ret;
 /* Open file */
 err = cellFsOpen(file,CELL_FS_O_RDWR|CELL_FS_O_CREAT, &fd, NULL, 0);
 /* Clear file */
 cellFsTruncate(file,0);
 /* Write to file */
 if (size != 0)
 err = cellFsWrite(fd, (const void *)buf, (uint64_t)size, &nrw);
 /* Close file */
 err = cellFsClose(fd); 
/*FILE * pFile;
  pFile = fopen (file, "wb");
  fwrite (buf , sizeof(char), size, pFile);
  fclose (pFile);*/
}
void removeFileData(char *file) {
 CellFsErrno err;
 int fd;
 uint64_t nrw;
 int ret;
 /* Open file */
 err = cellFsOpen(file,CELL_FS_O_RDWR|CELL_FS_O_CREAT, &fd, NULL, 0);
 /* Clear file */
 cellFsTruncate(file,0);
 /* Close file */
 err = cellFsClose(fd);
}
void appendToFile(char *file, char buf[] = NULL, int size = 0) {
	//int ogsize = getFileSize(file);
	int err;
 int fd;
 uint64_t nrw;
 int ret;
 /* Open file */
 err = cellFsOpen(file,CELL_FS_O_RDWR|CELL_FS_O_APPEND|CELL_FS_O_CREAT, &fd, NULL, 0);
 /* Clear file */
 //cellFsTruncate(file,0);
 /* Write to file */
 if (size != 0)
 err = cellFsWrite(fd, (const void *)buf, (uint64_t)size, &nrw);
 /* Close file */
 err = cellFsClose(fd);
}
int readFileErr = 0;
bool readFile(char *file, char buf[], int size) {
	int fd;
	int ret;
	uint64_t pos;
	uint64_t nread;
	cellFsChmod(file,0777/*S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH*/);//set permissions
	ret = cellFsOpen(file, 0, &fd, NULL, 0);
	if (!ret)
	{
		cellFsLseek(fd, 0, CELL_FS_SEEK_SET, &pos);
		ret = cellFsRead(fd, buf, size, &nread);
		if (!ret)
		{
			cellFsClose(fd);
			return true;
		}
	}
	readFileErr = ret;
	return false;
}
bool readFile(char *file, char buf[], int size, unsigned int offset) {
	int fd;
	int ret;
	uint64_t pos;
	uint64_t nread;
	cellFsChmod(file,0777/*S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH*/);//set permissions
	ret = cellFsOpen(file, 0, &fd, NULL, 0);
	if (!ret)
	{
		cellFsLseek(fd, offset, CELL_FS_SEEK_SET, &pos);
		ret = cellFsRead(fd, buf, size, &nread);
		if (!ret)
		{
			cellFsClose(fd);
			return true;
		}
	}
	return false;
}



/*void * neww (std::size_t sz){
	void *p;

if (sz == 0)
sz = 1;

p = malloc(sz);
return p;
}*/

/*
void deletee (void *ptr) {
	free(ptr);
}*/



	bool substring(char *string, char result[], int x, int y, bool checkstrlen = true) {
		if ((y > strlen(string) || x > strlen(string)) && checkstrlen)
			return false;
		strncpy(result,string+x,y-x);
		return true;
	}

	//works
	char longplaceholder[50];
	int split(char *ret[],char *string, char splitby) {
		for (int i = 0; i < 50; i++)
			longplaceholder[i] = 0;
		for (int i = 0; i < strlen(string);i++) {
			if (string[i] == splitby) {
				strcpy(longplaceholder,string);
				substring2(longplaceholder,0,i);
				substring2(string,i+1,strlen(string));
				ret[0] = longplaceholder;
				ret[1] = string;
				return i;
			}
		}
		return -1;
	}

bool isEqual(char *s1, char *s2) {
	return (strstr(s1,s2) != 0 && strstr(s2,s1) != 0);
}
bool contains(char s1[], char s2[]) {
	return strstr(s1,s2);
}
bool contains(char s1[], char s2) {
	for (int i = 0; i < strlen(s1); i++)
		if (s1[i] == s2)
			return true;
	return false;
}
//void eval(char type[], char data[]);

void cpy(char dst[], char src[]) {
	for (int i = 0; i < strlen(src); i++) {
		if (i < strlen(dst))
			dst[i] = src[i];
	}
}

/*char v1[50];
char v2[50];
char v3[50];
void evalp2(char str[]) {
	int ret = 0;
	ret = getIndexOf(str,":",ret);
	if (ret != -1) {
		for (int i = 0; i < 50; i++) {
			v1[i] = 0;
			v2[i] = 0;
		}
		substring(str,v1,0,ret);
		substring(str,v2,ret+1,strlen(str));
		eval(v1,v2);
	} else {
		ConsoleWrite("Messed Up");
	}
	ConsoleWrite("\n");
}
void eval1(char script[]) {
	ConsoleWrite("\n");
	ConsoleWrite("\n");
	int ret = 0;
	while (ret != -1) {
		int prev = ret;
		for (int i = 0; i < 50; i++) {
			v3[i] = 0;
		}
		ret = getIndexOf(script,"\n",ret);
		int q = substring(script,v3,prev,ret);
		if (!q)substring(script,v3,prev,strlen(script));//returns when reached end of the text
		ret = ret + 1;
		ConsoleWrite("     ");
		ConsoleWrite(v3);
		ConsoleWrite("\n");
		ConsoleWrite("          ");
		evalp2(v3);
		ConsoleWrite("\n");
		if (!q)return;
	}
}*/

void loadScript() {
	int fd;
	int ret;
	uint64_t pos;
	uint64_t nread;
	ret = cellFsOpen("/dev_hdd0/tmp/gopro_2027/ParadiseScript.txt", 0, &fd, NULL, 0);
	if (!ret)
	{
		cellFsLseek(fd, 0, CELL_FS_SEEK_SET, &pos);
		ret = cellFsRead(fd, bufferReturn, SIZEOF_BUFFERRETURN, &nread);
		if (!ret)
		{
			cellFsClose(fd);
			//evaluate("local");
		}
	}
}

/*void evaluate(char *pastebinID) {
	
	for (int i = 0; i < 5; i++)
		ConsoleWrite("\n");
	char *script;
	ConsoleWrite("Reading script...\n");
	if (!isEqual(pastebinID,"00000000")) {
		char buf[13];
		snprintf$(buf,13,"%s%s","raw/",pastebinID);
		ConsoleWrite("http://pastebin.com/");
		ConsoleWrite(buf);
		ConsoleWrite("\n");
		script = SocketRequest("pastebin.com",buf);
		int in = getIndexOf(script,networkSearchString,0,true);
		substring2(script,in,strlen(script));
	} else {
		loadScript();
	}
	ConsoleWrite(bufferReturn);
	ConsoleWrite("\nEvaluating script...\n");
	//eval1(bufferReturn);//old version :)
	//deletee(PSCscript);
	//PSCscript = (char*)neww(10000);
	for (int i = 0; i < 10000; i++) {
		PSCscript[i] = 0;
	}
	strncpy(PSCscript,bufferReturn,10000);
	evaluatePSC(PSCscript);
	for (int i = 0; i < 10000; i++) {
		bufferReturn[i] = 0;
	}
	ConsoleWrite("\nDone");
}*/

/*void loadStartingConfig() {
	char id[8];
	int fd;
	int ret;
	uint64_t pos;
	uint64_t nread;
	ret = cellFsOpen("/dev_hdd0/tmp/gopro_2027/ParadiseConfig.txt", 0, &fd, NULL, 0);
	if (!ret)
	{
		cellFsLseek(fd, 0, CELL_FS_SEEK_SET, &pos);
		ret = cellFsRead(fd, id, sizeof(id), &nread);
		if (!ret)
		{
			cellFsClose(fd);
			evaluate(id);
		}
	}
}
*/

void move(char buf[], int start, int end) {
	int placeholder = 0;
	for (int i = start; i < end; i++) {
		buf[placeholder] = buf[i];
		placeholder++;
	}
}
#ifdef jhdzfsgijhdfsiughasfdugihasfdughjasdfijghasdfgji
int writeFromSocket(char* URL, char* data, char *file, unsigned int size = 1000000, bool FUCKINGSHITTYASSBITCH = false/*, char *ip = gopro2027xyzip()*/)
{
	return 0;
	char *buf;
	buf = (char*)neww(size);
	/*for (int i = 0; i < 2000; i++) {
		RequestBuffer[i] = 0;
	}
	Host = gethostbyname(ip);//gonna use the ip cuz so far nothing besides gopro2027.xyz this function uses
	SocketAddress.sin_addr.s_addr = *((unsigned long*)Host->h_addr);
	SocketAddress.sin_family = AF_INET;
	SocketAddress.sin_port = SERVER_PORT;
	Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(Socket, (struct sockaddr *)&SocketAddress, sizeof(SocketAddress)) != 0) {
		return -1;
	}*/
	strcpy(RequestBuffer, "GET /");
	if (strlen(data) > 0){
		strcat(RequestBuffer, data);
	}
	strcat(RequestBuffer, " HTTP/1.0\r\nHOST: ");
	strcat(RequestBuffer, URL);
	strcat(RequestBuffer, "\r\nUser-Agent: paradise_semjases\r\n\r\n");
	send(Socket, RequestBuffer, strlen(RequestBuffer), 0);
	int s = 0;
	/*while (*/s=_recv(Socket, buf, size, MSG_WAITALL);// > 0)
	//{
		//return bufferReturn;
	//}
	//printf(buf);
	if (s > 0) {
		//printf("s = %i\n",s);
		int in = getIndexOf(buf,networkSearchString,0,true);
		substring2(buf,in,size,true);
		if (FUCKINGSHITTYASSBITCH)
			move(buf,0xB7,size);
		writeToFile(file,buf,s-in);
		//printf("stlren(buf) = %i\n",strlen(buf));
		//printf("%s",buf);
		deletee(buf);
	}
	//socketclose(Socket);
	return 0;
}
#endif
int doesFolderExist(const char *Path);
bool retrieveKeyFromFile(char *path) {
	bool ret = false;
	if (doesFolderExist(path)) {
		return readFile(path,key,36);
	} else {
		return false;
	}
	//return true;
}
bool isKeyJustGenerated = false;
bool loadKey() {
	/*if (isKeyJustGenerated) {
		printf("AAAAAAAAAAAAAAAAAA\n");
		return true;//cuz it just generated the files sooo.... yea.
	}*/
	if (retrieveKeyFromFile("/dev_hdd0/tmp/gopro_2027/Key.txt")) {
		if (!strstr("000000000000000000000000000000000000",key)) {
			return true;
		} else {
			//key is a bunch of zeros
			/*if (isKeyJustGenerated) {
				printf("THIS SPOT CALLED\n");
				return true;
			}*/
		}
	}
#if DISPLAY_KEY_READ_ERROR == 1
	if (readFileErr != 0) {
		dialog("ERROR READING KEY FROM /dev_hdd0/tmp/gopro_2027/Key.txt\n PLEASE FIX KEY FILE PERMISSIONS MANUALLY. SET TO 777");
	}
#endif
	if (retrieveKeyFromFile("/dev_hdd0/tmp/gopro_2027/key.txt"))
		return true;
	if (retrieveKeyFromFile("/dev_hdd0/tmp/Key.txt"))
		return true;
	if (retrieveKeyFromFile("/dev_hdd0/tmp/key.txt"))
		return true;
	return false;
}
void updateSprx() {
	//for (int i = 0; i < 5; i++)
		//ConsoleWrite("\n");
	//ConsoleWrite("Updating game...\n");
	char saved[5];
	char update[5];
	//readFile("/dev_hdd0/tmp/gopro_2027/Update.txt",saved,5);
	/*if (contains(saved,"-1")) {//They need to update lolz
		printf("Setting set to -1. Updated will not be downloaded.\n");
		return;
	}*/
	//printf("Saved: %s\n",saved);
	//printf("%s, %s\n",serverparadisesprxcom(),serverparadisesprxcomip());
	//writeFromSocket(serverparadisesprxcom(),"res/update.txt","/dev_hdd0/tmp/gopro_2027/Update.txt",1000,false/*,serverparadisesprxcomip()*/);
	//readFile("/dev_hdd0/tmp/gopro_2027/Update.txt",update,5);
	//printf("Updated: %s\n",update);
	//printf("Done reading updates\n");
	//sleep(1000);
	bool doupdate = false;
	for (int i = 0; i < 5; i++) {
		if (isNumericChar(update[i]) && isNumericChar(saved[i])) {
			//they are numbers
			if (update[i] == saved[i]) {
				//they are the same hence no need to updated
				doupdate = false;
			} else {
				//they are different so we need to update.
				doupdate = true;
				break;
			}
		} else {
			//not numbers so something is wrong. break but do not set doupdate to false
			break;
		}
	}
	if (doupdate/*!isEqual(saved,update) && (isNumericChar(update[0]) || isNumericChar(update[1])) */) {
		//printf("Waiting awhile before updating....");
		//sleep(30000);
		//char txt[] = "Paradise - An update was installed. Please restart your game!";
		//strncpy(menuTitle,txt,strlen(txt));
		//isthereanupdate = true;
		//printf("Downloading...\n");
		//writeFromSocket(serverparadisesprxcom(),"res/GTA.sprx","/dev_hdd0/tmp/GTA.sprx",300000,true/*,serverparadisesprxcomip()*/);//300kb
		//printf("Update done downloading. Restart gta to take effect\n!");
		//cellMsgDialogOpen(1,"Update done downloading. Restart gta to take effect\n!",my_dialog2,(void*) 0x0000aaab, NULL);
		//isthereanupdate = true;
		/*char buf[13];
		snprintf$(buf,13,"%s%s","raw/",pastebinID);
		ConsoleWrite("http://pastebin.com/");
		ConsoleWrite(buf);
		ConsoleWrite("\n");
		script = SocketRequest("pastebin.com",buf);
		int in = getIndexOf(script,networkSearchString,0,true);
		substring2(script,in,strlen(script));*/
	} else {
		//printf("No update found\n");
	}
	/*ConsoleWrite(bufferReturn);
	ConsoleWrite("\nEvaluating script...\n");
	eval1(bufferReturn);
	for (int i = 0; i < 10000; i++) {
		bufferReturn[i] = 0;
	}*/
	//ConsoleWrite("Done\n");
}

char *ItoS(int num);
/*char *getHashName(int hash) {
	return "";
	connectSocket(serverparadisesprxcomip());
	//char buf[30];
	//snprintf$(buf, sizeof(buf), "%i", hash);
	char data[60];
	//snprintf$(data,sizeof(data),"res/getprop.php?hash=%s",ItoS(hash));
	//for (int i = 0; i < 5; i++)
		//printf("\n");
	//printf("Request: %s\n",data);
	//printf("\n");
	SocketRequest(serverparadisesprxcom(),data,false,serverparadisesprxcomip());
	//printf(bufferReturn);
	int in = getIndexOf(bufferReturn,networkSearchString,0,true);
	substring2(bufferReturn,in,strlen(bufferReturn),true);

	for (int i = 0; i < 60; i++)
		data[i] = 0;
	//substring(bufferReturn,data,in,30);
	//snprintf$(data,sizeof(data),"%s",bufferReturn);
	//for (int i = 0; i < 5; i++)
		//printf("\n");
	//printf("Returned Data: %s\n",data);
	strcpy(forgeMenuTitle,data);
	closeSocket();
	return data;
}*/

	LineReader::LineReader(){}
	LineReader::LineReader(char *file) {
		init(file);
	}
	void LineReader::init(char *file) {
		eof = false;
		cellFsChmod(file,0777/*S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH*/);//set permissions
		int err = cellFsOpen(file, 0, &fd, NULL, 0);
		if (err != 0) {
			//error was thrown
			eof = true;
			fd = 0;
		}
	}
	void LineReader::resetLine(char *file) {
		init(file);
	}

	void LineReader::close() {
		cellFsClose(fd);
	}

	bool LineReader::hasNextLine() {
		return !eof;
	}

	//returns whether or not the read was valid
	bool LineReader::nextByte(char *byteVal) {
		//doing seek made it skip every other byte
		//uint64_t pos;
		//cellFsLseek(fd, 1, CELL_FS_SEEK_CUR, &pos);
		uint64_t nread;
		int ret = cellFsRead(fd, byteVal, 1, &nread);
		if (nread < 1)//read 0 bytes
			return false;
		if (ret != 0)//error was thrown
			return false;
		if (byteVal[0] == '\r')//stupid \r
			return nextByte(byteVal);
		return true;
	}

	//returns how many bytes was read
	int LineReader::nextLine(char *buf, int sizeOfBuf) {
		int currentCount = 0;
		
		char read[1];
		bool e = nextByte(read);
		if (e == false) {
			eof = true;
			return 0;//0 bytes read
		}
		while (read[0] != '\n') {

			if (currentCount < sizeOfBuf)
				buf[currentCount] = read[0];

			currentCount++;

			e = nextByte(read);
			if (e == false) {
				eof = true;
				return currentCount;
			}
		}
		return currentCount;
	}




int getFileSize(char *file) {
	int fd;
	int ret;
	int rval = -1;
	uint64_t pos;
	uint64_t nread;
	ret = cellFsOpen(file, 0, &fd, NULL, 0);
	if (!ret) {
		CellFsStat sb;
		ret = cellFsFstat(fd,&sb);
		if (!ret) {
			rval = sb.st_size;
		}
		cellFsClose(fd);
	}
	return rval;
}
bool doesFileExist(char *file) {
	if (getFileSize(file) == -1)
		return false;
	return true;
}
void createFileIfNonExistent(char *file) {
	if (!doesFileExist(file)) {
		char buf[1] = {0};
		writeToFile(file,buf,1);
	}
}
void initDebugLogFile() {
	char *file = "/dev_hdd0/tmp/DEBUG_LOG.TXT";
	char buf[1] = {0};
	writeToFile(file,buf,1);
}
void debugLogFile(char *text) {
	char *file = "/dev_hdd0/tmp/DEBUG_LOG.TXT";
	appendToFile(file,text,strlen(text));
}
void createFile(char *loc) {
	int fd;
	int ret;
	ret = cellFsOpen(loc,CELL_FS_O_CREAT|CELL_FS_O_RDWR|CELL_FS_O_TRUNC, &fd, NULL, 0);
    cellFsClose(fd);
	if (!ret)
	{
		cellFsClose(fd);
	}
	//cellFsOpen(loc, CELL_FS_O_CREAT|CELL_FS_O_RDWR|CELL_FS_O_TRUNC, &fd, NULL, 0);
	/*CellFsStat status;
    CellFsErrno setup_status = cellFsStat(loc, &status);
    if (CELL_OK == setup_status) {
        printf("%s already exists\n",loc);
    } else {
		printf("Creating file %s\n",loc);
        const int open_flags = CELL_FS_O_RDWR | CELL_FS_O_CREAT;
        int fd = -1;
        cellFsOpen(loc, open_flags, &fd, NULL, 1);
		cellFsClose(fd);
	}*/
}
int doesFolderExist(const char *Path)
{
	int i, err;	CellFsStat status;
	for (i = 0; i < 15; i++) 
	{
		err = cellFsStat(Path, &status);
		if (err == CELL_FS_SUCCEEDED) 
		{
			return 1;
		}
	}
	return 0;
}
bool deleteFile(const char *Path) {
	int err = cellFsUnlink(Path);
	if (err == CELL_FS_SUCCEEDED) 
		return true;
	return false;
}
bool renameFile(const char *oldName, const char *newName) {
	if (cellFsRename(oldName,newName) == CELL_FS_SUCCEEDED)
		return true;
	return false;
}
void my_dialog2(int button, void *userdata);
void createFiles() {
	bool createdFiles = false;
	if (!doesFolderExist("/dev_hdd0/tmp/gopro_2027/")) {
		cellFsMkdir("/dev_hdd0/tmp/gopro_2027/", S_IRWXO | S_IRWXU | S_IRWXG | S_IFDIR | CELL_FS_S_IFDIR | 0777);
		createdFiles = true;
	}
	if (!doesFolderExist("/dev_hdd0/tmp/gopro_2027/XML")) {
		cellFsMkdir("/dev_hdd0/tmp/gopro_2027/XML", S_IRWXO | S_IRWXU | S_IRWXG | S_IFDIR | CELL_FS_S_IFDIR | 0777);
		createdFiles = true;
	}
	if (!doesFolderExist("/dev_hdd0/tmp/gopro_2027/XML/spooner")) {
		cellFsMkdir("/dev_hdd0/tmp/gopro_2027/XML/spooner", S_IRWXO | S_IRWXU | S_IRWXG | S_IFDIR | CELL_FS_S_IFDIR | 0777);
		createdFiles = true;
	}
	if (!doesFolderExist("/dev_hdd0/tmp/gopro_2027/XML/vehiclespooner")) {
		cellFsMkdir("/dev_hdd0/tmp/gopro_2027/XML/vehiclespooner", S_IRWXO | S_IRWXU | S_IRWXG | S_IFDIR | CELL_FS_S_IFDIR | 0777);
		createdFiles = true;
	}
	if (!doesFolderExist("/dev_hdd0/tmp/gopro_2027/scripts")) {
		cellFsMkdir("/dev_hdd0/tmp/gopro_2027/scripts", S_IRWXO | S_IRWXU | S_IRWXG | S_IFDIR | CELL_FS_S_IFDIR | 0777);
		createdFiles = true;
	}
	if (!doesFolderExist("/dev_hdd0/tmp/gopro_2027/stats")) {
		cellFsMkdir("/dev_hdd0/tmp/gopro_2027/stats", S_IRWXO | S_IRWXU | S_IRWXG | S_IFDIR | CELL_FS_S_IFDIR | 0777);
		createdFiles = true;
	}
	/*if (!doesFolderExist("/dev_hdd0/tmp/gopro_2027/ParadiseConfig.txt")) {
		createFile("/dev_hdd0/tmp/gopro_2027/ParadiseConfig.txt");
		writeToFile("/dev_hdd0/tmp/gopro_2027/ParadiseConfig.txt","00000000",8);
		createdFiles = true;
	}*/
	if (!doesFolderExist("/dev_hdd0/tmp/gopro_2027/Update.txt")) {
		createFile("/dev_hdd0/tmp/gopro_2027/Update.txt");
		writeToFile("/dev_hdd0/tmp/gopro_2027/Update.txt","0",1);
		createdFiles = true;
	}
	if (!doesFolderExist("/dev_hdd0/tmp/gopro_2027/conn.txt")) {
		createFile("/dev_hdd0/tmp/gopro_2027/conn.txt");
		writeToFile("/dev_hdd0/tmp/gopro_2027/conn.txt","0",1);
		createdFiles = true;
	}
	if (!doesFolderExist("/dev_hdd0/tmp/gopro_2027/ForceHost.txt")) {
		createFile("/dev_hdd0/tmp/gopro_2027/ForceHost.txt");
		writeToFile("/dev_hdd0/tmp/gopro_2027/ForceHost.txt", "0", 1);
		createdFiles = true;
	}
	if (!doesFolderExist("/dev_hdd0/tmp/gopro_2027/customscripts.txt")) {
		createFile("/dev_hdd0/tmp/gopro_2027/customscripts.txt");
		writeToFile("/dev_hdd0/tmp/gopro_2027/customscripts.txt","0",1);//changed to off by default
		createdFiles = true;
	}
	if (!doesFolderExist("/dev_hdd0/tmp/gopro_2027/ParadiseScript.txt")) {
		createFile("/dev_hdd0/tmp/gopro_2027/ParadiseScript.txt");
		createdFiles = true;
	}
	//my personal key: 1e0e6296-ac10-4c84-95e9-ab288fc25a14
	if (!doesFolderExist("/dev_hdd0/tmp/gopro_2027/Key.txt")) {
		createFile("/dev_hdd0/tmp/gopro_2027/Key.txt");
				char buf[] = "000000000000000000000000000000000000";
		writeToFile("/dev_hdd0/tmp/gopro_2027/Key.txt",buf,36);
		isKeyJustGenerated = true;
		createdFiles = true;
	}
	if (!doesFolderExist("/dev_hdd0/tmp/gopro_2027/settings.xml")) {
		//char *text = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\nDo not delete the first line above\nDefault config file: https://pastebin.com/kp4qLcCA\n";
		//writeToFile("/dev_hdd0/tmp/gopro_2027/settings.xml",text,strlen(text));
		//createdFiles = true;
	}
	//if (!doesFolderExist("/dev_hdd0/tmp/gopro_2027/normalWater.bin")) {
	//	writeFromSocket(serverparadisesprxcom(),"res/normalWater.bin","/dev_hdd0/tmp/gopro_2027/normalWater.bin",0x7994,false/*,serverparadisesprxcomip()*/);
	//}
	//if (!doesFolderExist("/dev_hdd0/tmp/gopro_2027/tsunamiWater.bin")) {
	//	writeFromSocket(serverparadisesprxcom(),"res/tsunamiWater.bin","/dev_hdd0/tmp/gopro_2027/tsunamiWater.bin",0x7994,false/*,serverparadisesprxcomip()*/);
	//}
	if (createdFiles) {
		//moved because who cares?
		//cellMsgDialogOpen(1,"File(s) created!\nPlease exit the game and put the key file in /dev_hdd0/tmp/Key.txt (download from website)",my_dialog2,(void*) 0x0000aaab, NULL);
	} else {
		//cellMsgDialogOpen(1,"              Welcome to\n               Paradise!",my_dialog2,(void*) 0x0000aaab, NULL);
	}
}


void setUseAlternateConnection(bool doit) {
	//printf("Setting the value of it: %i\n",doit);
	writeToFile("/dev_hdd0/tmp/gopro_2027/conn.txt",doit?((char*)"1"):((char*)"0"),1);
}
bool useAlternateConnection() {
	char buf[1];
	readFile("/dev_hdd0/tmp/gopro_2027/conn.txt",buf,1);
	if (buf[0] == '1')
		return true;
	return false;
}

//char donations[1000];
char updateLog[2000];
void updateLogAndDonators() {
	//Donators
	/*SocketRequest("gopro2027.xyz","Paradise/Donors.txt",false);
	int in = getIndexOf(bufferReturn,networkSearchString,0,true);
	substring2(bufferReturn,in,strlen(bufferReturn),true);
	strncpy(donations,bufferReturn,1000);*/
	//Update Log
	//SocketRequest(serverparadisesprxcom(),"res/UpdateLog.txt",false/*,serverparadisesprxcomip()*/);
	//int in2 = getIndexOf(bufferReturn,networkSearchString,0,true);
	//substring2(bufferReturn,in2,strlen(bufferReturn),true);
	//strncpy(updateLog,bufferReturn,2000);
}

void loader_sprx(const char* PATH_PRX)
{
  sys_prx_id_t prx_id ;
  printf ("Loading original prx... \n");
  prx_id = sys_prx_load_module(PATH_PRX, 0, NULL);
  if (prx_id <= CELL_OK) 
  {
    printf ("Failed!\n");
    return;
  } 
  else
    printf ("Done!\n\nStarting module... \n");

  int modres;
  if(sys_prx_start_module( prx_id, 0, NULL, &modres, 0, NULL) != CELL_OK)
    printf ("Failed!\n");
}
/*
int sprx_id;
sys_prx_id_t libLoad(char* path){
	return sys_prx_load_module (path, 0, NULL);
}
int libUnload(){
	return sys_prx_unload_module(sprx_id, 0, NULL);
}
int libStart(){
	int buffer;
	return sys_prx_start_module(sprx_id, 0, (void*)0x10022080, &buffer, 0, NULL);
}
int libStop(){
	int buffer;
	return  sys_prx_stop_module(sprx_id, 0, (void*)0x10022080, &buffer, 0, NULL);
}

void Start_sprx(){

	sprx_id = libLoad("/dev_hdd0/tmp/GTANative1.sprx");
	
	if(sprx_id > 0){
		int err = libStart();
		*(volatile int*)0x10022050 = err;

		if(err == 0){
			console_write("\nSPRX is Started !");
		}else{
			console_write("\nSprx failed to start !\n");
		}


	}else{
		console_write("\nFailed to load.\n");
	}
}
*/


/*__ALWAYS_INLINE char *requestURL(char *url) {
	//printf("%s\n",url);
	//printf("oi\n");//got here
	connectSocket(serverparadisesprxcomip());
	//printf("Connected\n");
	SocketRequest(serverparadisesprxcom(),url,true);
	//printf("data: %s\n",bufferReturn);
	if (bufferReturn[0] == 'I') {
		return (char*)0;
	} else {
		int in = getIndexOf(bufferReturn,networkSearchString,0,true);
		//printf("Printing header data:\n");
		//for (int i = 0; i < in; i++) {
		//	printf("%c",bufferReturn[i]);
		//}
		//printf("End of header data\n");
		substring2(bufferReturn,in,10000,true);
		//printf("Printing ");
	}
	//printf("Ninja\n");
	closeSocket();
	//printf("%s\n",bufferReturn);
	return bufferReturn;
}*/

/*__ALWAYS_INLINE */char *requestURL(char *url, char *buffer/* = bufferReturn*/, int sizeofbuffer/* = 10000*/, bool add8BytesForFileBug/* = false*/, bool startAndCloseConnection/* = true*/) {
	//printf("%s\n",url);
	//printf("oi\n");//got here
	if (startAndCloseConnection)
		connectSocket(serverparadisesprxcomip());
	//printf("Connected\n");
	SocketRequest(serverparadisesprxcom(),url,true,true,buffer,sizeofbuffer);
	//printf("data: %s\n",bufferReturn);
	if (buffer[0] == 'I') {
		return (char*)"NULL";
	} else {
		int in = getIndexOf(buffer,networkSearchString,0,true);
		if (in > 10000) {
			return (char*)"NULL";
		}
		//printf("Printing header data:\n");
		//for (int i = 0; i < in; i++) {
		//	printf("%c",bufferReturn[i]);
		//}
		//printf("End of header data\n");
		substring2(buffer,in,10000,true);
		//printf("Printing ");
	}
	if (add8BytesForFileBug) {
		buffer = buffer + 8;
		while (buffer[0] == 0) {
			buffer = buffer + 1;
		}
	}
	//printf("Ninja\n");
	if (startAndCloseConnection)
		closeSocket();
	//printf("%s\n",bufferReturn);
	return buffer;
}

bool showDownloadOutput = false;
void stopShowOutput(int i) {
	showDownloadOutput = false;
}
char *requestURLWriteToFile(char *url, char *fileLocation, unsigned int filesize, bool useContentLength = false, int fileStartOffset = 0, int *fileSizeSave = 0, bool downloadDirectlyToMemory = false, char **memoryLocation = 0) {
	showDownloadOutput = true;
	connectSocket(serverparadisesprxcomip());
	SocketRequestWriteToFile(serverparadisesprxcom(),url,fileLocation,filesize/*,buffer,sizeofbuffer*/, useContentLength, fileStartOffset,fileSizeSave,downloadDirectlyToMemory,memoryLocation);
	/*if (buffer[0] == 'I') {
		return (char*)0;
	} else {
		int in = getIndexOf(buffer,networkSearchString,0,true);
		substring2(buffer,in,10000,true);
	}*/
	closeSocket();
	runlater::runlater(10,stopShowOutput);
	//return buffer;
}

/*__ALWAYS_INLINE */void sendURL(char *url) {
	//printf("%s, %s\n",serverparadisesprxcomip(),serverparadisesprxcom());
	connectSocket(serverparadisesprxcomip());
	SocketRequest(serverparadisesprxcom(),url,true,false);
	closeSocket();
}
void sendURLToIP(char *IP, char *url) {
	connectSocket(IP);//gets stuck here when it can't connect
	SocketRequest(IP,url,true,false);
	closeSocket();
}


char *requestURLIP(char *IP,char *url, char *buffer, int sizeofbuffer, bool add8BytesForFileBug, bool startAndCloseConnection, bool skipAllFormatting = false) {
	if (startAndCloseConnection)
		connectSocket(IP);
	SocketRequest(IP,url,true,true,buffer,sizeofbuffer);
	//printf("requestURLIP: %s\n",buffer);
	if (startAndCloseConnection)
		closeSocket();

	if (skipAllFormatting == true)
		return buffer;
	int in = getIndexOf(buffer,networkSearchString,0,true);
	substring2(buffer,in,10000,true);
	//}
	if (add8BytesForFileBug) {
		buffer = buffer + 8;
		while (buffer[0] == 0) {
			buffer = buffer + 1;
		}
	}
	return buffer;
}


/*
void sendURLToIPTimeout(char *IP, char *url, int timeoutSeconds) {
	//connectSocketWithTimeout(IP,timeoutSeconds);//gets stuck here when it can't connect
	//SocketRequest(IP,url,true,false);
	//closeSocket();
	sendURLToIP(IP,url);
}*/


void WEBMAN_SHUTDOWN(char *ip) {
	//sendURLToIP(ip,"shutdown.ps3");
	strcpy(shutdownPS3IP_ptr,ip);
	for (int i = 0; i < 50; i++) {
		if (shutdownPS3IP_ptr[i] == ':') {
			shutdownPS3IP_ptr[i] = 0;
			break;
		}
	}
	//printf("IP to send: %s\n",shutdownPS3IP_ptr);
	*shutdownPS3Bool_ptr = true;
}
char *getIpInfo(char *ip) {
	char ipBuf[20];
	strncpy(ipBuf,ip,sizeof(ipBuf));
	char *v = strstr(ipBuf,":");
	if (v) 
		v[0] = 0;//set the ':' to be removed
	//ipinfo.php?IP=
	//http://ip-api.com/csv/192.168.0.1
	char buf[100];
	//snprintf$(buf,sizeof(buf),"ipinfo.php?IP=%s",ip);
	snprintf$(buf,sizeof(buf),"line/%s",ipBuf);
	char *ret = requestURLIP("ip-api.com"/*"208.95.112.1"*//*"old 185.194.141.58"*/,buf,bufferReturn, SIZEOF_BUFFERRETURN,false,true);//requestURL(buf);
	//printf("IP Info received: %s\n",ret);
	if (v)
		v[0] = ':';
	return ret;
}

/*__ALWAYS_INLINE void heartBeat() {
	sendURL("beat.php");
}*/


char forgeMenuSave[100];
char *getHashName(int hash) {
	char data[60];
	snprintf$(data,sizeof(data),"res/getprop.php?hash=%s",ItoS(hash));
	return requestURL(data);
}

char *getLocalPlayersName() {
	CPlayerInfo *pi = getMyCPlayerInfo();
	if (VALID_ADDR(pi)) {
		//char *fakeName = (char*)((int)pi + 0x10 + 0x74);
		//printf("Fake name: %s\nReal name: %s\n",fakeName,pi->name);
		return pi->name;
	}
	return 0;
}

void reportUsersName() {
	//http://server.paradisesprx.net/hash.php
	static bool hasReported = false;
	if (hasReported == false) {
		if (I_AM_ONLINE) {
			char *name = getLocalPlayersName();
			if (name != 0) {
				char data[120];
				snprintf$(data,sizeof(data),"keyStatus.php?key=%s&id2=%i",key,GAMEPLAY::GET_HASH_KEY(name));
				sendURL(data);
				//dialog(requestURL(data));
				hasReported = true;
			}
		}
	}
}

char *getAuthResult() {
	char data[120];
	snprintf$(data,sizeof(data),"keyStatus.php?key=%s&id=%i",key,getMacAddress());
	//printf("Auth request data: %s\n",data);
	//static char returnData[300];
	//strncpy(returnData,requestURL(data),sizeof(returnData));
	//return returnData;
	return requestURL(data);
}

/*void downloadFile(char *netFileName, char *localFileName, unsigned int fileSize, unsigned int offset = 0x107) {
	printf("Downloading file %s\n",localFileName);
	char data[100];
	snprintf$(data,sizeof(data),"res/%s",netFileName);
	char buf[100];
	snprintf$(buf,sizeof(buf),"/dev_hdd0/tmp/%s",localFileName);
	char *dat = requestURL(data);
	printf("Done Downloading\n");
	writeToFile(buf,dat+offset,fileSize);
}*/
/*
void downloadFileOld(char *netFileName, char *localFileName, unsigned int fileSize, bool findFirstNonZero = true) {
	//printf("Downloading file %s\n",localFileName);
	char data[100];
	snprintf(data,sizeof(data),"res/%s",netFileName);
	char buf[100];
	snprintf(buf,sizeof(buf),"/dev_hdd0/tmp/%s",localFileName);
	void *alloc;
	char *dat;
	if (fileSize <= 10000) {
		dat = requestURL(data);
	} else {
		//printf("v1\n");
		alloc = (void*)0x10070000;//malloc(fileSize+1000);//add 1000 for the network header crap    -    0x10070000 gives enough for 200kb
		//printf("v2\n");
		//printf("Malloc address: 0x%X\ndata: %s\n",(unsigned int)alloc,data);
		dat = requestURL(data,(char*)alloc,fileSize+1000);
		//printf("v3\n");
	}
	//printf("Done Downloading\n");
	if (findFirstNonZero) {
		dat+=8;
		while (dat[0] == 0)
			dat++;
	}
	writeToFile(buf,dat,fileSize);
		//free(alloc);
	for (int i = 0; i < fileSize; i++) {
		printf("%X ",dat[i]);
		if (i%16 == 0)
			printf("\n");
	}
}*/

void downloadFile(char *netFileName, char *localFileName, unsigned int fileSize, bool useContentLength = false, int fileStartOffset = 0) {
	//printf("Downloading file %s\n",localFileName);
	char data[100];
	snprintf(data,sizeof(data),"res/%s",netFileName);
	char buf[100];
	snprintf(buf,sizeof(buf),"/dev_hdd0/tmp/%s",localFileName);
	//void *alloc;
	char *dat;
	//dat = requestURL(data);
	dat = requestURLWriteToFile(data,buf,fileSize,useContentLength, fileStartOffset);
	//printf("Done Downloading\n");
	
	//writeToFile(buf,dat,fileSize);
		//free(alloc);
	/*for (int i = 0; i < fileSize; i++) {
		printf("%X ",dat[i]);
		if (i%16 == 0)
			printf("\n");
	}*/
}

/*
This function is used for downloading files from the /files/ folder of the website
It should work with any file :)
*/

int downloadFileFromDownloadFolder(char *fileOnServer,char *localFileName, bool downloadDirectlyToMemory = false, char **memoryLocation = 0) {//returns filesize, -1 for file size if size could not be found
	char data[300];
	memset(data,sizeof(data),0);
	snprintf$(data,sizeof(data),"files/%s",fileOnServer);
	char buf[100];
	snprintf(buf,sizeof(buf),"/dev_hdd0/tmp/%s",localFileName);
	int fileSize = -1;
	requestURLWriteToFile(data,buf,0,true,0,&fileSize,downloadDirectlyToMemory,memoryLocation);//size comes from the Content-Length header
	return fileSize;
}

unsigned int getUpdateFilesize() {
	char data[75];
	snprintf$(data,sizeof(data),"res/downloadsprx.php?key=%s&filesize",key);
	char *c = requestURL(data);
	/*int i = 0;
	while (c[0] != 'F') {
		c++;
		i++;
		if (i > 1000) {
			//if (!strstr(c,"F"))
			dialog("Issues connecting to the paradise server");
			return 0;
		}
	}*/
	if (!strstr(c,"F"))
		return 0;
	return StoUI(c);
}

bool canReceiveNetworkData(char **thetemporarydata) {
	//checks anti-ddos screen
	//printf("Checking connection...\n");
	char *c = requestURL("check.html");
	//printf("Got result: %s\n",c);
	*thetemporarydata = c;
	//printf("reeceived data: %s\n",c);
	//search for READYFORCONNECTION
	if (strstr(c,"READYFORCONNECTION"))
		return true;
	else
		return false;
}



bool I_AM_ON_AN_OLD_UPDATE = false;
bool doUpdate(bool showDialog = true, bool actuallyDownload = true) {
#if AUTO_UPDATE == 0
	return false;
#else

	unsigned int updatefilesize = getUpdateFilesize();
	//printf("Update filesize: %i\n",updatefilesize);
	unsigned int currentfilesize = getFileSize("/dev_hdd0/tmp/ParadiseGTA.sprx");
	if (updatefilesize != currentfilesize && updatefilesize > 0) {
		I_AM_ON_AN_OLD_UPDATE = true;
		if (actuallyDownload)
			requestURLWriteToFile("files/ParadiseGTA.sprx","/dev_hdd0/tmp/ParadiseGTA.sprx",updatefilesize);
		if (showDialog) {
			cellMsgDialogClose(0);
			sleep(500);
			dialog("Paradise SPRX Update Downloaded!\nPlease restart the game to use.");
		}
		return true;
	}
	return false;
#endif
}
/*
__ALWAYS_INLINE bool injectDDS(char *fileName, unsigned int pixelSize, char *textureData, unsigned int addAmount) {
	const unsigned int sizeof32 = 1152;//bit depth 32
	const unsigned int sizeof64 = 4224;//bit depth 32
	const unsigned int sizeof128 = 0;
	const unsigned int sizeof256 = 65664;
	const unsigned int sizeof512 = 262272;
	const unsigned int sizeof1024 = 0;
	unsigned int fileSize = 0;
	switch(pixelSize) {
	case 32: fileSize = sizeof32;break;
	case 64: fileSize = sizeof64;break;
	case 128: fileSize = sizeof128;break;
	case 256: fileSize = sizeof256;break;
	case 512: fileSize = sizeof512;break;
	case 1024: fileSize = sizeof1024;break;
	}
	if (fileSize == 0)//cannot download
		return false;
	char data[100];
	snprintf$(data,sizeof(data),"res/downloadasset.php?key=%s&filename=%s",key,fileName);
	//printf("Request: %s\n",data);
	void *alloc;
	char *dat;
	if (fileSize <= 10000) {
		dat = requestURL(data);
	} else {
		//printf("v1\n");
		alloc = (void*)0x10070000;//malloc(fileSize+1000);//add 1000 for the network header crap    -    0x10070000 gives enough for 200kb
		//printf("v2\n");
		//printf("Malloc address: 0x%X\ndata: %s\n",(unsigned int)alloc,data);
		dat = requestURL(data,(char*)alloc,fileSize+1000);
		//printf("v3\n");
	}
	dat+=8;
	while (dat[0] == 0)
		dat++;
	for (int i = 0; i < fileSize-addAmount; i++) {
		textureData[i] = dat[i+addAmount];
		//dat[i] = 0;
	}
	//for (int i = 0; i < fileSize; i++)
		//dat[i] = 0;
}
*/

namespace socketConnectionStuff {
#ifdef redefineSocketBase
/*__ALWAYS_INLINE*/ bool connectSocket(char *IP, int port) {
	//printf("Wrong connect socket called!!!\n");
	//printf("%s:%i\n",IP,port);
	struct in_addr ip;
	struct hostent *hp;
	//printf("gonna create the socket\n");
	if (!inet_aton(IP, &ip)) {
		return false;
        //printf("ERROR: can't parse IP address %s\n", IP);
	}
	Host = gethostbyname(IP/*,sizeof(ip),AF_INET*/);
	if(Host != NULL) {
        SocketAddress.sin_addr.s_addr = *((unsigned long*)Host->h_addr);
    } else {
		//printf("Invalid Host!\n");
		return false;
	}
	SocketAddress.sin_family = AF_INET;
	SocketAddress.sin_port = port;
	//printf("got this far\n");
	Socket = socket(AF_INET, SOCK_STREAM, 0);
	//printf("got this far 2\n");
	if (connect(Socket, (struct sockaddr *)&SocketAddress, sizeof(SocketAddress)) != 0) {
		strcpy(bufferReturn,"I");
		//printf("Could not connect to paradise sprx servers!\n");
		return false;
	}
	//printf("Connected socket!\n");
	return true;
}

/*__ALWAYS_INLINE*/ void closeSocket() {
	socketclose(Socket);
}

/*__ALWAYS_INLINE*/ void sendSocketData(char* data = "")
{
	//printf("sending \"%s\"\n",data);
	send(Socket, data, strlen(data), 0);
	send(Socket, "\r", 1, 0);
}
/*__ALWAYS_INLINE*/ char *recieveSocketData(bool waitall = false) {
	for (int i = 0; i < 10000; i++) {
		bufferReturn[i] = 0;
	}
	char curChar[1];
	curChar[0] = '\0';
	while (_recv(Socket, bufferReturn, 10000, waitall ? MSG_WAITALL : 0) > 0)
	{
		//printf("BufferReturn: %s\n",bufferReturn);
		return bufferReturn;
	}
	//printf("BufferReturn: %s\n",bufferReturn);
	return "\0";
	/*int place = 0;
	int timeout = 0;
	bool kek = false;
	_recv(Socket, curChar, 1, 0);
	while (curChar[0] == '\r') {
		_recv(Socket, curChar, 1, 0);
	}
	bufferReturn[place] = curChar[0];
	place++;
	
	while (curChar[0] != '\r') {
		int size = _recv(Socket, curChar, 1, 0);
		if (size > 0) {
			if (curChar[0] == '\r')
				return bufferReturn;
			bufferReturn[place] = curChar[0];
			if (bufferReturn > 0) {
				place++;
			} else {
				timeout++;
				if (timeout > 1000)
					return "\0";
			}
		}
	}
	return bufferReturn;*/
}
#endif

	/*unsigned int jenkins(char *key, size_t len)
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
	}*/
/*__ALWAYS_INLINE*/ uint32_t jenkins(char *key, size_t key_len) {
    uint32_t hash = 0;
    size_t i;

    for (i = 0; i < key_len; i++) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}


	/*
	unsigned int nativeTable;//1 - 0x1E6FF38
	unsigned int cashDropFix;//2 - 0x003FA510
	unsigned int scriptBypass;//3 - 0x01306254
	unsigned int teleportPlayerCallback;//4 - 0x1C6BF80
	unsigned int objectBypass;//5 - 0x3F8B84
	unsigned int modelToHash;//6 - 0x9D9830
	unsigned int entityToIndex;//7 - 0x474054
	unsigned int getCNetGamePlayer;//8 - 0x47E00C
	unsigned int getEntityAttachedTo;//9 - 0x3A9EFC
	unsigned int hookP1;//10 - 0x3D600000
	unsigned int hookP2;//11 - 0x396B0000
	unsigned int hookP3;//12 - 0x7D6903A6
	unsigned int hookP4;//13 - 0x4E800420
	unsigned int devmode;//14 - 1 or 0 kek
*/

//bool outputSocketData = false;

__ALWAYS_INLINE bool SocketRequestGoToBegin(char* URL, char* data, char *goTo, int goToSize)
{
	buildRequest(URL, data);
	send(Socket, RequestBuffer, strlen(RequestBuffer), 0);
	//printf("trolo\n");
	int curCheckSpot = 0;
	char buffer[1];
	int sizeofbuffer = 1;
	//int runsOfRecv = 0;
	//printf("Right before the recv\n");
	int ret = _recv(Socket, buffer, sizeofbuffer, 0);
	if (ret == 0) {
		//printf("0 bytes found on first call!\n");
	}
	while (ret > 0)//this is gonna read one byte at a time
	{
		//printf("%c",buffer[0]);
		//runsOfRecv++;
		//if (outputSocketData) {
		//	appendToFile("/dev_hdd0/tmp/OUTPUT.txt",buffer,sizeofbuffer);
		//}
		if (buffer[0] == goTo[curCheckSpot]) {
			curCheckSpot++;
			if (curCheckSpot == goToSize) {
				return true;//this is getting called on the bug too

			}
		} else {
			curCheckSpot = 0;
		}
		ret = _recv(Socket, buffer, sizeofbuffer, 0);
	}
	//printf("After the recv\n");
	//char buffkjsdf[100];
	//snprintf(buffkjsdf,sizeof(buffkjsdf),"runs: %i\n",runsOfRecv);
	//appendToFile("/dev_hdd0/tmp/OUTPUT.txt",buffkjsdf,strlen(buffkjsdf));
	//dialog("FAILURE!");
	return false;
}

//returns whether or not the data was all gotten properly
__ALWAYS_INLINE bool recvGetNext(char *buf, int size) {
	bool ret = true;
	for (int i = 0; i < size; i++) {
		char sa[1];
		int s = _recv(Socket, sa, 1, 0);
		if (s == 1) {
			buf[i] = sa[0];
		} else {
			ret = false;
		}
	}
	return ret;
}

void recvSkipBytes(int s) {
	for (int i = 0; i < s; i++) {
		char sa[1];
		_recv(Socket, sa, 1, 0);
	}
}

void recvPrintBytes(int s) {
	for (int i = 0; i < s; i++) {
		char sa[1];
		_recv(Socket, sa, 1, 0);
		printf("%c",sa[0]);
	}
}


/*
returns true if data successfully gotten
returns false if not
THIS IS THE BEST FUNCTION I HAVE, I SHOULD USE IT FOR MORE
*/
bool requestURLAtHeader(char *requestData, char *saveTo, unsigned int size, unsigned int skipAtStart, bool makeNewConnection) {
	if (makeNewConnection)
		connectSocket(serverparadisesprxcomip());
	//printf("Request: %s skip %i\n",requestData, skipAtStart);
	bool found = SocketRequestGoToBegin(serverparadisesprxcom(),requestData,"BEGINDATA\n",10);
	recvSkipBytes(skipAtStart);//skip amount if 0 usually
	if (found) {
		//printf("found proper data while getting file\n");
		recvGetNext(saveTo,size);
		if (makeNewConnection)
			closeSocket();
		return true;
	} else {
		//printf("could not find the right data\n");
	}
	if (makeNewConnection)
		closeSocket();
	return false;
}

//gets recv up to BEGINDATA\n
__ALWAYS_INLINE bool startSock(char *mac, int versionCheck) {
	connectSocket(serverparadisesprxcomip());
	char buf[150];
	for (int i = 0; i < sizeof(buf); i++)
		buf[i] = 0;
	snprintf(buf,sizeof(buf),"connecq.php?sesh=%s&data=%s&ver=%i",key,mac,versionCheck);
	return SocketRequestGoToBegin(serverparadisesprxcom(),buf,"BEGINDATA\n",10);
}

__ALWAYS_INLINE void endSock() {
	closeSocket();
}

//each value is sent by the server as a plain decimal number, right padded with spaces to 20 characters
__ALWAYS_INLINE char *sock() {
	static char d[21];
	for (int i = 0; i < sizeof(d); i++)d[i]=0;
	recvGetNext(d,20);
	return d;
}

void getNextData(unsigned int &x) {
	x = StoUI(sock());
}

void getNextDataInt(int& x) {
	x = (int)StoUI(sock());
}

#define VERSION_CHECK_NUMBER 5

//returns true if the server accepted the key
bool testSocket() {
	useAlternateIP = useAlternateConnection();

	int cnt = 0;
	char *thetemporarydata = 0;
	while (canReceiveNetworkData(&thetemporarydata) == false && cnt < 1) {//this will check for the anti-ddos screen
		cnt++;
		useAlternateIP = !useAlternateIP;
		setUseAlternateConnection(useAlternateIP);
	}

	retreiveMacAddress();
	char macBuf[30];
	snprintf(macBuf,sizeof(macBuf),"%i",getMacAddress());
	bool gotDataProperly = startSock(macBuf,VERSION_CHECK_NUMBER);//open the socket connection

	getNextData(addrstruct().nativeTable);
	getNextData(addrstruct().cashDropFix);
	getNextData(addrstruct().scriptBypass);
	getNextData(addrstruct().teleportPlayerCallback);
	getNextData(addrstruct().objectBypass);
	getNextData(addrstruct().modelToHash);
	getNextData(addrstruct().entityToIndex);
	getNextData(addrstruct().getCNetGamePlayer);
	getNextData(addrstruct().getEntityAttachedTo);
	getNextData(addrstruct().hookP1);
	getNextData(addrstruct().hookP2);
	getNextData(addrstruct().hookP3);
	getNextData(addrstruct().hookP4);
	getNextData(addrstruct().textData);
	getNextData(addrstruct().hookAddress);
	getNextData(addrstruct().NETWORK_CREATE_SYNCHRONISED_SCENE);
	getNextData(addrstruct().quadAddress);
	getNextData(addrstruct().entityFromIndex);
	getNextData(addrstruct().devmode);
	getNextData(addrstruct().allClientStatsAddress);
	getNextData(addrstruct().FCWfuncAddress);//21
	getNextData(addrstruct().FCWarg0);//22
	getNextData(addrstruct().FCWarg1);//23
	getNextData(addrstruct().FCWarg2);//24
	getNextData(addrstruct().FCWarg3);//25
	getNextData(addrstruct().setPlayerTeamAddr);//26
	getNextData(addrstruct().getPlayerIdAddr);//27
	getNextData(addrstruct().setSCTVSlotsAddr);//28
	getNextData(addrstruct().setPlayerTeamAddr2);//29
	getNextData(addrstruct().antiFreezeAddr1);//30
	getNextData(addrstruct().antiFreezeAddr2);//31
	getNextData(addrstruct().renderResulutionParams);//32
	getNextData(addrstruct().stringDecryptHash);//33
	getNextData(addrstruct().SCEventTicketFunc);//34
	getNextData(addrstruct().SCEventAnotherFunc);//35
	getNextData(addrstruct().PedProtVal1);//36
	getNextData(addrstruct().PedProtVal2);//37
	getNextDataInt(addrstruct().temporaryTimeVal);//38

	getNextData(addrstruct().privk0);//39
	getNextData(addrstruct().privk1);//40
	getNextData(addrstruct().privk2);//41
	getNextData(addrstruct().privk3);//42
	getNextData(addrstruct().privk4);//43
	getNextData(addrstruct().privk5);//44
	getNextData(addrstruct().privk6);//45
	getNextData(addrstruct().privk7);//46
	getNextData(addrstruct().privk8);//47
	getNextData(addrstruct().privk9);//48
	getNextData(addrstruct().privk10);//49
	getNextData(addrstruct().privk11);//50
	getNextData(addrstruct().privk12);//51
	getNextData(addrstruct().privk13);//52
	getNextData(addrstruct().privk14);//53
	getNextData(addrstruct().privk15);//54
	getNextData(addrstruct().privk16);//55
	getNextData(addrstruct().privk17);//56
	getNextData(addrstruct().privk18);//57
	getNextData(addrstruct().privk19);//58
	getNextData(addrstruct().suggest);//59
	getNextData(addrstruct().privk_132AE30);//60

	endSock();//close the socket

	static char welcomeText[] = "              \xEF\x91\xAEWelcome to\xEF\x91\xAE\n               \xEF\x91\xAFParadise!\xEF\x91\xAF";
	static char unspecifiedNetworkErrorString[] = "UNSPECIFIED NETWORK ERROR.\nPlease restart the game and make sure you are on the latest update.\n\nIf the problem persists, try setting your DNS to these settings:\nPrimary DNS: 1.1.1.1\nSecondary DNS: 1.0.0.1\nFor additional help, visit " PARADISE_WEBSITE;

	char *spoot = getAuthResult();
	bool authed = false;
	if (strstr(spoot,"VALIDVALIDVALID")) {
		authed = true;
		spoot = welcomeText;
	}
	//otherwise spoot is the server's "LOGIN FAILED" message (invalid key, console not registered, banned)

	if (gotDataProperly == false) {
		doUpdate(false,true);
		spoot = unspecifiedNetworkErrorString;
		authed = false;
	}
	dialog(spoot);
	return authed;
}

bool doTestSocketThread() {
	return testSocket();
}


};






#ifdef khjsfhguidfgejugoierjoi
namespace webmanccapi {
	bool CCAPI;
	bool WebMan;
	static int connect_to_CAPPI(void)
{
 struct sockaddr_in sin;
 int s;

 sin.sin_family = AF_INET;
 sin.sin_addr.s_addr = 0x7F000001; //127.0.0.1 (localhost)
 sin.sin_port = htons(6333);
 s = socket(AF_INET, SOCK_STREAM, 0);
 if (s < 0)
 {
  return -1;
 }

 if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
 {
  return -1;
 }

 return s;
}


static int connect_to_webman(void)
{
 struct sockaddr_in sin;
 int s;

 sin.sin_family = AF_INET;
 sin.sin_addr.s_addr = 0x7F000001; //127.0.0.1 (localhost)
 sin.sin_port = htons(80);         //http port (80)
 s = socket(AF_INET, SOCK_STREAM, 0);
 if (s < 0)
 {
  return -1;
 }

 if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
 {
  return -1;
 }

 return s;
}

static void sclose(int *socket_e)
{
 if (*socket_e != -1)
 {
  shutdown(*socket_e, SHUT_RDWR);
  socketclose(*socket_e);
  *socket_e = -1;
 }
}


static void send_wm_request(const char *cmd)
{
 // send command
 int conn_s = -1;
 conn_s = connect_to_webman();

 struct timeval tv;
 tv.tv_usec = 0;
 tv.tv_sec = 3;
 setsockopt(conn_s, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
 setsockopt(conn_s, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

 if (conn_s >= 0)
 {
  char wm_cmd[1048];
  int cmd_len = sprintf(wm_cmd, "GET %s HTTP/1.0\r\n", cmd);
  send(conn_s, wm_cmd, cmd_len, 0);
  sclose(&conn_s);
 }
}

static void send_CCAPI_request(const char *cmd)
{
 // send command
 int conn_s = -1;
 conn_s = connect_to_CAPPI();

 struct timeval tv;
 tv.tv_usec = 0;
 tv.tv_sec = 3;
 setsockopt(conn_s, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
 setsockopt(conn_s, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

 if (conn_s >= 0)
 {
  char wm_cmd[1048];
  int cmd_len = sprintf(wm_cmd, "GET %s HTTP/1.0\r\n", cmd);
  send(conn_s, wm_cmd, cmd_len, 0);
  sclose(&conn_s);
 }
}

void fixSpaces(char** szReturn) {
 char *str = *szReturn;
 char _returnStr[512];// = (char*)Malloc(128);

 _returnStr[0] = '\0';

 int dwStrIndex = 0;

 for (int i = 0; i < strlen(str) + 1; i++) {
  if (str[i] != 0x20) {
   _returnStr[dwStrIndex] = str[i];
   dwStrIndex++;
  }
  else
  {
   _returnStr[dwStrIndex] = '%';
   _returnStr[dwStrIndex + 1] = '2';
   _returnStr[dwStrIndex + 2] = '0';
   dwStrIndex += 3;
  }


  _returnStr[dwStrIndex] = '\0';
 }

 *szReturn = _returnStr;
}

void DoNotify(char *szFormat,int id = 0) {
 char _notify_buffer[512];
 if(CCAPI == true)
 {
 snprintf(_notify_buffer, 512, "/ccapi/notify?id=%i&msg=%s",id,szFormat);
 send_CCAPI_request(_notify_buffer);
 }
 else if(WebMan == true)
 {
 fixSpaces(&szFormat);
 snprintf(_notify_buffer, 512, "/notify.ps3mapi?msg=%s", szFormat);
 send_wm_request(_notify_buffer);
 }
}

void ShutDownPS3() {
 char _notify_buffer[512];
 if(CCAPI == true)
 {
 snprintf(_notify_buffer, 512, "/ccapi/shutdown?mode=1");
 send_CCAPI_request(_notify_buffer);
 }
 else if(WebMan == true)
 {
 snprintf(_notify_buffer, 512, "/shutdown.ps3");
 send_wm_request(_notify_buffer);
 }
}

void AreYouCCAPIorWebMan()
{
	static bool checked = false;
	if (checked)
		return;
	checked = true;
	int CCAPI_s = -1;
	CCAPI_s = connect_to_CAPPI();
	if(CCAPI_s != -1)
	{
		CCAPI = true;
		printf("ccapi\n");
		/*WebMan = false;
		NoCW = false;*/
	}
	else
	{
		int web_s = -1;
		web_s= connect_to_webman();
		if(web_s >= 0)
	    {
		CCAPI = false;
		/*WebMan = true;
		NoCW = false;*/
		WebMan = true;
	    }
		else
		{
			CCAPI = false;
            /*WebMan = false;
			NoCW = true;*/
		}
	}

}

};




#endif

#if httpcrap
namespace HTTP {
	#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/sys_time.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netex/net.h>
#include <netex/errno.h>

//#define sys_net_errno 0xDEADBEEF

	#define BUF_SIZE	(128 * 1024)
#if 0
#define SOCKET_BUF_SIZE	(192 * 1024)
#endif
#define REQUEST_GET1	"GET / HTTP/1.0\r\nHOST: "
#define REQUEST_GET2	"\r\nUser-Agent: paradise_semjases\r\n\r\n"

//int http(int argc, char *argv[]);
typedef long long int int64_t;
static void print_throughput(system_time_t time0, int len, int ret)
{
	static int count = 0;
	system_time_t time1;
	int64_t us, bps;

	time1 = sys_time_get_system_time();
	us = (int64_t)(time1 - time0);
	bps = (int64_t)((int64_t)len * 8 * 1000000 / us);
	if ((count++) % 100 == 0) {
		printf("len=%d(%6d), time=%d.%06d, %lldbps\n",
				len, ret, (int)(us / 1000000), (int)(us % 1000000), bps);
	}
}

static int usage(void)
{
	printf("Usage: http <URL>\n");
	return (-1);
}

int download(char *serverDownloadPlace)
{
	char *server_name;
	unsigned int temp;
	struct hostent *hp;
	struct sockaddr_in sin;
	int s;
	char get_cmd[128];
	static char buf[BUF_SIZE];//131072 thats really large!!!
	printf("\n\n\n\n\n\n\n\n\nBAD CODE HERE REMOVE THIS!!!!!!!!!!\n\n\n\n\n\n\n\n\n");
	int len;
	system_time_t time0 = 0;
#if defined(SOCKET_BUF_SIZE)
	int optval;
#endif
	int ret;

	/*if (argc != 2) {
		return (usage());
	}*/
	server_name = serverDownloadPlace;//argv[1];

	if ((unsigned int)-1 != (temp = inet_addr(server_name))) {
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = temp;
	}
	else {
		if (NULL == (hp = gethostbyname(server_name))) {
			printf("unknown host %s, %d\n", server_name, sys_net_h_errno);
			return (-1);
		}
		sin.sin_family = hp->h_addrtype;
		memcpy(&sin.sin_addr, hp->h_addr, hp->h_length);
	}
	sin.sin_port = htons(80);
	printf("connect to %s ...\n", inet_ntoa(sin.sin_addr));

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		printf("socket() failed (errno=%d)\n", sys_net_errno);
		return (-1);
	}
#if defined(SOCKET_BUF_SIZE)
	optval = SOCKET_BUF_SIZE;
	ret = setsockopt(s, SOL_SOCKET, SO_RCVBUF, &optval, sizeof(optval));
	if (ret < 0) {
		printf("setsockopt(SO_RCVBUF) failed (errno=%d)\n", sys_net_errno);
		goto termination;
	}
#endif
	ret = connect(s, (struct sockaddr *)&sin, sizeof(sin));
	if (ret < 0) {
		printf("connect() failed (errno=%d)\n", sys_net_errno);
		goto termination;
	}
	printf("connect ok\n");

	strcpy(get_cmd, REQUEST_GET1);
	strcat(get_cmd, server_name);
	strcat(get_cmd, REQUEST_GET2);

	len = strlen(get_cmd);
	ret = send(s, get_cmd, len, 0);
	if (ret < 0) {
		printf("send() failed (errno=%d)\n", sys_net_errno);
		goto termination;
	}
	if (ret != len) {
		printf("send() failed\n");
		goto termination;
	}
	printf("send ok.\n");

	len = 0;
	for (;;) {
		ret = recv(s, buf, sizeof(buf), 0);
		if (len == 0) {
			time0 = sys_time_get_system_time();
		}
		if (ret < 0) {
			printf("recv() failed (errno=%d)\n", sys_net_errno);
			goto termination;
		}
		if (ret == 0) {
			printf("FIN received\n");
			break;
		}
		len += ret;
		print_throughput(time0, len, ret);
	} 
	printf("total len = %d\n", len);

termination:
	ret = shutdown(s, SHUT_RDWR);
	if (ret < 0) {
		printf("shutdown() failed (errno=%d)\n", sys_net_errno);
	}
	socketclose(s);
	return (0);
}


}
#endif


namespace SimpleDownloader {
	//downloads the file named net_locInRes from the /files/ folder of the website
	int download_managed(char* local_locInTmp, char* net_locInRes) {
		int size = downloadFileFromDownloadFolder(net_locInRes, local_locInTmp);
		return size;
	}

	//accesses any file directly, so this can be used to call new PHP files in /public_html/server/res/
	//not as useful
	int download_res(char* local_locInTmp, char* net_locInRes, int size) {
		downloadFile(net_locInRes, local_locInTmp, size);
		return size;
	}
};