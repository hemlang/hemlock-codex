// gcc -o file_defer_close file_defer_close.c
#include <stdio.h>
#include <string.h>

int main(void) {
    const char *path = "/tmp/hemlock_defer_test.txt";

    // Write file
    FILE *fw = fopen(path, "w");
    if (fw) { fputs("hello from defer", fw); fclose(fw); }

    // Read file (defer f.close() → fclose at end of scope)
    FILE *f = fopen(path, "r");
    if (f) {
        char contents[256] = {0};
        fgets(contents, sizeof(contents), f);
        fclose(f); // defer equivalent
        if (strcmp(contents, "hello from defer") == 0)
            printf("wrote and read back successfully\n");
    }

    remove(path);
    return 0;
}
