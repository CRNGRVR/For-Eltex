#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "draw.h"
#include "../Common/properties.h"
#include "clsession.h"
#include "threadHandlersArgs.h"

void _clearCurrentMessage(char *msg);


void *handler_msg(void *args) {
    struct threadHandlersArgs_msg castedArgs = *((struct threadHandlersArgs_msg*)args);

    while (1) {
        msg_service_list list;
        msgrcv(castedArgs.qfd_in_msg, &list,
               sizeof(msg_service_list) - sizeof(long), castedArgs.pid, 0);

        for (int index = 0; index < MAX_LIST_OF_MSG; index++) {
            castedArgs.messages[index] = list.messages[index];
        }

        draw_chat_update(castedArgs.screen, castedArgs.messages);
    }
}


void *handler_names(void *args) {
    struct threadHandlersArgs_name castedArgs = *((struct threadHandlersArgs_name*)args);

    while (1) {
        msg_service_names names;
        msgrcv(castedArgs.qfd_int_names, &names,
               sizeof(msg_service_names) - sizeof(long), castedArgs.pid, 0);

        for (int index = 0; index < MAX_USERS_COUNT; index++) {
            castedArgs.clients[index] = names.clients[index];
        }

        draw_name_update(castedArgs.screen, castedArgs.clients);
    }
}


void *handler_input(void *args) {
    struct threadHandlersArgs_input castedArgs = *((struct threadHandlersArgs_input*)args);

    int counter = 0;
    char msgText[MAX_MSG_LENGTH] = {};

    while (1) {
        int ch = wgetch(castedArgs.inputw);

        if (ch == KEY_F(3)) {
            clsession_disconnect(castedArgs.pid, castedArgs.qfd_out);
            endwin();
            exit(EXIT_SUCCESS);
        } else if (ch == 10) {
            //  [ENTER]
            clsession_sendMessage(castedArgs.pid, castedArgs.name,
                                  castedArgs.qfd_out, msgText);
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
