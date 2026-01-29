#ifndef ROUND_H
#define ROUND_H

#include "Stock.h"
#include "Layout.h"
#include "Hand.h"
#include "LayoutView.h"
#include "Tile.h"

class Round {
public:

    /* --- Constructor --- */
    /// <summary>
    /// Default constructor for the Round class that initializes a Round object.
    /// </summary>
    Round(int roundNumber);

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
    Stock m_stock;
    Layout m_layout;
    Hand m_humanHand;
    Hand m_computerHand;
    LayoutView m_view;

    int m_engineValue;
    bool m_isHumanTurn;

    // Helper Function
    static bool canPlayOnSide(const Tile& t, char side, bool isHumanTurn, bool opponentPassed);

    void performHumanTurn();
    void performComputerTurn();
    bool checkWinCondition();

    bool m_humanPassed;
    bool m_computerPassed;
};

#endif 