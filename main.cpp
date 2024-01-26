// main.cpp

#include <iostream>
#include <fstream>  // for filr input/output
#include <cstdlib>  // For calling srand(), rand()
#include <ctime>    // For calling time()
#include <unistd.h>     // For the calling of sleep()
#include <cstdio>   // To remove() saved file
#include "onehavenocards.h"
#include "selfDefStruct.h"    // For calling struct UNO & ListOfCards
#include "random.h" // For calling randomSingleUNO()
#include "AI_requestAI.h" // For calling AI_requestAI()
#include "card_effect.h" // For calling card_effect functions
#include "display_requestUser.h" // For calling display_requestUser()
#include "display_waitingForAI.h"   // For calling display_waitingForAI()
#include "whoWin.h"     // For calling of whoWin()
#include "display_result.h"   // display_result()
#include "SaveAndLoad.h"    // Saving and loading game status

using namespace std;


// Display the welcome screen and ask user to choose the game mode (i.e. the number of player)
// Return the number of player (MAX: 10)
void displayWelcomeScreen() {
    cout << "==== Welcome to UNO Game ====" << endl;
    cout << "1. Start New Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "3. About Game" << endl;
    cout << "4. Exit" << endl;
}

void getValidNumPlayers(int &numPlayers) {
    do {
        cout << "Enter the number of players (>1): ";
        cin >> numPlayers;

        if (numPlayers >= 2) {
            break;  // Valid input, exit the loop
        }
        else {
            cout << "Invalid input. Please enter a number greater than 1." << endl;
        }
    } while (true);

}

int getValidInitialNumOfCards() {
    int initialNumOfCards;

    do {
        cout << "Enter the initial hand size (>1): ";
        cin >> initialNumOfCards;

        if (initialNumOfCards > 1) {
            break;  // Valid input, exit the loop
        }
        else {
            cout << "Invalid input. Please enter a number greater than 1." << endl;
        }
    } while (true);

    return initialNumOfCards;
}

void startNewGame() {
    remove("savegame.txt");
    int numOfPlayers;
    getValidNumPlayers(numOfPlayers);
    int initialNumOfCards = getValidInitialNumOfCards();

    cout << "\nNew game started with " << numOfPlayers << " players and initial hand size of " << initialNumOfCards << "." << endl;

    // Dynamic array storing cards of players
    ListOfCards *player = new ListOfCards[numOfPlayers];

//    // Empty the array
//    for (int i = 0; i < numOfPlayers; i++) {
//        for (int j = 0; j < 100; j++) {
//            player[i].card[j].col = '\0';
//            player[i].card[j].num = '\0';
//        }
//    }

    // Randomly assign initial UNO cards to all players
    for (int i = 0; i < numOfPlayers; i++) {
        for (int j = 0; j < initialNumOfCards; j++) {
            player[i].card.push_back( randomSingleUNO(time(NULL) + i*65536 + j) );
        }
    }

    bool reverse = false;   // For reverse card - true if reverse card is played
    int counter = numOfPlayers * 65536;        // The remainder of counter / numOfPlayers telling which player is going to play
    int round = 0;          // For the leaderboard

    playedUNO currentCard;

    // Initialize the starting card
    currentCard.card = randomSingleUNO(time(NULL) - 123456);
    currentCard.colourToChange = 'n';
    // Exclude non-coloured card as initial card
    if ( currentCard.card.col == 'n' ) {
        currentCard.card.col = 'b';
        currentCard.card.num = '0';
    }

    // Each loop asks a player (user or AI) to play a suitable card, then determine and execute the action of the played card
    // Exit the loop when one of the player played all of his/her cards
    // If the number of cards holding by a player exceeds 100,
    // => the player can still draw a card,
    // => but a random card will be discarded automatically.
    bool crowned = false;
    bool save = false;  // Whether user decided to quit and save the file
    bool newOrNot = false; // Whether the played card / discard is newly played, then the program can determine whether it needs to execute the card action
    while (!onePlayerNoCards(player, numOfPlayers) && !save) {

	// Add a time delay
        cout << endl;
        sleep(1);

        // Prevent the counter from reaching zero
        if ( counter <= numOfPlayers ) {
            counter += numOfPlayers * 65536;
        }
        
        // Ask for input of playing card from user or AI
        if ( counter % numOfPlayers == 0 )    // The turn of user
            currentCard = display_requestUser(player, currentCard, numOfPlayers, newOrNot, save);    // The card played by player is stored as "currentCard"
        else {
            int AIIndex = counter % numOfPlayers;    // The turn of AI
            display_waitingForAI(currentCard, AIIndex, player, numOfPlayers); // Display which AI is playing and wait for a time delay of 1 second
            currentCard = AI_requestAI(player, AIIndex ,currentCard, newOrNot); // The card played by AI is stored as "currentCard"

        } 
        ///////////////////////////////////////////
        // (TO BE FILLED) Action after each cards//
        ///////////////////////////////////////////
        // Action only if the card is new
        if ( newOrNot ) {
            char check_col = currentCard.card.col;
            char check_num = currentCard.card.num;
            // check the color whether it is 'n' or not
            if(check_col != 'n'){ //if it is not, card effect only for D, R, S
	        	switch(check_num){
	        		case 'D':
	        			if(reverse == false){ //when it is not reverse, card should be added to next player(counter++)
	        				Draw2(player, (counter+1) % numOfPlayers);
                            skip(counter, reverse);
	        			}
	        			else{//when it is reverse, card should be added to next player(counter--)
	        				Draw2(player, (counter-1) % numOfPlayers);
                            skip(counter, reverse);
	        			}
	        			break;
	        		case 'R':
	        			reverse = (reverse == false) ? true : false; // when reverse == false, then set true and vice versa
	        			break;
	        		case 'S':
	        			skip(counter, reverse);
	        			break;
	        	}
	        }
	        else{ // if the color is 'n', only 'W', 'D' 
	        	switch(check_num){
	        		//case 'W':
	        		//	Wild(currentCard);
	        		//	break;
	        		case 'D':
	        			if(reverse == false){//when it is not reverse, card should be added to next player(counter++)
	        				WildDraw(player, (counter+1) % numOfPlayers);
                            skip(counter, reverse);
	        			}
	        			else{//when it is reverse, card should be added to next player(counter--)
	        				WildDraw(player, (counter-1) % numOfPlayers);
                            skip(counter, reverse);
	        			}
	        			break;
	        	}
	        }
        }
        // Save the file if save = T
        if ( save ) {
            saveGameProgress( player , numOfPlayers , currentCard , counter , round , reverse );
            delete [] player;
            return;
        }

        // Pass the turn to the next player
        if (reverse == true)
            counter--;
        else
            counter++;
        newOrNot = false;
    
//        // Determine and display who wins while no one played all the cards
//        int winPlayerIndex = whoWin(player, numOfPlayers);
//        if (winPlayerIndex > -1) {
//            display_result(player, numOfPlayers);
//            crowned = true;
//            break;
//        }
        // Save game progress
        //bool saveAndExit = saveGameProgress(player, *numOfPlayers, currentCard, counter, round);
        //if (saveAndExit) {
        //    cout << "Game progress saved. Goodbye!" << endl;
        //    return;
        //}
    }

    // Determine and display who wins while someone played all the cards
    if (crowned == false){
        int winPlayerIndex = whoWin(player, numOfPlayers);
        display_result(player, numOfPlayers);
    }
    delete [] player;
}

void loadGame() {

    int numOfPlayers;
    loadGameSize(numOfPlayers);
    
    ListOfCards *player = new ListOfCards[numOfPlayers];
    bool reverse;   // For reverse card - true if reverse card is played
    int counter;        // The remainder of counter / numOfPlayers telling which player is going to play
    int round;          // For the leaderboard
    playedUNO currentCard;

    loadGameProgress(player, numOfPlayers, currentCard, counter, round, reverse);
    remove("savegame.txt");

    bool crowned = false;
    bool save = false;  // Whether user decided to quit and save the file
    bool newOrNot = false; // Whether the played card / discard is newly played, then the program can determine whether it needs to execute the card action

    // Each loop asks a player (user or AI) to play a suitable card, then determine and execute the action of the played card
    // Exit the loop when one of the player played all of his/her cards
    // If the number of cards holding by a player exceeds 100,
    // => the player can still draw a card,
    // => but a random card will be discarded automatically.
    while (!onePlayerNoCards(player, numOfPlayers) && !save) {

	// Add a time delay
        cout << endl;
        sleep(1);

        // Prevent the counter from reaching zero
        if ( counter <= numOfPlayers ) {
            counter += numOfPlayers * 65536;
        }
        
        // Ask for input of playing card from user or AI
        if ( counter % numOfPlayers == 0 )    // The turn of user
            currentCard = display_requestUser(player, currentCard, numOfPlayers, newOrNot, save);    // The card played by player is stored as "currentCard"
        else {
            int AIIndex = counter % numOfPlayers;    // The turn of AI
            display_waitingForAI(currentCard, AIIndex, player, numOfPlayers); // Display which AI is playing and wait for a time delay of 1 second
            currentCard = AI_requestAI(player, AIIndex ,currentCard, newOrNot); // The card played by AI is stored as "currentCard"

        } 
        ///////////////////////////////////////////
        // (TO BE FILLED) Action after each cards//
        ///////////////////////////////////////////
        // Action only if the card is new
        if ( newOrNot ) {
            char check_col = currentCard.card.col;
            char check_num = currentCard.card.num;
            // check the color whether it is 'n' or not
            if(check_col != 'n'){ //if it is not, card effect only for D, R, S
	        	switch(check_num){
	        		case 'D':
	        			if(reverse == false){ //when it is not reverse, card should be added to next player(counter++)
	        				Draw2(player, (counter+1) % numOfPlayers);
                            skip(counter, reverse);
	        			}
	        			else{//when it is reverse, card should be added to next player(counter--)
	        				Draw2(player, (counter-1) % numOfPlayers);
                            skip(counter, reverse);
	        			}
	        			break;
	        		case 'R':
	        			reverse = (reverse == false) ? true : false; // when reverse == false, then set true and vice versa
	        			break;
	        		case 'S':
	        			skip(counter, reverse);
	        			break;
	        	}
	        }
	        else{ // if the color is 'n', only 'W', 'D' 
	        	switch(check_num){
	        		//case 'W':
	        		//	Wild(currentCard);
	        		//	break;
	        		case 'D':
	        			if(reverse == false){//when it is not reverse, card should be added to next player(counter++)
	        				WildDraw(player, (counter+1) % numOfPlayers);
                            skip(counter, reverse);
	        			}
	        			else{//when it is reverse, card should be added to next player(counter--)
	        				WildDraw(player, (counter-1) % numOfPlayers);
                            skip(counter, reverse);
	        			}
	        			break;
	        	}
	        }
        }
        // Save the file if save = T
        if ( save ) {
            saveGameProgress( player , numOfPlayers , currentCard , counter , round , reverse );
            delete [] player;
            return;
        }

        // Pass the turn to the next player
        if (reverse == true)
            counter--;
        else
            counter++;
        newOrNot = false;
    
//        // Determine and display who wins while no one played all the cards
//        int winPlayerIndex = whoWin(player, numOfPlayers);
//        if (winPlayerIndex > -1) {
//            display_result(player, numOfPlayers);
//            crowned = true;
//            break;
//        }
        // Save game progress
        //bool saveAndExit = saveGameProgress(player, *numOfPlayers, currentCard, counter, round);
        //if (saveAndExit) {
        //    cout << "Game progress saved. Goodbye!" << endl;
        //    return;
        //}
    }

    // Determine and display who wins while someone played all the cards
    if (crowned == false){
        int winPlayerIndex = whoWin(player, numOfPlayers);
        display_result(player, numOfPlayers);
    }
    delete [] player;
}

int main() {
    int choice;

    do {
        displayWelcomeScreen();

        cout << "Enter your choice (1-4): ";
        cin >> choice;

        if ( choice == 1 ) {
            startNewGame();
        }
        else if ( choice == 2 ) {
            ifstream fin;
            fin.open("savegame.txt");
	        if ( !fin.fail() ) {
                fin.close();
		        cout << "Game loaded successfully! Starting the game..." << endl;
                sleep(2);
		        loadGame();
	        } else {
                fin.close();
		        cout << "Failed to load the game. Please start a new game instead." << endl;
	        }
	    }
        else if ( choice == 3 ) {
	        cout << "HKUNO - Gameplay Overview" << endl;
            cout << "HKUNO brings the classic UNO card game to life through a text-based interface. Challenge computer opponents in a thrilling card-matching adventure." << endl;
            cout << "\nHow to Play:" << endl;
            cout << "1. Start by specifying the number of computer opponents and initial cards for each player." << endl;
            cout << "2. Match your cards with the top card on the discard pile by number, color, or symbol during your turn." << endl;
            cout << "3. Special action cards, including 'Skip,' 'Reverse,' 'Draw Two,' 'Wild,' and 'Wild Draw Four,' introduce strategic twists." << endl;
            cout << "4. AI players follow predefined behaviors outlined in AI_requestAI.cpp." << endl;
            cout << "5. Save and load your game progress seamlessly with SaveAndLoad.cpp." << endl;
            cout << "6. Draw a card if you cannot play during your turn." << endl;
            cout << "7. The first player to empty their hand emerges as the winner." << endl;
            cout << "\nNote: Assume valid user inputs for a smooth gaming experience." << endl;
            cout << "\nEnjoy the HKUNO experience and may you emerge as the UNO champion!" << endl;
        }
        else if ( choice == 4 ) {
            cout << "Exiting the game. Goodbye!" << endl;
        }
        else {
            cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
        }

        cout << endl;

    } while (choice != 4);

    return 0;
}
