/************************************************************
 * Name:  Race Partin                                       *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include <iostream>
#include <ios>

#include "Round.h"
#include "Tournament.h"

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

    // --- Step 1: Target Score Setup ---
    if (m_targetScore == 0) {
        // New Game: Ask for score
        while (true) {
            std::cout << "Enter score needed to win: ";
            if (std::cin >> m_targetScore && m_targetScore > 0) {
                std::cin.ignore(1000, '\n');
                break;
            }
            std::cout << "Invalid Input. Please enter a positive integer.\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        std::cout << "Target score set to: " << m_targetScore << "\n" << std::endl;
    }
    else {
        // Loaded Game: Score already exists
        std::cout << "Resuming Tournament. Target score: " << m_targetScore << "\n" << std::endl;
    }

    // --- Step 2: Main Tournament Loop ---
    while (m_totalHumanScore < m_targetScore && m_totalComputerScore < m_targetScore) {

        // Use the persistent member variable
        Round& currentRound = m_currentRound;

        // --- SYNC STEP: Pass Tournament Data to Round ---
        // We must do this because the Round constructor is now empty!
        currentRound.setTargetScore(m_targetScore);
        currentRound.setScores(m_totalHumanScore, m_totalComputerScore);
        currentRound.setRoundNumber(m_roundNumber);

        // --- PREPARE STEP: Deal Cards ---
        if (!m_isResumed) {
            std::cout << "Starting Round " << m_roundNumber << ". . .\n";

            // This function SHUFFLES and DEALS the cards.
            // Without this, everyone has 0 cards and the game ends instantly.
            currentRound.prepareRound(m_roundNumber);
        }
        else {
            std::cout << "Resuming Round " << m_roundNumber << " from saved state. . .\n";
            m_isResumed = false;
        }

        // --- PLAY STEP: Execute Logic ---
        currentRound.playRound(*this);

        // --- UPDATE STEP: Get Results ---
        m_totalHumanScore = currentRound.getHumanScore();
        m_totalComputerScore = currentRound.getComputerScore();

        if (m_totalHumanScore < m_targetScore && m_totalComputerScore < m_targetScore) {
            std::cout << "Press Enter to start the next round...";
            std::cin.get();
            m_roundNumber++;
        }
    }

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
    std::cout << "**************************************************\n" << std::endl;
}