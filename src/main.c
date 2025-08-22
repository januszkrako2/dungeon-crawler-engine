#include <stdint.h>
#include <stdio.h>

#include "defines.h"
#include "structs.h"
#include "externs.h"
#include "file_logic.h"
#include "game_logic.h"

Room rooms[MAX_ROOMS] = {0};
char response[MAX_RESPONSE_LENGTH] = {0};
Player player = {0};

int main() {
  load();
  helpText();
  printf("Type 'help' at any time to get reminded of these instructions.\n");
  printf("\n");

  // Ask player for name
  while (player.name[0] == '\0') {
	  printf("What is your name? ");
	  ask();
	  for (size_t i = 0; i < MAX_RESPONSE_LENGTH; i++) {
	  	player.name[i] = response[i];
	  }
  }

  // Main game loop
  while (1) {
    printf("What would you like to do? ");
    ask();
    gameLogic();
    save();
  }

  return 0;
}
