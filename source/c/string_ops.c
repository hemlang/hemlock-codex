// gcc -o string_ops string_ops.c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// to_upper in place
char *str_upper(const char *s, char *out) {
    int n = strlen(s);
    for (int i = 0; i <= n; i++) out[i] = toupper((unsigned char)s[i]);
    return out;
}

// starts_with
int starts_with(const char *s, const char *prefix) {
    return strncmp(s, prefix, strlen(prefix)) == 0;
}

// contains
int str_contains(const char *s, const char *sub) {
    return strstr(s, sub) != NULL;
}

// replace (first occurrence)
void str_replace(const char *s, const char *from, const char *to, char *out) {
    char *p = strstr(s, from);
    if (!p) { strcpy(out, s); return; }
    int prefix_len = p - s;
    strncpy(out, s, prefix_len);
    strcpy(out + prefix_len, to);
    strcat(out, p + strlen(from));
}

int main(void) {
    const char *s = "Hello, World!";
    printf("length: %zu\n", strlen(s));

    printf("concat: %s\n", "Hello, World!");

    const char *a = "abc", *b = "abc", *c = "def";
    printf("equal: %s\n", strcmp(a, b) == 0 ? "true" : "false");
    printf("less: %s\n", strcmp(a, c) < 0 ? "true" : "false");

    char *found = strstr(s, "World");
    printf("found at: %ld\n", found ? found - s : -1L);

    char replaced[64];
    str_replace(s, "World", "Hemlock", replaced);
    printf("replaced: %s\n", replaced);

    char upper[64];
    printf("upper: %s\n", str_upper(s, upper));
    printf("starts_with: %s\n", starts_with(s, "Hello") ? "true" : "false");
    printf("contains: %s\n", str_contains(s, "World") ? "true" : "false");

    // split by comma
    const char *csv = "one,two,three";
    char csv_copy[64];
    strcpy(csv_copy, csv);
    char *parts[8];
    int np = 0;
    char *tok = strtok(csv_copy, ",");
    while (tok) { parts[np++] = tok; tok = strtok(NULL, ","); }
    printf("split:");
    for (int i = 0; i < np; i++) {
        if (i > 0) printf(" |");
        printf(" %s", parts[i]);
    }
    printf("\n");
    return 0;
}
