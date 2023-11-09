/**
 *  06.11.2023
 *
 *  Клиент raw
 *  Обмен сообщениями с udp-сервером, заполняя заголовок транспортного и
 *  сетевого уровня самостоятельно
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/udp.h>
#include <stdlib.h>

#define SERV_ADDR "127.0.0.1"
#define SERV_PORT 5678
#define FICTIONAL_CLIENT_PORT 8765
#define BUFF_SIZE 50

#define UDP_HEADER_SIZE 8
#define IP_HEADER_SIZE 20
#define PAYLOAD "Hello"

//  Очистка буфера для нового пакета
void clearBuff(char *buff, int len);

int main() {
    char buff[BUFF_SIZE + IP_HEADER_SIZE + UDP_HEADER_SIZE] = {};
    int sockFD;
    struct sockaddr_in serv;
    struct in_addr addr;
    socklen_t len = sizeof(struct sockaddr_in);
    struct udphdr udp_header;
    struct iphdr ip_header;

    addr.s_addr = inet_addr(SERV_ADDR);
    serv.sin_family = AF_INET;
    serv.sin_addr = addr;
    serv.sin_port = htons(SERV_PORT);

    sockFD = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (sockFD == -1) {
        perror("");
        exit(EXIT_FAILURE);
    }

    int flag = 1;
    setsockopt(sockFD, IPPROTO_IP, IP_HDRINCL, &flag, sizeof(int));

    //  Заполнение заголовка сетевого уровня
    ip_header.daddr = inet_addr(SERV_ADDR);
    ip_header.frag_off = 0;
    ip_header.protocol = IPPROTO_UDP;
    ip_header.ttl = 10;
    ip_header.ihl = 5;
    ip_header.version = 4;
    ip_header.tos = 0;
    ip_header.check = 0;    //  Заполняется системой
    ip_header.saddr = 0;    //  -N-
    ip_header.id = 0;       //  -N-
    ip_header.tot_len = 0;  //  -N-

    //  Заполнение заголовка транспортного уровня
    udp_header.dest = htons(SERV_PORT);
    udp_header.source = htons(FICTIONAL_CLIENT_PORT);
    udp_header.check = 0;
    udp_header.len = htons(UDP_HEADER_SIZE + BUFF_SIZE);

    //  Заголовок добавляется в начало сообщения
    memcpy(buff, &ip_header, IP_HEADER_SIZE);
    memcpy(buff + IP_HEADER_SIZE, &udp_header, UDP_HEADER_SIZE);
    memcpy(buff + IP_HEADER_SIZE + UDP_HEADER_SIZE, PAYLOAD, BUFF_SIZE);
    sendto(sockFD, buff, BUFF_SIZE + IP_HEADER_SIZE + UDP_HEADER_SIZE, 0,
           (struct sockaddr*)&serv, sizeof(struct sockaddr_in));
    clearBuff(buff, BUFF_SIZE + IP_HEADER_SIZE + UDP_HEADER_SIZE);

    while (1) {
        recvfrom(sockFD, buff, BUFF_SIZE, 0, (struct sockaddr*)&serv, &len);

        struct udphdr *rcv_udp_hdr = (struct udphdr*)(buff + IP_HEADER_SIZE);
        if (ntohs(rcv_udp_hdr->dest) == FICTIONAL_CLIENT_PORT) {
            printf("%s\n", buff + IP_HEADER_SIZE + UDP_HEADER_SIZE);
            break;
        }

        clearBuff(buff, BUFF_SIZE + UDP_HEADER_SIZE);
    }
}

void clearBuff(char *buff, int len) {
    for (int i = 0; i < len; i++) {
        buff[i] = 0;
    }
}
