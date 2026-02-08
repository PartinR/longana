#ifndef HAND_H
#define HAND_H

/************************************************************
 * Name:  Race Partin                                       *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include <string>
#include <vector>

#include "Tile.h"

 /* *********************************************************************
 Class Name: Hand
 Purpose: Represents a player's hand in the Longana game. It manages a
          dynamic collection of Tile objects, allowing for adding tiles
          (drawing) and removing tiles (playing).
 ********************************************************************* */
class Hand {
public:
    /* --- Constructor --- */

    /* *********************************************************************
    Function Name: Hand
    Purpose: Default constructor. Initializes an empty hand for a player.
    Parameters: None
    Return Value: None
    Algorithm: Implicitly initializes the m_tiles vector to be empty.
    Reference: None
    ********************************************************************* */
    Hand() : m_tiles() {}

    /* --- Destructor --- */

    /* *********************************************************************
    Function Name: ~Hand
    Purpose: Destructor. Performs cleanup when a Hand object is destroyed.
    Parameters: None
    Return Value: None
    Algorithm: Standard vector destructor handles memory cleanup automatically.
    Reference: None
    ********************************************************************* */
    virtual ~Hand() {
        m_tiles.clear();
    }

    /* --- Selectors --- */

    /* *********************************************************************
    Function Name: getSize
    Purpose: To retrieve the current number of tiles in the hand.
    Parameters: None
    Return Value: An integer representing the count of tiles.
    Algorithm: Return m_tiles.size().
    Reference: None
    ********************************************************************* */
    inline int getSize() const { return static_cast<int>(m_tiles.size()); }

    /* *********************************************************************
    Function Name: isEmpty
    Purpose: Checks if the hand contains zero tiles.
    Parameters: None
    Return Value: true if the hand is empty, false otherwise.
    Algorithm: Return m_tiles.empty().
    Reference: None
    ********************************************************************* */
    inline bool isEmpty() const { return m_tiles.empty(); }

    /* *********************************************************************
    Function Name: getTileAtIndex
    Purpose: Retrieves a copy of a tile at a specific position in the hand.
            Used for inspecting tiles without removing them.
    Parameters:
            index, an integer passed by value. The position of the tile to retrieve.
    Return Value: A Tile object (by value).
    Algorithm: Return the element at m_tiles[index].
    Reference: None
    ********************************************************************* */
    inline Tile getTileAtIndex(int index) const { return m_tiles[index]; }

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
    int getHandScore() const;

    /* --- Mutators --- */

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
    bool addTile(const Tile& tile);

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
    bool playTile(int index, Tile& outTile);

    /* *********************************************************************
    Function Name: clearHand
    Purpose: To remove all tiles from the player's current hand, resetting
            the hand to an empty state. This is primarily used when
            re-initializing a hand during round transitions or loading.
    Parameters: None
    Return Value: None (void)
    Algorithm:
            1. Call the clear() method on the m_tiles vector.
            2. The vector's size is reduced to zero, and the memory
                management is handled by the standard library.
    Reference: None
    ********************************************************************* */
    void clearHand() { m_tiles.clear(); }

    /* --- Utility Functions --- */

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
    std::string toString() const;

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
    void loadFromString(const std::string& data);

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
    void displayHand() const;

private:
    // A dynamic array (vector) storing the collection of Tile objects
    std::vector<Tile> m_tiles;

};

#endif