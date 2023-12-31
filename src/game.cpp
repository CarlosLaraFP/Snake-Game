#include <iostream>
#include <fstream>
#include "game.h"
#include "food.hpp"
#include "boost.hpp"

Game::Game(std::size_t grid_width, std::size_t grid_height) 
    : snake { grid_width, grid_height }, 
      engine { dev() },
      randomWidth { 0, static_cast<int>(grid_width - 1) },
      randomHeight { 0, static_cast<int>(grid_height - 1) },
      gridWidth { grid_width }, gridHeight { grid_height }
{
    LoadHighScore();

    // limiting ammo to encourage thoughtful use
    ammoReserves.reserve(ammunitionLimit);
    ammoInFlight.reserve(ammunitionLimit);

    auto food = std::make_unique<Food>(grid_width, grid_height);
    SetNewCoordinates(*food);
    consumables.emplace_back(std::move(food));

    auto boost = std::make_unique<Boost>(grid_width, grid_height);
    SetNewCoordinates(*boost);
    consumables.emplace_back(std::move(boost));
}

void Game::Run(const Controller& controller, Renderer& renderer, std::size_t target_frame_duration) 
{
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;

    while (running) 
    {
        frame_start = SDL_GetTicks();

        // Input, Update, Render - the main game loop.
        controller.HandleInput(*this);
        this->UpdateAsync();
        renderer.Render(*this);

        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle takes.
        ++frameCount;
        frame_duration = frame_end - frame_start;

        // Every second, update the window title (because it displays current score and frame rate).
        if (frame_end - title_timestamp >= 500) 
        {
            renderer.UpdateWindowTitle(*this);
            frameCount = 0;
            title_timestamp = frame_end;
        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < target_frame_duration) 
        {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }

    UpdateHighScore();
}

void Game::UpdateAsync()     
{
    if (!snake.alive) return;

    // Updating game objects concurrently by category.
    // Note this is for demonstration purposes and should only be implemented for computationally intensive tasks.

    // Avoids holding onto completed futures and ensure that the resources associated with the asynchronous operations are released.
    updates.clear();
    // Passing pointers to the async tasks instead of copying
    updates.emplace_back(std::async(std::launch::async, &Snake::Update, &snake));
    updates.emplace_back(std::async(std::launch::async, &Game::UpdateProjectiles, this));
    updates.emplace_back(std::async(std::launch::async, &Game::UpdateConsumables, this));

    for (auto& update : updates) { update.wait(); }
}

void Game::UpdateProjectiles()
{
    std::lock_guard<std::mutex> lock { mutex };

    for (auto& projectile : ammoInFlight)
    {
        projectile.Update();
    }

    // Remove projectiles with negative X or Y
    ammoInFlight.erase(
        // reordering so that all the elements to be removed are moved to the end
        std::remove_if(
            ammoInFlight.begin(),
            ammoInFlight.end(),
            [](const Projectile& projectile) { return projectile.IsOffScreen(); }
        ),
        ammoInFlight.end()
    );
}

void Game::UpdateConsumables()
{
    for (auto& consumable : consumables)
    {
        consumable->Update(*this);
    }
}

void Game::Quit() { running = false; }

int Game::GetScore() const { return score; }

int Game::GetHighScore() const { return highScore; }

int Game::GetSnakeSize() const { return snake.size; }

int Game::GetFrameRate() const { return frameCount; }

int Game::GetAmmunition() const { return ammoReserves.size(); }

int Game::GetProjectilesInFlight() const { return ammoInFlight.size(); }

Snake& Game::GetSnake() { return snake; }

void Game::IncrementScore(int value) { score += value; }

void Game::IncrementAmmunition(int value) 
{ 
    for (auto i = 0; i < value; ++i)
    {
        if (ammoReserves.size() == ammunitionLimit) return;

        ammoReserves.emplace_back(gridWidth, gridHeight);
    }
}

void Game::SetNewCoordinates(Consumable& consumable)
{
    // Try until the new consumable location is different than any snake coordinates.
    while (true) 
    {
        SDL_Point newCoordinates { randomWidth(engine) , randomHeight(engine) };

        // Check that the location is not already occupied by a snake or another consumable.
        if (!snake.SnakeCell(newCoordinates) && !ConsumableCell(newCoordinates))
        {
            // replace with SDL_Point move semantics
            consumable.SetCoordinates(newCoordinates.x, newCoordinates.y);
            return;
        }
    }
}

bool Game::ConsumableCell(const SDL_Point& point) const
{
    for (const auto& consumable : consumables) 
    {
        auto& location = consumable->GetCoordinates();

        if (point.x == location.x && point.y == location.x)
        {
            return true;
        }
    }
    return false;
}

void Game::LoadHighScore()
{
    std::ifstream scoreFile { highScoreFileName };

    if (scoreFile.is_open())
    {
        scoreFile >> highScore;
        scoreFile.close();
    }
    else
    {
        std::ofstream newScoreFile { highScoreFileName };

        if (newScoreFile.is_open())
        {
            newScoreFile << highScore;
            newScoreFile.close();
        }
    }
}

void Game::UpdateHighScore()
{
    if (score > highScore) 
    {  
        // opens the file and truncates it it to zero length if it already exists to overwrite it with the new highscore
        std::ofstream updatedScoreFile { highScoreFileName, std::ios::trunc };

        if (updatedScoreFile.is_open())
        {
            updatedScoreFile << score;
            updatedScoreFile.close();
        }
    }
}
