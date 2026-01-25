#include <random>
#include <algorithm>
#include "Stock.h"
#include "Tile.h"

/*
 * Psuedocode:
 * Create all unique tiles for a standard double-six domino set.
 */
Stock::Stock() {
    // Create all unique tiles for a standard double-six domino set.
    for (int left = 0; left <= 6; ++left) {
        for (int right = left; right <= 6; ++right) {
            m_tiles.emplace_back(left, right);
        }
    }
}

/*
 * Psuedocode:
 * If m_tiles is empty, return false.
 * Else, copy the last tile in m_tiles to destination, remove it from m_tiles, and return true.
 */
bool Stock::drawTile(Tile& destination) {
    if (m_tiles.empty()) {
        return false;
    }
    else {
        destination = m_tiles.back();
        m_tiles.pop_back();
        return true;
    }
}

/*
 * Psuedocode:
 * Use std::shuffle with a random device to shuffle m_tiles.
 */
void Stock::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_tiles.begin(), m_tiles.end(), g);
}