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
bool Human::playTurn(Layout& layout, Stock& stock, bool opponentPassed) {
    // Step 1: Identify all playable tiles in the current hand
    std::vector<int> playableIndices;

    // Run through the tiles in the Human's Hand
    for (int i = 0; i < m_hand.getSize(); ++i) {
        Tile tile = m_hand.getTileAtIndex(i);

        // Check if the tile is playable
        bool fitL = canPlayOnSide(tile, 'L', opponentPassed) && layout.isLegalMove(tile, 'L');
        bool fitR = canPlayOnSide(tile, 'R', opponentPassed) && layout.isLegalMove(tile, 'R');

        // If it fits, add it to the Human's playable universe
        if (fitL || fitR) { playableIndices.push_back(i); }
    }

    // Step 2: Handle the scenario where no moves are available in the initial hand
    if (playableIndices.empty()) {
        std::cout << " >> No moves available. Drawing from boneyard..." << std::endl;

        if (stock.isEmpty()) {
            std::cout << " >> Boneyard empty. You must pass." << std::endl;
            return false;
        }

        Tile drawn;
        stock.drawTile(drawn);
        m_hand.addTile(drawn);
        std::cout << " >> You drew: " << drawn.getLeftPips() << "-" << drawn.getRightPips() << std::endl;

        // Check if the newly drawn tile can be played immediately
        bool fitL = canPlayOnSide(drawn, 'L', opponentPassed) && layout.isLegalMove(drawn, 'L');
        bool fitR = canPlayOnSide(drawn, 'R', opponentPassed) && layout.isLegalMove(drawn, 'R');

        // Skip turn if tile doesn't fit
        if (!fitL && !fitR) {
            std::cout << " >> Drawn tile cannot be played. You pass." << std::endl;
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
            std::cout << " >> Tile must be played on RIGHT." << std::endl;
        }
        else {
            std::cout << " >> Tile must be played on LEFT." << std::endl;
        }

        // Create tile for 'drawn' tile to be copied into
        Tile played;

        // The drawn tile is at the very end of the hand
        // m_hand.getSize() represent the index of the drawn tile
        m_hand.playTile(m_hand.getSize() - 1, played);

        // Add the tile to the layout
        if (side == 'R') { 
            layout.addRightTile(played); 
        }
        else { 
            layout.addLeftTile(played); 
        }

        return true;
    }

    // Step 3: Interaction loop for choosing a tile from the hand
    while (true) {
        int choice;
        std::cout << " >> Select tile index (1-" << m_hand.getSize() << "): ";
        std::cin >> choice;

        // Validate that the user input is a valid index within the hand
        if (choice < 1 || choice > m_hand.getSize()) {
            std::cout << "Invalid index. Please try again." << std::endl;
            continue;
        }

        Tile tile = m_hand.getTileAtIndex(choice - 1);

        // Check which tiles are playable
        bool fitL = canPlayOnSide(tile, 'L', opponentPassed) && layout.isLegalMove(tile, 'L');
        bool fitR = canPlayOnSide(tile, 'R', opponentPassed) && layout.isLegalMove(tile, 'R');

        // Validate that the chosen tile can actually be placed on the board
        if (!fitL && !fitR) {
            std::cout << "That tile cannot be played anywhere on the current layout." << std::endl;
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
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                continue;
            }
        }
        else if (fitR) {
            // Tile only fits the right side
            side = 'R';
        }

        // Execute the play: remove from hand
        Tile playedTile;
        m_hand.playTile(choice - 1, playedTile);

        // Add the played tile to the layout
        if (side == 'L') {
            layout.addLeftTile(playedTile);
        }
        else {
            layout.addRightTile(playedTile);
        }

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
    // 1. You can ALWAYS play on your own side (Left)
    if (side == 'L') { return true; }

    // 2. Huamn can play on opponent's side (Right) ONLY if:
    //    a. The tile is a Double
    //    b. OR the opponent passed their turn
    if (tile.isDouble() || opponentPassed) { return true; }

    return false;
}