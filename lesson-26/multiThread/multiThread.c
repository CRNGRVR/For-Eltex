//
//  01.08.2023
//
//  Многопоточная программа-счётчик
//  Считает циклом от 0 до 100000000 в 1000 потоках и имеет непредсказуемый
//  результат
//

#include <stdio.h>
#include <pthread.h>

int count = 0;


void *threadWork(void *args) {

    for (int i = 0; i < 100000; i++)
    {
        count++;
    }
}


int main(void) {

    //  Идентификаторы потоков
    pthread_t threads[1000];

    //  Создание потоков
    for (int i = 0; i < 1000; i++)
    {
        pthread_create(&threads[i], NULL, threadWork, NULL);
    }

    //  Установка ожидания потоков
    for (int i = 0; i < 1000; i++)
    {
        pthread_join(threads[i], NULL);
    }
    

    printf("%d\n", count);
}
