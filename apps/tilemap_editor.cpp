#include "tilemap_editor_app/tilemap_editor.hpp"

#include "tilemap_editor_app/tilemap_editor_state.hpp"

using namespace sf;
using namespace std;

TilemapEditor::TilemapEditor() : Application("Tilemap editor") {
  auto const desktopMode = VideoMode::getDesktopMode();

  setFullscreen(false, false);
  setResizable(true, false);
  resize({desktopMode.width / 2, desktopMode.height / 2}, false);

  stateStack_.pushState(make_unique<TilemapEditorState>(*this));
}