//
//  16.05.2023
//
//  Абонентский справочник
//
//  1. Список из 100 абонентов, являющихся структурами
//  2. Меню с фунциями "Добавить абонента", "Вывести список", "Поиск по имени", "Удалить абонента",
//  "Выйти из справочника"
//

#include <stdio.h>
#include <string.h>


int main(void) {

    struct Subscriber {

        char name[15];
        char phoneNumber[15];
    };

    struct Subscriber subscribers[100];


    char isRunning = 1;
    char choice;


    //  Очистка массива перед использованием. Какой ужас
    for (int i = 0; i < 100; i++) {

        for (int j = 0; j < 15; j++) {
            subscribers[i].name[j] = 0;
            subscribers[i].phoneNumber[j] = 0;
        }
    }
    

    while(isRunning){

        printf("\nВыберите команду:\n1. Добавить абонента.\n2. Вывести список абонентов.\n3. Найти абонента по имени\n4. Удалить абонента\n5. Выйти из справочника\n");
        scanf("%s", &choice);
        isRunning = 1;
        

        switch (choice) {
        case '1':

            printf("Введите имя абонента\n");
            char name[15] = {};
            scanf("%15s", &name);

            printf("Введите номер абонента\n");
            char phoneNumber[15] = {};
            scanf("%15s", &phoneNumber);


            //  Поиск пустого места в массиве и вставка в него элемента
            for(int i = 0; i < 100; i++) {
                
                if(strcmp(subscribers[i].name, "") == 0 && strcmp(subscribers[i].phoneNumber, "") == 0) {
                    
                    strcpy(subscribers[i].name, name);
                    strcpy(subscribers[i].phoneNumber, phoneNumber);
                    
                    break;
                }
            }

            break;

        case '2':

            printf("\n\n");

            for (int i = 0; i < 100; i++) {
                
                if (strcmp(subscribers[i].name, "") != 0) {
                    printf("%d. %s %s\n", i + 1, subscribers[i].name, subscribers[i].phoneNumber);
                }   
            }
            
            printf("\n\n");

            break;

        case '3':

            printf("\nВведите имя абонента, номер(а) которого нужно найти\n");
            char nameForFind[15] = {};
            scanf("%15s", &nameForFind);

            for (int i = 0; i < 100; i++) {
                
                if(strcmp(nameForFind, subscribers[i].name) == 0) {

                    printf("%s\n", subscribers[i].phoneNumber);
                }
            }
            
            break;

        case '4':

            printf("\nВведите имя абонента, подлежащего удалению\n");
            char nameForDeletion[15] = {};
            scanf("%15s", &nameForDeletion);
            
            for (int i = 0; i < 100; i++) {
                
                if (strcmp(nameForDeletion, subscribers[i].name) == 0) {
                    
                    for (int j = 0; j < 15; j++) {

                        subscribers[i].name[j] = 0;
                        subscribers[i].phoneNumber[j] = 0;
                    }
                }
            }

            break;

        case '5':

            isRunning = 0;
            break;

        default:
            printf("Ошибка ввода\n");
            break;
        }
    }
}