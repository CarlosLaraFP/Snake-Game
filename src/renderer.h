#pragma once

#include <vector>
#include <memory>
#include "SDL.h"

class Game;
class Consumable;
class Projectile;
class Snake;

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

    void RenderConsumables(SDL_Rect& block, std::vector<std::unique_ptr<Consumable>>& consumables);
    void RenderProjectiles(SDL_Rect& block, std::vector<Projectile>& projectiles);
    void RenderSnake(SDL_Rect& block, Snake& snake);
};
