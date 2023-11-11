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
    if (this->X() == game.GetSnake().X() && this->Y() == game.GetSnake().Y())
    {
        game.IncrementScore(1);
        game.IncrementAmmunition(5);
        game.SetNewCoordinates(*this); // revise
        game.GetSnake().GrowBody();
        game.GetSnake().IncrementSpeed(0.02);
    }
}
