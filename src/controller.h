#pragma once

#include "snake.h"
#include "game.h"

class Game;

class Controller {
public:
    void HandleInput(Game& game) const;
};
