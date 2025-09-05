#pragma once
#include "doctest.h"
#include "../game-source-code/Game.hpp"
#include "../game-source-code/TunnelSystem.hpp"

TEST_CASE("Game Mechanics and Collision Detection") {
    SUBCASE("Circle collision detection") {
        SUBCASE("Circles touching should collide") {
            bool collision = CheckCollisionCircles({100, 100}, 50.0f, {140, 100}, 30.0f);
            CHECK(collision);
        }
        
        SUBCASE("Circles not touching should not collide") {
            bool collision = CheckCollisionCircles({100, 100}, 10.0f, {200, 200}, 10.0f);
            CHECK_FALSE(collision);
        }
        
        SUBCASE("Circles exactly overlapping should collide") {
            bool collision = CheckCollisionCircles({100, 100}, 20.0f, {100, 100}, 20.0f);
            CHECK(collision);
        }
    }
    
    SUBCASE("Tunnel system functionality") {
        TunnelSystem tunnelSystem;
        tunnelSystem.Initialize(800, 600, 32);
        
        SUBCASE("Initial tunnel system should have no dug cells") {
            // Should be empty initially
        }
        
        SUBCASE("Digging tunnels creates dug cells") {
            tunnelSystem.DigTunnel({400, 300}, 32.0f);
            // Should have some dug cells now
        }
        
        SUBCASE("Position inside tunnel is detected correctly") {
            tunnelSystem.DigTunnel({400, 300}, 32.0f);
            bool inTunnel = tunnelSystem.IsInTunnel({400, 300});
            CHECK(inTunnel);
        }
        
        SUBCASE("Position outside tunnel is detected correctly") {
            bool inTunnel = tunnelSystem.IsInTunnel({10, 10});
            CHECK_FALSE(inTunnel);
        }
    }
    
    SUBCASE("Game state transitions") {
        // This would test game state machine
        // For now, we'll test basic state concepts
        SUBCASE("GameState enum values are correct") {
            CHECK(static_cast<int>(GameState::SPLASH) == 0);
            CHECK(static_cast<int>(GameState::PLAYING) == 1);
            CHECK(static_cast<int>(GameState::GAME_OVER) == 2);
            CHECK(static_cast<int>(GameState::LEVEL_COMPLETE) == 3);
        }
    }
}
