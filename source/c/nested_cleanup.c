// gcc -o nested_cleanup nested_cleanup.c
#include <stdio.h>

void inner(void) {
    printf("inner running\n");
    printf("inner cleanup\n");
}

void middle(void) {
    printf("middle running\n");
    inner();
    printf("middle cleanup\n");
}

void outer(void) {
    printf("outer running\n");
    middle();
    printf("outer cleanup\n");
}

int main(void) {
    outer();
    return 0;
}
