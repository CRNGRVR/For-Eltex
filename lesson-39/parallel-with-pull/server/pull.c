#include <pthread.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include "../properties.h"
#include "pull_service_unit.h"
#include "semwork.h"

void *pull_service(void *args);
void pull_changeState(pull_service_unit *pull, bool value);

//  Мьютекс для защиты списка серверов пулла от некорректной записи и чтения
pthread_mutex_t pull_changeState_mutex = PTHREAD_MUTEX_INITIALIZER;
 
void pull_create(pull_service_unit *pull, int amount) {
    pthread_t serviceThreads[amount];

    for (int index = 0; index < amount; index++) {
        pull[index].index = index;
        //  Под пулл резервируются адреса следующие после слушающего сервера
        pull[index].port = SERV_PORT + index + 1;
        pull[index].available = true;
    }

    for (int index = 0; index < amount; index++) {
        pthread_create(&serviceThreads[index], NULL, pull_service,
                       &pull[index]);
    }
}

int pull_search(pull_service_unit *pull, int amount) {
    pthread_mutex_lock(&pull_changeState_mutex);
    for (int index = 0; index < amount; index++) {
        if (pull[index].available) {
            pthread_mutex_unlock(&pull_changeState_mutex);
            return index;
        }
    }

    pthread_mutex_unlock(&pull_changeState_mutex);
    return -1;
}

//  Функция, выполняемая потоком-сервером
void *pull_service(void *args) {
    pull_service_unit *serv = (pull_service_unit*)args;
    struct sockaddr_in server, client;
    struct in_addr addr;
    socklen_t peerlen;

    addr.s_addr = inet_addr(SERV_ADDR);
    server.sin_family = AF_INET;
    server.sin_addr = addr;
    server.sin_port = htons(serv->port);

    int sockFD = socket(AF_INET, SOCK_STREAM, 0);
    bind(sockFD, (struct sockaddr*)&server, sizeof(struct sockaddr_in));
    listen(sockFD, 1);

    while (1) {
        //  Разблокировка служающего сервера, когда обслуживающий готов к
        //  работе, и клиента можно уведомлять
        semwork_unlock();

        int acceptedFD = accept(sockFD, (struct sockaddr*)&client, &peerlen);
        pull_changeState(serv, false); //  Указание того, что сервер занят
        send(acceptedFD, "Hi", BUFF_SIZE, 0);
        printf("Serviced via pull-service %d\n", serv->index);
        close(acceptedFD);
        pull_changeState(serv, true);
    }
}


//  Потокобезопасное изменение значений в списке
void pull_changeState(pull_service_unit *pull, bool value) {
    //  Примитивы синхронизации здесь как защита от параллельного чтения
    pthread_mutex_lock(&pull_changeState_mutex);
    pull->available = value;
    pthread_mutex_unlock(&pull_changeState_mutex);
}
