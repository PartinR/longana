#ifndef HUMAN_H
#define HUMAN_H

/************************************************************
 * Name:  Race Partin                                       *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include "Player.h"
#include "Layout.h"
#include "Stock.h"
#include "Tile.h"

/* *********************************************************************
Class Name: Human
Purpose: Represents the human player in the Longana game. Inherits from
        the Player class and implements logic to interact with the user via
        console input to play turns, validate moves, and draw tiles.
********************************************************************* */
class Human : public Player {
public:

    /* *********************************************************************
    Function Name: playTurn
    Purpose: Executes the logic for the Human player's turn. Handles user
            input for tile and side selection, manages drawing from the
            stock, and enforces immediate play rules.
    Parameters:
            layout, a Layout object passed by reference. The current board.
            stock, a Stock object passed by reference. The boneyard.
            opponentPassed, a bool passed by value. Indicates if Computer passed.
    Return Value: Boolean true if a tile was placed, false if the Human passed.
    Algorithm:
            1. Scan the current hand to determine if any legal moves exist.
            2. If a valid move exists in the hand:
                a. Prompt the user to select a tile by its index.
                b. If the tile is playable on both sides, prompt the user
                    to choose 'L' or 'R'.
                c. Validate the selection; if legal, remove from hand,
                    update Layout, and return true.
            3. If no legal move exists in the hand:
                a. Check if the stock is empty. If so, return false (Pass).
                b. Draw a single tile from the stock and add it to the hand.
                c. Check if the newly drawn tile is immediately playable
                    on either the Left or Right side.
                d. If playable, force the user to play it immediately
                    and return true.
                e. If not playable, return false (Pass).
    Reference: None
    ********************************************************************* */
    bool playTurn(Layout& layout, Stock& stock, bool opponentPassed) override;

private:

    /* *********************************************************************
    Function Name: canPlayOnSide
    Purpose: Helper function to validate if a selected tile can legally be
            placed on a specific side of the layout.
    Parameters:
            tile, a Tile object passed by const reference. The tile the user wants to play.
            side, a char passed by value. The side chosen ('L' for Left, 'R' for Right).
                user is allowed to play on the Computer's side.
    Return Value: true if the move is legal, false otherwise.
    Algorithm:
            1. Identify the open pip value on the specified side of the Layout.
            2. Check if the tile matches that value.
            3. Check if the side belongs to the player (Human side) or if the
                Condition (opponentPassed) allows play on the other side.
    Reference: None
    ********************************************************************* */
    bool canPlayOnSide(const Tile& tile, char side, bool opponentPassed) const;

};

#endif