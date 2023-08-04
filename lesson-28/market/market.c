//
//  02.08.2023
//
//  Эмулятор магазина
//
//  Есть 5 магазинов, в каждом изначально 1000 товаров.
//  Погрузчик заходит в случайный магазин, если там никого нет то заходит 
//  и добавляет 500 единиц, засыпает на 2 секунды. Повторяет бесконечно.
//
//  Покупателя 3. При создании имеют потребность в 10000. Ищут свободный
//  магазин, выбирают случайно, покупают всё и уменьшают потребность.
//  Засыпют на 1 секунду. Повторяют до конца потребности. Попутно все
//  выводят информацию. Как только заканчивается потребность всех 
//  покупателей, главный поток завершает погрузчика и программа завершается.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


//  Количество товаров в магазинах
int market[5] = {1000, 1000, 1000, 1000, 1000};

//  Примитивы синхронизации для каждого магазина
pthread_mutex_t mutex0 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex4 = PTHREAD_MUTEX_INITIALIZER;

//  Нужда покупателей
int customers[3] = {10000, 10000, 10000};


//
//  Функции change
//  role: l - погрузчик, c - покупатель
//  customerNum - номер конкретного покупателя, если role == 'l', то передаём NULL
//
void changeMarket0(char role, short customerNum) {

    if(role == 'l') {

        printf("\nПОГРУЗЧИК:       пытается зайти в магазин #0\n");
        
        if(pthread_mutex_trylock(&mutex0) == 0) {

            int last = market[0];
            market[0] += 500;
            printf("\nПОГРУЗЧИК:       заходит в магазин #0.   Магазин: %d -> %d\n", last, market[0]);
            sleep(2);
            pthread_mutex_unlock(&mutex0);
            printf("\nПОГРУЗЧИК:       выходит из магазина #0\n");
        }
        else {
            printf("\nПОГРУЗЧИК:       магазин #0 занят\n");
        }
    }
    else {
        //  Покупатель
        printf("\nПОКУПАТЕЛЬ %d:    пытается зайти в магазин #0\n", customerNum);

        if(pthread_mutex_trylock(&mutex0) == 0) {

            int lastMarket = market[0];
            int lastCustomer = customers[customerNum];

            if(customers[customerNum] > market[0]) {
                customers[customerNum] -= market[0];
                market[0] = 0;
            }
            else {
                market[0] -= customers[customerNum];
                customers[customerNum] = 0;
            }

            printf("\nПОКУПАТЕЛЬ %d:    заходит в магазин #0.  Магазин: %d -> %d, покупатель: %d -> %d\n", 
                    customerNum, lastMarket, market[0], lastCustomer, customers[customerNum]);

            sleep(1);
            pthread_mutex_unlock(&mutex0);
            printf("\nПОКУПАТЕЛЬ %d:    выходит из магазина #0\n", customerNum);
        }
        else {
            printf("\nПОКУПАТЕЛЬ %d:    магазин #0 занят\n", customerNum);
        }
    }
}

void changeMarket1(char role, short customerNum) {

    if(role == 'l') {

        printf("\nПОГРУЗЧИК:       пытается зайти в магазин #1\n");
        
        if(pthread_mutex_trylock(&mutex1) == 0) {

            int last = market[1];
            market[1] += 500;
            printf("\nПОГРУЗЧИК:       заходит в магазин #1.   Магазин: %d -> %d\n", last, market[1]);
            sleep(2);
            pthread_mutex_unlock(&mutex1);
            printf("\nПОГРУЗЧИК:       выходит из магазина #1\n");
        }
        else {
            printf("\nПОГРУЗЧИК:       магазин #1 занят\n");
        }
    }
    else {
        //  Покупатель
        printf("\nПОКУПАТЕЛЬ %d:    пытается зайти в магазин #1\n", customerNum);

        if(pthread_mutex_trylock(&mutex1) == 0) {

            int lastMarket = market[1];
            int lastCustomer = customers[customerNum];

            if(customers[customerNum] > market[1]) {
                customers[customerNum] -= market[1];
                market[1] = 0;
            }
            else {
                market[1] -= customers[customerNum];
                customers[customerNum] = 0;
            }

            printf("\nПОКУПАТЕЛЬ %d:    заходит в магазин #1.  Магазин: %d -> %d, покупатель: %d -> %d\n", 
                    customerNum, lastMarket, market[1], lastCustomer, customers[customerNum]);

            sleep(1);
            pthread_mutex_unlock(&mutex1);
            printf("\nПОКУПАТЕЛЬ %d:    выходит из магазина #0\n", customerNum);
        }
        else {
            printf("\nПОКУПАТЕЛЬ %d:    магазин #1 занят\n", customerNum);
        }
    }
}

void changeMarket2(char role, short customerNum) {

    if(role == 'l') {

        printf("\nПОГРУЗЧИК:       пытается зайти в магазин #2\n");
        
        if(pthread_mutex_trylock(&mutex2) == 0) {

            int last = market[2];
            market[2] += 500;
            printf("\nПОГРУЗЧИК:       заходит в магазин #2.   Магазин: %d -> %d\n", last, market[2]);
            sleep(2);
            pthread_mutex_unlock(&mutex2);
            printf("\nПОГРУЗЧИК:       выходит из магазина #2\n");
        }
        else {
            printf("\nПОГРУЗЧИК:       магазин #2 занят\n");
        }
    }
    else {
        //  Покупатель
        printf("\nПОКУПАТЕЛЬ %d:    пытается зайти в магазин #2\n", customerNum);

        if(pthread_mutex_trylock(&mutex2) == 0) {

            int lastMarket = market[2];
            int lastCustomer = customers[customerNum];

            if(customers[customerNum] > market[2]) {
                customers[customerNum] -= market[2];
                market[2] = 0;
            }
            else {
                market[2] -= customers[customerNum];
                customers[customerNum] = 0;
            }

            printf("\nПОКУПАТЕЛЬ %d:    заходит в магазин #2.  Магазин: %d -> %d, покупатель: %d -> %d\n", 
                    customerNum, lastMarket, market[2], lastCustomer, customers[customerNum]);

            sleep(1);
            pthread_mutex_unlock(&mutex2);
            printf("\nПОКУПАТЕЛЬ %d:    выходит из магазина #2\n", customerNum);
        }
        else {
            printf("\nПОКУПАТЕЛЬ %d:    магазин #2 занят\n", customerNum);
        }
    }
}

void changeMarket3(char role, short customerNum) {

    if(role == 'l') {

        printf("\nПОГРУЗЧИК:       пытается зайти в магазин #3\n");
        
        if(pthread_mutex_trylock(&mutex3) == 0) {

            int last = market[3];
            market[3] += 500;
            printf("\nПОГРУЗЧИК:       заходит в магазин #3.   Магазин: %d -> %d\n", last, market[3]);
            sleep(2);
            pthread_mutex_unlock(&mutex3);
            printf("\nПОГРУЗЧИК:       выходит из магазина #3\n");
        }
        else {
            printf("\nПОГРУЗЧИК:       магазин #3 занят\n");
        }
    }
    else {
        //  Покупатель
        printf("\nПОКУПАТЕЛЬ %d:    пытается зайти в магазин #3\n", customerNum);

        if(pthread_mutex_trylock(&mutex3) == 0) {

            int lastMarket = market[3];
            int lastCustomer = customers[customerNum];

            if(customers[customerNum] > market[3]) {
                customers[customerNum] -= market[3];
                market[3] = 0;
            }
            else {
                market[3] -= customers[customerNum];
                customers[customerNum] = 0;
            }

            printf("\nПОКУПАТЕЛЬ %d:    заходит в магазин #3.  Магазин: %d -> %d, покупатель: %d -> %d\n", 
                    customerNum, lastMarket, market[3], lastCustomer, customers[customerNum]);

            sleep(1);
            pthread_mutex_unlock(&mutex3);
            printf("\nПОКУПАТЕЛЬ %d:    выходит из магазина #3\n", customerNum);
        }
        else {
            printf("\nПОКУПАТЕЛЬ %d:    магазин #3 занят\n", customerNum);
        }
    }
}

void changeMarket4(char role, short customerNum) {

    if(role == 'l') {

        printf("\nПОГРУЗЧИК:       пытается зайти в магазин #4\n");
        
        if(pthread_mutex_trylock(&mutex4) == 0) {

            int last = market[4];
            market[4] += 500;
            printf("\nПОГРУЗЧИК:       заходит в магазин #4.   Магазин: %d -> %d\n", last, market[4]);
            sleep(2);
            pthread_mutex_unlock(&mutex4);
            printf("\nПОГРУЗЧИК:       выходит из магазина #4\n");
        }
        else {
            printf("\nПОГРУЗЧИК:       магазин #4 занят\n");
        }
    }
    else {
        //  Покупатель
        printf("\nПОКУПАТЕЛЬ %d:    пытается зайти в магазин #4\n", customerNum);

        if(pthread_mutex_trylock(&mutex4) == 0) {

            int lastMarket = market[4];
            int lastCustomer = customers[customerNum];

            if(customers[customerNum] > market[4]) {
                customers[customerNum] -= market[4];
                market[4] = 0;
            }
            else {
                market[4] -= customers[customerNum];
                customers[customerNum] = 0;
            }

            printf("\nПОКУПАТЕЛЬ %d:    заходит в магазин #4.  Магазин: %d -> %d, покупатель: %d -> %d\n", 
                    customerNum, lastMarket, market[4], lastCustomer, customers[customerNum]);

            sleep(1);
            pthread_mutex_unlock(&mutex4);
            printf("\nПОКУПАТЕЛЬ %d:    выходит из магазина #4\n", customerNum);
        }
        else {
            printf("\nПОКУПАТЕЛЬ %d:    магазин #4 занят\n", customerNum);
        }
    }
}


//  Погрузчик
void *loader() {

    while(1) {

        //  Случайный выбор магазина от 0 до 4
        short choice = random() % 5;

        switch (choice) {
            case 0:
                changeMarket0('l', NULL);
                break;
        
            case 1:
                changeMarket1('l', NULL);
                break;

            case 2:
                changeMarket2('l', NULL);
                break;

            case 3:
                changeMarket3('l', NULL);
                break;

            case 4:
                changeMarket4('l', NULL);
                break;

            default:
                break;
        }


        if(customers[0] == 0 && customers[1] == 0 && customers[2] == 0) {
            printf("\nПОГРУЗЧИК:       все покупатели удовлетворены, погрузчик уходит\n");
            pthread_exit(EXIT_SUCCESS);
        }
    }
}

//  Покупатель
void *customer(void *args) {

    short customerNum = *(short* )args;

    while(1) {

        //  Случайный выбор магазина от 0 до 4
        short choice = random() % 5;

        switch (choice) {
            case 0:
                changeMarket0('c', customerNum);
                break;
        
            case 1:
                changeMarket1('c', customerNum);
                break;

            case 2:
                changeMarket2('c', customerNum);
                break;

            case 3:
                changeMarket3('c', customerNum);
                break;

            case 4:
                changeMarket4('c', customerNum);
                break;

            default:
                break;
        }

        if(customers[customerNum] <= 0) {
            printf("\nПОКУПАТЕЛЬ %d:    удовлетворяет свою потребность и уходит\n", customerNum);
            pthread_exit(EXIT_SUCCESS);
        }
    }
}


int main(void) {

    //  Засеивание рандомной последовательности
    srandom(time(NULL));

    pthread_t loaderThread;
    pthread_t customer0Thread, customer1Thread, customer2Thread;

    //  Номера покупателей для передачи в функцию потока
    short arg0 = 0;
    short arg1 = 1;
    short arg2 = 2;

    pthread_create(&loaderThread, NULL, loader, NULL);
    pthread_create(&customer0Thread, NULL, customer, &arg0);
    pthread_create(&customer1Thread, NULL, customer, &arg1);
    pthread_create(&customer2Thread, NULL, customer, &arg2);


    pthread_join(loaderThread, NULL);
    pthread_join(customer0Thread, NULL);
    pthread_join(customer1Thread, NULL);
    pthread_join(customer2Thread, NULL);

    printf("\nЗАВЕРШЕНИЕ ПРОГРАММЫ\n");
    exit(EXIT_SUCCESS);
}