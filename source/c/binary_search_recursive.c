// gcc -o binary_search_recursive binary_search_recursive.c
#include <stdio.h>

int binary_search_rec(int arr[], int target, int low, int high) {
    if (low > high) return -1;
    int mid = low + (high - low) / 2;
    if (arr[mid] == target) return mid;
    else if (arr[mid] < target) return binary_search_rec(arr, target, mid + 1, high);
    else return binary_search_rec(arr, target, low, mid - 1);
}

int binary_search(int arr[], int n, int target) {
    return binary_search_rec(arr, target, 0, n - 1);
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
