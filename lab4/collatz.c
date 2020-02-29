#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	pid_t pid = fork();
	if(pid < 0)
		return errno;

	else if(pid == 0) {
        if(argv[1] == NULL) {
            printf("No number in input.");
            return 0;
        }
		
        int n = atoi(argv[1]);
        
        while(n != 1) {
            printf("%d ", n);
            if(n % 2)
                n = 3 * n + 1;
            else n = n / 2;
        }
        printf("1\n");
	}

	else {
		int status;
		wait(&status);
		if(WIFEXITED(status)) {
			printf("Child %d finished\n", getpid());
		}
	}
	return 0;
}
