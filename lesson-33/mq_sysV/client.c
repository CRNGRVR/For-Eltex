/**
 *  24.09.2023
 *
 *  System 5 - клиент и сервер. Обменяться словами Hello и hi. Сервер говорит
 *  что отправил и ждёт. Получает, выводит и завершается.
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

#define PATHNAME "server"
#define PROJID 5

struct msgBuff {
    long priority;
    char payload[10];
};

int main() {
    struct msgBuff buffOut;
    struct msgBuff buffIn;
    key_t key;
    int msqFd;

    buffOut.priority = 2;
    strcpy(buffOut.payload, "Hi!");

    key = ftok(PATHNAME, PROJID);
    msqFd = msgget(key, NULL);

    if (-1 == msqFd) {
        printf("Сервер не запущен\n");
        exit(EXIT_FAILURE);
    }

    msgsnd(msqFd, &buffOut, sizeof(struct msgBuff), NULL);
    msgrcv(msqFd, &buffIn, sizeof(struct msgBuff), 1, NULL);
    printf("%s\n", buffIn.payload);
    exit(EXIT_SUCCESS);
}
