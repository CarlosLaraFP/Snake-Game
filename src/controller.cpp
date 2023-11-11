#include "controller.h"
#include <iostream>
#include "SDL.h"

void Controller::HandleInput(Game& game) const 
{
    SDL_Event e;

    while (SDL_PollEvent(&e)) 
    {
        if (e.type == SDL_QUIT) 
        {
            game.Quit();
        } 
        else if (e.type == SDL_KEYDOWN) // TODO: Lazy Foo verify too fast input management
        {
            switch (e.key.keysym.sym) 
            {
            case SDLK_UP:
                game.GetSnake().ChangeDirection(Snake::Direction::kUp, Snake::Direction::kDown);
                break;

            case SDLK_DOWN:
                game.GetSnake().ChangeDirection(Snake::Direction::kDown, Snake::Direction::kUp);
                break;

            case SDLK_LEFT:
                game.GetSnake().ChangeDirection(Snake::Direction::kLeft, Snake::Direction::kRight);
                break;

            case SDLK_RIGHT:
                game.GetSnake().ChangeDirection(Snake::Direction::kRight, Snake::Direction::kLeft);
                break;

            case SDLK_SPACE:
                // O(1)
                if (!game.ammoReserves.empty()) 
                {
                    // TODO: Careful about concurrent access to shared resources
                    game.ammoInFlight.push_back(std::move(game.ammoReserves.back()));
                    game.ammoReserves.pop_back();
                }
                break;
            }
        }
    }
}


