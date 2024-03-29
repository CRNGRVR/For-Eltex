#ifndef _SINGLE_CLIENT
#define _SINGLE_CLIENT 1

/**
 *  single_client - узнаёт адрес обслуживабщего сервера у слушающего,
 *  подключается и обслуживается
 *
 *  Эта функция подключается к слушающему сервверу, получает от него адрес
 *  обслуживающего, подключается и обслуживается. Имеет 3 потокобезопасных
 *  счётчика, которые увеличиваются при:
 *  1.  Отказе слушающего сервера.
 *  2.  Проблема, возникшая во время обслуживания.
 *  3.  Успешное обслуживание.
 *  Счётчики представляют собой глобальные переменные и могут быть выведены
 *  функцией print_result.
 *
 *  Примечание: предполагается, что функции single_client будут порождены в
 *  виде большого количества процессов. С учётом этого сделаны счётчики для
 *  статистики, описанные выше.
*/
void *single_client();

/**
 *  print_result - выводит счётчики отказа запроса, проблем в обслуживании и
 *  успешного обслуживания
*/
void print_result();

#endif
