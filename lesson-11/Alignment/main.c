/**
 *  16.05.2023
 *
 *  Упражнение со структурами в памяти
*/

#include <stdio.h>

struct test {
    char a;
    int b;
};

struct testPacked {
    char a;
    int b;
} __attribute__((packed));

int main() {
    char str[10] = {'A', 0, 0, 0, 0, 'B', 0, 0, 0, 0};
    struct test *my_test_ptr = &str;
    struct testPacked *my_testPacked_ptr = &str;

    printf("a: %c, b: %c\n", my_test_ptr->a, (my_test_ptr + 1)->a);
    printf("a: %c, b: %c\n", my_testPacked_ptr->a, (my_testPacked_ptr + 1)->a);
    return 0;
}
