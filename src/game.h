#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

// forward references required when two header files reference each other
class Controller;
class Renderer;

class Game 
{
public:
    Game(std::size_t grid_width, std::size_t grid_height);
    void Run(const Controller& controller, Renderer& renderer, std::size_t target_frame_duration);
    void Quit();
    void UpdateHighScore();
    int GetScore() const;
    int GetHighScore() const;
    int GetSnakeSize() const;
    int GetFrameRate() const;
    SDL_Point& GetFood();
    Snake& GetSnake();

private:
    Snake snake;
    SDL_Point food;
    bool running { true };
    int score { 0 };
    int highScore { 0 };
    int frameCount { 0 };
    std::string highScoreFileName { "highscore.txt" };
    // Create a random number generator
    std::random_device dev;
    std::mt19937 engine;
    // Define distributions for width and height ranges
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;

    void LoadHighScore();
    void PlaceFood();
    void Update();
};

#endif