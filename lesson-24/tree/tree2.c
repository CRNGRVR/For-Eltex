//
//  28.07.2023
//
//  Построение древа процессов:
//
//              1
//             / \
//           [2]  3 
//           / \   \
//          4   5   6
//
//  Процесс 2. Ветвление до процессов 4 и 5
//

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {

    printf("\nProcess 2.\nPID: %d\nPPID: %d\n\n", getpid(), getppid());

    pid_t pid4;
    pid_t pid5;

    int status4;
    int status5;


    pid4 = fork();
    if(pid4 == 0) {

        //  Процесс 4
        execl("./tree4", "tree4", NULL);
    }
    else {

        //  Процесс 2
        pid5 = fork();

        if(pid5 == 0) {

            //  Процесс 5
            execl("./tree5", "tree5", NULL);
        }
        else {

            //  Процесс 2 oжидает процессы 4 и 5
            waitpid(pid4, &status4, 0);
            waitpid(pid5, &status5, 0);
        }
    }
}