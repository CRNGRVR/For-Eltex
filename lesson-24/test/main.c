/**
 *  20.07.2023
 *
 *  Ну тут чисто с процессами поиграться
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t current_pid;
    pid_t child_pid;
    int status;

    child_pid = fork();

    if(child_pid == 0) {
        //  Ветка дочернего процесса
        printf("\nChild PID: %d\nPPID: %d\n\n", getpid(), getppid());
        exit(1);
    } else {
        //  Ветка родительского процесса
        printf("\nParent PID: %d\nChild PID: %d\n\n", getpid(), child_pid);
        wait(&status);
        printf("status: %d\n", status);
    }
}
