#include "game_lib/game.hpp"

#include <unistd.h>

#include <SFML/Window/Event.hpp>
#include <iostream>

#include "game_lib/tilemap.hpp"
#include "game_lib/tileset.hpp"

using namespace sf;
using namespace std;

Game::Game(String const &windowTitle) : windowTitle_(windowTitle) {
  window_.setKeyRepeatEnabled(false);
  window_.setFramerateLimit(60);
}

void Game::run() {
  const auto fullscreenVideoMode = VideoMode::getDesktopMode();
  cout << "VideoMode" << '\n'
       << "- width: " << fullscreenVideoMode.width << '\n'
       << "- height: " << fullscreenVideoMode.height << '\n';

  window_.create(fullscreenVideoMode, windowTitle_, Style::Close);

  Tileset tileset({32u, 32u}, 2, 8);
  if (!tileset.loadTextureFromFile("../res/png/tiles.png")) return;

  Tilemap tilemap(tileset);
  if (!tilemap.create(5, 5)) return;

  while (window_.isOpen()) {
    Event event;
    while (window_.pollEvent(event)) {
      switch (event.type) {
        case Event::Closed: {
          window_.close();
          break;
        }

        case Event::KeyPressed: {
          switch (event.key.code) {
            case Keyboard::Escape: {
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
    window_.draw(tilemap);
    window_.display();
  }
}