// gcc -o bst_insert_search_delete bst_insert_search_delete.c
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

int search(Node *root, int value) {
    if (!root) return 0;
    if (value == root->value) return 1;
    if (value < root->value) return search(root->left, value);
    return search(root->right, value);
}

Node *find_min(Node *root) {
    while (root->left) root = root->left;
    return root;
}

Node *delete_node(Node *root, int value) {
    if (!root) return NULL;
    if (value < root->value) root->left = delete_node(root->left, value);
    else if (value > root->value) root->right = delete_node(root->right, value);
    else {
        if (!root->left) { Node *tmp = root->right; free(root); return tmp; }
        if (!root->right) { Node *tmp = root->left; free(root); return tmp; }
        Node *successor = find_min(root->right);
        root->value = successor->value;
        root->right = delete_node(root->right, successor->value);
    }
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

    if (search(root, 40)) printf("search 40: found\n");
    else printf("search 40: not found\n");

    if (search(root, 25)) printf("search 25: found\n");
    else printf("search 25: not found\n");

    root = delete_node(root, 30);

    inorder(root);
    printf("inorder:");
    for (int i = 0; i < result_len; i++) printf(" %d", result_buf[i]);
    printf("\n");
    return 0;
}
