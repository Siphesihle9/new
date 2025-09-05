#pragma once
#include "raylib-cpp.hpp"
#include "TunnelSystem.hpp"

enum class MonsterState {
    NORMAL,
    DISEMBODIED,
    INFLATING,
    POPPED
};

class Monster {
private:
    Vector2 position;
    Vector2 velocity;
    float radius;
    float speed;
    bool isDragon;
    MonsterState state;
    Color color;
    float stateTimer;
    float inflationLevel;
    
    Vector2 ChooseDirection(const Vector2& targetPos, const TunnelSystem& tunnelSystem);
    bool CanMoveTo(const Vector2& newPos, const TunnelSystem& tunnelSystem) const;
    
public:
    Monster(Vector2 startPosition, float radius, float speed, bool dragon = false);
    
    void Update(const Vector2& targetPos, const TunnelSystem& tunnelSystem);
    void Draw() const;
    void Inflate();
    
    Vector2 GetPosition() const { return position; }
    float GetRadius() const { return radius; }
    bool IsDragon() const { return isDragon; }
    MonsterState GetState() const { return state; }
    void SetPosition(Vector2 newPos) { position = newPos; }
};
