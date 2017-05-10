#ifndef LIBRARY_BOOKS_H
#define LIBRARY_BOOKS_H

#define MAXSTRING 50
#define MAXREVIEWS 5

typedef enum {
    FICTION, SCIENTIFIC, POLITICS
} genres;

typedef struct book {
    char author[MAXSTRING];
    char title[MAXSTRING];
    genres genre;
    int id;
    char reviews[MAXREVIEWS][MAXSTRING];
} book;

typedef struct node {
    struct book book;
    struct node *next;
} node;

typedef struct list {
    node *head;
    int size;
} *list;

int uniqueId;
node **bListHead;

list create_list();

const char *getGenreString(genres genre);

void printReviews(char reviews[MAXREVIEWS][MAXSTRING]);

void printMenu();

void print(book b);

list load(char *filename);

void save(char *filename, list bList);

int addBook(book b, list bList);

book findBook(book b, list bList);

int deleteBook(book b, list bList);

int updateBook(book b, list bList);

#endif //LIBRARY_BOOKS_H
