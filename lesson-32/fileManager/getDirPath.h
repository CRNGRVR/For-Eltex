#ifndef _GET_DIR_PATH
#define _GET_DIR_PATH 1

/**
 *  getDirPath_previous - изменяет путь на одну папку назад
 *
 *  path:   Абсолютный путь к папке.
 *
 *  Эта функция стирает символы с конца из path до первого символа '/'
*/
void getDirPath_previous(char *path);

/**
 *  getDirPath_next - добавляет к пути следующую указанную папку
 *
 *  path:               Абсолютный путь к папке.
 *  newRelativePath:    Следующая выбранная папка.
 *
 *  Эта функция добавляет в конец к path символ '/' и newRelativePath.
*/
void getDirPath_next(char *path, char *newRelativePath);

#endif
