#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "MainMenu.hpp"
#include <random>

int main()
{
 
    std::string menuTextures[6] = { "title.png", "play.png", "howTo.png", "exit.png", "back.png", "howToScreen.png"};
    std::string good[9] = { "good1.png", "good2.png", "good3.png", "goodM1.png", "goodM2.png", "goodM3.png", "goodH1.png", "goodH2.png", "goodH3.png" },
        bad[18] = { "syntax1.png", "syntax2.png", "syntax3.png", "syntaxM1.png", "syntaxM2.png", "syntaxM3.png", "syntaxH1.png", "syntaxH2.png", "syntaxH3.png",
                   "logic1.png", "logic2.png", "logic3.png", "logicM1.png", "logicM2.png", "logicM3.png", "logicH1.png", "logicH2.png", "logicH3.png" };
    Game game;
   
    game.runGame(good, 9, bad, 18, menuTextures, 6);

    return 0;
}