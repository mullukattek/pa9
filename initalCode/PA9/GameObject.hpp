/**************************************************************************************************************************************
* Programming Assignment: PA9
* Class: CptS 122, Spring 2026
* Date: April 29, 2026
***************************************************************************************************************************************/
// Base Class
#pragma once                 
#include <iostream>         
#include <SFML/Graphics.hpp>
// Base class for all objects in the game
class GameObject // public sf::Sprite{
{
protected:
    float x, y;            // position of object on screen
    float speed;           // movement speed

public:
    // Constructor
    GameObject(const float& startX = 0.f, const float& startY = 0.f, const float& spd = 0.f /*const sf::Texture& img*/);

    // Virtual destructor 
    virtual ~GameObject();

    // Virtual update function 
    virtual void update();

    // Virtual render function (display object)
    virtual void render();

    // Set position
   // void setPosition(float newX, float newY);

    // Set speed
   // void setSpeed(float spd);
};

