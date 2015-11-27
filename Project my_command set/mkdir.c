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

void p_option_cutAndmake(int n, int argc, char* dir[]);

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
	//not -p option.
	if(option_p==0){
		for(i=1; i<argc; i++){
			if(mkdir(argv[i],0777)!=0)
				perror("make error");
		}
	}
	// -p option adjust
	if(option_p==1){
		for(i=1; i<argc; i++){
			if(argv[i][0] == '-')
				continue;
			p_option_cutAndmake(i,argc,argv);
		}
	}
return 0;
}

void p_option_cutAndmake(int i, int argc, char* dir[])
{
	int j,cnt=0;
	char* temp[50];
	char dirCopy[50];
	char temp2[50];
	char* token=NULL;
	//dummy char* copy
	strcpy(dirCopy,dir[i]);
	//token is "/"
	//cut the string as a "/" standard
	token=strtok(dirCopy,"/");
	while(token != NULL){
		//save the cutting result to temp arr
		temp[cnt++]=token;
		token=strtok(NULL,"/");
	}

		//	ex. 		you command ./mkdir -p a/b/c
		//	result.		a    b    c


	for(j=0;j<cnt;j++){
		if(j==0){
			//make first dir ex. 'a'
			if(mkdir(temp[0],0777)!=0)
				perror("make error");
			strcpy(temp2,temp[0]);
		}

		//      ex.             you command ./mkdir -p a/b/c
		//      result 1.	a
		//	result 2.	a/b
		//	result 3.	a/b/c


		else{
			//attach '/' string
			strcat(temp2,"/");
			strcat(temp2,temp[j]);
			//make second,third... dir
			// ex. a/b    ex. a/b/c
			if(mkdir(temp2,0777)!=0)
				 perror("make error");
		}


	}
}
