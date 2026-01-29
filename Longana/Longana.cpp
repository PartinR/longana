#include <iostream>
#include "Tournament.h"

int main() {
    // 1. Create the Tournament Manager
    Tournament game;

    // 2. Start the game
    // This function handles asking for the score, looping rounds, 
    // and announcing the winner.
    game.playTournament();

    return 0;
}