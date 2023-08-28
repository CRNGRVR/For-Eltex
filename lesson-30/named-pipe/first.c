//
//  24.08.2023
//
//  Программа 1
//  Передача данных в именованных каналах
//

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

    mode_t fifoMode = S_IRWXU | S_IRWXG | S_IRWXO;  //  rwx-rwx-rwx
    int firstFD = 0;
    int secondFD = 0;

    char buff = NULL;
    char *hello = "hello";

    //  Флаг: получен ли хоть один байт сообщения
    bool received = false;


    mkfifo(FIRST_PIPE_FILE, fifoMode);
    mkfifo(SECOND_PIPE_FILE, fifoMode);

    secondFD = open(SECOND_PIPE_FILE, O_RDONLY | O_NONBLOCK);
    while (1) {
        //  Чтение из канала, прерывается когда read < 0 и прочитан по крайней
        //  мере один байт

        if (0 < read(secondFD, &buff, 1) || !received) {
            printf("%c", buff);
        } else {
            printf("\n");
            break;
        }

        if(buff != NULL) received = true;
    }

    firstFD = open(FIRST_PIPE_FILE, O_WRONLY);
    write(firstFD, hello, strlen(hello));

    close(firstFD);
    close(secondFD);

    exit(EXIT_SUCCESS);
}