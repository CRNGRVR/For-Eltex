#ifndef _THREADHANDLER_ARGS
#define _THREADHANDLER_ARGS 1

#include "draw_screen.h"
#include "../Common/msg.h"
#include "../Common/user.h"

struct threadHandlersArgs_msg {
    draw_screen *screen;    //  Экраны для перерисовки
    long pid;               //  Идентификатор процесса
    int qfd_in_msg;         //  Дескриптор очереди ввода сообщений
    msg_common *messages;   //  Общий список сообщений
};

struct threadHandlersArgs_name {
    draw_screen *screen;    //  Экраны для перерисовки
    long pid;               //  Идентификатор процесса
    int qfd_int_names;      //  Дескриптор очереди ввода имён
    user *clients;          //  Общий список имён
};

struct threadHandlersArgs_input {
    WINDOW *inputw;         //  Поле ввода сообщения
    long pid;               //  Идентификатор процесса
    char *name;             //  Имя пользователя
    int qfd_out;            //  Дескриптор очереди вывода
};

#endif
