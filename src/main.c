#include <stdint.h>
#include <stdio.h>

#include "defines.h"
#include "structs.h"
#include "externs.h"
#include "file_logic.h"
#include "game_logic.h"

Room rooms[MAX_ROOMS] = {0};
char response[MAX_RESPONSE_LENGTH] = {0};

int main() {
  load();
  helpText();
  while (1) {
    printf("What would you like to do? ");
    ask();
    gameLogic();
    save();
  }
  return 0;
}