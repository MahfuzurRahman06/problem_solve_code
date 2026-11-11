#include <bits/stdc++.h>
using namespace std;

// Game Settings
const int TOTAL_QUESTIONS = 10;
const int CORRECT_POINTS = 10;
const int WRONG_PENALTY = 5;
const int WINNING_SCORE = 60;

// Question Structure
struct Question {
    long long first = 0;
    long long second = 0;
    char operation = '+';
    long long answer = 0;

    string expression() const {
        return to_string(first) + " " + operation + " " + to_string(second);
    }
};

// Player Information
struct PlayerRecord {
    string name;
    int score = 0;
    int correct = 0;
    int total = TOTAL_QUESTIONS;
};

class MathChallenge {

private:

    mt19937 rng;
    vector<PlayerRecord> leaderboard;

    // Generate Random Number
    int randomInt(int low, int high) {
        uniform_int_distribution<int> dist(low, high);
        return dist(rng);
    }

    // Take Valid Integer Input
    long long readInteger(const string& prompt) {
        long long value;

        while (true) {
            cout << prompt;

            if (cin >> value) {
                return value;
            }

            cout << "Invalid input. Please enter a whole number.\n";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Take Player Name
    string readName() {
        string name;

        cout << "Enter your name: ";
        getline(cin >> ws, name);

        if (name.empty()) {
            name = "Player";
        }

        return name;
    }

    // Select Difficulty
    int chooseDifficulty() {

        cout << "\nSelect Difficulty\n";
        cout << "1. Easy   (Small Numbers)\n";
        cout << "2. Medium (Medium Numbers)\n";
        cout << "3. Hard   (Large Numbers)\n";

        while (true) {

            long long choice = readInteger("Enter choice: ");

            if (choice >= 1 && choice <= 3) {
                return static_cast<int>(choice);
            }

            cout << "Please choose 1, 2, or 3.\n";
        }
    }

    // Generate Random Question
    Question generateQuestion(int difficulty) {

        int limit;

        if (difficulty == 1)
            limit = 10;
        else if (difficulty == 2)
            limit = 50;
        else
            limit = 100;

        Question q;

        const char operations[] = {'+', '-', '*', '/'};

        q.operation = operations[randomInt(0, 3)];

        // Addition
        if (q.operation == '+') {

            q.first = randomInt(1, limit);
            q.second = randomInt(1, limit);

            q.answer = q.first + q.second;
        }

        // Subtraction
        else if (q.operation == '-') {

            q.first = randomInt(1, limit);
            q.second = randomInt(1, limit);

            if (q.second > q.first) {
                swap(q.first, q.second);
            }

            q.answer = q.first - q.second;
        }

        // Multiplication
        else if (q.operation == '*') {

            int multiplierLimit =
                (difficulty == 1 ? 10 :
                difficulty == 2 ? 12 : 20);

            q.first = randomInt(1, limit);
            q.second = randomInt(1, multiplierLimit);

            q.answer = q.first * q.second;
        }

        // Division (Always Exact)
        else {

            q.second = randomInt(1, limit);
            q.answer = randomInt(1, limit);

            q.first = q.second * q.answer;
        }

        return q;
    }

    // Merge Function
    void merge(
        vector<PlayerRecord>& records,
        int left,
        int mid,
        int right
    ) {

        vector<PlayerRecord> L(
            records.begin() + left,
            records.begin() + mid + 1
        );

        vector<PlayerRecord> R(
            records.begin() + mid + 1,
            records.begin() + right + 1
        );

        int i = 0;
        int j = 0;
        int k = left;

        while (i < (int)L.size() &&
               j < (int)R.size()) {

            if (L[i].score > R[j].score ||
                (L[i].score == R[j].score &&
                 L[i].correct >= R[j].correct)) {

                records[k++] = L[i++];
            }
            else {
                records[k++] = R[j++];
            }
        }

        while (i < (int)L.size()) {
            records[k++] = L[i++];
        }

        while (j < (int)R.size()) {
            records[k++] = R[j++];
        }
    }

    // Merge Sort: Highest Score First
    void mergeSort(
        vector<PlayerRecord>& records,
        int left,
        int right
    ) {

        if (left >= right) {
            return;
        }

        int mid = left + (right - left) / 2;

        mergeSort(records, left, mid);
        mergeSort(records, mid + 1, right);

        merge(records, left, mid, right);
    }

    // Start Game
    void playGame() {

        PlayerRecord record;

        record.name = readName();

        int difficulty = chooseDifficulty();

        // Stack for Question History
        stack<Question> questionHistory;

        cout << "\n========================================\n";
        cout << "              GAME STARTED              \n";
        cout << "========================================\n";

        cout << "Correct Answer: +" << CORRECT_POINTS << "\n";
        cout << "Wrong Answer: -" << WRONG_PENALTY << "\n";
        cout << "Winning Score: " << WINNING_SCORE << "\n\n";

        // Game Loop
        for (int i = 1; i <= TOTAL_QUESTIONS; i++) {

            Question q = generateQuestion(difficulty);

            questionHistory.push(q);

            cout << "\nQuestion " << i
                 << "/" << TOTAL_QUESTIONS << "\n";

            cout << q.expression() << " = ?\n";

            long long userAnswer =
                readInteger("Your Answer: ");

            // Check Answer
            if (userAnswer == q.answer) {

                record.correct++;

                record.score += CORRECT_POINTS;

                cout << "\nCorrect Answer!\n";
                cout << "+" << CORRECT_POINTS << " Points\n";
            }

            else {

                record.score = max(
                    0,
                    record.score - WRONG_PENALTY
                );

                cout << "\nWrong Answer!\n";

                cout << "Correct Answer: "
                     << q.answer << "\n";

                cout << "-" << WRONG_PENALTY
                     << " Points\n";
            }

            cout << "Current Score: "
                 << record.score << "\n";

            cout << "----------------------------------------\n";
        }

        // Calculate Performance
        int wrong = TOTAL_QUESTIONS - record.correct;

        double accuracy =
            100.0 * record.correct / TOTAL_QUESTIONS;

        // Final Result
        cout << "\n=============== GAME RESULT ===============\n";

        cout << "Player: " << record.name << "\n";

        cout << "Total Questions: "
             << TOTAL_QUESTIONS << "\n";

        cout << "Correct Answers: "
             << record.correct << "\n";

        cout << "Wrong Answers: "
             << wrong << "\n";

        cout << fixed << setprecision(1);

        cout << "Accuracy: "
             << accuracy << "%\n";

        cout << "Final Score: "
             << record.score << "\n";

        // Winning Condition
        if (record.score >= WINNING_SCORE) {

            cout << "\nCongratulations! YOU WIN!\n";
        }

        else {

            cout << "\nBetter Luck Next Time!\n";
        }

        cout << "===========================================\n";

        // Display Question History
        cout << "\nQuestion History (Latest First):\n";

        stack<Question> temp = questionHistory;

        int number = TOTAL_QUESTIONS;

        while (!temp.empty()) {

            cout << number-- << ". "
                 << temp.top().expression() << "\n";

            temp.pop();
        }

        // Add Player to Leaderboard
        leaderboard.push_back(record);

        cout << "\nYour result has been added "
             << "to the leaderboard.\n";
    }

    // Show Leaderboard
    void showLeaderboard() {

        if (leaderboard.empty()) {

            cout << "\nNo Scores Yet!\n";
            cout << "Play a game first.\n";

            return;
        }

        vector<PlayerRecord> sortedRecords = leaderboard;

        // Sort Using Merge Sort
        mergeSort(
            sortedRecords,
            0,
            (int)sortedRecords.size() - 1
        );

        cout << "\n=============== LEADERBOARD ===============\n";

        cout << left
             << setw(6) << "Rank"
             << setw(22) << "Player"
             << setw(10) << "Score"
             << setw(10) << "Correct"
             << "Total\n";

        cout << "----------------------------------------------\n";

        int limit = min(10, (int)sortedRecords.size());

        for (int i = 0; i < limit; i++) {

            cout << left
                 << setw(6) << i + 1
                 << setw(22)
                 << sortedRecords[i].name.substr(0, 20)
                 << setw(10)
                 << sortedRecords[i].score
                 << setw(10)
                 << sortedRecords[i].correct
                 << sortedRecords[i].total
                 << "\n";
        }

        cout << "==============================================\n";

        // Search Player Using Linear Search
        cout << "\nEnter a player name to search ";
        cout << "(or type - to return): ";

        string target;

        getline(cin >> ws, target);

        if (target == "-") {
            return;
        }

        bool found = false;

        for (const PlayerRecord& record : leaderboard) {

            if (record.name == target) {

                cout << "\nPlayer Found!\n";

                cout << "Name: "
                     << record.name << "\n";

                cout << "Score: "
                     << record.score << "\n";

                cout << "Correct Answers: "
                     << record.correct << "/"
                     << record.total << "\n";

                found = true;
            }
        }

        if (!found) {

            cout << "No record found for " << target << ".\n";
        }
    }

    // Game Instructions
    void showInstructions() {

        cout << "\n=============== HOW TO PLAY ===============\n";

        cout << "1. Enter your name.\n";

        cout << "2. Select a difficulty level.\n";

        cout << "3. You will get 10 random questions.\n";

        cout << "4. Operations: +, -, * and /.\n";

        cout << "5. Correct Answer: +10 Points.\n";

        cout << "6. Wrong Answer: -5 Points.\n";

        cout << "7. Minimum Score is zero.\n";

        cout << "8. Score of 60 or more means YOU WIN.\n";

        cout << "9. Leaderboard works during this session.\n";

        cout << "10. Scores reset when the program closes.\n";

        cout << "===========================================\n";
    }

public:

    // Constructor
    MathChallenge() : rng(random_device{}()) {}

    // Main Menu
    void run() {

        while (true) {

            cout << "\n========================================\n";

            cout << "             MATH CHALLENGE             \n";

            cout << "          Arithmetic Quiz Game          \n";

            cout << "========================================\n";

            cout << "1. Play Game\n";

            cout << "2. Leaderboard\n";

            cout << "3. Instructions\n";

            cout << "0. Exit\n";

            long long choice =
                readInteger("\nEnter your choice: ");

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

                case 0:
                    cout << "\nThanks for playing "
                         << "Math Challenge!\n";

                    return;

                default:
                    cout << "\nInvalid Choice! Try Again.\n";
            }
        }
    }
};

// Main Function
int main() {

    MathChallenge game;

    game.run();

    return 0;
}
