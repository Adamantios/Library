#include <stdio.h>
#include "books.h"

void printMenu() {

}

void print(book b) {

}

list load(char *filename, list bList) {
    FILE *file = fopen(filename, "r");

    if (file != NULL) {
        fread(&bList, sizeof(book), 1, file);
        fclose(file);
    }

    return bList;
}

void save(char *filename, list bList) {
    FILE *file = fopen(filename, "a");

    if (file != NULL) {
        fwrite(&bList, sizeof(book), 1, file);
        fclose(file);
    }
}

int addBook(book b, list bList) {
    return 0;
}

book findBook(book b, list bList) {
    book result;
    return result;
}

int deleteBook(book b, list bList) {
    return 0;
}

int updateBook(book b, list bList) {
    return 0;
}
