/**
 *  20.07.2023
 *
 *  Динамический абонентский справочник
*/

#include <malloc.h>
#include <stdio.h>
#include <string.h>

struct Subscriber {
    char name[15];
    char phoneNumber[15];
};

int main() {
    struct Subscriber *subscribers = (struct Subscriber*)malloc(30);
    int countOfSubscribers = 0;
    char isRunning = 1;
    char choice;

    while (isRunning) {
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

                for (int index = 0; index < countOfSubscribers; index++) {
                    printf("%d. %s %s\n", index + 1, subscribers[index].name, subscribers[index].phoneNumber);
                }

                printf("\n\n");
                break;

            case '3':
                printf("\nВведите имя абонента, номер(а) которого нужно найти\n");
                char nameForFind[15] = {};
                scanf("%15s", &nameForFind);

                for (int index = 0; index < countOfSubscribers; index++) {
                    if (strcmp(nameForFind, subscribers[index].name) == 0) {
                        printf("%s\n", subscribers[index].phoneNumber);
                    }
                }

                break;

            case '4':
                printf("\nВведите имя абонента, подлежащего удалению\n");
                char nameForDeletion[15] = {};
                scanf("%15s", &nameForDeletion);

                for (int index1 = 0; index1 < countOfSubscribers; index1++) {
                    if (strcmp(nameForDeletion, subscribers[index1].name) == 0) {
                        for (int index2 = 0; index2 < 15; index2++) {
                            subscribers[index1].name[index2] = 0;
                            subscribers[index1].phoneNumber[index2] = 0;
                        }

                        for (int index3 = index1 + 1; index3 <= countOfSubscribers; index3++) {
                            subscribers[index3 - 1] = subscribers[index3];
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
