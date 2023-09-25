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

    struct mq_attr attr1;
    struct mq_attr attr2;
    attr1.mq_maxmsg = 4;
    attr1.mq_msgsize = MSG_SIZE; 
    attr2.mq_maxmsg = 4;
    attr2.mq_msgsize = MSG_SIZE;


    strcpy(msgOut, "Hello!");

    fd1 = mq_open(PATHNAME1, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR, &attr1);
    fd2 = mq_open(PATHNAME2, O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR, &attr2);

    mq_send(fd1, msgOut, MSG_SIZE, 1);
    printf("Клиенту отправлено сообщение. Ожидание ответа...\n");
    mq_receive(fd2, msgIn, MSG_SIZE, &priorityIn);
    printf("%s\n", msgIn);

    mq_close(fd1);
    mq_close(fd2);
    mq_unlink(PATHNAME1);
    mq_unlink(PATHNAME2);
    exit(EXIT_SUCCESS);
}
