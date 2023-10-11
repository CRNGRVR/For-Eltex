#include <pthread.h>
#include "draw_screen.h"
#include "../Common/msg.h"
#include "../Common/user.h"
#include "threadHandlersArgs.h"
#include "handler.h"

void threadHandlers_start(draw_screen *screen, long pid, char *name,
                         int qfd_in_msg, int qfd_in_names, int qfd_out,
                         msg_common *messages, user *clients) {

    pthread_t msgHandler;
    pthread_t namesHandler;
    pthread_t inputHandler;

    struct threadHandlersArgs_msg argsMsgThread;
    struct threadHandlersArgs_name argsNameThread;
    struct threadHandlersArgs_input argsInputThread;

    argsMsgThread.messages = messages;
    argsMsgThread.pid = pid;
    argsMsgThread.qfd_in_msg = qfd_in_msg;
    argsMsgThread.screen = screen;

    argsNameThread.clients = clients;
    argsNameThread.pid = pid;
    argsNameThread.qfd_int_names = qfd_in_names;
    argsNameThread.screen = screen;

    argsInputThread.inputw = screen->inputScreen;
    argsInputThread.name = name;
    argsInputThread.pid = pid;
    argsInputThread.qfd_out = qfd_out;

    pthread_create(&msgHandler, NULL, handler_msg, &argsMsgThread);
    pthread_create(&namesHandler, NULL, handler_names, &argsNameThread);
    pthread_create(&inputHandler, NULL, handler_input, &argsInputThread);
    
    pthread_join(msgHandler, NULL);
    pthread_join(namesHandler, NULL);
    pthread_join(inputHandler, NULL);
}
