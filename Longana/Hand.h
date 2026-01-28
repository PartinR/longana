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

    /// <summary>
    /// Default constructor for the Hand class that initializes a Hand object.
    /// </summary>
    Hand() : m_tiles() {}

    /* --- Destructor --- */

    /// <summary>
    /// Destructor for the Hand class. Performs cleanup when a Hand object is destroyed.
    /// </summary>
    ~Hand() {}

    /* --- Selectors --- */

    /// <summary>
    /// Inline const member function that returns the number of tiles stored in m_tiles.
    /// </summary>
    /// <returns>The number of tiles as an int.</returns>
    inline int getSize() const { return m_tiles.size(); }

    /// <summary>
    /// Returns a copy of the tile at the specified index.
    /// </summary>
    /// <param name="index">Zero-based index of the tile to retrieve. Behavior is undefined if the index is out of range.</param>
    /// <returns>A Tile object at the given index (returned by value).</returns>
    inline Tile getTileAtIndex(int index) const { return m_tiles[index]; }

    /// <summary>
    /// Returns the score of this hand.
    /// </summary>
    /// <returns>The hand's score as an integer.</returns>
    int getHandScore() const;

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
    bool playTile(int index, Tile& outTile);

    /* --- Utility Functions --- */

    /// <summary>
    /// Displays the object's hand without modifying the object.
    /// </summary>
    void displayHand() const;

private:
    std::vector<Tile> m_tiles;

};

#endif