/**
 *  17.10.2023
 *
 *  Простое приложение с обработчиком сигнала USR1
*/

#include <stdio.h>
#include <signal.h>

void handler(int signum);

int main() {
    struct sigaction act;
    sigset_t sigset;

    sigemptyset(&sigset);
    sigaddset(&sigset, SIGUSR1);

    act.sa_handler = handler;
    act.sa_mask = sigset;

    sigaction(SIGUSR1, &act, 0);

    while (1) {}
}

void handler(int signum) {
    printf("Signal USR1(%d) received!\n", signum);
}
