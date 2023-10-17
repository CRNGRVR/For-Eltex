#include <pthread.h>
#include "draw_screen.h"
#include "../Common/msg.h"
#include "../Common/user.h"
#include "threadHandlersArgs.h"
#include "handler.h"

void threadHandlers_start(draw_screen *screen, user client, char *shm_p,
                          int sem_id, struct sembuf *operations) {

    pthread_t msgHandler;
    pthread_t namesHandler;
    pthread_t inputHandler;

    struct threadHandlersArgs_msg argsMsgThread;
    struct threadHandlersArgs_name argsNameThread;
    struct threadHandlersArgs_input argsInputThread;

    argsMsgThread.screen = screen;
    argsMsgThread.shm_p = shm_p;
    argsMsgThread.sem_id = sem_id;
    argsMsgThread.operations = operations;

    argsNameThread.screen = screen;
    argsNameThread.shm_p = shm_p;
    argsNameThread.sem_id = sem_id;
    argsNameThread.operations = operations;

    argsInputThread.inputw = screen->inputScreen;
    argsInputThread.client = client;
    argsInputThread.shm_p = shm_p;
    argsInputThread.sem_id = sem_id;
    argsInputThread.operations = operations;


    pthread_create(&msgHandler, NULL, handler_msg, &argsMsgThread);
    pthread_create(&namesHandler, NULL, handler_names, &argsNameThread);
    pthread_create(&inputHandler, NULL, handler_input, &argsInputThread);

    pthread_join(msgHandler, NULL);
    pthread_join(namesHandler, NULL);
    pthread_join(inputHandler, NULL);
}
