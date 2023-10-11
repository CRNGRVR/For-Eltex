#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include "../Common/properties.h"
#include "../Common/msg.h"
#include "../Common/user.h"

void _clearBuffService(msg_service_names *names);
void _clearMsgService(msg_service_list *list);


void request_names(long pid, char *name, int qfd_in_names, int qfd_out,
                   user *clients) {
    //  Запрос списка имён происходит через обычный тип сообщения с указанием
    //  специального флага
    msg_common initMessage;

    //  По запросу имён сервер идентифицирует нового пользователя
    initMessage.priority = P_CONNECTED;  
    initMessage.client.pid = pid;
    strcpy(initMessage.client.name, name);
    msgsnd(qfd_out, &initMessage, sizeof(msg_common), 0);

    msg_service_names names;
    _clearBuffService(&names);
    msgrcv(qfd_in_names, &names, sizeof(msg_service_names) - sizeof(long),
           pid, 0);

    for (int index = 0; index < MAX_USERS_COUNT; index++) {
        clients[index] = names.clients[index];
    }
}

void request_messages(long pid, char *name, int qfd_in_msg, int qfd_out,
                      msg_common *messages) {
    //  Запрос списка сообщений происходит через обычный тип сообщения с
    //  указанием специального флага
    msg_common msgreq;
    msgreq.client.pid = pid;
    msgreq.priority = P_MSGS_REQUIRED;
    strcpy(msgreq.client.name, name);
    msgsnd(qfd_out, &msgreq, sizeof(msg_common) - sizeof(long), 0);

    msg_service_list list;
    _clearMsgService(&list);
    msgrcv(qfd_in_msg, &list, sizeof(msg_service_list) - sizeof(long), pid, 0);

    for (int index = 0; index < MAX_LIST_OF_MSG; index++) {
        messages[index] = list.messages[index];
    }
}


void _clearMsgService(msg_service_list *list) {
    list->priority = 0;
    for (int index = 0; index < MAX_LIST_OF_MSG; index++) {
        list->messages[index].priority = 0;
        list->messages[index].client.pid = 0;

        for (int j = 0; j < MAX_MSG_LENGTH; j++) {   
            list->messages[index].payload[j] = 0;
        }

        for (int k = 0; k < MAX_NAME_LENGTH; k++) {
            list->messages[index].client.name[k] = 0;
        }
    }
}

void _clearBuffService(msg_service_names *names) {
    names->priority = 0;
    for (int index = 0; index < MAX_USERS_COUNT; index++) {
        names->clients[index].pid = 0;
        for (int j = 0; j < MAX_NAME_LENGTH; j++) {
            names->clients[index].name[j] = 0;
        }
    }
}
