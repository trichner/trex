
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

void panic(char *msg) {
  fprintf(stderr, "%s\n", msg);
  exit(17);
}

void *xmalloc(size_t size) {
  void *ptr = calloc(1, size);
  if (!ptr) {
    panic("Cannot allocate memory");
  }
  return ptr;
}
