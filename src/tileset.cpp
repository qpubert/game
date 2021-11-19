#include "game_lib/tileset.hpp"

using namespace sf;
using namespace std;

Tileset::Tileset(Vector2u const &tileSize, unsigned int tileCount,
                 unsigned int columns)
    : tileSize_(tileSize), tileCount_(tileCount), columns_(columns) {}

bool Tileset::loadTextureFromFile(string const &filename, IntRect const &area) {
  return texture_.loadFromFile(filename, area);
}

sf::Vector2u Tileset::getTileTexCoords(unsigned int tile) const {
  assert(tile < tileCount_);
  return {tileSize_.x * (tile % columns_), tileSize_.y * (tile / columns_)};
}