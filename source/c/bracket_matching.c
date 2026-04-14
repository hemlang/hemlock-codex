// gcc -o bracket_matching bracket_matching.c
#include <stdio.h>
#include <string.h>

int is_balanced(const char *s) {
    char stack[1024];
    int top = 0;
    for (int i = 0; s[i]; i++) {
        char c = s[i];
        if (c == '(' || c == '{' || c == '[') {
            stack[top++] = c;
        } else if (c == ')' || c == '}' || c == ']') {
            if (top == 0) return 0;
            char t = stack[--top];
            if (c == ')' && t != '(') return 0;
            if (c == '}' && t != '{') return 0;
            if (c == ']' && t != '[') return 0;
        }
    }
    return top == 0;
}

int main(void) {
    const char *tests[] = {"({[]})", "({[}])", ""};
    for (int i = 0; i < 3; i++) {
        if (is_balanced(tests[i]))
            printf("\"%s\" -> balanced\n", tests[i]);
        else
            printf("\"%s\" -> not balanced\n", tests[i]);
    }
    return 0;
}
