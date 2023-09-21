#include <string.h>

void getDirPath_previous(char *path) {
    for (int i = strlen(path); i > 0; i--) {
        if (path[i] == '/') {
            path[i] = 0;
            break;
        } else {
            path[i] = 0;
        }
    }
}

void getDirPath_next(char *path, char *newRelativePath) {
    strcat(path, "/");
    strcat(path, newRelativePath);
}
