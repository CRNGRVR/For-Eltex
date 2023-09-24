/**
 *  17.09.2023
 *
 *  Файловый менеджер
 *
 *  Два окна ncurses выводят содержимое начальной папки. Можно производить
 *  навигацию стрелочками, выходить и заходить в разные папки.
 *  Tab переключает курсор между окнами.
 *  F10 - выход.
*/

#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ncurses.h>
#include <locale.h>

#include "properties.h"
#include "fm_window.h"
#include "fm_print.h"
#include "fm_list.h"

int main() {
    WINDOW *mainScreen;
    fm_window leftWin;
    fm_window rightWin;

    bool active = LEFT_ACTIVE;
    fm_window *activeWin = &leftWin;

    setlocale(0, "");   //  Для корректной обработки кириллицы
    initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLUE);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    curs_set(0);
    noecho();

    mainScreen = newwin(25, 80, 0, 0);
    keypad(mainScreen, true);

    leftWin.borderedScreen = derwin(mainScreen, 25, 40, 0, 0);
    box(leftWin.borderedScreen, '|', '-');

    rightWin.borderedScreen = derwin(mainScreen, 25, 40, 0, 40);
    box(rightWin.borderedScreen, '|', '-');

    leftWin.screen = derwin(leftWin.borderedScreen, 23, 38, 1, 1);
    rightWin.screen = derwin(rightWin.borderedScreen, 23, 38, 1, 1);

    leftWin.selectedIndex = -1;
    leftWin.alignment = 0;

    rightWin.selectedIndex = -1;
    rightWin.alignment = 0;

    strcpy(leftWin.currentPath, "/");
    strcpy(rightWin.currentPath, "/");
    leftWin.filesCount = scandir(leftWin.currentPath, &(leftWin.files), NULL,
                                 NULL);
    rightWin.filesCount = scandir(rightWin.currentPath, &(rightWin.files),
                                  NULL, NULL);


    fm_printList(&leftWin);
    fm_printList_withoutMark(&rightWin);
    wrefresh(leftWin.screen);

    while (1) {
        int ch = wgetch(mainScreen);

        switch (ch) {
            case KEY_UP: {
                fm_list_up(activeWin);
                break;
            }
            case KEY_DOWN: {
                fm_list_down(activeWin);
                break;
            }
            //  [ENTER]
            case 10: {
                fm_list_enterDir(activeWin);
                break;
            }
            //  [TAB]
            case 9: {
                fm_printList_withoutMark(activeWin);

                if (active == LEFT_ACTIVE) {
                    active = RIGHT_ACTIVE;
                    activeWin = &rightWin;
                } else {
                    active = LEFT_ACTIVE;
                    activeWin = &leftWin;
                }
                break;
            }
            case KEY_F(10): {
                endwin();
                exit(EXIT_SUCCESS);
            }

            default:
                break;
        }

        wclear(activeWin->screen);
        fm_printList(activeWin);
    }
}
