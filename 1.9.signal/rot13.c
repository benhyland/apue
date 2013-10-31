#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include "exits.h"

#define BUFFER_SIZE 4096

static void prompt(void);

static int readLine(char line[BUFFER_SIZE]);

static void rot13(char line[BUFFER_SIZE]);

static void sigintHandler(int signal);

int
main(void) {
	
	char	line[BUFFER_SIZE];

	if(signal(SIGINT, sigintHandler) == SIG_ERR) {
		syserr("signal failed");
	}

	prompt();

	while(readLine(line)) {
		rot13(line);
		printf("%s\n", line);
		prompt();
	}

	exit(0);
}

static void prompt(void) {
	printf("$ ");
}

static int readLine(char line[BUFFER_SIZE]) {
	int gotLine = (NULL != fgets(line, BUFFER_SIZE, stdin));
	if(gotLine && line[strlen(line) - 1] == '\n') {
		line[strlen(line) - 1] = 0;
	}
	return gotLine;
}

static void rot13(char* line) {
	int i = 0;
	while(line[i] != 0) {
		char c = line[i];
		if((c >= 'a' && c <= 'm') || (c >= 'A' && c <= 'M')) {
			line[i] = c + 13;
		}
		else if((c >= 'n' && c <= 'z') || (c >= 'N' && c <= 'Z')) {
			line[i] = c - 13;
		}
		i++;
	}
}

static void sigintHandler(int signal) {
	char msg[] = "launching missiles!";
	rot13(msg);
	printf("%s\n", msg);
}

