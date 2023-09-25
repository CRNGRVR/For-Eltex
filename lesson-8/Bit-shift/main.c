/**
 *  08.05.2023
 *
 *  Побайтовый вывод и замена одного байта в целом числе
*/

#include <stdio.h>

int main() {
    unsigned int a = 0xAABBCCDD;
    int mask = 0x000000FF;

    printf("Начальное значение: %x\n", a);

    for (int index = 0; index < 4; index++) {
        printf("%x\n", (a >> index * 8) & mask);
    }

    //  Заменим второй байт
    int newValue = 0x00EF0000;
    int maskForReplacement = 0xFF00FFFF;

    a = a & maskForReplacement;
    a = a | newValue;

    printf("Изменённое значение: %x\n", a);
    return 0;
}
