/**************************************************************************************************************************************
* Programming Assignment: PA9
* Class: CptS 122, Spring 2026
* Date: April 29, 2026
***************************************************************************************************************************************/
// Base Class
#pragma once                 
#include <iostream>         

// Base class for all objects in the game
class GameObject {
protected:
    float x, y;            // position of object on screen
    float speed;           // movement speed

public:
    // Constructor
    GameObject(float startX = 0, float startY = 0, float spd = 1.0f);

    // Virtual destructor 
    virtual ~GameObject();

    // Virtual update function 
    virtual void update();

    // Virtual render function (display object)
    virtual void render();

    // Set position
    void setPosition(float newX, float newY);

    // Set speed
    void setSpeed(float spd);
};

