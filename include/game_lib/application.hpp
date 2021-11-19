#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "game_lib/application_state_stack.hpp"

class Application {
 public:
  Application(sf::String const& windowTitle, int const targetUpdatesPerSecond = 60);
  ~Application() noexcept = default;

  void setFullscreen(bool const fullscreen, bool const recreateWindow = true);
  void setResizable(bool const resizable, bool const recreateWindow = true);
  void resize(sf::Vector2u const newSize, bool const recreateWindow = true);

  void run();
  void stopRunning();

  void setTargetUpdatesPerSecond(int const targetUpdatesPerSecond);

  sf::View getDefaultView() const;
  sf::Window const& getWindow() const noexcept { return window_; }

 protected:
  ApplicationStateStack stateStack_;

 private:
  sf::String windowTitle_;
  sf::Uint32 windowStyle_;
  sf::VideoMode videoMode_;
  sf::RenderWindow window_;
  std::vector<sf::Event> events_;
  int targetUpdatesPerSecond_;
  bool running_;

  void handleEvents();
  void update(sf::Time const elapsedTime);
  void render();
};

#endif  // APPLICATION_HPP