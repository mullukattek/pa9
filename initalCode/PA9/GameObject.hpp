/**************************************************************************************************************************************
* Programming Assignment: PA9
* Class: CptS 122, Spring 2026
* Date: April 29, 2026
***************************************************************************************************************************************/
// Base Class
#pragma once                 
#include <iostream>         
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
// Base class for all objects in the game
class GameObject : public sf::Sprite // public sf::Sprite{
{
protected:
    sf::Vector2f velocity; // movement speed in x and y directions 
    int timeSpawn; // used to determine when each game object should spawn
public:
    // Constructor
    GameObject(const float& startX, const float& startY, const float& xSpd, const float& ySpd, const int& spawn, const sf::Texture& img);

    // Virtual destructor 
    virtual ~GameObject();

    // Virtual update function 
    virtual void update();

    // Virtual render function (display object)
    virtual void render();

    sf::Vector2f getSpeed() const;

    void setSpeed(const float& xSpd, const float& ySpd);

    int getSpawnTime() const;

    virtual int onSlice() = 0;

    // Set position
   // void setPosition(float newX, float newY);

    // Set speed
   // void setSpeed(float spd);
};

