/**
 *  22.08.2023
 *
 *  Передача данных в неименованных каналах
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main() {
    pid_t child;

    //  Дескрипторы для обмена
    //  fd1: Parent -> Child
    //  fd2: Parent <- Child
    int fd1[2];
    int fd2[2];

    char buff1;
    char buff2;

    char *hello = "hello";
    char *hi = "hi";

    pipe(fd1);
    pipe(fd2);

    child = fork();


    if (0 == child) {
        //  Дочерний процесc

        //  Закрытие неиспользуемых дескрипторов
        close(fd1[1]);
        close(fd2[0]);

        //  Чтение до конца "файла" по 1 байту и вывод
        while (0 < read(fd1[0], &buff1, 1)) {
            printf("%c", buff1);
        }
        printf("\n");

        close(fd1[0]);

        write(fd2[1], hello, 6);
        close(fd2[1]);

        exit(EXIT_SUCCESS);

    } else {
        //  Родительский процесс

        //  Закрытие неиспользуемых дескрипторов
        close(fd1[0]);
        close(fd2[1]);

        write(fd1[1], hi, 3);
        close(fd1[1]);


        //  Чтение до конца "файла" по 1 байту и вывод
        while (0 < read(fd2[0], &buff2, 1)) {
            printf("%c", buff2);
        }
        printf("\n");

        close(fd2[0]);

        exit(EXIT_SUCCESS);
    }
}
