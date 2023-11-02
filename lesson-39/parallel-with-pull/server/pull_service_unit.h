#ifndef _PULL_SERVICE_UNIT
#define _PULL_SERVICE_UNIT 1

#include <stdbool.h>

struct pull_service_unit {
    int index;          //  Номер сервера в пулле
    int port;           //  Порт сервера
    bool available;     //  Флаг наличия доступа к серверу
};

typedef struct pull_service_unit pull_service_unit;

#endif
