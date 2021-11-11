#ifndef APPLICATION_STATE_STACK_HPP
#define APPLICATION_STATE_STACK_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include <vector>

#include "game_lib/application_state.hpp"

using ApplicationStatePtr = std::unique_ptr<ApplicationState>;

class ApplicationStateStack final {
 public:
  ApplicationStateStack() = default;
  ~ApplicationStateStack() noexcept = default;

  void pushState(ApplicationStatePtr state);
  ApplicationStatePtr popState();

  void handleEvents(std::vector<sf::Event> const& events);
  void update(sf::Time const elapsedTime);
  void render(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

 private:
  std::vector<ApplicationStatePtr> applicationStates_;
};

#endif  // APPLICATION_STATE_STACK_HPP