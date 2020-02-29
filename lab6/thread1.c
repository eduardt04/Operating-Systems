#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* sir_reverse;

void* reverse(void* str) {
	int i, j;
	char* sir = (char*)str;
	sir_reverse = malloc(strlen(sir));
	for(i = strlen(sir) - 1, j = 0; i >= 0; i--, j++)
		sir_reverse[j] = sir[i];
	return sir_reverse;	
}

int main() {
	char* cuvant = "Hello";
	pthread_t tid;
	pthread_create(&tid, NULL, reverse, (void *)cuvant);
	pthread_join(tid, sir_reverse);
	printf("%s", (char*)sir_reverse);
	return 0;
}
