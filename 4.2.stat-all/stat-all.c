#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include "exits.h"

/*
emit some lstat details for all files given.
see also stat, fstat, fstatat.
*/

static void printFileInfo(char* file, struct stat* fileInfo);
static void getFileType(mode_t mode, char* type);

int
main(int argc, char* argv[]) {

	if(argc < 2) {
		usage("please provide at least one filename to stat");
	}

	char* file;
	int i;
	struct stat fileInfo;
	int result;
	for(i = 1; i < argc; i++) {
		file = argv[i];
		result = lstat(file, &fileInfo);
		if(result < 0) {
			syserr("failed to stat %s", file);
		}
		printFileInfo(file, &fileInfo);
	}
	exit(0);
}

static void printFileInfo(char* file, struct stat* fileInfo) {

	printf("stat for %s:\n", file);

	char type[30];
	getFileType(fileInfo->st_mode, type);

	printf("filetype %s\n", type);
	printf("inode %d\n", fileInfo->st_ino);
	printf("device %d\n", fileInfo->st_dev);
	printf("owner uid %d\n", fileInfo->st_uid);
	printf("owner gid %d\n", fileInfo->st_gid);
	printf("filesize %ld\n", fileInfo->st_size);
	printf("blocks %ld\n", fileInfo->st_blocks);
}

static void getFileType(mode_t mode, char* outType) {
	char* type;

	if(S_ISREG(mode)) {
		type = "regular file";
	}
	if(S_ISDIR(mode)) {
		type = "directory";
	}
	if(S_ISCHR(mode)) {
		type = "character special file";
	}
	if(S_ISBLK(mode)) {
		type = "block special file";
	}
	if(S_ISFIFO(mode)) {
		type = "fifo";
	}
	if(S_ISLNK(mode)) {
		type = "symbolic link";
	}
	if(S_ISSOCK(mode)) {
		type = "socket";
	}
	snprintf(outType, 20, "%s", type);
}

