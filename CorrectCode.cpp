/**************************************************************************************************************************************
* Programming Assignment: PA9
* Class: CptS 122, Spring 2026
* Date: April 29, 2026
***************************************************************************************************************************************/
// CorrectCode (+1 point)
#include "CorrectCode.hpp" 

// Constructor
CorrectCode::CorrectCode() : CodeItem() {
    
}

// Destructor
CorrectCode::~CorrectCode() {
  
}

// Function called when the object is sliced
int CorrectCode::onSlice() {
    sliced = true;   // Mark this object as sliced this is inherited from CodeItem
    return 1;        // Return +1 point since this is a correct code item
}