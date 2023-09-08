#include <stdio.h>
#include <string.h>
#include <malloc.h>


int input(char ***tokens_ext, int maxInputSize) {

    //  Строка ввода с клавиатуры
    char inputStr[maxInputSize];

    //  Указатели на подстроки вида: команда -флаг -флаг
    //  Включает указатели из inputStr
    char **tokens_tmp;

    //  Указатели на строки как в tokens_tmp, но адреса больше не ссылаются на
    //  inputStr. Если не дублировать строки сюда, после выхода из функции
    //  указатели будут ссылаться на мусор(освобождённую память)
    char **tokens;

    //  Количество подстрок, разделённых '|'
    int tokenCount = 0;


    printf("\n>> ");
    fgets(&inputStr, maxInputSize, stdin);

    tokens_tmp = (char**)calloc(1, sizeof(char**));
    tokens_tmp[0] = (char*)strtok(&inputStr, "|");

    //  Разделение на: команда -флаг -флаг
    for (int index = 1; index < 150; index++) {

        tokenCount++;
        tokens_tmp = (char**)realloc(tokens_tmp, (tokenCount + 1) * sizeof(char**));
        tokens_tmp[tokenCount] = (char*)strtok(NULL, "|");

        if (tokens_tmp[tokenCount] == NULL) {
            tokens_tmp[tokenCount - 1] = strtok(tokens_tmp[tokenCount - 1], "\n");
            break;
        }
    }


    //  Дублирование в итоговый массив
    tokens = (char**)calloc(tokenCount, sizeof(char**));
    for (int index = 0; index < tokenCount; index++) {
        tokens[index] = strdup(tokens_tmp[index]);
    }

    free(tokens_tmp);

    *tokens_ext = tokens;
    return tokenCount;
}
