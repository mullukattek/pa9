/**************************************************************************************************************************************
* Programming Assignment: PA9
* Class: CptS 122, Spring 2026
* Date: April 29, 2026
***************************************************************************************************************************************/
#include "BuggyCode.hpp"
#include <iostream> 

BuggyCode::BuggyCode(const float& startX, const float& startY, const float& xSpd, const float& ySpd, const int& spawn, const sf::Texture& img, const ErrorType& t):
    CodeItem(startX, startY, xSpd, ySpd, spawn, img)
{
    sliced = false;
    type = t;
}

// Destructor
BuggyCode::~BuggyCode() {}

// Polymorphism: behavior depends on type
int BuggyCode::onSlice() {
    sliced = true;
    if (type == SYNTAX) {
        return -1;
    }
    else if (type == LOGIC) {
        return -2;
    }
}

// Render shows which type it is
void BuggyCode::render() {
    if (type == SYNTAX) {
        //std::cout << "Syntax Error Code at (" <<  << ", " << y << ")" << std::endl;
    }
    else {
        //std::cout << "Logic Error Code at (" << x << ", " << y << ")" << std::endl;
    }
}