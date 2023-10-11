#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include "../Common/properties.h"
#include "../Common/msg.h"
#include "../Common/user.h"

void _sendNames(int qfd_out_names, user *clients);
void _sendMessages(int qfd_out_msg, msg_common *messages, user *clients);
int _countOfConnections(user *clients);
int _countMessages(msg_common *messages);
void _clearBuffService(msg_service_names *names);
void _moveAllBackOnOne(msg_common *messages);


void handle_connection(msg_common message, int qfd_out_names, user *clients) {
    //  Проверка на заполненность
    if (_countOfConnections(clients) < MAX_USERS_COUNT) {
        //  Поиск свободного места и вставка нового имени
        for (int index = 0; index < MAX_USERS_COUNT; index++) {
            if (clients[index].pid == 0) {
                clients[index].pid = message.client.pid;
                strcpy(clients[index].name, message.client.name);
                break;
            }
        }

        //  Отправка нового списка
        _sendNames(qfd_out_names, clients);
    }
}

void handle_messages_require(msg_common message, int qfd_out_msg,
                             msg_common *messages) {
    //  Формирование и отправка списка конкретному клиенту
    msg_service_list list;
    list.priority = message.client.pid;
    for (int index = 0; index < MAX_LIST_OF_MSG; index++) {
        list.messages[index] = messages[index];
    }

    msgsnd(qfd_out_msg, &list, sizeof(msg_service_list) - sizeof(long), 0);
}

void handle_disconnection(msg_common message, int qfd_out_names,
                          user *clients) {
    //  Поиск клиента в списке и очистка его данных
    for (int index1 = 0; index1 < MAX_LIST_OF_MSG; index1++) {
        if (clients[index1].pid == message.client.pid) {
            clients[index1].pid = 0;
            for (int index2 = 0; index2 < MAX_NAME_LENGTH; index2++) {
                clients[index1].name[index2] = 0;
            }

            break;
        }
    }

    //  Отправка нового списка всем
    _sendNames(qfd_out_names, clients);
}

void handle_commonMessage(msg_common message, int qfd_out_msg,
                          msg_common *messages, user *clients) {
    //  Проверка на заполненность списка сообщений. Если заполнен, все
    //  сообщения будут сдвинуты назад на 1, а новое вставлено в конец
    int currentMessagesCount = _countMessages(messages);
    if (currentMessagesCount < MAX_LIST_OF_MSG) {
        messages[currentMessagesCount] = message;
    } else {
        _moveAllBackOnOne(messages);
        messages[MAX_LIST_OF_MSG - 1] = message;
    }

    //  Рассылка нового списка всем
    _sendMessages(qfd_out_msg, messages, clients);
}


//  Отправка списка имён всем участникам
void _sendNames(int qfd_out_names, user *clients) {
    for (int index1 = 0; index1 < MAX_USERS_COUNT; index1++) {
        //  Проверка наличия участника
        if (clients[index1].pid != 0) {
            msg_service_names names;
            _clearBuffService(&names);
            names.priority = clients[index1].pid;

            for (int index2 = 0; index2 < MAX_USERS_COUNT; index2++) {
                if (clients[index2].pid != 0) {
                    names.clients[index2] = clients[index2];
                }
            }

            msgsnd(qfd_out_names, &names, 
                   sizeof(msg_service_names) - sizeof(long), 0);
        }
    }
}

//  Отправка списка сообщений всем участникам
void _sendMessages(int qfd_out_msg, msg_common *messages, user *clients) {
    for (int index1 = 0; index1 < MAX_USERS_COUNT; index1++) {
        if (clients[index1].pid != 0) {
            msg_service_list list;
            list.priority = clients[index1].pid;

            for (int index2 = 0; index2 < MAX_LIST_OF_MSG; index2++) {
                list.messages[index2] = messages[index2];
            }

            msgsnd(qfd_out_msg, &list,
                   sizeof(msg_service_list) - sizeof(long), 0);
        }
    }
}

//  Подсчёт подключений
int _countOfConnections(user *clients) {
    int count = 0;
    for (int index = 0; index < MAX_USERS_COUNT; index++) {
       if (clients[index].pid != 0) count++;
    }

    return count;
}

//  Подсчёт сообщений
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

void _clearBuffService(msg_service_names *names) {
    names->priority = 0;
    for (int index1 = 0; index1 < MAX_USERS_COUNT; index1++) {
        names->clients[index1].pid = 0;

        for (int index2 = 0; index2 < MAX_NAME_LENGTH; index2++) {
            names->clients[index1].name[index2] = 0;
        }
    }
}

//  Сдвиг всех сообщений на 1 назад
void _moveAllBackOnOne(msg_common *messages) {
    for (int index = 1; index < MAX_LIST_OF_MSG; index++) {
        messages[index - 1] = messages[index];
    }
}
