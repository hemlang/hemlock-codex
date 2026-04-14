// gcc -o error_cleanup_defer error_cleanup_defer.c
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

int cleaned = 0;

void cleanup(void) {
    cleaned = 1;
    printf("resource cleaned up\n");
}

jmp_buf jb;

void risky_operation(void) {
    void *p = malloc(64);
    // defer cleanup(); defer free(p);
    // simulate throw via longjmp
    cleanup();
    free(p);
    longjmp(jb, 1);
}

int main(void) {
    if (setjmp(jb) == 0) {
        risky_operation();
    } else {
        printf("error handled\n");
    }
    return 0;
}
