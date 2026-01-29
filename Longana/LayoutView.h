#ifndef LAYOUTVIEW_H
#define LAYOUTVIEW_H

#include <string>
#include "Stock.h"
#include "Layout.h"
#include "Hand.h"

class LayoutView {
public:

    /* --- Utility Functions --- */

    /// <summary>
    /// Display a header for the given round using the provided engine value and stock information. This member function does not modify the object.
    /// </summary>
    /// <param name="roundNumber">The current round number to display in the header.</param>
    /// <param name="engineValue">The engine's current value or identifier to include in the header.</param>
    /// <param name="stock">A const reference to a Stock object providing additional information to show in the header.</param>
    void displayHeader(int roundNumber, int engineValue, const Stock& stock) const;

    /// <summary>
    /// Displays or renders the board using the provided layout. This const member function does not modify the object.
    /// </summary>
    /// <param name="layout">A const reference to the Layout that describes the board state to display.</param>
    void displayBoard(const Layout& layout) const;

    /// <summary>
    /// Displays the provided Hand (e.g., prints or renders its contents) without modifying it.
    /// </summary>
    /// <param name="hand">The Hand to display; passed by const reference and not modified.</param>
    void displayHand(const Hand& hand) const;

    /// <summary>
    /// Prints the provided message. This is a const member function and does not modify the object's state.
    /// </summary>
    /// <param name="msg">The message to print.</param>
    void printMsg(const std::string& msg) const;

};

#endif