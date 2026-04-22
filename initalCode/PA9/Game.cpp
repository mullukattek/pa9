
#include "Game.hpp"

//checks if an item should be deleted
void Game::checkDel()
{
    for (int i = 0; i < mItems.size(); ++i)
    {
        if (mItems[i].getPosition().y >= window.getSize().y)
        {
            mItems.erase(mItems.begin() + i);
        }
    }
}

//creates and moves objects as needed
void Game::createMoveObj(const float& dt)
{
    std::random_device random;
    std::uniform_real_distribution<float> pos1(100.f * 2, (window.getSize().x - 100.f * 2));
    std::uniform_real_distribution<float> pos2(100.f * 2, (window.getSize().y - 100.f * 2));
    std::uniform_int_distribution<int> item(1, 2);
    img1.loadFromFile("test1.png");
    img2.loadFromFile("test2.jpg");
    if (temp == nullptr)
    {
        if (item(random) == 1)
        {
            temp = new CorrectCode(0, 0, 0, 0, 0, img1);
            temp->setScale(sf::Vector2f(0.1, 0.1));
        }
        else
        {
            temp = new BuggyCode(0, 0, 0, 0, 0, img2, SYNTAX);
            temp->setScale(sf::Vector2f(0.1, 0.1));
        }
        
    }
    if (mItems.size() < 4 && time.getElapsedTime().asSeconds() >= 2)
    {
        temp->setPosition(sf::Vector2f(pos1(random), pos2(random)));
        mItems.push_back(*temp);
        time.restart();
        temp = nullptr;
    }
    for (int i = 0; i < mItems.size(); ++i)
    {
        mItems[i].move(sf::Vector2f(0, 50 * dt));
    }
}

void Game::drawGame()
{
    
    for (int i = 0; i < mItems.size(); ++i)
    {
        window.draw(mItems[i]);
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
    window.create(s.getDesktopMode(), "Game");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds(); //makes movement of objects based on time and not on framerate
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        createMoveObj(deltaTime);
        checkDel();

        window.clear();
        drawGame();
        window.display();
    }
}
