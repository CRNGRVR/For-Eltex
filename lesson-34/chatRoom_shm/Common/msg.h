#ifndef _MSG
#define _MSG 1

#include "../Common/user.h"
#include "../Common/properties.h"

/**
 *  msg_common - объект обычного сообщения
*/
struct msg_common {
    user client;                    //  Информация об отправителе
    char payload[MAX_MSG_LENGTH];   //  Полезная нагрузка
};

typedef struct msg_common msg_common;

#endif
