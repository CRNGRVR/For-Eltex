/**
 *  11.05.2023
 *
 *  Заполнение квадратной матрицы числами по порядку
*/

#include <stdio.h>

#define N 3

int main() {
    int arr[N][N];
    int num = 1;

    //  Заполнение
    for (int index1 = 0; index1 < N; index1++) {
        for (int index2 = 0; index2 < N; index2++) {
            arr[index1][index2] = num;
            num++;
        }
    }

    //  Вывод
    for (int index1 = 0; index1 < N; index1++) {
        for (int index2 = 0; index2 < N; index2++) {
            printf("%d ", arr[index1][index2]);
        }

        printf("\n\n");
    }

    return 0;
}
