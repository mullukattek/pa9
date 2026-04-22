/**************************************************************************************************************************************
* Programming Assignment: PA9
* Class: CptS 122, Spring 2026
* Date: April 29, 2026
***************************************************************************************************************************************/
// CorrectCode (+1 point)
#include "CorrectCode.hpp" 

// Constructor
CorrectCode::CorrectCode(const float& startX, const float& startY, const float& xSpd, const float& ySpd, const int& spawn, const sf::Texture& img):
    CodeItem(startX, startY, xSpd, ySpd, spawn, img) 
{
    sliced = false;
}

// Destructor
CorrectCode::~CorrectCode() {
  
}

// Function called when the object is sliced
int CorrectCode::onSlice() {
    sliced = true;   // Mark this object as sliced this is inherited from CodeItem
    return 1;        // Return +1 point since this is a correct code item
}