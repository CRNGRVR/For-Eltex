//
//  28.08.2023
//
//  Командный интерпретатор с конвейром
//
//  Приглашает ввести команду, порождает дочерний процесс выбранной команды,
//  по завершению вновь приглашает к вводу.
//  Команды могут быть введены с ключами и конвейером
//


//  TEST: ls -l | wc -l

//  Гирлянда до рефакторинга
#include <unistd.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>


#define PTR_SIZE 8

int main() {

    char input[150] = {};

    char **tokens;
    int tokenCount = 0;

    char *command;
    char **args;

    pid_t pid;

    int fd1; 
    int fd2;

    
    while (1) {
        
        //  Приглашение ко вводу
        printf("\n>> ");

        fgets(&input, 150, stdin);

        tokens = (char**)calloc(1, PTR_SIZE);
        int m = malloc_usable_size(tokens);
        tokens[0] = (char*)strtok(&input, &"|");

        //  Разделение на "команда ключ ключ"
        for(int index = 1; index < 150; index++) {

            tokenCount++;

            tokens = (char**)realloc(tokens, (tokenCount + 1) * PTR_SIZE);
            m = malloc_usable_size(tokens);
            tokens[tokenCount] = (char*)strtok(NULL, &"|");

            if(tokens[tokenCount] == NULL) {
                tokens[tokenCount - 1] = strtok(tokens[tokenCount - 1], &"\n");
                break;
            }
        }


        
        for(int index = 0; index < tokenCount; index++) {

            command = strtok(tokens[index], &" ");
            args = calloc(1, PTR_SIZE);
            args[0] = command;

            for (int index1 = 1; index1 < 150; index1++) {

                args = (char**)realloc(args, (index1 + 1) * PTR_SIZE);

                args[index1] = (char*)strtok(NULL, &" ");
                if(args[index1] == NULL) break;
            }

            //  ТУТ ВЫПОЛНЕНИЕ

            char filePath[100] = "/bin/";
            strcat(&filePath, command);

            char buff;

            fd1 = open("tmp1", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
            fd2 = open("tmp2", O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);

            while (0 != read(fd2, &buff, 1)) {
                write(fd1, &buff, 1);
            }

        

            close(fd2);

            fd2 = open("tmp2", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
            
            
            pid = fork();

            if(pid == 0) {

                lseek(fd1, 0, SEEK_SET);
                
                dup2(fd1, STDIN_FILENO);
        

                if((index + 1) == tokenCount) {
                    //  Если выполняется последняя программа, её вывод должен попасть на экран
                    dup2(STDOUT_FILENO, fd2);
                } else {
                    dup2(fd2, STDOUT_FILENO);
                }


                int result = execv(filePath, args);
                if (result != NULL){
                    printf("Ошибка выполнения\n");
                    exit(EXIT_FAILURE);
                } 
            }
            else {
                waitpid(pid, NULL, NULL);
            }


            close(fd1);
            close(fd2);

            free(args);
        }


        tokenCount = 0;
        command = NULL;
        free(tokens);
    }
}