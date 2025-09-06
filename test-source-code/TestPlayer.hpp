#pragma once
#include "doctest.h"
#include "../game-source-code/Player.hpp"

TEST_CASE("Player Movement and Basic Functions") {
    // Initialize window for safety
    InitWindow(800, 600, "Test");
    
    Player player({400, 300}, 20.0f, 200.0f);
    
    SUBCASE("Player initial position is correct") {
        CHECK(player.GetPosition().x == 400.0f);
        CHECK(player.GetPosition().y == 300.0f);
        CHECK(player.GetRadius() == 20.0f);
    }
    
    SUBCASE("Player moves right correctly") {
        float initialX = player.GetPosition().x;
        player.Move({1, 0}, 0.016f); // Use explicit delta time
        player.Update(0.016f);
        CHECK(player.GetPosition().x > initialX);
    }
    
    SUBCASE("Player moves left correctly") {
        float initialX = player.GetPosition().x;
        player.Move({-1, 0}, 0.016f);
        player.Update(0.016f);
        CHECK(player.GetPosition().x < initialX);
    }
    
    SUBCASE("Player stays within screen bounds") {
        player.SetPosition({10, 300}); // Near left edge
        player.Move({-1, 0}, 0.1f);
        player.Update(0.1f);
        CHECK(player.GetPosition().x >= 20.0f); // Should not go past radius
    }
    
    SUBCASE("Player facing direction is normalized") {
        player.Move({2.0f, 3.0f}, 0.016f);
        Vector2 dir = player.GetFacingDirection();
        float length = sqrtf(dir.x * dir.x + dir.y * dir.y);
        CHECK(length == doctest::Approx(1.0f).epsilon(0.01f));
    }
    
    SUBCASE("Player velocity decreases with friction") {
        player.SetVelocity({100.0f, 0.0f});
        float initialSpeedX = player.GetVelocity().x;
        player.Update(0.016f);
        CHECK(player.GetVelocity().x < initialSpeedX);
    }
    
    SUBCASE("Player can fire harpoon") {
        auto harpoon = player.FireHarpoon();
        CHECK(harpoon.has_value());
    }
}

// Helper function to get velocity for testing
inline Vector2 Player::GetVelocity() const { return velocity; }