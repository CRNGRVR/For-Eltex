/**
 *  26.10.2023
 *
 *  Клиент мультипротокольного сервера
 *  В зависимости от опции будет передан запрос текущего времени по tcp или udp
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define SERV_ADDR "127.0.0.1"
#define SERV_STREAM_PORT 5678
#define SERV_DGRAM_PORT 5679
#define BUFF_SIZE 50

void stream_request();
void dgram_request();

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        printf("Usage: ./client [-t or -u]\n");
        printf("-t for send tcp request\n");
        printf("-u for send udp request\n\n");
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "-t") == 0) {
        stream_request();
    } else if (strcmp(argv[1], "-u") == 0) {
        dgram_request();
    }
}

//  Запросить время по tcp
void stream_request() {
    char buff[BUFF_SIZE];
    int sockFD;
    struct sockaddr_in serv;
    struct in_addr addr;

    addr.s_addr = inet_addr(SERV_ADDR);

    serv.sin_family = AF_INET;
    serv.sin_addr = addr;
    serv.sin_port = htons(SERV_STREAM_PORT);
    sockFD = socket(AF_INET, SOCK_STREAM, 0);
    connect(sockFD, (struct sockaddr*)&serv, sizeof(struct sockaddr_in));

    recv(sockFD, buff, BUFF_SIZE, 0);
    printf("%s\n", buff);
    close(sockFD);
}

//  Запросить время по udp
void dgram_request() {
    char req_notice = 1;        //  Сообщение-заглушка
    char buff[BUFF_SIZE];
    int sockFD;
    struct sockaddr_in serv;
    socklen_t size = sizeof(struct sockaddr_in);
    struct in_addr addr;

    addr.s_addr = inet_addr(SERV_ADDR);
    serv.sin_family = AF_INET;
    serv.sin_addr = addr;
    serv.sin_port = htons(SERV_DGRAM_PORT);

    sockFD = socket(AF_INET, SOCK_DGRAM, 0);

    //  Отправка сообщения-заглушки для уведомления сервера о клиенте
    sendto(sockFD, &req_notice, sizeof(char), 0, (struct sockaddr*)&serv,
           size);
    recvfrom(sockFD, &buff, BUFF_SIZE, 0, (struct sockaddr*)&serv, &size);
    printf("%s\n", buff);
    close(sockFD);
}
