// gcc -o two_sum two_sum.c
#include <stdio.h>
#include <stdlib.h>

// Simple hash map using open addressing
#define HASH_SIZE 1024
typedef struct { int key, val, used; } Entry;
Entry htable[HASH_SIZE];

void hmap_init(void) {
    for (int i = 0; i < HASH_SIZE; i++) htable[i].used = 0;
}

int hmap_hash(int key) {
    unsigned int h = (unsigned int)(key + 10000);
    return h % HASH_SIZE;
}

void hmap_set(int key, int val) {
    int h = hmap_hash(key);
    while (htable[h].used && htable[h].key != key) h = (h + 1) % HASH_SIZE;
    htable[h].key = key; htable[h].val = val; htable[h].used = 1;
}

int hmap_get(int key, int *out) {
    int h = hmap_hash(key);
    int start = h;
    while (htable[h].used) {
        if (htable[h].key == key) { *out = htable[h].val; return 1; }
        h = (h + 1) % HASH_SIZE;
        if (h == start) break;
    }
    return 0;
}

int main(void) {
    int nums[] = {2, 7, 11, 15};
    int n = 4;
    int target = 9;
    hmap_init();

    for (int i = 0; i < n; i++) {
        int complement = target - nums[i];
        int j;
        if (hmap_get(complement, &j)) {
            printf("indices: %d, %d\n", j, i);
            return 0;
        }
        hmap_set(nums[i], i);
    }
    printf("not found\n");
    return 0;
}
