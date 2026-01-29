/************************************************************
 * Name:  Race Benjamin Partin                              *
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
 Function Name: canPlayOnSide
 Purpose: Determines if a specific tile is legally eligible to be placed
          on a certain side of the layout based on Longana rules.
 Parameters:
          t, a Tile object passed by const reference. The tile to check.
          side, a char passed by value. 'L' for Computer's side, 'R' for Human's side.
          opponentPassed, a bool passed by value. Flag indicating if the human passed.
 Return Value: Boolean true if the tile is allowed on that side, false otherwise.
 Algorithm:
          1. If the tile is a double (pips match), it is playable on any side.
          2. If the opponent (Human) passed their last turn, any tile is playable on their side.
          3. Otherwise, return true only if the side is 'R' (the Computer's own designated side).
 Reference: None
 ********************************************************************* */
bool Computer::canPlayOnSide(const Tile& t, char side, bool opponentPassed) const {
    // All doubles are playable on any open side in Longana
    if (t.getLeftPips() == t.getRightPips()) return true;

    // If the opponent passed, their side of the layout becomes open to the Computer
    if (opponentPassed) return true;

    // By default, a player can always play on their own side (represented here as 'R')
    return (side == 'R');
}

/* *********************************************************************
Function Name: playTurn
Purpose: Executes the AI strategy for the Computer player. Searches the
         hand for the best move, draws if necessary, and updates the game board.
Parameters:
         layout, a Layout object passed by reference. The current board.
         stock, a Stock object passed by reference. The boneyard.
         opponentPassed, a bool passed by value. Indicates if Human passed.
Return Value: Boolean true if a tile was placed, false if the Computer passed.
Algorithm:
         1. Search through the hand for a tile that can play on the Computer's side (Right).
         2. If no Right move found, search for a move on the Left side.
         3. If a move is found, remove tile from hand, add to layout, and return true.
         4. If no move found, check if stock is empty. If empty, return false (Pass).
         5. Draw a tile from the stock and add to hand.
         6. Check if the newly drawn tile can be played (Preferring Right).
         7. If playable, place it and return true; otherwise, return false (Pass).
Reference: None
********************************************************************* */
bool Computer::playTurn(Layout& layout, Stock& stock, bool opponentPassed) {
    std::cout << "Computer is thinking...\n";

    // Variables to track the best identified move in the current hand
    int bestIndex = -1;
    char bestSide = 'R';

    // Step 1: Iterate through the hand to find a legal move
    for (int i = 0; i < m_hand.getSize(); ++i) {
        Tile t = m_hand.getTileAtIndex(i);

        // Prioritize playing on the Computer's own side (Right)
        if (canPlayOnSide(t, 'R', opponentPassed) && layout.isLegalMove(t, 'R')) {
            bestIndex = i;
            bestSide = 'R';
            break;
        }

        // If no Right move, check if the tile can be played on the Left
        if (bestIndex == -1 && canPlayOnSide(t, 'L', opponentPassed) && layout.isLegalMove(t, 'L')) {
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
            std::cout << "Computer placed " << played.getLeftPips() << "-" << played.getRightPips() << " on the RIGHT.\n";
        }
        else {
            layout.addLeftTile(played);
            std::cout << "Computer placed " << played.getLeftPips() << "-" << played.getRightPips() << " on the LEFT.\n";
        }
        return true;
    }

    // Step 2: Logic for drawing if no moves were found in hand
    if (stock.isEmpty()) {
        // If no moves and no tiles left to draw, the Computer must pass
        std::cout << "Computer cannot move and stock is empty. Computer passes.\n";
        return false;
    }

    // Draw a single tile from the boneyard
    Tile drawn;
    stock.drawTile(drawn);
    m_hand.addTile(drawn);
    std::cout << "Computer drew a tile.\n";

    // Check if the drawn tile is immediately playable
    bool fitR = canPlayOnSide(drawn, 'R', opponentPassed) && layout.isLegalMove(drawn, 'R');
    bool fitL = canPlayOnSide(drawn, 'L', opponentPassed) && layout.isLegalMove(drawn, 'L');

    if (fitR || fitL) {
        Tile played;
        // The drawn tile is at the very end of the hand
        m_hand.playTile(m_hand.getSize() - 1, played);

        // Again, prioritize playing on the Computer's own side
        if (fitR) {
            layout.addRightTile(played);
            std::cout << "Computer placed drawn tile on RIGHT.\n";
        }
        else {
            layout.addLeftTile(played);
            std::cout << "Computer placed drawn tile on LEFT.\n";
        }
        return true;
    }

    // If even the drawn tile cannot be played, the Computer passes
    std::cout << "Computer passes.\n";
    return false;
}