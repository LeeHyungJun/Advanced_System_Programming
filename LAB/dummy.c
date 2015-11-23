#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>

#define MAXLINE 30
#define STDIN_FILENO 0
#define STDOUT_FILENO 1

void err_sys(const char *x) { perror(x); }

int main(int argc, char *argv[]) {
	int n;
	pid_t pid;
	char line[MAXLINE];
	int fifo1, fifo2;

	fifo1 = open(argv[1], O_WRONLY);
	fifo2 = open(argv[2], O_RDONLY);

	while(fgets(line, MAXLINE, stdin) != NULL) {
		n = strlen(line);
		if(write(fifo1, line, n) != n)
			err_sys("write error to pipe");
		if((n = read(fifo2, line, MAXLINE)) < 0)
			err_sys("read error from pipe");
		if(n == 0) {
			err_sys("child closed pipe");
			break;
		}
		line[n] = 0;
		if(fputs(line, stdout) == EOF)
			err_sys("fputs error");
	}
	close(fifo1);
	close(fifo2);
	
	exit(0);
}
