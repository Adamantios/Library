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
    book book;
    struct node *next;
} node;

typedef struct list {
    node *head;
    int size;
} list;

list create_list();

void printMenu();

void print(book b);

list load(char *filename); //ανάκτηση λίστας βιβλίων από αρχείο

void save(char *filename, list bList); //αποθήκευση λίστας βιβλίων στο αρχείο

int addBook(book b, list bList);

book findBook(book b, list bList); //αναζήτηση με βάση το b->id

int deleteBook(book b, list bList); //διαγραφή με βάση το b->id

int updateBook(book b, list bList); //ανανέωση με βάση το b->id

#endif //LIBRARY_BOOKS_H
