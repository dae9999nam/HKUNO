// display_result.cpp

#include <iostream>
#include "selfDefStruct.h"
#include "whoWin.h"

void display_result(ListOfCards player[], int numOfPlayer) {
    int winner = whoWin(player, numOfPlayer);
    if (winner == -1) {
        std::cout << "The game is still ongoing.\n";
    } else if (winner == 0) {
        std::cout << "You have won the game!\n";
    } else {
        std::cout << "AI #" << winner << " has won the game!\n";
    }

    // Display the final state of the cards
    for (int i = 0; i < numOfPlayer; i++) {
        std::cout << "Player " << i << " has " << player[i].card.size() << " cards left.\n";
    }
}