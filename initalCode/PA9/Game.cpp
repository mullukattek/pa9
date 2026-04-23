
#include "Game.hpp"

//checks if an item should be deleted
void Game::checkDel()
{
    for (int i = 0; i < mItems.size(); ++i)
    {
        if (mItems[i].getPosition().y >= window.getSize().y + 300)
        {
            mItems.erase(mItems.begin() + i);
        }
    }
}

//creates and moves objects as needed
void Game::createMoveObj()
{
    std::random_device random;
    std::uniform_real_distribution<float> pos1(window.getSize().x / 3, window.getSize().x - (window.getSize().x / 3)); //random x position focused in the middle of the screen
    std::uniform_int_distribution<int> item(1, 10); //random item (buggy or normal)
    std::uniform_real_distribution<float> xSpeed(0, window.getSize().x *0.005); //the X speed can be between 0 and 0.5% of the screen size for any size of screen (this makes it so there is around a consistent speed between
                                                                                //screen sizes
    std::uniform_real_distribution<float> ySpeed(window.getSize().y * 0.029, window.getSize().y * 0.037); //similar logic for y speed
    std::uniform_int_distribution<int> spawnT(1, 2);
    //Once we add difficulty to the game we can create varibles for all of these and then change them as the diffculty increases;
    img1.loadFromFile("test1.png");
    img2.loadFromFile("test2.jpg");
    if (temp == nullptr)
    {
        if (item(random) <= 6) //higher probablity that a correct code item will spawn
        {
            temp = new CorrectCode(0, 0, xSpeed(random), -ySpeed(random), spawnT(random), img1);
        }
        else
        {
            temp = new BuggyCode(0, 0, xSpeed(random), -ySpeed(random), spawnT(random), img2, SYNTAX);
            
        }
        float aspectRatio = window.getSize().x / window.getSize().y;
        float temp1 = (window.getSize().x * 0.05) / temp->getTexture().getSize().x;
        float temp2 = temp1 * aspectRatio;
        temp->setScale(sf::Vector2f(temp1, temp2));
    }
    if (mItems.size() < 4 && spawnTime.getElapsedTime().asSeconds() >= temp->getSpawnTime())
    {
        temp->setPosition(sf::Vector2f(pos1(random), window.getSize().y));
        if (temp->getPosition().x > window.getSize().x / 2)
        {
            temp->setSpeed(-temp->getSpeed().x, temp->getSpeed().y);
        }
        mItems.push_back(*temp);
        spawnTime.restart();
        temp = nullptr;
    }
  
}

/*
Description: draws all of the items need for the game

Return: none

Pre: none

Post: The necessary objects have been drawn to the screen
*/
void Game::drawGame()
{
    
    for (int i = 0; i < mItems.size(); ++i)
    {
        window.draw(mItems[i]);
    }
}

void Game::moveObj(const float& dt)
{
    for (int i = 0; i < mItems.size(); ++i)
    {
        mItems[i].move(mItems[i].getSpeed());
        mItems[i].setSpeed(mItems[i].getSpeed().x, mItems[i].getSpeed().y + window.getSize().y * 0.000833333); //the amount you add also has to be a ratio adding 1 to 100 versus 20 creates vastly diffrent deacclerations
    }
}

Game::Game()
{
    temp = nullptr;
}

void Game::runGame()
{

    sf::Clock clock;
    sf::VideoMode s;
    window.create(sf::VideoMode({ 1920, 1000 }), "Game"); //s.getDesktopMode() // sf::VideoMode({200, 200})
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds(); //makes movement of objects independent from framerate (it will move at a similar speed regardless of the frame rate)
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        createMoveObj();
        moveObj(deltaTime);
        checkDel();

        window.clear();
        drawGame();
        window.display();
    }
}
