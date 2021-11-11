#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "game_lib/application_state_stack.hpp"

class Application {
 public:
  Application(sf::String const& windowTitle);
  ~Application() noexcept = default;

  void run();

 private:
  sf::String windowTitle_;
  sf::RenderWindow window_;
  ApplicationStateStack stateStack_;
  std::vector<sf::Event> events_;

  void handleEvents();
  void update(sf::Time const elapsedTime);
  void render();
};

#endif  // APPLICATION_HPP