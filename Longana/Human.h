#ifndef HUMAN_H
#define HUMAN_H

/************************************************************
 * Name:  Race Benjamin Partin                              *
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
    Purpose: Executes the logic for the Human player's turn. It prompts the
             user for input to select a tile and a side to play on. It handles
             input validation and enforces game rules.
    Parameters:
             layout, a Layout object passed by reference. Represents the current
                     board state. Modified when the user places a tile.
             stock, a Stock object passed by reference. Represents the boneyard.
                    Modified when the user draws a tile.
             opponentPassed, a boolean passed by value. Indicates if the computer
                             passed its last turn (allowing play on the opponent's side).
    Return Value: true if a move was made (tile placed), false if the player passed.
    Algorithm:
             1. Check if the player has any legal moves.
             2. If no moves are available, automatically draw from Stock.
             3. If a drawn tile is playable, play it immediately (per Longana rules).
             4. If moves are available, prompt user to select a tile index.
             5. If the tile can be played on multiple sides, prompt for side selection.
             6. Validate the move using canPlayOnSide.
             7. If valid, update Layout and Hand, then return true.
             8. If invalid, display error and repeat loop.
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
             opponentPassed, a boolean passed by value. Used to validate if the
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