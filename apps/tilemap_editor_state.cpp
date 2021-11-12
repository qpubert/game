
#include "tilemap_editor_app/tilemap_editor_state.hpp"

#include <SFML/Window/Event.hpp>
#include <cassert>

#include "game_lib/application.hpp"
#include "tilemap_editor_app/tilemap_editor.hpp"

using namespace sf;
using namespace std;

TilemapEditorState::TilemapEditorState(TilemapEditor& tilemapEditor)
    : ApplicationState(tilemapEditor),
      terminal_(tilemapEditor.getWindow().getSize()) {
  assert(
      terminalFont_.loadFromFile(RESOURCE_PATH "/ttf/Inconsolata-Regular.ttf"));
  terminal_.setFont(terminalFont_, false);
}

void TilemapEditorState::doHandleEvents(vector<Event> const& events) {
  for (auto const& event : events) {
    switch (event.type) {
      case Event::Closed:
        getApplication().stopRunning();
        break;

      case Event::KeyPressed:
        switch (event.key.code) {
          case Keyboard::Escape:
            getApplication().stopRunning();
            break;

          default:
            break;
        }

      default:
        break;
    }
  }

  terminal_.handleEvents(events);
}
void TilemapEditorState::doUpdate(Time const elapsedTime) {
  terminal_.update(elapsedTime);
}

void TilemapEditorState::doRender(RenderTarget& target,
                                  RenderStates states) const {
  target.draw(terminal_, states);
}