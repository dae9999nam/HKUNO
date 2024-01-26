#ifndef CARD_EFFECT_H
#define CARD_EFFECT_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "selfDefStruct.h"
#include "random.h"

void skip(int& counter, bool reverse);
void Draw2(ListOfCards player[], int AIIndex);
//void Wild(playedUNO& currentCard, int size);
void WildDraw(ListOfCards player[], int handsize);

#endif // CARD_EFFECT_H