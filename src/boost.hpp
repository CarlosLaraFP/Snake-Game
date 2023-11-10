#pragma once

#include "consumable.hpp"

class Game;

class Boost : public Consumable
{
public:
    Boost(std::size_t width, std::size_t height);

    void Update(Game& game) override;
};