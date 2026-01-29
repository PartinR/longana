#ifndef LAYOUT_H
#define LAYOUT_H

/************************************************************
 * Name:  Race Benjamin Partin                              *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include <deque>
#include "Tile.h"
#include "Hand.h"

 /* *********************************************************************
 Class Name: Layout
 Purpose: Manages the central game board (the line of play) in Longana.
          It utilizes a double-ended queue (deque) to allow efficient
          addition of tiles to both the left and right ends of the layout.
 ********************************************************************* */
class Layout {
public:
    /* --- Constructor --- */

    /* *********************************************************************
    Function Name: Layout
    Purpose: Default constructor. Initializes an empty layout object ready for
             the start of a round.
    Parameters: None
    Return Value: None
    Algorithm: Implicitly initializes the m_layout deque to be empty.
    Reference: None
    ********************************************************************* */
    Layout() : m_layout() {}

    /* --- Destructor --- */

    /* *********************************************************************
    Function Name: ~Layout
    Purpose: Destructor. Releases resources when a Layout object is destroyed.
    Parameters: None
    Return Value: None
    Algorithm: Standard deque destructor handles memory cleanup automatically.
    Reference: None
    ********************************************************************* */
    ~Layout() {}

    /* --- Selectors --- */

    /* *********************************************************************
    Function Name: getLeftEdge
    Purpose: Retrieves the open pip value on the extreme left end of the layout.
             Used to determine if a tile can be played on the left side.
    Parameters: None
    Return Value: An integer representing the pip value of the exposed edge.
    Algorithm: Access the front tile of the deque and return its left pip value.
    Reference: None
    ********************************************************************* */
    inline int getLeftEdge() const { return m_layout.front().getLeftPips(); }

    /* *********************************************************************
    Function Name: getRightEdge
    Purpose: Retrieves the open pip value on the extreme right end of the layout.
             Used to determine if a tile can be played on the right side.
    Parameters: None
    Return Value: An integer representing the pip value of the exposed edge.
    Algorithm: Access the back tile of the deque and return its right pip value.
    Reference: None
    ********************************************************************* */
    inline int getRightEdge() const { return m_layout.back().getRightPips(); }

    /* *********************************************************************
    Function Name: isEmpty
    Purpose: Checks if the layout currently has any tiles placed on it.
    Parameters: None
    Return Value: true if the layout is empty, false otherwise.
    Algorithm: Return m_layout.empty().
    Reference: None
    ********************************************************************* */
    inline bool isEmpty() const { return m_layout.empty(); }

    /* --- Mutators --- */

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
    bool addLeftTile(const Tile& tile);

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
    bool addRightTile(const Tile& tile);

    /* *********************************************************************
    Function Name: setEngine
    Purpose: Places the initial Engine tile (the starting double) onto the
             empty board to begin the round.
    Parameters:
             t, a Tile object passed by const reference. The engine tile.
    Return Value: None
    Algorithm: Push the engine tile into the empty deque.
    Reference: None
    ********************************************************************* */
    inline void setEngine(const Tile& t) { m_layout.push_back(t); }

    /* --- Utility Functions --- */

    /* *********************************************************************
    Function Name: isLegalMove
    Purpose: Determines if a specific tile can be legally placed on a specific
             side of the board.
    Parameters:
             tile, a Tile object passed by const reference. The tile to check.
             side, a char passed by value. 'L' for Left, 'R' for Right.
    Return Value: true if the move matches the pips, false otherwise.
    Algorithm:
             1. If side is 'L', compare tile pips to getLeftEdge().
             2. If side is 'R', compare tile pips to getRightEdge().
             3. Return true if a match is found (considering both orientations).
    Reference: None
    ********************************************************************* */
    bool isLegalMove(const Tile& tile, char side) const;

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
    bool findValidMoves(const Hand& hand) const;

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
    void displayLayout() const;

private:
    // A double-ended queue to store the line of tiles
    std::deque<Tile> m_layout;

};

#endif