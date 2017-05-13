#include <stdio.h>
#include <string.h>
#include <malloc.h>
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

void showMenu() {
    printf("Available commands:\n");
    printf("1: Create a new book.\n");
    printf("2: Delete a book.\n");
    printf("3: Search for a book.\n");
    printf("4: Update a book.\n");
    printf("5: Print a book's information.\n");
    printf("6: Print the book menu.\n");
    printf("7: Exit.\n");
    printf("Please insert a number in order to run a command.\n");
}

int yesOrNo() {
    printf("Press Y for yes or N for no.\n");
    int choice;
    choice = getchar();

    while (choice != 'N' && choice != 'Y') {
        printf("Unknown command! Please press Y for yes and N for no.");
        choice = getchar();
    }

    return choice == 'Y' ? 1 : 0;
}

genres readGenre() {
    printf("Please give a new genre for the book: ");
}

void executeCommands(char *filename, list bList) {
    showMenu();

    // read the user's command, until it is valid.
    int command;
    scanf("%d", &command);

    while (command < 1 || command > 7) {
        printf("Unknown command!\nPlease try inserting one of the available numbers.\n");
        scanf("%d", &command);
    }

    // execute the user's command.
    switch (command) {
        case 1:
            create();
        case 2:
            delete();
        case 3:
            search();
        case 4:
            printf("Please provide the id of the book that you want to update: ");

            // allocate memory for the book.
            book *bookToUpdate = (book *) malloc(sizeof(book));

            // read the book's id.
            scanf("%d", &bookToUpdate->id);

            // if the book with the id that the user has provided does not exist, break.
            if (bookExists(*bookToUpdate, bList)) {
                printf("There is no book with the id that you have provided!");
                break;
            }

            // find the book that the user wants to update.
            *bookToUpdate = findBook(*bookToUpdate, bList);

            // ask for the new book's information.
            printf("Would you like to update the book's author?\n");
            if (yesOrNo()) {
                printf("Please give a new Author name: ");
                scanf("%s", bookToUpdate->author);
            }

            printf("Would you like to update the book's title?\n");
            if (yesOrNo()) {
                printf("Please give a new title for the book: ");
                scanf("%s", bookToUpdate->title);
            }

            printf("Would you like to update the book's genre?\n");
            if (yesOrNo()) {
                bookToUpdate->genre = readGenre();
            }

            printf("Would you like to update the book's reviews?\n");
            if (yesOrNo()) {
                printf("Please give a new genre for the book: ");
                bookToUpdate->reviews = readReviews();
            }

            // update the book from the list.
            if (updateBook(*bookToUpdate, bList))
                printf("Something went wrong while trying to update the book! Please try again.\n");
            else
                // save changes to the file.
                save(filename, bList);

            // free the memory for the book.
            free(bookToUpdate);
        case 5:
            printf("Please provide the id of the book that you want to print: ");

            // allocate memory for the book.
            book *bookToPrint = (book *) malloc(sizeof(book));

            // read the book's id.
            scanf("%d", &bookToPrint->id);

            // if the book with the id that the user has provided does not exist, break.
            if (bookExists(*bookToPrint, bList)) {
                printf("There is no book with the id that you have provided!");
                break;
            }

            // get the book with the id that the user has provided.
            *bookToPrint = findBook(*bookToPrint, bList);

            // print the book.
            print(*bookToPrint);

            // free the memory for the book.
            free(bookToPrint);
        case 6:
            printMenu();
        case 7:
            printf("------- Thank you for using HUA Library! -------\n\n");
            printf("------------------------------------------------");
            return;
    }

    executeCommands(filename, bList);
}

void startLibraryApp(char *filename) {
    // create a book list. It will be empty if the filename is empty or does not exist.
    list bList = load(filename);

    printf("------------------------------------------------");
    printf("------------ Welcome To HUA Library ------------\n\n");
    executeCommands(filename, bList);
}

int main(int argc, char *argv[]) {
    if (argc == 2)
        startLibraryApp(argv[1]);
    else if (argc > 2)
        printf("Too many arguments supplied.\n");
    else
        printf("Please provide the filename as an argument.\n");

    return 0;
}
