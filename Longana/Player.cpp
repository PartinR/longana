#include "Player.h"

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