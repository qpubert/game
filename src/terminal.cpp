#include "game_lib/terminal.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <cmath>
#include <iostream>

using namespace sf;
using namespace std;

Terminal::Terminal(Vector2u const windowSize)
    : view_(static_cast<Vector2f>(windowSize) / 2.0f,
            static_cast<Vector2f>(windowSize)) {
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
      if (event.text.unicode == '\b' && !inputBuffer_.isEmpty()) {
        inputBuffer_.erase(inputBuffer_.getSize() - 1);
      } else if (event.text.unicode == '\r' || event.text.unicode == '\n') {
        continue;
      } else {
        inputBuffer_ += event.text.unicode;
      }

      computeLayout();
    } else if (event.type == Event::Resized) {
      view_.setSize(Vector2f(event.size.width, event.size.height));
      view_.setCenter(Vector2f(event.size.width / 2, event.size.height / 2));
      computeLayout();
    } else if (event.type == Event::KeyPressed) {
      switch (event.key.code) {
        case Keyboard::Return: {
          if (event.key.shift) {
            inputBuffer_ += '\n';
          } else {
            historyBuffer_ += '\n';
            historyBuffer_ += inputBuffer_;
            inputBuffer_.clear();
          }

          computeLayout();
          break;
        }

        default:
          break;
      }
    }
  }
}

void Terminal::update(Time const elapsedTime) {}

void Terminal::draw(RenderTarget& target, RenderStates states) const {
  auto const previousView = target.getView();
  target.setView(view_);

  target.draw(background_);
  target.draw(text_);

  target.setView(previousView);
}

void Terminal::wrapText() {
  auto const width = view_.getSize().x;
  auto const font = text_.getFont();
  auto const characterSize = text_.getCharacterSize();
  auto const boldness = text_.getStyle() & Text::Bold;

  auto buffer = text_.getString();
  auto characterPos = 0.0f;
  for (size_t characterIndex = 0; characterIndex < buffer.getSize();
       ++characterIndex) {
    auto const character = buffer[characterIndex];
    auto const& characterGlyph =
        font->getGlyph(character, characterSize, boldness);
    auto const characterWidth =
        characterGlyph.advance * text_.getLetterSpacing();

    characterPos += characterWidth;
    if (width < characterPos && character != '\n') {
      buffer.insert(characterIndex, '\n');
      characterPos = characterWidth;
      characterIndex++;
    }
  }

  text_.setString(buffer);
}

void Terminal::computeLayout() {
  auto const size = view_.getSize();

  background_.setSize({size.x, size.y / 2});
  background_.setPosition(0, size.y / 2);

  auto bufferCopy = historyBuffer_;
  bufferCopy += "\n > ";
  bufferCopy += inputBuffer_;

  text_.setString(bufferCopy);
  wrapText();

  auto const textLocalBounds = text_.getLocalBounds();
  auto const textLineHeight = text_.getCharacterSize() * text_.getLineSpacing();
  text_.setPosition(
      0, size.y - textLocalBounds.top -
             ceil(textLocalBounds.height / textLineHeight) * textLineHeight);
}