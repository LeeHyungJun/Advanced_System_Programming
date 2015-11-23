#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <utime.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#define BUFSIZE 512

int main(int argc, char *argv[]) {
	int i, fd;
	struct stat     statbuf;
	char buffer[BUFSIZE];
	size_t nread;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <files>...\n", argv[0]);
        return 0;
    }

	for (i=1; i<argc; i++) {
		if ((fd = open(argv[i], O_RDWR ,0644)) < 0) {
			fprintf(stderr, "%s: open error: %s\n",
                    	argv[i], strerror(errno));
			continue;
		}
	}

	while((nread=read(fd,buffer,BUFSIZE))>0){
		if(write(1,buffer,nread)<nread){
		close(fd);
		return (-3);
		}
	}
}

