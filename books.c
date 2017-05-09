#include <stdio.h>
#include "books.h"

void save(char *filename, list bList) {
    FILE *file = fopen(filename, "a");

    if (file != NULL) {
        fwrite(&bList, sizeof(book), 1, file);
        fclose(file);
    }
}

list load(char *filename, list bList) {
    FILE *file = fopen(filename, "r");

    if (file != NULL) {
        fread(&bList, sizeof(book), 1, file);
        fclose(file);
    }

    return bList;
}
