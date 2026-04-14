// gcc -o producer_consumer producer_consumer.c -lpthread
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define BUF_SIZE 16

int ring[BUF_SIZE];
int head = 0, tail = 0, count = 0;
int done = 0;
pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

void send(int val) {
    pthread_mutex_lock(&mu);
    while (count == BUF_SIZE) pthread_cond_wait(&not_full, &mu);
    ring[tail] = val;
    tail = (tail + 1) % BUF_SIZE;
    count++;
    pthread_cond_signal(&not_empty);
    pthread_mutex_unlock(&mu);
}

int recv(int *out) {
    pthread_mutex_lock(&mu);
    while (count == 0 && !done) pthread_cond_wait(&not_empty, &mu);
    if (count == 0) { pthread_mutex_unlock(&mu); return 0; }
    *out = ring[head];
    head = (head + 1) % BUF_SIZE;
    count--;
    pthread_cond_signal(&not_full);
    pthread_mutex_unlock(&mu);
    return 1;
}

void *producer(void *arg) {
    for (int i = 1; i <= 10; i++) send(i);
    pthread_mutex_lock(&mu);
    done = 1;
    pthread_cond_broadcast(&not_empty);
    pthread_mutex_unlock(&mu);
    return NULL;
}

int results[10];
int rlen = 0;

void *consumer(void *arg) {
    int val;
    while (recv(&val)) results[rlen++] = val;
    return NULL;
}

int main(void) {
    pthread_t p, c;
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);
    pthread_join(p, NULL);
    pthread_join(c, NULL);

    printf("received:");
    for (int i = 0; i < rlen; i++) printf(" %d", results[i]);
    printf("\n");
    return 0;
}
