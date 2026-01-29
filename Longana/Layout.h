#ifndef LAYOUT_H
#define LAYOUT_H

#include <deque>
#include "Tile.h"
#include "Hand.h"

/**
 * Class Name: Layout
 * Purpose: Manages the layout of tiles on the board in a Longana game.
 */
class Layout {
public:
    /* --- Constructor --- */

    /// <summary>
    /// Default constructor that creates and initializes a Layout object.
    /// </summary>
    Layout() : m_layout() {}

    /* --- Destructor --- */

    /// <summary>
    /// Destructor for the Layout class. Releases resources and performs any 
    /// necessary cleanup when a Layout object is destroyed.
    /// </summary>
    ~Layout() {}

    /* --- Selectors --- */

    /// <summary>
    /// Returns the left-most pip value currently open on the layout.
    /// </summary>
    /// <returns>The outer pip of the first tile in the deque.</returns>
    inline int getLeftEdge() const { return m_layout.front().getLeftPips(); }

    /// <summary>
    /// Returns the right-most pip value currently open on the layout.
    /// </summary>
    /// <returns>The outer pip of the last tile in the deque.</returns>
    inline int getRightEdge() const { return m_layout.back().getRightPips(); }

    /// <summary>
    /// Checks whether the internal layout container is empty.
    /// </summary>
    /// <returns>true if the internal layout container contains no elements; otherwise false.</returns>
    inline bool isEmpty() const { return m_layout.empty(); }

    /* --- Mutators --- */

    /// <summary>
    /// Attempts to add the given tile to the left side of a layout or collection.
    /// </summary>
    /// <param name="tile">The tile to add, passed by const reference.</param>
    /// <returns>true if the tile was added successfully; false otherwise.</returns>
    bool addLeftTile(const Tile& tile);

    /// <summary>
    /// Attempts to add a tile to the right side of the container or board.
    /// </summary>
    /// <param name="tile">The tile to add, passed by const reference.</param>
    /// <returns>true if the tile was added successfully; false otherwise.</returns>
    bool addRightTile(const Tile& tile);

    /// <summary>
    /// Places the starting engine tile on the empty board.
    /// </summary>
    /// <param name="t">The engine tile to place.</param>
    inline void setEngine(const Tile& t) { m_layout.push_back(t); }

    /* --- Utility Functions --- */

    /// <summary>
    /// Checks whether placing the specified tile on the given side is a legal move according to the game's rules. 
    /// This member function is const and does not modify object state.
    /// </summary>
    /// <param name="tile">The tile to place (passed by const reference).</param>
    /// <param name="side">A character indicating which side to place the tile (for example, 'L'/'R' for left or right).</param>
    /// <returns>true if placing the tile on the specified side is a legal move; false otherwise.</returns>
    bool isLegalMove(const Tile& tile, char side) const;

    /// <summary>
    /// Determines the valid moves for the given hand without modifying the object.
    /// </summary>
    /// <param name="hand">The Hand to evaluate for valid moves.</param>
    bool findValidMoves(const Hand& hand) const;

    /// <summary>
    /// Displays the object's layout without modifying the object.
    /// </summary>
    void displayLayout() const;

private:
    std::deque<Tile> m_layout;

};

#endif LAYOUT_H