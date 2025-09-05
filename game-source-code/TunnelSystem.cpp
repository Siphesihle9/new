#include "TunnelSystem.hpp"
#include "raylib-cpp.hpp"
#include <cmath>

TunnelSystem::TunnelSystem() : gridWidth(0), gridHeight(0), cellSize(32) {}

void TunnelSystem::Initialize(int screenWidth, int screenHeight, int cellSize) {
    this->cellSize = cellSize;
    gridWidth = (screenWidth + cellSize - 1) / cellSize;
    gridHeight = (screenHeight + cellSize - 1) / cellSize;
    
    grid.assign(gridHeight, std::vector<bool>(gridWidth, false));
    dugCells.clear();
}

void TunnelSystem::DigTunnel(Vector2 position, float radius) {
    int startX = static_cast<int>((position.x - radius) / cellSize);
    int endX = static_cast<int>((position.x + radius) / cellSize);
    int startY = static_cast<int>((position.y - radius) / cellSize);
    int endY = static_cast<int>((position.y + radius) / cellSize);
    
    for (int y = startY; y <= endY; ++y) {
        for (int x = startX; x <= endX; ++x) {
            if (IsValidGridPosition(x, y)) {
                Vector2 cellCenter = {
                    x * cellSize + cellSize / 2.0f,
                    y * cellSize + cellSize / 2.0f
                };
                
                if (CheckCollisionCircles(position, radius, cellCenter, cellSize / 2.0f)) {
                    grid[y][x] = true;
                    dugCells.insert(y * gridWidth + x);
                }
            }
        }
    }
}

bool TunnelSystem::IsInTunnel(Vector2 position) const {
    int gridX = static_cast<int>(position.x / cellSize);
    int gridY = static_cast<int>(position.y / cellSize);
    
    if (IsValidGridPosition(gridX, gridY)) {
        return grid[gridY][gridX];
    }
    return false;
}

bool TunnelSystem::IsValidGridPosition(int gridX, int gridY) const {
    return gridX >= 0 && gridX < gridWidth && gridY >= 0 && gridY < gridHeight;
}

int TunnelSystem::PositionToGridIndex(float x, float y) const {
    int gridX = static_cast<int>(x / cellSize);
    int gridY = static_cast<int>(y / cellSize);
    return gridY * gridWidth + gridX;
}

void TunnelSystem::Draw(const raylib::Texture2D& dirtTex, const raylib::Texture2D& tunnelTex) const {
    // Draw dirt background
    for (int y = 0; y < gridHeight; ++y) {
        for (int x = 0; x < gridWidth; ++x) {
            Vector2 pos = {x * static_cast<float>(cellSize), y * static_cast<float>(cellSize)};
            DrawTexture(dirtTex, pos.x, pos.y, WHITE);
        }
    }
    
    // Draw tunnels
    for (const auto& cellIndex : dugCells) {
        int y = cellIndex / gridWidth;
        int x = cellIndex % gridWidth;
        Vector2 pos = {x * static_cast<float>(cellSize), y * static_cast<float>(cellSize)};
        DrawTexture(tunnelTex, pos.x, pos.y, WHITE);
    }
}