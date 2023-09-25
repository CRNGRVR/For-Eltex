/**
 *  24.09.2023
 *
 *  POSIX - клиент и сервер. Обменяться словами Hello и hi. Сервер говорит
 *  что отправил и ждёт. Получает, выводит и завершается.
*/

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>
#include <stdlib.h>

#define PATHNAME1 "/tpmfile_mqp1"
#define PATHNAME2 "/tpmfile_mqp2"
#define MSG_SIZE 10

int main() {
    char msgOut[MSG_SIZE];
    char msgIn[MSG_SIZE];
    int priorityIn;

    mqd_t fd1;  //  server -> client
    mqd_t fd2;  //  server <- client


    strcpy(msgOut, "Hi!");

    fd1 = mq_open(PATHNAME1, O_RDONLY);
    fd2 = mq_open(PATHNAME2, O_WRONLY);

    mq_send(fd2, msgOut, MSG_SIZE, 1);
    mq_receive(fd1, msgIn, MSG_SIZE, &priorityIn);
    printf("%s\n", msgIn);

    mq_close(fd1);
    mq_close(fd2);
    exit(EXIT_SUCCESS);
}
