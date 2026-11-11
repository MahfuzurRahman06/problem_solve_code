#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;


// ==========================================
// STRUCTURE FOR CALCULATION HISTORY
// ==========================================

struct Calculation
{
    string expression;
    double result;
};


// ==========================================
// ADD CALCULATION TO HISTORY
// ==========================================

void addHistory(vector<Calculation>& history,
                string expression,
                double result)
{
    Calculation c;

    c.expression = expression;
    c.result = result;

    history.push_back(c);
}


// ==========================================
// ADDITION
// ==========================================

void addition(vector<Calculation>& history)
{
    double a, b;

    cout << "\nEnter first number: ";
    cin >> a;

    cout << "Enter second number: ";
    cin >> b;

    double result = a + b;

    cout << "\nResult = " << result << endl;

    string expression =
        to_string(a) + " + " +
        to_string(b);

    addHistory(history, expression, result);
}


// ==========================================
// SUBTRACTION
// ==========================================

void subtraction(vector<Calculation>& history)
{
    double a, b;

    cout << "\nEnter first number: ";
    cin >> a;

    cout << "Enter second number: ";
    cin >> b;

    double result = a - b;

    cout << "\nResult = " << result << endl;

    string expression =
        to_string(a) + " - " +
        to_string(b);

    addHistory(history, expression, result);
}


// ==========================================
// MULTIPLICATION
// ==========================================

void multiplication(vector<Calculation>& history)
{
    double a, b;

    cout << "\nEnter first number: ";
    cin >> a;

    cout << "Enter second number: ";
    cin >> b;

    double result = a * b;

    cout << "\nResult = " << result << endl;

    string expression =
        to_string(a) + " * " +
        to_string(b);

    addHistory(history, expression, result);
}


// ==========================================
// DIVISION
// ==========================================

void division(vector<Calculation>& history)
{
    double a, b;

    cout << "\nEnter first number: ";
    cin >> a;

    cout << "Enter second number: ";
    cin >> b;

    if (b == 0)
    {
        cout << "\nError: Cannot divide by zero!\n";
        return;
    }

    double result = a / b;

    cout << "\nResult = " << result << endl;

    string expression =
        to_string(a) + " / " +
        to_string(b);

    addHistory(history, expression, result);
}


// ==========================================
// MODULUS
// ==========================================

void modulus(vector<Calculation>& history)
{
    int a, b;

    cout << "\nEnter first integer: ";
    cin >> a;

    cout << "Enter second integer: ";
    cin >> b;

    if (b == 0)
    {
        cout << "\nError: Cannot use modulus by zero!\n";
        return;
    }

    int result = a % b;

    cout << "\nResult = " << result << endl;

    string expression =
        to_string(a) + " % " +
        to_string(b);

    addHistory(history, expression, result);
}


// ==========================================
// POWER
// ==========================================

void power(vector<Calculation>& history)
{
    double base, exponent;

    cout << "\nEnter base: ";
    cin >> base;

    cout << "Enter exponent: ";
    cin >> exponent;

    double result = pow(base, exponent);

    cout << "\nResult = " << result << endl;

    string expression =
        to_string(base) + " ^ " +
        to_string(exponent);

    addHistory(history, expression, result);
}


// ==========================================
// SQUARE ROOT
// ==========================================

void squareRoot(vector<Calculation>& history)
{
    double number;

    cout << "\nEnter number: ";
    cin >> number;

    if (number < 0)
    {
        cout << "\nError: Square root of negative number "
             << "is not supported.\n";

        return;
    }

    double result = sqrt(number);

    cout << "\nResult = " << result << endl;

    string expression =
        "sqrt(" + to_string(number) + ")";

    addHistory(history, expression, result);
}


// ==========================================
// PERCENTAGE
// ==========================================

void percentage(vector<Calculation>& history)
{
    double number, percent;

    cout << "\nEnter number: ";
    cin >> number;

    cout << "Enter percentage: ";
    cin >> percent;

    double result =
        (number * percent) / 100.0;

    cout << "\nResult = " << result << endl;

    string expression =
        to_string(percent) + "% of " +
        to_string(number);

    addHistory(history, expression, result);
}


// ==========================================
// SHOW HISTORY
// ==========================================

void showHistory(vector<Calculation>& history)
{
    if (history.empty())
    {
        cout << "\nNo calculation history.\n";
        return;
    }

    cout << "\n";
    cout << "========================================\n";
    cout << "          CALCULATION HISTORY\n";
    cout << "========================================\n";

    for (int i = 0; i < history.size(); i++)
    {
        cout << i + 1 << ". "
             << history[i].expression
             << " = "
             << history[i].result
             << endl;
    }
}


// ==========================================
// SEARCH HISTORY
// ==========================================

void searchHistory(vector<Calculation>& history)
{
    if (history.empty())
    {
        cout << "\nNo calculation history.\n";
        return;
    }

    string keyword;

    cout << "\nEnter keyword to search: ";
    cin >> keyword;

    bool found = false;

    cout << "\nSearch Results:\n";

    for (int i = 0; i < history.size(); i++)
    {
        if (history[i].expression.find(keyword)
            != string::npos)
        {
            cout << i + 1 << ". "
                 << history[i].expression
                 << " = "
                 << history[i].result
                 << endl;

            found = true;
        }
    }

    if (!found)
    {
        cout << "No matching calculation found.\n";
    }
}


// ==========================================
// SORT HISTORY BY RESULT
// ==========================================

void sortHistory(vector<Calculation>& history)
{
    if (history.empty())
    {
        cout << "\nNo history to sort.\n";
        return;
    }

    sort(history.begin(),
         history.end(),
         [](Calculation a, Calculation b)
         {
             return a.result > b.result;
         });

    cout << "\nHistory sorted by result "
         << "from highest to lowest.\n";
}


// ==========================================
// CLEAR HISTORY
// ==========================================

void clearHistory(vector<Calculation>& history)
{
    history.clear();

    cout << "\nCalculation history cleared.\n";
}


// ==========================================
// MAIN FUNCTION
// ==========================================

int main()
{
    vector<Calculation> history;

    int choice;

    while (true)
    {
        cout << "\n\n";

        cout << "========================================\n";
        cout << "          C++ SMART CALCULATOR\n";
        cout << "========================================\n";

        cout << "1. Addition\n";
        cout << "2. Subtraction\n";
        cout << "3. Multiplication\n";
        cout << "4. Division\n";
        cout << "5. Modulus\n";
        cout << "6. Power\n";
        cout << "7. Square Root\n";
        cout << "8. Percentage\n";
        cout << "9. Show History\n";
        cout << "10. Search History\n";
        cout << "11. Sort History\n";
        cout << "12. Clear History\n";
        cout << "0. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;


        switch (choice)
        {
            case 1:
                addition(history);
                break;

            case 2:
                subtraction(history);
                break;

            case 3:
                multiplication(history);
                break;

            case 4:
                division(history);
                break;

            case 5:
                modulus(history);
                break;

            case 6:
                power(history);
                break;

            case 7:
                squareRoot(history);
                break;

            case 8:
                percentage(history);
                break;

            case 9:
                showHistory(history);
                break;

            case 10:
                searchHistory(history);
                break;

            case 11:
                sortHistory(history);
                break;

            case 12:
                clearHistory(history);
                break;

            case 0:
                cout << "\nThank you for using "
                     << "Smart Calculator!\n";

                return 0;

            default:
                cout << "\nInvalid choice!\n";
        }
    }

    return 0;
}