#ifndef COMPUTER_H
#define COMPUTER_H

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
 Class Name: Computer
 Purpose: Represents the computer player in the Longana game.
          Inherits from the Player class and implements specific AI logic
          for determining the best legal move or drawing from the stock.
 ********************************************************************* */
class Computer : public Player {
public:

    /* *********************************************************************
    Function Name: playTurn
    Purpose: Executes the logic for the Computer's turn. It attempts to place
             a tile on the layout according to the game rules. If no move is
             possible, it draws from the stock.
    Parameters:
             layout, a Layout object passed by reference. Represents the current board state.
                     It is modified if the computer places a tile.
             stock, a Stock object passed by reference. Represents the boneyard.
                    It is modified if the computer draws a tile.
             opponentPassed, a boolean passed by value. Indicates if the human
                             player passed their last turn (allows playing on opponent's side).
    Return Value: true if a move was made (tile placed), false if the computer passed.
    Algorithm:
             1. Traverse the hand to find a legal move on the Computer's side,
                Layout's side (if Engine), or Human's side (if passed).
             2. If a move is found, place the tile and return true.
             3. If no move is found, draw a tile from the Stock.
             4. If the drawn tile can be played, play it and return true.
             5. If not, pass the turn and return false.
    Reference: None
    ********************************************************************* */
    bool playTurn(Layout& layout, Stock& stock, bool opponentPassed) override;

private:

    /* *********************************************************************
    Function Name: canPlayOnSide
    Purpose: Helper function to determine if a specific tile can be legally
             placed on a specific side of the layout given the current game state.
    Parameters:
             tile, a Tile object passed by const reference. The tile being checked.
             side, a char passed by value. Indicates which side ('L' for Left/Computer,
                   'R' for Right/Human) to check against.
             opponentPassed, a boolean passed by value. Used to determine if
                             playing on the opponent's side is currently legal.
    Return Value: true if the tile can be placed on the specified side, false otherwise.
    Algorithm:
             1. specific rules check (e.g., matching pips) against the layout's
                current end piece for the specified side.
    Reference: None
    ********************************************************************* */
    bool canPlayOnSide(const Tile& tile, char side, bool opponentPassed) const;

};

#endif