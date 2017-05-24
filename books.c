#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "books.h"

list create_list() {
    bookList *list = malloc(sizeof *list);

    // in case of failure print an error message and exit with error code 1.
    if (list == NULL) {
        fprintf(stderr, "Unable to allocate memory for the book list.\n");
        exit(1);
    }

    list->head = NULL;
    list->size = 0;

    bListHead = &list->head;

    return list;
}

const char *getGenreString(genres genre) {
    switch (genre) {
        case FICTION:
            return "Fiction";
        case SCIENTIFIC:
            return "Scientific";
        case POLITICS:
            return "Politics";
        default:
            return "Not Specified";
    }
}

void printReviews(char reviews[MAXREVIEWS][MAXSTRING]) {
    printf("Reviews: ");
    char *customTab = "         ";
    int i = 0;

    while (i < MAXREVIEWS && strcmp(reviews[i], "")) {
        if (i != 0)
            printf("%s", customTab);

        printf("| %i) %s\n", ++i, reviews[i]);
    }

    if (i == 0)
        printf("     There are no reviews currently for this book.\n");
}

void printMenu() {
    node *current = *bListHead;
    int counter = 0;

    if (current == NULL)
        printf("There are no books currently available!\n");

    while (current != NULL) {
        printf("-------------\nBook number %d\n-------------\n", ++counter);
        print(current->book);
        current = current->next;
    }
}

void print(book b) {
    printf("%-14s%s\n%-14s%s\n%-14s%s\n%-14s%d\n",
           "Author: ", b.author, "Title: ", b.title, "Genre: ", getGenreString(b.genre), "Id: ", b.id);
    printReviews(b.reviews);
}

genres intToGenre(int genre) {
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

list load(char *filename) {
    loadingFileFlag = 1;
    FILE *file = fopen(filename, "rb");
    list bList = create_list();

    if (file != NULL) {
        book *newBook = malloc(sizeof *newBook);

        // in case of failure print an error message and exit with error code 1.
        if (newBook == NULL) {
            fprintf(stderr, "Unable to allocate memory for the books.\n");
            exit(1);
        }

        // read the number of the book records.
        int size;
        fread(&size, sizeof(int), 1, file);

        // loop through all the book records.
        for (int j = 0; j < size; ++j) {
            // read a book record and add it to the book list.
            fread(newBook, sizeof(book), 1, file);
            addBook(*newBook, bList);
        }

        free(newBook);
        fclose(file);
    }

    loadingFileFlag = 0;
    return bList;
}

void save(char *filename, list bList) {
    FILE *file = fopen(filename, "wb");

    if (file != NULL) {
        // set the first book as current.
        node *current = bList->head;

        // write the number of the book records at the beginning of the file.
        fwrite(&bList->size, sizeof(int), 1, file);

        while (current != NULL) {
            // write the current book and move to the next.
            fwrite(&current->book, sizeof(book), 1, file);
            current = current->next;
        }

        fclose(file);
    } else
        printf("An error occurred while trying to save your books at %s!", filename);
}

int findUniqueId(int desiredId) {
    node *current = *bListHead;

    // if the list is empty return the desired id instantly.
    if (current == NULL)
        return desiredId;

    // go to the next node until the list is empty or a book with the desired id value exists.
    while (current != NULL && current->book.id != desiredId)
        current = current->next;

    // if an item with the same id was found,
    // make the desired id the result of the recursion with a parameter of the desired id plus one.
    if (current != NULL)
        desiredId = findUniqueId(++desiredId);

    return desiredId;
}

int addBook(book b, list bList) {
    // assign a unique id to the book,
    // except in the case of adding a book from a file, where the book already has an id.
    if (!loadingFileFlag)
        b.id = findUniqueId(INITIAL_ID_VALUE);

    // allocate memory for the new book.
    node *newBook = malloc(sizeof *newBook);

    // in case of failure print an error message and exit with error code 1.
    if (newBook == NULL) {
        fprintf(stderr, "Unable to allocate memory for a new book.\n");
        exit(1);
    }

    // assign the new book with the book passed and add it to the list.
    newBook->book = b;
    newBook->next = bList->head;
    bList->head = newBook;
    bList->size++;

    return 0;
}

book findBook(book b, list bList) {
    node *currentBook = bList->head;

    // go to the next book node until the list is empty or the book is found.
    while (currentBook != NULL && currentBook->book.id != b.id)
        currentBook = currentBook->next;

    // if the book was found, return it.
    if (currentBook != NULL)
        return currentBook->book;
    else
        return b;
}

int deleteBook(book b, list bList) {
    if (bList->size == 1) {
        if (b.id == bList->head->book.id) {
            node *tmp = bList->head;
            bList->head = bList->head->next;
            free(tmp);
            --bList->size;
            return 0;
        } else
            return 1;
    }

    node *current = bList->head->next;
    node *previous = bList->head;

    while (current != NULL && previous != NULL) {

        if (b.id == current->book.id) {
            node *temp = current;
            previous->next = current->next;
            free(temp);
            --bList->size;
            return 0;
        }

        previous = current;
        current = current->next;
    }

    return 1;
}

int updateBook(book b, list bList) {
    node *currentBook = bList->head;

    // go to the next book node, until the list is empty or the book is found.
    while (currentBook != NULL && currentBook->book.id != b.id)
        currentBook = currentBook->next;

    // if the book was found, update the list.
    if (currentBook != NULL) {
        currentBook->book = b;
        return 0;
    } else
        return 1;
}

int bookExists(book b, list bList) {
    node *currentBook = bList->head;

    // go to the next book node, until the list is empty or the book is found.
    while (currentBook != NULL && currentBook->book.id != b.id)
        currentBook = currentBook->next;

    // if the book was found, return 0.
    if (currentBook != NULL)
        return 0;
    else
        return 1;
}

void freeBookList() {
    node *tmp;
    node *head = *bListHead;

    // while the list is not null, point the current head to a temporary value,
    // and move the head at the next book node, before freeing it.
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }

    free(bListHead);
}
