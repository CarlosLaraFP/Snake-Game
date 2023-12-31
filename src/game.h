#pragma once

#include <memory>
#include <random>
#include <mutex>
#include <future>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "projectile.hpp"
#include "consumable.hpp"
/*
    unique_ptr needs to know the complete type to correctly manage the object, including its size and how to delete it.
    When the compiler processes templates (like std::unique_ptr), it requires the full definition of the involved types
    to generate the correct code for operations such as object destruction. Hence, we need to include it.
*/

// forward references required when two header files reference each other
class Controller;
class Renderer;
class Consumable;

class Game 
{
public:
    Game(std::size_t grid_width, std::size_t grid_height);
    void Run(const Controller& controller, Renderer& renderer, std::size_t target_frame_duration);
    void Quit();
    int GetScore() const;
    int GetHighScore() const;
    int GetSnakeSize() const;
    int GetFrameRate() const;
    int GetAmmunition() const;
    int GetProjectilesInFlight() const;
    void IncrementScore(int value);
    void IncrementAmmunition(int value);
    bool ConsumableCell(const SDL_Point& point) const;
    void SetNewCoordinates(Consumable& game);
    Snake& GetSnake();
    std::vector<std::unique_ptr<Consumable>> consumables;
    std::vector<Projectile> ammoReserves;
    std::vector<Projectile> ammoInFlight;
    // To ensure thread-safe reads/writes
    std::mutex mutex;

private:
    size_t gridWidth, gridHeight;
    Snake snake;
    bool running { true };
    int score { 0 };
    int highScore { 0 };
    int frameCount { 0 };
    const int ammunitionLimit { 10 };
    std::string highScoreFileName { "highscore.txt" };
    // Create a random number generator
    std::random_device dev;
    std::mt19937 engine;
    // Define distributions for width and height ranges
    std::uniform_int_distribution<int> randomWidth;
    std::uniform_int_distribution<int> randomHeight;
    // Asynchronous update tasks
    std::vector<std::future<void>> updates;

    void LoadHighScore();
    void UpdateHighScore();
    void UpdateAsync();
    void UpdateProjectiles();
    void UpdateConsumables();
};
