#include "renderer.h"
#include <iostream>
#include <string>

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
    // Same SDL_Rect gets reused for all rectangular drawings?
    SDL_Rect block;
    block.w = screen_width / grid_width; // 20
    block.h = screen_height / grid_height; // 20

    // Clear screen by initializing back buffer with a color
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);
    // everything from the previous frame has been cleared

    // Render consumable items (multiple types)
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    block.x = game.GetSinglePoint().x * block.w;
    block.y = game.GetSinglePoint().y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
    // double point item
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x80, 0x00, 0xFF);
    block.x = game.GetDoublePoint().x * block.w;
    block.y = game.GetDoublePoint().y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);

    // Render snake's body
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    for (const SDL_Point& point : game.GetSnake().body)
    {
        block.x = point.x * block.w;
        block.y = point.y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
    }

    // Render snake's head
    block.x = static_cast<int>(game.GetSnake().head_x) * block.w;
    block.y = static_cast<int>(game.GetSnake().head_y) * block.h;

    if (game.GetSnake().alive)
    {
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    } 
    else
    {
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    }

    SDL_RenderFillRect(sdl_renderer, &block);

    // Update Screen (swap finished back buffer with front buffer) - called once per frame
    SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(const Game& game) 
{
    std::string title {
        "Snake Score: " + std::to_string(game.GetScore()) + 
        " High Score: " + std::to_string(game.GetHighScore()) + 
        " FPS: " + std::to_string(game.GetFrameRate())
    };

    SDL_SetWindowTitle(sdl_window, title.c_str());
}
