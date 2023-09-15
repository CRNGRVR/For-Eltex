//
//  08.09.2023
//
//  Максимально простой(до неприличия) текстовый редактор
//
//  Функционал:
//  1. При запуске черное окно и три функциональные клавиши.
//  2. F1 - открыть файл. Появляется окно для ввода имени файла, на экране
//     появляется содержимое. Можно перемещаться курсором и редактировать. Если
//     имя файла пустое, создать новый.
//  3. F2 - сохранить изменения. Если файл новый, то вводим имя и сохраняем
//     по ENTER.
//  4. F3 - выйти из редактора.
//


//  TASK: защита от передвижения курсора по отсутствующей части файла

//  Версия до рефакторинга
//  Выглядит ужасно, зато полностью функциональна


#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "fileWork.h"

#define FILE_BUFF_SIZE 1000
#define FILE_NAME "aboba.txt"

#define FILE_EXISTS 0
#define FILE_NEED_TO_CREATE 1


int main() {

    bool flag = 0;
    char buff[FILE_BUFF_SIZE] = {};
    char fileName[45] = {};
    WINDOW *w;
    
    initscr();
    w = newwin(24, 80, 1, 1);

    hello(w);
    //fileWork_open(FILE_NAME, buff, &flag);
    choseFile(w, buff, &flag, fileName);

    //w = newwin(24, 80, 1, 1);
    //fillWindow(w, buff);
    input(w, buff, fileName, &flag);

    endwin();
}


void fillWindow(WINDOW *w, char *buff) {

    //w = newwin(24, 80, 1, 1);
    wclear(w);
    int counter = 0;
    while (buff[counter] != 0 && counter != FILE_BUFF_SIZE) {
        wechochar(w, buff[counter]);
        counter++;
    }

    keypad(w, true);
    wrefresh(w);
    //wgetch(w);
}

void input(WINDOW *w, char *buff, char *fileName, bool *flag) {

    fillWindow(w, buff);
   
    int i = 0;
    int ch;

    wmove(w, 0, 0);

    while (ch != KEY_F(3) && ch != KEY_F(2)) {
   
         ch = wgetch(w);

        if (ch == 10) {
            buff[i] = '\n';
            i++;

            int x, y;
            getyx(w, y, x);
            wmove(w, y + 1, 0);

        } else if (ch == KEY_LEFT) {
            int x, y;
            getyx(w, y, x);
            wmove(w, y, x - 1);
            i--;
        }
        else if (ch == KEY_RIGHT) {
            int x, y;
            getyx(w, y, x);
            wmove(w, y, x + 1);
            i++;
        } else if (ch == KEY_UP) {
            
            int lastNextStrPos = 0;
            int endlineCounter = 0;

            for (int index = i; index > 0 ; index--)
            {

                if (buff[index] == '\n') {
                    lastNextStrPos = index;
                    endlineCounter++;
                }

                if (endlineCounter == 2) break;
            }
            

            int x, y;
            getyx(w, y, x);
            wmove(w, y - 1, 0);

            if (endlineCounter < 2) {
                i = 0;
            } else {
                i = lastNextStrPos + 1;
            }
        } else if (ch == KEY_DOWN) {


            int lastNextStrPos = 0;

            for (int index = i; index < buffLen(buff); index++)
            {
                if (buff[index] == '\n') {
                    lastNextStrPos = index;
                    break;
                }
            }
            

            int x, y;
            getyx(w, y, x);
            wmove(w, y + 1, 0);

            i = lastNextStrPos + 1;
        }
        else {
            
            buff[i] = ch;
            i++;
        }
    }


    if (ch == KEY_F(2)) {
        fileWork_save(fileName, buff, flag);
    }
}


int buffLen(char *buff) {
    int counter = 0;

    while (buff[counter] != 0) {
        counter++;
    }
    
    return counter;
}






void hello(WINDOW *w) {

    wclear(w);
    //w = newwin(24, 80, 1, 1);
    curs_set(0);
    wattron(w, A_BOLD);
    wprintw(w, "Hello!\n");
    wattroff(w, A_BOLD);
    wprintw(w, "Its textEditor, simple programm for... editing text?\n\n[F1] - open or create text file\n[F2] - save file(use while editor open)\n[F3] - exit\n");
    wrefresh(w);

    keypad(w, true);
    int key = wgetch(w);

    if (key == KEY_F(3)) {
        endwin();
        exit(EXIT_SUCCESS);
    }


    //delwin(w);
}

void choseFile(WINDOW *w, char *buff, bool *flag, char *fileName) {

    wclear(w);

    WINDOW *sw;
    WINDOW *ssw;
    WINDOW *sssw;
    
    //char str[50];

    sw = derwin(w, 6, 52, 0, 0);
    box(sw, '|', '-');
    ssw = derwin(sw, 4, 50, 1, 1);

    wprintw(ssw, " Enter the file name for open or press [ENTER] on\n empty field for create one\n");
    wmove(ssw, 3, 0);
    wprintw(ssw, " -> \n");
    sssw = derwin(ssw, 1, 45, 3, 4);
    curs_set(1);
    keypad(sssw, true);
    wrefresh(w);


    int ch;
    int counter = 0;

    while (1)
    {
        ch = wgetch(sssw);

        if (ch == 10) {
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

    
    delwin(sw);
    delwin(ssw);
    delwin(sssw);
}