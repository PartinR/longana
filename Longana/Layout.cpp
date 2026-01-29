#include <iostream>
#include "Layout.h"
#include "Hand.h"
#include "Tile.h"

/*
 * Psuedocode:
 * ifEmpty, then add tile to back and return true
 * else check if leftPips or rightPips match leftEdge
 * if rightPips matches, flip tile before adding
 */
bool Layout::addLeftTile(const Tile& tile) {
    if (isEmpty()) {
        m_layout.push_front(tile);
        return true;
    }

    int leftEdge = getLeftEdge();
    if (tile.getRightPips() == leftEdge) {
        m_layout.push_front(tile);
        return true;
    }
    else if (tile.getLeftPips() == leftEdge) {
        Tile flippedTile = tile;
        flippedTile.flipTile();
        m_layout.push_front(flippedTile);
        return true;
    }
    return false;
}

/*
 * Psuedocode:
 * ifEmpty, then add tile to back and return true
 * else check if leftPips or rightPips match rightEdge
 * if leftPips matches, flip tile before adding
 */
bool Layout::addRightTile(const Tile& tile) {
    if (isEmpty()) {
        m_layout.push_back(tile);
        return true;
    }

    int rightEdge = getRightEdge();
    if (tile.getLeftPips() == rightEdge) {
        m_layout.push_back(tile);
        return true;
    }
    else if (tile.getRightPips() == rightEdge) {
        Tile flippedTile = tile;
        flippedTile.flipTile();
        m_layout.push_back(flippedTile);
        return true;
    }
    return false;
}

/*
 * Psuedocode:
 * If side is 'L', check if tile can be placed on left edge
 * If side is 'R', check if tile can be placed on right edge
 * Else return false
 */
bool Layout::isLegalMove(const Tile& tile, char side) const {
    if (isEmpty()) {
        return true; // Any tile can be played on an empty layout
    }

    int leftEdge = getLeftEdge();
    int rightEdge = getRightEdge();
    if (side == 'L') {
        return (tile.getLeftPips() == leftEdge || tile.getRightPips() == leftEdge);
    }
    else if (side == 'R') {
        return (tile.getLeftPips() == rightEdge || tile.getRightPips() == rightEdge);
    }
    return false;
}

/*
 * Psuedocode:
 * Check if each tile in hand can be legally placed on either side of layout.
 */
bool Layout::findValidMoves(const Hand& hand) const {
    if (isEmpty()) {
        return true;
    }

    bool foundMove = false;
    for (int i = 0; i < hand.getSize(); i++) {
        Tile current = hand.getTileAtIndex(i);

        if (isLegalMove(current, 'L') || isLegalMove(current, 'R')) {
            foundMove = true;
        }
    }

    return foundMove;
}

/*
 * Psuedocode:
 * For each tile in m_layout, display its left and right pips.
 */
void Layout::displayLayout() const {
    for (const Tile& tile : m_layout) {
        std::cout << tile.getLeftPips() << "-" << tile.getRightPips() << " ";
    }
}