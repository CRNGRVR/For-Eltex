/**
 *  18.10.2023
 *
 *  Приложение с ожиданием сигнала
*/

#include <stdio.h>
#include <signal.h>

void event(int signum);

int main() {
    int signum = 0;
    sigset_t sigset;
    sigfillset(&sigset);
    sigdelset(&sigset, SIGINT);
    sigprocmask(SIG_BLOCK, &sigset, NULL);

    while (1) {
        sigwait(&sigset, &signum);
        event(signum);
    }
}

void event(int signum) {
    if (signum == 10) printf("Event: signal USR1 received!\n");
}
