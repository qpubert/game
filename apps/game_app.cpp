#include <iostream>

#include "game_app/game.hpp"

using namespace std;

int main() {
  try {
    Game game;
    game.run();
  } catch (exception const &e) {
    cerr << e.what() << endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}