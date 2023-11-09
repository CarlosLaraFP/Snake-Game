#pragma once

class Consumable
{
public:
	// ensures that destructors of derived classes are called when an object is deleted through a pointer to the base class
	virtual ~Consumable() = default;

	virtual int GetPointValue() = 0;
};