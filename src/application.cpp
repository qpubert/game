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
  window_.create(fullscreenVideoMode, windowTitle_, Style::Fullscreen);

  while (window_.isOpen()) {
    window_.clear();
    window_.display();
  }
}

void Application::handleEvents() {
  events_.clear();

  Event event;
  while (window_.pollEvent(event)) {
    events_.push_back(event);
  }

  stateStack_.handleEvents(events_);
}

void Application::update(sf::Time const elapsedTime) {
  stateStack_.update(elapsedTime);
}

void Application::render() { stateStack_.render(window_); }