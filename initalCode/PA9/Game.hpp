#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <stdexcept>
#include <iostream>
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

	

	void checkDel(const sf::RectangleShape* deleteBox);
	void drawGame();
	void moveObj(const float& dt);

public:
	Game();
	bool createObj();
	bool loadTextures(const std::string* goodC, const int& size1, const std::string* badC, const int& size2);
	void runGame(const std::string* goodC, const int& size1, const std::string* badC, const int& size2, const std::string* menuTex, const int& size3);
	void runGame(const std::string* goodC, const int& size1, const std::string* badC, const int& size2, const std::string* menuTex, const int& size3, int Num);
};