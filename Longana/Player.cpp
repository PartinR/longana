#include "Player.h"
#include "Tile.h"

/*
 * Psuedocode:
 * Return whether the player's hand is empty.
 */

bool Player::isHandEmpty() const {
    return m_hand.isEmpty();
}


/*
 * Psuedocode:
 * Return the size of the player's hand.
 */

int Player::getHandSize() const {
    return m_hand.getSize();
}

/*
 * Psuedocode:
 * For each tile in the player's hand, check if it matches the target tile.
 * If found, remove it from the hand and return true.
 * If not found, return false.
 */

bool Player::removeSpecificTile(const Tile& target) {
    for (int i = 0; i < m_hand.getSize(); ++i) {
        Tile t = m_hand.getTileAtIndex(i);
        // Check for match
        if (t.getLeftPips() == target.getLeftPips() &&
            t.getRightPips() == target.getRightPips()) {

            Tile temp;
            // Remove the tile at this index
            m_hand.playTile(i, temp);
            return true; // Found and removed
        }
    }
    return false; // Player does not have this tile
}