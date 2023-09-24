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
#include <sys/stat.h>
#include <fcntl.h>
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

    buffOut.priority = 1;
    strcpy(buffOut.payload, "Hello!");

    key = ftok(PATHNAME, PROJID);
    msqFd = msgget(key, IPC_CREAT | S_IRUSR | S_IWUSR);

    msgsnd(msqFd, &buffOut, sizeof(struct msgBuff), NULL);
    printf("Клиенту отправлено сообщение. Ожидание ответа...\n");
    msgrcv(msqFd, &buffIn, sizeof(struct msgBuff), 2, NULL);
    printf("%s\n", buffIn.payload);
    msgctl(msqFd, IPC_RMID, NULL);  //  Удаление очереди
    exit(EXIT_SUCCESS);
}
