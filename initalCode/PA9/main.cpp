#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "MainMenu.hpp"
#include <random>

int main()
{
 
    std::string menuTextures[5] = { "title.png", "play.png", "howTo.png", "exit.png", "back.png"};
    std::string good[1] = { "test1.png" }, bad[1] = { "test2.jpg" };
    Game game;
   
    game.runGame(good, 1, bad, 1, menuTextures, 5);

    return 0;
}