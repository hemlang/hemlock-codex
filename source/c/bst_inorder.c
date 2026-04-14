// gcc -o bst_inorder bst_inorder.c
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

int result_buf[20];
int result_len = 0;

void inorder(Node *root) {
    if (!root) return;
    inorder(root->left);
    result_buf[result_len++] = root->value;
    inorder(root->right);
}

int main(void) {
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    Node *root = NULL;
    for (int i = 0; i < 7; i++) root = insert(root, values[i]);

    inorder(root);
    printf("inorder:");
    for (int i = 0; i < result_len; i++) printf(" %d", result_buf[i]);
    printf("\n");
    return 0;
}
