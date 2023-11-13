#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() 
{
    //std::lock_guard<std::mutex> lock { mutex };

    // We first capture the head's cell before updating.
    SDL_Point prev_cell { this->X(), this->Y() };

    UpdateHead();

    // Capture the head's cell after updating.
    SDL_Point current_cell { this->X(), this->Y() };

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

    // Check if the snake has died.
    for (const auto& item : body) 
    {
        if (current_head_cell.x == item.x && current_head_cell.y == item.y) 
        {
            alive = false;
        }
    }
}

const int Snake::X() const { return static_cast<int>(head_x); }

const int Snake::Y() const { return static_cast<int>(head_y); }

void Snake::GrowBody() { growing = true; }

void Snake::IncrementSpeed(float value) { speed += value; }

bool Snake::HeadCollision(const int& x, const int& y) const
{
    return x == this->X() && y == this->Y();
}

bool Snake::BodyCollision(const int& x, const int& y) const
{
    for (auto const& item : body)
    {
        if (x == item.x && y == item.y) return true;
    }
    return false;
}

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) 
{
    return HeadCollision(x, y) || BodyCollision(x, y);
}
