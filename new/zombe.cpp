
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int SIZE = 7;

int main() {
    srand(time(0));

    int playerX = 0, playerY = 0;
    int zombieX = 6, zombieY = 6;

    int health = 100;
    int score = 0;
    char move;

    cout << "============================\n";
    cout << "     ZOMBIE ESCAPE GAME\n";
    cout << "============================\n";

    cout << "Escape from the zombie!\n";
    cout << "Reach E to win.\n";
    cout << "W = Up, S = Down\n";
    cout << "A = Left, D = Right\n\n";

    while (health > 0) {

        // Display map
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {

                if (i == playerX && j == playerY)
                    cout << "P ";

                else if (i == zombieX && j == zombieY)
                    cout << "Z ";

                else if (i == 6 && j == 0)
                    cout << "E ";

                else
                    cout << ". ";
            }
            cout << endl;
        }

        cout << "\nHealth: " << health;
        cout << " | Score: " << score << endl;

        cout << "\nMove (W/A/S/D): ";
        cin >> move;

        // Player movement
        if (move == 'w' || move == 'W')
            playerX--;

        else if (move == 's' || move == 'S')
            playerX++;

        else if (move == 'a' || move == 'A')
            playerY--;

        else if (move == 'd' || move == 'D')
            playerY++;

        else {
            cout << "Invalid move!\n";
            continue;
        }

        // Boundary checking
        if (playerX < 0) playerX = 0;
        if (playerX >= SIZE) playerX = SIZE - 1;
        if (playerY < 0) playerY = 0;
        if (playerY >= SIZE) playerY = SIZE - 1;

        score += 10;

        // Check winning condition
        if (playerX == 6 && playerY == 0) {
            cout << "\nYOU ESCAPED SUCCESSFULLY!\n";
            cout << "Final Score: " << score << endl;
            break;
        }

        // Zombie movement
        if (zombieX < playerX)
            zombieX++;
        else if (zombieX > playerX)
            zombieX--;

        if (zombieY < playerY)
            zombieY++;
        else if (zombieY > playerY)
            zombieY--;

        // Zombie attack
        if (playerX == zombieX && playerY == zombieY) {
            health -= 25;
            cout << "\nWARNING! ZOMBIE ATTACKED YOU!\n";
        }
    }

    if (health <= 0) {
        cout << "\nGAME OVER! ZOMBIE CAUGHT YOU!\n";
        cout << "Final Score: " << score << endl;
    }

    return 0;
}
