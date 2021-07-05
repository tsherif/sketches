#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct String {
	char* s;
	size_t len;
	size_t size;
} String;

String string_create(void) {
	String s = {
		.s = calloc(1, 1),
		.len = 0,
		.size = 1
	};

	if (!s.s) {
		s.size = 0;
	}

	return s;
}

String string_create_substring(String* other, size_t start, size_t end) {
	size_t len = end - start;
	size_t size = 1;

	while (size <= len) {
		size <<= 1;
	}

	String s = {
		.s = malloc(size),
		.len = len,
		.size = size
	};

	if (s.s) {
		for (size_t i = 0; i < s.len; ++i) {
			s.s[i] = other->s[start + i];
		}
		s.s[s.len] = '\0';
	} else {
		s.len = 0;
		s.size = 0;
	}

	return s;
}

bool string_append_cstr(String* s, const char * cstr) {
	size_t len = 0;
	while (cstr[len]) {
		++len;
	}

	while (s->len + len + 1 > s->size) {
		s->size <<= 1;
	}

	s->s = realloc(s->s, s->size);

	if (!s->s) {
		return false;
	}

	for (size_t i = 0; i < len + 1; ++i) {
		s->s[s->len + i] = cstr[i];
	}
	s->len += len;

	return true;
}

bool string_readline(String* s) {
	const size_t CHUNK_SIZE = 8;
	char buf[CHUNK_SIZE];

	bool done = false;
	while (!done) {
		fgets(buf, CHUNK_SIZE, stdin);
		for (size_t i = 0; i < CHUNK_SIZE; ++i) {
			if (buf[i] == '\n') {
				buf[i] = '\0';
				done = true;
				break;
			}
		}

		if (!string_append_cstr(s, buf)) {
			return false;
		}
	}

	return true;
}

void string_destroy(String* s) {
	if (!s->s) {
		return;
	}

	free(s->s);
	s->s = NULL;
	s->len = 0;
	s->size = 0;
}

bool string_equal_substring(const String* s, const String* other, size_t start, size_t end) {
	if (s->len != end - start) {
		return false;
	}

	for (size_t i = 0; i < s->len; ++i) {
		if (s->s[i] != other->s[start + i]) {
			return false;
		}
	}

	return true;
}

typedef struct WordCounts {
	String* words;
	size_t* counts;
	size_t len;
	size_t size;
} WordCounts;

WordCounts wc_create(void) {
	return (WordCounts) {
		.words = malloc(sizeof(String)),
		.counts = malloc(sizeof(size_t)),
		.len = 0,
		.size = 1
	}; 
}

void wc_destroy(WordCounts* wc) {
	if (!wc->words) {
		return;
	}

	for (size_t i = 0; i < wc->len; ++i) {
		string_destroy(&wc->words[i]);
	}

	free(wc->words);
	free(wc->counts);

	wc->words = NULL;
	wc->counts = NULL;
	wc->len = 0;
	wc->size = 0;
}

bool wc_addWord(WordCounts* wc, String word) {
	if (wc->len == wc->size) {
		wc->words = realloc(wc->words, 2 * wc->size * sizeof(String));
		wc->counts = realloc(wc->counts, 2 * wc->size * sizeof(size_t));
		wc->size = 2 * wc->size;
		if (wc->words == NULL || wc->counts == NULL) {
			return false;
		}
	}

	wc->words[wc->len] = word;
	wc->counts[wc->len] = 1;
	wc->len++;

	return true;
}

typedef struct Range {
	size_t start;
	size_t end;
	bool finished;
} Range;

void nextWord(String* s, Range* r) {
	while(isspace(s->s[r->end])) {
		++r->end;
	}

	r->start = r->end;

	while (!isspace(s->s[r->end]) && s->s[r->end] != '\0') {
		++r->end;
	}

	if (s->s[r->end] == '\0') {
		r->finished = true;
	}
}

void countWords(String* s, WordCounts* wc) {
	Range r = { 0 };
	while(true) {
		nextWord(s, &r);
		bool found = false;
		for (size_t i = 0; i < wc->len; ++i) {
			if (string_equal_substring(&wc->words[i], s, r.start, r.end)) {
				++wc->counts[i];
				found = true;
				break;
			}
		}
		if (!found) {
			wc_addWord(wc, string_create_substring(s, r.start, r.end));
		}
		if (r.finished) {
			break;
		}
	}
}

int main() {
	WordCounts wc = wc_create();
	String input = string_create();

	printf("Enter a phrase: ");
	string_readline(&input);

	countWords(&input, &wc);

	printf("\n");
	for (int i = 0; i < wc.len; ++i) {
		printf("%s:\t%ld\n", wc.words[i].s, wc.counts[i]);
	}
	printf("\n");

	wc_destroy(&wc);
	string_destroy(&input);

	return 0;
}





