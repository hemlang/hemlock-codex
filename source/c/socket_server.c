// gcc -o socket_server socket_server.c -lpthread
// Simulates the echo server/client pattern using pthreads and pipes
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

// pipe[0] = request read, pipe[1] = request write
// pipe2[0] = response read, pipe2[1] = response write
int req_pipe[2], res_pipe[2];

void *echo_server(void *arg) {
    char buf[256];
    ssize_t n;
    while ((n = read(req_pipe[0], buf, sizeof(buf) - 1)) > 0) {
        buf[n] = '\0';
        if (strcmp(buf, "__DONE__") == 0) break;
        char echo[280];
        snprintf(echo, sizeof(echo), "echo: %s", buf);
        write(res_pipe[1], echo, strlen(echo));
    }
    return NULL;
}

void *client(void *arg) {
    const char *messages[] = {"hello", "world", "goodbye"};
    for (int i = 0; i < 3; i++) {
        write(req_pipe[1], messages[i], strlen(messages[i]));
        char reply[256];
        ssize_t n = read(res_pipe[0], reply, sizeof(reply) - 1);
        if (n > 0) { reply[n] = '\0'; printf("%s\n", reply); }
    }
    write(req_pipe[1], "__DONE__", 8);
    return NULL;
}

int main(void) {
    pipe(req_pipe); pipe(res_pipe);

    pthread_t server_t, client_t;
    pthread_create(&server_t, NULL, echo_server, NULL);
    pthread_create(&client_t, NULL, client, NULL);

    pthread_join(client_t, NULL);
    pthread_join(server_t, NULL);

    close(req_pipe[0]); close(req_pipe[1]);
    close(res_pipe[0]); close(res_pipe[1]);

    printf("server pattern demonstrated\n");
    return 0;
}
