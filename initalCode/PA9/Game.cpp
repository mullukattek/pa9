#include "Game.hpp"
#include <iostream>

bool Game::loadTextures(const std::string* goodC, const int& size1, const std::string* badC, const int& size2)
{
    sf::Texture temp;
    bool result = true;

    for (int i = 0; i < size1; ++i)
    {
        result = temp.loadFromFile(goodC[i]);
        if (!result) return result;
        goodCode.push_back(temp);
    }

    for (int c = 0; c < size2; ++c)
    {
        result = temp.loadFromFile(badC[c]);
        if (!result) return result;
        badCode.push_back(temp);
    }

    result = backText.loadFromFile("background.png");
    return result;
}

void Game::checkDel(const sf::RectangleShape* deleteBox)
{
    for (int i = 0; i < mItems.size(); ++i)
    {
        if ((deleteBox->getGlobalBounds().findIntersection(mItems[i]->getGlobalBounds())).has_value())
        {
            // i use polymorphism to get points
            int points = mItems[i]->onSlice();
            score += points;

            // i update score in window title
            window.setTitle("score: " + std::to_string(score));

            mItems.erase(mItems.begin() + i);
            i--;
        }
        else if (mItems[i]->getPosition().y >= 1400)
        {
            mItems.erase(mItems.begin() + i);
            i--;
        }
    }
}

void Game::createObj()
{
    std::random_device random;
    std::uniform_real_distribution<float> pos1(640, 1920 - 640);
    std::uniform_int_distribution<int> item(1, 10);
    std::uniform_real_distribution<float> xSpeed(0, 600);
    std::uniform_real_distribution<float> ySpeed(2100, 2700);
    std::uniform_int_distribution<int> spawnT(1, 2);
    std::uniform_int_distribution<int> synLog(1, 2);

    if (temp == nullptr)
    {
        if (item(random) <= 6)
        {
            temp = new CorrectCode(0, 0, xSpeed(random), -ySpeed(random), spawnT(random), goodCode[8]);
        }
        else
        {
            if (synLog(random) == 1)
                temp = new BuggyCode(0, 0, xSpeed(random), -ySpeed(random), spawnT(random), badCode[4], SYNTAX);
            else
                temp = new BuggyCode(0, 0, xSpeed(random), -ySpeed(random), spawnT(random), badCode[5], LOGIC);
        }

        temp->setScale(sf::Vector2f(4, 4));
    }

    if (mItems.size() < 4 && spawnTime.getElapsedTime().asSeconds() >= temp->getSpawnTime())
    {
        temp->setPosition(sf::Vector2f(pos1(random), 1200));

        if (temp->getPosition().x > 1920 / 2)
            temp->setSpeed(-temp->getSpeed().x, temp->getSpeed().y);

        mItems.push_back(temp);
        spawnTime.restart();
        temp = nullptr;
    }
}

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
    else
    {
        deleteBox->setSize({ 0.f,0.f });
        deleteBox->setPosition({ 0.f,0.f });
    }
}

void Game::moveObj(const float& dt)
{
    for (int i = 0; i < mItems.size(); ++i)
    {
        mItems[i]->move(mItems[i]->getSpeed() * dt);
        mItems[i]->setSpeed(mItems[i]->getSpeed().x, mItems[i]->getSpeed().y + (3000 * dt));
    }
}

Game::Game()
{
    temp = nullptr;
    deleteBox = nullptr;
    state = NA;
    score = 0;
}

void Game::runGame(const std::string* goodC, const int& size1, const std::string* badC, const int& size2, const std::string* menuTex, const int& size3)
{
    sf::Clock clock;

    // i use this to stop game after 60 seconds
    sf::Clock gameTimer;
    float maxTime = 60.0f;

    sf::VideoMode s;
    sf::View gameView(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(1920, 1200)));

    window.create(s.getDesktopMode(), "score: 0");
    window.setView(gameView);
    window.setFramerateLimit(120);

    if (loadTextures(goodC, size1, badC, size2) && mMenu.setUpMenu(menuTex, size3))
    {
        background.setTexture(&backText);
        background.setSize(sf::Vector2f(1920, 1200));
        background.setPosition(sf::Vector2f(0, 0));

        deleteBox = new sf::RectangleShape({ 7.f, 7.f });
        deleteBox->setFillColor(sf::Color::Transparent);

        int hold = 0;

        while (window.isOpen())
        {
            float dt = clock.restart().asSeconds();

            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();
            }

            if (state == PLAY)
            {
                // i end game after 60 seconds
                if (gameTimer.getElapsedTime().asSeconds() >= maxTime)
                {
                    std::cout << "game over! final score: " << score << std::endl;
                    window.close();
                }

                createObj();
                moveObj(dt);
                checkDel(deleteBox);

                window.clear();
                window.draw(background);
                drawGame();
                window.display();
            }
            else
            {
                hold = mMenu.menuLogic(window);

                if (hold == 1)
                {
                    state = PLAY;
                    gameTimer.restart();
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
}