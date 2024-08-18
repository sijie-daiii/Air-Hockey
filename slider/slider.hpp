#ifndef SLIDER_HPP
#define SLIDER_HPP

typedef struct slider {
    int upper_left_x;
    int upper_left_y;
    char draw_char;
    int draw_size;  // Size for drawing
    double collision_size;  // Size for collision detection
} slider_t;

// Function to initialize a slider at a given position
slider_t *init_slider (int initial_x, int initial_y, char type);

// Function to draw a slider on the screen
void draw_slider(slider_t *s);

// Function to undraw a slider from the screen
void undraw_slider(slider_t *s);

// Function to move a slider to a new position
void moveSlider(slider_t *s, int x, int y, int zone_width, int zone_height, bool is_top);

// Function to change the size of a slider
void change_slider_size(slider_t *s, int new_size);

#endif
