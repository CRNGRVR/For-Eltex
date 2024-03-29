#ifndef _PARSER_MODULE
#define _PARSER_MODULE 1

/**
 *  parser - принимает строку-команду, делит на имя файла, флаги и формирует
 *  путь к исполняемому файлу
 *
 *  command:    Указатель на строку-команду, которую функция будет делить.
 *  filePath:   Указатель на путь к файлу, будет сформирован по завершению
 *              работы функции.
 *  args_o:     Указатель на динамический массив, в котором будут находиться
 *              указатели на флаги по завершению работы функции.
 *
 *  Примечание: функция выделяет динамическую память, по завершению работы с
 *  данными память необходимо освободить вручную, вызвав free(args_o)
*/
void parser(char *command, char *filePath, char ***args_o);

#endif
