#ifndef STOCK_H
#define STOCK_H

#include <vector>
#include "Tile.h"

/**
 * Class Name: Stock
 * Purpose: Handles the 'Boneyard' or stock of domino tiles in a Longana game.
 * Handles tile creation, shuffling, and drawing tiles.
 */
class Stock {
public:
    /* --- Constructor --- */

    /// <summary>
    /// Default constructs a Stock object.
    /// </summary>
    Stock() : m_tiles() {
        // Create all unique tiles for a standard double-six domino set.
        for (int left = 0; left <= 6; ++left) {
            for (int right = left; right <= 6; ++right) {
                m_tiles.emplace_back(left, right);
            }
        }
    }

    /* --- Destructor --- */

    /// <summary>
    /// Destructor for the Stock class. Performs cleanup and releases any resources when a Stock object is destroyed.
    /// </summary>
    ~Stock() {}

    /* --- Selectors --- */

    /// <summary>
    /// Returns the number of tiles stored in the object.
    /// </summary>
    /// <returns>The number of elements in m_tiles, returned as an int. The method is const and does not modify the object.</returns>
    inline int getSize() const { return m_tiles.size(); }

    /// <summary>
    /// Checks whether the object's tile container is empty.
    /// </summary>
    /// <returns>true if the underlying tile container (m_tiles) contains no elements; otherwise false.</returns>
    inline bool isEmpty() const { return m_tiles.empty(); }

    /* --- Mutators --- */

    /// <summary>
    /// Renders or copies a tile into the provided destination object.
    /// </summary>
    /// <param name="destination">A reference to a Tile that will be populated or updated with the drawn tile data.</param>
    /// <returns>true if the tile was drawn successfully; false otherwise.</returns>
    bool drawTile(Tile& destination);

    /* --- Utility Functions --- */

    /// <summary>
    /// Performs a shuffling operation.
    /// </summary>
    void shuffle();

private:
    std::vector<Tile> m_tiles;

};

#endif