/************************************************************
 * Name:  Race Partin                                       *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include <iostream>
#include <string>
#include "Tournament.h"
#include "Serializer.h"

/* *********************************************************************
Function Name: main
Purpose: The entry point of the Longana application. It initializes the
        tournament controller, handles the initial menu for new or
        saved games, and starts the game execution.
Parameters: None
Return Value: Integer 0 upon successful completion.
Algorithm:
        1. Instantiate a Tournament object named 'game'.
        2. Display the main menu (Start New Game vs. Load Game).
        3. Capture and validate user input.
        4. If 'Load Game' is selected:
            a. Prompt for the filename.
            b. Call Serializer::loadGame to populate the 'game' object.
            c. Report success or failure.
        5. Call the playTournament() method to begin the round-robin play.
        6. Return 0 to the operating system.
Reference: None
********************************************************************* */
int main() {
    // Create tournament object
    Tournament game;

    // Display menu options to user
    std::cout << "Welcome to Longana!\n"
        << "1. Start New Game\n"
        << "2. Load Game\n"
        << ">> " << std::flush;

    int choice;
    if (!(std::cin >> choice)) {
        // Invalid input, exit
        return 0;
    }

    // Handle load game scenario
    if (choice == 2) {
        std::string filename;

        std::cout << "Enter filename to load: ";
        std::cin >> filename;

        // Attempt to populate the tournament object with data from file
        if (Serializer::loadGame(filename, game)) {
            std::cout << "Game loaded successfully." << std::endl;
        }
        else {
            // If loading fails, print error and continue to new game
            std::cerr << "Error: Could not load game. Starting new game instead." << std::endl;
        }
    }

    // Execute the primary game loop through the tournament interface
    // This will handle user input for target score and round coordination
    game.playTournament();

    return 0;
}