#include "projectile.hpp"

void Projectile::SetVelocity(float headX, float headY, Direction snakeHeadDirection)
{
    x = headX;
    y = headY;
    direction = snakeHeadDirection;
}

void Projectile::Update()
{
    switch (direction)
    {
    case Direction::kUp:
        y -= speed;
        break;

    case Direction::kDown:
        y += speed;
        break;

    case Direction::kLeft:
        x -= speed;
        break;

    case Direction::kRight:
        x += speed;
        break;
    }
}

bool Projectile::Collision(const Consumable& consumable) const
{
    auto& point = consumable.GetCoordinates();

    return this->X() == point.x && this->Y() == point.y;
}

bool Projectile::IsOffScreen() const
{
    return this->X() < 0 || this->X() > gridWidth || this->Y() < 0 || this->Y() > gridHeight;
}
