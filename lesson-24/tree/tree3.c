//
//  28.07.2023
//
//  Построение древа процессов:
//
//              1
//             / \
//            2  [3] 
//           / \   \
//          4   5   6
//
//  Процесс 3. Ветвление до процесса 6
//

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {

    printf("\nProcess 3.\nPID: %d\nPPID: %d\n\n", getpid(), getppid());

    pid_t pid6;

    int status6;

    pid6 = fork();
    if(pid6 == 0) {

        //  Процесс 6
        execl("./tree6", "tree6", NULL);
    }
    else {

        //  Процесс 3 ожидает процесс 6
        waitpid(pid6, &status6, 0);
    }
}