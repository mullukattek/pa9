/**************************************************************************************************************************************
* Programming Assignment: PA9
* Class: CptS 122, Spring 2026
* Date: April 29, 2026
***************************************************************************************************************************************/
// Derived from GameObject
#pragma once
#include "GameObject.hpp"

class CodeItem : public GameObject {
protected:
    // check if the object has been sliced
    bool sliced;        

public:
    CodeItem();
    virtual ~CodeItem();

    // Virtual function for slicing 
    virtual int onSlice(); // should returns points

    // Override render
    virtual void render() override;
};