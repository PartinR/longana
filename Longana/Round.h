#ifndef ROUND_H
#define ROUND_H

/************************************************************
 * Name:  Race Partin                                       *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include "Human.h"
#include "Computer.h"
#include "Stock.h"
#include "Layout.h"
#include "Hand.h"

class Tournament;

/* *********************************************************************
Class Name: Round
Purpose: Manages the execution of a single round of Longana. It is
        responsible for setting up the round (dealing tiles, finding the engine),
        alternating turns between the Human and Computer, and detecting
        end-of-round conditions (empty hand or blocked game).
********************************************************************* */
class Round {
public:

    /* --- Constructor --- */

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
    Round(int roundNumber, int tournamentTargetScore, int humanScore, int computerScore);

    /* --- Destructor --- */

    /* *********************************************************************
    Function Name: ~Round
    Purpose: Destructor. Clean up resources when the Round ends.
    Parameters: None
    Return Value: None
    Algorithm: Default destruction of member objects (Human, Computer, Layout, Stock).
    Reference: None
    ********************************************************************* */
    ~Round() = default;

    /* --- Selectors --- */

    /* *********************************************************************
    Function Name: getHumanScore
    Purpose: Retrieves the Human's score at the end of the round.
    Parameters: None
    Return Value: int representing the score.
    Algorithm: Return m_human.getScore().
    Reference: None
    ********************************************************************* */
    inline int getHumanScore() const { return m_human.getScore(); }

    /* *********************************************************************
    Function Name: getHumanHand
    Purpose: To provide access to the human player's current collection of
            tiles (hand).
    Parameters: None
    Return Value: A const reference to a Hand object.
    Algorithm: Returns the result of the getHand() method from the
            m_human member object.
    Reference: None
    ********************************************************************* */
    inline const Hand& getHumanHand() const { return m_human.getHand(); }

    /* *********************************************************************
    Function Name: getHumanHand
    Purpose: To provide mutable access to the human player's hand. This
            allows the round logic to modify the hand, such as adding
            tiles from the stock or removing tiles after a move.
    Parameters: None
    Return Value: A reference to a Hand object.
    Algorithm: Returns the result of the getHand() method from the
            m_human member object.
    Reference: None
    ********************************************************************* */
    inline Hand& getHumanHand() { return m_human.getHand(); }

    /* *********************************************************************
    Function Name: getComputerHand
    Purpose: To provide read-only access to the computer player's hand.
            This is typically used for displaying game state or saving
            the tournament progress without risk of modifying the tiles.
    Parameters: None
    Return Value: A const reference to a Hand object.
    Algorithm: Returns the result of the getHand() method from the
            m_computer member object.
    Reference: None
    ********************************************************************* */
    inline const Hand& getComputerHand() const { return m_computer.getHand(); }

    /* *********************************************************************
    Function Name: getComputerHand
    Purpose: To provide mutable access to the computer player's hand. This
            allows the round logic to modify the computer's tiles, such
            as adding a tile from the stock or removing a tile when the
            Computer makes a move.
    Parameters: None
    Return Value: A reference to a Hand object.
    Algorithm: Returns the result of the getHand() method from the
            m_computer member object.
    Reference: None
    ********************************************************************* */
    inline Hand& getComputerHand() { return m_computer.getHand(); }

    /* *********************************************************************
    Function Name: getComputerScore
    Purpose: Retrieves the Computer's score at the end of the round.
    Parameters: None
    Return Value: int representing the score.
    Algorithm: Return m_computer.getScore().
    Reference: None
    ********************************************************************* */
    inline int getComputerScore() const { return m_computer.getScore(); }

    /* *********************************************************************
    Function Name: getLayout
    Purpose: To provide read-only access to the game layout. This allows
            other classes, such as the Tournament or a View class, to
            inspect the current arrangement of tiles on the board without
            modifying them.
    Parameters: None
    Return Value: A const reference to a Layout object.
    Algorithm: Returns the m_layout member variable.
    Reference: None
    ********************************************************************* */
    inline const Layout& getLayout() const { return m_layout; }

    /* *********************************************************************
    Function Name: getLayout
    Purpose: To provide mutable access to the game layout. This allows
            the round logic to update the board state, such as adding
            tiles to the left or right ends of the layout during a turn.
    Parameters: None
    Return Value: A reference to a Layout object.
    Algorithm: Returns the m_layout member variable.
    Reference: None
    ********************************************************************* */
    inline Layout& getLayout() { return m_layout; }

    /* *********************************************************************
    Function Name: getStock
    Purpose: To provide read-only access to the stock (boneyard) of tiles.
            This allows the Tournament or other system components to
            check the number of tiles remaining or the state of the
            stock without modifying it.
    Parameters: None
    Return Value: A const reference to a Stock object.
    Algorithm: Returns the m_stock member variable.
    Reference: None
    ********************************************************************* */
    inline const Stock& getStock() const { return m_stock; }

    /* *********************************************************************
    Function Name: getStock
    Purpose: To provide mutable access to the stock (boneyard). This allows
            the round logic to perform actions such as drawing a tile
            when a player has no legal moves or shuffling the tiles
            during the initial setup.
    Parameters: None
    Return Value: A reference to a Stock object.
    Algorithm: Returns the m_stock member variable.
    Reference: None
    ********************************************************************* */
    inline Stock& getStock() { return m_stock; }

    /* *********************************************************************
    Function Name: isHumanTurn
    Purpose: To determine which player is currently active. This is used
            to control the flow of the round and ensure the correct
            logic is executed for either the human or computer player.
    Parameters: None
    Return Value: A boolean; true if it is the human player's turn,
            false if it is the computer player's turn.
    Algorithm: Returns the value of the m_isHumanTurn member variable.
    Reference: None
    ********************************************************************* */
    inline bool isHumanTurn() const { return m_isHumanTurn; }

    /* *********************************************************************
    Function Name: getHumanPassed
    Purpose: To retrieve the status of whether the human player was forced
            to pass their previous turn due to a lack of playable tiles.
    Parameters: None
    Return Value: A boolean; true if the human player passed, false otherwise.
    Algorithm: Returns the value of the m_humanPassed member variable.
    Reference: None
    ********************************************************************* */
    inline bool getHumanPassed() const { return m_humanPassed; }

    /* *********************************************************************
    Function Name: getComputerPassed
    Purpose: To retrieve the status of whether the computer player was
            forced to pass its previous turn. This is used by the game
            logic to determine if special rules (like playing on the
            opponent's side) are currently active.
    Parameters: None
    Return Value: A boolean; true if the computer player passed, false otherwise.
    Algorithm: Returns the value of the m_computerPassed member variable.
    Reference: None
    ********************************************************************* */
    inline bool getComputerPassed() const { return m_computerPassed; }

    /* --- Mutators --- */

    /* *********************************************************************
    Function Name: setHumanPassed
    Purpose: To update the status of whether the human player has passed
            their turn. This is called when the human draws from the stock
            and still cannot make a move, or reset when they successfully
            play a tile.
    Parameters:
            passed - A boolean indicating the new pass status (true if
                 passed, false if a tile was played).
    Return Value: None
    Algorithm: Assigns the passed parameter to the m_humanPassed member
            variable.
    Reference: None
    ********************************************************************* */
    inline void setHumanPassed(bool passed) { m_humanPassed = passed; }

    /* *********************************************************************
    Function Name: setComputerPassed
    Purpose: To update the status of whether the computer player has passed
            its turn. This status is vital for determining if the human
            player is allowed to play on the computer's "wing" during
            their next move.
    Parameters:
            passed - A boolean indicating the new pass status (true if
                 the computer passed, false if it played a tile).
    Return Value: None
    Algorithm: Assigns the passed parameter to the m_computerPassed
            member variable.
    Reference: None
    ********************************************************************* */
    inline void setComputerPassed(bool passed) { m_computerPassed = passed; }

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
    void prepareRound(int roundNumber);

    /* *********************************************************************
    Function Name: setRoundNumber
    Purpose: To establish or update the current round count within the
            round state. This is primarily used during initialization
            at the start of a new round or when restoring a game from
            a save file.
    Parameters:
            roundNumber - An integer representing the current round
                (e.g., 1, 2, 3...).
    Return Value: None
    Algorithm: Assigns the roundNumber parameter to the m_roundNumber
            member variable.
    Reference: None
    ********************************************************************* */
    inline void setRoundNumber(int roundNumber) { m_roundNumber = roundNumber; }

    /* *********************************************************************
    Function Name: setHumanTurn
    Purpose: To explicitly set which player is active. This is used during
            round initialization to determine the starting player based
            on the engine tile, and during the turn loop to toggle
            control between the human and the computer.
    Parameters:
            isHumanTurn - A boolean indicating the new turn state (true
                for human, false for computer).
    Return Value: None
    Algorithm: Assigns the isHumanTurn parameter to the m_isHumanTurn
            member variable.
    Reference: None
    ********************************************************************* */
    inline void setHumanTurn(bool isHumanTurn) { m_isHumanTurn = isHumanTurn; }

    /* *********************************************************************
    Function Name: setTargetScore
    Purpose: To establish the point threshold required to win the tournament.
            This value acts as the goalpost for the game; once a player's
            cumulative score reaches or exceeds this number, the
            tournament concludes.
    Parameters:
            score - An integer representing the winning point threshold
                (usually provided by the user at the start of the game).
    Return Value: None
    Algorithm: Assigns the score parameter to the m_tournamentScore
            member variable.
    Reference: None
    ********************************************************************* */
    inline void setTargetScore(int score) { m_tournamentScore = score; }

    /* *********************************************************************
    Function Name: setScores
    Purpose: To update the individual scores of both the human and computer
            players within the current round. This is essential when
            initializing a round from a saved state or when synchronizing
            player objects with tournament-wide totals.
    Parameters:
            humanScore - An integer representing the score to be assigned
                to the human player.
            computerScore - An integer representing the score to be assigned
                to the computer player.
    Return Value: None
    Algorithm: 
            1. Calls setScore on the m_human object with the humanScore
                parameter.
            2. Calls setScore on the m_computer object with the
                computerScore parameter.
    Reference: None
    ********************************************************************* */
    inline void setScores(int humanScore, int computerScore) {
        m_human.setScore(humanScore);
        m_computer.setScore(computerScore);
    }

    /* --- Utility Functions --- */

    /* *********************************************************************
    Function Name: playRound
    Purpose: Executes the main game loop for this round. Alternates turns
             until a win condition is met.
    Parameters: None
    Return Value: None (void)
    Algorithm:
             1. Loop while checkWinCondition() is false.
             2. Display game state (Layout, Hands, Scores).
             3. If Human turn: call m_human.playTurn(). Update pass flag.
             4. If Computer turn: call m_computer.playTurn(). Update pass flag.
             5. Toggle m_isHumanTurn.
    Reference: None
    ********************************************************************* */
    void playRound(const Tournament& tournament);

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
    void help();

private:
    int m_roundNumber;
    int m_tournamentScore;

    Human m_human;
    Computer m_computer;

    Stock m_stock;
    Layout m_layout;

    bool m_humanPassed;
    bool m_computerPassed;
    bool m_isHumanTurn;
    int m_engineValue;

    /* *********************************************************************
    Function Name: checkWinCondition
    Purpose: Checks if the round has ended due to a player emptying their hand
             or the game being blocked. Updates scores accordingly.
    Parameters: None
    Return Value: true if the round is over, false otherwise.
    Algorithm:
             1. Check if Human hand is empty -> Add Computer's pips to Human score -> Return true.
             2. Check if Computer hand is empty -> Add Human's pips to Computer score -> Return true.
             3. Check if both players passed and Stock is empty (Block).
                a. Compare pip totals.
                b. Winner gets loser's pips (or own + loser's depending on variant).
                c. Return true.
             4. Return false.
    Reference: None
    ********************************************************************* */
    bool checkWinCondition();

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
    void displayGameState();
};

#endif