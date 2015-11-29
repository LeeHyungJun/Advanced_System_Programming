/*
        Advanced System Programming
        Linux / Unix
        My_command set
        Kookmin UNIV. seoul, South Korea.
        20113315 이형준, hyungjun lee
        hjlee1765@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#define BUFSIZE 512

int main(int argc, char *argv[]) {
	int i, fd;
	struct stat	stat_buf;
	char buffer[BUFSIZE];
	size_t nread;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <files>...\n", argv[0]);
        return 0;
    }

	for (i=1; i<argc; i++) {
		//dir detect
                if(!(argv[i][0]=='-')){
                        stat(argv[i],&stat_buf);
                        if(S_ISDIR(stat_buf.st_mode)){
                                fprintf(stderr,"cat: %s :Is a directory\n",argv[i]);
                                exit(1);
                        }
                }

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

