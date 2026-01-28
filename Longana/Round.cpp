#include "Round.h"
#include "Tile.h"

/* 
 * Psuedocode:
 * Initialize member variables.
 * Shuffle stock.
 * Draw tiles for human and computer hands.
 * Determine engine value and starting player.
 */
Round::Round(int roundNumber)
    : m_engineValue(7 - roundNumber), // Round 1: 6, Round 2: 5, etc.
    m_isHumanTurn(true),
    m_stock(), m_layout(), m_humanHand(), m_computerHand()
{
    m_stock.shuffle();

    // 1. Initial Deal (8 tiles each)
    for (int i = 0; i < 8; ++i) {
        Tile hTile, cTile;
        if (m_stock.drawTile(hTile)) m_humanHand.addTile(hTile);
        if (m_stock.drawTile(cTile)) m_computerHand.addTile(cTile);
    }

    // 2. Search and Draw Loop
    bool engineFound = false;
    int engineIndex = -1;

    while (!engineFound) {
        // Check Human Hand
        for (int i = 0; i < m_humanHand.getSize(); i++) {
            Tile t = m_humanHand.getTileAtIndex(i);
            if (t.getLeftPips() == m_engineValue && t.getRightPips() == m_engineValue) {
                m_isHumanTurn = true;
                engineFound = true;
                engineIndex = i;
                break;
            }
        }

        if (engineFound) break;

        // Check Computer Hand
        for (int i = 0; i < m_computerHand.getSize(); i++) {
            Tile t = m_computerHand.getTileAtIndex(i);
            if (t.getLeftPips() == m_engineValue && t.getRightPips() == m_engineValue) {
                m_isHumanTurn = false;
                engineFound = true;
                engineIndex = i;
                break;
            }
        }

        // If still not found, both players draw one (The "Repeat" Rule)
        if (!engineFound) {
            Tile hExtra, cExtra;
            if (m_stock.drawTile(hExtra)) m_humanHand.addTile(hExtra);
            if (m_stock.drawTile(cExtra)) m_computerHand.addTile(cExtra);

            // If stock runs out (rare), you'd need a break condition here
            if (m_stock.isEmpty()) break;
        }
    }

    // 3. Force the first move (Automatic Engine Placement)
    if (engineFound) {
        Tile engineTile;
        if (m_isHumanTurn) {
            m_humanHand.playTile(engineIndex, engineTile);
        }
        else {
            m_computerHand.playTile(engineIndex, engineTile);
        }
        // Place on layout - side doesn't matter for the first tile
        m_layout.addLeftTile(engineTile);

        // The rule says the engine holder IS the first player, 
        // but they just used their turn to place it.
        // So we toggle the turn so the NEXT person goes.
        m_isHumanTurn = !m_isHumanTurn;
    }
}

/*
 * Psuedocode:
 * Play a round by alternating turns until a win condition is met.
 */
void Round::playRound() {
    bool roundOver = false;
    while (!roundOver) {
        if (m_isHumanTurn) {
            performHumanTurn();
        } 
        else {
            performComputerTurn();
        }
        
        if (checkWinCondition()) {
            roundOver = true;
        }
        else {
            m_isHumanTurn = !m_isHumanTurn;
        }
    }
}

/* 
 * Psuedocode:
 * Handle human player's turn.
 */
void Round::performHumanTurn() {
    bool turnComplete = false;

    while (!turnComplete) {
        // Implement human turn logic here (e.g., prompt for input, validate move, update layout)
        // Need layoutView
    }
}

/* 
 * Psuedocode:
 * Handle computer player's turn.
 */
void Round::performComputerTurn() {
    bool turnComplete = false;
    while (!turnComplete) {
        // Implement computer turn logic here (e.g., simple AI to choose a valid move, update layout)
        // Need layoutView
    }
}

/* 
 * Psuedocode:
 * Check if either player has won or if the game is blocked.
 */
bool Round::checkWinCondition() {
    // Implement win condition checks here (e.g., check if a hand is empty or if no valid moves are available)
    // Need layoutView
}