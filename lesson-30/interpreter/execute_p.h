#ifndef _EXECUTE_MODULE
#define _EXECUTE_MODULE 1

/**
 *  execute_p - запускает исполняемый файл с аргументами, перенаправляя вывод
 *  первой программы на ввод второй
 *
 *  path:               Путь исполняемого файла.
 *  args:               Массив аргументов.
 *  isLastExecOnQueue:  Флаг, указывающий является ли исполняемая программа
 *                      последней в очереди конвейера.
 *  inputFP:            Путь файла, используемого вместо потока ввода.
 *  outputFP:           Путь файла, используемого вместо потока вывода.
 *
 *  Эта функция ориентирована на выполнение сегмента конвейера. Перед
 *  выполнением поток ввода перенаправляется из inputFP, поток вывода в
 *  outputFP. Если указать isLastExecInQueue = true, вывод будет перенаправлен
 *  на экран.
*/
void execute_p(char *path, char **args, bool isLastExecInQueue, char *inputFP,
               char *outputFP);

#endif