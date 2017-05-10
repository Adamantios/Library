#include <stdio.h>
#include <stdlib.h>
#include "books.h"

list create_list() {
    list list = malloc(sizeof(list));
    list->head = NULL;
    list->size = 0;

    uniqueId = 0;
    bListHead = list->head;

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

    for (int i = 0; i < MAXREVIEWS; ++i) {
        printf("%i: %s\n", i, reviews[i]);
    }
}

void printMenu() {
    node *current = bListHead;

    while (current != NULL) {
        print(current->book);
        current = current->next;
    }
}

void print(book b) {
    printf("Author: %s\nTitle: %s\nGenre: %s\n", b.author, b.title, getGenreString(b.genre));
    printReviews(b.reviews);
}

list load(char *filename) {
    FILE *file = fopen(filename, "rb");
    list bList = create_list();
    book *newBook = (book *) malloc(sizeof(book));

    while (!feof(file)) {
        fread(newBook, sizeof(book), 1, file);
        addBook(*newBook, bList);
    }

    fclose(file);
    return bList;
}

void save(char *filename, list bList) {
    FILE *file = fopen(filename, "ab");

    if (file != NULL) {
        for (int i = 0; i < bList->size; ++i)
            fwrite(&bList[i], sizeof(book), 1, file);

        fwrite(&bList, sizeof(book), 1, file);
        fclose(file);
    }
}

int addBook(book b, list bList) {
    // assign a unique id to the book.
    b.id = uniqueId++;

    // allocate memory for the new book.
    node *newBook = (node *) malloc(sizeof(node));

    // in case of failure print an error message and finish program with exit code -1.
    if (newBook == NULL) {
        fprintf(stderr, "Unable to allocate memory for a new book.\n");
        exit(-1);
    }

    // create the new book.
    newBook->book = b;
    newBook->next = bList->head;
    bList->head = newBook;
    bList->size++;

    return 0;
}

book findBook(book b, list bList) {
    node *currentBook = bList->head;

    while (currentBook != NULL && currentBook->book.id != b.id)
        currentBook = currentBook->next;

    if (currentBook != NULL)
        return currentBook->book;
    else
        return b;
}

int deleteBook(book b, list bList) {
    node *previousBook = bList->head;
    node *currentBook = bList->head;

    while (currentBook != NULL && currentBook->book.id != b.id) {
        previousBook = currentBook;
        currentBook = currentBook->next;
    }

    if (currentBook != NULL) {
        previousBook->next = currentBook->next;
        free(currentBook);
        return 0;
    }

    return 1;
}

int updateBook(book b, list bList) {
    return 0;
}
