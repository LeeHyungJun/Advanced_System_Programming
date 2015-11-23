
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <utime.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    int	i, fd;
    struct stat	    statbuf;
    struct utimbuf  timebuf;

    if (argc < 2) {
	fprintf(stderr, "Usage: %s <files>...\n", argv[0]);
	return 0;
    }

    for (i=1; i<argc; i++) {
	if ((fd = open(argv[i], O_RDWR | O_CREAT ,0644)) < 0) {
	    fprintf(stderr, "%s: open error: %s\n",
		    argv[i], strerror(errno));
	    continue;
	}

	if (utime(argv[1], NULL) < 0) {
	    fprintf(stderr, "%s: utime error: %s\n",
		    argv[i], strerror(errno));
	    continue;
	}
    }

    return 0;
}
