#include <iostream>
#include "Round.h"

int main() {
    std::cout << "=======================================\n";
    std::cout << "      LONGANA - DEBUG TEST DRIVER      \n";
    std::cout << "=======================================\n";

    int roundNum = 1;
    char keepPlaying = 'y';

    while (keepPlaying == 'y' || keepPlaying == 'Y') {
        std::cout << "\n--- STARTING ROUND " << roundNum << " ---\n";

        // 1. Create the Round
        // Constructor logic: Engine = 7 - roundNum. 
        // Round 1 = 6-6, Round 2 = 5-5, etc.
        Round currentRound(roundNum);

        // 2. Play the Round
        // This function will loop internally until someone wins
        currentRound.playRound();

        // 3. Post-Game Options
        std::cout << "\nRound finished. Play next round? (y/n): ";
        std::cin >> keepPlaying;

        if (keepPlaying == 'y' || keepPlaying == 'Y') {
            roundNum++;
            // Reset roundNum to 1 if we go past 8 rounds (Engine 6-6 again)
            if (roundNum > 8) roundNum = 1;
        }
    }

    std::cout << "Exiting game.\n";
    return 0;
}