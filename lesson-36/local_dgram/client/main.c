/**
 *  18.10.2023
 *
 *  Простой обмен через сокеты
 *  Семейство: AF_LOCAL
 *  Тип: SOCK_DGRAM
 *  Клиент
*/

#include <sys/types.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

//  При использовании SOCK_DGRAM сервер и клиент биндятся на разные файлы
#define FILEPATH_SERV "/tmp/local_dgram_example"
#define FILEPATH_CLIENT "/tmp/local_dgram_example2"
#define BUFF_SIZE 10

int main() {
    char buff[BUFF_SIZE];
    int sockFD;
    struct sockaddr_un serv, client;
    socklen_t size = sizeof(struct sockaddr_un);

    serv.sun_family = AF_LOCAL;
    strcpy(serv.sun_path, FILEPATH_SERV);

    client.sun_family = AF_LOCAL;
    strcpy(client.sun_path, FILEPATH_CLIENT);

    sockFD = socket(AF_LOCAL, SOCK_DGRAM, 0);

    //  Привязка адреса обязательна для клиента SOCK_DGRAM
    bind(sockFD, (struct sockaddr*)&client, sizeof(struct sockaddr_un));
    sendto(sockFD, "Hello!", BUFF_SIZE, 0, (struct sockaddr*)&serv, size);
    recvfrom(sockFD, buff, BUFF_SIZE, 0, (struct sockaddr*)&serv, &size);
    printf("%s\n", buff);
    close(sockFD);
    unlink(FILEPATH_CLIENT);
}
