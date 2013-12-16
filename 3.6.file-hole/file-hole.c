#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "exits.h"


int
main(int argc, char* argv[]) {

	if(argc != 3) {
		syserr("wrong input");
	}

	int holeLen;

	if(sscanf(argv[2], "%d", &holeLen) != 1) {
		syserr("wrong input");
	}

	int fd;
	if((fd = open(argv[1], O_RDWR | O_CREAT)) < 0) {
		syserr("open failed");
	}
	if(lseek(fd, holeLen, SEEK_END) == -1) {
		syserr("seek failed");
	}
	if(write(fd, "end hole", 8) != 8) {
		syserr("write failed");
	}
	exit(0);
}
