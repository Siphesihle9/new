#include "Rock.hpp"
#include "raylib-cpp.hpp"
#include <iostream> // For debug if needed

Rock::Rock(Vector2 startPosition, float radius)
    : position(startPosition), velocity({0, 0}), radius(radius),
      isFalling(false), isSettled(false), fallSpeed(200.0f), color(GRAY) {
    // Ensure radius is positive
    if (radius <= 0) {
        this->radius = 20.0f; // Default size
    }
}

void Rock::Update(const TunnelSystem& tunnelSystem) {
    float deltaTime = GetFrameTime();
    if (deltaTime <= 0) deltaTime = 0.016f; // Prevent division by zero
    
    Update(tunnelSystem, deltaTime);
}

void Rock::Update(const TunnelSystem& tunnelSystem, float deltaTime) {
    if (isSettled) return;
    
    // Safety check for deltaTime
    if (deltaTime <= 0) deltaTime = 0.016f;
    
    if (!isFalling) {
        // Check if there's no tunnel below with safe bounds checking
        Vector2 below = {position.x, position.y + radius + 5.0f};
        
        // Add bounds checking to prevent infinite recursion
        if (below.y >= GetScreenHeight()) {
            isSettled = true;
            return;
        }
        
        if (!tunnelSystem.IsInTunnel(below)) {
            StartFalling();
        }
    }
    
    if (isFalling) {
        // Apply gravity (acceleration)
        velocity.y += 400.0f * deltaTime; // Gravity acceleration
        position.y += velocity.y * deltaTime;
        
        // Check if hit ground or tunnel with safe bounds
        if (position.y + radius >= GetScreenHeight() - 1.0f) {
            // Hit bottom of screen
            position.y = GetScreenHeight() - radius - 1.0f;
            isFalling = false;
            isSettled = true;
            velocity = {0, 0};
        }
        else {
            // Check tunnel collision
            Vector2 checkPoint = {position.x, position.y + radius + 2.0f};
            if (tunnelSystem.IsInTunnel(checkPoint)) {
                isFalling = false;
                isSettled = true;
                velocity = {0, 0};
            }
        }
    }
}

void Rock::StartFalling() {
    if (!isSettled && !isFalling) {
        isFalling = true;
        velocity.y = 0; // Start with zero velocity
    }
}

void Rock::Draw() const {
    DrawCircleV(position, radius, color);
    
    // Rock texture details
    DrawCircleLines(position.x, position.y, radius, DARKGRAY);
    DrawCircle(position.x - radius * 0.3f, position.y - radius * 0.2f, radius * 0.15f, DARKGRAY);
    DrawCircle(position.x + radius * 0.2f, position.y + radius * 0.3f, radius * 0.1f, DARKGRAY);
}