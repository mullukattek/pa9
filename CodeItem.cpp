/**************************************************************************************************************************************
* Programming Assignment: PA9
* Class: CptS 122, Spring 2026
* Date: April 29, 2026
***************************************************************************************************************************************/
// Derived from GameObject
#include "CodeItem.hpp"

// Constructor
CodeItem::CodeItem() : GameObject() {
    // Initializes the 'sliced' state to false (object starts unsliced)
    sliced = false;
}

// Destructor
CodeItem::~CodeItem() {}

// Default behavior when the object is sliced
// This function can be overridden in derived classes for different behavior
int CodeItem::onSlice() {
    sliced = true; // Mark the object as sliced
    return 0;      // have to rewrite next class---> no score awarded for now
}

// Render function to display the object
void CodeItem::render() {
    // Outputs the object's current position (x, y) to the console
    std::cout << "CodeItem at (" << x << ", " << y << ")" << std::endl;
}

