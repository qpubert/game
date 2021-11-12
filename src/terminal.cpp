#include "game_lib/terminal.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

using namespace sf;
using namespace std;

Terminal::Terminal(Vector2u const windowSize) : size_(windowSize) {
  background_.setFillColor(Color::Red);
  text_.setFillColor(Color::Green);
}

void Terminal::setFont(Font const& font, bool const recomputeLayout) {
  text_.setFont(font);
  if (recomputeLayout) {
    computeLayout();
  }
}

void Terminal::handleEvents(vector<Event> const& events) {
  for (auto const& event : events) {
    if (event.type == Event::TextEntered) {
      inputBuffer_ += event.text.unicode;
      computeLayout();
    } else if (event.type == Event::Resized) {
      size_ = {event.size.width, event.size.height};
      computeLayout();
    }
  }
}

void Terminal::update(Time const elapsedTime) {}

void Terminal::draw(RenderTarget& target, RenderStates states) const {
  auto const previousView = target.getView();
  target.setView(target.getDefaultView());

  target.draw(background_);

  auto const textBounds = text_.getGlobalBounds();
  RectangleShape blueDebug({textBounds.width, textBounds.height});
  blueDebug.setFillColor(Color::Blue);
  blueDebug.setPosition(textBounds.left, textBounds.top);
  target.draw(blueDebug);

  target.draw(text_);

  target.setView(previousView);
}

bool tryInsertingNewlineToPreventOverflow(String& buffer, Text& text,
                                          float const horizontalThreshold) {
  for (size_t characterIndex = 0; characterIndex != buffer.getSize();
       ++characterIndex) {
    auto const characterPos = text.findCharacterPos(characterIndex);
    if (characterPos.x > horizontalThreshold) {
      buffer.insert(characterIndex, "\n");
      text.setString(buffer);
      return true;
    }
  }

  return false;
}

void Terminal::computeLayout() {
  auto const fSize = static_cast<Vector2f>(size_);

  background_.setSize({fSize.x, fSize.y / 2});
  background_.setPosition(0, fSize.y / 2);

  auto bufferCopy = historyBuffer_;
  bufferCopy += "\n > ";
  bufferCopy += inputBuffer_;

  text_.setString(bufferCopy);
  while (text_.getLocalBounds().width > fSize.x) { // TODO: make this a finite loop
    if (!tryInsertingNewlineToPreventOverflow(bufferCopy, text_, fSize.x)) {
      break;
    }
  }

  auto const textLocalBounds = text_.getLocalBounds();
  text_.setPosition(0, fSize.y - textLocalBounds.top - textLocalBounds.height);
}