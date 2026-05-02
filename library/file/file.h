#ifndef FILE_H
#define FILE_H

#include <stdbool.h>

void initialiseRoomFile(FILE* roomFile);
void validateLine(FileInfo* info);
void errorCheck(FileInfo* info);
void extractRoomNumber(FileInfo* info);
void extractRoomMessage(FileInfo* info);
void addRoomConnection(Connection connection, FileInfo* info, Direction direction);
void extractRoomConnections(FileInfo* info);
void addRoomChallenges(FileInfo* info, size_t* challengeCounter);
void extractRoomChallenges(FileInfo* info);
void introductoryTextCheck(FileInfo info);
void extractIntroductoryText(FileInfo* info);
void updateLine(FileInfo* info);
void extract(FILE* roomFile);
void load(void);

#endif
