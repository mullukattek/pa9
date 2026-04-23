#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "BuggyCode.hpp"
#include "CorrectCode.hpp"

class Game
{
private:
	sf::RenderWindow window;
	std::vector<GameObject> mItems;
	sf::Texture img1, img2; //might have to change this later 
	GameObject* temp;
	sf::Clock spawnTime, overAll;
	
	void checkDel();

	void createMoveObj();

	void drawGame();

	void moveObj(const float& dt);
public:
	Game();

	void runGame();
};