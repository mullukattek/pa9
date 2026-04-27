#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "BuggyCode.hpp"
#include "CorrectCode.hpp"

#include "Game.hpp"
#include <exception>

namespace Test
{
	void RunTests();

	void TestCase1();

	void TestCase2();

	void TestCase3();

	void TestCase4();

	void TestCase5();

}


void Test::RunTests()
{
	Test::TestCase1();
	Test::TestCase2();
	Test::TestCase3();
	Test::TestCase4();
	Test::TestCase5();
};

//Ensures textures load prior to game run, The test forces the textures to be bad and cause a fail load, in which case it will print a Test successful
void Test::TestCase1()
{
	Game Temp;
	std::string good[9] = { "good1.png", "good2.png", "good3.png", "goodM1.png", "goodM2.png", "goodM3.png", "goodH1.png", "goodH2.png", "goodH3.png" },
		bad[18] = { "syntax1.png", "syntax2.png", "syntax3.png", "syntaxM1.png", "syntaxM2.png", "syntaxM3.png", "syntaxH1.png", "syntaxH2.png", "syntaxH3.png",
				   "logic1.png", "logic2.png", "logic3.png", "logicM1.png", "logicM2.png", "logicM3.png", "logicH1.png", "logicH2.png", "logicH3.png" };

	std::string menuTextures[6] = { "title.png", "play.png", "howTo.png", "exit.png", "back.png", "howToScreen.png" };
	try {
		Temp.runGame(good, 9, bad, 19, menuTextures, 0);
		std::cout << "Test failed" << std::endl;
	}
	catch (std::runtime_error)
	{
		std::cout << "Test successful" << std::endl;
		return;
	}
}

//1 fully functional loop
void Test::TestCase2()
{
	Game Temp;
	std::string good[9] = { "good1.png", "good2.png", "good3.png", "goodM1.png", "goodM2.png", "goodM3.png", "goodH1.png", "goodH2.png", "goodH3.png" },
		bad[18] = { "syntax1.png", "syntax2.png", "syntax3.png", "syntaxM1.png", "syntaxM2.png", "syntaxM3.png", "syntaxH1.png", "syntaxH2.png", "syntaxH3.png",
				   "logic1.png", "logic2.png", "logic3.png", "logicM1.png", "logicM2.png", "logicM3.png", "logicH1.png", "logicH2.png", "logicH3.png" };

	std::string menuTextures[6] = { "title.png", "play.png", "howTo.png", "exit.png", "back.png", "howToScreen.png" };
	
	try {
		Temp.runGame(good, 9, bad, 19, menuTextures, 0, 1);
		std::cout << "Test failed" << std::endl;
	}
	
	catch (std::runtime_error) {
		std::cout << "Test successful" << std::endl;
		return;
	}
	
};



//Score increament correctly
void Test::TestCase3()
{

};

//Score Decreament correctly
void Test::TestCase4()
{

};

//
void Test::TestCase5()
{

};