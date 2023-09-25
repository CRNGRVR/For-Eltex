/**
 *  28.07.2023
 *
 *  Построение древа процессов:
 *
 *              [1]
 *              / \
 *             2   3
 *            / \   \
 *           4   5   6
 *
 *  Процесс 1. Ветвление до процессов 2 и 3
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    printf("\nProcess 1.\nPID: %d\nPPID: %d\n\n", getpid(), getppid());

    //  PID процессов 2 и 3
    pid_t pid2;
    pid_t pid3;
    int status2;
    int status3;

    pid2 = fork();

    if (pid2 == 0) {
        //  Процесс 2
        execl("./tree2", "tree2", NULL);
        exit(1);
    } else {
        //  Процесс 1
        pid3 = fork();

        if (pid3 == 0) {
            //  Процесс 3
            execl("./tree3", "tree3", NULL);
            exit(1);
        } else {
            //  Процесс 1 ожидает процессы 2 и 3
            waitpid(pid2, &status2, 0);
            waitpid(pid3, &status3, 0);
        }
    }

    exit(1);
}
