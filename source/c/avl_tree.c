// gcc -o avl_tree avl_tree.c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value, height;
    struct Node *left, *right;
} Node;

Node *new_node(int value) {
    Node *n = malloc(sizeof(Node));
    n->value = value; n->height = 1; n->left = n->right = NULL;
    return n;
}

int height(Node *n) { return n ? n->height : 0; }
int max_val(int a, int b) { return a > b ? a : b; }
int get_balance(Node *n) { return n ? height(n->left) - height(n->right) : 0; }

Node *right_rotate(Node *y) {
    Node *x = y->left, *t2 = x->right;
    x->right = y; y->left = t2;
    y->height = max_val(height(y->left), height(y->right)) + 1;
    x->height = max_val(height(x->left), height(x->right)) + 1;
    return x;
}

Node *left_rotate(Node *x) {
    Node *y = x->right, *t2 = y->left;
    y->left = x; x->right = t2;
    x->height = max_val(height(x->left), height(x->right)) + 1;
    y->height = max_val(height(y->left), height(y->right)) + 1;
    return y;
}

Node *insert(Node *root, int value) {
    if (!root) return new_node(value);
    if (value < root->value) root->left = insert(root->left, value);
    else if (value > root->value) root->right = insert(root->right, value);
    else return root;

    root->height = max_val(height(root->left), height(root->right)) + 1;
    int balance = get_balance(root);

    if (balance > 1 && value < root->left->value) return right_rotate(root);
    if (balance < -1 && value > root->right->value) return left_rotate(root);
    if (balance > 1 && value > root->left->value) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    if (balance < -1 && value < root->right->value) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
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
    int values[] = {10, 20, 30, 40, 50, 25};
    Node *root = NULL;
    for (int i = 0; i < 6; i++) root = insert(root, values[i]);

    inorder(root);
    printf("inorder:");
    for (int i = 0; i < result_len; i++) printf(" %d", result_buf[i]);
    printf("\n");
    return 0;
}
