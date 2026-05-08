#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "constant.h"

void util_sanitise_input(char *user_input) {
	size_t read = 0;
	size_t write = 0;
	while (user_input[read] != '\0') {
		if (isspace(user_input[read])) {
			++read;
			continue;
		}

		if (user_input[read] >= 'A' && 
		    user_input[read] <= 'Z') {
			user_input[read] += 32;
		}

		user_input[write] = user_input[read];
		++write;
		++read;
	}
	user_input[write] = '\0';
}

void util_leave(void) {
	char user_input[MAX_RESPONSE_LENGTH] = {'\0'};

	while (strncmp(user_input, "\n", 1) != 0) {
		printf("Press enter to leave.\n");

		if (fgets(user_input, MAX_RESPONSE_LENGTH, stdin) == NULL) {
			exit(EXIT_FAILURE);
		}

		char *newline_position = strchr(user_input, '\n');
		if (newline_position == NULL) {
			while(getchar() != '\n');
		}
	}

	exit(EXIT_FAILURE);
}

void util_wait_for_user_input(char *user_input) {
	if (fgets(user_input, MAX_RESPONSE_LENGTH, stdin) == NULL) {
		exit(EXIT_FAILURE);
	}

	char *newline_position = strchr(user_input, '\n');

	if (newline_position == NULL) {
		while (getchar() != '\n');
	} else {
		*newline_position = '\0';
	}
}

void util_trim_start(char *text, size_t characters) {
	size_t i = 0;

	while (text[i + characters] != '\0') {
		text[i] = text[i + characters];
		++i;
	}

	for (size_t j = 0; j < characters; ++j) {
		text[i + j] = '\0';
	}
}

size_t util_string_to_size_t(char *text) {
	size_t value = 0;
	size_t i = 0;

	while (text[i] != '\0') {
		if (text[i] >= '0' && text[i] <= '9') {
			value = (value * 10) + text[i] - '0';
		}
		++i;
	}

	return value;
}
