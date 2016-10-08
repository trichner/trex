
#include <stdlib.h>

/* writes msg to stderr and exits with an error code */
void panic(char* msg);

/* allocates zeroed out memory and panics on error */
void* xmalloc(size_t size);
