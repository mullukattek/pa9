#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "BuggyCode.hpp"
#include "CorrectCode.hpp"
#include "MainMenu.hpp"

typedef enum gameState
{
	NA = 0, PLAY, EXIT
} GameState;

class Game
{
private:
	int score; // i store player score

	sf::RenderWindow window;
	MainMenu mMenu;

	std::vector<sf::Texture> goodCode, badCode;
	sf::Texture backText;

	std::vector<GameObject*> mItems;
	GameObject* temp;

	sf::Clock spawnTime, overAll;
	sf::RectangleShape title, play, exit, background;

	GameState state;

	sf::RectangleShape* deleteBox;

	bool loadTextures(const std::string* goodC, const int& size1, const std::string* badC, const int& size2);

	void checkDel(const sf::RectangleShape* deleteBox);
	void drawGame();
	void createObj();
	void moveObj(const float& dt);

public:
	Game();

	void runGame(const std::string* goodC, const int& size1, const std::string* badC, const int& size2, const std::string* menuTex, const int& size3);
};