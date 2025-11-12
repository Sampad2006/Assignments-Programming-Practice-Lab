/*
1. There are number of students. For every student roll (unique), name is to be
stored. For each subject, subject code and name is to be stored. A student can opt
for number of subjects. System should be able to maintain student list, subject list
and will be able to answer: i) which student has selected which subjects and ii)
for a subjects who are the students.
Design the classes and implement. For list consider memory data structure.

Name:Sampad De
Roll-002410501025
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Subject {
public:
    int code;
    string name;
    Subject(int c=0, string n="") { code=c; name=n; }
    void display() { cout << code << " - " << name << endl; }
};

class Student {
public:
    int roll;
    string name;
    vector<int> subjects;  // store subject codes

    Student(int r=0, string n="") { roll=r; name=n; }
    void display() { cout << roll << " - " << name << endl; }
};

class System {
    vector<Student> students;
    vector<Subject> subjects;
public:
    void addStudent(){
        int roll;
        string name;
        cout << "Enter student roll: "; cin >> roll;
        for(auto &s: students) if(s.roll==roll){ cout<<"Roll already exists!\n"; return; }
        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, name);
        students.push_back(Student(roll, name));
        cout << "Student added.\n";
    }

    void addSubject(){
        int code;
        string name;
        cout << "Enter subject code: "; cin >> code;
        for(auto &s: subjects) if(s.code==code){ cout<<"Subject code already exists!\n"; return; }
        cout << "Enter subject name: ";
        cin.ignore();
        getline(cin, name);
        subjects.push_back(Subject(code, name));
        cout << "Subject added.\n";
    }

    void assignSubjectToStudent(){
        int roll, code;
        cout << "Enter student roll: "; cin >> roll;
        Student *st = findStudent(roll);
        if(!st){ cout << "Student not found.\n"; return; }

        cout << "Enter subject code: "; cin >> code;
        Subject *sub = findSubject(code);
        if(!sub){ cout << "Subject not found.\n"; return; }

        for(auto c : st->subjects)
            if(c == code){ cout << "Already selected.\n"; return; }

        st->subjects.push_back(code);
        cout << "Subject assigned to student.\n";
    }

    void showSubjectsOfStudent(){
        int roll;
        cout << "Enter student roll: "; cin >> roll;
        Student *st = findStudent(roll);
        if(!st){ cout << "Student not found.\n"; return; }
        cout << "Subjects selected by " << st->name << ":\n";
        for(auto code : st->subjects){
            Subject *sub = findSubject(code);
            if(sub) sub->display();
        }
    }

    void showStudentsOfSubject(){
        int code;
        cout << "Enter subject code: "; cin >> code;
        Subject *sub = findSubject(code);
        if(!sub){ cout << "Subject not found.\n"; return; }
        cout << "Students who have selected " << sub->name << ":\n";
        for(auto &st : students){
            for(auto c : st.subjects){
                if(c == code) st.display();
            }
        }
    }

    void showAllStudents(){
        cout << "All Students:\n";
        for(auto &s : students) s.display();
    }

    void showAllSubjects(){
        cout << "All Subjects:\n";
        for(auto &s : subjects) s.display();
    }

private:
    Student* findStudent(int roll){
        for(auto &s : students)
            if(s.roll == roll) return &s;
        return nullptr;
    }

    Subject* findSubject(int code){
        for(auto &s : subjects)
            if(s.code == code) return &s;
        return nullptr;
    }
};

int main(){
    System sys;
    int choice;

    while(true){
        cout << "\n----- MENU -----\n";
        cout << "1. Add Student\n";
        cout << "2. Add Subject\n";
        cout << "3. Assign Subject to Student\n";
        cout << "4. Show Subjects of a Student\n";
        cout << "5. Show Students of a Subject\n";
        cout << "6. Display All Students\n";
        cout << "7. Display All Subjects\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice){
            case 1: sys.addStudent(); break;
            case 2: sys.addSubject(); break;
            case 3: sys.assignSubjectToStudent(); break;
            case 4: sys.showSubjectsOfStudent(); break;
            case 5: sys.showStudentsOfSubject(); break;
            case 6: sys.showAllStudents(); break;
            case 7: sys.showAllSubjects(); break;
            case 8: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice.\n";
        }
    }
}
