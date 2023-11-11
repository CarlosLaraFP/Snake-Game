#pragma once

#include "consumable.hpp"

class Game;

class Boost : public Consumable
{
public:
    Boost(size_t width, size_t height);

    void Update(Game& game) override;
};