#ifndef TILE_H
#define TILE_H

/************************************************************
 * Name:  Race Partin                                       *
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
    Purpose: Overloaded constructor to create a tile with specific pip values,
            validating that they fall within the legal range of 0 to 6.
    Parameters:
            left, an integer passed by value. The pips for the left side.
            right, an integer passed by value. The pips for the right side.
    Return Value: None
    Algorithm:
            1. Check if the 'left' parameter is between MIN_PIPS and MAX_PIPS.
            2. If valid, assign to m_left_pips; otherwise, default to 0.
            3. Check if the 'right' parameter is between MIN_PIPS and MAX_PIPS.
            4. If valid, assign to m_right_pips; otherwise, default to 0.
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
    ~Tile() = default;

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
    Purpose: Determines if two tiles are identical, accounting for the fact
            that a domino can be oriented in two ways.
    Parameters:
            other, a constant Tile reference. The tile to compare against.
    Return Value: Boolean true if the tiles are the same pair, false otherwise.
    Algorithm:
            1. Compare this tile's left to other's left AND this tile's right to other's right.
            2. Compare this tile's left to other's right AND this tile's right to other's left.
            3. Return true if either the standard match or the flipped match is true.
    Reference: None
    ******************************************************************** */
    bool operator==(const Tile& other) const;

    /* --- Mutators --- */

    /* *********************************************************************
    Function Name: setLeftPips
    Purpose: Safely updates the pip value on the left side of the tile.
    Parameters:
            pips, an integer passed by value.
    Return Value: Boolean true if the update was valid and successful, else false.
    Algorithm:
            1. Check if the pips value is outside the 0-6 range.
            2. If out of range, return false immediately.
            3. Otherwise, assign the value to m_left_pips and return true.
    Reference: None
    ********************************************************************* */
    bool setLeftPips(int pips);

    /* *********************************************************************
    Function Name: setRightPips
    Purpose: Safely updates the pip value on the right side of the tile.
    Parameters:
            pips, an integer passed by value.
    Return Value: Boolean true if the update was valid and successful, else false.
    Algorithm:
            1. Check if the pips value is outside the 0-6 range.
            2. If out of range, return false immediately.
            3. Otherwise, assign the value to m_right_pips and return true.
    Reference: None
    ********************************************************************* */
    bool setRightPips(int pips);

    /* --- Utility Functions --- */

    /* *********************************************************************
    Function Name: flipTile
    Purpose: Swaps the left and right pip values of the tile to change its
            orientation on the board.
    Parameters: None
    Return Value: None (void)
    Algorithm:
            1. Store the left pips in a temporary integer variable.
            2. Assign the right pips value to the left pips variable.
            3. Assign the temporary value to the right pips variable.
    Reference: None
    ********************************************************************* */
    void flipTile();

    /* *********************************************************************
    Function Name: toString
    Purpose: Generates a string representation of the tile for file saving.
    Parameters: None
    Return Value: A std::string in the format "L-R" (e.g., "6-1").
    Algorithm:
            1. Convert m_left_pips to string.
            2. Concatenate a dash.
            3. Convert m_right_pips to string and concatenate.
    Reference: None
    ********************************************************************* */
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