//
//  08.05.2023
//
//  Побайтовый вывод и замена одного байта в целом числе
//

#include <stdio.h>


int main(void){

    unsigned int a = 0xAABBCCDD;
    int mask = 0x000000FF;

    printf("Начальное значение: %x\n", a);

    for (int i = 0; i < 4; i++)
    {
        printf("%x\n", (a >> i * 8) & mask);
    }

    //  Заменим второй байт
    int newValue = 0x00EF0000;
    int maskForReplacement = 0xFF00FFFF;
    
    a = a & maskForReplacement;
    a = a | newValue;

    printf("Изменённое значение: %x\n", a);


    return 0;
}