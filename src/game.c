#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#include "constant.h"

#include "util.h"

struct physical_challenge {
	int health;
};

struct puzzle_challenge {
	int first;
	int second;
};

static void physical_challenge(struct game *game) {
	struct physical_challenge delinquent;
	delinquent.health = 2;

	printf("A delinquent appears! They look at you menacingly.\n");

	char user_input[MAX_RESPONSE_LENGTH] = {'\0'};

	while (delinquent.health > 0) {
		printf("How do you respond? ");

		util_wait_for_user_input(user_input);
		util_sanitise_input(user_input);

		if (strncmp(user_input, "attack", 6) != 0) {
			continue;
		}
		
		delinquent.health--;
		if (delinquent.health > 0) {
			printf("\nThe delinquent takes a hit.\n");
		} else {
			printf("\nThe delinquent falls and dies.\n");
		}
	}
}

static void puzzle_challenge(struct game *game) {
	srand(time(NULL));

	struct puzzle_challenge puzzle;
	puzzle.first = rand() % 100 + 1;
	puzzle.second = rand() % 100 + 1;
	size_t answer = puzzle.first * puzzle.second;

	printf("There is a note on the floor. You pick it up.\n");
	printf("It says, '%d x %d'.\n", puzzle.first, puzzle.second);

	char user_input[MAX_RESPONSE_LENGTH] = {'\0'};

	while (util_string_to_size_t(user_input) != answer) {
		printf("What could it possibly mean? ");
		util_wait_for_user_input(user_input);
		util_sanitise_input(user_input);
	}

	printf("\nYou write '%s' on the note. Nice.\n", user_input);
}

static void clear_challenge(struct game *game) {
	size_t i;
	for (i = 0; i < MAX_ROOMS; ++i) {
		if (game->player.room.room_number !=
		    game->rooms[i].room_number) {
			continue;
		}
		for (size_t j = 0; j < MAX_CHALLENGES_PER_ROOM; ++j) {
			if (game->rooms[i].challenges[j] != NONE) {
				game->rooms[i].challenges[j] = NONE;
				game->player.room.challenges[j] = NONE;
				break;
			}
		}
		break;
	}
	if (i == MAX_ROOMS) {
		printf("Cannot clear challenge from a room.\n");
		util_leave();
	}
}

static void move(struct game *game, enum direction direction) {
	size_t next_room = game->player.room.connections[direction];

	if (next_room == 0) {
		printf("\nYou hit a wall. Ouch!\n");
		return;
	}

	size_t i;
	for (i = 0; i < MAX_ROOMS; ++i) {
		if (game->rooms[i].room_number == next_room) {
			game->player.room = game->rooms[i];
			break;
		}
	}
	if (i == MAX_ROOMS) {
		printf("Couldn't find room.\n");
		util_leave();
	}

	printf("\n%s", game->player.room.message);
}

void print_help_text(void) {
	const char *help_text =
	"Type compass directions to move.\n"
	"Type 'attack' to attack.\n"
	"Type numbers to solve puzzles.\n"
	"Type 'exit', 'leave' or similar to quit.\n";

	printf("%s", help_text);
}

void play(struct game *game, char *user_input) {
	if (strncmp(user_input, "help", 4) == 0) {
		printf("\n");
		print_help_text();
		return;
	} else if (strncmp(user_input, "north", 5) == 0) {
		move(game, NORTH);
	} else if (strncmp(user_input, "east", 4) == 0) {
		move(game, EAST);
	} else if (strncmp(user_input, "south", 5) == 0) {
		move(game, SOUTH);
	} else if (strncmp(user_input, "west", 4) == 0) {
		move(game, WEST);
	} else if (strncmp(user_input, "exit", 4) == 0 ||
	           strncmp(user_input, "leave", 5) == 0 ||
	           strncmp(user_input, "quit", 4) == 0 ||
	           strncmp(user_input, "out", 3) == 0) {
		util_leave();
	}

	if (game->player.room.room_number == 1) {
		printf("Congratulations, %s!\n", game->player.name);
		util_leave();
	}

	for (size_t i = 0; i < MAX_CHALLENGES_PER_ROOM; ++i) {
		switch (game->player.room.challenges[i]) {
		case NONE:
			break;
		case PHYSICAL:
			physical_challenge(game);
			clear_challenge(game);
			break;
		case PUZZLE:
			puzzle_challenge(game);
			clear_challenge(game);
			break;
		}
	}
}
