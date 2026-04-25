#include "MainMenu.hpp"

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

bool MainMenu::setUpMenu(const std::string* arr, const int& size)
{
    if (loadTextures(arr, size))
    {
        title.setTexture(&menuText[0]);
        play.setTexture(&menuText[1]);
        exit.setTexture(&menuText[3]);
        back.setTexture(&menuText[4]);
        howTo.setTexture(&menuText[2]);
        if (title.getTexture() != nullptr && play.getTexture() != nullptr && exit.getTexture() != nullptr)
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
        window.draw(back);
    }
}

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

MainMenu::MainMenu()
{
    state = MAIN;
}
