#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

int main() {
	int fd1[2];//, fd2[2];

	if (pipe(fd1) < 0) {//|| pipe(fd2) < 0) {
    	close(fd1[READ]);
		close(fd1[WRITE]);
		//close(fd2[READ]);
		//close(fd2[WRITE]);
		return -1;
    }

	pid_t pid1;

	if ((pid1 = fork()) < 0) return 1;

	if (pid1 == 0) {
		dup2(fd1[WRITE], STDOUT_FILENO);
		close(fd1[READ]);
		close(fd1[WRITE]);
		//close(fd2[READ]);
		//close(fd2[WRITE]);
		execlp("ls", "ls", NULL);
		printf("--\n");
		exit(1);
	}
	pid_t pid2;
	if ((pid2 = fork()) < 0) return 2;

	if (pid2 == 0) {
		dup2(fd1[READ], STDIN_FILENO);
		close(fd1[READ]);
		close(fd1[WRITE]);
		//close(fd2[READ]);
		//close(fd2[WRITE]);
		execlp("grep", "grep", "main", NULL);
		printf("--\n");
		exit(1);
	}

	close(fd1[READ]);
	close(fd1[WRITE]);
	//close(fd2[READ]);
	//close(fd2[WRITE]);
	
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return 0;
}