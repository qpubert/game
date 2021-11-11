#include "tilemap_editor_app/tilemap_editor.hpp"

#include "tilemap_editor_app/tilemap_editor_state.hpp"

using namespace std;

TilemapEditor::TilemapEditor() : Application("Tilemap editor") {
  stateStack_.pushState(make_unique<TilemapEditorState>(*this));
}