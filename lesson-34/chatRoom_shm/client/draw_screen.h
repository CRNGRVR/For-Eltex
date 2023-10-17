#ifndef _DRAW_SCREEN
#define _DRAW_SCREEN 1

#include <ncurses.h>

/**
 *  screen - содержит все необходимые для работы экраны в одной структуре.
*/
struct screen {
    WINDOW *mainScreen;     //  Главный экран, содержит в себе все остальные
    WINDOW *historyScreen;  //  Экран, на который выводятся сообщения
    WINDOW *nameScreen;     //  Экран, на который выводятся имена пользователей
    WINDOW *inputScreen;    //  Экран для ввода сообщения пользователем
};

typedef struct screen draw_screen;

#endif
