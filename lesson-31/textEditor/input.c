#include <ncurses.h>
#include "fileWork.h"


void _fillWindow(WINDOW *win, char *buff) {

    wclear(win);
    int counter = 0;
    while (counter < fileWork_buffLen(buff)) {
        wechochar(win, buff[counter]);
        counter++;
    }

    wrefresh(win);
}

void input(WINDOW *mainScreen, char *fileName, char *buff, bool *flag) {

    int i = 0;
    int ch;

    _fillWindow(mainScreen, buff);
    wmove(mainScreen, 0, 0);
    keypad(mainScreen, true);

    while (ch != KEY_F(3) && ch != KEY_F(2)) {

        ch = wgetch(mainScreen);

        switch (ch) {
            //  [ENTER]
            case 10: {
                buff[i] = '\n';
                i++;

                int x, y;
                getyx(mainScreen, y, x);
                wmove(mainScreen, y + 1, 0);
                break;
            }

            case KEY_LEFT: {
                int x, y;
                getyx(mainScreen, y, x);

                if (0 < x) {
                    wmove(mainScreen, y, x - 1);
                    i--;
                }

                break;
            }

            case KEY_RIGHT: {
                int x, y;
                getyx(mainScreen, y, x);

                //  Ширина экрана 80 символов
                if (80 > x) {
                    wmove(mainScreen, y, x + 1);
                    i++;
                }

                break;
            }

            //  Перемещение вверх и вниз осуществляется переходом в начало
            //  строки ниже и выше соответственно
            case KEY_UP: {
                //  Поиск конца пред-предыдущей строки для лёгкого перехода в
                //  начало предыдущей строки
                int previousEndlinePos = 0;
                int endlineCounter = 0;

                for (int index = i; index > 0 ; index--) {

                    if (buff[index] == '\n') {
                        previousEndlinePos = index;
                        endlineCounter++;
                    }

                    if (endlineCounter == 2) break;
                }
            

                if (endlineCounter < 2) {
                    //  Если курсор переходит со второй строки на первую, то
                    //  символа конца пред-предыдущей строки не будет, очевидно
                    //  что это начало буфера
                    i = 0;
                } else {
                    //  Перемещение на начало нужной строки
                    i = previousEndlinePos + 1;
                }

                int x, y;
                getyx(mainScreen, y, x);
                wmove(mainScreen, y - 1, 0);

                break;
            }
            
            case KEY_DOWN: {
                //  Поиск символа конца строки в буфере для перехода на
                //  следующую строку
                int nextEndlinePos = 0;
                for (int index = i; index < fileWork_buffLen(buff); index++) {
                    if (buff[index] == '\n') {
                        nextEndlinePos = index;
                        break;
                    }
                }

                //  Проверка на наличие строки ниже курсора
                if (nextEndlinePos != 0) {
                    i = nextEndlinePos + 1; //  Символ после конца строки - новая строка
                    int x, y;
                    getyx(mainScreen, y, x);
                    wmove(mainScreen, y + 1, 0);
                }

                break;
            }

            default: {
                buff[i] = ch;
                i++;
                break;
            }
        }

        if (ch == KEY_F(2)) {
            fileWork_save(fileName, buff, flag);
        }
    }
}
