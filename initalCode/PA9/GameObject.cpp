/**************************************************************************************************************************************
* Programming Assignment: PA9
* Class: CptS 122, Spring 2026
* Date: April 29, 2026
***************************************************************************************************************************************/
// Base Class
#include "GameObject.hpp"

// initializes position and speed


GameObject::GameObject(const float& startX, const float& startY, const float& xSpd, const float& ySpd, const int& spawn, const sf::Texture& img) : sf::Sprite(img)
{
    setPosition(sf::Vector2f(startX, startY));
    velocity.x = xSpd;
    velocity.y = ySpd;
    timeSpawn = spawn;
}

// Destructor
GameObject::~GameObject() {}

// Update function moves object 
void GameObject::update() 
{
    move(velocity);
}

// Render function 
void GameObject::render() {
   
}

sf::Vector2f GameObject::getSpeed() const
{
    return velocity;
}

void GameObject::setSpeed(const float& xSpd, const float& ySpd)
{
    velocity.x = xSpd;
    velocity.y = ySpd;
}

int GameObject::getSpawnTime() const
{
    return timeSpawn;
}

// Set new position
//void GameObject::setPosition(float newX, float newY) {
//    x = newX;
//    y = newY;
//}
//
//// Set speed
//void GameObject::setSpeed(float spd) {
//    speed = spd;
//}