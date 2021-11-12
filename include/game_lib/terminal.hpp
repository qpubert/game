#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

class Terminal : public sf::Drawable {
 public:
  Terminal(sf::Vector2u const windowSize);
  ~Terminal() noexcept = default;

  void setFont(sf::Font const& font, bool const recomputeLayout = true);

  void handleEvents(std::vector<sf::Event> const& events);
  void update(sf::Time const elapsedTime);
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const final override;

  void computeLayout();

 private:
  sf::RectangleShape background_;
  sf::Text text_;
  sf::String historyBuffer_;
  sf::String inputBuffer_;
  sf::Vector2u size_;
};

#endif  // TERMINAL_HPP