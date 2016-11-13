/*
 * trex (pronounced t-rex) is a simple command line utility that works
 * similar to 'grep'. The main difference is that it only shows the matching
 * groups of a regular expressions.
 *
 * This allows simple parsing out of values from text with some context.
 *
 * This utility uses the UNIX/POSIX regex.h implementation of pattern matcher,
 * therefore POSIX syntax applies for provided patterns.
 *
 * TODO:
 * - allow input of multiple files
 * - add -i flag for case insensitive matches (eflags)
 * - add -0 flag for \0 separated matches instead of ' '
 *
 * authors:
 * - Thomas Richner <mail@trichner.ch>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "lr.h"
#include "matcher.h"
//#include "ftree_matcher.h"


int main(int argc, char **argv) {

  char** path_list = xmalloc(2*sizeof(char*));
  path_list[0] = "/home/trichner/tdot";

  if (argc <= 1) {
    panic("No pattern provided.\nUsage: trex <pattern> [file]");
  }

  /* allocate memory for capture groups */
  matcher_t *matcher = matcher_new();
  matcher_make(matcher, argv[1], 0);

  if(argc >= 3 && strcmp(argv[2],"-")!= 0){
    match_file(argv[2], matcher);
  }else{
    match_file(NULL, matcher);
  }

  matcher_free(matcher);
  free(matcher);

  return 0;
}

int match_file(const char* path, matcher_t* matcher){

  line_reader_t *lr = lr_new();
  FILE *f;
  size_t len;
  char *line;

  if (path) {
    f = fopen(path, "r");
    if (f == NULL) {
      panic("Cannot open file.");
    }
  } else {
    f = stdin;
  }

  /* read file line-by-line */
  lr_init(lr, f);
  while ((line = lr_next(lr, &len))) {

    /* exec regex */
    matcher_match_line(matcher, line, len, 0);

    /* print matches */
    int nmatches = 0;
    match_t *match;

    int i = 0;
    while ((match = matcher_match_get(matcher, i))) {
      if (match->start) {
        if (nmatches) {
          printf(" ");
        }
        printf("%.*s", match->len, match->start);
        nmatches++;
      }
      i++;
    }
    if (nmatches) {
      printf("\n");
    }

    /* reset, make ready for next matching */
    matcher_match_reset(matcher);
  }
  if (!feof(f)) {
    panic("Input error.");
  }

  /* cleanup */
  lr_free(lr);
  free(lr);

}