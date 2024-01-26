// selfDefStruct.h
// Include this header file to use the struct UNO and ListOfCards

#ifndef UNO_H
#define UNO_H

#include <vector>
using namespace std;

// Defining new type of variable "UNO"
// For example,
// ( UNO.col == 'n' && UNO.num == 'D' ) is Draw 4
// ( UNO.col == 'b' && UNO.num == '7' ) is Blue 7
struct UNO {
    char col;   // Colour of UNO card ( 'b' , 'g' , 'r' , 'y' , 'n' )
    char num;   // Number of UNO card ( '0'-'9', 'D'(Draw), 'R'(Reverse), 'S'(Skip) )
};

// Define a structure to store all the cards of a player
struct ListOfCards {
    vector<UNO> card;
};

// Stores the latest played card as "currentCard"
struct playedUNO {
    UNO card;
    char colourToChange;    // Unless the latest card is "Wild" or "nD (Draw 4)", this should be set to 'n' (N/A)
};

#endif
