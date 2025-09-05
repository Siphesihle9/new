#pragma once
#include "doctest.h"
#include "../game-source-code/Harpoon.hpp"

TEST_CASE("Harpoon Movement and Behavior") {
    Harpoon harpoon({400, 300}, {1, 0}, 300.0f);
    
    SUBCASE("Harpoon initial position is correct") {
        CHECK(harpoon.GetPosition().x == 400.0f);
        CHECK(harpoon.GetPosition().y == 300.0f);
    }
    
    SUBCASE("Harpoon moves in correct direction") {
        Vector2 initialPos = harpoon.GetPosition();
        harpoon.Update();
        Vector2 newPos = harpoon.GetPosition();
        
        CHECK(newPos.x > initialPos.x); // Moving right
        CHECK(newPos.y == doctest::Approx(initialPos.y).epsilon(0.01f));
    }
    
    SUBCASE("Harpoon should not be removed initially") {
        CHECK_FALSE(harpoon.ShouldRemove());
    }
    
    SUBCASE("Harpoon gets removed when out of bounds") {
        Harpoon outOfBoundsHarpoon({-10, 300}, {1, 0}, 300.0f);
        outOfBoundsHarpoon.Update();
        CHECK(outOfBoundsHarpoon.ShouldRemove());
    }
    
    SUBCASE("Harpoon gets removed after max distance") {
        Harpoon longHarpoon({400, 300}, {1, 0}, 1000.0f);
        
        // Simulate many updates to exceed max distance
        for (int i = 0; i < 50; i++) {
            longHarpoon.Update();
            if (longHarpoon.ShouldRemove()) break;
        }
        
        CHECK(longHarpoon.ShouldRemove());
    }
}
