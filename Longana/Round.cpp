/************************************************************
 * Name:  Race Partin                                       *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include <cstdlib>
#include <iostream>
#include <string>

#include "Hand.h"
#include "Round.h"
#include "Serializer.h"
#include "Stock.h"
#include "Tile.h"
#include "Tournament.h"

 /* *********************************************************************
Function Name: Round
Purpose: Constructor to initialize a Round object. It sets the initial
        state of the round number and synchronizes tournament scores.
Parameters:
        roundNumber - integer, current round number.
        tournamentTargetScore - integer, score to win the game.
        humanScore - integer, current human score.
        computerScore - integer, current computer score.
Return Value: None
Algorithm:
        1. Initialize member variables (round number, target score).
        2. Sync local player objects with current tournament scores.
        3. Initialize flags (m_isHumanTurn, etc.) to defaults.
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

}

/* *********************************************************************
Function Name: prepareRound
Purpose: To initialize the round state and handle the pre-game setup.
        This includes resetting flags, clearing hands and layout,
        shuffling the deck, dealing tiles, and determining the starting
        player by locating the "engine" (starting double) for the
        current round.
Parameters:
        roundNumber - An integer representing the current round, used
            to calculate which double tile is the engine.
Return Value: None
Algorithm:
        1. Reset round variables (pass flags and round number).
        2. Clear any data from previous rounds in the layout and hands.
        3. Initialize and shuffle the stock (boneyard).
        4. Deal 8 tiles to each player.
        5. Calculate the engine value based on the round number
            (e.g., Round 1 is 6-6, Round 2 is 5-5).
        6. Search player hands for the engine tile.
        7. If a player has the engine, play it to the layout and set
            the next turn to the opponent.
        8. If neither has it, pull the engine from the stock, place it,
            and default the first turn to the human.
Reference: None
********************************************************************* */
void Round::prepareRound(int roundNumber) {
    // 1. Reset Game State
    m_roundNumber = roundNumber;
    m_humanPassed = false;
    m_computerPassed = false;

    // Clear containers to ensure no leftover data from previous rounds
    m_layout.clearLayout();
    m_human.getHand().clearHand();
    m_computer.getHand().clearHand();

    // 2. Initialize and Shuffle Stock
    m_stock.initializeFullSet();
    m_stock.shuffle();

    // 3. Deal 8 tiles to each player per Longana rules
    for (int i = 0; i < 8; ++i) {
        Tile tile;
        // Check to ensure stock isn't empty (though it shouldn't be at start)
        if (m_stock.drawTile(tile)) {
            m_human.getHand().addTile(tile);
        }
        if (m_stock.drawTile(tile)) {
            m_computer.getHand().addTile(tile);
        }
    }

    // 4. Calculate Engine Value (Double-Double based on round)
    // Round 1 = 6-6, Round 2 = 5-5 ... Round 7 = 0-0, Round 8 = 6-6
    int pips = 6 - ((m_roundNumber - 1) % 7);
    Tile engineTile(pips, pips);
    m_engineValue = pips;

    // 5. Identify who starts the round by checking for the engine tile
    bool humanHasEngine = false;
    bool computerHasEngine = false;

    // Check Human Hand
    for (int i = 0; i < m_human.getHand().getSize(); ++i) {
        if (m_human.getHand().getTileAtIndex(i) == engineTile) {
            humanHasEngine = true;

            // Remove from hand and play immediately
            Tile played;
            m_human.getHand().playTile(i, played);
            m_layout.setEngine(played);
            break;
        }
    }

    // Check Computer Hand (if Human didn't have it)
    if (!humanHasEngine) {
        for (int i = 0; i < m_computer.getHand().getSize(); ++i) {
            if (m_computer.getHand().getTileAtIndex(i) == engineTile) {
                computerHasEngine = true;

                Tile played;
                m_computer.getHand().playTile(i, played);
                m_layout.setEngine(played);
                break;
            }
        }
    }

    // 6. Set Turn Logic based on Engine ownership
    if (humanHasEngine) {
        std::cout << " >> Human holds the Engine " << pips << "-" << pips << " and plays first.\n";
        m_isHumanTurn = false; // Next turn is Computer's because Human just played
    }
    else if (computerHasEngine) {
        std::cout << " >> Computer holds the Engine " << pips << "-" << pips << " and plays first.\n";
        m_isHumanTurn = true; // Next turn is Human's because Computer just played
    }
    else {
        // Neither has it; draw from stock and place it
        std::cout << " >> Neither player holds the Engine " << pips << "-" << pips << ".\n"
            << " >> Players will draw from the boneyard alternatively until the Engine is found." << std::endl;

        bool engineFound = false;

        while (!engineFound && !m_stock.isEmpty()) {
            // Human draws first
            Tile drawn;
            if (m_stock.drawTile(drawn)) {
                m_human.getHand().addTile(drawn);
                std::cout << "Human draws: " << drawn.getLeftPips() << "-" << drawn.getRightPips() << std::endl;

                if (drawn == engineTile) {
                    std::cout << " >> Engine found by Human. Human plays first." << std::endl;

                    Tile played;
                    int playedIndex = m_human.getHand().getSize() - 1;
                    m_human.getHand().playTile(playedIndex, played);

                    m_layout.setEngine(played);
                    // Computer goes next because Human just played
                    m_isHumanTurn = false;
                    engineFound = true;
                    break;
                }
            }

            if (m_stock.isEmpty()) { break; }

            if (m_stock.drawTile(drawn)) {
                m_computer.getHand().addTile(drawn);
                std::cout << "Computer draws: " << drawn.getLeftPips() << "-" << drawn.getRightPips() << std::endl;

                if (drawn == engineTile) {
                    std::cout << " >> Engine found by Computer. Computer plays first." << std::endl;

                    Tile played;
                    int playedIndex = m_computer.getHand().getSize() - 1;
                    m_computer.getHand().playTile(playedIndex, played);

                    m_layout.setEngine(played);
                    // Human goes next because Human just played
                    m_isHumanTurn = true;
                    engineFound = true;
                    break;
                }
            }
        }
    }
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

    if (m_layout.isEmpty()) { // Assuming Layout has isEmpty(). If not, check if m_layout.getCount() == 0

        std::cout << " >> Game Loaded or Started with empty board. Locating Engine..." << std::endl;

        // 1. Recalculate what the engine is for this round
        int pips = 6 - ((m_roundNumber - 1) % 7);
        Tile engineTile(pips, pips);
        m_engineValue = pips;

        bool humanHasEngine = false;
        bool computerHasEngine = false;
        bool enginePlayed = false;

        // 2. Check Human Hand
        for (int i = 0; i < m_human.getHand().getSize(); ++i) {
            if (m_human.getHand().getTileAtIndex(i) == engineTile) {
                humanHasEngine = true;
                Tile played;
                m_human.getHand().playTile(i, played);
                m_layout.setEngine(played);
                std::cout << " >> Human holds the Engine " << pips << "-" << pips << " and plays first.\n";

                m_isHumanTurn = false; 
                enginePlayed = true;
                break;
            }
        }

        // 3. Check Computer Hand (if Human didn't play it)
        if (!enginePlayed) {
            for (int i = 0; i < m_computer.getHand().getSize(); ++i) {
                if (m_computer.getHand().getTileAtIndex(i) == engineTile) {
                    computerHasEngine = true;
                    Tile played;

                    m_computer.getHand().playTile(i, played);
                    m_layout.setEngine(played);
                    std::cout << " >> Computer holds the Engine " << pips << "-" << pips << " and plays first.\n";
                    m_isHumanTurn = true;
                    enginePlayed = true;
                    break;
                }
            }
        }

        // 4. Alternating Draw Logic (If neither had it initially)
        if (!enginePlayed) {
            std::cout << " >> Neither player holds the Engine " << pips << "-" << pips << ".\n";
            std::cout << " >> Players will draw from the boneyard alternately until the Engine is found.\n";

            while (!enginePlayed && !m_stock.isEmpty()) {
                // -- Human Draw --
                Tile drawn;
                if (m_stock.drawTile(drawn)) {
                    m_human.getHand().addTile(drawn);
                    std::cout << "Human draws: " << drawn.getLeftPips() << "-" << drawn.getRightPips() << "\n";

                    if (drawn == engineTile) {
                        // Play it immediately
                        Tile played;
                        int lastIdx = m_human.getHand().getSize() - 1;
                        m_human.getHand().playTile(lastIdx, played);
                        m_layout.setEngine(played);

                        std::cout << " >> Human found the Engine! Playing to layout.\n";
                        m_isHumanTurn = false;
                        enginePlayed = true;
                        break;
                    }
                }

                if (m_stock.isEmpty()) break;

                // -- Computer Draw --
                if (m_stock.drawTile(drawn)) {
                    m_computer.getHand().addTile(drawn);
                    std::cout << "Computer draws: " << drawn.getLeftPips() << "-" << drawn.getRightPips() << "\n";

                    if (drawn == engineTile) {
                        // Play it immediately
                        Tile played;
                        int lastIdx = m_computer.getHand().getSize() - 1;
                        m_computer.getHand().playTile(lastIdx, played);
                        m_layout.setEngine(played);

                        std::cout << " >> Computer found the Engine! Playing to layout.\n";
                        m_isHumanTurn = true; // Human goes next
                        enginePlayed = true;
                        break;
                    }
                }
            }
        }
    }

    while (!roundOver) {
        // Render the board before every move
        displayGameState();

        if (m_isHumanTurn) {
            // Execute Human turn logic
            while (true) {
                // Prompt user (No flush needed because cin comes next)
                std::cout << "Enter command (play / help / save / quit): ";

                std::string command;
                std::cin >> command;

                if (command == "help") {
                    help();
                    continue;
                }
                else if (command == "save") {
                    // Prompt user (No flush needed because cin comes next)
                    std::cout << "Enter filename to save to: ";

                    std::string filename;
                    std::cin >> filename;

                    if (Serializer::saveGame(filename, tournament)) {
                        std::cout << "Game saved successfully to " << filename << std::endl;
                        std::exit(0);
                    }
                    else {
                        std::cout << "Game save was unsuccessful" << std::endl;
                    }
                }
                else if (command == "quit") {
                    std::cout << "Exiting game..." << std::endl;
                    exit(0);
                }
                else if (command == "play") {
                    break;
                }
                else {
                    std::cout << "Invalid command. Try again." << std::endl;
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
Function Name: help
Purpose: To provide the human player with a recommended move based on
        the current hand and layout state. It evaluates legal moves
        on the player's own side and, if the computer has passed,
        checks for legal moves on the opponent's side.
Parameters: None
Return Value: None (void)
Algorithm:
        1. Iterate through each tile in the human player's hand.
        2. Check if the tile can be legally placed on the LEFT side
            (the human's standard side).
        3. If the computer has passed, check if the tile can be
            legally placed on the RIGHT side (the computer's side).
        4. If a legal move is found, output the suggestion and exit.
        5. If no moves are found in the hand:
            - Suggest drawing if the stock (boneyard) is not empty.
            - Suggest passing if both the hand and boneyard offer no
                options.
Reference: None
********************************************************************* */
void Round::help() {
    const Hand& hand = m_human.getHand();
    bool foundMove = false;

    for (int i = 0; i < hand.getSize(); i++) {
        Tile t = hand.getTileAtIndex(i);

        if (m_layout.isLegalMove(t, 'L')) {
            std::cout << "Suggestion: Play " << t.getLeftPips() << "-" << t.getRightPips()
                << " on the LEFT" << std::endl;

            std::cout << "Reason: This first tile matches the open pips on your side (LEFT).\n"
                << "\tPlaying your own side is the standard move." << std::endl;
            foundMove = true;
            break;
        }

        if (m_computerPassed && m_layout.isLegalMove(t, 'R')) {
            std::cout << "Suggestion: Play " << t.getLeftPips() << "-" << t.getRightPips() 
                << " on the RIGHT" << std::endl;
            
            std::cout << "Reason: You can play on the Computer's side (RIGHT) because\n"
                << "\tthe computer passed on their previous turn and no moves are available on your side." << std::endl;

            foundMove = true;
            break;
        }
    }

    if (!foundMove) {
        if (!m_stock.isEmpty()) {
            std::cout << "No moves found. You Should DRAW." << std::endl;
            std::cout << "Reason: You have no tiles that match either the left or right side." << std::endl;
        }
        else {
            std::cout << "No moves and boneyard is empty. You must PASS." << std::endl;
            std::cout << "Reason: You have no legal moves and the boneyard is empty, you must forfeit your turn" << std::endl;
        }
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
        std::cout << "*** Human Wins Round! + " << points << " points ***" << std::endl;
        return true;
    }

    // Check for a standard "Out" win for the Computer
    if (m_computer.isHandEmpty()) {
        int points = m_human.getHand().getHandScore();
        m_computer.setScore(m_computer.getScore() + points);
        std::cout << "*** Computer Wins Round! + " << points << " points ***" << std::endl;
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
            std::cout << "*** Human Wins the Block! + " << points << " points ***" << std::endl;
        }
        else if (computerTotal < humanTotal) {
            int points = humanTotal;
            m_computer.setScore(m_computer.getScore() + points);
            std::cout << "*** Computer Wins the Block! + " << points << " points ***" << std::endl;
        }
        else {
            std::cout << "*** It's a Tie! 0 points awarded. ***" << std::endl;
        }

        return true;
    }

    return false;
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