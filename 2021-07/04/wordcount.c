#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define WC_INITIAL_SIZE 32

typedef struct WordCounts {
	char** words;
	size_t* counts;
	size_t len;
	size_t size;
} WordCounts;

bool wc_addWord(WordCounts* wc, char* word) {
	if (wc->len == wc->size) {
		wc->words = realloc(wc->words, 2 * wc->size * sizeof(char**));
		wc->counts = realloc(wc->counts, 2 * wc->size * sizeof(size_t));
		wc->size = 2 * wc->size;
		if (wc->words == NULL || wc->counts == NULL) {
			return false;
		}
	}

	size_t wordLen = strlen(word);
	wc->words[wc->len] = malloc(wordLen + 1);
	strncpy(wc->words[wc->len], word, wordLen);
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
			if (strcmp(buf, wc->words[i]) == 0) {
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
		.words = malloc(WC_INITIAL_SIZE * sizeof(char**)),
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
		printf("%s:\t%ld\n", wc.words[i], wc.counts[i]);
	}
	printf("\n");

	free(wc.words);
	free(wc.counts);

	return 0;
}





