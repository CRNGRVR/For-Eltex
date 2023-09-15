#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FILE_EXISTS 0
#define FILE_NEED_TO_CREATE 1
#define FILE_BUFF_SIZE 1000


void fileWork_open(char *fileName, char *buff, bool *flag) {

    int fd = open(fileName, O_RDWR);
    char buff_single;
    int counter = 0;

    if (-1 == fd) {
        *flag = FILE_NEED_TO_CREATE;
    } else {

        *flag = FILE_EXISTS;
        while (0 < read(fd, &buff_single, 1)) {
            buff[counter] = buff_single;
            counter++;
        }

        close(fd);
    }
}

void fileWork_save(char *fileName, char *buff, bool *flag) {

    int fd;
    int counter = 0;

    if (*flag == FILE_NEED_TO_CREATE) {
        fd = open(fileName, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    } else {
        fd = open(fileName, O_RDWR | O_TRUNC);
    }

    while (buff[counter] != 0 && counter != FILE_BUFF_SIZE) {
        write(fd, &buff[counter], 1);
        counter++;
    }

    close(fd);
}