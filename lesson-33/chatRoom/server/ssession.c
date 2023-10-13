#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <stdio.h>
#include "../Common/properties.h"
#include "../Common/msg.h"
#include "../Common/user.h"
#include "handle.h"

void _clearAtStart(msg_common *messages, user *clients);


void session_start(int *qfd_in, int *qfd_out_msg, int *qfd_out_names) {
    key_t key1 = ftok(PATHNAME, PROJID1);
    key_t key2 = ftok(PATHNAME, PROJID2);
    key_t key3 = ftok(PATHNAME, PROJID3);

    *qfd_in = msgget(key1, IPC_CREAT | S_IRUSR | S_IWUSR);
    *qfd_out_msg = msgget(key2, IPC_CREAT | S_IRUSR | S_IWUSR);
    *qfd_out_names = msgget(key3, IPC_CREAT | S_IRUSR | S_IWUSR);
}

void session_handle(int qfd_in, int qfd_out_msg, int qfd_out_names,
                    msg_common *messages, user *clients) {
    _clearAtStart(messages, clients);

    while (1) {
        msg_common buff;
        msgrcv(qfd_in, &buff, sizeof(msg_common), 0, 0);

        switch (buff.priority) {
            case P_CONNECTED: {
                printf("Client connected.\n");
                handle_connection(buff, qfd_out_names, clients);
                break;
            }

            case P_MSGS_REQUIRED: {
                printf("Messages required.\n");
                handle_messages_require(buff, qfd_out_msg, messages);
                break;
            }

            case P_DISCONNECTED: {
                printf("Client disconnected.\n");
                handle_disconnection(buff, qfd_out_names, clients);
                break;
            }

            default: {
                printf("Message sended.\n");
                handle_commonMessage(buff, qfd_out_msg, messages, clients);
                break;
            }
        }
    }
}


//  Очистка массивов перед началом работы
void _clearAtStart(msg_common *messages, user *clients) {
    for (int i = 0; i < MAX_USERS_COUNT; i++) {
        clients[i].pid = 0;
        for (int j = 0; j < MAX_NAME_LENGTH; j++) {
            clients[i].name[j] = 0;
        }
    }

    for (int i = 0; i < MAX_LIST_OF_MSG; i++) {
        messages[i].priority = 0;

        for (int j = 0; j < MAX_MSG_LENGTH; j++) {
            messages[i].payload[j] = 0;
        }

        for (int k = 0; k < MAX_USERS_COUNT; k++) {
            messages[i].client.pid = 0;
            for (int l = 0; l < MAX_NAME_LENGTH; l++) {
                messages[i].client.name[l] = 0;
            }
        }
    }
}
