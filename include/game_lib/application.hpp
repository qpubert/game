#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "game_lib/application_state_stack.hpp"

class Application {
 public:
  Application(sf::String const& windowTitle, int const targetUpdatesPerSecond = 60);
  ~Application() noexcept = default;

  void run();
  
  void setTargetUpdatesPerSecond(int const targetUpdatesPerSecond);

 protected:
  ApplicationStateStack stateStack_;

 private:
  sf::String windowTitle_;
  sf::RenderWindow window_;
  std::vector<sf::Event> events_;
  int targetUpdatesPerSecond_;

  void handleEvents();
  void update(sf::Time const elapsedTime);
  void render();
};

#endif  // APPLICATION_HPP