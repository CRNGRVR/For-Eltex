#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "semwork.h"
#include "../properties.h"

void *service(void *args) {
    int sockFD;
    struct sockaddr_in serv = *(struct sockaddr_in*)args;
    struct sockaddr_in client;
    struct in_addr addr;
    socklen_t peerlen;

    sockFD = socket(AF_INET, SOCK_STREAM, 0);
    bind(sockFD, (struct sockaddr*)&serv, sizeof(struct sockaddr_in));
    listen(sockFD, 1);

    //  Разблокировка ожидающего слушающего сервера, чтобы по готовности
    //  обслуживающего он уведомил клиента
    semwork_unlock();

    //  Обслуживание клиента
    int acceptedFD = accept(sockFD, (struct sockaddr*)&client, &peerlen);
    send(acceptedFD, "Hi", BUFF_SIZE, 0);
    close(acceptedFD);
    close(sockFD);
}
