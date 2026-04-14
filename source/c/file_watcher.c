// gcc -o file_watcher file_watcher.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    const char *watch_path = "/tmp/hemlock_watch_test.txt";

    // Write initial file
    FILE *f = fopen(watch_path, "w");
    fputs("initial content", f); fclose(f);
    long t1 = (long)clock();
    printf("[watcher] monitoring: %s\n", watch_path);
    printf("[watcher] initial write at t=%ld\n", t1);

    // Read back
    char buf[256] = {0};
    f = fopen(watch_path, "r"); fgets(buf, sizeof(buf), f); fclose(f);
    printf("[watcher] initial content: %s\n", buf);

    // Modify
    f = fopen(watch_path, "w");
    fputs("modified content", f); fclose(f);
    long t2 = (long)clock();
    printf("[watcher] file modified at t=%ld\n", t2);

    // Detect
    memset(buf, 0, sizeof(buf));
    f = fopen(watch_path, "r"); fgets(buf, sizeof(buf), f); fclose(f);
    if (strcmp(buf, "modified content") == 0) {
        printf("[watcher] file change detected\n");
        printf("[watcher] new content: %s\n", buf);
    } else {
        printf("[watcher] no change detected\n");
    }

    if (t2 >= t1) printf("[watcher] modification time advanced\n");

    printf("[watcher] done\n");
    remove(watch_path);
    return 0;
}
