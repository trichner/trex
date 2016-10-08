#include <stdlib.h>
#include <stdio.h>
#include <regex.h>
#include <string.h>

#include "lr.h"
#include "common.h"
#include "matcher.h"


regex_t* regex_make(const char* regex, int cflags){
	regex_t* matcher = (regex_t*) xmalloc(sizeof(regex_t));

	/* Compile regular expression */
	int err = regcomp(matcher, regex, cflags);
	if (err) {
		panic("Could not compile regex");
	}
	return matcher;
}

typedef struct {
	char* start;
	int len;
} match_t;

typedef struct {
	size_t mcap;
	match_t* matches;
	char* line;

	regex_t* regex;
	regmatch_t* groups;
} matcher_t;

void matcher_make(matcher_t* self, char* pattern, int cflags){
	self->regex = regex_make(pattern, REG_EXTENDED | cflags);

	size_t nsub = self->regex->re_nsub;
	self->groups = (regmatch_t*) xmalloc((nsub + 1) * sizeof(regmatch_t));
	self->mcap = nsub;

	self->matches = (match_t*) xmalloc(sizeof(match_t) * (self->mcap));
}

void matcher_match_reset(matcher_t* self){
	free(self->line);
	int i;
	for(i=0;i<self->mcap;i++){
		self->matches[i].start = NULL;
		self->matches[i].len = 0;
	}
}

/* free allocated internal structure */
void matcher_free(matcher_t* self){
	free(self->groups);

	/* Free memory allocated to the pattern buffer by regcomp() */
	regfree(self->regex);
	free(self->regex);

	matcher_match_reset(self);
	free(self->matches);
}

void matcher_match_line(matcher_t* self, const char* slice,const int len, int eflags){

	/* copy line and add terminator */
	self->line = (char*) xmalloc(len + 1);
	memcpy(self->line, slice, len);

	char* start = self->line;

	/* Execute regular expression */
	int err = regexec(self->regex, start, self->mcap + 1, self->groups, eflags);
	while(err == 0){
		/* store matched groups */
		int i;
		for(i = 1;i <= self->mcap;i++){
			regoff_t so = self->groups[i].rm_so;
			regoff_t eo = self->groups[i].rm_eo;
			if(so < 0 || eo < 0){
				continue;
			}
			self->matches[i-1].start = &start[so];
			self->matches[i-1].len = eo - so;
		}

		/* look for next match */
		start += self->groups[0].rm_eo;

		/* search next match on same line */
		//err = regexec(regex, start, groupsc, groups, eflags);
		err = REG_NOMATCH;
	}

	/* check for error */
	if (err != REG_NOMATCH) {
		char msgbuf[100];
		regerror(err, self->regex, msgbuf, sizeof(msgbuf));
		panic(msgbuf);
	}
}

int main(int argc, char** argv){

	/* allocate memory for capture groups */
	matcher_t* matcher = (matcher_t*) xmalloc(sizeof(matcher_t));
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
		int num_matches = 0;
		int i;
		for(i=0;i<matcher->mcap;i++){
			match_t match = matcher->matches[i];
			if(!match.start){
				continue;
			}
			if(num_matches){
				printf(" ");
			}
			printf("%.*s", match.len, match.start);
			num_matches++;
		}
		if(num_matches){
			printf("\n");
		}

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
