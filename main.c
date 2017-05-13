#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "books.h"

void addBookTest(char *filename, list bList) {
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

    // initialise a second book.
    strcpy(newBook->author, "Someone");
    strcpy(newBook->title, "His Book");
    newBook->genre = FICTION;
    strcpy(newBook->reviews[0], "First Review.");
    strcpy(newBook->reviews[1], "Second Review.");
    strcpy(newBook->reviews[2], "Third Review.");
    strcpy(newBook->reviews[3], "Fourth Review.");

    // add the second book at the book list.
    addBook(*newBook, bList);

    // save changes to the file.
    save(filename, bList);

    // print the book menu.
    printf("Printing all the available books after adding new books...\n");
    printMenu();
}

void findBookTest(list bList) {
    // allocate memory for the book.
    book *bookToSearch = (book *) malloc(sizeof(book));

    // set the book's id to 1.
    bookToSearch->id = 1;

    // find the book with id 1 from the list.
    *bookToSearch = findBook(*bookToSearch, bList);

    // free the memory for the book.
    free(bookToSearch);

    // print the book that was found.
    printf("Printing the book with id 1...\n");
    print(*bookToSearch);
}

void deleteBookTest(char *filename, list bList) {
    // allocate memory for the book.
    book *bookToDelete = (book *) malloc(sizeof(book));

    // set the book's id to 1.
    bookToDelete->id = 1;

    // delete the book with id 1 from the list.
    if (deleteBook(*bookToDelete, bList))
        printf("Something went wrong while trying to delete the book...\n");
    else {
        // save changes to the file.
        save(filename, bList);

        // print the new book menu.
        printf("Printing the book menu after deleting the book with id 1...\n");
        printMenu();
    }

    // free the memory for the book.
    free(bookToDelete);
}

void updateBookTest(char *filename, list bList) {
    // allocate memory for the book.
    book *bookToUpdate = (book *) malloc(sizeof(book));

    // set the book's id to 2.
    bookToUpdate->id = 2;

    // change the information of the book.
    strcpy(bookToUpdate->author, "Someone Else");
    strcpy(bookToUpdate->title, "The Best Book");
    bookToUpdate->genre = FICTION;
    strcpy(bookToUpdate->reviews[0], "First Review.");
    strcpy(bookToUpdate->reviews[1], "Second Review.");
    strcpy(bookToUpdate->reviews[2], "Third Review.");

    // update the book with id 2 from the list.
    if (updateBook(*bookToUpdate, bList))
        printf("Something went wrong while trying to update the book...\n");
    else {
        // save changes to the file.
        save(filename, bList);

        // print the new book menu.
        printf("Printing the book menu after updating the book with id 2...\n");
        printMenu();
    }

    // free the memory for the book.
    free(bookToUpdate);
}

void startTesting(char *filename) {
    // create a book list. It will be empty if the filename is empty or does not exist.
    list bList = load(filename);

    // check the file's content.
    printf("Printing all the available books...\n");
    printMenu();

    // test the functions.
    addBookTest(filename, bList);
    findBookTest(bList);
    deleteBookTest(filename, bList);
    updateBookTest(filename, bList);
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
