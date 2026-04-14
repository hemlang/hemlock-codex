// gcc -o thread_safe_queue thread_safe_queue.c -lpthread
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define NUM_PRODUCERS 3
#define ITEMS_PER_PRODUCER 5
#define TOTAL_ITEMS (NUM_PRODUCERS * ITEMS_PER_PRODUCER)
#define BUF_SIZE 128

// Thread-safe queue
char queue_data[BUF_SIZE][16];
int q_head = 0, q_tail = 0, q_count = 0;
pthread_mutex_t q_mu = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t q_not_empty = PTHREAD_COND_INITIALIZER;

void q_send(const char *val) {
    pthread_mutex_lock(&q_mu);
    strncpy(queue_data[q_tail], val, 15);
    q_tail = (q_tail + 1) % BUF_SIZE;
    q_count++;
    pthread_cond_signal(&q_not_empty);
    pthread_mutex_unlock(&q_mu);
}

void q_recv(char *out) {
    pthread_mutex_lock(&q_mu);
    while (q_count == 0) pthread_cond_wait(&q_not_empty, &q_mu);
    strncpy(out, queue_data[q_head], 15);
    q_head = (q_head + 1) % BUF_SIZE;
    q_count--;
    pthread_mutex_unlock(&q_mu);
}

typedef struct { int id; int count; } ProducerArgs;

void *producer(void *arg) {
    ProducerArgs *pa = (ProducerArgs*)arg;
    for (int i = 0; i < pa->count; i++) {
        char buf[16];
        snprintf(buf, 16, "p%d-%d", pa->id, i);
        q_send(buf);
    }
    return NULL;
}

char received[TOTAL_ITEMS][16];
int received_count = 0;

void *consumer(void *arg) {
    int expected = *(int*)arg;
    for (int i = 0; i < expected; i++) {
        q_recv(received[received_count++]);
    }
    return NULL;
}

int cmp_str(const void *a, const void *b) {
    return strcmp((const char*)a, (const char*)b);
}

int main(void) {
    int expected = TOTAL_ITEMS;
    pthread_t cons_t;
    pthread_create(&cons_t, NULL, consumer, &expected);

    pthread_t prod_t[NUM_PRODUCERS];
    ProducerArgs args[NUM_PRODUCERS];
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        args[i].id = i; args[i].count = ITEMS_PER_PRODUCER;
        pthread_create(&prod_t[i], NULL, producer, &args[i]);
    }
    for (int i = 0; i < NUM_PRODUCERS; i++) pthread_join(prod_t[i], NULL);
    pthread_join(cons_t, NULL);

    printf("consumed %d items\n", received_count);
    qsort(received, received_count, 16, cmp_str);
    printf("values:");
    for (int i = 0; i < received_count; i++) printf(" %s", received[i]);
    printf("\n");
    return 0;
}
