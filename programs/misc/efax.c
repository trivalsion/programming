/*
	@author : eltertrias
	@brief : transfers files through the network
*/

#define _DEFAULT_SOURCE
#include "include/efax.h"


int mode = 0;
char* peerAddress = NULL;
char* peerPort = NULL;
char* localPort = NULL;
char* filename = NULL;

char* argumentHandlersNames[] = {
    "-a", "-p", "-m", "-t", "-h", "-f", "-lp", NULL
};
int (*argumentHandlers[])(char* info) = {
    setAddress, setPort, setMode, displayTui, helpUser, setFile, setLocalPort, NULL
};



// Handles errors in selected mode
int errorHandler(int type, char* string){
    // Print system given error and exit
    if (type == ERROR_TYPE_SYS_FATAL){
        perror(string);
        exit(1);
    }
    // Print system given error
    else if (type == ERROR_TYPE_SYS)
        perror(string);
    // Print user given error
    else if (type == ERROR_TYPE_USER)
        fprintf(stderr, "Error: %s\n", string);
    // Print user given error and exit
    else if (type == ERROR_TYPE_USER_FATAL){
        fprintf(stderr, "Fatal: %s\n", string);
        exit(1);
    }
    else if (type == ERROR_TYPE_USER_FUNCTION){
        fprintf(stderr, "%s", string);
        return -1;
    }
    else if (type == ERROR_TYPE_SYS_FUNCTION){
        perror(string);
        return -1;
    }

    return 0;
}

// Cleans everything and finishes the program
void cleanFinish(){
    if (peerAddress != NULL)
        free(peerAddress);

    if (peerPort != NULL)
        free(peerPort);

    if (localPort != NULL)
        free(localPort);

    if (filename != NULL)
        free(filename);
}

// Tries to get bytes out of system buffer, if not enough were recieved
ssize_t readn(int fd, void *vptr, size_t n){
    size_t  bytesLeft;
    ssize_t bytesRead;
    char*   ptr;

    ptr = vptr;
    bytesLeft = n;

    while (bytesLeft > 0) {
        if ((bytesRead = read(fd, ptr, bytesLeft)) < 0) {
            // If system call was interrupted, then no bytes were read so reading must continue
            if (errno == EINTR)
                bytesRead = 0;
            // If other error occured, fail
            else
                return (-1);
        }
        // If zero was returned EOF is reached, so the function is finished
        else if (bytesRead == 0)
            break;

        // Decrease the amount of bytes left by the amount of bytes read
        bytesLeft -= bytesRead;

        // Increase the location in buffer by the amount of bytes read, so we are at the free byte and can continue writing
        ptr += bytesRead;
    }

    // Return the number of bytes read, by subtracting the amount of bytes that are left to read from requested
    return (n - bytesLeft);         /* return >= 0 */
}



// Command line agument handlers //
// Sets the address of the peer
int setAddress(char* info){
    peerAddress = strdup(info);

    return 0;
}

// Sets the port of the peer
int setPort(char* info){
    peerPort = strdup(info);

    return 0;
}

// Sets the mode
int setMode(char* info){
    if (strcmp(info, "send") == 0)
        mode = MODE_SEND;
    else if (strcmp(info, "receive") == 0)
        mode = MODE_RECEIVE;
    else
        return errorHandler(ERROR_TYPE_USER_FUNCTION, "This mode does not exist\n");

    return 0;
}

// Displays TUI interface for managing the program
int displayTui(char* info){
	REMOVE_UNUSED_WARNING(info);
    return 0;
}

// Prints the help message to the user
int helpUser(char* info){
	REMOVE_UNUSED_WARNING(info);

    printf("Usage: efax [OPTION]... [FILE]...\n\
    -r      sets receiver host information\n\
    -h      dispay help message and exit\n\
    -m      set the mode\n\
    -t      open programm with a tui interface\n");

    return 1;
}

// Sets the file variable to send/put received data into
int setFile(char* info){
    filename = strdup(info);

    return 0;
}

// Sets the local port
int setLocalPort(char* info){
    localPort = strdup(info);

    return 0;
}

// Interprets the command line arguments supplied by the user
int argumentInterpreter(int argc, char* argv[]){
    int i, j, argumentPresenceStatus = 0;
    int argumentHandlerStatus;

    if (argc < 2)
        return errorHandler(ERROR_TYPE_USER_FUNCTION, "Not enough command line arguments supplied\n");

    // Iterate through each command line argument and execute the appropriate function, otherwise return error
    for (i = 1; i < argc; i++){
        argumentPresenceStatus = 0;

        // Skip if it is not a command line argument, as it doesn't need to be interpreted
        if (argv[i][0] != '-')
            continue;

        // Iterate through the list of available command line arguments trying to find the one supplied by user, if found call corresponding function
        for (j = 0; argumentHandlersNames[j] != NULL; j++){
            if (strcmp(argumentHandlersNames[j], argv[i]) == 0){
                if ((argumentHandlerStatus = argumentHandlers[j](argv[i+1])) == 1 || argumentHandlerStatus == -1)
                    return argumentHandlerStatus;
                else {
                    argumentPresenceStatus = 1;
                    break;
                }
            }
        }

        // Report to user if argument deos not exist
        if (argumentPresenceStatus == 0){
            printf("Argument %s does not exist\n", argv[i]);
            helpUser(NULL);
            return -1;
        }
    }

    return 0;
}



// Program execution functions //
// Connect to the peer and send the file
int sendFile(FILE* fd){
    struct stat st;
    // Get the file stats for later sending
    if (stat(filename, &st) == -1)
        return errorHandler(ERROR_TYPE_SYS_FUNCTION, "Getting file size\n");
    uint8_t tempSendBuf[st.st_size];

    struct addrinfo gaiHints, *gaiResults, *gaiResultsI;
    int localSocket;

    ssize_t errorStatus;
    long left2send;

    // Fill in the default port if it was not done by the user
    if (peerPort == NULL)
        peerPort = strdup(FILE_SENDER_PORT);

    /// Connect to the remote socket
    // Fill the structure with criteria
    memset(&gaiHints, 0, sizeof(gaiHints));
    gaiHints.ai_family = AF_UNSPEC;
    gaiHints.ai_socktype = SOCK_STREAM;

    // Connect to the peer socket
    if (getaddrinfo(peerAddress, peerPort, &gaiHints, &gaiResults) < 0)
        return errorHandler(ERROR_TYPE_SYS_FUNCTION, "Getting receiver address\n");

    for (gaiResultsI = gaiResults; gaiResultsI != NULL; gaiResultsI = gaiResultsI->ai_next){
        if ((localSocket = socket(gaiResultsI->ai_family, gaiResultsI->ai_socktype, gaiResultsI->ai_protocol)) == -1)
            continue;
        else
            if (connect(localSocket, gaiResultsI->ai_addr, gaiResultsI->ai_addrlen) == -1){
                close(localSocket);
                continue;
            }
            else
                break;
    }
    if (gaiResultsI == NULL){
        freeaddrinfo(gaiResults);
        return errorHandler(ERROR_TYPE_USER_FUNCTION, "Failed to connect to the peer\n");
    }
    freeaddrinfo(gaiResults);

    // Read the data from file and send it to the peer
    if (fread(tempSendBuf, sizeof(uint8_t), st.st_size, fd) < (unsigned)st.st_size){
        close(localSocket);
        return errorHandler(ERROR_TYPE_USER_FUNCTION, "Failed to read data from the file\n");
    }
    // Send size of file to the peer
    if ((errorStatus = send(localSocket, &st.st_size, sizeof(st.st_size), 0)) < (signed)sizeof(st.st_size)){
        // If sending failed, retransmit data agian, if fail occures again close the connection
        if (send(localSocket, &st.st_size, sizeof(st.st_size), 0) < (signed)sizeof(st.st_size)){
            close(localSocket);
            return errorHandler(ERROR_TYPE_SYS_FUNCTION, "Failed to send the file size to peer");
        }
    }
    // Send the file to the peer
    if ((errorStatus = send(localSocket, tempSendBuf, sizeof(uint8_t)*st.st_size, 0)) < (signed)(sizeof(uint8_t)*st.st_size)){
        // If failed to send file, retransmit, if fail occures again close the connection
        if (errorStatus == -1){
            if (send(localSocket, tempSendBuf, sizeof(uint8_t)*st.st_size, 0) < (signed)(sizeof(uint8_t)*st.st_size)){
                close(localSocket);
                return errorHandler(ERROR_TYPE_SYS_FUNCTION, "Sending file");
            }
        }
        // If some part of file was not sent resend it, if fail occures agian close the connection
        else if (errorStatus != -1 && errorStatus < (signed)(sizeof(uint8_t)*st.st_size)){
            left2send = (sizeof(uint8_t)*st.st_size)-errorStatus;
            if (send(localSocket, &tempSendBuf[errorStatus], sizeof(uint8_t)*left2send, 0) < (signed)(sizeof(uint8_t)*left2send)){
                close(localSocket);
                return errorHandler(ERROR_TYPE_USER_FUNCTION, "Failed to send the file");
            }
        }
    }

    close(localSocket);
    return 0;
}

// Become a server and wait for any connections to establish and receive files
int receiveFile(FILE* fd){
    uint8_t* receiveBuffer;
    off_t file_size;

    struct addrinfo gaiHints, *gaiResults, *gaiResultsI;
    int localSocket;

    socklen_t clientAddrLen;
    struct sockaddr_storage clientAddress;
    int clientConnectionSocket;

    char clientAddressChar[NI_MAXHOST];
    char clientPortChar[NI_MAXSERV];

    ssize_t errorStatus;
    long left2read;

    struct timeval recvTimeout;

    // Fill in the default port if it was not done by the user
    if (localPort == NULL)
        localPort = strdup(FILE_SENDER_PORT);

    // Fill in the socket criteria
    memset(&gaiHints, 0, sizeof(gaiHints));
    gaiHints.ai_socktype = SOCK_STREAM;
    gaiHints.ai_family = AF_UNSPEC;
    gaiHints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;

    // Create and bind a socket
    if (getaddrinfo(NULL, localPort, &gaiHints, &gaiResults) < 0)
        return errorHandler(ERROR_TYPE_SYS_FUNCTION, "Getting info to create server\n");

    for (gaiResultsI = gaiResults; gaiResultsI != NULL; gaiResultsI = gaiResultsI->ai_next){
        if ((localSocket = socket(gaiResultsI->ai_family, gaiResultsI->ai_socktype, gaiResultsI->ai_protocol)) < 0)
            continue;
        else
            if (bind(localSocket, gaiResultsI->ai_addr, gaiResultsI->ai_addrlen) < 0){
                close(localSocket);
                continue;
            }
            else
                break;
    }
    if (gaiResultsI == NULL){
        close(localSocket);
        freeaddrinfo(gaiResults);
        return errorHandler(ERROR_TYPE_USER_FUNCTION, "Failed to bind the server\n");
    }
    freeaddrinfo(gaiResults);

    if (listen(localSocket, 1) == -1){
        close(localSocket);
        return errorHandler(ERROR_TYPE_SYS_FUNCTION, "Failed to make the socket listening\n");
    }

    // Accept the client connection
    for (;;){
        // Receive the connection from client
        clientAddrLen = sizeof(struct sockaddr_storage);
        if ((clientConnectionSocket = accept(localSocket, (struct sockaddr*)&clientAddress, &clientAddrLen)) < 0)
            continue;

        // If user set the peer port or address then check if the connected client applies to these criteria, else ask user to approve the connection
        if (getnameinfo((struct sockaddr*)&clientAddress, clientAddrLen, clientAddressChar, NI_MAXHOST, clientPortChar, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV) < 0){
            close(localSocket);
            close(clientConnectionSocket);
            return errorHandler(ERROR_TYPE_SYS_FUNCTION, "Failed to get the address and name of the peer\n");
        }
        // If port or address criteria supplied check for them
        if (peerPort != NULL || peerAddress != NULL){
            if (peerAddress != NULL)
                if (strcmp(peerAddress, clientAddressChar) != 0){
                    close(clientConnectionSocket);
                    continue;
                }
            if (peerPort != NULL)
                if (strcmp(peerPort, clientPortChar) != 0){
                    close(clientConnectionSocket);
                    continue;
                }
        }
        // If no port or address criteria for the client are supplied ask for the connection approval
        else {
            printf("A new connection request: \n");
            printf("Address: %s\n", clientAddressChar);
            printf("Port: %s\n", clientPortChar);

            printf("You didn't supply the connection criteria so your approval is required, do you want to accept the connection(y/n): ");
            if (getchar() == 'n'){
                close(clientConnectionSocket);
                continue;
            }
        }

        // Set a 30 second recv timeout
        recvTimeout.tv_sec = 30;
        recvTimeout.tv_usec = 0;
        setsockopt(clientConnectionSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&recvTimeout, sizeof(recvTimeout));

        // Receive the file size
        if (recv(clientConnectionSocket, &file_size, sizeof(off_t), 0) < (signed)sizeof(off_t)){
            // If failed to recieve file size, try reading one more time
            if (recv(clientConnectionSocket, &file_size, sizeof(off_t), 0) < (signed)sizeof(off_t)){
                close(localSocket);
                close(clientConnectionSocket);
                return errorHandler(ERROR_TYPE_SYS_FUNCTION, "Failed to receive the file size from the peer\n");
            }
        }
        // Allocate a buffer and recieve the file into there
        else {
            if ((receiveBuffer = malloc(sizeof(uint8_t)*file_size)) == NULL){
                close(localSocket);
                close(clientConnectionSocket);
                return errorHandler(ERROR_TYPE_SYS_FUNCTION, "Failed to allocate space for file\n");
            }
            if ((errorStatus = recv(clientConnectionSocket, receiveBuffer, sizeof(uint8_t)*file_size, 0)) < (signed)(sizeof(uint8_t)*file_size)){
                // If failed to recieve the full file
                if (errorStatus == -1) {
                    if ((errorStatus = recv(clientConnectionSocket, receiveBuffer, sizeof(uint8_t)*file_size, 0)) < (signed)(sizeof(uint8_t)*file_size)){
                        close(localSocket);
                        close(clientConnectionSocket);
                        free(receiveBuffer);
                        return errorHandler(ERROR_TYPE_SYS_FUNCTION, "Failed to receive the file from peer\n");
                    }
                }
                // If failed to recieve a part of file, try to recieve the missing part
                else if (errorStatus != -1 && errorStatus < (signed)(sizeof(uint8_t)*file_size)){
                    left2read = (sizeof(uint8_t)*file_size)-errorStatus;
                    if ((errorStatus = readn(clientConnectionSocket, &receiveBuffer[errorStatus], sizeof(uint8_t)*left2read)) < (signed)(sizeof(uint8_t)*left2read)){
                        close(localSocket);
                        close(clientConnectionSocket);
                        free(receiveBuffer);
                        return errorHandler(ERROR_TYPE_SYS_FUNCTION, "Failed to receive the file from peer\n");
                    }
                }
            }
        }

        // Write the received data into the file
        if (fwrite(receiveBuffer, sizeof(uint8_t), file_size, fd) < (unsigned)file_size){
            close(localSocket);
            close(clientConnectionSocket);
            free(receiveBuffer);
            return errorHandler(ERROR_TYPE_SYS_FUNCTION, "Failed to write buffer into the file\n");
        }
        break;
    }

    // Cleanup and exit
    close(localSocket);
    close(clientConnectionSocket);
    free(receiveBuffer);
    return 0;
}

// Execute everything based on the parameters set by argumentInterpreter using user command line arguments
int executeParameters(){
    FILE* fd = NULL;

    if (mode == MODE_SEND){
        if (filename == NULL)
            return errorHandler(ERROR_TYPE_USER_FUNCTION, "No filename was given so the file can't be sent\n");
        else {
            if ((fd = fopen(filename, "r")) == NULL)
                return errorHandler(ERROR_TYPE_SYS_FUNCTION, "Opening supplied file\n");
            if (sendFile(fd) == -1){
                fclose(fd);
                return -1;
            }
        }
    }
    else if (mode == MODE_RECEIVE){
        if (filename == NULL)
            return errorHandler(ERROR_TYPE_USER_FUNCTION, "No filename was given so the file can't be sent\n");
        else {
            if ((fd = fopen(filename, "w")) == NULL)
                return errorHandler(ERROR_TYPE_SYS_FUNCTION, "Opening supplied file\n");
            if (receiveFile(fd) == -1){
                fclose(fd);
                remove(filename);
                return -1;
            }
        }
    }

    if (fd != NULL)
        fclose(fd);
    return 0;
}


int main(int argc, char* argv[]){
    int argumentInterpreterStatus;

    // Check the command line arguments
    if ((argumentInterpreterStatus = argumentInterpreter(argc, argv)) == 1){
        cleanFinish();
        exit(0);
    }
    else if (argumentInterpreterStatus == -1){
        cleanFinish();
        errorHandler(ERROR_TYPE_USER_FATAL, "Failed to interpret supplied arguments");
    }

    // Start the execution of the program, using user set settings
    if (executeParameters() == -1){
        cleanFinish();
        errorHandler(ERROR_TYPE_USER_FATAL, "Failed to execute the requsted actions");
    }

    cleanFinish();
    exit(0);
}