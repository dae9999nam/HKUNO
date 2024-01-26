// whoWin.cpp

#include "onehavenocards.h"
#include "selfDefStruct.h"

int whoWin (ListOfCards player[], int numOfPlayer) {
    
    if ( onePlayerNoCards( player ,  numOfPlayer ) ) { //if someone run out of cards

        for (int i = 0; i < numOfPlayer; i++) {

            if ( player[i].card.size() == 0){
                return i; //the player has no cards
            }
        
        }
      
    } else {

        for (int i = 1; i < numOfPlayer; i++){ //compare num of cards between user and the AIs

            int aiCards = player[i].card.size();
            int userCards = player[0].card.size();
            if (aiCards - userCards >= 10) {
                return 0; //human win
            }
            if (userCards - aiCards >= 12) {
                return i; //AI win
            }
        
        }

    }

    return -1;
}