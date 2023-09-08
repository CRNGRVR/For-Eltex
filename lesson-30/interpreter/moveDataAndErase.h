#ifndef _MOVE_DATA_AND_ERASE_MODULE
#define _MOVE_DATA_AND_ERASE_MODULE 1

/**
 *  moveDataAndErase - перемещает данные из файла pathSrc в pathDest,
 *  стирает pathSrs
 *
 *  pathDest:   Путь(или имя) файла, в который будет произведена запись.
 *  pathSrc:    Путь(или имя) файла, из которого будет произведена запись.
 *
 *  Эта функция усекает файл pathDest до нулевой длины(стирает), записывает в
 *  него данные из файла pathSrc. После записи стирает pathSrc.
*/

void moveDataAndErase(char *pathDest, char *pathSrc);

#endif
