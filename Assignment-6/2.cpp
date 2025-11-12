/*
Consider a class Student with roll, name and score as attributes. Support to take and
display data is also there. One wants to works with array of Student objects. May
collect data for array elements, display those. In case index goes out of bounds,
exception is to be raised with suitable message.

Name:Sampad De
Roll-002410501025
*/
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

class OutOfBoundsException : public exception {
    string msg;
public:
    OutOfBoundsException(string m) : msg(m) {}
    const char* what() const noexcept override {
        return msg.c_str();
    }
};

class Student {
    int roll;
    string name;
    double score;
public:
    Student(int r=0, string n="", double s=0.0){
        roll=r; name=n; score=s;
    }

    void input(){
        cout << "Enter Roll: "; cin >> roll;
        cin.ignore();
        cout << "Enter Name: "; getline(cin, name);
        cout << "Enter Score: "; cin >> score;
    }

    void display(){
        cout << "Roll: " << roll << " | Name: " << name << " | Score: " << score << endl;
    }
};

class StudentArray {
    vector<Student> students;
public:
    void addStudent(){
        Student s;
        s.input();
        students.push_back(s);
        cout << "Student added successfully.\n";
    }

    void showAll(){
        if(students.empty()) cout << "No students found.\n";
        else {
            cout << "\n--- Student List ---\n";
            for(size_t i=0;i<students.size();i++){
                cout << "[" << i << "] ";
                students[i].display();
            }
        }
    }

    void showAtIndex(){
        int idx;
        cout << "Enter index to view: ";
        cin >> idx;
        try {
            if(idx < 0 || idx >= (int)students.size())
                throw OutOfBoundsException("Index out of range!");
            students[idx].display();
        }
        catch(const OutOfBoundsException &e){
            cout << "Exception: " << e.what() << endl;
        }
    }
};

int main(){
    StudentArray arr;
    int choice;
    while(true){
        cout << "\n===== STUDENT MENU =====\n";
        cout << "1. Add Student\n";
        cout << "2. Show All Students\n";
        cout << "3. Display Student by Index\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch(choice){
            case 1: arr.addStudent(); break;
            case 2: arr.showAll(); break;
            case 3: arr.showAtIndex(); break;
            case 4: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}
