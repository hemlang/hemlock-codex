// gcc -o signal_handling signal_handling.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t got_signal = 0;

void handler(int sig) {
    got_signal = 1;
    printf("caught signal %d\n", sig);
}

int main(void) {
    signal(SIGUSR1, handler);
    printf("signal handler registered\n");
    raise(SIGUSR1);
    if (got_signal) printf("signal was handled\n");
    return 0;
}
