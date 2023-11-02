#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include "pull_service_unit.h"
#include "pull.h"
#include "semwork.h"
#include "service.h"
#include "../properties.h"

void listener_init(int *sockFD, int clientsCount) {
    struct sockaddr_in serv;
    struct in_addr addr;

    addr.s_addr = inet_addr(SERV_ADDR);
    serv.sin_family = AF_INET;
    serv.sin_addr = addr;
    serv.sin_port = htons(SERV_PORT);

    *sockFD = socket(AF_INET, SOCK_STREAM, 0);
    int result = bind(*sockFD, (struct sockaddr*)&serv,
                      sizeof(struct sockaddr_in));
    if (result == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    listen(*sockFD, clientsCount);
}

void listener_listen(int sockFD, pull_service_unit *pull, uint16_t *portShift) {
    if ((SERV_PORT + PULL + *portShift) == 65534) *portShift = 1;

    struct sockaddr_in service_serv, client;
    struct in_addr addr;
    socklen_t peerlen;
    addr.s_addr = inet_addr(SERV_ADDR);

    int acceptedFD = accept(sockFD, (struct sockaddr*)&client, &peerlen);
    int availableServer = pull_search(pull, PULL); //  Поиск свободного сервера

    if (availableServer != -1) {
        service_serv.sin_family = AF_INET;
        service_serv.sin_addr = addr;
        service_serv.sin_port = htons(pull[availableServer].port);

        //  Пользователь уведомляется когда сервер готов его обслужить
        semwork_pending();
        send(acceptedFD, &service_serv, sizeof(struct sockaddr_in), 0);
        close(acceptedFD);

    } else {
        //  Если нет свободного сервера, для обслуживания этого клиента
        //  создаётся отдельный

        pthread_t serverThread;
        service_serv.sin_family = AF_INET;
        service_serv.sin_addr = addr;
        service_serv.sin_port = htons(SERV_PORT + PULL + *portShift);

        //  Порождение обслуживающего сервера и ожидание его готовности
        pthread_create(&serverThread, NULL, service, &service_serv);
        semwork_pending();

        send(acceptedFD, &service_serv, sizeof(struct sockaddr_in), 0);
        close(acceptedFD);
        portShift++;
    }
}
