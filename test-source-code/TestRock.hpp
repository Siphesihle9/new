#pragma once
#include "doctest.h"
#include "../game-source-code/Rock.hpp"
#include "../game-source-code/TunnelSystem.hpp"

TEST_CASE("Rock Physics and Behavior") {
    // Initialize window for screen dimension functions
    InitWindow(800, 600, "Test");
    
    // Create a real TunnelSystem but keep it simple
    TunnelSystem tunnelSystem;
    tunnelSystem.Initialize(800, 600, 32);
    
    SUBCASE("Rock basic initialization") {
        Rock rock({400, 100}, 40.0f);
        
        CHECK(rock.GetPosition().x == 400.0f);
        CHECK(rock.GetPosition().y == 100.0f);
        CHECK(rock.GetRadius() == 40.0f);
        CHECK_FALSE(rock.IsFalling());
        CHECK_FALSE(rock.IsSettled());
    }
    
    SUBCASE("Rock starts falling when triggered") {
        Rock rock({400, 100}, 40.0f);
        
        rock.StartFalling();
        CHECK(rock.IsFalling());
    }
    
    SUBCASE("Rock falls downward") {
        Rock rock({400, 100}, 40.0f);
        
        rock.StartFalling();
        float initialY = rock.GetPosition().y;
        
        // Small, safe update with explicit delta time
        rock.Update(tunnelSystem, 0.016f);
        
        CHECK(rock.GetPosition().y > initialY);
    }
    
    SUBCASE("Rock settles at bottom") {
        Rock rock({400, 550}, 40.0f); // Near bottom of 600px screen
        rock.StartFalling();
        
        // Few safe updates to reach bottom
        for (int i = 0; i < 5; i++) {
            rock.Update(tunnelSystem, 0.1f);
            if (rock.IsSettled()) break;
        }
        
        CHECK(rock.IsSettled());
        CHECK(rock.GetPosition().y + rock.GetRadius() <= 600.0f);
    }
    
    SUBCASE("Rock with zero radius handled") {
        Rock rock({400, 100}, 0.0f);
        CHECK(rock.GetRadius() > 0); // Should have minimum radius
    }
}