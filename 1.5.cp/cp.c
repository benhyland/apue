#include <unistd.h>
#include <stdlib.h>
#include "exits.h"

#define BUFFER_SIZE 4096

int
main(void) {
	int		readCount;
	char	buffer[BUFFER_SIZE];

	while((readCount = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {
		int writeCount = write(STDOUT_FILENO, buffer, readCount);
		if(readCount != writeCount) {
			syserr("write failed");
		}
	}

	if(readCount < 0) {
		syserr("read failed");
	}

	exit(0);
}
