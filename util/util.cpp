#include "util.hpp"
#include <random>

// Function to generate a random integer between min and max
int random_int(int min, int max) {
    // Initialize random number generator
    static std::mt19937 rng(std::random_device{}()); 
    // Define the distribution range
    std::uniform_int_distribution<int> dist(min, max); 
    // Generate and return a random number
    return dist(rng); 
}

// Function to reset the ball's position to a random location within the zone
void reset_ball_position(ball_t* b, int zone_width, int zone_height) {
    // Set random x-coordinate
    b->upper_left_x = random_int(1, zone_width - 1); 
    // Set random y-coordinate
    b->upper_left_y = random_int(1, zone_height - 1); 
}
