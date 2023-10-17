#ifndef _PROPERTIES
#define _PROPERTIES 1

//  Свойства для генерации ключей доступа
#define PATHNAME "../server/crserver"
#define PROJID_SHM 0
#define PROJID_SEM 1


#define MAX_LIST_OF_MSG 20  //  Максимальное количество сообщений
#define MAX_MSG_LENGTH 100  //  Максимальная длина одного сообщения

#define MAX_USERS_COUNT 10  //  Максимальное количество пользователей
#define MAX_NAME_LENGTH 15  //  Максимальная длина имени


//  Значения индексов операций семафоров
//  SEM 0
#define SEM_N_UPLOAD_LOCK       0
#define SEM_N_UPLOAD_UNLOCK     1
//  SEM 1
#define SEM_M_UPLOAD_LOCK       2
#define SEM_M_UPLOAD_UNLOCK     3
//  SEM 2
#define SEM_N_HANDLER_LOCK      4
#define SEM_N_HANDLER_UNLOCK    5
//  SEM 3
#define SEM_M_HANDLER_LOCK      6
#define SEM_M_HANDLER_UNLOCK    7

//  Смещение указателя от начала разделяемого сегмента до области сообщений
#define SHIFT_MESSAGES_POINTER ((sizeof(user) * MAX_USERS_COUNT) + 1)

#endif
