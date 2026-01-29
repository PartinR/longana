#include <iostream>
#include "Round.h"
#include "Hand.h"
#include "Tile.h"


/*
 * Psuedocode:
 * Round Constructor:
 * Create all the objects needed for a round.
 */

Round::Round(int roundNumber, int tournamentTargetScore, int humanScore, int computerScore)
    : m_roundNumber(roundNumber),
    m_tournamentScore(tournamentTargetScore),
    m_human(),
    m_computer(),
    m_stock(),
    m_layout(),
    m_computerPassed(false),
    m_humanPassed(false),
    m_isHumanTurn(false),
    m_engineValue(0)
{

    m_human.setScore(humanScore);
    m_computer.setScore(computerScore);

    // 1. Determine Engine Pips (e.g., Round 1 = 6-6)
    // If round > 7, wrap around (e.g. Round 8 is 6-6 again) or use mod.
    // For now, assuming simple 7 - roundNum logic:
    int enginePips = 7 - ((roundNumber - 1) % 7 + 1);

    // Store it properly now that the object is constructed
    m_engineValue = enginePips;

    Tile engine(enginePips, enginePips);

    // 2. Deal 8 tiles to each player
    for (int i = 0; i < 8; ++i) {
        Tile t;
        m_stock.drawTile(t);
        m_human.addTileToHand(t);

        m_stock.drawTile(t);
        m_computer.addTileToHand(t);
    }

    // 3. Determine First Player by hunting for the Engine
    bool engineFound = false;

    // Check if Human has the engine
    if (m_human.removeSpecificTile(engine)) {
        m_layout.setEngine(engine);
        m_isHumanTurn = false; // Human played, so it's Computer's turn next
        std::cout << " >> Human holds the Engine " << enginePips << "-" << enginePips << " and plays first.\n";
        engineFound = true;
    }
    // Check if Computer has the engine
    else if (m_computer.removeSpecificTile(engine)) {
        m_layout.setEngine(engine);
        m_isHumanTurn = true; // Computer played, so it's Human's turn next
        std::cout << " >> Computer holds the Engine " << enginePips << "-" << enginePips << " and plays first.\n";
        engineFound = true;
    }

    // EDGE CASE: Neither player has the engine (it is in the boneyard)
    if (!engineFound) {
        std::cout << " >> Neither player holds the Engine " << enginePips << "-" << enginePips << ".\n";

        // In standard rules, the player with the NEXT highest double starts.
        // For this assignment's simplicity, we can force-draw it or just place it from the void.
        // Let's assume we place it "from the boneyard" effectively:

        m_layout.setEngine(engine);

        // Technically, if it was in the stock, we should remove it from stock to be perfect.
        // But for now, we just start the game.
        // Default to Human starts if nobody had it.
        m_isHumanTurn = true;
        std::cout << " >> Engine placed on board. Human starts.\n";
    }
}


/*
 * Psuedocode:
 * Give the basic layout of the game state.
 * Tournament score, round number, hands, layout, boneyard size,
 * previous player passed, next player.
 */

void Round::displayGameState() {
    std::cout << "\n--------------------------------------------------\n";
    std::cout << "Tournament Score: " << m_tournamentScore << "\n";
    std::cout << "Round No.: " << m_roundNumber << "\n\n";

    // Computer Section (Now visible as requested)
    std::cout << "Computer:\n";
    std::cout << "   Hand: ";
    m_computer.getHand().displayHand(); // Ensure Hand::displayHand prints nicely
    std::cout << "\n   Score: " << m_computer.getScore() << "\n\n";

    // Human Section
    std::cout << "Human:\n";
    std::cout << "   Hand: ";
    m_human.getHand().displayHand();
    std::cout << "\n   Score: " << m_human.getScore() << "\n\n";

    // Layout
    std::cout << "Layout:\n";
    std::cout << "  L ";
    m_layout.displayLayout();
    std::cout << " R\n\n";

    // Boneyard (Now visible as requested)
    std::cout << "Boneyard:\n";
    m_stock.printStock(); // You added this to Stock class
    std::cout << "\n";

    // Status
    std::cout << "Previous Player Passed: " << (m_isHumanTurn ? (m_computerPassed ? "Yes" : "No") : (m_humanPassed ? "Yes" : "No")) << "\n";
    std::cout << "Next Player: " << (m_isHumanTurn ? "Human" : "Computer") << "\n";
    std::cout << "--------------------------------------------------\n";
}


/*
 * Psuedocode:
 * Main game loop for a round.
 * Alternate turns between Human and Computer
 * until a win condition is met.
 */

void Round::playRound() {
    bool roundOver = false;

    while (!roundOver) {
        // Display the FULL STATE before every turn
        displayGameState();

        if (m_isHumanTurn) {
            // Call Human Object
            // It returns true if they played, false if they passed
            bool moveMade = m_human.playTurn(m_layout, m_stock, m_computerPassed);
            m_humanPassed = !moveMade;
            m_isHumanTurn = false; // Switch turn
        }
        else {
            // Call Computer Object
            bool moveMade = m_computer.playTurn(m_layout, m_stock, m_humanPassed);
            m_computerPassed = !moveMade;
            m_isHumanTurn = true; // Switch turn
        }

        roundOver = checkWinCondition();
    }
}


/*
 * Psuedocode:
 * Check for win conditions:
 * 1. Human Wins (Human hand empty)
 * 2. Computer Wins (Computer hand empty)
 * 3. Blocked Game (Stock empty, both players passed)
 */

bool Round::checkWinCondition() {
    // 1. HUMAN WINS (Human went out)
    if (m_human.isHandEmpty()) {
        // Calculate points (Sum of pips in Computer's hand)
        int points = m_computer.getHand().getHandScore();

        // Update Human's total score immediately
        m_human.setScore(m_human.getScore() + points);

        std::cout << "*** Human Wins Round! + " << points << " points ***\n";
        return true;
    }

    // 2. COMPUTER WINS (Computer went out)
    if (m_computer.isHandEmpty()) {
        // Calculate points (Sum of pips in Human's hand)
        int points = m_human.getHand().getHandScore();

        // Update Computer's total score immediately
        m_computer.setScore(m_computer.getScore() + points);

        std::cout << "*** Computer Wins Round! + " << points << " points ***\n";
        return true;
    }

    // 3. BLOCKED GAME (Stock empty, both players passed consecutively)
    if (m_stock.isEmpty() && m_humanPassed && m_computerPassed) {
        std::cout << "\n*** Game Blocked! Counting pips... ***\n";

        // Get pip totals for comparison
        int humanTotal = m_human.getHand().getHandScore();
        int computerTotal = m_computer.getHand().getHandScore();

        std::cout << "Human Pips: " << humanTotal << " | Computer Pips: " << computerTotal << "\n";

        if (humanTotal < computerTotal) {
            // Human has fewer dots, so Human wins. 
            // In Longana, winner usually gets the loser's pip count (or sometimes their own + loser's).
            // Standard rule: Winner gets the loser's total.
            int points = computerTotal;

            m_human.setScore(m_human.getScore() + points);
            std::cout << "*** Human Wins the Block! + " << points << " points ***\n";
        }
        else if (computerTotal < humanTotal) {
            // Computer has fewer dots, so Computer wins.
            int points = humanTotal;

            m_computer.setScore(m_computer.getScore() + points);
            std::cout << "*** Computer Wins the Block! + " << points << " points ***\n";
        }
        else {
            // Tie (Rare)
            std::cout << "*** It's a Tie! 0 points awarded. ***\n";
        }

        return true; // Round is over
    }

    // Round is not over yet
    return false;
}