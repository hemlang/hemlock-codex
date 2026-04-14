// gcc -o async_file_processing async_file_processing.c -lpthread
#include <stdio.h>
#include <pthread.h>
#include <string.h>

typedef struct {
    const char *name;
    int *data;
    int len;
    int sum;
    int max;
    int count;
} FileResult;

void *process_file(void *arg) {
    FileResult *r = (FileResult*)arg;
    r->sum = 0; r->max = r->data[0];
    for (int i = 0; i < r->len; i++) {
        r->sum += r->data[i];
        if (r->data[i] > r->max) r->max = r->data[i];
    }
    r->count = r->len;
    return NULL;
}

int main(void) {
    int data_a[] = {10, 20, 30, 40, 50};
    int data_b[] = {5, 15, 25, 35, 45, 55};
    int data_c[] = {100, 200, 300};

    FileResult results[3] = {
        {"data_a.csv", data_a, 5, 0, 0, 0},
        {"data_b.csv", data_b, 6, 0, 0, 0},
        {"data_c.csv", data_c, 3, 0, 0, 0}
    };

    pthread_t tasks[3];
    for (int i = 0; i < 3; i++) pthread_create(&tasks[i], NULL, process_file, &results[i]);
    for (int i = 0; i < 3; i++) pthread_join(tasks[i], NULL);

    for (int i = 0; i < 3; i++) {
        printf("%s: sum=%d max=%d count=%d\n",
               results[i].name, results[i].sum, results[i].max, results[i].count);
    }
    printf("all files processed\n");
    return 0;
}
