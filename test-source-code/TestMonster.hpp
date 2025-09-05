#pragma once
#include "doctest.h"
#include "../game-source-code/Monster.hpp"
#include "../game-source-code/TunnelSystem.hpp"

TEST_CASE("Monster Behavior and Functions") {
    Monster monster({200, 200}, 24.0f, 120.0f, false);
    TunnelSystem tunnelSystem;
    tunnelSystem.Initialize(800, 600, 32);
    
    SUBCASE("Monster initial position is correct") {
        CHECK(monster.GetPosition().x == 200.0f);
        CHECK(monster.GetPosition().y == 200.0f);
    }
    
    SUBCASE("Monster radius is correct") {
        CHECK(monster.GetRadius() == 24.0f);
    }
    
    SUBCASE("Monster type identification") {
        Monster redMonster({100, 100}, 24.0f, 120.0f, false);
        Monster dragon({300, 300}, 24.0f, 120.0f, true);
        
        CHECK_FALSE(redMonster.IsDragon());
        CHECK(dragon.IsDragon());
    }
    
    SUBCASE("Monster state management") {
        CHECK(monster.GetState() == MonsterState::NORMAL);
    }
    
    SUBCASE("Monster moves towards target") {
        Vector2 target{300, 300};
        monster.Update(target, tunnelSystem);
        Vector2 newPos = monster.GetPosition();
        
        // Should move towards target
        CHECK(newPos.x >= 200.0f);
        CHECK(newPos.y >= 200.0f);
    }
}
