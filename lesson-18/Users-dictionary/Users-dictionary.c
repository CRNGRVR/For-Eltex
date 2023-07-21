//
//  20.07.2023
//
//  Динамический абонентский справочник
//

#include <malloc.h>
#include <stdio.h>
#include <string.h>


struct Subscriber {

    char name[15];
    char phoneNumber[15];
};


int main(void) {

    struct Subscriber *subscribers = (struct Subscriber*)malloc(30);
    int countOfSubscribers = 0;

    char isRunning = 1;
    char choice;
    

    while(isRunning) {

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

            countOfSubscribers += 1;
            subscribers = realloc(subscribers, sizeof(struct Subscriber) * countOfSubscribers);

            strcpy(subscribers[countOfSubscribers - 1].name, name);
            strcpy(subscribers[countOfSubscribers - 1].phoneNumber, phoneNumber);

            break;

        case '2':

            printf("\n\n");

            for (int i = 0; i < countOfSubscribers; i++) {
                printf("%d. %s %s\n", i + 1, subscribers[i].name, subscribers[i].phoneNumber);
            }
            
            printf("\n\n");

            break;

        case '3':

            printf("\nВведите имя абонента, номер(а) которого нужно найти\n");
            char nameForFind[15] = {};
            scanf("%15s", &nameForFind);

            for (int i = 0; i < countOfSubscribers; i++) {
                
                if(strcmp(nameForFind, subscribers[i].name) == 0) {

                    printf("%s\n", subscribers[i].phoneNumber);
                }
            }

            break;

        case '4':

            printf("\nВведите имя абонента, подлежащего удалению\n");
            char nameForDeletion[15] = {};
            scanf("%15s", &nameForDeletion);
            
            for (int i = 0; i < countOfSubscribers; i++) {
                
                if (strcmp(nameForDeletion, subscribers[i].name) == 0) {
                    
                    for (int j = 0; j < 15; j++) {

                        subscribers[i].name[j] = 0;
                        subscribers[i].phoneNumber[j] = 0;
                    }


                    for (int k = i + 1; k <= countOfSubscribers; k++) {
                        subscribers[k - 1] = subscribers[k];
                    }

                    countOfSubscribers -= 1;
                    subscribers = realloc(subscribers, sizeof(struct Subscriber) * countOfSubscribers);
                }
            }
            

            break;

        case '5':

            isRunning = 0;
            free(subscribers);
            break;

        default:
            printf("Ошибка ввода\n");
            break;
        }
    }
}