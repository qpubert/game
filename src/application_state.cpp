#include "game_lib/application_state.hpp"

void ApplicationState::handleEvents(std::vector<sf::Event> const& events) {
  doHandleEvents(events);
}

void ApplicationState::update(sf::Time const elapsedTime) {
  doUpdate(elapsedTime);
}

void ApplicationState::render(sf::RenderTarget& target,
                              sf::RenderStates states) const {
  doRender(target, states);
}