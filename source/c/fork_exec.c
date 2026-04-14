// gcc -o fork_exec fork_exec.c -lpthread
// Using pthreads to match the Hemlock spawn/join pattern
#include <stdio.h>
#include <pthread.h>

typedef struct { int id; } WorkerArgs;

void *do_work(void *arg) {
    WorkerArgs *wa = (WorkerArgs*)arg;
    int id = wa->id;
    printf("child %d: computing\n", id);
    int sum = 0;
    for (int i = 0; i < 1000; i++) sum += i;
    printf("child %d: result = %d\n", id, sum);
    return NULL;
}

int main(void) {
    printf("parent: spawning children\n");
    pthread_t tasks[3];
    WorkerArgs args[3];
    for (int i = 0; i < 3; i++) {
        args[i].id = i;
        pthread_create(&tasks[i], NULL, do_work, &args[i]);
    }
    for (int i = 0; i < 3; i++) pthread_join(tasks[i], NULL);
    printf("parent: all children done\n");
    return 0;
}
