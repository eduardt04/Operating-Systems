#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main() {
	pid_t pid = fork();
	if(pid < 0)
		return errno;

	else if(pid == 0) {
		char* argv[] = {"ls", NULL};
		execve("/bin/ls", argv, NULL);
		printf("child %d finished", getpid());
		perror(NULL);
	}

	else {
		printf("My PID: %d, Child PID: %d\n", getppid(), getpid());
		int status;
		wait(&status);
		if(WIFEXITED(status)) {
			printf("Child %d finished\n", getpid());
		}
	}
	return 0;
}
