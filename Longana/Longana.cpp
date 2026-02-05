/************************************************************
 * Name:  Race Partin                                       *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include <iostream>
#include "Tournament.h"

 /* *********************************************************************
 Function Name: main
 Purpose: The entry point of the Longana application. It initializes the
          tournament controller and starts the game execution.
 Parameters: None
 Return Value: Integer 0 upon successful completion.
 Algorithm:
          1. Instantiate a Tournament object named 'game'.
          2. Call the playTournament() method to begin the interactive
             setup and round-robin play.
          3. Return 0 to the operating system.
 Reference: None
 ********************************************************************* */
int main() {
    // Create the high-level tournament manager object
    Tournament game;

    // Execute the primary game loop through the tournament interface
    // This will handle user input for target score and round coordination
    game.playTournament();

    return 0;
}