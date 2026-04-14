// gcc -o simple_chat simple_chat.c -lpthread
// Chat pattern: Alice and Bob exchange messages via pipes
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

int alice_pipe[2]; // Bob writes to alice_pipe, Alice reads from it
int bob_pipe[2];   // Alice writes to bob_pipe, Bob reads from it

void send_msg(int fd, const char *msg) {
    write(fd, msg, strlen(msg) + 1);
}

int recv_msg(int fd, char *buf, int bufsz) {
    return read(fd, buf, bufsz);
}

void *alice_thread(void *arg) {
    char buf[256];
    send_msg(bob_pipe[1], "Hi Bob! How are you?");
    recv_msg(alice_pipe[0], buf, sizeof(buf));
    printf("Alice received: %s\n", buf);

    send_msg(bob_pipe[1], "I'm working on a Hemlock project!");
    recv_msg(alice_pipe[0], buf, sizeof(buf));
    printf("Alice received: %s\n", buf);

    send_msg(bob_pipe[1], "Thanks! Talk later.");
    recv_msg(alice_pipe[0], buf, sizeof(buf));
    printf("Alice received: %s\n", buf);
    return NULL;
}

void *bob_thread(void *arg) {
    char buf[256];
    recv_msg(bob_pipe[0], buf, sizeof(buf));
    printf("Bob received: %s\n", buf);
    send_msg(alice_pipe[1], "Hey Alice! I'm great, you?");

    recv_msg(bob_pipe[0], buf, sizeof(buf));
    printf("Bob received: %s\n", buf);
    send_msg(alice_pipe[1], "That sounds awesome!");

    recv_msg(bob_pipe[0], buf, sizeof(buf));
    printf("Bob received: %s\n", buf);
    send_msg(alice_pipe[1], "Bye Alice!");
    return NULL;
}

int main(void) {
    pipe(alice_pipe); pipe(bob_pipe);
    pthread_t a, b;
    pthread_create(&a, NULL, alice_thread, NULL);
    pthread_create(&b, NULL, bob_thread, NULL);
    pthread_join(a, NULL);
    pthread_join(b, NULL);
    printf("Chat ended.\n");
    return 0;
}
