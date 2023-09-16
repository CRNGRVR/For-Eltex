#ifndef _INPUT_MODULE
#define _INPUT_MODULE 1

#include <ncurses.h>

/**
 *  _fillWindow - заполняет окно win данными из buff
 *
 *  win:    Окно, в которое будут выведены данные
 *  buff:   Буфер, данными из которого будет заполнено окно
 *
 *  Эта функция очищает окно, и просто выводит на него значения из буфера
 *  до тех пор, пока из буфера не будет считан нуль(EOF)
 *
 *  Примечание: окно mainScreen перед передачей должно быть создано вызовом
 *  функции newwin()
*/
void _fillWindow(WINDOW *win, char *buff);

/**
 *  input - заполняет окно mainScreen данными из buff и даёт управление
 *  редактором пользователю
 *
 *  mainScreen: Окно редактора, на которое будут выведены данные
 *  fileName:   Имя открытого файла
 *  buff:       Буфер с текстом, что выведен на экран и доступен для
 *              редактирования пользователем
 *  flag:       Флаг, хранящий состояние, характеризующее наличие файла.
 *
 *  Эта функция заполняет окно данными из буфера(если есть) и предоставляет
 *  пользователю возможность редактирования. Возможности редактирования:
 *  1.  Ввод символа с клавиатуры
 *  2.  Перевод строки по нажатию [ENTER]
 *  3.  Перемещение курсора влево и вправо кнопками направления
 *  4.  Перемещение курсора Вверх и вниз кнопками направления на позиции начала
 *      нужных строк
 *  5.  Сохранение и выход из редактора по нажатию [F2]
 *  6.  Выход без сохранения по нажатию [F3]
 *
 *  Если выбранного файла с именем fileName не существует(состояние в flag), то
 *  при сохранении этот файл будет создан и записан данными из buff. Если файл
 *  существовал, то будет перезаписан данными из buff.
*/
void input(WINDOW *mainScreen, char *fileName, char *buff, bool *flag);

#endif
