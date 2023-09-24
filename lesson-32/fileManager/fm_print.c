#include <dirent.h>
#include <ncurses.h>
#include "fm_window.h"
#include "properties.h"

//  Печать строки ограниченной длины
void _printLimited(WINDOW *w, char *src, int limit, int fileType) {
    //  тип 4 - папка, для отличия от файла выделяется символом "/"
    if (fileType == 4) wprintw(w, "/");

    for (int i = 0; i < limit; i++) {
        if (src[i] != 0) {
            wprintw(w, "%c", src[i]);
        } else {
            break;
        }
    }
    wprintw(w, "\n");
}

//  Печать пункта назад "/.."
void _printBackLine(fm_window *win) {
    //  -1: пункт "/.." выбран
    if (win->selectedIndex == -1) {
        wattron(win->screen, COLOR_PAIR(1));
        wprintw(win->screen, "/..\n");
        wattroff(win->screen, COLOR_PAIR(1));
    } else {
        //  Пункт не выбран, но выделен цветом для отличия его от файлов/папок
        wattron(win->screen, COLOR_PAIR(2));
        wprintw(win->screen, "/..\n");
        wattroff(win->screen, COLOR_PAIR(2));
    }
}

//  Печать пункта назад "/.." для неактивного окна
void _printBackLine_withoutMark(fm_window *win) {
    wprintw(win->screen, "/..\n");
}

void fm_printList(fm_window *win) {
    wclear(win->screen);
    _printBackLine(win);

    //  Принятие решения: печать отрезка списка в размер экрана или печать
    //  всего списка, если влезет на экран
    int countToPrint;
    if (win->filesCount < SCREEN_HEIGHT_FOR_LIST) {
        countToPrint = win->filesCount;
    } else {
        countToPrint = win->alignment + SCREEN_HEIGHT_FOR_LIST;
    }

    for (int i = win->alignment; i < countToPrint; i++) {
        if (i != win->selectedIndex) {
            _printLimited(win->screen, win->files[i]->d_name,
                          SCREEN_WIDTH_FOR_LIST, win->files[i]->d_type);
        } else {
            //  Вывод элемента с подсветкой
            wattron(win->screen, COLOR_PAIR(1));
            _printLimited(win->screen, win->files[i]->d_name,
                          SCREEN_WIDTH_FOR_LIST, win->files[i]->d_type);
            wattroff(win->screen, COLOR_PAIR(1));
        }
    }
    wrefresh(win->screen);
}

void fm_printList_withoutMark(fm_window *win) {
    wclear(win->screen);
    _printBackLine_withoutMark(win);

    //  Принятие решения: печать отрезка списка в размер экрана или печать
    //  всего списка, если влезет на экран
    int countToPrint;
    if (win->filesCount < SCREEN_HEIGHT_FOR_LIST) {
        countToPrint = win->filesCount;
    } else {
        countToPrint = win->alignment + SCREEN_HEIGHT_FOR_LIST;
    }

    for (int i = win->alignment; i < countToPrint; i++) {
        _printLimited(win->screen, win->files[i]->d_name,
                      SCREEN_WIDTH_FOR_LIST, win->files[i]->d_type);
    }
    wrefresh(win->screen);
}
