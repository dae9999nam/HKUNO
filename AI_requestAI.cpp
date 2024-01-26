#include <iostream>
#include <ctime>
#include <cstdlib>
#include "selfDefStruct.h"
#include "random.h"
#include "AI_requestAI.h"
using namespace std;

playedUNO easyAI(ListOfCards player[], int AIIndex, playedUNO currentCard, bool &newOrNot ) { // AI mode is defined based on how the AI search for what card to put
	// easyAI search the array of card and find the first occurrence of appropriate card
	int pos = 0;
	bool found = false;
	
	if(currentCard.card.col != 'n'){ // check the card and when it is not 'n'
		for (int i = 0; i < player[AIIndex].card.size() ; i++){
			if (player[AIIndex].card[i].col == currentCard.card.col){ // when the card.col is same as currentCard  
				currentCard.card = player[AIIndex].card[i]; // change the current card
				pos = i;
				found = true;
				break;
			}
//			if(!player[AIIndex].card[i].col){ // when there is no card anymore // when the col is empty, there is no card
//				break;
//			}
			if(player[AIIndex].card[i].col == 'n' && found == false){ // when AI found black card and not played yet
				currentCard.card = player[AIIndex].card[i]; // put black card
				pos = i;
				currentCard.colourToChange = randomSingleUNO(time(NULL)-24234).col;		// Decide which colour to change
				if (currentCard.colourToChange == 'n')
					currentCard.colourToChange = 'y';
				found = true;
				break;
			}
		}
		if(!found == true){ // if no match card with same color, check for the same number
			for (int i = 0; i < player[AIIndex].card.size() ; i++){
				if (player[AIIndex].card[i].num == currentCard.card.num){ // when the card.num is same as currentCard  
					currentCard.card = player[AIIndex].card[i]; // change the current card
					pos = i;
					found = true;
					break;
				}
			}
		}
		if(found == true){
			for (int j = pos; j < (player[AIIndex].card.size()-1) ; j++){ // only for when the player put the card
				player[AIIndex].card[j] = player[AIIndex].card[j + 1]; // remove the card and move the cards to the front
			}
			player[AIIndex].card.pop_back();
		}
	}
	else{ // decision making after the wild card, we have to check colorTochange not the card color
		for (int i = 0; i < player[AIIndex].card.size() ; i++){
			if (player[AIIndex].card[i].col == currentCard.colourToChange){ // when the card.col is same as colorTochange 
				currentCard.card = player[AIIndex].card[i]; // change the current card
				pos = i;
				found = true;
				break;
			}
		} // in this case we dont need to check the num of card. cuz we have to put the correspond color card.
		if(found == true){ // when the AI put the card, it should be removed from the hand
			for (int j = pos; j < (player[AIIndex].card.size()-1) ; j++){ // only for when the player put the card
				player[AIIndex].card[j] = player[AIIndex].card[j + 1]; // remove the card and move the cards to the front
			}
			player[AIIndex].card.pop_back();
		}
	}

	// Draw a card if there is no card
    if (found == false) {
		// Draw a new card
        UNO newDraw = randomSingleUNO(time(NULL) - 246810);
        
        // Add a new random card
        player[AIIndex].card.push_back(newDraw);
    }
	
	// Tell the main() if the acrd is newly played
	if (found == false) {
		newOrNot = false;
	}
	else {
		newOrNot = true;
	}

	return currentCard;
}

	
//number of players = numOfPlayer = array size of player[]

playedUNO AI_requestAI(ListOfCards player[], int AIIndex, playedUNO currentCard, bool &newOrNot){ //player[AIIndex] size is required
	char check_col = currentCard.card.col;
	switch(check_col){
		case 'b':
			currentCard = easyAI(player, AIIndex, currentCard, newOrNot);
			break;
		case 'r':
			currentCard = easyAI(player, AIIndex, currentCard, newOrNot);
			break;
		case 'g':
			currentCard = easyAI(player, AIIndex, currentCard, newOrNot);
			break;
		case 'y':
			currentCard = easyAI(player, AIIndex, currentCard, newOrNot);
			break;
		case 'n':
			currentCard = easyAI(player, AIIndex, currentCard, newOrNot);
	}
	return currentCard;
}
