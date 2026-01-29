#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"
#include "Layout.h"
#include "Stock.h"
#include "Tile.h"

class Human : public Player {
public:

    bool playTurn(Layout& layout, Stock& stock, bool opponentPassed) override;

private:

    bool canPlayOnSide(const Tile& tile, char side, bool opponentPassed) const;

}; 


#endif