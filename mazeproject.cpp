#include <bits/stdc++.h>
using namespace std;

using namespace chrono;

const int MAX_SIZE = 100;

int n, m;
vector<string> maze;

pair<int, int> startPoint, endPoint;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

string direction[] = {"UP", "DOWN", "LEFT", "RIGHT"};

struct Result {
    string algorithm;
    bool found = false;
    vector<pair<int, int>> path;
    int visitedNodes = 0;
    double executionTime = 0;
};

// Check whether a cell is valid
bool isValid(int x, int y) {
    return (x >= 0 && x < n &&
            y >= 0 && y < m &&
            maze[x][y] != '#');
}

// Display maze
void displayMaze(vector<pair<int, int>> path = {}) {

    vector<string> temp = maze;

    for (auto p : path) {
        int x = p.first;
        int y = p.second;

        if (temp[x][y] != 'S' && temp[x][y] != 'E') {
            temp[x][y] = '*';
        }
    }

    cout << "\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << temp[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
}

// Reconstruct path using parent array
vector<pair<int, int>> getPath(
    vector<vector<pair<int, int>>>& parent
) {
    vector<pair<int, int>> path;

    pair<int, int> current = endPoint;

    while (current != startPoint) {

        path.push_back(current);

        current = parent[current.first][current.second];

        if (current.first == -1) {
            return {};
        }
    }

    path.push_back(startPoint);

    reverse(path.begin(), path.end());

    return path;
}

// BFS Algorithm
Result BFS() {

    Result res;
    res.algorithm = "BFS";

    auto startTime = high_resolution_clock::now();

    vector<vector<bool>> visited(
        n, vector<bool>(m, false)
    );

    vector<vector<pair<int, int>>> parent(
        n, vector<pair<int, int>>(
            m, {-1, -1}
        )
    );

    queue<pair<int, int>> q;

    q.push(startPoint);
    visited[startPoint.first][startPoint.second] = true;

    while (!q.empty()) {

        auto current = q.front();
        q.pop();

        int x = current.first;
        int y = current.second;

        res.visitedNodes++;

        if (current == endPoint) {
            res.found = true;
            break;
        }

        for (int i = 0; i < 4; i++) {

            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isValid(nx, ny) && !visited[nx][ny]) {

                visited[nx][ny] = true;

                parent[nx][ny] = {x, y};

                q.push({nx, ny});
            }
        }
    }

    if (res.found) {
        res.path = getPath(parent);
    }

    auto endTime = high_resolution_clock::now();

    res.executionTime =
        duration<double, milli>(
            endTime - startTime
        ).count();

    return res;
}

// DFS Algorithm
Result DFS() {

    Result res;
    res.algorithm = "DFS";

    auto startTime = high_resolution_clock::now();

    vector<vector<bool>> visited(
        n, vector<bool>(m, false)
    );

    vector<vector<pair<int, int>>> parent(
        n, vector<pair<int, int>>(
            m, {-1, -1}
        )
    );

    stack<pair<int, int>> st;

    st.push(startPoint);
    visited[startPoint.first][startPoint.second] = true;

    while (!st.empty()) {

        auto current = st.top();
        st.pop();

        int x = current.first;
        int y = current.second;

        res.visitedNodes++;

        if (current == endPoint) {
            res.found = true;
            break;
        }

        for (int i = 0; i < 4; i++) {

            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isValid(nx, ny) && !visited[nx][ny]) {

                visited[nx][ny] = true;

                parent[nx][ny] = {x, y};

                st.push({nx, ny});
            }
        }
    }

    if (res.found) {
        res.path = getPath(parent);
    }

    auto endTime = high_resolution_clock::now();

    res.executionTime =
        duration<double, milli>(
            endTime - startTime
        ).count();

    return res;
}

// Backtracking Algorithm
bool backtrack(
    int x,
    int y,
    vector<vector<bool>>& visited,
    Result& res
) {

    visited[x][y] = true;
    res.visitedNodes++;

    if (make_pair(x, y) == endPoint) {
        res.path.push_back({x, y});
        return true;
    }

    for (int i = 0; i < 4; i++) {

        int nx = x + dx[i];
        int ny = y + dy[i];

        if (isValid(nx, ny) && !visited[nx][ny]) {

            if (backtrack(nx, ny, visited, res)) {

                res.path.push_back({x, y});

                return true;
            }
        }
    }

    return false;
}

// Backtracking Solver
Result Backtracking() {

    Result res;
    res.algorithm = "Backtracking";

    auto startTime = high_resolution_clock::now();

    vector<vector<bool>> visited(
        n, vector<bool>(m, false)
    );

    res.found = backtrack(
        startPoint.first,
        startPoint.second,
        visited,
        res
    );

    if (res.found) {
        reverse(res.path.begin(), res.path.end());
    }

    auto endTime = high_resolution_clock::now();

    res.executionTime =
        duration<double, milli>(
            endTime - startTime
        ).count();

    return res;
}

// Display algorithm result
void showResult(Result res) {

    cout << "\n========== "
         << res.algorithm
         << " RESULT ==========\n";

    if (res.found) {

        cout << "Path Found: YES\n";

        cout << "Shortest Path Length: ";

        if (res.algorithm == "BFS") {
            cout << res.path.size() - 1 << " moves\n";
        }
        else {
            cout << res.path.size() - 1
                 << " moves (not guaranteed shortest)\n";
        }

        cout << "Visited Nodes: "
             << res.visitedNodes << endl;

        cout << "\nFinal Maze:\n";

        displayMaze(res.path);

    }
    else {

        cout << "Path Found: NO\n";
        cout << "No path available!\n";

    }

    cout << fixed << setprecision(6);

    cout << "Execution Time: "
         << res.executionTime
         << " ms\n";

    cout << "================================\n";
}

// Performance Comparison
void compareResults() {

    Result results[3];

    results[0] = BFS();
    results[1] = DFS();
    results[2] = Backtracking();

    cout << "\n========== PERFORMANCE COMPARISON ==========\n";

    cout << left
         << setw(18) << "Algorithm"
         << setw(15) << "Path Found"
         << setw(15) << "Visited Nodes"
         << setw(18) << "Path Length"
         << setw(15) << "Time (ms)"
         << endl;

    cout << string(81, '-') << endl;

    for (auto res : results) {

        cout << left
             << setw(18) << res.algorithm
             << setw(15) << (res.found ? "YES" : "NO")
             << setw(15) << res.visitedNodes;

        if (res.found) {
            cout << setw(18) << res.path.size() - 1;
        }
        else {
            cout << setw(18) << "N/A";
        }

        cout << fixed << setprecision(6)
             << res.executionTime
             << endl;
    }

    cout << string(81, '-') << endl;

    cout << "\nNote:\n";
    cout << "BFS guarantees shortest path in an unweighted maze.\n";
    cout << "DFS and Backtracking do not guarantee shortest path.\n";
}

// Main function
int main() {

    cout << "====================================\n";
    cout << "       SMART MAZE SOLVER\n";
    cout << "====================================\n";

    cout << "\nEnter number of rows: ";
    cin >> n;

    cout << "Enter number of columns: ";
    cin >> m;

    if (n <= 0 || m <= 0 || n > MAX_SIZE || m > MAX_SIZE) {
        cout << "Invalid maze dimensions!\n";
        return 0;
    }

    maze.resize(n);

    cout << "\nEnter maze row by row:\n";
    cout << "S = Start, E = End, # = Wall, . = Empty\n\n";

    int startCount = 0;
    int endCount = 0;

    for (int i = 0; i < n; i++) {

        cin >> maze[i];

        if ((int)maze[i].size() != m) {
            cout << "Invalid row length!\n";
            return 0;
        }

        for (int j = 0; j < m; j++) {

            if (maze[i][j] == 'S') {
                startPoint = {i, j};
                startCount++;
            }

            else if (maze[i][j] == 'E') {
                endPoint = {i, j};
                endCount++;
            }

            else if (maze[i][j] != '#' && maze[i][j] != '.') {
                cout << "Invalid maze character!\n";
                return 0;
            }
        }
    }

    if (startCount != 1 || endCount != 1) {
        cout << "Maze must contain exactly one S and one E!\n";
        return 0;
    }

    cout << "\nOriginal Maze:\n";
    displayMaze();

    int choice;

    do {

        cout << "\n========== MAIN MENU ==========\n";

        cout << "1. Solve using BFS\n";
        cout << "2. Solve using DFS\n";
        cout << "3. Solve using Backtracking\n";
        cout << "4. Performance Comparison\n";
        cout << "5. Display Original Maze\n";
        cout << "0. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1: {
                Result res = BFS();
                showResult(res);
                break;
            }

            case 2: {
                Result res = DFS();
                showResult(res);
                break;
            }

            case 3: {
                Result res = Backtracking();
                showResult(res);
                break;
            }

            case 4: {
                compareResults();
                break;
            }

            case 5: {
                displayMaze();
                break;
            }

            case 0:
                cout << "\nThank you for using Smart Maze Solver!\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
