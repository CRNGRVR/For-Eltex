//
//  15.05.2023
//
//  Побайтовый вывод числа и изменение в нём одного байта
//

#include <stdio.h>


int main(void) {

    unsigned int b = 0xAABBCCDD;
    char *pointer = &b;


    //  Вывод в изначальном порядке(развёрнутый)
    for(int i = sizeof(b) - 1; i >= 0; i--) {
        printf("%x ", pointer[i]);
    }

    printf("\n");


    int newValue = 0xEF;
    *(pointer + 2) = newValue;

    printf("%x\n", b);

    return 0;
}