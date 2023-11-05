/**
 *  05.11.2023
 *
 *  Сервер udp
 *  Обмен сообщениями с raw-клиентом, самостоятельно заполняющим заголовок
 *  транспортного уровня
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define SERV_ADDR "127.0.0.1"
#define SERV_PORT 5678
#define BUFF_SIZE 50

//  Сервер получает от клиента строку, модифицирует и посылает обратно
int main() {
    char buff[BUFF_SIZE] = {};
    int sockFD;
    struct sockaddr_in serv, client;
    socklen_t size = sizeof(struct sockaddr_in);
    struct in_addr addr;

    addr.s_addr = inet_addr(SERV_ADDR);
    serv.sin_family = AF_INET;
    serv.sin_addr = addr;
    serv.sin_port = htons(SERV_PORT);

    sockFD = socket(AF_INET, SOCK_DGRAM, 0);
    bind(sockFD, &serv, size);

    recvfrom(sockFD, buff, BUFF_SIZE, 0, &client, &size);
    printf("Received: %s\n", buff);

    strcat(buff, ", world!");
    sendto(sockFD, buff, BUFF_SIZE, 0, &client, size);
    close(sockFD);
}
