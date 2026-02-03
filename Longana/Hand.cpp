/************************************************************
 * Name:  Race Benjamin Partin                              *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include <iostream>
#include <sstream>
#include <string>
#include "Hand.h"
#include "Tile.h"

 /* *********************************************************************
 Function Name: getHandScore
 Purpose: Calculates the total pip value of all tiles currently in the hand.
 Parameters: None
 Return Value: An integer representing the total pip sum.
 Algorithm:
          1. Initialize totalScore to 0.
          2. Iterate through each Tile object in the m_tiles vector.
          3. Add the result of the tile's getSum() method to totalScore.
          4. Return the final totalScore.
 Reference: None
 ********************************************************************* */
int Hand::getHandScore() const {
    int totalScore = 0;

    // Sum the pips of every tile held by the player
    for (const Tile& tile : m_tiles) {
        totalScore += tile.getSum();
    }

    return totalScore;
}

/* *********************************************************************
Function Name: addTile
Purpose: Adds a new tile to the player's collection (e.g., from a draw).
Parameters:
         tile, a Tile object passed by const reference. The tile to be added.
Return Value: Boolean true indicating the operation was successful.
Algorithm:
         1. Use push_back to append the provided tile to the m_tiles vector.
         2. Return true.
Reference: None
********************************************************************* */
bool Hand::addTile(const Tile& tile) {
    // Append the new tile to the end of the hand container
    m_tiles.push_back(tile);
    return true;
}

/* *********************************************************************
Function Name: playTile
Purpose: Removes a tile at a specific index from the hand so it can be
         placed on the layout.
Parameters:
         index, an integer passed by value. The position of the tile to remove.
         outTile, a Tile object passed by reference. Used to return the
                  data of the removed tile to the caller.
Return Value: Boolean true if the index was valid and tile removed; false otherwise.
Algorithm:
         1. Validate if the provided index is within the vector bounds.
         2. If out of bounds, return false.
         3. If valid, copy the tile at the index into outTile.
         4. Erase the tile from the vector using an iterator.
         5. Return true.
Reference: None
********************************************************************* */
bool Hand::playTile(int index, Tile& outTile) {
    // Verify the index is valid for the current hand size
    if (index < 0 || index >= static_cast<int>(m_tiles.size())) {
        return false;
    }
    else
    {
        // Copy the tile data before removing it from the container
        outTile = m_tiles[index];

        // Erase the tile using the vector's iterator-based erase method
        m_tiles.erase(m_tiles.begin() + index);

        return true;
    }
}

/* *********************************************************************
Function Name: displayHand
Purpose: Prints the contents of the hand to the standard output.
Parameters: None
Return Value: None (void)
Algorithm:
         1. Iterate through each tile in the hand.
         2. Print the left and right pips of each tile in a readable format.
         3. Print a newline at the end of the list.
Reference: None
********************************************************************* */
void Hand::displayHand() const {
    // Display each tile in the hand separated by spaces
    for (const Tile& tile : m_tiles) {
        std::cout << "[" << tile.getLeftPips() << "|" << tile.getRightPips() << "] ";
    }

    // End the line after all tiles are displayed
    std::cout << std::endl;
}

std::string Hand::toString() const {
    std::string handStr;

    // Concatenate the string representation of each tile in the hand
    for (const Tile& tile : m_tiles) {
        handStr += tile.toString() + " ";
    }

    return handStr;
}

void Hand::loadFromString(const std::string& data) {
    m_tiles.clear();
    std::stringstream ss(data);
    std::string token;

    while (ss >> token) {
        size_t dashPos = token.find("-");

        if (dashPos != std::string::npos) {
            int left = std::stoi(token.substr(0, dashPos));
            int right = std::stoi(token.substr(dashPos + 1));
            m_tiles.push_back(Tile(left, right));
        }
    }
}