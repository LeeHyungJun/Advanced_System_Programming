/*
        Advanced System Programming
        Linux / Unix
        My_command set
        Kookmin UNIV. seoul, South Korea.
        20113315 이형준, hyungjun lee
        hjlee1765@gmail.com
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char* argv[])
{
	struct stat stat_buf;
	int option_s=0;
	int i,j;
        if(argc<2){
                printf("error\n");
                exit(1);
        }
	//option detect
	for(i=j=1; i<argc; i++) {
                if(argv[i][0]=='-'){
                        if(argv[i][1] == 's')
                                option_s=1;
                }
        }

	//hard link
        if(option_s==0){
		for(i=1; i<argc; i++){
			//is directory ?   is file?
			//distinguish file and dir
			stat(argv[i],&stat_buf);
			if(S_ISDIR(stat_buf.st_mode)){
				fprintf(stderr,"ln: %s: hard link not allowed for directory\n",argv[i]);
				return 0;
			}
			//make a hard link
                        if( -1 == link( argv[i], argv[i+1])){
 				printf("error\n");
				return 0;
			}
			else
				break;
                }
        }
	 //symlink
        if(option_s==1){
                for(i=1; i<argc; i++){
			if(argv[i][0] == '-')
                                continue;
			//make a symlink
                        if( -1 == symlink( argv[i], argv[i+1])){
                                printf("error\n");
				return 0;
			}
                        else
                                break;
                }
        }



}
