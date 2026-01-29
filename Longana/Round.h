#ifndef ROUND_H
#define ROUND_H

#include "Human.h"
#include "Computer.h"
#include "Stock.h"
#include "Layout.h"

class Round {
public:

    /* --- Constructor --- */
    /// <summary>
    /// Default constructor for the Round class that initializes a Round object.
    /// </summary>
    Round(int roundNumber, int humanScore, int computerScore);

    /* --- Destructor --- */

    /// <summary>
    /// Destructor for the Round class. Performs cleanup when a Round object is destroyed.
    /// </summary>
    ~Round() {}

    /* --- Selectors --- */

    /// <summary>
    /// Get the current round points for human.
    /// </summary>
    /// <returns>Returns the round points</returns>
    inline int getHumanScore() const { return m_human.getScore(); }

    /// <summary>
    /// Get the current round points for human.
    /// </summary>
    /// <returns>Returns the round points</returns>
    inline int getComputerScore() const { return m_computer.getScore(); }

    /* --- Utility Functions --- */

    /// <summary>
    /// Plays a single round.
    /// </summary>
    void playRound();

private:
    int m_roundNumber;
    int m_tournamentScore;

    Human m_human;
    Computer m_computer;

    Stock m_stock;
    Layout m_layout;

    bool m_humanPassed;
    bool m_computerPassed;
    bool m_isHumanTurn;
    int m_engineValue;

    bool checkWinCondition();
    void displayGameState();
};

#endif 