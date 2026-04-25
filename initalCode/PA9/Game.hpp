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
}GameState;

class Game
{
private:
	sf::RenderWindow window;
	MainMenu mMenu;
	std::vector<sf::Texture> goodCode, badCode; //want to use a vector for the graphics write a function which loads every graphic
	std::vector<GameObject*> mItems;
	GameObject* temp;
	sf::Clock spawnTime, overAll;
	sf::RectangleShape title, play, exit;
	GameState state;

	sf::RectangleShape* deleteBox;

	bool loadTextures(const std::string* goodC, const int& size1, const std::string* badC, const int& size2);

	void checkDel();
	void checkDel(const sf::RectangleShape* deleteBox);

	void drawGame();

	void createMoveObj();

	void moveObj(const float& dt);
public:
	Game();

	void runGame(const std::string* goodC, const int& size1, const std::string* badC, const int& size2, const std::string* menuTex, const int& size3);
};