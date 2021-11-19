#include "game_lib/application.hpp"

#include <SFML/Window/Event.hpp>
#include <cassert>
#include <iostream>

using namespace sf;
using namespace std;

Application::Application(String const &windowTitle,
                         int const targetUpdatesPerSecond)
    : windowTitle_(windowTitle),
      windowStyle_(Style::Close),
      targetUpdatesPerSecond_(targetUpdatesPerSecond),
      running_(false) {
  window_.setVerticalSyncEnabled(true);
}

void Application::setFullscreen(bool const fullscreen,
                                bool const recreateWindow) {
  if (fullscreen != (windowStyle_ & Style::Fullscreen)) {
    windowStyle_ ^= Style::Fullscreen;
    if (recreateWindow) {
      window_.create(videoMode_, windowTitle_, windowStyle_);
    }
  }
}

void Application::setResizable(bool const resizable,
                               bool const recreateWindow) {
  if (resizable != (windowStyle_ & Style::Resize)) {
    windowStyle_ ^= Style::Resize;
    if (recreateWindow) {
      window_.create(videoMode_, windowTitle_, windowStyle_);
    }
  }
}

void Application::resize(Vector2u const newSize, bool const recreateWindow) {
  videoMode_.width = newSize.x;
  videoMode_.height = newSize.y;
  if (recreateWindow) {
    window_.create(videoMode_, windowTitle_, windowStyle_);
  }
}

void Application::run() {
  window_.create(videoMode_, windowTitle_, windowStyle_);

  Clock clock;
  Time accumulator;

  running_ = true;
  while (running_) {
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

void Application::stopRunning() { running_ = false; }

void Application::setTargetUpdatesPerSecond(int const targetUpdatesPerSecond) {
  assert(targetUpdatesPerSecond > 0);
  targetUpdatesPerSecond_ = targetUpdatesPerSecond;
}

View Application::getDefaultView() const {
  auto const viewSize = static_cast<Vector2f>(window_.getSize());
  return {viewSize / 2.0f, viewSize};
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