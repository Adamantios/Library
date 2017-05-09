#include <stdio.h>
#include <stdlib.h>
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
    // allocate memory for the new book.
    list *newBook = (list *) malloc(sizeof(list));

    // in case of failure print an error message and finish program with exit code -1.
    if (newBook == NULL) {
        fprintf(stderr, "Unable to allocate memory for a new book.\n");
        exit(-1);
    }

    // create the new book.
    newBook->book = b;
    newBook->next = NULL;

    list *current = &bList;

    // move at the end of the list.
    while (current->next != NULL)
        current = current->next;

    // add the new node at the end of the list.
    current->next = newBook;

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
