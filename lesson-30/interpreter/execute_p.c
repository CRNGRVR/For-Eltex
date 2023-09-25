#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ACCES_FOR_ALL S_IRWXU | S_IRWXG | S_IRWXO

void execute_p(char *path, char **args, bool isLastExecInQueue, char *inputFP,
               char *outputFP) {

    int inputFD = open(inputFP, O_RDWR | O_CREAT, ACCES_FOR_ALL);
    int outputFD = open(outputFP, O_RDWR | O_CREAT, ACCES_FOR_ALL);

    pid_t pid = fork();

    if (0 == pid) {

        dup2(inputFD, STDIN_FILENO);

        if (isLastExecInQueue) {
            //  Если выполняется последняя программа, её вывод должен попасть
            //  на экран
            dup2(STDOUT_FILENO, outputFD);
        } else {
            dup2(outputFD, STDOUT_FILENO);
        }

        int result = execv(path, args);
        if (0 != result){
            printf("Ошибка выполнения\n");
            exit(EXIT_FAILURE);
        }
    } else {
        waitpid(pid, NULL, NULL);
    }

    close(inputFD);
    close(outputFD);
}
