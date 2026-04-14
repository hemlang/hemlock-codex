// gcc -o manual_linked_list manual_linked_list.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node: 4 bytes i32 value + 4 bytes padding + 8 bytes pointer = 16 bytes
// We use a proper struct for idiomatic C

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node *head = NULL;

void push(int val) {
    Node *node = malloc(sizeof(Node));
    node->value = val;
    node->next = head;
    head = node;
}

void traverse(void) {
    printf("list:");
    for (Node *c = head; c; c = c->next) printf(" %d", c->value);
    printf("\n");
}

void free_all(void) {
    int count = 0;
    while (head) {
        Node *next = head->next;
        free(head);
        head = next;
        count++;
    }
    printf("freed %d nodes\n", count);
}

int main(void) {
    push(10); push(20); push(30);
    traverse();
    free_all();
    return 0;
}
