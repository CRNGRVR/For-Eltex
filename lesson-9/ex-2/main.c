/**
 *  11.05.2023
 *
 *  Вывод массива размером N в обратном порядке
*/

#include <stdio.h>

#define N 5

int main() {
    int origin[N];
    int total[N];

    //  Заполнение
    for (int index = 0; index < N; index++) {
        origin[index] = index + 1;
    }

    //  Вывод до изменений
    printf("До изменений: ");
    for (int index = 0; index < N; index++) {
        printf("%d ", origin[index]);
    }
    printf("\n");


    //  Изменение
    for (int index = 0; index < N; index++) {
        total[index] = origin[(N - 1) - index];
    }

    //  Вывод после изменений
    for (int index = 0; index < N; index++) {
        printf("%d ", total[index]);
    }

    printf("\n");
    return 0;
}
