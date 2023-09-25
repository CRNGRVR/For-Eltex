/**
 *  24.08.2023
 *
 *  Программа 2
 *  Передача данных в именованных каналах
*/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#define FIRST_PIPE_FILE "firstFile"
#define SECOND_PIPE_FILE "secondFile"

int main() {
    //  first:  1 -> 2
    //  second: 1 <- 2

    int firstFD;
    int secondFD;

    char buff = NULL;
    char *hi = "Hi";

    //  Флаг: получен ли хоть один байт сообщения
    bool received = false;


    secondFD = open(SECOND_PIPE_FILE, O_WRONLY);
    write(secondFD, hi, strlen(hi));

    firstFD = open(FIRST_PIPE_FILE, O_RDONLY | O_NONBLOCK);
    while (1) {
        //  Чтение из канала, прерывается когда read < 0 и прочитан по крайней
        //  мере один байт

        if (0 < read(firstFD, &buff, 1) || !received) {
            printf("%c", buff);
        } else {
            close(secondFD);
            close(firstFD);
            printf("\n");
            break;
        }

        if(buff != NULL) received = true;
    }

    exit(EXIT_SUCCESS);
}
