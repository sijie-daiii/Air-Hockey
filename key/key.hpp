#ifndef KEY_HPP
#define KEY_HPP

#include <cstdbool>

// Enum to represent different key actions
enum {NOCHAR, REGCHAR, UP, DOWN, LEFT, RIGHT, BADESC, W, A, S, D}; 

// Function to read keyboard input and return the corresponding action
int read_escape(int *);

#endif // KEY_HPP
