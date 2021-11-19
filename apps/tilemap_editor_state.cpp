
#include "tilemap_editor_app/tilemap_editor_state.hpp"

#include <SFML/Window/Event.hpp>
#include <cassert>

#include "game_lib/application.hpp"
#include "tilemap_editor_app/tilemap_editor.hpp"

using namespace sf;
using namespace std;

TilemapEditorState::TilemapEditorState(TilemapEditor& tilemapEditor)
    : ApplicationState(tilemapEditor),
      terminal_(tilemapEditor, targetTerminalPosition(), targetTerminalSize(),
                20.0f),
      view_(tilemapEditor.getDefaultView()) {
  [[maybe_unused]] auto const fontLoaded =
      terminalFont_.loadFromFile(RESOURCE_PATH "/ttf/Inconsolata-Regular.ttf");
  assert(fontLoaded);
  terminal_.setFont(terminalFont_, false);
}

sf::Vector2f TilemapEditorState::targetTerminalPosition() const {
  return {0, static_cast<float>(getApplication().getWindow().getSize().y / 2)};
}

sf::Vector2f TilemapEditorState::targetTerminalSize() const {
  auto const windowSize =
      static_cast<Vector2f>(getApplication().getWindow().getSize());
  return {windowSize.x, windowSize.y / 2};
}

void TilemapEditorState::doHandleEvents(vector<Event> const& events) {
  for (auto const& event : events) {
    switch (event.type) {
      case Event::Closed: {
        getApplication().stopRunning();
        break;
      }

      case Event::KeyPressed: {
        switch (event.key.code) {
          case Keyboard::Escape: {
            getApplication().stopRunning();
            break;
          }

          case Keyboard::F11: {
            auto& app = getApplication();
            app.setFullscreen(!app.isFullscreen());
            break;
          }

          default:
            break;
        }

        break;
      }

      default:
        break;
    }
  }

  terminal_.handleEvents(events);
}

void TilemapEditorState::doUpdate(Time const elapsedTime) {
  auto const& application = getApplication();
  auto const renderTargetSize = application.getWindow().getSize();
  if (renderTargetSize_ != renderTargetSize) {
    renderTargetSize_ = renderTargetSize;

    auto const viewSize = application.getDefaultView().getSize();
    view_.setSize(viewSize);
    terminal_.setPosition(targetTerminalPosition());
    terminal_.setSize(targetTerminalSize());
  }

  terminal_.update(elapsedTime);
}

void TilemapEditorState::doRender(RenderTarget& target,
                                  RenderStates states) const {
  auto const previousView = target.getView();
  target.setView(view_);

  target.draw(terminal_, states);

  target.setView(previousView);
}