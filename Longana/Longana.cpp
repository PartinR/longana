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
    int choice;

    while (true) {
        // Display menu options to user
        std::cout << "Welcome to Longana!\n"
            << "1. Start New Game\n"
            << "2. Load Game\n"
            << ">> " << std::flush;

        // Input validation block
        if (!(std::cin >> choice)) {
            // Scenario 1: Input was not an integer (e.g., "a")
            std::cout << "Invalid input. Please enter a number.\n" << std::endl;
            std::cin.clear(); // Reset the failbit
            std::cin.ignore(1000, '\n'); // Clear the buffer
        }
        else if (choice != 1 && choice != 2) {
            // Scenario 2: Input was an integer, but not 1 or 2
            std::cout << "Invalid option. Please enter 1 or 2.\n" << std::endl;
        }
        else {
            // Scenario 3: Valid input
            break; // Exit the while loop
        }
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
    game.playTournament();

    return 0;
}