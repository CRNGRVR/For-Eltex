/**
 *  11.05.2023
 *
 *  Вывод матрицы, где верхняя левая часть состоит из нулей, а правая нижняя
 *  из единиц
*/

#include <stdio.h>

#define N 3

int main() {
    int surface[N][N];
    int zeroInRow = 0;

    for (int index1 = 0; index1 < N; index1++) {
        for (int index2 = 0; index2 < N; index2++) {
            zeroInRow = N - (index1 + 1);
            surface[index1][index2] = (index2 < zeroInRow) ? 0 : 1;
        }
    }

    for (int index1 = 0; index1 < N; index1++) {
        for (int index2 = 0; index2 < N; index2++) {
            printf("%d", surface[index1][index2]);
        }

        printf("\n");
    }

    return 0;
}
