#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include "../Common/properties.h"
#include "../Common/msg.h"
#include "../Common/user.h"


void ssession_start(int *shm_id, int *sem_id) {
    //  Разбиение на три операции исключительно в целях поддержания стиля кода
    int sizeUsers = sizeof(user) * MAX_USERS_COUNT;
    int sizeMSG = sizeof(msg_common) * MAX_LIST_OF_MSG;
    int sizeOfSHM = sizeUsers + sizeMSG;

    key_t shm_k = ftok(PATHNAME, PROJID_SHM);
    *shm_id = shmget(shm_k, sizeOfSHM, IPC_CREAT | S_IRUSR | S_IWUSR);

    key_t sem_k = ftok(PATHNAME, PROJID_SEM);
    *sem_id = semget(sem_k, 4, IPC_CREAT | S_IRUSR | S_IWUSR);


    struct sembuf operations[8];

    operations[SEM_N_UPLOAD_LOCK].sem_num = 0;
    operations[SEM_N_UPLOAD_LOCK].sem_op = -1;
    operations[SEM_N_UPLOAD_LOCK].sem_flg = 0;

    operations[SEM_N_UPLOAD_UNLOCK].sem_num = 0;
    operations[SEM_N_UPLOAD_UNLOCK].sem_op = 1;
    operations[SEM_N_UPLOAD_UNLOCK].sem_flg = 0;

    operations[SEM_M_UPLOAD_LOCK].sem_num = 1;
    operations[SEM_M_UPLOAD_LOCK].sem_op = -1;
    operations[SEM_M_UPLOAD_LOCK].sem_flg = 0;

    operations[SEM_M_UPLOAD_UNLOCK].sem_num = 1;
    operations[SEM_M_UPLOAD_UNLOCK].sem_op = 1;
    operations[SEM_M_UPLOAD_UNLOCK].sem_flg = 0;

    operations[SEM_N_HANDLER_LOCK].sem_num = 2;
    operations[SEM_N_HANDLER_LOCK].sem_op = -1;
    operations[SEM_N_HANDLER_LOCK].sem_flg = 0;

    operations[SEM_N_HANDLER_UNLOCK].sem_num = 2;
    operations[SEM_N_HANDLER_UNLOCK].sem_op = 1;
    operations[SEM_N_HANDLER_UNLOCK].sem_flg = 0;

    operations[SEM_M_HANDLER_LOCK].sem_num = 3;
    operations[SEM_M_HANDLER_LOCK].sem_op = -1;
    operations[SEM_M_HANDLER_LOCK].sem_flg = 0;

    operations[SEM_M_HANDLER_UNLOCK].sem_num = 3;
    operations[SEM_M_HANDLER_UNLOCK].sem_op = 1;
    operations[SEM_M_HANDLER_UNLOCK].sem_flg = 0;

    //  Изначально эти операции должны быть доступными к выполнению для
    //  блокирующего процесса
    semop(*sem_id, &operations[SEM_N_UPLOAD_UNLOCK], 1);
    semop(*sem_id, &operations[SEM_M_UPLOAD_UNLOCK], 1);

    //  После запуска на первом клиенте обновление сообщений должно произойти
    //  сразу
    semop(*sem_id, &operations[SEM_M_HANDLER_UNLOCK], 1);

    printf("SEM ID: %d\n", *sem_id);
    printf("Press [ENTER] to close server.\n");
}

void ssession_end(int shm_id, int sem_id) {
    shmctl(shm_id, IPC_RMID, NULL);
    semctl(sem_id, 4, IPC_RMID);
}
