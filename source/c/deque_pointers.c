// gcc -o deque_pointers deque_pointers.c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *prev, *next;
} Node;

Node *dq_head = NULL, *dq_tail = NULL;
int dq_size = 0;

Node *make_node(int val) {
    Node *n = malloc(sizeof(Node));
    n->val = val; n->prev = n->next = NULL;
    return n;
}

void push_front(int val) {
    Node *node = make_node(val);
    if (!dq_head) { dq_head = dq_tail = node; }
    else { node->next = dq_head; dq_head->prev = node; dq_head = node; }
    dq_size++;
    printf("push_front: %d\n", val);
}

void push_back(int val) {
    Node *node = make_node(val);
    if (!dq_tail) { dq_head = dq_tail = node; }
    else { node->prev = dq_tail; dq_tail->next = node; dq_tail = node; }
    dq_size++;
    printf("push_back: %d\n", val);
}

int pop_front(void) {
    if (!dq_head) { printf("deque empty\n"); return 0; }
    Node *node = dq_head;
    int val = node->val;
    dq_head = node->next;
    if (dq_head) dq_head->prev = NULL;
    else dq_tail = NULL;
    free(node); dq_size--;
    printf("pop_front: %d\n", val);
    return val;
}

int pop_back(void) {
    if (!dq_tail) { printf("deque empty\n"); return 0; }
    Node *node = dq_tail;
    int val = node->val;
    dq_tail = node->prev;
    if (dq_tail) dq_tail->next = NULL;
    else dq_head = NULL;
    free(node); dq_size--;
    printf("pop_back: %d\n", val);
    return val;
}

void print_deque(void) {
    printf("deque:");
    for (Node *c = dq_head; c; c = c->next) printf(" %d", c->val);
    printf("\n");
}

int main(void) {
    push_front(1); push_front(2); push_back(3); push_back(4);
    print_deque();
    printf("size: %d\n", dq_size);
    pop_front(); pop_back();
    print_deque();
    printf("size: %d\n", dq_size);
    while (dq_head) pop_front();
    printf("deque cleared\n");
    return 0;
}
