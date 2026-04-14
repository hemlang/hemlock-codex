// gcc -o parallel_merge_sort parallel_merge_sort.c -lpthread
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct { int *arr; int n; } SortArgs;

void merge_arrays(int *arr, int *left, int ln, int *right, int rn) {
    int i = 0, j = 0, k = 0;
    while (i < ln && j < rn) {
        if (left[i] <= right[j]) arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }
    while (i < ln) arr[k++] = left[i++];
    while (j < rn) arr[k++] = right[j++];
}

void *merge_sort_thread(void *arg) {
    SortArgs *sa = (SortArgs*)arg;
    int *arr = sa->arr; int n = sa->n;
    if (n <= 1) return NULL;

    int mid = n / 2;
    int *left = malloc(mid * sizeof(int));
    int *right = malloc((n - mid) * sizeof(int));
    memcpy(left, arr, mid * sizeof(int));
    memcpy(right, arr + mid, (n - mid) * sizeof(int));

    SortArgs la = {left, mid}, ra = {right, n - mid};

    if (n > 4) {
        pthread_t tl, tr;
        pthread_create(&tl, NULL, merge_sort_thread, &la);
        pthread_create(&tr, NULL, merge_sort_thread, &ra);
        pthread_join(tl, NULL);
        pthread_join(tr, NULL);
    } else {
        merge_sort_thread(&la);
        merge_sort_thread(&ra);
    }

    merge_arrays(arr, left, mid, right, n - mid);
    free(left); free(right);
    return NULL;
}

int main(void) {
    int arr[] = {38, 27, 43, 3, 9, 82, 10, 55};
    int n = 8;
    SortArgs sa = {arr, n};
    pthread_t t;
    pthread_create(&t, NULL, merge_sort_thread, &sa);
    pthread_join(t, NULL);

    printf("sorted:");
    for (int i = 0; i < n; i++) printf(" %d", arr[i]);
    printf("\n");
    return 0;
}
