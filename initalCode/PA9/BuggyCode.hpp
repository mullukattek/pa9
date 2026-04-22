/**************************************************************************************************************************************
* Programming Assignment: PA9
* Class: CptS 122, Spring 2026
* Date: April 29, 2026
***************************************************************************************************************************************/
#pragma once                  
#include <iostream>           
#include "CodeItem.hpp"         


enum ErrorType {
    SYNTAX,   // syntax error → -1
    LOGIC     // logic error → -2
};


// Inherits from CodeItem
// Handles both syntax + logic errors

class BuggyCode : public CodeItem {
private:
    ErrorType type;   // stores whether this is SYNTAX or LOGIC error

public:
    
    BuggyCode(const float& startX, const float& startY, const float& xSpd, const float& ySpd, const int& spawn, const sf::Texture& img, const ErrorType& t);

    virtual ~BuggyCode();

    
    // Polymorphic function
    // Returns score penalty based on type
    int onSlice() override;


    // Override render to display type
    void render() override;
};