#include "BonusItem.hpp"
#include "raylib-cpp.hpp"
#include "raylib-cpp.hpp"

BonusItem::BonusItem(Vector2 position, BonusType type, int value)
    : position(position), type(type), value(value),
      spawnTime(GetTime()), lifeTime(10.0f)
{

    switch (type)
    {
    case BonusType::BONUS_APPLE:
        color = RED;
        break;
    case BonusType::BONUS_CHERRY:
        color = MAROON;
        break;
    case BonusType::BONUS_STRAWBERRY:
        color = PINK;
        break;
    case BonusType::BONUS_ORANGE:
        color = ORANGE;
        break;
    }
}

void BonusItem::Update()
{
    // Bonus items can pulse or animate here
}

void BonusItem::Draw() const
{
    float pulse = sin(GetTime() * 5.0f) * 0.2f + 1.0f;
    float radius = 15.0f * pulse;

    DrawCircleV(position, radius, color);
    DrawCircleLines(position.x, position.y, radius, GOLD);

    // Draw value
    DrawText(TextFormat("%d", value), position.x - 10, position.y - 25, 20, WHITE);
}

bool BonusItem::ShouldRemove() const
{
    return GetTime() - spawnTime > lifeTime;
}