#ifndef AIR_HOCKEY_HPP
#define AIR_HOCKEY_HPP

#include <vector>
#include "../ball/ball.hpp"
#include "../zone/zone.hpp"
#include "../slider/slider.hpp"
#include "../score/score.hpp"

// Declare obstruction_t with width and height
struct obstruction_t {
    int x;
    int y;
    int width;
    int height;
    char draw_char;
};

// Function to display the welcome screen
void display_welcome_screen();

// Function to select the difficulty level
int select_difficulty();

// Function to display the game over screen with the final scores
void display_game_over_screen(int top_score, int bottom_score, const std::vector<ScoreEntry>& scores);

// Function to initialize an obstruction at a given position
obstruction_t* init_obstruction(int x, int y, int width, int height);

// Function to draw an obstruction
void draw_obstruction(obstruction_t* o);

// Function to undraw an obstruction
void undraw_obstruction(obstruction_t* o);

// Function to check collision between an obstruction and the ball
bool checkCollisionObstruction(obstruction_t* o, ball_t* b);

// Function to save the game state
void save_game_state(int top_score, int bottom_score, ball_t *b, slider_t *top, slider_t *bottom);

// Main game function that contains the game loop
void air_hockey();

#endif
