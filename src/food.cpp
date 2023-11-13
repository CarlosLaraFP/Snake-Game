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
    if (game.GetSnake().HeadCollision(this->X(), this->Y()))
    {
        game.IncrementScore(1);
        game.IncrementAmmunition(5);
        game.SetNewCoordinates(*this); // revise
        // mutation methods must be locked / std::shard_ptr<Snake>
        game.GetSnake().GrowBody();
        game.GetSnake().IncrementSpeed(0.02);
    }
}
