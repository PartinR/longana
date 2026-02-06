/************************************************************
 * Name:  Race Partin                                       *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include <iostream>
#include <sstream>
#include <string>

#include "Hand.h"
#include "Layout.h"
#include "Tile.h"

/* *********************************************************************
Function Name: addLeftTile
Purpose: Adds a tile to the left side of the layout. This often involves
        flipping the tile if necessary to match the pips.
Parameters:
        tile, a Tile object passed by const reference. The tile to be added.
Return Value: true if the tile was added, false otherwise.
Algorithm:
        1. Push the tile to the front of the deque (m_layout).
        2. (Note: Logic to orient/flip the tile is usually handled prior
            to calling this or within the detailed implementation).
Reference: None
********************************************************************* */
bool Layout::addLeftTile(const Tile& tile) {
    // Handle empty board initialization
    if (isEmpty()) {
        m_layout.push_front(tile);
        return true;
    }

    int leftEdge = getLeftEdge();

    // Standard placement: right side of new tile touches left side of board
    if (tile.getRightPips() == leftEdge) {
        m_layout.push_front(tile);
        return true;
    }
    // Rotation placement: flip tile so its right side matches the board
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
Purpose: Adds a tile to the right side of the layout.
Parameters:
        tile, a Tile object passed by const reference. The tile to be added.
Return Value: true if the tile was added, false otherwise.
Algorithm:
        1. Push the tile to the back of the deque (m_layout).
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
Purpose: Scans a player's hand to see if *any* tile can be legally played
        on the current layout.
Parameters:
        hand, a Hand object passed by const reference.
Return Value: true if at least one legal move exists, false otherwise.
Algorithm:
        1. Iterate through every tile in the Hand.
        2. For each tile, check isLegalMove on 'L' and 'R'.
        3. If any check returns true, return true immediately.
        4. If loop finishes without success, return false.
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
Purpose: Prints the current state of the board to the console, showing
        the chain of tiles from left to right.
Parameters: None
Return Value: None (void)
Algorithm:
        1. Print "L".
        2. Iterate through m_layout deque from begin to end.
        3. Print each tile.
        4. Print "R".
Reference: None
********************************************************************* */
void Layout::displayLayout() const {
    // Print the chain of tiles in order from Left to Right
    for (const Tile& tile : m_layout) {
        std::cout << tile.getLeftPips() << "-" << tile.getRightPips() << " ";
    }
}

/* *********************************************************************
Function Name: toString
Purpose: Converts the current board layout into a serialized string format.
        This representation includes markers for the left and right ends
        to maintain board orientation during the save/load process.
Parameters: None
Return Value: A std::string representing the board (e.g., "L 6-6 6-1 1-0 R").
Algorithm:
        1. Initialize a result string with the left-end marker "L ".
        2. Iterate through each Tile in the m_layout deque from the
            front to the back.
        3. For each tile, convert the pip values to a "Left-Right "
            string format and append it to the result.
        4. Append the right-end marker "R" to indicate the end of the
            line of play.
        5. Return the completed string.
Reference: None
********************************************************************* */
std::string Layout::toString() const {
    std::string layoutStr = "L ";

    for (const Tile& tile : m_layout) {
        layoutStr += std::to_string(tile.getLeftPips()) + "-" + std::to_string(tile.getRightPips()) + " ";
    }

    layoutStr += "R";
    return layoutStr;
}

/* *********************************************************************
Function Name: loadFromString
Purpose: Reconstructs the board layout by parsing a space-delimited string
        of tiles. Used primarily when restoring the game board from a
        saved state.
Parameters:
        data, a const std::string passed by reference. The raw string
            containing board data (e.g., "L 6-6 6-1 1-0 R").
Return Value: None (void)
Algorithm:
        1. Clear any existing tiles from the m_layout deque.
        2. Wrap the input string in a std::stringstream for easy tokenization.
        3. While there are tokens in the stream:
            a. Skip tokens that are strictly markers (like "L" or "R").
            b. Locate the position of the dash ('-') within the tile token.
            c. If found, extract the substring before the dash as the 'left' value.
            d. Extract the substring after the dash as the 'right' value.
            e. Convert these substrings to integers using std::stoi.
            f. Construct a new Tile object and push it to the back of
                the m_layout deque to maintain the sequence.
Reference: None
********************************************************************* */
void Layout::loadFromString(const std::string& data) {
    // Empty the layout to prepare for new data from the save file
    m_layout.clear();
    
    // Use stringstream to split the string into individual "6-6" tokens
    std::stringstream ss(data);
    std::string token;

    while (ss >> token) {
        if (token == "L" || token == "R") { continue; }

        size_t dashPos = token.find("-");

        // If there exists a dashPos, execute
        if (dashPos != std::string::npos) {
            // Extract substrings and convert to integers
            int left = std::stoi(token.substr(0, dashPos));
            int right = std::stoi(token.substr(dashPos + 1));

            // Create the Tile and store it to the layout
            m_layout.push_back(Tile(left, right));
        }
    }
}