// gcc -o map_reduce map_reduce.c -lpthread
// Map: square each number; Reduce: sum. Input [1..8], expected 204
#include <stdio.h>
#include <pthread.h>

typedef struct { int *chunk; int len; int *results; } MapArgs;
typedef struct { int *values; int len; long long *sum; } ReduceArgs;

void *map_worker(void *arg) {
    MapArgs *ma = (MapArgs*)arg;
    for (int i = 0; i < ma->len; i++) ma->results[i] = ma->chunk[i] * ma->chunk[i];
    return NULL;
}

void *reduce_worker(void *arg) {
    ReduceArgs *ra = (ReduceArgs*)arg;
    *ra->sum = 0;
    for (int i = 0; i < ra->len; i++) *ra->sum += ra->values[i];
    return NULL;
}

int main(void) {
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = 8, chunk_size = 2, num_chunks = n / chunk_size;

    int mapped[8];
    pthread_t map_tasks[4];
    MapArgs map_args[4];

    for (int i = 0; i < num_chunks; i++) {
        map_args[i].chunk = data + i * chunk_size;
        map_args[i].len = chunk_size;
        map_args[i].results = mapped + i * chunk_size;
        pthread_create(&map_tasks[i], NULL, map_worker, &map_args[i]);
    }
    for (int i = 0; i < num_chunks; i++) pthread_join(map_tasks[i], NULL);

    long long total;
    ReduceArgs ra = {mapped, n, &total};
    pthread_t reduce_t;
    pthread_create(&reduce_t, NULL, reduce_worker, &ra);
    pthread_join(reduce_t, NULL);

    printf("sum of squares: %lld\n", total);
    return 0;
}
