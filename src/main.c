#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "constants.h"
#include "structs.h"
#include "mutables.h"

#include "utils.h"
#include "file_logic.h"
#include "game_logic.h"

GameState global = {0};

void printDebugInfo(void) {
	printf("\n");
	printf("Player name: %s\n", global.player.name);
	printf("Last response: %s\n", global.response);
	printf("Introductory text: %s", global.introductoryText);
	printf("\n");
	printf("[ROOMS]\n");
	printf("\n");

	for (size_t i = 0; i < MAX_ROOMS; i++) {
		if (global.rooms[i].roomNumber == 0) break;

		printf("Room number: %zu\n", global.rooms[i].roomNumber);
		printf("Room message: %s\n", global.rooms[i].message);
		printf("North connection: %zu\n", global.rooms[i].connections[NORTH]);
		printf("East connection: %zu\n", global.rooms[i].connections[EAST]);
		printf("South connection: %zu\n", global.rooms[i].connections[SOUTH]);
		printf("West connection: %zu\n", global.rooms[i].connections[WEST]);
		printf("\n");

		for (size_t j = 0; j < MAX_CHALLENGES_PER_ROOM; j++)
			printf("Challenge %zu: %u\n", j + 1, global.rooms[i].challenge[j]);

		printf("\n");
	}
}

int main(void) {
	load();
	helpText();
	printf("Type 'help' at any time to bring up these instructions.\n\n");

	while (global.response[0] == '\0') {
		printf("What is your name? ");
		ask();
	}

	strncpy(global.player.name, global.response, MAX_RESPONSE_LENGTH);
	global.player.currentRoom = global.rooms[0];
	printf("\n%s", global.introductoryText);

	while (1) {
		printf("What would you like to do? ");
		ask();
		gameLogic();
		//printDebugInfo();
	}
	return 0;
}
