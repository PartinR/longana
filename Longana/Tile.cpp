/************************************************************
 * Name:  Race Partin                                       *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include <string>

#include "Tile.h"

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
Tile::Tile(int left, int right) {
    // Validate and assign the left side of the domino
    if (left >= MIN_PIPS && left <= MAX_PIPS) {
        m_left_pips = left;
    }
    else {
        m_left_pips = 0;
    }

    // Validate and assign the right side of the domino
    if (right >= MIN_PIPS && right <= MAX_PIPS) {
        m_right_pips = right;
    }
    else {
        m_right_pips = 0;
    }
}

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
********************************************************************* */
bool Tile::operator==(const Tile& other) const {
    // Standard orientation check (e.g., 1-2 vs 1-2)
    bool standardMatch = (m_left_pips == other.m_left_pips && m_right_pips == other.m_right_pips);

    // Flipped orientation check (e.g., 1-2 vs 2-1)
    bool flippedMatch = (m_left_pips == other.m_right_pips && m_right_pips == other.m_left_pips);

    return standardMatch || flippedMatch;
}

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
bool Tile::setLeftPips(int pips) {
    // Ensure the new value follows double-six domino set constraints
    if (pips < MIN_PIPS || pips > MAX_PIPS) { return false; }

    m_left_pips = pips;
    return true;
}

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
bool Tile::setRightPips(int pips) {
    // Ensure the new value follows double-six domino set constraints
    if (pips < MIN_PIPS || pips > MAX_PIPS) { return false; }

    m_right_pips = pips;
    return true;
}

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
void Tile::flipTile() {
    // Use a temporary swap to reverse the ends of the domino
    int temp = m_left_pips;
    m_left_pips = m_right_pips;
    m_right_pips = temp;
}

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
std::string Tile::toString() const {
    // Format the tile for serialization (e.g., "3-4")
    return std::to_string(m_left_pips) + "-" + std::to_string(m_right_pips);
}