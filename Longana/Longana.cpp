#include <iostream>
#include "Round.h"

int main() {
    std::cout << "=======================================\n";
    std::cout << "         LONGANA TOURNAMENT            \n";
    std::cout << "=======================================\n";

    // 1. Persistent Variables (The "Database")
    int roundNum = 1;
    int humanTotalScore = 0;
    int computerTotalScore = 0;
    const int TARGET_SCORE = 200; // Game ends when someone hits this

    bool tournamentOver = false;

    while (!tournamentOver) {
        std::cout << "\nStarting Round " << roundNum << "...\n";

        // 2. Create the Round (Pass in the CURRENT scores)
        Round currentRound(roundNum, humanTotalScore, computerTotalScore);

        // 3. Play the Round (The Round object manages turns until someone wins)
        currentRound.playRound();

        // 4. Retrieve Updated Scores (Save them back to our local variables)
        humanTotalScore = currentRound.getHumanScore();
        computerTotalScore = currentRound.getComputerScore();

        // 5. Display Tournament Standings
        std::cout << "\n****************************************\n";
        std::cout << " TOURNAMENT STANDINGS (After Round " << roundNum << ")\n";
        std::cout << " Human: " << humanTotalScore << "\n";
        std::cout << " Computer: " << computerTotalScore << "\n";
        std::cout << "****************************************\n";

        // 6. Check for Tournament Winner
        if (humanTotalScore >= TARGET_SCORE) {
            std::cout << "\n>>> CONGRATULATIONS! Human wins the Tournament! <<<\n";
            tournamentOver = true;
        }
        else if (computerTotalScore >= TARGET_SCORE) {
            std::cout << "\n>>> GAME OVER. Computer wins the Tournament! <<<\n";
            tournamentOver = true;
        }
        else {
            // Ask to continue
            char keepPlaying;
            std::cout << "\nPlay next round? (y/n): ";
            std::cin >> keepPlaying;

            if (keepPlaying == 'y' || keepPlaying == 'Y') {
                roundNum++;
            }
            else {
                std::cout << "Tournament paused. Exiting.\n";
                break;
            }
        }
    }

    return 0;
}