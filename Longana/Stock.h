#ifndef STOCK_H
#define STOCK_H

/************************************************************
 * Name:  Race Partin                                       *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include <vector>
#include <string>
#include "Tile.h"

/* *********************************************************************
Class Name: Stock
Purpose: Represents the 'Boneyard' in a Longana game. This class manages
        the pool of available domino tiles, including their initial
        generation (a standard double-six set), shuffling, and the
        mechanism for players to draw tiles during a round.
********************************************************************* */
class Stock {
public:

    /* --- Constructor --- */

    /* *********************************************************************
    Function Name: Stock
    Purpose: Default constructor. Initializes a complete double-six domino set.
    Parameters: None
    Return Value: None
    Algorithm:
             1. Clear the m_tiles vector.
             2. Use a nested loop to iterate through pip values 0 to 6.
             3. Generate unique pairs (left, right) where right >= left to
                avoid duplicate tiles (e.g., [1|2] and [2|1] are one tile).
             4. Store each generated Tile in the m_tiles vector.
    Reference: None
    ********************************************************************* */
    Stock() { initializeFullSet(); }

    /* --- Destructor --- */

    /* *********************************************************************
    Function Name: ~Stock
    Purpose: Destructor. Cleans up the Stock object upon destruction.
    Parameters: None
    Return Value: None
    Algorithm: Standard vector destructor handles memory cleanup automatically.
    Reference: None
    ********************************************************************* */
    ~Stock() = default;

    /* --- Selectors --- */

    /* *********************************************************************
    Function Name: getSize
    Purpose: To get the current count of tiles remaining in the boneyard.
    Parameters: None
    Return Value: An integer representing the number of tiles available.
    Algorithm: Return static_cast<int>(m_tiles.size()).
    Reference: None
    ********************************************************************* */
    inline int getSize() const { return static_cast<int>(m_tiles.size()); }

    /* *********************************************************************
    Function Name: isEmpty
    Purpose: Checks if the boneyard has run out of tiles.
    Parameters: None
    Return Value: true if empty, false otherwise.
    Algorithm: Return m_tiles.empty().
    Reference: None
    ********************************************************************* */
    inline bool isEmpty() const { return m_tiles.empty(); }

    /* --- Mutators --- */

    /* *********************************************************************
    Function Name: drawTile
    Purpose: To retrieve the next available tile from the boneyard and
            remove it from the stock collection.
    Parameters:
            destination, a Tile object passed by reference. This object
                is updated with the data from the drawn tile.
    Return Value:
            Boolean true if a tile was available to be drawn, false
                if the stock was empty.
    Algorithm:
            1. Check if the m_tiles vector is empty.
            2. If empty, return false.
            3. If not empty, assign the first element of the vector to
                the destination parameter.
            4. Remove that first element from the vector using erase(m_tiles.begin()).
            5. Return true.
    Reference: None
    ********************************************************************* */
    bool drawTile(Tile& destination);

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
    bool removeSpecificTile(const Tile& target);

    /* --- Utility Functions --- */

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
    void shuffle();

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
    void printStock() const;

    /* *********************************************************************
    Function Name: toString
    Purpose: Converts the boneyard tiles into a single space-separated string.
    Parameters: None
    Return Value: A std::string containing all tiles (e.g., "6-6 5-4").
    Algorithm:
            1. Iterate through each tile in m_tiles.
            2. Append the tile's pip string and a space to a result string.
            3. Return the result.
    ********************************************************************* */
    std::string toString() const;

    /* *********************************************************************
    Function Name: loadFromString
    Purpose: Reconstructs the boneyard from a saved string state.
    Parameters:
            data, a const std::string reference containing tile pips.
    Return Value: None (void)
    Algorithm:
            1. Clear the current m_tiles vector.
            2. Use stringstream to tokenize the input by spaces.
            3. For each token, find the dash and parse the left/right integers.
            4. Push a new Tile object onto the vector.
    ********************************************************************* */
    void loadFromString(const std::string& data);

    /* *********************************************************************
    Function Name: initializeFullSet
    Purpose: Generates a standard double-six domino set. This function ensures
            the stock is reset to a full, starting state for a new round.
    Parameters: None
    Return Value: None (void)
    Algorithm:
            1. Clear any existing tiles from the m_tiles vector to prevent
                duplicates or carry-over from previous rounds.
            2. Use a nested for-loop where the outer index 'left' represents
                the first side and the inner index 'right' represents the second.
            3. Start the inner loop at 'left' (right = left) to ensure only unique
                pairs are created (e.g., creating 1-2 but skipping 2-1).
            4. Instantiate a Tile object for each pair and add it to the
                m_tiles container.
    Reference: None
    ********************************************************************* */
    void initializeFullSet();

private:
    // A vector holding the pool of available tiles
    std::vector<Tile> m_tiles;

};

#endif