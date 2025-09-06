#include "Harpoon.hpp"
#include "raylib-cpp.hpp"

Harpoon::Harpoon(Vector2 startPosition, Vector2 direction, float maxDistance)
    : position(startPosition), direction(Vector2Normalize(direction)),
      speed(500.0f), maxDistance(maxDistance), distanceTraveled(0), shouldRemove(false) {}

void Harpoon::Update() {
    position.x += direction.x * speed * GetFrameTime();
    position.y += direction.y * speed * GetFrameTime();
    
    distanceTraveled += speed * GetFrameTime();
    
    // Check boundaries and max distance
    if (position.x < 0 || position.x > GetScreenWidth() ||
        position.y < 0 || position.y > GetScreenHeight() ||
        distanceTraveled >= maxDistance) {
        shouldRemove = true;
    }
}

void Harpoon::Draw() const {
    Vector2 endPos = {
        position.x - direction.x * 15.0f,
        position.y - direction.y * 15.0f
    };
    
    DrawLineEx(endPos, position, 3.0f, YELLOW);
    DrawCircleV(position, 5.0f, RED);
}