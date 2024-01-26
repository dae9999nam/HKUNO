// display_requestUser.h

#ifndef DISPLAY_REQUESTUSER_H
#define DISPLAY_REQUESTUSER_H

#include "selfDefStruct.h"  // For the calling of self-defined structures (UNO, playedUNO, listOfCards)

playedUNO display_requestUser( ListOfCards user[] , playedUNO currentCard , int numOfPlayer , bool &newOrNot , bool &save );

#endif