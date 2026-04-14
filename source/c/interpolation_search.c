// gcc -o interpolation_search interpolation_search.c
#include <stdio.h>

int interpolation_search(int arr[], int n, int target) {
    int low = 0, high = n - 1;
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        if (low == high) {
            if (arr[low] == target) return low;
            return -1;
        }
        int range = arr[high] - arr[low];
        int pos = low + ((target - arr[low]) * (high - low)) / range;
        if (arr[pos] == target) return pos;
        else if (arr[pos] < target) low = pos + 1;
        else high = pos - 1;
    }
    return -1;
}

int main(void) {
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int n = 10;

    int result1 = interpolation_search(arr, n, 23);
    if (result1 >= 0) printf("search 23: found at index %d\n", result1);
    else printf("search 23: not found\n");

    int result2 = interpolation_search(arr, n, 50);
    if (result2 >= 0) printf("search 50: found at index %d\n", result2);
    else printf("search 50: not found\n");

    return 0;
}
