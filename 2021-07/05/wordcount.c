#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define WC_INITIAL_SIZE 32

typedef struct String {
	char* s;
	size_t len;
	size_t size;
} String;

bool string_init(String* s, char* str) {
	s->len = 0;
	while (str[s->len]) {
		++s->len;
	}
	s->size = 1;

	while (s->size <= s->len) {
		s->size <<= 1;
	}

	s->s = malloc(s->size);

	if (!s->s) {
		return false;
	}

	for (size_t i = 0; i < s->len + 1; ++i) {
		s->s[i] = str[i];
	}

	return true;
}

bool string_equal_cstr(const String* s, const char* cstr) {
	for (size_t i = 0; i < s->len; ++i) {
		if (s->s[i] != cstr[i]) {
			return false;
		}
	}

	if (cstr[s->len] != '\0') {
		return false;
	}

	return true;
}

typedef struct WordCounts {
	String* words;
	size_t* counts;
	size_t len;
	size_t size;
} WordCounts;

bool wc_addWord(WordCounts* wc, char* word) {
	if (wc->len == wc->size) {
		wc->words = realloc(wc->words, 2 * wc->size * sizeof(String));
		wc->counts = realloc(wc->counts, 2 * wc->size * sizeof(size_t));
		wc->size = 2 * wc->size;
		if (wc->words == NULL || wc->counts == NULL) {
			return false;
		}
	}

	string_init(&wc->words[wc->len], word);
	wc->counts[wc->len] = 1;
	wc->len++;

	return true;
}

int nextWord(char* str, char* buf, int index) {
	int i = 0;

	while (!isspace(str[index + i]) && str[index + i] != '\0') {
		buf[i] = str[index + i];
		++i;
	}

	buf[i] = '\0';

	if (str[index + i] == '\0') {
		return -1;
	}

	while(isspace(str[index + i])) {
		++i;
	}

	return index + i;
}

void countWords(char* str, WordCounts* wc) {
	char buf[256];
	int index = 0;
	while(true) {
		index = nextWord(str, buf, index);
		bool found = false;
		for (size_t i = 0; i < wc->len; ++i) {
			if (string_equal_cstr(&wc->words[i], buf)) {
				++wc->counts[i];
				found = true;
				break;
			}
		}
		if (!found) {
			wc_addWord(wc, buf);
		}
		if (index < 0) {
			break;
		}
	}
}

int main() {
	size_t n = 8192;
	char buf[n];

	WordCounts wc = {
		.words = malloc(WC_INITIAL_SIZE * sizeof(String)),
		.counts = malloc(WC_INITIAL_SIZE * sizeof(size_t)),
		.len = 0,
		.size = WC_INITIAL_SIZE
	};

	printf("Enter a phrase: ");
	fgets(buf, n, stdin);
	size_t len = strlen(buf);
	buf[len - 1] = '\0';
	--len;

	countWords(buf, &wc);

	printf("\n");
	for (int i = 0; i < wc.len; ++i) {
		printf("%s:\t%ld\n", wc.words[i].s, wc.counts[i]);
	}
	printf("\n");

	free(wc.words);
	free(wc.counts);

	return 0;
}





