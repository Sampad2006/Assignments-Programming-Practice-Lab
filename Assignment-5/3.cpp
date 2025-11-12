/*
Employee has unique emp-id, name, designation and basic pay. An employee is
either a permanent one or contractual. For permanent employee salary is
computed as basic pay+ hra (30% of basic pay) + da (80% of basic pay). For
contractual employee it is basic pay + allowance (it is different for different
contractual employee). An employee pointer may point to either of the two
categories and accordingly the salary has to be created.
Design the classes and implement.

Name:Sampad De
Roll-002410501025
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Employee {
protected:
    int empID;
    string name;
    string designation;
    double basicPay;
public:
    Employee(int id=0, string n="", string d="", double b=0.0){
        empID = id; name = n; designation = d; basicPay = b;
    }
    virtual double computeSalary() = 0; // pure virtual
    virtual void display(){
        cout << empID << " | " << name << " | " << designation 
             << " | Basic: " << basicPay;
    }
    int getID(){ return empID; }
    virtual string type() = 0;
    virtual ~Employee(){}
};

class Permanent : public Employee {
public:
    Permanent(int id=0, string n="", string d="", double b=0.0)
        : Employee(id, n, d, b) {}
    double computeSalary(){
        double hra = 0.3 * basicPay;
        double da  = 0.8 * basicPay;
        return basicPay + hra + da;
    }
    void display(){
        Employee::display();
        cout << " | Type: Permanent | Salary: " << computeSalary() << endl;
    }
    string type(){ return "Permanent"; }
};

class Contractual : public Employee {
    double allowance;
public:
    Contractual(int id=0, string n="", string d="", double b=0.0, double a=0.0)
        : Employee(id, n, d, b), allowance(a) {}
    double computeSalary(){
        return basicPay + allowance;
    }
    void display(){
        Employee::display();
        cout << " | Type: Contractual | Allowance: " << allowance 
             << " | Salary: " << computeSalary() << endl;
    }
    string type(){ return "Contractual"; }
};

class Company {
    vector<Employee*> employees;
public:
    void addEmployee(){
        int id, choice;
        string name, desg;
        double basic, allowance;
        cout << "Enter Employee ID: "; cin >> id;
        for(auto e:employees) if(e->getID()==id){ cout<<"Employee ID exists!\n"; return; }
        cin.ignore();
        cout << "Enter Name: "; getline(cin, name);
        cout << "Enter Designation: "; getline(cin, desg);
        cout << "Enter Basic Pay: "; cin >> basic;
        cout << "Type (1=Permanent, 2=Contractual): "; cin >> choice;
        if(choice==1)
            employees.push_back(new Permanent(id, name, desg, basic));
        else{
            cout << "Enter Allowance: "; cin >> allowance;
            employees.push_back(new Contractual(id, name, desg, basic, allowance));
        }
        cout << "Employee added successfully.\n";
    }

    void showAll(){
        if(employees.empty()){ cout<<"No employees found.\n"; return; }
        cout << "\n--- Employee List ---\n";
        for(auto e:employees) e->display();
    }

    void showSalary(){
        int id;
        cout << "Enter Employee ID: "; cin >> id;
        for(auto e:employees)
            if(e->getID()==id){
                cout << "Employee " << e->type() << " Salary = " << e->computeSalary() << endl;
                return;
            }
        cout << "Employee not found.\n";
    }

    ~Company(){
        for(auto e:employees) delete e;
    }
};

int main(){
    Company comp;
    int choice;
    while(true){
        cout << "\n===== COMPANY MENU =====\n";
        cout << "1. Add Employee\n";
        cout << "2. Show All Employees\n";
        cout << "3. Show Salary of Employee\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice){
            case 1: comp.addEmployee(); break;
            case 2: comp.showAll(); break;
            case 3: comp.showSalary(); break;
            case 4: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}
