
#include "Game.hpp"

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

void Game::createMoveObj(const float& dt)
{
    std::random_device random;
    std::uniform_real_distribution<float> dist1(100.f * 2, (window.getSize().x - 100.f * 2));
    std::uniform_real_distribution<float> dist2(100.f * 2, (window.getSize().y - 100.f * 2));
    if (temp == nullptr)
    {
        temp = new sf::CircleShape(100.f);
    }
    if (mItems.size() < 4 && time.getElapsedTime().asSeconds() >= 2)
    {
        temp->setPosition(sf::Vector2f(dist1(random), dist2(random)));
        mItems.push_back(*temp);
        time.restart();
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
