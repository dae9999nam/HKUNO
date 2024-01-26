#include "SaveAndLoad.h"
#include "selfDefStruct.h"
#include <fstream>
#include <vector>
using namespace std;

void saveGameProgress(ListOfCards player[], int numOfPlayers, playedUNO currentCard, int counter, int round, bool reverse) {
    ofstream saveFile;
    saveFile.open("savegame.txt");

    // Save game state to the file
    saveFile << numOfPlayers << " " << counter << " " << round << " " << reverse << "\n";
    for (int i = 0; i < numOfPlayers; i++) {
        saveFile << player[i].card.size() << "\n";
        for (int j = 0; j < player[i].card.size() ; j++) {
            saveFile << player[i].card[j].num << " " << player[i].card[j].col << "\n";
        }
    }

    saveFile << currentCard.card.num << " " << currentCard.card.col << " " << currentCard.colourToChange << "\n";

    saveFile.close();
}

void loadGameProgress(ListOfCards player[], int &numOfPlayers, playedUNO &currentCard, int &counter, int &round, bool &reverse) {
    ifstream loadFile;
    loadFile.open("savegame.txt");

    // Load game state from the file
    loadFile >> numOfPlayers >> counter >> round >> reverse;
    for (int i = 0; i < numOfPlayers; i++) {
        int playerCardSize;
        loadFile >> playerCardSize;
        for (int j = 0; j < playerCardSize; j++) {
            UNO tmpUNO;
            loadFile >> tmpUNO.num >> tmpUNO.col;
            player[i].card.push_back(tmpUNO);
        }
    }

    loadFile >> currentCard.card.num >> currentCard.card.col >> currentCard.colourToChange;

    loadFile.close();
}

void loadGameSize(int &numOfPlayers) {
    ifstream loadFile;
    loadFile.open("savegame.txt");
    // Load game size from the file
    loadFile >> numOfPlayers;
    loadFile.close();
}