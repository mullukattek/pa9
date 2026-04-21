#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

class Game
{
private:
	sf::RenderWindow window;
	std::vector<sf::CircleShape> mItems;
	sf::CircleShape* temp;
	sf::Clock time;
	void checkDel();
	void createMoveObj(const float& dt);
	void drawGame();

public:
	Game();

	void runGame();
};