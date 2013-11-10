#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*

   Print a selection of sysconf values.
   See also sysconf.sym, pathconf.sym, sysconf(), pathconf(), fpathconf().

*/

struct conf_name {
	int name;
	char desc[128];
};

int
main(void) {
	
	struct conf_name names[] = {
		{ _SC_ARG_MAX,			"max length in bytes of arguments to exec() functions" },
		{ _SC_ATEXIT_MAX,		"max number of functions registerable with atexit()" },
		{ _SC_CHILD_MAX,		"max number of processes per real user id" },
		{ _SC_CLK_TCK,			"clock ticks per second" },
		{ _SC_DELAYTIMER_MAX,	"max number of timer expiration overruns" },
		{ _SC_HOST_NAME_MAX,	"max host name length from gethostname()" },
		{ _SC_LINE_MAX,			"max input line length handled by common utilities" },
		{ _SC_LOGIN_NAME_MAX,	"max length for a login name" },
		{ _SC_NGROUPS_MAX,		"max number of simultaneous supplementary group ids per process" },
		{ _SC_OPEN_MAX,			"the successor of the max value allowed for a new file descriptor" },
		{ _SC_PAGESIZE,			"page size in bytes" },
		{ _SC_RTSIG_MAX,		"max number of real time signals usable by applications" },
		{ _SC_SEM_NSEMS_MAX,	"max number of semaphores a process can use at once" },
		{ _SC_SEM_VALUE_MAX,	"max value of a semaphore" },
		{ _SC_STREAM_MAX,		"max number of streams a process can use at once" },
		{ _SC_SYMLOOP_MAX,		"max number of symlinks traversable during path resolution" },
		{ _SC_TIMER_MAX,		"max number of timers per process" },
	};

	int count = sizeof(names)/sizeof(names[0]);

	for(int i = 0; i < count; i++) {
		printf("%s: %ld\n", names[i].desc, sysconf(names[i].name));
	}

	exit(0);
}
