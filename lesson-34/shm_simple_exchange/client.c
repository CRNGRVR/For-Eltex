/**
 *  12.10.2023
 *
 *  Клиент: простой обмен в разделяемой памяти.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <string.h>

#define PATHNAME "./server"
#define PROJID_SHMEM 0
#define PROJID_SEMAPHOR 1

int main() {
    key_t key_shm;
    int shm_id;
    char *shm_p;

    key_t key_semaphor;
    int sem_id;
    struct sembuf sem_s_lock;
    struct sembuf sem_s_unlock;
    struct sembuf sem_c_lock;
    struct sembuf sem_c_unlock;

    //  s - server, c - client
    sem_s_lock.sem_num = 0;
    sem_s_lock.sem_op = -1;
    sem_s_lock.sem_flg = 0;

    sem_s_unlock.sem_num = 0;
    sem_s_unlock.sem_op = 1;
    sem_s_unlock.sem_flg = 0;

    sem_c_lock.sem_num = 1;
    sem_c_lock.sem_op = -1;
    sem_c_lock.sem_flg = 0;

    sem_c_unlock.sem_num = 1;
    sem_c_unlock.sem_op = 1;
    sem_c_unlock.sem_flg = 0;


    key_shm = ftok(PATHNAME, PROJID_SHMEM);
    shm_id = shmget(key_shm, 10, 0);
    shm_p = shmat(shm_id, 0, 0);

    key_semaphor = ftok(PATHNAME, PROJID_SEMAPHOR);
    sem_id = semget(key_semaphor, 2, 0);

    //  Блокировка клиента от чтения, чтобы сервер написал и разблокировал
    semop(sem_id, &sem_c_lock, 1);
    printf("%s\n", shm_p);

    for (int index = 0; index++; index < 10) shm_p[index] = 0;
    strcpy(shm_p, "Hi");

    //  Разблокировка сервера для вывода сообщения
    semop(sem_id, &sem_s_unlock, 1);
    shmdt(shm_p);
}
