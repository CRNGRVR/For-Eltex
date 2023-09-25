/**
 *  01.08.2023
 *
 *  Простая программа-счётчик
 *  Считает циклом от 0 до 100000000 в одном потоке
*/

#include <stdio.h>

int count = 0;

int main() {
    for (int index = 0; index < 100000000; index++) {
        count++;
    }

    printf("%d\n", count);
}
