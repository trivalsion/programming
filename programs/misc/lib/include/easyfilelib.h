/*
	@author : eltertrias
	@brief : local header for easyfilelib.c
*/

#include <stdint.h>
#include <stdio.h>

#define LIB_CONFIG_ERRORMESSAGE 1

#define FILE_EXISTS 1
#define FILE_TYPE 2
#define FILE_EXTENSION 4
#define FILE_CREATED 8
#define FILE_REACHED_END 16
#define FILE_CORRUPT 32

#define DATA_TYPE_VARS 0
#define DATA_TYPE_STRUCTS 1

// A structure for a file opened with easyOpen function
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

// Help functions //
// Sets a bit on/off in variable
static void setBit(uint16_t* var, uint8_t bit, uint16_t bit_num);

// Writes a message to stderr and always returns -1 so it can be supplied to the retrun kyword
static int errorHandler(char* message);


// Opens the file and does all of the checks
int easyOpen(easyfilestruct_t* easyFile);

// Read the contents of the file into the buffer
int easyRead(easyfilestruct_t* easyFile, easybufferstruct_t* easyBuffer);

// Writes the contents of the buffer into the file
int easyWrite(easyfilestruct_t* easyFile, easybufferstruct_t* easyBuffer);

// Frees all buffes and closes all files
int easyClose(easyfilestruct_t* easyFile, easybufferstruct_t* easyBuffer);