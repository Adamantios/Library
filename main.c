#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "books.h"

void firstTest(char *filename, list bList) {
    // allocate memory for a new book.
    book *newBook = (book *) malloc(sizeof(book));

    // initialise the new book.
    strcpy(newBook->author, "Me");
    strcpy(newBook->title, "My Book");
    newBook->genre = FICTION;
    strcpy(newBook->reviews[0], "First Review.");
    strcpy(newBook->reviews[1], "Second Review.");

    // add the new book at the book list.
    addBook(*newBook, bList);

    // save changes to the file.
    save(filename, bList);

    // print the book menu.
    printMenu();
}

void startTesting(char *filename) {
    // create a book list. It will be empty if the filename is empty or does not exist.
    list bList = load(filename);

    // check the file's content.
    printf("Printing all the available books...\n");
    printMenu();

    firstTest(filename, bList);
}

int main(int argc, char *argv[]) {
    if (argc == 2)
        startTesting(argv[1]);
    else if (argc > 2)
        printf("Too many arguments supplied.\n");
    else
        printf("Please provide the filename as an argument.\n");

    return 0;
}
