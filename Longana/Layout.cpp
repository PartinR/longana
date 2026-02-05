/************************************************************
 * Name:  Race Partin                                       *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include <iostream>
#include <string>
#include <sstream>
#include "Layout.h"
#include "Hand.h"
#include "Tile.h"

 /* *********************************************************************
 Function Name: addLeftTile
 Purpose: Adds a tile to the left end of the board, ensuring proper
          orientation so that touching pips match.
 Parameters:
          tile, a Tile object passed by const reference. The tile to add.
 Return Value: Boolean true if the tile was added; false otherwise.
 Algorithm:
          1. If the layout is empty, add the tile to the front.
          2. Retrieve the current leftmost pip value (leftEdge).
          3. If the tile's right side matches leftEdge, add it as is.
          4. If the tile's left side matches leftEdge, flip the tile
             so the right side matches, then add it.
          5. Return true if added, false if the move was illegal.
 Reference: None
 ********************************************************************* */
bool Layout::addLeftTile(const Tile& tile) {
    // Handle the case where this is the first tile (or engine) on the board
    if (isEmpty()) {
        m_layout.push_front(tile);
        return true;
    }

    int leftEdge = getLeftEdge();

    // Check if the tile fits without rotation
    if (tile.getRightPips() == leftEdge) {
        m_layout.push_front(tile);
        return true;
    }
    // Check if the tile fits if we flip it
    else if (tile.getLeftPips() == leftEdge) {
        Tile flippedTile = tile;
        flippedTile.flipTile();
        m_layout.push_front(flippedTile);
        return true;
    }

    return false;
}

/* *********************************************************************
Function Name: addRightTile
Purpose: Adds a tile to the right end of the board, ensuring proper
         orientation so that touching pips match.
Parameters:
         tile, a Tile object passed by const reference. The tile to add.
Return Value: Boolean true if the tile was added; false otherwise.
Algorithm:
         1. If the layout is empty, add the tile to the back.
         2. Retrieve the current rightmost pip value (rightEdge).
         3. If the tile's left side matches rightEdge, add it as is.
         4. If the tile's right side matches rightEdge, flip the tile
            so the left side matches, then add it.
         5. Return true if added, false if the move was illegal.
Reference: None
********************************************************************* */
bool Layout::addRightTile(const Tile& tile) {
    // Handle empty board initialization
    if (isEmpty()) {
        m_layout.push_back(tile);
        return true;
    }

    int rightEdge = getRightEdge();

    // Standard placement: left side of new tile touches right side of board
    if (tile.getLeftPips() == rightEdge) {
        m_layout.push_back(tile);
        return true;
    }
    // Rotation placement: flip tile so its left side matches the board
    else if (tile.getRightPips() == rightEdge) {
        Tile flippedTile = tile;
        flippedTile.flipTile();
        m_layout.push_back(flippedTile);
        return true;
    }

    return false;
}

/* *********************************************************************
Function Name: isLegalMove
Purpose: Checks if a tile can be placed on a specific side without
         modifying the board state.
Parameters:
         tile, a Tile object passed by const reference.
         side, a char indicating 'L' or 'R'.
Return Value: Boolean true if the move is legal, false otherwise.
Algorithm:
         1. If the board is empty, any tile is legal.
         2. If side is 'L', check if either side of the tile matches the left edge.
         3. If side is 'R', check if either side of the tile matches the right edge.
         4. Return the result of the check.
Reference: None
********************************************************************* */
bool Layout::isLegalMove(const Tile& tile, char side) const {
    // Rules usually allow any tile to start the layout if no engine is set
    if (isEmpty()) {
        return true;
    }

    if (side == 'L') {
        int leftEdge = getLeftEdge();
        return (tile.getLeftPips() == leftEdge || tile.getRightPips() == leftEdge);
    }
    else if (side == 'R') {
        int rightEdge = getRightEdge();
        return (tile.getLeftPips() == rightEdge || tile.getRightPips() == rightEdge);
    }

    return false;
}

/* *********************************************************************
Function Name: findValidMoves
Purpose: Determines if the provided hand contains at least one tile
         that can be played on the current layout.
Parameters:
         hand, a Hand object passed by const reference.
Return Value: Boolean true if a move exists, false otherwise.
Algorithm:
         1. If layout is empty, return true (any tile in hand can be played).
         2. Iterate through all tiles in the hand.
         3. For each tile, check if it can play on 'L' or 'R' using isLegalMove.
         4. If any legal move is found, return true immediately.
         5. If the loop completes, return false.
Reference: None
********************************************************************* */
bool Layout::findValidMoves(const Hand& hand) const {
    if (isEmpty()) {
        return true;
    }

    // Scan the entire hand for at least one playable tile
    for (int i = 0; i < hand.getSize(); i++) {
        Tile current = hand.getTileAtIndex(i);

        if (isLegalMove(current, 'L') || isLegalMove(current, 'R')) {
            return true;
        }
    }

    return false;
}

/* *********************************************************************
Function Name: displayLayout
Purpose: Prints the current sequence of tiles on the board to the console.
Parameters: None
Return Value: None (void)
Algorithm:
         1. Iterate through the m_layout deque from front to back.
         2. Print each tile formatted as "Left-Right".
Reference: None
********************************************************************* */
void Layout::displayLayout() const {
    // Print the chain of tiles in order from Left to Right
    for (const Tile& tile : m_layout) {
        std::cout << "[" << tile.getLeftPips() << "|" << tile.getRightPips() << "] ";
    }
}

std::string Layout::toString() const {
    std::string layoutStr = "L ";

    for (const Tile& tile : m_layout) {
        layoutStr += std::to_string(tile.getLeftPips()) + "-" + std::to_string(tile.getRightPips()) + " ";
    }

    layoutStr += "R";
    return layoutStr;
}

void Layout::loadFromString(const std::string& data) {
    m_layout.clear();
    
    std::stringstream ss(data);
    std::string token;

    while (ss << token) {
        size_t dashPos = token.find("-");

        if (dashPos != std::string::npos) {
            int left = std::stoi(token.substr(0, dashPos));
            int right = std::stoi(token.substr(dashPos + 1));

            m_layout.push_back(Tile(left, right));
        }
    }
}