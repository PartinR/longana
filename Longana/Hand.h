#ifndef HAND_H
#define HAND_H

/************************************************************
 * Name:  Race Benjamin Partin                              *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include <vector>
#include <string>
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
    ~Hand() {}

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
    Purpose: Calculates the total score value of the hand. In Longana, this is
             typically the sum of all pips on the tiles remaining in the hand.
    Parameters: None
    Return Value: An integer representing the total pip sum of the hand.
    Algorithm:
             1. Initialize total to 0.
             2. Iterate through m_tiles.
             3. For each tile, add its pip sum to total.
             4. Return total.
    Reference: None
    ********************************************************************* */
    int getHandScore() const;

    /* --- Mutators --- */

    /* *********************************************************************
    Function Name: addTile
    Purpose: Adds a new tile to the player's hand (usually from drawing).
    Parameters:
             tile, a Tile object passed by const reference. The tile to add.
    Return Value: true if successful, false otherwise.
    Algorithm: Use std::vector::push_back to add the tile to m_tiles.
    Reference: None
    ********************************************************************* */
    bool addTile(const Tile& tile);

    /* *********************************************************************
    Function Name: playTile
    Purpose: Removes a specific tile from the hand to be played on the layout.
    Parameters:
             index, an integer passed by value. The index of the tile to remove.
             outTile, a Tile object passed by reference. This variable is updated
                      to hold the value of the tile being removed (so the caller knows what was played).
    Return Value: true if the index was valid and tile removed, false otherwise.
    Algorithm:
             1. Check if index is within valid bounds (0 to size-1).
             2. If valid, assign m_tiles[index] to outTile.
             3. Remove the tile from the vector using std::vector::erase.
             4. Return true.
    Reference: None
    ********************************************************************* */
    bool playTile(int index, Tile& outTile);

    void clearHand() { m_tiles.clear(); }

    void loadFromString(const std::string& data);

    /* --- Utility Functions --- */

    /* *********************************************************************
    Function Name: displayHand
    Purpose: Prints the visual representation of the hand to the console.
    Parameters: None
    Return Value: None (void)
    Algorithm:
             1. Iterate through the m_tiles vector.
             2. Print each tile in the format [Left|Right].
             3. Print newlines or spaces as necessary for formatting.
    Reference: None
    ********************************************************************* */
    void displayHand() const;

    std::string toString() const;

private:
    // A dynamic array (vector) storing the collection of Tile objects
    std::vector<Tile> m_tiles;

};

#endif