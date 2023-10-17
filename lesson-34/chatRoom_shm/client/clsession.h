#ifndef _CLSESSION
#define _CLSESSION 1
#include "../Common/user.h"
#include "../Common/msg.h"

/**
 *  clsession_start - получение доступа к ресурсам, созданным сервером, и
 *  назначение операций над семафорами(соответствие properties.h)
 *
 *  shm_p:      Указатель на разделяемую память. Заполняется в этой функции.
 *  sem_id:     Идентификатор группы семафоров. Заполняется в этой функции.
 *  operations: Массив операций над семафорами. Заполняется в этой функции.
*/
void clsession_start(char **shm_p, int *sem_id, struct sembuf *operations);

/**
 *  clsession_insertName - безопасно вставляет имя текущего пользователя в
 *  список в разделяемой памяти и разблокирует семафоры обработчиков на
 *  клиентах
 *
 *  client:     Данные текущего пользователя.
 *  shm_p:      Указатель на разделяемую память.
 *  sem_id:     Идентификатор группы семафоров.
 *  operations: Операции над семафорами.
*/
void clsession_insertName(user client, char *shm_p, int sem_id,
                          struct sembuf *operations);

/**
 *  clsession_removeName - безопасно удаляет имя текущего пользователя из
 *  списка в разделяемой памяти и разблокирует семафоры обработчиков на 
 *  клиентах
 *
 *  client:     Данные текущего пользователя.
 *  shm_p:      Указатель на разделяемую память.
 *  sem_id:     Идентификатор группы семафоров.
 *  operations: Операции над семафорами.
*/
void clsession_removeName(user client, char *shm_p, int sem_id,
                          struct sembuf *operations);

/**
 *  clsession_insertMessage - безопасно вставляет сообщение в список в
 *  разделяемой памяти и разблокирует семафоры обработчиков на
 *  клиентах
 *
 *  message:    Сообщение, содержащее нагрузку и данные отправителя.
 *  shm_p:      Указатель на разделяемую память.
 *  sem_id:     Идентификатор группы семафоров.
 *  operations: Операции над семафорами.
*/
void clsession_insertMessage(msg_common message, char *shm_p, int sem_id,
                             struct sembuf *operations);

#endif
