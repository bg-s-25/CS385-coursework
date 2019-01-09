/*******************************************************************************
* Name : student.cpp
* Author : Bobby Georgiou
* Date : 09/07/2018
* Description : Lab 2 - Student Class
* Pledge : "I pledge my honor that I have abided by the Stevens Honor System."
******************************************************************************/
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Student {
public:
    /**
     * Constructor for class Student
     */
    Student(string first, string last, float gpa, int id) : first_{first}, last_{last}, gpa_{gpa}, id_{id} { }

    /**
     * Return full name of Student using first and last fields
     */
    string full_name() const {
        return first_ + " " + last_;
    }

    /**
     * Accessor for id field
     */
    int id() const {
        return id_;
    }

    /**
     * Accessor for gpa field
     */
    float gpa() const {
        return gpa_;
    }

    /**
     * Print information (all fields) about the Student
     */
    void print_info() const {
        cout << std::fixed;
        cout << std::setprecision(2);
        cout << full_name() << ", " << "GPA: " << gpa_ << ", " << "ID: " << id_ << endl;
    }

private:
    string first_, last_;
    float gpa_;
    int id_;
};

/**
 * Takes a vector of Student objects, and returns a new vector
 * with all Students whose GPA < 1.0
 */
vector<Student> find_failing_students(const vector<Student> &students) {
    vector<Student> failing_students;
    for (const auto &student : students) { // for each Student in vector students
        if (student.gpa() < 1.0) {
            failing_students.push_back(student);
        }
    }
    return failing_students;
}

/**
 * Takes a vector of Student objects and prints them to the screen
 */
void print_students(const vector<Student> &students) {
    for (const auto &student : students) {
        student.print_info();
    }
}

/**
 * Allows the user to enter information for multiple students, then
 * find those student whose GPA is below 1.0 and prints them to the
 * screen
 */
int main() {
    string first_name, last_name;
    float gpa;
    int id;
    char repeat;
    vector<Student> students;

    // prompts
    do {
        cout << "Enter student's first name: ";
        cin >> first_name;
        cout << "Enter student's last name: ";
        cin >> last_name;
        gpa = -1;
        while (gpa < 0 || gpa > 4) {
            cout << "Enter student's GPA (0.0-4.0): ";
            cin >> gpa;
        }
        cout << "Enter student's ID: ";
        cin >> id;
        students.push_back(Student(first_name, last_name, gpa, id));
        cout << "Add another student to database (Y/N)? ";
        cin >> repeat;
    } while (repeat == 'Y' || repeat == 'y');

    // print all students
    cout << endl << "All students:" << endl;
    print_students(students);

    // find failing students, print failing students or 'None' if no failing students
    cout << endl << "Failing students:";
    vector<Student> failing_students = find_failing_students(students);
    if (failing_students.empty()) {
        cout << " None" << endl;
    } else {
        cout << endl;
        for (const auto &student : failing_students) {
            student.print_info();
        }
        cout << endl;
    }

    return 0;
}