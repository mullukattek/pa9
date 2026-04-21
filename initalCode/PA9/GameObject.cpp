/**************************************************************************************************************************************
* Programming Assignment: PA9
* Class: CptS 122, Spring 2026
* Date: April 29, 2026
***************************************************************************************************************************************/
// Base Class
#include "GameObject.hpp"

// initializes position and speed
GameObject::GameObject(const float& startX, const float& startY, const float& spd/*, const sf::Texture& img*/ ) //: sf::Sprite(img)
{
    //setPosition(sf::Vector2f(startX, startY));
    speed = spd;
}

// Destructor
GameObject::~GameObject() {}

// Update function moves object 
void GameObject::update() {
    y += speed; 
}

// Render function 
void GameObject::render() {
    std::cout << "GameObject at (" << x << ", " << y << ")" << std::endl;
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