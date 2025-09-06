#include "Rock.hpp"
#include "raylib-cpp.hpp"

Rock::Rock(Vector2 startPosition, float radius)
    : position(startPosition), velocity({0, 0}), radius(radius),
      isFalling(false), isSettled(false), fallSpeed(100.0f), color(GRAY) {}

void Rock::Update(const TunnelSystem& tunnelSystem) {
    Update(tunnelSystem, GetFrameTime()); // Default to GetFrameTime()
}

void Rock::Update(const TunnelSystem& tunnelSystem, float deltaTime) {
    if (isSettled) return;
    
    if (!isFalling) {
        // Check if there's no tunnel below
        Vector2 below = {position.x, position.y + radius + 2.0f};
        if (!tunnelSystem.IsInTunnel(below)) {
            StartFalling();
        }
    }
    
    if (isFalling) {
        velocity.y += fallSpeed * deltaTime;
        position.y += velocity.y * deltaTime;
        
        // Check if hit ground or tunnel
        Vector2 below = {position.x, position.y + radius + 1.0f};
        if (tunnelSystem.IsInTunnel(below) || position.y + radius >= GetScreenHeight()) {
            isFalling = false;
            isSettled = true;
            velocity = {0, 0};
        }
    }
}

void Rock::StartFalling() {
    if (!isSettled && !isFalling) {
        isFalling = true;
        velocity.y = 0;
    }
}

void Rock::Draw() const {
    DrawCircleV(position, radius, color);
    
    // Rock texture details
    DrawCircleLines(position.x, position.y, radius, DARKGRAY);
    DrawCircle(position.x - radius * 0.3f, position.y - radius * 0.2f, radius * 0.15f, DARKGRAY);
    DrawCircle(position.x + radius * 0.2f, position.y + radius * 0.3f, radius * 0.1f, DARKGRAY);
}