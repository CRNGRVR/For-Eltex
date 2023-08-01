//
//  01.08.2023
//
//  Простая программа-счётчик
//  Считает циклом от 0 до 100000000 в одном потоке
//

#include <stdio.h>


int count = 0;

int main(void) {

    for(int i = 0; i < 100000000; i++) {
        count++;
    }

    printf("%d\n", count);
}
