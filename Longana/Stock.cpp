/************************************************************
 * Name:  Race Partin                                       *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include <random>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include "Stock.h"
#include "Tile.h"

 /* *********************************************************************
 Function Name: drawTile
 Purpose: To retrieve the next available tile from the boneyard and
          remove it from the stock collection.
 Parameters:
          destination, a Tile object passed by reference. This object
                       is updated with the data from the drawn tile.
 Return Value: Boolean true if a tile was available to be drawn, false
               if the stock was empty.
 Algorithm:
          1. Check if the m_tiles vector is empty.
          2. If empty, return false.
          3. If not empty, assign the last element of the vector to
             the destination parameter.
          4. Remove that last element from the vector using pop_back().
          5. Return true.
 Reference: None
 ********************************************************************* */
bool Stock::drawTile(Tile& destination) {
    // Verify that there are tiles left in the boneyard to draw
    if (m_tiles.empty()) {
        return false;
    }
    else {
        // Treat the end of the vector as the "top" of the pile for efficiency
        destination = m_tiles.back();
        m_tiles.pop_back();
        return true;
    }
}

/* *********************************************************************
Function Name: shuffle
Purpose: To randomize the order of the tiles in the boneyard using a
         high-quality pseudo-random number generator.
Parameters: None
Return Value: None (void)
Algorithm:
         1. Instantiate a random_device to provide a seed.
         2. Initialize a Mersenne Twister engine (mt19937) with that seed.
         3. Call std::shuffle on the m_tiles vector from beginning to end
            using the engine as the source of randomness.
Reference: C++ Standard Library Documentation for std::shuffle
********************************************************************* */
void Stock::shuffle() {
    // Seed the generator with a non-deterministic random device
    std::random_device rd;
    std::mt19937 g(rd());

    // Randomize the internal sequence of tiles
    std::shuffle(m_tiles.begin(), m_tiles.end(), g);
}

/* *********************************************************************
Function Name: printStock
Purpose: To display the current contents of the boneyard to the console.
         This is essential for verifying game state during a demonstration.
Parameters: None
Return Value: None (void)
Algorithm:
         1. Check if the stock is empty; if so, print a status message.
         2. Iterate through each tile in the m_tiles vector.
         3. Print the left and right pips of each tile in a readable format.
         4. Output a newline at the end.
Reference: None
********************************************************************* */
void Stock::printStock() const {
    // Check for empty state before attempting to iterate
    if (m_tiles.empty()) {
        std::cout << "The boneyard is empty." << std::endl;
        return;
    }

    // Loop through the vector and display the tile data
    for (const auto& t : m_tiles) {
        std::cout << t.getLeftPips() << "-" << t.getRightPips() << " ";
    }

    std::cout << std::endl;
}

/* *********************************************************************
Function Name: removeSpecificTile
Purpose: Searches the boneyard for a specific tile and removes it.
         Used to ensure the Engine is not duplicated if it starts in the stock.
Parameters:
         target, a Tile object passed by const reference.
Return Value: true if found and removed, false otherwise.
Algorithm:
         1. Iterate through the m_tiles vector using an index.
         2. Compare each tile to the target tile using the == operator.
         3. If a match is found, use the erase method with an iterator
            at the current index to remove the tile.
         4. Return true if removed; return false if the loop completes
            without finding the target.
Reference: None
********************************************************************* */
bool Stock::removeSpecificTile(const Tile& target) {
    for (int i = 0; i < m_tiles.size(); ++i) {
        if (m_tiles[i] == target) {
            m_tiles.erase(m_tiles.begin() + i);
            return true;
        }
    }
    return false;
}

std::string Stock::toString() const {
    std::string boneyard;

    for (const auto& tile : m_tiles) {
        boneyard += std::to_string(tile.getLeftPips()) + "-" + std::to_string(tile.getRightPips()) + " ";
    }

    return boneyard;
}

void Stock::loadFromString(const std::string& data) {
    m_tiles.clear();

    std::stringstream ss(data);
    std::string token;

    while (ss << token) {
        size_t dashPos = token.find("-");

        if (dashPos != std::string::npos) {
            int left = std::stoi(token.substr(0, dashPos));
            int right = std::stoi(token.substr(dashPos + 1));

            m_tiles.push_back(Tile(left, right));
        }
    }
}