#ifndef COMPUTER_H
#define COMPUTER_H

/************************************************************
 * Name:  Race Partin                                       *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include "Layout.h"
#include "Player.h"
#include "Stock.h"
#include "Tile.h"

/* *********************************************************************
Class Name: Computer
Purpose: Represents the computer player in the Longana game.
        Inherits from the Player class and implements specific logic
        which is placing the first possible move and favoring the 
        Computer's side.
********************************************************************* */
class Computer : public Player {
public:

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
    bool playTurn(Layout& layout, Stock& stock, bool opponentPassed) override;

private:

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
    bool canPlayOnSide(const Tile& tile, char side, bool opponentPassed) const;

};

#endif