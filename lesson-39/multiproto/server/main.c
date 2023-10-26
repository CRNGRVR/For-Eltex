/**
 *  26.10.2023
 *
 *  Мультипротокольный сервер
 *  Позволяет подключиться как по tcp, так и по udp, причём использует только
 *  один поток. Отправляет клиентам текущее время
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#include <time.h>
#include <string.h>

#define SERV_ADDR "127.0.0.1"
#define SERV_STREAM_PORT 5678
#define SERV_DGRAM_PORT 5679
#define BUFF_SIZE 50

void stream_respond(int sockFD, struct sockaddr *client);
void dgram_respond(int sockFD, struct sockaddr *client);
void getCurrentTime(char *strtime);

int main() {
    int sockFdStream, sockFdDgram;
    struct sockaddr_in serv_stream, client_stream, serv_dgram, client_dgram;
    struct in_addr addr;
    struct pollfd pfd[2];

    addr.s_addr = inet_addr(SERV_ADDR);

    serv_stream.sin_family = AF_INET;
    serv_stream.sin_addr = addr;
    serv_stream.sin_port = htons(SERV_STREAM_PORT);

    serv_dgram.sin_family = AF_INET;
    serv_dgram.sin_addr = addr;
    serv_dgram.sin_port = htons(SERV_DGRAM_PORT);

    sockFdStream = socket(AF_INET, SOCK_STREAM, 0);
    sockFdDgram = socket(AF_INET, SOCK_DGRAM, 0);

    bind(sockFdStream, (struct sockaddr*)&serv_stream,
         sizeof(struct sockaddr_in));
    bind(sockFdDgram, (struct sockaddr*)&serv_dgram,
         sizeof(struct sockaddr_in));
    listen(sockFdStream, 1);

    pfd[0].fd = sockFdStream;
    pfd[0].events = POLLIN;
    pfd[1].fd = sockFdDgram;
    pfd[1].events = POLLIN;


    while (1) {
        poll(pfd, 2, -1);

        if (pfd[0].revents == POLLIN) {
            stream_respond(sockFdStream, (struct sockaddr*)&client_stream);
        } else if (pfd[1].revents == POLLIN) {
            dgram_respond(sockFdDgram, (struct sockaddr*)&client_dgram);
        }
    }
}

//  Ответ по tcp
void stream_respond(int sockFD, struct sockaddr *client) {
    char time[BUFF_SIZE];
    socklen_t peerAddrLen;
    int acceptedSockFd = accept(sockFD, client, &peerAddrLen);
    getCurrentTime(time);
    send(acceptedSockFd, time, BUFF_SIZE, 0);
    close(acceptedSockFd);
}

//  Ответ по udp
void dgram_respond(int sockFD, struct sockaddr *client) {
    char buff;
    char time[BUFF_SIZE];
    socklen_t socklen = sizeof(struct sockaddr_in);

    //  Приём сообщения для заполнения адреса клиента
    recvfrom(sockFD, &buff, sizeof(char), 0, client, &socklen);
    getCurrentTime(time);
    sendto(sockFD, time, BUFF_SIZE, 0, client, socklen);
} 

//  Получение времени системы
void getCurrentTime(char *strtime) {
    time_t systime = time(0);
    strcpy(strtime, ctime(&systime));
}
