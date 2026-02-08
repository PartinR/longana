#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <string>
#include "Tournament.h"

class Serializer {
public:
    /* --- Constructor --- */

    /* *********************************************************************
    Function Name: Serializer (Constructor)
    Purpose: To prevent instantiation of the Serializer class. This class
            acts as a static utility library for saving and loading games.
    Parameters: None
    Return Value: None
    Algorithm: None (Function is deleted)
    Reference: None
    ********************************************************************* */
    Serializer() = delete;

    /* --- Destructor --- */

    /* *********************************************************************
    Function Name: ~Serializer (Destructor)
    Purpose: To prevent the destruction of Serializer objects, ensuring
            the class is used strictly in a static context.
    Parameters: None
    Return Value: None
    Algorithm: None (Function is deleted)
    Reference: None
    ********************************************************************* */
    ~Serializer() = delete;

    /* --- Utility Functions --- */

    /* *********************************************************************
    Function Name: saveGame
    Purpose: Serializes the current state of the tournament and round into
            a formatted text file.
    Parameters:
            filename, a string representing the output file path.
            tournament, a const reference to the Tournament object to be saved.
    Return Value:
            Boolean true if the file was opened and written successfully;
                false otherwise.
    Algorithm:
            1. Attempt to open the file output stream.
            2. If open fails, print error and return false.
            3. Write Tournament Score and Round Number.
            4. Write Computer's Hand and Score.
            5. Write Human's Hand and Score.
            6. Write the current Layout and Boneyard (Stock).
            7. Write state flags (Previous Player Passed, Next Player).
            8. Close file and return true.
    Reference: None
    ********************************************************************* */
    static bool saveGame(const std::string& filename, const Tournament& tournament);

    /* *********************************************************************
    Function Name: loadGame
    Purpose: Parses a saved game file and reconstructs the tournament state.
    Parameters:
            filename, a string representing the input file path.
            tournament, a reference to the Tournament object to be populated.
    Return Value:
            Boolean true if the file was parsed successfully; false otherwise.
    Algorithm:
            1. Open the file input stream. Return false on failure.
            2. Read the file line by line.
            3. Use stringstream to extract keys (e.g., "Round", "Computer:").
            4. Based on the key, parse the associated value (int, string, or boolean).
            5. Delegate complex parsing (Hands, Layout) to their respective classes
                using loadFromString().
            6. Set the 'Next Player' and 'Passed' flags based on parsed strings.
            7. Close file and return true.
    Reference: None
    ********************************************************************* */
    static bool loadGame(const std::string& filename, Tournament& tournament);

};

#endif