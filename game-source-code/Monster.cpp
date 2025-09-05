#include "Monster.hpp"
#include "raylib-cpp.hpp"
#include <cmath>
#include <algorithm>

Monster::Monster(Vector2 startPosition, float radius, float speed, bool dragon)
    : position(startPosition), velocity({0, 0}), radius(radius), speed(speed),
      isDragon(dragon), state(MonsterState::NORMAL), 
      color(dragon ? GREEN : RED), stateTimer(0), inflationLevel(0) {}

void Monster::Update(const Vector2& targetPos, const TunnelSystem& tunnelSystem) {
    if (state == MonsterState::POPPED) return;
    
    if (state == MonsterState::INFLATING) {
        stateTimer -= GetFrameTime();
        inflationLevel += GetFrameTime() * 0.5f;
        
        if (stateTimer <= 0) {
            state = MonsterState::POPPED;
        }
        return;
    }
    
    Vector2 direction = ChooseDirection(targetPos, tunnelSystem);
    
    if (Vector2Length(direction) > 0) {
        direction = Vector2Normalize(direction);
        velocity = Vector2Scale(direction, speed);
    }
    
    // Update position
    Vector2 newPos = {
        position.x + velocity.x * GetFrameTime(),
        position.y + velocity.y * GetFrameTime()
    };
    
    if (CanMoveTo(newPos, tunnelSystem)) {
        position = newPos;
    }
    
    // State transitions
    if (state == MonsterState::DISEMBODIED) {
        stateTimer -= GetFrameTime();
        if (stateTimer <= 0 || tunnelSystem.IsInTunnel(position)) {
            state = MonsterState::NORMAL;
        }
    }
}

Vector2 Monster::ChooseDirection(const Vector2& targetPos, const TunnelSystem& tunnelSystem) {
    if (!tunnelSystem.IsInTunnel(position)) {
        // If not in tunnel, try to find nearest tunnel or go disembodied
        if (GetRandomValue(0, 100) < 20) { // 20% chance to go disembodied
            state = MonsterState::DISEMBODIED;
            stateTimer = 2.0f;
            return Vector2Subtract(targetPos, position);
        }
    }
    
    // Basic chase behavior
    Vector2 toTarget = Vector2Subtract(targetPos, position);
    float distance = Vector2Length(toTarget);
    
    if (distance < 200.0f) { // Chase if close
        return toTarget;
    } else { // Wander if far
        return {static_cast<float>(GetRandomValue(-100, 100)) / 100.0f,
                static_cast<float>(GetRandomValue(-100, 100)) / 100.0f};
    }
}

bool Monster::CanMoveTo(const Vector2& newPos, const TunnelSystem& tunnelSystem) const {
    if (state == MonsterState::DISEMBODIED) {
        return true; // Can move anywhere when disembodied
    }
    return tunnelSystem.IsInTunnel(newPos);
}

void Monster::Inflate() {
    if (state == MonsterState::NORMAL) {
        state = MonsterState::INFLATING;
        stateTimer = 3.0f;
        inflationLevel = 0;
    }
}

void Monster::Draw() const {
    if (state == MonsterState::POPPED) return;
    
    if (state == MonsterState::INFLATING) {
        float scale = 1.0f + inflationLevel;
        DrawCircleV(position, radius * scale, Fade(color, 0.7f));
        return;
    }
    
    if (state == MonsterState::DISEMBODIED) {
        // Draw as eyes
        DrawCircle(position.x - radius * 0.5f, position.y, radius * 0.4f, WHITE);
        DrawCircle(position.x + radius * 0.5f, position.y, radius * 0.4f, WHITE);
        DrawCircle(position.x - radius * 0.5f, position.y, radius * 0.2f, BLACK);
        DrawCircle(position.x + radius * 0.5f, position.y, radius * 0.2f, BLACK);
    } else {
        DrawCircleV(position, radius, color);
        
        // Draw details based on type
        if (isDragon) {
            // Dragon features
            DrawCircle(position.x, position.y - radius * 0.5f, radius * 0.3f, DARKGREEN);
        } else {
            // Red monster features
            DrawCircle(position.x, position.y - radius * 0.3f, radius * 0.2f, YELLOW);
        }
    }
}