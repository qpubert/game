#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "game_lib/application_state_stack.hpp"

class Application {
 public:
  Application(sf::VideoMode const& windowVideoMode,
              sf::String const& windowTitle, sf::Uint32 const windowStyle,
              int const targetUpdatesPerSecond = 60);
  ~Application() noexcept = default;

  void setStyle(sf::Uint32 const style);
  void setFullscreen(bool const fullscreen);
  void setResizable(bool const resizable);

  void resize(sf::Vector2u const newSize);

  void run();
  void stopRunning();

  void setTargetUpdatesPerSecond(int const targetUpdatesPerSecond);

  sf::View getDefaultView() const;
  sf::Window const& getWindow() const noexcept { return window_; }
  sf::Uint32 getWindowStyle() const noexcept { return windowStyle_; }

  bool isFullscreen() const noexcept {
    return windowStyle_ & sf::Style::Fullscreen;
  }

 protected:
  ApplicationStateStack stateStack_;

 private:
  sf::VideoMode windowedVideoMode_;
  sf::VideoMode fullscreenVideoMode_;
  sf::VideoMode const* currentVideoModePtr_;
  sf::String windowTitle_;
  sf::Uint32 windowStyle_;
  sf::RenderWindow window_;

  std::vector<sf::Event> events_;

  int targetUpdatesPerSecond_;
  bool running_;
  bool windowNeedsRecreation_;

  void handleEvents();
  void update(sf::Time const elapsedTime);
  void render();
};

#endif  // APPLICATION_HPP