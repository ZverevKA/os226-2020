#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_LINE_SIZE 200
#define MAX_ARGS 20
#define MAX_WORD_LENGTH 30




int lastRetcode = 0;


void freeArgv(char *argv[]){
	for (int i = 0; i < MAX_ARGS; i++){
		free(argv[i]);
	}
	free(argv);
}

int echo(int argc, char *argv[]) {
	for (int i = 1; i < argc; ++i) {
		printf("%s%c", argv[i], i == argc - 1 ? '\n' : ' ');
	}
	return argc - 1;
}

int retcode(int argc, char *argv[]) {
	printf("%d\n", lastRetcode);
	return 0; 
}


int parse(char *str){
	char *aSave = NULL;
	char *bSave = NULL;
	char **argv;
	argv = malloc( MAX_ARGS * sizeof(char*));
	if (argv == NULL){
		printf("Memory error\n");
		exit(1);
	}
	for (int i = 0; i < MAX_ARGS; i++){
			argv[i] = malloc( MAX_WORD_LENGTH * sizeof(char));
			if (argv[i] == NULL){
			printf("Memory error\n");
			exit(1);
		}
	}

	int argc;

	char *fullCmd = strtok_r(str, ";\n", &aSave);
	while (fullCmd != NULL){
		char *token = strtok_r(fullCmd, " ", &bSave);		
		argc = 0;
		argv[0] = token;
		while (token != NULL){
			argc++;
			token = strtok_r(NULL, " ", &bSave);
			argv[argc] = token;
		}
		
		if (strcmp(argv[0], "echo") == 0){
			lastRetcode = echo(argc, argv);
		}
		else{		
			if (strcmp(argv[0], "retcode") == 0){
				lastRetcode = retcode(argc, argv);
			}
			else{
				printf("Unsigned token %s\n", argv[0]);
				free(argv);
				return 1;
			}
		}
		fullCmd = strtok_r(NULL, ";\n", &aSave);
	}
	free(argv);
	return 0;
}
		
int main(int argc, char *argv[]) {
	char str[MAX_LINE_SIZE];
	while (fgets(str, MAX_LINE_SIZE, stdin)){
		parse(str);
	}
	return 0;
}
