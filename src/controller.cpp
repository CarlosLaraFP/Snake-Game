#include "controller.h"
#include <iostream>
#include "SDL.h"

void Controller::ChangeDirection(Snake& snake, Snake::Direction input, Snake::Direction opposite) const 
{
    // Do not allow the user to turn the snake into itself (unless it's the starting size)
    if (snake.direction != opposite || snake.size == 1) snake.direction = input;
    else return;
}

void Controller::HandleInput(Game& game) const 
{
  SDL_Event e;

  while (SDL_PollEvent(&e)) 
  {
    if (e.type == SDL_QUIT) 
    {
        game.Quit();
    } 
    else if (e.type == SDL_KEYDOWN) 
    {
      switch (e.key.keysym.sym) 
      {
        case SDLK_UP:
          ChangeDirection(game.GetSnake(), Snake::Direction::kUp, Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(game.GetSnake(), Snake::Direction::kDown, Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(game.GetSnake(), Snake::Direction::kLeft, Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(game.GetSnake(), Snake::Direction::kRight, Snake::Direction::kLeft);
          break;
      }
    }
  }
}