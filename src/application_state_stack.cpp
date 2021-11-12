#include "game_lib/application_state_stack.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

using namespace sf;
using namespace std;

void ApplicationStateStack::pushState(ApplicationStatePtr state) {
  applicationStates_.push_back(move(state));
}

ApplicationStatePtr ApplicationStateStack::popState() {
  if (applicationStates_.empty()) return {};

  auto result = move(applicationStates_.back());
  applicationStates_.pop_back();
  return result;
}

void ApplicationStateStack::handleEvents(vector<Event> const& events) {
  if (applicationStates_.empty()) return;
  applicationStates_.back()->handleEvents(events);
}

void ApplicationStateStack::update(Time const elapsedTime) {
  if (applicationStates_.empty()) return;
  applicationStates_.back()->update(elapsedTime);
}

void ApplicationStateStack::render(RenderTarget& target,
                                   RenderStates states) const {
  auto const firstStateToRenderIt =
      find_if_not(crbegin(applicationStates_), crend(applicationStates_),
                  [](auto const& applicationStatePtr) {
                    return applicationStatePtr->renderUnderlyingState_;
                  });

  for (auto applicationStateIt = firstStateToRenderIt.base();
       applicationStateIt != cend(applicationStates_); ++applicationStateIt) {
    (*applicationStateIt)->render(target, states);
  }
}