// gcc -o trie trie.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHA 26

typedef struct TrieNode {
    struct TrieNode *children[ALPHA];
    int is_end;
} TrieNode;

TrieNode *new_trie_node(void) {
    TrieNode *n = calloc(1, sizeof(TrieNode));
    return n;
}

void trie_insert(TrieNode *root, const char *word) {
    TrieNode *node = root;
    for (int i = 0; word[i]; i++) {
        int idx = word[i] - 'a';
        if (!node->children[idx]) node->children[idx] = new_trie_node();
        node = node->children[idx];
    }
    node->is_end = 1;
}

int trie_search(TrieNode *root, const char *word) {
    TrieNode *node = root;
    for (int i = 0; word[i]; i++) {
        int idx = word[i] - 'a';
        if (!node->children[idx]) return 0;
        node = node->children[idx];
    }
    return node->is_end;
}

int trie_starts_with(TrieNode *root, const char *prefix) {
    TrieNode *node = root;
    for (int i = 0; prefix[i]; i++) {
        int idx = prefix[i] - 'a';
        if (!node->children[idx]) return 0;
        node = node->children[idx];
    }
    return 1;
}

int main(void) {
    TrieNode *root = new_trie_node();
    const char *words[] = {"apple", "app", "application", "bat", "ball"};
    for (int i = 0; i < 5; i++) trie_insert(root, words[i]);

    printf("search \"app\": %s\n", trie_search(root, "app") ? "true" : "false");
    printf("search \"ap\": %s\n", trie_search(root, "ap") ? "true" : "false");
    printf("search \"bat\": %s\n", trie_search(root, "bat") ? "true" : "false");
    printf("starts_with \"app\": %s\n", trie_starts_with(root, "app") ? "true" : "false");
    printf("starts_with \"ba\": %s\n", trie_starts_with(root, "ba") ? "true" : "false");
    printf("starts_with \"cat\": %s\n", trie_starts_with(root, "cat") ? "true" : "false");
    return 0;
}
