#include "tilemap_editor_app/tilemap_editor.hpp"

#include "tilemap_editor_app/tilemap_editor_state.hpp"

using namespace sf;
using namespace std;

VideoMode getInitialVideoMode() {
  auto videoMode = VideoMode::getDesktopMode();
  videoMode.width /= 2;
  videoMode.height /= 2;
  return videoMode;
} 

TilemapEditor::TilemapEditor() : Application(getInitialVideoMode(), "Tilemap editor", Style::Default) {
  stateStack_.pushState(make_unique<TilemapEditorState>(*this));
}