#ifndef ROUND_H
#define ROUND_H

/************************************************************
 * Name:  Race Benjamin Partin                              *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include "Human.h"
#include "Computer.h"
#include "Stock.h"
#include "Layout.h"
#include "Hand.h"

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
    Purpose: Constructor. Initializes a new round, deals tiles to players,
             determines the Engine pip value based on the round number, and
             decides who plays first based on who holds the Engine.
    Parameters:
             roundNumber, int passed by value. The current round number (1-based).
             tournamentTargetScore, int passed by value. Used for display purposes.
             humanScore, int passed by value. The Human's total score entering this round.
             computerScore, int passed by value. The Computer's total score entering this round.
    Return Value: None
    Algorithm:
             1. Store scores and round number.
             2. Calculate Engine value (e.g., Round 1 = 6-6).
             3. Create and shuffle Stock.
             4. Deal 8 tiles to Human and Computer.
             5. Check if Human has Engine -> Human starts.
             6. Else if Computer has Engine -> Computer starts.
             7. Else (Engine in stock) -> Place Engine on Layout, Human starts.
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
    ~Round() {}

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

    inline const Hand& getHumanHand() const { return m_human.getHand(); }

    /* *********************************************************************
    Function Name: getComputerScore
    Purpose: Retrieves the Computer's score at the end of the round.
    Parameters: None
    Return Value: int representing the score.
    Algorithm: Return m_computer.getScore().
    Reference: None
    ********************************************************************* */
    inline int getComputerScore() const { return m_computer.getScore(); }

    inline const Hand& getComputerHand() const { return m_computer.getHand(); }

    inline const Layout& getLayout() const { return m_layout; }

    inline const Stock& getStock() const { return m_stock; }

    inline bool isHumanTurn() const { return m_isHumanTurn; }

    inline bool getHumanPassed() const { return m_humanPassed; }

    inline bool getComputerPassed() const { return m_computerPassed; }

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
    void playRound();

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
    Purpose: Prints the current status of the round to the console.
    Parameters: None
    Return Value: None (void)
    Algorithm:
             1. Print Tournament Score and Round Number.
             2. Print Computer Hand and Score.
             3. Print Human Hand and Score.
             4. Print Layout.
             5. Print Boneyard status.
    Reference: None
    ********************************************************************* */
    void displayGameState();
};

#endif