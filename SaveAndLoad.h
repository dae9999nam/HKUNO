#ifndef SAVE_AND_LOAD_H
#define SAVE_AND_LOAD_H

#include <fstream>
#include "selfDefStruct.h"
using namespace std;

void saveGameProgress(ListOfCards player[], int numOfPlayers, playedUNO currentCard, int counter, int round, bool reverse);
void loadGameProgress(ListOfCards player[], int& numOfPlayers, playedUNO& currentCard, int& counter, int& round, bool &reverse);
void loadGameSize(int &numOfPlayers);

#endif