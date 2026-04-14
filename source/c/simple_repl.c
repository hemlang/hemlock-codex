// gcc -o simple_repl simple_repl.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct { char tokens[16][32]; int count; } Tokens;

Tokens tokenize(const char *expr) {
    Tokens t = {{}, 0};
    char num[32]; int ni = 0;
    for (int i = 0; expr[i]; i++) {
        char ch = expr[i];
        if (ch == ' ') {
            if (ni > 0) { num[ni] = '\0'; strcpy(t.tokens[t.count++], num); ni = 0; }
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            if (ni > 0) { num[ni] = '\0'; strcpy(t.tokens[t.count++], num); ni = 0; }
            t.tokens[t.count][0] = ch; t.tokens[t.count][1] = '\0'; t.count++;
        } else {
            num[ni++] = ch;
        }
    }
    if (ni > 0) { num[ni] = '\0'; strcpy(t.tokens[t.count++], num); }
    return t;
}

double evaluate(const char *expr) {
    Tokens t = tokenize(expr);
    if (t.count == 0) return 0;
    double result = atof(t.tokens[0]);
    for (int i = 1; i + 1 < t.count; i += 2) {
        char op = t.tokens[i][0];
        double operand = atof(t.tokens[i+1]);
        if (op == '+') result += operand;
        else if (op == '-') result -= operand;
        else if (op == '*') result *= operand;
        else if (op == '/') result /= operand;
    }
    return result;
}

int main(void) {
    const char *inputs[] = {"2 + 3", "10 * 4", "100 / 7", "50 - 18", "2 + 3 * 4"};
    int ni = 5;
    printf("=== Simple Calculator ===\n");
    for (int i = 0; i < ni; i++) {
        double result = evaluate(inputs[i]);
        long long int_result = (long long)result;
        if ((double)int_result == result) printf("> %s = %lld\n", inputs[i], int_result);
        else printf("> %s = %g\n", inputs[i], result);
    }
    printf("=== Done ===\n");
    return 0;
}
