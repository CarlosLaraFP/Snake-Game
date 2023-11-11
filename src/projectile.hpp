#pragma once

#include "SDL.h"
#include "snake.h"
#include "consumable.hpp"

class Projectile
{
public:
	Projectile(size_t width, size_t height) : gridWidth{ width }, gridHeight{ height } {}

    void SetVelocity(float headX, float headY, Direction snakeHeadDirection);
	void Update();
	bool Collision(const Consumable& consumable) const;
	bool IsOffScreen() const;

	const int& X() const { return static_cast<int>(x); }
	const int& Y() const { return static_cast<int>(y); }

private:
	size_t gridWidth, gridHeight;
	//SDL_Point gridLocation;
	Direction direction;
	float x, y;
    float speed { 0.5f };
    int maxDistance { 5 };
};
