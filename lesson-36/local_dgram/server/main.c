/**
 *  18.10.2023
 *
 *  Простой обмен через сокеты
 *  Семейство: AF_LOCAL
 *  Тип: SOCK_DGRAM
 *  Сервер
*/

#include <sys/types.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define FILEPATH_SERV "/tmp/local_dgram_example"
#define BUFF_SIZE 10

int main() {
    char buff[BUFF_SIZE];
    int sockFD;
    struct sockaddr_un serv, client;
    socklen_t size = sizeof(struct sockaddr_un);

    serv.sun_family = AF_LOCAL;
    strcpy(serv.sun_path, FILEPATH_SERV);

    sockFD = socket(AF_LOCAL, SOCK_DGRAM, 0);
    bind(sockFD, (struct sockaddr*)&serv, size);
    recvfrom(sockFD, buff, BUFF_SIZE, 0, (struct sockaddr*)&client,
             &size);
    printf("%s\n", buff);
    sendto(sockFD, "Hi", BUFF_SIZE, 0, (struct sockaddr*)&client, size);
    close(sockFD);
    unlink(FILEPATH_SERV);
}
