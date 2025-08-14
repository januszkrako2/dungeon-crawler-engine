#ifndef FILE_LOGIC_H
#define FILE_LOGIC_H

void initialise(FILE* saveFile);
void extractData(FILE* saveFile);
void load();
void saveHistory(FILE* saveFile);
void saveGameState(FILE* saveFile);
void save();

#endif
