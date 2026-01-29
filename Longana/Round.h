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
    Round(int roundNumber, int tournamentScore);

    /* --- Destructor --- */

    /// <summary>
    /// Destructor for the Round class. Performs cleanup when a Round object is destroyed.
    /// </summary>
    ~Round() {}

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