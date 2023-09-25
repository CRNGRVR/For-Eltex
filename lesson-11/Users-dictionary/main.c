/**
 *  16.05.2023
 *
 *  Абонентский справочник
 *  1. Список из 100 абонентов, являющихся структурами
 *  2. Меню с фунциями "Добавить абонента", "Вывести список", "Поиск по имени",
 *     "Удалить абонента", "Выйти из справочника"
*/

#include <stdio.h>
#include <string.h>

struct Subscriber {
    char name[15];
    char phoneNumber[15];
};

void insert(struct Subscriber *subscribers);
void showAll(struct Subscriber *subscribers);
void findSubscriber(struct Subscriber *subscribers);
void deleteSubscriber(struct Subscriber *subscribers);

int main() {
    struct Subscriber subscribers[100];
    char isRunning = 1;
    char choice;

    //  Очистка массива перед использованием.
    for (int index1 = 0; index1 < 100; index1++) {
        for (int index2 = 0; index2 < 15; index2++) {
            subscribers[index1].name[index2] = 0;
            subscribers[index1].phoneNumber[index2] = 0;
        }
    }

    while (isRunning) {
        printf("\nВыберите команду:\n1. Добавить абонента.\n");
        printf("2. Вывести список абонентов.\n3. Найти абонента по имени\n");
        printf("4. Удалить абонента\n5. Выйти из справочника\n");
        scanf("%s", &choice);
        isRunning = 1;

        switch (choice) {
            case '1':
                insert(&subscribers);
                break;

            case '2':
                showAll(&subscribers);
                break;

            case '3':
                findSubscriber(&subscribers);
                break;

            case '4':
                deleteSubscriber(&subscribers);
                break;

            case '5':
                //  Выход
                isRunning = 0;
                break;

            default:
                printf("Ошибка ввода\n");
                break;
        }
    }
}

//  Добавить абонента
void insert(struct Subscriber *subscribers) {
    printf("\nВведите имя абонента\n");
    char name[15] = {};
    scanf("%15s", &name);

    printf("\nВведите номер абонента\n");
    char phoneNumber[15] = {};
    scanf("%15s", &phoneNumber);

    //  Поиск пустого места в массиве и вставка в него элемента
    for (int index = 0; index < 100; index++) {
        if (strcmp(subscribers[index].name, "") == 0 && 
                   strcmp(subscribers[index].phoneNumber, "") == 0) {
            strcpy(subscribers[index].name, name);
            strcpy(subscribers[index].phoneNumber, phoneNumber);
            break;
        }
    }
}

//  Вывести список
void showAll(struct Subscriber *subscribers) {
    printf("\n\n");

    for (int index = 0; index < 100; index++) {
        if (strcmp(subscribers[index].name, "") != 0) {
            printf("%d. %s %s\n", index + 1, subscribers[index].name,
                   subscribers[index].phoneNumber);
        }
    }
    printf("\n\n");
}

//  Поиск по имени
void findSubscriber(struct Subscriber *subscribers) {
    printf("\nВведите имя абонента, номер(а) которого нужно найти\n");
    char nameForFind[15] = {};
    scanf("%15s", &nameForFind);
    printf("\n");

    for (int index = 0; index < 100; index++) {
        if (strcmp(nameForFind, subscribers[index].name) == 0) {
            printf("%s\n", subscribers[index].phoneNumber);
        }
    }
    printf("\n");
}

//  Удалить абонента
void deleteSubscriber(struct Subscriber *subscribers) {
    printf("\nВведите имя абонента, подлежащего удалению\n");
    char nameForDeletion[15] = {};
    scanf("%15s", &nameForDeletion);

    for (int index1 = 0; index1 < 100; index1++) {
        if (strcmp(nameForDeletion, subscribers[index1].name) == 0) {
            for (int index2 = 0; index2 < 15; index2++) {
                subscribers[index1].name[index2] = 0;
                subscribers[index1].phoneNumber[index2] = 0;
            }
        }
    }
}
