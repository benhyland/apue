#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "exits.h"

#define BUFFER_SIZE 4096

static void prompt(void);

static int readLine(char line[BUFFER_SIZE]);

static void waitForChild(pid_t pid);

int
main(void) {
	
	char	line[BUFFER_SIZE];
	pid_t	pid;

	prompt();

	while(readLine(line)) {
		if((pid = fork()) < 0) {
			syserr("fork failed");
		}
		
		if(pid == 0) {
			/* fork returns 0 to the child process */
			execlp(line, line, NULL);
			syserr("exec of %s failed", line);
		}

		if(pid > 0) {
			/* fork returns the child's pid to the parent process */
			waitForChild(pid);
		}

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

static void waitForChild(pid_t pid) {
	int status;
	pid_t childPid;
	do {
		childPid = waitpid(pid, &status, 0);
		if(childPid < 0) {
			syserr("waitpid failed for pid %ld", (long)pid);
		}
	} while(!WIFEXITED(status) && !WIFSIGNALED(status));
}

