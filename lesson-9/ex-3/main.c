//
//  11.05.2023
//
//  Вывод матрицы, где верхняя левая часть состоит из
//  нулей, а правая нижняя - из единиц
//

#include <stdio.h>

#define N 3


int main(void) {

    int surface[N][N];
    int zeroInRow = 0;

    for (int i = 0; i < N; i++) {

        for (int j = 0; j < N; j++) {
            
            zeroInRow = N - (i + 1);
            surface[i][j] = (j < zeroInRow) ? 0 : 1;
        }
    }
    

    for (int i = 0; i < N; i++) {

        for (int j = 0; j < N; j++) {

            printf("%d", surface[i][j]);
        }

        printf("\n");
    }


    return 0;
}