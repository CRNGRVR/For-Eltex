//
//  08.09.2023
//
//  Программа, работающая с файлом. Её действия:
//  1. Создаёт файл
//  2. Открывает файл на запись
//  3. Пишет строку в файл
//  4. Закрываает
//  5. Открывает на чтение
//  6. Читает
//  7. Удаляет
//

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "tmp"


int main(int argc, char* argv[]) {

    if (2 > argc) {
        printf("Строка не введена\n");
        exit(EXIT_FAILURE);
    }


    //  Строка на запись
    char *str = argv[1];

    int fd = open(FILE_NAME, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    write(fd, str, strlen(str));
    close(fd);

    char buf;
    fd = open(FILE_NAME, O_RDONLY);

    while (0 < read(fd, &buf, 1)) {
        printf("%c", buf);
    }
    printf("\n");
    close(fd);

    remove(FILE_NAME);

    exit(EXIT_SUCCESS);
}
