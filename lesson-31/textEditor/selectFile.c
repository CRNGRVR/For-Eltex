#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include "fileWork.h"


void selectFile(WINDOW *mainScreen, char *fileName, char *buff, bool *flag) {

    wclear(mainScreen);

    WINDOW *borderedWrap;   //  Окно с рамкой
    WINDOW *wrappedText;    //  Информация внутри окна с рамкой
    WINDOW *textField;      //  Поле для ввода имени файла внутри информации

    borderedWrap = derwin(mainScreen, 6, 52, 0, 0);
    box(borderedWrap, '|', '-');
    wrappedText = derwin(borderedWrap, 4, 50, 1, 1);

    //  Вывод в две строки для соблюдения кодстайла
    wprintw(wrappedText, " Enter the file name for open existed file, or\n");
    wprintw(wrappedText, " created new one\n");

    wmove(wrappedText, 3, 0);
    wprintw(wrappedText, " -> \n");
    textField = derwin(wrappedText, 1, 45, 3, 4);
    curs_set(1);
    keypad(textField, true);

    wrefresh(mainScreen);


    int ch;
    int counter = 0;

    while (1) {
        ch = wgetch(textField);

        if (ch == 10) {
            //  [ENTER]
            break;
        } else if (ch == KEY_F(3)) {
            endwin();
            exit(EXIT_SUCCESS);
        } else {
            fileName[counter] = ch;
            counter++;
        }
    }

    fileWork_open(fileName, buff, flag);

    delwin(borderedWrap);
    delwin(wrappedText);
    delwin(textField);
}
