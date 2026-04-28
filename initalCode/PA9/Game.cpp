
#include "Game.hpp"
#include <iostream>

/*
Description: Loads the good code textures and the bad code textures and stores them in the vectors goodCode and badCode respectivly

Return: false if any textures failed to load, true otherwise

Pre: none

Post: The textures have been loaded and stored the correct vector
*/
bool Game::loadTextures(const std::string* goodC, const int& size1,
    const std::string* badC, const int& size2) {
    sf::Texture temp;
    bool result = true;

    // Good code: indices 0-2 easy, 3-5 medium, 6-8 hard
    for (int i = 0; i < 3; i++) { result = temp.loadFromFile(goodC[i]); if (!result) return false; goodEasy.push_back(temp); }
    for (int i = 3; i < 6; i++) { result = temp.loadFromFile(goodC[i]); if (!result) return false; goodMed.push_back(temp); }
    for (int i = 6; i < 9; i++) { result = temp.loadFromFile(goodC[i]); if (!result) return false; goodHard.push_back(temp); }

    // Syntax bad: indices 0-2 easy, 3-5 medium, 6-8 hard
    for (int i = 0; i < 3; i++) { result = temp.loadFromFile(badC[i]);  if (!result) return false; badSynEasy.push_back(temp); }
    for (int i = 3; i < 6; i++) { result = temp.loadFromFile(badC[i]);  if (!result) return false; badSynMed.push_back(temp); }
    for (int i = 6; i < 9; i++) { result = temp.loadFromFile(badC[i]);  if (!result) return false; badSynHard.push_back(temp); }

    // Logic bad: indices 9-11 easy, 12-14 medium, 15-17 hard
    for (int i = 9; i < 12; i++) { result = temp.loadFromFile(badC[i]); if (!result) return false; badLogEasy.push_back(temp); }
    for (int i = 12; i < 15; i++) { result = temp.loadFromFile(badC[i]); if (!result) return false; badLogMed.push_back(temp); }
    for (int i = 15; i < 18; i++) { result = temp.loadFromFile(badC[i]); if (!result) return false; badLogHard.push_back(temp); }

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
            // i use polymorphism to get points
            int points = mItems[i]->onSlice();
            score += points;

            // i update score in window title
            window.setTitle("score: " + std::to_string(score));

            mItems.erase(mItems.begin() + i);
            i--;
        }
        else if (mItems[i]->getPosition().y >= 1200 + 200) //The object goes off the screen
        {
            mItems.erase(mItems.begin() + i);
            i--;
        }
    }
}

/* Description: returns speed range and spawn interval based on current difficulty level
   Pre:  diffLevel is 0, 1, or 2
   Post: out-params filled with appropriate ranges */
void Game::getDifficultyParams(float& minY, float& maxY,
    float& minSpawn, float& maxSpawn) {
    if (diffLevel == 0) {       // easy — slow and relaxed
        minY = 1800; maxY = 2200;
        minSpawn = 1.0f; maxSpawn = 2.0f;
    }
    else if (diffLevel == 1) { // medium — noticeably faster
        minY = 2100; maxY = 2600;
        minSpawn = 0.7f; maxSpawn = 1.5f;
    }
    else {                    // hard — fast and frequent
        minY = 2500; maxY = 3200;
        minSpawn = 0.4f; maxSpawn = 1.0f;
    }
}

/*
Description: Creates new objects randomly as objects are deleted from the screen, created with a random velocity, position (focused in the middle of the screen), and spawn time

Return: none

Pre: Textures have been properly loaded

Post: New objects are created with random speeds and positions
*/
void Game::createObj() {
    // --- update difficulty based on score ---
    if (score >= 15) diffLevel = 2;  // medium + hard textures
    else if (score >= 5)  diffLevel = 1;  // easy + medium textures
    else                  diffLevel = 0;  // easy only

    std::random_device random;
    std::uniform_real_distribution<float> pos1(640, 1920 - 640);
    std::uniform_int_distribution<int>    item(1, 10);   // 1-6 = correct, 7-10 = buggy
    std::uniform_int_distribution<int>    synLog(1, 2);  // 1=syntax, 2=logic
    std::uniform_int_distribution<int>    texPick(0, 2); // pick one of 3 textures in bucket

    // get speed + spawn ranges for this difficulty
    float minY, maxY, minSpawn, maxSpawn;
    getDifficultyParams(minY, maxY, minSpawn, maxSpawn);

    std::uniform_real_distribution<float> xSpeed(0, 600);
    std::uniform_real_distribution<float> ySpeed(minY, maxY);
    std::uniform_real_distribution<float> spawnT(minSpawn, maxSpawn);

    // pick which texture bucket(s) are active this difficulty level
    // diffLevel 0: easy only   diffLevel 1: easy or medium   diffLevel 2: medium or hard
    std::uniform_int_distribution<int> tierPick(0, 1); // choose between 2 active tiers
    int tier = (diffLevel == 0) ? 0 : tierPick(random); // 0=lower tier, 1=upper tier

    if (item(random) <= 6) {
        // correct code — pick texture from the right tier
        sf::Texture& tex = (diffLevel == 0) ? goodEasy[texPick(random)]
            : (diffLevel == 1) ? (tier == 0 ? goodEasy[texPick(random)]
                : goodMed[texPick(random)])
            : (tier == 0 ? goodMed[texPick(random)]
                : goodHard[texPick(random)]);
        temp = new CorrectCode(0, 0, xSpeed(random), -ySpeed(random), spawnT(random), tex);
    }
    else {
        // buggy code — syntax or logic, same tier logic
        if (synLog(random) == 1) {
            sf::Texture& tex = (diffLevel == 0) ? badSynEasy[texPick(random)]
                : (diffLevel == 1) ? (tier == 0 ? badSynEasy[texPick(random)]
                    : badSynMed[texPick(random)])
                : (tier == 0 ? badSynMed[texPick(random)]
                    : badSynHard[texPick(random)]);
            temp = new BuggyCode(0, 0, xSpeed(random), -ySpeed(random), spawnT(random), tex, SYNTAX);
        }
        else {
            sf::Texture& tex = (diffLevel == 0) ? badLogEasy[texPick(random)]
                : (diffLevel == 1) ? (tier == 0 ? badLogEasy[texPick(random)]
                    : badLogMed[texPick(random)])
                : (tier == 0 ? badLogMed[texPick(random)]
                    : badLogHard[texPick(random)]);
            temp = new BuggyCode(0, 0, xSpeed(random), -ySpeed(random), spawnT(random), tex, LOGIC);
        }
    }

    temp->setScale(sf::Vector2f(4, 4));

    // max objects on screen also grows with difficulty
    int maxOnScreen = (diffLevel == 0) ? 3 : (diffLevel == 1) ? 4 : 5;

    if ((int)mItems.size() < maxOnScreen &&
        spawnTime.getElapsedTime().asSeconds() >= temp->getSpawnTime()) {
        temp->setPosition(sf::Vector2f(pos1(random), 1200));
        if (temp->getPosition().x > 1920 / 2)
            temp->setSpeed(-temp->getSpeed().x, temp->getSpeed().y);
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
Game::Game() {
    temp = nullptr;
    deleteBox = nullptr;
    state = NA;
    score = 0;
    diffLevel = 0;   // ADD THIS — start at easy
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

    // i use this to stop game after 60 seconds
    sf::Clock gameTimer;
    float maxTime = 60.0f;

    sf::VideoMode s;
    sf::View gameView(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(1920, 1200)));

    window.create(s.getDesktopMode(), "score: 0");
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


//Only called in TestCase.h
void Game::runGame(const std::string* goodC, const int& size1, const std::string* badC, const int& size2, const std::string* menuTex, const int& size3, int Num)
{
    {
        sf::Clock clock;
        sf::VideoMode s;
        sf::View gameView(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(1920, 1200)));
        window.create(s.getDesktopMode(), "Game");
        window.setView(gameView);
        window.setFramerateLimit(120);

        //Makes sure that all of the textures were loaded properly
        loadTextures(goodC, size1, badC, size2) && mMenu.setUpMenu(menuTex, size3);

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

                state = PLAY;

                throw std::runtime_error("");
            }
        }
    }
}
