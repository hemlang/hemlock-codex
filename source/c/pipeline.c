// gcc -o pipeline pipeline.c -lpthread
// Pipeline: generate -> double -> add10 -> collect
#include <stdio.h>
#include <pthread.h>

typedef struct {
    int buf[16];
    int head, tail, count, closed;
    pthread_mutex_t mu;
    pthread_cond_t not_empty, not_full;
} Chan;

void chan_init(Chan *c) {
    c->head = c->tail = c->count = c->closed = 0;
    pthread_mutex_init(&c->mu, NULL);
    pthread_cond_init(&c->not_empty, NULL);
    pthread_cond_init(&c->not_full, NULL);
}

void chan_send(Chan *c, int val) {
    pthread_mutex_lock(&c->mu);
    while (c->count == 16) pthread_cond_wait(&c->not_full, &c->mu);
    c->buf[c->tail] = val;
    c->tail = (c->tail + 1) % 16;
    c->count++;
    pthread_cond_signal(&c->not_empty);
    pthread_mutex_unlock(&c->mu);
}

int chan_recv(Chan *c, int *out) {
    pthread_mutex_lock(&c->mu);
    while (c->count == 0 && !c->closed) pthread_cond_wait(&c->not_empty, &c->mu);
    if (c->count == 0) { pthread_mutex_unlock(&c->mu); return 0; }
    *out = c->buf[c->head];
    c->head = (c->head + 1) % 16;
    c->count--;
    pthread_cond_signal(&c->not_full);
    pthread_mutex_unlock(&c->mu);
    return 1;
}

void chan_close(Chan *c) {
    pthread_mutex_lock(&c->mu);
    c->closed = 1;
    pthread_cond_broadcast(&c->not_empty);
    pthread_mutex_unlock(&c->mu);
}

Chan gen_ch, dbl_ch, add_ch;

void *generate(void *arg) {
    for (int i = 1; i <= 5; i++) chan_send(&gen_ch, i);
    chan_close(&gen_ch);
    return NULL;
}

void *double_stage(void *arg) {
    int val;
    while (chan_recv(&gen_ch, &val)) chan_send(&dbl_ch, val * 2);
    chan_close(&dbl_ch);
    return NULL;
}

void *add10_stage(void *arg) {
    int val;
    while (chan_recv(&dbl_ch, &val)) chan_send(&add_ch, val + 10);
    chan_close(&add_ch);
    return NULL;
}

int main(void) {
    chan_init(&gen_ch); chan_init(&dbl_ch); chan_init(&add_ch);

    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, generate, NULL);
    pthread_create(&t2, NULL, double_stage, NULL);
    pthread_create(&t3, NULL, add10_stage, NULL);

    int results[16], ri = 0, val;
    while (chan_recv(&add_ch, &val)) results[ri++] = val;

    pthread_join(t1, NULL); pthread_join(t2, NULL); pthread_join(t3, NULL);

    for (int i = 0; i < ri; i++) {
        if (i > 0) printf(" ");
        printf("%d", results[i]);
    }
    printf("\n");
    return 0;
}
