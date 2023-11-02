/**
 *  30.10.2023
 *
 *  Параллельный сервер с предварительным пуллом
 *  Порождается определённое количество процессов обслуживающего сервера.
 *  Слушающий сервер принимает запрос, сообщает клиенту адрес свободного
 *  обслуживающего сервера, клиент подключается и обслуживается. Если в момент
 *  запроса клиента свободных обслуживающих серверов не оказалось, порождается
 *  новый.
*/

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include "semwork.h"
#include "pull_service_unit.h"
#include "pull.h"
#include "listener.h"
#include "../properties.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./server [Count of pending connections]\n");
        exit(EXIT_FAILURE);
    }

    int clientsCount = atoi(argv[1]);
    int sockFD;
    pull_service_unit pull[PULL];
    uint16_t portShift = 1;

    semwork_init();
    pull_create(pull, PULL);
    listener_init(&sockFD, clientsCount);

    //  Реализация слушающего сервера
    while (1) {
        listener_listen(sockFD, pull, &portShift);
    }
}
