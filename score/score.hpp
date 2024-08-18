#ifndef SCORE_HPP
#define SCORE_HPP

#include <vector>
#include <string>

// Structure to represent a score entry with the winner and score
struct ScoreEntry {
    std::string winner;
    int score;
};

// Function to load scores from a file
void load_scores(std::vector<ScoreEntry>& scores);

// Function to save scores to a file
void save_scores(const std::vector<ScoreEntry>& scores);

// Function to update the score list with a new score
void update_scores(std::vector<ScoreEntry>& scores, const std::string& winner, int new_score);

#endif
