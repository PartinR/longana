/************************************************************
 * Name:  Race Partin                                       *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include <cctype>
#include <iostream>
#include <vector>

#include "Human.h"
#include "Layout.h"
#include "Stock.h"
#include "Tile.h"

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
bool Human::canPlayOnSide(const Tile& tile, char side, bool opponentPassed) const {
    // Doubles can be played on either side regardless of pass status
    if (tile.getLeftPips() == tile.getRightPips()) return true;

    // The Human can play on the Computer's side (R) only if the Computer passed
    if (opponentPassed) return true;

    // Standard rule: Humans play on the Left side of the engine
    return (side == 'L');
}