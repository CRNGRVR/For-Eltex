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
#define BUFF_SIZE 10

int main() {
    char buff[BUFF_SIZE];
    int sockFD;
    struct sockaddr_un serv;

    serv.sun_family = AF_LOCAL;
    strcpy(serv.sun_path, FILEPATH);

    sockFD = socket(AF_LOCAL, SOCK_STREAM, 0);

    //  Привязка адреса происходит в момент подключения
    connect(sockFD, (struct sockaddr*)&serv, sizeof(struct sockaddr_un));

    recv(sockFD, buff, BUFF_SIZE, 0);
    printf("%s\n", buff);
    send(sockFD, "Hello!", BUFF_SIZE, 0);
    close(sockFD);
}
