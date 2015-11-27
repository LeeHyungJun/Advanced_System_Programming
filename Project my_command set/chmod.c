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


int main(int argc, char* argv[])
{
	int i,perm;
	char *ptr;
        if(argc<3){
                printf("error\n");
                exit(1);
        }

	for(i=2; i<argc; i++){
		//change string to int.
		//perm is octal number.
		perm = strtol(argv[1],&ptr,8);
		if ( -1 == chmod( argv[i], perm))
		printf("error\n");
	}

}
