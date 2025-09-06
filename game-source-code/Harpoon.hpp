#pragma once
#include "raylib-cpp.hpp"

class Harpoon {
private:
    Vector2 position;
    Vector2 direction;
    float speed;
    float maxDistance;
    float distanceTraveled;
    bool shouldRemove;
    
public:
    Harpoon(Vector2 startPosition, Vector2 direction, float maxDistance);
    
    void Update();
    void Draw() const;
    
    Vector2 GetPosition() const { return position; }
    bool ShouldRemove() const { return shouldRemove; }
};
