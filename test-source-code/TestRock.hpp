#pragma once
#include "doctest.h"
#include "../game-source-code/Rock.hpp"

// Simple mock TunnelSystem for testing
class MockTunnelSystem {
public:
    bool IsInTunnel(Vector2 point) const {
        // Simple mock - always return false (no tunnel) for testing
        // This prevents dependency issues during testing
        return false;
    }
    
    void Initialize(int width, int height, int gridSize) {
        // Mock initialization
    }
};

TEST_CASE("Rock Physics and Behavior") {
    // Mock screen dimensions safely
    InitWindow(800, 600, "Test");
    
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
        MockTunnelSystem mockTunnel;
        
        rock.StartFalling();
        CHECK(rock.IsFalling());
    }
    
    SUBCASE("Rock falls downward") {
        Rock rock({400, 100}, 40.0f);
        MockTunnelSystem mockTunnel;
        
        rock.StartFalling();
        float initialY = rock.GetPosition().y;
        
        // Small, safe update
        rock.Update(mockTunnel, 0.016f);
        
        CHECK(rock.GetPosition().y > initialY);
    }
    
    SUBCASE("Rock settles at bottom") {
        Rock rock({400, 550}, 40.0f); // Near bottom of 600px screen
        MockTunnelSystem mockTunnel;
        
        rock.StartFalling();
        
        // Few safe updates to reach bottom
        for (int i = 0; i < 3; i++) {
            rock.Update(mockTunnel, 0.1f);
            if (rock.IsSettled()) break;
        }
        
        CHECK(rock.IsSettled());
        CHECK(rock.GetPosition().y + rock.GetRadius() <= 600.0f);
    }
    
    SUBCASE("Rock with invalid radius handled") {
        Rock rock({400, 100}, -10.0f); // Invalid radius
        CHECK(rock.GetRadius() > 0); // Should be corrected to positive
    }
}