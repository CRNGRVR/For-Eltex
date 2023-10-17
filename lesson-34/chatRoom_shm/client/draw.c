#include <ncurses.h>
#include <stdlib.h>
#include <pthread.h>
#include "draw_screen.h"
#include "../Common/properties.h"
#include "../Common/user.h"
#include "../Common/msg.h"

pthread_mutex_t drawMutex = PTHREAD_MUTEX_INITIALIZER;
void _clearName(char *name);


void draw_start(draw_screen *screen) {
    initscr();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    screen->mainScreen = newwin(25, 80, 0, 0);
    curs_set(0);
    keypad(screen->mainScreen, true);
}

void draw_getName(draw_screen *screen, char *name) {
    wattron(screen->mainScreen, A_BOLD | COLOR_PAIR(1));
    wprintw(screen->mainScreen, "\n Hello!\n");
    wattroff(screen->mainScreen, A_BOLD | COLOR_PAIR(1));
    wprintw(screen->mainScreen, " It's simple IPC chatroom. Works on");
    wattron(screen->mainScreen, A_BOLD);
    wprintw(screen->mainScreen, " System V Shared memory\n");
    wattroff(screen->mainScreen, A_BOLD);
    wprintw(screen->mainScreen, " Follow the process party!\n\n");
    wprintw(screen->mainScreen, " [F3] - exit from chat\n\n");
    wprintw(screen->mainScreen, " Enter your name bellow:\n");
    wrefresh(screen->mainScreen);

    //  Окно ввода
    WINDOW *field = derwin(screen->mainScreen, 1, MAX_NAME_LENGTH + 4, 8, 0);
    keypad(field, true);
    wprintw(field, " -> ");

    _clearName(name);
    int index = 0;
    while (1) {
        int ch = wgetch(field);

        if (ch == KEY_F(3)) {
            endwin();
            exit(EXIT_SUCCESS);
        } else if (ch == 10) {
            //  [ENTER]
            break;
        } else if (index < MAX_NAME_LENGTH) {
            name[index] = ch;
            index++;
        }
    }

    wclear(screen->mainScreen);
    wrefresh(screen->mainScreen);
    delwin(field);
}

void draw_main(draw_screen *screen) {
    wclear(screen->mainScreen);
    box(screen->mainScreen, '|', '-');

    WINDOW *boxWrapper_history = derwin(screen->mainScreen, 23, 63, 0, 0);
    WINDOW *boxWrapper_names = derwin(screen->mainScreen, 25, 18, 0, 62);
    WINDOW *boxWrapper_input = derwin(screen->mainScreen, 3, 63, 22, 0);
    box(boxWrapper_history, '|', '-');
    box(boxWrapper_names, '|', '-');
    box(boxWrapper_input, '|', '-');

    screen->historyScreen = derwin(boxWrapper_history, 21, 61, 1, 1);
    screen->nameScreen = derwin(boxWrapper_names, 23, 16, 1, 1);
    screen->inputScreen = derwin(boxWrapper_input, 1, 61, 1, 1);


    wmove(screen->inputScreen, 0, 0);
    wattron(screen->inputScreen, COLOR_PAIR(1));
    wprintw(screen->inputScreen, " -> ");
    wattroff(screen->inputScreen, COLOR_PAIR(1));
    keypad(screen->inputScreen, true);
    wrefresh(screen->mainScreen);
}

void draw_chat_update(draw_screen *screen, msg_common *messages) {
    pthread_mutex_lock(&drawMutex);
    wclear(screen->historyScreen);

    for (int index = 0; index < MAX_LIST_OF_MSG; index++) {
        //  Проверка на наличие сообщения через pid отправителя
        if (messages[index].client.pid != 0) {
            wprintw(screen->historyScreen, "%s: %s\n", 
                    messages[index].client.name, messages[index].payload);
        }
    }

    wrefresh(screen->historyScreen);
    pthread_mutex_unlock(&drawMutex);
}

void draw_name_update(draw_screen *screen, user *clients) {
    pthread_mutex_lock(&drawMutex);
    wclear(screen->nameScreen);

    for (int index = 0; index < MAX_USERS_COUNT; index++) {
        wprintw(screen->nameScreen, "%s\n", clients[index].name);
    }

    wrefresh(screen->nameScreen);
    pthread_mutex_unlock(&drawMutex);
}

void draw_clearField(WINDOW *win) {
    pthread_mutex_lock(&drawMutex);
    wclear(win);
    wattron(win, COLOR_PAIR(1));
    wprintw(win, " -> ");
    wattroff(win, COLOR_PAIR(1));
    wrefresh(win);
    pthread_mutex_unlock(&drawMutex);
}


void _clearName(char *name) {
    for (int index = 0; index < MAX_NAME_LENGTH; index++) {
        name[index] = 0;
    }
}
