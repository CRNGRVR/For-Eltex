#ifndef _SELECT_FILE_MODULE
#define _SELECT_FILE_MODULE 1

#include <ncurses.h>
#include <stdbool.h>


/**
 *  selectFile - выводит окно для ввода имени файла, после чего копирует его
 *  содержимое в буфер
 *
 *  mainScreen: Экран для ввода и вывода.
 *  fileName:   Указатель на введённое имя файла, будет помещено туда по
 *              завершению работы функции.
 *  buff:       Статичный буфер, в который будет скопирован файл.
 *  flag:       Результат открытия файла. Нужен для работы функций fileWork.
 *
 *  Примечание: окно mainScreen перед передачей должно быть создано вызовом
 *  функции newwin()
*/
void selectFile(WINDOW *mainScreen, char *fileName, char *buff, bool *flag);

#endif
