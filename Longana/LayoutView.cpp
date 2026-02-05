/************************************************************
 * Name:  Race Partin                                       *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include <iostream>
#include <string>
#include "LayoutView.h"
#include "Stock.h"
#include "Layout.h"
#include "Hand.h"
#include "Tile.h"

 /* *********************************************************************
 Function Name: displayHeader
 Purpose: To provide a formatted visual header at the start of each round,
          displaying essential game state metadata to the user.
 Parameters:
          roundNumber, an integer passed by value. The current round index.
          engineValue, an integer passed by value. The pip value of the engine.
          stock, a Stock object passed by const reference. Used to query the boneyard count.
 Return Value: None (void)
 Algorithm:
          1. Print a leading newline for spacing.
          2. Print the round number inside decorative borders.
          3. Display the required engine value for the round.
          4. Query the stock for the remaining tile count and print it.
 Reference: None
 ********************************************************************* */
void LayoutView::displayHeader(int roundNumber, int engineValue, const Stock& stock) const {
    // Visual separation for the start of a new round or state refresh
    std::cout << std::endl;
    std::cout << "=== Round " << roundNumber << " ===" << std::endl;
    std::cout << "Engine Value: " << engineValue << std::endl;

    // Displaying the number of tiles available to be drawn
    std::cout << "Stock Size: " << stock.getSize() << " tiles remaining" << std::endl;
}

/* *********************************************************************
Function Name: displayBoard
Purpose: To render the current line of play (the layout) to the console
         so the player can see the available pips on the Left and Right ends.
Parameters:
         layout, a Layout object passed by const reference.
Return Value: None (void)
Algorithm:
         1. Print the "Current Board Layout" label.
         2. Print the "L" marker to indicate the Computer's end.
         3. Call the layout's internal display function to print the tile chain.
         4. Print the "R" marker to indicate the Human's end.
Reference: None
********************************************************************* */
void LayoutView::displayBoard(const Layout& layout) const {
    // L and R markers help the player identify which side of the engine is which
    std::cout << "Current Board Layout: ";
    std::cout << "L ";

    // Delegate the actual tile formatting to the Layout class
    layout.displayLayout();

    std::cout << " R" << std::endl;
}

/* *********************************************************************
Function Name: displayHand
Purpose: To print the player's current tiles with associated indices,
         allowing the user to make a selection by number.
Parameters:
         hand, a Hand object passed by const reference.
Return Value: None (void)
Algorithm:
         1. Print the "Player's Hand" label.
         2. Iterate through the hand based on its size.
         3. For each tile, print the 1-based index followed by the tile's pip values.
         4. Ensure all tiles are printed on a single line for readability.
Reference: None
********************************************************************* */
void LayoutView::displayHand(const Hand& hand) const {
    std::cout << "Player's Hand: ";

    // Iterate through the hand and provide 1-based indexing for user input
    for (int i = 0; i < hand.getSize(); ++i) {
        Tile tile = hand.getTileAtIndex(i);

        // Format: "Index: [L|R]"
        std::cout << (i + 1) << ": [" << tile.getLeftPips() << "|" << tile.getRightPips() << "]  ";
    }

    std::cout << std::endl;
}

/* *********************************************************************
Function Name: printMsg
Purpose: A standardized utility function to output status updates or
         instructional text to the player.
Parameters:
         msg, a constant string reference. The message to be displayed.
Return Value: None (void)
Algorithm:
         1. Output the message string to std::cout.
         2. Append a newline character.
Reference: None
********************************************************************* */
void LayoutView::printMsg(const std::string& msg) const {
    // Generic message output for game events and validation errors
    std::cout << msg << std::endl;
}