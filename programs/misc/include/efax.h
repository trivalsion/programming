/*
	@author : eltertrias
	@brief : header for efax.c
*/

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>


#define FILE_SENDER_PORT "48700"

#define ERROR_TYPE_SYS_FATAL -1
#define ERROR_TYPE_SYS 0
#define ERROR_TYPE_USER 1
#define ERROR_TYPE_USER_FATAL 2
#define ERROR_TYPE_USER_FUNCTION 3
#define ERROR_TYPE_SYS_FUNCTION 4

#define MODE_SEND 1
#define MODE_RECEIVE 2

#define REMOVE_UNUSED_WARNING(x) (void)(x)


// Handles errors in selected mode
int errorHandler(int type, char* string);

// Cleans everything and finishes the program
void cleanFinish();

// Tries to get bytes out of system buffer, if not enough were recieved
ssize_t readn(int fd, void *vptr, size_t n);


// Sets the address of the peer
int setAddress(char* info);

// Sets the port of the peer
int setPort(char* info);

// Sets the mode
int setMode(char* info);

// Displays TUI interface for managing the program
int displayTui(char* info);

// Prints the help message to the user
int helpUser(char* info);

// Sets the file variable to send/put recieved data into
int setFile(char* info);

// Sets the local port
int setLocalPort(char* info);

// Interprets the command line arguments supplied by the user
int argumentInterpreter(int argc, char* argv[]);


// Connect to the peer and send the file
int sendFile(FILE* fd);

// Become a server and wait for any connections to establish and recieve files
int receiveFile(FILE* fd);

// Execute everything based on the parameters set by argumentInterpreter using user command line arguments
int executeParameters();