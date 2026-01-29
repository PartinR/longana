#ifndef LAYOUTVIEW_H
#define LAYOUTVIEW_H

/************************************************************
 * Name:  Race Benjamin Partin                              *
 * Project: Project 1 (Longana)                             *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  02/12/2026                                        *
 ************************************************************/

#include <string>
#include "Stock.h"
#include "Layout.h"
#include "Hand.h"

 /* *********************************************************************
 Class Name: LayoutView
 Purpose: Acts as the "View" component in the application. It is strictly
          responsible for handling output to the console. It decouples the
          game logic from the visualization logic by providing specific
          functions to render the Board, Hands, and status messages.
 ********************************************************************* */
class LayoutView {
public:

    /* --- Utility Functions --- */

    /* *********************************************************************
    Function Name: displayHeader
    Purpose: Prints the standard header information at the start of a round
             or turn, including the Round Number, the Engine being played,
             and the status of the Boneyard.
    Parameters:
             roundNumber, an integer passed by value. The current round index.
             engineValue, an integer passed by value. The pip value of the engine (e.g., 6).
             stock, a Stock object passed by const reference. Used to display the boneyard contents.
    Return Value: None (void)
    Algorithm:
             1. Print formatted lines for Round Number and Engine.
             2. Delegate to stock.printStock() (or similar) to display the boneyard.
    Reference: None
    ********************************************************************* */
    void displayHeader(int roundNumber, int engineValue, const Stock& stock) const;

    /* *********************************************************************
    Function Name: displayBoard
    Purpose: Renders the central game board (the layout) to the console.
    Parameters:
             layout, a Layout object passed by const reference. The board state to render.
    Return Value: None (void)
    Algorithm:
             1. Print a label (e.g., "Layout:").
             2. Call the layout object's internal display function (layout.displayLayout()).
    Reference: None
    ********************************************************************* */
    void displayBoard(const Layout& layout) const;

    /* *********************************************************************
    Function Name: displayHand
    Purpose: Renders a specific player's hand to the console.
    Parameters:
             hand, a Hand object passed by const reference. The hand to display.
    Return Value: None (void)
    Algorithm:
             1. Call the hand object's internal display function (hand.displayHand()).
    Reference: None
    ********************************************************************* */
    void displayHand(const Hand& hand) const;

    /* *********************************************************************
    Function Name: printMsg
    Purpose: A generic utility to print a string message to the console.
             Used for status updates (e.g., "Player Passed", "Invalid Input").
    Parameters:
             msg, a std::string passed by const reference. The message to print.
    Return Value: None (void)
    Algorithm:
             1. Send the msg string to standard output (std::cout).
             2. Append a newline if necessary.
    Reference: None
    ********************************************************************* */
    void printMsg(const std::string& msg) const;

};

#endif