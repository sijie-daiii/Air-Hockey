#include "../key/key.hpp"
#include "../ball/ball.hpp"
#include "air_hockey.hpp"
#include "../score/score.hpp"
#include "../zone/zone.hpp"
#include "../slider/slider.hpp"
#include "../util/util.hpp"
#include <ncurses.h>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <fstream>
#include <string>


// Function to display the welcome screen
void display_welcome_screen() {
    clear();
    attron(COLOR_PAIR(1)); // Use color pair 1 for text
    mvprintw(5, 10, "Welcome to Air Hockey!");
    mvprintw(7, 10, "Instructions:");
    mvprintw(8, 12, "Use arrow keys to move the bottom slider.");
    mvprintw(9, 12, "Use 'W' and 'S' keys to move the top slider.");
    mvprintw(10, 12, "Press 'P' to pause the game.");
    mvprintw(11, 12, "Press 'Q' to quit the game.");
    mvprintw(12, 12, "The game ends after 120 seconds if no player reaches 10 points.");
    mvprintw(13, 12, "Any other key button without indication will set to be");
    mvprintw(14, 12, "default value during the game.");
    mvprintw(15, 12, "The hard level has obstructions. When the ball touches");
    mvprintw(16, 12, "an obstruction, the ball speed will increase and the ball");
    mvprintw(17, 12, "will appear in a random position.");
    mvprintw(19, 10, "Press any key to start...");
    attroff(COLOR_PAIR(1)); // Turn off color pair 1
    refresh();
    getch();
}

// Function to display the difficulty selection screen
int select_difficulty() {
    clear();
    attron(COLOR_PAIR(1)); // Use color pair 1 for text
    mvprintw(5, 10, "Select Difficulty Level:");
    mvprintw(7, 12, "1. Easy");
    mvprintw(8, 12, "2. Medium");
    mvprintw(9, 12, "3. Hard");
    mvprintw(11, 10, "Press 1, 2, or 3 to select difficulty level...");
    attroff(COLOR_PAIR(1)); // Turn off color pair 1
    refresh();

    int difficulty;
    while (true) {
        difficulty = getch();
        if (difficulty == '1' || difficulty == '2' || difficulty == '3') {
            break; 
        }
    }
    return difficulty;
}

// Function to prompt for slider size
int prompt_slider_size(int zone_width) {
    clear();
    attron(COLOR_PAIR(1)); // Use color pair 1 for text
    mvprintw(5, 10, "Set Slider Size (pay attention to your screen width):");
    attroff(COLOR_PAIR(1)); // Turn off color pair 1
    refresh();

    std::string input;
    int size = 0;

    while (true) {
        int ch = getch();
        if (ch == '\n' || ch == '\r') {
            if (!input.empty()) {
                size = std::stoi(input);
                if (size >= 1) {
                    break;
                }
            }
        } else if (isdigit(ch)) {
            input += ch;
            mvprintw(6, 10, "Current input: %s", input.c_str());
            refresh();
        } else if (ch == KEY_BACKSPACE || ch == 127) {
            if (!input.empty()) {
                input.pop_back();
                mvprintw(6, 10, "Current input: %s  ", input.c_str());
                refresh();
            }
        }
    }

    return size > zone_width ? zone_width : size;  // Ensure size does not exceed screen width
}

// Function to prompt for goal area width
int prompt_goal_area_width(int zone_width) {
    clear();
    attron(COLOR_PAIR(1)); // Use color pair 1 for text
    mvprintw(5, 10, "Set Goal Area Width (pay attention to your screen width):");
    attroff(COLOR_PAIR(1)); // Turn off color pair 1
    refresh();

    std::string input;
    int width = 0;

    while (true) {
        int ch = getch();
        if (ch == '\n' || ch == '\r') {
            if (!input.empty()) {
                width = std::stoi(input);
                if (width >= 1) {
                    break;
                }
            }
        } else if (isdigit(ch)) {
            input += ch;
            mvprintw(6, 10, "Current input: %s", input.c_str());
            refresh();
        } else if (ch == KEY_BACKSPACE || ch == 127) {
            if (!input.empty()) {
                input.pop_back();
                mvprintw(6, 10, "Current input: %s  ", input.c_str());
                refresh();
            }
        }
    }

    return width > zone_width ? zone_width : width;  // Ensure width does not exceed screen width
}

// Function to prompt for the number of sets
int prompt_number_of_sets() {
    clear();
    attron(COLOR_PAIR(1)); // Use color pair 1 for text
    mvprintw(5, 10, "Enter the number of sets to play:");
    attroff(COLOR_PAIR(1)); // Turn off color pair 1
    refresh();

    int sets;
    while (true) {
        sets = getch() - '0';
        if (sets > 0) {
            break; 
        }
    }
    return sets;
}

// Function to display the game over screen after each set
void display_set_over_screen(int top_sets_won, int bottom_sets_won, const std::vector<std::string>& winners) {
    clear();
    attron(COLOR_PAIR(1)); // Use color pair 1 for text
    mvprintw(5, 10, "Set Over!");
    mvprintw(7, 10, "Final Scores:");
    mvprintw(8, 12, "Top Sets Won: %d", top_sets_won);
    mvprintw(9, 12, "Bottom Sets Won: %d", bottom_sets_won);
    mvprintw(11, 10, "Winner Recording:");
    for (size_t i = 0; i < winners.size(); ++i) {
        mvprintw(12 + i, 12, "%d. Winner: %s 10", i + 1, winners[i].c_str());
    }
    if (top_sets_won > bottom_sets_won) {
        mvprintw(20, 10, "Winner: Top Player!");
    } else if (bottom_sets_won > top_sets_won) {
        mvprintw(20, 10, "Winner: Bottom Player!");
    } else {
        mvprintw(20, 10, "It's a Tie!");
    }
    mvprintw(22, 10, "Next set will start in 5 seconds...");
    attroff(COLOR_PAIR(1)); // Turn off color pair 1
    refresh();
    napms(5000);
}

// Function to display the final checkout screen
void display_final_checkout_screen(int top_sets_won, int bottom_sets_won) {
    clear();
    attron(COLOR_PAIR(1)); // Use color pair 1 for text
    mvprintw(5, 10, "Game Over!");
    mvprintw(7, 10, "Final Sets Won:");
    mvprintw(8, 12, "Top Sets Won: %d", top_sets_won);
    mvprintw(9, 12, "Bottom Sets Won: %d", bottom_sets_won);
    if (top_sets_won > bottom_sets_won) {
        mvprintw(20, 10, "Overall Winner: Top Player!");
    } else if (bottom_sets_won > top_sets_won) {
        mvprintw(20, 10, "Overall Winner: Bottom Player!");
    } else {
        mvprintw(20, 10, "Overall Result: It's a Tie!");
    }
    mvprintw(22, 10, "Game will exit in 10 seconds...");
    attroff(COLOR_PAIR(1)); // Turn off color pair 1
    refresh();
    napms(10000);
}

// Function to load the best 10 winner history
std::vector<std::string> load_best_10_winner_history() {
    std::vector<std::string> winner_history;
    std::ifstream infile("./saves/save_best_10.txt");
    std::string line;
    while (std::getline(infile, line)) {
        winner_history.push_back(line);
    }
    infile.close();
    return winner_history;
}

// Function to display the best 10 winner history
void display_best_10_winner_history() {
    std::vector<std::string> winner_history = load_best_10_winner_history();
    clear();
    attron(COLOR_PAIR(1)); // Use color pair 1 for text
    mvprintw(5, 10, "Top 10 Game Recording:");
    for (size_t i = 0; i < winner_history.size(); ++i) {
        mvprintw(7 + i, 12, "%s", winner_history[i].c_str());
    }
    mvprintw(22, 10, "Game will exit in 10 seconds...");
    attroff(COLOR_PAIR(1)); // Turn off color pair 1
    refresh();
    napms(10000);
}

// Initialize obstruction
obstruction_t* init_obstruction(int x, int y, int width, int height) {
    obstruction_t* o = (obstruction_t*) malloc(sizeof(obstruction_t));
    o->x = x;
    o->y = y;
    o->width = width;
    o->height = height;
    o->draw_char = '&';
    return o;
}

// Draw obstruction
void draw_obstruction(obstruction_t* o) {
    attron(COLOR_PAIR(3)); // Use color pair 3 for obstructions
    for (int i = 0; i < o->height; ++i) {
        for (int j = 0; j < o->width; ++j) {
            mvprintw(o->y + i, o->x + j, "%c", o->draw_char);
        }
    }
    attroff(COLOR_PAIR(3)); // Turn off color pair 3
}

// Undraw obstruction
void undraw_obstruction(obstruction_t* o) {
    for (int i = 0; i < o->height; ++i) {
        for (int j = 0; j < o->width; ++j) {
            mvprintw(o->y + i, o->x + j, " ");
        }
    }
}

// Check collision with obstruction
bool checkCollisionObstruction(obstruction_t* o, ball_t* b) {
    for (int i = 0; i < o->height; ++i) {
        for (int j = 0; j < o->width; ++j) {
            if (b->upper_left_x == o->x + j && b->upper_left_y == o->y + i) {
                return true;
            }
        }
    }
    return false;
}

// Function to save the game state
void save_game_state(int top_score, int bottom_score, ball_t *b, slider_t *top, slider_t *bottom) {
    std::ofstream save_file("./saves/game_state.txt");
    if (save_file.is_open()) {
        save_file << top_score << " " << bottom_score << std::endl;
        save_file << b->upper_left_x << " " << b->upper_left_y << " " << b->speed_x << " " << b->speed_y << std::endl;
        save_file << top->upper_left_x << " " << top->upper_left_y << std::endl;
        save_file << bottom->upper_left_x << " " << bottom->upper_left_y << std::endl;
        save_file.close();
        attron(COLOR_PAIR(4)); // Use color pair 4 for save confirmation
        mvprintw(0, 0, "Game state saved!");
        attroff(COLOR_PAIR(4)); // Turn off color pair 4
    } else {
        attron(COLOR_PAIR(4)); // Use color pair 4 for save failure
        mvprintw(0, 0, "Failed to save game state!");
        attroff(COLOR_PAIR(4)); // Turn off color pair 4
    }
}

// Function to clear the win.txt file
void clear_win_file() {
    std::ofstream win_file("./saves/win.txt", std::ofstream::trunc);
    if (win_file.is_open()) {
        win_file.close();
    }
}

// Function to update the win.txt file with the winner of each set
void update_win_file(const std::string& winner) {
    std::ofstream win_file("./saves/win.txt", std::ofstream::app);
    if (win_file.is_open()) {
        win_file << "Winner: " << winner << " 10\n";
        win_file.close();
    }
}

// Function to save the final set wins to save_best_10.txt
void save_final_set_wins(int top_sets_won, int bottom_sets_won) {
    std::vector<std::string> winner_history = load_best_10_winner_history();
    std::ofstream save_file("./saves/save_best_10.txt", std::ofstream::trunc);
    if (save_file.is_open()) {
        for (const auto& line : winner_history) {
            save_file << line << "\n";
        }
        if (top_sets_won > 0) {
            save_file << "Top Set Won: " << top_sets_won << "\n";
        }
        if (bottom_sets_won > 0) {
            save_file << "Bottom Set Won: " << bottom_sets_won << "\n";
        }
        save_file.close();
    }
}

// Main Game function
void air_hockey() {
    initscr();              
    noecho();               
    cbreak();                
    keypad(stdscr, TRUE);   

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);   
        init_pair(2, COLOR_GREEN, COLOR_BLACK); 
        init_pair(3, COLOR_YELLOW, COLOR_BLACK); 
        init_pair(4, COLOR_MAGENTA, COLOR_BLACK); 
        init_pair(5, COLOR_BLUE, COLOR_BLACK);
    }

    display_welcome_screen(); 

    int difficulty = select_difficulty();
    int zone_height, zone_width;
    getmaxyx(stdscr, zone_height, zone_width); 
    zone_height -= 1;
    zone_width -= 1;

    int slider_size = prompt_slider_size(zone_width);
    int goal_area_width = prompt_goal_area_width(zone_width); 
    int num_sets = prompt_number_of_sets(); 

    int ball_speed_x = 1, ball_speed_y = 1;
    int num_obstructions = 0; 

    switch (difficulty) {
        case '1': // Easy
            ball_speed_x = 1;
            ball_speed_y = 1;
            num_obstructions = 0;
            break;
        case '2': // Medium
            ball_speed_x = 2; 
            ball_speed_y = 2; 
            num_obstructions = 0;
            break;
        case '3': // Hard
            ball_speed_x = 3; 
            ball_speed_y = 3;
            num_obstructions = 2;
            break;
        default:
            ball_speed_x = 1;
            ball_speed_y = 1;
            num_obstructions = 0;
    }

    clear();                 
    refresh();

    struct timespec tim = {0, 200000000};
    struct timespec tim_ret;
    int arrow, c;
    int slider_x_speed = 5;
    int slider_y_speed = 2; 
    zone_t *z = init_zone(0, 0, zone_width, zone_height);

    // Initialize ball with random position within the zone
    int random_x = random_int(zone_width / 4, 3 * zone_width / 4);
    int random_y = random_int(zone_height / 4, 3 * zone_height / 4);
    ball_t *b = init_ball(random_x, random_y, ball_speed_x, ball_speed_y);

    slider_t *top = init_slider(zone_width / 2, 5, 'T');
    slider_t *bottom = init_slider(zone_width / 2, zone_height - 5, 'U');
    change_slider_size(top, slider_size);      
    change_slider_size(bottom, slider_size);  
    int top_score = 0;
    int bottom_score = 0;
    bool paused = false;

    std::vector<ScoreEntry> scores;
    load_scores(scores);  

    // Initialize obstructions
    std::vector<obstruction_t*> obstructions;

    // Place obstructions only if the difficulty is hard
    if (difficulty == '3') {
        int x1 = zone_width / 2 - 40;  
        int y1 = zone_height / 2 + 8;    
        obstructions.push_back(init_obstruction(x1, y1, 6, 3));  // Larger size

        int x2 = zone_width / 2 + 15; 
        int y2 = zone_height / 2 - 8;    
        obstructions.push_back(init_obstruction(x2, y2, 6, 3));  // Larger size
    }

    clear_win_file();  

    int sets_played = 0;
    int top_sets_won = 0;
    int bottom_sets_won = 0;
    std::vector<std::string> winners;

    while (sets_played < num_sets) {
        // Reset scores for each set
        top_score = 0;
        bottom_score = 0;

        // Clear and redraw the screen to remove any artifacts from the previous set
        clear();
        refresh();
        reset_ball_position(b, zone_width, zone_height);  // Reset ball position
        draw_zone(z, goal_area_width); 
        draw_slider(top);
        draw_slider(bottom);
        draw_ball(b);
        if (difficulty == '3') {
            for (auto& o : obstructions) draw_obstruction(o);
        }
        attron(COLOR_PAIR(1)); // Use color pair 1 for score display
        mvprintw(0, 0, "Top Score: %d | Bottom Score: %d", top_score, bottom_score); 
        attroff(COLOR_PAIR(1)); // Turn off color pair 1
        refresh();
        nodelay(stdscr, TRUE);  

        bool game_over = false; 

        time_t start_time = time(NULL); 
        int time_limit = 120; 

        while (!game_over) { 
            c = getch();
            if (c != ERR) {
                refresh();
                switch (c) {
                    // Functionality for Left Arrow Key that controls the bottom slider
                    case KEY_LEFT:
                        if (!paused) {
                            moveSlider(bottom, bottom->upper_left_x - slider_x_speed, bottom->upper_left_y, zone_width, zone_height, false);
                        }
                        break;
                    // Functionality for Right Arrow Key that controls the bottom slider
                    case KEY_RIGHT:
                        if (!paused) {
                            moveSlider(bottom, bottom->upper_left_x + slider_x_speed, bottom->upper_left_y, zone_width, zone_height, false);
                        }
                        break;
                    // Functionality for Up Arrow Key that controls the bottom slider
                    case KEY_UP:
                        if (!paused) {
                            moveSlider(bottom, bottom->upper_left_x, bottom->upper_left_y - slider_y_speed, zone_width, zone_height, false);
                        }
                        break;
                    // Functionality for Down Arrow Key that controls the bottom slider
                    case KEY_DOWN:
                        if (!paused) {
                            moveSlider(bottom, bottom->upper_left_x, bottom->upper_left_y + slider_y_speed, zone_width, zone_height, false);
                        }
                        break;
                    // Functionality for A Key that controls the top slider
                    case 'A':
                    case 'a':
                        if (!paused) {
                            moveSlider(top, top->upper_left_x - slider_x_speed, top->upper_left_y, zone_width, zone_height, true);
                        }
                        break; 
                    // Functionality for D Key that controls the top slider
                    case 'D':
                    case 'd':
                        if (!paused) {
                            moveSlider(top, top->upper_left_x + slider_x_speed, top->upper_left_y, zone_width, zone_height, true);
                        }
                        break;
                    // Functionality for W Key that controls the top slider
                    case 'W':
                    case 'w':
                        if (!paused) {
                            moveSlider(top, top->upper_left_x, top->upper_left_y - slider_y_speed, zone_width, zone_height, true);
                        }
                        break;
                    // Functionality for S Key that controls the top slider
                    case 'S':
                    case 's':
                        if (!paused) {
                            moveSlider(top, top->upper_left_x, top->upper_left_y + slider_y_speed, zone_width, zone_height, true);
                        }
                        save_game_state(top_score, bottom_score, b, top, bottom);  // Save game state
                        break;
                    // Functionality to change slider size
                    case '+':
                        if (!paused) {
                            change_slider_size(top, 7);
                            change_slider_size(bottom, 7);
                        }
                        break;
                    case '-':
                        if (!paused) {
                            change_slider_size(top, 3);
                            change_slider_size(bottom, 3);
                        }
                        break;
                    // Functionality to pause and resume the game
                    case 'P':
                    case 'p':
                        paused = !paused;
                        if (paused) {
                            attron(COLOR_PAIR(1)); // Use color pair 1 for pause message
                            mvprintw(zone_height / 2, zone_width / 2 - 5, "Game Paused");
                            attroff(COLOR_PAIR(1)); // Turn off color pair 1
                        } else {
                            mvprintw(zone_height / 2, zone_width / 2 - 5, "           "); // Clear pause message
                        }
                        break;
                    // Functionality to quit the game
                    case 'Q':
                    case 'q':
                        endwin();
                        return;
                    default:
                        break;
                }
            }

            if (!paused) {
                undraw_zone(z);
                draw_zone(z, goal_area_width); 
                undraw_ball(b);
                moveBall(b, z, bottom, top, obstructions, top_score, bottom_score, goal_area_width); 

                if (difficulty == '3') {
                    for (auto& o : obstructions) {
                        undraw_obstruction(o);
                        draw_obstruction(o);
                        if (checkCollisionObstruction(o, b)) {
                            // Reset ball position and increase speed
                            b->speed_x = (b->speed_x > 0 ? b->speed_x + 1 : b->speed_x - 1);
                            b->speed_y = (b->speed_y > 0 ? b->speed_y + 1 : b->speed_y - 1);
                            reset_ball_position(b, zone_width, zone_height);
                            // Reset scores if ball hits obstruction
                            top_score = 0;
                            bottom_score = 0;
                        }
                    }
                }

                // Display updated scores
                attron(COLOR_PAIR(1)); // Use color pair 1 for score display
                mvprintw(0, 0, "Top Score: %d | Bottom Score: %d", top_score, bottom_score);
                attroff(COLOR_PAIR(1)); // Turn off color pair 1

                draw_ball(b);

                // Check for win condition
                if (top_score >= 10 || bottom_score >= 10) {
                    // Determine the winner
                    std::string winner = top_score > bottom_score ? "Top" : "Bottom";
                    update_win_file(winner); 

                    winners.push_back(winner);

                    if (winner == "Top") {
                        top_sets_won++;
                    } else {
                        bottom_sets_won++;
                    }

                    // Display set over screen and end game
                    display_set_over_screen(top_sets_won, bottom_sets_won, winners);
                    sets_played++;
                    game_over = true;  // Set game_over flag to exit loop
                }

                // Check for time limit
                if (difftime(time(NULL), start_time) >= time_limit) {
                    // Time limit reached
                    clear();  // Clear the screen
                    refresh();
                    display_set_over_screen(top_sets_won, bottom_sets_won, winners);
                    sets_played++;
                    game_over = true;  // Set game_over flag to exit loop
                }
            }

            refresh();
            nanosleep(&tim, &tim_ret);
        }
    }

    // Save final set wins to save_best_10.txt
    save_final_set_wins(top_sets_won, bottom_sets_won);

    // Display final checkout screen after all sets
    display_final_checkout_screen(top_sets_won, bottom_sets_won);

    // Display best 10 winner history
    display_best_10_winner_history();

    // Ensure endwin() is called after displaying the game over screen
    endwin();
}
