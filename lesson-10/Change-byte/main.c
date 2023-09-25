/**
 *  15.05.2023
 *
 *  Побайтовый вывод числа и изменение в нём одного байта
*/

#include <stdio.h>

int main() {
    unsigned int b = 0xAABBCCDD;
    char *pointer = &b;

    //  Вывод в изначальном порядке(развёрнутый)
    for (int index = sizeof(b) - 1; index >= 0; index--) {
        printf("%x ", pointer[index]);
    }
    printf("\n");

    int newValue = 0xEF;
    *(pointer + 2) = newValue;

    printf("%x\n", b);

    return 0;
}
