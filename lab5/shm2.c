#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int n, i, nr;
	printf("Cate numere: "); 
	scanf("%d", &nr);
	printf("\n");
	printf("Starting Parent: %d\n", getpid());

	char shm_name[]="shared";
	int shm_fd = shm_open(shm_name, O_CREAT|O_RDWR, 0666);

	size_t shm_size = getpagesize() * nr;
	size_t page_size = getpagesize();
	
	printf("Page size: %zu\n\n", page_size);
	
	ftruncate(shm_fd, shm_size);

	char *shm_ptr;
	for(i=0; i<nr; i++)
	{
		shm_ptr = mmap(0, page_size, PROT_WRITE, MAP_SHARED, shm_fd, i * page_size);
		pid_t pid = fork();
		if(pid < 0) return errno;
		else if(pid == 0)
		{
			printf("introduceti nr: ");
			scanf("%d", &n);
			shm_ptr += sprintf(shm_ptr, "%d: %d ", n, n);
			while(n != 1)
			{
				if(n%2 == 0) n /= 2;
				else n = n*3 + 1;
				shm_ptr += sprintf(shm_ptr, "%d ", n);
			}
			printf("Parent %d Child %d\n", getppid(), getpid());
			return 0;
		}
		else{
			int status;
			wait(&status);
			if(WIFEXITED(status))
				printf("Child %d finished\n\n", getpid());
		}
		munmap(shm_ptr, page_size);
	}

	for(i=0; i<nr; i++)
	{
		shm_ptr = mmap(0, page_size, PROT_READ, MAP_SHARED, shm_fd, i * page_size);
		if(shm_ptr == MAP_FAILED)
		{
			perror(NULL);
			shm_unlink(shm_name);
			return errno;
		}
		printf("%s\n", shm_ptr);
		munmap(shm_ptr, page_size);
	}
	return 0;
}

