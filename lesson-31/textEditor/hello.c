#include <ncurses.h>
#include <stdlib.h>


void hello(WINDOW *mainScreen) {

    wclear(mainScreen);
    curs_set(0);
    wattron(mainScreen, A_BOLD);
    wprintw(mainScreen, "Hello!\n");
    wattroff(mainScreen, A_BOLD);
    //  Печать в 4 строки для поддержания кодстайла
    wprintw(mainScreen, "Its textEditor, simple programm for... editing text?\n\n");
    wprintw(mainScreen, "[F1] - open or create text file\n");
    wprintw(mainScreen, "[F2] - save file(use while editor open)\n");
    wprintw(mainScreen, "[F3] - exit\n");
    wrefresh(mainScreen);

    int key;
    keypad(mainScreen, true);
    while (1) {
        key = wgetch(mainScreen);
        if (key == KEY_F(3)) {
            endwin();
            exit(EXIT_SUCCESS);
        } else if (key == KEY_F(1)) {
            //  Инструкции выбора файла идут после выхода из функции
            break;
        }
    }
}
