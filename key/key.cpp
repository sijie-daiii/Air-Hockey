#include <ncurses.h>
#include "key.hpp"

// Function to read keyboard input and return the corresponding action
int read_escape(int *read_char) {
    int c;
    if ((c = getch()) == ERR) {
        return NOCHAR;
    } else if (c == 0x1b) {
        if ((c = getch()) == '[') {
            c = getch();
            switch (c) {
                case 'A': return UP;
                case 'B': return DOWN;
                case 'C': return RIGHT;
                case 'D': return LEFT;
                default: return BADESC;
            }
        }
    } else {
        *read_char = c;
        switch (c) {
            case 'a': case 'A': return A;
            case 'w': case 'W': return W;
            case 's': case 'S': return S;
            case 'd': case 'D': return D;
            default: return REGCHAR;
        }
    }
    return REGCHAR;
}
