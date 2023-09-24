#include <dirent.h>
#include "fm_window.h"
#include "getDirPath.h"
#include "properties.h"

void fm_list_up(fm_window *win) {
    //  Проверка на верхнюю границу
    if (win->selectedIndex > -1) {
        win->selectedIndex--;

        //  Изменение смещения, когда достигнута граница
        if (win->selectedIndex == win->alignment) {
            int willRemainToTop = win->alignment - ALIGNMENT_STEP;
            if (willRemainToTop < ALIGNMENT_STEP) {
                win->alignment = 0;
            } else {
                win->alignment -= ALIGNMENT_STEP;
            }
        }
    }
}

void fm_list_down(fm_window *win) {
    //  Проверка на нижнюю границу
    if (win->selectedIndex < (win->filesCount - 1)) {
        win->selectedIndex++;

        //  Изменение смещения, когда достигнута граница
        if (win->selectedIndex == (win->alignment + SCREEN_HEIGHT_FOR_LIST)) {
            int remainToBottom = win->filesCount - win->selectedIndex;
            if (remainToBottom < ALIGNMENT_STEP) {
                win->alignment += remainToBottom;
            } else {
                win->alignment += ALIGNMENT_STEP;
            }
        }
    }
}

void fm_list_enterDir(fm_window *win) {
    //  Выбор пункта назад "/.."
    if (win->selectedIndex != -1) {
        getDirPath_next(win->currentPath,
                        win->files[win->selectedIndex]->d_name);
        win->filesCount = scandir(win->currentPath, &win->files, NULL, NULL);
    } else {
        getDirPath_previous(win->currentPath);
        win->filesCount = scandir(win->currentPath, &win->files, NULL, NULL);
    }
    //  Сброс значений выделения и смещения для новой папки
    win->selectedIndex = -1;
    win->alignment = 0;
}
