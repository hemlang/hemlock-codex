// gcc -o binary_search_iterative binary_search_iterative.c
#include <stdio.h>

// Returns index or -1 if not found
int binary_search(int arr[], int n, int target) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int main(void) {
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int n = 10;

    int result1 = binary_search(arr, n, 23);
    if (result1 >= 0) printf("search 23: found at index %d\n", result1);
    else printf("search 23: not found\n");

    int result2 = binary_search(arr, n, 50);
    if (result2 >= 0) printf("search 50: found at index %d\n", result2);
    else printf("search 50: not found\n");

    return 0;
}
