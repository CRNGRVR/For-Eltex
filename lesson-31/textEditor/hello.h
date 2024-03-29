#ifndef _HELLO_MODULE
#define _HELLO_MODULE 1

#include <ncurses.h>

/**
 *  hello - выводит приветственный экран с инструкцией и ждёт выбор
 *  пользователя
 *
 *  mainScreen: Окно, на которое будет выведено приветственное сообщение.
 *
 *  Эта функция выводит на экран сообщение с инструкцией и ждёт команды
 *  пользователя:
 *  [F1] - Переход на следующий экран.
 *  [F3] - Завершение программы.
 *
 *  Примечание: окно mainScreen перед передачей должно быть создано вызовом
 *  функции newwin()
*/
void hello(WINDOW *mainScreen);

#endif
