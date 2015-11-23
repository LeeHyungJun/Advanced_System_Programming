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

void cutAndmake(int n, int argc, char* dir[]);

int main(int argc, char* argv[])
{
	if(argc<2){
		printf("error\n");
		exit(1);
	}

	int option_p=0;
	int i,j;
	//option detect
	for(i=j=1; i<argc; i++)	{
		if(argv[i][0]=='-'){
			if(argv[i][1] == 'p')
				option_p=1;
		}
	}
	if(option_p==0){
		for(i=1; i<argc; i++){
			if(mkdir(argv[i],0777)!=0)
				perror("make error");
		}
	}
	if(option_p==1){
		for(i=1; i<argc; i++){
			if(argv[i][0] == '-')
				continue;
			cutAndmake(i,argc,argv);
		}
	}
return 0;
}

void cutAndmake(int i, int argc, char* dir[])
{
	int j,cnt=0;
	char* temp[50];
	char dirCopy[50];
	char temp2[50];
	char* token=NULL;
	strcpy(dirCopy,dir[i]);

	token=strtok(dirCopy,"/");
	while(token != NULL){
		temp[cnt++]=token;
		token=strtok(NULL,"/");
	}

	for(j=0;j<cnt;j++){
//		printf("%s\n", temp[j]);
		if(j==0){
			if(mkdir(temp[0],0777)!=0)
				perror("make error");
			strcpy(temp2,temp[0]);
		}
		else{
			//strcpy(temp2,temp[j-1]);
			strcat(temp2,"/");
			//printf("%s\n",temp2);
			strcat(temp2,temp[j]);
			if(mkdir(temp2,0777)!=0)
				 perror("make error");
			//printf("%s\n", temp2);
		}
	}
}
