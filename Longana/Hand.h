#ifndef HAND_H
#define HAND_H

#include <vector>
#include "Tile.h"

/**
 * Class Name: Hand
 * Purpose: Represents a player's hand in a Longana game, managing the collection of tiles held by the player.
 */
class Hand {
public:
    /* --- Constructor --- */
    Hand();

    /* --- Destructor --- */
    ~Hand() {}

    /* --- Selectors --- */


    /* --- Mutators --- */

    /// <summary>
    /// Adds a tile to a collection or board.
    /// </summary>
    /// <param name="tile">The Tile to add (passed by const reference).</param>
    /// <returns>true if the tile was added successfully; false otherwise.</returns>
    bool addTile(const Tile& tile);

    /// <summary>
    /// Attempts to remove the specified tile.
    /// </summary>
    /// <param name="tile">The tile to remove.</param>
    /// <returns>true if the tile was successfully removed; false otherwise.</returns>
    bool removeTile(const Tile& tile);

    /* --- Utility Functions --- */

    /// <summary>
    /// Displays the object's hand without modifying the object.
    /// </summary>
    void displayHand() const;

private:
    std::vector<Tile> m_tiles;

};

#endif