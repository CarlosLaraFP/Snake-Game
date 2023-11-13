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
                game.GetSnake().ChangeDirection(Direction::kUp, Direction::kDown);
                break;

            case SDLK_DOWN:
                game.GetSnake().ChangeDirection(Direction::kDown, Direction::kUp);
                break;

            case SDLK_LEFT:
                game.GetSnake().ChangeDirection(Direction::kLeft, Direction::kRight);
                break;

            case SDLK_RIGHT:
                game.GetSnake().ChangeDirection(Direction::kRight, Direction::kLeft);
                break;

            case SDLK_SPACE:
                // O(1)
                if (!game.ammoReserves.empty()) 
                {
                    auto& projectile = game.ammoReserves.back();
                    projectile.SetVelocity(game.GetSnake().head_x, game.GetSnake().head_y, game.GetSnake().direction);
                    game.ammoInFlight.emplace_back(std::move(projectile));
                    game.ammoReserves.pop_back();
                }
                break;
            }
        }
    }
}


