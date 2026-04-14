// gcc -o priority_queue priority_queue.c
#include <stdio.h>

#define MAX 64

typedef struct { int heap[MAX]; int size; } PQ;

void pq_init(PQ *pq) { pq->size = 0; }

void pq_swap(PQ *pq, int i, int j) {
    int tmp = pq->heap[i]; pq->heap[i] = pq->heap[j]; pq->heap[j] = tmp;
}

void pq_insert(PQ *pq, int val) {
    pq->heap[pq->size++] = val;
    int i = pq->size - 1;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (pq->heap[i] < pq->heap[parent]) { pq_swap(pq, i, parent); i = parent; }
        else break;
    }
}

int pq_extract_min(PQ *pq) {
    int min = pq->heap[0];
    int last = pq->heap[--pq->size];
    if (pq->size > 0) {
        pq->heap[0] = last;
        int i = 0;
        while (1) {
            int left = 2*i+1, right = 2*i+2, smallest = i;
            if (left < pq->size && pq->heap[left] < pq->heap[smallest]) smallest = left;
            if (right < pq->size && pq->heap[right] < pq->heap[smallest]) smallest = right;
            if (smallest != i) { pq_swap(pq, i, smallest); i = smallest; }
            else break;
        }
    }
    return min;
}

int main(void) {
    PQ pq; pq_init(&pq);
    int values[] = {5, 3, 7, 1, 4, 2};
    for (int i = 0; i < 6; i++) pq_insert(&pq, values[i]);

    for (int i = 0; i < 6; i++) {
        if (i > 0) printf(" ");
        printf("%d", pq_extract_min(&pq));
    }
    printf("\n");
    return 0;
}
