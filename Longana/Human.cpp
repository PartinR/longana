#include <iostream>
#include <vector>
#include <cctype>
#include "Human.h"
#include "Layout.h"
#include "Stock.h"
#include "Tile.h"

bool Human::canPlayOnSide(const Tile& t, char side, bool opponentPassed) const {
    if (t.getLeftPips() == t.getRightPips()) return true; // Double
    if (opponentPassed) return true;                      // Opponent passed
    return (side == 'L');                                 // Default: Left only
}

bool Human::playTurn(Layout& layout, Stock& stock, bool opponentPassed) {
    // 1. Check for valid moves
    std::vector<int> playableIndices;
    for (int i = 0; i < m_hand.getSize(); ++i) {
        Tile t = m_hand.getTileAtIndex(i);
        bool fitL = canPlayOnSide(t, 'L', opponentPassed) && layout.isLegalMove(t, 'L');
        bool fitR = canPlayOnSide(t, 'R', opponentPassed) && layout.isLegalMove(t, 'R');
        if (fitL || fitR) playableIndices.push_back(i);
    }

    // 2. Handle "Must Draw"
    if (playableIndices.empty()) {
        std::cout << " >> No moves available. Drawing from boneyard...\n";
        if (stock.isEmpty()) {
            std::cout << " >> Boneyard empty. You must pass.\n";
            return false; // Passed
        }

        Tile drawn;
        stock.drawTile(drawn);
        m_hand.addTile(drawn);
        std::cout << " >> You drew: " << drawn.getLeftPips() << "-" << drawn.getRightPips() << " \n";

        // Check if drawn tile plays
        bool fitL = canPlayOnSide(drawn, 'L', opponentPassed) && layout.isLegalMove(drawn, 'L');
        bool fitR = canPlayOnSide(drawn, 'R', opponentPassed) && layout.isLegalMove(drawn, 'R');

        if (!fitL && !fitR) {
            std::cout << " >> Drawn tile cannot be played. You pass.\n";
            return false; // Passed
        }

        // It fits! Ask user where to play it.
        char side = 'L';
        if (fitL && fitR) {
            std::cout << " >> Drawn tile fits BOTH sides. Play (L)eft or (R)ight? ";
            std::cin >> side;
            side = toupper(side);
        }
        else if (fitR) {
            side = 'R';
            std::cout << " >> Tile must be played on RIGHT.\n";
        }
        else {
            std::cout << " >> Tile must be played on LEFT.\n";
        }

        Tile playedTile;
        m_hand.playTile(m_hand.getSize() - 1, playedTile);
        if (side == 'R') layout.addRightTile(playedTile);
        else layout.addLeftTile(playedTile);

        return true; // Moved
    }

    // 3. Main Input Loop
    while (true) {
        int choice;
        std::cout << " >> Select tile index (1-" << m_hand.getSize() << "): ";
        std::cin >> choice;

        if (choice < 1 || choice > m_hand.getSize()) {
            std::cout << "Invalid index.\n";
            continue;
        }

        Tile t = m_hand.getTileAtIndex(choice - 1);
        bool fitL = canPlayOnSide(t, 'L', opponentPassed) && layout.isLegalMove(t, 'L');
        bool fitR = canPlayOnSide(t, 'R', opponentPassed) && layout.isLegalMove(t, 'R');

        if (!fitL && !fitR) {
            std::cout << "That tile cannot be played anywhere.\n";
            continue;
        }

        // Ask for side if ambiguous OR if you just want manual control
        char side = 'L';
        if (fitL && fitR) {
            std::cout << " >> Play on (L)eft or (R)ight? ";
            std::cin >> side;
            side = toupper(side);
            if (side != 'L' && side != 'R') continue;
        }
        else if (fitR) {
            side = 'R'; // Forced Right
        }
        // else Forced Left

        Tile playedTile;
        m_hand.playTile(choice - 1, playedTile);
        if (side == 'L') layout.addLeftTile(playedTile);
        else layout.addRightTile(playedTile);

        return true; // Move made
    }
}