/**************************************************************************************************************************************
* Programming Assignment: PA9
* Class: CptS 122, Spring 2026
* Date: April 29, 2026
***************************************************************************************************************************************/
// CorrectCode (+1 point)
#pragma once
#include "CodeItem.hpp"

// Represents correct code
class CorrectCode : public CodeItem {
public:
    CorrectCode(const float& startX, const float& startY, const float& xSpd, const float& ySpd, const int& spawn, const sf::Texture& img);
    ~CorrectCode();

    // Override slice behavior
    int onSlice() override;
};