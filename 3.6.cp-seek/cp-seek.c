#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "exits.h"

#define BUFFER_SIZE 1024

static int canSeek(int fd);
static void showUsage();
static void doCopy(int from, int len);

int
main(int argc, char* argv[]) {

	if(argc != 3) {
		showUsage();
	}

	if(!canSeek(STDIN_FILENO)) {
		syserr("stdin is not seekable");
	}
	
	int from, len;

	int successCount =
		sscanf(argv[1], "%d", &from) +
		sscanf(argv[2], "%d", &len);

	if(successCount != 2) {
		showUsage();
	}

	doCopy(from, len);

	exit(0);
}

static int canSeek(int fd) {
	return lseek(fd, 0, SEEK_CUR) != -1;
}

static void showUsage() {
	usage("cp-seek <from> <len> - copies <len> bytes from stdin <from> offset to stdout");
}

static void doCopy(int from, int len) {

	int remaining = len;
	char buffer[BUFFER_SIZE];

	lseek(STDIN_FILENO, from, SEEK_SET);

	while(remaining > 0) {
		int toRead = remaining > BUFFER_SIZE ? BUFFER_SIZE : remaining;
		int readCount = read(STDIN_FILENO, buffer, toRead);
		if(readCount < 0) {
			syserr("read failed");
		}
		remaining -= readCount;
		int written = 0;
		while(written < readCount) {
			int writeCount = write(STDOUT_FILENO, buffer + written, readCount - written);
			if(writeCount < 0) {
				syserr("write failed");
			}
			written += writeCount;
		}
	}
}
