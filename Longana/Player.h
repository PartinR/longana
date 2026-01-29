#ifndef PLAYER_H
#define PLAYER_H

#include "Hand.h"
#include "Layout.h"
#include "Stock.h"
#include "Tile.h"

class Player {
protected:
    Hand m_hand;
    int m_score = 0;

public:

    /* --- Constructor --- */

    /// <summary>
    /// Default constructor for Player that initializes the member m_score to 0.
    /// </summary>
    Player() : m_score(0) {}

    /* --- Destructor --- */

    /// <summary>
    /// Virtual destructor for the Player class. Ensures proper cleanup in derived classes.
    /// </summary>
    virtual ~Player() {}

    /* --- Selectors --- */

    /// <summary>
    /// Retreives a read-only reference to the player's hand.
    /// </summary>
    /// <returns>A constant reference to the Hand object.</returns>
    inline const Hand& getHand() const { return m_hand; }

    /// <summary>
    /// Gets the player's current score.
    /// </summary>
    /// <returns>The total accumulated points across rounds.</returns>
    inline int getScore() const { return m_score; }

    /// <summary>
    /// Updates the player's score to the specified value.
    /// </summary>
    /// <param name="score">That integer value to set the new score.</param>
    inline void setScore(int score) { m_score = score; }


    /// <summary>
    /// Adds a tile to the player's hand.
    /// </summary>
    /// <param name="tile">The tile object to be added.</param>
    inline void addTileToHand(const Tile& tile) { m_hand.addTile(tile); }

    /* --- Utility Functions --- */

    /// <summary>
    /// Checks whether the player's hand is empty.
    /// </summary>
    /// <returns>True if empty, false otherwise</returns>
    bool isHandEmpty() const;

    /// <summary>
    /// Gets the size of the player's hand.
    /// </summary>
    /// <returns>The number of tiles in the players hand.</returns>
    int getHandSize() const;
    
    /// <summary>
    /// Virtual function that executes a single turn for the player.
    /// Must be overridden in derived classes.
    /// </summary>
    /// <param name="layout">The current game board layout</param>
    /// <param name="stock">The current boneyard</param>
    /// <param name="opponentPassed">Flag indicating whether the previous player passed.</param>
    /// <returns>True if tile successfully placed, false if player was unable to move and passed.</returns>
    virtual bool playTurn(Layout& layout, Stock& stock, bool opponentPassed) = 0;

};

#endif
