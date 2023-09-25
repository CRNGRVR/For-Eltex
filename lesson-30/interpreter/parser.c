#include <string.h>
#include <malloc.h>

#define BIN_FILES_FOLDER "/bin/"

void parser(char *command, char *filePath, char ***args_o) {

    char *binName;
    binName = strtok(command, " ");

    //  Формирование пути к исполняемому файлу
    *filePath = NULL;
    strcat(filePath, BIN_FILES_FOLDER);
    strcat(filePath, binName);


    char **args = (char**)calloc(1, sizeof(char**));

    //  Первым аргументом должно быть имя исполняемого файла
    args[0] = binName;

    for (int index1 = 1; ; index1++) {
        args = (char**)realloc(args, (index1 + 1) * sizeof(char**));
        args[index1] = (char*)strtok(NULL, " ");
        if (args[index1] == NULL) break;
    }

    *args_o = args;
}
