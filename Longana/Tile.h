#ifndef TILE_H
#define TILE_H

/**
 * Class Name: Tile
 * Purpose: Models a single domino tile with two ends (pips).
 */
class Tile {
public:
    /* --- Constructors --- */

    /// <summary>
    /// Default constructor that initializes both left and right pip counts to 0.
    /// </summary>
    Tile() : m_left_pips(0), m_right_pips(0) {}

    /// <summary>
    /// Constructs a Tile initialized with the given left and right integer values.
    /// </summary>
    /// <param name="left">An integer specifying the tile's left value.</param>
    /// <param name="right">An integer specifying the tile's right value.</param>
    Tile(int left, int right);

    /* --- Destructor --- */

    /// <summary>
    /// Destructor for the Tile class. Destroys the object; this implementation performs no special cleanup.
    /// </summary>
    ~Tile() {}

    /* --- Selectors --- */

    /// <summary>
    /// Returns the stored left pips value (inline const getter).
    /// </summary>
    /// <returns>The left pips value as an int.</returns>
    inline int getLeftPips() const { return m_left_pips; }

    /// <summary>
    /// Returns the stored right pips value (inline const getter).
    /// </summary>
    /// <returns>The right pips value as an int.</returns>
    inline int getRightPips() const { return m_right_pips; }

    /// <summary>
    /// Returns the sum of m_left_pips and m_right_pips.
    /// </summary>
    /// <returns>The sum of m_left_pips and m_right_pips.</returns>
    inline int getSum() const { return m_left_pips + m_right_pips; }

    /// <summary>
    /// Checks whether the left and right pips are equal.
    /// </summary>
    /// <returns>true if m_left_pips equals m_right_pips; otherwise false.</returns>
    inline bool isDouble() const { return m_left_pips == m_right_pips; }

    /// <summary>
    /// Compares this Tile with another for equality.
    /// </summary>
    /// <param name="other">The Tile to compare against.</param>
    /// <returns>true if this Tile is equal to other; otherwise false.</returns>
    bool operator==(const Tile& other) const;

    /* --- Mutators --- */

    /// <summary>
    /// Sets the number of left pips.
    /// </summary>
    /// <param name="pips">The number of pips to apply to the left side.</param>
    /// <returns>true if the left pips were set successfully; otherwise false.</returns>
    bool setLeftPips(int pips);

    /// <summary>
    /// Sets the number of pips on the right side.
    /// </summary>
    /// <param name="pips">The number of pips to set.</param>
    /// <returns>true if the pips were set successfully; false otherwise.</returns>
    bool setRightPips(int pips);

    /* --- Utility Functions --- */

    /// <summary>
    /// Flips a tile.
    /// </summary>
    void flipTile();

private:
    /* --- Constants --- */
    static const int MIN_PIPS = 0;
    static const int MAX_PIPS = 6;

    /* --- Variables --- */
    int m_left_pips;
    int m_right_pips;
};

#endif