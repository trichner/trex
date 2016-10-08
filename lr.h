#include <stdlib.h>
#include <stdio.h>

typedef struct line_reader_t line_reader_t;

line_reader_t* lr_new();
void lr_init(line_reader_t *lr, FILE *f);
char* lr_next(line_reader_t *lr, size_t *len);
void lr_free(line_reader_t *lr);
