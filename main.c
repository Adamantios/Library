#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "books.h"

void showMenu() {
    printf("Available commands:\n");
    printf("1: Create a new book.\n");
    printf("2: Delete a book.\n");
    printf("3: Update a book.\n");
    printf("4: Print a book's information.\n");
    printf("5: Print the book menu.\n");
    printf("6: Exit.\n");
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
    printf("Available Genres:\n");
    printf("1: Fiction\n");
    printf("2: Scientific\n");
    printf("3: Politics\n");
    printf("Please choose one of the available genres for the book, by inserting it's number: ");

    int genre;
    scanf("%d", &genre);

    while (genre < 1 || genre > 3) {
        printf("Unknown genre!\nPlease try inserting one of the available genres.\n");
        scanf("%d", &genre);
    }

    switch (genre) {
        case 1:
            return FICTION;
        case 2:
            return SCIENTIFIC;
        case 3:
            return POLITICS;
        default:
            return FICTION;
    }
}

char **readReviews() {
    char **reviews;
    reviews = (char **) malloc(sizeof(char *) * MAXREVIEWS);
    reviews[0] = (char *) malloc(sizeof(char) * MAXSTRING * MAXREVIEWS);

    int reviewsWritten = 0;

    while (reviewsWritten < MAXREVIEWS) {
        printf("Please write a review:\n    - ");
        scanf("%s", reviews[reviewsWritten++]);
        printf("Would you like to write another review?");

        if (!yesOrNo())
            break;
    }

    return reviews;
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
            // allocate memory for the book.
            book *bookToCreate = (book *) malloc(sizeof(book));

            // ask for the new book's information.
            printf("Please give an Author name: ");
            scanf("%s", bookToCreate->author);

            printf("Please give a new title for the book: ");
            scanf("%s", bookToCreate->title);

            bookToCreate->genre = readGenre();

            memcpy(bookToCreate->reviews, readReviews(), sizeof(char) * MAXSTRING * MAXREVIEWS);

            // add the book to the list.
            if (addBook(*bookToCreate, bList))
                printf("Something went wrong while trying to create the book! Please try again.\n");
            else
                // save changes to the file.
                save(filename, bList);

            // free the memory for the book.
            free(bookToCreate);
            break;
        case 2:
            printf("Please provide the id of the book that you want to delete: ");

            // allocate memory for the book.
            book *bookToDelete = (book *) malloc(sizeof(book));

            // read the book's id.
            scanf("%d", &bookToDelete->id);

            // if the book with the id that the user has provided does not exist, break.
            if (bookExists(*bookToDelete, bList)) {
                printf("There is no book with the id that you have provided!");
                break;
            }

            // delete the book from the list.
            if (deleteBook(*bookToDelete, bList))
                printf("Something went wrong while trying to update the book! Please try again.\n");
            else
                // save changes to the file.
                save(filename, bList);

            // free the memory for the book.
            free(bookToDelete);
            break;
        case 3:
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
            if (yesOrNo())
                bookToUpdate->genre = readGenre();

            printf("Would you like to update the book's reviews?\n");
            if (yesOrNo())
                memcpy(bookToUpdate->reviews, readReviews(), sizeof(char) * MAXSTRING * MAXREVIEWS);

            // update the book from the list.
            if (updateBook(*bookToUpdate, bList))
                printf("Something went wrong while trying to update the book! Please try again.\n");
            else
                // save changes to the file.
                save(filename, bList);

            // free the memory for the book.
            free(bookToUpdate);
            break;
        case 4:
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
            break;
        case 5:
            printMenu();
            break;
        case 6:
            printf("------- Thank you for using HUA Library! -------\n\n");
            printf("------------------------------------------------");
            return;
        default:
            break;
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
