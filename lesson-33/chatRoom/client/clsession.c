#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include "../Common/msg.h"
#include "../Common/user.h"
#include "../Common/properties.h"
#include "request.h"

void _clearAtStart(msg_common *messages, user *clients);


void clsession_start(long *pid, char *name, int *qfd_in_msg, int *qfd_in_names,
                     int *qfd_out, msg_common *messages, user *clients) {
    *pid = getpid();
    _clearAtStart(messages, clients);

    key_t key1 = ftok(PATHNAME, PROJID1);
    key_t key2 = ftok(PATHNAME, PROJID2);
    key_t key3 = ftok(PATHNAME, PROJID3);
    *qfd_out = msgget(key1, 0);
    *qfd_in_msg = msgget(key2, 0);
    *qfd_in_names = msgget(key3, 0);

    //  О подключении пользователя сервер уведомляется через запрос
    //  списков имён
    request_names(*pid, name, *qfd_in_names, *qfd_out, clients);
    request_messages(*pid, name, *qfd_in_msg, *qfd_out, messages);
}

void clsession_sendMessage(long pid, char *name, int qfd_out, char *payload) {
    msg_common msg;
    msg.client.pid = pid;
    //  Для определения сообщения как обычного, в приоритет ставится pid
    //  отправителя
    msg.priority = pid;
    strcpy(msg.client.name, name);
    strcpy(msg.payload, payload);

    msgsnd(qfd_out, &msg, sizeof(msg_common) - sizeof(long), 0);
}

void clsession_disconnect(long pid, int qfd_out) {
    //  Используется обычный тип сообщения без нагрузки, но с соответствующим
    //  флагом в приоритете, чтобы уведомить сервер об отключении пользователя
    msg_common msg;
    msg.client.pid = pid;
    msg.priority = P_DISCONNECTED;

    msgsnd(qfd_out, &msg, sizeof(msg_common) - sizeof(long), 0);
}


//  Очистка массивов перед началом работы
void _clearAtStart(msg_common *messages, user *clients) {
    for (int index1 = 0; index1 < MAX_USERS_COUNT; index1++) {
        clients[index1].pid = 0;
        for (int index2 = 0; index2 < MAX_NAME_LENGTH; index2++) {
            clients[index1].name[index2] = 0;
        }
    }

    for (int index1 = 0; index1 < MAX_LIST_OF_MSG; index1++) {
        messages[index1].priority = 0;

        for (int index2 = 0; index2 < MAX_MSG_LENGTH; index2++) {
            messages[index1].payload[index2] = 0;
        }

        for (int index2 = 0; index2 < MAX_USERS_COUNT; index2++) {
            messages[index1].client.pid = 0;
            for (int index3 = 0; index3 < MAX_NAME_LENGTH; index3++) {
                messages[index1].client.name[index3] = 0;
            }
        }
    }
}
