/**
 *  14.10.2023
 *
 *  Чат с общей комнатой: Клиент
*/

#include "../Common/properties.h"
#include "../Common/user.h"
#include "../Common/msg.h"
#include "draw.h"
#include "draw_screen.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include "clsession.h"
#include "threadHandlers.h"
#include <unistd.h>

int main() {
    draw_screen screen;
    user client;

    char *shm_p;
    int sem_id;
    struct sembuf operations[8];

    draw_start(&screen);
    draw_getName(&screen, client.name);
    client.pid = getpid();

    clsession_start(&shm_p, &sem_id, operations);
    clsession_insertName(client, shm_p, sem_id, operations);

    draw_main(&screen);
    draw_name_update(&screen, (user*)shm_p);
    draw_chat_update(&screen, (msg_common*)(shm_p + SHIFT_MESSAGES_POINTER));

    threadHandlers_start(&screen, client, shm_p, sem_id, operations);
}
