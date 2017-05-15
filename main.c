#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "books.h"

// TODO correct update and delete.
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

int readIntSafely() {
    int i;
    int result = scanf("%d", &i);

    // if an error occurred return 0.
    if (result == EOF)
        return 0;

    // clear the buffer.
    while (fgetc(stdin) != '\n') {}

    return i;
}

char *readStringSafely(int limitation) {
    char *input = malloc(sizeof(char) * limitation);

    // in case of failure print an error message and exit with error code 1.
    if (input == NULL) {
        fprintf(stderr, "Unable to allocate memory for your input.\n");
        exit(1);
    }

    int c;
    int input_length = 0;
    int warningFlag = 0;

    // loop until getchar() returns eof or user presses enter.
    while ((c = getchar()) != '\n' && c != EOF) {
        // check that we don't exceed the limitation - 1 to make room for the null terminator.
        if (input_length < limitation - 1)
            input[input_length++] = (char) c;
        else
            warningFlag = 1;
    }

    // terminate the array, so it can be used as a string.
    input[input_length] = '\0';

    if (warningFlag)
        printf("- You have exceeded the maximum string size limitations! (%d letters)\n", limitation);

    return input;
}

char readCharSafely() {
    char input = '\0';
    int c;
    int inputLength = 0;

    // loop until getchar() returns eof or user presses enter.
    while ((c = getchar()) != '\n' && c != EOF) {
        // check that we don't exceed the single character, or else return an empty character.
        if (inputLength < 1) {
            input = (char) c;
            ++inputLength;
        } else
            input = '\0';
    }

    return input;
}

int yesOrNo() {
    printf("Press Y for yes or N for no: ");
    char choice = readCharSafely();

    while (choice != 'Y' && choice != 'N') {
        printf("Unknown command! Please press Y for yes or N for no: ");
        choice = readCharSafely();
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
    genre = readIntSafely();

    while (genre < 1 || genre > 3) {
        printf("Unknown genre!\nPlease try inserting one of the available genres: ");
        genre = readIntSafely();
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

const char *promptReadDiscardEmpty(char *message, int limitation) {
    printf("%s", message);
    const char *result;
    result = readStringSafely(limitation);

    while (result[0] == '\0') {
        printf("%s", message);
        result = readStringSafely(limitation);
    }

    return result;
}

void executeCommands(char *filename, list bList) {
    showMenu();

    // read the user's command, until it is valid.
    int command = readIntSafely();

    while (command < 1 || command > 7) {
        printf("Unknown command!\nPlease try inserting one of the available numbers: ");
        command = readIntSafely();
    }

    // declare a book for the commands.
    book *book;

    // allocate memory for the book.
    book = malloc(sizeof(book));

    // in case of failure print an error message and exit with error code 1.
    if (book == NULL) {
        fprintf(stderr, "Unable to allocate memory for the program.\n");
        exit(1);
    }

    // initialize reviews table
    for (int i = 0; i < MAXREVIEWS; ++i) {
        for (int j = 0; j < MAXSTRING; ++j) {
            book->reviews[i][j] = '\0';
        }
    }

    // execute the user's command.
    switch (command) {
        case 1:
            // ask for the new book's information.
            strcpy(book->author, promptReadDiscardEmpty("Please give an Author name: ", MAXSTRING));
            strcpy(book->title, promptReadDiscardEmpty("Please give a new title for the book: ", MAXSTRING));

            book->genre = readGenre();

            int reviewsWritten = 0;

            while (reviewsWritten < MAXREVIEWS) {
                printf("Please write a review, or press enter to continue:\n    - ");
                strcpy(book->reviews[reviewsWritten++], readStringSafely(MAXSTRING));

                if (reviewsWritten < MAXREVIEWS) {
                    printf("Would you like to write another review?\n");

                    if (!yesOrNo())
                        break;
                }
            }

            // add the book to the list.
            if (addBook(*book, bList))
                printf("Something went wrong while trying to create the book! Please try again.\n");
            else
                // save changes to the file.
                save(filename, bList);

            break;
        case 2:
            printf("Please provide the id of the book that you want to delete: ");

            // read the book's id.
            book->id = readIntSafely();

            // if the book with the id that the user has provided does not exist, break.
            if (bookExists(*book, bList)) {
                printf("There is no book with the id that you have provided!\n");
                break;
            }

            // delete the book from the list.
            if (deleteBook(*book, bList))
                printf("Something went wrong while trying to delete the book! Please try again.\n");
            else {
                // save changes to the file and show success message.
                save(filename, bList);
                printf("The book has been successfully deleted.\n");
            }

            break;
        case 3:
            printf("Please provide the id of the book that you want to update: ");

            // read the book's id.
            book->id = readIntSafely();

            // if the book with the id that the user has provided does not exist, break.
            if (bookExists(*book, bList)) {
                printf("There is no book with the id that you have provided!\n");
                break;
            }

            // find the book that the user wants to update.
            *book = findBook(*book, bList);

            // ask for the new book's information.
            printf("Would you like to update the book's author?\n");
            if (yesOrNo())
                strcpy(book->author, promptReadDiscardEmpty("Please give an Author name: ", MAXSTRING));

            printf("Would you like to update the book's title?\n");
            if (yesOrNo())
                strcpy(book->title, promptReadDiscardEmpty("Please give a new title for the book: ", MAXSTRING));

            printf("Would you like to update the book's genre?\n");
            if (yesOrNo())
                book->genre = readGenre();

            printf("Would you like to update the book's reviews?\n");
            if (yesOrNo()) {
                reviewsWritten = 0;

                while (reviewsWritten < MAXREVIEWS) {
                    printf("Please write a review, or press enter to continue:\n    - ");
                    strcpy(book->reviews[reviewsWritten++], readStringSafely(MAXSTRING));

                    if (reviewsWritten < MAXREVIEWS) {
                        printf("Would you like to write another review?\n");

                        if (!yesOrNo())
                            break;
                    }
                }
            }

            // update the book from the list.
            if (updateBook(*book, bList))
                printf("Something went wrong while trying to update the book! Please try again.\n");
            else {
                // save changes to the file and show success message.
                save(filename, bList);
                printf("The book has been successfully updated.\n");
            }

            break;
        case 4:
            printf("Please provide the id of the book that you want to print: ");

            // read the book's id.
            book->id = readIntSafely();

            // if the book with the id that the user has provided does not exist, break.
            if (bookExists(*book, bList)) {
                printf("There is no book with the id that you have provided!\n");
                break;
            }

            // get the book with the id that the user has provided.
            *book = findBook(*book, bList);

            // print the book.
            print(*book);

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
