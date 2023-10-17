#ifndef _USER
#define _USER 1

#include "../Common/properties.h"

/**
 *  user - структура, описывающая пользователя.
*/
struct user {
    long pid;                   //  Идентификатор процесса пользователя
    char name[MAX_NAME_LENGTH]; //  Имя пользователя
};

typedef struct user user;

#endif
