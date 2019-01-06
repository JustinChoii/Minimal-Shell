#ifndef HEADER_FILE
#define HEADER_FILE


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 4096

struct commands{
	int num_commands;
	char str[BUFFSIZE];
	int num_pipes;
	char* input[BUFFSIZE];
	char* output[BUFFSIZE];
	int creat;
	int append;
};



int countChars(char* sh, char ch){
    return *sh == '\0' ? 0 : countChars(sh + 1, ch) + (*sh == ch);
}


#endif