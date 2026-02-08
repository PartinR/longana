#ifndef PLAYER_H
#define PLAYER_H

/************************************************************
 * Name:  Race Partin                                       *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include "Hand.h"
#include "Layout.h"
#include "Stock.h"
#include "Tile.h"

/* *********************************************************************
Class Name: Player
Purpose: An abstract base class representing a generic player in the
        Longana game. It manages the common state (Hand and Score) and
        defines the interface for playing a turn, which must be implemented
        by derived classes (Human and Computer).
********************************************************************* */
class Player {
public:

    /* --- Constructor --- */

    /* *********************************************************************
    Function Name: Player
    Purpose: Default constructor. Initializes a new player with a score of 0
            and an empty hand.
    Parameters: None
    Return Value: None
    Algorithm:
            1. Initialize m_score to 0.
            2. Hand constructor is called implicitly.
    Reference: None
    ********************************************************************* */
    Player() : m_score(0) {}

    /* --- Destructor --- */

    /* *********************************************************************
    Function Name: ~Player
    Purpose: Virtual destructor. Ensures proper cleanup of resources when
            a derived class object is deleted through a base class pointer.
    Parameters: None
    Return Value: None
    Algorithm: Standard virtual destructor behavior.
    Reference: None
    ********************************************************************* */
    virtual ~Player() = default;

    /* --- Selectors --- */

    /* *********************************************************************
    Function Name: getHand
    Purpose: Provides read-only access to the player's hand.
    Parameters: None
    Return Value: A constant reference to the internal Hand object.
    Algorithm: Return m_hand.
    Reference: None
    ********************************************************************* */
    inline const Hand& getHand() const { return m_hand; }

    /* *********************************************************************
    Function Name: getHand
    Purpose: To retrieve a reference to the player's Hand object. This
            allows other components (like the View or Controller) to
            inspect or modify the tiles held by the player.
    Parameters: None
    Return Value: A reference to a Hand object (Hand&).
    Algorithm:
            1. Return the m_hand member variable by reference.
    Reference: None
    ********************************************************************* */
    inline Hand& getHand() { return m_hand; }

    /* *********************************************************************
    Function Name: getScore
    Purpose: Retrieves the player's current tournament score.
    Parameters: None
    Return Value: An integer representing the total score.
    Algorithm: Return m_score.
    Reference: None
    ********************************************************************* */
    inline int getScore() const { return m_score; }

    /* *********************************************************************
    Function Name: setScore
    Purpose: Updates the player's total score (e.g., after a round ends).
    Parameters:
            score, an integer passed by value. The new total score.
    Return Value: None (void)
    Algorithm: Assign the parameter score to m_score.
    Reference: None
    ********************************************************************* */
    inline void setScore(int score) { m_score = score; }

    /* --- Mutators --- */

    /* *********************************************************************
    Function Name: addTileToHand
    Purpose: Adds a single tile to the player's hand.
    Parameters:
            tile, a Tile object passed by const reference.
    Return Value: None (void)
    Algorithm: Delegate to m_hand.addTile(tile).
    Reference: None
    ********************************************************************* */
    inline void addTileToHand(const Tile& tile) { m_hand.addTile(tile); }

    /* *********************************************************************
    Function Name: removeSpecificTile
    Purpose: Searches the player's hand for a specific tile and removes it if
            found. This is used for placing the Engine tile at the start of
            a round.
    Parameters:
            target, a Tile object passed by const reference. The tile to find.
    Return Value: Boolean true if the tile was found and removed, false otherwise.
    Algorithm:
            1. Iterate through the player's hand using a loop from 0 to hand size.
            2. For each tile, compare its left and right pips to the target tile.
            3. If a match is found:
                a. Use the hand's playTile method to remove the tile at that index.
                b. Return true immediately.
            4. If the loop completes without a match, return false.
    Reference: None
    ********************************************************************* */
    bool removeSpecificTile(const Tile& target);

    /* --- Utility Functions --- */

    /* *********************************************************************
    Function Name: isHandEmpty
    Purpose: Checks if the player has played all their tiles (winning condition).
    Parameters: None
    Return Value: true if hand is empty, false otherwise.
    Algorithm: Return m_hand.isEmpty().
    Reference: None
    ********************************************************************* */
    inline bool isHandEmpty() const { return m_hand.isEmpty(); }

    /* *********************************************************************
    Function Name: getHandSize
    Purpose: Retrieves the count of tiles currently in the hand.
    Parameters: None
    Return Value: An integer count.
    Algorithm: Return m_hand.getSize().
    Reference: None
    ********************************************************************* */
    inline int getHandSize() const { return m_hand.getSize(); }

    /* *********************************************************************
    Function Name: playTurn
    Purpose: Pure virtual function defining the interface for a turn.
            Derived classes must implement their specific turn logic here.
    Parameters:
            layout, a Layout object passed by reference.
            stock, a Stock object passed by reference.
            opponentPassed, a boolean indicating if the opponent passed.
    Return Value: true if a move was made, false if passed.
    Algorithm: N/A (Abstract function)
    Reference: None
    ********************************************************************* */
    virtual bool playTurn(Layout& layout, Stock& stock, bool opponentPassed) = 0;

protected:
    Hand m_hand;
    int m_score;

};

#endif