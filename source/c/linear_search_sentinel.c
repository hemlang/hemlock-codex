// gcc -o linear_search_sentinel linear_search_sentinel.c
#include <stdio.h>

// Returns index or -1 if not found
int linear_search_sentinel(int arr[], int n, int target) {
    int last = arr[n - 1];
    arr[n - 1] = target;

    int i = 0;
    while (arr[i] != target) i++;

    arr[n - 1] = last;

    if (i < n - 1) return i;
    if (arr[n - 1] == target) return n - 1;
    return -1;
}

int main(void) {
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int n = 10;

    int result1 = linear_search_sentinel(arr, n, 23);
    if (result1 >= 0) printf("search 23: found at index %d\n", result1);
    else printf("search 23: not found\n");

    int result2 = linear_search_sentinel(arr, n, 50);
    if (result2 >= 0) printf("search 50: found at index %d\n", result2);
    else printf("search 50: not found\n");

    return 0;
}
