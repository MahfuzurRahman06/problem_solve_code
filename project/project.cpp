#include <bits/stdc++.h>
using namespace std;

struct Student {
    int id;
    string name;

    int math;
    int programming;
    int dataStructure;
    int english;

    double average;
    double gpa;
};

// Calculate GPA
double calculateGPA(Student &s) {

    s.average =(s.math + s.programming + s.dataStructure + s.english) / 4.0;

    if (s.average >= 80)
        s.gpa = 4.00;

    else if (s.average >= 75)
        s.gpa = 3.75;

    else if (s.average >= 70)
        s.gpa = 3.50;

    else if (s.average >= 65)
        s.gpa = 3.25;

    else if (s.average >= 60)
        s.gpa = 3.00;

    else if (s.average >= 55)
        s.gpa = 2.75;

    else if (s.average >= 50)
        s.gpa = 2.50;

    else if (s.average >= 45)
        s.gpa = 2.25;

    else if (s.average >= 40)
        s.gpa = 2.00;

    else
        s.gpa = 0.00;

    return s.gpa;
}


// Add student
void addStudent(vector<Student> &students) {

    Student s;

    cout << "\nEnter Student ID: ";
    cin >> s.id;

    cout << "Enter Student Name: ";
    cin >> s.name;

    cout << "Enter Math Mark: ";
    cin >> s.math;

    cout << "Enter Programming Mark: ";
    cin >> s.programming;

    cout << "Enter Data Structure Mark: ";
    cin >> s.dataStructure;

    cout << "Enter English Mark: ";
    cin >> s.english;

    calculateGPA(s);

    students.push_back(s);

    cout << "\nStudent added successfully!\n";
}


// Display one student
void displayStudent(Student s) {

    cout << "\n-----------------------------\n";

    cout << "ID              : " << s.id << endl;
    cout << "Name            : " << s.name << endl;

    cout << "Math            : " << s.math << endl;
    cout << "Programming     : " << s.programming << endl;
    cout << "Data Structure  : " << s.dataStructure << endl;
    cout << "English         : " << s.english << endl;

    cout << "Average         : " << s.average << endl;
    cout << "GPA             : " << s.gpa << endl;

    if (s.gpa >= 2.00)
        cout << "Status          : PASS\n";
    else
        cout << "Status          : FAIL\n";

    cout << "-----------------------------\n";
}


// Show all students
void showStudents(vector<Student> &students) {

    if (students.empty()) {
        cout << "\nNo student found.\n";
        return;
    }

    cout << "\n========== ALL STUDENTS ==========\n";

    for (Student s : students) {
        displayStudent(s);
    }
}


// Search student
void searchStudent(vector<Student> &students) {

    int id;

    cout << "\nEnter Student ID: ";
    cin >> id;

    bool found = false;

    for (Student s : students) {

        if (s.id == id) {

            displayStudent(s);

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nStudent not found!\n";
    }
}


// Update marks
void updateStudent(vector<Student> &students) {

    int id;

    cout << "\nEnter Student ID: ";
    cin >> id;

    bool found = false;

    for (Student &s : students) {

        if (s.id == id) {

            cout << "\nEnter new Math mark: ";
            cin >> s.math;

            cout << "Enter new Programming mark: ";
            cin >> s.programming;

            cout << "Enter new Data Structure mark: ";
            cin >> s.dataStructure;

            cout << "Enter new English mark: ";
            cin >> s.english;

            calculateGPA(s);

            cout << "\nMarks updated successfully!\n";

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nStudent not found!\n";
    }
}


// Delete student
void deleteStudent(vector<Student> &students) {

    int id;

    cout << "\nEnter Student ID: ";
    cin >> id;

    bool found = false;

    for (int i = 0; i < students.size(); i++) {

        if (students[i].id == id) {

            students.erase(students.begin() + i);

            cout << "\nStudent deleted successfully!\n";

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nStudent not found!\n";
    }
}


// Sort by GPA
void sortByGPA(vector<Student> &students) {

    sort(students.begin(), students.end(),
        [](Student a, Student b) {

            return a.gpa > b.gpa;
        });

    cout << "\nStudents sorted by GPA!\n";
}


// Show top student
void showTopStudent(vector<Student> &students) {

    if (students.empty()) {
        cout << "\nNo student found.\n";
        return;
    }

    int index = 0;

    for (int i = 1; i < students.size(); i++) {

        if (students[i].gpa > students[index].gpa) {
            index = i;
        }
    }

    cout << "\n========== TOP STUDENT ==========\n";

    displayStudent(students[index]);
}


// Main
int main() {

    vector<Student> students;

    int choice;

    while (true) {

        cout << "\n\n";
        cout << "============================================\n";
        cout << "       STUDENT RESULT MANAGEMENT SYSTEM\n";
        cout << "============================================\n";

        cout << "1. Add Student\n";
        cout << "2. Show All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Marks\n";
        cout << "5. Delete Student\n";
        cout << "6. Sort By GPA\n";
        cout << "7. Show Top Student\n";
        cout << "8. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                addStudent(students);
                break;

            case 2:
                showStudents(students);
                break;

            case 3:
                searchStudent(students);
                break;

            case 4:
                updateStudent(students);
                break;

            case 5:
                deleteStudent(students);
                break;

            case 6:
                sortByGPA(students);
                break;

            case 7:
                showTopStudent(students);
                break;

            case 8:
                cout << "\nThank you!\n";
                return 0;

            default:
                cout << "\nInvalid choice!\n";
        }
    }

    return 0;
}