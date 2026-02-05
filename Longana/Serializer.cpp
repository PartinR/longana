#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "Serializer.h"
#include "Tournament.h"

bool Serializer::saveGame(const std::string& filename, const Tournament& tournament) {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << filename << std::endl;
        return false;
    }

    // Implementation for saving the game state to a file
    outFile << "Tournament Score: " << tournament.getTargetScore() << "\n";
    outFile << "Round No.: " << tournament.getRoundNumber() << "\n\n";
    
    outFile << "Computer:" << "\n";
    outFile << "\tHand: " << tournament.getComputerHand().toString() << "\n";
    outFile << "\tScore: " << tournament.getComputerScore() << "\n\n";

    outFile << "Human:" << "\n";
    outFile << "\tHand: " << tournament.getHumanHand().toString() << "\n";
    outFile << "\tScore: " << tournament.getHumanScore() << "\n\n";

    outFile << "Layout:" << "\n";
    outFile << "\t" << tournament.getLayout().toString() << "\n\n";

    outFile << "Boneyard:" << "\n";
    outFile << "\t" << tournament.getStock().toString() << "\n\n";

    outFile << "Previous Player Passed: " << (tournament.isPreviousPassed() ? "Yes" : "No") << "\n\n";

    outFile << "Next Player: " << (tournament.isHumanTurn() ? "Human" : "Computer");

    outFile.close();
    return true;
}

bool Serializer::loadGame(const std::string& filename, Tournament& tournament) {
    std::ifstream inFile(filename);

    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open file for reading: " << filename << std::endl;
        return false;
    }

    std::string line, key;
    std::string currentSection;

    bool tempPreviousPassed = false;
    bool isHumanTurn = true;

    while (std::getline(inFile, line)) {
        if (line.empty()) { continue; }

        std::stringstream ss(line);
        ss >> key;

        if (key == "Tournament") {
            std::string temp;
            ss >> temp;
            if (temp == "Score:") {
                int score;
                ss >> score;
                tournament.setTargetScore(score);
            }
        }
        else if (key == "Round") {
            std::string temp;
            ss >> temp;
            if (temp == "No.:") {
                int round;
                ss >> round;

                tournament.getCurrentRound().prepareRound(round);
                tournament.setRoundNumber(round);
            }
        }
        else if (key == "Computer:") {
            currentSection = "Computer";
        }
        else if (key == "Human:") {
            currentSection = "Human";
        }
        else if (key == "Hand:") {
            std::string handTiles;
            std::getline(ss, handTiles);

            if (currentSection == "Computer") {
                tournament.getCurrentRound().getComputerHand().loadFromString(handTiles);
            } else if (currentSection == "Human") {
                tournament.getCurrentRound().getHumanHand().loadFromString(handTiles);
            }
        }
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
        else if (key == "Layout:") {
            if (std::getline(inFile, line)) {
                tournament.getCurrentRound().getLayout().loadFromString(line);
            }
        }
        else if (key == "Boneyard:") {
            if (std::getline(inFile, line)) {
                tournament.getCurrentRound().getStock().loadFromString(line);
            }
        }
        else if (key == "Previous:") {
            std::string temp;
            ss >> temp;
            ss >> temp;
            
            std::string val;
            ss >> val;
            tempPreviousPassed = (val == "Yes");
        }
        else if (key == "Next") {
            std::string temp;
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
    return true; // Placeholder return value
}