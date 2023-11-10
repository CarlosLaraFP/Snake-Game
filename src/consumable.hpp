#pragma once

#include "SDL.h"
#include "game.h"

// When accessing another class' members, then the other class needs to be defined in the same file for successful compilation.

class Game;

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

	const int& X() const { return x; }
	const int& Y() const { return y; }

	void SetX(int value) { x = value; }
	void SetY(int value) { y = value; }

protected:
	int x, y;
	size_t gridWidth, gridHeight;
	Uint8 r, g, b, a;
	SDL_Point point;
	SDL_Point& GetPoint() { return point; }
};
