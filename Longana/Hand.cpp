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
Purpose: Adds a new tile to the player's hand (e.g., from a draw).
Parameters:
        tile, a Tile object passed by const reference. The tile to be added.
Return Value: Boolean true indicating the operation was successful.
Algorithm:
        1. Use push_back to append the provided tile to the m_tiles vector.
        2. Return true.
Reference: None
********************************************************************* */
bool Hand::addTile(const Tile& tile) {
    // Append the new tile to the end of the hand vector
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
        std::cout << tile.getLeftPips() << "-" << tile.getRightPips() << " ";
    }

    // End the line after all tiles are displayed
    std::cout << std::endl;
}

/* *********************************************************************
Function Name: toString
Purpose: Converts the entire collection of tiles in the hand into a
        single string representation.
Parameters: None
Return Value: A std::string containing all tiles, separated by spaces.
Algorithm:
        1. Initialize an empty string named handStr.
        2. Iterate through each Tile object in the m_tiles vector.
        3. Call the toString() method of each tile (e.g., producing "6-6").
        4. Append the tile's string and a trailing space to handStr.
        5. Return the resulting concatenated string.
Reference: None
********************************************************************* */
std::string Hand::toString() const {
    std::string handStr;

    // Concatenate the string representation of each tile in the hand
    for (const Tile& tile : m_tiles) {
        handStr += tile.toString() + " ";
    }

    return handStr;
}

/* *********************************************************************
Function Name: loadFromString
Purpose: Populates the hand by parsing a space-delimited string of tiles.
        Used primarily when loading a saved game state.
Parameters:
        data, a const std::string passed by reference. The raw string
            containing tile data (e.g., "6-6 1-0 4-2").
Return Value: None (void)
Algorithm:
        1. Clear any existing tiles from the m_tiles vector.
        2. Wrap the input string in a std::stringstream for easy tokenization.
        3. While there are tokens (individual tiles) in the stream:
            a. Locate the position of the dash ('-') within the token.
            b. If found, extract the substring before the dash as the 'left' value.
            c. Extract the substring after the dash as the 'right' value.
            d. Convert these substrings to integers using std::stoi.
            e. Construct a new Tile object and push it into the m_tiles vector.
Reference: None
********************************************************************* */
void Hand::loadFromString(const std::string& data) {
    // Empty the hand to prepare for new data from the save file
    m_tiles.clear();

    // Use stringstream to split the string into individual "6-6" tokens
    std::stringstream ss(data);
    std::string token;

    while (ss >> token) {
        size_t dashPos = token.find("-");

        // If there exists a dashPos, execute
        if (dashPos != std::string::npos) {
            // Extract substrings and convert to integers
            int left = std::stoi(token.substr(0, dashPos));
            int right = std::stoi(token.substr(dashPos + 1));

            // Create the Tile and store it in the hand
            m_tiles.push_back(Tile(left, right));
        }
    }
}