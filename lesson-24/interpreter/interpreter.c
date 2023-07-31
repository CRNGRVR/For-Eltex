//
//  28.07.2023
//
//  Командный интерпретатор
//  
//  Приглашает ввести команду, порождает дочерний процесс выбранной команды,
//  по завершению вновь приглашает к вводу.
//  Команда может быть введена с ключами
//

#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(void) {

    while(1) {

        //  Приглашение ко вводу
        printf("\n>> ");

        //  Введённая строка
        char input[150];
        fgets(&input, 150, stdin);


        //  Динамический массив указателей на подстроки
        char **args;
        args = (char*)calloc(1, 8);
    
        //  Разбиение на подстроки
        args[0] = (char*)strtok(&input, &" ");


        int counterOfArgs = 1;

        for (int i = 1; i < 150; i++) {
            args[i] = strtok(NULL, &" ");

            if(args[i] == NULL) {
                counterOfArgs = i;
                break;
            }
        }


        //  Удаление символа переноса строки для корректной работы команд
        args[counterOfArgs - 1] = strtok(args[counterOfArgs - 1], &"\n");

        char filePath[100] = "/bin/";
        strcat(&filePath, args[0]);
        

        pid_t pid = fork();

        if(pid == 0) {
            int result = execv(filePath, args);
            if(result != NULL) printf("Ошибка выполнения\n"); 
        }
        else {
            waitpid(pid, NULL, NULL);
            free(args);
        }
    }
}