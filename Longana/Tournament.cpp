#include <iostream>
#include <ios>
#include "Tournament.h"
#include "Round.h"

void Tournament::playTournament() {
    std::cout << "=======================================\n";
    std::cout << "         LONGANA TOURNAMENT            \n";
    std::cout << "=======================================\n";

    while (true) {
        std::cout << "Enter score needed to win: ";
        if (std::cin >> m_targetScore && m_targetScore > 0) {
            break;
        }
        else {
            std::cout << "Invalid Input. Try again.\n";
            std::cin.clear();
            std::cin.ignore();
        }
    }

    std::cout << "Target score set to: " << m_targetScore << std::endl;

    while (m_totalHumanScore < m_targetScore && m_totalComputerScore < m_targetScore) {
        
        std::cout << "Starting Round. . .\n";

        Round currentRound(m_roundNumber, m_targetScore, m_totalHumanScore, m_totalComputerScore);

        currentRound.playRound();

        m_totalHumanScore = currentRound.getHumanScore();
        m_totalComputerScore = currentRound.getComputerScore();

        if (m_totalHumanScore < m_targetScore && m_totalComputerScore < m_targetScore) {
            std::cout << "Press Enter to start the next round...";
            std::cin.ignore();
            std::cin.get(); // Wait for user to press Enter

            m_roundNumber++;
        }
    }

    announceWinner();
}

void Tournament::announceWinner() const {
    std::cout << "\n**************************************************\n";
    std::cout << "              TOURNAMENT FINAL RESULTS            \n";
    std::cout << "**************************************************\n";
    std::cout << " Final Human Score:    " << m_totalHumanScore << "\n";
    std::cout << " Final Computer Score: " << m_totalComputerScore << "\n";
    std::cout << " Target Score:         " << m_targetScore << "\n\n";

    if (m_totalHumanScore >= m_targetScore && m_totalComputerScore >= m_targetScore) {
        // Tie-breaker: If both cross the line in the same round, higher score wins
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