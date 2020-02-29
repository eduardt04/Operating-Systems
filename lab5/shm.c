#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    for(int i = 1; i <= argc; i++) {
        pid_t pid = fork();
        if(pid < 0)
            return errno;

        else if(pid == 0) {
            pid_t child_pid = getpid();
            int n = atoi(argv[i]);    
            while(n != 1) {
                printf("%d ", n);
                n = n % 2 ? 3 * n + 1 : n / 2;
            }
            printf("1\n");  
            printf("Child %d finished\n", getpid());
            return EXIT_SUCCESS;
        }

        else {
            wait(NULL);
            
        }
    }
	return 0;
}
