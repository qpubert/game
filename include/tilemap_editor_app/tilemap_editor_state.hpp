#ifndef TILEMAP_EDITOR_STATE_HPP
#define TILEMAP_EDITOR_STATE_HPP

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/View.hpp>

#include "game_lib/application_state.hpp"
#include "game_lib/terminal.hpp"

class TilemapEditor;

class TilemapEditorState final : public ApplicationState {
 public:
  TilemapEditorState(TilemapEditor& tilemapEditor);
  ~TilemapEditorState() noexcept = default;

 private:
  sf::Font terminalFont_;
  Terminal terminal_;
  sf::View view_;
  sf::Vector2u renderTargetSize_;

  void doHandleEvents(std::vector<sf::Event> const& events) final override;
  void doUpdate(sf::Time const elapsedTime) final override;
  void doRender(sf::RenderTarget& target,
                sf::RenderStates states) const final override;
};

#endif  // TILEMAP_EDITOR_STATE_HPP