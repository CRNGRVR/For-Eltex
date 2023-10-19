/**
 *  18.10.2023
 *
 *  Простой обмен через сокеты
 *  Семейство: AF_LOCAL
 *  Тип: SOCK_STREAM
 *  Сервер
*/

#include <sys/types.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define FILEPATH "/tmp/local_stream_example"
#define BUFF_SIZE 10

int main() {
    char buff[BUFF_SIZE];
    int sockFD;
    struct sockaddr_un serv, client;
    socklen_t peerAddrLen;

    serv.sun_family = AF_LOCAL;
    strcpy(serv.sun_path, FILEPATH);

    sockFD = socket(AF_LOCAL, SOCK_STREAM, 0);

    //  Привязка адреса
    bind(sockFD, (struct sockaddr*)&serv, sizeof(struct sockaddr_un));
    listen(sockFD, 1);

    int acceptedFD = accept(sockFD, (struct sockaddr*)&client, &peerAddrLen);
    send(acceptedFD, "Hi", BUFF_SIZE, 0);

    recv(acceptedFD, buff, BUFF_SIZE, 0);
    printf("%s\n", buff);
    close(acceptedFD);
    close(sockFD);
    unlink(FILEPATH);
}
