#ifndef _FM_LIST
#define _FM_LIST 1

#include "fm_window.h"

/**
 *  fm_list_up - "обработчик" кнопки вверх для главного окна. Выделяет элемент
 *  списка выше предыдущего
 *
 *  win:    Указатель на окно fm, в которое выведен список, параметры которого
 *  по выполнению этой функции будут изменены.
 *
 *  По выполнению этой функции будет выделен элемент по списку выше чем
 *  тот, что был выделен предыдущим, т.е. свойство selectedIndex будет
 *  декрементировано. Если предыдущий элемент был на самом верху экрана, а выше
 *  есть элементы(align не равно нулю), смещение будет так же декрементировано.
*/
void fm_list_up(fm_window *win);

/**
 *  fm_list_down - "обработчик" кнопки вниз для главного окна. Выделяет элемент
 *  списка ниже предыдущего
 *
 *  win:    Указатель на окно fm, в которое выведен список, параметры которого
 *  по выполнению этой функции будут изменены.
 *
 *  По выполнению этой функции будет выделен элемент по списку ниже чем
 *  тот, что был выделен предыдущим, т.е. свойство selectedIndex будет
 *  инкрементировано. Если предыдущий элемент был в самом низу экрана, а ниже
 *  есть элементы(selectedIndex меньше чем fileCount - 1), смещение будет так
 *  же инкрементировано.
*/
void fm_list_down(fm_window *win);

/**
 *  fm_list_enterDir - "обработчик" кнопки ENTER для главного окна. Открывает
 *  выделенную папку(номер которой в списке равен selectedIndex).
 *
 *  win:    Указатель на окно fm, в которое выведен список, параметры которого
 *  по выполнению этой функции будут изменены.
 *
 *  По выполнению этой функции имя элемента списка под номером selectedIndex
 *  будет скопировано в конец currentPath, после чего по этому пути будет
 *  открыта папка, её содержимое скопировано в files, свойство filesCount
 *  установлено количеством файлов/папок в открытом каталоге.
*/
void fm_list_enterDir(fm_window *win);

#endif
