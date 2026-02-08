#ifndef TOURNAMENT_H
#define TOURNAMENT_H

/************************************************************
 * Name:  Race Partin                                       *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include "Round.h"
#include "Hand.h"
#include "Layout.h"
#include "Stock.h"

/* *********************************************************************
Class Name: Tournament
Purpose: Acts as the high-level controller for the Longana game. It
        manages the overall tournament state, including the target score
        set by the user, the accumulation of points across multiple
        rounds, and the determination of the final winner.
********************************************************************* */
class Tournament {
public:

    /* --- Constructor --- */

    /* *********************************************************************
    Function Name: Tournament
    Purpose: Default constructor. Initializes the tournament state,
             setting all scores to zero and the starting round to one.
    Parameters: None
    Return Value: None
    Algorithm:
             1. Set m_totalHumanScore and m_totalComputerScore to 0.
             2. Set m_targetScore to 0.
             3. Set m_roundNumber to 1.
    Reference: None
    ********************************************************************* */
    Tournament()
        : m_totalHumanScore(0), m_totalComputerScore(0), m_targetScore(0), 
        m_roundNumber(1), m_isResumed(false), m_currentRound(1, 0, 0, 0)
    {
    }

    /* --- Destructor --- */

    /* *********************************************************************
    Function Name: ~Tournament
    Purpose: Destructor. Cleans up the Tournament object when it is destroyed.
    Parameters: None
    Return Value: None
    Algorithm: Standard object destruction.
    Reference: None
    ********************************************************************* */
    ~Tournament() = default;

    /* --- Selectors --- */

    inline int getTargetScore() const { return m_targetScore; }

    inline int getRoundNumber() const { return m_roundNumber; }

    inline int getHumanScore() const { return m_totalHumanScore; }

    inline int getComputerScore() const { return m_totalComputerScore; }

    const Hand& getHumanHand() const { return m_currentRound.getHumanHand(); }

    const Hand& getComputerHand() const { return m_currentRound.getComputerHand(); }

    const Layout& getLayout() const { return m_currentRound.getLayout(); } 

    const Stock& getStock() const { return m_currentRound.getStock(); }

    inline bool isHumanTurn() const { return m_currentRound.isHumanTurn(); }

    inline bool isPreviousPassed() const { 
        return m_currentRound.isHumanTurn() ? m_currentRound.getComputerPassed() : m_currentRound.getHumanPassed(); 
    }

    inline Round& getCurrentRound() { return m_currentRound; }

    /* --- Mutators --- */

    inline void setTargetScore(int targetScore) { m_targetScore = targetScore; }

    inline void setRoundNumber(int roundNumber) { m_roundNumber = roundNumber; }

    inline void setHumanScore(int score) { m_totalHumanScore = score; }

    inline void setComputerScore(int score) { m_totalComputerScore = score; }

    inline void setHumanPassed(bool passed) { m_currentRound.setHumanPassed(passed); }

    inline const void setComputerPassed(bool passed) { m_currentRound.setComputerPassed(passed); }

    void setIsResumed(bool resumed) { m_isResumed = resumed; }

    /* --- Utility Functions --- */

    /* *********************************************************************
    Function Name: playTournament
    Purpose: Coordinates the execution of the entire tournament. Handles the
             initial user input for the target score and loops through
             Round objects until the winning condition is met.
    Parameters: None
    Return Value: None (void)
    Algorithm:
             1. Prompt the user to enter a target tournament score.
             2. While neither player's score has reached m_targetScore:
                a. Instantiate a Round object with current tournament state.
                b. Call Round::playRound().
                c. Update m_totalHumanScore and m_totalComputerScore from the Round.
                d. Increment m_roundNumber.
             3. Call announceWinner() once the loop terminates.
    Reference: None
    ********************************************************************* */
    void playTournament();

private:

    int m_totalHumanScore;
    int m_totalComputerScore;
    int m_targetScore;
    int m_roundNumber;
    bool m_isResumed;

    Round m_currentRound;

    /* *********************************************************************
    Function Name: announceWinner
    Purpose: Compares the final scores and prints the tournament results
             to the console.
    Parameters: None
    Return Value: None (void)
    Algorithm:
             1. Print final scores for both Human and Computer.
             2. Compare totals to determine the winner or a draw.
             3. Print the winner announcement message.
    Reference: None
    ********************************************************************* */
    void announceWinner() const;

};

#endif