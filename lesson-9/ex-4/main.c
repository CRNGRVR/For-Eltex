/**
 *  11.05.2023
 *
 *  Вывод матрицы "улиткой"
*/

#include <stdio.h>

#define N 5

int main() {
    int origin[(N * N)];
    int total[N][N] = {};

    //  Заполнение одномерного массива
    for (int i = 0; i < (N * N); i++) {
        origin[i] = i + 1;
    }

    //  Счётчик итераций по одномерному массиву
    int iOrigin = 0;

    //  Счётчики итераций по итоговому двумерному массиву
    int iTotal = 0;
    int jTotal = 0;

    //  Счетчик элементов, добавляемых в одном из направлений
    //  Нужен для сравнения с границей
    int counterInCurrentDirection = 0;

    //  Счётчик главного цикла
    int mainCounter = 0;

    //  Количество элементов до границы.
    //  Счёт по индексам
    int beforeBorder = N - 1;

    //  Оси направлений заполнения:
    //
    //  Ось X:
    //  l - влево
    //  r - вправо
    //
    //  Ось Y:
    //  u - вверх
    //  d - вниз
    char axis = 'r';


    //  Главный цикл заполнения "улитки"
    while (mainCounter < (N * N)) {
        switch (axis) {
            case 'r':
                total[iTotal][jTotal] = origin[iOrigin];

                //  Проверка на столкновение с границей
                if (counterInCurrentDirection == beforeBorder) {
                    //  Элемент у границы. Происходит подготовка к заполнению
                    //  в следующую сторону
                    iOrigin++;
                    iTotal++;
                    beforeBorder--;
                    counterInCurrentDirection = 0;
                    axis = 'd';
                } else {
                    //  Элемент не у границы. Происходит подготовка к
                    //  заполнению в текущую сторону
                    iOrigin++;
                    jTotal++;
                    counterInCurrentDirection++;
                }

                break;

            case 'd':
                total[iTotal][jTotal] = origin[iOrigin];

                if (counterInCurrentDirection == beforeBorder) {
                    iOrigin++;
                    jTotal--;
                    counterInCurrentDirection = 0;
                    axis = 'l';
                } else {
                    iOrigin++;
                    iTotal++;
                    counterInCurrentDirection++;
                }

                break;

            case 'l':
                total[iTotal][jTotal] = origin[iOrigin];

                if (counterInCurrentDirection == beforeBorder) {
                    iOrigin++;
                    iTotal--;
                    beforeBorder--;
                    counterInCurrentDirection = 0;
                    axis = 'u';
                } else {
                    iOrigin++;
                    jTotal--;
                    counterInCurrentDirection++;
                }

                break;

            case 'u':
                total[iTotal][jTotal] = origin[iOrigin];

                if (counterInCurrentDirection == beforeBorder) {
                    iOrigin++;
                    jTotal++;
                    counterInCurrentDirection = 0;
                    axis = 'r';
                } else {
                    iOrigin++;
                    iTotal--;
                    counterInCurrentDirection++;
                }

                break;
        }

        mainCounter++;
    }

    //  Вывод
    printf("\n");
    for (int index1 = 0; index1 < N; index1++) {
        for (int index2 = 0; index2 < N; index2++) {
            //  Если число имеет 1 знак, то справа делается дополнительный
            //  отступ
            (total[index1][index2] < 10) ? printf("%d  ",
                total[index1][index2]) : printf("%d ", total[index1][index2]);
        }

        printf("\n\n");
    }

    return 0;
}
