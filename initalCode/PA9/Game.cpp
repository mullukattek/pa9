
#include "Game.hpp"

/*
Description: Loads the good code textures and the bad code textures and stores them in the vectors goodCode and badCode respectivly

Return: false if any textures failed to load, true otherwise

Pre: none

Post: The textures have been loaded and stored the correct vector
*/
bool Game::loadTextures(const std::string* goodC, const int& size1, const std::string* badC, const int& size2)
{
    sf::Texture temp;
    bool result = true;
    for (int i = 0; i < size1; ++i)
    {
        result = temp.loadFromFile(goodC[i]);
        if (!result)
        {
            return result;
        }
        goodCode.push_back(temp);
    }
    for (int c = 0; c < size2; ++c)
    {
        result = temp.loadFromFile(badC[c]);
        if (!result)
        {
            return result;
        }
        badCode.push_back(temp);
    }
    result = backText.loadFromFile("background.png");
    return result;
}


/*
Description: Checks to see if any objects currently on the screen need to be deleted

Return: none

Pre: none

Post: any objects that should be deleted are
*/
void Game::checkDel(const sf::RectangleShape* deleteBox)
{
    for (int i = 0; i < mItems.size(); ++i)
    {
        if ((deleteBox->getGlobalBounds().findIntersection(mItems[i]->getGlobalBounds())).has_value()) //Detect collision with the Clicker box and mItems
        {
            mItems[i]->onSlice(); // Ignores returned value, value must be added to score
            mItems.erase(mItems.begin() + i);
        }
        else if (mItems[i]->getPosition().y >= 1200 + 200) //The object goes off the screen
        {
            mItems.erase(mItems.begin() + i);
        }
    }
}


/*
Description: Creates new objects randomly as objects are deleted from the screen, created with a random velocity, position (focused in the middle of the screen), and spawn time

Return: none

Pre: Textures have been properly loaded

Post: New objects are created with random speeds and positions
*/
void Game::createObj()
{
    std::random_device random;
    std::uniform_real_distribution<float> pos1(640, 1920 - 640); //random x position focused in the middle of the screen
    std::uniform_int_distribution<int> item(1, 10); //random item (buggy or normal)
    std::uniform_real_distribution<float> xSpeed(0, 600); 
                                                                              
    std::uniform_real_distribution<float> ySpeed(2100, 2700); //similar logic for y speed
    std::uniform_int_distribution<int> spawnT(1, 2);
    std::uniform_int_distribution<int> synLog(1, 2); //chooses between logic or syntax

    //Once we add difficulty to the game we can create varibles for all of these and then change them as the diffculty increases;
    if (temp == nullptr) //if there is no object waiting to be added to the screen
    {
        if (item(random) <= 6) //higher probablity that a correct code item will spawn
        {
            temp = new CorrectCode(0, 0, xSpeed(random), -ySpeed(random), spawnT(random), goodCode[8]);
        }
        else
        {
            if (synLog(random) == 1)
            {
                temp = new BuggyCode(0, 0, xSpeed(random), -ySpeed(random), spawnT(random), badCode[4], SYNTAX);
            }
            else
            {
                temp = new BuggyCode(0, 0, xSpeed(random), -ySpeed(random), spawnT(random), badCode[5], LOGIC);
            } 
        }
        
        temp->setScale(sf::Vector2f(4, 4));
    }
    if (mItems.size() < 4 && spawnTime.getElapsedTime().asSeconds() >= temp->getSpawnTime())
    {
        temp->setPosition(sf::Vector2f(pos1(random), 1200));
        if (temp->getPosition().x > 1920 / 2) //Makes sure that objects don't immediately go off the side of the screen 
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
        deleteBox->setSize({ 15.f,15.f });
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

        deleteBox->setPosition(worldPos);
    }
    else // if the mouse isn't being held the deleteBox is made to be inactive
    {
        deleteBox->setSize({ 0.f,0.f });
        deleteBox->setPosition({ 0.f,0.f });
    }
}


/*
Description: Moves the items stored in mItems in an arch from the bottom of the screen

Return: none

Pre: none

Post: the objects stored in mItems are moved 
*/
void Game::moveObj(const float& dt)
{
    for (int i = 0; i < mItems.size(); ++i)
    {
        mItems[i]->move(mItems[i]->getSpeed() * dt);
        mItems[i]->setSpeed(mItems[i]->getSpeed().x, mItems[i]->getSpeed().y + (3000 * dt)); //the amount you add also has to be a ratio adding 1 to 100 versus 20 creates vastly diffrent deacclerations
    }
}


/*
Description: default constructer for a Game object, sets temp and deleteBox to nullptr and the game's state to NA

Return: none

Pre: none

Post: a game object has been intialzied
*/
Game::Game()
{
    temp = nullptr;
    deleteBox = nullptr;
    state = NA;
}


/*
Description: simulates the game, creates the screen and runs the game loop

Return: none

Pre: none

Post: none
*/
void Game::runGame(const std::string* goodC, const int& size1, const std::string* badC, const int& size2, const std::string* menuTex, const int& size3)
{
    sf::Clock clock;
    sf::VideoMode s;
    sf::View gameView(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(1920 , 1200)));
    window.create(s.getDesktopMode(), "Game"); //s.getDesktopMode() // sf::VideoMode({200, 200})
    window.setView(gameView);
    window.setFramerateLimit(120);
    
    if (loadTextures(goodC, size1, badC, size2) && mMenu.setUpMenu(menuTex, size3)) //Makes sure that all of the textures were loaded properly
    {
        background.setTexture(&backText);
        background.setSize(sf::Vector2f(1920, 1200));
        background.setPosition(sf::Vector2f(0, 0));

        deleteBox = new sf::RectangleShape({ 7.f, 7.f });
        deleteBox->setFillColor(sf::Color::Transparent);
        int hold = 0;
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
                createObj();
                moveObj(deltaTime);
                checkDel(deleteBox);

                window.clear();
                window.draw(background);
                drawGame();
                window.display();
            }
            else if (state == EXIT)
            {
                window.close();
            }
            else
            {
                hold = mMenu.menuLogic(window);
                if (hold == 1)
                {
                    state = PLAY;
                }
                else if (hold == 2)
                {
                    state = EXIT;
                }
                window.clear();
                window.draw(background);
                mMenu.drawMenu(window);
                window.display();
            }

        }
    }
    else
    {
        std::cout << "failed to load textures" << std::endl;
    }
}
