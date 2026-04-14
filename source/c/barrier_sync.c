// gcc -o barrier_sync barrier_sync.c -lpthread
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>

#define NUM_TASKS 4

atomic_int counter = 0;
int completed[NUM_TASKS];
pthread_mutex_t result_mu = PTHREAD_MUTEX_INITIALIZER;
int result_count = 0;

void *barrier_task(void *arg) {
    int id = *(int*)arg;

    // Increment and spin-wait
    atomic_fetch_add(&counter, 1);
    while (atomic_load(&counter) < NUM_TASKS) { /* spin */ }

    pthread_mutex_lock(&result_mu);
    completed[result_count++] = id;
    pthread_mutex_unlock(&result_mu);
    return NULL;
}

int main(void) {
    pthread_t tasks[NUM_TASKS];
    int ids[NUM_TASKS];

    for (int i = 0; i < NUM_TASKS; i++) {
        ids[i] = i;
        pthread_create(&tasks[i], NULL, barrier_task, &ids[i]);
    }
    for (int i = 0; i < NUM_TASKS; i++) pthread_join(tasks[i], NULL);

    printf("all %d tasks passed barrier\n", result_count);
    return 0;
}
