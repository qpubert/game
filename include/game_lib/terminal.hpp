#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

class Application;

class Terminal : public sf::Drawable {
 public:
  Terminal(Application& application, sf::Vector2f const position,
           sf::Vector2f const size, float const padding);
  ~Terminal() noexcept = default;

  void setFont(sf::Font const& font, bool const recomputeLayout = true);

  void handleEvents(std::vector<sf::Event> const& events);
  void update(sf::Time const elapsedTime);
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const final override;

  void setPosition(sf::Vector2f const& position);
  void setSize(sf::Vector2f const& size);
  void computeLayout();
  void wrapText();

 private:
  sf::RectangleShape background_;
  sf::Text text_;
  sf::String historyBuffer_;
  sf::String inputBuffer_;
  sf::Vector2f position_;
  sf::Vector2f size_;
  float padding_;
  bool layoutNeedsComputation_;

  Application& application_;
};

#endif  // TERMINAL_HPP