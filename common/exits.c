#include <stdarg.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "exits.h"

static void	verror(const char *, va_list);

void
syserr(const char* format, ...) {
	va_list	args;
	va_start(args, format);
	verror(format, args);
	va_end(args);
	exit(1);
}

void
usage(const char* format, ...) {
	errno = 0;
	char msg[MAX_MSG_LENGTH];
	snprintf(msg, MAX_MSG_LENGTH, "usage: %s", format);

	va_list	args;
	va_start(args, format);
	verror(msg, args);
	va_end(args);
	exit(1);
}

static void
verror(const char *format, va_list args) {
	char msg[MAX_MSG_LENGTH];

	vsnprintf(msg, MAX_MSG_LENGTH - 1, format, args);
	strcat(msg, "\n");

	if(errno != 0) {
		snprintf(msg + strlen(msg), MAX_MSG_LENGTH - strlen(msg) - 1, "last error: %s", strerror(errno));
		strcat(msg, "\n");
	}

	fflush(stdout);
	fputs(msg, stderr);
	fflush(NULL);
}
