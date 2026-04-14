// gcc -o test_runner test_runner.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    const char *name;
    // We'll use string comparison for everything
    char actual_s[64];
    char expected_s[64];
} Test;

Test tests[32];
int test_count = 0, passed = 0, failed = 0;

void add_test_str(const char *name, const char *actual, const char *expected) {
    Test *t = &tests[test_count++];
    t->name = name;
    strncpy(t->actual_s, actual, 63);
    strncpy(t->expected_s, expected, 63);
}

void add_test_int(const char *name, int actual, int expected) {
    char a[32], e[32];
    snprintf(a, 32, "%d", actual);
    snprintf(e, 32, "%d", expected);
    add_test_str(name, a, e);
}

void add_test_bool(const char *name, int actual, int expected) {
    add_test_str(name, actual ? "true" : "false", expected ? "true" : "false");
}

void run_tests(void) {
    printf("=== Test Results ===\n");
    for (int i = 0; i < test_count; i++) {
        if (strcmp(tests[i].actual_s, tests[i].expected_s) == 0) {
            printf("  PASS: %s\n", tests[i].name);
            passed++;
        } else {
            printf("  FAIL: %s (expected %s, got %s)\n",
                   tests[i].name, tests[i].expected_s, tests[i].actual_s);
            failed++;
        }
    }
    int total = passed + failed;
    printf("\n%d/%d tests passed\n", passed, total);
    if (failed > 0) printf("%d test(s) failed\n", failed);
}

// String helpers
int str_contains(const char *s, const char *sub) { return strstr(s, sub) != NULL; }
char *str_upper(const char *s, char *buf) {
    int n = strlen(s);
    for (int i = 0; i <= n; i++) buf[i] = (char)(s[i] >= 'a' && s[i] <= 'z' ? s[i] - 32 : s[i]);
    return buf;
}

int main(void) {
    char upper[64];
    // String tests
    add_test_int("string length", (int)strlen("hello"), 5);
    add_test_bool("string contains", str_contains("hello world", "world"), 1);
    add_test_str("string upper", str_upper("hello", upper), "HELLO");

    // Array tests
    int arr[] = {1, 2, 3, 4, 5};
    add_test_int("array length", 5, 5);
    add_test_int("array first", arr[0], 1);
    add_test_int("array last", arr[4], 5);
    add_test_bool("array contains", str_contains("1 2 3 4 5", "3"), 1);

    // Math tests
    add_test_int("addition", 2 + 3, 5);
    add_test_int("multiplication", 6 * 7, 42);
    add_test_bool("boolean logic", 1 && !0, 1);

    run_tests();
    return 0;
}
