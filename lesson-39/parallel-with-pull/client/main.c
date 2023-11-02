/**
 *  30.10.2023
 *
 *  Клиент параллельного сервера с предварительным пуллом
 *  Эксперимент на максимальное количество подключений без потерь
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "../properties.h"
#include "single_client.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./client [Count of connections]\n");
        exit(EXIT_FAILURE);
    }

    int clientsCount = atoi(argv[1]);
    pthread_t clientThread[clientsCount];

    for (int index = 0; index < clientsCount; index++) {
        int res = pthread_create(&clientThread[index], NULL, single_client,
                                 NULL);
        if (res == -1) {
           perror("Creation");
        }
    }

    for (int index = 0; index < clientsCount; index++) {
        pthread_join(clientThread[index], NULL);
    }

    print_result();
}
