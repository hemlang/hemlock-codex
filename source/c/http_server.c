// gcc -o http_server http_server.c -lpthread
// Simulated HTTP server using pthreads and pipes
#include <stdio.h>
#include <string.h>
#include <pthread.h>

typedef struct { const char *method; const char *path; } Request;
typedef struct { int status; const char *body; const char *method; const char *path; } Response;

Request requests[3] = {
    {"GET", "/"},
    {"GET", "/about"},
    {"GET", "/missing"}
};

Response responses[3];
int req_idx = 0;
pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t req_ready = PTHREAD_COND_INITIALIZER;
pthread_cond_t res_ready = PTHREAD_COND_INITIALIZER;
int req_available = 0, res_available = 0;
int current_req = -1, current_res = -1;

void *server(void *arg) {
    for (int i = 0; i < 3; i++) {
        pthread_mutex_lock(&mu);
        while (!req_available) pthread_cond_wait(&req_ready, &mu);
        int idx = current_req;
        req_available = 0;
        pthread_mutex_unlock(&mu);

        const char *body;
        int status;
        if (strcmp(requests[idx].path, "/") == 0) { status = 200; body = "Hello, World!"; }
        else if (strcmp(requests[idx].path, "/about") == 0) { status = 200; body = "About Page"; }
        else { status = 404; body = "Not Found"; }

        pthread_mutex_lock(&mu);
        responses[idx].status = status;
        responses[idx].body = body;
        responses[idx].method = requests[idx].method;
        responses[idx].path = requests[idx].path;
        current_res = idx;
        res_available = 1;
        pthread_cond_signal(&res_ready);
        pthread_mutex_unlock(&mu);
    }
    return NULL;
}

void *client_thread(void *arg) {
    for (int i = 0; i < 3; i++) {
        pthread_mutex_lock(&mu);
        current_req = i;
        req_available = 1;
        pthread_cond_signal(&req_ready);
        while (!res_available) pthread_cond_wait(&res_ready, &mu);
        int idx = current_res;
        res_available = 0;
        pthread_mutex_unlock(&mu);
        printf("[simulated] %s %s -> %d %s\n",
               responses[idx].method, responses[idx].path,
               responses[idx].status, responses[idx].body);
    }
    return NULL;
}

int main(void) {
    pthread_t srv, cli;
    pthread_create(&srv, NULL, server, NULL);
    pthread_create(&cli, NULL, client_thread, NULL);
    pthread_join(cli, NULL);
    pthread_join(srv, NULL);
    return 0;
}
