#include "food.hpp"
#include "game.h"

Food::Food(size_t width, size_t height)
{
    gridWidth = width;
    gridHeight = height;
    r = 0xFF;
    g = 0xCC;
    b = 0x00;
    a = 0xFF;
}

void Food::Update(Game& game)
{
    if (game.GetSnake().HeadCollision(this->GetCoordinates()))
    {
        game.IncrementScore(1);
        game.IncrementAmmunition(2);
        game.SetNewCoordinates(*this);
        game.GetSnake().GrowBody();
        game.GetSnake().IncrementSpeed(0.02);
    }
}
