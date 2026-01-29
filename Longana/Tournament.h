#ifndef TOURNAMENT_H
#define TOURNAMENT_H

class Tournament {
public:

    /* --- Constructor --- */

    /// <summary>
    /// Tournament constructor that initializes a Tournament objects.
    /// </summary>
    Tournament() 
        : m_totalHumanScore(0), m_totalComputerScore(0), m_targetScore(0), m_roundNumber(1) 
    {
    }

    /* --- Destructor --- */

    /// <summary>
    /// Tournament destructor. Performs cleanup when a Tournament object is destroyed.
    /// </summary>
    ~Tournament() {}


    /* --- Utility Functions --- */

    /// <summary>
    /// Allows the user to play a full tournament of Longana.
    /// </summary>
    void playTournament();

private:

    int m_totalHumanScore;
    int m_totalComputerScore;
    int m_targetScore;
    int m_roundNumber;

    void announceWinner() const;

};

#endif