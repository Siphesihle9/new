#pragma once
#include "doctest.h"
#include "../game-source-code/Rock.hpp"
#include "../game-source-code/TunnelSystem.hpp"

TEST_CASE("Rock Physics and Behavior") {
    // Mock screen dimensions
    SetWindowSize(800, 600);
    
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
        
        // Update with fixed delta time for predictable results
        rock.Update(tunnelSystem, 0.1f); // 100ms time step
        
        // Should fall: 0.5 * 100 * (0.1)^2 ≈ 0.5 units + some velocity
        CHECK(rock.GetPosition().y > initialY);
        CHECK(rock.GetPosition().y == doctest::Approx(100.5f).epsilon(0.1f));
    }
    
    SUBCASE("Rock accelerates when falling") {
        rock.StartFalling();
        float firstY, secondY;
        
        // First update
        rock.Update(tunnelSystem, 0.1f);
        firstY = rock.GetPosition().y;
        
        // Second update - should fall further due to acceleration
        rock.Update(tunnelSystem, 0.1f);
        secondY = rock.GetPosition().y;
        
        CHECK(secondY - firstY > firstY - 100.0f); // Acceleration check
    }
    
    SUBCASE("Rock settles when it hits bottom") {
        Rock bottomRock({400, 550}, 40.0f); // Near bottom (550 + 40 = 590, screen height 600)
        bottomRock.StartFalling();
        
        // Simulate falling with fixed time steps
        for (int i = 0; i < 5; i++) {
            bottomRock.Update(tunnelSystem, 0.1f);
            if (bottomRock.IsSettled()) break;
        }
        
        CHECK(bottomRock.IsSettled());
        CHECK(bottomRock.GetPosition().y >= 560.0f); // Should be at or above bottom
    }
    
    SUBCASE("Rock doesn't fall when on tunnel") {
        // Create a rock positioned over a tunnel (assuming tunnel at y=500)
        Rock supportedRock({400, 450}, 40.0f);
        
        // Should not start falling automatically
        supportedRock.Update(tunnelSystem, 0.1f);
        CHECK_FALSE(supportedRock.IsFalling());
    }
}