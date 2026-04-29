#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <exception>
#include "BuggyCode.hpp"
#include "CorrectCode.hpp"

#include "Game.hpp"
#include "MainMenu.hpp"

namespace Test
{
	void RunTests();

	void TestCase1();

	void TestCase2();

	void TestCase3();

	void TestCase4();

	void TestCase5();
}

//Simply Run each Test function
void Test::RunTests()
{
	Test::TestCase1();
	Test::TestCase2();
	Test::TestCase3();
	Test::TestCase4();
	Test::TestCase5();
};

//Test the texture loading will fail if an incorrect number vector size is input
void Test::TestCase1()
{
	Game Temp;
	std::string good[9] = { "good1.png" },
		bad[18] = { "syntax1.png", "syntax2.png", "syntax3.png", "syntaxM1.png", "syntaxM2.png", "syntaxM3.png", "syntaxH1.png", "syntaxH2.png", "syntaxH3.png",
				   "logic1.png", "logic2.png", "logic3.png", "logicM1.png", "logicM2.png", "logicM3.png", "logicH1.png", "logicH2.png", "logicH3.png" };
	if (Temp.loadTextures(good, 9, bad, 18))
	{
		std::cout << "#1 Test failed" << std::endl;
	}
	else
	{
		std::cout << "#1 Test successful" << std::endl;
	}
};

//Ensures textures load prior to game run, The test forces the textures to be bad and cause a fail load, in which case it will print a Test successful
void Test::TestCase2()
{
	Game Temp;
	std::string good[9] = { "good1.png", "good2.png", "good3.png", "goodM1.png", "goodM2.png", "goodM3.png", "goodH1.png", "goodH2.png", "goodH3.png" },
		bad[18] = { "syntax1.png", "syntax2.png", "syntax3.png", "syntaxM1.png", "syntaxM2.png", "syntaxM3.png", "syntaxH1.png", "syntaxH2.png", "syntaxH3.png",
				   "logic1.png", "logic2.png", "logic3.png", "logicM1.png", "logicM2.png", "logicM3.png", "logicH1.png", "logicH2.png", "logicH3.png" };

	std::string menuTextures[6] = { "title.png", "play.png", "howTo.png", "exit.png", "back.png", "howToScreen.png" };
	try {
		Temp.runGame(good, 9, bad, 18, menuTextures, 7);
		std::cout << "#2 Test failed" << std::endl;
	}
	catch (std::runtime_error)
	{
		std::cout << "#2 Test successful" << std::endl;
		return;
	}
}

//Ensures the Menu textures load properly
void Test::TestCase3()
{
	sf::RenderWindow window;
	std::string menuTextures[6] = { "title.png", "play.png", "howTo.png", "exit.png", "back.png", "howToScreen.png" };
	MainMenu Temp;
	if (Temp.setUpMenu(menuTextures, 6))
	{
		std::cout << "#3 Test successful" << std::endl;
	}
	else
	{
		std::cout << "#3 Test failed" << std::endl;
	}
};

//Test the creation and insertion of an object into the mItem object
void Test::TestCase4()
{
	Game Temp;
	std::string good[9] = { "good1.png", "good2.png", "good3.png", "goodM1.png", "goodM2.png", "goodM3.png", "goodH1.png", "goodH2.png", "goodH3.png" },
		bad[18] = { "syntax1.png", "syntax2.png", "syntax3.png", "syntaxM1.png", "syntaxM2.png", "syntaxM3.png", "syntaxH1.png", "syntaxH2.png", "syntaxH3.png",
				   "logic1.png", "logic2.png", "logic3.png", "logicM1.png", "logicM2.png", "logicM3.png", "logicH1.png", "logicH2.png", "logicH3.png" };
	try {
		Temp.loadTextures(good, 9, bad, 18);
		Temp.createObj();
		std::cout << "#4 Test successful" << std::endl;
	}
	catch (const std::out_of_range& e) {
		std::cout << "#4 Test failed" << std::endl;
		return;
	}
};

//Runs 1 loop of a shortened runGame function, this function was shortend to require zero input from a user
void Test::TestCase5()
{
	Game Temp;
	std::string good[9] = { "good1.png", "good2.png", "good3.png", "goodM1.png", "goodM2.png", "goodM3.png", "goodH1.png", "goodH2.png", "goodH3.png" },
		bad[18] = { "syntax1.png", "syntax2.png", "syntax3.png", "syntaxM1.png", "syntaxM2.png", "syntaxM3.png", "syntaxH1.png", "syntaxH2.png", "syntaxH3.png",
				   "logic1.png", "logic2.png", "logic3.png", "logicM1.png", "logicM2.png", "logicM3.png", "logicH1.png", "logicH2.png", "logicH3.png" };
	std::string menuTextures[6] = { "title.png", "play.png", "howTo.png", "exit.png", "back.png", "howToScreen.png" };
	try {
		Temp.runGame(good, 9, bad, 19, menuTextures, 6, 1);
		std::cout << "#5 Test failed" << std::endl;
	}
	catch (std::runtime_error) {
		std::cout << "#5 Test successful" << std::endl;
		return;
	}
};