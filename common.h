#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>

#define debug_printf(fmt, ...) \
        do { if (DEBUG) fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
                                __LINE__, __func__, __VA_ARGS__); } while (0)

/* writes msg to stderr and exits with an error code */
void panic(char* msg);

/* allocates zeroed out memory and panics on error */
void* xmalloc(size_t size);

#endif