// gcc -o lowest_common_ancestor lowest_common_ancestor.c
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

Node *lca(Node *root, int p, int q) {
    if (!root) return NULL;
    if (p < root->value && q < root->value) return lca(root->left, p, q);
    if (p > root->value && q > root->value) return lca(root->right, p, q);
    return root;
}

int main(void) {
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    Node *root = NULL;
    for (int i = 0; i < 7; i++) root = insert(root, values[i]);

    Node *r1 = lca(root, 20, 40);
    printf("lca(20, 40): %d\n", r1->value);

    Node *r2 = lca(root, 20, 70);
    printf("lca(20, 70): %d\n", r2->value);

    Node *r3 = lca(root, 60, 80);
    printf("lca(60, 80): %d\n", r3->value);

    return 0;
}
