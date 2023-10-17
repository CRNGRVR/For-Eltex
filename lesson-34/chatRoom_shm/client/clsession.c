#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include "../Common/properties.h"
#include "../Common/user.h"
#include "../Common/msg.h"

int _countOfConnections(user *clients);
int _countMessages(msg_common *messages);
void _moveAllBackOnOne(msg_common *messages);


void clsession_start(char **shm_p, int *sem_id, struct sembuf *operations) {
    int shm_k = ftok(PATHNAME, PROJID_SHM);
    int shm_id = shmget(shm_k, 0, 0);
    *shm_p = shmat(shm_id, 0, 0);

    int sem_k = ftok(PATHNAME, PROJID_SEM);
    *sem_id = semget(sem_k, 0, 0);

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
}

void clsession_insertName(user client, char *shm_p, int sem_id,
                          struct sembuf *operations) {

    //  Защита от записи другими процессами
    semop(sem_id, &(operations[SEM_N_UPLOAD_LOCK]), 1);

    for (int index = 0; index < MAX_USERS_COUNT; index++) {
        if (((user*)shm_p)[index].pid == 0) {
            ((user*)shm_p)[index].pid = client.pid;
            strcpy(((user*)shm_p)[index].name, client.name);
            break;
        }
    }

    semop(sem_id, &(operations[SEM_N_UPLOAD_UNLOCK]), 1);

    //  Разблокировка обработчиков
    operations[SEM_N_HANDLER_UNLOCK].sem_op = _countOfConnections((user*)(shm_p));
    semop(sem_id, &(operations[SEM_N_HANDLER_UNLOCK]), 1);
}

void clsession_removeName(user client, char *shm_p, int sem_id,
                          struct sembuf *operations) {

    //  Защита от записи другими процессами
    semop(sem_id, &operations[SEM_N_UPLOAD_LOCK], 1);

    for (int index1 = 0; index1 < MAX_LIST_OF_MSG; index1++) {
        if (((user*)shm_p)[index1].pid == client.pid) {
            ((user*)shm_p)[index1].pid = 0;
            for (int index2 = 0; index2 < MAX_NAME_LENGTH; index2++) {
                ((user*)shm_p)[index1].name[index2] = 0;
            }

            break;
        }
    }

    semop(sem_id, &(operations[SEM_N_UPLOAD_UNLOCK]), 1);

    //  Разблокировка обработчиков
    operations[SEM_N_HANDLER_UNLOCK].sem_op = _countOfConnections((user*)(shm_p));
    semop(sem_id, &(operations[SEM_N_HANDLER_UNLOCK]), 1);
}


void clsession_insertMessage(msg_common message, char *shm_p, int sem_id,
                             struct sembuf *operations) {

    //  Защита от записи другими процессами
    semop(sem_id, &(operations[SEM_M_UPLOAD_LOCK]), 1);

    int currentMessagesCount = _countMessages((msg_common*)(shm_p + SHIFT_MESSAGES_POINTER));
    if (currentMessagesCount < MAX_LIST_OF_MSG) {
        ((msg_common*)(shm_p + SHIFT_MESSAGES_POINTER))[currentMessagesCount] = message;
    } else {
        _moveAllBackOnOne((msg_common*)(shm_p + SHIFT_MESSAGES_POINTER));
        ((msg_common*)(shm_p + SHIFT_MESSAGES_POINTER))[MAX_LIST_OF_MSG - 1] = message;
    }

    semop(sem_id, &(operations[SEM_M_UPLOAD_UNLOCK]), 1);

    //  Разблокировка обработчиков
    operations[SEM_M_HANDLER_UNLOCK].sem_op = _countOfConnections((user*)(shm_p));
    semop(sem_id, &(operations[SEM_M_HANDLER_UNLOCK]), 1);
}


int _countMessages(msg_common *messages) {
    int count = 0;
    for (int index = 0; index < MAX_LIST_OF_MSG; index++) {
        int length = strlen(messages[index].payload);
        if (messages[index].client.pid != 0 || length != 0) {
            count++;
        }
    }

    return count;
}

void _moveAllBackOnOne(msg_common *messages) {
    for (int index = 1; index < MAX_LIST_OF_MSG; index++) {
        messages[index - 1] = messages[index];
    }
}

int _countOfConnections(user *clients) {
    int count = 0;
    for (int index = 0; index < MAX_USERS_COUNT; index++) {
       if (clients[index].pid != 0) count++;
    }

    return count;
}
