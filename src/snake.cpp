#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() 
{
    // We first capture the head's cell before updating.
    SDL_Point prev_cell { static_cast<int>(head_x), static_cast<int>(head_y) };

    UpdateHead();

    // Capture the head's cell after updating.
    SDL_Point current_cell { static_cast<int>(head_x), static_cast<int>(head_y) };

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

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) 
{
    if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) 
    {
        return true;
    }
    for (auto const &item : body) {
        if (x == item.x && y == item.y) {
            return true;
        }
    }
    return false;
}