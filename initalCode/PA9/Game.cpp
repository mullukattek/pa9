
#include "Game.hpp"

void Game::loadTextures()
{
    img1.loadFromFile("test1.png");
    img2.loadFromFile("test2.jpg");
}

//checks if an item should be deleted
void Game::checkDel()
{
    for (int i = 0; i < mItems.size(); ++i)
    {
        if (mItems[i]->getPosition().y >= 1200 + 200)
        {
            mItems.erase(mItems.begin() + i);
        }
    }
}

void Game::checkDel(const sf::RectangleShape* deleteBox)
{
    for (int i = 0; i < mItems.size(); ++i)
    {
        if ((deleteBox->getGlobalBounds().findIntersection(mItems[i]->getGlobalBounds())).has_value()) //Detect collision with the Clicker box and mItems
        {
            mItems[i]->onSlice(); // Ignores returned value, value must be added to score
            mItems.erase(mItems.begin() + i);
        }
    }
}

void Game::setUpMenu()
{
    title.setPosition(sf::Vector2f(window.getSize().x / 2, 0));
    title.setSize(sf::Vector2f(100, 100));
}


void Game::drawMenu()
{
    window.draw(title);
    window.draw(play);
    window.draw(exit);
}

void Game::menuLogic()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        if (title.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
        {
            state = PLAY;
        }
    }
}

//creates objects
void Game::createMoveObj()
{
    std::random_device random;
    std::uniform_real_distribution<float> pos1(640, 1920 - 640); //random x position focused in the middle of the screen
    std::uniform_int_distribution<int> item(1, 10); //random item (buggy or normal)
    std::uniform_real_distribution<float> xSpeed(0, 600); //the X speed can be between 0 and 0.5% of the screen size for any size of screen (this makes it so there is around a consistent speed between
                                                                                //screen sizes
    std::uniform_real_distribution<float> ySpeed(2100, 2700); //similar logic for y speed
    std::uniform_int_distribution<int> spawnT(1, 2);
    //Once we add difficulty to the game we can create varibles for all of these and then change them as the diffculty increases;
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
        float aspectRatio = temp->getTexture().getSize().x / temp->getTexture().getSize().y;
        temp->setScale(sf::Vector2f(0.1, 0.1 * aspectRatio));
    }
    if (mItems.size() < 4 && spawnTime.getElapsedTime().asSeconds() >= temp->getSpawnTime())
    {
        temp->setPosition(sf::Vector2f(pos1(random), 1200));
        if (temp->getPosition().x > window.getSize().x / 2)
        {
            temp->setSpeed(-temp->getSpeed().x, temp->getSpeed().y);
        }
        mItems.push_back(temp);
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
        window.draw(*mItems[i]);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

        deleteBox->setPosition(worldPos);

        window.draw(*deleteBox);
    }
}

void Game::moveObj(const float& dt)
{
    for (int i = 0; i < mItems.size(); ++i)
    {
        mItems[i]->move(mItems[i]->getSpeed() * dt);
        mItems[i]->setSpeed(mItems[i]->getSpeed().x, mItems[i]->getSpeed().y + (3500 * dt)); //the amount you add also has to be a ratio adding 1 to 100 versus 20 creates vastly diffrent deacclerations
    }
}

Game::Game()
{
    temp = nullptr;
    deleteBox = nullptr;
    state = NA;
   
}

void Game::runGame()
{
    sf::Clock clock;
    sf::VideoMode s;
    sf::View gameView(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(1920 , 1200)));
    window.create(s.getDesktopMode(), "Game"); //s.getDesktopMode() // sf::VideoMode({200, 200})
    window.setView(gameView);
    window.setFramerateLimit(60);
    loadTextures();
    title.setTexture(&img1);
    setUpMenu();
    window.setFramerateLimit(30);

    //Set up DeleteBox object on Heap
    deleteBox = new sf::RectangleShape({ 7.f, 7.f });
    deleteBox->setFillColor(sf::Color::Transparent);

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
        if (state == PLAY)
        {
            createMoveObj();
            moveObj(deltaTime);
            checkDel();

            window.clear();
            drawGame();
            checkDel(deleteBox);

            window.display();
        }
        else if (state == EXIT)
        {
            window.close();
        }
        else
        {
            menuLogic();

            window.clear();
            drawMenu();
            window.display();
        }
       
    }
}
