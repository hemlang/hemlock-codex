// gcc -o file_io file_io.c
#include <stdio.h>
#include <string.h>

int main(void) {
    const char *path = "/tmp/hemlock_file_io_test.txt";

    // Write
    FILE *f = fopen(path, "w");
    if (f) { fprintf(f, "Hello from Hemlock!\nLine 2\nLine 3\n"); fclose(f); }

    // Read back
    FILE *f2 = fopen(path, "r");
    if (f2) {
        char buf[256];
        while (fgets(buf, sizeof(buf), f2)) fputs(buf, stdout);
        fclose(f2);
    }

    remove(path);
    printf("file I/O complete\n");
    return 0;
}
