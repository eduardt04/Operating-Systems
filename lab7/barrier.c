#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <semaphore.h>

pthread_mutex_t mtx;
sem_t sem;
const int n = 5;
int nr;
struct thread{
    pthread_t thr;
    int id;
}th[10];
void barrier_point() {
    int nr_local;
    pthread_mutex_lock(&mtx);
    ++nr;
    nr_local = nr;
    pthread_mutex_unlock(&mtx);
    if(nr_local < n) {
        sem_wait(&sem);
    }
    else {
        for(int i = 0; i < n - 1; i++)
            sem_post(&sem);
    }
}
void* tfun(void* v) {
    int tid = *(int*) v;
    printf("%d reached the barrier\n", tid);
    barrier_point();
    printf("%d passed the barrier\n", tid);
    return NULL;
}
int main(int argc, char* argv[]) {
    printf("NTHRS=%d\n", n);
    if(pthread_mutex_init(&mtx, NULL)) {
        perror(NULL);
        return errno;
    }
    sem_init(&sem, 0, 0);
    for(int i = 0; i < n; ++i) {
        th[i].id = i;
        pthread_create(&th[i].thr, NULL, tfun, &th[i].id);
    }
    for(int i = 0; i < n; ++i)
        pthread_join(th[i].thr, NULL);
    pthread_mutex_destroy(&mtx);
    sem_destroy(&sem);
    return 0;
}
