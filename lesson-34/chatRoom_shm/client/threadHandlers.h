#ifndef _THREADHANDLERS
#define _THREADHANDLERS 1

#include "draw.h"

/**
 *  threadHandlers_start - запускает потоки обработки ввода, новых сообщений и
 *  новых имён
 *
 *  screen: Структура, что сожержит необходимые экраны для работы.
 *  
 *
 *  Эта функция запускает потоки обработки ввода, новых сообщений и новых имён.
 *  Все эти потоки блокируются, по этому работают отдельно. В потоки передаются
 *  все необходимые аргументы из списка выше.
*/
void threadHandlers_start(draw_screen *screen, user client, char *shm_p,
                          int sem_id, struct sembuf *operations);

#endif
