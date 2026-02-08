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
             4. Set m_isResumed to false.
             5. Set m_currentRound to 1, 0, 0, 0.
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

    /* *********************************************************************
    Function Name: getTargetScore
    Purpose: To retrieve the point threshold required to win the game.
    Parameters: None
    Return Value: An integer representing the target score (e.g., 61).
    Algorithm: Returns the value stored in the m_targetScore member variable.
    Reference: None
    ********************************************************************* */
    inline int getTargetScore() const { return m_targetScore; }

    /* *********************************************************************
    Function Name: getRoundNumber
    Purpose: To retrieve the current round number in the game sequence.
    Parameters: None
    Return Value: An integer representing the current round (e.g., 1, 2, 3).
    Algorithm: Returns the value of the m_roundNumber member variable.
    Reference: None
    ********************************************************************* */
    inline int getRoundNumber() const { return m_roundNumber; }

    /* *********************************************************************
    Function Name: getHumanScore
    Purpose: To retrieve the cumulative score accumulated by the human player.
    Parameters: None
    Return Value: An integer representing the human player's total points.
    Algorithm: Returns the value of the m_totalHumanScore member variable.
    Reference: None
    ********************************************************************* */
    inline int getHumanScore() const { return m_totalHumanScore; }

    /* *********************************************************************
    Function Name: getComputerScore
    Purpose: To retrieve the cumulative score accumulated by the computer player.
    Parameters: None
    Return Value: An integer representing the computer player's total points.
    Algorithm: Returns the value of the m_totalComputerScore member variable.
    Reference: None
    ********************************************************************* */
    inline int getComputerScore() const { return m_totalComputerScore; }

    /* *********************************************************************
    Function Name: getHumanHand
    Purpose: To provide access to the human player's current hand of tiles.
    Parameters: None
    Return Value: A const reference to a Hand object.
    Algorithm: Returns the result of the getHumanHand() call from the
            m_currentRound member object.
    Reference: None
    ********************************************************************* */
    const Hand& getHumanHand() const { return m_currentRound.getHumanHand(); }

    /* *********************************************************************
    Function Name: getComputerHand
    Purpose: To provide access to the computer player's current hand of tiles.
    Parameters: None
    Return Value: A const reference to a Hand object.
    Algorithm: Returns the result of the getComputerHand() call from the
            m_currentRound member object.
    Reference: None
    ********************************************************************* */
    const Hand& getComputerHand() const { return m_currentRound.getComputerHand(); }

    /* *********************************************************************
    Function Name: getLayout
    Purpose: To provide access to the current arrangement of tiles on the
            game board (the layout).
    Parameters: None
    Return Value: A const reference to a Layout object.
    Algorithm: Returns the result of the getLayout() call from the
            m_currentRound member object.
    Reference: None
    ********************************************************************* */
    const Layout& getLayout() const { return m_currentRound.getLayout(); } 

    /* *********************************************************************
    Function Name: getStock
    Purpose: To provide access to the boneyard (stock) of tiles remaining
            in the current round.
    Parameters: None
    Return Value: A const reference to a Stock object.
    Algorithm: Returns the result of the getStock() call from the
            m_currentRound member object.
    Reference: None
    ********************************************************************* */
    const Stock& getStock() const { return m_currentRound.getStock(); }

    /* *********************************************************************
    Function Name: isHumanTurn
    Purpose: To determine if it is currently the human player's turn to move.
    Parameters: None
    Return Value: A boolean; true if it is the human's turn, false if it
            is the computer's turn.
    Algorithm: Returns the result of the isHumanTurn() call from the
            m_currentRound member object.
    Reference: None
    ********************************************************************* */
    inline bool isHumanTurn() const { return m_currentRound.isHumanTurn(); }

    /* *********************************************************************
    Function Name: isPreviousPassed
    Purpose: To determine if the player who just moved (the previous player)
            passed their turn due to having no playable tiles.
    Parameters: None
    Return Value: A boolean; true if the opponent of the current player
            passed, false otherwise.
    Algorithm: 
            1. Check whose turn it is using isHumanTurn().
            2. If it is the human's turn, return the computer's pass status.
            3. If it is the computer's turn, return the human's pass status.
    Reference: None
    ********************************************************************* */
    inline bool isPreviousPassed() const { 
        return m_currentRound.isHumanTurn() ? m_currentRound.getComputerPassed() : m_currentRound.getHumanPassed(); 
    }

    /* *********************************************************************
    Function Name: getCurrentRound
    Purpose: To provide a non-const reference to the current round object.
            This allows the game controller to modify round state.
    Parameters: None
    Return Value: A reference to the current Round object.
    Algorithm: Returns the m_currentRound member variable.
    Reference: None
    ********************************************************************* */
    inline Round& getCurrentRound() { return m_currentRound; }

    /* --- Mutators --- */

    /* *********************************************************************
    Function Name: setTargetScore
    Purpose: To establish the point threshold required to win the game.
    Parameters:
            targetScore, an integer representing the goal score (e.g., 61).
    Return Value: None (void)
    Algorithm: Assigns the value of the targetScore parameter to the
            m_targetScore member variable.
    Reference: None
    ********************************************************************* */
    inline void setTargetScore(int targetScore) { m_targetScore = targetScore; }

    /* *********************************************************************
    Function Name: setRoundNumber
    Purpose: To set the current round index for the game.
    Parameters:
            roundNumber, an integer representing the current round (e.g., 1).
    Return Value: None (void)
    Algorithm: Assigns the value of the roundNumber parameter to the
            m_roundNumber member variable.
    Reference: None
    ********************************************************************* */
    inline void setRoundNumber(int roundNumber) { m_roundNumber = roundNumber; }

    /* *********************************************************************
    Function Name: setHumanScore
    Purpose: To set the cumulative score for the human player.
    Parameters:
            score, an integer representing the new total human score.
    Return Value: None (void)
    Algorithm: Assigns the value of the score parameter to the
            m_totalHumanScore member variable.
    Reference: None
    ********************************************************************* */
    inline void setHumanScore(int score) { m_totalHumanScore = score; }

    /* *********************************************************************
    Function Name: setComputerScore
    Purpose: To set the cumulative score for the computer player.
    Parameters:
            score, an integer representing the new total computer score.
    Return Value: None (void)
    Algorithm: Assigns the value of the score parameter to the
            m_totalComputerScore member variable.
    Reference: None
    ******************************************************************** */
    inline void setComputerScore(int score) { m_totalComputerScore = score; }

    /* *********************************************************************
    Function Name: setHumanPassed
    Purpose: To update the human player's pass status for the current turn.
    Parameters:
            passed, a boolean indicating if the human player has passed (true)
                or successfully made a move (false).
    Return Value: None (void)
    Algorithm: Calls the setHumanPassed() method on the m_currentRound
            member object with the provided boolean value.
    Reference: None
    ********************************************************************* */
    inline void setHumanPassed(bool passed) { m_currentRound.setHumanPassed(passed); }

    /* *********************************************************************
    Function Name: setComputerPassed
    Purpose: To update the computer player's pass status for the current turn.
    Parameters:
            passed, a boolean indicating if the computer player has passed (true)
                or successfully made a move (false).
    Return Value: None (void)
    Algorithm: Calls the setComputerPassed() method on the m_currentRound
            member object with the provided boolean value.
    Reference: None
    ********************************************************************* */
    inline void setComputerPassed(bool passed) { m_currentRound.setComputerPassed(passed); }

    /* *********************************************************************
    Name: setIsResumed
    Purpose: To set the flag indicating whether the current game session
            was loaded from a save file.
    Parameters:
            resumed, a boolean where true indicates a resumed game and
                false indicates a fresh game.
    Return Value: None (void)
    Algorithm: Assigns the value of the resumed parameter to the
            m_isResumed member variable.
    Reference: None
    ********************************************************************* */
    void setIsResumed(bool resumed) { m_isResumed = resumed; }

    /* --- Utility Functions --- */

    /* *********************************************************************
    Function Name: playTournament
    Purpose: Acts as the main driver for the entire application. It handles
            the initial setup, maintains the tournament-wide scores, and
            manages the progression from one round to the next.
    Parameters: None
    Return Value: None (void)
    Algorithm:
            1. Display the tournament welcome banner.
            2. Prompt the user for a target winning score; validate that the
                input is a positive integer.
            3. Enter a loop that continues as long as both players' total
                scores are below the target score.
            4. Within the loop, instantiate a Round object, passing in
                the current tournament state (scores and round number).
            5. Call playRound() to execute the game logic for that round.
            6. Retrieve the updated scores from the Round object and update
                the tournament's persistent score variables.
            7. If the tournament is not yet won, wait for user input and
                increment the round counter.
            8. Once a player reaches the target, call announceWinner().
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
    Purpose: Compares the final tournament scores and outputs the final
            standings and the winner's announcement.
    Parameters: None
    Return Value: None (void)
    Algorithm:
            1. Print the final results header.
            2. Display final scores for the Human and Computer against the target.
            3. If both players exceeded the target in the same round, the
                player with the higher score is declared the winner.
            4. If only one player exceeded the target, they are the winner.
            5. In the event of an exact tie above the target, declare a draw.
    Reference: None
    ********************************************************************* */
    void announceWinner() const;

};

#endif