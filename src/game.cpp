#include "game_lib/game.hpp"

#include <iostream>

#include <SFML/Window/Event.hpp>

using namespace sf;
using namespace std;

Game::Game(String const &windowTitle) : windowTitle_(windowTitle)
{
    window_.setKeyRepeatEnabled(false);
    window_.setFramerateLimit(60);
}

void Game::run()
{
    const auto fullscreenVideoMode = VideoMode::getDesktopMode();
    cout << "VideoMode:" << '\n'
         << "\twidth: " << fullscreenVideoMode.width << '\n'
         << "\theight: " << fullscreenVideoMode.height << '\n';

    window_.create(fullscreenVideoMode, windowTitle_, Style::Fullscreen);

    while (window_.isOpen())
    {
        Event event;
        while (window_.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
            {
                window_.close();
                break;
            }

            case Event::KeyPressed:
            {
                switch (event.key.code)
                {
                    case Keyboard::Escape:
                    {
                        window_.close();
                        break;
                    }
                }
            }
            
            default:
                break;
            }
        }

        window_.clear();
        window_.display();
    }
}