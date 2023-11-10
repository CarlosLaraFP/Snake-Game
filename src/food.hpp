#pragma once

#include "consumable.hpp"

class Game;

class Food : public Consumable
{
public:
    Food(size_t width, size_t height);

    void Update(Game& game) override;
};
