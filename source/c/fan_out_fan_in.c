// gcc -o fan_out_fan_in fan_out_fan_in.c -lpthread
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Work channel: distribute 1-20
#define WORK_CAP 32
int work_buf[WORK_CAP];
int work_head = 0, work_tail = 0, work_count = 0, work_done = 0;
pthread_mutex_t work_mu = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t work_not_empty = PTHREAD_COND_INITIALIZER;

int result_buf[32];
int result_count = 0;
pthread_mutex_t result_mu = PTHREAD_MUTEX_INITIALIZER;

void work_send(int val) {
    pthread_mutex_lock(&work_mu);
    work_buf[work_tail] = val;
    work_tail = (work_tail + 1) % WORK_CAP;
    work_count++;
    pthread_cond_signal(&work_not_empty);
    pthread_mutex_unlock(&work_mu);
}

int work_recv(int *out) {
    pthread_mutex_lock(&work_mu);
    while (work_count == 0 && !work_done) pthread_cond_wait(&work_not_empty, &work_mu);
    if (work_count == 0) { pthread_mutex_unlock(&work_mu); return 0; }
    *out = work_buf[work_head];
    work_head = (work_head + 1) % WORK_CAP;
    work_count--;
    pthread_mutex_unlock(&work_mu);
    return 1;
}

void *worker(void *arg) {
    int val;
    while (work_recv(&val)) {
        int sq = val * val;
        pthread_mutex_lock(&result_mu);
        result_buf[result_count++] = sq;
        pthread_mutex_unlock(&result_mu);
    }
    return NULL;
}

int cmp_int(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main(void) {
    for (int i = 1; i <= 20; i++) work_send(i);
    pthread_mutex_lock(&work_mu);
    work_done = 1;
    pthread_cond_broadcast(&work_not_empty);
    pthread_mutex_unlock(&work_mu);

    pthread_t workers[4];
    for (int i = 0; i < 4; i++) pthread_create(&workers[i], NULL, worker, NULL);
    for (int i = 0; i < 4; i++) pthread_join(workers[i], NULL);

    qsort(result_buf, result_count, sizeof(int), cmp_int);
    printf("results:");
    for (int i = 0; i < result_count; i++) printf(" %d", result_buf[i]);
    printf("\n");
    return 0;
}
