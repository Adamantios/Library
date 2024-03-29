#ifndef LIBRARY_BOOKS_H
#define LIBRARY_BOOKS_H

#define MAXSTRING 100
#define MAXREVIEWS 5
#define INITIAL_ID_VALUE 1

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
} bookList;

typedef bookList *list;

node **bListHead;

int loadingFileFlag;

list create_list();

const char *getGenreString(genres genre);

void printReviews(char reviews[MAXREVIEWS][MAXSTRING]);

void printMenu();

void print(book b);

genres intToGenre(int genre);

list load(char *filename);

void save(char *filename, list bList);

int findUniqueId(int desiredId);

int addBook(book b, list bList);

book findBook(book b, list bList);

int deleteBook(book b, list bList);

int updateBook(book b, list bList);

int bookExists(book b, list bList);

void freeBookList();

#endif //LIBRARY_BOOKS_H
