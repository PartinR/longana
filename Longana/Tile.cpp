#include "Tile.h"


/*
 * Psuedocode:
 * Check if inputs are between 0 and 6.
 * If yes, assign via initializer. If no, default to 0;
 */

Tile::Tile(int left, int right) {
    if (left >= MIN_PIPS && left <= MAX_PIPS) {
        m_left_pips = left;
    }
    else {
        m_left_pips = 0;
    }

    if (right >= MIN_PIPS && right <= MAX_PIPS) {
        m_right_pips = right;
    }
    else {
        m_right_pips = 0;
    }
}


/*
 * Psuedocode:
 * Return true if (left==left AND right==right) OR (left==right AND right==left).
 */

bool Tile::operator==(const Tile& other) const {
    bool standardMatch = (m_left_pips == other.m_left_pips && m_right_pips == other.m_right_pips);
    bool flippedMatch = (m_left_pips == other.m_right_pips && m_right_pips == other.m_left_pips);
    return standardMatch || flippedMatch;
}


/*
 * Mutators:
 * Return true if success, else false
 * Set left pips, set right pips, and switch pips.
 */

bool Tile::setLeftPips(int pips) {
    if (pips < MIN_PIPS || pips > MAX_PIPS) return false;
    m_left_pips = pips;
    return true;
}

bool Tile::setRightPips(int pips) {
    if (pips < MIN_PIPS || pips > MAX_PIPS) return false;
    m_right_pips = pips;
    return true;
}

void Tile::flipTile() {
    int temp = m_left_pips;
    m_left_pips = m_right_pips;
    m_right_pips = temp;
}