/*
Modify the STRING class so that assigning/initializing a string by another will
not copy it physically but will keep a reference count, which will be incremented.
Reference value 0 means the space can be released


Name: Sampad De
Roll-002410501025
*/

#include <iostream>
#include <cstring>
using namespace std;

class String {
    struct SData {
        char *s;
        int ref;
        SData(const char *str="") {
            s = new char[strlen(str) + 1];
            strcpy(s, str);
            ref = 1;
        }
        ~SData() { delete[] s; }
    };
    SData *data;

public:
    String(const char *str="") {
        data = new SData(str);
    }

    String(const String &x) {
        data = x.data;
        data->ref++;
    }

    ~String() {
        if (--data->ref == 0)
            delete data;
    }

    String& operator=(const String &x) {
        if (this != &x) {
            if (--data->ref == 0)
                delete data;
            data = x.data;
            data->ref++;
        }
        return *this;
    }

    String operator+(const String &x) {
        char *temp = new char[strlen(data->s) + strlen(x.data->s) + 1];
        strcpy(temp, data->s);
        strcat(temp, x.data->s);
        String result(temp);
        delete[] temp;
        return result;
    }

    bool operator==(const String &x) { return strcmp(data->s, x.data->s) == 0; }
    bool operator<(const String &x) { return strcmp(data->s, x.data->s) < 0; }
    bool operator>(const String &x) { return strcmp(data->s, x.data->s) > 0; }

    void input() {
        char temp[100];
        cout << "Enter string: ";
        cin.ignore();
        cin.getline(temp, 100);
        if (--data->ref == 0)
            delete data;
        data = new SData(temp);
    }

    void display() const {
        cout << data->s << " (ref count: " << data->ref << ")\n";
    }
};

int main() {
    String a, b, c;
    int choice;

    while (true) {
        cout << "\n----- STRING (REF COUNT) MENU -----\n";
        cout << "1. Input String A\n";
        cout << "2. Input String B\n";
        cout << "3. Display Strings\n";
        cout << "4. Concatenate (A + B)\n";
        cout << "5. Assign A = B\n";
        cout << "6. Compare A and B\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter String A:\n";
            a.input();
        }
        else if (choice == 2) {
            cout << "Enter String B:\n";
            b.input();
        }
        else if (choice == 3) {
            cout << "String A: "; a.display();
            cout << "String B: "; b.display();
            cout << "String C: "; c.display();
        }
        else if (choice == 4) {
            c = a + b;
            cout << "Result (A + B): "; c.display();
        }
        else if (choice == 5) {
            a = b;
            cout << "A assigned from B.\n";
        }
        else if (choice == 6) {
            if (a == b) cout << "A and B are equal.\n";
            else if (a < b) cout << "A is smaller than B.\n";
            else cout << "A is greater than B.\n";
        }
        else if (choice == 7) {
            cout << "Exiting...\n";
            break;
        }
        else cout << "Invalid choice.\n";
    }

    return 0;
}
