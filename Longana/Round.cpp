/************************************************************
 * Name:  Race Partin                                       *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
#include "Round.h"
#include "Hand.h"
#include "Stock.h"
#include "Serializer.h"
#include "Tournament.h"
#include "Tile.h"

 /* *********************************************************************
 Function Name: Round
 Purpose: Constructor to initialize a single round of Longana. It sets up
          player scores, determines the specific engine for the round,
          shuffles and deals tiles, and identifies the starting player.
 Parameters:
          roundNumber, an integer passed by value. Used to calculate engine pips.
          tournamentTargetScore, an integer passed by value.
          humanScore, an integer passed by value (current tournament total).
          computerScore, an integer passed by value (current tournament total).
 Return Value: None
 Algorithm:
          1. Initialize member variables and set existing tournament scores.
          2. Calculate the Engine value using a wrap-around formula: 7 - ((roundNumber - 1) % 7 + 1).
          3. Shuffle the stock and deal 8 tiles to each player.
          4. Check if the Human holds the calculated Engine; if so, Human plays first.
          5. If not, check if the Computer holds the Engine; if so, Computer plays first.
          6. If neither holds it (it is in the boneyard), place the Engine automatically
             and default to the Human starting.
 Reference: None
 ********************************************************************* */
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
    // Sync the local round players with the overall tournament scores
    m_human.setScore(humanScore);
    m_computer.setScore(computerScore);

    // Determine the Engine for this specific round (e.g., Round 1 is 6-6, Round 2 is 5-5)
    int enginePips = 7 - ((roundNumber - 1) % 7 + 1);
    m_engineValue = enginePips;
    Tile engine(enginePips, enginePips);

    // Prepare the deck
    m_stock.shuffle();

    // Deal 8 tiles to each player per Longana rules
    for (int i = 0; i < 8; ++i) {
        Tile t;
        m_stock.drawTile(t);
        m_human.addTileToHand(t);

        m_stock.drawTile(t);
        m_computer.addTileToHand(t);
    }

    // Identify who starts the round by checking for the engine tile
    bool engineFound = false;

    if (m_human.removeSpecificTile(engine)) {
        m_layout.setEngine(engine);
        // Human played the engine, so the next turn is the Computer's
        m_isHumanTurn = false;
        std::cout << " >> Human holds the Engine " << enginePips << "-" << enginePips << " and plays first.\n";
        engineFound = true;
    }
    else if (m_computer.removeSpecificTile(engine)) {
        m_layout.setEngine(engine);
        // Computer played the engine, so the next turn is the Human's
        m_isHumanTurn = true;
        std::cout << " >> Computer holds the Engine " << enginePips << "-" << enginePips << " and plays first.\n";
        engineFound = true;
    }

    // Handle case where engine is in the boneyard rather than a player's hand
    if (!engineFound) {
        std::cout << " >> Neither player holds the Engine " << enginePips << "-" << enginePips << ".\n";

        // Remove the actual tile from the stock so it isn't drawn later
        m_stock.removeSpecificTile(engine);

        // Place the engine on the layout to start the round
        m_layout.setEngine(engine);
        m_isHumanTurn = true;
        std::cout << " >> Engine placed from boneyard. Human starts.\n";
    }
}

/* *********************************************************************
Function Name: displayGameState
Purpose: Prints the comprehensive state of the game board, including
         scores, hands, the layout, and the boneyard for grading verification.
Parameters: None
Return Value: None (void)
Algorithm:
         1. Print headers for Tournament Score and Round Number.
         2. Display Computer's hand and current score.
         3. Display Human's hand and current score.
         4. Display the Layout with 'L' and 'R' markers.
         5. Display every tile remaining in the boneyard.
         6. Indicate if the previous player passed.
Reference: None
********************************************************************* */
void Round::displayGameState() {
    std::cout << "\n--------------------------------------------------\n";
    std::cout << "Tournament Score To Win: " << m_tournamentScore << "\n";
    std::cout << "Round No.: " << m_roundNumber << "\n\n";

    // Show Computer state (Hand is visible for verification)
    std::cout << "Computer:\n";
    std::cout << "   Hand: ";
    m_computer.getHand().displayHand();
    std::cout << "   Score: " << m_computer.getScore() << "\n\n";

    // Show Human state
    std::cout << "Human:\n";
    std::cout << "   Hand: ";
    m_human.getHand().displayHand();
    std::cout << "   Score: " << m_human.getScore() << "\n\n";

    // Show board state
    std::cout << "Layout:\n";
    std::cout << "   L ";
    m_layout.displayLayout();
    std::cout << " R\n\n";

    // Show all tiles in the boneyard
    std::cout << "Boneyard:\n";
    m_stock.printStock();
    std::cout << "\n";

    // Display turn status
    std::cout << "Previous Player Passed: " << (m_isHumanTurn ? (m_computerPassed ? "Yes" : "No") : (m_humanPassed ? "Yes" : "No")) << "\n";
    std::cout << "Next Player: " << (m_isHumanTurn ? "Human" : "Computer") << "\n";
    std::cout << "--------------------------------------------------\n";
}

/* *********************************************************************
Function Name: playRound
Purpose: The main round loop. Continues to execute turns for each player
         until one player wins or the game becomes blocked.
Parameters: None
Return Value: None (void)
Algorithm:
         1. Enter a while loop that persists until roundOver is true.
         2. Display the full game state.
         3. If it is the Human's turn, call m_human.playTurn(). Update pass status.
         4. If it is the Computer's turn, call m_computer.playTurn(). Update pass status.
         5. Toggle the turn to the other player.
         6. Call checkWinCondition() to update roundOver status.
Reference: None
********************************************************************* */
void Round::playRound(const Tournament& tournament) {
    bool roundOver = false;

    while (!roundOver) {
        // Render the board before every move
        displayGameState();

        if (m_isHumanTurn) {
            // Execute Human turn logic
            while (true) {
                std::cout << "Enter command (play / help / save / quit): ";
                std::string command;
                std::cin >> command;

                if (command == "help") {
                    help();
                    continue;
                }
                else if (command == "save") {
                    std::cout << "Enter filename to save to: ";
                    std::string filename;
                    std::cin >> filename;

                    if (Serializer::saveGame(filename, tournament)) {
                        std::cout << "Game saved successfully to " << filename << "\n";
                    }
                    else {
                        std::cout << "Game save was unsuccessful\n";
                    }
                }
                else if (command == "quit") {
                    std::cout << "Exiting game...";
                    exit(0);
                }
                else if (command == "play") {
                    break;
                }
                else {
                    std::cout << "Invalid command. Try again.\n";
                }
            }

            // Execute Human turn logic
            bool moveMade = m_human.playTurn(m_layout, m_stock, m_computerPassed);
            m_humanPassed = !moveMade;
            m_isHumanTurn = false;
        }
        else {
            // Execute Computer turn logic
            bool moveMade = m_computer.playTurn(m_layout, m_stock, m_humanPassed);
            m_computerPassed = !moveMade;
            m_isHumanTurn = true;
        }

        // Check if the move resulted in a win or a block
        roundOver = checkWinCondition();
    }
}

/* *********************************************************************
Function Name: checkWinCondition
Purpose: Evaluates if the round has ended and calculates points for the winner.
Parameters: None
Return Value: Boolean true if the round has concluded, false if it should continue.
Algorithm:
         1. Check if Human's hand is empty. If so, add Computer's hand pips to Human's score.
         2. Check if Computer's hand is empty. If so, add Human's hand pips to Computer's score.
         3. Check if the game is "Blocked" (Stock empty and both players passed).
            a. Compare total pips in both hands.
            b. The player with fewer pips wins the block and receives the opponent's pip total.
            c. If tied, 0 points are awarded.
         4. Return true for any of the above, otherwise return false.
Reference: None
********************************************************************* */
bool Round::checkWinCondition() {
    // Check for a standard "Out" win for the Human
    if (m_human.isHandEmpty()) {
        int points = m_computer.getHand().getHandScore();
        m_human.setScore(m_human.getScore() + points);
        std::cout << "*** Human Wins Round! + " << points << " points ***\n";
        return true;
    }

    // Check for a standard "Out" win for the Computer
    if (m_computer.isHandEmpty()) {
        int points = m_human.getHand().getHandScore();
        m_computer.setScore(m_computer.getScore() + points);
        std::cout << "*** Computer Wins Round! + " << points << " points ***\n";
        return true;
    }

    // Check for a "Blocked" game state
    if (m_stock.isEmpty() && m_humanPassed && m_computerPassed) {
        std::cout << "\n*** Game Blocked! Counting pips... ***\n";

        int humanTotal = m_human.getHand().getHandScore();
        int computerTotal = m_computer.getHand().getHandScore();

        std::cout << "Human Pips: " << humanTotal << " | Computer Pips: " << computerTotal << "\n";

        // In a block, the player with the lowest total wins the opponent's pips
        if (humanTotal < computerTotal) {
            int points = computerTotal;
            m_human.setScore(m_human.getScore() + points);
            std::cout << "*** Human Wins the Block! + " << points << " points ***\n";
        }
        else if (computerTotal < humanTotal) {
            int points = humanTotal;
            m_computer.setScore(m_computer.getScore() + points);
            std::cout << "*** Computer Wins the Block! + " << points << " points ***\n";
        }
        else {
            std::cout << "*** It's a Tie! 0 points awarded. ***\n";
        }

        return true;
    }

    return false;
}

void Round::prepareRound(int roundNumber) {
    m_roundNumber = roundNumber;

    m_human.getHand().clearHand();
    m_computer.getHand().clearHand();
    m_layout.clearLayout();
    m_stock = Stock();

    m_humanPassed = false;
    m_computerPassed = false;
    m_isHumanTurn = true;
}

void Round::help() {
    const Hand& hand = m_human.getHand();
    bool foundMove = false;

    for (int i = 0; i < hand.getSize(); i++) {
        Tile t = hand.getTileAtIndex(i);

        if (m_layout.isLegalMove(t, 'L')) {
            std::cout << t.getLeftPips() << "-" << t.getRightPips() << std::endl;
            foundMove = true;
            break;
        }

        if (m_computerPassed && m_layout.isLegalMove(t, 'R')) {
            std::cout << t.getLeftPips() << "-" << t.getRightPips() << std::endl;
            foundMove = true;
            break;
        }
    }

    if (!foundMove) {
        if (!m_stock.isEmpty()) {
            std::cout << "No moves found. You Should DRAW." << std::endl;
        }
        else {
            std::cout << "No moves and boneyard is empty. You must PASS." << std::endl;
        }
    }
}
