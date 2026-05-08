#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "constant.h"

#include "util.h"
#include "file.h"
#include "game.h"

void print_debug_info(struct game *game) {
	printf("\n");
	printf("Player name: %s\n", game->player.name);
	printf("Introductory text: %s", game->introductory_text);
	printf("\n");
	printf("[ROOMS]\n");
	printf("\n");

	for (size_t i = 0; i < MAX_ROOMS; ++i) {
		if (game->rooms[i].room_number == 0) {
			break;
		}

		printf("Room number: %zu\n", game->rooms[i].room_number);
		printf("Room message: %s\n", game->rooms[i].message);
		printf("North connection: %zu\n",
		       game->rooms[i].connections[NORTH]);
		printf("East connection: %zu\n",
		       game->rooms[i].connections[EAST]);
		printf("South connection: %zu\n",
		       game->rooms[i].connections[SOUTH]);
		printf("West connection: %zu\n",
		       game->rooms[i].connections[WEST]);
		printf("\n");
		for (size_t j = 0; j < MAX_CHALLENGES_PER_ROOM; j++) {
			printf("Challenge %zu: %u\n", 
			       j + 1, game->rooms[i].challenges[j]);
		}
		printf("\n");
	}
}

struct game game = {0};

int main(void) {
	load_game_from_config_file(&game);
	
	print_help_text();
	printf("Type 'help' to bring up these instructions (after giving your name).\n\n");

	char user_input[MAX_RESPONSE_LENGTH] = {'\0'};

	while (user_input[0] == '\0') {
		printf("What is your name? ");
		util_wait_for_user_input(user_input);
		util_sanitise_input(user_input);
		user_input[0] = toupper(user_input[0]);
	}

	snprintf(game.player.name, MAX_RESPONSE_LENGTH, "%s", user_input);

	game.player.room = game.rooms[0];

	printf("\n%s\n\n", game.introductory_text);
	
	while (1) {
		printf("What would you like to do? ");
		util_wait_for_user_input(user_input);
		util_sanitise_input(user_input);
		play(&game, user_input);
		//print_debug_info(&game);
	}

	return EXIT_SUCCESS;
}
