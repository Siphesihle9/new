#include "Game.hpp"
#include "raylib-cpp.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <optional>

Game::Game() 
    : window(std::make_unique<raylib::Window>(800, 600, "Dig Dug")),
      currentState(GameState::SPLASH),
      score(0),
      lives(3),
      currentLevel(1),
      gameTime(0.0f) {  // Make sure this line ends with a parenthesis
    
    // Load resources
    dirtTexture = raylib::Texture2D("resources/images/dirt.png");
    tunnelTexture = raylib::Texture2D("resources/images/tunnel.png");
    gameFont = raylib::Font("resources/fonts/default.ttf");
    
    tunnelSystem.Initialize(800, 600, 32);
    ResetGame();
}

void Game::InitializeLevel() {
    player = Player({400, 300}, 32.0f, 200.0f);
    monsters.clear();
    rocks.clear();
    harpoons.clear();
    bonusItems.clear();
    
    LoadLevelFromFile("resources/levels/level" + std::to_string(currentLevel) + ".txt");
    SpawnBonusItems();
}

void Game::LoadLevelFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        // Default level if file not found
        SpawnMonsters(3);
        SpawnRocks(5);
        return;
    }
    
    // Simple level format: monster_count,rock_count,monster_positions,rock_positions
    int monsterCount, rockCount;
    file >> monsterCount >> rockCount;
    
    SpawnMonsters(monsterCount);
    SpawnRocks(rockCount);
    
    file.close();
}

void Game::SpawnMonsters(int count) {
    for (int i = 0; i < count; ++i) {
        Vector2 pos = {
            static_cast<float>(GetRandomValue(100, 700)),
            static_cast<float>(GetRandomValue(100, 500))
        };
        monsters.emplace_back(pos, 24.0f, 120.0f, i % 2 == 0);
    }
}

void Game::SpawnRocks(int count) {
    for (int i = 0; i < count; ++i) {
        Vector2 pos = {
            static_cast<float>(GetRandomValue(100, 700)),
            static_cast<float>(GetRandomValue(100, 200))
        };
        rocks.emplace_back(pos, 40.0f);
    }
}

void Game::SpawnBonusItems() {
    bonusItems.emplace_back(Vector2{400, 300}, BonusType::BONUS_APPLE, 100);
    bonusItems.emplace_back(Vector2{200, 200}, BonusType::BONUS_CHERRY, 150);
}

void Game::Run() {
    window->SetTargetFPS(60);
    
    while (!window->ShouldClose()) {
        float deltaTime = window->GetFrameTime();
        gameTime += deltaTime;
        
        switch (currentState) {
            case GameState::SPLASH:
                if (IsKeyPressed(KEY_ENTER)) {
                    currentState = GameState::PLAYING;
                }
                break;
                
            case GameState::PLAYING:
                UpdateGameplay();
                if (monsters.empty()) {
                    currentState = GameState::LEVEL_COMPLETE;
                }
                break;
                
            case GameState::GAME_OVER:
                if (IsKeyPressed(KEY_ENTER)) {
                    ResetGame();
                    currentState = GameState::PLAYING;
                }
                break;
                
            case GameState::LEVEL_COMPLETE:
                if (IsKeyPressed(KEY_ENTER)) {
                    NextLevel();
                    currentState = GameState::PLAYING;
                }
                break;
        }
        
        window->BeginDrawing();
        window->ClearBackground(BLACK);
        
        switch (currentState) {
            case GameState::SPLASH: DrawSplashScreen(); break;
            case GameState::PLAYING: DrawGameplay(); break;
            case GameState::GAME_OVER: DrawGameOverScreen(); break;
            case GameState::LEVEL_COMPLETE: DrawLevelCompleteScreen(); break;
        }
        
        window->EndDrawing();
    }
}

void Game::UpdateGameplay() {
    player.Update();
    
    // Update player tunnels
    player.UpdateTunnels(tunnelSystem);
    
    // Check for harpoon firing
    auto newHarpoon = player.FireHarpoon();
    if (newHarpoon) {
        harpoons.push_back(*newHarpoon);
    }
    
    // Update monsters
    for (auto& monster : monsters) {
        monster.Update(player.GetPosition(), tunnelSystem);
    }
    
    // Update harpoons
    for (auto it = harpoons.begin(); it != harpoons.end();) {
        it->Update();
        if (it->ShouldRemove()) {
            it = harpoons.erase(it);
        } else {
            ++it;
        }
    }
    
    // Update rocks
    for (auto& rock : rocks) {
        rock.Update(tunnelSystem);
    }
    
    CheckCollisions();
}

void Game::CheckCollisions() {
    // Player vs Monster
    for (auto& monster : monsters) {
        if (CheckCollisionCircles(player.GetPosition(), player.GetRadius(),
                                monster.GetPosition(), monster.GetRadius())) {
            lives--;
            if (lives <= 0) {
                currentState = GameState::GAME_OVER;
            } else {
                InitializeLevel();
            }
            return;
        }
    }
    
    // Harpoon vs Monster
    for (auto it = harpoons.begin(); it != harpoons.end();) {
        bool harpoonRemoved = false;
        
        for (auto mit = monsters.begin(); mit != monsters.end();) {
            if (CheckCollisionCircles(it->GetPosition(), 5.0f,
                                    mit->GetPosition(), mit->GetRadius())) {
                score += mit->IsDragon() ? 200 : 100;
                mit = monsters.erase(mit);
                it = harpoons.erase(it);
                harpoonRemoved = true;
                break;
            } else {
                ++mit;
            }
        }
        
        if (!harpoonRemoved) {
            ++it;
        }
    }
    
    // Player vs Bonus
    for (auto it = bonusItems.begin(); it != bonusItems.end();) {
        if (CheckCollisionCircles(player.GetPosition(), player.GetRadius(),
                                it->GetPosition(), it->GetRadius())) {
            score += it->GetValue();
            it = bonusItems.erase(it);
        } else {
            ++it;
        }
    }
    
    // Rock vs Monster/Player
    for (auto& rock : rocks) {
        if (rock.IsFalling()) {
            for (auto mit = monsters.begin(); mit != monsters.end();) {
                if (CheckCollisionCircles(rock.GetPosition(), rock.GetRadius(),
                                        mit->GetPosition(), mit->GetRadius())) {
                    score += 150;
                    mit = monsters.erase(mit);
                } else {
                    ++mit;
                }
            }
            
            if (CheckCollisionCircles(rock.GetPosition(), rock.GetRadius(),
                                    player.GetPosition(), player.GetRadius())) {
                lives--;
                if (lives <= 0) {
                    currentState = GameState::GAME_OVER;
                } else {
                    InitializeLevel();
                }
                return;
            }
        }
    }
}

void Game::DrawGameplay() {
    // Draw background
    tunnelSystem.Draw(dirtTexture, tunnelTexture);
    
    // Draw game objects
    for (auto& bonus : bonusItems) {
        bonus.Draw();
    }
    
    for (auto& rock : rocks) {
        rock.Draw();
    }
    
    for (auto& harpoon : harpoons) {
        harpoon.Draw();
    }
    
    for (auto& monster : monsters) {
        monster.Draw();
    }
    
    player.Draw();
    DrawUI();
}

void Game::DrawUI() {
    DrawText(TextFormat("Score: %d", score), 10, 10, 20, WHITE);
    DrawText(TextFormat("Lives: %d", lives), 10, 40, 20, WHITE);
    DrawText(TextFormat("Level: %d", currentLevel), 10, 70, 20, WHITE);
}

void Game::DrawSplashScreen() {
    DrawText("DIG DUG", 300, 100, 40, YELLOW);
    DrawText("Controls:", 50, 200, 30, WHITE);
    DrawText("Arrow Keys - Move", 50, 250, 20, WHITE);
    DrawText("SPACE - Fire Harpoon", 50, 280, 20, WHITE);
    DrawText("Press ENTER to start", 250, 400, 25, GREEN);
}

void Game::DrawGameOverScreen() {
    DrawText("GAME OVER", 300, 250, 40, RED);
    DrawText(TextFormat("Final Score: %d", score), 300, 320, 30, WHITE);
    DrawText("Press ENTER to restart", 250, 400, 25, GREEN);
}

void Game::DrawLevelCompleteScreen() {
    DrawText("LEVEL COMPLETE!", 280, 250, 40, GREEN);
    DrawText(TextFormat("Score: %d", score), 300, 320, 30, WHITE);
    DrawText("Press ENTER for next level", 250, 400, 25, GREEN);
}

void Game::ResetGame() {
    score = 0;
    lives = 3;
    currentLevel = 1;
    InitializeLevel();
}

void Game::NextLevel() {
    currentLevel++;
    InitializeLevel();
}