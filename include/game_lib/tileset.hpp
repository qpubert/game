#ifndef TILESET_HPP
#define TILESET_HPP

#include <SFML/Graphics/Texture.hpp>

class Tileset
{
public:
    Tileset(sf::Vector2u const& tileSize, unsigned int tileCount, unsigned int columns = 0);

    bool loadTextureFromFile(std::string const& filename, sf::IntRect const& area = sf::IntRect());

    inline sf::Vector2u getTileSize() const { return tileSize_; };

private:
    sf::Vector2u tileSize_;
    unsigned int tileCount_, columns_;
    sf::Texture texture_;
};

#endif // TILESET_HPP