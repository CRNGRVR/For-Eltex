#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

struct sembuf operations[2];
int semid;

//  Удаление семафоров при выходе из программы
void _semwork_end(int sig);

void semwork_init() {
    operations[0].sem_num = 0;
    operations[0].sem_op = -1;
    operations[0].sem_flg = 0;

    operations[1].sem_num = 0;
    operations[1].sem_op = 1;
    operations[1].sem_flg = 0;

    key_t key_semaphor = ftok("./server", 0);
    semid = semget(key_semaphor, 1, IPC_CREAT | S_IRUSR | S_IWUSR);

    //  Удаление ресурсов при [CTRL] + [c]
    signal(SIGINT, _semwork_end);
}

//  Блокирование для ожидания
void semwork_pending() {
    semop(semid, &operations[0], 1);
}

//  Разблокировка
void semwork_unlock() {
    semop(semid, &operations[1], 1);
}


void _semwork_end(int sig) {
    printf("End.\n");
    semctl(semid, 0, IPC_RMID);
    exit(EXIT_SUCCESS);
}
