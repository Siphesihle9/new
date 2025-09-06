#pragma once
#include "doctest.h"
#include "../game-source-code/Player.hpp"

TEST_CASE("Player Movement and Basic Functions") {
    InitWindow(800, 600, "Test");
   
    Player player({400, 300}, 20.0f, 200.0f);
   
    SUBCASE("Player initial position is correct") {
        CHECK(player.GetPosition().x == 400.0f);
        CHECK(player.GetPosition().y == 300.0f);
        CHECK(player.GetRadius() == 20.0f);
    }
   
    SUBCASE("Player moves with input") {
        float initialX = player.GetPosition().x;
        player.Move({1, 0}, 0.016f);
        player.Update(0.016f);
        CHECK(player.GetPosition().x > initialX);
    }
   
    SUBCASE("Player respects boundaries") {
        player.SetPosition({25, 300});
        player.Move({-1, 0}, 0.1f);
        player.Update(0.1f);
        CHECK(player.GetPosition().x >= 20.0f);
    }
   
    SUBCASE("Direction normalization works") {
        player.Move({5.0f, 0.0f}, 0.016f);
        Vector2 dir = player.GetFacingDirection();
        CHECK(dir.x == doctest::Approx(1.0f).epsilon(0.01f));
        CHECK(dir.y == doctest::Approx(0.0f).epsilon(0.01f));
    }
   
    SUBCASE("Harpoon firing works") {
        CHECK(player.FireHarpoon().has_value());
    }
}