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
#include <stdio_ext.h>

#define BUFSIZE 512

int rmProcess(int i, int argc, char *argv[], int option);

typedef enum {false, true } bool;
bool isFile = true;
bool option_f, option_i =false;



int main(int argc, char *argv[]) {
	int i,j, fd;
	struct stat stat_buf;
        char buffer[BUFSIZE];

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <files>...\n", argv[0]);
		return 0;
 	}
	//option detect
	for(i=j=1; i<argc; i++) {
                if(argv[i][0]=='-'){
                        if(argv[i][1] == 'f')
                                option_f=true;
			else if(argv[i][1] == 'i')
				option_i=true;
                }
        }
	 // -i option
        if(option_i){
                for(i=1; i<argc; i++){
                        if(argv[i][0] == '-')
                                continue;
                        rmProcess(i,argc,argv,'i');
                }
        }

	// "-f option" and "no option"
	//because empty option equal -f option.
	else if(option_f){
		for(i=1; i<argc; i++){
			if(argv[i][0] == '-')
                                continue;
                        rmProcess(i,argc,argv,'f');
		}
	}
}

int rmProcess(int i, int argc, char *argv[], int option ){

	struct stat stat_buf;
	char buffer[BUFSIZE];
	int yesOrNo='y';

                 //distinguish file and directory
                memset(&stat_buf,0,sizeof(struct stat));
                stat(argv[i],&stat_buf);
                if(S_ISDIR(stat_buf.st_mode)){
                        isFile=false;
                        fprintf(stderr,"cannot remove '%s' : is a directory\n",argv[i]);
                        return 0;
                }

		if(option=='i'){
		printf("rm: remove regular file '%s'? ", argv[i]);
			scanf("%c",&yesOrNo);
			//fpurge equal fflush.
			//gcc did not  provide fflush.
			//that's why i used the fpurge.
			__fpurge(stdin);
		}

                if(yesOrNo=='y' || yesOrNo == 'Y'){
           		if(remove(argv[i])<0)
                               printf("file remove fail\n");
		}
		else
			printf("%s is  not remove\n",argv[i]);
}

