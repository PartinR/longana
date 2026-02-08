/************************************************************
 * Name:  Race Partin                                       *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include "Player.h"
#include "Tile.h"

/* *********************************************************************
Function Name: removeSpecificTile
Purpose: Searches the player's hand for a specific tile and removes it if
        found. This is used for placing the Engine tile at the start of
        a round.
Parameters:
        target, a Tile object passed by const reference. The tile to find.
Return Value: Boolean true if the tile was found and removed, false otherwise.
Algorithm:
        1. Iterate through the player's hand using a loop from 0 to hand size.
        2. For each tile, compare its left and right pips to the target tile.
        3. If a match is found:
            a. Use the hand's playTile method to remove the tile at that index.
            b. Return true immediately.
        4. If the loop completes without a match, return false.
Reference: None
********************************************************************* */
bool Player::removeSpecificTile(const Tile& target) {
    // Iterate through the hand to locate a tile matching the target pips
    for (int i = 0; i < m_hand.getSize(); ++i) {
        Tile tile = m_hand.getTileAtIndex(i);

        // Check for an exact match between the current tile and the target engine
        if (tile.getLeftPips() == target.getLeftPips() &&
            tile.getRightPips() == target.getRightPips()) {

            // Create temporary tile
            Tile temp;

            // Remove the tile from the hand to prepare it for placement on the board
            m_hand.playTile(i, temp);
            return true;
        }
    }

    // Return false if the player was not the one holding the specific tile
    return false;
}