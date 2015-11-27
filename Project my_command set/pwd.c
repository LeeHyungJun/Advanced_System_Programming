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

int main(int argc, char* argv[])
{
	char buf[BUFSIZ];
	//get current working directory
	getcwd(buf,BUFSIZ);

	printf("%s\n",buf);
	return 0;

}
