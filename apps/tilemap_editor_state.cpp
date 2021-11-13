
#include "tilemap_editor_app/tilemap_editor_state.hpp"

#include <SFML/Window/Event.hpp>
#include <cassert>

#include "game_lib/application.hpp"
#include "tilemap_editor_app/tilemap_editor.hpp"

using namespace sf;
using namespace std;

TilemapEditorState::TilemapEditorState(TilemapEditor& tilemapEditor)
    : ApplicationState(tilemapEditor),
      terminal_(tilemapEditor.getWindow().getSize()),
      view_(static_cast<Vector2f>(tilemapEditor.getWindow().getSize()) / 2.0f,
            static_cast<Vector2f>(tilemapEditor.getWindow().getSize())) {
  assert(
      terminalFont_.loadFromFile(RESOURCE_PATH "/ttf/Inconsolata-Regular.ttf"));
  terminal_.setFont(terminalFont_, false);
}

void TilemapEditorState::doHandleEvents(vector<Event> const& events) {
  for (auto const& event : events) {
    switch (event.type) {
      case Event::Resized: {
        view_.setSize(Vector2f(event.size.width, event.size.height));
        view_.setCenter(Vector2f(event.size.width / 2, event.size.height / 2));
        break;
      }

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
  auto const previewView = target.getView();
  target.setView(view_);

  target.draw(terminal_, states);

  target.setView(previewView);
}