// gcc -o lru_cache lru_cache.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key, val;
    struct Node *prev, *next;
} Node;

#define HASH_SIZE 16
typedef struct {
    Node *map[HASH_SIZE];
    Node *head, *tail;
    int capacity, size;
} LRU;

Node *new_node(int key, int val) {
    Node *n = malloc(sizeof(Node));
    n->key = key; n->val = val; n->prev = n->next = NULL;
    return n;
}

void remove_node(LRU *cache, Node *n) {
    n->prev->next = n->next;
    n->next->prev = n->prev;
}

void add_to_front(LRU *cache, Node *n) {
    n->next = cache->head->next;
    n->prev = cache->head;
    cache->head->next->prev = n;
    cache->head->next = n;
}

void lru_init(LRU *cache, int cap) {
    cache->capacity = cap; cache->size = 0;
    memset(cache->map, 0, sizeof(cache->map));
    cache->head = new_node(0, 0);
    cache->tail = new_node(0, 0);
    cache->head->next = cache->tail;
    cache->tail->prev = cache->head;
}

int lru_get(LRU *cache, int key) {
    int h = ((unsigned)key) % HASH_SIZE;
    for (Node *n = cache->map[h]; n; n = n->next == cache->map[h] ? NULL : n->next) {
        // Use a simple linear scan instead
        break;
    }
    // Simple linear scan for correctness
    Node *found = NULL;
    for (int i = 0; i < HASH_SIZE; i++) {
        Node *n = cache->map[i];
        if (n && n->key == key) { found = n; break; }
    }
    if (!found) { printf("get(%d) -> miss\n", key); return -1; }
    remove_node(cache, found);
    add_to_front(cache, found);
    printf("get(%d) -> %d (hit)\n", key, found->val);
    return found->val;
}

void lru_put(LRU *cache, int key, int val) {
    // Check existing
    Node *found = NULL;
    int found_slot = -1;
    for (int i = 0; i < HASH_SIZE; i++) {
        if (cache->map[i] && cache->map[i]->key == key) { found = cache->map[i]; found_slot = i; break; }
    }
    if (found) {
        found->val = val;
        remove_node(cache, found);
        add_to_front(cache, found);
        printf("put(%d, %d) -> updated\n", key, val);
    } else {
        Node *n = new_node(key, val);
        int slot = ((unsigned)key) % HASH_SIZE;
        cache->map[slot] = n;
        add_to_front(cache, n);
        cache->size++;
        if (cache->size > cache->capacity) {
            Node *evict = cache->tail->prev;
            remove_node(cache, evict);
            // Remove from map
            int ev_slot = ((unsigned)evict->key) % HASH_SIZE;
            cache->map[ev_slot] = NULL;
            cache->size--;
            printf("put(%d, %d) -> added, evicted key %d\n", key, val, evict->key);
            free(evict);
        } else {
            printf("put(%d, %d) -> added\n", key, val);
        }
    }
}

int main(void) {
    LRU cache;
    lru_init(&cache, 3);
    lru_put(&cache, 1, 10);
    lru_put(&cache, 2, 20);
    lru_put(&cache, 3, 30);
    lru_get(&cache, 2);
    lru_put(&cache, 4, 40);
    lru_get(&cache, 1);
    lru_get(&cache, 3);
    lru_get(&cache, 4);
    return 0;
}
