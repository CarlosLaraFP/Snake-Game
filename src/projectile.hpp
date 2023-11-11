#pragma once

#include "SDL.h"

class Projectile
{
public:
	Projectile(size_t width, size_t height) : gridWidth{ width }, gridHeight{ height } {}

private:
	size_t gridWidth, gridHeight;
	SDL_Point location;
	float speed { 0.1f };
};
