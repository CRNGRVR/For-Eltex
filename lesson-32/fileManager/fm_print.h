#ifndef _FM_PRINT
#define _FM_PRINT 1

#include <ncurses.h>
#include "fm_window.h"

/**
 *  fm_printList - выводит на экран список файлов, папок, пункт возврата, и
 *  окрашивает выделенный элемент
 *
 *  win:    Указатель на окно fm, в screen которого будет выведен список files
 *          с учётом его свойств.
 *
 *  Эта функция выводит на экран screen пункт "/..", список файлов/папок
 *  files[].d_name и выделяет активный пункт под номером selectedIndex.
 *
 *  Папок может быть больше, чем позволяет вместить экран. Для решения этой
 *  проблемы, печать списка начинается с элемента под номером alignment.
 *  Заканчивается либо на последнем элементе списка(когда хватает места
 *  на экране), либо на последнем элементе, который позволяет вместить экран.
 *  Параметры alignment и filesCount, используемые для решения этой проблемы,
 *  определяются другими функциями.
*/
void fm_printList(fm_window *win);

/**
 *  fm_printList_withoutMark - выводит на экран список файлов, папок и пункт
 *  возврата
 *
 *  win:    Указатель на окно fm, в screen которого будет выведен список files
 *          с учётом его свойств.
 *
 *  Эта функция является копией функции fm_printList, за исключением того, что
 *  она не окрашивает пункт под номером selectedIndex.
 *
 *  Используется для снятия окрашивания выделенного пункта в неактивном окне
 *  заменой его содержимого на аналогичное из этой функции, только без
 *  выделения.
*/
void fm_printList_withoutMark(fm_window *win);

#endif
