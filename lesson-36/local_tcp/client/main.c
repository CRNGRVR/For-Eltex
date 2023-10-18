/**
 *  18.10.2023
 *
 *  Простой обмен через сокеты
 *  Семейство: AF_LOCAL
 *  Тип: SOCK_STREAM
 *  Клиент
*/

#include <sys/types.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define FILEPATH "/tmp/local_stream_example"


int main() {
    char buff[10];
    int sockFD;
    struct sockaddr_un serv;

    serv.sun_family = AF_LOCAL;
    strcpy(serv.sun_path, FILEPATH);

    sockFD = socket(AF_LOCAL, SOCK_STREAM, 0);
    connect(sockFD, &serv, sizeof(struct sockaddr_un));

    recv(sockFD, buff, 10, 0);
    printf("%s\n", buff);
    send(sockFD, "Hello!", 10, 0);
    close(sockFD);
}
