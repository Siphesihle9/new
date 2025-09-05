#pragma once

#include "raylib-cpp.hpp"
#include "Player.hpp"
#include "Monster.hpp"
#include "Rock.hpp"
#include "Harpoon.hpp"
#include "BonusItem.hpp"
#include "TunnelSystem.hpp"
#include "GameState.hpp"
#include <vector>
#include <memory>
#include <string>

class Game {
private:
    std::unique_ptr<raylib::Window> window;
    Player player;
    std::vector<Monster> monsters;
    std::vector<Rock> rocks;
    std::vector<Harpoon> harpoons;
    std::vector<BonusItem> bonusItems;
    TunnelSystem tunnelSystem;
    
    GameState currentState;
    int score;
    int lives;
    int currentLevel;
    float gameTime;
    
    raylib::Texture2D dirtTexture;
    raylib::Texture2D tunnelTexture;
    raylib::Font gameFont;
    
    void InitializeLevel();
    void LoadLevelFromFile(const std::string& filename);
    void SpawnMonsters(int count);
    void SpawnRocks(int count);
    void SpawnBonusItems();
    void CheckCollisions();
    void UpdateGameplay();
    void DrawGameplay();
    void DrawUI();
    void DrawSplashScreen();
    void DrawGameOverScreen();
    void DrawLevelCompleteScreen();
    
public:
    Game();
    ~Game() = default;
    
    void Run();
    void ResetGame();
    void NextLevel();
};
