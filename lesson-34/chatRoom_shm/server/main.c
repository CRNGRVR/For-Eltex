/**
 *  15.10.2023
 *
 *  Чат с общей комнатой: Сервер
 *  Назначение сервера в комплексе: создание и удаление ресурсов, необходимых
 *  для работы клиентов(создание разделяемой памяти и группы семафоров).
*/

#include <stdio.h>
#include "ssession.h"

int main() {
    int shm_id;
    int sem_id;

    ssession_start(&shm_id, &sem_id);

    //  Завершение по нажатию для отложенного удаления ресурсов
    getchar();

    ssession_end(shm_id, sem_id);
}
