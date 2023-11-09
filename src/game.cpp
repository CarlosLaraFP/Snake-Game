#include "game.h"
#include <iostream>
#include <fstream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height), engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) 
{
    LoadHighScore();
    PlaceSinglePoint();
    PlaceDoublePoint();
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

        // After every 500 ms, update the window title (because it displays current score and frame rate).
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

void Game::Quit() { running = false; }

void Game::PlaceSinglePoint() 
{
    int x, y;
    // Try until the new consumable location is different than any snake coordinates.
    while (true) {
        x = random_w(engine);
        y = random_h(engine);
        // Check that the location is not occupied by a snake item before placing consumable.
        if (!snake.SnakeCell(x, y)) 
        {
            singlePoint.x = x;
            singlePoint.y = y;
            return;
        }
    }
}

void Game::PlaceDoublePoint()
{
    int x, y;
    // Try until the new consumable location  is different than any snake and single point coordinates.
    while (true)
    {
        x = random_w(engine);
        y = random_h(engine);
        // Check that the location is not occupied by a snake item before placing consumable.
        if (!snake.SnakeCell(x, y) && x != static_cast<int>(singlePoint.x) && y != static_cast<int>(singlePoint.y))
        {
            doublePoint.x = x;
            doublePoint.y = y;
            return;
        }
    }
}

void Game::Update() 
{
    if (!snake.alive) return;

    snake.Update();

    int new_x = static_cast<int>(snake.head_x);
    int new_y = static_cast<int>(snake.head_y);

    // Check if there's food at the new head coordinate
    if (singlePoint.x == new_x && singlePoint.y == new_y)
    {
        ++score;
        PlaceSinglePoint();
        snake.GrowBody();
        snake.speed += 0.02;
    }
    else if (doublePoint.x == new_x && doublePoint.y == new_y)
    {
        score += 2;
        PlaceDoublePoint();
        // special item does not grow snake body and does not increase speed (but is ephemeral)
    }
}

int Game::GetScore() const { return score; }

int Game::GetHighScore() const { return highScore; }

int Game::GetSnakeSize() const { return snake.size; }

int Game::GetFrameRate() const { return frameCount; }

SDL_Point& Game::GetSinglePoint() { return singlePoint; }

SDL_Point& Game::GetDoublePoint() { return doublePoint; }

Snake& Game::GetSnake() { return snake; }

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
