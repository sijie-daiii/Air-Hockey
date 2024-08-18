#include "zone.hpp"
#include <ncurses.h>
#include <cstdio>
#include <ctime>
#include <cstdlib>

// Initializes zone position and dimensions
zone_t *init_zone(int upper_left_x, int upper_left_y, int width, int height) {
    zone_t *z;
    z = (zone_t *) malloc(sizeof(zone_t));
    z->upper_left_x = upper_left_x;
    z->upper_left_y = upper_left_y;
    z->width = width;
    z->height = height;
    z->draw_char = '#';
    z->color[0] = 0;
    z->color[1] = 0;
    z->color[2] = 0;
    return (z);
}

// Renders zone on the screen
void draw_zone(zone_t *z, int goal_area_width) {
    int row_counter, column_counter;

    attron(COLOR_PAIR(3)); // Use color pair 3 for the zone border

    // Draw the top side of the zone
    for (row_counter = z->upper_left_x; row_counter <= (z->upper_left_x + z->width); row_counter++) {
        mvprintw(z->upper_left_y, row_counter, "%c", z->draw_char);
    }

    // Draw left side of zone
    for (column_counter = z->upper_left_y; column_counter <= (z->upper_left_y + z->height); column_counter++) {
        mvprintw(column_counter, z->upper_left_x, "%c", z->draw_char);
    }

    // Draw right side of zone
    for (column_counter = z->upper_left_y; column_counter <= (z->upper_left_y + z->height); column_counter++) {
        mvprintw(column_counter, (z->upper_left_x + z->width), "%c", z->draw_char);
    }

    // Draw Bottom of zone 
    for (row_counter = z->upper_left_x; row_counter <= (z->upper_left_x + z->width); row_counter++) {
        mvprintw(z->upper_left_y + z->height, row_counter, "%c", z->draw_char);
    }

    attroff(COLOR_PAIR(3)); // Turn off color pair 3

    // Draw goal areas using the specified width
    int goal_start = (z->width - goal_area_width) / 2;
    int goal_end = goal_start + goal_area_width;

    draw_goal_area(z->upper_left_y, z->upper_left_x + goal_start, z->upper_left_x + goal_end);  // Top goal area
    draw_goal_area(z->upper_left_y + z->height, z->upper_left_x + goal_start, z->upper_left_x + goal_end);  // Bottom goal area
}

// Replaces the zone boundary with blank spaces
void undraw_zone(zone_t *z) {
    int row_counter, column_counter;

    // Draw the top side of the zone
    for (row_counter = z->upper_left_x; row_counter <= (z->upper_left_x + z->width); row_counter++) {
        mvprintw(z->upper_left_y, row_counter, " ");
    }

    // Draw left side of zone
    for (column_counter = z->upper_left_y; column_counter <= (z->upper_left_y + z->height); column_counter++) {
        mvprintw(column_counter, z->upper_left_x, " ");
    }

    // Draw right side of zone
    for (column_counter = z->upper_left_y; column_counter <= (z->upper_left_y + z->height); column_counter++) {
        mvprintw(column_counter, (z->upper_left_x + z->width), " ");
    }

    // Draw Bottom of zone 
    for (row_counter = z->upper_left_x; row_counter <= (z->upper_left_x + z->width); row_counter++) {
        mvprintw(z->upper_left_y + z->height, row_counter, " ");
    }
}

// Draw goal areas
void draw_goal_area(int y, int x_start, int x_end) {
    attron(COLOR_PAIR(2)); // Use color pair 2 for goal areas
    for (int x = x_start; x <= x_end; ++x) {
        mvprintw(y, x, "=");
    }
    attroff(COLOR_PAIR(2)); // Turn off color pair 2
}
