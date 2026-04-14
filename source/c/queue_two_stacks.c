// gcc -o queue_two_stacks queue_two_stacks.c
#include <stdio.h>

#define MAX 64

typedef struct {
    int inbox[MAX], outbox[MAX];
    int in_top, out_top;
} Queue;

void queue_init(Queue *q) { q->in_top = q->out_top = 0; }

void enqueue(Queue *q, int val) { q->inbox[q->in_top++] = val; }

int dequeue(Queue *q) {
    if (q->out_top == 0) {
        while (q->in_top > 0) q->outbox[q->out_top++] = q->inbox[--q->in_top];
    }
    return q->outbox[--q->out_top];
}

int main(void) {
    Queue q;
    queue_init(&q);
    enqueue(&q, 1); enqueue(&q, 2); enqueue(&q, 3);

    int results[5];
    results[0] = dequeue(&q);
    results[1] = dequeue(&q);

    enqueue(&q, 4); enqueue(&q, 5);

    results[2] = dequeue(&q);
    results[3] = dequeue(&q);
    results[4] = dequeue(&q);

    for (int i = 0; i < 5; i++) {
        if (i > 0) printf(" ");
        printf("%d", results[i]);
    }
    printf("\n");
    return 0;
}
