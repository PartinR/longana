#include <iostream>
#include <string>
#include "LayoutView.h"
#include "Stock.h"
#include "Layout.h"
#include "Hand.h"
#include "Tile.h"

/*
 * Psuedocode:
 * Print round number, engine value, and stock size
 */
void LayoutView::displayHeader(int roundNumber, int engineValue, const Stock& stock) const {
    std::cout << "=== Round " << roundNumber << " ===" << std::endl;
    std::cout << "Engine Value: " << engineValue << std::endl;
    std::cout << "Stock Size: " << stock.getSize() << " tiles remaining" << std::endl;
}

/*
 * Psudeocode:
 * Print the layout of the board.
 */
void LayoutView::displayBoard(const Layout& layout) const {
    std::cout << "Current Board Layout: ";
    std::cout << "L ";
    layout.displayLayout();
    std::cout << " R" << std::endl;
}

/*
 * Psuedocode:
 * Print each tile in the hand.
 */
void LayoutView::displayHand(const Hand& hand) const {
    std::cout << "Player's Hand: ";
    for (int i = 0; i < hand.getSize(); ++i) {
        Tile tile = hand.getTileAtIndex(i);
        std::cout << (i + 1) << ": [" << tile.getLeftPips() << "|" << tile.getRightPips() << "] ";
    }
    std::cout << std::endl;
}

/*
 * Psuedocode:
 * Print the provided message.
 */
void LayoutView::printMsg(const std::string& msg) const {
    std::cout << msg << std::endl;
}