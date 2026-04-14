// gcc -o malloc_free malloc_free.c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n = 10;
    int *arr = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) arr[i] = i * i;

    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}
