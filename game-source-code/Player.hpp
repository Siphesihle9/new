#pragma once
#include "raylib-cpp.hpp"
#include "Harpoon.hpp"
#include "TunnelSystem.hpp"
#include <vector>
#include <memory>
#include <optional>

class Player {
private:
    Vector2 position;
    Vector2 velocity;
    Vector2 facingDirection;
    float radius;
    float speed;
    bool isDigging;
    Color color;
    float digCooldown;
    float maxDigCooldown;
    
public:
    Player(Vector2 startPosition, float radius, float speed);
    
    void Update();
    void Update(float deltaTime); // For testing
    void Draw() const;
    void Move(Vector2 direction);
    void Move(Vector2 direction, float deltaTime); // For testing
    std::optional<Harpoon> FireHarpoon();
    void UpdateTunnels(TunnelSystem& tunnelSystem);
    
    Vector2 GetPosition() const { return position; }
    float GetRadius() const { return radius; }
    Vector2 GetFacingDirection() const { return facingDirection; }
    bool IsDigging() const { return isDigging; }
    void SetPosition(Vector2 newPos) { position = newPos; }
    void SetVelocity(Vector2 newVel) { velocity = newVel; } // For testing
};