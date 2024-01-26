// display_requestUser.cpp

#include <iostream>
#include <string>
#include <cstdlib>  // For calling srand(), rand()
#include <ctime>    // For calling time()
#include "selfDefStruct.h"  // For the calling of self-defined structures (UNO, playedUNO, listOfCards)
#include "random.h" // For calling randomSingleUNO()
#include "display_requestUser.h"    // Allow other programs to call this function via the header file
using namespace std;

playedUNO display_requestUser( ListOfCards player[] , playedUNO currentCard , int numOfPlayer , bool &newOrNot , bool &save ) {

    system("clear");

//    // DEBUG USE
//    cout << "DEBUG:" << endl;
//    for ( int i = 0 ; i < numOfPlayer ; i++ ) {
//        cout << i << ": ";
//        for ( int j = 0 ; j < player[i].card.size() ; j++ ) {
//            cout << player[i].card[j].col << player[i].card[j].num << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;

    int *numOfCards = new int[numOfPlayer];
	for ( int i = 0 ; i < numOfPlayer ; i++ ) {
        // Count the number of cards
        numOfCards[i] = player[i].card.size();
    }

    //1 Print the number of AI and their numbers of cards on the top 
    cout << "Current player (number of cards left) :" << endl;
    cout << "\033[1;32;40m[YOU(" << numOfCards[0] << ")]\033[0m";
    for (int i = 2 ; i < (numOfPlayer + 1) ; i++ ) {
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
    cout << endl << endl;

    cout << "Please enter the colour of the card following by the NUMBER/ACTION" << endl;
    cout << "For example: yD (Yellow Draw 2), nW (Wild), nD (Draw 4)" << endl;
    cout << "If you want to draw extra card, enter 'draw'" << endl;
    cout << "If you want to save and exit the game, enter 'wq'" << endl;

    //5 Checking whether the card to be inputed by player is valid
    //    If not, the player will be asked again
    bool valid, cardExist, draw = false;
    string playerInput;
    char col, num, colToChange;     // Parameters of the returning
    int pos = 0;  // Position of card to be played
    while ( !valid ) {
        cout << "Which card would you like to play? ";
        cin >> playerInput;

        if (playerInput == "wq") {
            // Set the flag to indicate that 'wq' has been played
            save = true;
            delete [] numOfCards;
            return currentCard;
        }


        //EXCEPTION: If player hopes to draw a new card, the loop is exited
        if ( playerInput == "draw" ) {
            draw = true;
            break;
        }
        
        col = playerInput.c_str()[0];
        num = playerInput.c_str()[1];

        //5.1 Check whether the card is in the player card list
        cardExist = false;
        for ( int i = 0 ; i < player[0].card.size() ; i++ ) {
            if ( col == player[0].card[i].col && num == player[0].card[i].num ) {
                cardExist = true;
                pos = i;
                break;
            }
        }

        //5.2 If the card is found...
        if ( cardExist ) {
            //5.2.1 If the card is of black colour, ask for the colour to change
            if ( col == 'n' ) {
                bool colourValid = false;
                while ( !colourValid ) {    // Ask the colour to change until player gives a valid input
                    cout << "Which colour would you like to change (b/g/r/y)? ";
                    cin >> playerInput;
                    colToChange = playerInput.c_str()[0];
                    if ( colToChange == 'b' || colToChange == 'g' || colToChange == 'r' || colToChange == 'y' ) {
                        colourValid = true;
                        valid = true;
                    }
                    else
                        cout << "Invalid colour!" << endl;
                }
            }

            //5.2.2 If the card is b/g/r/y, check whether it matches the current discard 
            else {
                if ( col == currentCard.card.col || col == currentCard.colourToChange || num == currentCard.card.num ) {
                    colToChange = 'n';
                    valid = true;
                }
                else
                    cout << "Mismatch card!" << endl;
            }
        }

        //5.3 If the card is not found
        else
            cout << "Card not found!" << endl;
    }

    // Initialize the card to be returned
    playedUNO newCard;

    if ( draw ) {
        newOrNot = false;
        // The round is skipped and the current discard remains
        newCard = currentCard;
        
        // Draw a new card
        UNO newDraw = randomSingleUNO(time(NULL) - 246810);
        
        // Add a new random card
        player[0].card.push_back(newDraw);
    }
    else {
        newOrNot = true;
        // Put the cards to the front and replace the played card
        for ( int i = pos ; i < ( player[0].card.size() - 1 ) ; i++ ) {
            player[0].card[i] = player[0].card[i+1];
        }

        // Delete the newly played card from the card list
        player[0].card.pop_back();
        
        // Returning the newly played card
        newCard.card.col = col;
        newCard.card.num = num;
        newCard.colourToChange = colToChange;
    }

    delete [] numOfCards;

    return newCard;
}
