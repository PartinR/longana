/************************************************************
 * Name:  Race Partin                                       *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include <iostream>
#include <vector>
#include <cctype>
#include "Human.h"
#include "Layout.h"
#include "Stock.h"
#include "Tile.h"

/* *********************************************************************
Function Name: canPlayOnSide
Purpose: Determines if the human player is legally allowed to place a
        specific tile on a specific side of the layout.
Parameters:
        tile, a Tile object passed by const reference. The tile to check.
        side, a char passed by value. 'L' for Human side, 'R' for Computer side.
        opponentPassed, a bool passed by value. Flag indicating if computer passed.
Return Value: Boolean true if the move is permitted by rules, false otherwise.
Algorithm:
        1. If the tile is a double, it is legally playable on any side.
        2. If the opponent (Computer) passed their turn, the Human can play on the 'R' side.
        3. Otherwise, the Human is restricted to their own side ('L').
Reference: None
********************************************************************* */
bool Human::canPlayOnSide(const Tile& tile, char side, bool opponentPassed) const {
    // Doubles can be played on either side regardless of pass status
    if (tile.getLeftPips() == tile.getRightPips()) return true;

    // The Human can play on the Computer's side (R) only if the Computer passed
    if (opponentPassed) return true;

    // Standard rule: Humans play on the Left side of the engine
    return (side == 'L');
}

/* *********************************************************************
Function Name: playTurn
Purpose: Manages the interactive turn for the human player, including
        move validation, drawing from the boneyard, and user input.
Parameters:
        layout, a Layout object passed by reference.
        stock, a Stock object passed by reference.
        opponentPassed, a bool passed by value.
Return Value: Boolean true if a tile was successfully placed, false if passed.
Algorithm:
        1. Scan the hand for any legal moves on any valid side.
        2. If no moves exist:
            a. Prompt the user and draw from the boneyard.
            b. If drawn tile is playable, prompt for side and place it.
            c. If not playable, inform the user and return false (pass).
        3. If moves exist, enter a loop:
            a. Prompt user for a tile index.
            b. Validate index and check if the tile can play on 'L' or 'R'.
            c. If the tile fits both, prompt for side selection.
            d. Remove tile from hand and add to Layout.
            e. Return true.
Reference: None
********************************************************************* */
bool Human::playTurn(Layout& layout, Stock& stock, bool opponentPassed) {
    // Step 1: Identify all playable tiles in the current hand
    std::vector<int> playableIndices;
    for (int i = 0; i < m_hand.getSize(); ++i) {
        Tile t = m_hand.getTileAtIndex(i);
        bool fitL = canPlayOnSide(t, 'L', opponentPassed) && layout.isLegalMove(t, 'L');
        bool fitR = canPlayOnSide(t, 'R', opponentPassed) && layout.isLegalMove(t, 'R');
        if (fitL || fitR) playableIndices.push_back(i);
    }

    // Step 2: Handle the scenario where no moves are available in the initial hand
    if (playableIndices.empty()) {
        std::cout << " >> No moves available. Drawing from boneyard...\n";

        if (stock.isEmpty()) {
            std::cout << " >> Boneyard empty. You must pass.\n";
            return false;
        }

        Tile drawn;
        stock.drawTile(drawn);
        m_hand.addTile(drawn);
        std::cout << " >> You drew: " << drawn.getLeftPips() << "-" << drawn.getRightPips() << "\n";

        // Check if the newly drawn tile can be played immediately
        bool fitL = canPlayOnSide(drawn, 'L', opponentPassed) && layout.isLegalMove(drawn, 'L');
        bool fitR = canPlayOnSide(drawn, 'R', opponentPassed) && layout.isLegalMove(drawn, 'R');

        if (!fitL && !fitR) {
            std::cout << " >> Drawn tile cannot be played. You pass.\n";
            return false;
        }

        // Determine which side to place the drawn tile
        char side = 'L';
        if (fitL && fitR) {
            std::cout << " >> Drawn tile fits BOTH sides. Play (L)eft or (R)ight? ";
            std::cin >> side;
            side = toupper(side);
        }
        else if (fitR) {
            side = 'R';
            std::cout << " >> Tile must be played on RIGHT.\n";
        }
        else {
            std::cout << " >> Tile must be played on LEFT.\n";
        }

        Tile playedTile;
        m_hand.playTile(m_hand.getSize() - 1, playedTile);
        if (side == 'R') layout.addRightTile(playedTile);
        else layout.addLeftTile(playedTile);

        return true;
    }

    // Step 3: Interaction loop for choosing a tile from the hand
    while (true) {
        int choice;
        std::cout << " >> Select tile index (1-" << m_hand.getSize() << "): ";
        std::cin >> choice;

        // Validate that the user input is a valid index within the hand
        if (choice < 1 || choice > m_hand.getSize()) {
            std::cout << "Invalid index. Please try again.\n";
            continue;
        }

        Tile t = m_hand.getTileAtIndex(choice - 1);
        bool fitL = canPlayOnSide(t, 'L', opponentPassed) && layout.isLegalMove(t, 'L');
        bool fitR = canPlayOnSide(t, 'R', opponentPassed) && layout.isLegalMove(t, 'R');

        // Validate that the chosen tile can actually be placed on the board
        if (!fitL && !fitR) {
            std::cout << "That tile cannot be played anywhere on the current layout.\n";
            continue;
        }

        char side = 'L';
        // If the tile is a double or the opponent passed, it might fit both ends
        if (fitL && fitR) {
            std::cout << " >> Play on (L)eft or (R)ight? ";
            std::cin >> side;
            side = toupper(side);
            if (side != 'L' && side != 'R') {
                std::cout << "Invalid side selection.\n";
                continue;
            }
        }
        else if (fitR) {
            // Tile only fits the right side
            side = 'R';
        }

        // Execute the play: remove from hand and place on the board
        Tile playedTile;
        m_hand.playTile(choice - 1, playedTile);
        if (side == 'L') layout.addLeftTile(playedTile);
        else layout.addRightTile(playedTile);

        return true;
    }
}