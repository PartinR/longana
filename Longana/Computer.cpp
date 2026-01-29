#include <iostream>
#include "Computer.h"
#include "Layout.h"
#include "Stock.h"
#include "Tile.h"


/*
 * Psuedocode:
 * Returns whether or not the tile can be played on the specified side.
 */

bool Computer::canPlayOnSide(const Tile& t, char side, bool opponentPassed) const {
    if (t.getLeftPips() == t.getRightPips()) return true;
    if (opponentPassed) return true;
    return (side == 'R'); // Default: Right only
}


/*
 * Psuedocode:
 * Computer's turn logic:
 * 1. Search for moves in hand, prefer right side
 * 2. If no moves, draw from stock
 */

bool Computer::playTurn(Layout& layout, Stock& stock, bool opponentPassed) {
    std::cout << "Computer is thinking...\n";

    // 1. Search for moves
    int bestIndex = -1;
    char bestSide = 'R';

    for (int i = 0; i < m_hand.getSize(); ++i) {
        Tile t = m_hand.getTileAtIndex(i);

        // Prefer Own Side (R)
        if (canPlayOnSide(t, 'R', opponentPassed) && layout.isLegalMove(t, 'R')) {
            bestIndex = i; bestSide = 'R'; break;
        }
        // Accept Other Side (L)
        if (bestIndex == -1 && canPlayOnSide(t, 'L', opponentPassed) && layout.isLegalMove(t, 'L')) {
            bestIndex = i; bestSide = 'L';
        }
    }

    if (bestIndex != -1) {
        Tile played;
        m_hand.playTile(bestIndex, played);
        if (bestSide == 'R') {
            layout.addRightTile(played);
            std::cout << "Computer placed " << played.getLeftPips() << "-" << played.getRightPips() << " on the RIGHT.\n";
        }
        else {
            layout.addLeftTile(played);
            std::cout << "Computer placed " << played.getLeftPips() << "-" << played.getRightPips() << " on the LEFT.\n";
        }
        return true;
    }

    // 2. Draw
    if (stock.isEmpty()) {
        std::cout << "Computer cannot move and stock is empty. Computer passes.\n";
        return false;
    }

    Tile drawn;
    stock.drawTile(drawn);
    m_hand.addTile(drawn);
    std::cout << "Computer drew a tile.\n";

    bool fitR = canPlayOnSide(drawn, 'R', opponentPassed) && layout.isLegalMove(drawn, 'R');
    bool fitL = canPlayOnSide(drawn, 'L', opponentPassed) && layout.isLegalMove(drawn, 'L');

    if (fitR || fitL) {
        Tile played;
        m_hand.playTile(m_hand.getSize() - 1, played);
        // Prefer Right
        if (fitR) {
            layout.addRightTile(played);
            std::cout << "Computer placed drawn tile on RIGHT.\n";
        }
        else {
            layout.addLeftTile(played);
            std::cout << "Computer placed drawn tile on LEFT.\n";
        }
        return true;
    }

    std::cout << "Computer passes.\n";
    return false;
}