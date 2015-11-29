/*
        Advanced System Programming
        Linux / Unix
        My_command set
        Kookmin UNIV. seoul, South Korea.
        20113315 이형준, hyungjun lee
        hjlee1765@gmail.com
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <utime.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

void timechange(int argc, char *argv[], int i);

int main(int argc, char *argv[]) {
	int i, fd;
	struct stat stat_buf;
	struct utimbuf timebuf;

	if (argc < 2) {
	fprintf(stderr, "Usage: %s <files>...\n", argv[0]);
	return 0;
	}


	for (i=1; i<argc; i++) {
		//distingush directory and file
		stat(argv[i],&stat_buf);

		//directory
		if(S_ISDIR(stat_buf.st_mode))
			timechange(argc,argv,i);

		//file
		else{
			//I used to "O_CREAT" , so if is not there file, make it !
			if ((fd = open(argv[i], O_RDWR | O_CREAT ,0644)) < 0) {
				fprintf(stderr, "%s: open error: %s\n",argv[i], strerror(errno));
				continue;
			}
			timechange(argc,argv,i);
		}
	}
	return 0;
}

// fuc time change
void timechange(int argc, char* argv[],int i){
	if (utime(argv[i], NULL) < 0)
		fprintf(stderr, "%s: utime error: %s\n",argv[i], strerror(errno));
}
