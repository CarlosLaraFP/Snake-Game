#include "boost.hpp"

Boost::Boost(std::size_t width, std::size_t height)
{
    gridWidth = width;
    gridHeight = height;
    r = 0x00;
    g = 0x80;
    b = 0x00;
    a = 0xFF;
}

void Boost::Update(Game& game)
{
    // TODO: Only update as soon as the first in-flight Projectile
    game.IncrementScore(2);
    game.SetNewCoordinates(*this); // revise
    game.GetSnake().IncrementSpeed(-0.02);
}
