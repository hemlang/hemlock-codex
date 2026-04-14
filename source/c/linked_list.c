// gcc -o linked_list linked_list.c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node *push(Node *head, int value) {
    Node *n = malloc(sizeof(Node));
    n->value = value; n->next = head;
    return n;
}

void print_list(Node *head) {
    printf("list:");
    for (Node *cur = head; cur; cur = cur->next) printf(" %d", cur->value);
    printf("\n");
}

void free_list(Node *head) {
    while (head) { Node *tmp = head; head = head->next; free(tmp); }
}

int main(void) {
    Node *list = NULL;
    for (int i = 5; i >= 1; i--) list = push(list, i);
    print_list(list);
    free_list(list);
    return 0;
}
