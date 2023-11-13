#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() 
{
    // We first capture the head's cell before updating.
    SDL_Point prev_cell = this->GetCoordinates();

    UpdateHead();

    // Capture the head's cell after updating.
    SDL_Point current_cell = this->GetCoordinates();

    // Update all of the body vector items if the snake head has moved to a new cell (head changed direction).
    if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) 
    {
        UpdateBody(current_cell, prev_cell);
    }
}

// This method simply grants a velocity to the head in whatever direction it's currently going.
// The origin (0, 0) is at the top-left corner (X increases to the right and Y increases downward).
void Snake::UpdateHead() 
{
    // locking section due to concurrent access to 'speed' variable
    std::unique_lock<std::mutex> lock { mutex };

    switch (direction) 
    {
    case Direction::kUp:
        head_y -= speed;
        break;

    case Direction::kDown:
        head_y += speed;
        break;

    case Direction::kLeft:
        head_x -= speed;
        break;

    case Direction::kRight:
        head_x += speed;
        break;
    }

    lock.unlock();

    // Wrap the Snake around to the beginning if going off of the screen.
    // fmod computes the floating-point remainder of the division of two numbers.
    // Adding grid_width and grid_height guarantees fmod always returns a positive remainder.
    // If the first argument is < than the second argument, the remainder is simply the first argument.
    head_x = fmod(head_x + grid_width, grid_width);
    head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::ChangeDirection(Direction input, Direction opposite)
{
    // Do not allow the user to turn the snake into itself (unless it's the starting size)
    if (direction != opposite || size == 1) direction = input;
    else return;
}

void Snake::UpdateBody(SDL_Point& current_head_cell, SDL_Point& prev_head_cell) 
{
    // locking section due to concurrent access to 'growing' variable
    std::unique_lock<std::mutex> lock { mutex };
    
    // Add previous head location to vector
    body.push_back(prev_head_cell);

    if (!growing) 
    {
        // Remove the tail from the vector.
        body.erase(body.begin());
    } 
    else 
    {
        growing = false;
        size++;
    }

    lock.unlock();

    // Check if the snake has died.
    for (const auto& item : body) 
    {
        if (current_head_cell.x == item.x && current_head_cell.y == item.y) 
        {
            alive = false;
        }
    }
}

const SDL_Point Snake::GetCoordinates() const 
{ 
    return SDL_Point { static_cast<int>(head_x), static_cast<int>(head_y) };
}

void Snake::GrowBody() 
{ 
    std::lock_guard<std::mutex> lock { mutex };

    growing = true; 
}

void Snake::IncrementSpeed(float value) 
{
    std::lock_guard<std::mutex> lock { mutex };

    speed += value; 
}

bool Snake::HeadCollision(const SDL_Point& point) const
{
    SDL_Point current_cell = this->GetCoordinates();

    return point.x == current_cell.x && point.y == current_cell.y;
}

bool Snake::BodyCollision(const SDL_Point& point) const
{
    for (const auto& item : body)
    {
        if (point.x == item.x && point.y == item.y) return true;
    }
    return false;
}

// Check if cell is occupied by snake.
bool Snake::SnakeCell(const SDL_Point& point)
{
    return HeadCollision(point) || BodyCollision(point);
}
