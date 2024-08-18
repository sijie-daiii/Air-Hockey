#include "slider.hpp"
#include <ncurses.h>
#include <cstring>
#include <cstdlib>  

// Moves the slider to a new position, while ensuring it doesn't cross boundaries or the center line.
void moveSlider(slider_t *s, int x, int y, int zone_width, int zone_height, bool is_top) {
    // Boundary checks
    if (x < 1 || x + s->draw_size > zone_width + 2) return; 
    if (is_top && (y < 1 || y > zone_height / 2 - 1)) return;  
    if (!is_top && (y < zone_height / 2 || y > zone_height - 2)) return;

    // Remove the slider from its current position
    undraw_slider(s);
    // Update the slider's position
    s->upper_left_x = x;
    s->upper_left_y = y;
    // Draw the slider at the new position
    draw_slider(s);
}

// Changes the size of the slider
void change_slider_size(slider_t *s, int new_size) {
    s->draw_size = new_size; 
    s->collision_size = new_size - 0.5; 
}

// Initializes a new slider with the specified initial position and type ('T' for top, 'U' for bottom)
slider_t *init_slider (int initial_x, int initial_y, char type) {
    slider_t *s = (slider_t*) malloc(sizeof(slider_t));
    s->upper_left_x = initial_x;
    s->upper_left_y = initial_y;
    s->draw_char = (type == 'T') ? '%' : '+';
    s->draw_size = 4; 
    s->collision_size = 3.5;  
    return s;
}

// Draws the slider on the screen
void draw_slider(slider_t *s) {
    int color_pair = (s->draw_char == '%') ? 1 : 5; // Use color pair 1 for top slider, 5 for bottom slider
    attron(COLOR_PAIR(color_pair));  
    for (int x = 0; x < s->draw_size; ++x) {
        mvprintw(s->upper_left_y, s->upper_left_x + x, "%c", s->draw_char);
    }
    attroff(COLOR_PAIR(color_pair));  
}

// Erases the slider from the screen
void undraw_slider(slider_t *s) {
    for (int x = 0; x < s->draw_size; ++x) {
        mvprintw(s->upper_left_y, s->upper_left_x + x, " "); 
    }
}
