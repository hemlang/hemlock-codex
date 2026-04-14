// gcc -o atomic_counter atomic_counter.c -lpthread
#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

#define NUM_TASKS 10
#define ITERATIONS 100

atomic_int counter = 0;

void *increment_worker(void *arg) {
    for (int i = 0; i < ITERATIONS; i++) atomic_fetch_add(&counter, 1);
    return NULL;
}

int main(void) {
    pthread_t tasks[NUM_TASKS];
    for (int i = 0; i < NUM_TASKS; i++) pthread_create(&tasks[i], NULL, increment_worker, NULL);
    for (int i = 0; i < NUM_TASKS; i++) pthread_join(tasks[i], NULL);
    printf("final: %d\n", atomic_load(&counter));
    return 0;
}
