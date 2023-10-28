#ifndef _SEMWORK
#define _SEMWORK 1

/**
 *  semwork_init - подготовка семафоров у работе
 *
 *  Эта функция инициализирует 1 семафор, его операции и назначает сигнал для
 *  удаления семафора при выходе 
*/
void semwork_init();

/**
 *  semwork_pending - блокирование семафора и ожидание его разблокировки
*/
void semwork_pending();

/**
 *  semwork_unlock - разблокировка семафора
*/
void semwork_unlock();

#endif
