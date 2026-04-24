#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "BuggyCode.hpp"
#include "CorrectCode.hpp"

typedef enum menu
{
	NA = 0, PLAY, HOWTO, RULES, EXIT
}Menu;

class Game
{
private:
	sf::RenderWindow window;
	std::vector<GameObject> mItems;
	sf::Texture img1, img2; //want to use a vector for the graphics write a function which loads every graphic
	GameObject* temp;
	sf::Clock spawnTime, overAll;
	sf::RectangleShape title, play, exit;
	Menu state;

	void loadTextures();

	void checkDel();

	void setUpMenu();

	void drawMenu();

	void menuLogic();

	void drawGame();

	void createMoveObj();

	void moveObj(const float& dt);
public:
	Game();

	void runGame();
};