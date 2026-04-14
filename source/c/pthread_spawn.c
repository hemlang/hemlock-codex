// gcc -o pthread_spawn pthread_spawn.c -lpthread
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4

typedef struct { int start; int end; long sum; } WorkerArgs;

void *worker(void *arg) {
    WorkerArgs *wa = (WorkerArgs*)arg;
    wa->sum = 0;
    for (int i = wa->start; i <= wa->end; i++) wa->sum += i;
    return NULL;
}

int main(void) {
    pthread_t threads[NUM_THREADS];
    WorkerArgs args[NUM_THREADS];
    int chunk = 100 / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].start = i * chunk + 1;
        args[i].end = (i == NUM_THREADS - 1) ? 100 : (i + 1) * chunk;
        pthread_create(&threads[i], NULL, worker, &args[i]);
    }

    long total = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        total += args[i].sum;
    }
    printf("total: %ld\n", total);
    return 0;
}
