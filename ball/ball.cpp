#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstdbool>
#include <ncurses.h>
#include "../key/key.hpp"
#include "ball.hpp"
#include "../air_hockey/air_hockey.hpp"

// Move the ball based on its speed
void moveBall(ball_t *b, zone_t *z, slider_t *bottom, slider_t *top, std::vector<obstruction_t*>& obstructions, int& top_score, int& bottom_score, int goal_area_width) {
    int steps = std::max(abs(b->speed_x), abs(b->speed_y));
    int step_x = b->speed_x / steps;
    int step_y = b->speed_y / steps;

    for (int i = 0; i < steps; ++i) {
        // Clear the previous position of the ball
        undraw_ball(b);

        // Update the ball's position
        b->upper_left_x += step_x;
        b->upper_left_y += step_y;

        // Check for collisions with zone boundaries and goals
        if (checkCollisionWithZone(b, z, top_score, bottom_score, goal_area_width)) {
            break;
        }

        // Check for collisions with sliders
        if (checkCollisionSlider(bottom, b)) {
            b->speed_y = -abs(b->speed_y);
            b->upper_left_y = bottom->upper_left_y - 1;
        } else if (checkCollisionSlider(top, b)) {
            b->speed_y = abs(b->speed_y);
            b->upper_left_y = top->upper_left_y + 1;
        }

        // Check for collisions with obstructions
        for (std::vector<obstruction_t*>::iterator it = obstructions.begin(); it != obstructions.end(); ++it) {
            if (checkCollisionObstruction(*it, b)) {
                // Reset ball position and increase speed
                b->speed_x = (b->speed_x > 0 ? b->speed_x + 1 : b->speed_x - 1);
                b->speed_y = (b->speed_y > 0 ? b->speed_y + 1 : b->speed_y - 1);
                reset_ball_position(b, z->width, z->height);
                // Reset scores if ball hits obstruction
                top_score = 0;
                bottom_score = 0;
                break;
            }
        }

        // Draw the ball at the new position
        draw_ball(b);
        refresh();
    }
}

// Check if the ball collides with the slider.
// Change Y direction of the ball if it collides
bool checkCollisionSlider(slider_t *s, ball_t *b) {
    int x_ball = b->upper_left_x;
    int y_ball = b->upper_left_y;

    // Check if the ball's y-coordinate is within the slider's y-coordinate range
    if ((y_ball == s->upper_left_y - 1 && b->speed_y > 0) || (y_ball == s->upper_left_y + 1 && b->speed_y < 0)) {
        // Check if the ball's x-coordinate is within the slider's range
        if (x_ball >= s->upper_left_x && x_ball <= (s->upper_left_x + static_cast<int>(s->collision_size))) {
            b->speed_y *= -1;
            return true;
        }
    }
    return false;
}

// Check if the ball collides with the walls or goals of the zone.
// Change direction of the ball if it collides with walls, update scores if it collides with goals
bool checkCollisionWithZone(ball_t *b, zone_t *z, int& top_score, int& bottom_score, int goal_area_width) {
    // Calculate goal start and end positions
    int goal_start = (z->width - goal_area_width) / 2;
    int goal_end = goal_start + goal_area_width;

    // Check for side wall collisions
    if (b->upper_left_x <= z->upper_left_x) {
        b->upper_left_x = z->upper_left_x + 1; 
        b->speed_x *= -1; 
        return true;
    } else if (b->upper_left_x >= z->upper_left_x + z->width) {
        b->upper_left_x = z->upper_left_x + z->width - 1; 
        b->speed_x *= -1;
        return true;
    }

    // Check for top goal collision
    if (b->upper_left_y <= z->upper_left_y) {
        if (b->upper_left_x >= z->upper_left_x + goal_start && b->upper_left_x <= z->upper_left_x + goal_end) {
            bottom_score++;
            reset_ball_position(b, z->width, z->height);
            b->speed_y = abs(b->speed_y);
            return true;
        } else {
            b->upper_left_y = z->upper_left_y + 1; 
            b->speed_y *= -1; 
            return true;
        }
    }

    // Check for bottom goal collision
    if (b->upper_left_y >= z->upper_left_y + z->height) {
        if (b->upper_left_x >= z->upper_left_x + goal_start && b->upper_left_x <= z->upper_left_x + goal_end) {
            top_score++;
            reset_ball_position(b, z->width, z->height);
            b->speed_y = -abs(b->speed_y); 
            return true;
        } else {
            b->upper_left_y = z->upper_left_y + z->height - 1; 
            b->speed_y *= -1; 
            return true;
        }
    }

    return false;
}

// Inititialize ball with its position and speed in the X & Y directions
ball_t *init_ball(int upper_left_x, int upper_left_y, int speed_x, int speed_y) {
    ball_t *b;
    b = (ball_t *) malloc(sizeof(ball_t));
    b->draw_char = 'O';
    b->upper_left_x = upper_left_x;
    b->upper_left_y = upper_left_y;
    b->color[0] = 0;
    b->color[1] = 0;
    b->color[2] = 0;
    b->speed_x = speed_x;
    b->speed_y = speed_y;
    return (b);
}

// Renders the ball on the screen
void draw_ball(ball_t *b) {
    mvprintw(b->upper_left_y, b->upper_left_x, "%c", b->draw_char);
}

// Replaces the ball with blank space
void undraw_ball(ball_t *b) {
    mvprintw(b->upper_left_y, b->upper_left_x, " ");
}
