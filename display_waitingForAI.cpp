// display_waitingForAI.h

#include <iostream>
#include <string>
#include <unistd.h>     // For the calling of sleep()
#include "selfDefStruct.h"  // For the calling of self-defined structures (UNO, playedUNO, listOfCards)
#include "display_waitingForAI.h"    // Allow other programs to call this function via the header file
using namespace std;

void display_waitingForAI(playedUNO currentCard, int AIIndex, ListOfCards player[], int numOfPlayers) {

    system("clear");

//    // DEBUG USE
//    cout << "DEBUG:" << endl;
//    for ( int i = 0 ; i < numOfPlayers ; i++ ) {
//        cout << i << ": ";
//        for ( int j = 0 ; j < player[i].card.size() ; j++ ) {
//            cout << player[i].card[j].col << player[i].card[j].num << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;

    int *numOfCards = new int[numOfPlayers];
	for ( int i = 0 ; i < numOfPlayers ; i++ ) {
        // Count the number of cards
        numOfCards[i] = player[i].card.size();
    }

    //1 Print the number of AI and which AI is playing on the top 
    cout << "Current player (number of cards left) :" << endl;
    cout << "You(" << numOfCards[0] << ")";
    for ( int i = 2 ; i < numOfPlayers + 1 ; i++ ) {
        if ( (AIIndex + 1) == i )
            cout << " \033[1;32;40m[AI" << i << "(" << numOfCards[i-1] << ")]\033[0m";
        else
            cout << " AI" << i << "(" << numOfCards[i-1] << ")";
    }
    cout << endl << endl;

    //2 Display the latest discard
    cout << "Latest discard :" <<endl;
    if ( currentCard.card.col == 'n' ) {
        if ( currentCard.colourToChange == 'b' )
            cout << "\033[1;40;34m";
        else if ( currentCard.colourToChange == 'g' )
            cout << "\033[1;40;32m";
        else if ( currentCard.colourToChange == 'r' )
            cout << "\033[1;40;31m";
        else if ( currentCard.colourToChange == 'y' )
            cout << "\033[1;40;33m";
    }
    else if ( currentCard.card.col == 'b')
        cout << "\033[1;44;37m";
    else if ( currentCard.card.col == 'g')
        cout << "\033[1;42;30m";
    else if ( currentCard.card.col == 'r')
        cout << "\033[1;41;37m";
    else if ( currentCard.card.col == 'y')
        cout << "\033[1;43;30m";
    cout << "┌───────┐" << endl;
    cout << "│       │" << endl;
    cout << "│";
    if ( currentCard.card.num >= '0' && currentCard.card.num <= '9' )
        cout << "   " << currentCard.card.num << "   ";
    else if ( currentCard.card.col == 'n' && currentCard.card.num == 'D')
        cout << " Draw 4";
    else if ( currentCard.card.num == 'W')
        cout << "  Wild ";
    else if ( currentCard.card.num == 'D')
        cout << " Draw 2";
    else if ( currentCard.card.num == 'R')
        cout << "Reverse";
    else if ( currentCard.card.num == 'S')
        cout << "  Skip ";
    cout << "│" << endl;
    cout << "│       │" << endl;
    cout << "└───────┘" << "\033[0m" << endl << endl;

    //3 Display the instruction and meanings of notations
    cout << "(D = Draw 2 (Draw 4 if it is white/black))" << endl;
    cout << "(W = Wild)" << endl;
    cout << "(R = Reverse)" << endl;
    cout << "(S = Skip)" << endl;

    //4 Print the cards that are held by the player currently (Organized by colours)
    cout << "Your cards :" << endl;
    for ( int i = 0 ; i < player[0].card.size() ; i++ ) {   // Pint blue
        cout << "\033[1;34m";
        if ( player[0].card[i].col == 'b') {
            cout << player[0].card[i].num << " ";
        }
        cout << "\033[0m";
    }
    for ( int i = 0 ; i < player[0].card.size() ; i++ ) {   // Pint green
        cout << "\033[1;32m";
        if ( player[0].card[i].col == 'g') {
            cout << player[0].card[i].num << " ";
        }
        cout << "\033[0m";
    }    
    for ( int i = 0 ; i < player[0].card.size() ; i++ ) {   // Pint red
        cout << "\033[1;31m";
        if ( player[0].card[i].col == 'r') {
            cout << player[0].card[i].num << " ";
        }
        cout << "\033[0m";
    }
    for ( int i = 0 ; i < player[0].card.size() ; i++ ) {   // Pint yellow
        cout << "\033[1;33m";
        if ( player[0].card[i].col == 'y') {
            cout << player[0].card[i].num << " ";
        }
        cout << "\033[0m";
    }
    for ( int i = 0 ; i < player[0].card.size() ; i++ ) {   // Pint no colour
        if ( player[0].card[i].col == 'n') {
            cout << player[0].card[i].num << " ";
        }
    }
    cout << endl;

    sleep(2);

    delete [] numOfCards;

    return;
}
