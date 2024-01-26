// leaderboard.cpp

#include <iostream>

void leaderboard(int wins[], int numOfPlayer) {
    std::cout << "---------------------------------\n";
    std::cout << "|           LEADERBOARD         |\n";
    std::cout << "---------------------------------\n";
    for (int i = 0; i < numOfPlayer; i++) {
        if (i == 0) {
            std::cout << "|   Human player: " << wins[i] << " wins   |\n";
        } else {
            std::cout << "|   AI #" << i << ": " << wins[i] << " wins   |\n";
        }
    }
    std::cout << "---------------------------------\n";
}

