#ifndef _THREADHANDLERS
#define _THREADHANDLERS 1

/**
 *  threadHandlers_start - запускает потоки обработки ввода, новых сообщений и
 *  новых имён
 *
 *  screen:         Структура, что сожержит необходимые экраны для работы.
 *  pid:            Идентификатор процесса.
 *  name:           Имя пользователя.
 *  qfd_in_msg:     Дескриптор очереди ввода сообщений.
 *  qfd_in_names:   Дескриптор очереди ввода имён.
 *  qfd_out:        Дескриптор очереди вывода.
 *  messages:       Общий список сообщений.
 *  clients:        Общий список пользователей.
 *
 *  Эта функция запускает потоки обработки ввода, новых сообщений и новых имён.
 *  Все эти потоки блокируются, по этому работают отдельно. В потоки передаются
 *  все необходимые аргументы из списка выше.
*/
void threadHandlers_start(draw_screen *screen, long pid, char *name,
                         int qfd_in_msg, int qfd_in_names, int qfd_out,
                         msg_common *messages, user *clients);

#endif
