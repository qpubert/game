#include <iostream>

#include "tilemap_editor_app/tilemap_editor.hpp"

using namespace std;

int main() {
  try {
    TilemapEditor tilemapEditor;
    tilemapEditor.run();
  } catch (exception const& e) {
    cerr << e.what() << endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}