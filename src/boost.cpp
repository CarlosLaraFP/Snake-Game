#include <algorithm>
#include "boost.hpp"
#include "game.h"

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
    for (auto i = game.ammoInFlight.begin(); i != game.ammoInFlight.end(); ++i)
    {
        if (i->Collision(*this))
        {
            game.IncrementScore(2);
            game.SetNewCoordinates(*this); // revise
            game.GetSnake().IncrementSpeed(-0.01);

            std::swap(*i, game.ammoInFlight.back());
            game.ammoInFlight.pop_back();
            return;
        }
    }
}
