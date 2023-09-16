/**
 *  08.09.2023
 *
 *  Максимально простой текстовый редактор
 *
 *  Функционал:
 *  1. При запуске черное окно и три функциональные клавиши.
 *  2. F1 - открыть файл. Появляется окно для ввода имени файла, на экране
 *     появляется содержимое. Можно перемещаться курсором и редактировать. Если
 *     файла с таким именем нет, создать новый при сохранении.
 *  3. F2 - сохранить изменения.
 *  4. F3 - выйти из редактора.
*/

#include <curses.h>
#include "hello.h"
#include "selectFile.h"
#include "input.h"

#define FILE_BUFF_SIZE 1000


int main() {

    char fileName[45] = {};
    char buff[FILE_BUFF_SIZE] = {};
    bool flag;
    WINDOW *mainWindow;

    initscr();
    mainWindow = newwin(24, 80, 1, 1);

    hello(mainWindow);
    selectFile(mainWindow, fileName, buff, &flag);
    input(mainWindow, fileName, buff, &flag);

    delwin(mainWindow);
    endwin();
}
