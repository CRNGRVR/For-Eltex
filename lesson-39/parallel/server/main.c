/**
 *  24.10.2023
 *
 *  Параллельный сервер
 *  Слушающий сервер принимает запрос, порождает обслуживающий сервер, сообщает
 *  клиенту адрес, клиент подключается и обслуживается.
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "semwork.h"
#include "service.h"
#include "../properties.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./server [Count of pending connections]\n");
        exit(EXIT_FAILURE);
    }

    int clientsCount = atoi(argv[1]);
    int sockFD;
    struct sockaddr_in serv, client;
    struct in_addr addr;
    socklen_t peerlen;
    uint16_t portShift = 1;

    semwork_init();

    addr.s_addr = inet_addr(SERV_ADDR);
    serv.sin_family = AF_INET;
    serv.sin_addr = addr;
    serv.sin_port = htons(SERV_PORT);

    sockFD = socket(AF_INET, SOCK_STREAM, 0);

    int result = bind(sockFD, (struct sockaddr*)&serv,
                      sizeof(struct sockaddr_in));
    if (result == -1) {
        perror("");
        exit(EXIT_FAILURE);
    }

    listen(sockFD, clientsCount);

    //  Реализация слушающего сервера
    while (1) {
        if ((SERV_PORT + portShift) == 65534) portShift = 1;
        int acceptedFD = accept(sockFD, (struct sockaddr*)&client, &peerlen);
        pthread_t serverThread;
        struct sockaddr_in service_serv;
        struct in_addr addr;

        addr.s_addr = inet_addr(SERV_ADDR);
        service_serv.sin_family = AF_INET;
        service_serv.sin_addr = addr;
        service_serv.sin_port = htons(SERV_PORT + portShift);

        //  Порождение обслуживающего сервера и ожидание его готовности
        pthread_create(&serverThread, NULL, service, &service_serv);
        semwork_pending();

        send(acceptedFD, &service_serv, sizeof(struct sockaddr_in), 0);
        printf("listener send addres with port %d\n", (SERV_PORT + portShift));
        close(acceptedFD);
        portShift++;
    }
}
