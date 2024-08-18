#ifndef BALL_HPP
#define BALL_HPP

#include "../zone/zone.hpp"
#include "../slider/slider.hpp"
#include <vector>

// Forward declaration of obstruction_t
struct obstruction_t;

typedef struct ball {
    int upper_left_x;
    int upper_left_y;
    int speed_x;
    int speed_y;
    char draw_char;
    char color[3];
} ball_t;

// Function to initialize the ball with its position and speed
ball_t *init_ball(int upper_left_x, int upper_left_y, int speed_x, int speed_y);

// Function to draw the ball on the screen
void draw_ball(ball_t *b);

// Function to undraw the ball from the screen
void undraw_ball(ball_t *b);

// Function to check collision between the ball and the zone boundaries or goals
bool checkCollisionWithZone(ball_t *b, zone_t *z, int& top_score, int& bottom_score, int goal_area_width);

// Function to check collision between the ball and a slider
bool checkCollisionSlider(slider_t *s, ball_t *b);

// Function to move the ball and handle collisions
void moveBall(ball_t *b, zone_t *z, slider_t *bottom, slider_t *top, std::vector<obstruction_t*>& obstructions, int& top_score, int& bottom_score, int goal_area_width);

// Function to reset the ball to a random position
void reset_ball_position(ball_t *b, int zone_width, int zone_height);

#endif
