#include "score.hpp"
#include <fstream>
#include <algorithm>
#include <sys/stat.h> 
#include <sys/types.h> 

const std::string SCORE_FILE = "./saves/save_best_10.txt";

// Helper function to create the saves directory if it doesn't exist
void create_saves_directory() {
    struct stat info;

    if (stat("./saves", &info) != 0) {
        // Directory does not exist, create it
        mkdir("./saves", 0755);
    }
}

// Load scores from a file
void load_scores(std::vector<ScoreEntry>& scores) {
    std::ifstream infile(SCORE_FILE.c_str());
    std::string winner;
    int score;
    while (infile >> winner >> score) {
        ScoreEntry entry;
        entry.winner = winner;
        entry.score = score;
        scores.push_back(entry);
    }
    infile.close();
}

// Save scores to a file
void save_scores(const std::vector<ScoreEntry>& scores) {
    create_saves_directory(); // Ensure the saves directory exists
    std::ofstream outfile(SCORE_FILE.c_str());
    for (size_t i = 0; i < scores.size(); ++i) {
        outfile << "Winner: " << scores[i].winner << " " << scores[i].score << std::endl;
    }
    outfile.close();
}

// Function to compare scores for sorting in descending order
bool compare_scores(const ScoreEntry& a, const ScoreEntry& b) {
    return a.score > b.score;
}

// Update the score list with a new score
void update_scores(std::vector<ScoreEntry>& scores, const std::string& winner, int new_score) {
    ScoreEntry entry;
    entry.winner = winner;
    entry.score = new_score;
    scores.push_back(entry);
    std::sort(scores.begin(), scores.end(), compare_scores);
    if (scores.size() > 10) {
        scores.resize(10);
    }
}
