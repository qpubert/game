#include "game_lib/terminal.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "game_lib/application.hpp"

using namespace sf;
using namespace std;

Terminal::Terminal(Application& application, Vector2f const position,
                   Vector2f const size, float const padding)
    : position_(position),
      size_(size),
      padding_(padding),
      layoutNeedsComputation_(true),
      application_(application) {
  background_.setFillColor({0, 0, 0, 150});
  text_.setFillColor(Color::Green);
}

void Terminal::setFont(Font const& font, bool const recomputeLayout) {
  text_.setFont(font);
  layoutNeedsComputation_ = layoutNeedsComputation_ || recomputeLayout;
}

void Terminal::handleEvents(vector<Event> const& events) {
  for (auto const& event : events) {
    if (event.type == Event::TextEntered) {
      if (event.text.unicode == '\b') {
        if (!inputBuffer_.isEmpty()) {
        inputBuffer_.erase(inputBuffer_.getSize() - 1);
        }
      } else if (event.text.unicode == '\r' || event.text.unicode == '\n') {
        continue;
      } else {
        inputBuffer_ += event.text.unicode;
      }

      layoutNeedsComputation_ = true;
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

          layoutNeedsComputation_ = true;
          break;
        }

        default:
          break;
      }
    }
  }
}

void Terminal::update(Time const) {
  if (layoutNeedsComputation_) {
    computeLayout();
    layoutNeedsComputation_ = false;
  }
}

void Terminal::draw(RenderTarget& target, RenderStates) const {
  auto const previousView = target.getView();
  target.setView(application_.getDefaultView());

  target.draw(background_);
  target.draw(text_);

  target.setView(previousView);
}

void Terminal::setPosition(sf::Vector2f const& position) {
  position_ = position;
  layoutNeedsComputation_ = true;
}
void Terminal::setSize(sf::Vector2f const& size) {
  size_ = size;
  layoutNeedsComputation_ = true;
}

void Terminal::wrapText() {
  auto const width = size_.x - 2 * padding_;
  auto const font = text_.getFont();
  auto const characterSize = text_.getCharacterSize();
  auto const boldness = text_.getStyle() & Text::Bold;
  auto const whitespaceWidthWithoutLetterSpacing =
      font->getGlyph(L' ', characterSize, boldness).advance;
  auto const letterSpacingFactor = text_.getLetterSpacing();
  auto const letterSpacing =
      (whitespaceWidthWithoutLetterSpacing / 3.f) * (letterSpacingFactor - 1.f);
  auto const whitespaceWidth =
      whitespaceWidthWithoutLetterSpacing + letterSpacing;

  auto buffer = text_.getString();
  auto characterPos = 0.0f;
  Uint32 previousCharacter = 0;
  for (size_t characterIndex = 0; characterIndex < buffer.getSize();
       ++characterIndex) {
    auto const character = buffer[characterIndex];
    auto const& characterGlyph =
        font->getGlyph(character, characterSize, boldness);
    auto const kerning =
        font->getKerning(previousCharacter, character, characterSize);

    previousCharacter = character;
    characterPos += kerning;
    switch (character) {
      case L' ': {
        characterPos += whitespaceWidth;
        continue;
      }

      case L'\t': {
        characterPos += whitespaceWidth * 4;
        continue;
      }

      case L'\n': {
        characterPos = 0;
        continue;
      }

      default:
        break;
    }

    characterPos += characterGlyph.advance + letterSpacing;
    if (width < characterPos) {
      buffer.insert(characterIndex, L'\n');
      characterPos = characterGlyph.advance + letterSpacing;
      characterIndex++;
    }
  }

  text_.setString(buffer);
}

void Terminal::computeLayout() {
  background_.setSize(size_);
  background_.setPosition(position_);

  auto bufferCopy = historyBuffer_;
  bufferCopy += L"\n> ";
  bufferCopy += inputBuffer_;

  text_.setString(bufferCopy);
  auto const wrappedText = wrapText();
  text_.setString(wrappedText);

  auto const numberOfNewlines =
      count(cbegin(wrappedText), cend(wrappedText), L'\n');
  auto const font = text_.getFont();
  auto const characterSize = text_.getCharacterSize();
  auto const textLineHeight =
      font->getLineSpacing(characterSize) * text_.getLineSpacing();
  text_.setPosition(position_.x + padding_,
                    position_.y + size_.y -
                        (numberOfNewlines + 1) * textLineHeight - padding_);
}