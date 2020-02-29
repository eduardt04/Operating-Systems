#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	ssize_t count;
	char buffer[1024];
	int fd_read = open(argv[1], O_RDONLY);
	int fd_write = open(argv[2], O_RDWR | O_CREAT, 0666);
	int read_count = 0;

	while((count = read(fd_read, buffer, sizeof(buffer))) != 0)
		write(fd_write, buffer, count);

	close(fd_read);
	close(fd_write);
	return 0;
}
