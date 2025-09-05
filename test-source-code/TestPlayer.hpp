#pragma once
#include "doctest.h"
#include "../game-source-code/Player.hpp"

TEST_CASE("Player Movement and Basic Functions") {
    Player player({400, 300}, 20.0f, 200.0f);
    
    SUBCASE("Player initial position is correct") {
        CHECK(player.GetPosition().x == 400.0f);
        CHECK(player.GetPosition().y == 300.0f);
    }
    
    SUBCASE("Player moves right correctly") {
        player.Move({1, 0});
        player.Update();
        CHECK(player.GetPosition().x > 400.0f);
    }
    
    SUBCASE("Player moves left correctly") {
        player.Move({-1, 0});
        player.Update();
        CHECK(player.GetPosition().x < 400.0f);
    }
    
    SUBCASE("Player stays within screen bounds") {
        player.Move({-1, 0});
        for (int i = 0; i < 100; i++) player.Update();
        CHECK(player.GetPosition().x >= 20.0f);
    }
    
    SUBCASE("Player radius is correct") {
        CHECK(player.GetRadius() == 20.0f);
    }
    
    SUBCASE("Player facing direction is normalized") {
        player.Move({2.0f, 3.0f});
        Vector2 dir = player.GetFacingDirection();
        float length = sqrtf(dir.x * dir.x + dir.y * dir.y);
        CHECK(length == doctest::Approx(1.0f).epsilon(0.01f));
    }
}