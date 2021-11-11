#include "game_app/game.hpp"

#include <unistd.h>

#include <SFML/Window/Event.hpp>
#include <iostream>

#include "game_lib/tilemap.hpp"
#include "game_lib/tileset.hpp"

using namespace sf;
using namespace std;

Game::Game() : Application("Game application") {}