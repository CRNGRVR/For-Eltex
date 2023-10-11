/**
 *  26.09.2023
 *
 *  Чат с общей комнатой: Сервер
 *  Создаёт очереди сообщений и управляет ими. Собирает имена подключающихся к
 *  очередям клиентов и рассылает всем клиентам. Хранит все имена и сообщения.
 *  Вновь подключившимся клиентам рассылает историю сообщений. Клиенты могут
 *  писать в общий чат всем. При получении сообщения сервер рассылает всем
 *  новый список. При выходе пользователя сервер так же обновляет список имён и
 *  отправляет всем пользователям.
*/

#include "../Common/msg.h" 
#include "../Common/user.h"
#include "../Common/properties.h"
#include "ssession.h"

int main() {
    int queueFD_IN;
    int queueFD_OUT_MSG;
    int queueFD_OUT_NAMES;

    user clients[MAX_USERS_COUNT];
    msg_common listMsg[MAX_LIST_OF_MSG];

    session_start(&queueFD_IN, &queueFD_OUT_MSG, &queueFD_OUT_NAMES);
    session_handle(queueFD_IN, queueFD_OUT_MSG, queueFD_OUT_NAMES, listMsg,
                   clients);
}
