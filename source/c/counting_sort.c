// gcc -o counting_sort counting_sort.c
#include <stdio.h>
#include <stdlib.h>

void counting_sort(int arr[], int n) {
    if (n == 0) return;
    int max_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) max_val = arr[i];
    }
    int *count = calloc(max_val + 1, sizeof(int));
    for (int i = 0; i < n; i++) count[arr[i]]++;
    int idx = 0;
    for (int i = 0; i <= max_val; i++) {
        while (count[i] > 0) {
            arr[idx++] = i;
            count[i]--;
        }
    }
    free(count);
}

int main(void) {
    int arr[] = {64, 34, 25, 12, 22, 11, 90, 1, 45, 78};
    int n = 10;
    counting_sort(arr, n);
    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");
    return 0;
}
