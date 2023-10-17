#ifndef _THREADHANDLER_ARGS
#define _THREADHANDLER_ARGS 1

#include "draw_screen.h"
#include "../Common/msg.h"
#include "../Common/user.h"

/**
 *  Структуры аргументов для передачи в потоки
*/
struct threadHandlersArgs_msg {
    draw_screen *screen;        //  Экраны для перерисовки
    char *shm_p;                //  Указатель на сегмент разделяемой памяти
    int sem_id;                 //  Идентификатор группы семафоров
    struct sembuf *operations;  //  Операции над семафорами
};

struct threadHandlersArgs_name {
    draw_screen *screen;        //  Экраны для перерисовки
    char *shm_p;                //  Указатель на сегмент разделяемой памяти
    int sem_id;                 //  Идентификатор группы семафоров
    struct sembuf *operations;  //  Операции над семафорами
};

struct threadHandlersArgs_input {
    WINDOW *inputw;             //  Поле ввода сообщения
    user client;                //  Описание текущего пользователя
    char *shm_p;                //  Указатель на сегмент разделяемой памяти
    int sem_id;                 //  Идентификатор группы семафоров
    struct sembuf *operations;  //  Операции над семафорами
};

#endif
