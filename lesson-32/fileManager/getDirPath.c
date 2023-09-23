#include <string.h>

void getDirPath_previous(char *path) {
    for (int index = strlen(path); index > 0; index--) {
        if (path[index] == '/') {
            path[index] = 0;
            break;
        } else {
            path[index] = 0;
        }
    }
}

void getDirPath_next(char *path, char *newRelativePath) {
    strcat(path, "/");
    strcat(path, newRelativePath);
}
