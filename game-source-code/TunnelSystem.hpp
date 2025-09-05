#pragma once
#include "raylib-cpp.hpp"
#include <vector>
#include <unordered_set>

class TunnelSystem {
private:
    int gridWidth;
    int gridHeight;
    int cellSize;
    std::vector<std::vector<bool>> grid;
    std::unordered_set<int> dugCells;
    
    int PositionToGridIndex(float x, float y) const;
    bool IsValidGridPosition(int gridX, int gridY) const;
    
public:
    TunnelSystem();
    
    void Initialize(int screenWidth, int screenHeight, int cellSize);
    void DigTunnel(Vector2 position, float radius);
    bool IsInTunnel(Vector2 position) const;
    void Draw(const raylib::Texture2D& dirtTex, const raylib::Texture2D& tunnelTex) const;
    
    const std::unordered_set<int>& GetDugCells() const { return dugCells; }
};