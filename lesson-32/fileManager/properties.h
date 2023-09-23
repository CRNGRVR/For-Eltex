#ifndef _PROPERTIES
#define _PROPERTIES 1

//  Максимальный размер пути к файлу
#define MAX_PATH_SIZE 1000

//  Длина и ширина области, доступной для списка
//  От фактического размера:
//  По длине -2 для рамок и -1 для пункта "/.."
//  По ширине -2 для рамок
#define SCREEN_HEIGHT_FOR_LIST 22
#define SCREEN_WIDTH_FOR_LIST 38

//  Обозначение левого и правого окон
#define LEFT_ACTIVE 0
#define RIGHT_ACTIVE 1

//  Шаг смещения списка при достижении края экрана
#define ALIGNMENT_STEP 8

#endif
