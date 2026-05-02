#ifndef FILE_H
#define FILE_H

#include <stdbool.h>

void initialiseRoomFile(FILE* roomFile);
void validateLine(struct file* info);
void errorCheck(struct file* info);
void extractRoomNumber(struct file* info);
void extractRoomMessage(struct file* info);
void addRoomConnection(struct connection connection, struct file* info, enum direction direction);
void extractRoomConnections(struct file* info);
void addRoomChallenges(struct file* info, size_t* challengeCounter);
void extractRoomChallenges(struct file* info);
void introductoryTextCheck(struct file info);
void extractIntroductoryText(struct file* info);
void updateLine(struct file* info);
void extract(FILE* roomFile);
void load(void);

#endif
