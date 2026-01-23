#pragma once

/**
 * Class Name: Tile
 * Purpose: Models a single domino tile with two ends (pips).
 */
class Tile {
public:
    /* --- Constructors --- */

    // Default constructor - set pips to 0
    // Use member initializer syntax
    Tile() : m_left_pips(0), m_right_pips(0) {}

    // Constructor with values
    Tile(int left, int right);

    /* --- Destructor --- */
    ~Tile() {}

    /* --- Selectors --- */

    // Returns the value of the left side
    inline int getLeftPips() const { return m_left_pips; }

    // Returns the value of the right side
    inline int getRightPips() const { return m_right_pips; }

    // Returns total pips for scoring
    inline int getSum() const { return m_left_pips + m_right_pips; }

    // Check if tiles is a double
    inline bool isDouble() const { return m_left_pips == m_right_pips; }

    // Logic for equality
    bool operator==(const Tile& other) const;

    /* --- Mutators --- */

    // Set left pips, returns true if successful
    bool setLeftPips(int pips);

    // Set right pips, returns true if successful
    bool setRightPips(int pips);

    /* --- Utility Functions --- */

    // Swap left and right pips
    void flipTile();

private:
    /* --- Constants --- */
    static const int MIN_PIPS = 0;
    static const int MAX_PIPS = 6;

    /* --- Variables --- */
    int m_left_pips;
    int m_right_pips;
};