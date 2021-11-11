#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics/RenderWindow.hpp>

class Application {
 public:
  Application(sf::String const& windowTitle);

  void run();

 private:
  sf::String windowTitle_;
  sf::RenderWindow window_;
};

#endif  // APPLICATION_HPP