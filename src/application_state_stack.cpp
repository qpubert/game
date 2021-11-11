#include "game_lib/application_state_stack.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

void ApplicationStateStack::pushState(ApplicationStatePtr state) {
  applicationStates_.push_back(std::move(state));
}

ApplicationStatePtr ApplicationStateStack::popState() {
  if (applicationStates_.empty()) return {};

  auto result = std::move(applicationStates_.back());
  applicationStates_.pop_back();
  return result;
}

void ApplicationStateStack::handleEvents(std::vector<sf::Event> const& events) {
  if (applicationStates_.empty()) return;
  applicationStates_.back()->handleEvents(events);
}

void ApplicationStateStack::update(sf::Time const elapsedTime) {
  if (applicationStates_.empty()) return;
  applicationStates_.back()->update(elapsedTime);
}

void ApplicationStateStack::render(sf::RenderTarget& target,
                                   sf::RenderStates states) const {
  for (auto const& applicationState : applicationStates_) {
    applicationState->render(target, states);
  }
}