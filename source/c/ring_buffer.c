// gcc -o ring_buffer ring_buffer.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    int capacity, head, tail, count;
} RingBuffer;

RingBuffer *ring_new(int cap) {
    RingBuffer *rb = malloc(sizeof(RingBuffer));
    rb->data = malloc(cap * sizeof(int));
    rb->capacity = cap; rb->head = rb->tail = rb->count = 0;
    return rb;
}

int ring_write(RingBuffer *rb, int val) {
    if (rb->count == rb->capacity) {
        printf("ring full, cannot write %d\n", val);
        return 0;
    }
    rb->data[rb->tail] = val;
    rb->tail = (rb->tail + 1) % rb->capacity;
    rb->count++;
    return 1;
}

int ring_read(RingBuffer *rb, int *out) {
    if (rb->count == 0) { printf("ring empty\n"); return 0; }
    *out = rb->data[rb->head];
    rb->head = (rb->head + 1) % rb->capacity;
    rb->count--;
    return 1;
}

int main(void) {
    RingBuffer *rb = ring_new(4);
    ring_write(rb, 1); ring_write(rb, 2); ring_write(rb, 3); ring_write(rb, 4);

    int results[6], ri = 0, val;
    ring_read(rb, &val); results[ri++] = val;
    ring_read(rb, &val); results[ri++] = val;

    ring_write(rb, 5); ring_write(rb, 6);

    ring_read(rb, &val); results[ri++] = val;
    ring_read(rb, &val); results[ri++] = val;
    ring_read(rb, &val); results[ri++] = val;
    ring_read(rb, &val); results[ri++] = val;

    for (int i = 0; i < ri; i++) {
        if (i > 0) printf(" ");
        printf("%d", results[i]);
    }
    printf("\n");

    free(rb->data); free(rb);
    return 0;
}
