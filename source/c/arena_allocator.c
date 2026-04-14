// gcc -o arena_allocator arena_allocator.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARENA_SIZE 1024

char arena[ARENA_SIZE];
int offset = 0;

void *arena_alloc(int size) {
    if (offset + size > ARENA_SIZE) {
        printf("arena out of memory!\n");
        return NULL;
    }
    void *p = arena + offset;
    offset += size;
    return p;
}

void arena_reset(void) { offset = 0; }

int main(void) {
    int *a = arena_alloc(4);
    int *b = arena_alloc(4);
    int *c = arena_alloc(4);
    int *d = arena_alloc(4);
    int *e = arena_alloc(4);

    *a = 100; *b = 200; *c = 300; *d = 400; *e = 500;

    printf("slot 0: %d\n", *a);
    printf("slot 1: %d\n", *b);
    printf("slot 2: %d\n", *c);
    printf("slot 3: %d\n", *d);
    printf("slot 4: %d\n", *e);

    printf("arena used: %d bytes\n", offset);
    // Stack-allocated arena, no explicit free needed
    printf("arena freed\n");
    return 0;
}
