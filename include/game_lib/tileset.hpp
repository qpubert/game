#ifndef TILESET_HPP
#define TILESET_HPP

#include <SFML/Graphics/Texture.hpp>

class Tileset {
 public:
  Tileset(sf::Vector2u const& tileSize = sf::Vector2u(),
          unsigned int tileCount = 0, unsigned int columns = 0);

  bool loadTextureFromFile(std::string const& filename,
                           sf::IntRect const& area = sf::IntRect());

  inline sf::Vector2u getTileSize() const { return tileSize_; };
  inline sf::Texture const& getTexture() const { return texture_; }

  sf::Vector2u getTileTexCoords(unsigned int tile) const;

 private:
  sf::Vector2u tileSize_;
  unsigned int tileCount_, columns_;
  sf::Texture texture_;
};

#endif  // TILESET_HPP