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

    ammoReserves.reserve(ammunitionLimit); // limiting ammo to encourage thoughtful use

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
        this->Update();
        renderer.Render(*this);

        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle takes.
        ++frameCount;
        frame_duration = frame_end - frame_start;

        // Every second, update the window title (because it displays current score and frame rate).
        if (frame_end - title_timestamp >= 1000) 
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

void Game::Update() 
{
    if (!snake.alive) return;

    snake.Update();

    int newX = static_cast<int>(snake.head_x);
    int newY = static_cast<int>(snake.head_y);

    // TODO: snake head no longer determines Update to Boost consumable

    for (auto& consumable : consumables)
    {
        if (consumable->X() == newX && consumable->Y() == newY)
        {
            consumable->Update(*this);
        }
    }
}

void Game::Quit() { running = false; }

int Game::GetScore() const { return score; }

int Game::GetHighScore() const { return highScore; }

int Game::GetSnakeSize() const { return snake.size; }

int Game::GetFrameRate() const { return frameCount; }

int Game::GetAmmunition() const { return ammoReserves.size(); }

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
    while (true) {
        int newX = randomWidth(engine);
        int newY = randomHeight(engine);
        // Check that the location is not already occupied by a snake or another consumable.
        if (!snake.SnakeCell(newX, newY) && !ConsumableCell(newX, newY))
        {
            consumable.SetX(newX);
            consumable.SetY(newY);
            return;
        }
    }
}

bool Game::ConsumableCell(int x, int y)
{
    for (const auto& consumable : consumables) {
        if (x == consumable->X() && y == consumable->Y()) {
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
