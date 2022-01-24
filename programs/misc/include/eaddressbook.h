/*
	@author : eltertrias
	@brief : header for eaddressbook.c
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct contact {
    char name[15];
    char surname[15];
    char phone[13];
    char email[20];
    char description[20];
};

// Reads the contents of the file into buffer
int readf(char filename[]);

// Writes buffer back to the file
void writef(char filename[]);

// Creates a new file in case inputted in main() does not exist
void newFile(char filename[]);

// Searches for the attribute through contacts
void search();

// Adds contacts to the file
void addContact();

// Removes contacts from the file
void removeContact();

// List contacts
void listContacts();

// Erorr correction
void errorCorrect();