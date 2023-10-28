#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../properties.h"

//  Примитивы синхронизации для потокобезопасных счётчиков
pthread_mutex_t mutex_lost_listen = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_lost_service = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_success_service = PTHREAD_MUTEX_INITIALIZER;
int counter_lost_listen = 0;
int counter_lost_service = 0;
int counter_success_service = 0;

//  Потокобезопасное увеличение счётчиков
void lostOnListen_increment();
void lostOnServe_increment();
void successServiced_increment();

void *single_client() {
    char buff[BUFF_SIZE];
    int sockFD;
    struct sockaddr_in listen_serv, service_serv;
    struct in_addr addr;

    addr.s_addr = inet_addr(SERV_ADDR);
    listen_serv.sin_family = AF_INET;
    listen_serv.sin_addr = addr;
    listen_serv.sin_port = htons(SERV_PORT);

    //  Подключение к слушающему серверу и получение адреса от него
    sockFD = socket(AF_INET, SOCK_STREAM, 0);
    int resultConnectToListen = connect(sockFD, (struct sockaddr*)&listen_serv,
                                        sizeof(struct sockaddr_in));
    if (resultConnectToListen == -1) {
        //  Увеличение счётчика статистики при ошибке соединения
        lostOnListen_increment();
        close(sockFD);
        exit(EXIT_FAILURE);
    }

    recv(sockFD, &service_serv, sizeof(struct sockaddr_in), 0);
    close(sockFD);

    //  Подключение к обслуживающему серверу по адресу, полученному от
    //  слушающего
    sockFD = socket(AF_INET, SOCK_STREAM, 0);
    int resultConnectToService = connect(sockFD,
                                         (struct sockaddr*)&service_serv,
                                         sizeof(struct sockaddr_in));
    if (resultConnectToService == -1) {
        //  Увеличение счётчика статистики при ошибке соединения
        lostOnServe_increment();
        perror("Service");
        close(sockFD);
        exit(EXIT_FAILURE);
    }

    recv(sockFD, buff, BUFF_SIZE, 0);
    close(sockFD);

    successServiced_increment();
    printf("Serviced: %d\n", counter_success_service);
}

void print_result() {
    printf("Denied connections: %d, loose on service: %d\n",
           counter_lost_listen, counter_lost_service);
}


//  Счётчик отказа в обслуживании
void lostOnListen_increment() {
    pthread_mutex_lock(&mutex_lost_listen);
    counter_lost_listen++;
    pthread_mutex_unlock(&mutex_lost_listen);
}

//  Счётчик проблем, произошедших после успешного обмена с слушающим
void lostOnServe_increment() {
    pthread_mutex_lock(&mutex_lost_service);
    counter_lost_service++;
    pthread_mutex_unlock(&mutex_lost_service);
}

//  Счётчик обслуживания без ошибок
void successServiced_increment() {
    pthread_mutex_lock(&mutex_success_service);
    counter_success_service++;
    pthread_mutex_unlock(&mutex_success_service);
}
