#ifndef _HANDLE
#define _HANDLE 1

#include "../Common/msg.h"
#include "../Common/user.h"

/**
 *  handle_connection - обработчик нового подключения. Заносит нового клиента в
 *  список и отравляет всем обновлённый
 *
 *  message:        Сообщение нового клиента, на основании которого он
 *                  заносится в список.
 *  qfd_out_names:  Дескриптор очереди вывода списка имён. Эту очередь слушают
 *                  клиенты, чтобы получить новые списки.
 *  clients:        Список клиентов, в который будет занесён новый
 *                  пользователь.
 *
 *  Эта функция обрабатывает запрос клиентом списка имён и интерпретирует это
 *  как новое подключение. Из message берёт имя отправителя, заносит в общий
 *  список и отправляет всем клиентам(в том числе и новому) обновлённый список.
*/
void handle_connection(msg_common message, int qfd_out_names, user *clients);

/**
 *  handle_messages_require - обработчик запроса списка сообщений
 *
 *  message:        Сообщение клиента, из которого берётся pid для 
 *                  персонального ответа через общую очередь.
 *  qfd_out_msg:    Дескриптор очереди вывода списка сообщений. Эту очередь
 *                  слушают клиенты, чтобы получить список сообщений.
 *  messages:       Список сообщений, что будет отправлен пользователю.
 *
 *  Эта функция обрабатывает запрос клиента на получение списка сообщений.
 *  Просто берёт общий список messages, оборачивает его в тип msg_service_list
 *  и отправляет в очередь qfd_out_msg с приоритетом pid взятым из message
 *  отправителя запроса.
*/
void handle_messages_require(msg_common message, int qfd_out_msg,
                             msg_common *messages);

/**
 *  handle_disconnection - обработчик отключения клиента
 *
 *  message:        Сообщение клиента, из которого берётся его pid.
 *  qfd_out_names:  Дескриптор очереди вывода имён.
 *  clients:        Список всех клиентов.
 *
 *  Эта функция ищет в списке clients пользователя с pid соответствующим pid
 *  отправителя, взятым из message, и удаляет его из списка. Обновлённый
 *  список clients отправляет всем пользователям.
*/
void handle_disconnection(msg_common message, int qfd_out_names,
                          user *clients);

/**
 *  handle_commonMessage - обработчик обычного сообщения
 *
 *  message:        Сообщение, что будет обработано.
 *  qfd_out_msg:    Дескриптор вывода сообщений.
 *  messages:       Список всех сообщений.
 *  clients:        Список всех клиентов.
 *
 *  Эта функция берёт сообщение message, добавляет его в конец списка messages,
 *  и рассылает новый список всем пользователям по их pid, взятым из clients.
 *  Причём если очередь сообщений заполнилась целиком, все сообщения будут
 *  сдвитнуты назад на 1, а новое будет поставлено в конец.
*/
void handle_commonMessage(msg_common message, int qfd_out_msg,
                          msg_common *messages, user *clients);

#endif
