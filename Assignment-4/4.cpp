/*
4. Design a STRING class, which will have the initialization facility similar to array
class. Provide support for
• Assigning one object for another,
• Two string can be concatenated using + operator,
• Two strings can be compared using the relational operators.

Name: Sampad De
Roll-002410501025
*/

#include <iostream>
#include <cstring>
using namespace std;

class String {
    char *s;
public:
    String(const char *str=""){
        s = new char[strlen(str)+1];
        strcpy(s, str);
    }

    String(const String &x){
        s = new char[strlen(x.s)+1];
        strcpy(s, x.s);
    }

    ~String(){ delete[] s; }

    String& operator=(const String &x){
        if(this != &x){
            delete[] s;
            s = new char[strlen(x.s)+1];
            strcpy(s, x.s);
        }
        return *this;
    }

    String operator+(const String &x){
        char *temp = new char[strlen(s) + strlen(x.s) + 1];
        strcpy(temp, s);
        strcat(temp, x.s);
        String result(temp);
        delete[] temp;
        return result;
    }

    bool operator==(const String &x){ return strcmp(s, x.s) == 0; }
    bool operator<(const String &x){ return strcmp(s, x.s) < 0; }
    bool operator>(const String &x){ return strcmp(s, x.s) > 0; }

    void input(){
        char temp[100];
        cout << "Enter string: ";
        cin.ignore();
        cin.getline(temp, 100);
        delete[] s;
        s = new char[strlen(temp)+1];
        strcpy(s, temp);
    }

    void display() const { cout << s << endl; }

    const char* getStr() const { return s; }
};

int main(){
    String a, b, c;
    int choice;

    while(true){
        cout << "\n----- STRING MENU -----\n";
        cout << "1. Input String A\n";
        cout << "2. Input String B\n";
        cout << "3. Display Strings\n";
        cout << "4. Concatenate (A + B)\n";
        cout << "5. Assign A = B\n";
        cout << "6. Compare A and B\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if(choice == 1){
            cout << "Enter String A:\n";
            a.input();
        }
        else if(choice == 2){
            cout << "Enter String B:\n";
            b.input();
        }
        else if(choice == 3){
            cout << "String A: "; a.display();
            cout << "String B: "; b.display();
        }
        else if(choice == 4){
            c = a + b;
            cout << "Result (A + B): ";
            c.display();
        }
        else if(choice == 5){
            a = b;
            cout << "A has been assigned B.\n";
        }
        else if(choice == 6){
            if(a == b) cout << "A and B are equal.\n";
            else if(a < b) cout << "A is smaller than B.\n";
            else cout << "A is greater than B.\n";
        }
        else if(choice == 7){
            cout << "Exiting...\n";
            break;
        }
        else cout << "Invalid choice.\n";
    }

    return 0;
}
