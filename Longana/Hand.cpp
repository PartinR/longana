#include <iostream>
#include "Hand.h"
#include "Tile.h"

/*
 * Psuedocode:
 * Initialize totalScore to 0.
 * For each tile in m_tiles, add tile.getSum() to totalScore.
 * Return totalScore.
 */
int Hand::getHandScore() const {
    int totalScore = 0;
    for (const Tile& tile : m_tiles) {
        totalScore += tile.getSum();
    }
    return totalScore;
}

/*
 * Psuedocode:
 * Add the provided tile to m_tiles and return true.
 */
bool Hand::addTile(const Tile& tile) {
    m_tiles.push_back(tile);
    return true;
}

/*
 * Psuedocode:
 * If index is out of bounds, return false.
 * Else, copy the tile at m_tiles[index] to outTile, remove it from m_tiles, and return true.
 */
bool Hand::playTile(int index, Tile& outTile) {
    if (index < 0 || index >= static_cast<int>(m_tiles.size())) {
        return false;
    }
    else 
    {
        outTile = m_tiles[index];
        m_tiles.erase(m_tiles.begin() + index);
        return true;
    }
}

/*
 * Psuedocode:
 * For each tile in m_tiles, display its left and right pips.
 */
void Hand::displayHand() const {
    for (const Tile& tile : m_tiles) {
        std::cout << tile.getLeftPips() << "-" << tile.getRightPips() << " ";
    }
    std::cout << std::endl;
}