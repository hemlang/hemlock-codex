// gcc -o expression_tree expression_tree.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char value[8];
    struct Node *left, *right;
} Node;

Node *new_node(const char *value) {
    Node *n = malloc(sizeof(Node));
    strncpy(n->value, value, 7); n->value[7] = '\0';
    n->left = n->right = NULL;
    return n;
}

int evaluate(Node *node) {
    if (!node->left && !node->right) return atoi(node->value);
    int left_val = evaluate(node->left);
    int right_val = evaluate(node->right);
    if (strcmp(node->value, "+") == 0) return left_val + right_val;
    if (strcmp(node->value, "-") == 0) return left_val - right_val;
    if (strcmp(node->value, "*") == 0) return left_val * right_val;
    return 0;
}

int main(void) {
    // Build: (2 + 3) * (4 - 1)
    Node *add_node = new_node("+");
    add_node->left = new_node("2");
    add_node->right = new_node("3");

    Node *sub_node = new_node("-");
    sub_node->left = new_node("4");
    sub_node->right = new_node("1");

    Node *mul_node = new_node("*");
    mul_node->left = add_node;
    mul_node->right = sub_node;

    int result = evaluate(mul_node);
    printf("result: %d\n", result);
    return 0;
}
