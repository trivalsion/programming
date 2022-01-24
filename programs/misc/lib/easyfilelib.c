/*
	@author : eltertrias
	@brief : library that is supposed to make interaction with files much easier(but actually does not becuase it is tash code)
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "include/easyfilelib.h"

// Sets a bit on/off in variable
static void setBit(uint16_t* var, uint8_t bit, uint16_t bit_num){
    if (bit == 1){
        if (!(*var & bit_num))
            *var ^= bit_num;
    }
    else if (bit == 0){
        if (*var & bit_num)
            *var ^= bit_num;
    }
}

// Writes a message to stderr and always returns -1 so it can be supplied to the retrun kyword
static int errorHandler(char* message){
    if (LIB_CONFIG_ERRORMESSAGE == 1)
        fprintf(stderr, "Error: %s\n", message);
    return -1;
}

// Opens the file and does all of the checks
int easyOpen(easyfilestruct_t* easyFile){
    // Do not let function use a structure that wasn't zerod
    if (easyFile->status != 0 || easyFile->fd != NULL)
        return errorHandler("Some of the variables that need to be empty(fd and status) contain data");

    // Check if the file exists and set the corresponding flag in the status
    if (access(easyFile->filename, F_OK) != -1)
        setBit(&easyFile->status, 1, FILE_EXISTS);

    // Check if the extension exists and set the corresponding flag in status
    if (strstr(easyFile->filename, easyFile->extension) != NULL)
        setBit(&easyFile->status, 1, FILE_EXTENSION);

    // Do not allow reading non-existant files
    if (!(easyFile->status & FILE_EXISTS) && ((strstr(easyFile->mode, "r") != NULL || strstr(easyFile->mode, "a") != NULL) && strstr(easyFile->mode, "+") == NULL))
        return errorHandler("The file does not exist and is attempted to be opened in a mode that needs already existant file");

    // Cases if the file does not already exist
    if (!(easyFile->status & FILE_EXISTS)){
        // If there is an extension just open
        if (easyFile->status & FILE_EXTENSION){
            if ((easyFile->fd = fopen(easyFile->filename, easyFile->mode)) == NULL)
                return errorHandler("Failed to open the file(with extension)");
            setBit(&easyFile->status, 1, FILE_CREATED);
        }
        // If there is no extension add it and then open
        else{
            // Fail if there is no place for extnesion or the length of filename is too big
            if (strlen(easyFile->filename) > 255 || (strlen(easyFile->filename) + strlen(easyFile->extension)) > 255)
                return errorHandler("The filname is too long to fit the extension and maybe exeeds system filename size limit");

            strcpy(&easyFile->filename[strlen(easyFile->filename)], easyFile->extension);
            printf("Extension was not supplied so one was added\n");
            if ((easyFile->fd = fopen(easyFile->filename, easyFile->mode)) == NULL)
                return errorHandler("Failed to open the file(with extension added by library)");
            setBit(&easyFile->status, 1, FILE_CREATED);
        }
    }

    return 0;
}

// Read the contents of the file into the buffer
int easyRead(easyfilestruct_t* easyFile, easybufferstruct_t* easyBuffer){
    long filePosition = ftell(easyFile->fd);

    // Make the tests to make sure everything is alright with the file
    if (easyFile->fd == NULL ||
        !(easyFile->status & FILE_EXTENSION) ||
        (easyFile->status & FILE_CORRUPT) ||
        (easyBuffer->bufferAdderess != NULL) ||
        ((strstr(easyFile->mode, "w") != NULL || strstr(easyFile->mode, "a") != NULL) && strstr(easyFile->mode, "+") == NULL) ||
        (!(easyFile->status & FILE_EXISTS) && !(easyFile->status & FILE_CREATED)))
            return errorHandler("File failed to pass the tests");


    // Fail if 0 elements are given or if size of one element is 0
    if (easyBuffer->elementSize == 0 || easyBuffer->elementAmount == 0)
        return errorHandler("There are 0 elements or their size is 0 which is impossible to read");
    // Allocate the space for the data to be read from file
    if ((easyBuffer->bufferAdderess = malloc(easyBuffer->elementSize * easyBuffer->elementAmount)) == NULL)
        return errorHandler("Failed to allocate the buffer for data from the file");

    // Read the data from the file to buffer
    if (fread(easyBuffer->bufferAdderess, easyBuffer->elementSize, easyBuffer->elementAmount, easyFile->fd) < (easyBuffer->elementSize * easyBuffer->elementAmount)){
        // If end of file was reached set the approprate flag in status
        if (feof(easyFile->fd) != 0)
            setBit(&easyFile->status, 1, FILE_REACHED_END);
        // Else try again and if it fails set flag that file is corrupt
        else{
            // Reset the file location before retrying if it changed
            if (filePosition != ftell(easyFile->fd))
                if (fseek(easyFile->fd, SEEK_SET, filePosition) == -1)
                    return errorHandler("Failed to reset the file location");

            // Clean the buffer before retrying
            memset(easyBuffer->bufferAdderess, 0, easyBuffer->elementSize * (easyBuffer->elementAmount));

            // Retry, and if it fails once more time, check if it was the end of file and if no set the corrupt flag on
            if (fread(easyBuffer->bufferAdderess, easyBuffer->elementSize, easyBuffer->elementAmount, easyFile->fd) < (easyBuffer->elementSize * easyBuffer->elementAmount)){
                if (feof(easyFile->fd) != 0)
                    setBit(&easyFile->status, 1, FILE_REACHED_END);
                else
                    setBit(&easyFile->status, 1, FILE_CORRUPT);
            }
        }

        // Cleaning on fail
        free(easyBuffer->bufferAdderess);
        easyBuffer->bufferAdderess = NULL;
        return errorHandler("Failed to read the information from the file");
    }

    // Set the size of the buffer if not set
    if (easyBuffer->bufferSize != (easyBuffer->elementAmount * easyBuffer->elementSize))
        easyBuffer->bufferSize == easyBuffer->elementSize * easyBuffer->elementAmount;
    return 0;
}

// Writes the contents of the buffer into the file
int easyWrite(easyfilestruct_t* easyFile, easybufferstruct_t* easyBuffer){
    long filePosition = ftell(easyFile->fd);

    // Make the tests to make sure everything is alright with the file
    if (easyFile->fd == NULL ||
        !(easyFile->status & FILE_EXTENSION) ||
        (easyFile->status & FILE_CORRUPT) ||
        (strstr(easyFile->mode, "r") != NULL && strstr(easyFile->mode, "+") == NULL) ||
        (!(easyFile->status & FILE_EXISTS) && !(easyFile->status & FILE_CREATED)))
            return errorHandler("File failed to pass the tests");

    // Fail if 0 elements are given or if size of element is zero
    if (easyBuffer->elementSize == 0 || easyBuffer->elementAmount == 0)
        return errorHandler("There are 0 elements or their size is 0 which is impossible to write");
    // Check if the array pointer is not NULL
    if(easyBuffer->bufferAdderess == NULL)
        return errorHandler("There is a value in buffer address field which needs to be empty");

    // Write the data from buffer into the file
    if (fwrite(easyBuffer->bufferAdderess, easyBuffer->elementSize, easyBuffer->elementAmount, easyFile->fd) < (easyBuffer->elementSize * easyBuffer->elementAmount)){
        // If end of file was reached set the approprate flag in status
        if (feof(easyFile->fd) != 0)
            setBit(&easyFile->status, 1, FILE_REACHED_END);
        // Else try again and if it fails set flag that file is corrupt
        else {
            // Reset the file pointer location before retrying if it changed
            if (filePosition != ftell(easyFile->fd))
                if (fseek(easyFile->fd, SEEK_SET, filePosition) == -1)
                    return errorHandler("Failed to reset the file location");

            // Retry, and if it fails once more check if it was the end of file and if no set the corrupt flag on
            if (fwrite(easyBuffer->bufferAdderess, easyBuffer->elementSize, easyBuffer->elementAmount, easyFile->fd) < (easyBuffer->elementSize * easyBuffer->elementAmount)){
                if (feof(easyFile->fd) != 0)
                    setBit(&easyFile->status, 1, FILE_REACHED_END);
                else
                    setBit(&easyFile->status, 1, FILE_CORRUPT);
            }
        }

        return errorHandler("Failed to write the information to the file");
    }

    return 0;
}

// Frees all buffes and closes all files
int easyClose(easyfilestruct_t* easyFile, easybufferstruct_t* easyBuffer){
    if (easyFile->fd != NULL)
        fclose(easyFile->fd);

    if (easyBuffer->bufferAdderess != NULL)
        free(easyBuffer->bufferAdderess);

    return 0;
}