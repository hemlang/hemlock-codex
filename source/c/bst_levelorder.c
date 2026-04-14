// gcc -o bst_levelorder bst_levelorder.c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *left, *right;
} Node;

Node *new_node(int value) {
    Node *n = malloc(sizeof(Node));
    n->value = value; n->left = n->right = NULL;
    return n;
}

Node *insert(Node *root, int value) {
    if (!root) return new_node(value);
    if (value < root->value) root->left = insert(root->left, value);
    else if (value > root->value) root->right = insert(root->right, value);
    return root;
}

int main(void) {
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    Node *root = NULL;
    for (int i = 0; i < 7; i++) root = insert(root, values[i]);

    // BFS with a simple queue
    Node *queue[100];
    int head = 0, tail = 0;
    int result[100];
    int result_len = 0;

    if (root) queue[tail++] = root;
    while (head < tail) {
        Node *node = queue[head++];
        result[result_len++] = node->value;
        if (node->left) queue[tail++] = node->left;
        if (node->right) queue[tail++] = node->right;
    }

    printf("levelorder:");
    for (int i = 0; i < result_len; i++) printf(" %d", result[i]);
    printf("\n");
    return 0;
}
