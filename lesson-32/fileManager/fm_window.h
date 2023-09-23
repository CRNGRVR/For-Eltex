#ifndef _FM_WINDOW
#define _FM_WINDOW 1

#include <ncurses.h>
#include "properties.h"

struct fm_window {
    struct dirent **files;  //  Файлы в открытой папке
    char currentPath[MAX_PATH_SIZE];    //  Открытая папка
    int filesCount;  //  Количество файлов в открытой папке


    WINDOW *screen; // Окно для вывода списка файлов. Дочернее к borderedScreen
    WINDOW *borderedScreen; //  Окно для вывода рамки окна screen
    int selectedIndex;  //  Номер выбранного файла в списке

    //  Смещение относительно начала списка. Необходимо если содержимое списка
    //  не вмещается на экран
    int alignment;
};

typedef struct fm_window fm_window;

#endif
