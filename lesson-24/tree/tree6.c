/**
 *  28.07.2023
 *
 *  Построение древа процессов:
 *
 *              1
 *             / \
 *            2   3
 *           / \   \
 *          4   5  [6]
 *
 *  Процесс 6
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    printf("\nProcess 6.\nPID: %d\nPPID: %d\n\n", getpid(), getppid());
    while (1) {}
}
