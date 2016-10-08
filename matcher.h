

typedef struct {
	char* start;
	int len;
} match_t;

typedef struct matcher_t matcher_t;

/* allocate a new matcher */
matcher_t* matcher_new();

/* setup matcher internal structure */
void matcher_make(matcher_t* self, char* pattern, int cflags);

/* reset current matc */
void matcher_match_reset(matcher_t* self);

/* free allocated internal structure */
void matcher_free(matcher_t* self);

/* match a single line */
void matcher_match_line(matcher_t* self, const char* slice,const int len, int eflags);

/* returns the match at index idx or null if out of bounds */
match_t* matcher_match_get(matcher_t* self, size_t idx);
