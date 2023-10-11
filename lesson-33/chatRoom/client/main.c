/**
 *  26.09.2023
 *
 *  Чат с общей комнатой: Клиент
 *
 *  Имеет интерфейс ncurses. Появляется поле для ввода имени, после ввода
 *  появляется главный экран, что содержит:
 *  1.  Поле сообщений. Отображена история и можно вводить новые сообщения.
 *      Видно от кого пришло сообщение.
 *  2.  Поле с подключёнными участниками.
 *
 *  После запуска подключается к очередям, созданным сервером. Вводит своё имя
 *  и отправляет на сервер. В ответ получает историю сообщений и возможность
 *  писать новые. Создаёт три потока, в которых обрабатывает ввод пользователя,
 *  пришедшие новые сообщения от сервера, пришедшие новые имена от сервера.
 *
 *  Весь обмен происходит через сервер: когда кто-то подключается, он
 *  уведомляет об этом сервер, сервер добавляет его в список и разсылает всем
 *  участникам новый список. С сообщениями так же: пользователь шлёт их на 
 *  сервер, а сервер добавляет сообщение в список и распространяет на ожидающих
 *  пользователей.
*/

#include "../Common/properties.h"
#include "../Common/user.h"
#include "../Common/msg.h"
#include "draw.h"
#include "draw_screen.h"
#include "clsession.h"
#include "threadHandlers.h"

int main() {
    draw_screen screen;
    long pid;
    int queueFD_IN_MSG;
    int queueFD_IN_NAMES;
    int queueFD_OUT;
    char name[MAX_NAME_LENGTH] = {};
    user clients[MAX_USERS_COUNT];
    msg_common listMsg[MAX_LIST_OF_MSG];

    draw_start(&screen);
    draw_getName(&screen, name);

    clsession_start(&pid, name, &queueFD_IN_MSG, &queueFD_IN_NAMES,
                    &queueFD_OUT, listMsg, clients);

    draw_main(&screen);

    //  Отрисовка существующих данных
    draw_name_update(&screen, clients);
    draw_chat_update(&screen, listMsg);

    //  Обработка новых
    threadHandlers_start(&screen, pid, name,
                         queueFD_IN_MSG, queueFD_IN_NAMES, queueFD_OUT,
                         listMsg, clients);
}
