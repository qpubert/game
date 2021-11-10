#include "game_lib/tilemap.hpp"
#include "game_lib/tileset.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Vertex.hpp>

using namespace sf;
using namespace std;

Tilemap::Tilemap(Vector2f const &tileSize)
    : tileSize_(tileSize),
      tilesetPtr_(nullptr),
      vertexBuffer_(PrimitiveType::Quads, VertexBuffer::Usage::Static)
{
}

Tilemap::Tilemap(Tileset const &tileset)
    : tilesetPtr_(&tileset),
      tileSize_(static_cast<Vector2f>(tileset.getTileSize())),
      vertexBuffer_(PrimitiveType::Quads, VertexBuffer::Usage::Static)
{
}

Tilemap::Tilemap(Tileset const &tileset, Vector2f const &tileSize)
    : tilesetPtr_(&tileset),
      tileSize_(tileSize),
      vertexBuffer_(PrimitiveType::Quads, VertexBuffer::Usage::Static)
{
}

bool Tilemap::setTileset(Tileset const &tileset, bool resetTileSize)
{
    tilesetPtr_ = &tileset;
    if (resetTileSize)
    {
        tileSize_ = static_cast<Vector2f>(tileset.getTileSize());
        return updateVertices();
    }

    return true;
}

bool Tilemap::create(unsigned int width, unsigned int height)
{
    size_ = {width, height};
    if (!vertexBuffer_.create(width * height * 4))
    {
        return false;
    }

    tiles_.resize(width * height);
    fill(begin(tiles_), end(tiles_), 0);

    return updateVertices();
}

void Tilemap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(vertexBuffer_, states);
}

bool Tilemap::updateVertices()
{
    const auto width = size_.x;
    const auto height = size_.y;

    vector<Vertex> vertices(width * height * 4);
    for (size_t row = 0, tileIndex = 0; row < height; ++row)
    {
        for (size_t col = 0; col < width; ++col, tileIndex)
        {
            auto &tlVertex = vertices[tileIndex * 4 + 0];
            auto &trVertex = vertices[tileIndex * 4 + 1];
            auto &brVertex = vertices[tileIndex * 4 + 2];
            auto &blVertex = vertices[tileIndex * 4 + 3];

            const float leftBound = static_cast<float>(col) * tileSize_.x;
            const float topBound = static_cast<float>(row) * tileSize_.y;
            const float rightBound = leftBound + tileSize_.x;
            const float bottomBound = topBound + tileSize_.y;

            tlVertex.position = {leftBound, topBound};
            trVertex.position = {rightBound, topBound};
            brVertex.position = {rightBound, bottomBound};
            blVertex.position = {leftBound, bottomBound};
        }
    }

    return vertexBuffer_.update(vertices.data());
}