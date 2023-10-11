#ifndef _MSG_SERVICE
#define _MSG_SERVICE 1

#include "../Common/user.h"
#include "../Common/properties.h"

/**
 *  msg_common - объект обычного сообщения. Используется как обычное клиентское
 *  сообщение или как запрос клиента к серверу списков сообщений и имён.
*/
struct msg_common {
    //  Приоритет, описывающий назначение сообщения. Константы назначения
    //  в properties.h
    long priority;

    //  Информация об отправителе
    user client;

    //  Полезная нагрузка. Если сообщение используется как запрос, будет иметь
    //  нулевую длину
    char payload[MAX_MSG_LENGTH];
};

typedef struct msg_common msg_common;

/**
 *  msg_service_list - список сообщений, разсылаемый сервером клиентам.
*/
struct msg_service_list {
    long priority;  //  pid клиента, которому предназначается список
    msg_common messages[MAX_LIST_OF_MSG];   //  Список всех сообщений
};

typedef struct msg_service_list msg_service_list;

/**
 *  msg_service_names - список подключённых пользователей, разсылаемый сервером
 *  клиентам.
*/
struct msg_service_names {
    long priority;  //  pid клиента, которому предназначается список
    user clients[MAX_USERS_COUNT];  //  Список пользователей
};

typedef struct msg_service_names msg_service_names;

#endif
