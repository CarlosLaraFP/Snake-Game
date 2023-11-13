#pragma once

#include <vector>
#include <mutex>
#include "SDL.h"

enum class Direction { kUp, kDown, kLeft, kRight };

class Snake 
{
public:
    Snake(std::size_t grid_width, std::size_t grid_height)
        : grid_width{ grid_width }, grid_height { grid_height },
          head_x(grid_width / 2), head_y(grid_height / 2) {}

    void Update();
    void GrowBody();
    void IncrementSpeed(float value);
    bool SnakeCell(const SDL_Point& point);
    void ChangeDirection(Direction input, Direction opposite);
    bool HeadCollision(const SDL_Point& point) const;
    bool BodyCollision(const SDL_Point& point) const;

    const SDL_Point GetCoordinates() const;

    float speed { 0.1f };
    int size { 1 };
    bool alive { true };
    float head_x, head_y;
    std::vector<SDL_Point> body;
    Direction direction = Direction::kUp;

private:
    std::size_t grid_width, grid_height;
    bool growing { false };
    std::mutex mutex;

    void UpdateHead();
    void UpdateBody(SDL_Point& current_cell, SDL_Point& prev_cell);
};
