/**
 *  05.11.2023
 *
 *  Клиент raw
 *  Обмен сообщениями с udp-сервером, заполняя заголовок транспортного уровня
 *  самостоятельно
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/udp.h>
#include <stdlib.h>

#define SERV_ADDR "127.0.0.1"
#define SERV_PORT 5678
#define FICTIONAL_CLIENT_PORT 8765
#define BUFF_SIZE 50

#define UDP_HEADER_SIZE 8
#define IP_HEADER_SIZE 20
#define PAYLOAD "Hello"

//  Очистка буфера для нового пакета
void clearBuff(char *buff, int len);

int main() {
    char buff[BUFF_SIZE + UDP_HEADER_SIZE] = {};
    int sockFD;
    struct sockaddr_in serv;
    struct in_addr addr;
    socklen_t len = sizeof(struct sockaddr_in);
    struct udphdr header;

    addr.s_addr = inet_addr(SERV_ADDR);
    serv.sin_family = AF_INET;
    serv.sin_addr = addr;
    serv.sin_port = htons(SERV_PORT);

    sockFD = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (sockFD == -1) {
        perror("");
        exit(EXIT_FAILURE);
    }

    //  Заполнение заголовка транспортного уровня
    header.dest = htons(SERV_PORT);
    header.source = htons(FICTIONAL_CLIENT_PORT);
    header.check = 0;
    header.len = htons(UDP_HEADER_SIZE + BUFF_SIZE);

    //  Заголовок добавляется в начало сообщения
    memcpy(buff, &header, UDP_HEADER_SIZE);
    memcpy(buff + UDP_HEADER_SIZE, PAYLOAD, BUFF_SIZE);
    sendto(sockFD, buff, BUFF_SIZE + UDP_HEADER_SIZE, 0, &serv,
           sizeof(struct sockaddr_in));
    clearBuff(buff, BUFF_SIZE + UDP_HEADER_SIZE);

    while (1) {
        recvfrom(sockFD, buff, BUFF_SIZE, 0, &serv, &len);

        struct udphdr *rcv_header = buff + IP_HEADER_SIZE;
        if (ntohs(rcv_header->dest) == FICTIONAL_CLIENT_PORT) {
            printf("%s\n", buff + IP_HEADER_SIZE + UDP_HEADER_SIZE);
            break;
        }

        clearBuff(buff, BUFF_SIZE + UDP_HEADER_SIZE);
    }
}

void clearBuff(char *buff, int len) {
    for (int i = 0; i < len; i++) {
        buff[i] = 0;
    }
}
