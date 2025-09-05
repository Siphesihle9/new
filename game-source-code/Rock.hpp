#pragma once
#include "raylib-cpp.hpp"
#include "TunnelSystem.hpp"

class Rock {
private:
    Vector2 position;
    Vector2 velocity;
    float radius;
    bool isFalling;
    bool isSettled;
    float fallSpeed;
    Color color;
    
public:
    Rock(Vector2 startPosition, float radius);
    
    void Update(const TunnelSystem& tunnelSystem);
    void Draw() const;
    
    Vector2 GetPosition() const { return position; }
    float GetRadius() const { return radius; }
    bool IsFalling() const { return isFalling; }
    bool IsSettled() const { return isSettled; }
    void StartFalling();
};
