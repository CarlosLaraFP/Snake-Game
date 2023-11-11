#include <iostream>
#include <string>
#include <algorithm>
#include "renderer.h"
#include "consumable.hpp"
#include "game.h"

Renderer::Renderer(
    const std::size_t screen_width, const std::size_t screen_height,
    const std::size_t grid_width, const std::size_t grid_height
) : screen_width(screen_width), screen_height(screen_height), grid_width(grid_width), grid_height(grid_height) 
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create Window
    sdl_window = SDL_CreateWindow(
        "Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        screen_width, screen_height, SDL_WINDOW_SHOWN
    );

    if (sdl_window == nullptr) {
        std::cerr << "Window could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create renderer
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);

    if (sdl_renderer == nullptr) {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
}

Renderer::~Renderer() 
{
    SDL_DestroyWindow(sdl_window);
    sdl_window = nullptr;
    sdl_renderer = nullptr;
    SDL_Quit();
}

void Renderer::Render(Game& game)
{
    // Same SDL_Rect gets reused for all geometric draws
    SDL_Rect block;
    block.w = screen_width / grid_width; // 20
    block.h = screen_height / grid_height; // 20

    // Clear screen by initializing back buffer with a color
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);
    // everything from the previous frame has been cleared

    // Render consumable items (multiple types)
    RenderConsumables(block, game.consumables);

    // Render projectiles
    RenderProjectiles(block, game.ammoInFlight);

    // Render snake head and body
    RenderSnake(block, game.GetSnake());

    // Update Screen (swap finished back buffer with front buffer) - called once per frame
    SDL_RenderPresent(sdl_renderer);
}

void Renderer::RenderConsumables(SDL_Rect& block, std::vector<std::unique_ptr<Consumable>>& consumables)
{
    for (const auto& consumable : consumables)
    {
        SDL_SetRenderDrawColor(sdl_renderer, consumable->R(), consumable->G(), consumable->B(), consumable->A());
        block.x = consumable->X() * block.w;
        block.y = consumable->Y() * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
    }
}

void Renderer::RenderProjectiles(SDL_Rect& block, std::vector<Projectile>& projectiles)
{
    // semi transparent red
    SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 0, 128);

    // Render projectiles with non-negative X and Y
    for (const auto& projectile : projectiles) 
    {
        if (projectile.X() >= 0 && projectile.Y() >= 0) 
        {
            block.x = projectile.X() * block.w;
            block.y = projectile.Y() * block.h;
            SDL_RenderFillRect(sdl_renderer, &block);
        }
    }
}

void Renderer::RenderSnake(SDL_Rect& block, Snake& snake)
{
    // Render snake's body
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    for (const SDL_Point& point : snake.body)
    {
        block.x = point.x * block.w;
        block.y = point.y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
    }

    // Render snake's head
    block.x = snake.X() * block.w;
    block.y = snake.Y() * block.h;

    if (snake.alive)
    {
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    }
    else
    {
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    }

    SDL_RenderFillRect(sdl_renderer, &block);
}

void Renderer::UpdateWindowTitle(const Game& game) 
{
    std::string title {
        "Snake Score: " + std::to_string(game.GetScore()) + 
        " Ammunition: " + std::to_string(game.GetAmmunition()) +
        //" Projectiles In Flight: " + std::to_string(game.GetProjectilesInFlight()) +
        " High Score: " + std::to_string(game.GetHighScore()) + 
        " FPS: " + std::to_string(game.GetFrameRate())
    };

    SDL_SetWindowTitle(sdl_window, title.c_str());
}
