//
//  11.05.2023
//
//  Заполнение квадратной матрицы числами по порядку
//

#include <stdio.h>

#define N 3


int main(void) {

    int arr[N][N];
    int num = 1;

    //  Заполнение
    for(int i = 0; i < N; i++) {
        
        for(int j = 0; j < N; j++) {
            arr[i][j] = num;
            num++;
        }
    }


    //  Вывод
    for(int i = 0; i < N; i++) {

        for (int j = 0; j < N; j++) {
            printf("%d ", arr[i][j]);
        }

        printf("\n\n");
    }

    return 0;
}