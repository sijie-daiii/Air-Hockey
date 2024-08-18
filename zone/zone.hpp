#ifndef ZONE_HPP
#define ZONE_HPP

// Structure to represent the playing zone
typedef struct zone {
    // The x-coordinate of the upper left corner of the zone
    int upper_left_x;  

    // The y-coordinate of the upper left corner of the zone
    int upper_left_y;  

    // The width of the zone
    int width;         

    // The height of the zone
    int height;        

    // The character used to draw the zone boundaries
    char draw_char;    

    // Array to store the color attributes (not currently used)
    char color[3];     
} zone_t;

// Function to remove the zone boundary from the screen
void undraw_zone(zone_t *z);

// Function to draw the zone on the screen, including the goal areas
void draw_zone(zone_t *z, int goal_area_width);

// Function to initialize the zone with specified position and dimensions
zone_t *init_zone(int upper_left_x, int upper_left_y, int width, int height);

// Function to draw the goal area with specified start and end positions
void draw_goal_area(int y, int x_start, int x_end);

#endif
