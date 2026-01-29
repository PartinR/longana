#include <iostream>
#include "Round.h"

int main() {
    std::cout << "=======================================\n";
    std::cout << "      LONGANA - DEBUG TEST DRIVER      \n";
    std::cout << "=======================================\n";

    int roundNum = 1;
    int tournamentScore = 0; // <--- 1. NEW VARIABLE
    char keepPlaying = 'y';

    while (keepPlaying == 'y' || keepPlaying == 'Y') {
        std::cout << "\n";

        // 2. FIXED: Pass BOTH arguments here
        Round currentRound(roundNum, tournamentScore);

        // 3. Play
        currentRound.playRound();

        // TODO: Later, you will need to get the points from 'currentRound' 
        // and add them to 'tournamentScore' here.

        std::cout << "\nRound finished. Play next round? (y/n): ";
        std::cin >> keepPlaying;

        if (keepPlaying == 'y' || keepPlaying == 'Y') {
            roundNum++;
            if (roundNum > 8) roundNum = 1;
        }
    }

    std::cout << "Exiting game.\n";
    return 0;
}