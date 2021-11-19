#include "game_lib/application.hpp"

#include <SFML/Window/Event.hpp>
#include <cassert>
#include <iostream>

using namespace sf;
using namespace std;

Application::Application(VideoMode const& windowVideoMode,
                         String const& windowTitle, Uint32 const windowStyle,
                         int const targetUpdatesPerSecond)
    : windowedVideoMode_(windowVideoMode),
      fullscreenVideoMode_(VideoMode::getFullscreenModes().front()),
      currentVideoModePtr_((windowStyle & Style::Fullscreen)
                               ? &fullscreenVideoMode_
                               : &windowedVideoMode_),
      windowTitle_(windowTitle),
      windowStyle_(windowStyle),
      window_(*currentVideoModePtr_, windowTitle_, windowStyle_),
      targetUpdatesPerSecond_(targetUpdatesPerSecond),
      running_(false),
      windowNeedsRecreation_(false) {
  window_.setVerticalSyncEnabled(true);
}

void Application::setStyle(Uint32 const style) {
  if (windowStyle_ != style) {
    windowStyle_ = style;
    windowNeedsRecreation_ = true;
  }
}

void Application::setFullscreen(bool const fullscreen) {
  setStyle((windowStyle_ & ~Style::Fullscreen) |
           (fullscreen ? Style::Fullscreen : 0));
  currentVideoModePtr_ =
      fullscreen ? &fullscreenVideoMode_ : &windowedVideoMode_;
}

void Application::setResizable(bool const resizable) {
  setStyle((windowStyle_ & ~Style::Resize) | (resizable ? Style::Resize : 0));
}

void Application::resize(Vector2u const newSize) {
  windowedVideoMode_.width = newSize.x;
  windowedVideoMode_.height = newSize.y;
  windowNeedsRecreation_ = true;
}

void Application::run() {
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

    render();
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
  if (windowNeedsRecreation_) {
    windowNeedsRecreation_ = false;
    window_.create(*currentVideoModePtr_, windowTitle_, windowStyle_);
  }

  stateStack_.update(elapsedTime);
}

void Application::render() {
  window_.clear(Color::White);
  stateStack_.render(window_);
  window_.display();
}