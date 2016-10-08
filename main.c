#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lr.h"
#include "common.h"
#include "matcher.h"


int main(int argc, char** argv){

	/* allocate memory for capture groups */
	matcher_t* matcher = matcher_new();
	matcher_make(matcher, argv[1], 0);

	line_reader_t *lr = lr_new();
	FILE *f;
	size_t len;
	char *line;
	if(argc >= 3){
		f = fopen(argv[2], "r");
		if (f == NULL) {
			panic("Cannot open file.");
		}
	}else{
		f = stdin;
	}

	/* read file line-by-line */
	lr_init(lr, f);
	while (line = lr_next(lr, &len)) {

		/* exec regex */
		matcher_match_line(matcher, line, len, 0);

		/* print matches */
		int nmatches = 0;
		match_t* match;

		int i = 0;
		while(match = matcher_match_get(matcher, i)){
			if(match->start){
				if(nmatches){
					printf(" ");
				}
				printf("%.*s", match->len, match->start);
				nmatches++;
			}
			i++;
		}
		if(nmatches){
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

	matcher_free(matcher);
	free(matcher);

	return 0;
}
