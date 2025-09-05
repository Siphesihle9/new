#pragma once
#include "doctest.h"
#include "../game-source-code/Rock.hpp"
#include "../game-source-code/TunnelSystem.hpp"

TEST_CASE("Rock Physics and Behavior") {
    Rock rock({400, 100}, 40.0f);
    TunnelSystem tunnelSystem;
    tunnelSystem.Initialize(800, 600, 32);
    
    SUBCASE("Rock initial position is correct") {
        CHECK(rock.GetPosition().x == 400.0f);
        CHECK(rock.GetPosition().y == 100.0f);
    }
    
    SUBCASE("Rock radius is correct") {
        CHECK(rock.GetRadius() == 40.0f);
    }
    
    SUBCASE("Rock initial state is not falling") {
        CHECK_FALSE(rock.IsFalling());
        CHECK_FALSE(rock.IsSettled());
    }
    
    SUBCASE("Rock starts falling when triggered") {
        rock.StartFalling();
        CHECK(rock.IsFalling());
    }
    
    SUBCASE("Rock falls with gravity") {
        rock.StartFalling();
        float initialY = rock.GetPosition().y;
        rock.Update(tunnelSystem);
        CHECK(rock.GetPosition().y > initialY);
    }
    
    SUBCASE("Rock settles when it hits bottom") {
        Rock bottomRock({400, 550}, 40.0f); // Near bottom
        bottomRock.StartFalling();
        
        // Simulate multiple updates to reach bottom
        for (int i = 0; i < 10; i++) {
            bottomRock.Update(tunnelSystem);
            if (bottomRock.IsSettled()) break;
        }
        
        CHECK(bottomRock.IsSettled());
    }
}
