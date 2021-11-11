#ifndef GAME_HPP
#define GAME_HPP

#include "game_lib/application.hpp"

class Game : public Application {
 public:
  Game();
  ~Game() noexcept = default;
};

#endif  // GAME_HPP