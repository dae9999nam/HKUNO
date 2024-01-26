// random.cpp

#include <iostream>
#include <cstdlib>  // For calling srand(), rand()
#include "random.h"
#include "selfDefStruct.h"    // For calling struct UNO & ListOfCards
using namespace std;

// This function takes integer as input to initialize the random seed
// It returns a random UNO

UNO randomSingleUNO(int seed) {

    const char allCol[9] = {
        'b', 'g', 'r', 'y', 'n',    // 'b'=blue, 'g'=green, 'r'=red, 'y'=yellow, 'n'=NA/no colour/black
        'b', 'g', 'r', 'y'          // 2 items of blue/green/red/yellow to increase the probability of them
    };

    const char allNumForCol[13] = {     // Set of numbers/actions for coloured UNO cards
        '0','1','2','3','4','5','6','7','8','9',
        'D',    // Draw 2
        'R',    // Reverse
        'S',    // Skip
    };
    
    const char allActForNA[2] = {   // Set of actions for UNO cards with no colour
        'W',    // Wild
        'D'     // Wild Draw 4
    };

    UNO randomCard;     // Define the variable (UNO Card) to be returned
    srand( seed );  // Initialize random seed
    
    randomCard.col = allCol[ rand() % 9 ];  // Generate random colour

    if ( randomCard.col=='b' || randomCard.col=='g' || randomCard.col=='r' || randomCard.col=='y' )
        randomCard.num = allNumForCol[ rand() % 13 ];   // Generate random number/actions
    else
        randomCard.num = allActForNA[ rand() % 2 ];     // Generate random actions for uncoloured cards

    return randomCard;
}