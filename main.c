#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

#define BUFFSIZE 4096


int main(){
	while(1){
		// set up variables
		char input[BUFFSIZE];
		struct commands cm;
		cm.num_pipes = 0;
		cm.num_commands = 0;
		int end = 0;
		int pipe_count = 0;
		char* tokens[BUFFSIZE];
		char* args[BUFFSIZE];
		int c = 0;
		int argsc = 0;
		int runs = 0;
		char* file;

		// begin the prompt
		printf("? ");

		// receive input and store it into cm.str
		file = fgets(cm.str, BUFFSIZE, stdin);
		if (file == NULL){
			continue;
		}
		if (cm.str[0] == '\n'){
			printf("0: \n");
			continue;
		}

		strtok(cm.str, "\n");

		// count and store the number of pipes. Need this to figure out how many loops to use.
		cm.num_pipes = countChars(cm.str, '|');

		// separate the tokens by the "|" delimiter. 
		// store the tokens into an array called tokens[].
		char *p = strtok(cm.str, "|");
		while (p != NULL){
			tokens[pipe_count] = p;
			p = strtok(NULL, "|");

			pipe_count += 1;
		}

		int lt_index = 0;
		int lt_index2 = 0;
		int lt2 = 0;
		int lt2i = 0;

		int gt_index = 0;
		int gt_index2 = 0;

		int lt = 0;
		int gt = 0;
		int a = 0;


		// Now go through the tokens, and retrieve the information we need.
		printf("%d: ", cm.num_pipes + 1);
		for (int i = 0; i < cm.num_pipes+1; i++){
			
			int hold = argsc;
			char *s = strtok(tokens[i], " ");
			while (s != NULL){
				args[c] = s;
				s = strtok(NULL, " ");
				c += 1;
				argsc += 1;
			}
			c+= 1;
			argsc += 1;


			// Loop once to gather information where I/O redirection exists (> or <)
			// Keep track of where the input/output redirection variables are.
			for (int j = hold; j < argsc - 1; j++){
				lt = 0;
				gt = 0;
				lt = countChars(args[j], '<');
				gt = countChars(args[j], '>');
				if (args[j] == "|"){
				}
				else{
					if (lt > 0){
						lt_index = j;
						lt_index2 = j+1;
						lt2 = lt_index;
						lt2i = lt_index2;
						if (i > 0){
							a = i;
						}

					}
					else if (gt > 0){
						gt_index = j;
						gt_index2 = j+1;
					}
					else{			
					}
				}
			}
			if(a = 0){
				printf("'%s' ", args[0]);
			}

			// Now that we know if > or < exists, we can begin to print the parsed information.
			// The input redirection will change how the parser interprets the given arguments.
			// We have three cases: if input exists, if output exists, if neither exist.
			// Print statements for each given case below:
			
			for (int k = hold; k < argsc - 1; k++){
				lt = 0;
				gt = 0;
				lt = countChars(args[k], '<');
				gt = countChars(args[k], '>');
				if (lt_index2 > 0){

					if(k == lt_index || k == lt_index2){
						continue;
					}
					else if(lt2 > 0){
						printf("%s", args[lt_index]);
						printf("'%s' ", args[lt_index2]);
					}
					if (gt > 0){
						printf("%s", args[k]);
					}
					else{
						printf("'%s' ", args[k]);
					}
					lt2 = 0;
				}
				else{

					if (gt > 0){
						printf("%s", args[k]);	
					}
					else{
						printf("'%s' ", args[k]);
					}
				}
			}
			if(i < cm.num_pipes){
				printf("| ");				
			}
		}
		printf("\n");
	}
	return 0;
}