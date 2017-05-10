#include <stdio.h>
#include "books.h"

int main(int argc, char *argv[]) {
    char *filename;

    if (argc == 2) {
        filename = argv[1];
        list bList = load(filename);
        printMenu();
    } else if (argc > 2)
        printf("Too many arguments supplied.\n");
    else
        printf("Please provide the filename as an argument.\n");

    return 0;
}