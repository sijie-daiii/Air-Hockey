#ifndef UTIL_HPP
#define UTIL_HPP

#include "../ball/ball.hpp"

// Function to generate a random integer between min and max
int random_int(int min, int max);

// Function to reset the ball's position to a random location within the zone
void reset_ball_position(ball_t* b, int zone_width, int zone_height);

#endif
