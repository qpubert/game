#ifndef APPLICATION_STATE_HPP
#define APPLICATION_STATE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>
#include <vector>

namespace sf {
struct Event;
}

class ApplicationState {
 public:
  ApplicationState() = default;
  virtual ~ApplicationState() noexcept = default;

  void handleEvents(std::vector<sf::Event> const& events);
  void update(sf::Time const elapsedTime);
  void render(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

 protected:
  virtual void doHandleEvents(std::vector<sf::Event> const& events) = 0;
  virtual void doUpdate(sf::Time const elapsedTime) = 0;
  virtual void doRender(sf::RenderTarget& target,
                        sf::RenderStates states) const = 0;
};

#endif  // APPLICATION_STATE_HPP