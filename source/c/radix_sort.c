// gcc -o radix_sort radix_sort.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void counting_sort_by_digit(int arr[], int n, int exp) {
    int *output = malloc(n * sizeof(int));
    int count[10] = {0};
    for (int i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        count[digit]--;
        output[count[digit]] = arr[i];
    }
    memcpy(arr, output, n * sizeof(int));
    free(output);
}

void radix_sort(int arr[], int n) {
    if (n == 0) return;
    int max_val = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] > max_val) max_val = arr[i];
    for (int exp = 1; max_val / exp > 0; exp *= 10) {
        counting_sort_by_digit(arr, n, exp);
    }
}

int main(void) {
    int arr[] = {64, 34, 25, 12, 22, 11, 90, 1, 45, 78};
    int n = 10;
    radix_sort(arr, n);
    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");
    return 0;
}
