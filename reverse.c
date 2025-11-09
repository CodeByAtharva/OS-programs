#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No numbers received!\n");
        return 1;
    }

    printf("\nNew program (reverse.c) executed using execve()\n");
    printf("Array elements in reverse order: ");

    for (int i = argc - 1; i > 0; i--) {
        printf("%s ", argv[i]);
    }
    printf("\n");

    return 0;
}
