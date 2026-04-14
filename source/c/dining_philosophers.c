// gcc -o dining_philosophers dining_philosophers.c -lpthread
#include <stdio.h>
#include <pthread.h>

#define NUM_PHIL 5

pthread_mutex_t forks[NUM_PHIL];

void *philosopher(void *arg) {
    int id = *(int*)arg;
    int left = id, right = (id + 1) % NUM_PHIL;
    int first = left < right ? left : right;
    int second = left < right ? right : left;

    pthread_mutex_lock(&forks[first]);
    pthread_mutex_lock(&forks[second]);

    printf("philosopher %d is eating\n", id);

    pthread_mutex_unlock(&forks[second]);
    pthread_mutex_unlock(&forks[first]);
    return NULL;
}

int main(void) {
    for (int i = 0; i < NUM_PHIL; i++) pthread_mutex_init(&forks[i], NULL);

    pthread_t tasks[NUM_PHIL];
    int ids[NUM_PHIL];
    for (int i = 0; i < NUM_PHIL; i++) {
        ids[i] = i;
        pthread_create(&tasks[i], NULL, philosopher, &ids[i]);
    }
    for (int i = 0; i < NUM_PHIL; i++) pthread_join(tasks[i], NULL);

    printf("all philosophers ate\n");
    return 0;
}
