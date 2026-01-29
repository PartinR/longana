#ifndef COMPUTER_H
#define COMPUTER_H

#include "Player.h"
#include "Layout.h"
#include "Stock.h"
#include "Tile.h"

class Computer : public Player {
public:

    bool playTurn(Layout& layout, Stock& stock, bool opponentPassed) override;

private:

    bool canPlayOnSide(const Tile& tile, char side, bool opponentPassed) const;

};

#endif