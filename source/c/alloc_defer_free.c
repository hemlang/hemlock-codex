// gcc -o alloc_defer_free alloc_defer_free.c
#include <stdio.h>
#include <stdlib.h>

void demo(void) {
    int *a = malloc(8);
    int *b = malloc(8);
    int *c = malloc(8);
    // defer free(c); defer free(b); defer free(a); → free at end in reverse order

    *a = 10; *b = 20; *c = 30;

    int va = *a, vb = *b, vc = *c;
    printf("%d %d %d\n", va, vb, vc);
    printf("all memory freed\n");

    free(c); free(b); free(a);
}

int main(void) {
    demo();
    return 0;
}
