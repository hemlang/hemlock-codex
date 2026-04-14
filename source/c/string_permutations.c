// gcc -o string_permutations string_permutations.c
#include <stdio.h>
#include <string.h>

char arr[8];
int n;

void permute(int start) {
    if (start == n - 1) {
        printf("%s\n", arr);
        return;
    }
    for (int i = start; i < n; i++) {
        char tmp = arr[start]; arr[start] = arr[i]; arr[i] = tmp;
        permute(start + 1);
        tmp = arr[start]; arr[start] = arr[i]; arr[i] = tmp;
    }
}

int main(void) {
    strcpy(arr, "abc");
    n = strlen(arr);
    permute(0);
    return 0;
}
