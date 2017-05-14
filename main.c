#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "books.h"

// TODO add exit to all mallocs if not successful.
// TODO correct update.

void showMenu() {
    printf("\nAvailable commands:\n");
    printf("1: Create a new book.\n");
    printf("2: Delete a book.\n");
    printf("3: Update a book.\n");
    printf("4: Print a book's information.\n");
    printf("5: Print the book menu.\n");
    printf("6: Exit.\n\n");
    printf("Please insert a number in order to run a command: ");
}

char *readUserInput() {
    char *input = malloc(sizeof(char) * MAXSTRING);
    int c;
    int input_length = 0;

    // loop until getchar() returns eof or user presses enter
    // check that we don't exceed the MAXSTRING - 1 to make room for the null terminator
    while ((c = getchar()) != '\n' && c != EOF && input_length < MAXSTRING - 1)
        input[input_length++] = (char) c;

    // terminate the array, so it can be used as a string
    input[input_length] = '\0';

    return input;
}

int yesOrNo() {
    printf("Press Y for yes or N for no: ");
    int choice;
    while ((choice = getchar()) != '\n' && choice != EOF && choice != 'N' && choice != 'Y')
        printf("Unknown command! Please press Y for yes and N for no: ");

    return choice == 'Y' ? 1 : 0;
}

genres readGenre() {
    printf("Available Genres:\n");
    printf("1: Fiction\n");
    printf("2: Scientific\n");
    printf("3: Politics\n");
    printf("Please choose one of the available genres for the book, by inserting it's number: ");

    int genre;
    genre = atoi(readUserInput());

    while (genre < 1 || genre > 3) {
        printf("Unknown genre!\nPlease try inserting one of the available genres: ");
        genre = atoi(readUserInput());
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

void executeCommands(char *filename, list bList) {
    showMenu();

    // read the user's command, until it is valid.
    int command;
    command = atoi(readUserInput());

    while (command < 1 || command > 7) {
        printf("Unknown command!\nPlease try inserting one of the available numbers: ");
        command = atoi(readUserInput());
    }

    // declare a book for the commands.
    book *book;

    // execute the user's command.
    switch (command) {
        case 1:
            // allocate memory for the book.
            book = malloc(sizeof(book));

            // ask for the new book's information.
            printf("Please give an Author name: ");
            strcpy(book->author, readUserInput());

            printf("Please give a new title for the book: ");
            strcpy(book->title, readUserInput());

            book->genre = readGenre();

            int reviewsWritten = 0;

            while (reviewsWritten < MAXREVIEWS) {
                printf("Please write a review:\n    - ");
                strcpy(book->reviews[reviewsWritten], readUserInput());
                ++reviewsWritten;
                printf("Would you like to write another review?");

                if (!yesOrNo())
                    break;
            }

            // add the book to the list.
            if (addBook(*book, bList))
                printf("Something went wrong while trying to create the book! Please try again.\n");
            else
                // save changes to the file.
                save(filename, bList);

            // free the memory for the book.
            free(book);
            break;
        case 2:
            printf("Please provide the id of the book that you want to delete: ");

            // allocate memory for the book.
            book = malloc(sizeof(book));

            // read the book's id.
            book->id = atoi(readUserInput());

            // if the book with the id that the user has provided does not exist, break.
            if (bookExists(*book, bList)) {
                printf("There is no book with the id that you have provided!\n");
                break;
            }

            // delete the book from the list.
            if (deleteBook(*book, bList))
                printf("Something went wrong while trying to update the book! Please try again.\n");
            else
                // save changes to the file.
                save(filename, bList);

            // free the memory for the book.
            free(book);
            break;
        case 3:
            printf("Please provide the id of the book that you want to update: ");

            // allocate memory for the book.
            book = malloc(sizeof(book));

            // read the book's id.
            book->id = atoi(readUserInput());

            // if the book with the id that the user has provided does not exist, break.
            if (bookExists(*book, bList)) {
                printf("There is no book with the id that you have provided!\n");
                break;
            }

            // find the book that the user wants to update.
            *book = findBook(*book, bList);

            // ask for the new book's information.
            printf("Would you like to update the book's author?\n");
            if (yesOrNo()) {
                printf("Please give a new Author name: ");
                strcpy(book->author, readUserInput());
            }

            printf("Would you like to update the book's title?\n");
            if (yesOrNo()) {
                printf("Please give a new title for the book: ");
                strcpy(book->title, readUserInput());
            }

            printf("Would you like to update the book's genre?\n");
            if (yesOrNo())
                book->genre = readGenre();

            printf("Would you like to update the book's reviews?\n");
            if (yesOrNo()) {
                reviewsWritten = 0;

                while (reviewsWritten < MAXREVIEWS) {
                    printf("Please write a review:\n    - ");
                    strcpy(book->reviews[reviewsWritten], readUserInput());
                    ++reviewsWritten;
                    printf("Would you like to write another review?");

                    if (!yesOrNo())
                        break;
                }
            }

            // update the book from the list.
            if (updateBook(*book, bList))
                printf("Something went wrong while trying to update the book! Please try again.\n");
            else
                // save changes to the file.
                save(filename, bList);

            // free the memory for the book.
            free(book);
            break;
        case 4:
            printf("Please provide the id of the book that you want to print: ");

            // allocate memory for the book.
            book = malloc(sizeof(book));

            // read the book's id.
            book->id = atoi(readUserInput());

            // if the book with the id that the user has provided does not exist, break.
            if (bookExists(*book, bList)) {
                printf("There is no book with the id that you have provided!\n");
                break;
            }

            // get the book with the id that the user has provided.
            *book = findBook(*book, bList);

            // print the book.
            print(*book);

            // free the memory for the book.
            free(book);
            break;
        case 5:
            printMenu();
            break;
        case 6:
            printf("\n------- Thank you for using HUA Library! -------\n\n");
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

    printf("------------------------------------------------\n\n");
    printf("------------ Welcome To HUA Library ------------\n");
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
