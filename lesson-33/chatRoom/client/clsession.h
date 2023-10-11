#ifndef _CLSESSION
#define _CLSESSION 1

#include "../Common/msg.h"
#include "../Common/user.h"

/**
 *  clsession_start - заполняет данные для начала работы
 *
 *  pid:            Идентификатор процесса. Заполняется внутри функции.
 *  name:           Имя пользователя.
 *  qfd_in_msg:     Дескриптор очереди ввода сообщений. Заполняется внутри
 *                  функции.
 *  qfd_in_names:   Дескриптор очереди ввода имён. Заполняется внутри функции.
 *  qfd_out:        Дескриптор очереди вывода. Заполняется внутри функции.
 *  messages:       Список сообщений. Заполняется внутри функции.
 *  clients:        Список пользователей. Заполняется внутри функции.
 *
 *  Эта функция заполняет pid, очищает массивы messages и clients, открывает
 *  очереди и запрашивает у сервера список имён и сообщений.
*/
void clsession_start(long *pid, char *name, int *qfd_in_msg, int *qfd_in_names,
                     int *qfd_out, msg_common *messages, user *clients);

/**
 *  clsession_sendMessage - отправляет сообщение обычного вида
 *
 *  pid:        Идентификатор процесса.
 *  name:       Имя пользователя.
 *  qfd_out:    Дескриптор очереди вывода.
 *  payload:    Полезная нагрузка сообщения. Заполняется внутри функции.
 *
 *  Эта функция отправляет серверу сообщение обычного вида в очередь qfd_out,
 *  содержания payload с приоритетом pid.
*/
void clsession_sendMessage(long pid, char *name, int qfd_out, char *payload);

/**
 *  clsession_disconnect - уведомляет сервер сообщением обычного вида
 *  об отключении
 *
 *  pid:        Идентификатор процесса.
 *  qfd_out:    Дескриптор очереди вывода.
 *
 *  Эта функция посылает серверу сообщение типа msg_common с нулевой нагрузкой
 *  и соответствующим флагом приоритета для уведомления об отключении.
*/
void clsession_disconnect(long pid, int qfd_out);

#endif
