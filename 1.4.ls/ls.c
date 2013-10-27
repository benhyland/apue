#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "exits.h"

int
main(int argc, char* argv[])
{
	DIR*			dp;
	struct dirent*	dirp;

	if(argc != 2) {
		usage("ls <dirname>");
	}

	dp = opendir(argv[1]);
	if(dp == NULL) {
		syserr("cannot open '%s'", argv[1]);
	}

	while((dirp = readdir(dp)) != NULL) {
		printf("%s\n", dirp->d_name);
	}

	closedir(dp);
	exit(0);
}

