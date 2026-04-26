#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

typedef enum menu
{
	MAIN, HOWTO, RULES
}Menu;

class MainMenu
{
private:

	Menu state;
	std::vector<sf::Texture> menuText;
	sf::RectangleShape title, play, howTo, exit, back, howToScreen;
	
	bool loadTextures(const std::string* arr, const int& size);

public:

	MainMenu();

	int menuLogic(sf::RenderWindow& window);

	bool setUpMenu(const std::string* arr, const int& size);

	void drawMenu(sf::RenderWindow& window);

};