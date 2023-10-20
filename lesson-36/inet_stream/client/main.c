/**
 *  19.10.2023
 *
 *  Простой обмен через сокеты
 *  Семейство: AF_INET
 *  Тип: SOCK_STREAM
 *  Клиент
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#define SERV_ADDR "127.0.0.1"
#define SERV_PORT 5678
#define BUFF_SIZE 10

int main() {
    char buff[BUFF_SIZE];
    int sockFD;
    struct sockaddr_in serv;
    struct in_addr addr;

    addr.s_addr = inet_addr(SERV_ADDR);

    serv.sin_family = AF_INET;
    serv.sin_addr = addr;
    serv.sin_port = htons(SERV_PORT);
    sockFD = socket(AF_INET, SOCK_STREAM, 0);
    connect(sockFD, (struct sockaddr*)&serv, sizeof(struct sockaddr_in));

    recv(sockFD, buff, BUFF_SIZE, 0);
    printf("%s\n", buff);
    send(sockFD, "Hello!", BUFF_SIZE, 0);
    close(sockFD);
}
