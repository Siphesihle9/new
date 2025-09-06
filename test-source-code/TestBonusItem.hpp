#pragma once
#include "doctest.h"
#include "../game-source-code/BonusItem.hpp"

TEST_CASE("Bonus Item Behavior and Functions") {
    float testTime = 0.0f;
    BonusItem apple({400, 300}, BonusType::BONUS_APPLE, 100, testTime);
    
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
        CHECK_FALSE(apple.ShouldRemove(testTime));
    }
    
    SUBCASE("Different bonus types have different values") {
        BonusItem cherry({200, 200}, BonusType::BONUS_CHERRY, 150, testTime);
        BonusItem strawberry({300, 300}, BonusType::BONUS_STRAWBERRY, 200, testTime);
        BonusItem orange({400, 400}, BonusType::BONUS_ORANGE, 250, testTime);
        
        CHECK(cherry.GetValue() == 150);
        CHECK(strawberry.GetValue() == 200);
        CHECK(orange.GetValue() == 250);
    }
    
    SUBCASE("Bonus item removal after lifetime") {
        BonusItem testItem({100, 100}, BonusType::BONUS_APPLE, 50, 0.0f);
        
        // Should not be removed before lifetime expires
        CHECK_FALSE(testItem.ShouldRemove(5.0f));
        
        // Should be removed after lifetime expires
        CHECK(testItem.ShouldRemove(15.0f));
    }
}