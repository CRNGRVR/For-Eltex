/**
 *  12.10.2023
 *
 *  Сервер: простой обмен в разделяемой памяти.
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
    key_t key_shmem;
    int shm_id;
    char *shm_p;

    key_t key_semaphor;
    int sem_id;

    //  s - server, c - client
    struct sembuf sem_s_lock;
    struct sembuf sem_s_unlock;
    struct sembuf sem_c_lock;
    struct sembuf sem_c_unlock;

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


    key_shmem = ftok(PATHNAME, PROJID_SHMEM);
    shm_id = shmget(key_shmem, 10, IPC_CREAT | S_IRUSR | S_IWUSR);
    shm_p = shmat(shm_id, 0, 0);

    key_semaphor = ftok(PATHNAME, PROJID_SEMAPHOR);
    sem_id = semget(key_semaphor, 2, IPC_CREAT | S_IRUSR | S_IWUSR);


    strcpy(shm_p, "Hello!");

    //  Разблокировка клиента для чтения и ответа
    semop(sem_id, &sem_c_unlock, 1);

    //  Блокировка в ожидании ответа
    semop(sem_id, &sem_s_lock, 1);
    printf("%s\n", shm_p);

    shmdt(shm_p);
    shmctl(shm_id, IPC_RMID, NULL);
}
