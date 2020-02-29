#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	const char* buffer = "Hello world!";
	write(1, buffer, strlen(buffer) * sizeof(char));
	return 0;
}
