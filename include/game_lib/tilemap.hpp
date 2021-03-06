#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>
#include <vector>

class Tileset;

class Tilemap : public sf::Drawable, public sf::Transformable {
 public:
  Tilemap(sf::Vector2f const& tileSize = sf::Vector2f());
  Tilemap(Tileset const& tileset);
  Tilemap(Tileset const& tileset, sf::Vector2f const& tileSize);
  ~Tilemap() noexcept = default;

  bool setTileset(Tileset const& tileset, bool resetTileSize = false);

  bool create(unsigned int width, unsigned int height);

  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

 private:
  Tileset const* tilesetPtr_;
  sf::Vector2u size_;
  sf::Vector2f tileSize_;
  std::vector<unsigned int> tiles_;
  sf::VertexBuffer vertexBuffer_;

  bool updateVertices();
};

#endif  // TILEMAP_HPP