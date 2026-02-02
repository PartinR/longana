#ifndef TILE_H
#define TILE_H

/************************************************************
 * Name:  Race Benjamin Partin                              *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include <string>

 /* *********************************************************************
 Class Name: Tile
 Purpose: Models a single domino tile used in the Longana game. Each tile
          contains two sides, referred to as "left" and "right" pips,
          ranging from 0 to 6. This class provides the fundamental data
          structure for the game's logic.
 ********************************************************************* */
class Tile {
public:
    /* --- Constructors --- */

    /* *********************************************************************
    Function Name: Tile
    Purpose: Default constructor. Initializes a blank tile with zero pips
             on both sides.
    Parameters: None
    Return Value: None
    Algorithm:
             1. Set m_left_pips to 0.
             2. Set m_right_pips to 0.
    Reference: None
    ********************************************************************* */
    Tile() : m_left_pips(0), m_right_pips(0) {}

    /* *********************************************************************
    Function Name: Tile
    Purpose: Overloaded constructor to create a tile with specific pip values.
    Parameters:
             left, an integer passed by value. Represents the pips on the
                   left side.
             right, an integer passed by value. Represents the pips on the
                    right side.
    Return Value: None
    Algorithm:
             1. Assign left parameter to m_left_pips.
             2. Assign right parameter to m_right_pips.
    Reference: None
    ********************************************************************* */
    Tile(int left, int right);

    /* --- Destructor --- */

    /* *********************************************************************
    Function Name: ~Tile
    Purpose: Destructor for the Tile class. Performs no special cleanup as
             the class does not use dynamic memory.
    Parameters: None
    Return Value: None
    Algorithm: Standard object destruction.
    Reference: None
    ********************************************************************* */
    ~Tile() {}

    /* --- Selectors --- */

    /* *********************************************************************
    Function Name: getLeftPips
    Purpose: Retrieves the number of pips on the left side of the tile.
    Parameters: None
    Return Value: An integer representing the left pips.
    Algorithm: Return m_left_pips.
    Reference: None
    ********************************************************************* */
    inline int getLeftPips() const { return m_left_pips; }

    /* *********************************************************************
    Function Name: getRightPips
    Purpose: Retrieves the number of pips on the right side of the tile.
    Parameters: None
    Return Value: An integer representing the right pips.
    Algorithm: Return m_right_pips.
    Reference: None
    ********************************************************************* */
    inline int getRightPips() const { return m_right_pips; }

    /* *********************************************************************
    Function Name: getSum
    Purpose: Calculates the total pip value of the tile.
    Parameters: None
    Return Value: An integer sum of left and right pips.
    Algorithm: Add m_left_pips and m_right_pips and return the result.
    Reference: None
    ********************************************************************* */
    inline int getSum() const { return m_left_pips + m_right_pips; }

    /* *********************************************************************
    Function Name: isDouble
    Purpose: Determines if the tile is a "double" (both sides equal).
    Parameters: None
    Return Value: true if the pips match, false otherwise.
    Algorithm: Compare m_left_pips to m_right_pips.
    Reference: None
    ********************************************************************* */
    inline bool isDouble() const { return m_left_pips == m_right_pips; }

    /* *********************************************************************
    Function Name: operator==
    Purpose: Overloads the equality operator to compare two Tile objects.
             Matches tiles regardless of orientation (e.g., [1|2] == [2|1]).
    Parameters:
             other, a Tile object passed by const reference.
    Return Value: true if the tiles represent the same pair of pips, false otherwise.
    Algorithm:
             1. Check if left pips match other's left and right pips match other's right.
             2. Check if left pips match other's right and right pips match other's left.
             3. Return true if either condition is true.
    Reference: None
    ********************************************************************* */
    bool operator==(const Tile& other) const;

    /* --- Mutators --- */

    /* *********************************************************************
    Function Name: setLeftPips
    Purpose: Updates the number of pips on the left side of the tile.
    Parameters:
             pips, an integer passed by value. The new pip count.
    Return Value: true if the update was valid (within 0-6), false otherwise.
    Algorithm:
             1. Verify pips is between MIN_PIPS and MAX_PIPS.
             2. If valid, update m_left_pips and return true.
    Reference: None
    ********************************************************************* */
    bool setLeftPips(int pips);

    /* *********************************************************************
    Function Name: setRightPips
    Purpose: Updates the number of pips on the right side of the tile.
    Parameters:
             pips, an integer passed by value. The new pip count.
    Return Value: true if the update was valid (within 0-6), false otherwise.
    Algorithm:
             1. Verify pips is between MIN_PIPS and MAX_PIPS.
             2. If valid, update m_right_pips and return true.
    Reference: None
    ********************************************************************* */
    bool setRightPips(int pips);

    /* --- Utility Functions --- */

    /* *********************************************************************
    Function Name: flipTile
    Purpose: Reverses the orientation of the tile, swapping left and right pips.
    Parameters: None
    Return Value: None (void)
    Algorithm:
             1. Store m_left_pips in a temporary variable.
             2. Assign m_right_pips to m_left_pips.
             3. Assign the temporary variable to m_right_pips.
    Reference: None
    ********************************************************************* */
    void flipTile();

    std::string toString() const;

private:
    /* --- Constants --- */
    static const int MIN_PIPS = 0;
    static const int MAX_PIPS = 6;

    /* --- Variables --- */
    int m_left_pips;
    int m_right_pips;
};

#endif