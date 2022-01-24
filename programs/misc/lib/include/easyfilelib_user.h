/*
	@author : eltertrias
	@brief : global header for easyfilelib.c
*/

#include <stdint.h>
#include <stdio.h>

#define FILE_EXISTS 1
#define FILE_TYPE 2
#define FILE_EXTENSION 4
#define FILE_CREATED 8
#define FILE_REACHED_END 16
#define FILE_CORRUPT 32

struct easyFileStruct{
    char filename[256];
    char extension[256];
    uint16_t status;
    FILE* fd;
    char mode[3];
};
typedef struct easyFileStruct easyfilestruct_t;

// A structure for a buffer used to communicate with the easyFileLib functions
struct easyBufferStruct{
    void* bufferAdderess;
    size_t elementSize;
    size_t elementAmount;
    size_t bufferSize;
};
typedef struct easyBufferStruct easybufferstruct_t;


// Opens the file and does all of the checks, status and fd memebers of easyFile should be set to 0 and NULL acordingly, but filename, extension and mode should be set
extern int easyOpen(easyfilestruct_t* easyFile);

// Read the contents of the file into the buffer
extern int easyRead(easyfilestruct_t* easyFile, easybufferstruct_t* easyBuffer);

// Writes the contents of the buffer into the file
extern int easyWrite(easyfilestruct_t* easyFile, easybufferstruct_t* easyBuffer);

// Frees all buffes and closes all files
extern int easyClose(easyfilestruct_t* easyFile, easybufferstruct_t* easyBuffer);