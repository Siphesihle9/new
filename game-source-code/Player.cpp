#include "Player.hpp"
#include "raylib-cpp.hpp"
#include <algorithm>
#include <cmath>  // Add this for sqrtf
#include "raylib.h"

Player::Player(Vector2 startPosition, float radius, float speed)
    : position(startPosition), velocity({0, 0}), facingDirection({1, 0}),
    radius(radius), speed(speed), isDigging(false), 
    color(SKYBLUE), digCooldown(0), maxDigCooldown(0.1f) {}

void Player::Update() {
    // Handle input
    Vector2 inputDirection = {0, 0};
    
    if (IsKeyDown(KEY_RIGHT)) inputDirection.x += 1;
    if (IsKeyDown(KEY_LEFT)) inputDirection.x -= 1;
    if (IsKeyDown(KEY_UP)) inputDirection.y -= 1;
    if (IsKeyDown(KEY_DOWN)) inputDirection.y += 1;
    
    if (Vector2Length(inputDirection) > 0) {
        facingDirection = Vector2Normalize(inputDirection);
        Move(inputDirection);
        isDigging = true;
        digCooldown = maxDigCooldown;
    } else {
        isDigging = false;
    }
    
    // Update position with velocity
    position.x += velocity.x * GetFrameTime();
    position.y += velocity.y * GetFrameTime();
    
    // Boundary check
    float screenWidth = GetScreenWidth();
    float screenHeight = GetScreenHeight();
    position.x = std::clamp(position.x, radius, screenWidth - radius);
    position.y = std::clamp(position.y, radius, screenHeight - radius);
    
    // Apply friction
    velocity.x *= 0.8f;
    velocity.y *= 0.8f;
    
    // Update dig cooldown
    if (digCooldown > 0) {
        digCooldown -= GetFrameTime();
    }
}

void Player::Move(Vector2 direction) {
    if (Vector2Length(direction) > 0) {
        direction = Vector2Normalize(direction);
        velocity.x += direction.x * speed * GetFrameTime();
        velocity.y += direction.y * speed * GetFrameTime();
        
        // Limit velocity
        float maxSpeed = speed;
        float currentSpeed = Vector2Length(velocity);
        if (currentSpeed > maxSpeed) {
            velocity = Vector2Scale(Vector2Normalize(velocity), maxSpeed);
        }
    }
}

std::optional<Harpoon> Player::FireHarpoon() {
    if (IsKeyPressed(KEY_SPACE)) {
        return Harpoon(position, facingDirection, 300.0f);
    }
    return std::nullopt;
}

void Player::UpdateTunnels(TunnelSystem& tunnelSystem) {
    if (isDigging && digCooldown <= 0) {
        tunnelSystem.DigTunnel(position, radius);
        digCooldown = maxDigCooldown;
    }
}

void Player::Draw() const {
    DrawCircleV(position, radius, color);
    
    // Draw direction indicator
    if (Vector2Length(facingDirection) > 0) {
        Vector2 endPos = {
            position.x + facingDirection.x * radius * 1.2f,
            position.y + facingDirection.y * radius * 1.2f
        };
        DrawLineEx(position, endPos, 3.0f, RED);
    }
    
    // Change all DrawCircle to DrawCircleV
DrawCircleV(Vector2{position.x - radius * 0.3f, position.y - radius * 0.3f}, radius * 0.2f, WHITE);
DrawCircleV(Vector2{position.x + radius * 0.3f, position.y - radius * 0.3f}, radius * 0.2f, WHITE);
DrawCircleV(Vector2{position.x - radius * 0.3f, position.y - radius * 0.3f}, radius * 0.1f, BLACK);
DrawCircleV(Vector2{position.x + radius * 0.3f, position.y - radius * 0.3f}, radius * 0.1f, BLACK);
}