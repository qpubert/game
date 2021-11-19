#include "game_app/game.hpp"

#include <unistd.h>

#include <SFML/Window/Event.hpp>

#include "game_lib/tilemap.hpp"
#include "game_lib/tileset.hpp"

using namespace sf;
using namespace std;

VideoMode getInitialVideoMode() {
    auto videoMode = VideoMode::getDesktopMode();
    videoMode.width /= 2;
    videoMode.height /= 2;
    return videoMode;
}

Game::Game() : Application(getInitialVideoMode(), "Game application", Style::Fullscreen) {}