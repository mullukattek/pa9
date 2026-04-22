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
	sf::Clock time;
	
	void checkDel();
	void createMoveObj(const float& dt);
	void drawGame();

public:
	Game();

	void runGame();
};