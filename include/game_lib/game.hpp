#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics/RenderWindow.hpp>

class Game
{
public:
    Game(sf::String const& windowTitle);

    void run();

private:
    sf::String windowTitle_;
    sf::RenderWindow window_;
};

#endif // GAME_HPP