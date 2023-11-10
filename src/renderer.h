#pragma once

#include <vector>
#include "SDL.h"

class Game;
class Consumable;

class Renderer 
{
public:
    Renderer(const std::size_t screen_width, const std::size_t screen_height,
             const std::size_t grid_width, const std::size_t grid_height);
    ~Renderer();

    void Render(Game& game);
    void UpdateWindowTitle(const Game& game);

private:
    SDL_Window* sdl_window;
    SDL_Renderer* sdl_renderer;

    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;

    void RenderConsumable(SDL_Rect& block, const Consumable& consumable);
};
