#include "raylib-cpp.hpp"
#include "Game.hpp"

int main() {
    // Show splash screen with controls
    raylib::Window splash(800, 600, "Dig Dug - Controls");
    splash.SetTargetFPS(60);
    
    while (!splash.ShouldClose() && !IsKeyPressed(KEY_ENTER)) {
        splash.BeginDrawing();
        splash.ClearBackground(BLACK);
        
        DrawText("DIG DUG", 300, 100, 40, YELLOW);
        DrawText("Controls:", 50, 200, 30, WHITE);
        DrawText("Arrow Keys - Move", 50, 250, 20, WHITE);
        DrawText("SPACE - Fire Harpoon", 50, 280, 20, WHITE);
        DrawText("Press ENTER to start", 250, 400, 25, GREEN);
        
        splash.EndDrawing();
    }
    
    // Main game
    Game game;
    game.Run();
    
    return 0;
}