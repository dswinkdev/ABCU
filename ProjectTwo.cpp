//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Derricko Swink
// Version     : 1.0
// Copyright   : Copyright © 2023 SNHU COCE
// Description : Lab 5-2 Binary Search Tree
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Define the Course structure
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;

    Course(string number, string title, vector<string> prereqs)
        : courseNumber(number), courseTitle(title), prerequisites(prereqs) {}
};

// Define the Node for the BST
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course c) : course(c), left(nullptr), right(nullptr) {}
};

// Binary Search Tree to store Course data
class BST {
private:
    Node* root;

    // Helper function to insert a course into the tree
    Node* insert(Node* node, Course course) {
        if (node == nullptr) {
            return new Node(course);
        }
        if (course.courseNumber < node->course.courseNumber) {
            node->left = insert(node->left, course);
        } else {
            node->right = insert(node->right, course);
        }
        return node;
    }

    // Helper function for in-order traversal (sorted output)
    void inOrder(Node* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        cout << node->course.courseNumber << ": " << node->course.courseTitle << endl;
        inOrder(node->right);
    }

    // Helper function to search for a course
    Node* search(Node* node, const string& courseNumber) {
        if (node == nullptr || node->course.courseNumber == courseNumber) {
            return node;
        }
        if (courseNumber < node->course.courseNumber) {
            return search(node->left, courseNumber);
        }
        return search(node->right, courseNumber);
    }

public:
    BST() : root(nullptr) {}

    // Public insert function
    void insert(Course course) {
        root = insert(root, course);
    }

    // Display the sorted course list
    void displayCourseList() {
        cout << "\nCourse List (Sorted):\n";
        inOrder(root);
    }

    // Search for and display course details
    void displayCourse(const string& courseNumber) {
        Node* node = search(root, courseNumber);
        if (node) {
            cout << "Course Number: " << node->course.courseNumber << endl;
            cout << "Course Title: " << node->course.courseTitle << endl;
            cout << "Prerequisites: ";
            if (node->course.prerequisites.empty()) {
                cout << "None";
            } else {
                for (const string& prereq : node->course.prerequisites) {
                    cout << prereq << " ";
                }
            }
            cout << endl;
        } else {
            cout << "Course not found.\n";
        }
    }
};

// Function to split a string by a delimiter
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to load courses from a file into the BST
void loadCourses(const string& fileName, BST& bst) {
    ifstream file(fileName);
    if (!file) {
        cerr << "Error: File not found or cannot be opened.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        vector<string> tokens = split(line, ',');
        if (tokens.size() >= 2) {  // Ensure valid format
            string courseNumber = tokens[0];
            string courseTitle = tokens[1];
            vector<string> prerequisites(tokens.begin() + 2, tokens.end());
            Course course(courseNumber, courseTitle, prerequisites);
            bst.insert(course);
        }
    }
    cout << "Courses loaded successfully.\n";
}

int main() {
    BST bst;
    string fileName;
    int choice;

    cout << "Welcome to the ABCU Course Advising System\n";

    do {
        cout << "\nMenu Options:\n";
        cout << "1. Load Course Data\n";
        cout << "2. Print Course List\n";
        cout << "3. Print Course Details\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            fileName = "CS 300 ABCU_Advising_Program_Input.csv";
            loadCourses(fileName, bst);
            break;

        case 2:
            bst.displayCourseList();
            break;

        case 3:
            cout << "Enter the course number (ex. CSCI101): ";
            {
                string courseNumber;
                cin >> courseNumber;
                bst.displayCourse(courseNumber);
            }
            break;

        case 9:
            cout << "Exiting the program. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Please select a valid option.\n";
            break;
        }
    } while (choice != 9);

    return 0;
}
