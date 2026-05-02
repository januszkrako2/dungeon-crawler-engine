#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#include "constant.h"
#include "struct.h"
#include "mutable.h"

#include "utility.h"

void helpText(void) {
	const char* helpText =
	"Type compass directions to move.\n"
	"Type 'attack' to attack.\n"
	"Type numbers to solve puzzles.\n";

	printf("%s", helpText);
}

void interpretInput(void) {
	size_t read = 0;
	size_t write = 0;
	while (game.response[read] != '\0') {
		if (isspace(game.response[read])) {
			read++;
			continue;
		}

		if (game.response[read] >= 'A' && game.response[read] <= 'Z') game.response[read] += 32;

		game.response[write] = game.response[read];
		write++;
		read++;
	}
	game.response[write] = '\0';

	if (strncmp(game.response, "go", 2) == 0) trimStart(game.response, 2);
	else if (strncmp(game.response, "now", 3) == 0) trimStart(game.response, 3);
	else if (strncmp(game.response, "solve", 5) == 0) trimStart(game.response, 5);
}

void physicalChallenge(void) {
	struct physical_challenge delinquent;
	delinquent.health = 2;

	printf("A delinquent appears! They look at you menacingly.\n");

	while (delinquent.health > 0) {
		printf("How do you respond? ");
		ask();

		interpretInput();
		if (strncmp(game.response, "attack", 6) != 0) continue;
		
		delinquent.health--;
		if (delinquent.health > 0) printf("\nThe delinquent takes a hit.\n");
		else printf("\nThe delinquent falls and dies.\n");
	}
}

void puzzleChallenge(void) {
	srand(time(NULL));

	struct puzzle_challenge puzzle;
	puzzle.first = rand() % 100 + 1;
	puzzle.second = rand() % 100 + 1;
	size_t answer = puzzle.first * puzzle.second;

	printf("There is a note on the floor. You pick it up.\n");
	printf("It says, '%zu x %zu'.\n", puzzle.first, puzzle.second);

	while (stringToSizeT(game.response) != answer) {
		printf("What could it possibly mean? ");
		ask();
		interpretInput();
	}

	printf("\nYou write '%s' on the note. Nice.\n", game.response);
}

void clearChallenge(void) {
	size_t i;
	for (i = 0; i < MAX_ROOMS; i++) {
		if (game.player.currentRoom.roomNumber != game.rooms[i].roomNumber) continue;
		for (size_t j = 0; j < MAX_CHALLENGES_PER_ROOM; j++) {
			if (game.rooms[i].challenge[j] != NONE) {
				game.rooms[i].challenge[j] = NONE;
				game.player.currentRoom = game.rooms[i];
				break;
			}
		}
		break;
	}
	if (i == MAX_ROOMS) {
		printf("Cannot clear challenge from a room.\n");
		leave();
	}
}

void challengeLogic(void) {
	for (size_t i = 0; i < MAX_CHALLENGES_PER_ROOM; i++) {
		switch (game.player.currentRoom.challenge[i]) {
		case NONE:
			break;
		case PHYSICAL:
			physicalChallenge();
			clearChallenge();
			break;
		case PUZZLE:
			puzzleChallenge();
			clearChallenge();
			break;
		}
	}
}

void moveLogic(size_t nextRoom) {
	if (nextRoom == 0) {
		printf("\nYou hit a wall. Ouch!\n");
		return;
	}

	size_t i;
	for (i = 0; i < MAX_ROOMS; i++) {
		if (game.rooms[i].roomNumber == nextRoom) {
			game.player.currentRoom = game.rooms[i];
			break;
		}
	}
	if (i == MAX_ROOMS) {
		printf("Couldn't find room.\n");
		leave();
	}

	printf("\n%s", game.player.currentRoom.message);
}

void gameLogic(void) {
	interpretInput();

	size_t nextRoom = 0;
	bool moved = false;
	if (strncmp(game.response, "help", 4) == 0) {
		printf("\n");
		helpText();
		return;
	} else if (strncmp(game.response, "north", 5) == 0) {
		moved = true;
		nextRoom = game.player.currentRoom.connections[NORTH];
	} else if (strncmp(game.response, "east", 4) == 0) {
		moved = true;
		nextRoom = game.player.currentRoom.connections[EAST];
	} else if (strncmp(game.response, "south", 5) == 0) {
		moved = true;
		nextRoom = game.player.currentRoom.connections[SOUTH];
	} else if (strncmp(game.response, "west", 4) == 0) {
		moved = true;
		nextRoom = game.player.currentRoom.connections[WEST];
	}
	if (moved) moveLogic(nextRoom);

	if (game.player.currentRoom.roomNumber == 1) {
		printf("Congratulations, %s!\n", game.player.name);
		leave();
	}

	challengeLogic();
}
