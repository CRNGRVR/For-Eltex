//
//  11.05.2023
//
//  Вывод массива размером N в обратном порядке
//

#include <stdio.h>

#define N 5


int main(void) {

    int origin[N];
    int total[N];
    
    //  Заполнение
    for (int i = 0; i < N; i++) {
        origin[i] = i + 1;
    }
    

    //  Вывод до изменений
    printf("До изменений: ");

    for (int i = 0; i < N; i++) {   
        printf("%d ", origin[i]);
    }
        
    printf("\n");


    //  Изменение
    for (int i = 0; i < N; i++) {
        total[i] = origin[(N - 1) - i];
    }
    

    //  Вывод после изменений
    for (int i = 0; i < N; i++) {   
        printf("%d ", total[i]);
    }

    printf("\n");

    return 0;
}