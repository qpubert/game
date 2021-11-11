#include "game_lib/application.hpp"

#include <SFML/Window/Event.hpp>
#include <cassert>
#include <iostream>

using namespace sf;
using namespace std;

Application::Application(String const &windowTitle,
                         int const targetUpdatesPerSecond)
    : windowTitle_(windowTitle),
      targetUpdatesPerSecond_(targetUpdatesPerSecond) {
  window_.setKeyRepeatEnabled(false);
  window_.setVerticalSyncEnabled(true);
}

void Application::run() {
  auto const fullscreenVideoMode = VideoMode::getDesktopMode();
  window_.create(fullscreenVideoMode, windowTitle_, Style::Fullscreen);

  Clock clock;
  Time accumulator;

  while (window_.isOpen()) {
    handleEvents();

    accumulator += clock.restart();
    if (targetUpdatesPerSecond_) {
      auto const targetUpdateElapsedTime =
          seconds(1.0f / targetUpdatesPerSecond_);
      while (accumulator > targetUpdateElapsedTime) {
        update(targetUpdateElapsedTime);
        accumulator -= targetUpdateElapsedTime;
      }
    }

    window_.clear();
    render();
    window_.display();
  }
}

void Application::setTargetUpdatesPerSecond(int const targetUpdatesPerSecond) {
  assert(targetUpdatesPerSecond > 0);
  targetUpdatesPerSecond_ = targetUpdatesPerSecond;
}

void Application::handleEvents() {
  events_.clear();

  Event event;
  while (window_.pollEvent(event)) {
    events_.push_back(event);
  }

  stateStack_.handleEvents(events_);
}

void Application::update(Time const elapsedTime) {
  stateStack_.update(elapsedTime);
}

void Application::render() { stateStack_.render(window_); }