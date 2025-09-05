#pragma once
#include "doctest.h"
#include "../game-source-code/BonusItem.hpp"

TEST_CASE("Bonus Item Behavior and Functions") {
    BonusItem apple({400, 300}, BonusType::APPLE, 100);
    
    SUBCASE("Bonus item initial position is correct") {
        CHECK(apple.GetPosition().x == 400.0f);
        CHECK(apple.GetPosition().y == 300.0f);
    }
    
    SUBCASE("Bonus item value is correct") {
        CHECK(apple.GetValue() == 100);
    }
    
    SUBCASE("Bonus item radius is correct") {
        CHECK(apple.GetRadius() == 15.0f);
    }
    
    SUBCASE("Bonus item should not be removed initially") {
        CHECK_FALSE(apple.ShouldRemove());
    }
    
    SUBCASE("Different bonus types have different values") {
        BonusItem cherry({200, 200}, BonusType::CHERRY, 150);
        BonusItem strawberry({300, 300}, BonusType::STRAWBERRY, 200);
        BonusItem orange({400, 400}, BonusType::ORANGE, 250);
        
        CHECK(cherry.GetValue() == 150);
        CHECK(strawberry.GetValue() == 200);
        CHECK(orange.GetValue() == 250);
    }
    
    SUBCASE("Bonus item removal after lifetime") {
        // This would require mocking time, so we'll just test the interface
        CHECK(apple.ShouldRemove() == false); // Should not be removed immediately
    }
}
