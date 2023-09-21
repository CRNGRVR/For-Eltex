/**
 *  17.09.2023
 *
 *  Файловый менеджер
 *
 *  Два окна ncurses выводят содержимое начальной папки. Можно производить
 *  навигацию стрелочками, выходить и заходить в разные папки. 
 *  Tab переключает курсор между окнами.
*/

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#include "getDirPath.h"


int main(int argc, char *argv[]) {

    char currentPath[1000] = {};
    strcpy(currentPath, "/home/ivan/test");

    struct dirent **names;
    int dirs = scandir(currentPath, &names, NULL, NULL);

    
    initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLUE);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    curs_set(0);



    WINDOW *w;
    WINDOW *sw;

    int selectedIndex = -1;
    int align = 0;

    w = newwin(25, 40, 0, 0);
    box(w, '|', '-');
    wrefresh(w);

    sw = derwin(w, 23, 38, 1, 1);
    keypad(sw, true);

    
    while (1) {
        
        wclear(sw);

        //  Первый пункт с возвращением
        if (selectedIndex == -1) {
            wattron(sw, COLOR_PAIR(1));
            wprintw(sw, "/..\n");
            wattroff(sw, COLOR_PAIR(1));
        } else {
            wattron(sw, COLOR_PAIR(2));
            wprintw(sw, "/..\n");
            wattroff(sw, COLOR_PAIR(2));
        }



        int countToPrint;
        if (dirs > 22) {
            countToPrint = align + 22;
        } else {
            countToPrint = dirs;
        }

        //  Печать всех пунктов с выделением и "/" у папок
        for (int i = align; i < countToPrint; i++) {
            if (i != selectedIndex) {
                if (names[i]->d_type == 4) wprintw(sw, "/");
                wprintw(sw, "%s\n", names[i]->d_name);
            } else {
                wattron(sw, COLOR_PAIR(1));
                if (names[i]->d_type == 4) wprintw(sw, "/");
                wprintw(sw, "%s\n", names[i]->d_name);
                wattroff(sw, COLOR_PAIR(1));
            }
        }
        wrefresh(sw);
        

        int ch = wgetch(sw);

        if (ch == KEY_F(3)) break;

        if (ch == KEY_UP && selectedIndex > -1) {
            selectedIndex--;

            if (selectedIndex == align) {

                int willRemainToTop = align - 8;
                if (willRemainToTop < 8) {
                    align = 0;
                } else {
                    align -= 8;
                }
            }

        } else if (ch == KEY_DOWN && selectedIndex < (dirs - 1)) {
            selectedIndex++;

            if (selectedIndex == (align + 22)) {
                int remainToBottom = dirs - (align + 22);
                if (remainToBottom < 8) {
                    align += remainToBottom;
                } else {
                    align += 8;
                }
            }

        } else if (ch == 10) {
            if (selectedIndex != -1) {
                getDirPath_next(currentPath, names[selectedIndex]->d_name);
                dirs = scandir(currentPath, &names, NULL, NULL);
                
            } else {
                getDirPath_previous(currentPath);
                dirs = scandir(currentPath, &names, NULL, NULL);
            }

            selectedIndex = -1;
            align = 0;
        }
    }

    endwin();
    exit(EXIT_SUCCESS);
}
