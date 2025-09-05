#pragma once
#include "raylib-cpp.hpp"

enum class BonusType {
    APPLE,
    CHERRY,
    STRAWBERRY,
    ORANGE
};

class BonusItem {
private:
    Vector2 position;
    BonusType type;
    int value;
    float spawnTime;
    float lifeTime;
    Color color;
    
public:
    BonusItem(Vector2 position, BonusType type, int value);
    
    void Update();
    void Draw() const;
    
    Vector2 GetPosition() const { return position; }
    int GetValue() const { return value; }
    float GetRadius() const { return 15.0f; }
    bool ShouldRemove() const;
};