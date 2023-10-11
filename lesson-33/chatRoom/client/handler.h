#ifndef _HANDLER
#define _HANDLER 1

/**
 *  handler_msg - обрабатывает новые сообщения
 *
 *  args:   Аргументы, передаваемые в функцию потока. Предполагается, что будет
 *          передана структура threadHandlersArgs_msg.
 *
 *  Эта функция ожидает сообщение типа msg_service_list в очереди ввода 
 *  сообщений. Блокируется до получения, после получения заполняет переданный
 *  в аргументах список сообщений, и перерисовывает экран.
 *  Предполагается использование в отдельном потоке, так как большую часть
 *  времени поток блокируется.
*/
void *handler_msg(void *args);

/**
 *  handler_names - обрабатывает новые подключения
 *
 *  args:   Аргументы, передаваемые в функцию потока. Предполагается, что будет
 *          передана структура threadHandlersArgs_name.
 *
 *  Эта функция ожидает сообщение типа msg_service_names в очереди ввода
 *  имён. Блокируется до получения, после получения заполняет переданный
 *  в аргументах список имён, и перерисовывает экран.
 *  Предполагается использование в отдельном потоке, так как большую часть
 *  времени поток блокируется.
*/
void *handler_names(void *args);

/**
 *  handler_input - обрабатывает действия пользователя
 *
 *  args:   Аргументы, передаваемые в функцию потока. Предполагается, что будет
 *          передана структура threadHandlersArgs_input.
 *
 *  Эта функция ожидает от пользователя ввод с клавиатуры. По 
 *  нажатию [F3] уведомит сервер об отключении и завершит программу. По нажатию
 *  обычных клавиш будет заполнять поле ввода сообщения inputw,
 *  по нажатию [ENTER] отправит сообщение и очистит поле ввода.
 *  Предполагается использование в отдельном потоке, так как большую часть
 *  времени поток блокируется.
*/
void *handler_input(void *args);

#endif
