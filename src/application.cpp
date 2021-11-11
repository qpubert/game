#include "game_lib/application.hpp"

#include <SFML/Window/Event.hpp>
#include <iostream>

using namespace sf;
using namespace std;

Application::Application(String const &windowTitle)
    : windowTitle_(windowTitle) {
  window_.setKeyRepeatEnabled(false);
  window_.setFramerateLimit(60);
}

void Application::run() {
  const auto fullscreenVideoMode = VideoMode::getDesktopMode();
  window_.create(fullscreenVideoMode, windowTitle_, Style::Close);

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
    window_.display();
  }
}