/************************************************************
 * Name:  Race Partin                                       *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include <iostream>

#include "Computer.h"
#include "Layout.h"
#include "Stock.h"
#include "Tile.h"

/* *********************************************************************
Function Name: playTurn
Purpose: Executes the strategy for the Computer player using a "First-Fit"
        approach with side prioritization.
Parameters:
        layout, a Layout object passed by reference. The current board.
        stock, a Stock object passed by reference. The boneyard.
        opponentPassed, a bool passed by value. Indicates if Human passed.
Return Value: Boolean true if a tile was placed, false if the Computer passed.
Algorithm:
        1. Initialize bestIndex to -1 and bestSide to 'R'.
        2. Iterate through the hand to find a legal move:
            a. PRIORITY 1: If a tile fits on the Computer's side (Right),
               select it immediately and stop searching (break).
            b. PRIORITY 2: If a tile fits on the Opponent's side (Left)
               and no Right move has been found yet, mark it as the best candidate.
        3. If a valid move was found in the hand:
            a. Remove the tile from the hand.
            b. Add it to the Layout on the selected side.
            c. Return true.
        4. If no move was found in the hand:
            a. Check if the stock is empty. If so, return false (Pass).
            b. Draw a single tile from the stock and add it to the hand.
            c. Check if the drawn tile is playable (Prioritizing Right over Left).
            d. If playable, place it immediately and return true.
            e. If not playable, return false (Pass).
Reference: None
********************************************************************* */
bool Computer::playTurn(Layout& layout, Stock& stock, bool opponentPassed) {
    std::cout << "Computer is thinking..." << std::endl;

    // Variables to track the best identified move in the current hand
    int bestIndex = -1;
    char bestSide = 'R';

    // Step 1: Iterate through the hand to find a legal move
    for (int i = 0; i < m_hand.getSize(); ++i) {
        Tile tile = m_hand.getTileAtIndex(i);

        // Prioritize playing on the Computer's own side (Right)
        if (canPlayOnSide(tile, 'R', opponentPassed) && layout.isLegalMove(tile, 'R')) {
            bestIndex = i;
            bestSide = 'R';
            break;
        }

        // If no Right move, check if the tile can be played on the Left
        if (bestIndex == -1 && canPlayOnSide(tile, 'L', opponentPassed) && layout.isLegalMove(tile, 'L')) {
            bestIndex = i;
            bestSide = 'L';
        }
    }

    // If a legal move was found in the initial hand, execute it
    if (bestIndex != -1) {
        Tile played;
        m_hand.playTile(bestIndex, played);

        if (bestSide == 'R') {
            layout.addRightTile(played);
            std::cout << "Computer placed " << played.getLeftPips() << "-" << played.getRightPips() 
                << " on the RIGHT." << std::endl;
        }
        else {
            layout.addLeftTile(played);
            std::cout << "Computer placed " << played.getLeftPips() << "-" << played.getRightPips() 
                << " on the LEFT." << std::endl;
        }

        return true;
    }

    // Step 2: Logic for drawing if no moves were found in hand
    // If no moves and no tiles left to draw, the Computer must pass
    if (stock.isEmpty()) {
        std::cout << "Computer cannot move and stock is empty. Computer passes." << std::endl;
        return false;
    }

    // Draw a single tile from the boneyard and add it to the Computer's Hand
    Tile drawn;
    stock.drawTile(drawn);
    m_hand.addTile(drawn);
    std::cout << "Computer drew: " << drawn.getLeftPips() << "-" << drawn.getRightPips() << std::endl;

    // Check if the drawn tile is immediately playable
    bool fitR = canPlayOnSide(drawn, 'R', opponentPassed) && layout.isLegalMove(drawn, 'R');
    bool fitL = canPlayOnSide(drawn, 'L', opponentPassed) && layout.isLegalMove(drawn, 'L');

    if (fitR || fitL) {
        // Create tile for 'drawn' tile to be copied into
        Tile played;

        // The drawn tile is at the very end of the hand
        // m_hand.getSize() represent the index of the drawn tile
        m_hand.playTile(m_hand.getSize() - 1, played);

        // Again, prioritize playing on the Computer's own side
        if (fitR) {
            layout.addRightTile(played);
            std::cout << "Computer placed drawn tile on RIGHT." << std::endl;
        }
        else {
            layout.addLeftTile(played);
            std::cout << "Computer placed drawn tile on LEFT." << std::endl;
        }

        return true;
    }

    // If even the drawn tile cannot be played, the Computer passes
    std::cout << "Computer passes." << std::endl;
    return false;
}

/* *********************************************************************
Function Name: canPlayOnSide
Purpose: Determines if a specific tile is legally eligible to be placed
        on a certain side of the layout based on Longana rules.
Parameters:
        tile, a Tile object passed by const reference. The tile to check.
        side, a char passed by value. 'R' for Computer's side, 'L' for Human's side.
        opponentPassed, a bool passed by value. Flag indicating if the human passed.
Return Value: Boolean true if the tile is allowed on that side, false otherwise.
Algorithm:
        1. If the tile is a double (pips match), it is playable on any side.
        2. If the opponent (Human) passed their last turn, any tile is playable on their side.
        3. Otherwise, return true only if the side is 'R' (the Computer's own designated side).
Reference: None
********************************************************************* */
bool Computer::canPlayOnSide(const Tile& tile, char side, bool opponentPassed) const {
    // 1. Computer can ALWAYS play on its own side (Right)
    if (side == 'R') { return true; }

    // 2. Computer can play on opponent's side (Left) ONLY if:
    //    a. The tile is a Double
    //    b. OR the opponent passed their turn
    if (tile.isDouble() || opponentPassed) { return true; }

    return false;
}