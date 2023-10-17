#include <stdlib.h>
#include "draw.h"
#include "../Common/properties.h"
#include "threadHandlersArgs.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include "clsession.h"

void _clearCurrentMessage(char *msg);


void *handler_msg(void *args) {
    struct threadHandlersArgs_msg castedArgs = *((struct threadHandlersArgs_msg*)args);

    while (1) {
        semop(castedArgs.sem_id, 
              &(castedArgs.operations[SEM_M_HANDLER_LOCK]), 1);

        draw_chat_update(castedArgs.screen,
                         (msg_common*)(castedArgs.shm_p + SHIFT_MESSAGES_POINTER));
    }
}


void *handler_names(void *args) {
    struct threadHandlersArgs_name castedArgs = *((struct threadHandlersArgs_name*)args);

    while (1) {
        semop(castedArgs.sem_id, 
              &(castedArgs.operations[SEM_N_HANDLER_LOCK]), 1);

        draw_name_update(castedArgs.screen, (user*)(castedArgs.shm_p));
    }
}


void *handler_input(void *args) {
    struct threadHandlersArgs_input castedArgs = *((struct threadHandlersArgs_input*)args);

    int counter = 0;
    char msgText[MAX_MSG_LENGTH] = {};

    while (1) {
        int ch = wgetch(castedArgs.inputw);

        if (ch == KEY_F(3)) {
            clsession_removeName(castedArgs.client, castedArgs.shm_p, 
                                 castedArgs.sem_id, castedArgs.operations);
            endwin();
            exit(EXIT_SUCCESS);
        } else if (ch == 10) {
            //  [ENTER]
            msg_common msg;
            msg.client = castedArgs.client;
            strcpy(msg.payload, msgText);
            clsession_insertMessage(msg, castedArgs.shm_p, castedArgs.sem_id,
                                    castedArgs.operations);

            draw_clearField(castedArgs.inputw);
            _clearCurrentMessage(msgText);
            counter = 0;
        } else {
            msgText[counter] = ch;
            counter++;
        }
    }
}


void _clearCurrentMessage(char *msg) {
    for (int index = 0; index < MAX_MSG_LENGTH; index++) {
        msg[index] = 0;
    }
}
