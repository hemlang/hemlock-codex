// gcc -o memory_pool memory_pool.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SLOT_SIZE 8
#define POOL_SLOTS 8

char pool_buf[SLOT_SIZE * POOL_SLOTS];
int used[POOL_SLOTS];
int alloc_count = 0;

void pool_init(void) {
    memset(used, 0, sizeof(used));
    alloc_count = 0;
}

void *pool_alloc(void) {
    for (int i = 0; i < POOL_SLOTS; i++) {
        if (!used[i]) {
            used[i] = 1;
            alloc_count++;
            printf("alloc slot %d\n", i);
            return pool_buf + i * SLOT_SIZE;
        }
    }
    printf("pool exhausted!\n");
    return NULL;
}

void pool_free(int slot_index) {
    if (used[slot_index]) {
        used[slot_index] = 0;
        alloc_count--;
        printf("freed slot %d\n", slot_index);
    }
}

int active_count(void) {
    int count = 0;
    for (int i = 0; i < POOL_SLOTS; i++) if (used[i]) count++;
    return count;
}

int main(void) {
    pool_init();
    long long *s0 = pool_alloc();
    long long *s1 = pool_alloc();
    long long *s2 = pool_alloc();
    long long *s3 = pool_alloc();
    long long *s4 = pool_alloc();

    *s0 = 100; *s1 = 200;

    printf("active: %d\n", active_count());

    pool_free(1); pool_free(3);

    printf("active after free: %d\n", active_count());

    pool_alloc(); pool_alloc(); pool_alloc();

    printf("final active: %d\n", active_count());
    printf("pool freed\n");
    return 0;
}
