#ifndef LAYOUT_H
#define LAYOUT_H

/************************************************************
 * Name:  Race Partin                                       *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include <deque>
#include <string>
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
    ~Layout() = default;

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
    inline void setEngine(const Tile& tile) { m_layout.push_back(tile); }

    /* *********************************************************************
    Function Name: clearLayout
    Purpose: To remove all tiles from the current game layout, resetting
            the board to an empty state. This is typically used when
            starting a new round or re-initializing the game state.
    Parameters: None
    Return Value: None (void)
    Algorithm:
            1. Call the clear() method on the m_layout vector (or container).
            2. The container's size is reduced to zero, and memory is
                managed by the standard library.
    Reference: None
    ********************************************************************* */
    inline void clearLayout() { m_layout.clear(); }

    /* --- Utility Functions --- */

    /* *********************************************************************
    Function Name: isLegalMove
    Purpose: Checks if a tile can be placed on a specific side without
            modifying the board state.
    Parameters:
            tile, a Tile object passed by const reference.
            side, a char indicating 'L' or 'R'.
    Return Value: Boolean true if the move is legal, false otherwise.
    Algorithm:
            1. If the board is empty, any tile is legal.
            2. If side is 'L', check if either side of the tile matches the left edge.
            3. If side is 'R', check if either side of the tile matches the right edge.
            4. Return the result of the check.
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
             1. Iterate through m_layout deque from begin to end.
             2. Print each tile.
    Reference: None
    ********************************************************************* */
    void displayLayout() const;

    /* *********************************************************************
    Function Name: toString
    Purpose: Converts the current board layout into a serialized string format.
            This representation includes markers for the left and right ends
            to maintain board orientation during the save/load process.
    Parameters: None
    Return Value: A std::string representing the board (e.g., "L 6-6 6-1 1-0 R").
    Algorithm:
            1. Initialize a result string with the left-end marker "L ".
            2. Iterate through each Tile in the m_layout deque from the
                front to the back.
            3. For each tile, convert the pip values to a "Left-Right "
                string format and append it to the result.
            4. Append the right-end marker "R" to indicate the end of the
                line of play.
            5. Return the completed string.
    Reference: None
    ********************************************************************* */
    std::string toString() const;

    /* *********************************************************************
    Function Name: loadFromString
    Purpose: Reconstructs the board layout by parsing a space-delimited string
            of tiles. Used primarily when restoring the game board from a
            saved state.
    Parameters:
            data, a const std::string passed by reference. The raw string
                containing board data (e.g., "L 6-6 6-1 1-0 R").
    Return Value: None (void)
    lgorithm:
            1. Clear any existing tiles from the m_layout deque.
            2. Wrap the input string in a std::stringstream for easy tokenization.
            3. While there are tokens in the stream:
                a. Skip tokens that are strictly markers (like "L" or "R").
                b. Locate the position of the dash ('-') within the tile token.
                c. If found, extract the substring before the dash as the 'left' value.
                d. Extract the substring after the dash as the 'right' value.
                e. Convert these substrings to integers using std::stoi.
                f. Construct a new Tile object and push it to the back of
                    the m_layout deque to maintain the sequence.
    Reference: None
    ********************************************************************* */
    void loadFromString(const std::string& data);

private:
    // A double-ended queue to store the line of tiles
    std::deque<Tile> m_layout;

};

#endif