#include "MainMenu.hpp"

/*
Description: Loads all of the textures for the main menu and puts them into the vector menuText

Return: false if any texture fails to load, true if otherwise

Pre: none

Post: All the textures for the main menu has been loaded and is stored in the vector menuText
*/
bool MainMenu::loadTextures(const std::string* arr, const int& size)
{
    bool result = true;
    sf::Texture temp;
    for (int i = 0; i < size; i++)
    {
        result = temp.loadFromFile(arr[i]);
        if (!result)
        {
            return result;
        }
        menuText.push_back(temp);
    }
    return result;
}


/*
Description: Sets up the main menu, sets the rectangle shapes (title, play, exit, back, howTo, des) to the corresponding texture and then places them on the screen at the correct position and size

Return: false if the textures failed to load or it failed to set any of the textures

Pre: none

Post: The menu has been set up
*/
bool MainMenu::setUpMenu(const std::string* arr, const int& size)
{
    if (loadTextures(arr, size))
    {
        title.setTexture(&menuText[0]);
        play.setTexture(&menuText[1]);
        exit.setTexture(&menuText[3]);
        back.setTexture(&menuText[4]);
        howTo.setTexture(&menuText[2]);
        howToScreen.setTexture(&menuText[5]);
        if (title.getTexture() != nullptr && play.getTexture() != nullptr && exit.getTexture() != nullptr && back.getTexture() != nullptr && howTo.getTexture() != nullptr && howToScreen.getTexture() != nullptr)
        {
            title.setSize(sf::Vector2f(660, 250));
            title.setOrigin(sf::Vector2f(330, 125));
            title.setPosition(sf::Vector2f(960, 225));

            play.setSize(sf::Vector2f(230, 75));
            play.setOrigin(sf::Vector2f(115, 37));
            play.setPosition(sf::Vector2f(960, 600));
            
            howTo.setSize(sf::Vector2f(230, 75));
            howTo.setOrigin(sf::Vector2f(115, 37));
            howTo.setPosition(sf::Vector2f(960, 750));
            
            howToScreen.setSize(sf::Vector2f(990, 375));
            howToScreen.setOrigin(sf::Vector2f(495, 187));
            howToScreen.setPosition(sf::Vector2f(960, 600));

            exit.setSize(sf::Vector2f(230, 75));
            exit.setOrigin(sf::Vector2f(115, 37));
            exit.setPosition(sf::Vector2f(960, 900));
            
            back.setSize(sf::Vector2f(230, 75));
            back.setOrigin(sf::Vector2f(115, 37));
            back.setPosition(sf::Vector2f(1750, 1000));
            
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}


/*
Description: Draws the correct items depending on the state of the menu

Return: none

Pre: The menu has already been set up

Post: the menu is drawn to the screen correctly
*/
void MainMenu::drawMenu(sf::RenderWindow& window)
{
    if (state == MAIN)
    {
        window.draw(title);
        window.draw(play);
        window.draw(exit);
        window.draw(howTo);
    }
    else if (state == HOWTO)
    {
        window.draw(howToScreen);
        window.draw(back);
    }
}


/*
Description: Handles the logic for the menu, play starts the game, how to takes you to the instructions, exit closes the game, back takes you back to the main menu

Return: 1 if they click the play button, 2 if they click exit 0 if otherwise

Pre: Menu has been set up

Post: The screen changes according to the button the user presses
*/
int MainMenu::menuLogic(sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        if (state == MAIN)
        {
            if (play.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            {
                return 1;
            }
            else if (exit.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            {
                return 2;
            }
            else if (howTo.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            {
                state = HOWTO;
            }
        }
        else if (state == HOWTO)
        {
            if (back.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            {
                state = MAIN;
            }
        }
    }
    return 0;
}


/*
Description: Default constructor for a MainMenu item, sets state to MAIN

Return: none

Pre: none

Post: MainMenu object has been initialized
*/
MainMenu::MainMenu()
{
    state = MAIN;
}
