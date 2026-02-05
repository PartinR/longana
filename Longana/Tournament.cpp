/************************************************************
 * Name:  Race Partin                                       *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include <iostream>
#include <ios>
#include "Tournament.h"
#include "Round.h"

 /* *********************************************************************
 Function Name: playTournament
 Purpose: Acts as the main driver for the entire application. It handles
          the initial setup, maintains the tournament-wide scores, and
          manages the progression from one round to the next.
 Parameters: None
 Return Value: None (void)
 Algorithm:
          1. Display the tournament welcome banner.
          2. Prompt the user for a target winning score; validate that the
             input is a positive integer.
          3. Enter a loop that continues as long as both players' total
             scores are below the target score.
          4. Within the loop, instantiate a Round object, passing in
             the current tournament state (scores and round number).
          5. Call playRound() to execute the game logic for that round.
          6. Retrieve the updated scores from the Round object and update
             the tournament's persistent score variables.
          7. If the tournament is not yet won, wait for user input and
             increment the round counter.
          8. Once a player reaches the target, call announceWinner().
 Reference: None
 ********************************************************************* */
void Tournament::playTournament() {
    std::cout << "=======================================\n";
    std::cout << "          LONGANA TOURNAMENT           \n";
    std::cout << "=======================================\n";

    // Input validation loop for setting the tournament goal
    while (true) {
        std::cout << "Enter score needed to win: ";
        if (std::cin >> m_targetScore && m_targetScore > 0) {
            break;
        }
        else {
            // Clear error flags and discard bad input from the buffer
            std::cout << "Invalid Input. Please enter a positive integer.\n";
            std::cin.clear();
            std::cin.ignore();
        }
    }

    std::cout << "Target score set to: " << m_targetScore << std::endl;

    // Main tournament loop: continues until a player crosses the score threshold
    while (m_totalHumanScore < m_targetScore && m_totalComputerScore < m_targetScore) {

        std::cout << "Starting Round. . .\n";

        // Pass the persistent tournament state into the Round coordinator
        Round currentRound(m_roundNumber, m_targetScore, m_totalHumanScore, m_totalComputerScore);

        // Execute the round's turn-based logic
        currentRound.playRound();

        // Update tournament totals based on the outcome of the round
        m_totalHumanScore = currentRound.getHumanScore();
        m_totalComputerScore = currentRound.getComputerScore();

        // Check if we need to proceed to another round
        if (m_totalHumanScore < m_targetScore && m_totalComputerScore < m_targetScore) {
            std::cout << "Press Enter to start the next round...";
            std::cin.ignore();
            std::cin.get(); // Pause execution for user readiness

            m_roundNumber++;
        }
    }

    // Tournament end: announce final results
    announceWinner();
}

/* *********************************************************************
Function Name: announceWinner
Purpose: Compares the final tournament scores and outputs the final
         standings and the winner's announcement.
Parameters: None
Return Value: None (void)
Algorithm:
         1. Print the final results header.
         2. Display final scores for the Human and Computer against the target.
         3. If both players exceeded the target in the same round, the
            player with the higher score is declared the winner.
         4. If only one player exceeded the target, they are the winner.
         5. In the event of an exact tie above the target, declare a draw.
Reference: None
********************************************************************* */
void Tournament::announceWinner() const {
    std::cout << "\n**************************************************\n";
    std::cout << "              TOURNAMENT FINAL RESULTS            \n";
    std::cout << "**************************************************\n";
    std::cout << " Final Human Score:    " << m_totalHumanScore << "\n";
    std::cout << " Final Computer Score: " << m_totalComputerScore << "\n";
    std::cout << " Target Score:         " << m_targetScore << "\n\n";

    // Evaluation logic for determining the ultimate tournament winner
    if (m_totalHumanScore >= m_targetScore && m_totalComputerScore >= m_targetScore) {
        // Tie-breaker logic: higher margin of victory wins
        if (m_totalHumanScore > m_totalComputerScore) {
            std::cout << " >>> CONGRATULATIONS! HUMAN WINS THE TOURNAMENT! <<<\n";
        }
        else if (m_totalComputerScore > m_totalHumanScore) {
            std::cout << " >>> GAME OVER. COMPUTER WINS THE TOURNAMENT! <<<\n";
        }
        else {
            std::cout << " >>> IT'S A DRAW! <<<\n";
        }
    }
    else if (m_totalHumanScore >= m_targetScore) {
        std::cout << " >>> CONGRATULATIONS! HUMAN WINS THE TOURNAMENT! <<<\n";
    }
    else {
        std::cout << " >>> GAME OVER. COMPUTER WINS THE TOURNAMENT! <<<\n";
    }
    std::cout << "**************************************************\n";
}