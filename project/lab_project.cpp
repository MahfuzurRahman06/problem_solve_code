
#include <bits/stdc++.h>

using namespace std;

// Game Settings
const int TOTAL_QUESTIONS = 10;
const int CORRECT_POINTS = 10;
const int WRONG_PENALTY = 5;
const int WINNING_SCORE = 60;

// Question Structure
struct Question {
    int num1;
    int num2;
    char op;
    int answer;
};

// Player Structure
struct PlayerRecord {
    string name;
    int score;
    int correct;
    int wrong;
};

// Global Variables
mt19937 rng(random_device{}());

vector<PlayerRecord> leaderboard;

// Generate Random Number
int randomInt(int low, int high) {
    
}

// Input Validation
int readInteger() {

}

// Generate Question
Question generateQuestion(int difficulty) {
    
}

// Merge Function
void merge(vector<PlayerRecord>& arr, int left, int mid, int right) {
    
}

// Merge Sort
void mergeSort(vector<PlayerRecord>& arr, int left, int right) {
    
}

// Linear Search
int linearSearch(const vector<PlayerRecord>& arr, string target) {
    
}

// Show Instructions
void showInstructions() {
    
}

// Play Game
void playGame() {
    
}

// Show Leaderboard
void showLeaderboard() {
    
}

// Main Menu
void showMenu() {
    
}

// Main Function
int main() {

    showMenu();

    return 0;
}
