#include <iostream>
#include <vector>
#include <cctype>
#include "Round.h"
#include "Tile.h"

/* 
 * Psuedocode:
 * Initialize member variables.
 * Shuffle stock.
 * Draw tiles for human and computer hands.
 * Determine engine value and starting player.
 */
Round::Round(int roundNumber)
    : m_engineValue(7 - roundNumber), // Round 1: 6, Round 2: 5, etc.
    m_isHumanTurn(true),
    m_humanPassed(false),
    m_computerPassed(false),
    m_stock(), m_layout(), m_humanHand(), m_computerHand()
{
    m_stock.shuffle();

    // 1. Initial Deal (8 tiles each)
    for (int i = 0; i < 8; ++i) {
        Tile hTile, cTile;
        if (m_stock.drawTile(hTile)) m_humanHand.addTile(hTile);
        if (m_stock.drawTile(cTile)) m_computerHand.addTile(cTile);
    }

    // 2. Search and Draw Loop
    bool engineFound = false;
    int engineIndex = -1;

    while (!engineFound) {
        // Check Human Hand
        for (int i = 0; i < m_humanHand.getSize(); i++) {
            Tile t = m_humanHand.getTileAtIndex(i);
            if (t.getLeftPips() == m_engineValue && t.getRightPips() == m_engineValue) {
                m_isHumanTurn = true;
                engineFound = true;
                engineIndex = i;
                break;
            }
        }

        if (engineFound) break;

        // Check Computer Hand
        for (int i = 0; i < m_computerHand.getSize(); i++) {
            Tile t = m_computerHand.getTileAtIndex(i);
            if (t.getLeftPips() == m_engineValue && t.getRightPips() == m_engineValue) {
                m_isHumanTurn = false;
                engineFound = true;
                engineIndex = i;
                break;
            }
        }

        // If still not found, both players draw one (The "Repeat" Rule)
        if (!engineFound) {
            Tile hExtra, cExtra;
            if (m_stock.drawTile(hExtra)) m_humanHand.addTile(hExtra);
            if (m_stock.drawTile(cExtra)) m_computerHand.addTile(cExtra);

            // If stock runs out (rare), you'd need a break condition here
            if (m_stock.isEmpty()) break;
        }
    }

    // 3. Force the first move (Automatic Engine Placement)
    if (engineFound) {
        Tile engineTile;
        if (m_isHumanTurn) {
            m_humanHand.playTile(engineIndex, engineTile);
        }
        else {
            m_computerHand.playTile(engineIndex, engineTile);
        }
        // Place on layout - side doesn't matter for the first tile
        m_layout.addLeftTile(engineTile);

        // The rule says the engine holder IS the first player, 
        // but they just used their turn to place it.
        // So we toggle the turn so the NEXT person goes.
        m_isHumanTurn = !m_isHumanTurn;
    }
}

/*
 * Psuedocode:
 * Play a round by alternating turns until a win condition is met.
 */
void Round::playRound() {
    bool roundOver = false;
    while (!roundOver) {
        if (m_isHumanTurn) {
            performHumanTurn();
        } 
        else {
            performComputerTurn();
        }
        
        if (checkWinCondition()) {
            roundOver = true;
        }
        else {
            m_isHumanTurn = !m_isHumanTurn;
        }
    }
}

/*
 * Psuedocode:
 * Helper function to decide when play can be made on opposing side.
 */
bool Round::canPlayOnSide(const Tile& t, char side, bool isHumanTurn, bool opponentPassed) {
    bool isDouble = (t.getLeftPips() == t.getRightPips());

    // Rule: Doubles can go ANYWHERE.
    if (isDouble) return true;

    // Rule: If opponent passed, you can play ANYWHERE.
    if (opponentPassed) return true;

    // Rule: Otherwise, stick to your side.
    if (isHumanTurn) {
        return (side == 'L'); // Human owns Left
    }
    else {
        return (side == 'R'); // Computer owns Right
    }
}

/* 
 * Psuedocode:
 * Handle human player's turn.
 */
void Round::performHumanTurn() {
    m_view.displayHeader(7 - m_engineValue, m_engineValue, m_stock);
    m_view.displayBoard(m_layout);
    if (m_computerPassed) { m_view.printMsg("Computer passed, you can play both sides."); }
    
    // Create vector of playable tiles for later indexing
    std::vector<int> playableTiles;
    for (int i = 0; i < m_humanHand.getSize(); i++) {
        Tile t = m_humanHand.getTileAtIndex(i);
        bool fitL = canPlayOnSide(t, 'L', true, m_computerPassed) && m_layout.isLegalMove(t, 'L');
        bool fitR = canPlayOnSide(t, 'R', true, m_computerPassed) && m_layout.isLegalMove(t, 'R');

        if (fitL || fitR) { playableTiles.push_back(i); }
    }

    if (playableTiles.empty()) {
        m_view.printMsg("No valid moves.");

        // Scenario: Stock has no tiles left.
        // Force pass.
        if (m_stock.isEmpty()) {
            m_view.printMsg("Stock is empty, you must pass.");
            m_humanPassed = true;
            return;
        }
        
        // Scenario: Stock has tiles left.
        // Draw until a playable tile is found or stock is empty.
        m_view.printMsg("Drawing from stock...");
        Tile drawn;
        if (!m_stock.drawTile(drawn)) { return; } // Stock empty after all.

        m_humanHand.addTile(drawn);
        std::cout << "Drew tile: [" << drawn.getLeftPips() << "|" << drawn.getRightPips() << "]" << std::endl;

        // Check if drawn tile is playable
        bool playL = canPlayOnSide(drawn, 'L', true, m_computerPassed) && m_layout.isLegalMove(drawn, 'L');
        bool playR = canPlayOnSide(drawn, 'R', true, m_computerPassed) && m_layout.isLegalMove(drawn, 'R');

        // Boolean Logic: Not playable on either side -> must pass.
        if (!playL && !playR) { 
            m_view.printMsg("Drawn tile is not playable. You pass.");
            m_humanPassed = true;
            return;
        }

        // If playable on both sides, let player choose.
        char sideChoice = 'L';
        if (playL && playR) {
            m_view.printMsg("You can play the drawn tile on either side. Choose L or R:");
            std::cin >> sideChoice;
            sideChoice = toupper(sideChoice);
        }
        else if (playR) {
            sideChoice = 'R';
        }

        Tile playedTile;
        m_humanHand.playTile(m_humanHand.getSize() - 1, playedTile); // Play the drawn tile
        (sideChoice == 'L') ? m_layout.addLeftTile(playedTile) : m_layout.addRightTile(playedTile);

        m_view.printMsg("Played drawn tile.");
        m_humanPassed = false;
        return;
    }

    m_humanPassed = false;
    
    while (true) {
        m_view.displayHand(m_humanHand);
        int choice;
        std::cout << "Select a tile to play by index (1-" << m_humanHand.getSize() << "): ";
        std::cin >> choice;

        // Index validation.
        if (choice < 1 || choice > m_humanHand.getSize()) {
            m_view.printMsg("Invalid index. Try again.");
            continue;
        }

        Tile t = m_humanHand.getTileAtIndex(choice - 1);
        bool fitL = canPlayOnSide(t, 'L', true, m_computerPassed) && m_layout.isLegalMove(t, 'L');
        bool fitR = canPlayOnSide(t, 'R', true, m_computerPassed) && m_layout.isLegalMove(t, 'R');

        if (!fitL && !fitR) {
            m_view.printMsg("Selected tile cannot be played. Choose another.");
            continue;
        }

        char sideChoice = 'L';
        if (fitL && fitR) {
            m_view.printMsg("You can play this tile on either side. Choose L or R:");
            std::cin >> sideChoice;
            sideChoice = toupper(sideChoice);
        }
        else if (fitR) {
            sideChoice = 'R';
        }

        // Execute the play
        Tile playedTile;
        m_humanHand.playTile(choice - 1, playedTile);
        if (sideChoice == 'L') {
            m_layout.addLeftTile(playedTile);
        }
        else {
            m_layout.addRightTile(playedTile);
        }

        break; // Exit loop after successful play
    }
}

/* 
 * Psuedocode:
 * Handle computer player's turn.
 */
void Round::performComputerTurn() {
    m_view.printMsg("Computer is thinking...");

    // --- 1. SEARCH FOR MOVES ---
    int bestIndex = -1;
    char bestSide = 'R'; // Default preference

    for (int i = 0; i < m_computerHand.getSize(); ++i) {
        Tile t = m_computerHand.getTileAtIndex(i);

        // Check Right (Computer's Side) - Priority 1
        if (canPlayOnSide(t, 'R', false, m_humanPassed) && m_layout.isLegalMove(t, 'R')) {
            bestIndex = i;
            bestSide = 'R';
            break; // Found preferred move, stop looking
        }

        // Check Left (Human's Side) - Priority 2
        // We only mark this if we haven't found a Right move yet
        if (bestIndex == -1 && canPlayOnSide(t, 'L', false, m_humanPassed) && m_layout.isLegalMove(t, 'L')) {
            bestIndex = i;
            bestSide = 'L';
            // Continue searching to see if we can find a Right move instead
        }
    }

    // --- 2. EXECUTE MOVE (If found) ---
    if (bestIndex != -1) {
        Tile playedTile;
        m_computerHand.playTile(bestIndex, playedTile);

        if (bestSide == 'R') {
            m_layout.addRightTile(playedTile);
            m_view.printMsg("Computer played a tile on the RIGHT.");
        }
        else {
            m_layout.addLeftTile(playedTile);
            m_view.printMsg("Computer played a tile on the LEFT.");
        }
        m_computerPassed = false;
        return;
    }

    // --- 3. HANDLE DRAWING (If no moves) ---
    m_view.printMsg("Computer has no moves. Drawing...");

    if (m_stock.isEmpty()) {
        m_view.printMsg("Stock is empty. Computer passes.");
        m_computerPassed = true;
        return;
    }

    Tile drawn;
    if (!m_stock.drawTile(drawn)) return; // Safety check
    m_computerHand.addTile(drawn);
    m_view.printMsg("Computer drew a tile.");

    // Check if the NEW tile can be played
    bool fitsR = canPlayOnSide(drawn, 'R', false, m_humanPassed) && m_layout.isLegalMove(drawn, 'R');
    bool fitsL = canPlayOnSide(drawn, 'L', false, m_humanPassed) && m_layout.isLegalMove(drawn, 'L');

    if (fitsR || fitsL) {
        // It plays! Logic: Prefer Right if possible.
        char sideToPlay = fitsR ? 'R' : 'L';

        Tile playedTile;
        m_computerHand.playTile(m_computerHand.getSize() - 1, playedTile);

        if (sideToPlay == 'R') {
            m_layout.addRightTile(playedTile);
            m_view.printMsg("Computer played the drawn tile on the RIGHT.");
        }
        else {
            m_layout.addLeftTile(playedTile);
            m_view.printMsg("Computer played the drawn tile on the LEFT.");
        }
        m_computerPassed = false;
    }
    else {
        m_view.printMsg("Computer cannot play the drawn tile. Computer passes.");
        m_computerPassed = true;
    }
}

/* 
 * Psuedocode:
 * Check if either player has won or if the game is blocked.
 */
bool Round::checkWinCondition() {
    // --- 1. HUMAN WINS (Empty Hand) ---
    // If you haven't added isEmpty() yet, use: m_humanHand.getSize() == 0
    if (m_humanHand.isEmpty()) {
        m_view.displayBoard(m_layout);

        // Calculate points: Sum of pips in opponent's (Computer's) hand
        int points = m_computerHand.getHandScore();

        std::cout << "\n****************************************\n";
        std::cout << "             YOU WIN THE ROUND!           \n";
        std::cout << "****************************************\n";
        std::cout << " >> You emptied your hand first.\n";
        std::cout << " >> Points earned: " << points << "\n\n";

        // TODO: Add 'points' to the human's Tournament Score here later
        return true;
    }

    // --- 2. COMPUTER WINS (Empty Hand) ---
    if (m_computerHand.isEmpty()) {
        m_view.displayBoard(m_layout);

        // Calculate points: Sum of pips in opponent's (Human's) hand
        int points = m_humanHand.getHandScore();

        std::cout << "\n****************************************\n";
        std::cout << "           COMPUTER WINS THE ROUND!       \n";
        std::cout << "****************************************\n";
        std::cout << " >> Computer emptied its hand first.\n";
        std::cout << " >> Points earned: " << points << "\n\n";

        // TODO: Add 'points' to the computer's Tournament Score here later
        return true;
    }

    // --- 3. BLOCKED GAME (Stock Empty + Both Passed) ---
    if (m_stock.isEmpty() && m_humanPassed && m_computerPassed) {
        m_view.displayBoard(m_layout);

        int humanTotal = m_humanHand.getHandScore();
        int computerTotal = m_computerHand.getHandScore();

        std::cout << "\n****************************************\n";
        std::cout << "       ROUND OVER: GAME BLOCKED         \n";
        std::cout << "****************************************\n";
        std::cout << " >> Stock is empty and both players passed.\n";
        std::cout << " >> Your pip count: " << humanTotal << "\n";
        std::cout << " >> Computer pip count: " << computerTotal << "\n";

        if (humanTotal < computerTotal) {
            // Human has fewer pips -> Human Wins
            // Winner gets points equal to OPPONENT'S total
            std::cout << " >> YOU WIN (Lower pip count)!\n";
            std::cout << " >> Points earned: " << computerTotal << "\n\n";
            // TODO: Add computerTotal to Human Score
        }
        else if (computerTotal < humanTotal) {
            // Computer has fewer pips -> Computer Wins
            std::cout << " >> COMPUTER WINS (Lower pip count)!\n";
            std::cout << " >> Points earned: " << humanTotal << "\n\n";
            // TODO: Add humanTotal to Computer Score
        }
        else {
            // Tie
            std::cout << " >> IT'S A DRAW! (Equal pips)\n";
            std::cout << " >> Points earned: 0\n\n";
        }

        return true;
    }

    // Game is not over yet
    return false;
}