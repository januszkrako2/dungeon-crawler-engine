#ifndef CONSTANT_H
#define CONSTANT_H

#define MAX_RESPONSE_LENGTH 13
#define MAX_ROOMS 64
#define MAX_ROOM_MESSAGE_LENGTH 200
#define MAX_CHALLENGES_PER_ROOM 8
#define INTRO_TEXT_MAX_LENGTH 80
#define MAX_FILE_LINE_LENGTH 200
#define CONFIG_FILE_NAME "config.txt"

enum challenge {
	NONE,
	PHYSICAL,
	PUZZLE
};

enum direction {
	NORTH,
	EAST,
	SOUTH,
	WEST
};

struct room {
	size_t room_number;
	size_t connections[4]; // North, East, South, West
	enum challenge challenges[MAX_CHALLENGES_PER_ROOM];
	char message[MAX_ROOM_MESSAGE_LENGTH];
};

struct player {
	char name[MAX_RESPONSE_LENGTH];
	struct room room;
};

struct game {
	struct player player;
	struct room rooms[MAX_ROOMS];
	char introductory_text[INTRO_TEXT_MAX_LENGTH];
};

#endif
