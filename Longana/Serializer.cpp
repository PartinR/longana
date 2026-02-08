/************************************************************
 * Name:  Race Partin                                       *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Serializer.h"
#include "Tournament.h"

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
bool Serializer::saveGame(const std::string& filename, const Tournament& tournament) {
    // Open file for writing
    std::ofstream outFile(filename);

    // Verify file access
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << filename << std::endl;
        return false;
    }

    // --- Serialize Tourament Data ---
    outFile << "Tournament Score: " << tournament.getTargetScore() << "\n";

    // --- Serialize Round Data ---
    outFile << "Round No.: " << tournament.getRoundNumber() << "\n\n";
    
    // --- Serialize Computer Data ---
    outFile << "Computer:" << "\n";
    outFile << "\tHand: " << tournament.getComputerHand().toString() << "\n";
    outFile << "\tScore: " << tournament.getComputerScore() << "\n\n";

    // --- Serialize Human Data --- 
    outFile << "Human:" << "\n";
    outFile << "\tHand: " << tournament.getHumanHand().toString() << "\n";
    outFile << "\tScore: " << tournament.getHumanScore() << "\n\n";

    // --- Serialize Board Layout ---
    outFile << "Layout:" << "\n";
    outFile << "\t" << tournament.getLayout().toString() << "\n\n";

    outFile << "Boneyard:" << "\n";
    outFile << "\t" << tournament.getStock().toString() << "\n\n";

    outFile << "Previous Player Passed: " << (tournament.isPreviousPassed() ? "Yes" : "No") << "\n\n";
    outFile << "Next Player: " << (tournament.isHumanTurn() ? "Human" : "Computer");

    outFile.close();
    return true;
}

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
bool Serializer::loadGame(const std::string& filename, Tournament& tournament) {
    // Open file for reading
    std::ifstream inFile(filename);

    // Verify file access
    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open file for reading: " << filename << std::endl;
        return false;
    }

    std::string line, key;
    std::string currentSection;

    // Temporary storage of turn flags
    bool tempPreviousPassed = false;
    bool isHumanTurn = true;

    // Read the file line by line
    while (std::getline(inFile, line)) {
        // Skip empty lines
        if (line.empty()) { continue; }

        // Extract the first word
        std::stringstream ss(line);
        ss >> key;
        
        // --- Parse Tournament Data ---
        if (key == "Tournament") {
            std::string temp;
            ss >> temp;
            if (temp == "Score:") {
                int score;
                ss >> score;
                tournament.setTargetScore(score);
            }
        }
        // --- Parse Round Data ---
        else if (key == "Round") {
            std::string temp;
            ss >> temp;
            if (temp == "No.:") {
                int round;
                ss >> round;

                tournament.setRoundNumber(round);
                tournament.getCurrentRound().setRoundNumber(round);
            }
        }
        // --- Context Switching ---
        else if (key == "Computer:") {
            currentSection = "Computer";
        }
        else if (key == "Human:") {
            currentSection = "Human";
        }
        // --- Parse Hand Data ---
        else if (key == "Hand:") {
            std::string handTiles;
            std::getline(ss, handTiles);

            if (currentSection == "Computer") {
                tournament.getCurrentRound().getComputerHand().loadFromString(handTiles);
            } else if (currentSection == "Human") {
                tournament.getCurrentRound().getHumanHand().loadFromString(handTiles);
            }
        }
        // --- Parse Scores ---
        else if (key == "Score:") {
            int score;
            ss >> score;

            if (currentSection == "Computer") {
                tournament.setComputerScore(score);
            }
            else if (currentSection == "Human") {
                tournament.setHumanScore(score);
            }
        }
        // --- Parse Board Layout --- 
        else if (key == "Layout:") {
            std::string layoutData;

            if (std::getline(inFile, layoutData)) {
                tournament.getCurrentRound().getLayout().loadFromString(layoutData);
            }
        }
        else if (key == "Boneyard:") {
            std::string boneyardData;
            
            if (std::getline(inFile, boneyardData)) {
                tournament.getCurrentRound().getStock().loadFromString(boneyardData);
            }
        }
        // --- Parse Turn Flags ---
        else if (key == "Previous:") {
            std::string temp;
            // Eat 'Player' and 'Passed:'
            ss >> temp;
            ss >> temp;
            
            std::string val;
            ss >> val;
            tempPreviousPassed = (val == "Yes");
        }
        else if (key == "Next") {
            std::string temp;
            // Eat 'Player:'
            ss >> temp;

            std::string val;
            ss >> val;
            isHumanTurn = (val == "Human");
            tournament.getCurrentRound().setHumanTurn(isHumanTurn);
        }       
    }
    if (!isHumanTurn) {
        tournament.setComputerPassed(tempPreviousPassed);
        tournament.setHumanPassed(false);
    }
    else {
        tournament.setHumanPassed(tempPreviousPassed);
        tournament.setComputerPassed(false);
    }

    inFile.close();

    tournament.setIsResumed(true);

    return true;
}