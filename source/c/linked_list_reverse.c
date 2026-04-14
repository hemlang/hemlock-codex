// gcc -o linked_list_reverse linked_list_reverse.c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node { int val; struct Node *next; } Node;

Node *make_node(int val, Node *next) {
    Node *n = malloc(sizeof(Node));
    n->val = val; n->next = next;
    return n;
}

Node *build_list(int arr[], int n) {
    Node *head = NULL;
    for (int i = n - 1; i >= 0; i--) head = make_node(arr[i], head);
    return head;
}

void print_list(Node *head, const char *label) {
    printf("%s:", label);
    for (Node *c = head; c; c = c->next) printf(" %d", c->val);
    printf("\n");
}

Node *reverse_list(Node *head) {
    Node *prev = NULL, *curr = head;
    while (curr) {
        Node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5};
    Node *head = build_list(arr, 5);
    print_list(head, "original");
    head = reverse_list(head);
    print_list(head, "reversed");
    return 0;
}
