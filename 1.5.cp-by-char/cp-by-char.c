#include <stdio.h>
#include <stdlib.h>
#include "exits.h"

int
main(void) {
	int		c;

	while((c = getc(stdin)) != EOF) {
		int written = putc(c, stdout);
		if(written == EOF) {
			syserr("write failed");
		}
	}

	if(ferror(stdin)) {
		syserr("read failed");
	}

	exit(0);
}
