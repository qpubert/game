#include "game_lib/application_state.hpp"

using namespace sf;
using namespace std;

ApplicationState::ApplicationState(Application& application)
    : renderUnderlyingState_(false), application_(application) {}

void ApplicationState::handleEvents(vector<Event> const& events) {
  doHandleEvents(events);
}

void ApplicationState::update(Time const elapsedTime) { doUpdate(elapsedTime); }

void ApplicationState::render(RenderTarget& target, RenderStates states) const {
  doRender(target, states);
}