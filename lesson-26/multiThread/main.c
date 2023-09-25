/**
 *  01.08.2023
 *
 *  Многопоточная программа-счётчик
 *  Считает циклом от 0 до 100000000 в 1000 потоках и имеет непредсказуемый
 *  результат
*/

#include <stdio.h>
#include <pthread.h>

int count = 0;

void *threadWork(void *args) {
    for (int index = 0; index < 100000; index++) {
        count++;
    }
}

int main() {
    //  Идентификаторы потоков
    pthread_t threads[1000];

    //  Создание потоков
    for (int index = 0; index < 1000; index++) {
        pthread_create(&threads[index], NULL, threadWork, NULL);
    }

    //  Установка ожидания потоков
    for (int index = 0; index < 1000; index++) {
        pthread_join(threads[index], NULL);
    }

    printf("%d\n", count);
}
