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


#define buf 128

void head(int n, int argc, char* argv[]);

int main(int argc, char* argv[])
{
        int option_n=0;
        int i,j,n;
	//default nValue= 10
	int nValue=10;
	char *char_nValue;
	FILE *fp;
	char str[buf];
	if(argc<2){
                printf("error\n");
                exit(1);
        }

        //option detect
        for(i=j=1; i<argc; i++) {
                if(argv[i][0]=='-'){
                        if(argv[i][1] == 'n'){
				if(argc<=3){
                                        printf("parameter error\n");
                                        exit(1);
                                }
                                option_n=1;
				//print the first nValue lines instead of the first 10
				char_nValue=argv[i+1];
				nValue=atoi(char_nValue);
			}
			else{
				printf("incorrect option\n");
				exit(1);
			}
                }
        }

	head(nValue,argc,argv);
}
void head(int nValue, int argc, char* argv[]){
	int i,n;
	FILE* fp;
	char str[buf];
	struct stat stat_buf;
	n=nValue;
	for(i=1; i<argc; i++){

		//dir detect
		if(!(argv[i][0]=='-')){
			stat(argv[i],&stat_buf);
                	if(S_ISDIR(stat_buf.st_mode)){
                        	fprintf(stderr,"head: error reading '%s' :  is a directory\n",argv[i]);
                        	exit(1);
                	}
		}


		//muti parameter print process
		//no -n option
		if(n==10){
			if(argc>2)
				printf("==> %s <==\n", argv[i]);
		}
		// yes -n option
		else{
			if(argv[i][0] == '-'){
				i++;
                                continue;
			}
			if(argc>4)
	    	                 printf("==> %s <==\n", argv[i]);
		}
		//main algorithm
		fp=fopen(argv[i],"r");
		if (fp == NULL)
			fprintf(stderr, "Can't open file\n");
		while(n)
		{
			fgets(str,buf,fp);
			printf("%s",str);
			n--;
		}
		fclose(fp);
		//recovery
		n=nValue;
	}
}
