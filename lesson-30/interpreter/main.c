/**
 *  28.08.2023
 *
 *  Командный интерпретатор с конвейером
 *  Приглашает ввести команду, порождает дочерний процесс выбранной команды,
 *  по завершению вновь приглашает к вводу.
 *  Команды могут быть введены с ключами и конвейером
*/

#include <malloc.h>
#include <stdbool.h>
#include "input.h"
#include "parser.h"
#include "moveDataAndErase.h"
#include "execute_p.h"

#define MAX_INPUT_SIZE 150
#define MAX_FILEPATH_SIZE 100
#define INPUT_FILE_NAME "tmp1"
#define OUTPUT_FILE_NAME "tmp2"

int main() {

    //  Подстроки-команды конвейера
    char **commands;
    int commandsCount = 0;

    //  Путь к исполняемому файлу
    char path[MAX_FILEPATH_SIZE] = "";
    char **args;

    while (1) {
        commandsCount = input(&commands, MAX_INPUT_SIZE);

        //  Выполнение конвейера. За каждую итерацию выполняется одна программа
        for (int index = 0; index < commandsCount; index++) {
            parser(commands[index], path, &args);
            moveDataAndErase(INPUT_FILE_NAME, OUTPUT_FILE_NAME);

            bool isLastExecutionInQueue = ((index + 1) == commandsCount);
            execute_p(path, args, isLastExecutionInQueue, INPUT_FILE_NAME,
                      OUTPUT_FILE_NAME);

            free(args);
        }

        commandsCount = 0;
        free(commands);
    }
}
