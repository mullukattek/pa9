#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <random>
int main()
{

    Game game;


    game.runGame();
    //sf::VideoMode s;
    //sf::RenderWindow window(s.getDesktopMode(), "SFML works!");
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);
    //std::queue<sf::CircleShape> test;

    //test.push(shape);
    //test.push(sf::CircleShape(100.f));
    //sf::Clock clock;
   
    //window.setFramerateLimit(60);

    //while (window.isOpen())
    //{
    //    float deltaTime = clock.restart().asSeconds(); //makes movement of objects based on time and not on framerate
    //   while (const std::optional event = window.pollEvent())
    //    {
    //        if (event->is<sf::Event::Closed>())
    //        {
    //            window.close();
    //        }
    //    }

    //    shape.move(sf::Vector2f(0, 100.f * deltaTime));

    //    window.clear();
    //    window.display();
    //}
}