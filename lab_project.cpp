
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
    uniform_int_distribution<int> dist(low, high);
    return dist(rng);
}

// Input Validation
int readInteger() {
    int value;

    while (!(cin >> value)) {
        cout << "Invalid input! Enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return value;
}

// Generate Question
Question generateQuestion(int difficulty) {

    int low, high;

    if (difficulty == 1) {
        low = 1;
        high = 10;
    }
    else if (difficulty == 2) {
        low = 10;
        high = 50;
    }
    else {
        low = 20;
        high = 100;
    }

    Question q;

    q.op = "+-*/"[randomInt(0, 3)];

    q.num1 = randomInt(low, high);
    q.num2 = randomInt(low, high);

    if (q.op == '+') {
        q.answer = q.num1 + q.num2;
    }
    else if (q.op == '-') {

        if (q.num1 < q.num2) {
            swap(q.num1, q.num2);
        }

        q.answer = q.num1 - q.num2;
    }
    else if (q.op == '*') {
        q.answer = q.num1 * q.num2;
    }
    else {
        // Exact Division
        q.num2 = randomInt(1, high);
        q.answer = randomInt(1, high);
        q.num1 = q.num2 * q.answer;
    }

    return q;
}

// Merge Function
void merge(vector<PlayerRecord>& arr, int left, int mid, int right) {

    vector<PlayerRecord> temp;

    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right) {

        if (arr[i].score > arr[j].score ||
            (arr[i].score == arr[j].score &&
             arr[i].correct >= arr[j].correct)) {

            temp.push_back(arr[i]);
            i++;
        }
        else {
            temp.push_back(arr[j]);
            j++;
        }
    }

    while (i <= mid) {
        temp.push_back(arr[i]);
        i++;
    }

    while (j <= right) {
        temp.push_back(arr[j]);
        j++;
    }

    for (int k = 0; k < (int)temp.size(); k++) {
        arr[left + k] = temp[k];
    }
}

// Merge Sort
void mergeSort(vector<PlayerRecord>& arr, int left, int right) {

    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    merge(arr, left, mid, right);
}

// Linear Search
int linearSearch(const vector<PlayerRecord>& arr, string target) {

    for (int i = 0; i < (int)arr.size(); i++) {

        if (arr[i].name == target) {
            return i;
        }
    }

    return -1;
}

// Show Instructions
void showInstructions() {

    cout << "\n========== INSTRUCTIONS ==========\n";

    cout << "1. There are 10 questions.\n";
    cout << "2. Choose Easy, Medium or Hard.\n";
    cout << "3. Correct answer gives +10 points.\n";
    cout << "4. Wrong answer deducts 5 points.\n";
    cout << "5. Minimum score is 0.\n";
    cout << "6. Score 60 or above to win.\n";
    cout << "7. Operations: +, -, *, /\n";
}

// Play Game
void playGame() {

    string name;
    int difficulty;

    cout << "\nEnter Player Name: ";
    cin >> ws;
    getline(cin, name);

    if (name.empty()) {
        cout << "Name cannot be empty!\n";
        return;
    }

    cout << "\nSelect Difficulty\n";
    cout << "1. Easy\n";
    cout << "2. Medium\n";
    cout << "3. Hard\n";

    cout << "Enter Choice: ";
    difficulty = readInteger();

    while (difficulty < 1 || difficulty > 3) {
        cout << "Invalid choice! Select 1, 2 or 3: ";
        difficulty = readInteger();
    }

    int score = 0;
    int correct = 0;
    int wrong = 0;

    stack<Question> history;

    cout << "\n========== GAME START ==========\n";

    // Question Loop
    for (int i = 1; i <= TOTAL_QUESTIONS; i++) {

        Question q = generateQuestion(difficulty);

        history.push(q);

        cout << "\nQuestion " << i << " / " << TOTAL_QUESTIONS << "\n";

        cout << q.num1 << " " << q.op << " " << q.num2 << " = ?\n";

        cout << "Your Answer: ";

        int userAnswer = readInteger();

        if (userAnswer == q.answer) {

            cout << "Correct Answer!\n";

            score += CORRECT_POINTS;
            correct++;
        }
        else {

            cout << "Wrong Answer!\n";

            cout << "Correct Answer: " << q.answer << "\n";

            score -= WRONG_PENALTY;

            if (score < 0) {
                score = 0;
            }

            wrong++;
        }

        cout << "Current Score: " << score << "\n";
    }

    // Performance Report
    double accuracy = (correct * 100.0) / TOTAL_QUESTIONS;

    cout << "\n========== GAME RESULT ==========\n";

    cout << "Player Name: " << name << "\n";
    cout << "Total Questions: " << TOTAL_QUESTIONS << "\n";
    cout << "Correct Answers: " << correct << "\n";
    cout << "Wrong Answers: " << wrong << "\n";
    cout << "Final Score: " << score << "\n";

    cout << fixed << setprecision(2);
    cout << "Accuracy: " << accuracy << "%\n";

    if (score >= WINNING_SCORE) {
        cout << "\nCongratulations! YOU WIN!\n";
    }
    else {
        cout << "\nBetter Luck Next Time!\n";
    }

    // Question History using Stack
    cout << "\n========== QUESTION HISTORY ==========\n";

    stack<Question> temp = history;

    int count = TOTAL_QUESTIONS;

    while (!temp.empty()) {

        Question q = temp.top();

        cout << "Question " << count << ": " << q.num1 << " " << q.op
             << " " << q.num2
             << " = " << q.answer << "\n";

        temp.pop();
        count--;
    }

    // Save Player Record
    PlayerRecord player;

    player.name = name;
    player.score = score;
    player.correct = correct;
    player.wrong = wrong;

    leaderboard.push_back(player);

    cout << "\nYour result has been added to Leaderboard!\n";
}

// Show Leaderboard
void showLeaderboard() {

    if (leaderboard.empty()) {
        cout << "\nNo player records available!\n";
        return;
    }

    vector<PlayerRecord> sorted = leaderboard;

    // Sort using Merge Sort
    mergeSort(sorted, 0, (int)sorted.size() - 1);

    cout << "\n========== LEADERBOARD ==========\n";

    cout << left << setw(6) << "Rank"
         << setw(20) << "Player"
         << setw(12) << "Score"
         << setw(12) << "Correct"
         << "Wrong\n";

    cout << "------------------------------------------------\n";

    for (int i = 0; i < (int)sorted.size(); i++) {

        cout << left << setw(6) << i + 1
             << setw(20) << sorted[i].name
             << setw(12) << sorted[i].score
             << setw(12) << sorted[i].correct
             << sorted[i].wrong << "\n";
    }

    // Search Player using Linear Search
    string target;

    cout << "\nEnter Player Name to Search: ";
    cin >> ws;
    getline(cin, target);

    int index = linearSearch(leaderboard, target);

    if (index != -1) {

        cout << "\nPlayer Found!\n";
        cout << "Name: " << leaderboard[index].name << "\n";
        cout << "Score: " << leaderboard[index].score << "\n";
        cout << "Correct Answers: " << leaderboard[index].correct << "\n";
        cout << "Wrong Answers: " << leaderboard[index].wrong << "\n";
    }
    else {
        cout << "\nPlayer Not Found!\n";
    }
}

// Main Menu
void showMenu() {

    int choice;

    while (true) {

        cout << "\n================================\n";
        cout << "        MATH CHALLENGE\n";
        cout << "================================\n";

        cout << "1. Start Game\n";
        cout << "2. Leaderboard\n";
        cout << "3. Instructions\n";
        cout << "4. Exit\n";

        cout << "Enter Choice: ";

        choice = readInteger();

        switch (choice) {

            case 1:
                playGame();
                break;

            case 2:
                showLeaderboard();
                break;

            case 3:
                showInstructions();
                break;

            case 4:
                cout << "\nThank you for playing!\n";
                return;

            default:
                cout << "\nInvalid Choice! Try Again.\n";
        }
    }
}

// Main Function
int main() {

    showMenu();

    return 0;
}
