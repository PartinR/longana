#ifndef STOCK_H
#define STOCK_H

/************************************************************
 * Name:  Race Benjamin Partin                              *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include <vector>
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
    Stock() : m_tiles() {
        for (int left = 0; left <= 6; ++left) {
            for (int right = left; right <= 6; ++right) {
                m_tiles.emplace_back(left, right);
            }
        }
    }

    /* --- Destructor --- */

    /* *********************************************************************
    Function Name: ~Stock
    Purpose: Destructor. Cleans up the Stock object upon destruction.
    Parameters: None
    Return Value: None
    Algorithm: Standard vector destructor handles memory cleanup automatically.
    Reference: None
    ********************************************************************* */
    ~Stock() {}

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
    Purpose: Removes the top tile from the stock and provides it to the caller.
    Parameters:
             destination, a Tile object passed by reference. This object is
                          updated with the values of the drawn tile.
    Return Value: true if a tile was successfully drawn, false if the stock was empty.
    Algorithm:
             1. Check if m_tiles is empty.
             2. If not empty, assign the last tile in the vector to destination.
             3. Remove the last tile from the vector using pop_back().
             4. Return true.
    Reference: None
    ********************************************************************* */
    bool drawTile(Tile& destination);

    /* *********************************************************************
    Function Name: removeSpecificTile
    Purpose: Searches the boneyard for a specific tile (the Engine) and
         removes it to prevent duplicate tiles on the board.
    Parameters: target, a Tile object passed by const reference.
    Return Value: true if found and removed, false otherwise.
    Algorithm:
         1. Loop through the m_tiles vector.
         2. Compare each tile to the target using the == operator.
         3. If a match is found, use m_tiles.erase() with the current iterator.
         4. Return true if removed, false if the tile wasn't in the stock.
    Reference: None
    ********************************************************************* */
    bool removeSpecificTile(const Tile& target);

    /* --- Utility Functions --- */

    /* *********************************************************************
    Function Name: shuffle
    Purpose: Randomizes the order of the tiles in the stock to ensure
             unpredictable dealing and drawing.
    Parameters: None
    Return Value: None (void)
    Algorithm:
             1. Use a random number generator (e.g., std::shuffle) combined
                with a random seed.
             2. Reorder the elements within the m_tiles vector.
    Reference: None
    ********************************************************************* */
    void shuffle();

    /* *********************************************************************
    Function Name: printStock
    Purpose: Displays all tiles currently in the boneyard. This is required
             by the project guidelines to verify game state correctness.
    Parameters: None
    Return Value: None (void)
    Algorithm:
             1. Iterate through the m_tiles vector.
             2. Print the string representation of each tile to the console.
    Reference: None
    ********************************************************************* */
    void printStock() const;

private:
    // A vector holding the pool of available tiles
    std::vector<Tile> m_tiles;

};

#endif