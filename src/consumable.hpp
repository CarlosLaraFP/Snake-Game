#pragma once

#include "SDL.h"

// When accessing another class' members in a header file, then the other class needs to be defined in the same file for successful compilation.

class Game;

// abstract class
class Consumable
{
public:
	// ensures that destructors of derived classes are called when an object is deleted through a pointer to the base class
	virtual ~Consumable() = default;
	virtual void Update(Game& game) = 0;

	const Uint8& R() const { return r; }
	const Uint8& G() const { return g; }
	const Uint8& B() const { return b; }
	const Uint8& A() const { return a; }

	const int& X() const { return gridLocation.x; }
	const int& Y() const { return gridLocation.y; }

	void SetX(int value) { gridLocation.x = value; }
	void SetY(int value) { gridLocation.y = value; }

protected:
	size_t gridWidth, gridHeight;
	Uint8 r, g, b, a; // needed for SDL_Renderer
	SDL_Point gridLocation; // needed for instantiation in discrete space

private:
	float x, y; // needed for motion
};
