// gcc -o merge_sort merge_sort.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int *result, int *left, int llen, int *right, int rlen) {
    int i = 0, j = 0, k = 0;
    while (i < llen && j < rlen) {
        if (left[i] <= right[j]) result[k++] = left[i++];
        else result[k++] = right[j++];
    }
    while (i < llen) result[k++] = left[i++];
    while (j < rlen) result[k++] = right[j++];
}

void merge_sort(int arr[], int n) {
    if (n <= 1) return;
    int mid = n >> 1;
    int *left = malloc(mid * sizeof(int));
    int *right = malloc((n - mid) * sizeof(int));
    memcpy(left, arr, mid * sizeof(int));
    memcpy(right, arr + mid, (n - mid) * sizeof(int));
    merge_sort(left, mid);
    merge_sort(right, n - mid);
    merge(arr, left, mid, right, n - mid);
    free(left);
    free(right);
}

int main(void) {
    int arr[] = {64, 34, 25, 12, 22, 11, 90, 1, 45, 78};
    int n = 10;
    merge_sort(arr, n);
    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");
    return 0;
}
