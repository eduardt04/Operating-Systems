#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#define MAX_RESOURCES 10
int available_resources = MAX_RESOURCES;
pthread_mutex_t mtx;

int decrease_count(int count) {
    pthread_mutex_lock(&mtx);
    if(available_resources < count) {
        pthread_mutex_unlock(&mtx);
        return -1;
    }
    else {
        available_resources -= count;
        printf("Got %d resources %d remaining\n", count, available_resources);
    }
    pthread_mutex_unlock(&mtx);
    return 0;
}

int increase_count(int count) {
    pthread_mutex_lock(&mtx);
    available_resources += count;
    printf("Released %d resources %d remaining\n", count, available_resources);
    pthread_mutex_unlock(&mtx);
    return 0;
}

void* use(void* arg) {
    int count = (int)arg;
    if(decrease_count(count) == 0)
        increase_count(count);
    return NULL;
}

int main(int argc, char* argv[]) {
    int count;
    if(pthread_mutex_init(&mtx, NULL)) {
        perror(NULL);
        return errno;
    }
    pthread_t thr[10];
    
    for(int i = 0; i < 10; ++i) {
        //count = rand() % (MAX_RESOURCES + 1);
        if(pthread_create(&thr[i], NULL, use, i)) {
            perror(NULL);
            return errno;
        }
    }
    for(int i = 0; i < 10; ++i) {
        if(pthread_join(thr[i], NULL)) {
            perror(NULL);
            return errno;
        }
    }
    pthread_mutex_destroy(&mtx);
    return 0;
}
